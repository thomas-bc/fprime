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
#include <Fw/Ccsds/Cfdp/EndOfFile.hpp>
#include <Fw/Ccsds/Cfdp/FileData.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Finished.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>
#include <Fw/Ccsds/Cfdp/Metadata.hpp>

namespace Fw
{

namespace Cfdp
{

/*
 * Test Header helpers.
 */
namespace TestHeader1
{
  namespace Values
  {
    const U8 version =
        0x001;

    const FilePacket::DataType type =
      FilePacket::DataType::FILE_DIRECTIVE;

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

    const U16 dataFieldLength = 16;
  }

  enum Serialized : U8
  {
    OCTET_00 = 0x24, // |0 0 1|0|0|1|0|0| - Version through large file flag
    OCTET_01 = 0x00, // |0 0 0 0 0 0 0 0| - Data field length bits 0-7
    OCTET_02 = 0x10, // |0 0 0 1 0 0 0 0| - Data field length bits 8-15
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

  // Create a test object with the above values.
  FilePacket::Header create();

  // Fill buffer with the expected serialization.
  void fillBuffer(Buffer& buf, U32 offset);

  // Verify data in buffer matches the expected serialization.
  void verifyBuffer(Buffer& buf, U32 offset);

  // Verify object contains the expected values.
  void verifyObject(FilePacket::Header& header);
};

/*
 * Test Header helpers.
 */
namespace TestHeader2
{
  namespace Values
  {
    const U8 version =
        0x001;

    const FilePacket::DataType type =
      FilePacket::DataType::FILE_DATA;

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
      FilePacket::SegmentMetadataFlag::PRESENT;

    const U8 transSeqNumLength = 3;

    const U64 transSeqNumber = 5;

    const U8 entityIdLength = 3;

    const U64 sourceEntityId = 6;

    const U64 destEntityId = 7;

    const U16 dataFieldLength = 25;
  }

  enum Serialized : U8
  {
    OCTET_00 = 0x35, // |0 0 1|1|0|1|0|1| - Version through large file flag
    OCTET_01 = 0x00, // |0 0 0 0 0 0 0 0| - Data field length bits 0-7
    OCTET_02 = 0x19, // |0 0 0 1 1 0 0 1| - Data field length bits 8-15
    OCTET_03 = 0x2A, // |0|0 1 0|1|0 1 0| - Seg control through seq num length
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

  // Create a test object with the above values.
  FilePacket::Header create();

  // Fill buffer with the expected serialization.
  void fillBuffer(Buffer& buf, U32 offset);

  // Verify data in buffer matches the expected serialization.
  void verifyBuffer(Buffer& buf, U32 offset);

  // Verify object contains the expected values.
  void verifyObject(FilePacket::Header& header);
};

/*
 * Test File Data helpers.
 */
namespace TestFileData1
{
  namespace Values
  {
    const U64 offset =
      154;

    const U8 fileData[] = {'T', 'e', 's', 't', 'F', 'i',
                           'l', 'e', 'D', 'a', 't', 'a'};

    const U16 fileDataLength = 12;

    /*
     * These values should be ignored when (de)serializing.
     */

    const FilePacket::ContinuationState continuationState =
      FilePacket::ContinuationState::NONE;

    const U8* const metadata = NULL;

    const U8 metadataLength = 0;
  }

  enum Serialized : U8
  {
    OCTET_00 = 0x00, // |0 0 0 0 0 0 0 0| - Offset value octet 0.
    OCTET_01 = 0x00, // |0 0 0 0 0 0 0 0| - Offset value octet 1.
    OCTET_02 = 0x00, // |0 0 0 0 0 0 0 0| - Offset value octet 2.
    OCTET_03 = 0x9A, // |1 0 0 1 1 0 1 0| - Offset value octet 3.
    OCTET_04 = 0x54, // |0 1 0 1 0 1 0 0| - File data octet 0.
    OCTET_05 = 0x65, // |0 1 1 0 0 1 0 1| - File data octet 1.
    OCTET_06 = 0x73, // |0 1 1 1 0 0 1 1| - File data octet 2.
    OCTET_07 = 0x74, // |0 1 1 1 0 1 0 0| - File data octet 3.
    OCTET_08 = 0x46, // |0 1 0 0 0 1 1 0| - File data octet 4.
    OCTET_09 = 0x69, // |0 1 1 0 1 0 0 1| - File data octet 5.
    OCTET_10 = 0x6C, // |0 1 1 0 1 1 0 0| - File data octet 6.
    OCTET_11 = 0x65, // |0 1 1 0 0 1 0 1| - File data octet 7.
    OCTET_12 = 0x44, // |0 1 0 0 0 1 0 0| - File data octet 8.
    OCTET_13 = 0x61, // |0 1 1 0 0 0 0 1| - File data octet 9.
    OCTET_14 = 0x74, // |0 1 1 1 0 1 0 0| - File data octet 10.
    OCTET_15 = 0x61, // |0 1 1 0 0 0 0 1| - File data octet 11.
    LENGTH = 16,
  };

  // Create a test object with the above values.
  FilePacket::FileData create();

  // Fill buffer with the expected serialization.
  void fillBuffer(Buffer& buf, U32 offset);

  // Verify data in buffer matches the expected serialization.
  void verifyBuffer(Buffer& buf, U32 offset);

  // Verify object contains the expected values.
  void verifyObject(FilePacket::FileData& fileData);
};

/*
 * Test File Data helpers.
 */
namespace TestFileData2
{
  namespace Values
  {
    const U64 offset =
      154;

    const U8 fileData[] = {'T', 'e', 's', 't', 'F', 'i',
                           'l', 'e', 'D', 'a', 't', 'a'};

    const U16 fileDataLength = 12;

    const FilePacket::ContinuationState continuationState =
      FilePacket::ContinuationState::BOTH;

    const U8 metadata[] = {'M', 'E', 'T', 'A'};

    const U8 metadataLength = 4;
  }

  enum Serialized : U8
  {
    OCTET_00 = 0xC4, // |1 1|0 0 0 1 0 0| - State through metadata length.
    OCTET_01 = 0x4D, // |0 1 0 0 1 1 0 1| - Metadata octet 0.
    OCTET_02 = 0x45, // |0 1 0 0 0 1 0 1| - Metadata octet 1.
    OCTET_03 = 0x54, // |0 1 0 1 0 1 0 0| - Metadata octet 2.
    OCTET_04 = 0x41, // |0 1 0 0 0 0 0 1| - Metadata octet 3.
    OCTET_05 = 0x00, // |0 0 0 0 0 0 0 0| - Offset value octet 0.
    OCTET_06 = 0x00, // |0 0 0 0 0 0 0 0| - Offset value octet 1.
    OCTET_07 = 0x00, // |0 0 0 0 0 0 0 0| - Offset value octet 2.
    OCTET_08 = 0x00, // |0 0 0 0 0 0 0 0| - Offset value octet 3.
    OCTET_09 = 0x00, // |0 0 0 0 0 0 0 0| - Offset value octet 4.
    OCTET_10 = 0x00, // |0 0 0 0 0 0 0 0| - Offset value octet 5.
    OCTET_11 = 0x00, // |0 0 0 0 0 0 0 0| - Offset value octet 6.
    OCTET_12 = 0x9A, // |1 0 0 1 1 0 1 0| - Offset value octet 7.
    OCTET_13 = 0x54, // |0 1 0 1 0 1 0 0| - File data octet 0.
    OCTET_14 = 0x65, // |0 1 1 0 0 1 0 1| - File data octet 1.
    OCTET_15 = 0x73, // |0 1 1 1 0 0 1 1| - File data octet 2.
    OCTET_16 = 0x74, // |0 1 1 1 0 1 0 0| - File data octet 3.
    OCTET_17 = 0x46, // |0 1 0 0 0 1 1 0| - File data octet 4.
    OCTET_18 = 0x69, // |0 1 1 0 1 0 0 1| - File data octet 5.
    OCTET_19 = 0x6C, // |0 1 1 0 1 1 0 0| - File data octet 6.
    OCTET_20 = 0x65, // |0 1 1 0 0 1 0 1| - File data octet 7.
    OCTET_21 = 0x44, // |0 1 0 0 0 1 0 0| - File data octet 8.
    OCTET_22 = 0x61, // |0 1 1 0 0 0 0 1| - File data octet 9.
    OCTET_23 = 0x74, // |0 1 1 1 0 1 0 0| - File data octet 10.
    OCTET_24 = 0x61, // |0 1 1 0 0 0 0 1| - File data octet 11.
    LENGTH = 25,
  };

  // Create a test object with the above values.
  FilePacket::FileData create();

  // Fill buffer with the expected serialization.
  void fillBuffer(Buffer& buf, U32 offset);

  // Verify data in buffer matches the expected serialization.
  void verifyBuffer(Buffer& buf, U32 offset);

  // Verify object contains the expected values.
  void verifyObject(FilePacket::FileData& fileData);
};

/*
 * Test EndOfFile helpers.
 */
namespace TestEndOfFile1
{
  namespace Values
  {
    const FilePacket::ConditionCode conditionCode =
      FilePacket::ConditionCode::NO_ERROR;

    const U8 spare = 0;

    const U32 fileChecksum = 0xA4B8;

    const U64 fileSize = 128;
  }

  enum Serialized : U8
  {
    OCTET_00 = 0x04, // |0 0 0 0 0 1 0 0| - End-of-file directive code.
    OCTET_01 = 0x00, // |0 0 0 0|0 0 0 0| - Condition code through spare.
    OCTET_02 = 0x00, // |0 0 0 0 0 0 0 0| - File checksum octet 0.
    OCTET_03 = 0x00, // |0 0 0 0 0 0 0 0| - File checksum octet 1.
    OCTET_04 = 0xA4, // |1 0 1 0 0 1 0 0| - File checksum octet 2.
    OCTET_05 = 0xB8, // |1 0 1 1 1 0 0 0| - File checksum octet 3.
    OCTET_06 = 0x00, // |0 0 0 0 0 0 0 0| - File size value octet 0.
    OCTET_07 = 0x00, // |0 0 0 0 0 0 0 0| - File size value octet 1.
    OCTET_08 = 0x00, // |0 0 0 0 0 0 0 0| - File size value octet 2.
    OCTET_09 = 0x80, // |1 0 0 0 0 0 0 0| - File size value octet 3.
    LENGTH = 10,
  };

  // Create a test object with the above values.
  FilePacket::EndOfFile create();

  // Fill buffer with the expected serialization.
  void fillBuffer(Buffer& buf, U32 offset);

  // Verify data in buffer matches the expected serialization.
  void verifyBuffer(Buffer& buf, U32 offset);

  // Verify object contains the expected values.
  void verifyObject(FilePacket::EndOfFile& endOfFile);
};

/*
 * Test Finished helpers.
 */
namespace TestFinished1
{
  namespace Values
  {
    const FilePacket::ConditionCode conditionCode =
      FilePacket::ConditionCode::NO_ERROR;

    const U8 spare = 0;

    const FilePacket::DeliveryCode deliveryCode =
      FilePacket::DeliveryCode::DATA_COMPLETE;

    const FilePacket::FileStatus fileStatus =
      FilePacket::FileStatus::SUCCESS;
  }

  enum Serialized : U8
  {
    OCTET_00 = 0x05, // |0 0 0 0 0 1 0 1| - Finished directive code.
    OCTET_01 = 0x02, // |0 0 0 0|0|0|1|0| - Condition code through file status.
    LENGTH = 2,
  };

  // Create a test object with the above values.
  FilePacket::Finished create();

  // Fill buffer with the expected serialization.
  void fillBuffer(Buffer& buf, U32 offset);

  // Verify data in buffer matches the expected serialization.
  void verifyBuffer(Buffer& buf, U32 offset);

  // Verify object contains the expected values.
  void verifyObject(FilePacket::Finished& finished);
};

/*
 * Test Metadata helpers.
 */namespace TestMetadata1
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
    OCTET_00 = 0x07, // |0 0 0 0 0 1 1 1| - Metadata directive code.
    OCTET_01 = 0x4F, // |0|1|0|0|1|1|1|1| - Reserved through checksum type.
    OCTET_02 = 0x00, // |0 0 0 0 0 0 0 0| - Small file size octet 0.
    OCTET_03 = 0x00, // |0 0 0 0 0 0 0 0| - Small file size octet 1.
    OCTET_04 = 0x00, // |0 0 0 0 0 0 0 0| - Small file size octet 2.
    OCTET_05 = 0x10, // |0 0 0 1 0 0 0 0| - Small file size octet 3.
    OCTET_06 = 0x0E, // |0 0 0 0 1 1 1 0| - Source file name LV length.
    OCTET_07 = 0x53, // |0 1 0 1 0 0 1 1| - Source file name LV value octet 0.
    OCTET_08 = 0x6F, // |0 1 1 0 1 1 1 1| - Source file name LV value octet 1.
    OCTET_09 = 0x75, // |0 1 1 1 0 1 0 1| - Source file name LV value octet 2.
    OCTET_10 = 0x72, // |0 1 1 1 0 0 1 0| - Source file name LV value octet 3.
    OCTET_11 = 0x63, // |0 1 1 0 0 0 1 1| - Source file name LV value octet 4.
    OCTET_12 = 0x65, // |0 1 1 0 0 1 0 1| - Source file name LV value octet 5.
    OCTET_13 = 0x46, // |0 1 0 0 0 1 1 0| - Source file name LV value octet 6.
    OCTET_14 = 0x69, // |0 1 1 0 1 0 0 1| - Source file name LV value octet 7.
    OCTET_15 = 0x6C, // |0 1 1 0 1 1 0 0| - Source file name LV value octet 8.
    OCTET_16 = 0x65, // |0 1 1 0 0 1 0 1| - Source file name LV value octet 9.
    OCTET_17 = 0x6E, // |0 1 1 0 1 1 1 0| - Source file name LV value octet 10.
    OCTET_18 = 0x61, // |0 1 1 0 0 0 0 1| - Source file name LV value octet 11.
    OCTET_19 = 0x6D, // |0 1 1 0 1 1 0 1| - Source file name LV value octet 12.
    OCTET_20 = 0x65, // |0 1 1 0 0 1 0 1| - Source file name LV value octet 13.
    OCTET_21 = 0x0C, // |0 0 0 0 1 1 0 0| - Dest file name LV length.
    OCTET_22 = 0x44, // |0 1 0 0 0 1 0 0| - Dest file name LV value octet 0.
    OCTET_23 = 0x65, // |0 1 1 0 0 1 0 1| - Dest file name LV value octet 1.
    OCTET_24 = 0x73, // |0 1 1 1 0 0 1 1| - Dest file name LV value octet 2.
    OCTET_25 = 0x74, // |0 1 1 1 0 1 0 0| - Dest file name LV value octet 3.
    OCTET_26 = 0x46, // |0 1 0 0 0 1 1 0| - Dest file name LV value octet 4.
    OCTET_27 = 0x69, // |0 1 1 0 1 0 0 1| - Dest file name LV value octet 5.
    OCTET_28 = 0x6C, // |0 1 1 0 1 1 0 0| - Dest file name LV value octet 6.
    OCTET_29 = 0x65, // |0 1 1 0 0 1 0 1| - Dest file name LV value octet 7.
    OCTET_30 = 0x6E, // |0 1 1 0 1 1 1 0| - Dest file name LV value octet 8.
    OCTET_31 = 0x61, // |0 1 1 0 0 0 0 1| - Dest file name LV value octet 9.
    OCTET_32 = 0x6D, // |0 1 1 0 1 1 0 1| - Dest file name LV value octet 10.
    OCTET_33 = 0x65, // |0 1 1 0 0 1 0 1| - Dest file name LV value octet 11.
    LENGTH = 34,
  };

  // Create a test object with the above values.
  FilePacket::Metadata create();

  // Fill buffer with the expected serialization.
  void fillBuffer(Buffer& buf, U32 offset);

  // Verify data in buffer matches the expected serialization.
  void verifyBuffer(Buffer& buf, U32 offset);

  // Verify object contains the expected values.
  void verifyObject(FilePacket::Metadata& metadata);
};

} // namespace Cfdp

} // namespace Fw

#endif // FW_CFDP_TESTFILEPACKET_HPP
