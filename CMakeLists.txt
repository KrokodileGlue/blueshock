cmake_minimum_required (VERSION 2.6)
project (blueshock)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCE_FILES src/main.cpp)
include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(blueshock ${SOURCE_FILES})

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})

target_link_libraries(blueshock ${SDL2_LIBRARY})
target_link_libraries(blueshock ${GLEW_LIBRARIES})
target_link_libraries(blueshock ${OPENGL_gl_LIBRARY})

install (TARGETS blueshock DESTINATION bin)