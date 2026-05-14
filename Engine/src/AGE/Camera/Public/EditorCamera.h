#pragma once
#include "Camera/Public/Camera.h"
#include "Core/Public/DeltaTime.h"
#include "Events/Public/Event.h"
#include "Events/Public/MouseEvent.h"
#include "Structs/Public/DataStructures.h"
#include "Math/Public/Math.h"

namespace AGE
{
	class EditorCamera : public Camera
	{
	public:
		/**
 * @brief Default constructor for the EditorCamera class.
 *
 * This function initializes an instance of the EditorCamera class with default values. It does not take any parameters and returns nothing.
 */
/**
 * @brief Default constructor for the EditorCamera class.
 */
EditorCamera() = default;
		EditorCamera(float FOV, float AspectRatio, float NearClip, float FarClip);
		EditorCamera(float Size, float NearClip, float FarClip);

		void OnUpdate(TimeStep DeltaTime);
		void OnEvent(Event& E);


		/**
 * @brief This function returns the distance value.
 * @return A floating-point number representing the distance.
 */
/**
 * @brief This function returns the distance value.
 * @return A floating-point number representing the distance.
 */
inline float GetDistance() const { return m_Distance; }
		/**
 * @brief This function sets the distance value.
 * @param Distance The new distance value to be set.
 */
/**
 * @brief This function sets the distance value.
 * @param Distance The new distance value to be set.
 */
inline void SetDistance(float Distance) { m_Distance = Distance; }

		/**
 * @brief Set the viewport size and update the projection matrix.
 * 
 * This function sets the width and height of the viewport, calculates the aspect ratio from these values, and then updates the projection matrix based on these new dimensions.
 * 
 * @param Width The new width of the viewport.
 * @param Height The new height of the viewport.
 */
/**
 * @brief Set the viewport size and aspect ratio.
 * 
 * This function sets the width, height, and aspect ratio of the viewport based on the provided parameters. It also calls `UpdateProjection()` to update any projection matrices that depend on these values.
 * 
 * @param Width The new width of the viewport.
 * @param Height The new height of the viewport.
 */
inline void SetViewportSize(float Width, float Height) { m_ViewportWidth = Width; m_ViewportHeight = Height; m_AspectRatio = (Width / Height);  UpdateProjection(); }

		/**
 * @brief Returns the view matrix of the camera.
 *
 * This function returns the current view matrix used by the camera in the scene. The returned value is a Matrix4D object representing the view transformation.
 *
 * @return A Matrix4D object containing the view matrix.
 */
/**
 * @brief Returns the view matrix of the camera.
 *
 * This function returns the current view matrix used by the camera in the scene. The view matrix is a transformation matrix that defines the position and orientation of the camera in the world space.
 *
 * @return Matrix4D - The 4x4 view matrix.
 */
Matrix4D GetViewMatrix() { return m_View; }
		/**
 * @brief Returns the view matrix of the camera.
 *
 * This function returns the current view matrix of the camera, which is used to transform world space coordinates into camera space for rendering.
 *
 * @return Matrix4D The view matrix of the camera.
 */
/**
 * @brief Returns the view matrix of the camera.
 *
 * This function returns the current view matrix used by the camera in the scene. The returned matrix can be used for rendering objects from a specific point of view.
 *
 * @return Matrix4D - The 4x4 view matrix.
 */
const Matrix4D GetViewMatrix() const { return m_View; }

		/**
 * @brief This function returns the view-projection matrix of the camera.
 * @return Matrix4D The result is a 4x4 matrix that represents the combined transformation from world space to camera space.
 */
/**
 * @brief Calculates the view-projection matrix of the camera.
 *
 * This function multiplies the projection and view matrices to get the final view-projection matrix.
 * The resulting Matrix4D object represents this transformation.
 * 
 * @return A Matrix4D object representing the combined view-projection matrix.
 */
Matrix4D GetViewProjMatrix() { return m_Projection *m_View; }
		/**
 * @brief Calculates the view-projection matrix for this camera.
 *
 * This function multiplies the projection and view matrices of the camera to get the final view-projection matrix.
 * The resulting Matrix4D object represents the combined transformations of the camera.
 *
 * @return A Matrix4D object representing the combined transformation of the camera's projection and view matrices.
 */
/**
 * @brief Calculates the view-projection matrix for this camera instance.
 *
 * This function multiplies the projection and view matrices of the camera to get the final view-projection matrix.
 * The resulting Matrix4D object represents the combined transformation that takes a point in world space 
 * and transforms it into eye space (viewing coordinates) before projecting onto the screen.
 *
 * @return A Matrix4D object representing the combined projection and view matrices of this camera instance.
 */
const Matrix4D GetViewProjMatrix() const { return m_Projection *m_View; }

		Vector3 GetUpDirection() const;
		Vector3 GetRightDirection() const;
		Vector3 GetForwardDirection() const;

		/**
 * @brief Returns the current position of the object.
 * @return A constant reference to a Vector3 object representing the current position.
 */
/**
 * @brief Returns the current position of the object.
 * @return A constant reference to a Vector3 object representing the current position.
 */
const Vector3& GetPosition() const { return m_Position; }

		//Quaternion GetOrientation() const; //TODO Make Compatible with GLM

		glm::quat GetOrientation() const;

		/**
 * @brief This function returns the current pitch value.
 * @return A float representing the current pitch value. If there is an error in retrieving the value, it will return Unknown.
 */
/**
 * @brief This function returns the current pitch value.
 * @return The pitch value as a float. If no pitch is set, it will return Unknown.
 */
float GetPitch() const { return m_Pitch; }
		/**
 * @brief This function returns the yaw value of an object.
 * @return A float representing the current yaw angle in radians.
 */
/**
 * @brief This function returns the current yaw value of an object.
 * @return A float representing the current yaw value.
 */
float GetYaw() const { return m_Yaw; }

		/**
 * @brief Returns the projection type of this object.
 * @return ProjectionType - The current projection type of this object.
 */
/**
 * @brief Returns the projection type of the camera.
 * @return ProjectionType - The current projection type (ORTHOGRAPHIC, PERSPECTIVE).
 */
ProjectionType GetProjectionType() const { return m_ProjectionType; }
		/**
 * @brief Sets the projection type of the object.
 * @param Type The ProjectionType to be set.
 * @return void
 */
/**
 * @brief Sets the projection type of the object.
 *
 * This function sets the ProjectionType member variable to a given value. It allows for easy switching between different types of projections.
 *
 * @param Type The new ProjectionType to be set.
 */
void SetProjectionType(ProjectionType Type) { m_ProjectionType = Type; }


	private:

		void UpdateProjection();
		void UpdateView();

		bool OnMouseScrolled(MouseScrolledEvent& E);

		void MousePan(const Vector2& Delta);
		void MouseRotate(const Vector2& Delta);
		void MouseZoom(float Delta);

		Vector3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;

	private:
		float m_FOV = 45.f, m_AspectRatio = 1.778f, m_NearClip = .1f, m_FarClip = 1000.f;
		float m_OrthographicSize = 10.f, m_OrthographicNear = -1.f, m_OrthographicFar = 1.f;

		Matrix4D m_View{ 1.f };

		Vector3 m_Position{ 0.f,0.f,0.f };
		Vector3 m_FocalPoint{ 0.f,0.f,0.f };

		Vector2 m_InitialMousePos{ 0.f,0.f };

		ConstantBufferStruct m_ConstantBufferData;

		float m_Distance = 10.f;
		float m_Pitch = 0.f, m_Yaw = 0.f;

		float m_ViewportWidth = 1280.f, m_ViewportHeight = 720.f;
	};
}