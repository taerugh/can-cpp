#include <can-cpp/can/packet.hpp>
#include <can-cpp/can/frame.hpp>
#include <can-cpp/n2k/n2k.hpp>
#include <iostream>

int main()
{
  // Create an N2K packet with typical marine data
  // Example: Engine parameters (PGN 127488)
  uint8_t  priority       = 6;                      // Normal priority
  uint8_t  source_address = 42;                     // Engine ECU address
  uint32_t pgn            = 127488;                 // Engine Parameters, Dynamic

  // Calculate the COB-ID using the N2K helper function
  uint32_t cobid = n2k::to_cobid(priority, source_address, pgn);

  // Create payload data for engine RPM and temperature
  // In a real scenario, this would contain actual sensor data
  can::PayloadData engine_data(0x1A2B3C4D5E6F7081); // Example engine data

  // Create the N2K packet
  can::Packet n2k_packet(
    36,                                             // size
    1,                                              // type
    12345,                                          // tag
    1234567890,                                     // timestamp
    1,                                              // channel
    8,                                              // dlc (data length code)
    0,                                              // flag
    cobid,                                          // COB-ID calculated above
    engine_data                                     // payload data
    );

  std::cout << "=== N2K (NMEA 2000) Example ===" << std::endl;
  std::cout << "Created N2K packet for Engine Parameters:" << std::endl;
  std::cout << n2k::packet_to_string(n2k_packet) << std::endl;

  // Demonstrate COB-ID decoding
  uint8_t  decoded_priority, decoded_source;
  uint32_t decoded_pgn;
  n2k::from_cobid(cobid, decoded_priority, decoded_source, decoded_pgn);

  std::cout << "\nCOB-ID Analysis:" << std::endl;
  std::cout << "Original COB-ID: 0x" << std::hex << cobid << std::dec << std::endl;
  std::cout << "Decoded Priority: " << static_cast <int>(decoded_priority) << std::endl;
  std::cout << "Decoded Source Address: " << static_cast <int>(decoded_source) << std::endl;
  std::cout << "Decoded PGN: " << decoded_pgn << std::endl;

  // Create another N2K packet - GPS Position (PGN 129025)
  priority       = 3;                            // High priority for navigation data
  source_address = 15;                           // GPS receiver address
  pgn            = 129025;                       // Position, Rapid Update

  cobid = n2k::to_cobid(priority, source_address, pgn);
  can::PayloadData gps_data(0xAABBCCDDEEFF0011); // Example GPS coordinates

  can::Packet gps_packet(
    36, 1, 12346, 1234567891, 1, 8, 0, cobid, gps_data
    );

  std::cout << "\n=== Second N2K Packet (GPS Position) ===" << std::endl;
  std::cout << n2k::packet_to_string(gps_packet) << std::endl;

  // Convert to frame format
  can::Frame n2k_frame = n2k_packet.to_frame();
  std::cout << "\nN2K Frame representation:" << std::endl;
  std::cout << n2k_frame.to_string() << std::endl;

  return(0);
} // main
