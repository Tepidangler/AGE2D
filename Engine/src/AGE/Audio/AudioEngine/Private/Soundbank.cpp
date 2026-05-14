//
// Created by De'Lano Wilcox on 11/22/2025.
//

#include "Audio/AudioEngine/Public/Soundbank.h"

namespace AGE
{
	/**
 * @brief Constructs a SoundBank object with the given file path and UUID.
 * @param FilePath The path to the sound bank file.
 * @param ID The unique identifier for this sound bank.
 * 
 * This function initializes a new SoundBank object by setting its file path and UUID, and also sets the name of the sound bank as the filename from the given path.
 */
/**
 * @brief Constructs a SoundBank object from the given file path and UUID.
 * @param FilePath The path to the sound bank file.
 * @param ID The unique identifier for this sound bank.
 */
SoundBank::SoundBank(const std::filesystem::path& FilePath, UUID ID)
		:m_FilePath(FilePath), m_AssetID(ID)
	{
		m_Name = m_FilePath.filename().string();
	}
}
