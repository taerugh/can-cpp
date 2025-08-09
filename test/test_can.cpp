#include <packet.hpp>

#include <gtest/gtest.h>


TEST(CanLib, PacketFromFrame_Nominal)
{
  can::Frame frame = {
    0x00, 0x24, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x46, 0xa3, 0xae, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x02,
    0x99, 0xff, 0x0b, 0x00, 0x20, 0x0d, 0x32, 0x99, 0x20, 0x11, 0x86, 0x3e };

  can::Packet packet(frame);

  ASSERT_EQ(packet.get_size(), 0x24);
  ASSERT_EQ(packet.get_type(), 0x80);
  ASSERT_EQ(packet.get_tag(), 0);
  ASSERT_EQ(packet.get_timestamp(), 5090103525040455680);
  ASSERT_EQ(packet.get_channel(), 0);
  ASSERT_EQ(packet.get_dlc(), 8);
  ASSERT_EQ(packet.get_flag(), 2);
  ASSERT_EQ(packet.get_id(), 2583628544);
  ASSERT_EQ(packet.get_data().to_ullong(), 0x3E86112099320D20);
}


TEST(CanLib, PacketToFrame_Nominal)
{
  can::Packet packet(0x24, 0x80, 0, 0, 0, 8, 0, 0x120,
                     can::PayloadData(0x0706050403020100));

  ASSERT_EQ(packet.get_size(), 0x24);
  ASSERT_EQ(packet.get_type(), 0x80);
  ASSERT_EQ(packet.get_tag(), 0);
  ASSERT_EQ(packet.get_timestamp(), 0);
  ASSERT_EQ(packet.get_channel(), 0);
  ASSERT_EQ(packet.get_dlc(), 8);
  ASSERT_EQ(packet.get_flag(), 0);
  ASSERT_EQ(packet.get_id(), 0x120);
  ASSERT_EQ(packet.get_data().to_ullong(), 0x0706050403020100);

  const can::Frame& frame          = packet.to_frame();
  can::Frame        expected_frame =
  { 0, 0x24, 0, 0x80, 0, 0, 0, 0,   0,    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,    0, 0, 0x08, 0, 0, 0, 0, 0x1, 0x20, 0, 1, 2, 3, 4, 5, 6, 7 };

  for (std::size_t i = 0; i < frame.size(); ++i)
  {
    ASSERT_EQ(frame[i], expected_frame[i]) << "index: " << i;
  }
}
