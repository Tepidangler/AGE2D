cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INC_GLFW ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glfw/include CACHE PATH "Path to GLFW")
set(INC_GLAD ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glad/include CACHE PATH "Path to GLAD")
set(INC_ImGui ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/imgui CACHE PATH "Path to ImGui")
set(INC_GLM ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glm CACHE PATH "Path to GLM")
set(INC_STB ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/stb CACHE PATH "Path to stb")
set(INC_Wwise ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/include CACHE PATH "Path to Wwise")
set(INC_BOX2C ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/box2c/include/box2d CACHE PATH "Path to box2c")
set(INC_BOX2D ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/box2c/src CACHE PATH "Path to box2d") 
set(INC_FILEWATCH ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/filewatch CACHE PATH "Path to filewatch")
set(INC_FASTGLTF ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fastgltf/include CACHE PATH "Path to fastgltf")
set(INC_UFBX ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/ufbx CACHE PATH "Path to ufbx")
set(INC_ENTT ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/entt/include CACHE PATH "Path to EnTT")
set(INC_IMGUIZMO ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/ImGuizmo CACHE PATH "Path to ImGuizmo")
set(INC_SPDLOG ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/spdlog/include CACHE PATH "Path to spdlog")
set(INC_MSDFGEN ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/msdf-atlas-gen/msdfgen CACHE PATH "Path to msdfgen")
set(INC_MSDFATLASGEN ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/msdf-atlas-gen/msdf-atlas-gen  CACHE PATH "Path to msdf-atlas-gen")
set(INC_YAMLCPP ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/yaml-cpp/include  CACHE PATH "Path to yaml-cpp")
set(INC_OPENAL ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/include CACHE PATH "Path to OpenAL")
set(INC_OPENALGSL ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/gsl/include CACHE PATH "Path to OpenAL/gsl")
set(INC_OPENALROOT ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL CACHE PATH "Path to OpenAL Root")
set(INC_OPENALAL ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/al CACHE PATH "Path to OpenAL/al")
set(INC_OPENALALC ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/alc CACHE PATH "Path to OpenAL/alc")
set(INC_OPENALCommon ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/common CACHE PATH "Path to OpenAL/common")
set(INC_OPENALExamples ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/examples/common CACHE PATH "Path to OpenAL/common")
set(INC_OPENALFmt ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/fmt-11.1.4/include CACHE PATH "Path to OpenAL/fmt")
set(INC_LIBXML2 ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/libxml2/include CACHE PATH "Path to libxml2")
set(INC_LIBTMX ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/tmx/ CACHE PATH "Path to tmx")
set(INC_MINIMP3 ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/minimp3 CACHE PATH "Path to minimp3")
set(INC_RAPIDCSV ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/rapidcsv CACHE PATH "Path to rapidcsv")
set(INC_JSON ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/json/single_include CACHE PATH "Path to json")
set(INC_FMODCORE ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/core/inc CACHE PATH "Path to fmod")
set(INC_FMODSTUDIO ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/studio/inc CACHE PATH "Path to fmodstudio")
set(INC_FMT ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmt/include CACHE PATH "Path to fmt")
set(INC_RTTR ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/rttr/src CACHE PATH "Path to Run Time Type Reflection")
set(INC_ZLIB ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/zlib/include CACHE PATH "Path to zlib")
set(INC_INE ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/imgui-node-editor CACHE PATH "Path to imgui-node-editor")

set(MINIMUM_HDR ${CMAKE_SOURCE_DIR}/Engine/src/*)
set(ANIMATION_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Animation/Private/*)
set(ANIMATION_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Animation/Public/*)
set(ASSETS_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Assets/Public/*)
set(ASSETS_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Assets/Private/*)
set(AGESOUND_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Audio/AGESound/Private/*)
set(AGESOUND_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Audio/AGESound/Public/*)
set(AUDIOENGINE_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Audio/AudioEngine/Private/*)
set(AUDIOENGINE_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Audio/AudioEngine/Public/*)
set(FMOD_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Audio/Fmod/Private/*)
set(FMOD_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Audio/Fmod/Public/*)
set(WWISE_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Audio/Wwise/Private/*)
set(WWISE_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Audio/Wwise/Public/*)
set(CAMERA_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Camera/Private/*)
set(CAMERA_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Camera/Public/*)
set(CORE_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Core/Private/*)
set(CORE_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Core/Public/*)
set(DEBUG_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Debug/Private/*)
set(DEBUG_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Debug/Public/*)
set(EVENTS_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Events/Private/*)
set(EVENTS_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Events/Public/*)
set(IMGUI_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/ImGui/Private/*)
set(IMGUI_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/ImGui/Public/*)
set(MATH_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Math/Private/*)
set(MATH_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Math/Public/*)
set(PARSER_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Parser/Private/*)
set(PARSER_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Parser/Public/*)
set(PARTICLES_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Particles/Private/*)
set(UFBX_SRC ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/ufbx/*)
set(PARTICLES_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Particles/Public/*)
set(PHYSICS_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Physics/Private/*)
set(PHYSICS_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Physics/Public/*)
set(OPENGL_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Platform/OpenGL/Private/*)
set(OPENGL_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Platform/OpenGL/Public/*)
set(WINDOWS_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Platform/Windows/Private/*)
set(WINDOWS_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Platform/Windows/Public/*)
set(XINPUT_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Platform/Microsoft/XInput/Private/*)
set(XINPUT_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Platform/Microsoft/XInput/Public/*)
set(PROJECT_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Project/Private/*)
set(PROJECT_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Project/Public/*)
set(RENDER_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Render/Private/*)
set(RENDER_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Render/Public/*)
set(RNG_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/RNG/Private/*)
set(RNG_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/RNG/Public/*)
set(SCENE_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Scene/Private/*)
set(SCENE_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Scene/Public/*)
set(SERIALIZERS_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Serializers/Private/*)
set(SERIALIZERS_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Serializers/Public/*)
set(SPRITE_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Sprite/Private/*)
set(SPRITE_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Sprite/Public/*)
set(STATICS_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Statics/Private/*)
set(STATICS_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Statics/Public/*)
set(STRUCTS_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Structs/Private/*)
set(STRUCTS_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Structs/Public/*)
set(TEXTURE_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Texture/Private/*)
set(TEXTURE_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Texture/Public/*)
set(TILEMAP_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Tilemap/Private/*)
set(TILEMAP_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Tilemap/Public/*)
set(UTILS_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Utils/Private/*)
set(UTILS_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Utils/Public/*)
set(VIDEO_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Video/Private/*)
set(VIDEO_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Video/Public/*)
set(VISUALSCRIPTING_SRC ${CMAKE_SOURCE_DIR}/Engine/src/AGE/VisualScripting/Private/*)
set(VISUALSCRIPTING_HDR ${CMAKE_SOURCE_DIR}/Engine/src/AGE/VisualScripting/Public/*)

add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fastgltf)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glad)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glm)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/zlib)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/spdlog)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/entt)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/tmx)
#set(PNG_PNG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/include/libpng16" CACHE FILEPATH "Png include directory")
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/msdf-atlas-gen)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/imgui)
set(LIBTYPE STATIC) #OpenAL requires this to be set so that you can utilize it's new Device class as ALCdevice is now deprecated (and yes; they didn't document this anywhere)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL)
set(OPENAL_LIBRARY "${OpenAL_BINARY_DIR}/Debug/OpenAL32.lib" CACHE FILEPATH "OpenAL library")
set(OPENAL_INCLUDE_DIR "${OpenAL_SOURCE_DIR}/include" CACHE PATH "OpenAL include directory")
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/yaml-cpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/box2c)
message(STATUS "CMAKE BUILD DIR include dir: ${OpenAL_BINARY_DIR}")

configure_file(${INC_RTTR}/rttr/detail/base/version.h.in ${INC_RTTR}/rttr/detail/base/version.h)

include_directories(BEFORE 
                    "src/AGE/Core/Public" 
                    "../Game/src/GameFramework"
                    "src/AGE/"
                    "src/"
                    "${INC_GLFW}" 
                    "${INC_GLAD}" 
                    "${INC_ImGui}" 
                    "${INC_GLM}" 
                    "${INC_STB}"
                    "${INC_Wwise}"
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
                    "${INC_OPENALROOT}"
                    "${OpenAL_BINARY_DIR}"
                    "${INC_OPENALGSL}"
                    "${INC_OPENALAL}"
                    "${INC_OPENALALC}"
                    "${INC_OPENALExamples}"
                    "${INC_OPENALFmt}"
                    "${INC_OPENALCommon}"
                    "${INC_LIBXML2}"
                    "${INC_LIBTMX}"
                    "${INC_MINIMP3}"
                    "${INC_RAPIDCSV}"
                    "${INC_JSON}"
                    "${INC_FMODCORE}"
                    "${INC_FMODSTUDIO}"
                    "${INC_FMT}"
                    "${INC_ZLIB}"
                    "${INC_INE}"
                    "${INC_RTTR}"
                    "${INC_FASTGLTF}"
                    "${INC_UFBX}"
)

link_directories(BEFORE
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glfw/lib-vc2019
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glad/lib
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/spdlog/lib
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/libxml2/lib
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/tmx/lib
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glm/lib
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Release\(StaticCRT\)/lib
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/box2c/lib
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/libxml2/lib
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/tmx/lib
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/core/lib/x64
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/studio/lib/x64
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/zlib/lib
    $ENV{VULKAN_SDK}/Lib
)
if(WIN32)
    add_compile_definitions(AG_PLATFORM_WINDOWS
                            GLFW_INCLUDE_NONE
                            AK_OPTIMIZED
                            AK_WIN
                            AL_LIBTYPE_STATIC
                            IMGUI_DEFINE_MATH_OPERATORS
                            _CRT_SECRURE_NO_WARNINGS
                            _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNINGS
                            NOMINMAX
                            UNICODE
                            ZLIB_WINAPI
                            )
elseif(APPLE)
    add_compile_definitions(AG_PLATFORM_MACOS
                            GLFW_INCLUDE_NONE
                            AK_OPTIMIZED
                            AL_LIBTYPE_STATIC
                            IMGUI_DEFINE_MATH_OPERATORS
                            _CRT_SECRURE_NO_WARNINGS
                            _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNINGS
                            ZLIB_WINAPI
                            )
elseif(UNIX)
    add_compile_definitions(AG_PLATFORM_LINUX
                            GLFW_INCLUDE_NONE
                            AK_OPTIMIZED
                            AL_LIBTYPE_STATIC
                            IMGUI_DEFINE_MATH_OPERATORS
                            _CRT_SECRURE_NO_WARNINGS
                            _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNINGS
                            ZLIB_WINAPI
                            )
endif()

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Engine/src)
project(Engine VERSION 0.1.0)

message(Status " Detected System Architecture: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
if(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "x86_64" OR ${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
    add_compile_definitions(_AMD64_)
elseif(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "IA64") 
    add_compile_definitions(_IA64_)
endif()


file(GLOB HDR_FILES "${MINIMUM_HDR}"
                    "${ANIMATION_HDR}"
                    "${ASSETS_HDR}"
                    "${AGESOUND_HDR}"
                    "${AUDIOENGINE_HDR}"
                    "${FMOD_HDR}"
                    "${WWISE_HDR}"
					"${CAMERA_HDR}"
					"${CORE_HDR}"
					"${DEBUG_HDR}"
					"${EVENTS_HDR}"
					"${IMGUI_HDR}"
					"${MATH_HDR}"
					"${PARSER_HDR}"
					"${PARTICLES_HDR}"
					"${PHYSICS_HDR}"
					"${OPENGL_HDR}"
					"${WINDOWS_HDR}"
                    "${XINPUT_HDR}"
					"${PROJECT_HDR}"
					"${RENDER_HDR}"
					"${RNG_HDR}"
					"${SCENE_HDR}"
					"${SERIALIZERS_HDR}"
					"${SPRITE_HDR}"
					"${STATICS_HDR}"
					"${STRUCTS_HDR}"
					"${TEXTURE_HDR}"
					"${TILEMAP_HDR}"
					"${UTILS_HDR}"
					"${VIDEO_HDR}"
					"${VISUALSCRIPTING_HDR}"
                    "${UFBX_SRC}"
					*.h)

file(GLOB UFBXC_SRC "${UFBX_SRC}"
                    *.c)

file(GLOB CPP_FILES "${ANIMATION_SRC}"
                    "${ASSETS_SRC}"
                    "${AGESOUND_SRC}"
                    "${AUDIOENGINE_SRC}"
                    "${FMOD_SRC}"
                    "${WWISE_SRC}"
					"${CAMERA_SRC}"
					"${CORE_SRC}"
					"${DEBUG_SRC}"
					"${EVENTS_SRC}"
					"${IMGUI_SRC}"
					"${MATH_SRC}"
					"${PARSER_SRC}"
					"${PARTICLES_SRC}"
					"${PHYSICS_SRC}"
					"${OPENGL_SRC}"
					"${WINDOWS_SRC}"
                    "${XINPUT_SRC}"
					"${PROJECT_SRC}"
					"${RENDER_SRC}"
					"${RNG_SRC}"
					"${SCENE_SRC}"
					"${SERIALIZERS_SRC}"
					"${SPRITE_SRC}"
					"${STATICS_SRC}"
					"${STRUCTS_SRC}"
					"${TEXTURE_SRC}"
					"${TILEMAP_SRC}"
					"${UTILS_SRC}"
					"${VIDEO_SRC}"
					"${VISUALSCRIPTING_SRC}"

					*.cpp)

file(GLOB INC_INE_INL ${INC_INE}/*

                      *.inl)
file(GLOB INC_INE_HDR ${INC_INE}/*
                      ${INC_INE}/utilities/*
                      ${INC_INE}/external/DXSDK/include/*
                      ${INC_INE}/external/ScopeGuard/*

                      *.h)

file(GLOB INC_INE_SRC ${INC_INE}/*
                      ${INC_INE}/utilities/*
                      ${INC_INE}/external/DXSDK/src/*

                      *.cpp)

file(GLOB INC_WWISE_HDR ${INC_Wwise}/AK/*
                      ${INC_Wwise}/AK/Comm/*
                      ${INC_Wwise}/AK/DSP/*
                      ${INC_Wwise}/AK/DSP/Generic/*
                      ${INC_Wwise}/AK/MusicEngine/Common/*
                      ${INC_Wwise}/AK/Plugin/*
                      ${INC_Wwise}/AK/Plugin/PluginServices/*
                      ${INC_Wwise}/AK/SoundEngine/Common/*
                      ${INC_Wwise}/AK/SoundEngine/Platforms/*
                      ${INC_Wwise}/AK/SoundEngine/Platforms/arm_neon/*
                      ${INC_Wwise}/AK/SoundEngine/Platforms/Generic/*
                      ${INC_Wwise}/AK/SoundEngine/Platforms/Linux/*
                      ${INC_Wwise}/AK/SoundEngine/Platforms/POSIX/*
                      ${INC_Wwise}/AK/SoundEngine/Platforms/Windows/*
                      ${INC_Wwise}/AK/SpatialAudio/Common/*
                      ${INC_Wwise}/AK/Tools/Common/*
                      ${INC_Wwise}/AK/Tools/POSIX/*
                      ${INC_Wwise}/AK/Tools/Win32/*
                      ${INC_Wwise}/AK/Wwise/SourceControl/*
                      ${INC_Wwise}/AK/Wwise/*
                      ${INC_Wwise}/AK/Wwise/Plugin/*
                      ${INC_Wwise}/AK/Wwise/Plugin/V1/*
                      ${INC_Wwise}/AK/WwiseAuthoringAPI/*
                      ${INC_Wwise}/AK/WwiseAuthoringAPI/AkAuthbahn/*

                      *.h)

file(GLOB INC_WWISE_SRC ${INC_Wwise}/SoundEngine/Common/*

                      *.cpp)

file(GLOB INC_FMOD_HDR ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/core/inc/*
                       ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/fsbank/inc/*
                       ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/studio/inc/*
                      *.h)
list(APPEND INC_FMOD_HDR ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/core/inc/fmod.hpp ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/studio/inc/fmod_studio.hpp)

message(STATUS "HDR Files: ${HDR_FILES} ${INC_INE_INL} ${INC_INE_HDR} ${INC_WWISE_HDR} ${INC_FMOD_HDR}")
message(STATUS "CPP Files: ${CPP_FILES} ${INC_INE_SRC} ${INC_WWISE_SRC} ${UFBXC_SRC}")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Header Files" FILES ${HDR_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source Files" FILES ${CPP_FILES})

add_library(Engine STATIC
                  ${CPP_FILES} 
                  ${HDR_FILES} 
                  ${INC_INE_INL}
                  ${INC_INE_HDR}
                  ${INC_INE_SRC}
                  ${INC_ImGui}/misc/cpp/imgui_stdlib.cpp
                  ${INC_ImGui}/backends/imgui_impl_glfw.cpp
                  ${INC_ImGui}/backends/imgui_impl_opengl3.cpp
                  ${INC_IMGUIZMO}/ImGuizmo.cpp
                  ${INC_IMGUIZMO}/ImGuizmo.h
                  ${INC_WWISE_HDR}
                  ${INC_WWISE_SRC}
                  ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/stb/stb_image.cpp
                  ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/stb/stb_image.h
                  ${INC_FMOD_HDR}
                  ${UFBXC_SRC}
		src/AGE/Audio/AudioEngine/Public/Soundbank.h
		src/AGE/Audio/AudioEngine/Private/Soundbank.cpp
        src/AGE/UI/Private/WidgetStack.cpp
		src/AGE/UI/Public/WidgetStack.h
        src/AGE/UI/Public/Widget.h
		src/AGE/UI/Private/UiComponent.cpp
		src/AGE/UI/Public/UiComponent.h
		src/AGE/UI/Components/Private/TextComponent.cpp
		src/AGE/UI/Components/Public/TextComponent.h
		src/AGE/UI/Components/Private/TextBoxComponent.cpp
		src/AGE/UI/Components/Public/TextBoxComponent.h
		src/AGE/Serializers/Private/IniReader.cpp
		src/AGE/Serializers/Public/IniReader.h
		src/AGE/Serializers/Private/IniWriter.cpp
		src/AGE/Serializers/Public/IniWriter.h
		src/AGE/UI/Public/UIStructs.h
		src/AGE/UI/Private/ScriptableWidget.cpp
		src/AGE/UI/Public/ScriptableWidget.h
        src/AGE/Events/Public/UIEvent.h
		src/AGE/UI/Components/Private/UiImageComponent.cpp
		src/AGE/UI/Components/Public/UiImageComponent.h
        src/AGE/UI/Components/Private/ButtonComponent.cpp
		src/AGE/UI/Components/Public/ButtonComponent.h
        src/AGE/UI/Components/Private/VerticalBoxComponent.cpp
		src/AGE/UI/Components/Public/VerticalBoxComponent.h
		src/AGE/UI/Components/Private/HorizontalBoxComponent.cpp
		src/AGE/UI/Components/Public/HorizontalBoxComponent.h
)

target_compile_definitions(Engine PUBLIC 
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

#target_precompile_headers(Engine PUBLIC
#		${CMAKE_SOURCE_DIR}/Engine/src/AGE/Core/Public/AGEpch.hpp
#)
find_library(opengl32.lib OpenGL32)
find_library(glm glm PATHS ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glm/lib NO_DEFAULT_PATH)
find_library(AkSoundEngine AkSoundEngine.lib PATHS ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib NO_DEFAULT_PATH)
find_package(Freetype REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenAL REQUIRED)
find_package(RTTR CONFIG REQUIRED Core)
find_package(OpenAL REQUIRED)
find_path(SIMPLEINI_INCLUDE_DIRS "ConvertUTF.c")
target_include_directories(Engine PRIVATE ${SIMPLEINI_INCLUDE_DIRS})

target_link_libraries(Engine PUBLIC 
                        glfw 
                        glad
                        ImGUI
                        glm
                        spdlog::spdlog
                     	opengl32.lib
		                "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/AkSoundEngine.lib"
		                "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/AkMemoryMgr.lib"
		                "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/AkStreamMgr.lib"
                        "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/AkMusicEngine.lib"
                        "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/AkSpatialAudio.lib"                
		                "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/CommunicationCentral.lib"
		                Ws2_32
		                Winmm
		                "Version.lib"
		                BCrypt
                        xinput
                        tmx
                        EnTT::EnTT 
                        msdf-atlas-gen::msdf-atlas-gen
                        msdfgen::msdfgen
                        freetype
                        yaml-cpp::yaml-cpp 
                        LibXml2::LibXml2
						RTTR::Core
                        "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/core/lib/x64/fmod_vc.lib"
                        "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/studio/lib/x64/fmodstudio_vc.lib"
                        box2d 
                        ZLIB::ZLIB
                        OpenAL::OpenAL
                        )



configure_file(CMake/Versioning.h.in Versioning.h)
