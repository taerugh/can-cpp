cmake_minimum_required(VERSION 3.16)

project(can-cpp 
  VERSION 1.0.0
  DESCRIPTION "C++ CAN bus library"
  LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the library target
add_library(can-cpp
  # Source files
  src/can/packet.cpp
  src/lib/byte_manip.cpp
  src/canopen/canopen.cpp
  src/n2k/n2k.cpp
  
  # Header files (for IDE support)
  include/can-cpp/can/frame.hpp
  include/can-cpp/can/packet.hpp
  include/can-cpp/lib/bits.hpp
  include/can-cpp/lib/byte_manip.hpp
  include/can-cpp/canopen/canopen.hpp
  include/can-cpp/n2k/n2k.hpp
)

# Set target properties
target_include_directories(can-cpp
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Compiler-specific options
target_compile_features(can-cpp PUBLIC cxx_std_20)

# Add compiler warnings
if(MSVC)
  target_compile_options(can-cpp PRIVATE /W4)
else()
  target_compile_options(can-cpp PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Create alias target for easier consumption
add_library(can-cpp::can-cpp ALIAS can-cpp)

# Install configuration
include(GNUInstallDirs)

# Install the library
install(TARGETS can-cpp
  EXPORT can-cpp-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install headers
install(DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.hpp"
)

# Install CMake config files
install(EXPORT can-cpp-targets
  FILE can-cpp-targets.cmake
  NAMESPACE can-cpp::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/can-cpp
)

# Generate config files
include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/can-cpp-config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/can-cpp-config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/can-cpp
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/can-cpp-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/can-cpp-config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/can-cpp-config-version.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/can-cpp
)

# Optional: Build examples/demos
option(BUILD_EXAMPLES "Build example programs" OFF)
if(BUILD_EXAMPLES)
  add_subdirectory(example)
endif()

# Optional: Build tests
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

# Optional: Enable linting with Uncrustify
option(ENABLE_LINTING "Enable code linting with Uncrustify" OFF)
if(ENABLE_LINTING)
  find_program(UNCRUSTIFY_EXECUTABLE uncrustify)
  if(UNCRUSTIFY_EXECUTABLE)
    # Get all source files for linting
    file(GLOB_RECURSE ALL_SOURCE_FILES
      "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/example/*.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp"
    )
    
    # Create lint target
    add_custom_target(lint
      COMMAND ${UNCRUSTIFY_EXECUTABLE}
        --check
        --config ${CMAKE_CURRENT_SOURCE_DIR}/.uncrustify.cfg
        ${ALL_SOURCE_FILES}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "Running Uncrustify linter"
    )
    
    # Create format target to apply fixes
    add_custom_target(format
      COMMAND ${UNCRUSTIFY_EXECUTABLE}
        --replace
        --no-backup
        --config ${CMAKE_CURRENT_SOURCE_DIR}/.uncrustify.cfg
        ${ALL_SOURCE_FILES}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "Applying Uncrustify formatting"
    )
    
    message(STATUS "Uncrustify found: ${UNCRUSTIFY_EXECUTABLE}")
    message(STATUS "Use 'make lint' to check formatting, 'make format' to apply fixes")
  else()
    message(WARNING "Uncrustify not found. Please install uncrustify to enable linting.")
  endif()
endif()
