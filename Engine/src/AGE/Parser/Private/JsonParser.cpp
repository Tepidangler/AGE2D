#include "AGEpch.hpp"
#include "Parser/Public/JsonParser.h"
#include "Quests/Public/QuestManager.h"
#include "Inventory/Public/Inventory.h"
#include "GameStructs/Public/GameStructs.h"
namespace AGE
{
	JsonParser::JsonParser(const std::string& FilePath)
	{

	}

	template<>
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
			for (int i = 0; i < D->GetCheckpoints().size(); i++)
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
		size_t Size = In.tellg();
		if (Size <= 2)
		{
			CoreLogger::Warn("{} was empty!", Filepath.string());
			return nlohmann::json::object();
		}
		nlohmann::json Data = nlohmann::json::parse(In);
		return Data;
	}
	std::string JsonParser::Parse(const std::string& FilePath)
	{
		std::ifstream In(FilePath);
		nlohmann::json data = nlohmann::json::parse(In);

		std::string Dump = data.array();
		return Dump;

	}
	std::string JsonParser::ParseString(const std::string& String)
	{
		nlohmann::json data = nlohmann::json::parse(String);

		std::string Dump = data.array();
		return Dump;
	}
}