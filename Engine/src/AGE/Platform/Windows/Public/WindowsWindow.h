#pragma once

#include "Core/Public/Window.h"
#include "Render/Public/GraphicsContext.h"
#include <GLFW/glfw3.h>
#ifdef AG_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(AG_PLATFORM_LINUX)
#define GLFW_EXPOSE_NATIVE_X11
#elif defined(AG_PLATFORM_MACOS)
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

typedef uint16_t JoyStickID;
namespace AGE
{
	class WindowsWindow : public AGEWindow
	{
	public:

		WindowsWindow(const WindowProps& Props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		/**
 * @brief Returns the width of the data object.
 *
 * This function returns the width of the data object stored in member variable 'm_Data'. The width is a property of the data object and is not dependent on any other factors or variables.
 * 
 * @return unsigned int Width of the data object.
 */
inline unsigned int GetWidth() const override { return m_Data.Width; }
		/**
 * @brief This function returns the height of an object.
 *
 * @return An unsigned integer representing the height of the object.
 */
inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window Attributes

		/**
 * @brief This function sets the event callback for all objects in the system.
 * The callback is set both to `m_Data.EventCallback` and `m_RendererCallback`, as well as 
 * each object's `D.EventCallback` within the loop.
 *
 * @param Callback The function or lambda that will be called when an event occurs.
 */
inline void SetEventCallback(const EventCallbackFn& Callback) override 
		{
			m_Data.EventCallback = Callback; 
			m_RendererCallback = Callback;

			for (auto& D : m_JDatas)
			{
				D.EventCallback = Callback;
			}

		}
		void SetVSync(bool Enabled) override;
		bool IsVSync() const override;
		void ProcessJoystickInput();

		/**
 * @brief Returns a reference to the static instance of WindowsWindow.
 * @return Reference to the static instance of WindowsWindow.
 */
static WindowsWindow& Get() { return *s_Window; }
		/**
 * @brief This function returns a pointer to the native window object.
 * @return A void pointer to the native window, or nullptr if no such window exists.
 */
void* GetNativeWindow() const override { return m_Window; }
#ifdef AG_PLATFORM_WINDOWS
		/**
 * @brief This function returns the platform window handle.
 *
 * @return HWND The platform-specific window handle.
 */
HWND GetPlatformWindow() override { return m_Win32Window; }
#elif defined(AG_PLATFORM_LINUX)
		/**
 * @brief This function returns the platform window associated with this object.
 * @return The X11 Window for this object.
 */
Window GetPlatformWindow() override { return m_X11Window; }
#elif defined( AG_PLATFORM_MACOS)
		/**
 * @brief This function returns the platform window handle.
 *
 * @return HWND The platform-specific window handle.
 */
HWND GetPlatformWindow() override { return m_CocoasWindow; }
#endif
		Vector2 GetMousePos() override;

		/**
 * @brief This function returns the Graphics Context object.
 * @return A pointer to the Graphics Context object, which is stored in member variable 'm_Context'. If no context exists, it will return a nullptr.
 */
GraphicsContext* GetGraphicsContext() override { return m_Context.get(); }

		static void JoystickCallback(int JID, int Event);

		void SwitchRenderer() override;

		void RebuildWindow() override;

		void SetWindowIcon(const std::filesystem::path& Path) override;

	private:
		virtual void Init(const WindowProps& Props);
		virtual void Shutdown();

	private:

		GLFWwindow* m_Window;
#ifdef AG_PLATFORM_WINDOWS
		HWND m_Win32Window;
#elif defined(AG_PLATFORM_LINUX)
		Window m_X11Window;
#elif defined(AG_PLATFORM_MACOS)
		NSWindow* m_CocoaWindow;
#endif
		GLFWgamepadstate m_PadState;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			const char* String;

			EventCallbackFn EventCallback;
		};

		struct JoystickData
		{
			std::string Name;

			EventCallbackFn EventCallback;
		};

		EventCallbackFn m_RendererCallback;

		WindowData m_Data;

		std::array<JoystickData, 15> m_JDatas;

		static WindowsWindow* s_Window;

		Scope<GraphicsContext> m_Context;

		GLFWimage m_Images[1];
		
	};
}