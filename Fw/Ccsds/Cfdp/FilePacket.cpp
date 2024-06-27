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

void FilePacket::
  serializeValue(U8* data, U64 value, U8 size)
{
  U64 input = value;

  for (U8 i = 0; i < size; ++i)
  {
    data[size - i - 1] = input & 0xFF;
    input >>= 8;
  }
}

U64 FilePacket::
  deserializeValue(U8* data, U8 size)
{
  U64 output = 0;

  for (U8 i = 0; i < size; ++i)
  {
    output <<= 8;
    output |= data[i];
  }

  return output;
}

FilePacket::FileSizeSensitive::
  FileSizeSensitive()
{
  this->value = 0;
}

FilePacket::FileSizeSensitive::
  FileSizeSensitive(U64 value)
{
  this->value = value;
}

U64 FilePacket::FileSizeSensitive::
  getValue()
{
  return this->value;
}

void FilePacket::FileSizeSensitive::
  serialize(Fw::Buffer& buf, U32 offset, Header& header)
{
  U8* data = buf.getData() + offset;

  if (header.getLargeFileFlag() == FilePacket::LargeFileFlag::SMALL_FILE)
  {
    FilePacket::serializeValue(data, this->value, 4);
  }
  else
  {
    FilePacket::serializeValue(data, this->value, 8);
  }
}

void FilePacket::FileSizeSensitive::
  deserialize(Fw::Buffer& buf, U32 offset, Header& header)
{
  U8* data = buf.getData() + offset;

  if (header.getLargeFileFlag() == FilePacket::LargeFileFlag::SMALL_FILE)
  {
    this->value = FilePacket::deserializeValue(data, 4);
  }
  else
  {
    this->value = FilePacket::deserializeValue(data, 8);
  }
}

U32 FilePacket::FileSizeSensitive::
  getSerializedLength(Header& header)
{
  return (
    (header.getLargeFileFlag() == FilePacket::LargeFileFlag::SMALL_FILE)
      ? 4 // 32-bits for small files
      : 8 // 64-bits for large files
  );
}

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
  serialize(Fw::Buffer& buf, U32 offset)
{
  this->header.serialize(buf, offset);

  this->dataField.serialize(
    buf,
    this->header.getSerializedLength(),
    this->header
  );
}

void FilePacket::
  deserialize(Fw::Buffer& buf, U32 offset)
{
  this->header.deserialize(buf, offset);

  this->dataField.deserialize(
    buf,
    this->header.getSerializedLength(),
    this->header
  );
}

} // namespace Cfdp

} // namespace Fw
