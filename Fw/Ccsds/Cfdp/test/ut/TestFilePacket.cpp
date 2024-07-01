//! ============================================================================
//! @file   TestFilePacket.cpp
//! @brief  CFDP file packet FilePacket test file.
//! @author chownw
//! ============================================================================

#include <gtest/gtest.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>
#include <Fw/Ccsds/Cfdp/test/ut/TestFilePacket.hpp>
#include <Fw/Types/Assert.hpp>

namespace Fw
{

namespace Cfdp
{

TEST(FilePacket, FileSizeSensitiveSmallFile)
{
  // Allocate buffer for serialization
  U8 data[4];
  Fw::Buffer buffer(data, 4);

  FilePacket::Header header = TestHeader1::create();
  FilePacket::FileSizeSensitive fss(UINT32_MAX);

  // Verify values before serialization
  EXPECT_EQ(
    fss.getValue(),
    UINT32_MAX
  );

  // Call serialize and deserialize functions
  fss.serialize(buffer, 0, header);
  fss.deserialize(buffer, 0, header);

  // Verify fss contains expected values after deserialization
  EXPECT_EQ(
    fss.getValue(),
    UINT32_MAX
  );

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    fss.getSerializedLength(header),
    4
  );
}

TEST(FilePacket, FileSizeSensitiveLargeFile)
{
  // Allocate buffer for serialization
  U8 data[8];
  Fw::Buffer buffer(data, 8);

  FilePacket::Header header = TestHeader2::create();
  FilePacket::FileSizeSensitive fss(UINT64_MAX);

  // Verify values before serialization
  EXPECT_EQ(
    fss.getValue(),
    UINT64_MAX
  );

  // Call serialize and deserialize functions
  fss.serialize(buffer, 0, header);
  fss.deserialize(buffer, 0, header);

  // Verify fss contains expected values after deserialization
  EXPECT_EQ(
    fss.getValue(),
    UINT64_MAX
  );

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    fss.getSerializedLength(header),
    8
  );
}

TEST(FilePacket, LengthValue)
{
  // Allocate buffer for serialization
  U8 data[11];
  Fw::Buffer buffer(data, 11);

  const char* value = "test/value";
  FilePacket::LengthValue lv(strlen(value), reinterpret_cast<const U8*>(value));

  // Verify values before serialization
  EXPECT_EQ(
    lv.getLength(),
    strlen(value)
  );
  EXPECT_EQ(
    lv.getValue(),
    reinterpret_cast<const U8*>(value)
  );

  // Call serialize and deserialize functions
  lv.serialize(buffer, 0);
  lv.deserialize(buffer, 0);

  // Verify lv contains expected values after deserialization
  EXPECT_EQ(
    lv.getLength(),
    strlen(value)
  );
  EXPECT_EQ(
    strncmp(
      reinterpret_cast<const char*>(lv.getValue()),
      value,
      lv.getLength()
    ),
    0
  );

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    lv.getSerializedLength(),
    strlen(value) + 1
  );
}

TEST(FilePacket, LengthValueEmpty)
{
  // Allocate buffer for serialization
  U8 data[11];
  Fw::Buffer buffer(data, 11);

  // Call default constructor which should initialize an empty LV object
  FilePacket::LengthValue lv;

  // Verify values before serialization
  EXPECT_EQ(
    lv.getLength(),
    0
  );

  // Call serialize and deserialize functions
  lv.serialize(buffer, 0);
  lv.deserialize(buffer, 0);

  // Verify lv contains expected values after deserialization
  EXPECT_EQ(
    lv.getLength(),
    0
  );

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    lv.getSerializedLength(),
    1 // Serialization should just contain the 'length' byte
  );
}

TEST(FilePacket, GetTypeFromBuffer)
{
  U32 filePacketLength =
    TestHeader1::Serialized::LENGTH + TestMetadata1::Serialized::LENGTH;

  // Allocate buffer for serialization
  U8 data[filePacketLength];
  Fw::Buffer buffer(data, filePacketLength);

  // Fill buffer with a serialized test packet
  TestHeader1::fillBuffer(buffer, 0);
  TestMetadata1::fillBuffer(buffer, TestHeader1::Serialized::LENGTH);

  // Verify function returns the expected type
  EXPECT_EQ(
    FilePacket::getTypeFromBuffer(buffer, 0),
    FilePacket::Type::METADATA_PACKET
  );
}

TEST(FilePacket, Serialize)
{
  U32 filePacketLength =
    TestHeader1::Serialized::LENGTH + TestMetadata1::Serialized::LENGTH;

  // Allocate buffer for serialization
  U8 data[filePacketLength];
  Fw::Buffer buffer(data, filePacketLength);

  // Create source file packet from header and metadata
  FilePacket::Header header = TestHeader1::create();
  FilePacket::Metadata metadata = TestMetadata1::create();
  FilePacket filePacket(header, metadata);

  // Serialize file packet
  filePacket.serialize(buffer, 0);

  // Verify buffer
  TestHeader1::verifyBuffer(buffer, 0);
  TestMetadata1::verifyBuffer(buffer, TestHeader1::Serialized::LENGTH);
}

TEST(FilePacket, Deserialize)
{
  U32 filePacketLength =
    TestHeader1::Serialized::LENGTH + TestMetadata1::Serialized::LENGTH;

  // Allocate buffer for serialization
  U8 data[filePacketLength];
  Fw::Buffer buffer(data, filePacketLength);

  // Fill buffer with a serialized test packet
  TestHeader1::fillBuffer(buffer, 0);
  TestMetadata1::fillBuffer(buffer, TestHeader1::Serialized::LENGTH);

  // Create destination file packet to fill
  FilePacket::Header header;
  FilePacket::Metadata metadata;
  FilePacket filePacket(header, metadata);

  // Deserialize file packet
  filePacket.deserialize(buffer, 0);

  // Verify file packets
  TestHeader1::verifyHeader(header);
  TestMetadata1::verifyMetadata(metadata);
}

} // namespace Cfdp

} // namespace Fw
