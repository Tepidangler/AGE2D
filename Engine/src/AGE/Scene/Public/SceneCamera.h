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
		virtual ~SceneCamera() = default;

		void SetOrthographic(float Size, float NearClip, float FarClip);
		void SetPerspective(float VerticalFOV, float NearClip, float FarClip);

		void SetViewportSize(uint32_t Width, uint32_t Height);

		float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
		void SetPerspectiveVerticalFOV(float VerticalFOV) { m_PerspectiveFOV = VerticalFOV; RecalculateProjection();}

		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		void SetPerspectiveNearClip(float NearClip) { m_PerspectiveNear = NearClip; RecalculateProjection(); }

		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		void SetPerspectiveFarClip(float FarClip) { m_PerspectiveFar = FarClip; RecalculateProjection(); }

		float GetOrthographicSize() const { return m_OrthographicSize; }
		void  SetOrthographicSize(float Size) { m_OrthographicSize = Size; RecalculateProjection(); }

		float GetOrthographicNearClip() const { return m_OrthographicNear; }
		void  SetOrthographicNearClip(float NearClip) { m_OrthographicNear = NearClip; RecalculateProjection(); }

		float GetOrthographicFarClip() const { return m_OrthographicFar; }
		void  SetOrthographicFarClip(float FarClip) { m_OrthographicFar = FarClip; RecalculateProjection(); }

		ProjectionType GetProjectionType() const { return m_ProjectionType; }
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