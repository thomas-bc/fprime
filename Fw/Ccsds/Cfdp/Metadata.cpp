//! ============================================================================
//! @file   Metadata.cpp
//! @brief  cpp file for a CFDP file packet Metadata data field.
//! @author chownw
//! ============================================================================

#include <string.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>
#include <Fw/Ccsds/Cfdp/Metadata.hpp>

namespace Fw
{

namespace Cfdp
{

FilePacket::DirectiveType FilePacket::Metadata::directiveCode =
  FilePacket::DirectiveType::METADATA;

FilePacket::Metadata::
  Metadata()
{
}

FilePacket::Metadata::
  Metadata(
    FilePacket::ClosureRequested closureRequested,
    FilePacket::ChecksumType checksumType,
    U64 fileSize,
    const char* sourceFilename,
    const char* destFilename
  )
{
  this->reserved0 = 0;
  this->closureRequested = closureRequested;
  this->reserved1 = 0;
  this->checksumType = checksumType;
  this->fileSize = FileSizeSensitive(fileSize);

  this->sourceFilename = FilePacket::LengthValue(
    strnlen(sourceFilename, FilePacket::LengthValue::MAX_LENGTH),
    reinterpret_cast<const U8*>(sourceFilename)
  );

  this->destFilename = FilePacket::LengthValue(
    strnlen(destFilename, FilePacket::LengthValue::MAX_LENGTH),
    reinterpret_cast<const U8*>(destFilename)
  );
}

FilePacket::ClosureRequested FilePacket::Metadata::
  getClosureRequested() const
{
  return this->closureRequested;
}

FilePacket::ChecksumType FilePacket::Metadata::
  getChecksumType() const
{
  return this->checksumType;
}

U64 FilePacket::Metadata::
  getFileSize() const
{
  return this->fileSize.getValue();
}

const char* FilePacket::Metadata::
  getSourceFilename() const
{
  return reinterpret_cast<const char*>(this->sourceFilename.getValue());
}

U8 FilePacket::Metadata::
  getSourceFilenameLength() const
{
  return this->sourceFilename.getLength();
}

const char* FilePacket::Metadata::
  getDestFilename() const
{
  return reinterpret_cast<const char*>(this->destFilename.getValue());
}

U8 FilePacket::Metadata::
  getDestFilenameLength() const
{
  return this->destFilename.getLength();
}

void FilePacket::Metadata::
  serialize(const Fw::Buffer& buf, U32 offset, const Header& header) const
{
  U8* data = buf.getData() + offset;

  // Serialize octet 0
  data[0] = static_cast<U8>(this->directiveCode);

  // Serialize octet 1
  data[1] = 0;
  data[1] |= (static_cast<U8>(this->closureRequested) & 1) << 6;
  data[1] |= (static_cast<U8>(this->checksumType) & 15);

  // Serialize the FSS field file size
  U32 fileSizeOffset = offset + FixedSize::BYTES;
  this->fileSize.serialize(buf, fileSizeOffset, header);

  // Serialize the LV field source file name
  U32 sourceFilenameOffset =
    fileSizeOffset + this->fileSize.getSerializedLength(header);
  this->sourceFilename.serialize(buf, sourceFilenameOffset);

  // Serialize the LV field destination file name
  U32 destFilenameOffset =
    sourceFilenameOffset + this->sourceFilename.getSerializedLength();
  this->destFilename.serialize(buf, destFilenameOffset);
}

void FilePacket::Metadata::
  deserialize(const Fw::Buffer& buf, U32 offset, const Header& header)
{
  U8* data = buf.getData() + offset;

  // Deserialize octet 1
  this->reserved0 = (data[1] >> 7) & 1;
  this->closureRequested =
    static_cast<FilePacket::ClosureRequested>((data[1] >> 6) & 1);
  this->reserved1 = (data[1] >> 4) & 3;
  this->checksumType = static_cast<FilePacket::ChecksumType>(data[1] & 15);

  // Deserialize the FSS field file size
  U32 fileSizeOffset = offset + FixedSize::BYTES;
  this->fileSize.deserialize(buf, fileSizeOffset, header);

  // Deserialize the LV field source file name
  U32 sourceFilenameOffset =
    fileSizeOffset + this->fileSize.getSerializedLength(header);
  this->sourceFilename.deserialize(buf, sourceFilenameOffset);

  // Deserialize the LV field destination file name
  U32 destFilenameOffset =
    sourceFilenameOffset + this->sourceFilename.getSerializedLength();
  this->destFilename.deserialize(buf, destFilenameOffset);
}

U32 FilePacket::Metadata::
  getSerializedLength(const Header& header) const
{
  return (
    FixedSize::BYTES
    + this->fileSize.getSerializedLength(header)
    + this->sourceFilename.getSerializedLength()
    + this->destFilename.getSerializedLength()
  );
}

} // Cfdp

} // Fw
