# ~ LibMath
cmake_minimum_required(VERSION 3.24 FATAL_ERROR) # PATH_EQUAL



if(${CMAKE_CURRENT_SOURCE_DIR} PATH_EQUAL ${CMAKE_SOURCE_DIR})
	# Create project if build directly
	set(CMAKE_CXX_STANDARD 23)
	set(CMAKE_CXX_STANDARD_REQUIRED True)

	get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
	project(${PROJECT_NAME} LANGUAGES CXX)

	set(IS_MASTER_PROJECT ON)
	
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set(DEPENDENCY_FOLDER Dependency)
else()
	# Default to not generating unit test if build from add_subdirectory() or FetchContent_MakeAvailable()
	set(IS_MASTER_PROJECT OFF)
endif()


option(LIBMATH_UNIT_TEST "Generate unit test project" ${IS_MASTER_PROJECT})

add_subdirectory(LibMath)


if (${LIBMATH_UNIT_TEST})
	add_subdirectory(UnitTest)

	if(MSVC)
		set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT UnitTest)
	endif()
endif()
