/**

    @file      World2D.cpp
    @brief     
    @details   ~
    @author    De'Lano Wilcox
    @date      30.05.2025
    @copyright � Alcoy Game Studios, 2025. All right reserved.

**/
#include "AGEpch.hpp"
#include "Physics/Public/World2D.h"

namespace AGE
{
	static b2BodyType Rigid2DTypeToBox2DBody(BodyType BodyType)
	{
		switch (BodyType)
		{
		case BodyType::Static:
		{
			return b2_staticBody;
		}
		case BodyType::Dynamic:
		{
			return b2_dynamicBody;
		}
		case BodyType::Kinematic:
		{
			return b2_kinematicBody;
		}
		}

		AGE_CORE_ASSERT(false, "Unknown Body Type");
		return b2_staticBody;
	}

	World2D::World2D(Ref<Scene> scene)
		:m_WorldScene(scene)
	{
		b2WorldDef WorldDef = b2DefaultWorldDef();
		WorldDef.gravity = { 0.0f,-9.8f };
		m_World = b2CreateWorld(&WorldDef);
	}

	World2D::~World2D()
	{
		if (b2World_IsValid(m_World))
		{ 
			b2DestroyWorld(m_World);
		}
	}

	void World2D::DestroyWorld()
	{
		b2DestroyWorld(m_World);
	}

	void World2D::Step(TimeStep DeltaTime)
	{
		const int32_t SubStepCount = 4;

		b2World_Step(m_World, DeltaTime, SubStepCount);
	}

	void World2D::MakeDefaultQueryFilter()
	{
		m_QueryFilter = b2DefaultQueryFilter(); 
	}

	void World2D::QueryBoxOverlap(const QueryParams& Params)
	{
		Box2DQueryContext QC = { Params.Point2D,Params.InstigatorID };
		b2Transform Trans;
		Trans.p = { Params.Location.x,Params.Location.y };
		Trans.q = b2MakeRot(Params.Rotation.z);
		b2World_OverlapPolygon(m_World, &Params.Box2D, Trans, GetQueryFilter(), Params.OverlapFunc2D, Params.Context);
	}

	void World2D::QueryCapsuleOverlap(const QueryParams& Params)
	{
		Box2DQueryContext QC = { Params.Point2D,Params.InstigatorID };
		b2Transform Trans;
		Trans.p = { Params.Location.x,Params.Location.y };
		Trans.q = b2MakeRot(Params.Rotation.z);
		b2World_OverlapCapsule(m_World, &Params.Capsule2D, Trans, GetQueryFilter(), Params.OverlapFunc2D, Params.Context);
	}

	void World2D::QuerySegmentOverlap(const QueryParams& Params)
	{

		Box2DQueryContext QC = { Params.Point2D,Params.InstigatorID };
		b2Transform Trans;
		Trans.p = { Params.Location.x,Params.Location.y };
		Trans.q = b2MakeRot(Params.Rotation.z);
		b2AABB SegAABB = b2ComputeSegmentAABB(&Params.Segment2D, Trans);
		b2World_OverlapAABB(m_World, SegAABB, GetQueryFilter(), Params.OverlapFunc2D, &QC);
	}

	void World2D::QueryHit(const QueryParams& Params)
	{
		Box2DQueryContext QC = { Params.Point2D, Params.InstigatorID };
		b2Vec2 Origin = { Params.Point2D.x, Params.Point2D.y };
		b2Vec2 Translation = { Params.Location.x, Params.Location.y };

		//b2WorldId worldId, const b2Circle* circle, b2Transform originTransform, b2Vec2 translation, b2QueryFilter filter, b2CastResultFcn* fcn, void* context
		b2World_CastRay(m_World, Origin, Translation, GetQueryFilter(), Params.CastFunc2D, &QC);
	}

	b2BodyDef World2D::MakeBodyDefinition(const BodyType& Type, const Vector3& Translation, const Vector3 Rotation, bool IsRotationFixed, void* UserData)
	{
		b2BodyDef Def = b2DefaultBodyDef();

		Def.userData = UserData;
		Def.type = Rigid2DTypeToBox2DBody(Type);
		Def.position.x = Translation.x;
		Def.position.y = Translation.y;
		Def.rotation = b2MakeRot(Rotation.z);
		//Def.rotation = MakeRotation(Rotation.z);
		Def.fixedRotation = IsRotationFixed;
		
		return Def;
	}

	b2ShapeDef World2D::MakeShapeDefinition(float Density, float Friction, float Restitution, bool ShouldGenerateEvents, void* UserData)
	{
		b2ShapeDef Fixture = b2DefaultShapeDef();
		Fixture.userData = UserData;
		Fixture.density = Density;
		Fixture.friction = Friction;
		Fixture.restitution = Restitution;
		Fixture.enableContactEvents = ShouldGenerateEvents;
		Fixture.enableHitEvents = ShouldGenerateEvents;

		return Fixture;
	}

	b2Rot World2D::MakeRotation(float Z)
	{
		return b2MakeRot(Z);
	}

	b2Polygon World2D::CreateBox(float HeightX, float HeightY, const Vector3 Scale)
	{
		return b2MakeBox(HeightX * Scale.x, HeightY * Scale.y);
	}

	b2ShapeId World2D::CreatePolygonShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Polygon& Box)
	{
		return b2CreatePolygonShape(ID, &Fixture, &Box);
	}

	b2Capsule World2D::CreateCapsule(const Vector2& Offset, const Vector3 Scale, const float Radius)
	{
		b2Capsule Capsule;
		Capsule.center1 = { Offset.x * Scale.x, Offset.y * Scale.y };
		Capsule.center2 = { (Offset.x * Scale.x) - 1.f, (Offset.y * Scale.y) - 1.f };
		Capsule.radius = Scale.x * Radius;

		return Capsule;
	}

	b2ShapeId World2D::CreateCapsuleShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Capsule& Capsule)
	{
		return b2CreateCapsuleShape(ID, &Fixture, &Capsule);
	}

	b2Segment World2D::CreateSegment()
	{
		return { {0.f, 0.f},{1.f, 0.f} };
	}

	b2ShapeId World2D::CreateSegmentShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Segment& Segment)
	{
		return b2CreateSegmentShape(ID, &Fixture, &Segment);
	}

	b2BodyId World2D::CreateBody(b2BodyDef& Def)
	{
		return b2CreateBody(m_World, &Def);;
	}

	b2BodyId World2D::GetBody(const b2ShapeId& ID)
	{
		return b2Shape_GetBody(ID);
	}

	Vector2 World2D::GetBodyPosition(const b2BodyId& ID)
	{
		b2Vec2 Vec = b2Body_GetPosition(ID);
		return Vector2(Vec.x, Vec.y);
	}

	b2Polygon World2D::GetPolygon(const b2ShapeId& ID)
	{
		return b2Shape_GetPolygon(ID);
	}

	b2Capsule World2D::GetCapsule(const b2ShapeId& ID)
	{
		return b2Shape_GetCapsule(ID);
	}

	float World2D::GetRotationAngle(const b2BodyId& ID)
	{
		return Math::Degrees(b2Rot_GetAngle(b2Body_GetRotation(ID)));
	}

	void* World2D::GetUserData(const b2ShapeId& ID)
	{
		return b2Shape_GetUserData(ID);
	}

	b2WorldId& World2D::GetWorld()
	{
		return m_World;
	}
	Ref<Scene>& World2D::GetWorldScene()
	{
		return m_WorldScene;
	}

	template<>
	World2D* World::As()
	{
		return (World2D*)this;
	}
}