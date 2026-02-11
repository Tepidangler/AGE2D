#pragma once

#include "Texture/Public/Texture.h"
#include "Serializers/Public/DataWriter.h"
#include "Serializers/Public/DataReader.h"
#include <string>


namespace GameFramework
{	
	struct ItemInfo;

	class Weapon
	{
	public:
		Weapon() = default;
		Weapon(std::string Name);
		Weapon(const ItemInfo& Info);
		Weapon(std::string Name, AGE::Ref<AGE::Texture2D> Texture);
		Weapon(const Weapon&) = default;


		virtual ~Weapon() {};

		virtual std::string GetName() { return m_Name; }
		virtual std::string GetName() const { return m_Name; }
		virtual AGE::Ref<AGE::Texture2D> GetTexture();

		virtual int GetCount() { return m_Count; }
		virtual int GetCount() const { return m_Count; }

		virtual void SetCount(int C) { m_Count = C; }

		virtual void IncrementCount() { m_Count++; }

		virtual void DecrementCount() { m_Count--; }

		virtual bool operator==(const Weapon& Other) const
		{
			return m_Name == ((Weapon&)Other).m_Name;
		}

		static void Serialize(AGE::DataWriter* Serializer, const Weapon& Instance)
		{
			Serializer->WriteString(Instance.GetName());
			Serializer->WriteRaw<int>(Instance.GetCount());
		}

		static void Deserialize(AGE::DataReader* Deserializer, Weapon& Instance)
		{
			std::string WeaponName = Instance.GetName();
			Deserializer->ReadString(WeaponName);
			int Type;
			Deserializer->ReadRaw<int>(Type);
			int Count;
			Deserializer->ReadRaw<int>(Count);
			Instance.SetCount(Count);
		}

	protected:

		std::string m_Name = "None";
		int m_Count = 0;
	};
}