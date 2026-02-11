find_path(STB_INC_DIRS "stb_image.h")
find_path(FILEWATCH_INC_DIRS "thomasmonkman-filewatch/FileWatch.hpp")
find_path(SIMPLEINI_INCLUDE_DIRS "ConvertUTF.c")
find_path(MINIMP3_INCLUDE_DIRS "minimp3/minimp3.h")
find_path(JSON_INC_DIRS "nlohmann/json.hpp")
find_path(RCSV_INC_DIRS "rapidcsv.h")

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

FetchContent_Declare(Imgui-Node-Editor
GIT_REPOSITORY https://github.com/Tepidangler/imgui-node-editor.git
GIT_TAG master)

FetchContent_MakeAvailable(Imgui-Node-Editor)

FetchContent_Declare(rttr
GIT_REPOSITORY https://github.com/Tepidangler/rttr.git
GIT_TAG master)

FetchContent_MakeAvailable(rttr)


FetchContent_Declare(ufbx
        GIT_REPOSITORY https://github.com/Tepidangler/ufbx.git
        GIT_TAG master)

FetchContent_MakeAvailable(ufbx)
