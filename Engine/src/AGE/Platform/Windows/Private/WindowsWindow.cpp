#include "AGEpch.hpp"
#include "Utils/Public/WindowsUtils.h"
#include "Platform/Windows/Public/WindowsWindow.h"
#include "Render/Public/GraphicsContext.h"
#include "Render/Public/Renderer.h"


#include "Events/Public/ApplicationEvent.h"
#include "Events/Public/KeyEvent.h"
#include "Events/Public/MouseEvent.h"
#include "Events/Public/GameEvent.h"
#include "Events/Public/RendererEvent.h"

#include "Core/Public/JoyStickCodes.h"

#include <stb_image.h>
#include <glad/glad.h>



namespace AGE
{
	static bool s_GLFWInitialized = false;
	WindowsWindow* WindowsWindow::s_Window;

	static void GLFWErrorCallback(int Error, const char* Description)
	{
		CoreLogger::Error("GLFW Error ({0}): {1}", Error, Description);
	}

	Scope<Window> Window::Create(const WindowProps& Props)
	{
		return CreateScope<WindowsWindow>(Props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& Props)
	{
		AGE_PROFILE_FUNCTION();
		Init(Props);
		s_Window = this;
	}

	WindowsWindow::~WindowsWindow()
	{
		AGE_PROFILE_FUNCTION();
		Shutdown();
	}

	Vector2 WindowsWindow::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(m_Window,&x, &y);
		return {static_cast<float>(x),static_cast<float>(y)};
	}

	void WindowsWindow::JoystickCallback(int jid, int event)
	{

		if (event == GLFW_CONNECTED)
		{
			CoreLogger::Info("Controller {0} Connected!", jid);
			WindowsWindow::Get().m_JDatas[jid].Name = "Controller " + std::to_string(jid);
			glfwSetJoystickUserPointer(jid, &WindowsWindow::Get().m_JDatas[jid]);

		}
		else if (event == GLFW_DISCONNECTED)
		{
			CoreLogger::Info("Controller {0} Disconnected!", jid);
		}
	}

	void WindowsWindow::SwitchRenderer()
	{
		RendererChangeEvent Event(this);
		m_RendererCallback(Event);
	}

	void WindowsWindow::RebuildWindow()
	{
		Shutdown();
		m_Context.reset();
		WindowProps Props;
		Props.Title = m_Data.Title;
		Props.Width = m_Data.Width;
		Props.Height = m_Data.Height;
		Props.String = m_Data.String;
		Init(Props);
	}

	void WindowsWindow::SetWindowIcon(const std::filesystem::path& Path)
	{
		m_Images[0].pixels = stbi_load(Path.string().c_str(), &m_Images[0].width, &m_Images[0].height, 0, 4);
		glfwSetWindowIcon(m_Window, 1, m_Images);
		stbi_image_free(m_Images[0].pixels);
	}

	void WindowsWindow::Init(const WindowProps& Props)
	{
		AGE_PROFILE_FUNCTION();
		m_Data.Title = Props.Title;
		m_Data.Width = Props.Width;
		m_Data.Height = Props.Height;
		m_Data.String = Props.String;
		

		CoreLogger::Info("Creating Window {0} ({1}, {2})", Props.Title, Props.Width, Props.Height);
		

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			AGE_CORE_ASSERT(success, "Could not initialize GLFW!")

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}


		if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
		{

			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		}

		m_Window = glfwCreateWindow((int)Props.Width, (int)Props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();
		m_Win32Window = glfwGetWin32Window(m_Window);
			
		glfwSetWindowUserPointer(m_Window, &m_Data);
			
			//SetVSync(true);
		// Set GLFW callbacks

		glfwSetJoystickCallback(JoystickCallback);
		int index = 0;
		for (auto& D : m_JDatas)
		{

			glfwSetJoystickUserPointer(index, &D);
			index++;
		}

		glfwSetJoystickButtonCallback([](int JID, int Button, int Action) {
			JoystickData& Data = *(JoystickData*)glfwGetJoystickUserPointer(JID);

			switch (Action)
			{
			case GLFW_PRESS:
			{
				GamepadButtonPressedEvent Event(Button);

				Data.EventCallback(Event);
				break;
			}
			case GLFW_RELEASE:
			{
				GamepadButtonReleasedEvent Event(Button);

				Data.EventCallback(Event);
			}

			}

			});

		glfwSetJoystickAxisCallback([](int JID, int Axis, float Pos) {

			JoystickData& Data = *(JoystickData*)glfwGetJoystickUserPointer(JID);

			AxisEvent Event(Axis, Pos);
			Data.EventCallback(Event);
			});

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height)
		{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				Data.Width = Width;
				Data.Height = Height;
				FramebufferResizeEvent Event(Width,Height);
				Data.EventCallback(Event);

				
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				Data.Width = Width;
				Data.Height = Height;

				WindowResizeEvent Event(Width, Height);

				Data.EventCallback(Event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* Window)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				WindowCloseEvent Event;
				
				Data.EventCallback(Event);

			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);


					switch (Action)
					{
						case GLFW_PRESS:
						{
							KeyPressedEvent Event(Key, 0);
							Data.EventCallback(Event);
							break;
						}

						case GLFW_RELEASE:
						{
							KeyReleasedEvent Event(Key);
							Data.EventCallback(Event);
							break;
						}
						
						case GLFW_REPEAT:
						{
							KeyPressedEvent Event(Key, 1);
							Data.EventCallback(Event);
							break;
						}
						

					}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* Window, unsigned int Char)
		{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

				KeyTypedEvent Event(Char);
				Data.EventCallback(Event);
		});



		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* Window, int Button, int Action, int Mods)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

				switch (Action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent Event(Button);
						Data.EventCallback(Event);
						break;
					}

					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent Event(Button);
						Data.EventCallback(Event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* Window, double Xoffset, double Yoffset)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

				MouseScrolledEvent Event((float)Xoffset, (float)Yoffset);
				Data.EventCallback(Event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* Window, double X, double Y)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

				MouseMovedEvent Event((float)X, (float)Y);

				Data.EventCallback(Event);

			});

		
		glfwSetErrorCallback([](int Code, const char* Desc)
			{
				CoreLogger::Error("GLFW Error {0}: {1}", Code, Desc);
			});


	}

	void WindowsWindow::Shutdown()
	{
		AGE_PROFILE_FUNCTION();
		glfwSetWindowShouldClose(m_Window, true);
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		s_GLFWInitialized = false;
	

	}




	void WindowsWindow::OnUpdate()
	{
		AGE_PROFILE_FUNCTION();
		glfwPollEvents();
		//ProcessJoystickInput();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool Enabled)
	{
		AGE_PROFILE_FUNCTION();

		if (Enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.VSync = Enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
	void WindowsWindow::ProcessJoystickInput()
	{
	}
}



