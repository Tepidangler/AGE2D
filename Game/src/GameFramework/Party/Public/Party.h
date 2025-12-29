#pragma once
#include <Age.h>
#include <map>


namespace GameFramework
{
	class Character;
	class Inventory;

	enum class PartyType : uint8_t
	{
		Player,
		Enemy
	};

	class Party
	{
	public:
		virtual ~Party() = default;
		virtual AGE::Ref<Character> GetPrimaryPartyMember() = 0;
		virtual void AddPartyMember(std::pair<int, AGE::Ref<Character>> Member) = 0;
		virtual void ReplacePartyMember(int Key, AGE::Ref<Character> Char) = 0;
		virtual std::map<int, AGE::Ref<Character>> GetMembers() = 0;
		virtual int FindMember(AGE::Ref<Character> Char) = 0;
		virtual void SetPrimaryPartyMember(int Key) = 0;
		virtual void SetPartyLimit(int Limit) = 0;
		virtual int GetPartyLimit() = 0;
		virtual void RestoreStats() = 0;
		virtual size_t GetMembersSize() = 0;
		virtual bool IsPartyAlive() = 0;
		virtual void AttachPartyMember(AGE::Ref<Character> Char) = 0;
		virtual void DetachPartyMember(AGE::Ref<Character> Char)= 0;

		virtual bool AddXP(int XP) = 0;
		virtual AGE::Ref<Inventory>& GetInventory()= 0;
		static AGE::Ref<Party> Create(PartyType Type);

		template<typename T>
		T* As();

	protected:
		AGE::Ref<Inventory> m_Inventory;
		std::map<int, AGE::Ref<Character>> m_Party;
		int m_PartyLimit = 4;
	};

	class PlayerParty : public Party
	{
	public:
		PlayerParty();
		AGE::Ref<Character> GetPrimaryPartyMember() override;
		void AddPartyMember(std::pair<int, AGE::Ref<Character>> Member) override;
		void ReplacePartyMember(int Key, AGE::Ref<Character> Char) override;
		std::map<int, AGE::Ref<Character>> GetMembers() override;
		int FindMember(AGE::Ref<Character> Char) override;
		void SetPrimaryPartyMember(int Key) override;
		void SetPartyLimit(int Limit) override;
		int GetPartyLimit() override;
		void RestoreStats() override;
		size_t GetMembersSize() override;
		bool IsPartyAlive() override;
		void AttachPartyMember(AGE::Ref<Character> Char) override;
		void DetachPartyMember(AGE::Ref<Character> Char) override;

		bool AddXP(int XP) override;

		AGE::Ref<Inventory>& GetInventory() override { return m_Inventory; }
	private:
		int m_ControlledCharacterKey = 0;
	};

	class EnemyParty : public Party
	{
	public:
		EnemyParty();
		AGE::Ref<Character> GetPrimaryPartyMember() override {return nullptr;};
		void AddPartyMember(std::pair<int, AGE::Ref<Character>> Member) override;
		void ReplacePartyMember(int Key, AGE::Ref<Character> Char) override {};
		std::map<int, AGE::Ref<Character>> GetMembers() override {return m_Party;};
		int FindMember(AGE::Ref<Character> Char) override;
		void SetPrimaryPartyMember(int Key) override{};
		void SetPartyLimit(int Limit) override{ m_PartyLimit = Limit; };
		int GetPartyLimit() override{return m_PartyLimit;};
		void RestoreStats() override{};
		size_t GetMembersSize() override;
		bool IsPartyAlive() override;
		void AttachPartyMember(AGE::Ref<Character> Char) override;
		void DetachPartyMember(AGE::Ref<Character> Char) override;

		void GenerateEnemyParty();

		bool AddXP(int XP) override {return false;};

		AGE::Ref<Inventory>& GetInventory() { return m_Inventory; }

	private:

		int m_ControlledCharacterKey = 0;
	};


}