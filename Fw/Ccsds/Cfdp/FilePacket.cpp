//! ============================================================================
//! @file   FilePacket.cpp
//! @brief  cpp file for a CFDP PDU file packet.
//! @author chownw
//! ============================================================================

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>

namespace Fw
{

namespace Cfdp
{

FilePacket::LengthValue::
  LengthValue(U8 length, const U8* value)
{
  this->length = length;
  this->value = value;
}

U8 FilePacket::LengthValue::
  getLength()
{
  return this->length;
}

const U8* FilePacket::LengthValue::
  getValue()
{
  return this->value;
}

void FilePacket::LengthValue::
  serialize(Fw::Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  // Octet 0
  data[0] = this->length;

  // Copy value into the buffer starting at octet 1
  for (int i = 0; i < this->length; ++i)
  {
    data[i + 1] = this->value[i];
  }
}

void FilePacket::LengthValue::
  deserialize(Fw::Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  // Octet 0
  this->length = data[0];

  // Get a pointer to octet 1 which is the start of the value in the buffer
  this->value = &data[1];
}

FilePacket::TypeLengthValue::
  TypeLengthValue(
    FilePacket::TypeLengthValue::TlvType type,
    U8 length,
    const U8* value
  ) : LengthValue(length, value)
{
  this->type = type;
}

FilePacket::TypeLengthValue::TlvType FilePacket::TypeLengthValue::
  getType()
{
  return this->type;
}

void FilePacket::TypeLengthValue::
  serialize(Fw::Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  // Octet 0
  data[0] = static_cast<U8>(this->type);

  // Serialize length and value fields
  FilePacket::LengthValue::serialize(buf, 1);
}

void FilePacket::TypeLengthValue::
  deserialize(Fw::Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  // Octet 0
  this->type = static_cast<FilePacket::TypeLengthValue::TlvType>(data[0]);

  // Deserialize length and value fields
  FilePacket::LengthValue::deserialize(buf, 1);
}

FilePacket::
  FilePacket(Header& header) : header(header)
{

}

void FilePacket::
  serialize(Fw::Buffer& buf)
{
  // this->header.serialize();
}

void FilePacket::
  deserialize(Fw::Buffer& buf)
{
  // this->header.deserialize();
}

} // namespace Cfdp

} // namespace Fw
