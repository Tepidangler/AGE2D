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
 * This function creates a new physics world and assigns it to the member variable `m_World`. It then checks if the creation was successful by checking if `m_World` is null. If the creation was not successful, it returns true; otherwise, false.
 *
 * @param scene The scene for which to create a new physics world.
 * @return True if the creation of the physics world was unsuccessful (i.e., `m_World` is null), and false otherwise.
 */
bool Physics2D::CreateNewPhysicsWorld(Ref<Scene> scene)
	{
		m_World = World::Create(scene);

		return m_World == nullptr;
	}

	/**
 * @brief Destroys the 2D physics world.
 * 
 * This function is used to destroy the 2D physics world, which will free up any resources that were being used by it.
 * After calling this function, you should not use the world anymore as it has been destroyed.
 */
void Physics2D::DestroyWorld()
	{
		m_World->DestroyWorld();
	}

	/**
 * @brief This function steps the physics simulation by a given time step.
 * 
 * The function takes in a TimeStep parameter which represents the amount of time to step the simulation forward.
 * It then calls the Step() method on the m_World object with this DeltaTime as an argument, effectively advancing the simulation that many seconds further.
 *
 * @param DeltaTime - A floating point value representing the amount of time to step the physics simulation by.
 */
void Physics2D::Step(TimeStep DeltaTime)

	{
		m_World->Step(DeltaTime);
	}

	/**
 * @brief Creates a new body in the physics world.
 * 
 * This function creates a new rigid body with the given definition and adds it to the physics world. The function returns an identifier for the newly created body, which can be used to manipulate the body later on.
 * 
 * @param Def A reference to the b2BodyDef that specifies the properties of the new body.
 * @return An identifier (b2BodyId) for the newly created body.
 */
b2BodyId Physics2D::CreateBody(b2BodyDef& Def)
	{
		return m_World->As<World2D>()->CreateBody(Def);
	}

	/**
 * @brief Creates a body definition for the physics world.
 * 
 * This function creates and returns a b2BodyDef object with the specified parameters. The body type, translation, rotation, and whether the rotation is fixed are set based on the input arguments. User data can also be provided.
 * 
 * @param Type The type of the body to create.
 * @param Translation The initial position of the body.
 * @param Rotation The initial rotation of the body.
 * @param IsRotationFixed A flag indicating whether the rotation should be fixed or not.
 * @param UserData Pointer to any user data associated with the body.
 * 
 * @return Returns a b2BodyDef object based on the input parameters.
 */
b2BodyDef Physics2D::MakeBodyDefinition(const BodyType& Type, const Vector3& Translation, const Vector3 Rotation, bool IsRotationFixed, void* UserData)
	{
		return m_World->As<World2D>()->MakeBodyDefinition(Type,Translation,Rotation,IsRotationFixed,UserData);
	}

	/**
 * @brief Creates a shape definition for the physics world.
 * 
 * This function creates and returns a shape definition with specified density, friction, restitution, event generation flag, and user data. The resulting shape definition is then used by the physics world to create new shapes.
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
 * @param Scale A Vector3 representing the scaling factor for the box.
 * 
 * @return b2Polygon The created box shape with specified dimensions and scale.
 */
b2Polygon Physics2D::CreateBox(float HeightX, float HeightY, const Vector3 Scale)
	{
		return m_World->As<World2D>()->CreateBox(HeightX,HeightY,Scale);
	}

	/** 
 * @brief Creates a polygon shape for the given body with the specified fixture and box.
 * 
 * This function creates a polygon shape for the body identified by 'ID' using the provided fixture definition and box data. The created shape is then returned.
 * 
 * @param ID The identifier of the body to create the shape for.
 * @param Fixture The fixture definition specifying properties of the shape.
 * @param Box The polygon defining the shape.
 * 
 * @return A unique identifier representing the created shape.
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
 * @param Offset A Vector2 representing the position of the capsule.
 * @param Scale A Vector3 representing the scaling factors for the capsule.
 * @param Radius The float value representing the radius of the capsule.
 * 
 * @return b2Capsule The created capsule shape.
 */
b2Capsule Physics2D::CreateCapsule(const Vector2& Offset, const Vector3 Scale, const float Radius)
	{
		return m_World->As<World2D>()->CreateCapsule(Offset,Scale,Radius);
	}

	/**
 * @brief Creates a capsule shape in the physics world.
 * 
 * This function creates a capsule shape with the given parameters and adds it to the specified body. The function returns an identifier for the newly created shape.
 * 
 * @param ID The identifier of the body to which the new shape will be added.
 * @param Fixture A structure containing the fixture definition, including density, friction, restitution, etc.
 * @param Capsule A structure containing the dimensions of the capsule (radius and height).
 * 
 * @return The identifier for the newly created shape.
 */
b2ShapeId Physics2D::CreateCapsuleShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Capsule& Capsule)
	{
		return m_World->As<World2D>()->CreateCapsuleShape(ID,Fixture,Capsule);
	}

	/**
 * @brief Creates a new segment in the physics world.
 * 
 * This function creates and returns a new segment object within the physics world. The specifics of how this is done are not defined by this function, but it's assumed that the physics engine used has a method for creating segments.
 * 
 * @return b2Segment A newly created segment in the physics world.
 */
b2Segment Physics2D::CreateSegment()
	{
		return m_World->As<World2D>()->CreateSegment();
	}

	/**
 * @brief Creates a segment shape in the physics world.
 * 
 * This function creates a new segment shape within the physics world and assigns it to the specified body. The segment is defined by two points (endpoints).
 * 
 * @param ID The identifier of the body to which the segment shape will be attached.
 * @param Fixture A structure containing the definition for the segment shape. This includes properties like density, friction, and restitution.
 * @param Segment A structure representing the endpoints of the segment. It contains two points (start and end).
 * 
 * @return The identifier of the newly created segment shape.
 */
b2ShapeId Physics2D::CreateSegmentShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Segment& Segment)
	{
		return m_World->As<World2D>()->CreateSegmentShape(ID,Fixture,Segment);
	}

	/**
 * @brief Retrieves a body from the physics world using its shape id.
 * 
 * This function takes in a b2ShapeId, which is used to identify a specific shape within the physics world. It then returns the corresponding b2BodyId, which can be used to access more detailed information about that body.
 * 
 * @param ID The unique identifier for the shape whose associated body we want to retrieve.
 * @return The b2BodyId of the body associated with the given shape id. If no such body exists, this function returns an invalid b2BodyId.
 */
b2BodyId Physics2D::GetBody(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetBody(ID);
	}

	/** 
 * @brief Get the position of a body in the physics world.
 * 
 * This function retrieves the current position of a body with a given ID in the physics world.
 * The position is returned as a Vector2 object.
 * 
 * @param ID A constant reference to the b2BodyId of the body whose position we want to retrieve.
 * @return A Vector2 object representing the position of the specified body.
 */
Vector2 Physics2D::GetBodyPosition(const b2BodyId& ID)
	{
		return m_World->As<World2D>()->GetBodyPosition(ID);
	}

	/**
 * @brief Retrieves a polygon from the physics world using its shape id.
 * 
 * This function takes an ID of type b2ShapeId as input and returns a b2Polygon object. It retrieves the polygon data associated with the given shape id from the physics world.
 * 
 * @param[in] ID The unique identifier for the shape whose polygon is to be retrieved.
 * @return A b2Polygon object representing the polygon of the specified shape.
 */
b2Polygon Physics2D::GetPolygon(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetPolygon(ID);
	}

	/**
 * @brief Retrieves a capsule with the given identifier.
 * 
 * This function retrieves and returns a capsule from the physics world using its unique identifier.
 * The capsule is retrieved through the `World2D` object associated with the physics world, which is accessed via the `As<World2D>()` method.
 * If no capsule exists with the given ID, an exception will be thrown.
 * 
 * @param ID A constant reference to the identifier of the capsule to retrieve.
 * @return The capsule associated with the provided identifier.
 * 
 * @throws std::runtime_error if no capsule is found with the provided ID.
 */
b2Capsule Physics2D::GetCapsule(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetCapsule(ID);
	}

	/**
 * @brief Retrieves user data associated with a specific shape id.
 * 
 * This function retrieves the user data that was previously set using Physics2D::SetUserData() for a given b2ShapeId.
 * The retrieved data is cast to void* and can be reinterpreted as any other type based on how it was originally stored.
 *
 * @param ID The shape id of the object whose user data needs to be retrieved.
 * 
 * @return A pointer to the user data associated with the given shape id, or nullptr if no such data exists.
 */
void* Physics2D::GetUserData(const b2ShapeId& ID)
	{
		return m_World->As<World2D>()->GetUserData(ID);
	}

	/** 
 * @brief This function returns the rotation angle of a body with a given id.
 * 
 * @param ID The unique identifier for the body whose rotation angle is to be returned.
 * @return float Returns the rotation angle in degrees. If no such body exists, it will return -1.0.
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
 * @brief This function is used to query for overlapping between a capsule and the world.
 * 
 * @param Params The parameters of the capsule overlap query.
 * 
 * @return void
 */
void Physics2D::QueryCapsuleOverlap(const QueryParams& Params)
	{
		m_World->QueryCapsuleOverlap(Params);
	}

	/**
 * @brief This function is used to query for overlapping segments in the physics world.
 * 
 * The function takes a QueryParams object as input, which contains parameters defining the segment to be queried. It then uses this information to perform an overlap query on the physics world.
 * 
 * @param Params A const reference to a QueryParams object containing the parameters for the segment overlap query.
 * 
 * @return void This function does not return any value.
 */
void Physics2D::QuerySegmentOverlap(const QueryParams& Params)
	{
		m_World->QuerySegmentOverlap(Params);
	}
	/**
 * @brief This function is used to perform a 2D physics query with the given parameters.
 * 
 * @param Params A const reference to an object of type QueryParams, which contains all necessary information for the query.
 * 
 * @return Returns true if there was a hit during the query, false otherwise.
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