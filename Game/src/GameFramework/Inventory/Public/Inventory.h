#pragma once
#include "Items/Public/Item.h"
#include "Items/Public/Weapon.h"
#include "Items/Public/Armor.h"
#include "Core/Public/UUID.h"


namespace GameFramework
{
	struct ItemInfo
	{
	public:
		ItemInfo() = default;
		virtual ~ItemInfo() = default;

		std::string Name;
		int ItemType = 0;
		int ItemBuffType = 0;
		int HP = 0;
		int MP = 0;
		int Strength = 0;
		int Speed = 0;
		int Defense = 0;
		bool bIsWeapon = false;
		bool bIsArmor = false;
		bool bIsKeyItem = false;

		AGE::UUID ID;

	};
	
	class Inventory
	{
	public:
		Inventory();
		Inventory(const Inventory&) = default;
		virtual ~Inventory() = default;


		int GetItemMaxCapacity() { return m_MaxItemCapacity; }
		int GetWeaponMaxCapacity() { return m_MaxWeaponCapacity; }
		int GetArmorMaxCapacity() { return m_MaxArmorCapacity; }
		std::vector<AGE::Ref<Item>> GetItems() { return m_Items; }
		std::vector< AGE::Ref<Weapon>> GetWeapons() { return m_Weapons; }
		std::vector<AGE::Ref<Armor>> GetArmors() { return m_Armor; }

		bool AddReward(const std::vector<std::string>& InventoryToAdd);
		bool AddItem(AGE::Ref<Item> Item);

		bool RemoveItem(AGE::Ref<Item> Item);

		bool AddWeapon(AGE::Ref<Weapon> Weapon);

		bool RemoveWeapon(AGE::Ref<Weapon> Weapon);

		bool AddArmor(AGE::Ref<Armor> Armor);

		bool RemoveArmor(AGE::Ref<Armor> Armor);

		static void Serialize(AGE::DataWriter* Serializer, const Inventory& Instance)
		{
			Serializer->WriteRaw<int>((int)Instance.m_Items.size());
			for (int i = 0; i < Instance.m_Items.size(); i++)
			{
				Serializer->WriteObject<Item>(*Instance.m_Items[i].get());
			}
			Serializer->WriteRaw<int>((int)Instance.m_Weapons.size());
			for (int i = 0; i < Instance.m_Weapons.size(); i++)
			{
				Serializer->WriteObject<Weapon>(*Instance.m_Weapons[i].get());
			}
			Serializer->WriteRaw<int>((int)Instance.m_Armor.size());
			for (int i = 0; i < Instance.m_Armor.size(); i++)
			{
				Serializer->WriteObject<Armor>(*Instance.m_Armor[i].get());
			}
			Serializer->WriteRaw<int>(Instance.m_MaxItemCapacity);
			Serializer->WriteRaw<int>(Instance.m_MaxArmorCapacity);
			Serializer->WriteRaw<int>(Instance.m_MaxWeaponCapacity);
		}
		static void Deserialize(AGE::DataReader* Deserializer, Inventory& Instance)
		{
			Item I;
			Weapon W;
			Armor A;
			int Size;
			Deserializer->ReadRaw<int>(Size);
			Instance.m_Items.resize(Size);
			for (int i = 0; i < Size; i++)
			{
				Deserializer->ReadObject<Item>(I);
				Instance.m_Items[i] = AGE::CreateRef<Item>(I);
			}
			Deserializer->ReadRaw<int>(Size);
			Instance.m_Weapons.resize(Size);
			for (int i = 0; i < Size; i++)
			{
				Deserializer->ReadObject<Weapon>(W);
				Instance.m_Weapons[i] = AGE::CreateRef<Weapon>(W);
			}
			Deserializer->ReadRaw<int>(Size);
			Instance.m_Armor.resize(Size);
			for (int i = 0; i < Size; i++)
			{
				Deserializer->ReadObject<Armor>(A);
				Instance.m_Armor[i] = AGE::CreateRef<Armor>(A);
			}
			Deserializer->ReadRaw<int>(Instance.m_MaxItemCapacity);
			Deserializer->ReadRaw<int>(Instance.m_MaxArmorCapacity);
			Deserializer->ReadRaw<int>(Instance.m_MaxWeaponCapacity);
		}

	private:
		std::vector<AGE::Ref<Item>> m_Items;
		std::vector< AGE::Ref<Weapon>> m_Weapons;
		std::vector<AGE::Ref<Armor>> m_Armor;

		std::vector<GameFramework::ItemInfo> m_Database;

		//Denotes how many instances of an individual item is allowed
		int m_MaxItemCapacity = 99;
		//Denotes how many instances of a piece of armor is allowed
		int m_MaxArmorCapacity = 99;
		//Denotes how many instnaces of an individual weapon is allowed
		int m_MaxWeaponCapacity = 99;

	};

}