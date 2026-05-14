#include "AGEpch.hpp"
#include "Parser/Public/JsonParser.h"
#include "Quests/Public/QuestManager.h"
#include "Inventory/Public/Inventory.h"
#include "GameStructs/Public/GameStructs.h"
namespace AGE
{
	/**
 * @brief Constructor for JsonParser class. 
 * Initializes the object with a JSON file path to parse.
 *
 * @param FilePath The path of the JSON file to be parsed.
 */
/**
 * @brief Constructs a JsonParser object with the given file path.
 * 
 * This function initializes a new instance of the JsonParser class, which is used to parse JSON files. The file path provided should point to a valid JSON file.
 * 
 * @param FilePath A string representing the path to the JSON file that will be parsed by this object.
 */
JsonParser::JsonParser(const std::string& FilePath)
	{

	}

	template<>
	
"/**\n * @brief This function saves a vector of QuestInfo objects to a JSON file.\n * \n * @param Filepath The path to the file where the data will be saved.\n * @param Data A reference to a vector containing the QuestInfo objects that will be serialized and written to the file.\n * \n * @return Returns true if successful, false otherwise. If the input vector is empty, this function returns false without writing anything to the file.\n * \n * @exception This function does not handle exceptions related to file I/O or JSON serialization. Any such errors should be handled by the caller of this function.\n */"
bool JsonParser::SaveJsonFile<Ref<GameFramework::QuestInfo>>(const std::filesystem::path& Filepath, std::vector<Ref<GameFramework::QuestInfo>>& Data)
	{
		std::ofstream Out(Filepath);
		if (Data.empty())
		{
			return false;
		}
		nlohmann::json SData = nlohmann::json::object();
		int x = 0;
		//SData
		for(auto& D : Data)
		{
			nlohmann::json QuestInfo;
			QuestInfo["quest_id"] = (uint64_t)D->ID;
			QuestInfo["quest_type"] = (int)D->GetQuestType();
			QuestInfo["title"] = D->QuestName;
			QuestInfo["description"] = D->QuestDescription;
			for (size_t i = 0; i < D->GetCheckpoints().size(); i++)
			{
				QuestInfo["checkpoints"]["id"] = i + 1;
				QuestInfo["checkpoints"]["text"] = D->GetCheckpointTexts()[i];

			}
			QuestInfo["rewards"]["xp"] = D->XPReward;
			QuestInfo["rewards"]["items"] = D->ItemRewards;
			SData[std::to_string(x)] = QuestInfo;
			x++;
		}
		Out << std::setw(4) << SData << std::endl;;
		Out.close();
		return true;
	}

	template<>
	"/**\n * @brief This function saves a vector of ItemInfo objects to a JSON file.\n * \n * @param Filepath The path where the JSON file will be saved.\n * @param Data A reference to the vector of ItemInfo objects that will be serialized and written to the file.\n *\n * @return Returns true if successful, false otherwise. If the data vector is empty, this function returns false without attempting to write anything.\n */"
/**
 * @brief Saves a vector of ItemInfo objects to a JSON file.
 * 
 * @param Filepath The path to the JSON file where the data will be saved.
 * @param Data A reference to the vector of ItemInfo objects that will be serialized and written to the file.
 * 
 * @return Returns true if successful, false otherwise. If the input vector is empty, this function returns false without writing anything to the file.
 */
bool JsonParser::SaveJsonFile<GameFramework::ItemInfo>(const std::filesystem::path& Filepath, std::vector<GameFramework::ItemInfo>& Data)
	{
		std::ofstream Out(Filepath);
		if (Data.empty())
		{
			return false;
		}
		nlohmann::json SData = nlohmann::json::object();
		int x = 0;

		for (auto& D : Data)
		{
			nlohmann::json ItemInfo;
			ItemInfo["item_name"] = D.Name;
			ItemInfo["item_type"] = D.ItemType;
			ItemInfo["item_buff_type"] = D.ItemBuffType;
			ItemInfo["hp"] = D.HP;
			ItemInfo["mp"] = D.MP;
			ItemInfo["strength"] = D.Strength;
			ItemInfo["speed"] = D.Speed;
			ItemInfo["defense"] = D.Defense;
			ItemInfo["isweapon"] = D.bIsWeapon;
			ItemInfo["isarmor"] = D.bIsArmor;
			ItemInfo["iskeyitem"] = D.bIsKeyItem;
			ItemInfo["id"] = (uint64_t)D.ID;
			SData[std::to_string(x)] = ItemInfo;
			x++;

		}
		Out << std::setw(4) << SData << std::endl;;
		Out.close();
		return true;
	}

	template<>
	/**
 * @brief This function saves a vector of PlayerStats objects to a JSON file.
 * 
 * @param Filepath The path to the JSON file where the data will be saved.
 * @param Data A reference to a vector containing the PlayerStats objects that will be serialized and written to the file.
 * @return bool Returns true if successful, false otherwise.
 * 
 * @note If the input vector is empty, the function returns false without attempting to write anything to the file.
 */
/**
 * @brief Saves a collection of player statistics into a JSON file.
 * 
 * This function takes an array of PlayerStats objects and writes them to a JSON file at the specified path. Each object is serialized as a separate JSON object in the output file, with each key-value pair representing a statistic (e.g., "name", "hp"). If the input vector is empty, this function returns false without writing anything to the file.
 * 
 * @param Filepath The path of the file where the data should be saved.
 * @param Data A reference to the array of PlayerStats objects that will be serialized and written to the file.
 * 
 * @return Returns true if successful, false otherwise.
 */
bool JsonParser::SaveJsonFile<GameFramework::PlayerStats>(const std::filesystem::path& Filepath, std::vector<GameFramework::PlayerStats>& Data)
	{
		std::ofstream Out(Filepath);
		if (Data.empty())
		{
			return false;
		}
		nlohmann::json SData = nlohmann::json::object();
		int x = 0;
		for (auto& D : Data)
		{
			nlohmann::json Stats;
			Stats["name"] = D.Name;
			Stats["hp"] = D.HP;
			Stats["mp"] = D.MP;
			Stats["strength"] = D.Strength;
			Stats["attack"] = D.Attack;
			Stats["magicattack"] = D.MagicAttack;
			Stats["defense"] = D.Defense;
			Stats["agility"] = D.Agility;
			Stats["speed"] = D.Speed;
			Stats["luck"] = D.Luck;
			Stats["hitrate"] = D.HitRate;
			SData[std::to_string(x)] = Stats;
			x++;
		}
		Out << std::setw(4) << SData << std::endl;;
		Out.close();
		return true;
	}

	template<>
	/**
 * This function saves a vector of EnemyStats objects to a JSON file at the specified path. The JSON file will contain an object for each EnemyStat in the vector, with keys corresponding to the members of the EnemyStat class and values being the respective member's value. If the directory for the given filepath does not exist, it is created.
 * 
 * @param Filepath The path where the JSON file will be saved.
 * @param Data A reference to the vector of EnemyStats objects that will be saved.
 * 
 * @return Returns true if successful, false otherwise. If the data is empty (i.e., no stats to save), it returns false.
 */

bool JsonParser::SaveJsonFile<GameFramework::EnemyStats>(const std::filesystem::path& Filepath, std::vector<GameFramework::EnemyStats>& Data)
	{
		if (!std::filesystem::exists(Filepath.parent_path()))
		{
			std::filesystem::create_directory(Filepath.parent_path());
		}
		std::ofstream Out(Filepath);
		if (Data.empty())
		{
			return false;
		}
		nlohmann::json SData = nlohmann::json::object();
		int x = 0;
		for (auto& D : Data)
		{
			nlohmann::json Stats;
			Stats["name"] = D.Name;
			Stats["hp"] = D.HP;
			Stats["mp"] = D.MP;
			Stats["strength"] = D.Strength;
			Stats["attack"] = D.Attack;
			Stats["magicattack"] = D.MagicAttack;
			Stats["defense"] = D.Defense;
			Stats["agility"] = D.Agility;
			Stats["speed"] = D.Speed;
			Stats["luck"] = D.Luck;
			Stats["hitrate"] = D.HitRate;
			SData[std::to_string(x)] = Stats;
			x++;
		}
		Out << std::setw(4) << SData << std::endl;;
		Out.close();
		return true;
	}


	/**
 * @brief Loads a JSON file from the given path.
 * 
 * This function attempts to load a JSON file at the provided path and returns its content as a nlohmann::json object. If the file does not exist, it logs an error message and returns an empty json object. If the file is empty or corrupted, it also logs a warning message and returns an empty json object.
 * 
 * @param Filepath The path to the JSON file to load.
 * @return nlohmann::json An object containing the content of the loaded JSON file. Returns an empty json object if the file does not exist or is empty/corrupted.
 */
/**
 * @brief Loads a JSON file from the given path.
 *
 * This function attempts to load a JSON file at the specified location and parse it into a nlohmann::json object. If the 
 * file does not exist, an empty json object is returned with a warning message. If the file exists but is empty or corrupted,
 * another warning message is returned.
 *
 * @param Filepath The path to the JSON file to load.
 * @return A nlohmann::json object containing the data from the loaded file, or an empty json object if the file does not 
 * exist or is empty/corrupted.
 */
nlohmann::json JsonParser::LoadJsonFile(const std::filesystem::path& Filepath)
	{
		if (!std::filesystem::exists(Filepath))
		{
			CoreLogger::Warn("{} doesn't exist!", Filepath.string());
			return nlohmann::json::object();
		}
		// Because json doesn't handle empty files, we must first check if the file is empty 
		// accomdating for both \n and EOF therefore our size should be 2 if it's empty 
		// and less if it's corrupted
		std::ifstream In(Filepath);
		In.seekg(std::ios::end);
#if __clang__
		long Size = In.tellg();
#else
		size_t Size = In.tellg();
#endif
		if (Size <= 2)
		{
			CoreLogger::Warn("{} was empty!", Filepath.string());
			return nlohmann::json::object();
		}
		nlohmann::json Data = nlohmann::json::parse(In);
		return Data;
	}
	/**
 * @brief Parses a JSON file and returns its content as a string.
 * @param FilePath The path to the JSON file that should be parsed.
 * @return A string containing the contents of the JSON file, or an empty string if the file could not be opened or parsed.
 */
/**
 * @brief Parses a JSON file and returns its content as a string.
 * @param FilePath The path to the JSON file that should be parsed.
 * @return A string containing the contents of the JSON file, or an empty string if the file could not be opened or parsed.
 */
std::string JsonParser::Parse(const std::string& FilePath)
	{
		std::ifstream In(FilePath);
		nlohmann::json data = nlohmann::json::parse(In);

		std::string Dump = data.array();
		return Dump;

	}
	/**
 * @brief Parses a JSON string and returns its array representation.
 *
 * This function takes in a JSON string, parses it using the nlohmann::json library, 
 * converts it to an array (if possible), and then returns this array as a string.
 *
 * @param String The input JSON string to be parsed.
 * @return A string representation of the parsed JSON data's array. If the JSON data is not an array, "Unknown" will be returned.
 */
/**
 * @brief Parses a JSON string and returns its array representation.
 *
 * This function takes in a JSON string, parses it using the nlohmann::json library, 
 * converts it to an array (if possible), and then returns this array as a string.
 *
 * @param String The input JSON string that needs to be parsed.
 * @return A string representation of the parsed JSON data's array part. If the JSON data is not an array, 
 *         or if it cannot be converted into a string, "Unknown" will be returned.
 */
std::string JsonParser::ParseString(const std::string& String)
	{
		nlohmann::json data = nlohmann::json::parse(String);

		std::string Dump = data.array();
		return Dump;
	}
}