cmake_minimum_required (VERSION 2.6)
project (blueshock)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

set (SDL2_LOCATION "NOT_FOUND" CACHE STRING "The root directory of SDL2")
set (GLEW_LOCATION "NOT_FOUND" CACHE STRING "The root directory of GLEW")
set (ASSIMP_LOCATION "NOT_FOUND" CACHE STRING "The root directory of assimp")
set (LUA_LOCATION "NOT_FOUND" CACHE STRING "The root directory of lua")

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
find_package(lua REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/* include/*)

add_executable(blueshock ${SOURCE_FILES})

add_custom_target(copy_resources ALL
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res
	DEPENDS ${blueshock})
	
# http://stackoverflow.com/a/33813154
	file(
	    GLOB_RECURSE _source_list 
	    LIST_DIRECTORIES false
	    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	    "${CMAKE_CURRENT_SOURCE_DIR}/*.c*"
	    "${CMAKE_CURRENT_SOURCE_DIR}/*.h*"
	)

	add_library(blueshock_source_files ${_source_list})

	foreach(_source IN ITEMS ${_source_list})
	    get_filename_component(_source_path "${_source}" PATH)
	    string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
	    source_group("${_source_path_msvc}" FILES "${_source}")
	endforeach()

message("the SDL2 include directory is: ${SDL2_INCLUDE_DIR}")
message("the GLEW include directory is: ${GLEW_INCLUDE_DIR}")
message("the assimp include directory is: ${ASSIMP_INCLUDE_DIR}")
message("the lua include directory is: ${LUA_INCLUDE_DIR}")

message("the SDL2 library directory is: ${SDL2_LIBRARY}")
message("the GLEW library directory is: ${GLEW_LIBRARY}")
message("the assimp library directory is: ${ASSIMP_LIBRARY}")
message("the lua library directory is: ${LUA_LIBRARIES}")

include_directories(
${PROJECT_SOURCE_DIR}/include
${PROJECT_SOURCE_DIR}/third_party
${ASSIMP_INCLUDE_DIR}
${GLEW_INCLUDE_DIR}
${SDL2_INCLUDE_DIR}
${LUA_INCLUDE_DIR})

target_link_libraries(blueshock ${SDL2_LIBRARY})
target_link_libraries(blueshock ${GLEW_LIBRARY})
target_link_libraries(blueshock ${OPENGL_gl_LIBRARY})
target_link_libraries(blueshock ${ASSIMP_LIBRARY})
target_link_libraries(blueshock ${LUA_LIBRARIES})

install (TARGETS blueshock DESTINATION /usr/local/bin)
