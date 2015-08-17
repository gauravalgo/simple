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

src/utils/*.cpp
src/utils/*.h

src/*.h
src/*.cpp
)

## Set version and info
set(simple_major_version 0)
set(simple_minor_version 1)
set(simple_patch_version 0)

set(simple_package "simple")
set(simple_creator "Muresan Vlad")
set(simple_version "${simple_major_version}.${simple_minor_version}.${simple_patch_version}")
set(simple_copyright "Copyright (c) 2015, ${simple_creator}.")

message(STATUS "${simple_package} ${simple_version}")

#GLFW & GLEW & STB_IMAGE 
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
#INCLUDE(FindPkgConfig)
#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
#INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
add_subdirectory(deps/sdl2)
set(SDL2_INCLUDE_DIR deps/sdl2/include)
include_directories(deps/sdl2/include)

#freetype
add_subdirectory(deps/freetype)
set(FREETYPE_INCLUDE_DIR deps/freetype/include)
set(FREETYPE_LIBRARIES freetype)
include_directories(deps/freetype/include)

if(APPLE)
  target_link_libraries(simple ${SDL2_LIBRARIES} glfw
    ${GLFW_LIBRARIES} ${FREETYPE_LIBRARIES})
endif()

if(UNIX)
  target_link_libraries(simple dl glfw
    ${GLFW_LIBRARIES} ${FREETYPE_LIBRARIES} ${SDL2_LIBRARIES})
endif()

if(MINGW)
  target_link_libraries(simple ws2_32.lib glfw
    ${GLFW_LIBRARIES} ${FREETYPE_LIBRARIES} ${SDL2_LIBRARIES})
endif()
