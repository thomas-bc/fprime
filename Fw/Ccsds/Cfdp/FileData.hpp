//! ============================================================================
//! @file   FileData.hpp
//! @brief  hpp file for a CFDP file packet File Data data field.
//! @author chownw
//! ============================================================================

#ifndef FW_CFDP_FILEDATA_HPP
#define FW_CFDP_FILEDATA_HPP

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>

namespace Fw
{

namespace Cfdp
{

//! @brief Record continuation state options.
//!
enum class FilePacket::ContinuationState
{
  NONE = 0, //!< File data contains neither the start nor the end of any record.
  FIRST = 1, //!< File data starts with the first octet of a record.
  LAST = 2, //!< File data ends with the last octet of a record.
  BOTH = 3, //!< File data starts and ends with first and last octet of record.
};

//! @brief A CFDP file packet File Data data field.
//!
class FilePacket::FileData : public DataField
{
  friend FilePacket;

  public:
    //! @brief Construct an empty CFDP file packet File Data data field type.
    //!
    //! This can be used to construct an initially empty data field for
    //! deserialized data.
    //!
    FileData();

    //! @brief Construct a filled CFDP file packet File Data data field type.
    //!
    //! This can be used to construct a data field with values for
    //! serialization.
    //!
    //! @param offset The file data offset in octets.
    //! @param fileDataLength The length of file data in octets.
    //! @param fileData A pointer to variable length file data.
    //! @param continuationState The record continuation state.
    //! @param metadataLength The length of metadata in octets, from 0 to 63.
    //! @param metadata A pointer to segment metadata.
    //!
    FileData(
      U64 offset,
      U16 fileDataLength,
      const U8* fileData,
      ContinuationState continuationState,
      U8 metadataLength,
      const U8* metadata
    );

    //! @brief Get the offset.
    //!
    U64 getOffset() const;

    //! @brief Get the length of file data.
    //!
    U16 getFileDataLength() const;

    //! @brief Get the pointer to file data.
    //!
    const U8* getFileData() const;

    //! @brief Get the record continuation state.
    //!
    ContinuationState getContinuationState() const;

    //! @brief Get the length of segment metadata.
    //!
    U8 getSegmentMetadataLength() const;

    //! @brief Get the pointer to segment metadata.
    //!
    const U8* getSegmentMetadata() const;

  PRIVATE:
    //! @brief Serialize this data field into a buffer.
    //!
    //! @param buf The buffer to hold the serialized data.
    //! @param offset The byte offset to start serialization from.
    //! @param header The header attached to this file packet.
    //!
    void serialize(
      const Fw::Buffer& buf,
      U32 offset,
      const Header& header
    ) const;

    //! @brief Deserialize a buffer containing a serialized data field.
    //!
    //! @param buf The buffer containing serialized data.
    //! @param offset The byte offset to start deserialization from.
    //! @param header The header attached to this file packet.
    //!
    void deserialize(
      const Fw::Buffer& buf,
      U32 offset,
      const Header& header
    );

    //! @brief Get the length in octets of this data field when serialized.
    //!
    //! @param header The header attached to this file packet.
    //!
    U32 getSerializedLength(const Header& header) const;

  PRIVATE:
    //! @brief Get the length in octets of non file data fields.
    //!
    //! Length includes the record continuation state, segment metadata length,
    //! segment metadata, and offset fields.
    //!
    U16 getFileDataMetadataLength(const Header& header) const;

  PRIVATE:
    //! @brief Length in bits of fixed-size header fields.
    //!
    enum FieldLength : U32
    {
      RECORD_CONTINUATION_STATE = 2,
      SEGMENT_METADATA_LENGTH = 6,
    };

    //! @brief Total length of fixed-size fields.
    //!
    enum FixedSize : U32
    {
      BITS =
        FieldLength::RECORD_CONTINUATION_STATE
        + FieldLength::SEGMENT_METADATA_LENGTH,
      BYTES = BITS / 8,
    };

    //! @brief The file data offset in octets.
    //!
    FileSizeSensitive offset;

    //! @brief The length of file data in octets.
    //!
    U16 fileDataLength;

    //! @brief The pointer to file data.
    //!
    const U8* fileData;

    //! @brief The record continuation state.
    //!
    //! Present if and only if the value of the segment metadata flag in the
    //! header is 1.
    //!
    ContinuationState continuationState;

    //! @brief The length of segment metadata.
    //!
    //! Present if and only if the value of the segment metadata flag in the
    //! header is 1.
    //!
    U8 metadataLength;

    //! @brief The pointer to segment metadata.
    //!
    //! Present if and only if the value of the segment metadata flag in the
    //! header is 1.
    //!
    const U8* metadata;
};

} // Cfdp

} // Fw

#endif // FW_CFDP_FILEDATA_HPP
