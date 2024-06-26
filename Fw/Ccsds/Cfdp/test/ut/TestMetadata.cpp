//! ============================================================================
//! @file   TestMetadata.cpp
//! @brief  CFDP Metadata PDU test file.
//! @author chownw
//! ============================================================================

#include <gtest/gtest.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>
#include <Fw/Ccsds/Cfdp/Metadata.hpp>
#include <Fw/Types/Assert.hpp>

namespace
{

enum SerializedTestMetadata1 : U8
{
  OCTET_00 = 0x4F, // |0|1|0|0|1|1|1|1| - Reserved through checksum type.
  OCTET_01 = 0x00, // |0 0 0 0 0 0 0 0| - Small file size octet 0.
  OCTET_02 = 0x00, // |0 0 0 0 0 0 0 0| - Small file size octet 1.
  OCTET_03 = 0x00, // |0 0 0 0 0 0 0 0| - Small file size octet 2.
  OCTET_04 = 0x10, // |0 0 0 1 0 0 0 0| - Small file size octet 3.
  OCTET_05 = 0x0E, // |0 0 0 0 1 1 1 0| - Source file name LV length.
  OCTET_06 = 0x53, // |0 1 0 1 0 0 1 1| - Source file name LV value octet 0.
  OCTET_07 = 0x6F, // |0 1 1 0 1 1 1 1| - Source file name LV value octet 1.
  OCTET_08 = 0x75, // |0 1 1 1 0 1 0 1| - Source file name LV value octet 2.
  OCTET_09 = 0x72, // |0 1 1 1 0 0 1 0| - Source file name LV value octet 3.
  OCTET_10 = 0x63, // |0 1 1 0 0 0 1 1| - Source file name LV value octet 4.
  OCTET_11 = 0x65, // |0 1 1 0 0 1 0 1| - Source file name LV value octet 5.
  OCTET_12 = 0x46, // |0 1 0 0 0 1 1 0| - Source file name LV value octet 6.
  OCTET_13 = 0x69, // |0 1 1 0 1 0 0 1| - Source file name LV value octet 7.
  OCTET_14 = 0x6C, // |0 1 1 0 1 1 0 0| - Source file name LV value octet 8.
  OCTET_15 = 0x65, // |0 1 1 0 0 1 0 1| - Source file name LV value octet 9.
  OCTET_16 = 0x6E, // |0 1 1 0 1 1 1 0| - Source file name LV value octet 10.
  OCTET_17 = 0x61, // |0 1 1 0 0 0 0 1| - Source file name LV value octet 11.
  OCTET_18 = 0x6D, // |0 1 1 0 1 1 0 1| - Source file name LV value octet 12.
  OCTET_19 = 0x65, // |0 1 1 0 0 1 0 1| - Source file name LV value octet 13.
  OCTET_20 = 0x0C, // |0 0 0 0 1 1 0 0| - Dest file name LV length.
  OCTET_21 = 0x44, // |0 1 0 0 0 1 0 0| - Dest file name LV value octet 0.
  OCTET_22 = 0x65, // |0 1 1 0 0 1 0 1| - Dest file name LV value octet 1.
  OCTET_23 = 0x73, // |0 1 1 1 0 0 1 1| - Dest file name LV value octet 2.
  OCTET_24 = 0x74, // |0 1 1 1 0 1 0 0| - Dest file name LV value octet 3.
  OCTET_25 = 0x46, // |0 1 0 0 0 1 1 0| - Dest file name LV value octet 4.
  OCTET_26 = 0x69, // |0 1 1 0 1 0 0 1| - Dest file name LV value octet 5.
  OCTET_27 = 0x6C, // |0 1 1 0 1 1 0 0| - Dest file name LV value octet 6.
  OCTET_28 = 0x65, // |0 1 1 0 0 1 0 1| - Dest file name LV value octet 7.
  OCTET_29 = 0x6E, // |0 1 1 0 1 1 1 0| - Dest file name LV value octet 8.
  OCTET_30 = 0x61, // |0 1 1 0 0 0 0 1| - Dest file name LV value octet 9.
  OCTET_31 = 0x6D, // |0 1 1 0 1 1 0 1| - Dest file name LV value octet 10.
  OCTET_32 = 0x65, // |0 1 1 0 0 1 0 1| - Dest file name LV value octet 11.
  LENGTH = 33,
};

//! @brief Construct a Metadata that serializes to SerializedTestMetadata1.
//!
Fw::Cfdp::FilePacket::Metadata
  createTestMetadata1()
{
  Fw::Cfdp::FilePacket::Metadata metadata(
    Fw::Cfdp::FilePacket::ClosureRequested::REQUESTED,
    Fw::Cfdp::FilePacket::ChecksumType::NULL_CHECKSUM,
    16,
    "SourceFilename",
    "DestFilename"
  );

  return metadata;
}

//! @brief Construct a header.
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

TEST(FilePacketMetadata, Serialize)
{
  // Allocate buffer for serialized metadata
  U8 data[SerializedTestMetadata1::LENGTH];
  Fw::Buffer buffer(data, SerializedTestMetadata1::LENGTH);

  // Create header
  FilePacket::Header header = createTestHeader1();

  // Create metadata
  FilePacket::Metadata metadata = createTestMetadata1();

  // Call metadata serialization function
  metadata.serialize(buffer, 0, header);

  // Verify buffer contains data in the expected format
  EXPECT_EQ(
    buffer.getData()[0],
    SerializedTestMetadata1::OCTET_00
  );
  EXPECT_EQ(
    buffer.getData()[1],
    SerializedTestMetadata1::OCTET_01
  );
  EXPECT_EQ(
    buffer.getData()[2],
    SerializedTestMetadata1::OCTET_02
  );
  EXPECT_EQ(
    buffer.getData()[3],
    SerializedTestMetadata1::OCTET_03
  );
  EXPECT_EQ(
    buffer.getData()[4],
    SerializedTestMetadata1::OCTET_04
  );
  EXPECT_EQ(
    buffer.getData()[5],
    SerializedTestMetadata1::OCTET_05
  );
  EXPECT_EQ(
    buffer.getData()[6],
    SerializedTestMetadata1::OCTET_06
  );
  EXPECT_EQ(
    buffer.getData()[7],
    SerializedTestMetadata1::OCTET_07
  );
  EXPECT_EQ(
    buffer.getData()[8],
    SerializedTestMetadata1::OCTET_08
  );
  EXPECT_EQ(
    buffer.getData()[9],
    SerializedTestMetadata1::OCTET_09
  );
  EXPECT_EQ(
    buffer.getData()[10],
    SerializedTestMetadata1::OCTET_10
  );
  EXPECT_EQ(
    buffer.getData()[11],
    SerializedTestMetadata1::OCTET_11
  );
  EXPECT_EQ(
    buffer.getData()[12],
    SerializedTestMetadata1::OCTET_12
  );
  EXPECT_EQ(
    buffer.getData()[13],
    SerializedTestMetadata1::OCTET_13
  );
  EXPECT_EQ(
    buffer.getData()[14],
    SerializedTestMetadata1::OCTET_14
  );
  EXPECT_EQ(
    buffer.getData()[15],
    SerializedTestMetadata1::OCTET_15
  );
  EXPECT_EQ(
    buffer.getData()[16],
    SerializedTestMetadata1::OCTET_16
  );
  EXPECT_EQ(
    buffer.getData()[17],
    SerializedTestMetadata1::OCTET_17
  );
  EXPECT_EQ(
    buffer.getData()[18],
    SerializedTestMetadata1::OCTET_18
  );
  EXPECT_EQ(
    buffer.getData()[19],
    SerializedTestMetadata1::OCTET_19
  );
  EXPECT_EQ(
    buffer.getData()[20],
    SerializedTestMetadata1::OCTET_20
  );
  EXPECT_EQ(
    buffer.getData()[21],
    SerializedTestMetadata1::OCTET_21
  );
  EXPECT_EQ(
    buffer.getData()[22],
    SerializedTestMetadata1::OCTET_22
  );
  EXPECT_EQ(
    buffer.getData()[23],
    SerializedTestMetadata1::OCTET_23
  );
  EXPECT_EQ(
    buffer.getData()[24],
    SerializedTestMetadata1::OCTET_24
  );
  EXPECT_EQ(
    buffer.getData()[25],
    SerializedTestMetadata1::OCTET_25
  );
  EXPECT_EQ(
    buffer.getData()[26],
    SerializedTestMetadata1::OCTET_26
  );
  EXPECT_EQ(
    buffer.getData()[27],
    SerializedTestMetadata1::OCTET_27
  );
  EXPECT_EQ(
    buffer.getData()[28],
    SerializedTestMetadata1::OCTET_28
  );
  EXPECT_EQ(
    buffer.getData()[29],
    SerializedTestMetadata1::OCTET_29
  );
  EXPECT_EQ(
    buffer.getData()[30],
    SerializedTestMetadata1::OCTET_30
  );
  EXPECT_EQ(
    buffer.getData()[31],
    SerializedTestMetadata1::OCTET_31
  );
  EXPECT_EQ(
    buffer.getData()[32],
    SerializedTestMetadata1::OCTET_32
  );
}

TEST(FilePacketMetadata, Deserialize)
{
  // Allocate buffer for serialized metadata
  U8 data[SerializedTestMetadata1::LENGTH];
  Fw::Buffer buffer(data, SerializedTestMetadata1::LENGTH);

  // Create "deserialized" header
  FilePacket::Header header = createTestHeader1();

  // Create an empty metadata to fill with deserialized data
  FilePacket::Metadata metadata;

  // Define serialized metadata
  data[0] = SerializedTestMetadata1::OCTET_00;
  data[1] = SerializedTestMetadata1::OCTET_01;
  data[2] = SerializedTestMetadata1::OCTET_02;
  data[3] = SerializedTestMetadata1::OCTET_03;
  data[4] = SerializedTestMetadata1::OCTET_04;
  data[5] = SerializedTestMetadata1::OCTET_05;
  data[6] = SerializedTestMetadata1::OCTET_06;
  data[7] = SerializedTestMetadata1::OCTET_07;
  data[8] = SerializedTestMetadata1::OCTET_08;
  data[9] = SerializedTestMetadata1::OCTET_09;
  data[10] = SerializedTestMetadata1::OCTET_10;
  data[11] = SerializedTestMetadata1::OCTET_11;
  data[12] = SerializedTestMetadata1::OCTET_12;
  data[13] = SerializedTestMetadata1::OCTET_13;
  data[14] = SerializedTestMetadata1::OCTET_14;
  data[15] = SerializedTestMetadata1::OCTET_15;
  data[16] = SerializedTestMetadata1::OCTET_16;
  data[17] = SerializedTestMetadata1::OCTET_17;
  data[18] = SerializedTestMetadata1::OCTET_18;
  data[19] = SerializedTestMetadata1::OCTET_19;
  data[20] = SerializedTestMetadata1::OCTET_20;
  data[21] = SerializedTestMetadata1::OCTET_21;
  data[22] = SerializedTestMetadata1::OCTET_22;
  data[23] = SerializedTestMetadata1::OCTET_23;
  data[24] = SerializedTestMetadata1::OCTET_24;
  data[25] = SerializedTestMetadata1::OCTET_25;
  data[26] = SerializedTestMetadata1::OCTET_26;
  data[27] = SerializedTestMetadata1::OCTET_27;
  data[28] = SerializedTestMetadata1::OCTET_28;
  data[29] = SerializedTestMetadata1::OCTET_29;
  data[30] = SerializedTestMetadata1::OCTET_30;
  data[31] = SerializedTestMetadata1::OCTET_31;
  data[32] = SerializedTestMetadata1::OCTET_32;

  // Call metadata deserialization function
  metadata.deserialize(buffer, 0, header);

  // Verify buffer contains data in the expected format
  EXPECT_EQ(
    metadata.reserved0,
    0
  );
  EXPECT_EQ(
    metadata.getClosureRequested(),
    FilePacket::ClosureRequested::REQUESTED
  );
  EXPECT_EQ(
    metadata.reserved1,
    0
  );
  EXPECT_EQ(
    metadata.getChecksumType(),
    FilePacket::ChecksumType::NULL_CHECKSUM
  );
  EXPECT_EQ(
    metadata.getFileSize(),
    16
  );
  EXPECT_EQ(
    strncmp(
      metadata.getSourceFilename(),
      "SourceFilename",
      metadata.getSourceFilenameLength()
    ),
    0
  );
  EXPECT_EQ(
    strncmp(
      metadata.getDestFilename(),
      "DestFilename",
      metadata.getDestFilenameLength()
    ),
    0
  );
}

TEST(FilePacketMetadata, SerializedLength)
{
  // Create header
  FilePacket::Header header = createTestHeader1();

  // Create metadata
  FilePacket::Metadata metadata = createTestMetadata1();

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    metadata.getSerializedLength(header),
    SerializedTestMetadata1::LENGTH
  );
}

}

}