#pragma once
#include "Core.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"
#include "Core/Public/UUID.h"

namespace GameFramework
{
	struct ItemInfo;
	enum class ItemBuffType
	{
		None = 0,
		HP = 1,
		MP = 2,
		Strength = 3,
		Speed = 4,
		Defense = 5
		

	};

	enum class ItemType
	{
		None = 0,
		Buff = 1,
		Debuff = 2

	};

	struct ItemStats
	{
		float HP = 0.f;
		float MP = 0.f;
		float Str = 0.f;
		float Spd = 0.f;
		float Def = 0.f;

		static void Serialize(AGE::DataWriter* Serializer, const ItemStats& Instance)
		{
			Serializer->WriteRaw<float>(Instance.HP);
			Serializer->WriteRaw<float>(Instance.MP);
			Serializer->WriteRaw<float>(Instance.Str);
			Serializer->WriteRaw<float>(Instance.Spd);
			Serializer->WriteRaw<float>(Instance.Def);
		}
		static void Deserialize(AGE::DataReader* Deserializer, ItemStats& Instance)
		{
			Deserializer->ReadRaw<float>(Instance.HP);
			Deserializer->ReadRaw<float>(Instance.MP);
			Deserializer->ReadRaw<float>(Instance.Str);
			Deserializer->ReadRaw<float>(Instance.Spd);
			Deserializer->ReadRaw<float>(Instance.Def);
		}

	};

	class Item
	{
	public:

		Item() = default;
		Item(const ItemInfo& Info);
		Item(std::string Name);
		Item(const Item&) = default;
		virtual ~Item() = default;


		std::string GetName() { return m_Name; }
		ItemStats& GetStats() { return m_Stats; }

		int GetCount() { return m_Count; }

		ItemType GetItemType() { return m_Type; }

		ItemBuffType GetItemBuffType() { return m_BuffType; }


		void SetItemType(ItemType Type) { m_Type = Type; }

		void SetItemBuffType(ItemBuffType Type) { m_BuffType = Type; }


		void IncrementCount() { m_Count++; }

		void DecrementCount() { m_Count--; }

		virtual bool operator==(const Item& Other) const
		{
			return m_Name == ((Item&)Other).m_Name;
		}


		static void Serialize(AGE::DataWriter* Serializer, const Item& Instance)
		{
			Serializer->WriteString(Instance.m_Name);
			Serializer->WriteObject<ItemStats>(Instance.m_Stats);
			Serializer->WriteRaw<int>((int)Instance.m_Type);
			Serializer->WriteRaw<int>((int)Instance.m_BuffType);
			Serializer->WriteRaw<int>(Instance.m_Count);
		}

		static void Deserialize(AGE::DataReader* Deserializer, Item& Instance)
		{
			int Type;
			int BuffType;
			int Count;
			Deserializer->ReadString(Instance.m_Name);
			Deserializer->ReadObject<ItemStats>(Instance.m_Stats);
			Deserializer->ReadRaw<int>(Type);
			Instance.m_Type = (ItemType)Type;
			Deserializer->ReadRaw<int>(BuffType);
			Instance.m_BuffType = (ItemBuffType)BuffType;
			Deserializer->ReadRaw<int>(Count);
			Instance.m_Count = Count;
		}

	protected:

		std::string m_Name = "None";

		int m_Count = 0;

		ItemStats m_Stats;

		AGE::UUID m_ID;

		ItemType m_Type = ItemType::None;

		ItemBuffType m_BuffType = ItemBuffType::None;

	};
}