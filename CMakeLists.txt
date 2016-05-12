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
set(simple_patch_version 3)

set(simple_package "simple")
set(simple_creator "Muresan Vlad")
set(simple_version "${simple_major_version}.${simple_minor_version}.${simple_patch_version}")
set(simple_copyright "Copyright (c) 2015, ${simple_creator}.")

message(STATUS "${simple_package} ${simple_version}")
add_executable(
  simple
  ${SOURCE_FILES}
  deps/stb_image/stb_image.c
  deps/stb_vorbis/stb_vorbis.c
  )

if (APPLE)
  
  SET(MACOSX_RPATH 1)
  # use, i.e. don't skip the full RPATH for the build tree
  SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

  # when building, don't use the install RPATH already
  # (but later on when installing)
  SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

  SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

  # add the automatically determined parts of the RPATH
  # which point to directories outside the build tree to the install RPATH
  SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


  # the RPATH to be used when installing, but only if it's not a system directory
  LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
  IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  ENDIF("${isSystemDir}" STREQUAL "-1")

  FIND_PACKAGE(OpenGL REQUIRED)
  FIND_LIBRARY(COCOA_LIB Cocoa)
  FIND_LIBRARY(CORE_SERVICES_LIB CoreServices)
  FIND_LIBRARY(FOUNDATION_LIB Foundation)
  FIND_LIBRARY(IOKIT_LIB IOKit)
  #SET(MTCL_BUILD_FLAGS "-mmacosx-version-min=10.6")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MTCL_BUILD_FLAGS} -O3 -DOSX")
  SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D__Debug__")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MTCL_BUILD_FLAGS} -O3 -DOSX")
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D__Debug__")
  SET(CMAKE_SHARED_LINKER_FLAGS "-Wl")
  SET(OS_SPECIFIC_LIBRARIES ${COCOA_LIB} ${CORE_SERVICES_LIB} ${FOUNDATION_LIB} ${IOKIT_LIB})
endif()

#GLFW & GLEW & STB_IMAGE
add_subdirectory(deps/glew/)
SET(GLEW_INCLUDE_DIR deps/glew/include/GL/)

add_subdirectory(deps/glfw)
include_directories(deps/glfw/include)
include_directories(deps/stb_image)
include_directories(deps/stb_vorbis)


#freetype
add_subdirectory(deps/freetype)
set(FREETYPE_INCLUDE_DIR deps/freetype/include)

#openal
add_subdirectory(deps/openal)
set(OPENAL_INCLUDE_DIR deps/openal/include/)

#lua
add_subdirectory(deps/lua)
set(LUA_INCLUDE_DIR deps/lua/)
SET(LUA_LIBRARIES lua)

add_definitions(-DAL_LIBTYPE_STATIC)
add_definitions(-DGLEW_STATIC)
add_definitions(-DFT2_BUILD_LIBRARY)

SET(FREETYPE_LIBRARIES freetype)
include_directories(deps/freetype/include)

SET(GLEW_LIBRARIES libglew_static)

if(MINGW)
SET(OPENAL_LIBRARIES OpenAL32)
endif()
if(UNIX)
SET(OPENAL_LIBRARIES openal)
endif()


if(APPLE)
  target_link_libraries(simple glfw
    ${GLFW_LIBRARIES} 
        ${OPENGL_LIBRARIES} ${OPENAL_LIBRARIES}
        ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES})
endif()

if(UNIX)
  target_link_libraries(simple dl glfw
    ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} openal ${OPENAL_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES})
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
    ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} openal ${OPENAL_LIBRARIES} ${FREETYPE_LIBRARIES} ${LUA_LIBRARIES})
endif()
