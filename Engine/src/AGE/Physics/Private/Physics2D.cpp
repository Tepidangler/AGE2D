#include "AGEpch.hpp"
#include "Physics/Public/Physics2D.h"
#include "Scene/Public/Entity.h"
#include "Scene/Public/Scene.h"
#include "Physics/Public/World2D.h"

namespace AGE
{
	bool Physics2D::CreateNewPhysicsWorld(Ref<Scene> scene)
	{
		m_World = World::Create(scene);

		return m_World == nullptr;
	}

	void Physics2D::DestroyWorld()
	{
		m_World->DestroyWorld();
	}

	void Physics2D::Step(TimeStep DeltaTime)

	{
		m_World->Step(DeltaTime);
	}

	b2BodyId Physics2D::CreateBody(b2BodyDef& Def)
	{
		return m_World->As<World2D>()->CreateBody(Def);
	}

	b2BodyDef Physics2D::MakeBodyDefinition(const BodyType& Type, const Vector3& Translation, const Vector3 Rotation, bool IsRotationFixed, void* UserData)
	{
		return m_World->As<World2D>()->MakeBodyDefinition(Type,Translation,Rotation,IsRotationFixed,UserData);
	}

	b2ShapeDef Physics2D::MakeShapeDefinition(float Density, float Friction, float Restitution, bool ShouldGenerateEvents, void* UserData)
	{
		return m_World->As<World2D>()->MakeShapeDefinition(Density,Friction,Restitution,ShouldGenerateEvents,UserData);
	}

	b2Rot Physics2D::MakeRotation(float Z)
	{
		return m_World->As<World2D>()->MakeRotation(Z);
	}

	b2Polygon Physics2D::CreateBox(float HeightX, float HeightY, const Vector3 Scale)
	{
		return m_World->As<World2D>()->CreateBox(HeightX,HeightY,Scale);
	}

	b2ShapeId Physics2D::CreatePolygonShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Polygon& Box)
	{
		return m_World->As<World2D>()->CreatePolygonShape(ID,Fixture,Box);
	}

	b2Capsule Physics2D::CreateCapsule(const Vector2& Offset, const Vector3 Scale, const float Radius)
	{
		return m_World->As<World2D>()->CreateCapsule(Offset,Scale,Radius);
	}

	b2ShapeId Physics2D::CreateCapsuleShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Capsule& Capsule)
	{
		return m_World->As<World2D>()->CreateCapsuleShape(ID,Fixture,Capsule);
	}

	b2Segment Physics2D::CreateSegment()
	{
		return m_World->As<World2D>()->CreateSegment();
	}

	b2ShapeId Physics2D::CreateSegmentShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Segment& Segment)
	{
		return m_World->As<World2D>()->CreateSegmentShape(ID,Fixture,Segment);
	}

	b2BodyId Physics2D::GetBody(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetBody(ID);
	}

	Vector2 Physics2D::GetBodyPosition(const b2BodyId& ID)
	{
		return m_World->As<World2D>()->GetBodyPosition(ID);
	}

	b2Polygon Physics2D::GetPolygon(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetPolygon(ID);
	}

	b2Capsule Physics2D::GetCapsule(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetCapsule(ID);
	}

	void* Physics2D::GetUserData(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetUserData(ID);
	}

	float Physics2D::GetRotationAngle(const b2BodyId& ID)
	{
		return m_World->As<World2D>()->GetRotationAngle(ID);
	}

	void Physics2D::QueryBoxOverlap(const QueryParams& Params)
	{
		m_World->QueryBoxOverlap(Params);
	}

	void Physics2D::QueryCapsuleOverlap(const QueryParams& Params)
	{
		m_World->QueryCapsuleOverlap(Params);
	}

	void Physics2D::QuerySegmentOverlap(const QueryParams& Params)
	{
		m_World->QuerySegmentOverlap(Params);
	}
	bool Physics2D::QueryHit(const QueryParams& Params)
	{
		return false;
	}
	//bool Physics2D::QueryCallback(b2ShapeId ShapeID, void* context)
	//{
	//	Box2DQueryContext* queryContext = static_cast<Box2DQueryContext*>(context);
	//
	//
	//
	//	b2BodyId bodyId = b2Shape_GetBody(ShapeID);
	//	b2BodyType bodyType = b2Body_GetType(bodyId);
	//	if (bodyType != b2_dynamicBody)
	//	{
	//		// continue query
	//		return true;
	//	}
	//
	//	b2Vec2 P{ queryContext->Point.x ,queryContext->Point.y };
	//	bool overlap = b2Shape_TestPoint(ShapeID, P);
	//	if (overlap)
	//	{
	//		// found shape
	//		queryContext->BodyID = bodyId;
	//		return false;
	//	}
	//
	//	return true;
	//}
	//bool Physics2D::OverlapCallback(b2ShapeId shapeID, void* context)
	//{
	//
	//	
	//	//add custom functionality
	//	//Entity userData = Entity(*(entt::entity*)(int*)b2Shape_GetUserData(shapeID), g_PhysicsData->SceneRef.get());
	//
	//	//if (userData && !userData.GetComponent<RigidBody2DComponent>().bInteractable)
	//	//{
	//	//	
	//	//	// continue the query
	//	//}
	//	//else
	//	//{
	//	//	return true;
	//	//
	//	//}
	//
	//	Scene* sample = (Scene*)context;
	//
	//	//if (sample->)
	//	//{
	//	//	int index = sample->m_doomCount;
	//	//	sample->m_doomIds[index] = shapeId;
	//	//	sample->m_doomCount += 1;
	//	//}
	//
	//	// continue the query
	//	return true;
	//}
}