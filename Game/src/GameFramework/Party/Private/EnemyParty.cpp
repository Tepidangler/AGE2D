//
// Created by gdmgp on 11/27/2025.
//

#include <random>
#include <Core/Public/AGEpch.hpp>
#include <Age.h>
#include "Party/Public/Party.h"
#include "Characters/Public/Character.h"
#include "Inventory/Public/Inventory.h"

namespace GameFramework
{
    EnemyParty::EnemyParty()
    {
        m_Inventory = AGE::CreateRef<Inventory>();
    }

    void EnemyParty::AddPartyMember(std::pair<int, AGE::Ref<Character>> Member)
    {
        m_Party.emplace(Member);
    }
    void EnemyParty::AttachPartyMember(AGE::Ref<Character> Char)
    {
        int PartySize = 0; // ASPlayerParty::SizeOfParty();
        if (PartySize < m_PartyLimit)
        {
            //	Party.Push(Cast<ASPlayerCharacter>(member));
            m_Party.emplace(PartySize, Char);
            if (PartySize == 0)
            {
                SetPrimaryPartyMember(1);
            }
        }
        else if (PartySize == m_PartyLimit)
        {
            m_Party.emplace(m_PartyLimit, Char);
        }
    }
    void EnemyParty::DetachPartyMember(AGE::Ref<Character> Char)
    {
        int MemberPos = FindMember(Char);
        if (MemberPos > -1 && m_Party.size() > 1)
        {
            m_Party[MemberPos] = nullptr;
        }
    }

    void EnemyParty::GenerateEnemyParty()
    {
        std::random_device Device;
        std::mt19937 Rng(Device());
        std::uniform_int_distribution<> RngDist(1, 6);
        uint32_t PartyLimit = RngDist(Rng);

        SetPartyLimit(PartyLimit);

        for (int i = 0; i < m_PartyLimit; i++)
        {
            //Perhaps we can have a Enemy factory that pops out enemies randomly here
        }


    }

    int EnemyParty::FindMember(AGE::Ref<Character> Char)
    {
        for (uint32_t x = 0; x < m_Party.size(); ++x)
        {
            auto Member = m_Party.find(x);

            if (Char.get() == Member->second.get())
            {
                return Member->first;
            }
        }

        return -1;
    }

    size_t EnemyParty::GetMembersSize()
    {
        return m_Party.size();
    }

    bool EnemyParty::IsPartyAlive()
    {
        size_t NumOfUnconciousCharacters = 0;
        for (auto& M : m_Party)
        {
#if 0
            if (M.second.GetStats().HP <= 0)
            {
                NumOfUnconciousCharacters++;
            }
#endif
        }

        return NumOfUnconciousCharacters != m_Party.size();
    }

    template<>
    EnemyParty* Party::As()
    {
        return (EnemyParty*)this;
    }

}