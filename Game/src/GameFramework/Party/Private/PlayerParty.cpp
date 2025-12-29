//
// Created by gdmgp on 11/26/2025.
//
#include <Core/Public/AGEpch.hpp>
#include <Age.h>
#include "Party/Public/Party.h"
#include "Characters/Public/Character.h"
#include "Inventory/Public/Inventory.h"

namespace GameFramework
{
    PlayerParty::PlayerParty()
    {
        m_Inventory = AGE::CreateRef<Inventory>();
    }

    AGE::Ref<Character> PlayerParty::GetPrimaryPartyMember()
    {
        return m_Party[m_ControlledCharacterKey];
    }
    void PlayerParty::AddPartyMember(std::pair<int, AGE::Ref<Character>> Member)
    {
        m_Party.emplace(Member);
    }
    void PlayerParty::AttachPartyMember(AGE::Ref<Character> Char)
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
    void PlayerParty::DetachPartyMember(AGE::Ref<Character> Char)
    {
        int MemberPos = FindMember(Char);
        if (MemberPos > -1 && m_Party.size() > 1)
        {
            m_Party[MemberPos] = nullptr;
        }
    }
    void PlayerParty::ReplacePartyMember(int Key, AGE::Ref<Character> Char)
    {
        m_Party[Key] = Char;
    }

    std::map<int, AGE::Ref<Character>> PlayerParty::GetMembers()
    {
        return m_Party;
    }

    int PlayerParty::FindMember(AGE::Ref<Character> Char)
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
    void PlayerParty::SetPrimaryPartyMember(int Key)
    {
        int PartySize = (int)m_Party.size();

        if (Key < PartySize)
        {
            m_ControlledCharacterKey = Key;
        }
    }

    void PlayerParty::SetPartyLimit(int Limit)
    {
        m_PartyLimit = Limit;
    }
    int PlayerParty::GetPartyLimit()
    {
        return m_PartyLimit;
    }

    void PlayerParty::RestoreStats()
    {
        for (auto& M : m_Party)
        {
            //M.second->ResetStats();
        }
    }

    size_t PlayerParty::GetMembersSize()
    {
        return m_Party.size();
    }

    bool PlayerParty::IsPartyAlive()
    {
        size_t NumOfUnconciousCharacters = 0;
        for (auto& M : m_Party)
        {
#if 0
            if (M.second->GetStats().HP <= 0)
            {
                NumOfUnconciousCharacters++;
            }
#endif
        }

        return NumOfUnconciousCharacters != m_Party.size();
    }

    bool PlayerParty::AddXP(int XP)
    {
        for (auto& C : m_Party)
        {
            C.second->AddXP(XP);
        }
        return false;
    }

    template<>
    PlayerParty* Party::As()
    {
        return (PlayerParty*)this;
    }
}