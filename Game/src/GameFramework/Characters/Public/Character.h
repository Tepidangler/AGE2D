/**

    @file      Character.h
    @brief     Controllable Entity
    @details   
    @author    De'Lano Wilcox
    @date      30.05.2025
    @copyright � Alcoy Game Studios, 2025. All right reserved.

**/
#pragma once

#include "Core.h"
#include "Actors/Public/Actor.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"
#include "Structs/Public/Functions.h"
#include "Input/Public/InputComponent.h"
#include "Items/Public/Item.h"
#include "Items/Public/Weapon.h"
#include "Items/Public/Armor.h"
#include "GameStructs/Public/GameStructs.h"

namespace AGE
{
	struct AGENode;
}

namespace GameFramework
{
	
	class QuestComponent;

	class Character : public Actor
	{
	public:

		//Getters
		virtual AGE::Vector3 GetLocation() override {return m_Handle.GetComponent<AGE::TransformComponent>().Translation; }
		virtual AGE::Entity GetEntity() { return m_Handle; }
		virtual std::string GetScriptableEntityType() override { return m_EntityType; }
		virtual std::string GetName() override { return m_Name; }
		virtual void AddBeginPlayFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func) override;
		virtual void AddTickFunctions(AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity> Func) override;

		virtual void ClearFunctions() override
		{
			m_BeginPlayFunctions.clear();
			m_TickFunctions.clear();
		}

		AGE::Ref<InputComponent>& GetInputComponent() { return m_InputComponent; }

		//Script Construction
		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual void OnUpdate(AGE::TimeStep DeltaTime) override;
		virtual void OnEvent(AGE::Event& E) override;

		virtual void OnOverlapStart() override;
		virtual void OnOverlapStop() override;
		virtual void OnHit() override;

		virtual AGE::Vector3& GetActorLocation() override;
		virtual void SetLocation(const AGE::Vector3& Location) override { SetActorLocation(Location); }
		virtual void SetActorLocation(const AGE::Vector3& Location) override;
		virtual AGE::Ref<AGE::Texture2D> GetCharTex();
		virtual AGE::Ref<AGE::Texture2D> GetDiagTex();
		AGE::Ref<QuestComponent>& GetQuestComponent() { return m_QuestComponent; }
		virtual void SetupInput(AGE::Ref<InputComponent>& PlayerInputComponent);
		AGE::Ref<PlayerStats> GetStats() const {return m_Stats; }

	public:

		void MoveForward(float AxisValue);
		void MoveRight(float AxisValue);
		void CancelAction();

		void AddXP(int XP);


		bool operator < (const Character& O) const
		{
			return false;
		}

		bool bQuestCharacter = false;

	protected:
		virtual void OnBeginPlay() override;

	private:
		std::string m_EntityType = "Character";
		AGE::Ref<InputComponent> m_InputComponent;
		AGE::Ref<AGE::Scene> m_ActiveScene;
		AGE::Entity m_Handle;
		AGE::Ref<PlayerStats> m_Stats;

		std::vector<AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity>> m_BeginPlayFunctions;
		std::vector<AGE::AGEFunction<AGE::AGENode, AGE::ScriptableEntity>> m_TickFunctions;

		RTTR_ENABLE(GameFramework::Actor)
		RTTR_REGISTRATION_FRIEND
	};


}