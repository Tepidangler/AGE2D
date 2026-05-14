//
// Created by gdmgp on 12/5/2025.
//

#include "Core/Public/AGEpch.hpp"
#include "../Public/IniReader.h"
#include "Core/Public/Log.h"

namespace AGE
{
	/**
 * @brief Constructor for the IniReader class. Takes a path to an .ini file as input and loads it into memory.
 * @param Path The filesystem path to the .ini file that will be loaded.
 */
/**
 * @brief Constructor for the IniReader class. It takes a file path as input and loads the INI file at that location into memory.
 * @param Path The filesystem path to the INI file which is to be loaded.
 */
IniReader::IniReader(const std::filesystem::path &Path)
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
 * @brief This function reads a value from the INI file.
 *
 * The function retrieves a value associated with a given key in a specified section of the INI file. If the key does not exist, it logs an error message and returns an empty string. 
 *
 * @param Section The name of the section to read from.
 * @param Key The key for which to retrieve a value.
 * @param[out] HasMultipleValues A flag indicating whether the key has multiple values in the INI file.
 *
 * @return Returns the value associated with the given key, or an empty string if the key does not exist.
 */
/**
 * @brief This function reads a value from the INI file.
 *
 * The function takes three parameters - section name, key and a boolean reference to indicate if there are multiple values for the given key in the specified section. It returns an empty string if it fails to read the value or the key-value pair does not exist. 
 *
 * @param Section A constant reference to the section name where the key is located.
 * @param Key A constant reference to the key whose value needs to be retrieved.
 * @param HasMultipleValues A boolean reference that indicates if there are multiple values for the given key in the specified section.
 * 
 * @return Returns a string containing the value of the key-value pair, or an empty string if it fails to read the value or the key-value pair does not exist.
 */
std::string IniReader::Read(const std::string &Section, const std::string &Key, bool &HasMultipleValues)
	{
		std::string Result = "";

		Result =  m_Ini.GetValue(Section.c_str(),Key.c_str(),nullptr,&HasMultipleValues);

		if (Result.empty())
		{
			CoreLogger::Error("Unable To Read Value From Key {} in Section {}", Key, Section);
			return Result;
		}

		return Result;

	}

	/**
 * @brief Reads all values associated with a given key in a specified section of the INI file.
 * 
 * This function retrieves all values associated with a specific key within a particular section of the INI file. If no such key exists, it logs an error message and returns an empty vector. The results are sorted based on their load order as defined by CSimpleIniA::Entry::LoadOrder().
 * 
 * @param Section A string representing the name of the section in the INI file to be read from.
 * @param Key A string representing the key whose values are to be retrieved.
 * @return A vector of strings containing all values associated with the provided key in the specified section, sorted based on their load order. If no such key exists, an empty vector is returned.
 */
/**
 * @brief Reads all values associated with a given key in a specified section of the INI file.
 * 
 * This function retrieves all values associated with a specific key within a particular section of the INI file. If no such key exists, it returns an empty vector.
 * 
 * @param Section The name of the section to search for keys in.
 * @param Key The key whose associated values are being retrieved.
 * @return A vector containing all values associated with the provided key in the specified section. If no such key exists, it returns an empty vector.
 */
std::vector<std::string> IniReader::ReadAll(const std::string &Section, const std::string &Key)
	{
		CSimpleIniA::TNamesDepend Values;
		std::vector<std::string> Results;

		m_Ini.GetAllValues(Section.c_str(),Key.c_str(),Values);

		if (Values.empty())
		{
			CoreLogger::Error("Unable To Read Values From Key {} in Section {}", Key, Section);
			return Results;
		}

		Values.sort(CSimpleIniA::Entry::LoadOrder());

		for (const auto& V : Values)
		{
			Results.emplace_back(V.pItem);
		}

		return Results;
	}

} // AGE