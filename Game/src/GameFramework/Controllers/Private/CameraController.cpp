#include <Core/Public/AGEpch.hpp>
#include "Controllers/Public/CameraController.h"

namespace GameFramework
{
	void CameraController::OnCreate()
	{
		//auto& Trans = GetComponent<TransformComponent>().Translation;
		//Trans.x = rand() % 10 - 5.f;
	}
	void CameraController::OnDestroy()
	{
	}
	void CameraController::OnUpdate(AGE::TimeStep DeltaTime)
	{
		auto& Trans = GetComponent<AGE::TransformComponent>().Translation;

		float Speed = 5.f;

		if (AGE::Input::IsKeyPressed(AGE::Key::A))
		{
			Trans.x += Speed * DeltaTime;
		}
		if (AGE::Input::IsKeyPressed(AGE::Key::D))
		{
			Trans.x-= Speed * DeltaTime;
		}
		if (AGE::Input::IsKeyPressed(AGE::Key::W))
		{
			Trans.y -= Speed * DeltaTime;
		}
		if (AGE::Input::IsKeyPressed(AGE::Key::S))
		{
			Trans.y += Speed * DeltaTime;
		}
	}
}