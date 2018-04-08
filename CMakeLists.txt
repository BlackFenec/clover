cmake_minimum_required(VERSION 2.8.2)

set(PROJECT_NAME clover)
project(${PROJECT_NAME})

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

set(CMAKE_CXX_STANDARD 11)

add_library(clover_lib ${SRC_FILES})

option(BUILD_TESTS "Build all tests." OFF)

if (BUILD_TESTS)
	add_subdirectory(libraries/gtest-1.8.0)
	enable_testing()

	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	if (CMAKE_VERSION VERSION_LESS 2.8.11)
		include_directories(BEFORE SYSTEM "${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")
	else()
		target_include_directories(gmock_main SYSTEM BEFORE INTERFACE "${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")
	endif()

	add_executable(ctest ${TEST_SRC_FILES})

	target_link_libraries(ctest gmock_main)
	target_link_libraries(ctest clover_lib)

	add_test(UnitTests ctest)

	set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/.travis/cmake)

	if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
		include(CodeCoverage)
		setup_target_for_coverage(${PROJECT_NAME}_coverage runUnitTests coverage)

		SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
		SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
	endif()

endif()