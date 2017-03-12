cmake_minimum_required (VERSION 2.6)
project (blueshock)

set(CMAKE_CXX_STANDARD 14)
include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp)

add_executable(blueshock ${SOURCE_FILES})
target_link_libraries(blueshock ${SDL2_LIBRARY})

install (TARGETS blueshock DESTINATION bin)