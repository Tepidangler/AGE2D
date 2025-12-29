#include <Core/Public/AGEpch.hpp>
#include <Age.h>
#include "Party/Public/Party.h"

namespace GameFramework
{
    AGE::Ref<Party> Party::Create(PartyType Type)
    {
        switch (Type)
        {
            case PartyType::Player:
            {
                return AGE::CreateRef<PlayerParty>();
                break;
            }
            case PartyType::Enemy:
            {
                return AGE::CreateRef<EnemyParty>();
                break;
            }
        }
    }


}