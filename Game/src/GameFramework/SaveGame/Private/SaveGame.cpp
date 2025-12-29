#include <Core/Public/AGEpch.hpp>
#include <Age.h>
#include "SaveGame/Public/SaveGame.h"
#include "Core/Public/Buffer.h"

namespace GameFramework
{
	SaveGame::SaveGame()
	{
		m_SlotName = "Default";
		m_Index = 0;
	}
	SaveGame::SaveGame(std::string Name, int Index)
	{
		m_SlotName = Name;
		m_Index = Index;
	}
	SaveGame::~SaveGame()
	{

	}
	void SaveGame::CreateSaveFile(const std::string& FileName)
	{
		AGE::FileStreamWriter stream(FileName);
		std::string Header = "AGE_SAVEGAME";
		stream.WriteString(Header);
		stream.WriteRaw<size_t>(m_SlotName.size());
		stream.WriteString(m_SlotName);
		stream.WriteRaw<int>(m_Version);
		stream.WriteRaw<int>(m_Index);
		stream.WriteObject<AGE::Buffer>(*m_Data.get());
	}

	SaveGame& SaveGame::LoadSaveFile(const std::string& FileName)
	{
		AGE::FileStreamReader stream(FileName);
		std::string Header;
		stream.ReadString(Header);

		if (Header.compare("AGE_SAVEGAME") != 0)
		{
			AGE_GAME_ERROR("Unable to Load {0}! \n\t Invalid Header!", FileName);
			return *this;
		}

		AGE_GAME_INFO("Header Sucessfully Read!");
		stream.ReadString(m_SlotName);
		stream.ReadRaw<int>(m_Version);
		stream.ReadRaw<int>(m_Index);
		stream.ReadObject<AGE::Buffer>(*m_Data.get());
		AGE_GAME_INFO("{0} Loaded Successfully", FileName);

		return *this;

	}

}