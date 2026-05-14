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
 * This function takes in a `BodyType` and converts it into the corresponding 
 * `b2BodyType` from Box2D physics engine. The conversion is done based on the 
 * following rules:
 * - `BodyType::Static` corresponds to `b2_staticBody`,
 * - `BodyType::Dynamic` corresponds to `b2_dynamicBody`, and
 * - `BodyType::Kinematic` corresponds to `b2_kinematicBody`.
 * 
 * If the input is not one of these three types (which should be impossible), an 
 * assertion will fail with a message "Unknown Body Type". The function then 
 * returns `b2_staticBody` as a default fallback option.
 *
 * @param BodyType The type to convert from Rigid body type to Box2D's body type.
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
 * @brief Constructs a new instance of World2D with the given scene.
 * @param scene The Scene to be associated with this World2D object.
 * 
 * This constructor initializes the b2World object, setting its gravity to {0.0f,-9.8f} and associating it with the provided scene.
 */
rld2D::World2D(Ref<Scene> scene)
		:m_WorldScene(scene)
	{
		CoreLogger::Trace("Initializing World {}", scene->GetName());
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
 * This function is used to destroy the Box2D world object, which was previously created using World2D::CreateWorld(). It calls b2DestroyWorld() on the m_World member variable of the class instance.
 *
 * @return void
 */
id World2D::DestroyWorld()
	{
		b2DestroyWorld(m_World);
	}

	vo/**
 * @brief Performs a single step of the simulation.
 * 
 * This function performs one step in the simulation by advancing all bodies and joints
 * in the world according to the specified time step. The number of substeps used is fixed at 4.
 *
 * @param DeltaTime The duration of the time step.
 * @return void
 */
id World2D::Step(TimeStep DeltaTime)
	{
		const int32_t SubStepCount = 4;

		b2World_Step(m_World, DeltaTime, SubStepCount);
	}

	vo/**
 * @brief Sets the query filter to its default state.
 *
 * This function resets the internal query filter of the World2D object back to its initial, default state. The m_QueryFilter member variable is set using b2DefaultQueryFilter(), which presumably returns a default query filter for Box2D physics engine. 
 *
 * @return void
 */
id World2D::MakeDefaultQueryFilter()
	{
		m_QueryFilter = b2DefaultQueryFilter(); 
	}

	vo"This function queries for overlaps within a 2D world using Box2D. It takes as input a QueryParams struct containing all necessary parameters for the overlap query."
id World2D::QueryBoxOverlap(const QueryParams& Params)
	{
		[[maybe_unused]] Box2DQueryContext QC = { Params.Point2D,Params.InstigatorID };
		b2ShapeProxy Proxy{};
		Proxy.count = Params.Box2D.count;
		for (size_t i = 0; i < 4; i++)
		{
			Proxy.points[i] = Params.Box2D.vertices[i];
		}
		b2Transform Trans;
		Trans.p = { Params.Location.x,Params.Location.y };
		Trans.q = b2MakeRot(Params.Rotation.z);
		b2World_OverlapShape(m_World, &Proxy,GetQueryFilter(),Params.OverlapFunc2D, Params.Context);
	}

	vo
id World2D::QueryCapsuleOverlap(const QueryParams& Params)
	{
		[[maybe_unused]] Box2DQueryContext QC = { Params.Point2D,Params.InstigatorID };
		b2ShapeProxy Proxy{};
		Proxy.count = 2;
		Proxy.points[0] = Params.Capsule2D.center1;
		Proxy.points[1] = Params.Capsule2D.center2;
		Proxy.radius = Params.Box2D.radius;
		b2Transform Trans;
		Trans.p = { Params.Location.x,Params.Location.y };
		Trans.q = b2MakeRot(Params.Rotation.z);
		b2World_OverlapShape(m_World, &Proxy,GetQueryFilter(),Params.OverlapFunc2D, Params.Context);
	}

	vo"Unknown"
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
 * @brief This function is used to perform a ray-casting operation in the 2D world.
 * It takes as input a QueryParams object that contains information about the point of origin and the location where the ray should be casted, as well as other parameters for the query.
 * The function returns an id representing the result of the hit query.
 * @param Params An instance of QueryParams containing all necessary data for the operation.
 * @return A unique identifier (id) representing the result of the hit query.
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
 * This function creates and returns a b2BodyDef object, which is used to define properties of a rigid body in the Box2D physics engine.
 * The returned BodyDef has its userData set to the provided UserData pointer, its type set based on the given Type parameter, its position set to Translation, 
 * and its rotation set to Rotation. It also sets the fixedRotation flag according to IsRotationFixed.
 * 
 * @param Type The type of body to be created. This is used to determine how the body behaves in the physics simulation.
 * @param Translation A Vector3 specifying the initial position of the body.
 * @param Rotation A Vector3 specifying the initial rotation of the body, in radians.
 * @param IsRotationFixed A boolean indicating whether the body's rotation should be fixed or not.
 * @param UserData A void pointer to user data that can be associated with the body. This is typically used for game-specific data.
 * 
 * @return The created b2BodyDef object, ready to be passed to a Box2D physics engine function to create a new rigid body.
 */
BodyDef World2D::MakeBodyDefinition(const BodyType& Type, const Vector3& Translation, const Vector3& Rotation, bool IsRotationFixed, void* UserData)
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
 * @brief Creates a ShapeDefinition for use in Box2D physics engine.
 * 
 * This function creates and returns a ShapeDefinition object that can be used to define the properties of a fixture in the Box2D physics engine. The returned object is initialized with default values, which are then overridden by the parameters provided.
 * 
 * @param Density The density of the shape. This value will determine how much mass the shape has.
 * @param Friction A coefficient that determines how much the surface roughness affects the friction between this fixture and another.
 * @param Restitution A factor determining the bounciness of the object when it hits something.
 * @param ShouldGenerateEvents Determines whether contact events should be generated for this shape.
 * @param UserData Pointer to user data that can be associated with this fixture. This is typically used to store custom data about the fixture.
 * 
 * @return A ShapeDefinition object initialized with the provided parameters.
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
 * This function takes an angle in radians as input and returns a Rotation object representing that angle. The returned Rotation object can be used for various 2D transformations.
 * 
 * @param Z The angle in radians to convert into a rotation object.
 * @return A Rotation object representing the input angle.
 */
Rot World2D::MakeRotation(float Z)
	{
		return b2MakeRot(Z);
	}

	b2/**
 * @brief Creates a box polygon with given dimensions and scale.
 *
 * This function creates a box polygon with the specified height in x-direction (HeightX), y-direction (HeightY) 
 * and the provided scale factor for both directions. The resulting Polygon is then returned by the function.
 *
 * @param HeightX The half width of the box, scaled by Scale.x.
 * @param HeightY The half height of the box, scaled by Scale.y.
 * @param Scale A scaling factor for both directions.
 * 
 * @return Polygon The resulting polygon after applying the scale factors to the dimensions.
 */
Polygon World2D::CreateBox(float HeightX, float HeightY, const Vector3& Scale)
	{
		return b2MakeBox(HeightX * Scale.x, HeightY * Scale.y);
	}

	b2/**
 * @brief Creates a polygon shape for the given body.
 *
 * This function creates a polygon shape with the specified definition and box for the body identified by ID. The fixture and box parameters are used to define the properties of the new shape.
 *
 * @param ID The identifier of the body for which the shape is being created.
 * @param Fixture A reference to the fixture definition that will be applied to the new shape.
 * @param Box A reference to the polygon box that defines the vertices of the new shape.
 * 
 * @return Returns a ShapeId representing the newly created shape.
 */
ShapeId World2D::CreatePolygonShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Polygon& Box)
	{
		return b2CreatePolygonShape(ID, &Fixture, &Box);
	}

	b2/**
 * @brief Creates a capsule shape with the given parameters.
 * 
 * This function creates a capsule shape by setting its center points and radius based on the provided offset, scale, and radius values.
 * The centers are calculated as (Offset.x * Scale.x, Offset.y * Scale.y) for both ends of the capsule.
 * 
 * @param Offset The offset to use when calculating the center points.
 * @param Scale The scale to use when calculating the center points and radius.
 * @param Radius The radius of the capsule.
 * 
 * @return A b2Capsule object representing a capsule shape with the specified parameters.
 */
Capsule World2D::CreateCapsule(const Vector2& Offset, const Vector3& Scale, const float Radius)
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
 * The function returns an identifier for the newly created shape, which can be used to manipulate or query this shape later on.
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
 * @brief Creates a new segment with default values.
 * 
 * This function creates and returns a Segment object with its start point at (0,0) and end point at (1,0).
 * The Segment is initialized in the world coordinate system.
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
 * This function creates a new segment shape within the physics engine and associates it with a body. The segment is defined by two points, forming a line segment.
 * 
 * @param ID The identifier of the body to which the segment shape should be associated.
 * @param Fixture A structure defining the properties of the segment shape.
 * @param Segment A structure specifying the endpoints of the segment.
 * 
 * @return Returns a unique identifier for the newly created segment shape.
 */
ShapeId World2D::CreateSegmentShape(const b2BodyId& ID, const b2ShapeDef& Fixture, const b2Segment& Segment)
	{
		return b2CreateSegmentShape(ID, &Fixture, &Segment);
	}

	b2/**
 * @brief Creates a body in the world.
 *
 * This function creates a new rigid body for simulation. A definition is passed to it specifying properties of the body such as its position, angle, linear velocity, angular velocity etc.
 * 
 * @param Def The definition of the body to be created.
 * @return BodyId Identifier for the newly created body.
 */
BodyId World2D::CreateBody(b2BodyDef& Def)
	{
		return b2CreateBody(m_World, &Def);;
	}

	b2/**
 * @brief Retrieves the body associated with a given shape id.
 * 
 * This function takes in a const reference to an object of type `b2ShapeId`, which represents the unique identifier for a physics shape. It then returns the corresponding `BodyId` representing the body that owns this shape.
 * 
 * @param ID A constant reference to the shape id.
 * @return The body associated with the given shape id. If no such body exists, an unknown value is returned.
 */
BodyId World2D::GetBody(const b2ShapeId& ID)
	{
		return b2Shape_GetBody(ID);
	}

	Ve/**
 * @brief Gets the position of a body in the world.
 *
 * This function retrieves the current position of a body within the 2D world using its unique ID.
 * The returned value is a Vector2 representing the x and y coordinates of the body's position.
 *
 * @param ID Unique identifier for the body whose position we want to retrieve.
 * @return A Vector2 containing the x and y coordinates of the specified body's position.
 */
ctor2 World2D::GetBodyPosition(const b2BodyId& ID)
	{
		b2Vec2 Vec = b2Body_GetPosition(ID);
		return Vector2(Vec.x, Vec.y);
	}

	b2/** 
 * @brief Retrieves a polygon associated with the given shape id.
 * 
 * This function takes an argument of type `b2ShapeId` and returns a Polygon object. It uses the `b2Shape_GetPolygon()` function to get the polygon based on the provided ID.
 * The returned value is expected to be used for rendering or other geometric operations in the 2D World.
 * 
 * @param ID A constant reference to an instance of `b2ShapeId`, which represents a unique identifier for a shape.
 * @return Polygon object representing the polygon associated with the provided shape id.
 */
Polygon World2D::GetPolygon(const b2ShapeId& ID)
	{
		return b2Shape_GetPolygon(ID);
	}

	b2/** 
 * @brief Retrieves a capsule from the world using its shape id.
 * 
 * This function is used to retrieve a capsule object from the world by providing the unique ID of the capsule's shape.
 * The function uses the b2Shape_GetCapsule() method to get the capsule with the given ID.
 *
 * @param[in] ID Unique identifier for the capsule shape in the World2D object.
 * @return A Capsule object corresponding to the provided shape id.
 */
Capsule World2D::GetCapsule(const b2ShapeId& ID)
	{
		return b2Shape_GetCapsule(ID);
	}

	fl/**
 * @brief Get the rotation angle of a body in degrees.
 * 
 * This function retrieves the rotation angle of a body with a given ID, converting it from radians to degrees using Math::Degrees().
 * The b2Rot_GetAngle() and b2Body_GetRotation() functions are used for this purpose.
 *
 * @param ID Unique identifier for the body whose rotation angle is being retrieved.
 * 
 * @return The rotation angle of the specified body in degrees.
 */
oat World2D::GetRotationAngle(const b2BodyId& ID)
	{
		return Math::Degrees(b2Rot_GetAngle(b2Body_GetRotation(ID)));
	}

	vo/**
 * @brief Retrieves the user data associated with a specific shape id.
 * 
 * This function retrieves the user data that was previously set using World2D::SetUserData() for a given b2ShapeId.
 * The returned pointer can be used to access any custom data associated with this shape.
 * 
 * @param ID The unique identifier of the shape whose user data is being retrieved.
 * @return Pointer to the user data, or nullptr if no user data was set for the given shape id.
 */
id* World2D::GetUserData(const b2ShapeId& ID)
	{
		return b2Shape_GetUserData(ID);
	}

	b2/**
 * @brief Returns a reference to the world object.
 * 
 * This function returns a reference to the world object that is currently being used by the World2D class. The returned reference can be used to modify or access the properties of this world object.
 * 
 * @return A reference to the current world object.
 */
WorldId& World2D::GetWorld()
	{
		return m_World;
	}
	Re/**
 * @brief Get the reference to the world scene object.
 * 
 * This function returns a reference to the world scene object, which is an instance of the Scene class. The purpose of this function is to provide access to the current state of the world scene for other parts of the program that need it.
 * 
 * @return f<Scene>& A reference to the world scene object.
 */
f<Scene>& World2D::GetWorldScene()
	{
		return m_WorldScene;
	}

	template<>
	Wo/**
 * @brief This function returns a pointer to the derived class 'World2D' from the base class 'World'.
 * It is used for polymorphism and dynamic binding. The returned object can be treated as an instance of World2D.
 * 
 * @return A pointer to the derived class 'World2D'.
 */
rld2D* World::As()
	{
		return (World2D*)this;
	}
}