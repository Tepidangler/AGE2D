/**

    @file      World.cpp
    @brief     
    @details   ~
    @author    De'Lano Wilcox
    @date      29.05.2025
    @copyright � Alcoy Game Studios, 2025. All right reserved.

**/

#include "AGEpch.hpp"
#include "Physics/Public/World.h"
#include "Physics/Public/World2D.h"

namespace AGE
{
    Ref<World> World::Create(Ref<Scene> scene)
    {
        return CreateRef<World2D>(scene);
    }

    template<typename T>
    T* World::As()
    {
        AGE_CORE_ASSERT(false, "As() Failed!");
        return nullptr;
    }
}