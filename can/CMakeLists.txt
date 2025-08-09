# CAN Library
add_library(can
  src/packet.cpp
  src/byte_manip.cpp
)

target_include_directories(can
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(can PUBLIC cxx_std_20)

# Add compiler warnings
if(MSVC)
  target_compile_options(can PRIVATE /W4)
else()
  target_compile_options(can PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Create alias target
add_library(can-cpp::can ALIAS can)
