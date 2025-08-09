# CANopen Library
add_library(canopen
  src/canopen.cpp
)

target_include_directories(canopen
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../can/include
)

target_compile_features(canopen PUBLIC cxx_std_20)

# Add compiler warnings
if(MSVC)
  target_compile_options(canopen PRIVATE /W4)
else()
  target_compile_options(canopen PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Link to CAN library
target_link_libraries(canopen PUBLIC can)

# Create alias target
add_library(can-cpp::canopen ALIAS canopen)
