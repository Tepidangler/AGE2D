#pragma once

#include "AGEpch.hpp"
#include "Core.h"
#include "Events/Public/Event.h"
#include "Render/Public/GraphicsContext.h"
#ifdef AG_PLATFORM_LINUX
#include <X11/Xlib.h>
#elif defined( AG_PLATFORM_MACOS)
#endif

namespace AGE
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		const char* String;

		/**
 * @brief Constructs a WindowProps object with default values.
 * 
 * The function initializes the properties of a window, including its title, width, height and string. If no arguments are provided, it uses default values.
 * 
 * @param T A string representing the title of the window (default: "Alcoy Game Engine Editor").
 * @param W An unsigned integer representing the width of the window in pixels (default: 1280).
 * @param H An unsigned integer representing the height of the window in pixels (default: 720).
 * @param S A C-style string representing additional information about the window (default: "").
 * 
 * @return A WindowProps object with properties set according to the provided arguments. If no arguments are provided, it uses default values.
 */
/**
 * @brief Constructs a WindowProps object with default values.
 * 
 * The constructor initializes the properties of the window, including its title, width, height and string. If no arguments are provided, it defaults to "Alcoy Game Engine Editor", 1280x720 resolution and an empty string.
 * 
 * @param T Title of the window (default: "Alcoy Game Engine Editor")
 * @param W Width of the window in pixels (default: 1280)
 * @param H Height of the window in pixels (default: 720)
 * @param S String to be displayed on the window (default: "")
 */
WindowProps(const std::string& T = "Alcoy Game Engine Editor", unsigned int W = 1280, unsigned int H = 720, const char* S = "")
			: Title(T), Width(W), Height(H), String(S)
		{

		}
	};

	//Represents a desktop system based Window

	
/**
 * @brief Virtual destructor for the AGEWindow class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime. It does not return anything and has no parameters.
 */
virtual ~AGEWindow() {}
class AGE_API AGEWindow
	{
	public:
		
		using EventCallbackFn = std::function<void(Event&)>;

		/**
 * @brief Virtual destructor for the AGEWindow class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime. It does not return anything and has no parameters.
 */
/**
 * @brief Virtual destructor for the AGEWindow class.
 *
 * This function is responsible for releasing any resources that were acquired by the AGEWindow object, such as memory or file handles. It does not return anything and thus has an empty return type (void).
 */
virtual ~AGEWindow() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Attributes
		virtual void SetEventCallback(const EventCallbackFn& Callback) = 0;

		virtual void SetVSync(bool Enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual Vector2 GetMousePos() = 0;
		virtual void* GetNativeWindow() const = 0;
#ifdef AG_PLATFORM_WINDOWS
		inline virtual HWND GetPlatformWindow() = 0;
#elif defined(AG_PLATFORM_LINUX)
		inline virtual Window GetPlatformWindow() = 0;
#elif defined(AG_PLATFORM_MACOS)
		inline virtual HWND GetPlatformWindow() = 0;
#endif

		virtual GraphicsContext* GetGraphicsContext() = 0;

		virtual void SwitchRenderer() = 0;
		virtual void RebuildWindow() = 0;

		virtual void SetWindowIcon(const std::filesystem::path& Path) =0;

		static Scope<AGEWindow> Create(const WindowProps& props = WindowProps());
	};
}