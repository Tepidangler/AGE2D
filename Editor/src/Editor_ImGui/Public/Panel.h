#pragma once
#if !AG_DIST

#include <Core/Public/Layer.h>
#include <Core/Public/DeltaTime.h>

#include <imgui.h>
#include <imgui_internal.h>


namespace AGE
{
	class Panel : public Layer
	{
	public:

		Panel(const char* Name);
		virtual ~Panel() = default;

		virtual void OnImGuiRender(AGE::TimeStep DeltaTime) override;

	private:
		const char* m_Name;
	};
}
 
#endif //AG_DIST