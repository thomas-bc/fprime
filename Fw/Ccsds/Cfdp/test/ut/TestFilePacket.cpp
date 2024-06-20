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

  lv.serialize(buffer);
  lv.deserialize(buffer);

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

TEST(FilePacketFieldFormats, TypeLengthValue)
{
  // Allocate buffer for serialized TLV object
  U8 data[12];
  Fw::Buffer buffer(data, 12);

  // Test TLV value
  const char* value = "test/value";

  // Create TLV object
  FilePacket::TypeLengthValue tlv(
    FilePacket::TypeLengthValue::TlvType::MESSAGE_TO_USER,
    strlen(value),
    reinterpret_cast<const U8*>(value)
  );

  // Verify constructor
  EXPECT_EQ(tlv.type, FilePacket::TypeLengthValue::TlvType::MESSAGE_TO_USER);
  EXPECT_EQ(tlv.length, strlen(value));
  EXPECT_EQ(tlv.value, reinterpret_cast<const U8*>(value));

  tlv.serialize(buffer);
  tlv.deserialize(buffer);

  // Verify deserialization resulted in the correct length, a pointer to the
  // start of the value in the serialized buffer, and that serialization
  // correctly copied the value into the buffer
  EXPECT_EQ(
    tlv.getType(),
    FilePacket::TypeLengthValue::TlvType::MESSAGE_TO_USER
  );
  EXPECT_EQ(
    tlv.getLength(),
    strlen(value)
  );
  EXPECT_EQ(
    strncmp(
      reinterpret_cast<const char*>(tlv.getValue()),
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
