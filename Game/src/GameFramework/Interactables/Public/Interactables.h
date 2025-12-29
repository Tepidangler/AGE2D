/**

	@file      Interactables.h
	@brief
	@details   ~
	@author    De'Lano Wilcox
	@date      29.05.2025
	@copyright � Alcoy Game Studios, 2025. All right reserved.

**/
#pragma once

#include "Actors/Public/Actor.h"
#include "Structs/Public/Functions.h"
#include "Math/Public/Vector3.h"

namespace AGE
{
	struct AGENode;
}

namespace GameFramework
{
	class Interactable : public Actor
	{
	public:

		virtual void OnCreate() override;

		virtual void OnDestroy() override;

		virtual void OnUpdate(AGE::TimeStep DeltaTime) override;

		virtual AGE::Vector3 GetLocation() override { return GetActorLocation(); };
		virtual AGE::Vector3& GetActorLocation();

		virtual void SetLocation(const AGE::Vector3& Location)  override { SetActorLocation(Location); }
		virtual void SetActorLocation(const AGE::Vector3& Location);

		virtual std::string GetScriptableEntityType() override { return m_EntityType; }
		virtual std::string GetName() override { return m_Name; }

		virtual void AddBeginPlayFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func) override;
		virtual void AddTickFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func) override;

		virtual void OnOverlapStart() override;
		virtual void OnOverlapStop() override;
		virtual void OnHit() override;

	protected:

		virtual void OnBeginPlay() override;
		virtual void Reset() override;

	protected:
		AGE::Vector3 m_StartLocation = AGE::Vector3(0.f);

	private:
		std::string m_EntityType = "Interactable";
		std::string m_Name;
		AGE::Ref<QuestComponent> m_QuestComponent;
		AGE::Ref<AGE::Scene> m_ActiveScene;
		AGE::Entity m_Handle;

		std::vector<AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity>> m_BeginPlayFunctions;
		std::vector<AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity>> m_TickFunctions;

		friend class NodeEditorWindow;

	};
}
