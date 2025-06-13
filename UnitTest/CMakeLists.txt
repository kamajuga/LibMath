# ~ LibMath/UnitTest
get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

include(FetchContent)


# ~ Catch2
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
	GIT_TAG         v3.7.1 # or a later release
	GIT_SHALLOW		ON
)

set(CATCH_INSTALL_DOCS OFF CACHE BOOL "Install documentation alongside library")
set(CATCH_INSTALL_EXTRAS OFF CACHE BOOL "Install extras (CMake scripts, debugger helpers) alongside library")

set(OLD_FOLDER ${CMAKE_FOLDER})
set(OLD_BUILD ${BUILD_SHARED_LIBS})

set(CMAKE_FOLDER ${DEPENDENCY_FOLDER}/Catch2)
set(BUILD_SHARED_LIBS FALSE)

FetchContent_MakeAvailable(Catch2)


# ~ glm
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG			1.0.0
	GIT_SHALLOW		ON
)

set(CMAKE_FOLDER ${DEPENDENCY_FOLDER}/GLM)

FetchContent_MakeAvailable(glm)

set(BUILD_SHARED_LIBS ${OLD_BUILD})
set(CMAKE_FOLDER ${OLD_FOLDER})


# ~ Sources
file(GLOB_RECURSE TARGET_HEADER_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl)
list(FILTER TARGET_HEADER_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE TARGET_SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cc # C with classe
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
list(FILTER TARGET_SOURCE_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE TARGET_EXTRA_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.txt
	${CMAKE_CURRENT_SOURCE_DIR}/*.md)
list(FILTER TARGET_EXTRA_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})

set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES} ${TARGET_EXTRA_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES}) # generate visual studio filter


# ~ Executable
add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Header)

target_link_libraries(${TARGET_NAME} PRIVATE ${LIBMATH_LIBRARY})
target_link_libraries(${TARGET_NAME} PRIVATE Catch2::Catch2)
target_link_libraries(${TARGET_NAME} PRIVATE glm::glm)

if(MSVC)
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX /Za)
	# /Za disable "compiler language extension" (https://github.com/g-truc/glm/blob/master/doc/manual.pdf page 44)

	target_link_options(${TARGET_NAME} PRIVATE /FORCE:UNRESOLVED)
	# /FORCE:UNRESOLVED disable "compiler LNK2019: unresolved external symbol"
else()
	message("not using MSVC")
endif()

# ??? auto run all test on cmake build ??? # todo test
#list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
#include(CTest)
#include(Catch)
#catch_discover_tests(${TARGET_NAME})
