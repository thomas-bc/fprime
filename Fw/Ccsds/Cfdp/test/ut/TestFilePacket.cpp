//! ============================================================================
//! @file   TestFilePacket.cpp
//! @brief  CFDP PDU file packet main test file.
//! @author chownw
//! ============================================================================

#include <gtest/gtest.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Types/Assert.hpp>

namespace Fw
{

namespace Cfdp
{

TEST(FilePacketFieldFormats, LengthValue)
{
  // Allocate buffer for serialized LV object
  U8 data[11];
  Fw::Buffer buffer(data, 11);

  // Test LV value
  const char* value = "test/value";

  // Create LV object
  FilePacket::LengthValue lv(strlen(value), reinterpret_cast<const U8*>(value));

  // Verify constructor
  EXPECT_EQ(lv.length, strlen(value));
  EXPECT_EQ(lv.value, reinterpret_cast<const U8*>(value));

  lv.serialize(buffer, 0);
  lv.deserialize(buffer, 0);

  // Verify deserialization resulted in the correct length, a pointer to the
  // start of the value in the serialized buffer, and that serialization
  // correctly copied the value into the buffer
  EXPECT_EQ(
    lv.getLength(),
    strlen(value)
  );
  EXPECT_EQ(
    strncmp(
      reinterpret_cast<const char*>(lv.getValue()),
      value,
      strlen(value)
    ),
    0
  );
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

} // namespace Cfdp

} // namespace Fw
