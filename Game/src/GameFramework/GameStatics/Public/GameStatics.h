#pragma once

#include "GameState/Public/GameState.h"
#include "SaveGame/Public/SaveGame.h"

namespace GameFramework
{
	class GameStatics
	{
	public:
		static void SaveGameToSlot(SaveGame& Save);

		static SaveGame LoadGameFromSlot(const char* Name, int Index);

		static AGE::Ref<GameState> GetGameState();

	private:
	};
}