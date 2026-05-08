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
		
		/**
 * @brief Virtual destructor for the GraphicsContext class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime, such as memory or GPU handles. It does not return anything and thus has an empty return type (void).
 */
virtual ~GraphicsContext() {}
		virtual void Init() = 0;

		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(void* Window);

		template<typename T>
		T* As();
	};

}