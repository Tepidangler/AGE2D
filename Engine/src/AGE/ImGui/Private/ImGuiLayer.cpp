#include "AGEpch.hpp"
#include "ImGui/Public/ImGuiLayer.h"
#include "Utils/Public/WindowsUtils.h"

#include <imgui.h>
#include <ImGuizmo.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>
#include "Core/Public/App.h"
#include "Events/Public/KeyEvent.h"
#include "Events/Public/MouseEvent.h"
#include "Platform/OpenGL/Public/OpenGlContext.h"

// Temp
#include <GLFW/glfw3.h>
namespace AGE
{
    /**
 * @brief ImGuiLayer is a class representing the layer for handling user interface elements with ImGui library in our application.
 */
/**
 * @brief ImGuiLayer is a class representing the layer for handling user interface elements with ImGui library in our application. 
 * It extends the base Layer class and provides additional functionality specific to this library.
 */
ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {

    }

    /**
 * @brief Destructor for the ImGuiLayer class.
 */
/**
 * @brief Destructor for the ImGuiLayer class.
 */
ImGuiLayer::~ImGuiLayer()
    {
    }

    

void ImGuiLayer::OnAttach()
    {
        AppConfig Config = App::Get().GetAppConfig();
        AGE_PROFILE_FUNCTION();
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        std::string Path = Config.EditorAssetPath.string() + "Fonts/IBM_Plex_Sans/IBMPlexSans-Bold.ttf";
        io.Fonts->AddFontFromFileTTF(Path.c_str(), 18.f);
        io.FontDefault = io.Fonts->AddFontFromFileTTF(Path.c_str(), 18.f);

        // Setup Dear ImGui style
        //ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();
        SetDarkThemeColors();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        App& app = App::Get();

       m_Context = app.GetDeviceManager().GetWindow().GetGraphicsContext();
       m_CurrentGraphicsAPI = Renderer::GetAPI();

        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetDeviceManager().GetWindow().GetNativeWindow());

        // Setup Platform/Renderer backends
 

        switch (Renderer::GetAPI())
        {
            case 0:
            {
                break;
            }
            case 1:
            {
                ImGui_ImplGlfw_InitForOpenGL(window, true);
                ImGui_ImplOpenGL3_Init("#version 450");
                break;
            }
            default:
            {
                CoreLogger::Assert(false, "Invalid Render API Selected!");
                break;
            }
        }
    }
    /**
 * @brief This function is called when the ImGuiLayer detaches from its attached renderer.
 * It handles cleanup based on which rendering API was selected at runtime.
 * 
 * @return void
 */
/**
 * @brief Detaches the ImGui layer.
 * 
 * This function is responsible for detaching the ImGui layer from the application. It does this by shutting down the necessary components based on the current render API in use.
 * 
 * @return void
 */
void ImGuiLayer::OnDetach()
    {

        AGE_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
            case 0:
            {
                break;
            }
            case 1:
            {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplGlfw_Shutdown();
                ImGui::DestroyContext();
                break;
            }
            default:
            {
                CoreLogger::Assert(false, "Invalid Render API Selected!");
                break;
            }

        }         
    }



    /**
 * @brief Begins the ImGui layer. This function prepares for rendering of UI elements by initializing necessary states and setting up frame data based on the current render API in use.
 * 
 * The function first checks the currently selected Render API using `Renderer::GetAPI()`. Depending on the result, it performs different actions:
 * - If the API is OpenGL (0), no action is taken as there are no UI elements to initialize for this case.
 * - If the API is DirectX or Vulkan (1), it calls ImGui's NewFrame function and sets up frame data for these APIs using `ImGui_ImplOpenGL3_NewFrame()`, `ImGui_ImplGlfw_NewFrame()`, and `ImGuizmo::BeginFrame()`.
 * - If an invalid API is selected (anything else), it asserts false with a message "Invalid Render API Selected!" to halt execution.
 * 
 * @return void
 */
/**
 * @brief Begins the ImGui layer. This function initializes the ImGui context based on the currently selected render API.
 * 
 * The Renderer::GetAPI() function is used to determine which render API is in use. Depending on this, different actions are taken:
 * - If the OpenGL API is being used (case 1), then the ImGui_ImplOpenGL3_NewFrame(), ImGui_ImplGlfw_NewFrame(), and ImGui::NewFrame() functions are called to prepare for a new frame.
 *   Additionally, if not in distribution mode (AG_DIST), ImGuizmo::BeginFrame() is also called.
 * - If an invalid render API is selected (default case), then an assertion failure occurs with the message "Invalid Render API Selected!".
 * 
 * @return void
 */
void ImGuiLayer::Begin()
    {
        AGE_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
            case 0:
            {
                break;
            }
            case 1:
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
#if !AG_DIST
                ImGuizmo::BeginFrame();
#endif
                break;
            }
            default:
            {
                CoreLogger::Assert(false, "Invalid Render API Selected!");
                break;
            }
        }

    }

    /**
 * @brief This function is an event handler for the ImGuiLayer class. It dispatches events to their respective handlers based on the event type.
 * 
 * @param E Reference to the Event object that needs to be handled.
 */
/**
 * @brief Handles events dispatched by the application.
 *
 * This function is responsible for dispatching events to their respective handlers. It uses an event dispatcher to handle different types of events, such as window resizing events. 
 * The function also checks if event blocking is enabled and updates the ImGui IO accordingly.
 *
 * @param E Reference to the Event object that needs to be handled.
 */
void ImGuiLayer::OnEvent(Event& E)
    {
        EventDispatcher Dispatcher(E);

        Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResized));

        if (m_BlockEvents)
        {
           ImGuiIO& io = ImGui::GetIO();
           E.Handled |= E.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
           E.Handled |= E.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
           
        }
    }

    /**
 * @brief Handles the window resize event.
 * 
 * This function is triggered when the user resizes the window of the application. It updates the viewport and framebuffer size accordingly.
 * 
 * @param E The WindowResizeEvent object containing information about the new window size.
 * @return Returns true if the operation was successful, false otherwise. In this case, it always returns false as there are no errors to handle.
 */
/**
 * @brief Handles the window resize event.
 * 
 * This function is triggered when the size of the window changes. It updates the viewport and framebuffer sizes accordingly.
 * 
 * @param E The WindowResizeEvent object containing information about the new window size.
 * @return Returns true if the event was handled, false otherwise. In this case, it always returns false as there is no specific handling for resize events yet.
 */
bool ImGuiLayer::OnWindowResized(WindowResizeEvent& E)
    {
        return false;
    }

    

    /**
 * @brief This function is responsible for rendering the ImGui interface elements in the application.
 * 
 * @param[in] DeltaTime The time step representing the elapsed time since the last frame.
 * 
 * @return void No return value expected as this function does not explicitly return anything.
 */
/**
 * @brief This function is used to render the ImGui interface elements for a specific layer.
 * 
 * @param DeltaTime The time step representing the elapsed time since the last frame.
 */
void ImGuiLayer::OnImGuiRender(TimeStep DeltaTime)
    {
    }

    /**
 * @brief This function is responsible for ending the ImGui layer and rendering the GUI.
 * It updates the display size based on the window's width and height, then renders the GUI using either OpenGL or a different API depending on the current Renderer API. 
 * If an invalid Render API is selected, it asserts false with a message "Invalid Render API Selected!".
 * @return void
 */
/**
 * @brief This function is responsible for ending the ImGui layer and rendering it. It also updates the display size based on the window's width and height.
 * 
 * @param None
 * 
 * @return void
 */
void ImGuiLayer::End()
    {
        //If we've changed renderers then that means there will be nothing there to draw so we'll simply skip this frame and start fresh
        AGE_PROFILE_FUNCTION();
        ImGuiIO& IO = ImGui::GetIO();

        App& app = App::Get();

        IO.DisplaySize = ImVec2((float)app.GetDeviceManager().GetWindow().GetWidth(), (float)app.GetDeviceManager().GetWindow().GetHeight());

        //Rendering

        switch (Renderer::GetAPI())
        {
            case 0:
            {
                break;
            }
            case 1:
            {
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                {
                    GLFWwindow* backup_current_context = glfwGetCurrentContext();
                    ImGui::UpdatePlatformWindows();
                    ImGui::RenderPlatformWindowsDefault();
                    glfwMakeContextCurrent(backup_current_context);
                }
                break;
            }
            default:
            {
                CoreLogger::Assert(false, "Invalid Render API Selected!");
                break;
            }
        }
    }

    
/**
 * @brief Sets the colors for the dark theme in ImGui.
 * 
 * This function sets various color values used by ImGui to create a dark theme. The colors are set based on predefined RGBA values.
 * 
 * @return void
 */
void ImGuiLayer::SetDarkThemeColors()
    {
        auto& Colors = ImGui::GetStyle().Colors;

        Colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

        // Headers
        Colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        Colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        Colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Buttons
        Colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        Colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        Colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Frame BG
        Colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        Colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        Colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Tabs
        Colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        Colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
        Colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
        Colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        Colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

        // Title
        Colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        Colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        Colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    }



};