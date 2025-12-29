#pragma once
#include <GameFramework.h>

namespace AGE
{
	class InventoryDatabase
	{
	public:
		InventoryDatabase();

		virtual ~InventoryDatabase();

		void OnImGuiRender();

		void RestoreWindow();

		void RenderWindow(const char* WindowName, bool* IsOpen);

		void LoadDatabase();

	private:
		bool SerializeDatabase(const std::string& FileName);

		bool DeserializeDatabase(const std::string& FileName);
	private:
		GameFramework::ItemInfo m_CurrentItem;
		std::vector<GameFramework::ItemInfo> m_Database;
		int m_Rows = 1;
		bool m_bIsOpen = false;
	};
}