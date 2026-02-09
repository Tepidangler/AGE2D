cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(BEFORE 
                    "src/"
                    "../Engine/src/AGE"
                    "../Engine/src"
                    "${INC_GLFW}" 
                    "${INC_GLAD}" 
                    "${INC_ImGui}" 
                    "${INC_GLM}" 
                #    "${INC_STB}"
                    "${INC_Wwise}"
                    "${INC_BOX2C}"
                    "${INC_BOX2D}"
                 #   "${INC_FILEWATCH}"
                    "${OPENAL_INC_DIRS}"
              #      "${INC_ENTT}"
                    "${ImGuizmo_SOURCE_DIR}"
                    "${INC_YAMLCPP}"
                   # "${INC_SPDLOG}"
                  #  "${INC_OPENAL}"
                  #  "${INC_OPENALAL}"
                  #  "${INC_OPENALALC}"
                  #  "${INC_OPENALCommon}"
                    "${INC_LIBXML2}"
                    "${INC_LIBTMX}"
                 #   "${INC_MINIMP3}"
                    "${INC_RAPIDCSV}"
                    "${INC_JSON}"
                    "${INC_FMODCORE}"
                    "${INC_FMODSTUDIO}"
                    "${INC_ZLIB}"
                    "${INC_INE}"
                 #   "${INC_RTTR}"
                    "${INC_FASTGLTF}"
                    "${INC_UFBX}"
                    "${GAME_PATH}"
                    "${GAMEFRAMEWORK_PATH}"
)


if(WIN32)
    add_compile_definitions(AG_PLATFORM_WINDOWS
                            AK_WIN
                            IMGUI_DEFINE_MATH_OPERATORS
                            AL_LIBTYPE_STATIC
                            _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNINGS
                            ZLIB_WINAPI
                            LIBXML_STATIC
                            UNICODE
                            NOMINMAX
                            )
elseif(APPLE)
    add_compile_definitions(AG_PLATFORM_MACOS
                            IMGUI_DEFINE_MATH_OPERATORS
                            _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNINGS
                            ZLIB_WINAPI
                            LIBXML_STATIC
                            )
elseif(UNIX)
    add_compile_definitions(AG_PLATFORM_LINUX
                            IMGUI_DEFINE_MATH_OPERATORS
                            _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNINGS
                            ZLIB_WINAPI
                            LIBXML_STATIC
                            )
endif()

link_directories( 
    $ENV{VULKAN_SDK}/Lib
    ${OpenAL_BINARY_DIR}/Debug
)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Editor/src)
project(Editor VERSION 0.1.0)

message(Status " Detected System Architecture: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
if(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "x86_64" OR ${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
    add_compile_definitions(_AMD64_)
elseif(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "IA64") 
    add_compile_definitions(_IA64_)
endif()

add_executable(Editor
        src/Viewports/Public/Viewport.h
        src/Editor_ImGui/Private/InventoryDatabase.cpp
        src/Editor_Core/Public/EditorLayer.h
        src/Editor_ImGui/Public/QuestManagerWindow.h
        src/Editor_ImGui/Public/Toolbar.h
        src/Editor_ImGui/Private/ContentBrowserPanel.cpp
        src/Editor_ImGui/Private/AssetRegistryWindow.cpp
        src/Editor_ImGui/Private/ConsoleLog.cpp
        src/MenuSystem/Public/CreateProjectMenu.h
        src/Editor_ImGui/Public/AssetRegistryWindow.h
        src/Editor_ImGui/Private/QuestManagerWindow.cpp
        src/Editor_ImGui/Private/SceneHierarchyPanel.cpp
        src/Editor_Core/Private/Database.cpp
        src/Editor_ImGui/Public/ContentBrowserPanel.h
        src/MenuSystem/Public/MainMenuBar.h
        src/MenuSystem/Private/MainMenuBar.cpp
        src/Editor_ImGui/Public/SceneHierarchyPanel.h
        src/Editor_ImGui/Public/InventoryDatabase.h
        src/Editor_ImGui/Private/Dockspace.cpp
        src/Editor_Core/Private/AGEeditor.cpp
        src/Editor_ImGui/Public/ConsoleLog.h
        src/Editor_Core/Public/Database.h
        src/Viewports/Private/Viewport.cpp
        src/MenuSystem/Private/CreateProjectMenu.cpp
        src/Editor_ImGui/Public/Panel.h
        src/Editor_ImGui/Public/Dockspace.h
        src/Editor_Core/Private/EditorLayer.cpp
        src/Editor_ImGui/Private/Toolbar.cpp
        src/Editor_ImGui/Private/Panel.cpp
        src/Editor_ImGui/Public/DatabaseWindow.h
        src/Editor_ImGui/Private/DatabaseWindow.cpp
        src/Editor_Core/Private/NewProjectLayer.cpp
        src/Editor_Core/Public/NewProjectLayer.h
        src/Editor_ImGui/Private/UiEditorWindow.cpp
        src/Editor_ImGui/Public/UiEditorWindow.h
        src/Editor_Core/Private/CodeGen.cpp
        src/Editor_Core/Public/CodeGen.h
)
set_property(TARGET Editor PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_compile_definitions(Editor PUBLIC
                            $<$<CONFIG:Debug>:AG_DEBUG=1>
                            $<$<CONFIG:Debug>:AG_RELEASE=0>
                            $<$<CONFIG:Debug>:AG_DIST=0>
                            $<$<CONFIG:Release>:AG_RELEASE=1>
                            $<$<CONFIG:Release>:AG_DEBUG=0>
                            $<$<CONFIG:Release>:AG_DIST=0>
                            $<$<CONFIG:Dist>:AG_DIST=1>
                            $<$<CONFIG:Dist>:AG_DEBUG=0>
                            $<$<CONFIG:Dist>:AG_RELEASE=0>
)
find_package(Freetype REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
#find_package(RTTR CONFIG REQUIRED Core)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(Editor PRIVATE 
                        Engine #-WHOLEARCHIVE:$<TARGET_FILE:Engine>
                        Game
                        Freetype::Freetype
                        vulkan-1
                        libpqxx::pqxx
                        OpenSSL::Crypto
                        OpenSSL::SSL
                        spdlog::spdlog
                        fmt::fmt
                        RTTR::Core_Lib
                        )

configure_file(CMake/Versioning.h.in Versioning.h)
