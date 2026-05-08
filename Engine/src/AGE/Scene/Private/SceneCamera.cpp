#include "AGEpch.hpp"
#include "Scene/Public/SceneCamera.h"
#include "Structs/Public/DataStructures.h"
#include <glm/gtc/matrix_transform.hpp>

namespace AGE
{
	/**
 * @brief Constructor for the SceneCamera class. 
 * Initializes a new instance of SceneCamera and calls RecalculateProjection to set up the projection matrix.
 */
SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}
	/**
 * @brief Sets the camera's projection to Orthographic.
 * 
 * This function sets the camera's projection type to Orthographic and updates the size, near clip, and far clip values. It then calls RecalculateProjection() to recreate the projection matrix based on these new values.
 * @param Size The desired orthographic size (width or height).
 * @param NearClip The distance from the camera to the near clipping plane.
 * @param FarClip The distance from the camera to the far clipping plane.
 */
void SceneCamera::SetOrthographic(float Size, float NearClip, float FarClip)
	{
		m_ProjectionType = ProjectionType::Orthographic;
		m_OrthographicSize = Size;
		m_OrthographicNear = NearClip;
		m_OrthographicFar = FarClip;
		RecalculateProjection();
	}
	/**
 * @brief Sets the perspective parameters of the camera.
 * 
 * This function sets the vertical field of view (FOV), near clip plane, and far clip plane for a perspective projection. It also recalculates the projection matrix based on these new values.
 * 
 * @param VerticalFOV The vertical field of view in degrees.
 * @param NearClip The distance to the near clipping plane.
 * @param FarClip The distance to the far clipping plane.
 * 
 * @return void
 */
void SceneCamera::SetPerspective(float VerticalFOV, float NearClip, float FarClip)
	{
		m_ProjectionType = ProjectionType::Perspective;
		m_PerspectiveFOV = VerticalFOV;
		m_PerspectiveNear = NearClip;
		m_PerspectiveFar = FarClip;

		RecalculateProjection();
	}
	/**
 * @brief Set the viewport size of the scene camera.
 *
 * This function sets the width and height of the viewport, calculates the aspect ratio based on these dimensions, 
 * and updates the projection matrix accordingly.
 *
 * @param Width The new width of the viewport.
 * @param Height The new height of the viewport.
 */
void SceneCamera::SetViewportSize(uint32_t Width, uint32_t Height)
	{
		m_AspectRatio = (float)Width / (float)Height;
		
		RecalculateProjection();
	}
	/**
 * @brief Recalculates the projection matrix based on the current settings.
 * 
 * This function updates the projection matrix of the camera depending on its type (perspective or orthogonal) and the current aspect ratio. It uses the glm library for creating perspective or orthographic projections.
 * 
 * @return void
 */
void SceneCamera::RecalculateProjection()
	{

		if (m_ProjectionType == ProjectionType::Perspective && m_AspectRatio > 0.f)
		{
			m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
		else
		{
			float OrthoLeft = -m_OrthographicSize * m_AspectRatio * .5f;
			float OrthoRight = m_OrthographicSize * m_AspectRatio * .5f;
			float OrthoTop = m_OrthographicSize * .5f;
			float OrthoBottom = -m_OrthographicSize * .5f;

			m_Projection = glm::ortho(OrthoLeft, OrthoRight, OrthoBottom, OrthoTop, m_OrthographicNear, m_OrthographicFar);
		}
		
	}
}