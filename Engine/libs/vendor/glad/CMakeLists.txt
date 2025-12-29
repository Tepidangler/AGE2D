add_library(glad INTERFACE)

target_include_directories(glad
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_sources(glad
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c>
)

target_link_libraries(glad
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_DL_LIBS}>
)