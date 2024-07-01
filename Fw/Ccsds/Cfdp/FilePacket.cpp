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
  deserializeValue(const U8* data, U8 size)
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
  getValue() const
{
  return this->value;
}

void FilePacket::FileSizeSensitive::
  serialize(const Fw::Buffer& buf, U32 offset, const Header& header) const
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
  deserialize(const Fw::Buffer& buf, U32 offset, const Header& header)
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
  getSerializedLength(const Header& header) const
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
  getLength() const
{
  return this->length;
}

const U8* FilePacket::LengthValue::
  getValue() const
{
  return this->value;
}

void FilePacket::LengthValue::
  serialize(const Fw::Buffer& buf, U32 offset) const
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
  deserialize(const Fw::Buffer& buf, U32 offset)
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
  getSerializedLength() const
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
  serialize(const Fw::Buffer& buf, U32 offset) const
{
  this->header.serialize(buf, offset);

  this->dataField.serialize(
    buf,
    this->header.getSerializedLength(),
    this->header
  );
}

void FilePacket::
  deserialize(const Fw::Buffer& buf, U32 offset)
{
  this->header.deserialize(buf, offset);

  this->dataField.deserialize(
    buf,
    this->header.getSerializedLength(),
    this->header
  );
}

FilePacket::Type FilePacket::
  getTypeFromBuffer(const Fw::Buffer& buf, U32 offset)
{
  // Deserialize the header
  Header header;
  header.deserialize(buf, offset);

  // Get pointer to the start of the data field
  U8* data = buf.getData() + offset + header.getSerializedLength();

  return static_cast<FilePacket::Type>(
    (static_cast<U8>(header.getType()) << 8) | data[0]
  );
}

} // namespace Cfdp

} // namespace Fw
