#include <can-cpp/lib/byte_manip.hpp>


std::string bytes_to_string(const uint8_t *data, const std::size_t size)
{
  std::string str = "";

  for (std::size_t i = 0; i < size; ++i)
  {
    str += std::format("{:02x}", data[i]);
    if (i < size - 1)
    {
      str += " ";
    }
  }
  return(str);
}
