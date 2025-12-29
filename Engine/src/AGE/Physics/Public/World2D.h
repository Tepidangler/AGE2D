/**

    @file      World2D.h
    @brief     
    @details   ~
    @author    De'Lano Wilcox
    @date      29.05.2025
    @copyright © Alcoy Game Studios, 2025. All right reserved.

**/
#pragma once
#include "Core/Public/Core.h"
#include "Physics/Public/World.h"
#include "Scene/Public/Components.h"


namespace AGE
{
    class World2D final : public World
    {
    public:
        World2D(Ref<Scene> scene);

        virtual ~World2D();

        virtual void DestroyWorld() override;

        virtual void Step(TimeStep DeltaTime) override;

        virtual void MakeDefaultQueryFilter() override;

        virtual void QueryBoxOverlap(const QueryParams& Params) override;
        virtual void QueryCapsuleOverlap(const QueryParams& Params) override;
        virtual void QuerySegmentOverlap(const QueryParams& Params) override;
        virtual void QueryHit(const QueryParams& Params) override;

        b2QueryFilter& GetQueryFilter() { return m_QueryFilter; }

        b2BodyDef MakeBodyDefinition(const BodyType& Type, const Vector3& Translation, const Vector3 Rotation, bool IsRotationFixed, void* UserData);

        b2ShapeDef MakeShapeDefinition(float Density, float Friction, float Restitution, bool ShouldGenerateEvents, void* UserData);

        b2Rot MakeRotation(float Z);

        b2Polygon CreateBox(float HeightX, float HeightY, const Vector3 Scale);
        b2ShapeId CreatePolygonShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Polygon& Box);

        b2Capsule CreateCapsule(const Vector2& Offset, const Vector3 Scale, const float Radius);
        b2ShapeId CreateCapsuleShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Capsule& Capsule);

        b2Segment CreateSegment();
        b2ShapeId CreateSegmentShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Segment& Segment);



        b2BodyId CreateBody(b2BodyDef& Def);

        b2BodyId GetBody(const b2ShapeId& ID);

        Vector2 GetBodyPosition(const b2BodyId& ID);

        b2Polygon GetPolygon(const b2ShapeId& ID);

        b2Capsule GetCapsule(const b2ShapeId& ID);


        float GetRotationAngle(const b2BodyId& ID);

        void* GetUserData(const b2ShapeId& ID);

        b2WorldId& GetWorld();

        Ref<Scene>& GetWorldScene();

    private:

        b2WorldId m_World = { 0,0 };

        Ref<Scene> m_WorldScene = nullptr;

        b2QueryFilter m_QueryFilter;
    };
}