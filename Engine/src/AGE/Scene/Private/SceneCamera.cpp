#include "AGEpch.hpp"
#include "Scene/Public/SceneCamera.h"
#include "Structs/Public/DataStructures.h"
#include <glm/gtc/matrix_transform.hpp>

namespace AGE
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}
	void SceneCamera::SetOrthographic(float Size, float NearClip, float FarClip)
	{
		m_ProjectionType = ProjectionType::Orthographic;
		m_OrthographicSize = Size;
		m_OrthographicNear = NearClip;
		m_OrthographicFar = FarClip;
		RecalculateProjection();
	}
	void SceneCamera::SetPerspective(float VerticalFOV, float NearClip, float FarClip)
	{
		m_ProjectionType = ProjectionType::Perspective;
		m_PerspectiveFOV = VerticalFOV;
		m_PerspectiveNear = NearClip;
		m_PerspectiveFar = FarClip;

		RecalculateProjection();
	}
	void SceneCamera::SetViewportSize(uint32_t Width, uint32_t Height)
	{
		m_AspectRatio = (float)Width / (float)Height;
		
		RecalculateProjection();
	}
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