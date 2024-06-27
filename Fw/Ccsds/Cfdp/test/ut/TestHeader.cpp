//! ============================================================================
//! @file   TestHeader.cpp
//! @brief  CFDP file packet Header test file.
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

FilePacket::Header TestHeader1::
  create()
{
  Fw::Cfdp::FilePacket::Header header(
    TestHeader1::Values::type,
    TestHeader1::Values::direction,
    TestHeader1::Values::transmissionMode,
    TestHeader1::Values::crcFlag,
    TestHeader1::Values::largeFileFlag,
    TestHeader1::Values::segmentationControl,
    TestHeader1::Values::segmentMetadataFlag,
    TestHeader1::Values::transSeqNumLength,
    TestHeader1::Values::transSeqNumber,
    TestHeader1::Values::entityIdLength,
    TestHeader1::Values::sourceEntityId,
    TestHeader1::Values::destEntityId,
    TestHeader1::Values::dataFieldLength
  );

  return header;
}

void TestHeader1::
  fillBuffer(Buffer &buf)
{
  U8* data = buf.getData();

  data[0] = TestHeader1::Serialized::OCTET_00;
  data[1] = TestHeader1::Serialized::OCTET_01;
  data[2] = TestHeader1::Serialized::OCTET_02;
  data[3] = TestHeader1::Serialized::OCTET_03;
  data[4] = TestHeader1::Serialized::OCTET_04;
  data[5] = TestHeader1::Serialized::OCTET_05;
  data[6] = TestHeader1::Serialized::OCTET_06;
  data[7] = TestHeader1::Serialized::OCTET_07;
  data[8] = TestHeader1::Serialized::OCTET_08;
  data[9] = TestHeader1::Serialized::OCTET_09;
  data[10] = TestHeader1::Serialized::OCTET_10;
  data[11] = TestHeader1::Serialized::OCTET_11;
  data[12] = TestHeader1::Serialized::OCTET_12;
}

void TestHeader1::
  verifyBuffer(Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  EXPECT_EQ(
    data[0],
    TestHeader1::Serialized::OCTET_00
  );
  EXPECT_EQ(
    data[1],
    TestHeader1::Serialized::OCTET_01
  );
  EXPECT_EQ(
    data[2],
    TestHeader1::Serialized::OCTET_02
  );
  EXPECT_EQ(
    data[3],
    TestHeader1::Serialized::OCTET_03
  );
  EXPECT_EQ(
    data[4],
    TestHeader1::Serialized::OCTET_04
  );
  EXPECT_EQ(
    data[5],
    TestHeader1::Serialized::OCTET_05
  );
  EXPECT_EQ(
    data[6],
    TestHeader1::Serialized::OCTET_06
  );
  EXPECT_EQ(
    data[7],
    TestHeader1::Serialized::OCTET_07
  );
  EXPECT_EQ(
    data[8],
    TestHeader1::Serialized::OCTET_08
  );
  EXPECT_EQ(
    data[9],
    TestHeader1::Serialized::OCTET_09
  );
  EXPECT_EQ(
    data[10],
    TestHeader1::Serialized::OCTET_10
  );
  EXPECT_EQ(
    data[11],
    TestHeader1::Serialized::OCTET_11
  );
  EXPECT_EQ(
    data[12],
    TestHeader1::Serialized::OCTET_12
  );
}

void TestHeader1::
  verifyHeader(FilePacket::Header& header)
{
  EXPECT_EQ(
    header.getVersion(),
    TestHeader1::Values::version
  );
  EXPECT_EQ(
    header.getType(),
    TestHeader1::Values::type
  );
  EXPECT_EQ(
    header.getDirection(),
    TestHeader1::Values::direction
  );
  EXPECT_EQ(
    header.getTransmissionMode(),
    TestHeader1::Values::transmissionMode
  );
  EXPECT_EQ(
    header.getCrcFlag(),
    TestHeader1::Values::crcFlag
  );
  EXPECT_EQ(
    header.getLargeFileFlag(),
    TestHeader1::Values::largeFileFlag
  );
  EXPECT_EQ(
    header.getDataFieldLength(),
    TestHeader1::Values::dataFieldLength
  );
  EXPECT_EQ(
    header.getSegmentationControl(),
    TestHeader1::Values::segmentationControl
  );
  EXPECT_EQ(
    header.getEntityIdLength(),
    TestHeader1::Values::entityIdLength
  );
  EXPECT_EQ(
    header.getSegmentMetadataFlag(),
    TestHeader1::Values::segmentMetadataFlag
  );
  EXPECT_EQ(
    header.getTransSeqNumLength(),
    TestHeader1::Values::transSeqNumLength
  );
  EXPECT_EQ(
    header.getSourceEntityId(),
    TestHeader1::Values::sourceEntityId
  );
  EXPECT_EQ(
    header.getTransSeqNumber(),
    TestHeader1::Values::transSeqNumber
  );
  EXPECT_EQ(
    header.getDestEntityId(),
    TestHeader1::Values::destEntityId
  );
}

FilePacket::Header TestHeader2::
  create()
{
  Fw::Cfdp::FilePacket::Header header(
    TestHeader2::Values::type,
    TestHeader2::Values::direction,
    TestHeader2::Values::transmissionMode,
    TestHeader2::Values::crcFlag,
    TestHeader2::Values::largeFileFlag,
    TestHeader2::Values::segmentationControl,
    TestHeader2::Values::segmentMetadataFlag,
    TestHeader2::Values::transSeqNumLength,
    TestHeader2::Values::transSeqNumber,
    TestHeader2::Values::entityIdLength,
    TestHeader2::Values::sourceEntityId,
    TestHeader2::Values::destEntityId,
    TestHeader2::Values::dataFieldLength
  );

  return header;
}

void TestHeader2::
  fillBuffer(Buffer &buf)
{
  U8* data = buf.getData();

  data[0] = TestHeader2::Serialized::OCTET_00;
  data[1] = TestHeader2::Serialized::OCTET_01;
  data[2] = TestHeader2::Serialized::OCTET_02;
  data[3] = TestHeader2::Serialized::OCTET_03;
  data[4] = TestHeader2::Serialized::OCTET_04;
  data[5] = TestHeader2::Serialized::OCTET_05;
  data[6] = TestHeader2::Serialized::OCTET_06;
  data[7] = TestHeader2::Serialized::OCTET_07;
  data[8] = TestHeader2::Serialized::OCTET_08;
  data[9] = TestHeader2::Serialized::OCTET_09;
  data[10] = TestHeader2::Serialized::OCTET_10;
  data[11] = TestHeader2::Serialized::OCTET_11;
  data[12] = TestHeader2::Serialized::OCTET_12;
}

TEST(FilePacketHeader, Serialize)
{
  // Allocate buffer for serialization
  U8 data[TestHeader1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestHeader1::Serialized::LENGTH);

  FilePacket::Header header = TestHeader1::create();
  header.serialize(buffer, 0);

  // Verify buffer
  TestHeader1::verifyBuffer(buffer, 0);
}

TEST(FilePacketHeader, Deserialize)
{
  // Allocate buffer for serialization
  U8 data[TestHeader1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestHeader1::Serialized::LENGTH);

  // Fill buffer with serialization
  TestHeader1::fillBuffer(buffer);

  // Call deserialize function
  FilePacket::Header header;
  header.deserialize(buffer, 0);

  // Verify header
  TestHeader1::verifyHeader(header);
}

TEST(FilePacketHeader, Offset)
{
  // Test (de)serialization of header with arbitrary offset in the buffer
  U32 offset = 11;

  // Allocate buffer for serialization
  U8 data[TestHeader1::Serialized::LENGTH + offset];
  Fw::Buffer buffer(data, TestHeader1::Serialized::LENGTH + offset);

  // Test serialize function
  FilePacket::Header sourceHeader = TestHeader1::create();
  sourceHeader.serialize(buffer, offset);
  TestHeader1::verifyBuffer(buffer, offset);

  // Test deserialize function
  FilePacket::Header destHeader;
  destHeader.deserialize(buffer, offset);
  TestHeader1::verifyHeader(destHeader);
}

TEST(FilePacketHeader, SerializedLength)
{
  FilePacket::Header header = TestHeader1::create();

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    header.getSerializedLength(),
    TestHeader1::Serialized::LENGTH
  );
}

} // namespace Cfdp

} // namespace Fw
