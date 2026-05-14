if(WIN32)
find_path(FILEWATCH_INC_DIRS "thomasmonkman-filewatch/FileWatch.hpp")
find_path(SIMPLEINI_INCLUDE_DIRS "ConvertUTF.c")
find_path(MINIMP3_INCLUDE_DIRS "minimp3/minimp3.h")
find_path(JSON_INC_DIRS "nlohmann/json.hpp")
find_path(RCSV_INC_DIRS "rapidcsv.h")
endif()

include(FetchContent)

FetchContent_Declare(msdf-atlas-gen
        GIT_REPOSITORY https://github.com/Chlumsky/msdf-atlas-gen.git
        GIT_TAG c76a32319934c39e51a8c4838240d7b2362b0882)

# Set necessary options for msdf-atlas-gen
set(MSDF_ATLAS_USE_VCPKG OFF CACHE BOOL "" FORCE)
set(MSDF_ATLAS_BUILD_STANDALONE OFF CACHE BOOL "" FORCE)
set(MSDF_ATLAS_MSDFGEN_EXTERNAL OFF CACHE BOOL "" FORCE)
set(MSDF_ATLAS_DYNAMIC_RUNTIME OFF CACHE BOOL "Build Dynamic Runtime MSDF-ATLAS-GEN")
set(MSDFGEN_CORE_ONLY OFF)
set(MSDFGEN_BUILD_STANDALONE OFF)
set(MSDFGEN_DISABLE_SVG OFF)
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(msdf-atlas-gen)

FetchContent_Declare(GLAD
        GIT_REPOSITORY https://github.com/Tepidangler/glad.git
        GIT_TAG main)

FetchContent_MakeAvailable(GLAD)


FetchContent_Declare(GLFW
        GIT_REPOSITORY https://github.com/Tepidangler/glfw.git
        GIT_TAG master)

FetchContent_MakeAvailable(GLFW)

FetchContent_Declare(openal-soft
        GIT_REPOSITORY https://github.com/Tepidangler/openal-soft.git
        GIT_TAG master)

set(LIBTYPE STATIC)

FetchContent_MakeAvailable(openal-soft)

set(OPENAL_INC_DIRS
        "${openal-soft_SOURCE_DIR}"
        "${openal-soft_SOURCE_DIR}/include"
        "${openal-soft_SOURCE_DIR}/common"
        "${openal-soft_SOURCE_DIR}/gsl/include"
        "${openal-soft_BINARY_DIR}" CACHE PATH "OpenAL Include Dirs" FORCE)

FetchContent_Declare(ImGui
        GIT_REPOSITORY https://github.com/Tepidangler/imgui
        GIT_TAG docking)

FetchContent_MakeAvailable(ImGui)

FetchContent_Declare(ImGuizmo
GIT_REPOSITORY https://github.com/Tepidangler/ImGuizmo.git
GIT_TAG master
)

FetchContent_MakeAvailable(ImGuizmo)

#stb
FetchContent_Declare(stb
        GIT_REPOSITORY https://github.com/Tepidangler/stb.git
        GIT_TAG master
)
FetchContent_MakeAvailable(stb)

if(WIN32)
FetchContent_Declare(Imgui-Node-Editor
GIT_REPOSITORY https://github.com/Tepidangler/imgui-node-editor.git
GIT_TAG master)
FetchContent_MakeAvailable(Imgui-Node-Editor)
endif()

FetchContent_Declare(rttr
GIT_REPOSITORY https://github.com/Tepidangler/rttr.git
GIT_TAG master)

FetchContent_MakeAvailable(rttr)


FetchContent_Declare(ufbx
        GIT_REPOSITORY https://github.com/Tepidangler/ufbx.git
        GIT_TAG master)

FetchContent_MakeAvailable(ufbx)

if(${BUILD_WITH_FMOD})
    if(NOT "${FMOD_INSTALL_PATH}" STREQUAL "")
        FetchContent_Declare(Fmod
                GIT_REPOSITORY https://github.com/Tepidangler/FModCmake.git
                GIT_TAG "origin/main"
        )
        FetchContent_MakeAvailable(Fmod)
    endif()
endif()

if(${BUILD_WITH_WWISE})
    if(NOT "${WWISE_INSTALL_PATH}" STREQUAL "")
        FetchContent_Declare(Wwise
                GIT_REPOSITORY https://github.com/Tepidangler/WwiseCmake.git
                GIT_TAG "origin/main"
        )
        FetchContent_MakeAvailable(Wwise)
    endif()
endif()

#portable-file-dialogs
FetchContent_Declare(portable-file-dialogs
        GIT_REPOSITORY https://github.com/Tepidangler/portable-file-dialogs.git
        GIT_TAG main)
FetchContent_MakeAvailable(portable-file-dialogs)

find_path(PFD_INC_DIRS "portable-file-dialogs.h" ${portable-file-dialogs_SOURCE_DIR})

if(UNIX)
    #entt
    FetchContent_Declare(entt
            GIT_REPOSITORY https://github.com/Tepidangler/entt.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(entt)
    #fastgltf
    FetchContent_Declare(fastgltf
            GIT_REPOSITORY https://github.com/Tepidangler/fastgltf.git
            GIT_TAG main
    )
    FetchContent_MakeAvailable(fastgltf)
    #minimp3
    FetchContent_Declare(minimp3
            GIT_REPOSITORY https://github.com/Tepidangler/minimp3.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(minimp3)
    #nlohmann-json
    FetchContent_Declare(nlohmann_json
            GIT_REPOSITORY https://github.com/Tepidangler/json.git
            GIT_TAG develop
    )
    FetchContent_MakeAvailable(nlohmann_json)

    #filwatch
    FetchContent_Declare(filewatch
            GIT_REPOSITORY https://github.com/Tepidangler/filewatch.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(filewatch)
    #simpleini
    FetchContent_Declare(simpleini
            GIT_REPOSITORY https://github.com/Tepidangler/simpleini.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(simpleini)
    #rapidcsv
    FetchContent_Declare(rapidcsv
            GIT_REPOSITORY https://github.com/Tepidangler/rapidcsv.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(rapidcsv)
    #libtmx
    FetchContent_Declare(libtmx
            GIT_REPOSITORY https://github.com/Tepidangler/tmx.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(libtmx)
    #box2d
    FetchContent_Declare(box2d
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/erincatto/box2d/archive/refs/tags/v3.1.1.zip
    )
    FetchContent_MakeAvailable(box2d)
    #x11-compat INE
    FetchContent_Declare(Imgui-Node-Editor
            GIT_REPOSITORY https://github.com/Tepidangler/imgui-node-editor.git
            GIT_TAG x11-compat)
    FetchContent_MakeAvailable(Imgui-Node-Editor)


    find_path(FILEWATCH_INC_DIRS "FileWatch.hpp" ${filewatch_SOURCE_DIR})
    find_path(SIMPLEINI_INCLUDE_DIRS "ConvertUTF.c" ${simpleini_SOURCE_DIR})
    find_path(MINIMP3_INCLUDE_DIRS "minimp3.h" ${minimp3_SOURCE_DIR})
    find_path(JSON_INC_DIRS "single_include/nlohmann/json.hpp" ${nlohmann_json_SOURCE_DIR})
    find_path(RCSV_INC_DIRS "src/rapidcsv.h" ${rapidcsv_SOURCE_DIR})

endif()
    find_path(STB_INC_DIRS "stb_image.h" ${stb_SOURCE_DIR})
