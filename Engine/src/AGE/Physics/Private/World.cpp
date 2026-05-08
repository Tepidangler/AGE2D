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
    Re/**
 * @brief Creates a new instance of the World class.
 * 
 * This function creates and returns a new instance of the World class, which is specialized for handling 2D scenes. The scene parameter specifies the Scene that this world will be associated with.
 * 
 * @param scene A reference to the Scene object that this world will be associated with.
 * @return A reference to the newly created World instance.
 */
f<World> World::Create(Ref<Scene> scene)
    {
        return CreateRef<World2D>(scene);
    }

    template<typename T>
    T*/**
 * @brief This function is currently not implemented and will always assert false.
 * It returns a null pointer.
 *
 * @return nullptr Always.
 */
 World::As()
    {
        CoreLogger::Assert(false, "As() Failed!");
        return nullptr;
    }
}