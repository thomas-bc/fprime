//! ============================================================================
//! @file   Header.hpp
//! @brief  hpp file for a CFDP PDU header.
//! @author chownw
//! ============================================================================

#ifndef FW_CFDP_HEADER_HPP
#define FW_CFDP_HEADER_HPP

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>

namespace Fw
{

namespace Cfdp
{

//! @brief PDU direction options.
//!
//! Used to perform PDU forwarding.
//!
enum class FilePacket::Direction
{
  TOWARD_RECEIVER = 0, //!< Indicates a PDU towards the file receiver.
  TOWARD_SENDER = 1, //!< Indicates a PDU towards the file sender.
};

//! @brief Transmission mode options.
//!
//! If the transmission mode is ACKNOWLEDGED, protocol entity will use
//! reliable file transfer procedures. Acknowledged transmission mode
//! requires duplex transmission paths.
//!
enum class FilePacket::TransmissionMode
{
  ACKNOWLEDGED = 0, //!< Indicates acknowledged transmission mode.
  UNACKNOWLEDGED = 1, //!< Indicates unacknowledged transmission mode.
};

//! @brief CRC flag options.
//!
//! If the flag is PRESENT, the sending protocol entity will calculate the
//! CRC for each outgoing PDU and append it to the data field. The receiving
//! protocol entity will calculate the CRC for each incoming PDU.
//!
enum class FilePacket::CrcFlag
{
  NOT_PRESENT = 0, //!< Indicates a CRC is not included in the data field.
  PRESENT = 1, //!< Indicates a CRC is included in the data field.
};

//! @brief Large file flag options.
//!
//! If the file is a LARGE_FILE, then its size cannot be represented in an
//! unsigned 32-bit integer. All files of unbounded size shall be flagged as
//! LARGE_FILE, all other files shall be flagged as SMALL_FILE.
//!
enum class FilePacket::LargeFileFlag
{
  SMALL_FILE = 0, //!< Indicates a 'small' file.
  LARGE_FILE = 1, //!< Indicates a 'large' file.
};

//! @brief Segmentation control options.
//!
//! If flag is PRESERVED, then record boundaries are preserved in file data
//! segmentation.
//!
enum class FilePacket::SegmentationControl
{
  NOT_PRESERVED = 0, //!< Indicates record boundaries are not preserved.
  PRESERVED = 1, //!< Indicates record boundaries are preserved.
};

//! @brief Segment metadata flag options.
//!
enum class FilePacket::SegmentMetadataFlag
{
  NOT_PRESENT = 0, //!< Indicates segment metadata is not in the PDU.
  PRESENT = 1, //!< Indicates segment metadata is in the PDU.
};

//! @brief A CFDP PDU header.
//!
class FilePacket::Header
{
  friend FilePacket;

  public:
    //! @brief Construct an empty CFDP PDU header.
    //!
    //! This can be used to construct a header to hold deserialized data.
    //!
    Header();

    //! @brief Construct a filled CFDP PDU header.
    //!
    //! This can be used to construct a header for serialization.
    //!
    //! @param type The type of the PDU.
    //! @param direction The direction of the PDU.
    //! @param transmissionMode The transmission mode for the PDU.
    //! @param crcFlag Whether to calculate a CRC for the PDU.
    //! @param largeFileFlag Whether the file is large or small.
    //! @param segmentationControl Whether to preserve record boundaries.
    //! @param segmentMetadataFlag Whether to include segment metadata.
    //! @param transSeqNumLength The sequence number length in octets.
    //! @param transSeqNumber The transaction sequence number.
    //! @param entityIdLength Entity ID lengths in octets.
    //! @param sourceEntityId The source entity ID.
    //! @param destEntityId The destination entity ID.
    //! @param dataFieldLength The data field length in octets.
    //!
    Header(
      DataType type,
      Direction direction,
      TransmissionMode transmissionMode,
      CrcFlag crcFlag,
      LargeFileFlag largeFileFlag,
      SegmentationControl segmentationControl,
      SegmentMetadataFlag segmentMetadataFlag,
      U8 transSeqNumLength,
      U64 transSeqNumber,
      U8 entityIdLength,
      U64 sourceEntityId,
      U64 destEntityId,
      U16 dataFieldLength
    );

    //! @brief Get the protocol version.
    //!
    U8 getVersion() const;

    //! @brief Get the PDU type.
    //!
    DataType getType() const;

    //! @brief Get the direction used to perform PDU forwarding.
    //!
    Direction getDirection() const;

    //! @brief Get the transmission mode.
    //!
    TransmissionMode getTransmissionMode() const;

    //! @brief Get the CRC flag.
    //!
    CrcFlag getCrcFlag() const;

    //! @brief Get the large file flag.
    //!
    LargeFileFlag getLargeFileFlag() const;

    //! @brief Get the PDU data field length in octets.
    //!
    U16 getDataFieldLength() const;

    //! @brief Get whether record boundaries are preserved in data segmentation.
    //!
    SegmentationControl getSegmentationControl() const;

    //! @brief Get the number of octets in the entity ID less one.
    //!
    U8 getEntityIdLength() const;

    //! @brief Get whether segment metadata is present in the PDU.
    //!
    SegmentMetadataFlag getSegmentMetadataFlag() const;

    //! @brief Get the number of octets in the sequence number less one.
    //!
    U8 getTransSeqNumLength() const;

    //! @brief Get the source protocol entity ID.
    //!
    U64 getSourceEntityId() const;

    //! @brief Get the transaction sequence number.
    //!
    U64 getTransSeqNumber() const;

    //! @brief Get the destination protocol entity ID.
    //!
    U64 getDestEntityId() const;

  PRIVATE:
    //! @brief Serialize this header into a buffer.
    //!
    //! @param buf The buffer to hold the serialized data.
    //! @param offset The byte offset to start serialization from.
    //!
    void serialize(const Fw::Buffer& buf, U32 offset) const;

    //! @brief Deserialize a buffer containing serialized header data.
    //!
    //! @param buf The buffer containing serialized data.
    //! @param offset The byte offset to start deserialization from.
    //!
    void deserialize(const Fw::Buffer& buf, U32 offset);

    //! @brief Get the length in octets of this header when serialized.
    //!
    U32 getSerializedLength() const;

  PRIVATE:
    //! @brief Length in bits of fixed-size header fields.
    //!
    enum FieldLength : U32
    {
      VERSION = 3,
      TYPE = 1,
      DIRECTION = 1,
      TRANSMISSION_MODE = 1,
      CRC_FLAG = 1,
      LARGE_FILE_FLAG = 1,
      DATA_FIELD_LENGTH = 16,
      SEGMENTATION_CONTROL = 1,
      ENTITY_ID_LENGTH = 3,
      SEGMENT_METADATA_FLAG = 1,
      TRANS_SEQ_NUM_LENGTH = 3,
    };

    //! @brief Total length of fixed-size header fields.
    //!
    enum FixedSize : U32
    {
      BITS =
        FieldLength::VERSION
        + FieldLength::TYPE
        + FieldLength::DIRECTION
        + FieldLength::TRANSMISSION_MODE
        + FieldLength::CRC_FLAG
        + FieldLength::LARGE_FILE_FLAG
        + FieldLength::DATA_FIELD_LENGTH
        + FieldLength::SEGMENTATION_CONTROL
        + FieldLength::ENTITY_ID_LENGTH
        + FieldLength::SEGMENT_METADATA_FLAG
        + FieldLength::TRANS_SEQ_NUM_LENGTH,
      BYTES = BITS / 8,
    };

    //! @brief The protocol version.
    //!
    U8 version;

    //! @brief The PDU type.
    //!
    DataType type;

    //! @brief The direction.
    //!
    Direction direction;

    //! @brief The transmission mode.
    //!
    TransmissionMode transmissionMode;

    //! @brief The CRC flag.
    //!
    CrcFlag crcFlag;

    //! @brief The large file flag.
    //!
    LargeFileFlag largeFileFlag;

    //! @brief The PDU data field length in octets.
    //!
    U16 dataFieldLength;

    //! @brief Segmentation control.
    //!
    SegmentationControl segmentationControl;

    //! @brief Entity ID lengths in octets.
    //!
    U8 entityIdLength;

    //! @brief The segment metadata flag.
    //!
    SegmentMetadataFlag segmentMetadataFlag;

    //! @brief The transaction sequence number length in octets.
    //!
    U8 transSeqNumLength;

    //! @brief The source protocol entity ID.
    //!
    U64 sourceEntityId;

    //! @brief The transaction sequence number.
    //!
    U64 transSeqNumber;

    //! @brief The destination protocol entity ID.
    //!
    U64 destEntityId;
};

} // namespace Cfdp

} // namespace Fw

#endif // FW_CFDP_HEADER_HPP
