cmake_minimum_required(VERSION 3.0)
# This CMake file was created by Lane Schwartz <dowobeha@gmail.com>

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.18.29.tar.gz"
    SHA1 "ebea5d2fa4aa70de1234b05c4bf1b69705abb1ba"
)

# Define a single cmake project
project(mtplz VERSION 0.1)

option(MTPLZ_BUILD_EXE "Build executables" ON)

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

# Installation {
# (https://github.com/forexample/package-example)

set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

include(CMakePackageConfigHelpers)

# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Use variables:
#   * targets_export_name
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

install(
    DIRECTORY decode lm pt util search
    DESTINATION "${include_install_dir}"
    FILES_MATCHING PATTERN "*.hh"
)

install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)

# }

find_package(Threads REQUIRED)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

# Process subdirectories
add_subdirectory(util)
add_subdirectory(lm)
add_subdirectory(search)
add_subdirectory(pt)
add_subdirectory(decode)
