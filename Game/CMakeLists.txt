cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories(BEFORE
                    "src/"
                    "../Engine/src/AGE"
                    "src/GameFramework"
                    "../Engine/src"
                    "${INC_GLFW}"
                    "${INC_GLAD}"
                    "${INC_ImGui}"
                    "${INC_GLM}"
                  #  "${INC_STB}"
                    "${INC_Wwise}"
                    "${INC_BOX2C}"
                    "${INC_BOX2D}"
                 #   "${INC_FILEWATCH}"
                    "${OPENAL_INC_DIRS}"
                  #  "${INC_ENTT}"
                   # "${INC_IMGUIZMO}"
                 #   "${INC_MSDFGEN}"
                #    "${INC_MSDFATLASGEN}"
                    "${INC_YAMLCPP}"
                   # "${INC_SPDLOG}"
                  #  "${INC_OPENAL}"
                  #  "${INC_OPENALAL}"
                  #  "${INC_OPENALALC}"
                  #  "${INC_OPENALCommon}"
                    "${INC_LIBXML2}"
                    "${INC_LIBTMX}"
                #    "${INC_MINIMP3}"
                    "${INC_RAPIDCSV}"
                    "${INC_JSON}"
                    "${INC_FMODCORE}"
                    "${INC_FMODSTUDIO}"
                    "${INC_ZLIB}"
                    "${INC_INE}"
                    #"${INC_RTTR}"
                    "${INC_FASTGLTF}"
                    "${INC_UFBX}"
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
    ${OpenAL_BINARY_DIR}/Debug
)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Game/src)
set(GAME_PATH ${PROJECT_SOURCE_DIR} CACHE PATH "Path To Game Source")
set(GAMEFRAMEWORK_PATH ${PROJECT_SOURCE_DIR}/GameFramework CACHE PATH "Path To Game Framework Source")
project(Game VERSION 1.0.0)

message(Status " Detected System Architecture: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
if(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "x86_64" OR ${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
    add_compile_definitions(_AMD64_)
elseif(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "IA64") 
    add_compile_definitions(_IA64_)
endif()

add_library(Game
        src/Base/Public/Dockspace.h
        src/Base/Public/GameLayer.h
        src/Base/Public/GameViewport.h
        src/Base/Private/Dockspace.cpp
        src/Base/Private/Game.cpp
        src/Base/Private/GameLayer.cpp
        src/Base/Private/GameViewport.cpp
        src/GameFramework/Actors/Public/Actor.h
        src/GameFramework/Actors/Private/Actor.cpp
        src/GameFramework/Characters/Public/Character.h
        src/GameFramework/Characters/Private/Character.cpp
        src/GameFramework/Controllers/Public/AIController.h
        src/GameFramework/Controllers/Public/AudioController.h
        src/GameFramework/Controllers/Public/CameraController.h
        src/GameFramework/Controllers/Public/PlayerController.h
        src/GameFramework/Controllers/Private/AIController.cpp
        src/GameFramework/Controllers/Private/AudioController.cpp
        src/GameFramework/Controllers/Private/CameraController.cpp
        src/GameFramework/Controllers/Private/PlayerController.cpp
        src/GameFramework/GameState/Public/GameState.h
        src/GameFramework/GameState/Private/GameState.cpp
        src/GameFramework/GameStatics/Public/GameStatics.h
        src/GameFramework/GameStatics/Private/GameStatics.cpp
        src/GameFramework/GameStructs/Public/GameStructs.h
        src/GameFramework/Input/Public/InputComponent.h
        src/GameFramework/Input/Private/InputComponent.cpp
        src/GameFramework/Interactables/Public/Interactables.h
        src/GameFramework/Interactables/Private/Interactables.cpp
        src/GameFramework/Items/Public/Item.h
        src/GameFramework/Items/Public/Armor.h
        src/GameFramework/Items/Public/Weapon.h
        src/GameFramework/Items/Private/Item.cpp
        src/GameFramework/Items/Private/Armor.cpp
        src/GameFramework/Items/Private/Weapon.cpp
        src/GameFramework/Inventory/Public/Inventory.h
        src/GameFramework/Inventory/Private/Inventory.cpp
        src/GameFramework/Party/Public/Party.h
        src/GameFramework/Party/Private/Party.cpp
        src/GameFramework/Party/Private/PlayerParty.cpp
        src/GameFramework/Party/Private/EnemyParty.cpp
        src/GameFramework/Quests/Public/QuestComponent.h
        src/GameFramework/Quests/Public/QuestManager.h
        src/GameFramework/Quests/Private/QuestComponent.cpp
        src/GameFramework/Quests/Private/QuestManager.cpp
        src/GameFramework/SaveGame/Public/SaveGame.h
        src/GameFramework/SaveGame/Private/SaveGame.cpp
        src/Base/Private/UiLayer.cpp
        src/Base/Public/UiLayer.h
        src/UI/MainMenu/Private/MainMenu.cpp
        src/UI/MainMenu/Public/MainMenu.h
)
set_property(TARGET Game PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_compile_definitions(Game PUBLIC
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
#find_package(RTTR CONFIG REQUIRED Core)
target_link_libraries(Game PRIVATE
                        Engine
                        freetype
                        RTTR::Core_Lib
                        )

configure_file(CMake/Versioning.h.in Versioning.h)
