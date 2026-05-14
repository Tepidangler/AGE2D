//
// Created by gdmgp on 12/5/2025.
//

#include "Core/Public/AGEpch.hpp"
#include "../Public/IniWriter.h"
#include "Core/Public/Log.h"


namespace AGE
{
	/**
 * @brief Constructs an IniWriter object with a given path to the INI file.
 * @param Path The path to the INI file.
 * @return None
 */
/**
 * @brief Constructor for the IniWriter class.
 * 
 * This constructor takes a const reference to std::filesystem::path as an argument, which is used to initialize the member variable m_IniPath. It also sets the Unicode encoding for the INI file and attempts to load it from the provided path. If the loading fails (indicated by a return code less than 0), an error message is logged.
 * 
 * @param Path The path of the INI file to be loaded.
 */
IniWriter::IniWriter(const std::filesystem::path &Path)
		:m_IniPath(Path)
	{
		m_Ini.SetUnicode();

		SI_Error rc = m_Ini.LoadFile(Path.string().c_str());

		if (rc < 0)
		{
			CoreLogger::Error("Unable To Load {}", Path.string());
		}
	}

	/**
 * @brief Writes a key-value pair to the INI file.
 * 
 * This function writes a given value for a specific key in a specified section of an INI file. The operation is successful if the key was not present and has been inserted, or if the key was already present and has been updated.
 * 
 * @param Section The name of the section to write into.
 * @param Key The key to be written.
 * @param Value The value to be associated with the given key.
 * 
 * @return True if the operation is successful (key was inserted or updated), false otherwise.
 */
/**
 * @brief Writes a key-value pair to an INI file.
 *
 * This function writes the provided value for the given key in the specified section of the INI file. The function returns true if the operation was successful, false otherwise. 
 *
 * @param Section The name of the section where the key-value pair will be written.
 * @param Key The key that will be associated with the provided value.
 * @param Value The value to be written for the given key in the specified section.
 *
 * @return True if the operation was successful, false otherwise. 
 */
bool IniWriter::Write(const std::string &Section, const std::string &Key, const std::string &Value)
	{
		SI_Error rc = m_Ini.SetValue(Section.c_str(), Key.c_str(), Value.c_str());

		return rc == SI_INSERTED || rc == SI_UPDATED;
	}

	/**
 * @brief Saves the INI file with the given path and content.
 *
 * This function saves the current INI data to a file at the specified path. It uses the SaveFile method of the m_Ini object, which writes the data to the file system. The function returns true if the save operation was successful (indicated by SI_OK return code), and false otherwise.
 *
 * @return True if the INI file was successfully saved, False otherwise.
 */
/**
 * @brief Saves the INI file with the given path and content.
 *
 * This function saves the current INI data to a file at the specified path. It uses the SaveFile method of the m_Ini object, which writes the contents of the INI structure into the file. The function returns true if the save operation was successful (indicated by SI_OK return code), and false otherwise.
 *
 * @return True if the save operation was successful, false otherwise.
 */
bool IniWriter::SaveFile()
	{
		SI_Error rc = m_Ini.SaveFile(m_IniPath.c_str());

		return rc == SI_OK;

	}
} // AGE