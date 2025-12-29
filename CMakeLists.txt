cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CONFIGURATION_TYPES Debug;Release;Dist)
set(CMAKE_INSTALL_PREFIX "./")
set(msdfgen_DIR "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/msdf-atlas-gen/msdfgen/cmake")
set(ZLIB_ROOT "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/zlib")
set(WANT_ZLIB OFF)
set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "Use the DLL version of the MSVC runtime library")
set(FASTGLTF_COMPILE_AS_CPP20 ON CACHE BOOL "Compile fastgltf as C++20")
set(FASTGLTF_ENABLE_IMPLICIT_SHAPES ON CACHE BOOL "Enable implicit shapes in fastgltf")
set(FASTGLTF_ENABLE_KHR_PHYSICS_RIGID_BODIES ON CACHE BOOL "Enable khr_physics_rigid_bodies in fastgltf")
set(MSDF_ATLAS_USE_VCPKG ON CACHE BOOL "Use vcpkg to find dependencies")
set(MSDF_ATLAS_DYNAMIC_RUNTIME ON CACHE BOOL "Build MSDF with dynamic runtime") 
set(MSDF_ATLAS_USE_SKIA OFF CACHE INTERNAL "Don't use skia")
set(MSDF_ATLAS_BUILD_STANDALONE OFF CACHE INTERNAL "Don't build standalone executable for msdf-atlas-gen")
set(MSDFGEN_USE_SKIA OFF CACHE INTERNAL "Don't use skia msdfgen")
set(PNG_EXECUTABLES OFF CACHE BOOL "Don't build png executables")
set(PNG_SHARED OFF CACHE BOOL "Don't build png shared library")
set(PNG_TESTS OFF CACHE BOOL "Don't build png tests")
set(PNG_STATIC ON CACHE BOOL "Build png static library")
set(PNG_TOOLS ON CACHE BOOL "Don't build png tools")
set(SPDLOG_WCHAR_SUPPORT ON CACHE BOOL "Enable wchar support")
set(SPDLOG_USE_STD_FORMAT ON CACHE BOOL "Use std::format instead of fmtlib")
set(SPDLOG_WCHAR_FILENAMES ON CACHE BOOL "Use wchar filenames")
set(SPDLOG_WCHAR_CONSOLE ON CACHE BOOL "Use wchar console")
set(BUILD_RTTR_DYNAMIC OFF CACHE BOOL "Build the dynamic/shared version of RTTR library")
set(BUILD_STATIC ON CACHE BOOL "Build RTTR as static library")
set(BUILD_UNIT_TESTS OFF CACHE BOOL "Don't build the unit tests of RTTR")
set(BUILD_DOCUMENTATION OFF CACHE BOOL "Don't build the documentation of RTTR")
set(BUILD_EXAMPLES OFF CACHE BOOL "Don't build the examples of RTTR")
set(BUILD_WITH_STATIC_RUNTIME_LIBS ON CACHE BOOL "Link against the static runtime libraries of RTTR")
set(BUILD_PACKAGE OFF CACHE BOOL "Disable building the installer for RTTR")
set(BUILD_SHARED_LIBS OFF)
set(ZLIB_BUILD_EXAMPLES OFF CACHE BOOL "Don't build zlib examples")

#configure_file(${msdfgen_DIR}/msdfgenConfig.cmake.in ${msdfgen_DIR}/msdfgenConfig.cmake)
#configure_file(${msdfgen_DIR}/msdfgen-config.h.in ${msdfgen_DIR}/msdfgen-config.h)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Engine/libs/vendor/msdf-atlas-gen/msdfgen/cmake/")
project(AGE)
message(Status " VCPKG_ROOT: " $ENV{VCPKG_ROOT})

add_subdirectory(Engine)
target_include_directories(Engine PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src"
                          )
add_subdirectory(Game)
target_include_directories(Game PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/src"
)

add_subdirectory(Editor)
target_include_directories(Editor PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src"
                          )

