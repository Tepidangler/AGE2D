#pragma once
#include <Age.h>
#include "Party/Public/Party.h"
#include "Inventory/Public/Inventory.h"
#include "SaveGame/Public/SaveGame.h"
#include "Quests/Public/QuestManager.h"


namespace GameFramework
{
	class GameState : public std::enable_shared_from_this<GameState>
	{

	public:

		GameState();
		~GameState();

		void SaveGameData(std::string SlotName, int Index);
		SaveGame LoadGameData(std::string FileName, int Index);
		void SwitchLevel(const AGE::Ref<AGE::Scene>& Scene);
		void StoreActiveScene();
		void RestoreActiveScene();

		void OnEvent(AGE::Event& Event);

		void OnUpdate(AGE::TimeStep DeltaTime);


		//Getters
		inline static GameState* Get() { return s_GameState; }

		AGE::Ref<Party>& GetParty() { return m_PlayerParty; }
		AGE::Ref<Inventory>& GetInventory() { return m_Inventory; }
		AGE::Ref<QuestManager>& GetQuestManager() { return m_QuestManager; }
		AGE::Ref<GameState> GetSharedPtr() { return shared_from_this(); }

	protected:
		//Setters
		void SetParty(AGE::Ref<Party> Party) { m_PlayerParty = Party; }
		void SetInventory(AGE::Ref<Inventory> Inventory) { m_Inventory = Inventory; }

		AGE::Ref<QuestManager> m_QuestManager;

		AGE::Ref<Party> m_PlayerParty;

		AGE::Ref<Inventory> m_Inventory;

		AGE::Ref<AGE::Scene> m_ActiveScene;

		AGE::Ref<AGE::Scene> m_PreviousScene;

		std::array<AGE::Ref<SaveGame>, 10> m_SaveGames;

		std::vector<AGE::Entity> m_EntityHandles;



	private:
		static GameState* s_GameState;
	};
}