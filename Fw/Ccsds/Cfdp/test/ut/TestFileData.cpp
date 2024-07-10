//! ============================================================================
//! @file   TestFileData.cpp
//! @brief  CFDP file packet File Data test file.
//! @author chownw
//! ============================================================================

#include <gtest/gtest.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FileData.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>
#include <Fw/Ccsds/Cfdp/test/ut/TestFilePacket.hpp>
#include <Fw/Types/Assert.hpp>

namespace
{

// Compare File Data data.
//
bool compareData(const U8* data1, const U8* data2, U16 length)
{
  for (int i = 0; i < length; ++i)
  {
    if (data1[i] != data2[i])
    {
      return false;
    }
  }
  return true;
}

} //

namespace Fw
{

namespace Cfdp
{

FilePacket::FileData TestFileData1::
  create()
{
  Fw::Cfdp::FilePacket::FileData fileData(
    TestFileData1::Values::offset,
    TestFileData1::Values::fileDataLength,
    TestFileData1::Values::fileData,
    TestFileData1::Values::continuationState,
    TestFileData1::Values::metadataLength,
    TestFileData1::Values::metadata
  );

  return fileData;
}

void TestFileData1::
  fillBuffer(Buffer &buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  data[0] = TestFileData1::Serialized::OCTET_00;
  data[1] = TestFileData1::Serialized::OCTET_01;
  data[2] = TestFileData1::Serialized::OCTET_02;
  data[3] = TestFileData1::Serialized::OCTET_03;
  data[4] = TestFileData1::Serialized::OCTET_04;
  data[5] = TestFileData1::Serialized::OCTET_05;
  data[6] = TestFileData1::Serialized::OCTET_06;
  data[7] = TestFileData1::Serialized::OCTET_07;
  data[8] = TestFileData1::Serialized::OCTET_08;
  data[9] = TestFileData1::Serialized::OCTET_09;
  data[10] = TestFileData1::Serialized::OCTET_10;
  data[11] = TestFileData1::Serialized::OCTET_11;
  data[12] = TestFileData1::Serialized::OCTET_12;
  data[13] = TestFileData1::Serialized::OCTET_13;
  data[14] = TestFileData1::Serialized::OCTET_14;
  data[15] = TestFileData1::Serialized::OCTET_15;
}

void TestFileData1::
  verifyBuffer(Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  EXPECT_EQ(
    data[0],
    TestFileData1::Serialized::OCTET_00
  );
  EXPECT_EQ(
    data[1],
    TestFileData1::Serialized::OCTET_01
  );
  EXPECT_EQ(
    data[2],
    TestFileData1::Serialized::OCTET_02
  );
  EXPECT_EQ(
    data[3],
    TestFileData1::Serialized::OCTET_03
  );
  EXPECT_EQ(
    data[4],
    TestFileData1::Serialized::OCTET_04
  );
  EXPECT_EQ(
    data[5],
    TestFileData1::Serialized::OCTET_05
  );
  EXPECT_EQ(
    data[6],
    TestFileData1::Serialized::OCTET_06
  );
  EXPECT_EQ(
    data[7],
    TestFileData1::Serialized::OCTET_07
  );
  EXPECT_EQ(
    data[8],
    TestFileData1::Serialized::OCTET_08
  );
  EXPECT_EQ(
    data[9],
    TestFileData1::Serialized::OCTET_09
  );
  EXPECT_EQ(
    data[10],
    TestFileData1::Serialized::OCTET_10
  );
  EXPECT_EQ(
    data[11],
    TestFileData1::Serialized::OCTET_11
  );
  EXPECT_EQ(
    data[12],
    TestFileData1::Serialized::OCTET_12
  );
  EXPECT_EQ(
    data[13],
    TestFileData1::Serialized::OCTET_13
  );
  EXPECT_EQ(
    data[14],
    TestFileData1::Serialized::OCTET_14
  );
  EXPECT_EQ(
    data[15],
    TestFileData1::Serialized::OCTET_15
  );
}

void TestFileData1::
  verifyObject(FilePacket::FileData& fileData)
{
  EXPECT_EQ(
    fileData.getOffset(),
    TestFileData1::Values::offset
  );
  EXPECT_EQ(
    fileData.getFileDataLength(),
    TestFileData1::Values::fileDataLength
  );
  EXPECT_TRUE(
    compareData(
      fileData.getFileData(),
      TestFileData1::Values::fileData,
      TestFileData1::Values::fileDataLength
    )
  );
  EXPECT_TRUE(
    fileData.getFileData() != NULL
  );
  // NOTE: Don't check other values since they are meaningless for file data
  // with no segment metadata
}

FilePacket::FileData TestFileData2::
  create()
{
  Fw::Cfdp::FilePacket::FileData fileData(
    TestFileData2::Values::offset,
    TestFileData2::Values::fileDataLength,
    TestFileData2::Values::fileData,
    TestFileData2::Values::continuationState,
    TestFileData2::Values::metadataLength,
    TestFileData2::Values::metadata
  );

  return fileData;
}

void TestFileData2::
  fillBuffer(Buffer &buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  data[0] = TestFileData2::Serialized::OCTET_00;
  data[1] = TestFileData2::Serialized::OCTET_01;
  data[2] = TestFileData2::Serialized::OCTET_02;
  data[3] = TestFileData2::Serialized::OCTET_03;
  data[4] = TestFileData2::Serialized::OCTET_04;
  data[5] = TestFileData2::Serialized::OCTET_05;
  data[6] = TestFileData2::Serialized::OCTET_06;
  data[7] = TestFileData2::Serialized::OCTET_07;
  data[8] = TestFileData2::Serialized::OCTET_08;
  data[9] = TestFileData2::Serialized::OCTET_09;
  data[10] = TestFileData2::Serialized::OCTET_10;
  data[11] = TestFileData2::Serialized::OCTET_11;
  data[12] = TestFileData2::Serialized::OCTET_12;
  data[13] = TestFileData2::Serialized::OCTET_13;
  data[14] = TestFileData2::Serialized::OCTET_14;
  data[15] = TestFileData2::Serialized::OCTET_15;
  data[16] = TestFileData2::Serialized::OCTET_16;
  data[17] = TestFileData2::Serialized::OCTET_17;
  data[18] = TestFileData2::Serialized::OCTET_18;
  data[19] = TestFileData2::Serialized::OCTET_19;
  data[20] = TestFileData2::Serialized::OCTET_20;
  data[21] = TestFileData2::Serialized::OCTET_21;
  data[22] = TestFileData2::Serialized::OCTET_22;
  data[23] = TestFileData2::Serialized::OCTET_23;
  data[24] = TestFileData2::Serialized::OCTET_24;
}

void TestFileData2::
  verifyBuffer(Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  EXPECT_EQ(
    data[0],
    TestFileData2::Serialized::OCTET_00
  );
  EXPECT_EQ(
    data[1],
    TestFileData2::Serialized::OCTET_01
  );
  EXPECT_EQ(
    data[2],
    TestFileData2::Serialized::OCTET_02
  );
  EXPECT_EQ(
    data[3],
    TestFileData2::Serialized::OCTET_03
  );
  EXPECT_EQ(
    data[4],
    TestFileData2::Serialized::OCTET_04
  );
  EXPECT_EQ(
    data[5],
    TestFileData2::Serialized::OCTET_05
  );
  EXPECT_EQ(
    data[6],
    TestFileData2::Serialized::OCTET_06
  );
  EXPECT_EQ(
    data[7],
    TestFileData2::Serialized::OCTET_07
  );
  EXPECT_EQ(
    data[8],
    TestFileData2::Serialized::OCTET_08
  );
  EXPECT_EQ(
    data[9],
    TestFileData2::Serialized::OCTET_09
  );
  EXPECT_EQ(
    data[10],
    TestFileData2::Serialized::OCTET_10
  );
  EXPECT_EQ(
    data[11],
    TestFileData2::Serialized::OCTET_11
  );
  EXPECT_EQ(
    data[12],
    TestFileData2::Serialized::OCTET_12
  );
  EXPECT_EQ(
    data[13],
    TestFileData2::Serialized::OCTET_13
  );
  EXPECT_EQ(
    data[14],
    TestFileData2::Serialized::OCTET_14
  );
  EXPECT_EQ(
    data[15],
    TestFileData2::Serialized::OCTET_15
  );
  EXPECT_EQ(
    data[16],
    TestFileData2::Serialized::OCTET_16
  );
  EXPECT_EQ(
    data[17],
    TestFileData2::Serialized::OCTET_17
  );
  EXPECT_EQ(
    data[18],
    TestFileData2::Serialized::OCTET_18
  );
  EXPECT_EQ(
    data[19],
    TestFileData2::Serialized::OCTET_19
  );
  EXPECT_EQ(
    data[20],
    TestFileData2::Serialized::OCTET_20
  );
  EXPECT_EQ(
    data[21],
    TestFileData2::Serialized::OCTET_21
  );
  EXPECT_EQ(
    data[22],
    TestFileData2::Serialized::OCTET_22
  );
  EXPECT_EQ(
    data[23],
    TestFileData2::Serialized::OCTET_23
  );
  EXPECT_EQ(
    data[24],
    TestFileData2::Serialized::OCTET_24
  );
}

void TestFileData2::
  verifyObject(FilePacket::FileData& fileData)
{
  EXPECT_EQ(
    fileData.getOffset(),
    TestFileData2::Values::offset
  );
  EXPECT_EQ(
    fileData.getFileDataLength(),
    TestFileData2::Values::fileDataLength
  );
  EXPECT_TRUE(
    compareData(
      fileData.getFileData(),
      TestFileData2::Values::fileData,
      TestFileData2::Values::fileDataLength
    )
  );
  EXPECT_TRUE(
    fileData.getFileData() != NULL
  );
  EXPECT_EQ(
    fileData.getContinuationState(),
    TestFileData2::Values::continuationState
  );
  EXPECT_EQ(
    fileData.getSegmentMetadataLength(),
    TestFileData2::Values::metadataLength
  );
  EXPECT_TRUE(
    compareData(
      fileData.getSegmentMetadata(),
      TestFileData2::Values::metadata,
      TestFileData2::Values::metadataLength
    )
  );
  EXPECT_TRUE(
    fileData.getSegmentMetadata() != NULL
  );
}

TEST(FilePacketFileData, Serialize1)
{
  // Allocate buffer for serialization
  U8 data[TestFileData1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestFileData1::Serialized::LENGTH);

  FilePacket::Header header = TestHeader1::create();
  FilePacket::FileData fileData = TestFileData1::create();
  fileData.serialize(buffer, 0, header);

  // Verify buffer
  TestFileData1::verifyBuffer(buffer, 0);
}

TEST(FilePacketFileData, Serialize2)
{
  // Allocate buffer for serialization
  U8 data[TestFileData2::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestFileData2::Serialized::LENGTH);

  FilePacket::Header header = TestHeader2::create();
  FilePacket::FileData fileData = TestFileData2::create();
  fileData.serialize(buffer, 0, header);

  // Verify buffer
  TestFileData2::verifyBuffer(buffer, 0);
}

TEST(FilePacketFileData, Deserialize1)
{
  // Allocate buffer for serialization
  U8 data[TestFileData1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestFileData1::Serialized::LENGTH);

  // Fill buffer with serialization
  TestFileData1::fillBuffer(buffer, 0);

  // Call deserialize function
  FilePacket::Header header = TestHeader1::create();
  FilePacket::FileData fileData;
  fileData.deserialize(buffer, 0, header);

  // Verify fileData
  TestFileData1::verifyObject(fileData);
}

TEST(FilePacketFileData, Deserialize2)
{
  // Allocate buffer for serialization
  U8 data[TestFileData2::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestFileData2::Serialized::LENGTH);

  // Fill buffer with serialization
  TestFileData2::fillBuffer(buffer, 0);

  // Call deserialize function
  FilePacket::Header header = TestHeader2::create();
  FilePacket::FileData fileData;
  fileData.deserialize(buffer, 0, header);

  // Verify fileData
  TestFileData2::verifyObject(fileData);
}

TEST(FilePacketFileData, FileDataMetadataLength0)
{
  FilePacket::Header header = TestHeader1::create();
  FilePacket::FileData fileData = TestFileData1::create();

  // Sanity check header and file data make sense
  EXPECT_EQ(
    TestHeader1::Values::dataFieldLength,
    TestFileData1::Serialized::LENGTH
  );
  // Verify getFileDataMetadataLength returns the expected length
  EXPECT_EQ(
    fileData.getFileDataMetadataLength(header),
    4 // Length not including file data
  );
}

TEST(FilePacketFileData, FileDataMetadataLength1)
{
  FilePacket::Header header = TestHeader2::create();
  FilePacket::FileData fileData = TestFileData2::create();

  // Sanity check header and file data make sense
  EXPECT_EQ(
    TestHeader2::Values::dataFieldLength,
    TestFileData2::Serialized::LENGTH
  );
  // Verify getFileDataMetadataLength returns the expected length
  EXPECT_EQ(
    fileData.getFileDataMetadataLength(header),
    13 // Length not including file data
  );
}

TEST(FilePacketFileData, SerializedLength1)
{
  FilePacket::Header header = TestHeader1::create();
  FilePacket::FileData fileData = TestFileData1::create();

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    fileData.getSerializedLength(header),
    TestFileData1::Serialized::LENGTH
  );
}

TEST(FilePacketFileData, SerializedLength2)
{
  FilePacket::Header header = TestHeader2::create();
  FilePacket::FileData fileData = TestFileData2::create();

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    fileData.getSerializedLength(header),
    TestFileData2::Serialized::LENGTH
  );
}

} // Cfdp

} // Fw
