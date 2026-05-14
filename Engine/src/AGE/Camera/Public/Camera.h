#pragma once

#include <glm/glm.hpp>
#include "Core/Public/DeltaTime.h"
#include "Math/Public/MathStructures.h"
#include "Math/Public/UtilityFunctions.h"
#include "Render/Public/GraphicsContext.h"


namespace AGE
{
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	class Camera
	{

	public:
		/**
 * @brief Default constructor for the Camera class.
 *
 * This function initializes a new instance of the Camera class with default values.
 * It does not take any parameters and returns nothing.
 */
COMMENT:
/**
 * @brief Default constructor for the Camera class.
 *
 * This function initializes a new instance of the Camera class with default values.
 * It does not take any parameters and returns no value.
 */
CONFIDENCE: 1.0;

Camera() = default;
		COMMENT:
/**
 * @brief Constructs a Camera object with the specified projection matrix.
 * @param[in] Projection The projection matrix to be used for this camera.
 */
CONFIDENCE: 1.0;

COMMENT:
/**
 * @brief Constructs a Camera object with the given projection matrix.
 * @param Projection The projection matrix to be used for this camera.
 */
CONFIDENCE: 1.0;

Camera(Matrix4D Projection)
			: m_Projection(Projection) {}
		/**
 * @brief Constructor for the Camera class that initializes a camera with an eye position, at position and up direction.
 * @param Eye The eye position of the camera as a Vector4 object.
 * @param At The at position of the camera as a Vector4 object. This is usually the point in 3D space that the camera is looking at.
 * @param Up The up direction of the camera as a Vector4 object. This defines the orientation of the camera.
 */
/**
 * @brief Constructor for the Camera class.
 * @param Eye A Vector4 representing the eye position in world space coordinates.
 * @param At A Vector4 representing the point at which to look in world space coordinates.
 * @param Up A Vector4 representing the up direction in world space coordinates.
 */
Camera(Vector4 Eye, Vector4 At, Vector4 Up) {};

		/**
 * @brief Returns the projection matrix used for rendering.
 * @return A constant reference to the projection matrix (m_Projection).
 */
/**
 * @brief Returns the projection matrix used for rendering.
 * @return A constant reference to the projection matrix (m_Projection).
 */
const Matrix4D& GetProjection() const { return m_Projection; }
		/**
 * @brief Returns the projection matrix of the camera.
 *
 * This function returns a reference to the projection matrix used by the camera for rendering. The returned object can be modified directly, which will affect all subsequent calls to this method and any other methods that use the same projection matrix.
 *
 * @return A reference to the projection matrix.
 */
/**
 * @brief Returns the projection matrix of the camera.
 * @return A reference to the projection matrix (m_Projection).
 */
Matrix4D& GetProjection() { return m_Projection; }
		/**
 * @brief Returns the world matrix of the object.
 *
 * This function returns the current world transformation matrix of the object. It is used to transform the object's vertices from local space to world space.
 *
 * @return The 4x4 world matrix as a Matrix4D object.
 */
/**
 * @brief Returns the world matrix of the object.
 *
 * This function returns the current world matrix of the object, which is used for transformations and other calculations in the scene.
 *
 * @return Matrix4D The current world matrix of the object.
 */
const Matrix4D GetWorldMatrix() const  { return m_World; }
		/**
 * @brief Returns the world matrix of the object.
 *
 * This function returns the current world matrix of the object, which is used for transformations and other calculations in the scene.
 *
 * @return Matrix4D The current world matrix of the object.
 */
/**
 * @brief Returns the world matrix of the object.
 *
 * This function returns the current world matrix of the object, which is used for transformations and other calculations in the scene.
 *
 * @return Matrix4D The current world matrix of the object.
 */
Matrix4D GetWorldMatrix() { return m_World; }
		/**
 * @brief This function returns the constant buffer data.
 * @return A struct of type ConstantBufferStruct containing the constant buffer data.
 */
/**
 * @brief Retrieves the constant buffer data.
 *
 * This function returns a copy of the constant buffer data stored in the object. The returned data is a struct that contains all the necessary information for rendering.
 *
 * @return A ConstantBufferStruct containing the constant buffer data.
 */
const ConstantBufferStruct GetConstantBufferData() const { return m_ConstantBuffer; }
		/**
 * @brief This function returns the constant buffer data.
 * @return ConstantBufferStruct object containing the constant buffer data.
 */
/**
 * @brief This function returns the constant buffer data.
 * @return ConstantBufferStruct object containing the constant buffer data.
 */
ConstantBufferStruct GetConstantBufferData() { return m_ConstantBuffer; }
		/**
 * @brief Returns the projection type of this object.
 * @return The ProjectionType of this object. Possible values are defined in an enumeration.
 */
/**
 * @brief Returns the projection type of the camera.
 * @return ProjectionType - The current projection type (ORTHOGRAPHIC, PERSPECTIVE).
 */
ProjectionType GetProjectionType() const { return m_ProjectionType; }
		/**
 * @brief Sets the projection type of the object.
 * @param Type The ProjectionType to be set.
 * @return None
 */
/**
 * @brief Sets the projection type of the object.
 * @param Type The ProjectionType to be set.
 */
virtual void SetProjectionType(ProjectionType Type) { m_ProjectionType = Type; }

		/**
 * @brief Virtual destructor for the Camera class.
 *
 * This function is a virtual destructor that cleans up any resources used by an instance of the Camera class. It does not take any parameters and returns nothing.
 */
/**
 * @brief Virtual destructor for the Camera class.
 *
 * This function is a virtual destructor that cleans up any resources used by an instance of the Camera class. It does not take any parameters and returns no value.
 */
virtual ~Camera() {}

	protected:

		Matrix4D m_Projection{ 1.f };
		Matrix4D m_World{ 1.f };
		ConstantBufferStruct m_ConstantBuffer;
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

	};
}