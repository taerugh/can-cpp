# CAN C++ Library Examples

This directory contains example programs demonstrating the usage of the can-cpp library for different CAN bus protocols.

## Building the Examples

To build the examples, enable the `BUILD_EXAMPLES` option when configuring CMake:

```bash
cd build
cmake -DBUILD_EXAMPLES=ON ..
make
```

The example executables will be built in the `build/example/` directory.

## Available Examples

### 1. can_example
**File:** `can_example.cpp`

Demonstrates basic CAN packet creation, manipulation, and frame conversion using the core CAN functionality.

**Features:**
- Creating CAN packets with custom data
- Converting packets to frames and back
- Basic packet information display

**Run:** `./can_example`

### 2. n2k_example  
**File:** `n2k_example.cpp`

Demonstrates NMEA 2000 (N2K) marine networking protocol usage.

**Features:**
- Creating N2K packets with proper COB-ID encoding
- Using priority, source address, and PGN (Parameter Group Number) fields
- Examples of engine parameters (PGN 127488) and GPS position (PGN 129025)
- COB-ID encoding/decoding demonstration
- N2K packet string formatting

**Run:** `./n2k_example`

### 3. canopen_example
**File:** `canopen_example.cpp`

Demonstrates CANopen industrial networking protocol usage.

**Features:**
- Creating CANopen PDO (Process Data Object) packets
- Using different function codes (TPDO1, TPDO2, RPDO1, RPDO2, etc.)
- SYNC frame usage for synchronization
- COB-ID encoding/decoding for CANopen
- Function code reference display

**Run:** `./canopen_example`

## Protocol Overview

### NMEA 2000 (N2K)
- **Purpose:** Marine and maritime applications
- **COB-ID Structure:** Priority (3 bits) + PGN (18 bits) + Source Address (8 bits)
- **Key Features:** Parameter Group Numbers (PGNs) for different data types
- **Applications:** Engine monitoring, GPS, navigation, marine sensors

### CANopen
- **Purpose:** Industrial automation and control
- **COB-ID Structure:** Function Code (8 bits) + Node ID (7 bits)
- **Key Features:** PDOs for real-time data, SYNC for synchronization
- **Applications:** Motion control, robotics, industrial sensors and actuators

### Basic CAN
- **Purpose:** General-purpose CAN bus communication
- **COB-ID Structure:** User-defined 11-bit or 29-bit identifier
- **Key Features:** Flexible packet structure, frame conversion
- **Applications:** Automotive, general embedded systems

## Example Output

Each example produces detailed output showing:
- Packet parameters (size, type, timestamp, etc.)
- Protocol-specific information (PGN, function codes, etc.)
- COB-ID analysis and decoding
- Raw data representation
- Frame format conversion

## Next Steps

These examples provide a foundation for:
- Building custom CAN applications
- Understanding protocol-specific packet structures
- Implementing real-world CAN communication systems
- Testing and debugging CAN networks
