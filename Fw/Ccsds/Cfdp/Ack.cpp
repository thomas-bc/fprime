//! ============================================================================
//! @file   Ack.cpp
//! @brief  cpp file for a CFDP file packet Ack data field.
//! @author chownw
//! ============================================================================

#include <string.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/Ack.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>

namespace Fw
{

namespace Cfdp
{

FilePacket::DirectiveType FilePacket::Ack::directiveCode =
  FilePacket::DirectiveType::ACK;

FilePacket::Ack::
  Ack()
{
}

FilePacket::Ack::
  Ack(
    DirectiveType directiveCode,
    DirectiveSubtypeCode subtypeCode,
    ConditionCode conditionCode,
    TransactionStatus status
  )
{
  this->ackDirectiveCode = directiveCode;
  this->subtypeCode = subtypeCode;
  this->conditionCode = conditionCode;
  this->spare = 0;
  this->transactionStatus = status;
}

FilePacket::DirectiveType FilePacket::Ack::
  getDirectiveCode() const
{
  return this->ackDirectiveCode;
}

FilePacket::DirectiveSubtypeCode FilePacket::Ack::
  getSubtypeCode() const
{
  return this->subtypeCode;
}

FilePacket::ConditionCode FilePacket::Ack::
  getConditionCode() const
{
  return this->conditionCode;
}

FilePacket::TransactionStatus FilePacket::Ack::
  getTransactionStatus() const
{
  return this->transactionStatus;
}

void FilePacket::Ack::
  serialize(const Fw::Buffer& buf, U32 offset, const Header& header) const
{
  U8* data = buf.getData() + offset;

  // Serialize octet 0
  data[0] = static_cast<U8>(this->directiveCode);

  // Serialize octet 1
  data[1] = 0;
  data[1] |= (static_cast<U8>(this->ackDirectiveCode) & 15) << 4;
  data[1] |= static_cast<U8>(this->subtypeCode) & 15;

  // Serialize octet 2
  data[2] = 0;
  data[2] |= (static_cast<U8>(this->conditionCode) & 15) << 4;
  data[2] |= static_cast<U8>(this->transactionStatus) & 3;
}

void FilePacket::Ack::
  deserialize(const Fw::Buffer& buf, U32 offset, const Header& header)
{
  U8* data = buf.getData() + offset;

  // Deserialize octet 1
  this->ackDirectiveCode =
    static_cast<FilePacket::DirectiveType>((data[1] >> 4) & 15);
  this->subtypeCode =
    static_cast<FilePacket::DirectiveSubtypeCode>(data[1] & 15);

  // Deserialize octet 2
  this->conditionCode =
    static_cast<FilePacket::ConditionCode>((data[2] >> 4) & 15);
  this->spare = ((data[2] >> 2) & 3);
  this->transactionStatus =
    static_cast<FilePacket::TransactionStatus>(data[2] & 3);
}

U32 FilePacket::Ack::
  getSerializedLength(const Header& header) const
{
  return FixedSize::BYTES;
}

} // Cfdp

} // Fw
