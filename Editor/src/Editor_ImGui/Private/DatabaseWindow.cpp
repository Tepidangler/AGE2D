//
// Created by by De'Lano Wilcox on 11/22/2025.
//

#include "Core/Public/AGEpch.hpp"
#include "Editor_ImGui/Public/DatabaseWindow.h"
#include <misc/cpp/imgui_stdlib.h>
#include <openssl/evp.h>
#include <AGE.h>

namespace AGE
{
	DatabaseWindow::DatabaseWindow(Database* Database)
	{
		m_Database = Database;
	}

	void DatabaseWindow::OnImGuiRender()
	{
		RenderWindow();

		if (bPromptingForPassword)
		{
			PromptForPassword();
		}
	}

	void DatabaseWindow::RenderWindow()
	{
		if (!m_Database->IsLoggedIn())
		{
			if (bPromptOpen)
			{
				DisplayLoginPrompt(&bPromptOpen);
			}
		}
		else
		{
			if (bOpened)
			{
				DisplayDatabase(&bOpened);
			}

		}
	}

	void DatabaseWindow::DisplayDatabase(bool* IsOpen)
	{
		if (!ImGui::Begin(std::vformat("Database Address: {}", std::make_format_args(m_LoginStrings[2])).c_str(), IsOpen, ImGuiWindowFlags_MenuBar))
		{
			ImGui::End();
			return;
		}

		DrawMenuBar();

		if (bDisplayReloadTablePopup)
		{
			ImGui::OpenPopup("ReloadTable");
			DisplayReloadTablePopup();

		}
		if (bDisplayExportTablePopup)
		{
			ImGui::OpenPopup("ExportTable");
			DisplayExportTablePopup();
		}

		m_AvailableDBs = m_Database->GetDatabaseNames();
		if (m_AvailableDBs.size() > 0)
		{
			//CurrentDatabaseString = m_AvailableDBs.front();
			ImGui::Text("Database: "); ImGui::SameLine();
			if (ImGui::BeginCombo("##Databases", m_CurrentDatabaseString.c_str()))
			{
				for (int i = 0; i < m_AvailableDBs.size(); ++i)
				{
					bool IsSelected = m_CurrentDatabaseString == m_AvailableDBs.at(i);
					if (ImGui::Selectable(m_AvailableDBs[i].c_str(), IsSelected))
					{
						m_CurrentDatabaseString = m_AvailableDBs.at(i);
					}

					if (IsSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			if (!m_Database->IsConnectedToDB(m_CurrentDatabaseString))
			{
				if (!m_CurrentDatabaseString.empty())
				{
					if (m_LoginStrings[1].empty())
					{
						bPromptingForPassword = true;
						ImGui::End();
						return;
					}
					m_Database->ConnectToDatabase(m_CurrentDatabaseString,m_LoginStrings[0],m_LoginStrings[1],m_LoginStrings[2],m_PortNumber);
					m_LoginStrings[1] = "";
					m_Tables = m_Database->GetTableNames(m_CurrentDatabaseString);
					for (auto& TN : m_Tables)
					{
						std::vector<std::string> ColumnNames = m_Database->GetColumnNames(m_CurrentDatabaseString, TN);
						m_Database->AddPreppedStatement(m_CurrentDatabaseString, StatementType::INSERT, ConstructPreppedStatement(StatementType::INSERT, TN,ColumnNames));
						m_Database->AddPreppedStatement(m_CurrentDatabaseString, StatementType::UPDATE, ConstructPreppedStatement(StatementType::UPDATE, TN,ColumnNames));
						m_Database->MakePreparedStatements(TN);
						m_Database->ClearPreparedStatements(m_CurrentDatabaseString);
					}
				}

			}

			if (m_Database->IsConnectedToDB(m_CurrentDatabaseString))
			{
				DrawEnemyDataTable();
			}

			if (!m_CurrentDatabaseString.empty())
			{
				if (ImGui::Button("Create New Table"))
				{
					ImGui::OpenPopup("CreateTable");
				}
				if (ImGui::BeginPopup("CreateTable"))
				{
					ImGui::Text("Table Name: "); ImGui::SameLine();
					ImGui::InputText("##TableName", &m_NewTableName);
					uint64_t ID = 900;
					for (auto& D : m_NewTableData)
					{
						ImGui::Text("Column Name: "); ImGui::SameLine();
						ImGui::InputText(MakeWindowID(ID).c_str(), &std::get<0>(D)); ImGui::SameLine();
						if (ImGui::BeginCombo(MakeWindowID(ID).c_str(), std::get<1>(D).c_str()))
						{
							for (int i = 0; i < m_SQLTypes.size(); ++i)
							{
								bool IsSelected = std::get<1>(D) == m_SQLTypes[i];
								if (ImGui::Selectable(m_SQLTypes[i].c_str(), IsSelected))
								{
									std::get<1>(D) = m_SQLTypes[i];
								}

								if (IsSelected)
								{
									ImGui::SetItemDefaultFocus();
								}
							}

							ImGui::EndCombo();
						}
						ImGui::SameLine();
						ImGui::Text("Primary Key?"); ImGui::SameLine();
						ImGui::Checkbox(MakeWindowID(ID).c_str(),&std::get<2>(D));
					}

					if (ImGui::Button("Add New Column"))
					{
						m_NewTableData.emplace_back(std::make_tuple("","",false));
					}
					ImGui::SameLine();
					ImGui::Dummy({16.f,0.f});
					if (ImGui::Button("Submit"))
					{
						if (!ContainsPrimaryKey())
						{
							CoreLogger::Error("Table contains no primary key!");
						}

						if (m_NewTableName.empty())
						{
							CoreLogger::Error("No Table Name Provided!");
						}

						if (ContainsPrimaryKey() && !m_NewTableName.empty())
						{
							CoreLogger::Info("Attempting to create table {} in Database {}", m_NewTableName, m_CurrentDatabaseString);
							m_Database->CreateTable(m_CurrentDatabaseString, m_NewTableName, m_NewTableData);
							ImGui::CloseCurrentPopup();
						}

					}
					ImGui::EndPopup();
				}
			}

		}
		ImGui::End();
	}

	void DatabaseWindow::RestoreWindow()
	{
		if (!m_Database->HasAnyOpenConnections())
		{
			bPromptOpen = true;
		}
		bOpened = true;
	}

	void DatabaseWindow::DisplayLoginPrompt(bool* IsOpen)
	{
		if (!ImGui::Begin("Login", IsOpen))
		{
			ImGui::End();
		}
		ImGui::Text("Username:"); ImGui::SameLine();
		ImGui::InputText("##USERNAME", &m_LoginStrings[0]);
		ImGui::Text("Password:"); ImGui::SameLine();
		ImGui::InputText("##PASSWORD", &m_LoginStrings[1],ImGuiInputTextFlags_Password);
		ImGui::Text("Host: "); ImGui::SameLine();
		ImGui::InputText("##HOST", &m_LoginStrings[2]);
		ImGui::Text("Port:"); ImGui::SameLine();
		ImGui::InputUInt("##PORT", &m_PortNumber);

		if (ImGui::Button("Login"))
		{
			if (!m_Database->Login(m_LoginStrings[0],m_LoginStrings[1],m_LoginStrings[2],m_PortNumber))
			{
				CoreLogger::Error("Can't connect to database server");
				ImGui::End();
				return;
			}
			CoreLogger::Info("Connected to database at {}", m_LoginStrings[2]);
			HashPassword(m_LoginStrings[1]);
			m_LoginStrings[1] = "";
		}
		ImGui::End();
	}

	void DatabaseWindow::DrawEnemyDataTable()
	{
		if (m_EnemyData.empty())
		{
			m_EnemyData = m_Database->GetTable<GameFramework::EnemyStats>("EnemyData", m_CurrentDatabaseString);
		}
		if (ImGui::Button("Reload"))
		{
			m_EnemyData.clear();
			m_EnemyData = m_Database->GetTable<GameFramework::EnemyStats>("EnemyData", m_CurrentDatabaseString);
		}
		ImGui::SameLine();
		if (ImGui::Button("Export Table"))
		{
			std::string Path = AssetManager::Get().GetGameContentPath().string() + std::format("/ExportedTables/{}.json", "EnemyData");
			JsonParser Parser;
			if (Parser.SaveJsonFile<GameFramework::EnemyStats>(Path, m_EnemyData))
			{
				CoreLogger::Trace("Table exported successfully saved to {}", Path);
			}

		}
		ImGui::SameLine();
		if (ImGui::TreeNode("Enemies"))
		{

			if (!ImGui::BeginTable("Enemy Data", 13, ImGuiTableFlags_Resizable))
			{
				ImGui::EndTable();
			}
			ImGui::TableSetupColumn("Name");
			ImGui::TableSetupColumn("HP");
			ImGui::TableSetupColumn("MP");
			ImGui::TableSetupColumn("Strength");
			ImGui::TableSetupColumn("MagicAttack");
			ImGui::TableSetupColumn("Attack");
			ImGui::TableSetupColumn("Defense");
			ImGui::TableSetupColumn("Agility");
			ImGui::TableSetupColumn("Speed");
			ImGui::TableSetupColumn("Absorb");
			ImGui::TableSetupColumn("Reduce");
			ImGui::TableSetupColumn("Weakness");
			ImGui::TableSetupColumn("##Save");
			ImGui::TableHeadersRow();
			ImGui::TableNextColumn();
			uint64_t ID = 100;
			for (auto& D : m_EnemyData)
			{
				ImGui::InputText(MakeWindowID(ID).c_str(), &D.Name);
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				ImGui::InputUInt(MakeWindowID(ID).c_str(), &D.HP);
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				ImGui::InputUInt(MakeWindowID(ID).c_str(), &D.MP);
				ImGui::Dummy({8.f,8.f});
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				ImGui::InputUInt(MakeWindowID(ID).c_str(), &D.Strength);
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				ImGui::InputUInt(MakeWindowID(ID).c_str(), &D.MagicAttack);
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				ImGui::InputUInt(MakeWindowID(ID).c_str(), &D.Attack);
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				ImGui::InputUInt(MakeWindowID(ID).c_str(), &D.Defense);
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				ImGui::InputUInt(MakeWindowID(ID).c_str(), &D.Agility);
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				ImGui::InputUInt(MakeWindowID(ID).c_str(), &D.Speed);
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				for (auto& A : D.Absorb)
				{
					ImGui::InputUInt(MakeWindowID(ID).c_str(), &A);
				}
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				for (auto& R : D.Reduce)
				{
					ImGui::InputUInt(MakeWindowID(ID).c_str(), &R);
				}
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				for (auto& W : D.Weak)
				{
					ImGui::InputUInt(MakeWindowID(ID).c_str(), &W);
				}
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
				if (ImGui::Button(std::string("Save " + D.Name ).c_str()))
				{
					CoreLogger::Info("Attempting to write {} Data to Database", D.Name);
					m_Database->UpdateRow<GameFramework::EnemyStats>(m_CurrentDatabaseString,"EnemyData",D.Name, D);
				}
				ImGui::Dummy({8.f,8.f});
				ImGui::TableNextColumn();
			}
			ImGui::EndTable();


			if (ImGui::Button("Add Row"))
			{
				ImGui::OpenPopup("AddRow");
			}
			if (ImGui::BeginPopup("AddRow"))
			{
				ImGui::InputText("NewName", &m_NewEnemyData.Name);
				ImGui::InputUInt("NewHP", &m_NewEnemyData.HP);
				ImGui::InputUInt("NewMP", &m_NewEnemyData.MP);
				ImGui::InputUInt("NewStrength", &m_NewEnemyData.Strength);
				ImGui::InputUInt("NewMgAtk", &m_NewEnemyData.MagicAttack);
				ImGui::InputUInt("NewAtk", &m_NewEnemyData.Attack);
				ImGui::InputUInt("NewDef", &m_NewEnemyData.Defense);
				ImGui::InputUInt("NewAgl", &m_NewEnemyData.Agility);
				ImGui::InputUInt("NewSpd", &m_NewEnemyData.Speed);

				if (ImGui::Button("Submit"))
				{
					CoreLogger::Info("Adding Row {} to table {} in Database {}", m_NewEnemyData.Name, "EnemyData", m_CurrentDatabaseString);
					m_Database->InsertRow<GameFramework::EnemyStats>(m_CurrentDatabaseString, "EnemyData", m_NewEnemyData);
				}
				ImGui::EndPopup();
			}
			ImGui::TreePop();
		}

	}



	std::string DatabaseWindow::MakeWindowID(uint64_t& IDIndex)
	{
		std::string Str = std::string("##" +  std::to_string(IDIndex));
		IDIndex++;
		return Str;
	}

	bool DatabaseWindow::ContainsPrimaryKey()
	{
		for (auto& D : m_NewTableData)
		{
			if (std::get<2>(D))
			{
				return true;
			}
		}
		return false;
	}

	bool DatabaseWindow::HashPassword(std::string &Password)
	{
		EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();

		if (!md_ctx)
		{
			return false;
		}

		if (EVP_DigestInit_ex(md_ctx, EVP_sha256(), NULL) != 1)
		{
			return false;
		}

		if (EVP_DigestUpdate(md_ctx, Password.c_str(), Password.size()) != 1)
		{
			return false;
		}
		uint8_t Hash[EVP_MAX_MD_SIZE];
		uint32_t Len;
		if (EVP_DigestFinal_ex(md_ctx, Hash, &Len) !=1 )
		{
			EVP_MD_CTX_free(md_ctx);
			return false;
		}
		EVP_MD_CTX_free(md_ctx);
		std::stringstream ss;
		for (uint32_t i = 0; i < Len; i++)
		{
			ss << std::hex << std::setw(2) << std::setfill('0') << (int)Hash[i];
		}
		m_HashedPassword = ss.str();
		return true;
	}

	bool DatabaseWindow::IsPasswordCorrect(const std::string &Password)
	{
		EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();

		if (!md_ctx)
		{
			return false;
		}

		if (EVP_DigestInit_ex(md_ctx, EVP_sha256(), NULL) != 1)
		{
			return false;
		}

		if (EVP_DigestUpdate(md_ctx, Password.c_str(), Password.size()) != 1)
		{
			return false;
		}
		uint8_t Hash[EVP_MAX_MD_SIZE];
		uint32_t Len;
		if (EVP_DigestFinal_ex(md_ctx, Hash, &Len) !=1 )
		{
			EVP_MD_CTX_free(md_ctx);
			return false;
		}
		EVP_MD_CTX_free(md_ctx);
		std::stringstream ss;
		for (uint32_t i = 0; i < Len; i++)
		{
			ss << std::hex << std::setw(2) << std::setfill('0') << (int)Hash[i];
		}
		std::string ThisHash = ss.str();
		return ThisHash == m_HashedPassword;
	}

	void DatabaseWindow::PromptForPassword()
	{
		ImGui::OpenPopup("PasswordPrompt");
		if (ImGui::BeginPopup("PasswordPrompt"))
		{
			ImGui::Text("Enter Password: "); ImGui::SameLine();
			ImGui::InputText("##Password", &m_Password, ImGuiInputTextFlags_Password);

			if (ImGui::Button("Login"))
			{
				if (!IsPasswordCorrect(m_Password))
				{
					ImGui::Text("Unable To login!");
					ImGui::EndPopup();
					return;
				}
				else
				{
					m_LoginStrings[1] = m_Password;
					bPromptingForPassword = false;
					m_Password = "";
				}
			}
			ImGui::EndPopup();
		}
	}

	void DatabaseWindow::DrawMenuBar()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Reload Table"))
				{
					bDisplayReloadTablePopup = true;
				}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Export"))
			{
				if (ImGui::MenuItem("Export Table"))
				{
					bDisplayExportTablePopup = true;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

	}

	void DatabaseWindow::DisplayReloadTablePopup()
	{
		if (ImGui::BeginPopup("ReloadTable"))
		{
			ImGui::Text("Table: ");ImGui::SameLine();
			if (ImGui::BeginCombo("##ReloadTableCombo",m_CurrentTable.c_str()))
			{
				for (int i = 0; i < m_Tables.size(); ++i)
				{
					bool IsSelected = m_CurrentTable == m_Tables[i];
					if (ImGui::Selectable(m_Tables[i].c_str(), IsSelected))
					{
						m_CurrentTable = m_Tables[i];
					}


					if (IsSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			if (ImGui::Button("Confirm"))
			{
				m_EnemyData.clear();
				m_EnemyData = m_Database->GetTable<GameFramework::EnemyStats>(m_CurrentTable, m_CurrentDatabaseString);
				m_CurrentTable = "";
				bDisplayReloadTablePopup = false;
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::Button("Cancel"))
			{
				bDisplayReloadTablePopup = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

	void DatabaseWindow::DisplayExportTablePopup()
	{
		if (ImGui::BeginPopup("ExportTable"))
		{
			ImGui::Text("Table: ");ImGui::SameLine();
			if (ImGui::BeginCombo("##ExportTableCombo",m_CurrentTable.c_str()))
			{
				for (int i = 0; i < m_Tables.size(); ++i)
				{
					bool IsSelected = m_CurrentTable == m_Tables[i];
					if (ImGui::Selectable(m_Tables[i].c_str(), IsSelected))
					{
						m_CurrentTable = m_Tables[i];
					}


					if (IsSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			if (ImGui::Button("Confirm"))
			{
				std::string Path = AssetManager::Get().GetGameContentPath().string() + std::format("/ExportedTables/{}.json", "EnemyData");
				JsonParser Parser;
				if (Parser.SaveJsonFile<GameFramework::EnemyStats>(Path, m_EnemyData))
				{
					m_CurrentTable = "";
					bDisplayExportTablePopup = false;
					ImGui::CloseCurrentPopup();
					CoreLogger::Trace("Table exported successfully saved to {}", Path);
				}
				else
				{
					CoreLogger::Trace("Failed to export table!");
				}
			}
			if (ImGui::Button("Cancel"))
			{
				bDisplayExportTablePopup = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

	std::string DatabaseWindow::ConstructPreppedStatement(StatementType Type,  const std::string& TableName,std::vector<std::string>& Columns)
	{
		std::string InsertStatement = std::format("INSERT INTO \"{}\" ", TableName);
		std::string UpdateStatement = std::format("UPDATE \"{}\" \nSET ", TableName);
		switch(Type)
		{
			case StatementType::SELECT:
			{
				break;
			}
			case StatementType::INSERT:
			{
				std::string Column = "(";
				std::string Values = " VALUES (";
				for (int i = 0; i < Columns.size(); ++i)
				{
					if (i == Columns.size() - 1)
					{
						Column += std::format(" \"{}\"", Columns[i]);
						Values += std::format(" ${}", std::to_string(i+1));
						continue;

					}
						Column += std::format(" \"{}\",", Columns[i]);
						Values += std::format(" ${},", std::to_string(i+1));
				}
				Column += " )";
				Values += " )";
				InsertStatement += Column;
				InsertStatement += Values;

				return InsertStatement;
				break;
			}
			case StatementType::UPDATE:
			{
				std::string PrimaryKey = m_Database->GetPrimaryKey(m_CurrentDatabaseString, TableName);
				std::string ColumnValue = "";
				int i = 0;
				for (i ; i < Columns.size(); ++i)
				{
					if (i == Columns.size() - 1)
					{
						ColumnValue += std::format(" \"{}\"=${}", Columns[i], std::to_string(i+1));
						continue;
					}
					ColumnValue += std::format(" \"{}\"=${},", Columns[i], std::to_string(i+1));
				}

				UpdateStatement += ColumnValue;
				UpdateStatement += std::format("\nWHERE \"{}\"=${}", PrimaryKey, std::to_string(i+1));
				return UpdateStatement;
				break;
			}
		}
		CoreLogger::Error("Invalid Statement Type! Returning empty string.");
		return {};
	}
}
