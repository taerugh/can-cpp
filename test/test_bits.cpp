#include <bits.hpp>

#include <gtest/gtest.h>


TEST(Bits, GetBits_Nominal)
{
  Bits <64>   bits(0x0807060504030201);
  std::size_t bit_idx = 0;

  Bits <16> get1 = bits.get_bits_and_increment <16>(bit_idx);

  ASSERT_EQ(get1.to_ulong(), 0x0201);

  Bits <16> get2 = bits.get_bits_and_increment <16>(bit_idx);
  ASSERT_EQ(get2.to_ulong(), 0x0403);

  Bits <16> get3 = bits.get_bits_and_increment <16>(bit_idx);
  ASSERT_EQ(get3.to_ulong(), 0x0605);

  Bits <16> get4 = bits.get_bits_and_increment <16>(bit_idx);
  ASSERT_EQ(get4.to_ulong(), 0x0807);
}


TEST(Bits, SetBits_Nominal)
{
  Bits <64>   bits(0x0000000000000000);
  std::size_t bit_idx = 0;

  bits.set_bits_and_increment(bit_idx, Bits <16>(0x0201));
  ASSERT_EQ(bits.to_ullong(), 0x0000000000000201);

  bits.set_bits_and_increment(bit_idx, Bits <16>(0x0403));
  ASSERT_EQ(bits.to_ullong(), 0x0000000004030201);

  bits.set_bits_and_increment(bit_idx, Bits <16>(0x0605));
  ASSERT_EQ(bits.to_ullong(), 0x0000060504030201);

  bits.set_bits_and_increment(bit_idx, Bits <16>(0x0807));
  ASSERT_EQ(bits.to_ullong(), 0x0807060504030201);
}


TEST(Bits, ToString_Nominal)
{
  Bits <32> bits(0x01020304);

  ASSERT_EQ(bits.to_string(), "01 02 03 04");
}
