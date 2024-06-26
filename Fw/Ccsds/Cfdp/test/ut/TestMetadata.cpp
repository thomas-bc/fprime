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
}

}

}