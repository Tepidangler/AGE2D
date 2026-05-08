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
	st/**
 * @brief Converts a Rigid body type to Box2D's body type.
 *
 * This function takes in a `BodyType` and returns the corresponding `b2BodyType` from Box2D. 
 * The possible values for `BodyType` are: Static, Dynamic, Kinematic.
 * For each of these types, this function will return b2_staticBody, b2_dynamicBody or b2_kinematicBody respectively.
 * If the input is not one of these three types, an assertion error with message "Unknown Body Type" is thrown and the function returns `b2_staticBody`.
 * 
 * @param BodyType The type of body to convert.
 * @return b2BodyType The corresponding Box2D body type.
 */
atic b2BodyType Rigid2DTypeToBox2DBody(BodyType BodyType)
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

		CoreLogger::Assert(false, "Unknown Body Type");
		return b2_staticBody;
	}

	Wo/**
 * @brief Constructs a new instance of World2D with the given scene and sets up the Box2D world with default gravity.
 * @param scene The Scene to be associated with this World2D.
 */
rld2D::World2D(Ref<Scene> scene)
		:m_WorldScene(scene)
	{
		b2WorldDef WorldDef = b2DefaultWorldDef();
		WorldDef.gravity = { 0.0f,-9.8f };
		m_World = b2CreateWorld(&WorldDef);
	}

	Wo/**
 * @brief Destructor for the World2D class. It destroys the Box2D world if it is valid.
 */
rld2D::~World2D()
	{
		if (b2World_IsValid(m_World))
		{ 
			b2DestroyWorld(m_World);
		}
	}

	vo/** 
 * @brief Destroys the Box2D world object.
 *
 * This function is used to destroy the Box2D world object, which was previously created using World2D::CreateWorld(). It calls b2DestroyWorld() on the m_World member variable of the current instance of the class.
 * 
 * @return void
 */
id World2D::DestroyWorld()
	{
		b2DestroyWorld(m_World);
	}

	vo/**
 * @brief This function steps the simulation forward in time.
 * 
 * The function takes a timestep as input and performs multiple substeps to simulate physics accurately.
 * It uses the Box2D library's internal step method for this purpose.
 *
 * @param DeltaTime The amount of time that has passed since the last frame, in seconds.
 * 
 * @return void
 */
id World2D::Step(TimeStep DeltaTime)
	{
		const int32_t SubStepCount = 4;

		b2World_Step(m_World, DeltaTime, SubStepCount);
	}

	vo/**
 * @brief Sets the query filter to default values.
 *
 * This function sets the member variable m_QueryFilter to its default value, which is a call to b2DefaultQueryFilter().
 * The purpose of this function is to reset the state of the object and prepare it for use in a new scenario.
 * 
 * @return void
 */
id World2D::MakeDefaultQueryFilter()
	{
		m_QueryFilter = b2DefaultQueryFilter(); 
	}

	vo/**
 * @brief Queries for overlaps in the world with a box shape at a given location and rotation.
 * 
 * This function queries the physics world for any overlaps between an arbitrary box shape and other objects in the world, using the provided parameters. The box's position and orientation are defined by the `Location` and `Rotation` parameters respectively. The `Point2D` parameter is used to specify a point within the box that will be tested for overlap with other objects.
 * 
 * @param Params A structure containing all necessary information for the query, including the box shape (`Box2D`), the location and rotation of the box (`Location` and `Rotation` respectively), an instigator ID (`InstigatorID`) that can be used to identify the source of the overlap query, a function pointer (`OverlapFunc2D`) for handling overlaps, and a context pointer (`Context`) that can be used by the overlap handler.
 * 
 * @return An identifier representing the result of the query. This could be an error code or another form of status information depending on how the function is implemented. The exact meaning of this return value would depend on the specifics of the implementation and usage of this function.
 */
id World2D::QueryBoxOverlap(const QueryParams& Params)
	{
		Box2DQueryContext QC = { Params.Point2D,Params.InstigatorID };
		b2Transform Trans;
		Trans.p = { Params.Location.x,Params.Location.y };
		Trans.q = b2MakeRot(Params.Rotation.z);
		//b2World_OverlapPolygon(m_World, &Params.Box2D, Trans, GetQueryFilter(), Params.OverlapFunc2D, Params.Context);
	}

	vo/**
 * @brief Queries for overlapping with a capsule shape at the given location and rotation.
 * 
 * This function queries for any overlap between a capsule shape defined by `Capsule2D` and another object in the world,
 * using the provided parameters such as `Point2D`, `InstigatorID`, `Location`, `Rotation` etc. The query is performed
 * with respect to the given transform (location and rotation). The results are passed to an overlap function specified by 
 * `OverlapFunc2D` along with a context pointer provided in `Context`.
 *
 * @param Params Query parameters containing details about the capsule, location, rotation etc.
 * @return An identifier for the query result which can be used later to retrieve more information if needed.
 */
id World2D::QueryCapsuleOverlap(const QueryParams& Params)
	{
		Box2DQueryContext QC = { Params.Point2D,Params.InstigatorID };
		b2Transform Trans;
		Trans.p = { Params.Location.x,Params.Location.y };
		Trans.q = b2MakeRot(Params.Rotation.z);
		//b2World_OverlapCapsule(m_World, &Params.Capsule2D, Trans, GetQueryFilter(), Params.OverlapFunc2D, Params.Context);
	}

	vo/**
 * @brief Queries if a segment overlaps with the world's physics objects using AABB overlap test.
 * 
 * This function takes in parameters such as location and rotation of an object, along with a segment to be tested for overlap. It computes the axis-aligned bounding box (AABB) of the segment based on its position and orientation, then uses this AABB to perform an overlap test against all physics objects present in the world.
 * 
 * @param Params Contains details about the location, rotation, and segment of the object for which the overlap is being tested.
 * @return An identifier representing the result of the query (e.g., whether or not there was an overlap).
 */
id World2D::QuerySegmentOverlap(const QueryParams& Params)
	{

		Box2DQueryContext QC = { Params.Point2D,Params.InstigatorID };
		b2Transform Trans;
		Trans.p = { Params.Location.x,Params.Location.y };
		Trans.q = b2MakeRot(Params.Rotation.z);
		b2AABB SegAABB = b2ComputeSegmentAABB(&Params.Segment2D, Trans);
		b2World_OverlapAABB(m_World, SegAABB, GetQueryFilter(), Params.OverlapFunc2D, &QC);
	}

	vo/**
 * @brief Queries the world for a hit at a given point.
 *
 * This function queries the world for any objects that might be hit by a ray from the specified point in the direction of the translation vector. The result is returned through a callback function provided as an argument to this method.
 *
 * @param Params A structure containing parameters for the query, including the point at which to start the ray, the location of the end of the ray (which will be used as the translation vector), and pointers to functions that handle the result of the query.
 * 
 * @return An identifier representing the world in which the query was performed. This can be used to identify the specific world instance if there are multiple worlds running concurrently. If no such identifiers exist, this function will return an unknown value.
 */
id World2D::QueryHit(const QueryParams& Params)
	{
		Box2DQueryContext QC = { Params.Point2D, Params.InstigatorID };
		b2Vec2 Origin = { Params.Point2D.x, Params.Point2D.y };
		b2Vec2 Translation = { Params.Location.x, Params.Location.y };

		//b2WorldId worldId, const b2Circle* circle, b2Transform originTransform, b2Vec2 translation, b2QueryFilter filter, b2CastResultFcn* fcn, void* context
		b2World_CastRay(m_World, Origin, Translation, GetQueryFilter(), Params.CastFunc2D, &QC);
	}

	b2/**
 * @brief Creates a body definition for the Box2D physics engine.
 * 
 * This function creates and returns a b2BodyDef object, which is used to define properties of a rigid body in the Box2D physics engine. The parameters provided are used to set various properties of the body such as its type (dynamic, static etc.), position, rotation and whether or not the rotation should be fixed.
 * 
 * @param Type The type of the body (e.<｜begin▁of▁sentence｜>ciprt>RigidBodyType</code>). This determines how the body behaves in the physics simulation.
 * @param Translation A Vector3 specifying the initial position of the body.
 * @param Rotation A Vector3 specifying the initial rotation of the body (in radians).
 * @param IsRotationFixed A boolean indicating whether or not the rotation should be fixed. If true, the body's rotation will not change with the physics simulation.
 * @param UserData A pointer to user data that can be associated with the body. This is typically used for custom application-specific data.
 * 
 * @return b2BodyDef The newly created BodyDefinition object.
 */
BodyDef World2D::MakeBodyDefinition(const BodyType& Type, const Vector3& Translation, const Vector3 Rotation, bool IsRotationFixed, void* UserData)
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

	b2/**
 * @brief Creates a ShapeDefinition for Box2D physics engine.
 *
 * This function creates and returns a ShapeDefinition object that can be used to define the properties of a fixture in the Box2D physics engine. 
 * The returned object is initialized with default values, which are then overridden by the parameters provided.
 *
 * @param Density The density of the shape. This value will be used when calculating the mass of an object that uses this fixture definition.
 * @param Friction The friction coefficient. It controls how much the surface roughness affects the dynamic simulation.
 * @param Restitution The restitution (bounciness) factor. It determines how bouncy the shape is.
 * @param ShouldGenerateEvents A boolean flag indicating whether contact and hit events should be generated for this fixture.
 * @param UserData Pointer to user-defined data that can be associated with the fixture. This could be a pointer to an object or any other type of data.
 * 
 * @return ShapeDefinition The created ShapeDefinition object.
 */
ShapeDef World2D::MakeShapeDefinition(float Density, float Friction, float Restitution, bool ShouldGenerateEvents, void* UserData)
	{
		b2ShapeDef Fixture = b2DefaultShapeDef();
		Fixture.userData = UserData;
		Fixture.density = Density;
		//Fixture.friction = Friction;
		//Fixture.restitution = Restitution;
		Fixture.enableContactEvents = ShouldGenerateEvents;
		Fixture.enableHitEvents = ShouldGenerateEvents;

		return Fixture;
	}

	b2/**
 * @brief Creates a rotation object from an angle in radians.
 * 
 * This function takes an angle in radians and returns a Rot object, which is used to represent rotations in the Box2D physics engine.
 * The returned Rot object can be used with other functions that require a rotation parameter.
 * 
 * @param Z The angle in radians.
 * @return A Rot object representing the input angle.
 */
Rot World2D::MakeRotation(float Z)
	{
		return b2MakeRot(Z);
	}

	b2/**
 * @brief Creates a box shape for Box2D physics engine based on given dimensions and scale.
 * 
 * This function creates a box shape with the specified height in x-direction (HeightX) and y-direction (HeightY), both multiplied by the Scale factor. The resulting Polygon is then used to create a fixture for Box2D physics engine.
 * @param HeightX The half length of the box along the x-axis, before scaling.
 * @param HeightY The half length of the box along the y-axis, before scaling.
 * @param Scale A Vector3 scale factor to apply to the box dimensions.
 * @return Polygon The resulting polygon representing the box shape after applying the scale factors.
 */
Polygon World2D::CreateBox(float HeightX, float HeightY, const Vector3 Scale)
	{
		return b2MakeBox(HeightX * Scale.x, HeightY * Scale.y);
	}

	b2/**
 * @brief Creates a polygon shape for the given body.
 *
 * This function creates a new polygon shape and attaches it to the specified body. The shape is defined by its vertices in the Box parameter.
 *
 * @param ID The identifier of the body to which the shape will be attached.
 * @param Fixture A structure containing the definition of the fixture (density, restitution etc.).
 * @param Box A structure defining the polygon's vertices and edges.
 * 
 * @return ShapeId Returns a unique identifier for the newly created shape.
 */
ShapeId World2D::CreatePolygonShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Polygon& Box)
	{
		return b2CreatePolygonShape(ID, &Fixture, &Box);
	}

	b2/**
 * @brief Creates a capsule shape with the given parameters.
 * 
 * This function creates a capsule shape by setting its center points and radius based on the provided offset, scale, and radius values.
 * The centers are calculated as (Offset.x * Scale.x, Offset.y * Scale.y) for each point.
 * The radius is set to be Scale.x * Radius.
 * 
 * @param Offset The offset of the capsule from the origin.
 * @param Scale The scale factor applied to the offset.
 * @param Radius The radius of the capsule.
 * 
 * @return A b2Capsule object representing a capsule shape with the specified parameters.
 */
Capsule World2D::CreateCapsule(const Vector2& Offset, const Vector3 Scale, const float Radius)
	{
		b2Capsule Capsule;
		Capsule.center1 = { Offset.x * Scale.x, Offset.y * Scale.y };
		Capsule.center2 = { (Offset.x * Scale.x) - 1.f, (Offset.y * Scale.y) - 1.f };
		Capsule.radius = Scale.x * Radius;

		return Capsule;
	}

	b2/**
 * @brief Creates a capsule shape for the given body.
 *
 * This function creates and adds a capsule shape to the specified body with the provided fixture definition and capsule parameters. 
 * The function returns an identifier for the newly created shape, which can be used to access or modify this shape later on.
 *
 * @param ID Identifier of the body to add the shape to.
 * @param Fixture Definition of the fixture (e.<｜begin▁of▁sentence｜>cifics like density and restitution) to apply to the shape.
 * @param Capsule Parameters defining the capsule's size and orientation.
 * 
 * @return Identifier for the newly created shape.
 */
ShapeId World2D::CreateCapsuleShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Capsule& Capsule)
	{
		return b2CreateCapsuleShape(ID, &Fixture, &Capsule);
	}

	b2/**
 * @brief Creates a segment with default values.
 *
 * This function creates and returns a Segment object with its start point at (0,0) and end point at (1,0).
 *
 * @return A Segment object with default values.
 */
Segment World2D::CreateSegment()
	{
		return { {0.f, 0.f},{1.f, 0.f} };
	}

	b2/**
 * @brief Creates a segment shape in the world.
 *
 * This function creates a segment shape with given body ID, fixture definition and segment data. It returns the ShapeId of the created segment shape.
 *
 * @param[in] ID The unique identifier for the body.
 * @param[in] Fixture The fixture definition for the segment shape.
 * @param[in] Segment The segment data defining the shape of the segment shape.
 * 
 * @return ShapeId The identifier for the created segment shape.
 */
ShapeId World2D::CreateSegmentShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Segment& Segment)
	{
		return b2CreateSegmentShape(ID, &Fixture, &Segment);
	}

	b2/**
 * @brief Creates a body in the world.
 *
 * This function creates a new rigid body for simulation. A definition is passed to it specifying properties of the body such as its position, angle, linear velocity, angular velocity etc. 
 * The created body can then be added to a joint or fixture.
 *
 * @param Def Definition of the body to create. This includes parameters like type of body (static, dynamic), position, angle, linear and angular velocities etc.
 * @return A handle to the newly created body.
 */
BodyId World2D::CreateBody(b2BodyDef& Def)
	{
		return b2CreateBody(m_World, &Def);;
	}

	b2/**
 * @brief Retrieves the body associated with a given shape id.
 * 
 * This function takes in a const reference to an object of type `b2ShapeId`, which presumably represents some kind of unique identifier for a physics shape. It then returns an object of type `Body`, which is likely a class representing a physical body in the game world. The exact nature of this return value would depend on how your codebase is structured and what types these classes are.
 * 
 * @param ID A const reference to an object that represents a unique identifier for a physics shape.
 * @return An object of type `Body` representing the physical body associated with the input shape id.
 */
BodyId World2D::GetBody(const b2ShapeId& ID)
	{
		return b2Shape_GetBody(ID);
	}

	Ve/**
 * @brief Gets the position of a body in the world.
 *
 * This function retrieves the current position of a body within the 2D world. The body's ID is required to perform this operation.
 *
 * @param ID A constant reference to the b2BodyId object representing the unique identifier for the body whose position we want to retrieve.
 *
 * @return Returns a Vector2 object containing the x and y coordinates of the specified body in the world. If the provided ID does not correspond to any existing body, an undefined state is returned.
 */
ctor2 World2D::GetBodyPosition(const b2BodyId& ID)
	{
		b2Vec2 Vec = b2Body_GetPosition(ID);
		return Vector2(Vec.x, Vec.y);
	}

	b2/**
 * @brief Retrieves a polygon associated with the given shape id.
 * 
 * This function retrieves and returns the Polygon object that is linked to the provided shape ID. If no such shape exists, it will return an empty Polygon object.
 * 
 * @param ID The unique identifier of the shape for which we want to retrieve a polygon.
 * @return A Polygon object representing the shape associated with the given id. Returns an empty Polygon if no such shape exists.
 */
Polygon World2D::GetPolygon(const b2ShapeId& ID)
	{
		return b2Shape_GetPolygon(ID);
	}

	b2/**
 * @brief Retrieves a capsule shape from the world.
 * 
 * This function retrieves a capsule shape with a specific ID from the world. The ID is used to identify and retrieve the desired shape.
 * 
 * @param ID A constant reference to the b2ShapeId that represents the unique identifier of the capsule shape.
 * @return Returns the Capsule World2D object associated with the provided ID. If no such object exists, it returns an empty Capsule World2D object.
 */
Capsule World2D::GetCapsule(const b2ShapeId& ID)
	{
		return b2Shape_GetCapsule(ID);
	}

	fl/**
 * @brief Get the rotation angle of a body in degrees.
 * 
 * This function retrieves the rotation angle of a body with a given ID in degrees. It uses the Box2D physics engine's functions to get the rotation and convert it into degrees.
 * 
 * @param ID The unique identifier for the body whose rotation angle is being retrieved.
 * @return The rotation angle of the specified body, in degrees.
 */
oat World2D::GetRotationAngle(const b2BodyId& ID)
	{
		return Math::Degrees(b2Rot_GetAngle(b2Body_GetRotation(ID)));
	}

	vo/**
 * @brief Retrieves the user data associated with a specific shape id.
 * 
 * This function retrieves and returns the user data that is linked to the provided shape id. The user data is stored in the Box2D physics engine, which this World2D class interacts with. If no user data exists for the given ID, it will return nullptr.
 * 
 * @param ID A constant reference to a b2ShapeId object representing the unique identifier of the shape whose user data we want to retrieve.
 * @return Pointer to the user data associated with the provided shape id or nullptr if no such data exists.
 */
id* World2D::GetUserData(const b2ShapeId& ID)
	{
		return b2Shape_GetUserData(ID);
	}

	b2/**
 * @brief Get the world object
 * 
 * This function returns a reference to the world object. The returned object can be modified by other functions or methods.
 * 
 * @return WorldId& Reference to the world object
 */
WorldId& World2D::GetWorld()
	{
		return m_World;
	}
	Re/**
 * @brief Get the reference to the world scene object.
 * 
 * This function returns a reference to the world scene object, which is an instance of the f<Scene> class. The purpose of this function is to provide access to the internal state of the World2D class and allow other parts of the program to interact with it in a controlled manner.
 * 
 * @return A reference to the m_WorldScene object.
 */
f<Scene>& World2D::GetWorldScene()
	{
		return m_WorldScene;
	}

	template<>
	Wo/**
 * @brief This function returns a pointer to the derived class 'World2D' from the base class 'World'.
 * 
 * @return A pointer of type rld2D*, which is casted from this.
 */
rld2D* World::As()
	{
		return (World2D*)this;
	}
}