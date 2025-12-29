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
		EditorCamera() = default;
		EditorCamera(float FOV, float AspectRatio, float NearClip, float FarClip);
		EditorCamera(float Size, float NearClip, float FarClip);

		void OnUpdate(TimeStep DeltaTime);
		void OnEvent(Event& E);


		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float Distance) { m_Distance = Distance; }

		inline void SetViewportSize(float Width, float Height) { m_ViewportWidth = Width; m_ViewportHeight = Height; m_AspectRatio = (Width / Height);  UpdateProjection(); }

		Matrix4D GetViewMatrix() { return m_View; }
		const Matrix4D GetViewMatrix() const { return m_View; }

		Matrix4D GetViewProjMatrix() { return m_Projection *m_View; }
		const Matrix4D GetViewProjMatrix() const { return m_Projection *m_View; }

		Vector3 GetUpDirection() const;
		Vector3 GetRightDirection() const;
		Vector3 GetForwardDirection() const;

		const Vector3& GetPosition() const { return m_Position; }

		//Quaternion GetOrientation() const; //TODO Make Compatible with GLM

		glm::quat GetOrientation() const;

		float GetPitch() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }

		ProjectionType GetProjectionType() const { return m_ProjectionType; }
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