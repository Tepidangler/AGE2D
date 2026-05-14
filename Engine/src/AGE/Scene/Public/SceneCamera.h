#pragma once
#include "Camera/Public/Camera.h"
#include "Math/Public/Math.h"

namespace AGE
{
	class SceneCamera : public Camera
	{
	public:

	public:

		SceneCamera();
		/**
 * @brief Virtual destructor for the SceneCamera class.
 *
 * This function is responsible for releasing any resources that were acquired by the SceneCamera object, such as memory or file handles. It does not return anything and has no parameters. 
 */
/**
 * @brief Virtual destructor for the SceneCamera class.
 *
 * This function is responsible for releasing any resources that were acquired by the SceneCamera object during its lifetime. It does not return anything and has no parameters.
 */
virtual ~SceneCamera() = default;

		void SetOrthographic(float Size, float NearClip, float FarClip);
		void SetPerspective(float VerticalFOV, float NearClip, float FarClip);

		void SetViewportSize(uint32_t Width, uint32_t Height);

		/**
 * @brief This function returns the vertical field of view for a perspective camera.
 * @return A float representing the vertical FOV in degrees.
 */
/**
 * @brief This function returns the vertical field of view for a perspective camera.
 * @return A float representing the vertical FOV in degrees.
 */
float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
		/**
 * @brief Sets the vertical field of view for the perspective projection.
 *
 * This function sets the value of the member variable `m_PerspectiveFOV` to the input parameter `VerticalFOV`, 
 * and then calls the `RecalculateProjection()` function to update the perspective matrix based on this new field of view.
 *
 * @param VerticalFOV The new vertical field of view in degrees.
 */
/**
 * @brief Sets the vertical field of view for a perspective projection.
 *
 * This function updates the private member variable `m_PerspectiveFOV` with the provided value and then calls 
 * `RecalculateProjection()` to update any associated projection matrices based on this new FOV value.
 *
 * @param VerticalFOV The new vertical field of view angle in degrees.
 */
void SetPerspectiveVerticalFOV(float VerticalFOV) { m_PerspectiveFOV = VerticalFOV; RecalculateProjection();}

		/**
 * @brief This function returns the near clipping plane of the perspective projection.
 * @return A float representing the near clipping plane value.
 */
/**
 * @brief Returns the perspective near clip plane value.
 *
 * This function returns the current value of the perspective near clip plane, which is used in rendering calculations to determine what objects are visible on the screen.
 *
 * @return The current value of the perspective near clip plane as a float.
 */
float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		/**
 * @brief Sets the perspective near clip plane value.
 *
 * This function sets the near clipping plane for a perspective projection matrix. It updates the private member variable m_PerspectiveNear with the provided NearClip parameter and then calls RecalculateProjection() to recalculate the projection matrix based on the new near clip plane value.
 *
 * @param NearClip The new near clipping plane value.
 */
/**
 * @brief Sets the perspective near clip plane value.
 *
 * This function sets the near clipping plane for a perspective projection matrix. It updates the member variable m_PerspectiveNear with the provided NearClip parameter and then calls RecalculateProjection() to recalculate the projection matrix based on the new near clip plane value.
 *
 * @param NearClip The new near clipping plane value to be set.
 */
void SetPerspectiveNearClip(float NearClip) { m_PerspectiveNear = NearClip; RecalculateProjection(); }

		/**
 * @brief This function returns the perspective far clip value.
 * @return A float representing the perspective far clip value.
 */
/**
 * @brief This function returns the perspective far clip plane value.
 * @return A float representing the perspective far clip plane value.
 */
float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		/**
 * @brief Sets the perspective far clip plane value.
 *
 * This function sets the far clip plane of the perspective projection matrix to a new value. It updates the member variable m_PerspectiveFar with the provided parameter and then calls RecalculateProjection() to recalculate the projection matrix based on the updated values.
 *
 * @param FarClip The new far clip plane value.
 */
/**
 * @brief Sets the perspective far clip plane value.
 *
 * This function sets the far clip plane of the perspective projection matrix to a new value. It updates the member variable m_PerspectiveFar with the provided parameter and then calls RecalculateProjection() to recalculate the projection matrix based on the updated values.
 *
 * @param FarClip The new far clip plane value.
 */
void SetPerspectiveFarClip(float FarClip) { m_PerspectiveFar = FarClip; RecalculateProjection(); }

		/**
 * @brief This function returns the orthographic size of the camera.
 * @return A float representing the current orthographic size.
 */
/**
 * @brief Returns the orthographic size of the camera.
 * @return A float representing the current orthographic size.
 */
float GetOrthographicSize() const { return m_OrthographicSize; }
		/**
 * @brief Sets the orthographic size for the camera.
 *
 * This function sets the orthographic size of the camera, which determines how large the visible area is in world units.
 * The aspect ratio and near/far planes are also updated to maintain the same view frustum.
 *
 * @param Size The new orthographic size for the camera. Must be greater than 0.
 */
/**
 * @brief Sets the orthographic size for the camera.
 * @param Size The new orthographic size to be set.
 * @return None
 */
void  SetOrthographicSize(float Size) { m_OrthographicSize = Size; RecalculateProjection(); }

		/**
 * @brief This function returns the near clipping plane of the camera in orthographic mode.
 * @return A float representing the near clipping plane value.
 */
/**
 * @brief Returns the near clipping plane for an orthographic camera.
 * @return The near clipping plane value as a float.
 */
float GetOrthographicNearClip() const { return m_OrthographicNear; }
		/**
 * @brief Sets the near clipping plane for an orthographic projection.
 *
 * This function sets the value of the member variable `m_OrthographicNear` to the provided parameter `NearClip`, and then calls the `RecalculateProjection()` function to update the projection matrix based on this new near clipping plane value. 
 *
 * @param NearClip The new near clipping plane value. This should be a positive number that is less than or equal to the far clipping plane value (`m_OrthographicFar`).
 */
/**
 * @brief Sets the near clip plane for an orthographic projection.
 *
 * This function sets the value of the member variable `m_OrthographicNear` to the provided parameter `NearClip`, and then calls the `RecalculateProjection()` function to update the projection matrix based on this new near clip plane value. 
 *
 * @param NearClip The new near clip plane value to be set. This should be a positive float number representing the distance from the camera to the near clipping plane in world units.
 */
void  SetOrthographicNearClip(float NearClip) { m_OrthographicNear = NearClip; RecalculateProjection(); }

		/**
 * @brief This function returns the orthographic far clip value.
 * @return A float representing the orthographic far clip value.
 */
/**
 * @brief Returns the orthographic far clip plane value.
 *
 * This function returns the current value of the orthographic far clip plane, which is used to determine how far objects are clipped in an orthographic perspective.
 *
 * @return The current value of m_OrthographicFar as a float.
 */
float GetOrthographicFarClip() const { return m_OrthographicFar; }
		/**
 * @brief Sets the far clip plane for an orthographic projection.
 *
 * This function sets the 'm_OrthographicFar' variable to the provided parameter 'FarClip'. It then calls RecalculateProjection() to update any associated projection matrices with this new value.
 * 
 * @param FarClip The new far clip plane value.
 */
/**
 * @brief Sets the far clip plane for an orthographic projection.
 *
 * This function sets the 'm_OrthographicFar' member variable to the provided parameter, and then calls the 'RecalculateProjection()' function to update the projection matrix based on this new value. 
 * The purpose of this function is to allow for dynamic adjustment of the far clip plane distance in an orthographic projection.
 *
 * @param FarClip A float representing the desired far clip plane distance.
 */
void  SetOrthographicFarClip(float FarClip) { m_OrthographicFar = FarClip; RecalculateProjection(); }

		/**
 * @brief Returns the projection type of this object.
 * @return The ProjectionType of this object, which can be either ORTHOGRAPHIC or PERSPECTIVE.
 */
/**
 * @brief Gets the projection type of this object.
 *
 * @return The ProjectionType of this object.
 */
ProjectionType GetProjectionType() const { return m_ProjectionType; }
		/**
 * @brief This function sets the projection type and adjusts the corresponding parameters accordingly.
 * 
 * @param Type The new ProjectionType to be set.
 * 
 * @return void
 */
/**
 * @brief Sets the projection type and adjusts the corresponding parameters.
 *
 * This function sets the ProjectionType to the provided value and then calls either SetPerspective or SetOrthographic, depending on the new ProjectionType.
 * The SetPerspective function is called if the ProjectionType is 0 (perspective), while the SetOrthographic function is called for any other value.
 *
 * @param Type The new ProjectionType to set.
 */
virtual void SetProjectionType(ProjectionType Type) override { m_ProjectionType = Type; if ((int)Type == 0) { SetPerspective(m_PerspectiveFOV, m_PerspectiveNear, m_PerspectiveFar); } else { SetOrthographic(m_OrthographicSize, m_OrthographicNear, m_OrthographicFar); } }

	private:

		void RecalculateProjection();

	private:
	

		float m_PerspectiveFOV = Math::Radians(45.f);
		float m_PerspectiveNear = .01f, m_PerspectiveFar = 1000.f;
		float m_OrthographicSize = 10.f;
		float m_OrthographicNear = -1.f, m_OrthographicFar = 1.f;
		
		float m_AspectRatio = 0.f;
	};
}