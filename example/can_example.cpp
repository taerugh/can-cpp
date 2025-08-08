#include <can-cpp/can/packet.hpp>
#include <can-cpp/can/frame.hpp>
#include <iostream>

int main()
{
  // Create a CAN packet
  can::PayloadData data(0x1234567890ABCDEF);
  can::Packet      packet(
    36,               // size
    1,                // type
    12345,            // tag
    1234567890,       // timestamp
    1,                // channel
    8,                // dlc
    0,                // flag
    0x123,            // id
    data              // data
    );

  std::cout << "Created CAN packet:\n";
  std::cout << packet.to_string() << std::endl;

  // Convert to frame and back
  can::Frame frame = packet.to_frame();
  std::cout << "\nFrame representation:\n";
  std::cout << frame.to_string() << std::endl;

  // Create packet from frame
  can::Packet packet2(frame);
  std::cout << "\nPacket reconstructed from frame:\n";
  std::cout << packet2.to_string() << std::endl;

  return(0);
}
