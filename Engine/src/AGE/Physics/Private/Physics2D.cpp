#include "AGEpch.hpp"
#include "Physics/Public/Physics2D.h"
#include "Scene/Public/Entity.h"
#include "Scene/Public/Scene.h"
#include "Physics/Public/World2D.h"

namespace AGE
{
	/**
 * @brief Creates a new physics world for the given scene.
 * 
 * This function creates a new physics world and assigns it to the member variable `m_World`. It returns true if the creation was successful, false otherwise.
 * 
 * @param scene The scene for which to create the physics world.
 * @return True if the creation was successful, false otherwise.
 */
bool Physics2D::CreateNewPhysicsWorld(Ref<Scene> scene)
	{
		m_World = World::Create(scene);

		return m_World == nullptr;
	}

	/** 
 * @brief Destroys the physics world.
 * 
 * This function is used to destroy the physics world, freeing up any resources it was using. After calling this function, the physics world should not be used again until a new one has been created.
 * 
 * @return void
 */
void Physics2D::DestroyWorld()
	{
		m_World->DestroyWorld();
	}

	/** 
 * @brief This function steps the physics simulation by a given time step.
 * 
 * @param[in] DeltaTime The amount of time to simulate, in seconds.
 * 
 * @return void
 */
void Physics2D::Step(TimeStep DeltaTime)

	{
		m_World->Step(DeltaTime);
	}

	/** 
 * @brief Creates a body in the physics world.
 * 
 * This function creates a new body within the physics simulation based on the provided definition. The body is added to the physics world and its ID is returned.
 * 
 * @param Def A reference to the b2BodyDef that defines the properties of the new body.
 * @return The unique identifier (b2BodyId) for the newly created body.
 */
b2BodyId Physics2D::CreateBody(b2BodyDef& Def)
	{
		return m_World->As<World2D>()->CreateBody(Def);
	}

	/** 
 * @brief Creates a body definition for the physics world.
 * 
 * This function creates and returns a b2BodyDef object with the given parameters. The body type, translation, rotation, and whether the rotation is fixed are set based on the input parameters. User data can also be provided.
 * 
 * @param Type The type of the body to create.
 * @param Translation The initial position of the body.
 * @param Rotation The initial rotation of the body.
 * @param IsRotationFixed A flag indicating whether the rotation should be fixed or not.
 * @param UserData Pointer to any user data associated with the body.
 * 
 * @return Returns a b2BodyDef object based on the input parameters.
 */
b2BodyDef Physics2D::MakeBodyDefinition(const BodyType& Type, const Vector3& Translation, const Vector3& Rotation, bool IsRotationFixed, void* UserData)
	{
		return m_World->As<World2D>()->MakeBodyDefinition(Type,Translation,Rotation,IsRotationFixed,UserData);
	}

	/**
 * @brief Creates a shape definition with the given parameters.
 * 
 * This function creates and returns a shape definition using the provided density, friction, restitution, event generation flag, and user data. The resulting shape definition is then used to create a new shape in the physics world.
 * 
 * @param Density The density of the shape.
 * @param Friction The friction coefficient of the shape.
 * @param Restitution The restitution coefficient of the shape.
 * @param ShouldGenerateEvents A flag indicating whether collision events should be generated for this shape.
 * @param UserData Pointer to user-defined data associated with the shape.
 * 
 * @return b2ShapeDef The created shape definition.
 */
b2ShapeDef Physics2D::MakeShapeDefinition(float Density, float Friction, float Restitution, bool ShouldGenerateEvents, void* UserData)
	{
		return m_World->As<World2D>()->MakeShapeDefinition(Density,Friction,Restitution,ShouldGenerateEvents,UserData);
	}

	/**
 * @brief Creates a rotation object based on the given angle in radians.
 * 
 * This function creates and returns a rotation object using the provided angle (in radians). The resulting rotation can be used to rotate objects or perform other transformations.
 * 
 * @param Z The angle in radians for which to create the rotation.
 * @return A rotation object representing the specified angle.
 */
b2Rot Physics2D::MakeRotation(float Z)
	{
		return m_World->As<World2D>()->MakeRotation(Z);
	}

	/**
 * @brief Creates a box shape with the given dimensions and scale.
 * 
 * This function creates a box shape with the specified height in X and Y directions and applies the provided scale to it. The resulting b2Polygon is then returned by the function.
 * 
 * @param HeightX The horizontal extent of the box.
 * @param HeightY The vertical extent of the box.
 * @param Scale The scaling factor for the box shape.
 * 
 * @return A b2Polygon representing the created box shape.
 */
b2Polygon Physics2D::CreateBox(float HeightX, float HeightY, const Vector3& Scale)
	{
		return m_World->As<World2D>()->CreateBox(HeightX,HeightY,Scale);
	}

	/** 
 * @brief Creates a polygon shape for the given body with the specified fixture and box.
 * 
 * This function creates a polygon shape for the given body using the provided fixture definition and box. The resulting shape is then returned by the function.
 * 
 * @param ID The identifier of the body to create the shape for.
 * @param Fixture The fixture definition specifying the properties of the shape.
 * @param Box The polygon defining the vertices of the shape.
 * 
 * @return A unique identifier representing the newly created shape.
 */
b2ShapeId Physics2D::CreatePolygonShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Polygon& Box)
	{
		return m_World->As<World2D>()->CreatePolygonShape(ID,Fixture,Box);
	}

	/**
 * @brief Creates a capsule shape with the given parameters.
 * 
 * This function creates and returns a capsule shape using the provided offset, scale, and radius values. The capsule is created in the context of the current world.
 * 
 * @param Offset A Vector2 specifying the position of the capsule.
 * @param Scale A Vector3 specifying the scaling factors for the capsule.
 * @param Radius The float value representing the radius of the capsule.
 * 
 * @return b2Capsule The newly created capsule shape.
 */
b2Capsule Physics2D::CreateCapsule(const Vector2& Offset, const Vector3& Scale, const float Radius)
	{
		return m_World->As<World2D>()->CreateCapsule(Offset,Scale,Radius);
	}

	/** 
 * @brief Creates a capsule shape in the physics world.
 * 
 * This function creates a capsule shape with the given parameters and adds it to the specified body. The ID of the body is passed as an argument, along with the fixture definition and the dimensions of the capsule.
 * 
 * @param[in] ID The identifier for the body in which the capsule will be added.
 * @param[in] Fixture A structure containing the properties of the fixture to be applied to the shape.
 * @param[in] Capsule A structure containing the dimensions of the capsule (half-height, radius).
 * 
 * @return The identifier for the newly created capsule shape.
 */
b2ShapeId Physics2D::CreateCapsuleShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Capsule& Capsule)
	{
		return m_World->As<World2D>()->CreateCapsuleShape(ID,Fixture,Capsule);
	}

	/** 
 * @brief Creates a segment in the physics world.
 * 
 * This function creates and returns a new segment object within the physics world. The specifics of how this is done are not specified as it depends on the implementation of the World2D class.
 * 
 * @return A newly created segment object.
 */
b2Segment Physics2D::CreateSegment()
	{
		return m_World->As<World2D>()->CreateSegment();
	}

	/** 
 * @brief Creates a segment shape with the given parameters.
 * 
 * This function creates and adds a new segment shape to the physics world of the game engine. The segment is defined by two points in space.
 * 
 * @param ID A reference to the body id that this fixture will be attached to.
 * @param Fixture A structure containing the definition for the fixture (e.g., density, restitution).
 * @param Segment A structure representing the segment of the shape.
 * 
 * @return The unique identifier for the newly created segment shape.
 */
b2ShapeId Physics2D::CreateSegmentShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Segment& Segment)
	{
		return m_World->As<World2D>()->CreateSegmentShape(ID,Fixture,Segment);
	}

	/**
 * @brief Retrieves a body from the physics world using its shape id.
 * 
 * This function takes in a b2ShapeId, which is used to identify a specific shape within the physics world, and returns the corresponding b2BodyId. If no such body exists, it will return an invalid b2BodyId.
 * 
 * @param ID The unique identifier of the shape whose associated body we want to retrieve.
 * @return The b2BodyId that corresponds to the given shape id. Returns an invalid b2BodyId if no such body exists in the physics world.
 */
b2BodyId Physics2D::GetBody(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetBody(ID);
	}

	/**
 * @brief Get the position of a body in the 2D physics world.
 *
 * This function retrieves the current position of a body with a given ID in the 2D physics world.
 * The position is returned as a Vector2 object.
 *
 * @param ID The unique identifier for the body whose position you want to retrieve.
 * @return A Vector2 object representing the position of the specified body.
 */
Vector2 Physics2D::GetBodyPosition(const b2BodyId& ID)
	{
		return m_World->As<World2D>()->GetBodyPosition(ID);
	}

	/** 
 * @brief Retrieves a polygon from the physics world using its shape id.
 * 
 * This function takes an ID of type b2ShapeId as input and returns a b2Polygon object. It retrieves the polygon data associated with the given ID from the physics world.
 * 
 * @param[in] ID The unique identifier for the polygon in the physics world.
 * @return A b2Polygon object representing the polygon with the provided ID.
 */
b2Polygon Physics2D::GetPolygon(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetPolygon(ID);
	}

	/** 
 * @brief Retrieves a capsule with the given shape id.
 * @param[in] ID The unique identifier of the capsule to retrieve.
 * @return A b2Capsule object representing the retrieved capsule, or an empty one if no such capsule exists.
 */
b2Capsule Physics2D::GetCapsule(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetCapsule(ID);
	}

	/**
 * @brief Retrieves the user data associated with a given shape id.
 * 
 * This function retrieves the user data that was previously set using SetUserData() for a specific shape in the physics world.
 * The shape's ID is used to identify and retrieve its corresponding user data.
 *
 * @param[in] ID The unique identifier of the shape whose user data needs to be retrieved.
 * 
 * @return A void pointer to the user data associated with the given shape id, or nullptr if no such user data exists.
 */
void* Physics2D::GetUserData(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetUserData(ID);
	}

	/** 
 * @brief This function returns the rotation angle of a body with a given id.
 * 
 * @param ID The unique identifier for the body whose rotation angle is to be returned.
 * @return The rotation angle in radians. If no such body exists, it will return 0.
 */
float Physics2D::GetRotationAngle(const b2BodyId& ID)
	{
		return m_World->As<World2D>()->GetRotationAngle(ID);
	}

	/** 
 * @brief This function is used to perform a box overlap query in the physics world.
 * 
 * The function takes as input a QueryParams object which contains all the parameters required for the box overlap query. It then calls the QueryBoxOverlap method on the m_World object, passing it the QueryParams object.
 * 
 * @param Params A const reference to a QueryParams object containing the parameters for the box overlap query.
 * 
 * @return void This function does not return any value.
 */
void Physics2D::QueryBoxOverlap(const QueryParams& Params)
	{
		m_World->QueryBoxOverlap(Params);
	}

	/** 
 * @brief This function is used to query for overlapping between a capsule and the physics world.
 * 
 * @param Params The parameters of the capsule overlap query, including position, orientation, radius, and height.
 * @return void
 */
void Physics2D::QueryCapsuleOverlap(const QueryParams& Params)
	{
		m_World->QueryCapsuleOverlap(Params);
	}

	/** 
 * @brief This function is used to query for overlapping segments in the physics world.
 * 
 * @param Params The parameters of the segment overlap query, including start and end points, layer mask, etc.
 * 
 * @return void
 */
void Physics2D::QuerySegmentOverlap(const QueryParams& Params)
	{
		m_World->QuerySegmentOverlap(Params);
	}
	/** 
 * @brief This function is used to query for a hit in the physics simulation.
 * 
 * The function takes as input a const reference to a QueryParams object, which contains parameters related to the query. It returns a boolean value indicating whether or not a hit occurred based on these parameters.
 * 
 * @param Params A constant reference to an instance of QueryParams containing information about the query.
 * @return Returns true if a hit is detected and false otherwise.
 */
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