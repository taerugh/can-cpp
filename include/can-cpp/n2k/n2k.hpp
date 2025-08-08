#pragma once

#include <can-cpp/can/packet.hpp>


namespace n2k
{
/**
 * @brief Convert priority, source address, and pgn to cobid
 * @param priority Priority
 * @param source_address Source address
 * @param pgn PGN
 * @return COB-ID
 */
constexpr uint32_t to_cobid(
  const uint8_t priority,
  const uint8_t source_address,
  const uint32_t pgn)
{
  return((priority << 26) + (pgn << 8) + source_address);
}

/**
 * @brief Convert cobid to priority, source address, and pgn
 * @param cobid (input) COB-ID
 * @param priority (output) Priority
 * @param source_address (output) Source address
 * @param pgn (output) PGN
 */
void from_cobid(
  const uint32_t cobid,
  uint8_t& priority,
  uint8_t& source_address,
  uint32_t& pgn);


/**
 * @brief Generate a string description of the N2k packet
 */
std::string packet_to_string(
  const can::Packet& packet);
} // namespace n2k
