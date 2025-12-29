#include <Core/Public/AGEpch.hpp>
#include "Items/Public/Weapon.h"
#include "Inventory/Public/Inventory.h"

namespace GameFramework
{
	Weapon::Weapon(std::string Name)
		:m_Name(Name)
	{
	}
	Weapon::Weapon(const ItemInfo& Info)
	{
		m_Name = Info.Name;
	}
	Weapon::Weapon(std::string Name, AGE::Ref<AGE::Texture2D> Texture)
	{
	}
	AGE::Ref<AGE::Texture2D> Weapon::GetTexture()
	{
		return AGE::Ref<AGE::Texture2D>();
	}

}