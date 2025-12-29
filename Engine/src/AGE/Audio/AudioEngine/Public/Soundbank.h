//
// Created by De'Lano Wilcox on 11/22/2025.
//
#pragma once
#ifndef AGE_SOUNDBANK_H
#define AGE_SOUNDBANK_H

#endif //AGE_SOUNDBANK_H

#include "Core/Public/UUID.h"
#include <string>
#include <filesystem>

namespace AGE
{
	class SoundBank
	{
	public:
		SoundBank(const std::filesystem::path& FilePath, UUID ID);
		SoundBank(const SoundBank&) = default;
		~SoundBank() = default;

		std::filesystem::path& GetFilePath() {return m_FilePath; }
		std::string& GetBankName() {return m_Name;}
		void SetBankName(const std::string& Name) {m_Name = Name;};
		uint32_t GetBankID() {return m_ID;}
		void SetBankID(uint32_t ID) {m_ID = ID;}

		UUID& GetAssetID() {return m_AssetID;}

		std::filesystem::path m_FilePath;
		std::string m_Name;
		uint32_t m_ID;
		UUID m_AssetID;
	};


}
