cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(BEFORE 
                    "src/"
                    "../Engine/src/AGE"
                    "../Engine/src"
                    "${GLFW_SOURCE_DIR}/include"
                    "${ImGUI_SOURCE_DIR}"
                    "${ImGUI_SOURCE_DIR}/misc"
                     ${INE_INC_DIRS}
                    ${STB_INC_DIRS}
                    "${OPENAL_INC_DIRS}"
                    "${ImGuizmo_SOURCE_DIR}"
                     ${RCSV_INC_DIRS}
                     ${JSON_INC_DIRS}
                     ${UFBX_INC_DIR}
                    "${GAME_PATH}"
                    "${GAMEFRAMEWORK_PATH}"
)

if(UNIX)
    include_directories(BEFORE
            ${SIMPLEINI_INCLUDE_DIRS}
    )

endif()
if(${BUILD_WITH_WWISE})
    if(NOT "${WWISE_INSTALL_PATH}" STREQUAL "")
        include_directories(BEFORE
                ${WWISE_INSTALL_PATH}/include
        )
    endif()
endif()

if(${BUILD_WITH_FMOD})
    if(NOT "${FMOD_INSTALL_PATH}" STREQUAL "")
        include_directories(BEFORE
                ${FMOD_INSTALL_PATH}/api/core/inc
                ${FMOD_INSTALL_PATH}/api/studio/inc
        )
    endif()
endif()


if(WIN32)
    add_compile_definitions(AG_PLATFORM_WINDOWS
                            AK_WIN
                            IMGUI_DEFINE_MATH_OPERATORS
                            AL_LIBTYPE_STATIC
                            _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNINGS
                            ZLIB_WINAPI
                            _DISABLE_STL_ANNOTATION
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

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Editor/src)
project(Editor VERSION 0.1.0)

message(Status " Detected System Architecture: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
if(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "x86_64" OR ${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
    add_compile_definitions(_AMD64_)
elseif(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "IA64") 
    add_compile_definitions(_IA64_)
endif()

if(${BUILD_WITH_FMOD})
    if(NOT "${FMOD_INSTALL_PATH}" STREQUAL "")
        link_directories(BEFORE
                ${FMOD_INSTALL_PATH}/api/core/lib/x64
                ${FMOD_INSTALL_PATH}/api/studio/lib/x64
        )
    endif()
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
                            $<$<CONFIG:RelWithDebInfo>:AG_RELEASE=1>
                            $<$<CONFIG:RelWithDebInfo>:AG_DEBUG=0>
                            $<$<CONFIG:RelWithDebInfo>:AG_DIST=0>
                            $<$<CONFIG:MinSizeRel>:AG_DIST=1>
                            $<$<CONFIG:MinSizeRel>:AG_DEBUG=0>
                            $<$<CONFIG:MinSizeRel>:AG_RELEASE=0>
)
if(WIN32)
    target_compile_options(Editor PUBLIC
            $<$<CONFIG:Debug>:/WX /Od>
            $<$<CONFIG:RelWithDebInfo>:/WX /O2>
            $<$<CONFIG:MinSizeRel>:/WX /Os /Oy>
    )
elseif(UNIX)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(Editor PUBLIC
                $<$<CONFIG:Debug>:-fsanitize=address,undefined -static-libsan -MT -Wall -Werror -Wconversion -O0  -g>
                $<$<CONFIG:RelWithDebInfo>:-Wall -Werror -Wconversion -MT -O3>
                $<$<CONFIG:MinSizeRel>:-Wall -Werror -Wconversion -MT -Os>
        )
        target_link_options(Editor PUBLIC

                $<$<CONFIG:Debug>:-fsanitize=address,undefined -static-libsan>
                $<$<CONFIG:RelWithDebInfo>:-fsanitize=address,undefined>
                $<$<CONFIG:MinSizeRel>:-fsanitize=address,undefined>
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(Editor PUBLIC
                $<$<CONFIG:Debug>:-fsanitize=address,undefined -static-libasan -static-libubsan -MT -Wall -Werror -Wconversion -O0  -g>
                $<$<CONFIG:RelWithDebInfo>:-Wall -Werror -Wconversion -MT -O3>
                $<$<CONFIG:MinSizeRel>:-Wall -Werror -Wconversion -MT -Os>
        )
        target_link_options(Editor PUBLIC

                $<$<CONFIG:Debug>:-fsanitize=address,undefined -static-libasan -static-libubsan>
                $<$<CONFIG:RelWithDebInfo>:-fsanitize=address,undefined>
                $<$<CONFIG:MinSizeRel>:-fsanitize=address,undefined>
        )
    endif()

elseif(APPLE)
    target_compile_options(Editor PUBLIC
            $<$<CONFIG:Debug>:-Wall -MT -Wconversion -O0>
            $<$<CONFIG:RelWithDebInfo> -Wall -MT -Wconversion -O3>
            $<$<CONFIG:MinSizeRel>:-Wall -MT -Wconversion -Os>
    )
endif()

find_package(Freetype REQUIRED)
if(UNIX)
find_package(PkgConfig REQUIRED)
    pkg_check_modules(PQXX REQUIRED libpqxx)
else()
find_package(libpqxx REQUIRED)
endif()

find_package(OpenSSL REQUIRED)
find_package(spdlog CONFIG REQUIRED)
if(WIN32)
find_package(nlohmann_json 3.12.0 REQUIRED)
endif()
find_package(fmt CONFIG REQUIRED)
target_link_libraries(Editor PRIVATE 
                        Engine #-WHOLEARCHIVE:$<TARGET_FILE:Engine>
                        Game
                        Freetype::Freetype
                        OpenSSL::Crypto
                        OpenSSL::SSL
                        spdlog::spdlog
                        fmt::fmt
                        nlohmann_json::nlohmann_json
                        glfw
                        ImGuizmo
                        ImGUI
                        )

if(UNIX)
    target_link_libraries(Editor PRIVATE
            ${PQXX_LIBRARIES}
    )
else()
    target_link_libraries(Editor PRIVATE
        libpqxx::pqxx
    )
endif()

configure_file(CMake/Versioning.h.in Versioning.h)
