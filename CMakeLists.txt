cmake_minimum_required(VERSION 3.0)
# This CMake file was created by Lane Schwartz <dowobeha@gmail.com>

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.18.16.tar.gz"
    SHA1 "6cbca2b0e7605ad8ea22ee3527850996436f71b8"
)

# Define a single cmake project
project(kenlm)

# Tell cmake that we want unit tests to be compiled
include(CTest)
enable_testing()

# Add our CMake helper functions
include(cmake/KenLMFunctions.cmake)

if(MSVC)
  set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /w34716")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w34716")
endif()

# And our helper modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

# We need boost
hunter_add_package(Boost COMPONENTS system thread program_options test)
find_package(Boost CONFIG REQUIRED COMPONENTS
  program_options
  system
  thread
  unit_test_framework
)

set(
    Boost_LIBRARIES
    Boost::system
    Boost::thread
    Boost::program_options
    Boost::unit_test_framework
)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

# Process subdirectories
add_subdirectory(util)
add_subdirectory(lm)
add_subdirectory(search)
add_subdirectory(pt)
add_subdirectory(decode)
