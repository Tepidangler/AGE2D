#include <Core/Public/AGEpch.hpp>
#include "GameState/Public/GameState.h"
#include "GameStatics/Public/GameStatics.h"

namespace GameFramework
{
	GameState* GameState::s_GameState = nullptr;

	GameState::GameState()
	{
		s_GameState = this;
		AGE_CORE_ASSERT(s_GameState, "GameState Already Exists!");

		m_QuestManager = AGE::CreateRef<QuestManager>();
		m_PlayerParty = Party::Create(PartyType::Player);
		m_Inventory = m_PlayerParty->GetInventory();
	}
	GameState::~GameState()
	{

	}
	void GameState::SaveGameData(std::string SlotName, int Index)
	{
		SaveGame Save(SlotName, Index);

		GameStatics::SaveGameToSlot(Save);


	}
	SaveGame GameState::LoadGameData(std::string FileName, int Index)
	{
		SaveGame Save = std::move(GameStatics::LoadGameFromSlot(FileName.c_str(), Index)); // We're trying move here because making all of these copies seems kind of unnecessary

		return Save;
	}
	void GameState::SwitchLevel(const AGE::Ref<AGE::Scene>& Scene)
	{
		StoreActiveScene();
		m_ActiveScene->OnRuntimeStop();
		m_ActiveScene = Scene;
		m_ActiveScene->OnRuntimeStart();
	}
	void GameState::StoreActiveScene()
	{
		m_PreviousScene = m_ActiveScene;
	}
	void GameState::RestoreActiveScene()
	{
		m_ActiveScene->OnRuntimeStop();
		m_ActiveScene = m_PreviousScene;
		m_ActiveScene->OnRuntimeStart();
	}

	void GameState::OnUpdate(AGE::TimeStep DeltaTime)
	{

	}
}
