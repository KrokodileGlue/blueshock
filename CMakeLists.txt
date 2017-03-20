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
find_package(assimp REQUIRED)

set(SOURCE_FILES
src/main.cpp
src/render/Shader.cpp
src/render/Shader.h
src/render/ShaderProgram.cpp
src/render/ShaderProgram.h
src/render/Display.cpp
src/render/Display.h
src/render/Camera.cpp
src/render/Camera.h
src/render/Model.cpp
src/render/Model.h
src/render/Renderer.cpp
src/render/Renderer.h
src/render/Mesh.cpp
src/render/Mesh.h
src/util.cpp
src/util.h
src/Log.cpp
src/Log.h
src/Input.cpp
src/Input.h)
include_directories(
${PROJECT_SOURCE_DIR}/src
${PROJECT_SOURCE_DIR}/src/render
${PROJECT_SOURCE_DIR}/third_party/glm
${PROJECT_SOURCE_DIR}/third_party/glm/gtc
${PROJECT_SOURCE_DIR}/third_party/glm/gtx
${ASSIMP_INCLUDE_DIR})

add_executable(blueshock ${SOURCE_FILES})

add_custom_target(copy_resources ALL
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res
	DEPENDS ${blueshock})

message("the SDL2 include directory is: ${SDL2_INCLUDE_DIR}")
message("the GLEW include directory is: ${GLEW_INCLUDE_DIR}")

message("the SDL2 library directory is: ${SDL2_LIBRARY}")
message("the GLEW library directory is: ${GLEW_LIBRARY}")

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})

target_link_libraries(blueshock ${SDL2_LIBRARY})
target_link_libraries(blueshock ${GLEW_LIBRARY})
target_link_libraries(blueshock ${OPENGL_gl_LIBRARY})
target_link_libraries(blueshock ${ASSIMP_LIBRARY_DIR})

install (TARGETS blueshock DESTINATION bin)