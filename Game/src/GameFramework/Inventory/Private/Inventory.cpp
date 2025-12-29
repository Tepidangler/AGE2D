#include <Core/Public/AGEpch.hpp>
#include <Age.h>
#include "Inventory/Public/Inventory.h"

namespace GameFramework
{
    Inventory::Inventory()
    {

    }
    bool Inventory::AddReward(const std::vector<std::string>& InventoryToAdd)
    {
        for (auto& I : InventoryToAdd)
        {
            for (auto& E : m_Database)
            {
                if (E.Name == I)
                {
                    if (E.bIsWeapon)
                    {
                        m_Weapons.emplace_back(AGE::CreateRef<Weapon>(E));
                        return true;
                    }

                    if (E.bIsArmor)
                    {
                        m_Armor.emplace_back(AGE::CreateRef<Armor>(E));
                        return true;
                    }

                    m_Items.emplace_back(AGE::CreateRef<Item>(E));
                    return true;
                }
            }
        }
        return false;
    }
    bool Inventory::AddItem(AGE::Ref<Item> Item)
    {
        if (Item->GetCount() < m_MaxItemCapacity)
        {
            m_Items.push_back(Item);
            Item->IncrementCount();
            return true;
        }
        else
        {
            return false;
        }
        return false;
    }
    bool Inventory::RemoveItem(AGE::Ref<Item> Item)
    {
        for (int i = 0; i < m_Items.size(); i++)
        {
            if (*m_Items[i].get() == *Item.get())
            {
                m_Items.erase(m_Items.begin() + i);
                m_Items.shrink_to_fit();
                Item->DecrementCount();
                return true;
            }
        }

        return false;
    }
    bool Inventory::AddWeapon(AGE::Ref<Weapon> Weapon)
    {
        if (Weapon->GetCount() < m_MaxWeaponCapacity)
        {
            m_Weapons.push_back(Weapon);
            Weapon->IncrementCount();
            return true;
        }
        else
        {
            return false;
        }
        return false;
    }
    bool Inventory::RemoveWeapon(AGE::Ref<Weapon> Weapon)
    {
        for (int i = 0; i < m_Weapons.size(); i++)
        {
            if (*m_Weapons[i].get() == *Weapon.get())
            {
                m_Weapons.erase(m_Weapons.begin() + i);
                m_Weapons.shrink_to_fit();
                Weapon->DecrementCount();
                return true;
            }
        }
        return false;
    }
    bool Inventory::AddArmor(AGE::Ref<Armor> Armor)
    {
        if (Armor->GetCount() < m_MaxArmorCapacity)
        {
            m_Armor.push_back(Armor);
            Armor->IncrementCount();
            return true;
        }
        else
        {
            return false;
        }
        return false;
    }
    bool Inventory::RemoveArmor(AGE::Ref<Armor> Armor)
    {
        for (int i = 0; i < m_Armor.size(); i++)
        {
            if (*m_Armor[i].get() == *Armor.get())
            {
                m_Armor.erase(m_Armor.begin() + i);
                m_Armor.shrink_to_fit();
                Armor->DecrementCount();
                return true;
            }
        }
        return false;
    }
}