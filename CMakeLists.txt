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

  src/input/*.cpp
  src/input/*.h

  src/sound/*.cpp
  src/sound/*.h

  src/*.h
  src/*.cpp
  )

## Set version and info
set(simple_major_version 0)
set(simple_minor_version 2)
set(simple_patch_version 2)

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
  deps/stb_vorbis.c
  )

#freetype
add_subdirectory(deps/freetype)
set(FREETYPE_INCLUDE_DIR deps/freetype/include)
set(FREETYPE_LIBRARIES freetype)
include_directories(deps/freetype/include)

#openal
add_subdirectory(deps/openal)
set(OPENAL_INCLUDE_DIR deps/openal/include)
set(OPENAL_LIBRARIES "${OPENAL_LIBRARY}")

#lua
add_subdirectory(deps/lua)
set(LUA_INCLUDE_DIR deps/lua/ ${CMAKE_BINARY_DIR}/deps/lua/)
SET(LUA_LIBRARIES lua)

if(APPLE)
  target_link_libraries(simple glfw
    ${GLFW_LIBRARIES} openal ${OPENAL_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES})
endif()

if(UNIX)
  target_link_libraries(simple dl glfw
    ${GLFW_LIBRARIES} openal ${OPENAL_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES})
endif()

IF(WIN32)
  FIND_PACKAGE(OpenGL REQUIRED)

  LINK_DIRECTORIES("$ENV{DXSDK_DIR}/Lib/$ENV{PROCESSOR_ARCHITECTURE}")
  SET(SDL_BUILDING_LIBRARY ON)
  SET(USE_NETWORKING FALSE)

  IF(SSE2_TRUE)
    SET(SSE_FLAG /arch:SSE2)
  ELSEIF(SSE_TRUE)
    SET(SSE_FLAG /arch:SSE)
  ENDIF()

  SET(flag_var "/MD")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc /nologo /GR /FC /DWIN32 /D_MBCS")
  SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /Z7 /W4 /Od /MDd /D_DEBUG /D__Debug__")
  SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /W1 /O2 /Ot /MD /DNDEBUG /fp:fast ${SSE_FLAG}")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  /EHsc /nologo /GR /FC /DWIN32 /D_MBCS")
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7 /W4 /Od /MDd /D_DEBUG /D__Debug__")
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W1 /O2 /Ot /MD /DNDEBUG /fp:fast ${SSE_FLAG}")


  SET(FREETYPE_LIBRARY "freetype")
  SET(GLFW_LIBRARY "glfw")
  SET(OPENAL_LIBRARY "OpenAL32")
ENDIF(WIN32)

if(WIN32)
  target_link_libraries(simple ws2_32.lib glfw
    ${GLFW_LIBRARIES} openal ${OPENAL_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES})
endif()
