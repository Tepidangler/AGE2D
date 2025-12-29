#include <Core/Public/AGEpch.hpp>
#include <Age.h>
#include "Quests/Public/QuestManager.h"
#include "Parser/Public/JsonParser.h"
#include "Project/Public/Project.h"
#include "GameStatics/Public/GameStatics.h"
#include "Inventory/Public/Inventory.h"

namespace GameFramework
{
	namespace Utils
	{
		static void StripExtension(std::string& Filename)
		{

			std::string base = Filename.substr(Filename.find_last_of("/\\") + 1);
			std::string::size_type const p(base.find_last_of('.'));
			std::string filename = base.substr(0, p);
			Filename = filename;
		}
	}

	QuestManager::QuestManager()
	{

	}

	QuestManager::~QuestManager()
	{
		//Here we should serialize the quests
		if (!m_Quests.empty())
		{
			std::string Name = AGE::Project::GetActive()->GetConfig().Name;
			Utils::StripExtension(Name);
			Name.append("_Quests.json");
			SerializeQuests(Name);
		}

	}

	std::vector<AGE::Ref<QuestInfo>> QuestManager::GetActiveQuests()
	{
		std::vector<AGE::Ref<QuestInfo>> ActiveQuests;

		for (auto& Q : m_Quests)
		{
			if (Q.second->IsActive())
			{
				ActiveQuests.push_back(Q.second);
			}
		}

		if (ActiveQuests.size() > 0)
		{
			return ActiveQuests;
		}

		return std::vector<AGE::Ref<QuestInfo>>();
	}

	void QuestManager::AddQuest(const QuestInfo& Quest)
	{
		m_Quests[Quest.ID] = AGE::CreateRef<QuestInfo>(Quest);
	
	}

	bool QuestManager::StartQuest(const AGE::UUID QuestID)
	{
		m_Quests[QuestID]->StartQuest();

		return m_Quests[QuestID]->Status == QuestCompletionStatus::Active;
	}

	//If this returns false then the quest is complete
	bool QuestManager::AdvanceQuest(const AGE::UUID QuestID)
	{
		if (m_Quests[QuestID]->AdvanceCheckpoint())
		{
			return true;
		}
		else
		{
			GameStatics::GetGameState()->GetParty()->AddXP(m_Quests[QuestID]->XPReward);
			GameStatics::GetGameState()->GetInventory()->AddReward(m_Quests[QuestID]->ItemRewards);
			if (m_Quests[QuestID]->HasDependentQuest())
			{
				m_Quests[m_Quests[QuestID]->DependentQuestID]->Status = QuestCompletionStatus::Available;
				return true;
			}

			return false;
		}
		
		return false;
	}

	QuestType& QuestManager::GetQuestType(const AGE::UUID QuestID)
	{
		return m_Quests[QuestID]->GetQuestType();
	}

	AGE::Ref<QuestInfo>& QuestManager::GetQuest(const AGE::UUID QuestID)
	{
		return m_Quests[QuestID];
	}

	AGE::Ref<QuestInfo> QuestManager::GetQuest(const std::string QuestName)
	{
		for (auto& Q : m_Quests)
		{
			if (Q.second->QuestName == QuestName)
			{
				return Q.second;
			}
		}

		return AGE::Ref<QuestInfo>(nullptr);
	}

	bool QuestManager::SerializeQuests(const std::string& FileName)
	{
		AGE::JsonParser Parser;
		std::vector <AGE::Ref<QuestInfo>> Info;

		for (auto& I : m_Quests)
		{
			Info.emplace_back(I.second);
		}

		return Parser.SaveJsonFile(AGE::Project::GetActive()->GetAssetDirectory().string() + "/Quests/" + FileName, Info);
	}

	bool QuestManager::DeserializeQuests(const std::filesystem::path& FilePath)
	{
		return LoadQuests(FilePath);
	}

	//TODO: In it's current state this works however, I'll need to test with a single file that contains multiple quests and possibly write a new function
	//to handle files like that if any kind of changes need to be made in the process.
	bool QuestManager::LoadQuests(const std::filesystem::path& Filepath)
	{
		//Here we'll parse Quest from some sort of file
		QuestInfo Quest;

		nlohmann::json QuestData = AGE::JsonParser::LoadJsonFile(Filepath);
		for (auto& D : QuestData)
		{
			Quest.ID = D.at("quest_id").get<uint64_t>();
			Quest.Type = (QuestType)D.at("quest_type").get<int>();
			D.at("title").get_to(Quest.QuestName);
			D.at("description").get_to(Quest.QuestDescription);
			int i = 1;
			std::string Text;
			if (D.contains("checkpoints"))
			{
				for (auto& C : D.at("checkpoints"))
				{


					if (C.find("item") != C.end())
					{
						Quest.AddCheckPoint(i, false);
						C.at("type").get_to(Text);
						Text.append(" ");
						std::string ToAppend;
						C.at("item").get_to(ToAppend);
						Text.append(ToAppend);
						Quest.AddCheckpointText(Text);
						continue;
					}
					if (C.find("location") != C.end())
					{
						i++;
						Quest.AddCheckPoint(i, false);
						C.at("type").get_to(Text);
						Text.append(" ");
						std::string ToAppend;
						C.at("location").get_to(ToAppend);
						Text.append(ToAppend);
						Quest.AddCheckpointText(Text);
						continue;
					}

				}
			}

			if (D.at("rewards").contains("xp"))
			{
				D.at("rewards")["xp"].get_to(Quest.XPReward);
			}
			if (D.at("rewards").contains("items"))
			{
				D.at("rewards")["items"].get_to(Quest.ItemRewards);
			}
			m_Quests[Quest.ID] = AGE::CreateRef<QuestInfo>(Quest);
		}
		//Quest.Type = (QuestType)QuestData.at("quest_type").get<int>();
		//Quest.Type = (QuestType)QuestData["quest_type"].template get<int>();

		


		return true; // We'll add some way to return false if things don't work out down the line.
	}
}
