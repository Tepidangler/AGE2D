#include <Core/Public/AGEpch.hpp>
#include "Items/Public/Armor.h"
#include "Inventory/Public/Inventory.h"

namespace GameFramework
{
    Armor::Armor(const ItemInfo& Info)
    {
        m_Name = Info.Name;
    }
    Armor::Armor(std::string Name)
        :m_Name(Name)
    {
    }
    Armor::Armor(std::string Name, AGE::Ref<AGE::Texture2D> Texture)
    {
    }
}