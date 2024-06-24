//! ============================================================================
//! @file   Header.cpp
//! @brief  cpp file for a CFDP PDU header.
//! @author chownw
//! ============================================================================

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>
#include <Fw/Ccsds/Cfdp/Header.hpp>

namespace
{

//! @brief Serialize an integer value in big-endian format.
//!
//! @param data A pointer to the start of the data.
//! @param value The integer value to write.
//! @param size The number of bytes required to store the value.
//!
void serialize_value(U8* data, U64 value, U8 size)
{
  U64 input = value;
  for (U8 i = 0; i < size; ++i)
  {
    data[size - i - 1] = input & 0xFF;
    input >>= 8;
  }
}

//! @brief Read a serialized integer value in big-endian format.
//!
//! @param data A pointer to the start of the data.
//! @param size The number of bytes required to store the value.
//!
U64 deserialize_value(U8* data, U8 size)
{
  U32 output = 0;
  for (U8 i = 0; i < size; ++i)
  {
    output <<= 8;
    output |= data[i];
  }
  return output;
}

} //

namespace Fw
{

namespace Cfdp
{

FilePacket::Header::
  Header()
{
}

FilePacket::Header::
  Header(
    FilePacket::Type type,
    FilePacket::Direction direction,
    FilePacket::TransmissionMode transmissionMode,
    FilePacket::CrcFlag crcFlag,
    FilePacket::LargeFileFlag largeFileFlag,
    FilePacket::SegmentationControl segmentationControl,
    FilePacket::SegmentMetadataFlag segmentMetadataFlag,
    U8 transSeqNumLength,
    U64 transSeqNumber,
    U8 entityIdLength,
    U64 sourceEntityId,
    U64 destEntityId,
    U16 dataFieldLength
  )
{
  // TODO: Check invariants

  // Indicates second version of the protocol
  this->version = 0x001;

  this->type = type;
  this->direction = direction;
  this->transmissionMode = transmissionMode;
  this->crcFlag = crcFlag;
  this->largeFileFlag = largeFileFlag;
  this->transSeqNumLength = transSeqNumLength;
  this->entityIdLength = entityIdLength;
  this->transSeqNumber = transSeqNumber;
  this->sourceEntityId = sourceEntityId;
  this->destEntityId = destEntityId;
  this->dataFieldLength = dataFieldLength;

  // These fields are always '0' and should be ignored for file directive PDUs
  if (this->type == FilePacket::Type::FILE_DIRECTIVE)
  {
    this->segmentationControl = FilePacket::SegmentationControl::NOT_PRESERVED;
    this->segmentMetadataFlag = FilePacket::SegmentMetadataFlag::NOT_PRESENT;
  }
  else
  {
    this->segmentationControl = segmentationControl;
    this->segmentMetadataFlag = segmentMetadataFlag;
  }
}

U8 FilePacket::Header::
  getVersion()
{
  return this->version;
}

FilePacket::Type FilePacket::Header::
  getType()
{
  return this->type;
}

FilePacket::Direction FilePacket::Header::
  getDirection()
{
  return this->direction;
}

FilePacket::TransmissionMode FilePacket::Header::
  getTransmissionMode()
{
  return this->transmissionMode;
}

FilePacket::CrcFlag FilePacket::Header::
  getCrcFlag()
{
  return this->crcFlag;
}

FilePacket::LargeFileFlag FilePacket::Header::
  getLargeFileFlag()
{
  return this->largeFileFlag;
}

U16 FilePacket::Header::
  getDataFieldLength()
{
  return this->dataFieldLength;
}

FilePacket::SegmentationControl FilePacket::Header::
  getSegmentationControl()
{
  return this->segmentationControl;
}

U8 FilePacket::Header::
  getEntityIdLength()
{
  return this->entityIdLength;
}

FilePacket::SegmentMetadataFlag FilePacket::Header::
  getSegmentMetadataFlag()
{
  return this->segmentMetadataFlag;
}

U8 FilePacket::Header::
  getTransSeqNumLength()
{
  return this->transSeqNumLength;
}

U64 FilePacket::Header::
  getSourceEntityId()
{
  return this->sourceEntityId;
}

U64 FilePacket::Header::
  getTransSeqNumber()
{
  return this->transSeqNumber;
}

U64 FilePacket::Header::
  getDestEntityId()
{
  return this->destEntityId;
}

void FilePacket::Header::
  serialize(Fw::Buffer& buf, U32 offset)
{
  // TODO: Check buffer size is >= header size + offset

  U8* data = buf.getData() + offset;

  // Serialize octet 0
  data[0] = 0;
  data[0] |= this->version << 5;
  data[0] |= (static_cast<U8>(this->type) & 1) << 4;
  data[0] |= (static_cast<U8>(this->direction) & 1) << 3;
  data[0] |= (static_cast<U8>(this->transmissionMode) & 1) << 2;
  data[0] |= (static_cast<U8>(this->crcFlag) & 1) << 1;
  data[0] |= (static_cast<U8>(this->largeFileFlag) & 1);

  // Serialize octet 1
  data[1] = this->dataFieldLength >> 8;

  // Serialize octet 2
  data[2] = this->dataFieldLength;

  // Serialize octet 3
  data[3] = 0;
  data[3] |= (static_cast<U8>(this->segmentationControl) & 1) << 7;
  data[3] |= ((this->entityIdLength & 7) - 1) << 4; // TODO: - 1?
  data[3] |= (static_cast<U8>(this->segmentMetadataFlag) & 1) << 3;
  data[3] |= ((this->transSeqNumLength & 7) - 1); // TODO: - 1?

  // Push source entity ID onto buffer in big-endian format
  serialize_value(
    &data[4],
    this->sourceEntityId,
    this->entityIdLength
  );

  // Push transaction sequence number onto buffer in big-endian format
  serialize_value(
    &data[4 + this->entityIdLength],
    this->transSeqNumber,
    this->transSeqNumLength
  );

  // Push destination entity ID onto buffer in big-endian format
  serialize_value(
    &data[4 + this->entityIdLength + this->transSeqNumLength],
    this->destEntityId,
    this->entityIdLength
  );
}

void FilePacket::Header::
  deserialize(Fw::Buffer& buf, U32 offset)
{
  U8* data = buf.getData() + offset;

  // Deserialize octet 0
  this->version = data[0] >> 5;
  this->type = static_cast<FilePacket::Type>((data[0] >> 4) & 1);
  this->direction = static_cast<FilePacket::Direction>((data[0] >> 3) & 1);
  this->transmissionMode =
    static_cast<FilePacket::TransmissionMode>((data[0] >> 2) & 1);
  this->crcFlag = static_cast<FilePacket::CrcFlag>((data[0] >> 1) & 1);
  this->largeFileFlag = static_cast<FilePacket::LargeFileFlag>(data[0] & 1);

  // Deserialize octet 1
  this->dataFieldLength = data[1] * 0x100;

  // Deserialize octet 2
  this->dataFieldLength += data[2];

  // Deserialize octet 3
  this->segmentationControl =
    static_cast<FilePacket::SegmentationControl>((data[3] >> 7) & 1);
  this->entityIdLength = ((data[3] >> 4) & 7) + 1;
  this->segmentMetadataFlag =
    static_cast<FilePacket::SegmentMetadataFlag>((data[3] >> 3) & 1);
  this->transSeqNumLength = (data[3] & 7) + 1;

  // Deserialize source entity ID bytes
  this->sourceEntityId = deserialize_value(
    &data[4],
    this->entityIdLength
  );

  // Deserialize transaction sequence number bytes
  this->transSeqNumber = deserialize_value(
    &data[4 + this->entityIdLength],
    this->transSeqNumLength
  );

  // Deserialize destination entity ID bytes
  this->destEntityId = deserialize_value(
    &data[4 + this->entityIdLength + this->transSeqNumLength],
    this->entityIdLength
  );
}

U32 FilePacket::Header::
  getSerializedLength()
{
  return (
    FixedSize::BYTES
    + this->entityIdLength
    + this->transSeqNumLength
    + this->entityIdLength
  );
}

} // namespace Cfdp

} // namespace Fw
