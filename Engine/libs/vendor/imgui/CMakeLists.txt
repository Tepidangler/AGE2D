cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/)
set(BACKENDS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/backends/)
set(BACKENDS ${BACKENDS_DIR}imgui_impl_glfw.h
             ${BACKENDS_DIR}imgui_impl_glfw.cpp
             ${BACKENDS_DIR}imgui_impl_opengl3.h
             ${BACKENDS_DIR}imgui_impl_opengl3.cpp
)
include_directories(BEFORE 
                    ${CMAKE_SOURCE_DIR}/Engine/src/AGE
                    "${MAIN_SRC}"
                    ${CMAKE_SOURCE_DIR}/Engine/src/AGE/Core/Public
                    "${INC_GLFW}" 
                    "${INC_SPDLOG}"
)

if(WIN32)
    add_compile_definitions(AG_PLATFORM_WINDOWS
                            UNICODE
                            FMT_UNICODE=0
                            )
elseif(APPLE)
    add_compile_definitions(AG_PLATFORM_MACOS
                            )
elseif(UNIX)
    add_compile_definitions(AG_PLATFORM_LINUX
                            )
endif()

project (ImGUI)

message(Status " Detected System Architecture: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
if(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "x86_64" OR ${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
add_compile_definitions(_AMD64_)
elseif(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "IA64") 
add_compile_definitions(_IA64_)
endif()

message(Status " Using STD Format in SPDLOG?: " ${SPDLOG_USE_STD_FORMAT})

file(GLOB HDR_FILES 
                    ${MAIN_SRC}
					*.h)

file(GLOB CPP_FILES 
                    ${MAIN_SRC}
					*.cpp)
message(STATUS "Backend Files: ${BACKENDS}")
message(STATUS "HDR Files: ${HDR_FILES}")
message(STATUS "CPP Files: ${CPP_FILES}")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Header Files" FILES ${HDR_FILES} )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source Files" FILES ${CPP_FILES})
add_library(ImGUI STATIC ${CPP_FILES} ${HDR_FILES} ${BACKENDS})