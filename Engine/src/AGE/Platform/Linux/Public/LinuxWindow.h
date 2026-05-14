//
// Created by gdmgp on 3/7/2026.
//
#ifdef AG_PLATFORM_LINUX
#ifndef AGE_LINUXWINDOW_H
#define AGE_LINUXWINDOW_H
#include "Core/Public/Window.h"
#include "Render/Public/GraphicsContext.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>


namespace AGE
{
	class LinuxWindow : public AGEWindow
	{
	public:

		LinuxWindow(const WindowProps& Props);
		virtual ~LinuxWindow();

		void OnUpdate() override;

		/**
 * @brief Returns the width of the data object.
 * @return The width of the data object as an unsigned integer.
 */
inline unsigned int GetWidth() const override { return m_Data.Width; }
		/**
 * @brief This function returns the height of an object.
 * @return The height as an unsigned integer.
 */
inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window Attributes

		/**
 * @brief This function sets the event callback for various components of the system.
 * The callback is used to notify clients about certain events that occur within the system.
 * It's set both in m_Data and m_RendererCallback, as well as in each JData object in m_JDatas.
 * 
 * @param Callback The event callback function to be set. This function should take an EventType parameter and return void.
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
 * @brief This function returns a reference to the static instance of LinuxWindow.
 * @return A reference to the static instance of LinuxWindow.
 */
static LinuxWindow& Get() { return *s_Window; }
		/**
 * @brief This function returns a pointer to the native window object.
 * @return A void pointer to the native window object, or nullptr if no such object exists.
 */
void* GetNativeWindow() const override { return m_Window; }
		/**
 * @brief This function returns the platform window associated with this object.
 * @return The X11 Window for this object.
 */
Window GetPlatformWindow() override { return m_X11Window; }
		Vector2 GetMousePos() override;

		/**
 * @brief This function returns the GraphicsContext object associated with this class instance.
 * @return A pointer to the GraphicsContext object, or nullptr if no context is available.
 */
GraphicsContext* GetGraphicsContext() override { return m_Context.get(); }

		static void JoystickCallback(int JID, int Event);

		void SwitchRenderer() override;

		void RebuildWindow() override;

		void SetWindowIcon(const std::filesystem::path& Path) override;

	private:
		virtual void Init(const WindowProps& Props);
		virtual void Shutdown();

		GLFWwindow* m_Window;

		Window m_X11Window;

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

		static LinuxWindow* s_Window;

		Scope<GraphicsContext> m_Context;

		GLFWimage m_Images[1];

	};
} // AGE

#endif //AGE_LINUXWINDOW_H
#endif //AG_PLATFORM_LINUX