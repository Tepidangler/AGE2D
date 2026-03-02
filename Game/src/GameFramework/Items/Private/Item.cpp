#include <Core/Public/AGEpch.hpp>
#include "Items/Public/Item.h"
#include "Inventory/Public/Inventory.h"


namespace GameFramework
{
	Item::Item(const ItemInfo& Info)
	{
		m_ID = Info.ID;
		m_Stats.HP = (float)Info.HP;
		m_Stats.MP = (float)Info.MP;
		m_Stats.Def = (float)Info.Defense;
		m_Stats.Str = (float)Info.Strength;
		m_Stats.Spd = (float)Info.Speed;
		m_BuffType = (ItemBuffType)Info.ItemBuffType;
		m_Name = Info.Name;
		m_Type = (ItemType)Info.ItemType;
	}
	Item::Item(std::string Name)
		:m_Name(Name)
	{
	}

}