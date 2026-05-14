
#ifdef AG_PLATFORM_WINDOWS
#pragma once
#include "Core/Public/Window.h"
#include "Render/Public/GraphicsContext.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
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
 * @return The width of the data object as an unsigned integer.
 */
inline unsigned int GetWidth() const override { return m_Data.Width; }
		/**
 * @brief Returns the height of the object.
 *
 * This function returns the current height value stored in the 'm_Data' member variable.
 * It is an overridden method from the base class and hence, it provides a way to access the height data.
 * 
 * @return unsigned int The current height value of the object.
 */
inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window Attributes

		/**
 * @brief This function sets the event callback for all objects in the system.
 * The callback is used to notify clients of changes in state or other events.
 *
 * @param Callback A const reference to an EventCallbackFn object, which represents a function that takes no arguments and returns void. 
 * It's expected to be defined elsewhere in the codebase.
 *
 * @return This function does not return anything (void).
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
 * @return A reference to the static instance of WindowsWindow.
 */
static WindowsWindow& Get() { return *s_Window; }
		/**
 * @brief This function returns a pointer to the native window object.
 * @return A void pointer to the native window object, or nullptr if no such object exists.
 */
void* GetNativeWindow() const override { return m_Window; }
		/**
 * @brief This function returns the platform window handle.
 *
 * @return HWND The platform-specific window handle.
 */
HWND GetPlatformWindow() override { return m_Win32Window; }
		Vector2 GetMousePos() override;

		/**
 * @brief This function returns the Graphics Context object.
 * @return A pointer to the Graphics Context object, which is a smart pointer of type std::unique_ptr<GraphicsContext>. If no context exists, it will return nullptr.
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
		HWND m_Win32Window;
		[[maybe_unused]] GLFWgamepadstate m_PadState;

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
#endif