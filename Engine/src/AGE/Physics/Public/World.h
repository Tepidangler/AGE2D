/**

    @file      World.h
    @brief     
    @details   ~
    @author    De'Lano Wilcox
    @date      29.05.2025
    @copyright © Alcoy Game Studios, 2025. All right reserved.

**/
#pragma once
#include "Core/Public/Core.h"
#include <box2d/box2d.h>
#include "Scene/Public/Scene.h"


namespace AGE
{
    class World
    {
    public:
        virtual void DestroyWorld() = 0;

        virtual void Step(TimeStep DeltaTime) = 0;

        virtual void MakeDefaultQueryFilter() = 0;
        virtual void QueryBoxOverlap(const QueryParams& Params) = 0;
        virtual void QueryCapsuleOverlap(const QueryParams& Params) = 0;
        virtual void QuerySegmentOverlap(const QueryParams& Params) = 0;
        virtual void QueryHit(const QueryParams& Params) = 0;
        template<typename T>
        T* As();

        static Ref<World> Create(Ref<Scene> scene);


    };
}