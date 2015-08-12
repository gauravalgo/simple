cmake_minimum_required(VERSION 2.8)

project(simple)

FILE(
GLOB SOURCE_FILES
src/maths/*.h
src/graphics/*.cpp
src/window/*.cpp
src/*.cpp)

add_executable(
  simple
  ${SOURCE_FILES}
  deps/glew/src/glew.c
  deps/lodepng/lodepng.c
)


#GLFW & GLEW
add_subdirectory(deps/glfw)
include_directories(deps/glew/include)
include_directories(deps/glfw/include)
include_directories(deps/lodepng)

#SDL2
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

if(APPLE)
  target_link_libraries(simple ${SDL2_LIBRARIES} glfw
    ${GLFW_LIBRARIES})
endif()

if(UNIX)
  target_link_libraries(simple dl glfw
    ${GLFW_LIBRARIES} ${SDL2_LIBRARIES})
endif()

if(MINGW)
  target_link_libraries(simple ws2_32.lib glfw
    ${GLFW_LIBRARIES} ${SDL2_LIBRARIES})
endif()
