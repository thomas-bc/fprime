//! ============================================================================
//! @file   TestAck.cpp
//! @brief  CFDP file packet Ack test file.
//! @author chownw
//! ============================================================================

#include <gtest/gtest.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/Ack.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>
#include <Fw/Ccsds/Cfdp/test/ut/TestFilePacket.hpp>
#include <Fw/Types/Assert.hpp>

namespace Fw
{

namespace Cfdp
{

FilePacket::Ack TestAck1::
  create()
{
  Fw::Cfdp::FilePacket::Ack ack(
    TestAck1::Values::ackDirectiveCode,
    TestAck1::Values::subtypeCode,
    TestAck1::Values::conditionCode,
    TestAck1::Values::transactionStatus
  );

  return ack;
}

void TestAck1::
  fillBuffer(Buffer &buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  data[0] = TestAck1::Serialized::OCTET_00;
  data[1] = TestAck1::Serialized::OCTET_01;
  data[2] = TestAck1::Serialized::OCTET_02;
}

void TestAck1::
  verifyBuffer(Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  EXPECT_EQ(
    data[0],
    TestAck1::Serialized::OCTET_00
  );
  EXPECT_EQ(
    data[1],
    TestAck1::Serialized::OCTET_01
  );
  EXPECT_EQ(
    data[2],
    TestAck1::Serialized::OCTET_02
  );
}

void TestAck1::
  verifyObject(FilePacket::Ack& ack)
{
  EXPECT_EQ(
    ack.directiveCode,
    FilePacket::DirectiveType::ACK
  );
  EXPECT_EQ(
    ack.getDirectiveCode(),
    TestAck1::Values::ackDirectiveCode
  );
  EXPECT_EQ(
    ack.getSubtypeCode(),
    TestAck1::Values::subtypeCode
  );
  EXPECT_EQ(
    ack.getConditionCode(),
    TestAck1::Values::conditionCode
  );
  EXPECT_EQ(
    ack.spare,
    TestAck1::Values::spare
  );
  EXPECT_EQ(
    ack.getTransactionStatus(),
    TestAck1::Values::transactionStatus
  );
}

TEST(FilePacketAck, Serialize)
{
  // Allocate buffer for serialization
  U8 data[TestAck1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestAck1::Serialized::LENGTH);

  FilePacket::Header header = TestHeader1::create();
  FilePacket::Ack ack = TestAck1::create();
  ack.serialize(buffer, 0, header);

  // Verify buffer
  TestAck1::verifyBuffer(buffer, 0);
}

TEST(FilePacketAck, Deserialize)
{
  // Allocate buffer for serialization
  U8 data[TestAck1::Serialized::LENGTH];
  Fw::Buffer buffer(data, TestAck1::Serialized::LENGTH);

  // Fill buffer with serialization
  TestAck1::fillBuffer(buffer, 0);

  // Call deserialize function
  FilePacket::Header header = TestHeader1::create();
  FilePacket::Ack ack;
  ack.deserialize(buffer, 0, header);

  // Verify End-of-file
  TestAck1::verifyObject(ack);
}

TEST(FilePacketAck, Offset)
{
  // Test (de)serialization with arbitrary offset in the buffer
  U32 offset = 15;

  // Allocate buffer for serialization
  U8 data[TestAck1::Serialized::LENGTH + offset];
  Fw::Buffer buffer(data, TestAck1::Serialized::LENGTH + offset);

  // Test serialize function
  FilePacket::Header header = TestHeader1::create();
  FilePacket::Ack srcAck = TestAck1::create();
  srcAck.serialize(buffer, offset, header);
  TestAck1::verifyBuffer(buffer, offset);

  // Test deserialize function
  FilePacket::Ack destAck;
  destAck.deserialize(buffer, offset, header);
  TestAck1::verifyObject(destAck);
}

TEST(FilePacketAck, SerializedLength)
{
  FilePacket::Header header = TestHeader1::create();
  FilePacket::Ack ack = TestAck1::create();

  // Verify getSerializedLength returns the expected length
  EXPECT_EQ(
    ack.getSerializedLength(header),
    TestAck1::Serialized::LENGTH
  );
}

} // namespace Cfdp

} // namespace Fw
