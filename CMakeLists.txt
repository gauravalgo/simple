cmake_minimum_required(VERSION 2.8)

project(simple)

FILE(
GLOB SOURCE_FILES
src/maths/*.h
src/maths/*.cpp
src/graphics/*.cpp
src/graphics/*.c
src/graphics/*.h
src/window/*.cpp
src/window/*.h
src/*.h
src/*.cpp
)

## Set version and info
SET(simple_major_version 0)
SET(simple_minor_version 1)
SET(simple_patch_version 0)

SET(simple_package "simple")
SET(simple_creator "Muresan Vlad")
SET(simple_version "${simple_major_version}.${simple_minor_version}.${simple_patch_version}")
SET(simple_copyright "Copyright (c) 2015, ${simple_creator}.")

MESSAGE(STATUS "${simple_package} ${simple_version}")

#GLFW & GLEW & STB_IMAGE & GLM
add_subdirectory(deps/glfw)
include_directories(deps/glew/include)
include_directories(deps/glfw/include)
include_directories(deps/stb_image)

add_executable(
  simple
  ${SOURCE_FILES}
  deps/glew/src/glew.c
  deps/stb_image/stb_image.c
)

#SDL2
#Autofind?
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

#add_subdirectory(deps/sdl2)
#INCLUDE_DIRECTORIES(deps/sdl2/include)

if(APPLE)
  target_link_libraries(simple ${GLM} ${SDL2_LIBRARIES} glfw
    ${GLFW_LIBRARIES})
endif()

if(UNIX)
  target_link_libraries(simple dl glfw
    ${GLFW_LIBRARIES} ${GLM} ${SDL2_LIBRARIES})
endif()

if(MINGW)
  target_link_libraries(simple ws2_32.lib glfw
    ${GLFW_LIBRARIES} ${SDL2_LIBRARIES})
endif()
