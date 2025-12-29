#include <Core/Public/AGEpch.hpp>
#include "GameStatics/Public/GameStatics.h"
#include <rttr/registration>

namespace GameFramework
{
	void GameStatics::SaveGameToSlot(SaveGame& Save)
	{
		AGE_PROFILE_FUNCTION();
		std::string Ext = ".sav";
		std::string NewStr; 
		NewStr.append("Saves/");
		NewStr.append(Save.GetSlotName());
		NewStr.append(Ext);

		Save.CreateSaveFile(NewStr);
	}

	SaveGame GameStatics::LoadGameFromSlot(const char* Name, int Index)
	{
		AGE_PROFILE_FUNCTION();

		std::string NewStr;
		NewStr.append(Name);
		SaveGame Save;
		Save.LoadSaveFile(NewStr);

		return Save;
	}

	AGE::Ref<GameState> GameStatics::GetGameState()
	{
		return GameState::Get()->GetSharedPtr();
	}
}