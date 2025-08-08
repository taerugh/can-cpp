#include <can-cpp/n2k/n2k.hpp>


namespace n2k
{
void from_cobid(
  const uint32_t cobid,
  uint8_t& priority,
  uint8_t& source_address,
  uint32_t& pgn)
{
  source_address = cobid & 0xFF;
  pgn            = (cobid >> 8) & 0x3FFFF;
  priority       = (cobid >> 26) & 0x07;
}

std::string packet_to_string(
  const can::Packet& packet)
{
  uint8_t  priority, source_address;
  uint32_t pgn;

  from_cobid(packet.get_id(), priority, source_address, pgn);

  return("size: " + std::to_string(packet.get_size()) +
         ", type: " + std::to_string(packet.get_type()) +
         ", tag: " + std::to_string(packet.get_tag()) +
         ", timestamp: " + std::to_string(packet.get_timestamp()) +
         ", channel: " + std::to_string(packet.get_channel()) +
         ", dlc: " + std::to_string(packet.get_dlc()) +
         ", flag: " + std::to_string(packet.get_flag()) +
         ", priority: " + std::to_string(priority) +
         ", source_address: " + std::to_string(source_address) +
         ", pgn: " + std::to_string(pgn) +
         ", data: " + packet.get_data().to_string());
}
} // namespace n2k
