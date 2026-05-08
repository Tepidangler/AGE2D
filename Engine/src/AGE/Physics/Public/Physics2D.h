/**

    @file      Physics2D.h
    @brief     Abstraction layer for Box2D
    @details   This class provides an interface for the Box2D API allowing for ENGINE PROGRAMMERS to something or other
    @author    De'Lano Wilcox
    @date      30.05.2025
    @copyright � Alcoy Game Studios, 2025. All right reserved.

**/
#pragma once

#include "Core/Public/DeltaTime.h"
#include "Structs/Public/DataStructures.h"
#include "Physics/Public/World.h"
#include "Scene/Public/Components.h"
#include <box2d/types.h>

namespace AGE
{
	class Physics2D final
	{
	public:

		Ph/**
 * @brief Default constructor for the ysics2D class.
 *
 * This function initializes a new instance of the ysics2D class with default values.
 * It does not take any parameters and returns an object of type ysics2D.
 * 
 * @return A new instance of the ysics2D class with default values.
 */
ysics2D() = default;

		vi/**
 * @brief Virtual destructor for the Physics2D class.
 *
 * This function is responsible for freeing any resources that were allocated by the object during its lifetime. It does not return anything and thus, it has a void return type.
 */
rtual ~Physics2D() = default;

		bool CreateNewPhysicsWorld(Ref<Scene> scene);

		void DestroyWorld();

		void Step(TimeStep DeltaTime);

		b2BodyId CreateBody(b2BodyDef& Def);

		b2BodyDef MakeBodyDefinition(const BodyType& Type, const Vector3& Translation, const Vector3 Rotation, bool IsRotationFixed, void* UserData);

		b2ShapeDef MakeShapeDefinition(float Density, float Friction, float Restitution, bool ShouldGenerateEvents, void* UserData);

		b2Rot MakeRotation(float Z);

		b2Polygon CreateBox(float HeightX, float HeightY, const Vector3 Scale);
		b2ShapeId CreatePolygonShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Polygon& Box);

		b2Capsule CreateCapsule(const Vector2& Offset, const Vector3 Scale, const float Radius);
		b2ShapeId CreateCapsuleShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Capsule& Capsule);

		b2Segment CreateSegment();
		b2ShapeId CreateSegmentShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Segment& Segment);

		b2BodyId GetBody(const b2ShapeId& ID);

		Vector2 GetBodyPosition(const b2BodyId& ID);

		b2Polygon GetPolygon(const b2ShapeId& ID);

		b2Capsule GetCapsule(const b2ShapeId& ID);

		void* GetUserData(const b2ShapeId& ID);
		float GetRotationAngle(const b2BodyId& ID);

		void QueryBoxOverlap(const QueryParams& Params);

		void QueryCapsuleOverlap(const QueryParams& Params);

		void QuerySegmentOverlap(const QueryParams& Params);

		bool QueryHit(const QueryParams& Params);

		Re/**
 * @brief Returns a reference to the World object.
 *
 * This function returns a reference to the World object that is currently being used by the program. The returned object can be modified or accessed directly, allowing for changes to be made to the state of the world.
 * 
 * @return A reference to the current World object.
 */
f<World>& GetWorld() { return m_World; }

		template<typename T>
		st/**
 * @brief Retrieves a shape from its ID.
 * 
 * This function retrieves and returns the shape based on the provided ID. The type of shape returned depends on the value of the ID, which is determined by calling b2Shape_GetType().
 * 
 * @param[in] ID The unique identifier for a shape.
 * @return A shape object corresponding to the given ID. If no matching shape exists, it returns a default polygon shape.
 */
atic T GetShapeFromID(b2ShapeId ID)
		{
			switch (b2Shape_GetType(ID))
			{
			case b2_capsuleShape:
			{
				return b2Shape_GetCapsule(ID);
				break;
			}
			case b2_polygonShape:
			{
				return b2Shape_GetPolygon(ID);
				break;
			}
			case b2_segmentShape:
			{
				return b2Shape_GetSegment(ID);
				break;
			}
			default:
			{
				break;
			}
			}
			return b2Shape_GetPolygon(ID);
		}
	private:

		Ref<World> m_World;
	};
}