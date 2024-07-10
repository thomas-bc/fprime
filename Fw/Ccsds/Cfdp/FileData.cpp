//! ============================================================================
//! @file   FileData.cpp
//! @brief  cpp file for a CFDP file packet File Data data field.
//! @author chownw
//! ============================================================================

#include <string.h>

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FileData.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>

namespace Fw
{

namespace Cfdp
{

FilePacket::FileData::
  FileData()
{
}

FilePacket::FileData::
  FileData(
    U64 offset,
    U16 fileDataLength,
    const U8* fileData,
    ContinuationState continuationState,
    U8 metadataLength,
    const U8* metadata
  )
{
  this->offset = FileSizeSensitive(offset);
  this->fileDataLength = fileDataLength;
  this->fileData = fileData;
  this->continuationState = continuationState;
  this->metadataLength = metadataLength;
  this->metadata = metadata;
}

U64 FilePacket::FileData::
  getOffset() const
{
  return this->offset.getValue();
}

U16 FilePacket::FileData::
  getFileDataLength() const
{
  return this->fileDataLength;
}

const U8* FilePacket::FileData::
  getFileData() const
{
  return this->fileData;
}

FilePacket::ContinuationState FilePacket::FileData::
  getContinuationState() const
{
  return this->continuationState;
}

U8 FilePacket::FileData::
  getSegmentMetadataLength() const
{
  return this->metadataLength;
}

const U8* FilePacket::FileData::
  getSegmentMetadata() const
{
  return this->metadata;
}

void FilePacket::FileData::
  serialize(const Fw::Buffer& buf, U32 offset, const Header& header) const
{
  U8* data = buf.getData() + offset;

  // Truncate metadata length to only 6 bits
  U8 metadataLength = this->metadataLength & 63;

  // Initialize offset of the offset field
  U32 offsetOffset = offset;

  if (header.segmentMetadataFlag == SegmentMetadataFlag::PRESENT)
  {
    // Serialize record continuation state and segment metadata length
    data[0] = 0;
    data[0] |= (static_cast<U8>(this->continuationState) & 3) << 6;
    data[0] |= metadataLength;

    // Serialize segment metadata
    for (int i = 0; i < metadataLength; ++i)
    {
      data[i + 1] = this->metadata[i];
    }

    // Update offset of the offset field
    offsetOffset += FixedSize::BYTES + metadataLength;
  }

  // Serialize offset
  this->offset.serialize(buf, offsetOffset, header);

  U32 fileDataOffset = offsetOffset + this->offset.getSerializedLength(header);

  // Serialize file data
  for (int i = 0; i < this->fileDataLength; ++i)
  {
    data[i + fileDataOffset] = this->fileData[i];
  }
}

void FilePacket::FileData::
  deserialize(const Fw::Buffer& buf, U32 offset, const Header& header)
{
  U8* data = buf.getData() + offset;

  // Initialize offset of the offset field
  U32 offsetOffset = offset;

  if (header.segmentMetadataFlag == SegmentMetadataFlag::PRESENT)
  {
    // Deserialize record continuation state and segment metadata length
    this->continuationState =
      static_cast<FilePacket::ContinuationState>((data[0] >> 6) & 3);
    this->metadataLength = data[0] & 63;

    // Deserialize segment metadata
    if (this->metadataLength == 0)
    {
      this->metadata = NULL; // Segment metadata length is 0
    }
    else
    {
      this->metadata = &data[1];
    }

    // Update offset of the offset field
    offsetOffset += FixedSize::BYTES + this->metadataLength;
  }

  // Serialize offset
  this->offset.deserialize(buf, offsetOffset, header);

  // Calculate the length of file data
  this->fileDataLength =
    header.dataFieldLength - this->getFileDataMetadataLength(header);

  U32 fileDataOffset = offsetOffset + this->offset.getSerializedLength(header);

  // Serialize file data
  if (this->fileDataLength == 0)
  {
    this->fileData = NULL; // File data length is 0
  }
  else
  {
    this->fileData = &data[fileDataOffset];
  }
}

U32 FilePacket::FileData::
  getSerializedLength(const Header& header) const
{
  return this->getFileDataMetadataLength(header) + this->fileDataLength;
}

U16 FilePacket::FileData::
  getFileDataMetadataLength(const Header& header) const
{
  U32 fixedLength = 0; // Record continuation state and segment metadata length
  U32 metadataLength = 0; // Segment metadata

  if (header.segmentMetadataFlag == SegmentMetadataFlag::PRESENT)
  {
    fixedLength = FixedSize::BYTES;
    metadataLength = this->metadataLength;
  }

  return (
    fixedLength
    + metadataLength
    + this->offset.getSerializedLength(header)
  );
}

} // Cfdp

} // Fw
