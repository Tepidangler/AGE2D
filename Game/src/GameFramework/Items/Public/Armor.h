#pragma once
#include "Texture/Public/Texture.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"

namespace GameFramework
{
	struct ItemInfo;

	class Armor
	{
	public:
		Armor() = default;
		Armor(const ItemInfo& Info);
		Armor(std::string Name);
		Armor(std::string Name, AGE::Ref<AGE::Texture2D> Texture);
		Armor(const Armor&) = default;
		virtual ~Armor() = default;

		virtual std::string GetName() { return m_Name; }
		virtual std::string GetName() const { return m_Name; }
		virtual AGE::Ref<AGE::Texture2D> GetTexture() { return m_Texture; }


		virtual void SetCount(int C) { m_Count = C; }


		virtual int GetCount() { return m_Count; }
		virtual int GetCount() const { return m_Count; }

		virtual void IncrementCount() { m_Count++; }

		virtual void DecrementCount() { m_Count--; }

		virtual bool operator==(const Armor& Other) const
		{
			return m_Name == ((Armor&)Other).m_Name;

		}

		static void Serialize(AGE::DataWriter* Serializer, const Armor& Instance)
		{
			Serializer->WriteString(Instance.GetName());

			Serializer->WriteRaw<int>(Instance.GetCount());
		}
		static void Deserialize(AGE::DataReader* Deserializer, Armor& Instance)
		{
			std::string ArmorName = Instance.GetName();
			Deserializer->ReadString(ArmorName);
			int Count;
			Deserializer->ReadRaw<int>(Count);
			Instance.SetCount(Count);
		}

	protected:

		std::string m_Name = "None";
		AGE::Ref<AGE::Texture2D> m_Texture;
		int m_Count = 0;
	};
}
