/**

    @file      Interactables.cpp
    @brief     
    @details   ~
    @author    De'Lano Wilcox
    @date      29.05.2025
    @copyright � Alcoy Game Studios, 2025. All right reserved.

**/

#include <Core/Public/AGEpch.hpp>
#include "Interactables/Public/Interactables.h"
#include "Quests/Public/QuestComponent.h"
#include "VisualScripting/Public/VisualScriptingStructs.h"

namespace GameFramework
{
    void Interactable::OnCreate()
    {
        GetEntityHandle().AddComponent<AGE::MovementComponent>();
        m_StartLocation = GetEntityHandle().GetComponent<AGE::TransformComponent>().Translation;
    }
    void Interactable::OnDestroy()
    {
    }
    void Interactable::OnUpdate(AGE::TimeStep DeltaTime)
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
    AGE::Vector3& Interactable::GetActorLocation()
    {
        return m_Handle.GetComponent<AGE::TransformComponent>().Translation;
    }
    void Interactable::SetActorLocation(const AGE::Vector3& Location)
    {
        m_Handle.GetComponent<AGE::TransformComponent>().Translation = Location;
    }
    void Interactable::AddBeginPlayFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func)
    {
        m_BeginPlayFunctions.push_back(Func);
    }
    void Interactable::AddTickFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func)
    {
        m_TickFunctions.push_back(Func);
    }
    void Interactable::OnOverlapStart()
    {
        AGE::GameLogger::Trace("OverlapCollision Happened in Interactable");
    }
    void Interactable::OnOverlapStop()
    {
        AGE::GameLogger::Trace("OverlapCollision Ended in Interactable");
    }
    void Interactable::OnHit()
    {
        AGE::GameLogger::Trace("Cast Hit Happened in Interactable");
    }
    void Interactable::OnBeginPlay()
    {
        for (auto& F : m_BeginPlayFunctions)
        {
            F.Execute();
        }
    }
    void Interactable::Reset()
    {
        GetEntityHandle().GetComponent<AGE::TransformComponent>().Translation = m_StartLocation;
    }
}