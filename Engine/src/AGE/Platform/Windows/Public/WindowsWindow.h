#pragma once

#include "Core/Public/Window.h"
#include "Render/Public/GraphicsContext.h"
#include <GLFW/glfw3.h>
#ifdef AG_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elifdef AG_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elifdef AG_PLATFORM_MACOS
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

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window Attributes

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

		static WindowsWindow& Get() { return *s_Window; }
		void* GetNativeWindow() const override { return m_Window; }
#ifdef AG_PLATFORM_WINDOWS
		HWND GetPlatformWindow() override { return m_Win32Window; }
#elifdef AG_PLATFORM_LINUX
		Window GetPlatformWindow() override { return m_X11Window; }
#elifdef AG_PLATFORM_MACOS
		HWND GetPlatformWindow() override { return m_CocoasWindow; }
#endif
		Vector2 GetMousePos() override;

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
#elifdef AG_PLATFORM_LINUX
		Window m_X11Window;
#elifdef AG_PLATFORM_MACOS
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