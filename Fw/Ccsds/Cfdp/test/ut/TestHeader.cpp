//! ============================================================================
//! @file   TestHeader.cpp
//! @brief  CFDP PDU header test file.
//! @author chownw
//! ============================================================================

#include <gtest/gtest.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>
#include <Fw/Types/Assert.hpp>

namespace
{

enum SerializedTestHeader1 : U8
{
  OCTET_00 = 0x24, // |0 0 1|0|0|1|0|0| - Version through large file flag
  OCTET_01 = 0x00, // |0 0 0 0 0 0 0 0| - Data field length bits 0-7
  OCTET_02 = 0x04, // |0 0 0 0 0 1 0 0| - Data field length bits 8-15
  OCTET_03 = 0x22, // |0|0 1 0|0|0 1 0| - Seg control through seq num length
  OCTET_04 = 0x00, // |0 0 0 0 0 0 0 0| - Source entity ID octet 0
  OCTET_05 = 0x00, // |0 0 0 0 0 0 0 0| - Source entity ID octet 1
  OCTET_06 = 0x06, // |0 0 0 0 0 1 1 0| - Source entity ID octet 2
  OCTET_07 = 0x00, // |0 0 0 0 0 0 0 0| - Seq num octet 0
  OCTET_08 = 0x00, // |0 0 0 0 0 0 0 0| - Seq num octet 1
  OCTET_09 = 0x05, // |0 0 0 0 0 1 0 1| - Seq num octet 2
  OCTET_10 = 0x00, // |0 0 0 0 0 0 0 0| - Destination entity ID octet 0
  OCTET_11 = 0x00, // |0 0 0 0 0 0 0 0| - Destination entity ID octet 1
  OCTET_12 = 0x07, // |0 0 0 0 0 1 1 1| - Destination entity ID octet 2
  LENGTH = 13,
};

//! @brief Construct a header that serializes to SerializedTestHeader1.
//!
Fw::Cfdp::FilePacket::Header
  createTestHeader1()
{
  Fw::Cfdp::FilePacket::Header header(
    Fw::Cfdp::FilePacket::Type::FILE_DIRECTIVE,
    Fw::Cfdp::FilePacket::Direction::TOWARD_RECEIVER,
    Fw::Cfdp::FilePacket::TransmissionMode::UNACKNOWLEDGED,
    Fw::Cfdp::FilePacket::CrcFlag::NOT_PRESENT,
    Fw::Cfdp::FilePacket::LargeFileFlag::SMALL_FILE,
    Fw::Cfdp::FilePacket::SegmentationControl::NOT_PRESERVED,
    Fw::Cfdp::FilePacket::SegmentMetadataFlag::NOT_PRESENT,
    3,
    5,
    3,
    6,
    7,
    4
  );

  return header;
}

} //

namespace Fw
{

namespace Cfdp
{

TEST(FilePacketHeader, ConstructDirective)
{
  // Create header
  FilePacket::Header header = createTestHeader1();

  // Create file packet with header
  FilePacket filePacket(header);

  // Verify private header fields contain the expected values
  EXPECT_EQ(
    filePacket.header.version,
    0x001
  );
  EXPECT_EQ(
    filePacket.header.type,
    FilePacket::Type::FILE_DIRECTIVE
  );
  EXPECT_EQ(
    filePacket.header.direction,
    FilePacket::Direction::TOWARD_RECEIVER
  );
  EXPECT_EQ(
    filePacket.header.transmissionMode,
    FilePacket::TransmissionMode::UNACKNOWLEDGED
  );
  EXPECT_EQ(
    filePacket.header.crcFlag,
    FilePacket::CrcFlag::NOT_PRESENT
  );
  EXPECT_EQ(
    filePacket.header.largeFileFlag,
    FilePacket::LargeFileFlag::SMALL_FILE
  );
  EXPECT_EQ(
    filePacket.header.dataFieldLength,
    4
  );
  EXPECT_EQ(
    filePacket.header.segmentationControl,
    FilePacket::SegmentationControl::NOT_PRESERVED
  );
  EXPECT_EQ(
    filePacket.header.entityIdLength,
    3
  );
  EXPECT_EQ(
    filePacket.header.segmentMetadataFlag,
    FilePacket::SegmentMetadataFlag::NOT_PRESENT
  );
  EXPECT_EQ(
    filePacket.header.transSeqNumLength,
    3
  );
  EXPECT_EQ(
    filePacket.header.sourceEntityId,
    6
  );
  EXPECT_EQ(
    filePacket.header.transSeqNumber,
    5
  );
  EXPECT_EQ(
    filePacket.header.destEntityId,
    7
  );
}

TEST(FilePacketHeader, GetFields)
{
  // Create header
  FilePacket::Header header = createTestHeader1();

  // Create file packet with header
  FilePacket filePacket(header);

  // Verify getter functions return the expected values
  EXPECT_EQ(
    filePacket.header.getVersion(),
    0x001
  );
  EXPECT_EQ(
    filePacket.header.getType(),
    FilePacket::Type::FILE_DIRECTIVE
  );
  EXPECT_EQ(
    filePacket.header.getDirection(),
    FilePacket::Direction::TOWARD_RECEIVER
  );
  EXPECT_EQ(
    filePacket.header.getTransmissionMode(),
    FilePacket::TransmissionMode::UNACKNOWLEDGED
  );
  EXPECT_EQ(
    filePacket.header.getCrcFlag(),
    FilePacket::CrcFlag::NOT_PRESENT
  );
  EXPECT_EQ(
    filePacket.header.getLargeFileFlag(),
    FilePacket::LargeFileFlag::SMALL_FILE
  );
  EXPECT_EQ(
    filePacket.header.getDataFieldLength(),
    4
  );
  EXPECT_EQ(
    filePacket.header.getSegmentationControl(),
    FilePacket::SegmentationControl::NOT_PRESERVED
  );
  EXPECT_EQ(
    filePacket.header.getEntityIdLength(),
    3
  );
  EXPECT_EQ(
    filePacket.header.getSegmentMetadataFlag(),
    FilePacket::SegmentMetadataFlag::NOT_PRESENT
  );
  EXPECT_EQ(
    filePacket.header.getTransSeqNumLength(),
    3
  );
  EXPECT_EQ(
    filePacket.header.getSourceEntityId(),
    6
  );
  EXPECT_EQ(
    filePacket.header.getTransSeqNumber(),
    5
  );
  EXPECT_EQ(
    filePacket.header.getDestEntityId(),
    7
  );
}

TEST(FilePacketHeader, Serialize)
{
  // Allocate buffer for serialized header
  U8 data[SerializedTestHeader1::LENGTH];
  Fw::Buffer buffer(data, SerializedTestHeader1::LENGTH);

  // Create header
  FilePacket::Header header = createTestHeader1();

  // Call header serialization function
  header.serialize(buffer, 0);

  // Verify buffer contains data in the expected format
  EXPECT_EQ(
    buffer.getData()[0],
    SerializedTestHeader1::OCTET_00
  );
  EXPECT_EQ(
    buffer.getData()[1],
    SerializedTestHeader1::OCTET_01
  );
  EXPECT_EQ(
    buffer.getData()[2],
    SerializedTestHeader1::OCTET_02
  );
  EXPECT_EQ(
    buffer.getData()[3],
    SerializedTestHeader1::OCTET_03
  );
  EXPECT_EQ(
    buffer.getData()[4],
    SerializedTestHeader1::OCTET_04
  );
  EXPECT_EQ(
    buffer.getData()[5],
    SerializedTestHeader1::OCTET_05
  );
  EXPECT_EQ(
    buffer.getData()[6],
    SerializedTestHeader1::OCTET_06
  );
  EXPECT_EQ(
    buffer.getData()[7],
    SerializedTestHeader1::OCTET_07
  );
  EXPECT_EQ(
    buffer.getData()[8],
    SerializedTestHeader1::OCTET_08
  );
  EXPECT_EQ(
    buffer.getData()[9],
    SerializedTestHeader1::OCTET_09
  );
  EXPECT_EQ(
    buffer.getData()[10],
    SerializedTestHeader1::OCTET_10
  );
  EXPECT_EQ(
    buffer.getData()[11],
    SerializedTestHeader1::OCTET_11
  );
  EXPECT_EQ(
    buffer.getData()[12],
    SerializedTestHeader1::OCTET_12
  );
}

TEST(FilePacketHeader, Deserialize)
{
  // Allocate buffer for serialized header
  U8 data[SerializedTestHeader1::LENGTH];
  Fw::Buffer buffer(data, SerializedTestHeader1::LENGTH);

  // Create an empty header to fill with deserialized data
  FilePacket::Header header;

  // Define serialized header
  data[0] = SerializedTestHeader1::OCTET_00;
  data[1] = SerializedTestHeader1::OCTET_01;
  data[2] = SerializedTestHeader1::OCTET_02;
  data[3] = SerializedTestHeader1::OCTET_03;
  data[4] = SerializedTestHeader1::OCTET_04;
  data[5] = SerializedTestHeader1::OCTET_05;
  data[6] = SerializedTestHeader1::OCTET_06;
  data[7] = SerializedTestHeader1::OCTET_07;
  data[8] = SerializedTestHeader1::OCTET_08;
  data[9] = SerializedTestHeader1::OCTET_09;
  data[10] = SerializedTestHeader1::OCTET_10;
  data[11] = SerializedTestHeader1::OCTET_11;
  data[12] = SerializedTestHeader1::OCTET_12;

  // Call header serialization function
  header.deserialize(buffer, 0);

  // Verify buffer contains data in the expected format
  EXPECT_EQ(
    header.version,
    0x001
  );
  EXPECT_EQ(
    header.type,
    FilePacket::Type::FILE_DIRECTIVE
  );
  EXPECT_EQ(
    header.direction,
    FilePacket::Direction::TOWARD_RECEIVER
  );
  EXPECT_EQ(
    header.transmissionMode,
    FilePacket::TransmissionMode::UNACKNOWLEDGED
  );
  EXPECT_EQ(
    header.crcFlag,
    FilePacket::CrcFlag::NOT_PRESENT
  );
  EXPECT_EQ(
    header.largeFileFlag,
    FilePacket::LargeFileFlag::SMALL_FILE
  );
  EXPECT_EQ(
    header.dataFieldLength,
    4
  );
  EXPECT_EQ(
    header.segmentationControl,
    FilePacket::SegmentationControl::NOT_PRESERVED
  );
  EXPECT_EQ(
    header.entityIdLength,
    3
  );
  EXPECT_EQ(
    header.segmentMetadataFlag,
    FilePacket::SegmentMetadataFlag::NOT_PRESENT
  );
  EXPECT_EQ(
    header.transSeqNumLength,
    3
  );
  EXPECT_EQ(
    header.sourceEntityId,
    6
  );
  EXPECT_EQ(
    header.transSeqNumber,
    5
  );
  EXPECT_EQ(
    header.destEntityId,
    7
  );
}

TEST(FilePacketHeader, SerializedLength)
{
  // Create header
  FilePacket::Header header = createTestHeader1();

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    header.getSerializedLength(),
    SerializedTestHeader1::LENGTH
  );
}

} // namespace Cfdp

} // namespace Fw
