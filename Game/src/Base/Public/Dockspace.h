#pragma once
#include <Age.h>

namespace Proj
{
	class Dockspace : public AGE::Layer
	{
	public:
		Dockspace() = default;
		virtual ~Dockspace() = default;

		virtual void OnImGuiRender(AGE::TimeStep DeltaTime) override;
	};
}