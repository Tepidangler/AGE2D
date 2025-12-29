#pragma once
#include "Core/Public/Core.h"
#include "Core/Public/Buffer.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"

namespace GameFramework
{

	class SaveGame final
	{

	public:

		SaveGame();
		SaveGame(std::string Name, int Index);
		SaveGame(const SaveGame&) = default;
		SaveGame(SaveGame&& Other) noexcept
		{
			this->m_SlotName = Other.m_SlotName;
			this->m_Index = Other.m_Index;
			this->m_Version = Other.m_Version;
			this->m_Data = Other.m_Data;
			Other.~SaveGame(); // Leaving this comment here because if something goes wrong this is probably the offender
		}

		~SaveGame();

		std::string GetSlotName() { return m_SlotName; }
		int GetIndex() { return m_Index; }

		template<class T>
		void SetGameData(const T& Data)
		{
			m_Data->Allocate(sizeof(T));
			m_Data->Write((uint8_t)Data);

		}

		void SetSlotName(std::string& Name) { m_SlotName = Name; }
		void SetIndex(int Index) { m_Index = Index; }

		void CreateSaveFile(const std::string& FileName);

		SaveGame& LoadSaveFile(const std::string& FileName);


	private:
		std::string m_SlotName;

		AGE::Ref<AGE::Buffer> m_Data;

		int m_Index;
		int m_Version = 1;
	};
}
