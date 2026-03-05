cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CONFIGURATION_TYPES Debug;RelWithDebInfo;MinSizeRel)
set(FMOD_INSTALL_PATH "" CACHE PATH "Path FMod SDK is Installed to")
option(BUILD_WITH_FMOD "Build with FMOD Audio Engine" OFF)
set(WWISE_INSTALL_PATH "" CACHE PATH "Path Wwise SDK is Installed to")
option(BUILD_WITH_WWISE "Build with Wwise Audio Engine" OFF)
set(SPDLOG_USE_STD_FORMAT ON CACHE BOOL "Use std::format instead of fmtlib")
set(MSDF_ATLAS_USE_SKIA OFF CACHE BOOL "Use Skia with msdf-gen-atlas")

option(BUILD_PACKAGE "Build a package for corresponding operating systems" OFF)
if(WIN32)
    message(Status " VCPKG_ROOT: " $ENV{VCPKG_ROOT})
    set(YAML_MSVC_SHARED_RT OFF CACHE BOOL "Don't use /MD || Don't use /MT")
    set(GLFW_BUILD_WIN32 ON CACHE BOOL "Build for Windows")
    set(VCPKG_TARGET_TRIPLET x64-windows-static CACHE STRING "Vcpkg target triplet")
    set(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")
elseif(UNIX)
    set(GLFW_BUILD_X11  ON CACHE BOOL "Build for Unix")
    set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")
elseif(APPLE)
    set(GLFW_BUILD_COCOA ON CACHE BOOL "Build for MacOS")
    set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")
endif()

if(BUILD_PACKAGE)
include(GNUInstallDirs)
include(CPack)
endif()
project(AGE LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



include(Dependencies.cmake)

add_subdirectory(Engine)

add_subdirectory(Game)

add_subdirectory(Editor)


