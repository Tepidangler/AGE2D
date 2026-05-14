//
// Created by gdmgp on 3/7/2026.
//
#ifdef AG_PLATFORM_LINUX

#include "AGEpch.hpp"
#include "Utils/Public/WindowsUtils.h"
#include "Platform/Linux/Public/LinuxWindow.h"
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
	LinuxWindow* LinuxWindow::s_Window;

	/**
 * @brief This function is a callback for GLFW error handling. It logs the error code and description to the CoreLogger.
 * 
 * @param Error The error code provided by GLFW.
 * @param Description A string describing the error in more detail.
 */
static void GLFWErrorCallback(int Error, const char* Description)
	{
		CoreLogger::Error("GLFW Error ({0}): {1}", Error, Description);
	}

	/**
 * @brief Creates a new instance of the LinuxWindow class.
 * 
 * This function creates and returns an instance of the LinuxWindow class, initialized with the provided WindowProps object.
 * The returned Scope<AGEWindow> can be used to interact with the newly created window.
 * 
 * @param Props A reference to a constant WindowProps object containing properties for the new window.
 * @return A Scope<AGEWindow> representing the newly created LinuxWindow instance.
 */
Scope<AGEWindow> AGEWindow::Create(const WindowProps& Props)
	{
		return CreateScope<LinuxWindow>(Props);
	}

	/**
 * @brief Constructor for LinuxWindow class. Initializes the window with given properties.
 * @param Props The WindowProperties object containing details about the window.
 */
LinuxWindow::LinuxWindow(const WindowProps& Props)
	{
		AGE_PROFILE_FUNCTION();
		Init(Props);
		s_Window = this;
	}

	/** 
 * @brief Destructor for the LinuxWindow class.
 * 
 * This function is responsible for cleaning up any resources that were allocated during the lifetime of this object, such as memory or system resources. It also calls the Shutdown() function to perform necessary cleanup tasks.
 * 
 * @return void
 */
LinuxWindow::~LinuxWindow()
	{
		AGE_PROFILE_FUNCTION();
		Shutdown();
	}

	/**
 * @brief Get the current mouse position in window coordinates.
 *
 * This function retrieves the current cursor position within the LinuxWindow, 
 * which is represented as a Vector2 where x and y are floating point values.
 * The position is returned in screen coordinates with (0,0) being at the top left corner of the window.
 *
 * @return A Vector2 representing the current mouse position.
 */
Vector2 LinuxWindow::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(m_Window,&x, &y);
		return {static_cast<float>(x),static_cast<float>(y)};
	}

	/**
 * @brief Callback function for joystick events.
 *
 * This function is called whenever a joystick event occurs, such as when a controller is connected or disconnected. 
 * It logs the event and updates the name of the corresponding joystick data if necessary.
 *
 * @param jid The ID of the joystick that triggered the event.
 * @param event The type of the event (GLFW_CONNECTED or GLFW<｜begin▁of▁sentence｜>GLFW_DISCONNECTED).
 */
void LinuxWindow::JoystickCallback(int jid, int event)
	{

		if (event == GLFW_CONNECTED)
		{
			CoreLogger::Info("Controller {0} Connected!", jid);
			LinuxWindow::Get().m_JDatas[(size_t)jid].Name = "Controller " + std::to_string(jid);
			glfwSetJoystickUserPointer(jid, &LinuxWindow::Get().m_JDatas[(size_t)jid]);

		}
		else if (event == GLFW_DISCONNECTED)
		{
			CoreLogger::Info("Controller {0} Disconnected!", jid);
		}
	}

	/** 
 * @brief Switches the renderer for this Linux window.
 *
 * This function triggers a RendererChangeEvent, which is then processed by the m_RendererCallback member variable of this class.
 * The exact behavior of the callback depends on its implementation and should be documented in the code that uses it.
 * 
 * @return void
 */
void LinuxWindow::SwitchRenderer()
	{
		RendererChangeEvent Event(this);
		m_RendererCallback(Event);
	}

	/**
 * @brief Rebuilds the window by shutting down the current context, resetting it and initializing a new one with the same properties as before.
 * 
 * This function is used to update the state of the window without having to create a new instance from scratch. It's useful when you want to change some properties of the window but keep its state intact.
 */
void LinuxWindow::RebuildWindow()
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
 * @brief Set the window icon.
 *
 * This function sets the icon for the current window using a file path to an image. The image is loaded into memory and then used to set the window's icon. After this, the image data is freed from memory.
 *
 * @param Path A const reference to a std::filesystem::path object representing the location of the image file.
 */
void LinuxWindow::SetWindowIcon(const std::filesystem::path& Path)
	{
		m_Images[0].pixels = stbi_load(Path.string().c_str(), &m_Images[0].width, &m_Images[0].height, 0, 4);
		glfwSetWindowIcon(m_Window, 1, m_Images);
		stbi_image_free(m_Images[0].pixels);
	}

	/**
 * @brief Initializes a Linux Window with specified properties.
 *
 * This function sets up a new GLFW window and its context. It also sets up various callbacks for handling events such as key presses, mouse movements etc.
 * 
 * @param Props Structure containing the properties of the window to be created.
 */
void LinuxWindow::Init(const WindowProps& Props)
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
		m_X11Window = glfwGetX11Window(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

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
			default:
			{
				break;
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
						default:
						{
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
					default:
					{
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
 * @brief Shutdown the Linux window and terminate GLFW.
 * 
 * This function sets the flag for the GLFW window to close, destroys the window itself, then terminates GLFW. It also resets the static variable s_GLFWInitialized to false.
 * 
 * @return void
 */
void LinuxWindow::Shutdown()
	{
		AGE_PROFILE_FUNCTION();
		glfwSetWindowShouldClose(m_Window, true);
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		s_GLFWInitialized = false;
	}

	/** 
 * @brief This function is responsible for processing updates in the Linux window. It polls events from GLFW, processes joystick input if necessary, and then swaps buffers of the context.
 * @return void
 */
void LinuxWindow::OnUpdate()
	{
		AGE_PROFILE_FUNCTION();
		glfwPollEvents();
		//ProcessJoystickInput();
		m_Context->SwapBuffers();
	}

	/**
 * @brief This function is used to set the Vertical Synchronization (VSync) setting for a LinuxWindow object.
 * 
 * @param Enabled A boolean value indicating whether VSync should be enabled or disabled. If true, VSync will be enabled; if false, it will be disabled.
 */
void LinuxWindow::SetVSync(bool Enabled)
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
 * @brief This function is used to check the Vertical Synchronization (VSync) status of a Linux window.
 * 
 * @return True if VSync is enabled, false otherwise.
 */
bool LinuxWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
	/**
 * @brief Processes joystick input for the Linux window system.
 * 
 * This function is responsible for processing all joystick inputs from connected devices and updating the corresponding game state accordingly.
 * It does not return any value, as it directly modifies the internal game state based on the received joystick inputs.
 * 
 * @return void
 */
void LinuxWindow::ProcessJoystickInput()
	{
	}
} // AGE
#endif