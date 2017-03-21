cmake_minimum_required (VERSION 2.6)
project (blueshock)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set (SDL2_LOCATION "NOT_FOUND" CACHE STRING "The root directory of SDL2")
set (GLEW_LOCATION "NOT_FOUND" CACHE STRING "The root directory of GLEW")
set (ASSIMP_LOCATION "NOT_FOUND" CACHE STRING "The root directory of assimp")

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

file(GLOB_RECURSE SOURCE_FILES src/* include/*)

add_executable(blueshock ${SOURCE_FILES})

add_custom_target(copy_resources ALL
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res
	DEPENDS ${blueshock})

message("the SDL2 include directory is: ${SDL2_INCLUDE_DIR}")
message("the GLEW include directory is: ${GLEW_INCLUDE_DIR}")
message("the assimp include directory is: ${ASSIMP_INCLUDE_DIR}")

message("the SDL2 library directory is: ${SDL2_LIBRARY}")
message("the GLEW library directory is: ${GLEW_LIBRARY}")
message("the assimp library directory is: ${ASSIMP_LIBRARY}")

include_directories(
${PROJECT_SOURCE_DIR}/include
${PROJECT_SOURCE_DIR}/third_party
${ASSIMP_INCLUDE_DIR}
${GLEW_INCLUDE_DIR}
${SDL2_INCLUDE_DIR})

target_link_libraries(blueshock ${SDL2_LIBRARY})
target_link_libraries(blueshock ${GLEW_LIBRARY})
target_link_libraries(blueshock ${OPENGL_gl_LIBRARY})
target_link_libraries(blueshock ${ASSIMP_LIBRARY})

install (TARGETS blueshock DESTINATION bin)