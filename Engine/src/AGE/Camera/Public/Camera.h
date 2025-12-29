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
		Camera() = default;
		Camera(Matrix4D Projection)
			: m_Projection(Projection) {}
		Camera(Vector4 Eye, Vector4 At, Vector4 Up) {};

		const Matrix4D& GetProjection() const { return m_Projection; }
		Matrix4D& GetProjection() { return m_Projection; }
		const Matrix4D GetWorldMatrix() const  { return m_World; }
		Matrix4D GetWorldMatrix() { return m_World; }
		const ConstantBufferStruct GetConstantBufferData() const { return m_ConstantBuffer; }
		ConstantBufferStruct GetConstantBufferData() { return m_ConstantBuffer; }
		ProjectionType GetProjectionType() const { return m_ProjectionType; }
		virtual void SetProjectionType(ProjectionType Type) { m_ProjectionType = Type; }

		virtual ~Camera() {}

	protected:

		Matrix4D m_Projection{ 1.f };
		Matrix4D m_World{ 1.f };
		ConstantBufferStruct m_ConstantBuffer;
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

	};
}