#pragma once

#include <bitset>
#include <cstdint>
#include <cstring>
#include <format>


/**
 * @brief `Bits` extends `std::bitset` to provide methods for getting and setting values in a bitset
 */
template <std::size_t N_BITS>
class Bits : public std::bitset <N_BITS>
{
public:
// Inherit constructors from std::bitset
  using std::bitset <N_BITS>::bitset;


// Default constructor
  Bits() : std::bitset <N_BITS>()
  {
  }

// Constructor from unsigned long long
  explicit Bits(unsigned long long value) : std::bitset <N_BITS>(value)
  {
  }

  static Bits <N_BITS> from_float(const float value)
  {
    return(Bits <N_BITS>(*reinterpret_cast <const uint32_t *>(&value)));
  }

/**
 * @brief static cast to type `T` from the bitset
 */
  template <typename T>
  operator T() const
  {
    return(static_cast <T>(this->to_ullong()));
  }

/**
 * @brief mirror the bytes in the bitset (change endianness)
 */
  Bits <N_BITS> mirror_bytes() const
  {
    Bits <N_BITS> mirrored;

    for (size_t i = 0; i < (*this).size(); i += 8)
    {
      for (int j = 0; j < 8; ++j)
      {
        mirrored[i + j] = (*this)[(N_BITS - 8 - i) + j];
      }
    }
    return(mirrored);
  }

/**
 * @brief mirror all of the bits in the bitset
 */
  Bits <N_BITS> mirror() const
  {
    Bits <N_BITS> mirrored;

    for (size_t i = 0; i < (*this).size(); i++)
    {
      mirrored[i] = (*this)[N_BITS - i - 1];
    }
    return(mirrored);
  }

/**
 * @brief get `N_BITS_GOT` starting at `bit_idx`
 * @param bit_idx incremented by `N_BITS_GOT`
 */
  template <std::size_t N_BITS_GOT>
  Bits <N_BITS_GOT> get_bits_and_increment(std::size_t& bit_idx) const
  {
    Bits <N_BITS_GOT> bits_got;

    for (size_t i = 0; i < N_BITS_GOT; i++)
    {
      bits_got[i] = (*this)[bit_idx];
      bit_idx++;
    }

    return(bits_got);
  }

/**
 * @brief Sets `N_BITS_SET` starting at `bit_idx` to `bits_set`
 * @param bit_idx incremented by `N_BITS_SET`
 */
  template <std::size_t N_BITS_SET>
  void set_bits_and_increment(std::size_t& bit_idx, const Bits <N_BITS_SET>& bits_set)
  {
    for (size_t i = 0; i < N_BITS_SET; i++)
    {
      (*this)[bit_idx] = bits_set[i];
      bit_idx++;
    }
  }

/**
 * @brief Sets `n_bits_set` starting at `bit_idx` to 1
 * @param bit_idx incremented by `n_bits_set`
 */
  void set_ones_and_increment(std::size_t& bit_idx, const std::size_t n_bits_set)
  {
    for (size_t i = 0; i < n_bits_set; i++)
    {
      (*this)[bit_idx] = 1;
      bit_idx++;
    }
  }

/**
 * @brief Sets `n_bits_set` starting at `bit_idx` to 0
 * @param bit_idx incremented by `n_bits_set`
 */
  void set_zeros_and_increment(std::size_t& bit_idx, const std::size_t n_bits_set)
  {
    for (size_t i = 0; i < n_bits_set; i++)
    {
      (*this)[bit_idx] = 0;
      bit_idx++;
    }
  }

  std::string to_string() const
  {
    std::size_t bit_idx = 0;
    std::string hexstr;

    while (true)
    {
      hexstr.insert(0, std::format("{:02X} ", (uint8_t)get_bits_and_increment <8>(bit_idx)));
      if (bit_idx >= N_BITS - 1)
      {
        hexstr.pop_back();
        return(hexstr);
      }
    }
  }
};
