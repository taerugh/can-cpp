#include <packet.hpp>

#include <byte_manip.hpp>


namespace can
{
Packet::Packet()
{
}

Packet::Packet(
  const uint16_t size,
  const uint16_t type,
  const uint64_t tag,
  const uint64_t timestamp,
  const uint8_t channel,
  const uint8_t dlc,
  const uint16_t flag,
  const uint32_t id,
  const PayloadData& data)
  : size_(size),
  type_(type),
  tag_(tag),
  timestamp_(timestamp),
  channel_(channel),
  dlc_(dlc),
  flag_(flag),
  id_(id),
  data_(data)
{
}

template <typename T>
static inline T get_val(const Frame& frame, std::size_t& i)
{
  const T val = num_from_bytes <T>((uint8_t *)(&frame), i);

  i += sizeof(T);
  return(val);
}

Packet::Packet(const Frame& frame)
{
  std::size_t i = 0;

  size_      = ntoh(get_val <uint16_t>(frame, i));
  type_      = ntoh(get_val <uint16_t>(frame, i));
  tag_       = ntoh(get_val <uint64_t>(frame, i));
  timestamp_ = ntoh(get_val <uint64_t>(frame, i));
  channel_   = ntoh(get_val <uint8_t>(frame, i));
  dlc_       = ntoh(get_val <uint8_t>(frame, i));
  flag_      = ntoh(get_val <uint16_t>(frame, i));
  id_        = ntoh(get_val <uint32_t>(frame, i));
  data_      = PayloadData(get_val <uint64_t>(frame, i)); // network byte order
}

template <typename T>
static inline void add_val(Frame& frame, std::size_t& i, const T& value)
{
  memcpy(&frame[i], &value, sizeof(value));
  i += sizeof(value);
}

Frame Packet::to_frame() const
{
  Frame frame = {};

  std::size_t i = 0;

  add_val <uint16_t>(frame, i, hton(size_));
  add_val <uint16_t>(frame, i, hton(type_));
  add_val <uint64_t>(frame, i, hton(tag_));
  add_val <uint64_t>(frame, i, hton(timestamp_));
  add_val <uint8_t>(frame, i, hton(channel_));
  add_val <uint8_t>(frame, i, hton(dlc_));
  add_val <uint16_t>(frame, i, hton(flag_));
  add_val <uint32_t>(frame, i, hton(id_));
  add_val <uint64_t>(frame, i, data_.to_ullong());

  return(frame);
}

std::string Packet::to_string() const
{
  return("size: " + std::to_string(size_) +
         ", type: " + std::to_string(type_) +
         ", tag: " + std::to_string(tag_) +
         ", timestamp: " + std::to_string(timestamp_) +
         ", channel: " + std::to_string(channel_) +
         ", dlc: " + std::to_string(dlc_) +
         ", flag: " + std::to_string(flag_) +
         ", id: " + std::to_string(id_) +
         ", data: " + data_.to_string());
}
} // namespace can
