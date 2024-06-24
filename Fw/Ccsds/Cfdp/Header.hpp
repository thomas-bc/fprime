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

//! @brief A CFDP PDU header.
//!
class FilePacket::Header
{
  friend class FilePacket;

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
      Type type,
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
    U8 getVersion();

    //! @brief Get the PDU type.
    //!
    Type getType();

    //! @brief Get the direction used to perform PDU forwarding.
    //!
    Direction getDirection();

    //! @brief Get the transmission mode.
    //!
    TransmissionMode getTransmissionMode();

    //! @brief Get the CRC flag.
    //!
    CrcFlag getCrcFlag();

    //! @brief Get the large file flag.
    //!
    LargeFileFlag getLargeFileFlag();

    //! @brief Get the PDU data field length in octets.
    //!
    U16 getDataFieldLength();

    //! @brief Get whether record boundaries are preserved in data segmentation.
    //!
    SegmentationControl getSegmentationControl();

    //! @brief Get the number of octets in the entity ID less one.
    //!
    U8 getEntityIdLength();

    //! @brief Get whether segment metadata is present in the PDU.
    //!
    SegmentMetadataFlag getSegmentMetadataFlag();

    //! @brief Get the number of octets in the sequence number less one.
    //!
    U8 getTransSeqNumLength();

    //! @brief Get the source protocol entity ID.
    //!
    U64 getSourceEntityId();

    //! @brief Get the transaction sequence number.
    //!
    U64 getTransSeqNumber();

    //! @brief Get the destination protocol entity ID.
    //!
    U64 getDestEntityId();

  PRIVATE:
    //! @brief Serialize this header into a buffer.
    //!
    //! @param buf The buffer to hold the serialized data.
    //! @param offset The byte offset to start serialization from.
    //!
    void serialize(Fw::Buffer& buf, U32 offset);

    //! @brief Deserialize a buffer containing serialized header data.
    //!
    //! @param buf The buffer containing serialized data.
    //! @param offset The byte offset to start deserialization from.
    //!
    void deserialize(Fw::Buffer& buf, U32 offset);

  PRIVATE:
    //! @brief The protocol version.
    //!
    U8 version;

    //! @brief The PDU type.
    //!
    Type type;

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
