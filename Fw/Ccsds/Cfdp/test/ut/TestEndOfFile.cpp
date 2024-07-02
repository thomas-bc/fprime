//! ============================================================================
//! @file   TestEndOfFile.cpp
//! @brief  CFDP file packet End-of-file test file.
//! @author chownw
//! ============================================================================

#include <gtest/gtest.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/EndOfFile.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>
#include <Fw/Ccsds/Cfdp/test/ut/TestFilePacket.hpp>
#include <Fw/Types/Assert.hpp>

namespace Fw
{

namespace Cfdp
{

FilePacket::EndOfFile TestEndOfFile1::
  create()
{
  Fw::Cfdp::FilePacket::EndOfFile endOfFile(
    TestEndOfFile1::Values::conditionCode,
    TestEndOfFile1::Values::fileChecksum,
    TestEndOfFile1::Values::fileSize
  );

  return endOfFile;
}

void TestEndOfFile1::
  fillBuffer(Buffer &buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  data[0] = TestEndOfFile1::Serialized::OCTET_00;
  data[1] = TestEndOfFile1::Serialized::OCTET_01;
  data[2] = TestEndOfFile1::Serialized::OCTET_02;
  data[3] = TestEndOfFile1::Serialized::OCTET_03;
  data[4] = TestEndOfFile1::Serialized::OCTET_04;
  data[5] = TestEndOfFile1::Serialized::OCTET_05;
  data[6] = TestEndOfFile1::Serialized::OCTET_06;
  data[7] = TestEndOfFile1::Serialized::OCTET_07;
  data[8] = TestEndOfFile1::Serialized::OCTET_08;
  data[9] = TestEndOfFile1::Serialized::OCTET_09;
}

void TestEndOfFile1::
  verifyBuffer(Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  EXPECT_EQ(
    data[0],
    TestEndOfFile1::Serialized::OCTET_00
  );
  EXPECT_EQ(
    data[1],
    TestEndOfFile1::Serialized::OCTET_01
  );
  EXPECT_EQ(
    data[2],
    TestEndOfFile1::Serialized::OCTET_02
  );
  EXPECT_EQ(
    data[3],
    TestEndOfFile1::Serialized::OCTET_03
  );
  EXPECT_EQ(
    data[4],
    TestEndOfFile1::Serialized::OCTET_04
  );
  EXPECT_EQ(
    data[5],
    TestEndOfFile1::Serialized::OCTET_05
  );
  EXPECT_EQ(
    data[6],
    TestEndOfFile1::Serialized::OCTET_06
  );
  EXPECT_EQ(
    data[7],
    TestEndOfFile1::Serialized::OCTET_07
  );
  EXPECT_EQ(
    data[8],
    TestEndOfFile1::Serialized::OCTET_08
  );
  EXPECT_EQ(
    data[9],
    TestEndOfFile1::Serialized::OCTET_09
  );
}

void TestEndOfFile1::
  verifyObject(FilePacket::EndOfFile& endOfFile)
{
  EXPECT_EQ(
    endOfFile.directiveCode,
    FilePacket::DirectiveType::END_OF_FILE
  );
  EXPECT_EQ(
    endOfFile.getConditionCode(),
    TestEndOfFile1::Values::conditionCode
  );
  EXPECT_EQ(
    endOfFile.spare,
    TestEndOfFile1::Values::spare
  );
  EXPECT_EQ(
    endOfFile.getFileChecksum(),
    TestEndOfFile1::Values::fileChecksum
  );
  EXPECT_EQ(
    endOfFile.getFileSize(),
    TestEndOfFile1::Values::fileSize
  );
}

TEST(FilePacketEndOfFile, Serialize)
{
  // Allocate buffer for serialization
  U8 data[TestEndOfFile1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestEndOfFile1::Serialized::LENGTH);

  FilePacket::Header header = TestHeader1::create();
  FilePacket::EndOfFile endOfFile = TestEndOfFile1::create();
  endOfFile.serialize(buffer, 0, header);

  // Verify buffer
  TestEndOfFile1::verifyBuffer(buffer, 0);
}

TEST(FilePacketEndOfFile, Deserialize)
{
  // Allocate buffer for serialization
  U8 data[TestEndOfFile1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestEndOfFile1::Serialized::LENGTH);

  // Fill buffer with serialization
  TestEndOfFile1::fillBuffer(buffer, 0);

  // Call deserialize function
  FilePacket::Header header = TestHeader1::create();
  FilePacket::EndOfFile endOfFile;
  endOfFile.deserialize(buffer, 0, header);

  // Verify End-of-file
  TestEndOfFile1::verifyObject(endOfFile);
}

TEST(FilePacketEndOfFile, Offset)
{
  // Test (de)serialization with arbitrary offset in the buffer
  U32 offset = 15;

  // Allocate buffer for serialization
  U8 data[TestEndOfFile1::Serialized::LENGTH + offset];
  Fw::Buffer buffer(data, TestEndOfFile1::Serialized::LENGTH + offset);

  // Test serialize function
  FilePacket::Header header = TestHeader1::create();
  FilePacket::EndOfFile srcEndOfFile = TestEndOfFile1::create();
  srcEndOfFile.serialize(buffer, offset, header);
  TestEndOfFile1::verifyBuffer(buffer, offset);

  // Test deserialize function
  FilePacket::EndOfFile destEndOfFile;
  destEndOfFile.deserialize(buffer, offset, header);
  TestEndOfFile1::verifyObject(destEndOfFile);
}

TEST(FilePacketEndOfFile, SerializedLength)
{
  FilePacket::Header header = TestHeader1::create();
  FilePacket::EndOfFile endOfFile = TestEndOfFile1::create();

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    endOfFile.getSerializedLength(header),
    TestEndOfFile1::Serialized::LENGTH
  );
}

} // namespace Cfdp

} // namespace Fw
