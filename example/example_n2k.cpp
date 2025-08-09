#include <packet.hpp>
#include <frame.hpp>
#include <n2k.hpp>
#include <iostream>

int main()
{
  // Example 1: Water Depth (PGN 0x1f50b)
  {
    std::cout << "\n=== Water Depth PGN ===" << std::endl;
    std::cout << std::endl;

    // raw CAN frame
    const can::Frame frame = {
      0x00, 0x24, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x39,
      0x00, 0x00, 0x00, 0x00, 0x49, 0x96, 0x02, 0xd2, 0x01, 0x08, 0x00, 0x00,
      0x19, 0xf5, 0x0b, 0x19, 0x01, 0x0d, 0x02, 0x00, 0x00, 0xf4, 0x01, 0x32
    };

    std::cout << "CAN Frame: " << std::endl;
    std::cout << "  " << frame.to_string() << std::endl;
    std::cout << std::endl;

    // CAN packet
    can::Packet packet(frame);

    std::cout << "CAN Packet: " << std::endl;
    std::cout << "  " << packet.to_string() << std::endl;
    std::cout << std::endl;

    // N2k COB-ID
    uint8_t  priority, source_address;
    uint32_t pgn;
    n2k::from_cobid(packet.get_id(), priority, source_address, pgn);

    std::cout << "Decoded COB-ID: " << std::endl;
    std::cout << "  Priority: " << static_cast <int>(priority);
    std::cout << ", Source Address: " << static_cast <int>(source_address);
    std::cout << ", PGN: 0x" << std::hex << pgn << std::dec << std::endl;
    std::cout << std::endl;

    // N2k Data
    n2k::pgns::water_depth water_depth(packet.get_data());

    std::cout << "PGN-specific Data:" << std::endl;
    std::cout << "  SID: " << static_cast <int>(water_depth.sid);
    std::cout << ", Depth: " << water_depth.depth << " m";
    std::cout << ", Offset: " << water_depth.offset << " m";
    std::cout << ", Range: " << static_cast <int>(water_depth.range) << std::endl;
    std::cout << std::endl;
  }

  // Example 2: Wind Data (PGN 0x1fd02)
  {
    std::cout << "\n=== Wind Data PGN ===" << std::endl;
    std::cout << std::endl;

    // raw CAN frame
    const can::Frame frame = {
      0x00, 0x24, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x3a,
      0x00, 0x00, 0x00, 0x00, 0x49, 0x96, 0x02, 0xd3, 0x01, 0x08, 0x00, 0x00,
      0x0d, 0xfd, 0x02, 0x1e, 0x02, 0x0e, 0x06, 0xf4, 0x7e, 0x02, 0x00, 0x00
    };

    std::cout << "CAN Frame: " << std::endl;
    std::cout << "  " << frame.to_string() << std::endl;
    std::cout << std::endl;

    // CAN packet
    can::Packet packet(frame);

    std::cout << "CAN Packet: " << std::endl;
    std::cout << "  " << packet.to_string() << std::endl;
    std::cout << std::endl;

    // N2k COB-ID
    uint8_t  priority, source_address;
    uint32_t pgn;
    n2k::from_cobid(packet.get_id(), priority, source_address, pgn);

    std::cout << "Decoded COB-ID: " << std::endl;
    std::cout << "  Priority: " << static_cast <int>(priority);
    std::cout << ", Source Address: " << static_cast <int>(source_address);
    std::cout << ", PGN: 0x" << std::hex << pgn << std::dec << std::endl;
    std::cout << std::endl;

    // N2k Data
    n2k::pgns::wind_data wind_data(packet.get_data());

    std::cout << "PGN-specific Data:" << std::endl;
    std::cout << "  SID: " << static_cast <int>(wind_data.sid);
    std::cout << ", Wind Speed: " << wind_data.wind_speed << " m/s";
    std::cout << ", Wind Angle: " << wind_data.wind_angle << " degrees";
    std::cout << std::endl;
  }

  return(0);
}
