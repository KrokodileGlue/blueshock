# this module uses ASSIMP_LOCATION and defines ASSIMP_INCLUDE_DIR and ASSIMP_LIBRARY

if(WIN32)
	# win32 stuff
	if(MSVC12)
		set(ASSIMP_MSVC_VERSION "vc120")
	elseif(MSVC14)
		set(ASSIMP_MSVC_VERSION "vc140")
	endif()

	set (
		ASSIMP_INCLUDE_DIR ${ASSIMP_LOCATION}/include
	)

	find_library(
		ASSIMP_LIBRARY
		NAMES assimp-${ASSIMP_MSVC_VERSION}-mt.lib
		PATHS # TODO: look in places other than just this
			${ASSIMP_LOCATION}/build/code/Debug
	)
else () # ASSume we're on some Linux distro
	find_path (
		ASSIMP_INCLUDE_DIR
		NAMES postprocess.h scene.h postprocess.h scene.h version.h config.h cimport.h
		PATHS /usr/local/include/assimp
	)
	message("ASSIMP_INCLUDE_DIR: ${ASSIMP_INCLUDE_DIR}")

	find_library (
		ASSIMP_LIBRARY
		NAMES assimp
		PATHS /usr/local/lib
		)
	message("ASSIMP_LIBRARY: ${ASSIMP_LIBRARY}")
endif ()

if (ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
	SET(assimp_FOUND TRUE)
endif ()

if (assimp_FOUND)
	message(STATUS "Found asset importer library: ${ASSIMP_LIBRARY}")
else ()
	if (assimp_FIND_REQUIRED)
		message (FATAL_ERROR "Could not find asset importer library")
	endif ()
endif ()
