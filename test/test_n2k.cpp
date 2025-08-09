#include <n2k.hpp>

#include <gtest/gtest.h>


TEST(N2kLib, FromCobid_Nominal)
{
  constexpr uint32_t cobid = 0x19FF0B00;

  uint8_t  priority, source_address;
  uint32_t pgn;

  n2k::from_cobid(cobid, priority, source_address, pgn);

  ASSERT_EQ(priority, 6);
  ASSERT_EQ(source_address, 0);
  ASSERT_EQ(pgn, 0x01FF0B);
}


TEST(N2kLib, ToCobid_Nominal)
{
  constexpr uint8_t  priority       = 6;
  constexpr uint8_t  source_address = 0;
  constexpr uint32_t pgn            = 0x01FF0B;

  constexpr uint32_t cobid = n2k::to_cobid(priority, source_address, pgn);

  ASSERT_EQ(cobid, 0x19FF0B00);
}
