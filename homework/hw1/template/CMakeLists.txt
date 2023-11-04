cmake_minimum_required (VERSION 3.24)

project ("Simple CMake Template" VERSION 1.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Tell MSVC to build using multiple processes.
# This may speed up compilation time significantly.
# For more information check:
# https://learn.microsoft.com/en-us/cpp/build/reference/mp-build-with-multiple-processes?view=msvc-170
#
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

# Makes it easier to display some useful info
include(CMakePrintHelpers)

# Uncomment the line below, if you want to specify additional
# locations to be searched by find_package and include.
# For example, a local cmake/ direcory within the project, etc.
# list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Display some useful information
cmake_print_variables(CMAKE_MODULE_PATH)
cmake_print_variables(CMAKE_PREFIX_PATH)



################################################################################
#
# Unit testing
#

# Configure the project for testing with CTest/CDash
# Automatically adds the BUILD_TESTING option and sets it to ON
# If BUILD_TESTING is ON, automatically calls enable_testing().
# Check the following resources for more info:
#   https://cmake.org/cmake/help/latest/module/CTest.html
#   https://cmake.org/cmake/help/latest/command/enable_testing.html
#   https://cmake.org/cmake/help/latest/manual/ctest.1.html
include(CTest)


# Make Catch2 available
if(BUILD_TESTING)

  message(STATUS "Make Catch2 available...")

  if(EXISTS ${CMAKE_SOURCE_DIR}/lib/Catch2)

    # If Catch2's repo has been cloned to the /lib directory, use that    
    add_subdirectory(${CMAKE_SOURCE_DIR}/lib/Catch2)
  
  else()

    # Try to either find a local installation of Catch2,
    # or download it from its repository.
    #
    # You can find more information on how FetchContent works and
    # what is the order of locations being searched in these sources:
    #
    # Using Dependencies Guide
    #   https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html#guide:Using%20Dependencies%20Guide
    # FetchContent examples:
    #   https://cmake.org/cmake/help/latest/module/FetchContent.html#fetchcontent-find-package-integration-examples
    # If necessary, set up FETCHCONTENT_TRY_FIND_PACKAGE_MODE. Check:
    #   https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_TRY_FIND_PACKAGE_MODE
    # For Catch2's own documentation on CMake integration check:
    #   https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md
    
    include(FetchContent)

    # FIND_PACKAGE_ARGS makes it so that CMake first tries to find
    # CMake with find_package() and if it is NOT found, it will
    # be retrieved from its repository.
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
        FIND_PACKAGE_ARGS
    )

    FetchContent_MakeAvailable(Catch2)

    # The line below was necessary when Catch2 was obtained with FetchContent,
    # as described here:
    #   https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md)
    # This does not seem to be the case anymore.
    # list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

  endif()

  # Include the Catch module, which provides catch_discover_tests
  include(Catch)

  # Status messages
  cmake_print_variables(Catch2_DIR)
  cmake_print_variables(catch2_SOURCE_DIR)
  cmake_print_variables(Catch2_SOURCE_DIR)
  cmake_print_variables(CMAKE_MODULE_PATH)

endif()



################################################################################
#
# Targets
#

# Add the src/ directory to the include path of all targets
include_directories("src")

# Library for expression processing
add_subdirectory("src/expression-lib")

# Application
add_subdirectory("src/application")

# Unit tests
if(BUILD_TESTING)
  include(Catch)
  add_subdirectory("test")
endif()
