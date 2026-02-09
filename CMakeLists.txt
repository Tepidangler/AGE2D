cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CONFIGURATION_TYPES Debug;Release;Dist)
set(SPDLOG_USE_STD_FORMAT ON CACHE BOOL "Use std::format instead of fmtlib")
#if(WIN32)
#    set(COVERAGE_FLAGS "/fsanitize=address /MTd")
#elseif(UNIX)
#    set(COVERAGE_FLAGS "-fsanitize=address -fsanitize=undefined -Wall -Wconversion")
#endif()
#set(CMAKE_CXX_FLAGS "${COVERAGE_FLAGS}")

project(AGE LANGUAGES CXX)
message(Status " VCPKG_ROOT: " $ENV{VCPKG_ROOT})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(Dependencies.cmake)

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

