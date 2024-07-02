//! ============================================================================
//! @file   EndOfFile.cpp
//! @brief  cpp file for a CFDP file packet End-of-file data field.
//! @author chownw
//! ============================================================================

#include <string.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/EndOfFile.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>

namespace Fw
{

namespace Cfdp
{

FilePacket::DirectiveType FilePacket::EndOfFile::directiveCode =
  FilePacket::DirectiveType::END_OF_FILE;

FilePacket::EndOfFile::
  EndOfFile()
{
}

FilePacket::EndOfFile::
  EndOfFile(ConditionCode conditionCode, U32 fileChecksum, U64 fileSize)
{
  this->conditionCode = conditionCode;
  this->spare = 0;
  this->fileChecksum = fileChecksum;
  this->fileSize = FileSizeSensitive(fileSize);
}

FilePacket::ConditionCode FilePacket::EndOfFile::
  getConditionCode() const
{
  return this->conditionCode;
}

U32 FilePacket::EndOfFile::
  getFileChecksum() const
{
  return this->fileChecksum;
}

U64 FilePacket::EndOfFile::
  getFileSize() const
{
  return this->fileSize.getValue();
}

void FilePacket::EndOfFile::
  serialize(const Fw::Buffer& buf, U32 offset, const Header& header) const
{
  U8* data = buf.getData() + offset;

  // Serialize octet 0
  data[0] = static_cast<U8>(this->directiveCode);

  // Serialize octet 1
  data[1] = (static_cast<U8>(this->conditionCode) & 15) << 4;

  // Push file checksum in big-endian format
  FilePacket::serializeValue(
    &data[2],
    this->fileChecksum,
    FieldLength::FILE_CHECKSUM / 8
  );

  // Serialize the FSS field file size
  U32 fileSizeOffset = offset + FixedSize::BYTES;
  this->fileSize.serialize(buf, fileSizeOffset, header);
}

void FilePacket::EndOfFile::
  deserialize(const Fw::Buffer& buf, U32 offset, const Header& header)
{
  U8* data = buf.getData() + offset;

  // Deserialize octet 1
  this->conditionCode =
    static_cast<FilePacket::ConditionCode>((data[1] >> 4) & 15);
  this->spare = data[1] & 15;

  // Deserialize file checksum bytes
  this->fileChecksum = FilePacket::deserializeValue(
    &data[2],
    FieldLength::FILE_CHECKSUM / 8
  );

  // Deserialize the FSS field file size
  U32 fileSizeOffset = offset + FixedSize::BYTES;
  this->fileSize.deserialize(buf, fileSizeOffset, header);
}

U32 FilePacket::EndOfFile::
  getSerializedLength(const Header& header) const
{
  return (
    FixedSize::BYTES
    + this->fileSize.getSerializedLength(header)
  );
}

} // Cfdp

} // Fw
