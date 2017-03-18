cmake_minimum_required (VERSION 2.6)
project (blueshock)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

message("CMAKE_SIZEOF_VOID_P: ${CMAKE_SIZEOF_VOID_P}")
if(CMAKE_SIZEOF_VOID_P MATCHES 8)
	set (ARCH "x64" CACHE STRING "CPU Architecture")
else ()
	set (ARCH "x86" CACHE STRING "CPU Architecture")
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCE_FILES
src/main.cpp
src/Shader.cpp
src/Shader.h
src/GenericShaderProgram.cpp
src/GenericShaderProgram.h
src/Display.cpp
src/Display.h
src/util.h)
include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(blueshock ${SOURCE_FILES})

message("the SDL2 include directory is: ${SDL2_INCLUDE_DIR}")
message("the GLEW include directory is: ${GLEW_INCLUDE_DIR}")

message("the SDL2 library directory is: ${SDL2_LIBRARY}")
message("the GLEW library directory is: ${GLEW_LIBRARY}")

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})

target_link_libraries(blueshock ${SDL2_LIBRARY})
target_link_libraries(blueshock ${GLEW_LIBRARY})
target_link_libraries(blueshock ${OPENGL_gl_LIBRARY})

install (TARGETS blueshock DESTINATION bin)