//! ============================================================================
//! @file   Finished.cpp
//! @brief  CFDP file packet Finished test file.
//! @author chownw
//! ============================================================================

#include <gtest/gtest.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/Finished.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>
#include <Fw/Ccsds/Cfdp/test/ut/TestFilePacket.hpp>
#include <Fw/Types/Assert.hpp>

namespace Fw
{

namespace Cfdp
{

FilePacket::Finished TestFinished1::
  create()
{
  Fw::Cfdp::FilePacket::Finished finished(
    TestFinished1::Values::conditionCode,
    TestFinished1::Values::deliveryCode,
    TestFinished1::Values::fileStatus
  );

  return finished;
}

void TestFinished1::
  fillBuffer(Buffer &buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  data[0] = TestFinished1::Serialized::OCTET_00;
  data[1] = TestFinished1::Serialized::OCTET_01;
}

void TestFinished1::
  verifyBuffer(Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  EXPECT_EQ(
    data[0],
    TestFinished1::Serialized::OCTET_00
  );
  EXPECT_EQ(
    data[1],
    TestFinished1::Serialized::OCTET_01
  );
}

void TestFinished1::
  verifyObject(FilePacket::Finished& finished)
{
  EXPECT_EQ(
    finished.directiveCode,
    FilePacket::DirectiveType::FINISHED
  );
  EXPECT_EQ(
    finished.getConditionCode(),
    TestFinished1::Values::conditionCode
  );
  EXPECT_EQ(
    finished.spare,
    TestFinished1::Values::spare
  );
  EXPECT_EQ(
    finished.getDeliveryCode(),
    TestFinished1::Values::deliveryCode
  );
  EXPECT_EQ(
    finished.getFileStatus(),
    TestFinished1::Values::fileStatus
  );
}

TEST(FilePacketFinished, Serialize)
{
  // Allocate buffer for serialization
  U8 data[TestFinished1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestFinished1::Serialized::LENGTH);

  FilePacket::Header header = TestHeader1::create();
  FilePacket::Finished finished = TestFinished1::create();
  finished.serialize(buffer, 0, header);

  // Verify buffer
  TestFinished1::verifyBuffer(buffer, 0);
}

TEST(FilePacketFinished, Deserialize)
{
  // Allocate buffer for serialization
  U8 data[TestFinished1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestFinished1::Serialized::LENGTH);

  // Fill buffer with serialization
  TestFinished1::fillBuffer(buffer, 0);

  // Call deserialize function
  FilePacket::Header header = TestHeader1::create();
  FilePacket::Finished finished;
  finished.deserialize(buffer, 0, header);

  // Verify End-of-file
  TestFinished1::verifyObject(finished);
}

TEST(FilePacketFinished, Offset)
{
  // Test (de)serialization with arbitrary offset in the buffer
  U32 offset = 15;

  // Allocate buffer for serialization
  U8 data[TestFinished1::Serialized::LENGTH + offset];
  Fw::Buffer buffer(data, TestFinished1::Serialized::LENGTH + offset);

  // Test serialize function
  FilePacket::Header header = TestHeader1::create();
  FilePacket::Finished srcfinished = TestFinished1::create();
  srcfinished.serialize(buffer, offset, header);
  TestFinished1::verifyBuffer(buffer, offset);

  // Test deserialize function
  FilePacket::Finished destfinished;
  destfinished.deserialize(buffer, offset, header);
  TestFinished1::verifyObject(destfinished);
}

TEST(FilePacketFinished, SerializedLength)
{
  FilePacket::Header header = TestHeader1::create();
  FilePacket::Finished finished = TestFinished1::create();

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    finished.getSerializedLength(header),
    TestFinished1::Serialized::LENGTH
  );
}

} // namespace Cfdp

} // namespace Fw
