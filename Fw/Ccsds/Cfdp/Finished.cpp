//! ============================================================================
//! @file   EndOfFile.cpp
//! @brief  cpp file for a CFDP file packet Finished data field.
//! @author chownw
//! ============================================================================

#include <string.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/Finished.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>

namespace Fw
{

namespace Cfdp
{

FilePacket::DirectiveType FilePacket::Finished::directiveCode =
  FilePacket::DirectiveType::FINISHED;

FilePacket::Finished::
  Finished()
{
}

FilePacket::Finished::
  Finished(
    ConditionCode conditionCode,
    DeliveryCode deliveryCode,
    FileStatus fileStatus
  )
{
  this->conditionCode = conditionCode;
  this->spare = 0;
  this->deliveryCode = deliveryCode;
  this->fileStatus = fileStatus;
}

FilePacket::ConditionCode FilePacket::Finished::
  getConditionCode() const
{
  return this->conditionCode;
}

FilePacket::DeliveryCode FilePacket::Finished::
  getDeliveryCode() const
{
  return this->deliveryCode;
}

FilePacket::FileStatus FilePacket::Finished::
  getFileStatus() const
{
  return this->fileStatus;
}

void FilePacket::Finished::
  serialize(const Fw::Buffer& buf, U32 offset, const Header& header) const
{
  U8* data = buf.getData() + offset;

  // Serialize octet 0
  data[0] = static_cast<U8>(this->directiveCode);

  // Serialize octet 1
  data[1] = 0;
  data[1] |= (static_cast<U8>(this->conditionCode) & 15) << 4;
  data[1] |= (static_cast<U8>(this->deliveryCode) & 1) << 2;
  data[1] |= static_cast<U8>(this->fileStatus) & 3;
}

void FilePacket::Finished::
  deserialize(const Fw::Buffer& buf, U32 offset, const Header& header)
{
  U8* data = buf.getData() + offset;

  // Deserialize octet 1
  this->conditionCode =
    static_cast<FilePacket::ConditionCode>((data[1] >> 4) & 15);
  this->spare = ((data[1] >> 3) & 1);
  this->deliveryCode =
    static_cast<FilePacket::DeliveryCode>((data[1] >> 2) & 1);
  this->fileStatus =
    static_cast<FilePacket::FileStatus>(data[1] & 3);
}

U32 FilePacket::Finished::
  getSerializedLength(const Header& header) const
{
  return FixedSize::BYTES;
}

} // Cfdp

} // Fw
