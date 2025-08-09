#pragma once

#include <byte_manip.hpp>
#include <array>


namespace can
{
constexpr int FRAME_SIZE = 36; // n bytes in a frame

/**
 * @brief A frame of data in the CAN bus.
 *
 * Network byte order
 */
class Frame : public std::array <uint8_t, FRAME_SIZE>
{
public:
  std::string to_string() const
  {
    return(bytes_to_string(this->data(), FRAME_SIZE));
  }
};
} // namespace can
