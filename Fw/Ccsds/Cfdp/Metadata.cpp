//! ============================================================================
//! @file   Metadata.cpp
//! @brief  cpp file for a CFDP Metadata PDU.
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
  // Set reserved fields to 0
  this->reserved0 = 0;
  this->reserved1 = 0;

  this->closureRequested = closureRequested;
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
  getClosureRequested()
{
  return this->closureRequested;
}

FilePacket::ChecksumType FilePacket::Metadata::
  getChecksumType()
{
  return this->checksumType;
}

U64 FilePacket::Metadata::
  getFileSize()
{
  return this->fileSize.getValue();
}

const char* FilePacket::Metadata::
  getSourceFilename()
{
  return reinterpret_cast<const char*>(this->sourceFilename.getValue());
}

U8 FilePacket::Metadata::
  getSourceFilenameLength()
{
  return this->sourceFilename.getLength();
}

const char* FilePacket::Metadata::
  getDestFilename()
{
  return reinterpret_cast<const char*>(this->destFilename.getValue());
}

U8 FilePacket::Metadata::
  getDestFilenameLength()
{
  return this->destFilename.getLength();
}

void FilePacket::Metadata::
  serialize(Fw::Buffer& buf, U32 offset, Header& header)
{
  U8* data = buf.getData() + offset;

  // Serialize octet 0
  data[0] = 0;
  data[0] |= (static_cast<U8>(this->closureRequested) & 1) << 6;
  data[0] |= (static_cast<U8>(this->checksumType) & 15);

  // Serialize the FSS field file size
  this->fileSize.serialize(buf, 1, header);

  // Serialize the LV field source file name
  U32 sourceFilenameOffset = 1 + this->fileSize.getSerializedLength(header);
  this->sourceFilename.serialize(buf, sourceFilenameOffset);

  // Serialize the LV field destination file name
  U32 destFilenameOffset =
    sourceFilenameOffset + sourceFilename.getSerializedLength();
  this->destFilename.serialize(buf, destFilenameOffset);
}

void FilePacket::Metadata::
  deserialize(Fw::Buffer& buf, U32 offset, Header& header)
{
  U8* data = buf.getData() + offset;

  // Deserialize octet 0
  this->reserved0 = (data[0] >> 7) & 1;
  this->closureRequested =
    static_cast<FilePacket::ClosureRequested>((data[0] >> 6) & 1);
  this->reserved1 = (data[0] >> 4) & 3;
  this->checksumType = static_cast<FilePacket::ChecksumType>(data[0] & 15);

  // Deserialize the FSS field file size
  this->fileSize.deserialize(buf, 1, header);

  // Deserialize the LV field source file name
  U32 sourceFilenameOffset = 1 + this->fileSize.getSerializedLength(header);
  this->sourceFilename.deserialize(buf, sourceFilenameOffset);

  // Deserialize the LV field destination file name
  U32 destFilenameOffset =
    sourceFilenameOffset + sourceFilename.getSerializedLength();
  this->destFilename.deserialize(buf, destFilenameOffset);
}

U32 FilePacket::Metadata::
  getSerializedLength(Header& header)
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
