# can-cpp

A C++ library for CAN bus packet handling, including support for higher level protocols CANopen and NMEA 2000.

## Features

- Unpack raw CAN frame byte sequences to `can::Packet` struct
- Convert `can::Packet` to raw CAN frame to be transmitted
- `Bits` class extends `std::bitset` for bit manipulation of CAN payload data
- Convenient size-agnostic endianness conversion with `hton()` and `ntoh()`
- CANopen protocol support
- NMEA 2000 (n2k) protocol support

## Dependencies

- C++20
- CMake 3.16 or later

## Building

### Build the library

Note: add flags to optionally build examples/tests, enable linting.

```bash
mkdir build
cd build
cmake .. -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON -DENABLE_LINTING=ON
make
```

### Running tests

After building with tests enabled:

```bash
# Run all tests via CTest (shows individual test cases)
make test

# Or run CTest directly with verbose output
ctest --verbose

# Run individual test executables
./test/test_can
# ... etc.
```

**Note**: Google Test is automatically downloaded and built as part of the build process, ensuring consistent behavior across all platforms.

### Code Linting and Formatting

This project supports code linting and formatting using [Uncrustify](https://github.com/uncrustify/uncrustify). 

#### Installation

Install Uncrustify on your system:

**macOS:**
```bash
brew install uncrustify
```

**Ubuntu/Debian:**
```bash
sudo apt-get install uncrustify
```

**Other systems:** See the [Uncrustify installation guide](https://github.com/uncrustify/uncrustify).

#### Usage

After building with linting enabled:

```bash
# Check code formatting (non-destructive)
make lint

# Apply formatting fixes automatically
make format
```

### Installation

```bash
sudo make install
```

## Usage

Include the library in your CMake project:

```cmake
find_package(can-cpp REQUIRED)
target_link_libraries(your_target can-cpp::can-cpp)
```
