/**

    @file      InventoryDatabase.cpp
    @brief     
    @details   ~
    @author    De'Lano Wilcox
    @date      31.05.2025
    @copyright � Alcoy Game Studios, 2025. All right reserved.

**/
#include <Core/Public/AGEpch.hpp>
#include "Editor_ImGui/Public/InventoryDatabase.h"
#include "Parser/Public/JsonParser.h"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include "Project/Public/Project.h"

namespace AGE
{
    InventoryDatabase::InventoryDatabase()
    {
    }
    InventoryDatabase::~InventoryDatabase()
    {
        //Serialize the database
        SerializeDatabase("/InventoryDatabase/ItemDatabase.json");

    }
    void InventoryDatabase::OnImGuiRender()
    {
        if (m_bIsOpen)
        {
            RenderWindow("Inventory Database", &m_bIsOpen);       
        }
    }
    void InventoryDatabase::RestoreWindow()
    {
        m_bIsOpen = true;
    }
    void InventoryDatabase::RenderWindow(const char* WindowName, bool* IsOpen)
    {
        if (ImGui::Begin(WindowName, IsOpen))
        {
            if (!ImGui::BeginTable("Inventory Table", 11))
            {
                ImGui::EndTable();
                return;
            }
            
            ImGui::TableSetupColumn("Item Name");
            ImGui::TableSetupColumn("Item Type");
            ImGui::TableSetupColumn("Item Buff Type");
            ImGui::TableSetupColumn("HP");
            ImGui::TableSetupColumn("MP");
            ImGui::TableSetupColumn("Strength");
            ImGui::TableSetupColumn("Speed");
            ImGui::TableSetupColumn("Defense");
            ImGui::TableSetupColumn("Is Weapon?");
            ImGui::TableSetupColumn("Is Armor?");
            ImGui::TableSetupColumn("Is KeyItem?");
            ImGui::TableHeadersRow();
            ImGui::TableNextColumn();

            for (int i = 0; i < m_Database.size(); i++)
            {
                ImGui::InputText(std::string("##ItemName" + std::to_string(i)).c_str(), &m_Database[i].Name);
                ImGui::TableNextColumn();
                ImGui::InputInt(std::string("##ItemType" + std::to_string(i)).c_str(), &m_Database[i].ItemType, 1, 0);
                ImGui::TableNextColumn();
                ImGui::InputInt(std::string("##ItemBuffType" + std::to_string(i)).c_str(), &m_Database[i].ItemBuffType, 1, 0);
                ImGui::TableNextColumn();
                ImGui::InputInt(std::string("##HP" + std::to_string(i)).c_str(), &m_Database[i].HP, 1, 0);
                ImGui::TableNextColumn();
                ImGui::InputInt(std::string("##MP" + std::to_string(i)).c_str(), &m_Database[i].MP, 1, 0);
                ImGui::TableNextColumn();
                ImGui::InputInt(std::string("##Strength" + std::to_string(i)).c_str(), &m_Database[i].Strength, 1, 0);
                ImGui::TableNextColumn();
                ImGui::InputInt(std::string("##Speed" + std::to_string(i)).c_str(), &m_Database[i].Speed, 1, 0);
                ImGui::TableNextColumn();
                ImGui::InputInt(std::string("##Defense" + std::to_string(i)).c_str(), &m_Database[i].Defense, 1, 0);
                ImGui::TableNextColumn();
                ImGui::Checkbox(std::string("##IsWeapon" + std::to_string(i)).c_str(), &m_Database[i].bIsWeapon);
                ImGui::TableNextColumn();
                ImGui::Checkbox(std::string("##IsArmor" + std::to_string(i)).c_str(), &m_Database[i].bIsArmor);
                ImGui::TableNextColumn();
                ImGui::Checkbox(std::string("##IsKeyItem" + std::to_string(i)).c_str(), &m_Database[i].bIsKeyItem);
                ImGui::TableNextColumn();

            }


            ImGui::EndTable();

            if (ImGui::Button("Add Item"))
            {
                m_Rows++;
                m_Database.emplace_back(GameFramework::ItemInfo());
            }
            ImGui::End();
        }
    }
    void InventoryDatabase::LoadDatabase()
    {
        std::string Path = Project::GetActive()->GetAssetDirectory().string();
        Path.append("/InventoryDatabase/ItemDatabase.json");
        DeserializeDatabase(Path);
    }
    bool InventoryDatabase::SerializeDatabase(const std::string& FileName)
    {
        std::string Path = Project::GetActive()->GetAssetDirectory().string();
        Path.append(FileName);
        JsonParser Parser;
        return Parser.SaveJsonFile(Path, m_Database);
    }
    bool InventoryDatabase::DeserializeDatabase(const std::string& FileName)
    {
        JsonParser Parser;

        nlohmann::json Data = Parser.LoadJsonFile(FileName);

        if (Data.size() <= 0)
        {
            return false;
        }
        
        for (auto& D : Data)
        {
            GameFramework::ItemInfo Info;

            Info.Name = D.at("item_name").get<std::string>();
            Info.ItemType = D.at("item_type").get<int>();
            Info.ItemBuffType = D.at("item_buff_type").get<int>();
            Info.HP = D.at("hp").get<int>();
            Info.MP = D.at("mp").get<int>();
            Info.Strength = D.at("strength").get<int>();
            Info.Speed = D.at("speed").get<int>();
            Info.Defense = D.at("defense").get<int>();
            Info.bIsWeapon = D.at("isweapon").get<bool>();
            Info.bIsArmor = D.at("isarmor").get<bool>();
            Info.bIsKeyItem = D.at("iskeyitem").get<bool>();
            Info.ID = D.at("id").get<uint64_t>();
            m_Database.emplace_back(Info);
        }
        
        return false;
    }
}