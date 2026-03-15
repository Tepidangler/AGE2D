#pragma once
#include "Core/Public/Core.h"
#include "Events/Public/GameEvent.h"
#include "Scene/Public/Components.h"
#include "Scene/Public/ScriptableEntity.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"
#include "Math/Public/MathStructures.h"
#include "Actors/Public/Actor.h"
#include <functional>
#include <cinttypes>
#include "Core/Public/InputBinding.h"

namespace GameFramework
{
#if  0
	struct InputActionBinding
	{
	private:


	public:
		KeyState State;
		using ActionCallbackFn = std::function<void()>;

		ActionCallbackFn BindedFunction;

	public:
		InputActionBinding()
			:bPaired(false), Name(std::string()), bConsumeInput(true), bExecuteWhenPaused(false), Handle(-1), State(KeyState::Pressed){}

		InputActionBinding(const std::string& ActionName, const KeyState EventStatus)
			: bPaired(false), Name(ActionName), bConsumeInput(true), bExecuteWhenPaused(false),Handle(-1), State(EventStatus) {}

		InputActionBinding(const InputActionBinding&) = default;
		//InputActionBinding(const AGE::Ref<InputActionBinding>&) = default;

		//TODO: Consider Move Constructor

		std::string GetActionName() const { return Name; }
		bool IsPaired() const { return bPaired; }
		int32_t GetHandle() const { return Handle; }

		void GenerateNewHandle()
		{
			static int32_t sHandle = 1;
			Handle = sHandle++;
		}

		bool operator==(const InputActionBinding& rhs)
		{
			return (IsValid() && GetHandle() == rhs.GetHandle());
		}

		bool IsValid() { return Handle != -1; }

		void Execute()
		{
			(void)BindedFunction();
		}

		friend class InputComponent;
	};

	struct InputAxisBinding
	{
	public:
		std::string AxisName;
		float AxisValue;
		uint8_t bConsumeInput = 1;
		uint8_t bExecuteWhenPaused = 1;



		using AxisCallbackFn = std::function<void(float)>;

		AxisCallbackFn BindedFunction;

		InputAxisBinding()
			: AxisName(std::string()), AxisValue(0.f), bConsumeInput(true), bExecuteWhenPaused(false) {}
		InputAxisBinding(const std::string& Name)
			: AxisName(Name), AxisValue(0.f), bConsumeInput(true), bExecuteWhenPaused(false) {}

		template<typename T>
		void BindFunction(AxisCallbackFn Func)
		{
			BindedFunction = Func;
		}

		void Execute()
		{
			BindedFunction(AxisValue);
		}
	};
#endif

	namespace InputType
	{
		enum Type
		{
			Gamepad,
			KBM
		};
	}

	class InputComponent : public AGE::ScriptableEntity
	{
	public:

		void OnCreate() override;

		void OnUpdate(AGE::TimeStep DeltaTime) override;

		void OnEvent(AGE::Event& E) override;

		std::string GetScriptableEntityType() override { return m_Name; }

		bool OnAxisMoved(AGE::AxisEvent& E);
		bool OnButtonPressed(AGE::GamepadButtonPressedEvent& E);
		bool OnButtonReleased(AGE::GamepadButtonReleasedEvent& E);

		static void Serialize(AGE::DataWriter* Serializer, const InputComponent& Data)
		{

		}

		static void Deserialize(AGE::DataReader* Serializer, InputComponent& Data)
		{

		}

		std::vector<AGE::Ref<AGE::InputBinding>> m_ActionBindings;
		std::vector<AGE::Ref<AGE::InputBinding>> m_AxisBindings;
		bool bBlockInput = false;

		AGE::InputBinding& BindAction(const std::string& Action,  AGE::KeyState::State state, uint16_t button, InputType::Type type, AGE::InputBinding::ActionCallbackFn Func)
		{
//			InputActionBinding Binding(Action, state);
			switch (type)
			{
				case InputType::KBM:
				{
					m_ActionBindings.emplace_back();
					AddActionBinding(AGE::InputBinding::CreateKBMBinding(Action,(AGE::Key::Keys)button,AGE::Binding::Action));
					m_ActionBindings.back()->BindActionFunction((Func));
					m_AxisBindings.back()->SetInputType("KBM");
					return *m_ActionBindings.back().get();
				}
				case InputType::Gamepad:
				{
					m_ActionBindings.emplace_back(AGE::InputBinding::CreateGamepadBinding(Action,(AGE::GamePad::Buttons)button,AGE::Binding::Action));
					AddActionBinding(m_ActionBindings.back());
					m_ActionBindings.back()->BindActionFunction((Func));
					m_AxisBindings.back()->SetInputType("Gamepad");
					return *m_ActionBindings.back().get();
				}
				default:
				{
					AGE::CoreLogger::Error("Unknown Input Binding! Creating Invalid Type...");
					return *AGE::InputBinding::CreateInvalid().get();
				}
			}
		}

		AGE::Ref<AGE::InputBinding>& BindAxis(const std::string& Axis, uint16_t button, InputType::Type type, AGE::InputBinding::AxisCallbackFn Func)
		{
			switch (type)
			{
				case InputType::KBM:
				{
					m_AxisBindings.emplace_back(AGE::InputBinding::CreateKBMBinding(Axis,(AGE::Key::Keys)button, AGE::Binding::Axis));
					m_AxisBindings.back()->SetInputType("KBM");
					break;
				}
				case InputType::Gamepad:
				{
					m_AxisBindings.emplace_back(AGE::InputBinding::CreateGamepadBinding(Axis,(AGE::GamePad::Axes)button,AGE::Binding::Axis));
					m_AxisBindings.back()->SetInputType("Gamepad");
					break;
				}
			}
			m_AxisBindings.back()->BindAxisFunction(Func);
			return m_AxisBindings.back();
		}

		AGE::InputBinding& AddActionBinding(AGE::Ref<AGE::InputBinding> Binding)
		{

			AGE::InputBinding& BindRef = *m_ActionBindings.back().get();
			BindRef.GenerateNewHandle();

			if (BindRef.m_State == AGE::KeyState::Pressed || BindRef.m_State == AGE::KeyState::Released)
			{
				const AGE::KeyState::State PairedEvent = Binding->m_State == AGE::KeyState::Pressed ? AGE::KeyState::Released : AGE::KeyState::Pressed;

				for (int i = m_ActionBindings.size() - 2; i >= 0; i--)
				{
					AGE::InputBinding& Ref = *m_ActionBindings[(size_t)i].get();
					if (Ref.GetName() == BindRef.GetName())
					{
						if (Ref.IsPaired())
						{
							BindRef.SetPaired(true);
							break;
						}
						else if (Ref.m_State == PairedEvent)
						{
							Ref.SetPaired(true);
							BindRef.SetPaired(true);
						}
					}
				}
			}

			return BindRef;
		}

		void ShouldBlockInput(bool Block)
		{
			bBlockInput = Block;
		}

		bool IsBlockingInput() { return bBlockInput; }



	private:
		std::string m_Name = "Input Component";

		std::string FindCorrespondingAxisName(std::vector<std::pair<std::string, std::vector<uint8_t>>>& AxisBindings, uint8_t Key);
		std::string FindCorrespondingActionName(std::vector<std::pair<std::string, std::vector<uint8_t>>>& ActionBindings, uint8_t Key);


	};
}
