//
// Created by by De'Lano Wilcox on 11/22/2025.
//

#ifndef AGE_DATABASEWINDOW_H
#define AGE_DATABASEWINDOW_H

#endif //AGE_DATABASEWINDOW_H

#pragma once
#include <imgui.h>
#include "Editor_Core/Public/Database.h"
#include "GameFramework/GameStructs/Public/GameStructs.h"

namespace AGE
{
	class DatabaseWindow
	{
	public:

		DatabaseWindow(Database* Database);
		~DatabaseWindow() = default;

		void OnImGuiRender();

		void RestoreWindow();
	private:
		void RenderWindow();

		void DisplayDatabase(bool* IsOpen);

		void DisplayLoginPrompt(bool* IsOpen);

		void DrawEnemyDataTable();

		std::string MakeWindowID(uint64_t& IDIndex);

		bool ContainsPrimaryKey();

		bool HashPassword(std::string& Password);

		bool IsPasswordCorrect(const std::string& Password);

		void PromptForPassword();

		void DrawMenuBar();

		void DisplayReloadTablePopup();
		void DisplayExportTablePopup();

	private:
		Database* m_Database;
		bool bOpened = false;
		bool bPromptOpen = false;
		bool bPromptingForPassword = false;
		bool bDisplayReloadTablePopup = false;
		bool bDisplayExportTablePopup = false;

		GameFramework::EnemyStats m_NewEnemyData;
		std::array<std::string, 4> m_LoginStrings;
		std::string m_HashedPassword;
		std::string m_Password;
		std::string m_CurrentTable = "";

		std::vector<std::string> m_AvailableDBs;
		std::vector<GameFramework::EnemyStats> m_EnemyData;
		std::vector<std::string> m_Tables;
		std::string m_CurrentDatabaseString = "";
		std::vector<std::tuple<std::string,std::string,bool>> m_NewTableData = {std::make_tuple("","",false)};
		uint16_t m_PortNumber = 5432;
		std::string m_NewTableName = "";

		std::array<std::string, 22> m_SQLTypes =
			{
			"bigint",
			"bigserial",
			"bit(255)",
			"varbit(255)",
			"bool",
			"box",
			"bytea",
			"char(255)",
			"varchar(255)",
			"cidr",
			"circle",
			"date",
			"float",
			"inet",
			"int",
			"money",
			"real",
			"smallint",
			"smallserial",
			"serial",
			"text",
			"uuid"
		};

	private:
		std::string ConstructPreppedStatement(StatementType Type, const std::string& TableName, std::vector<std::string>& Columns);
	};
}
