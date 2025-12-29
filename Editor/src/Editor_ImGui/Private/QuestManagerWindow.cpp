/**

    @file      QuestManagerWindow.cpp
    @brief     
    @details   ~
    @author    De'Lano Wilcox
    @date      30.05.2025
    @copyright � Alcoy Game Studios, 2025. All right reserved.

**/

#include "Core/Public/AGEpch.hpp"
#include <Core/Public/Colors.h>
#include "Editor_ImGui/Public/QuestManagerWindow.h"

#include "GameState/Public/GameState.h"

#include "misc/cpp/imgui_stdlib.h"
#include "Utils/Public/WindowsUtils.h"



namespace AGE
{
    static std::string ConvertQuestTypeToString(GameFramework::QuestType Type)
    {
        switch (Type)
        {
        case GameFramework::QuestType::Main:
            return std::string("Main");

        case GameFramework::QuestType::Side:
            return std::string("Side");

        default:
            return std::string("UNDEFINED");
        }

        return std::string("UNDEFINED");

    }

    using C = Colors::Color;
    QuestManagerWindow::QuestManagerWindow()
    {
       m_QuestManager = GameFramework::GameState::Get()->GetQuestManager();
        for (auto& N : m_QuestManager->GetQuests())
        {
            m_QuestNameStrings.emplace_back(N.second->QuestName);
        }
    }
    void QuestManagerWindow::OnImGuiRender()
    {
        if (m_bIsOpen)
        {
            RenderWindow("Quest Manager Window", &m_bIsOpen);
        }
    }
    void QuestManagerWindow::DrawSelection(const std::string& CurrentQuestName)
    {
        ImVec4 col = { C::LightGreen[0], C::LightGreen[1], C::LightGreen[2], C::LightGreen[3] };
        char buf[256];
        snprintf(buf, sizeof buf, "QuestID: %I64u", (uintptr_t)m_QuestManager->GetQuest(CurrentQuestName)->ID);
        ImGui::TextColored(col, buf);
        ImGui::SameLine();
        std::string NameString = "Quest Name: " + CurrentQuestName;
        ImGui::Text(NameString.c_str());
        //Add Dependent Quest ID's and ability to set a dependent quest here
        ImGui::Text("Quest Description");
        ImGui::Separator();
        ImGui::Text(m_QuestManager->GetQuest(CurrentQuestName)->QuestDescription.c_str());

        ImGui::Separator();
        int Reward = m_QuestManager->GetQuest(CurrentQuestName)->XPReward;
        ImGui::Text("XP Reward: "); ImGui::SameLine(); 
        ImGui::InputInt("##XPReward", &Reward, 1, 10);
        m_QuestManager->GetQuest(CurrentQuestName)->XPReward = Reward;
        ImGui::Text("Item Reward: "); ImGui::SameLine();
        for (int i = 0; i < m_QuestManager->GetQuest(CurrentQuestName)->ItemRewards.size(); i++)
        {
            std::string Item = m_QuestManager->GetQuest(CurrentQuestName)->ItemRewards[i];
            ImGui::Text(Item.c_str());
            ImGui::SameLine();
        }
        ImGui::Dummy({1.f,1.f});
        std::string lbl = "##";
        ImGui::InputText(lbl.c_str(), &m_ItemToAdd);
        if (ImGui::Button("Add Item"))
        {

            if (!m_ItemToAdd.empty())
            {
                m_QuestManager->GetQuest(CurrentQuestName)->ItemRewards.emplace_back(m_ItemToAdd);
                m_ItemToAdd.clear();
            }
        }
        ImGui::Text("Quest Type: "); ImGui::SameLine();
        ImGui::Text(ConvertQuestTypeToString(m_QuestManager->GetQuest(CurrentQuestName)->GetQuestType()).c_str());
        ImGui::Separator();

        int Index = 0;
        for (auto& C : m_QuestManager->GetQuest(CurrentQuestName)->GetCheckpoints())
        {
            ImGui::Text("Checkpoint ID: "); ImGui::SameLine();
            ImGui::Text(std::to_string(C.first).c_str());
            ImGui::Text("Checkpoint Text: "); ImGui::SameLine();
            ImGui::Text(m_QuestManager->GetQuest(CurrentQuestName)->GetCheckpointTexts()[Index].c_str());
            ImGui::Separator();
            Index++;
        }
    }
    void QuestManagerWindow::OpenWindow()
    {
        m_bIsOpen = true;
    }
    void QuestManagerWindow::DrawAddQuest()
    {
        const char* QuestTypeStrings[] = { "Main", "Side" };
        const char* CurrentQuestTypeString = QuestTypeStrings[(int)m_SelectionContext.GetQuestType()];
        ImGui::BeginChild("Add Quest");
            ImGui::Text("Quest Type: ");
            if (ImGui::BeginCombo("##QuestType", CurrentQuestTypeString))
            {
                for (int i = 0; i < 2; i++)
                {
                    bool IsSelected = CurrentQuestTypeString == QuestTypeStrings[i];

                    if (ImGui::Selectable(QuestTypeStrings[i], IsSelected))
                    {
                        CurrentQuestTypeString = QuestTypeStrings[i];
                        m_SelectionContext.SetQuestType((GameFramework::QuestType)i);
                    }
                    if (IsSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }
            ImGui::Text("Quest Name: "); ImGui::SameLine();
            ImGui::InputText("##Name", &m_SelectionContext.QuestName);
            ImGui::Separator();
            ImGui::Text("Quest Description: ");
            ImGui::InputText("##Description", &m_SelectionContext.QuestDescription);
            ImGui::Separator();
            ImGui::Text("Checkpoints");
            if (ImGui::Button("Add Checkpoint"))
            {
                m_SelectionContext.AddCheckpoint();
            }
            int Index = 0;
            for (auto& C : m_SelectionContext.GetCheckpoints())
            {
                ImGui::Text("Checkpoint ID: "); ImGui::SameLine();
                ImGui::Text(std::to_string(C.first).c_str());
                std::string lbl = "##CheckpointText" +std::to_string(Index);
                ImGui::InputText(lbl.c_str(), &m_SelectionContext.GetCheckpointTexts()[Index]);
                Index++;
            }
            ImGui::Separator();
            ImGui::Text("Rewards");
            ImGui::Text("XP: "); ImGui::SameLine();
            ImGui::InputInt("##XP", &m_SelectionContext.XPReward, 1, 10);
            for (int i = 0; i < m_SelectionContext.ItemRewards.size(); i++)
            {
                std::string Item = m_SelectionContext.ItemRewards[i];
                ImGui::Text(Item.c_str());
                ImGui::SameLine();
            }
            ImGui::Dummy({ 1.f,1.f });
            std::string lbl = "##";
            ImGui::InputText(lbl.c_str(), &m_ItemToAdd);
            if (ImGui::Button("Add Item"))
            {

                if (!m_ItemToAdd.empty())
                {
                    m_SelectionContext.ItemRewards.emplace_back(m_ItemToAdd);
                    m_ItemToAdd.clear();
                }
            }
            ImGui::Separator();
            if (ImGui::Button("Create Quest"))
            {
                m_QuestManager->AddQuest(m_SelectionContext);
                m_SelectionContext = GameFramework::QuestInfo();
                m_bAddingNewQuest = false;
                for (auto& N : m_QuestManager->GetQuests())
                {
                    m_QuestNameStrings.emplace_back(N.second->QuestName);
                }
                if (m_CurrentQuestName.empty())
                {
                    m_CurrentQuestName = m_QuestNameStrings.back();
                }
            }

         ImGui::EndChild();
        
    }
    void QuestManagerWindow::ImportQuest()
    {
        std::filesystem::path Filepath(FileDialogs::OpenFile("JSON(*.json)\0 * .json\0"));
        if (Filepath.empty())
        {
            return;
        }
        m_QuestManager->LoadQuests(Filepath);
        m_QuestNameStrings.clear();
        for (auto& N : m_QuestManager->GetQuests())
        {
            m_QuestNameStrings.emplace_back(N.second->QuestName);
        }
        if (m_CurrentQuestName.empty())
        {
            m_CurrentQuestName = m_QuestNameStrings.back();
        }
    }
    void QuestManagerWindow::RenderWindow(const char* WindowName, bool* IsOpen)
    {
        if (ImGui::Begin(WindowName, IsOpen))
        {
            if (!m_QuestNameStrings.empty())
            {
                if (!m_bAddingNewQuest)
                {
                    std::string CurrentQuestName = m_CurrentQuestName;
                    ImGui::Text("Current Quest: ");
                    if (ImGui::BeginCombo("##CurrentQuest", CurrentQuestName.c_str()))
                    {
                        for (int i = 0; i < m_QuestNameStrings.size(); i++)
                        {
                            bool IsSelected = CurrentQuestName == m_QuestNameStrings[i];

                            if (ImGui::Selectable(m_QuestNameStrings[i].c_str(), IsSelected))
                            {
                                CurrentQuestName = m_QuestNameStrings[i];
                                m_CurrentQuestName = CurrentQuestName;
                            }
                        }
                        ImGui::EndCombo();
                    }
                    DrawSelection(CurrentQuestName);
                }
            }
        }

        if (!m_bAddingNewQuest)
        {
            if (ImGui::Button("Import Quest"))
            {
                ImportQuest();
            }
            if (ImGui::Button("Create New Quest"))
            {
                m_bAddingNewQuest = true;
            }
        }

        if (m_bAddingNewQuest)
        {
            DrawAddQuest();
        }
        ImGui::End();
    }
    void QuestManagerWindow::Sync()
    {
        for (auto& N : m_QuestManager->GetQuests())
        {
            m_QuestNameStrings.emplace_back(N.second->QuestName);
        }
        if (m_QuestNameStrings.empty())
        {
            return;
        }
        m_CurrentQuestName = m_QuestNameStrings.front();
    }
}


