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
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {

    }

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
                ImGuizmo::BeginFrame();
                break;
            }
            default:
            {
                CoreLogger::Assert(false, "Invalid Render API Selected!");
                break;
            }
        }

    }

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

    bool ImGuiLayer::OnWindowResized(WindowResizeEvent& E)
    {
        return false;
    }

    

    void ImGuiLayer::OnImGuiRender(TimeStep DeltaTime)
    {
    }

    void ImGuiLayer::End()
    {
        //If we've changed renderers then that means there will be nothing there to draw so we'll simply skip this frame and start fresh
        if (m_RendererChanged)
        {
            m_RendererChanged = false;
            ImGui::Render();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            m_CurrentGraphicsAPI = Renderer::GetAPI();
            return;
        }
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