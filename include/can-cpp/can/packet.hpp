#pragma once

#include <can-cpp/can/frame.hpp>
#include <can-cpp/lib/bits.hpp>


namespace can
{
/**
 * @brief The data payload of a CAN packet.
 *
 * Network byte order
 */
using PayloadData = Bits <64>;


class Packet
{
public:
  Packet();

  Packet(
    const uint16_t size,
    const uint16_t type,
    const uint64_t tag,
    const uint64_t timestamp,
    const uint8_t channel,
    const uint8_t dlc,
    const uint16_t flag,
    const uint32_t id,
    const PayloadData& data);

  Packet(const Frame& frame);

  Frame to_frame() const;

  virtual std::string to_string() const;

  uint16_t get_size() const
  {
    return(size_);
  }

  uint16_t get_type() const
  {
    return(type_);
  }

  uint64_t get_tag() const
  {
    return(tag_);
  }

  uint64_t get_timestamp() const
  {
    return(timestamp_);
  }

  uint8_t get_channel() const
  {
    return(channel_);
  }

  uint8_t get_dlc() const
  {
    return(dlc_);
  }

  uint16_t get_flag() const
  {
    return(flag_);
  }

  uint32_t get_id() const
  {
    return(id_);
  }

  PayloadData get_data() const
  {
    return(data_);
  }

protected:
  uint16_t size_;
  uint16_t type_;
  uint64_t tag_;
  uint64_t timestamp_;
  uint8_t channel_;
  uint8_t dlc_;
  uint16_t flag_;
  uint32_t id_;
  PayloadData data_;
};
} // namespace can
