#pragma once

#include <cstdint>
#include <string>
#include <bitset>
#include <format>

extern "C" {
  #include <arpa/inet.h>
}


/**
 * @brief Converts a byte array to a string of hex digits
 */
std::string bytes_to_string(const uint8_t *data, const std::size_t size);


/**
 * @brief Network to host byte order for 64-bit integers
 */
#ifndef ntohll
inline uint64_t ntohll(uint64_t value)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
  return((((uint64_t)ntohl((uint32_t)value)) << 32) | ntohl((uint32_t)(value >> 32)));
#else
  return(value);
#endif
}

#endif


/**
 * @brief Host to network byte order for 64-bit integers
 */
#ifndef htonll
inline uint64_t htonll(uint64_t value)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
  return((((uint64_t)htonl((uint32_t)value)) << 32) | htonl((uint32_t)(value >> 32)));
#else
  return(value);
#endif
}

#endif


/**
 * @brief Network to host byte order
 */
template <typename T>
T ntoh(const T& value)
{
  switch (sizeof(T))
  {
  case 2:
    return(ntohs(value));

  case 4:
    return(ntohl(value));

  case 8:
    return(ntohll(value));

  default:
    return(value);
  }
}

/**
 * @brief Host to network byte order
 */
template <typename T>
T hton(const T& value)
{
  switch (sizeof(T))
  {
  case 2:
    return(htons(value));

  case 4:
    return(htonl(value));

  case 8:
    return(htonll(value));

  default:
    return(value);
  }
}

/**
 * @brief Get number from a byte array
 */
template <typename T>
T num_from_bytes(const uint8_t *data, const std::size_t i)
{
  return(*((T *)&data[i]));
}
