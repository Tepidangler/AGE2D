#pragma once
#ifdef AG_PLATFORM_WINDOWS
#include "d3d11_4.h"
#endif
#include "Structs/Public/DataStructures.h"

namespace AGE
{
	class GraphicsContext
	{
	public:
		
		virtual ~GraphicsContext() {}
		virtual void Init() = 0;

		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(void* Window);

		template<typename T>
		T* As();
	};

}