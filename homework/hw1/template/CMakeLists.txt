cmake_minimum_required (VERSION 3.13)

project ("Homework 1: Expression processing")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HOW_TO_MAKE_CATCH2_AVAILABLE FETCH_CONTENT CACHE STRING "Can be one of FETCH_CONTENT, FIND_PACKAGE or DIRECTORY")

# Make the src/ directory available to all targets
include_directories(unit-tests PRIVATE "src/")

#
# Tell MSVC to build using multiple processes.
# This may speed up compilation time significantly.
# For more information check:
# https://learn.microsoft.com/en-us/cpp/build/reference/mp-build-with-multiple-processes?view=msvc-170
#
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

# Make Catch2 available
if(HOW_TO_MAKE_CATCH2_AVAILABLE STREQUAL "FETCH_CONTENT")

  message(STATUS "Catch2 will be retrieved with FetchContent")
  
  # Automatically retrieve Catch2 with FetchContent. For more information check
  # https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md
  Include(FetchContent)

  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0)

  FetchContent_MakeAvailable(Catch2)

  list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

elseif(HOW_TO_MAKE_CATCH2_AVAILABLE STREQUAL "FIND_PACKAGE")

  message(STATUS "Catch2 will be made available with find_package")
  find_package(Catch2 3 REQUIRED)
  
elseif(HOW_TO_MAKE_CATCH2_AVAILABLE STREQUAL "DIRECTORY")
  
  message(STATUS "Catch2 will be loaded from ./lib/Catch2")
  add_subdirectory(lib/Catch2)

else()

  message(FATAL_ERROR "HOW_TO_MAKE_CATCH2_AVAILABLE is set to an incorrect value!")

endif()

# Configure a project for testing with CTest/CDash
# Automatically adds the BUILD_TESTING option and sets it to ON
# If BUILD_TESTING is ON, automatically calls enable_testing()
# Check the following resources for more info:
# https://cmake.org/cmake/help/latest/module/CTest.html
# https://cmake.org/cmake/help/latest/command/enable_testing.html
# https://cmake.org/cmake/help/latest/manual/ctest.1.html
include(CTest)

# Library for expression processing
add_subdirectory("src/expression-lib")

# Application
add_subdirectory("src/application")

# Unit tests
if(BUILD_TESTING)
  include(Catch)
  add_subdirectory("test")
endif()
