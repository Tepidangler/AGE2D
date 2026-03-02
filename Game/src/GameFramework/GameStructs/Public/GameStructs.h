/**

    @file      GameStructs.h
    @brief     
    @details   ~
    @author    De'Lano Wilcox
    @date      29.05.2025
    @copyright � Alcoy Game Studios, 2025. All right reserved.

**/
#pragma once
#include <cstdint>

namespace GameFramework
{

    struct PlayerStats
    {
    public:
        PlayerStats() = default;
        PlayerStats(const PlayerStats&) = default;

        std::string Name = "";
        uint32_t Level = 1;
        uint32_t HP = 0;
        uint32_t MP = 0;
        uint32_t Strength = 0;
        uint32_t Attack = 0;
        uint32_t MagicAttack = 0;
        uint32_t Defense = 0;
        uint32_t Agility = 0;
        uint32_t Speed = 0;
        uint32_t Luck = 0;
        float HitRate = 0.f;
        std::array<uint32_t, 10> Maxes;
    };
    struct EnemyStats
    {
    public:
        EnemyStats() = default;
        EnemyStats(const EnemyStats&) = default;
        EnemyStats(std::tuple<int,int,int,int,int,int,int,int,uint8_t,uint8_t,uint8_t,std::string> Tuple)
        {
            HP = (uint32_t)std::get<0>(Tuple);
            MP = (uint32_t)std::get<1>(Tuple);
            Strength = (uint32_t)std::get<2>(Tuple);
            MagicAttack = (uint32_t)std::get<3>(Tuple);
            Attack = (uint32_t)std::get<4>(Tuple);
            Defense = (uint32_t)std::get<5>(Tuple);
            Agility = (uint32_t)std::get<6>(Tuple);
            Speed = (uint32_t)std::get<7>(Tuple);
            Name = std::get<11>(Tuple);

        }
        uint32_t HP = 0;
    	uint32_t MP = 0;
        uint32_t Strength = 0;
        uint32_t MagicAttack = 0;
        uint32_t Attack = 0;
        uint32_t Defense = 0;
        uint32_t Agility = 0;
        uint32_t Speed = 0;
        uint32_t Luck = 0;
        float HitRate = 0.f;
        std::array<uint32_t, 10> Maxes;
        std::vector<uint16_t> Absorb;
        std::vector<uint16_t> Reduce;
        std::vector<uint16_t> Weak;
        std::string Name = "";

    };
}

