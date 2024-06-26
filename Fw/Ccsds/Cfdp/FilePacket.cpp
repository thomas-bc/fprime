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
  LengthValue()
{
  this->length = 0;
  this->value = NULL;
}

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

  // Copy value into the buffer starting at octet 1, skip if length is 0
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

  if (this->length == 0)
  {
    // Length is 0, there is no value field to deserialize
    this->value = NULL;
  }
  else
  {
    // Get pointer to octet 1 which is the start of value field in the buffer
    this->value = &data[1];
  }
}

U32 FilePacket::LengthValue::
  getSerializedLength()
{
  return this->length + 1;
}

FilePacket::
  FilePacket
  (
    Header& header,
    DataField& dataField
  ) : header(header), dataField(dataField)
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
