cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CONFIGURATION_TYPES Debug;RelWithDebInfo;MinSizeRel)
option(BUILD_WITH_FMOD "Build with FMOD Audio Engine" OFF)
option(BUILD_WITH_WWISE "Build with Wwise Audio Engine" OFF)
set(SPDLOG_USE_STD_FORMAT ON CACHE BOOL "Use std::format instead of fmtlib")
if(WIN32)
    message(Status " VCPKG_ROOT: " $ENV{VCPKG_ROOT})
    set(YAML_MSVC_SHARED_RT OFF CACHE BOOL "Don't use /MD || Don't use /MT")
    set(GLFW_BUILD_WIN32 ON CACHE BOOL "Build for Windows")
    set(VCPKG_TARGET_TRIPLET x64-windows-static CACHE STRING "Vcpkg target triplet")
elseif(UNIX)
    set(GLFW_BUILD_X11  ON CACHE BOOL "Build for Unix")
elseif(APPLE)
    set(GLFW_BUILD_COCOA ON CACHE BOOL "Build for MacOS")
endif()

project(AGE LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(Dependencies.cmake)

add_subdirectory(Engine)

add_subdirectory(Game)

add_subdirectory(Editor)

