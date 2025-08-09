#pragma once

#include <packet.hpp>


namespace canopen
{
// Standard CANopen function codes
// See https://en.wikipedia.org/wiki/CANopen#Predefined_Connection_Set[7]
constexpr uint8_t FUNCTION_CODE_RPDO1 = 0x04;
constexpr uint8_t FUNCTION_CODE_RPDO2 = 0x06;
constexpr uint8_t FUNCTION_CODE_RPDO3 = 0x08;
constexpr uint8_t FUNCTION_CODE_RPDO4 = 0x0A;
constexpr uint8_t FUNCTION_CODE_TPDO1 = 0x03;
constexpr uint8_t FUNCTION_CODE_TPDO2 = 0x05;
constexpr uint8_t FUNCTION_CODE_TPDO3 = 0x07;
constexpr uint8_t FUNCTION_CODE_TPDO4 = 0x09;

constexpr uint8_t COBID_SYNC = 0x80;
const can::Frame  SYNC_FRAME = can::Packet(0x24, 0x80, 0, 0, 0, 0, 0, COBID_SYNC, {}).to_frame();


/**
 * @brief Convert node_id and function_code to cobid
 * @param node_id Node ID
 * @param function_code Function code
 * @return COB-ID
 */
constexpr uint32_t to_cobid(
  const uint8_t node_id,
  const uint8_t function_code)
{
  return((function_code << 7) + node_id);
}

/**
 * @brief Convert cobid to node_id and function_code
 * @param cobid (input) COB-ID
 * @param node_id (output) Node ID
 * @param function_code (output) Function code
 */
void from_cobid(
  const uint32_t cobid,
  uint8_t& node_id,
  uint8_t& function_code);


/**
 * @brief Generate a string description of the CANopen packet
 */
std::string packet_to_string(
  const can::Packet& packet);
} // namespace canopen
