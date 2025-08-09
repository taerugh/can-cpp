# N2K Library
add_library(n2k
  src/n2k.cpp
)

target_include_directories(n2k
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../can/include
)

target_compile_features(n2k PUBLIC cxx_std_20)

# Add compiler warnings
if(MSVC)
  target_compile_options(n2k PRIVATE /W4)
else()
  target_compile_options(n2k PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Link to CAN library
target_link_libraries(n2k PUBLIC can)

# Create alias target
add_library(can-cpp::n2k ALIAS n2k)
