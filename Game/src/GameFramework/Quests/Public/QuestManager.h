#pragma once
#include "Core/Public/Core.h"
#include "Actors/Public/Actor.h"
#include <rttr/registration>

#include "crude_json.h"

namespace GameFramework
{

	enum class QuestCompletionStatus : uint8_t
	{
		Unavailable = 0,
		Available =1,
		Active = 2,
		Completed = 3
	};

	enum class QuestType : uint8_t
	{
		Main = 0,
		Side = 1
	};
	RTTR_REGISTRATION
	{
		rttr::registration::enumeration<QuestCompletionStatus>("QuestCompletionStatus")(
			rttr::value("Unavailable", QuestCompletionStatus::Unavailable),
			rttr::value("Available", QuestCompletionStatus::Available),
			rttr::value("Active", QuestCompletionStatus::Active),
			rttr::value("Completed", QuestCompletionStatus::Completed)
			);

		rttr::registration::enumeration<QuestType>("QuestType")(
			rttr::value("Main", QuestType::Main),
			rttr::value("Side", QuestType::Side)
			);
	}
	struct QuestInfo
	{
	public:

		QuestInfo()
			: ID(AGE::UUID()) {}
		QuestInfo(const QuestInfo&) = default;

		std::string QuestName;
		std::string QuestDescription;

		AGE::UUID ID;

		AGE::UUID DependentQuestID;

		std::string CurrentCheckpointText;
		
		AGE::Ref<Actor> QuestGiver;

		int CurrentCheckpoint = 0;

		int XPReward = 0;
		std::vector<std::string> ItemRewards;

		void AddCheckpoint()
		{
			int CurrentCheckpointSize = (int)Checkpoints.size();
			Checkpoints.emplace(std::pair<int,bool>(CurrentCheckpointSize, false ));
			CheckpointTexts.emplace_back(std::string(" "));
		}
		std::map<int, bool>& GetCheckpoints() { return Checkpoints; }
		std::vector<std::string>& GetCheckpointTexts() { return CheckpointTexts; }
		QuestType& GetQuestType() { return Type; }
		void SetQuestType(QuestType QType) { Type = QType; }

	private:

		std::string& GetDescription()
		{
			return QuestDescription;
		}


		void MakeQuestAvailable()
		{
			Status = QuestCompletionStatus::Available;		
		}

		void StartQuest()
		{
			Status = QuestCompletionStatus::Active;
		}

		//If this returns false then the quest is complete
		bool AdvanceCheckpoint()
		{
			Checkpoints[CurrentCheckpoint] = true;
			if (CurrentCheckpoint == Checkpoints.size() - 1)
			{
				Status = QuestCompletionStatus::Completed;
				CurrentCheckpointText = std::string();
				return false;
			}
			else
			{
				CurrentCheckpoint++;
				CurrentCheckpointText = CheckpointTexts[CurrentCheckpoint];
				return true;
			}

		}

		bool IsActive()
		{

			return Status == QuestCompletionStatus::Active;
		}
		
		bool IsCompleted()
		{
			return Status == QuestCompletionStatus::Completed;
		}


		void AddCheckPoint(int Pos, bool Completed)
		{
			Checkpoints[Pos] = Completed;
		}

		void AddCheckpointText(const std::string& Text)
		{
			CheckpointTexts.push_back(Text);
		}

		bool HasDependentQuest()
		{
			if (DependentQuestID)
			{
				return true;
			}

			return false;
		}

		std::map<int, bool> Checkpoints;
		std::vector<std::string> CheckpointTexts;
		QuestCompletionStatus Status = QuestCompletionStatus::Unavailable;
		QuestType Type = QuestType::Main;

		friend class QuestManager;
	};

	class QuestManager
	{
	public:

		QuestManager();
		QuestManager(const QuestManager&) = default;
		QuestManager(QuestManager&&) = delete;
		virtual ~QuestManager();

		bool LoadQuests(const std::filesystem::path& Filepath);

		//Getters
		std::unordered_map<AGE::UUID, AGE::Ref<QuestInfo>>& GetQuests() { return m_Quests; }

		std::vector<AGE::Ref<QuestInfo>> GetActiveQuests();
		void AddQuest(const QuestInfo& Quest);
		bool StartQuest(const AGE::UUID QuestID);
		bool AdvanceQuest(const AGE::UUID QuestID);

		QuestType& GetQuestType(const AGE::UUID QuestID);

		AGE::Ref<QuestInfo>& GetQuest(const AGE::UUID QuestID);
		AGE::Ref<QuestInfo> GetQuest(const std::string QuestName);

	private:
		bool SerializeQuests(const std::string& FileName);
		bool DeserializeQuests(const std::filesystem::path& FilePath);
	private:
		std::unordered_map<AGE::UUID, AGE::Ref<QuestInfo>> m_Quests;
	};
}
