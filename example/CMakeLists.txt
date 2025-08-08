# Example programs for can-cpp library

# Example: Basic CAN packet usage
add_executable(can_example
  can_example.cpp
)

target_link_libraries(can_example
  PRIVATE
    can-cpp::can-cpp
)

# Example: N2K (NMEA 2000) packet usage
add_executable(n2k_example
  n2k_example.cpp
)

target_link_libraries(n2k_example
  PRIVATE
    can-cpp::can-cpp
)

# Example: CANopen packet usage
add_executable(canopen_example
  canopen_example.cpp
)

target_link_libraries(canopen_example
  PRIVATE
    can-cpp::can-cpp
)
