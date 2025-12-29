#include "Actors/Public/Actor.h"
#include "Quests/Public/QuestComponent.h"
#include <Age.h>
#include <rttr/registration>

RTTR_REGISTRATION{
	rttr::registration::class_<GameFramework::Actor>("Actor")
	.method("GetActorLocation", &GameFramework::Actor::GetLocation)
	.method("GetName", &GameFramework::Actor::GetName)
	.method("SetActorLocation", &GameFramework::Actor::SetLocation)
	.method("OnOverlapStart", &GameFramework::Actor::OnOverlapStart)
	.method("OnOverlapStop", &GameFramework::Actor::OnOverlapStop)
	.method("OnHit", &GameFramework::Actor::OnHit)
	.property("Name", &GameFramework::Actor::m_Name)(
		rttr::metadata("Description", "A base actor capable of being placed in a game world."),
		rttr::metadata(AGE::MetaDataType::Scriptable, true)
		)
	.property("Quest Component", &GameFramework::Actor::m_QuestComponent)(
		rttr::metadata("Description", "The Quest Component associated with this actor"),
		rttr::metadata(AGE::MetaDataType::Scriptable, true)
		);


}

namespace GameFramework
{

	void Actor::OnCreate()
	{
		GetEntityHandle().AddComponent<AGE::MovementComponent>();
		m_StartLocation = GetEntityHandle().GetComponent<AGE::TransformComponent>().Translation;

	}
	void Actor::OnDestroy()
	{

	}
	void Actor::OnUpdate(AGE::TimeStep DeltaTime)
	{
		if (m_QuestComponent)
		{
			m_QuestComponent->OnUpdate(DeltaTime);
		}

		for (auto& F : m_TickFunctions)
		{
			F.Execute(DeltaTime);
		}
	}
	AGE::Vector3& Actor::GetActorLocation()
	{
		return m_Handle.GetComponent<AGE::TransformComponent>().Translation;
	}
	void Actor::SetActorLocation(const AGE::Vector3& Location)
	{
		m_Handle.GetComponent<AGE::TransformComponent>().Translation = Location;
	}
	void Actor::AddBeginPlayFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func)
	{
		m_BeginPlayFunctions.push_back(Func);
	}
	void Actor::AddTickFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func)
	{
		m_TickFunctions.push_back(Func);
	}
	void Actor::OnOverlapStart()
	{
		AGE::GameLogger::Trace("OverlapCollision Happened in Actor");
	}
	void Actor::OnOverlapStop()
	{
	}
	void Actor::OnHit()
	{
		AGE::GameLogger::Trace("Cast Hit Happened in Actor");
	}
	void Actor::OnBeginPlay()
	{
		for (auto& F : m_BeginPlayFunctions)
		{
			F.Execute();
		}

	}

	void Actor::Reset()
	{
		GetEntityHandle().GetComponent<AGE::TransformComponent>().Translation = m_StartLocation;
	}

}