cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INC_GLFW ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glfw/include CACHE PATH "Path to GLFW")
set(INC_GLAD ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glad/include CACHE PATH "Path to GLAD")
set(INC_ImGui ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/imgui CACHE PATH "Path to ImGui")
set(INC_GLM ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glm CACHE PATH "Path to GLM")
#set(INC_STB ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/stb CACHE PATH "Path to stb")
set(INC_Wwise ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/include CACHE PATH "Path to Wwise")
set(INC_BOX2C ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/box2c/include/box2d CACHE PATH "Path to box2c")
set(INC_BOX2D ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/box2c/src CACHE PATH "Path to box2d") 
set(INC_FILEWATCH ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/filewatch CACHE PATH "Path to filewatch")
set(INC_FASTGLTF ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fastgltf/include CACHE PATH "Path to fastgltf")
set(INC_UFBX ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/ufbx CACHE PATH "Path to ufbx")
#set(INC_IMGUIZMO ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/ImGuizmo CACHE PATH "Path to ImGuizmo")
#set(INC_SPDLOG ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/spdlog/include CACHE PATH "Path to spdlog")
set(INC_YAMLCPP ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/yaml-cpp/include  CACHE PATH "Path to yaml-cpp")
#set(INC_OPENAL ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/include CACHE PATH "Path to OpenAL")
#set(INC_OPENALGSL ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/gsl/include CACHE PATH "Path to OpenAL/gsl")
#set(INC_OPENALROOT ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL CACHE PATH "Path to OpenAL Root")
#set(INC_OPENALAL ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/al CACHE PATH "Path to OpenAL/al")
#set(INC_OPENALALC ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/alc CACHE PATH "Path to OpenAL/alc")
#set(INC_OPENALCommon ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/common CACHE PATH "Path to OpenAL/common")
#set(INC_OPENALExamples ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/examples/common CACHE PATH "Path to OpenAL/common")
#set(INC_OPENALFmt ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL/fmt-11.1.4/include CACHE PATH "Path to OpenAL/fmt")
set(INC_LIBXML2 ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/libxml2/include CACHE PATH "Path to libxml2")
set(INC_LIBTMX ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/tmx/ CACHE PATH "Path to tmx")
set(INC_RAPIDCSV ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/rapidcsv CACHE PATH "Path to rapidcsv")
set(INC_JSON ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/json/single_include CACHE PATH "Path to json")
set(INC_FMODCORE ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/core/inc CACHE PATH "Path to fmod")
set(INC_FMODSTUDIO ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/studio/inc CACHE PATH "Path to fmodstudio")
set(INC_FMT ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmt/include CACHE PATH "Path to fmt")
#set(INC_RTTR ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/rttr/src CACHE PATH "Path to Run Time Type Reflection")
set(INC_ZLIB ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/zlib/include CACHE PATH "Path to zlib")
set(INC_INE ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/imgui-node-editor CACHE PATH "Path to imgui-node-editor")

set(MINIMUM_HDR ${CMAKE_SOURCE_DIR}/Engine/src/*)

add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fastgltf)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glad)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glm)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/zlib)
#add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/spdlog)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/tmx)
#add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/imgui)
#set(LIBTYPE STATIC) #OpenAL requires this to be set so that you can utilize it's new Device class as ALCdevice is now deprecated (and yes; they didn't document this anywhere)
#add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/OpenAL)
#set(OPENAL_LIBRARY "${OpenAL_BINARY_DIR}/Debug/OpenAL32.lib" CACHE FILEPATH "OpenAL library")
#set(OPENAL_INCLUDE_DIR "${OpenAL_SOURCE_DIR}/include" CACHE PATH "OpenAL include directory")
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/yaml-cpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/libs/vendor/box2c)
message(STATUS "CMAKE BUILD DIR include dir: ${OpenAL_BINARY_DIR}")

#configure_file(${INC_RTTR}/rttr/detail/base/version.h.in ${INC_RTTR}/rttr/detail/base/version.h)

include_directories(BEFORE 
                    "src/AGE/Core/Public" 
                    "../Game/src/GameFramework"
                    "src/AGE/"
                    "src/"
                    "${INC_GLFW}" 
                    "${INC_GLAD}" 
                    "${INC_ImGui}" 
                    "${INC_GLM}" 
#                    "${INC_STB}"
                    "${INC_Wwise}"
       #             "${INC_BOX2C}"
       #             "${INC_BOX2D}"
        #            "${INC_FILEWATCH}"
                    #"${INC_IMGUIZMO}"
         #           "${INC_YAMLCPP}"
           #         "${INC_SPDLOG}"
                #    "${INC_OPENAL}"
                #    "${INC_OPENALROOT}"
                #    "${OpenAL_BINARY_DIR}"
                #    "${INC_OPENALGSL}"
                #    "${INC_OPENALAL}"
                #    "${INC_OPENALALC}"
                #    "${INC_OPENALExamples}"
                #    "${INC_OPENALFmt}"
                #    "${INC_OPENALCommon}"
                    "${INC_LIBXML2}"
                    "${INC_LIBTMX}"
                    "${INC_RAPIDCSV}"
                    "${INC_JSON}"
                    "${INC_FMODCORE}"
                    "${INC_FMODSTUDIO}"
					"${ImGuizmo_SOURCE_DIR}"
                #    "${INC_FMT}"
                    "${INC_ZLIB}"
                    "${INC_INE}"
                    #"${INC_RTTR}"
                    "${INC_FASTGLTF}"
                    "${INC_UFBX}"
)

link_directories(BEFORE

    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glfw/lib-vc2019
    ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/glad/lib
   # ${CMAKE_SOURCE_DIR}/Engine/libs/vendor/spdlog/lib
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

file(GLOB UFBXC_SRC "${UFBX_SRC}"
                    *.c)

#file(GLOB INC_INE_INL ${INC_INE}/*
#
#                      *.inl)
#file(GLOB INC_INE_HDR ${INC_INE}/*
#                      ${INC_INE}/utilities/*
#                      ${INC_INE}/external/DXSDK/include/*
#                      ${INC_INE}/external/ScopeGuard/*
#
#                      *.h)

#file(GLOB INC_INE_SRC ${INC_INE}/*
#                      ${INC_INE}/utilities/*
#                      ${INC_INE}/external/DXSDK/src/*
#
#                      *.cpp)

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

#source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Header Files" FILES ${HDR_FILES})
#source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source Files" FILES ${CPP_FILES})

add_library(Engine STATIC
                  #${INC_INE_INL}
                  #${INC_INE_HDR}
                  #${INC_INE_SRC}
                  #${INC_ImGui}/misc/cpp/imgui_stdlib.cpp
                  #${INC_ImGui}/backends/imgui_impl_glfw.cpp
                  #${INC_ImGui}/backends/imgui_impl_opengl3.cpp
                  ${INC_WWISE_HDR}
                  ${INC_WWISE_SRC}
                  #${STB_INC_DIRS}/stb_image.cpp
                  ${STB_INC_DIRS}/stb_image.h
                  ${INC_FMOD_HDR}
                  ${UFBXC_SRC}
		src/AGE/Core/Private/AGEpch.cpp
		src/AGE/Core/Public/AGEpch.hpp
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
		src/AGE/Animation/Private/Animation.cpp
		src/AGE/Animation/Public/Animation.h
		src/AGE/Assets/Private/AssetManager.cpp
		src/AGE/Assets/Public/AssetManager.h
		src/AGE/Audio/AGESound/Private/Sound.cpp
		src/AGE/Audio/AGESound/Public/Sound.h
		src/AGE/Audio/AGESound/Private/AGEAudio.cpp
		src/AGE/Audio/AGESound/Public/AGEAudio.h
		src/AGE/Audio/AudioEngine/Private/AudioEngine.cpp
		src/AGE/Audio/AudioEngine/Public/AudioEngine.h
		src/AGE/Audio/Fmod/Private/FmodEngine.cpp
		src/AGE/Audio/Fmod/Public/FmodEngine.h
		src/AGE/Audio/Wwise/Private/WwiseEngine.cpp
		src/AGE/Audio/Wwise/Public/WwiseEngine.h
		src/AGE/Camera/Private/EditorCamera.cpp
		src/AGE/Camera/Public/EditorCamera.h
		src/AGE/Camera/Public/Camera.h
		src/AGE/Core/Private/App.cpp
		src/AGE/Core/Public/App.h
		src/AGE/Core/Private/DeviceManager.cpp
		src/AGE/Core/Public/DeviceManager.h
		src/AGE/Core/Private/Layer.cpp
		src/AGE/Core/Public/Layer.h
		src/AGE/Core/Private/LayerStack.cpp
		src/AGE/Core/Public/LayerStack.h
		src/AGE/Core/Private/Log.cpp
		src/AGE/Core/Public/Log.h
		src/AGE/Core/Private/ScriptableComponentStack.cpp
		src/AGE/Core/Public/ScriptableComponentStack.h
		src/AGE/Core/Private/UUID.cpp
		src/AGE/Core/Public/UUID.h
		src/AGE/Core/Public/Timer.h
		src/AGE/Core/Public/Core.h
		src/AGE/Core/Public/MouseButtonCodes.h
		src/AGE/Core/Public/Keycodes.h
		src/AGE/Core/Public/Colors.h
		src/AGE/Core/Public/Wwise_IDs.h
		src/AGE/Core/Public/DeltaTime.h
		src/AGE/Core/Public/JoyStickCodes.h
		src/AGE/Core/Public/Buffer.h
		src/AGE/Core/Public/Window.h
		src/AGE/Core/Public/GamepadCodes.h
		src/AGE/Core/Public/EntryPoint.h
		src/AGE/Core/Public/Input.h
		src/AGE/Debug/Public/Instrumentor.h
		src/AGE/Events/Public/ApplicationEvent.h
		src/AGE/Events/Public/Event.h
		src/AGE/Events/Public/GameEvent.h
		src/AGE/Events/Public/KeyEvent.h
		src/AGE/Events/Public/MouseEvent.h
		src/AGE/Events/Public/RendererEvent.h
		src/AGE/ImGui/Private/ImGuiLayer.cpp
		src/AGE/ImGui/Public/ImGuiLayer.h
		src/AGE/Math/Private/Math.cpp
		src/AGE/Math/Public/Math.h
		src/AGE/Math/Public/MathStructures.h
		src/AGE/Math/Private/Vector4.cpp
		src/AGE/Math/Public/Vector4.h
		src/AGE/Math/Private/UtilityFunctions.cpp
		src/AGE/Math/Public/UtilityFunctions.h
		src/AGE/Math/Private/Vector3.cpp
		src/AGE/Math/Public/Vector3.h
		src/AGE/Math/Private/Vector2.cpp
		src/AGE/Math/Public/Vector2.h
		src/AGE/Parser/Private/CsvParser.cpp
		src/AGE/Parser/Public/CsvParser.h
		src/AGE/Parser/Private/JsonParser.cpp
		src/AGE/Parser/Public/JsonParser.h
		src/AGE/Parser/Private/FbxParser.cpp
		src/AGE/Parser/Public/FbxParser.h
		src/AGE/Particles/Private/ParticleSystem.cpp
		src/AGE/Particles/Public/ParticleSystem.h
		src/AGE/Physics/Private/World.cpp
		src/AGE/Physics/Public/World.h
		src/AGE/Physics/Private/World2D.cpp
		src/AGE/Physics/Public/World2D.h
		src/AGE/Physics/Private/Physics2D.cpp
		src/AGE/Physics/Public/Physics2D.h
		src/AGE/Platform/OpenGL/Private/OpenGLVertexArray.cpp
		src/AGE/Platform/OpenGL/Public/OpenGLVertexArray.h
		src/AGE/Platform/OpenGL/Private/OpenGlContext.cpp
		src/AGE/Platform/OpenGL/Public/OpenGlContext.h
		src/AGE/Platform/OpenGL/Private/OpenGLFrameBuffer.cpp
		src/AGE/Platform/OpenGL/Public/OpenGLFrameBuffer.h
		src/AGE/Platform/OpenGL/Private/OpenGLPipeline.cpp
		src/AGE/Platform/OpenGL/Public/OpenGLPipeline.h
		src/AGE/Platform/OpenGL/Private/OpenGLShader.cpp
		src/AGE/Platform/OpenGL/Public/OpenGLShader.h
		src/AGE/Platform/OpenGL/Private/OpenGLRendererAPI.cpp
		src/AGE/Platform/OpenGL/Public/OpenGLRendererAPI.h
		src/AGE/Platform/OpenGL/Private/OpenGLTexture.cpp
		src/AGE/Platform/OpenGL/Public/OpenGLTexture.h
		src/AGE/Platform/OpenGL/Public/imgui_impl_opengl3_loader.h
		src/AGE/Platform/Windows/Private/WindowsWindow.cpp
		src/AGE/Platform/Windows/Public/WindowsWindow.h
		src/AGE/Platform/Microsoft/XInput/Private/XInput.cpp
		src/AGE/Platform/Microsoft/XInput/Public/XInput.h
		src/AGE/Platform/OpenGL/Private/OpenGLBuffer.cpp
		src/AGE/Platform/OpenGL/Public/OpenGLBuffer.h
		src/AGE/Platform/Windows/Private/WindowsInput.cpp
		src/AGE/Project/Private/Project.cpp
		src/AGE/Project/Public/Project.h
		src/AGE/Render/Private/Shader.cpp
		src/AGE/Render/Public/Shader.h
		src/AGE/Render/Private/Font.cpp
		src/AGE/Render/Public/Font.h
		src/AGE/Render/Private/Renderer2D.cpp
		src/AGE/Render/Public/Renderer2D.h
		src/AGE/Render/Private/RenderCommand.cpp
		src/AGE/Render/Public/RenderCommand.h
		src/AGE/Render/Private/RenderBuffer.cpp
		src/AGE/Render/Public/RenderBuffer.h
		src/AGE/Render/Private/GraphicsContext.cpp
		src/AGE/Render/Public/GraphicsContext.h
		src/AGE/Render/Private/FrameBuffer.cpp
		src/AGE/Render/Public/FrameBuffer.h
		src/AGE/Render/Private/RenderAPI.cpp
		src/AGE/Render/Public/RenderAPI.h
		src/AGE/Render/Private/VertexArray.cpp
		src/AGE/Render/Public/VertexArray.h
		src/AGE/Render/Private/Renderer.cpp
		src/AGE/Render/Public/Renderer.h
		src/AGE/Render/Private/Pipeline.cpp
		src/AGE/Render/Public/Pipeline.h
		src/AGE/Render/Public/MSDFData.h
		src/AGE/RNG/Private/RNG.cpp
		src/AGE/RNG/Public/RNG.h
		src/AGE/Scene/Private/Scene.cpp
		src/AGE/Scene/Public/Scene.h
		src/AGE/Scene/Private/Entity.cpp
		src/AGE/Scene/Public/Entity.h
		src/AGE/Scene/Private/SceneCamera.cpp
		src/AGE/Scene/Public/SceneCamera.h
		src/AGE/Scene/Private/ScriptableEntity.cpp
		src/AGE/Scene/Public/ScriptableEntity.h
		src/AGE/Scene/Public/Components.h
		src/AGE/Serializers/Private/DataReader.cpp
		src/AGE/Serializers/Public/DataReader.h
		src/AGE/Serializers/Private/DataWriter.cpp
		src/AGE/Serializers/Public/DataWriter.h
		src/AGE/Sprite/Private/Aseprite.cpp
		src/AGE/Sprite/Public/Aseprite.h
		src/AGE/Sprite/Private/Image.cpp
		src/AGE/Sprite/Public/Image.h
		src/AGE/Sprite/Private/SpriteAPI.cpp
		src/AGE/Sprite/Public/SpriteAPI.h
		src/AGE/Statics/Public/Statics.h
		src/AGE/Structs/Public/DataStructures.h
		src/AGE/Structs/Public/Functions.h
		src/AGE/Texture/Private/Texture.cpp
		src/AGE/Texture/Public/Texture.h
		src/AGE/Texture/Private/SubTexture.cpp
		src/AGE/Texture/Public/SubTexture.h
		src/AGE/TileMap/Private/TileMapManager.cpp
		src/AGE/TileMap/Public/TileMapManager.h
		src/AGE/TileMap/Private/TileMapImporter.cpp
		src/AGE/TileMap/Public/TileMapImporter.h
		src/AGE/Utils/Private/Serializers.cpp
		src/AGE/Utils/Public/Serializers.h
		src/AGE/Utils/Private/WindowsUtils.cpp
		src/AGE/Utils/Public/WindowsUtils.h
		src/AGE/Video/Private/VideoSource.cpp
		src/AGE/Video/Public/VideoSource.h
		src/AGE/Video/Private/AGEVideo.cpp
		src/AGE/Video/Public/AGEVideo.h
		src/AGE/VisualScripting/Private/NodeEditorManager.cpp
		src/AGE/VisualScripting/Public/NodeEditorManager.h
		src/AGE/VisualScripting/Public/VisualScriptingStructs.h
		src/AGE/VisualScripting/Private/NodeEditorWindow.cpp
		src/AGE/VisualScripting/Public/NodeEditorWindow.h
		src/AGE/Core/Public/Pointers.h
)
set_property(TARGET Engine PROPERTY
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
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
find_package(LibXml2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Freetype CONFIG REQUIRED)
find_package(EnTT REQUIRED)
#find_package(RTTR CONFIG REQUIRED Core)
find_package(box2d CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(yaml-cpp REQUIRED)

target_include_directories(Engine PRIVATE
		${SIMPLEINI_INCLUDE_DIRS}
		${MINIMP3_INCLUDE_DIRS}
		"${OPENAL_INC_DIRS}"
		${STB_INC_DIRS}
		${FILEWATCH_INC_DIRS}
)
target_link_libraries(Engine PUBLIC
                        glfw 
                        glad
                        ImGUI
                        glm
                        spdlog::spdlog
						fmt::fmt
                     	opengl32.lib
		                "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/AkSoundEngine.lib"
		                "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/AkMemoryMgr.lib"
		                "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/AkStreamMgr.lib"
                        "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/AkMusicEngine.lib"
                        "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/AkSpatialAudio.lib"                
		                "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/Wwise/x64_vc170/Debug\(StaticCRT\)/lib/CommunicationCentral.lib"
		                Ws2_32
		                Winmm
		                BCrypt
                        xinput
                        tmx
                        EnTT::EnTT
                        msdfgen::msdfgen-core
                        msdfgen::msdfgen-ext
                        msdf-atlas-gen::msdf-atlas-gen
                        Freetype::Freetype
                        yaml-cpp::yaml-cpp 
                        LibXml2::LibXml2
						RTTR::Core_Lib
                        "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/core/lib/x64/fmod_vc.lib"
                        "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/fmod/api/studio/lib/x64/fmodstudio_vc.lib"
                        box2d::box2d
                        ZLIB::ZLIB
                        )

configure_file(CMake/Versioning.h.in Versioning.h)
