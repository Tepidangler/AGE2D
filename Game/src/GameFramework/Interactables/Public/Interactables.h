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

		void OnCreate() override;

		void OnDestroy() override;

		void OnUpdate(AGE::TimeStep DeltaTime) override;

		AGE::Vector3 GetLocation() override { return GetActorLocation(); };
		AGE::Vector3& GetActorLocation() override;

		void SetLocation(const AGE::Vector3& Location)  override { SetActorLocation(Location); }
		void SetActorLocation(const AGE::Vector3& Location) override;

		std::string GetScriptableEntityType() override { return m_EntityType; }
		std::string GetName() override { return m_Name; }

		void AddBeginPlayFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func) override;
		void AddTickFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func) override;

		void OnOverlapStart() override;
		void OnOverlapStop() override;
		void OnHit() override;

	protected:

		void OnBeginPlay() override;
		void Reset() override;

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
