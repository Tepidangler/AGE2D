#pragma once

#include "Window.h"
#include "Render/Public/GraphicsContext.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

typedef uint16_t JoyStickID;
namespace AGE
{
	class WindowsWindow : public Window
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
		HWND GetWin32Window() override { return m_Win32Window; }
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
		HWND m_Win32Window;
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