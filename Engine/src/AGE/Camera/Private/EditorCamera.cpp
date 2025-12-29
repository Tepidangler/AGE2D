#include "AGEpch.hpp"
#include "Camera/Public/EditorCamera.h"

#include "Core/Public/Input.h"
#include "Core/Public/Keycodes.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace AGE
{
	EditorCamera::EditorCamera(float FOV, float AspectRatio, float NearClip, float FarClip)
		:m_FOV(FOV),m_AspectRatio(AspectRatio),m_NearClip(NearClip),m_FarClip(FarClip)
	{
		UpdateView();
	}
	EditorCamera::EditorCamera(float Size, float NearClip, float FarClip)
		:m_OrthographicSize(Size),m_OrthographicNear(NearClip),m_OrthographicFar(FarClip)
	{
		m_AspectRatio = 16.f / 9.f;
		UpdateView();
	}
	void EditorCamera::OnUpdate(TimeStep DeltaTime)
	{
		if (Input::IsKeyPressed(Key::LEFT_ALT))
		{
			Vector2 Mouse{ Input::GetMouseX(), Input::GetMouseY() };
			Vector2 Delta = (Mouse - m_InitialMousePos) * .0003f;
			m_InitialMousePos = Mouse;

			if (Input::IsMouseButtonPressed(Mouse::Middle))
			{
				MousePan(Delta);
			}
			else if (Input::IsMouseButtonPressed(Mouse::Left))
			{
				MouseRotate(Delta);
			}
			else if (Input::IsMouseButtonPressed(Mouse::Right))
			{
				MouseZoom(Delta.y);
			}

			float Speed = 5.f;

			if (Input::IsKeyPressed(Key::LEFT))
			{
				m_FocalPoint.x += Speed * DeltaTime;
			}
			if (Input::IsKeyPressed(Key::RIGHT))
			{
				m_FocalPoint.x -= Speed * DeltaTime;
			}
			if (Input::IsKeyPressed(Key::UP))
			{
				m_FocalPoint.y -= Speed * DeltaTime;
			}
			if (Input::IsKeyPressed(Key::DOWN))
			{
				m_FocalPoint.y += Speed * DeltaTime;
			}
		}

		UpdateView();
	}
	void EditorCamera::OnEvent(Event& E)
	{
		EventDispatcher Dispatcher(E);
		Dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(EditorCamera::OnMouseScrolled));
	}
	Vector3 EditorCamera::GetUpDirection() const
	{
		glm::vec3 Vec = glm::rotate(GetOrientation(), Convert::ToGLM(Vector3(0.f,1.f,0.f)));
		return {Vec.x,Vec.y,Vec.z};
	}
	Vector3 EditorCamera::GetRightDirection() const
	{
		glm::vec3 Vec = glm::rotate(GetOrientation(), Convert::ToGLM(Vector3(1.f, 0.f, 0.f)));
		return { Vec.x,Vec.y,Vec.z };
	}
	Vector3 EditorCamera::GetForwardDirection() const
	{
		glm::vec3 Vec = glm::rotate(GetOrientation(), Convert::ToGLM(Vector3(0.f, 0.f, -1.f)));
		return { Vec.x,Vec.y,Vec.z };
	}
	glm::quat EditorCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch,-m_Yaw,0.f));
	}
	void EditorCamera::UpdateProjection()
	{
		if (m_ProjectionType == ProjectionType::Perspective && m_AspectRatio > 0.f)
		{
			m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
			m_ConstantBufferData.Projection = m_Projection = glm::perspective(Math::Radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
		}
		else
		{
			float OrthoLeft = -m_OrthographicSize * m_AspectRatio * .5f;
			float OrthoRight = m_OrthographicSize * m_AspectRatio * .5f;
			float OrthoTop = m_OrthographicSize * .5f;
			float OrthoBottom = -m_OrthographicSize * .5f;

			m_ConstantBufferData.Projection = m_Projection = glm::ortho(OrthoLeft, OrthoRight, OrthoBottom, OrthoTop, m_OrthographicNear, m_OrthographicFar);
		}

	}
	void EditorCamera::UpdateView()
	{
		if (m_ProjectionType == ProjectionType::Perspective)
		{
			m_Position = CalculatePosition();
		
			glm::quat Orientation = GetOrientation();
			m_View = glm::translate(Matrix4D(1.f).ToGLM(), Convert::ToGLM(m_Position)) * glm::toMat4(Orientation);
			m_ConstantBufferData.View = m_View = glm::inverse(m_View.ToGLM());
		}
		else
		{
			m_Position = CalculatePosition();
		
			m_View = glm::translate(Matrix4D(1.f).ToGLM(), Convert::ToGLM(m_Position));
			m_ConstantBufferData.View =  m_View = glm::inverse(m_View.ToGLM());
		}
	
	}
	bool EditorCamera::OnMouseScrolled(MouseScrolledEvent& E)
	{
		float Delta = E.GetYOffset() * .1f;
		MouseZoom(Delta);
		UpdateView();
		return false;
	}
	void EditorCamera::MousePan(const Vector2& Delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		 glm::vec3 Vec = glm::vec3((- 1.f * GetRightDirection().x), (-1.f * GetRightDirection().y), (-1.f * GetRightDirection().z)) * Delta.x * xSpeed * m_Distance;
		 m_FocalPoint += Vector3(Vec.x, Vec.y, Vec.z);
		 m_FocalPoint += GetRightDirection() * Delta.y * ySpeed * m_Distance;
	}
	void EditorCamera::MouseRotate(const Vector2& Delta)
	{
		float YawSign = GetUpDirection().y < 0 ? -1.f : 1.f;
		m_Yaw += YawSign * Delta.x * RotationSpeed();
		m_Pitch += Delta.y * RotationSpeed();
	}
	void EditorCamera::MouseZoom(float Delta)
	{
		m_Distance -= Delta * ZoomSpeed();
		if (m_Distance < 1.f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.f;
		}
	}
	Vector3 EditorCamera::CalculatePosition() const
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}
	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.f, 2.4f); // max  = 2.4f
		float xFactor = .366f * (x * x) - .1778f * x + .3021f;

		float y = std::min(m_ViewportHeight / 1000.f, 2.4f); // max = 2.4f
		float yFactor = .366f * (y * y) - .1778f * y + .3021f;

		return { xFactor,yFactor };
	}
	float EditorCamera::RotationSpeed() const
	{
		return 0.8f;
	}
	float EditorCamera::ZoomSpeed() const
	{
		float Distance = m_Distance * .2f;
		Distance = std::max(Distance, 0.f);
		float Speed = Distance * Distance;
		Speed = std::min(Speed, 100.f);
		return Speed;
	}
}