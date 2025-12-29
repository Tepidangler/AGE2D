cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EDITORCORE_SRC ${CMAKE_SOURCE_DIR}/Editor/src/Editor_Core/Private/*)
set(EDITORCORE_HDR ${CMAKE_SOURCE_DIR}/Editor/src/Editor_Core/Public/*)
set(EDITORIMGUI_SRC ${CMAKE_SOURCE_DIR}/Editor/src/Editor_ImGui/Private/*)
set(EDITORIMGUI_HDR ${CMAKE_SOURCE_DIR}/Editor/src/Editor_ImGui/Public/*)
set(MENUSYSTEM_SRC ${CMAKE_SOURCE_DIR}/Editor/src/MenuSystem/Private/*)
set(MENUSYSTEM_HDR ${CMAKE_SOURCE_DIR}/Editor/src/MenuSystem/Public/*)
set(VIEWPORT_SRC ${CMAKE_SOURCE_DIR}/Editor/src/Viewports/Private/*)
set(VIEWPORT_HDR ${CMAKE_SOURCE_DIR}/Editor/src/Viewports/Public/*)

include_directories(BEFORE 
                    "src/"
                    "../Engine/src/AGE"
                    "../Engine/src"
                    "${INC_GLFW}" 
                    "${INC_GLAD}" 
                    "${INC_ImGui}" 
                    "${INC_GLM}" 
                    "${INC_STB}"
                    "${INC_Wwise}"
                    "${INC_DX12}"
                    "${INC_BOX2C}"
                    "${INC_BOX2D}"
                    "${INC_FILEWATCH}"
                    "${INC_ENTT}"
                    "${INC_IMGUIZMO}"
                    "${INC_MSDFGEN}"
                    "${INC_MSDFATLASGEN}"
                    "${INC_YAMLCPP}"
                    "${INC_SPDLOG}"
                    "${INC_OPENAL}"
                    "${INC_OPENALAL}"
                    "${INC_OPENALALC}"
                    "${INC_OPENALCommon}"
                    "${INC_LIBXML2}"
                    "${INC_LIBTMX}"
                    "${INC_MINIMP3}"
                    "${INC_RAPIDCSV}"
                    "${INC_JSON}"
                    "${INC_FMODCORE}"
                    "${INC_FMODSTUDIO}"
                    "${INC_ZLIB}"
                    "${INC_INE}"
                    "${INC_RTTR}"
                    "${INC_FASTGLTF}"
                    "${INC_UFBX}"
                    "${GAME_PATH}"
                    "${GAMEFRAMEWORK_PATH}"
)


if(WIN32)
    add_compile_definitions(AG_PLATFORM_WINDOWS
                            AK_WIN
                            IMGUI_DEFINE_MATH_OPERATORS
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


file(GLOB HDR_FILES "${EDITORCORE_HDR}"
					"${EDITORIMGUI_HDR}"
					"${MENUSYSTEM_HDR}"
					"${VIEWPORT_HDR}"					
					*.h)

file(GLOB CPP_FILES "${EDITORCORE_SRC}"
					"${EDITORIMGUI_SRC}"
					"${MENUSYSTEM_SRC}"
					"${VIEWPORT_SRC}"
					*.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Header Files" FILES ${HDR_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source Files" FILES ${CPP_FILES})

add_executable(Editor ${CPP_FILES} ${HDR_FILES}
        src/Editor_ImGui/Public/DatabaseWindow.h
        src/Editor_ImGui/Private/DatabaseWindow.cpp
        src/Editor_Core/Private/NewProjectLayer.cpp
        src/Editor_Core/Public/NewProjectLayer.h
        src/Editor_ImGui/Private/UiEditorWindow.cpp
        src/Editor_ImGui/Public/UiEditorWindow.h
)

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
find_package(RTTR CONFIG REQUIRED Core)
target_link_libraries(Editor PRIVATE 
                        Engine #-WHOLEARCHIVE:$<TARGET_FILE:Engine>
                        Game
                        freetype
                        vulkan-1
                        libpqxx::pqxx
                        OpenSSL::Crypto
                        OpenSSL::SSL
                        )

configure_file(CMake/Versioning.h.in Versioning.h)
