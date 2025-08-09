#include <canopen.hpp>


namespace canopen
{
void from_cobid(
  const uint32_t cobid,
  uint8_t& node_id,
  uint8_t& function_code)
{
  node_id       = cobid & 0x7F;
  function_code = (cobid >> 7) & 0xFF;
}

std::string packet_to_string(
  const can::Packet& packet)
{
  uint8_t node_id, function_code;

  from_cobid(packet.get_id(), node_id, function_code);

  return("size: " + std::to_string(packet.get_size()) +
         ", type: " + std::to_string(packet.get_type()) +
         ", tag: " + std::to_string(packet.get_tag()) +
         ", timestamp: " + std::to_string(packet.get_timestamp()) +
         ", channel: " + std::to_string(packet.get_channel()) +
         ", dlc: " + std::to_string(packet.get_dlc()) +
         ", flag: " + std::to_string(packet.get_flag()) +
         ", node_id: " + std::to_string(node_id) +
         ", function_code: " + std::to_string(function_code) +
         ", data: " + packet.get_data().to_string());
}
} // namespace canopen
