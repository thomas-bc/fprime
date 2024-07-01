//! ============================================================================
//! @file   TestMetadata.cpp
//! @brief  CFDP file packet Metadata test file.
//! @author chownw
//! ============================================================================

#include <gtest/gtest.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>
#include <Fw/Ccsds/Cfdp/Metadata.hpp>
#include <Fw/Ccsds/Cfdp/test/ut/TestFilePacket.hpp>
#include <Fw/Types/Assert.hpp>

namespace Fw
{

namespace Cfdp
{

FilePacket::Metadata TestMetadata1::
  create()
{
  Fw::Cfdp::FilePacket::Metadata metadata(
    TestMetadata1::Values::closureRequested,
    TestMetadata1::Values::checksumType,
    TestMetadata1::Values::fileSize,
    TestMetadata1::Values::sourceFilename,
    TestMetadata1::Values::destFilename
  );

  return metadata;
}

void TestMetadata1::
  fillBuffer(Buffer &buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  data[0] = TestMetadata1::Serialized::OCTET_00;
  data[1] = TestMetadata1::Serialized::OCTET_01;
  data[2] = TestMetadata1::Serialized::OCTET_02;
  data[3] = TestMetadata1::Serialized::OCTET_03;
  data[4] = TestMetadata1::Serialized::OCTET_04;
  data[5] = TestMetadata1::Serialized::OCTET_05;
  data[6] = TestMetadata1::Serialized::OCTET_06;
  data[7] = TestMetadata1::Serialized::OCTET_07;
  data[8] = TestMetadata1::Serialized::OCTET_08;
  data[9] = TestMetadata1::Serialized::OCTET_09;
  data[10] = TestMetadata1::Serialized::OCTET_10;
  data[11] = TestMetadata1::Serialized::OCTET_11;
  data[12] = TestMetadata1::Serialized::OCTET_12;
  data[13] = TestMetadata1::Serialized::OCTET_13;
  data[14] = TestMetadata1::Serialized::OCTET_14;
  data[15] = TestMetadata1::Serialized::OCTET_15;
  data[16] = TestMetadata1::Serialized::OCTET_16;
  data[17] = TestMetadata1::Serialized::OCTET_17;
  data[18] = TestMetadata1::Serialized::OCTET_18;
  data[19] = TestMetadata1::Serialized::OCTET_19;
  data[20] = TestMetadata1::Serialized::OCTET_20;
  data[21] = TestMetadata1::Serialized::OCTET_21;
  data[22] = TestMetadata1::Serialized::OCTET_22;
  data[23] = TestMetadata1::Serialized::OCTET_23;
  data[24] = TestMetadata1::Serialized::OCTET_24;
  data[25] = TestMetadata1::Serialized::OCTET_25;
  data[26] = TestMetadata1::Serialized::OCTET_26;
  data[27] = TestMetadata1::Serialized::OCTET_27;
  data[28] = TestMetadata1::Serialized::OCTET_28;
  data[29] = TestMetadata1::Serialized::OCTET_29;
  data[30] = TestMetadata1::Serialized::OCTET_30;
  data[31] = TestMetadata1::Serialized::OCTET_31;
  data[32] = TestMetadata1::Serialized::OCTET_32;
  data[33] = TestMetadata1::Serialized::OCTET_33;
}

void TestMetadata1::
  verifyBuffer(Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  EXPECT_EQ(
    data[0],
    TestMetadata1::Serialized::OCTET_00
  );
  EXPECT_EQ(
    data[1],
    TestMetadata1::Serialized::OCTET_01
  );
  EXPECT_EQ(
    data[2],
    TestMetadata1::Serialized::OCTET_02
  );
  EXPECT_EQ(
    data[3],
    TestMetadata1::Serialized::OCTET_03
  );
  EXPECT_EQ(
    data[4],
    TestMetadata1::Serialized::OCTET_04
  );
  EXPECT_EQ(
    data[5],
    TestMetadata1::Serialized::OCTET_05
  );
  EXPECT_EQ(
    data[6],
    TestMetadata1::Serialized::OCTET_06
  );
  EXPECT_EQ(
    data[7],
    TestMetadata1::Serialized::OCTET_07
  );
  EXPECT_EQ(
    data[8],
    TestMetadata1::Serialized::OCTET_08
  );
  EXPECT_EQ(
    data[9],
    TestMetadata1::Serialized::OCTET_09
  );
  EXPECT_EQ(
    data[10],
    TestMetadata1::Serialized::OCTET_10
  );
  EXPECT_EQ(
    data[11],
    TestMetadata1::Serialized::OCTET_11
  );
  EXPECT_EQ(
    data[12],
    TestMetadata1::Serialized::OCTET_12
  );
  EXPECT_EQ(
    data[13],
    TestMetadata1::Serialized::OCTET_13
  );
  EXPECT_EQ(
    data[14],
    TestMetadata1::Serialized::OCTET_14
  );
  EXPECT_EQ(
    data[15],
    TestMetadata1::Serialized::OCTET_15
  );
  EXPECT_EQ(
    data[16],
    TestMetadata1::Serialized::OCTET_16
  );
  EXPECT_EQ(
    data[17],
    TestMetadata1::Serialized::OCTET_17
  );
  EXPECT_EQ(
    data[18],
    TestMetadata1::Serialized::OCTET_18
  );
  EXPECT_EQ(
    data[19],
    TestMetadata1::Serialized::OCTET_19
  );
  EXPECT_EQ(
    data[20],
    TestMetadata1::Serialized::OCTET_20
  );
  EXPECT_EQ(
    data[21],
    TestMetadata1::Serialized::OCTET_21
  );
  EXPECT_EQ(
    data[22],
    TestMetadata1::Serialized::OCTET_22
  );
  EXPECT_EQ(
    data[23],
    TestMetadata1::Serialized::OCTET_23
  );
  EXPECT_EQ(
    data[24],
    TestMetadata1::Serialized::OCTET_24
  );
  EXPECT_EQ(
    data[25],
    TestMetadata1::Serialized::OCTET_25
  );
  EXPECT_EQ(
    data[26],
    TestMetadata1::Serialized::OCTET_26
  );
  EXPECT_EQ(
    data[27],
    TestMetadata1::Serialized::OCTET_27
  );
  EXPECT_EQ(
    data[28],
    TestMetadata1::Serialized::OCTET_28
  );
  EXPECT_EQ(
    data[29],
    TestMetadata1::Serialized::OCTET_29
  );
  EXPECT_EQ(
    data[30],
    TestMetadata1::Serialized::OCTET_30
  );
  EXPECT_EQ(
    data[31],
    TestMetadata1::Serialized::OCTET_31
  );
  EXPECT_EQ(
    data[32],
    TestMetadata1::Serialized::OCTET_32
  );
  EXPECT_EQ(
    data[33],
    TestMetadata1::Serialized::OCTET_33
  );
}

void TestMetadata1::
  verifyMetadata(FilePacket::Metadata& metadata)
{
  EXPECT_EQ(
    metadata.directiveCode,
    FilePacket::DirectiveType::METADATA
  );
  EXPECT_EQ(
    metadata.reserved0,
    TestMetadata1::Values::reserved0
  );
  EXPECT_EQ(
    metadata.getClosureRequested(),
    TestMetadata1::Values::closureRequested
  );
  EXPECT_EQ(
    metadata.reserved1,
    TestMetadata1::Values::reserved1
  );
  EXPECT_EQ(
    metadata.getChecksumType(),
    TestMetadata1::Values::checksumType
  );
  EXPECT_EQ(
    metadata.getFileSize(),
    TestMetadata1::Values::fileSize
  );
  EXPECT_EQ(
    metadata.getSourceFilenameLength(),
    TestMetadata1::Values::sourceFilenameLength
  );
  EXPECT_EQ(
    strncmp(
      metadata.getSourceFilename(),
      TestMetadata1::Values::sourceFilename,
      metadata.getSourceFilenameLength()
    ),
    0
  );
  EXPECT_EQ(
    metadata.getDestFilenameLength(),
    TestMetadata1::Values::destFilenameLength
  );
  EXPECT_EQ(
    strncmp(
      metadata.getDestFilename(),
      TestMetadata1::Values::destFilename,
      metadata.getDestFilenameLength()
    ),
    0
  );
}

TEST(FilePacketMetadata, Serialize)
{
  // Allocate buffer for serialization
  U8 data[TestMetadata1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestMetadata1::Serialized::LENGTH);

  FilePacket::Header header = TestHeader1::create();
  FilePacket::Metadata metadata = TestMetadata1::create();
  metadata.serialize(buffer, 0, header);

  // Verify buffer
  TestMetadata1::verifyBuffer(buffer, 0);
}

TEST(FilePacketMetadata, Deserialize)
{
  // Allocate buffer for serialization
  U8 data[TestMetadata1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestMetadata1::Serialized::LENGTH);

  // Fill buffer with serialization
  TestMetadata1::fillBuffer(buffer, 0);

  // Call deserialize function
  FilePacket::Header header = TestHeader1::create();
  FilePacket::Metadata metadata;
  metadata.deserialize(buffer, 0, header);

  // Verify metadata
  TestMetadata1::verifyMetadata(metadata);
}

TEST(FilePacketMetadata, Offset)
{
  // Test (de)serialization of metadata with arbitrary offset in the buffer
  U32 offset = 7;

  // Allocate buffer for serialization
  U8 data[TestMetadata1::Serialized::LENGTH + offset];
  Fw::Buffer buffer(data, TestMetadata1::Serialized::LENGTH + offset);

  // Test serialize function
  FilePacket::Header header = TestHeader1::create();
  FilePacket::Metadata sourceMetadata = TestMetadata1::create();
  sourceMetadata.serialize(buffer, offset, header);
  TestMetadata1::verifyBuffer(buffer, offset);

  // Test deserialize function
  FilePacket::Metadata destMetadata;
  destMetadata.deserialize(buffer, offset, header);
  TestMetadata1::verifyMetadata(destMetadata);
}

TEST(FilePacketMetadata, SerializedLength)
{
  FilePacket::Header header = TestHeader1::create();
  FilePacket::Metadata metadata = TestMetadata1::create();

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    metadata.getSerializedLength(header),
    TestMetadata1::Serialized::LENGTH
  );
}

} // namespace Cfdp

} // namespace Fw
