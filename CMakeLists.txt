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

# Define the library targets by adding subdirectories
add_subdirectory(can)
add_subdirectory(canopen)
add_subdirectory(n2k)

# Create a combined library target for backward compatibility
add_library(can-cpp INTERFACE)
target_link_libraries(can-cpp INTERFACE can canopen n2k)

# Create alias target for easier consumption
add_library(can-cpp::can-cpp ALIAS can-cpp)

# Install configuration
include(GNUInstallDirs)

# Install the libraries
install(TARGETS can canopen n2k can-cpp
  EXPORT can-cpp-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install headers from each library
install(DIRECTORY can/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.hpp"
)
install(DIRECTORY canopen/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.hpp"
)
install(DIRECTORY n2k/include/
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
      "${CMAKE_CURRENT_SOURCE_DIR}/can/src/*.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/can/include/*.hpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/canopen/src/*.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/canopen/include/*.hpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/n2k/src/*.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/n2k/include/*.hpp"
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
