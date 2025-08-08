#include <can-cpp/canopen/canopen.hpp>

#include <gtest/gtest.h>


TEST(CanopenLib, FromCobid_Nominal)
{
  constexpr int32_t cobid = 0x000001FF;

  uint8_t node_id, function_code;

  canopen::from_cobid(cobid, node_id, function_code);

  ASSERT_EQ(node_id, 0x7F);
  ASSERT_EQ(function_code, 0x03);
}


TEST(CanopenLib, ToCobid_Nominal)
{
  constexpr uint8_t node_id       = 0x7F;
  constexpr uint8_t function_code = 0x03;

  constexpr uint32_t cobid = canopen::to_cobid(node_id, function_code);

  ASSERT_EQ(cobid, 0x000001FF);
}
