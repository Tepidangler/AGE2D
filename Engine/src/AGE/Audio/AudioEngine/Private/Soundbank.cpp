//
// Created by De'Lano Wilcox on 11/22/2025.
//

#include "Audio/AudioEngine/Public/Soundbank.h"

namespace AGE
{
	SoundBank::SoundBank(const std::filesystem::path& FilePath, UUID ID)
		:m_FilePath(FilePath), m_AssetID(ID)
	{
		m_Name = m_FilePath.filename().string();
	}
}
