//! ============================================================================
//! @file   TestFilePacket.hpp
//! @brief  hpp file for CFDP file packet tests.
//! @author chownw
//! ============================================================================

#ifndef FW_CFDP_TESTFILEPACKET_HPP
#define FW_CFDP_TESTFILEPACKET_HPP

#include <string.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>
#include <Fw/Ccsds/Cfdp/Metadata.hpp>

namespace Fw
{

namespace Cfdp
{

/*
 * Expected values and corresponding serialization for a test header.
 */
namespace TestHeader1
{
  namespace Values
  {
    const U8 version =
        0x001;

    const FilePacket::Type type =
      FilePacket::Type::FILE_DIRECTIVE;

    const FilePacket::Direction direction =
      FilePacket::Direction::TOWARD_RECEIVER;

    const FilePacket::TransmissionMode transmissionMode =
      FilePacket::TransmissionMode::UNACKNOWLEDGED;

    const FilePacket::CrcFlag crcFlag =
      FilePacket::CrcFlag::NOT_PRESENT;

    const FilePacket::LargeFileFlag largeFileFlag =
      FilePacket::LargeFileFlag::SMALL_FILE;

    const FilePacket::SegmentationControl segmentationControl =
      FilePacket::SegmentationControl::NOT_PRESERVED;

    const FilePacket::SegmentMetadataFlag segmentMetadataFlag =
      FilePacket::SegmentMetadataFlag::NOT_PRESENT;

    const U8 transSeqNumLength = 3;

    const U64 transSeqNumber = 5;

    const U8 entityIdLength = 3;

    const U64 sourceEntityId = 6;

    const U64 destEntityId = 7;

    const U16 dataFieldLength = 4;
  }

  enum Serialized : U8
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

  // Create a header with the above values.
  FilePacket::Header create();

  // Fill buffer with serialized values.
  void fillBuffer(Buffer& buf);

  // Verify buffer contains data in the expected format
  void verifyBuffer(Buffer& buf, U32 offset);

  // Verify header contains expected values after deserialization
  void verifyHeader(FilePacket::Header& header);
};

/*
 * Expected values and corresponding serialization for a test header.
 */
namespace TestHeader2
{
  namespace Values
  {
    const U8 version =
        0x001;

    const FilePacket::Type type =
      FilePacket::Type::FILE_DIRECTIVE;

    const FilePacket::Direction direction =
      FilePacket::Direction::TOWARD_RECEIVER;

    const FilePacket::TransmissionMode transmissionMode =
      FilePacket::TransmissionMode::UNACKNOWLEDGED;

    const FilePacket::CrcFlag crcFlag =
      FilePacket::CrcFlag::NOT_PRESENT;

    const FilePacket::LargeFileFlag largeFileFlag =
      FilePacket::LargeFileFlag::LARGE_FILE;

    const FilePacket::SegmentationControl segmentationControl =
      FilePacket::SegmentationControl::NOT_PRESERVED;

    const FilePacket::SegmentMetadataFlag segmentMetadataFlag =
      FilePacket::SegmentMetadataFlag::NOT_PRESENT;

    const U8 transSeqNumLength = 3;

    const U64 transSeqNumber = 5;

    const U8 entityIdLength = 3;

    const U64 sourceEntityId = 6;

    const U64 destEntityId = 7;

    const U16 dataFieldLength = 4;
  }

  enum Serialized : U8
  {
    OCTET_00 = 0x25, // |0 0 1|0|0|1|0|1| - Version through large file flag
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

  // Create a header with the above values.
  FilePacket::Header create();

  // Fill buffer with serialized values.
  void fillBuffer(Buffer& buf);
};

/*
 * Expected values and corresponding serialization for a test metadata.
 */
namespace TestMetadata1
{
  namespace Values
  {
    const U8 reserved0 = 0;

    const FilePacket::ClosureRequested closureRequested =
      FilePacket::ClosureRequested::REQUESTED;

    const U8 reserved1 = 0;

    const FilePacket::ChecksumType checksumType =
      FilePacket::ChecksumType::NULL_CHECKSUM;

    const U64 fileSize = 16;

    const char* const sourceFilename = "SourceFilename";

    const U8 sourceFilenameLength = strlen(sourceFilename);

    const char* const destFilename = "DestFilename";

    const U8 destFilenameLength = strlen(destFilename);
  }

  enum Serialized : U8
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

  // Create a metadata with the above values.
  FilePacket::Metadata create();

  // Fill buffer with serialized values.
  void fillBuffer(Buffer& buf);

  // Verify buffer contains data in the expected format
  void verifyBuffer(Buffer& buf, U32 offset);

  // Verify metadata contains expected values after deserialization
  void verifyMetadata(FilePacket::Metadata& metadata);
};

} // namespace Cfdp

} // namespace Fw

#endif // FW_CFDP_TESTFILEPACKET_HPP
