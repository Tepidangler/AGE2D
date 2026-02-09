#include <Core/Public/AGEpch.hpp>
#include "Characters/Public/Character.h"
#include "Quests/Public/QuestComponent.h"
#include <Age.h>

RTTR_REGISTRATION{
	rttr::registration::class_<GameFramework::Character>("Character")
	.method("GetActorLocation", &GameFramework::Character::GetLocation)
	.method("GetName", &GameFramework::Character::GetName)
	.method("SetActorLocation", &GameFramework::Character::SetLocation)
	.method("OnOverlapStart", &GameFramework::Character::OnOverlapStart)
	.method("OnOverlapStop", &GameFramework::Character::OnOverlapStop)
	.method("OnHit", &GameFramework::Character::OnHit);
	//.property("Name", &GameFramework::Character::m_Name)(rttr::metadata("Description", "A base actor capable of being placed in a game world."))
	//.property("Quest Component", &GameFramework::Character::m_QuestComponent)(rttr::metadata("Description", "The Quest Component associated with this actor"));


}

namespace GameFramework
{
	template<>
	InputActionBinding& InputComponent::BindAction<Character>(const std::string& Action, KeyStatus Status, Character* Instigator, InputActionBinding::ActionCallbackFn Func)
	{
		InputActionBinding Binding(Action, Status);
		Binding.BindedFunction = Func;
		return AddActionBinding(Binding);
	}

	template<>
	AGE::Ref<InputAxisBinding>& InputComponent::BindAxis<Character>(const std::string& Axis, Character* Instigator, InputAxisBinding::AxisCallbackFn Func)
	{
		InputAxisBinding Binding(Axis);
		Binding.BindedFunction = Func;
		m_AxisBindings.emplace_back(AGE::CreateRef<InputAxisBinding>(Binding));
		return m_AxisBindings.back();
	}

	void Character::OnCreate()
	{
		m_Handle = GetEntityHandle();
		if (!GetEntityHandle().HasComponent<AGE::MovementComponent>())
		{
			GetEntityHandle().AddComponent<AGE::MovementComponent>();
		}
		m_InputComponent = AGE::CreateRef<InputComponent>();
		if (!GetEntityHandle().HasComponent<AGE::SpriteRendererComponent>())
		{
			GetEntityHandle().AddComponent<AGE::SpriteRendererComponent>();
		}
		if (!GetEntityHandle().HasComponent<AGE::RigidBody2DComponent>())
		{
			GetEntityHandle().AddComponent<AGE::RigidBody2DComponent>();
		}
		if (!GetEntityHandle().HasComponent<AGE::CapsuleCollider2DComponent>())
		{
			GetEntityHandle().AddComponent<AGE::CapsuleCollider2DComponent>();
		}
		SetupInput(m_InputComponent);

		if (bQuestCharacter && !m_QuestComponent)
		{
			m_QuestComponent = AGE::CreateRef<QuestComponent>();
		}

		m_StartLocation = m_Handle.GetComponent<AGE::TransformComponent>().Translation;

	}
	void Character::OnDestroy()
	{

	}
	void Character::OnUpdate(AGE::TimeStep DeltaTime)
	{
		Actor::OnUpdate(DeltaTime);
		m_InputComponent->OnUpdate(DeltaTime);

		if (m_QuestComponent)
		{
			m_QuestComponent->OnUpdate(DeltaTime);
		}

		for (auto& F : m_TickFunctions)
		{
			F.Execute(DeltaTime);
		}
	}
	void Character::OnEvent(AGE::Event& E)
	{
		m_InputComponent->OnEvent(E);
		if (m_QuestComponent)
		{
			m_QuestComponent->OnEvent(E);
		}
	}

	void Character::OnOverlapStart()
	{
		AGE::GameLogger::Trace("OverlapCollision Happened in Character");
	}

	void Character::OnOverlapStop()
	{
		AGE::GameLogger::Trace("OverlapCollision Ended in Character");
	}

	void Character::OnHit()
	{
		AGE::GameLogger::Trace("Cast Hit Happened in Character");
	}
	
	AGE::Vector3& Character::GetActorLocation()
	{
		return m_Handle.GetComponent<AGE::TransformComponent>().Translation;
	}

	void Character::SetActorLocation(const AGE::Vector3& Location)
	{
		m_Handle.GetComponent<AGE::TransformComponent>().Translation = Location;
	}

	AGE::Ref<AGE::Texture2D> Character::GetCharTex()
	{
		return m_Handle.GetComponent<AGE::SpriteRendererComponent>().Texture;
	}
	AGE::Ref<AGE::Texture2D> Character::GetDiagTex()
	{
		return m_Handle.GetComponent<AGE::SpriteRendererComponent>().DiagTexture;
	}
	void Character::OnBeginPlay()
	{
		Actor::OnBeginPlay();

		for (auto& F : m_BeginPlayFunctions)
		{
			F.Execute();
		}
	}
	void Character::SetupInput(AGE::Ref<InputComponent>& PlayerInputComponent)
	{
		AGE::GameLogger::Assert(!PlayerInputComponent, "Invalid Input Component");
		PlayerInputComponent->BindAxis<Character>("MoveForward", this, BIND_AXIS_FN(Character::MoveForward));
		PlayerInputComponent->BindAxis<Character>("MoveRight", this, BIND_AXIS_FN(Character::MoveRight));
		PlayerInputComponent->BindAction<Character>("Cancel", KeyStatus::Pressed, this, BIND_ACTION_FN(Character::CancelAction));
	}
	void Character::MoveForward(float AxisValue)
	{
		auto& Trans = GetComponent<AGE::TransformComponent>().Translation;

		float Speed = GetEntityHandle().GetComponent<AGE::MovementComponent>().Speed;

		if (AGE::Input::IsJoyStickConnected(AGE::JoyStick::JoyStick1))
		{
			Trans.y -= Speed * AxisValue; // This has to be -= because Up on the y axis is -1 and down is 1
			return;
		}
		
		{
			float Value = 1.f;
			if (AGE::Input::IsKeyPressed(AGE::Key::DOWN))
			{
				Trans.y -= Speed * Value;
			}
			if (AGE::Input::IsKeyPressed(AGE::Key::UP))
			{
				Trans.y += Speed * Value;
			}
		}



	}
	void Character::MoveRight(float AxisValue)
	{
		auto& Trans = GetComponent<AGE::TransformComponent>().Translation;

		float Speed = GetEntityHandle().GetComponent<AGE::MovementComponent>().Speed;

		if (AGE::Input::IsJoyStickConnected(AGE::JoyStick::JoyStick1))
		{
			Trans.x += Speed * AxisValue;
			return;
		}

		{
			float Value = 1.f;
			if (AGE::Input::IsKeyPressed(AGE::Key::RIGHT))
			{
				Trans.x += Speed * Value;
			}
			if (AGE::Input::IsKeyPressed(AGE::Key::LEFT))
			{
				Trans.x -= Speed * Value;
			}
		}
	}

	void Character::CancelAction()
	{
	}

	void Character::AddXP(int XP)
	{

	}




	void Character::AddBeginPlayFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func)
	{
		m_BeginPlayFunctions.push_back(Func);
	}

	void Character::AddTickFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func)
	{
		m_TickFunctions.push_back(Func);
	}

}

