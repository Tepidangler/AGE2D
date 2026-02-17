cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)

project(FMOD)


add_library(FMOD STATIC
        ${FMOD_INSTALL_PATH}/api/core/inc/fmod_codec.h
        ${FMOD_INSTALL_PATH}/api/core/inc/fmod_common.h
        ${FMOD_INSTALL_PATH}/api/core/inc/fmod_dsp_effects.h
        ${FMOD_INSTALL_PATH}/api/core/inc/fmod_dsp.h
        ${FMOD_INSTALL_PATH}/api/core/inc/fmod_output.h
        ${FMOD_INSTALL_PATH}/api/core/inc/fmod_errors.h
        ${FMOD_INSTALL_PATH}/api/core/inc/fmod.h
        ${FMOD_INSTALL_PATH}/api/core/inc/fmod.hpp
        ${FMOD_INSTALL_PATH}/api/fsbank/inc/fsbank.h
        ${FMOD_INSTALL_PATH}/api/fsbank/inc/fsbank_errors.h
        ${FMOD_INSTALL_PATH}/api/studio/inc/fmod_studio.h
        ${FMOD_INSTALL_PATH}/api/studio/inc/fmod_studio.hpp
        ${FMOD_INSTALL_PATH}/api/studio/inc/fmod_studio_common.h
)

link_directories(BEFORE
        ${FMOD_INSTALL_PATH}/api/core/lib/x64
        ${FMOD_INSTALL_PATH}/api/studio/lib/x64
)
find_library(FMOD_CORE
    fmod_vc.lib
)
find_library(FMOD_STUDIO
    fmod_studio_vc.lib
)
target_link_libraries(FMOD PUBLIC
        FMOD_CORE
        FMOD_STUDIO
)