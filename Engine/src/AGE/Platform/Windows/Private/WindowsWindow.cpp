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

	/**
 * @brief This function is a callback for GLFW errors. It logs the error code and description to the CoreLogger.
 * 
 * @param[in] Error The error code from GLFW.
 * @param[in] Description A string describing the error in more detail.
 */
static void GLFWErrorCallback(int Error, const char* Description)
	{
		CoreLogger::Error("GLFW Error ({0}): {1}", Error, Description);
	}

	/**
 * @brief Creates a new instance of the WindowsWindow class.
 * 
 * This function creates and returns a new instance of the WindowsWindow class, initialized with the provided properties.
 * The returned object is encapsulated in a Scope<AGEWindow> to manage its lifetime automatically.
 * 
 * @param Props - A reference to an instance of WindowProps containing the initial window properties.
 * @return A new instance of Scope<AGEWindow>, which contains the newly created WindowsWindow object.
 */
Scope<AGEWindow> AGEWindow::Create(const WindowProps& Props)
	{
		return CreateScope<WindowsWindow>(Props);
	}

	/**
 * @brief Constructor for the WindowsWindow class. Initializes a new instance of the WindowsWindow with specified properties.
 * 
 * @param Props The WindowProperties object containing information about the window, such as its title and size.
 */
WindowsWindow::WindowsWindow(const WindowProps& Props)
	{
		AGE_PROFILE_FUNCTION();
		Init(Props);
		s_Window = this;
	}

	/**
 * @brief Destructor for the WindowsWindow class.
 * 
 * This function is responsible for cleaning up any resources that were allocated during the lifetime of this object, such as memory or system resources. It also calls the Shutdown() function to perform necessary cleanup tasks.
 * 
 * @return void
 */
WindowsWindow::~WindowsWindow()
	{
		AGE_PROFILE_FUNCTION();
		Shutdown();
	}

	/**
 * @brief Get the current mouse position in window coordinates.
 *
 * This function retrieves the current cursor position within the window,
 * and returns it as a Vector2 object with x and y values representing 
 * the horizontal and vertical positions respectively. The positions are 
 * floating point numbers.
 *
 * @return A Vector2 object containing the current mouse position in 
 *         window coordinates.
 */
Vector2 WindowsWindow::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(m_Window,&x, &y);
		return {static_cast<float>(x),static_cast<float>(y)};
	}

	/**
 * @brief This function is a callback for joystick events. It gets called when a joystick is connected or disconnected.
 * @param jid The ID of the joystick that has an event.
 * @param event An integer representing the type of event (GLFW_CONNECTED or GLFW<｜begin▁of▁sentence｜>GLFW_DISCONNECTED).
 */
void WindowsWindow::JoystickCallback(int jid, int event)
	{

		if (event == GLFW_CONNECTED)
		{
			CoreLogger::Info("Controller {0} Connected!", jid);
			WindowsWindow::Get().m_JDatas[(size_t)jid].Name = "Controller " + std::to_string(jid);
			glfwSetJoystickUserPointer(jid, &WindowsWindow::Get().m_JDatas[(size_t)jid]);

		}
		else if (event == GLFW_DISCONNECTED)
		{
			CoreLogger::Info("Controller {0} Disconnected!", jid);
		}
	}

	/** 
 * @brief Switches the renderer for this window instance.
 * 
 * This function triggers a RendererChangeEvent, which is then processed by the m_RendererCallback member variable of this class. The exact behavior and effect of this event on the rendering process will depend on how the callback has been implemented elsewhere in the codebase.
 * 
 * @return void No return value.
 */
void WindowsWindow::SwitchRenderer()
	{
		RendererChangeEvent Event(this);
		m_RendererCallback(Event);
	}

	/**
 * @brief Rebuilds the window by shutting down the current context, resetting it and initializing a new one with the properties of the old window.
 * 
 * This function is used to update the state of the window without having to create a new instance. It's important to note that this function does not handle any errors or exceptions that may occur during its execution.
 * 
 * @return void
 */
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

	/**
 * @brief Sets the icon of the window.
 *
 * This function sets the icon for the window using a file path provided as an argument. It loads the image from the given path, 
 * stores it in the internal data structure and then uses glfwSetWindowIcon to set this image as the icon for the window. The loaded 
 * image is freed after use with stbi_image_free.
 *
 * @param Path A const reference to a std::filesystem::path object representing the path of the image file.
 */
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
			CoreLogger::Assert(success, "Could not initialize GLFW!");

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
#ifdef AG_PLATFORM_WINDOWS
		m_Win32Window = glfwGetWin32Window(m_Window);
#elif defined(AG_PLATFORM_LINUX)
		m_X11Window = glfwGetX11Window(m_Window);
#elif defined(AG_PLATFORM_MACOS)
		m_CocoaWindow = glfwGetCocoaWindow(m_Window);
#endif

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
				Data.Width = (uint32_t)Width;
				Data.Height = (uint32_t)Height;
				FramebufferResizeEvent Event((uint32_t)Width,(uint32_t)Height);
				Data.EventCallback(Event);

				
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				Data.Width = (uint32_t)Width;
				Data.Height = (uint32_t)Height;

				WindowResizeEvent Event((uint32_t)Width, (uint32_t)Height);

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

				KeyTypedEvent Event((int)Char);
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

	/**
 * @brief Shuts down the WindowsWindow.
 *
 * This function sets the window should close flag to true, destroys the window and terminates GLFW. It also resets the s_GLFWInitialized flag.
 * 
 * @return void
 */
void WindowsWindow::Shutdown()
	{
		AGE_PROFILE_FUNCTION();
		glfwSetWindowShouldClose(m_Window, true);
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		s_GLFWInitialized = false;
	

	}




	/** 
 * @brief This function is responsible for updating the window. It polls events, processes joystick input and swaps buffers.
 * @return void
 */
void WindowsWindow::OnUpdate()
	{
		AGE_PROFILE_FUNCTION();
		glfwPollEvents();
		//ProcessJoystickInput();
		m_Context->SwapBuffers();
	}

	/**
 * @brief This function sets the Vertical Synchronization (VSync) setting for the window.
 * 
 * @param Enabled A boolean value indicating whether to enable or disable VSync. If true, VSync is enabled; if false, it's disabled.
 * 
 * @return void
 */
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

	/**
 * @brief This function is used to check the Vertical Synchronization (VSync) status of a window.
 * 
 * @return Returns true if VSync is enabled, false otherwise.
 */
bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
	/**
 * @brief Processes joystick input for the window.
 * 
 * This function processes any incoming joystick inputs and updates the internal state of the window accordingly.
 * It does not return anything as it directly modifies the internal state of the window.
 *
 * @return None
 */
void WindowsWindow::ProcessJoystickInput()
	{
	}
}



