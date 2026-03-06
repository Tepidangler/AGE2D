#pragma once
#if !AG_DIST

#include <Core/Public/Layer.h>
#include <Core/Public/DeltaTime.h>

#include <imgui.h>
#include <imgui_internal.h>


namespace AGE
{
	class Panel
	{
	public:

		Panel();
		virtual ~Panel() = default;

		void OnImGuiRender([[maybe_unused]] AGE::TimeStep DeltaTime);

	};
}
 
#endif //AG_DIST