# Example programs for can-cpp library

# Example: Basic CAN packet usage
add_executable(can_example
  example_can.cpp
)

target_link_libraries(can_example
  PRIVATE
    can-cpp::can-cpp
)

target_include_directories(can_example
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../can/include
)

# Example: N2K (NMEA 2000) packet usage
add_executable(n2k_example
  example_n2k.cpp
)

target_link_libraries(n2k_example
  PRIVATE
    can-cpp::can-cpp
)

target_include_directories(n2k_example
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../can/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../n2k/include
)

# Example: CANopen packet usage
add_executable(canopen_example
  example_canopen.cpp
)

target_link_libraries(canopen_example
  PRIVATE
    can-cpp::can-cpp
)

target_include_directories(canopen_example
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../can/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../canopen/include
)
