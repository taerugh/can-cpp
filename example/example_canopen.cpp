#include <packet.hpp>
#include <frame.hpp>
#include <canopen.hpp>
#include <iostream>

int main()
{
  // Create a CANopen TPDO1 packet
  uint8_t node_id       = 5;                            // Node ID for a motor controller
  uint8_t function_code = canopen::FUNCTION_CODE_TPDO1; // Transmit PDO 1

  // Calculate the COB-ID using the CANopen helper function
  uint32_t cobid = canopen::to_cobid(node_id, function_code);

  // Create payload data for motor status (position, velocity, etc.)
  can::PayloadData motor_status(0x12345678ABCDEF00);    // Example motor status data

  // Create the CANopen packet
  can::Packet canopen_packet(
    36,                                                 // size
    1,                                                  // type
    12345,                                              // tag
    1234567890,                                         // timestamp
    1,                                                  // channel
    8,                                                  // dlc (data length code)
    0,                                                  // flag
    cobid,                                              // COB-ID calculated above
    motor_status                                        // payload data
    );

  std::cout << "=== CANopen Example ===" << std::endl;
  std::cout << "Created CANopen TPDO1 packet from motor controller:" << std::endl;
  std::cout << canopen::packet_to_string(canopen_packet) << std::endl;

  // Demonstrate COB-ID decoding
  uint8_t decoded_node_id, decoded_function_code;
  canopen::from_cobid(cobid, decoded_node_id, decoded_function_code);

  std::cout << "\nCOB-ID Analysis:" << std::endl;
  std::cout << "Original COB-ID: 0x" << std::hex << cobid << std::dec << std::endl;
  std::cout << "Decoded Node ID: " << static_cast <int>(decoded_node_id) << std::endl;
  std::cout << "Decoded Function Code: 0x" << std::hex << static_cast <int>(decoded_function_code) << std::dec;
  std::cout << " (TPDO1)" << std::endl;

  // Create an RPDO2 packet (commands to a different node)
  node_id       = 10;
  function_code = canopen::FUNCTION_CODE_RPDO2;
  cobid         = canopen::to_cobid(node_id, function_code);

  can::PayloadData motor_command(0xFEDCBA9876543210);   // Example motor commands
  can::Packet      rpdo_packet(
    36, 1, 12346, 1234567891, 1, 8, 0, cobid, motor_command
    );

  std::cout << "\n=== Second CANopen Packet (RPDO2) ===" << std::endl;
  std::cout << canopen::packet_to_string(rpdo_packet) << std::endl;

  // Demonstrate SYNC frame usage
  std::cout << "\n=== CANopen SYNC Frame ===" << std::endl;
  std::cout << "SYNC COB-ID: 0x" << std::hex << static_cast <int>(canopen::COBID_SYNC) << std::dec << std::endl;
  std::cout << "SYNC Frame: " << canopen::SYNC_FRAME.to_string() << std::endl;

  // Create a packet from the SYNC frame
  can::Packet sync_packet(canopen::SYNC_FRAME);
  std::cout << "SYNC Packet: " << canopen::packet_to_string(sync_packet) << std::endl;

  // Show different function codes
  std::cout << "\n=== CANopen Function Code Reference ===" << std::endl;
  std::cout << "TPDO1: 0x" << std::hex << static_cast <int>(canopen::FUNCTION_CODE_TPDO1) << std::dec << std::endl;
  std::cout << "TPDO2: 0x" << std::hex << static_cast <int>(canopen::FUNCTION_CODE_TPDO2) << std::dec << std::endl;
  std::cout << "TPDO3: 0x" << std::hex << static_cast <int>(canopen::FUNCTION_CODE_TPDO3) << std::dec << std::endl;
  std::cout << "TPDO4: 0x" << std::hex << static_cast <int>(canopen::FUNCTION_CODE_TPDO4) << std::dec << std::endl;
  std::cout << "RPDO1: 0x" << std::hex << static_cast <int>(canopen::FUNCTION_CODE_RPDO1) << std::dec << std::endl;
  std::cout << "RPDO2: 0x" << std::hex << static_cast <int>(canopen::FUNCTION_CODE_RPDO2) << std::dec << std::endl;
  std::cout << "RPDO3: 0x" << std::hex << static_cast <int>(canopen::FUNCTION_CODE_RPDO3) << std::dec << std::endl;
  std::cout << "RPDO4: 0x" << std::hex << static_cast <int>(canopen::FUNCTION_CODE_RPDO4) << std::dec << std::endl;

  // Convert to frame format
  can::Frame canopen_frame = canopen_packet.to_frame();
  std::cout << "\nCANopen Frame representation:" << std::endl;
  std::cout << canopen_frame.to_string() << std::endl;

  return(0);
} // main
