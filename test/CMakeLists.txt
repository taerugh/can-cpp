# Test configuration for can-cpp library

include(FetchContent)

# Download and build Google Test
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG    v1.17.0  # Use a specific stable version
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make googletest available
FetchContent_MakeAvailable(googletest)

# Create test executables
add_executable(test_can
  test_can.cpp
)

add_executable(test_bits
  test_bits.cpp
)

add_executable(test_canopen
  test_canopen.cpp
)

add_executable(test_n2k
  test_n2k.cpp
)

# Link with the fetched Google Test
target_link_libraries(test_can
  PRIVATE
    can-cpp::can-cpp
    gtest_main
    gtest
)

target_link_libraries(test_bits
  PRIVATE
    can-cpp::can-cpp
    gtest_main
    gtest
)

target_link_libraries(test_canopen
  PRIVATE
    can-cpp::can-cpp
    gtest_main
    gtest
)

target_link_libraries(test_n2k
  PRIVATE
    can-cpp::can-cpp
    gtest_main
    gtest
)

# Enable CTest and add tests
enable_testing()
include(GoogleTest)

# Discover tests automatically
gtest_discover_tests(test_can)
gtest_discover_tests(test_bits)
gtest_discover_tests(test_canopen)
gtest_discover_tests(test_n2k)
