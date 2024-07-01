//! ============================================================================
//! @file   Metadata.hpp
//! @brief  hpp file for a CFDP Metadata PDU.
//! @author chownw
//! ============================================================================

#ifndef FW_CFDP_METADATA_HPP
#define FW_CFDP_METADATA_HPP

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>

namespace Fw
{

namespace Cfdp
{

//! @brief Closure requested options.
//!
enum class FilePacket::ClosureRequested
{
  NOT_REQUESTED = 0, //!< Indicates transaction closure is not requested.
  REQUESTED = 1, //!< Indicates transaction closure is requested.
};

//! @brief CFDP checksum identifiers defined in the SANA registry.
//!
enum class FilePacket::ChecksumType
{
  MODULAR_CHECKSUM = 0, //!< Identifies the CFDP Modular Checksum algorithm.
  PROXIMITY1_CRC32 = 1, //!< Identifies the CCSDS Proximity-1 CRC algorithm.
  CRC32C = 2, //!< Identifies the RFC 4960 CRC32c Checksum algorithm.
  IEEE_802_3_FCS = 3, //!< Identifies the IEEE Std 802.3 2018 FCS algorithm.
  NULL_CHECKSUM = 15, //!< Identifies the CFDP Null Checksum algorithm.
};

//! @brief A CFDP Metadata PDU.
//!
class FilePacket::Metadata : public DataField
{
  friend FilePacket;

  public:
    //! @brief Construct an empty CFDP Metadata PDU.
    //!
    //! This can be used to construct a metadata PDU to hold deserialized data.
    //!
    Metadata();

    //! @brief Construct a filled CFDP Metadata PDU.
    //!
    //! This can be used to construct a metadata PDU for serialization.
    //!
    //! @param closureRequested Whether transaction closure is requsted.
    //! @param checksumType The file checksum algorithm to use.
    //! @param fileSize The length of the file in octets, or 0 for unbounded.
    //! @param sourceFilename The source file name, or NULL.
    //! @param destFilename The destination file name, or NULL.
    //!
    Metadata(
      ClosureRequested closureRequested,
      ChecksumType checksumType,
      U64 fileSize,
      const char* sourceFilename,
      const char* destFilename
    );

    //! @brief Get whether closure is requested.
    //!
    ClosureRequested getClosureRequested() const;

    //! @brief Get the checksum type.
    //!
    ChecksumType getChecksumType() const;

    //! @brief Get the file size.
    //!
    U64 getFileSize() const;

    //! @brief Get the source file name.
    //!
    const char* getSourceFilename() const;

    //! @brief Get the source file name length in bytes.
    //!
    U8 getSourceFilenameLength() const;

    //! @brief Get the destination file name.
    //!
    const char* getDestFilename() const;

    //! @brief Get the destination file name length in bytes.
    //!
    U8 getDestFilenameLength() const;

  PRIVATE:
    //! @brief Serialize this Metadata PDU into a buffer.
    //!
    //! @param buf The buffer to hold the serialized data.
    //! @param offset The byte offset to start serialization from.
    //! @param header The header attached to this PDU.
    //!
    void serialize(
      const Fw::Buffer& buf,
      U32 offset,
      const Header& header
    ) const;

    //! @brief Deserialize a buffer containing serialized Metadata PDU data.
    //!
    //! @param buf The buffer containing serialized data.
    //! @param offset The byte offset to start deserialization from.
    //! @param header The header attached to this PDU.
    //!
    void deserialize(
      const Fw::Buffer& buf,
      U32 offset,
      const Header& header
    );

    //! @brief Get the length in octets of this Metadata PDU when serialized.
    //!
    //! @param header The header attached to this PDU.
    //!
    U32 getSerializedLength(const Header& header) const;

  PRIVATE:
    //! @brief Length in bits of fixed-size Metadata PDU fields.
    //!
    enum FieldLength : U32
    {
      DIRECTIVE_CODE = 8,
      RESERVED0 = 1,
      CLOSURE_REQUESTED = 1,
      RESERVED1 = 2,
      CHECKSUM_TYPE = 4,
    };

    //! @brief Total length of fixed-size Metadata PDU fields.
    //!
    enum FixedSize : U32
    {
      BITS =
        FieldLength::DIRECTIVE_CODE
        + FieldLength::RESERVED0
        + FieldLength::CLOSURE_REQUESTED
        + FieldLength::RESERVED1
        + FieldLength::CHECKSUM_TYPE,
      BYTES = BITS / 8,
    };

    //! @brief Indicates that the data field contains a metadata PDU.
    //!
    static DirectiveType directiveCode;

    //! @brief Reserved for future use.
    //!
    U8 reserved0;

    //! @brief Closure requested.
    ClosureRequested closureRequested;

    //! @brief Reserved for future use.
    //!
    U8 reserved1;

    //! @brief The checksum algorithm identifier.
    //!
    ChecksumType checksumType;

    //! @brief The file size in octets.
    //!
    FileSizeSensitive fileSize;

    //! @brief The source file name.
    //!
    LengthValue sourceFilename;

    //! @brief The destination file name.
    //!
    LengthValue destFilename;

    // NOTE: Options field not supported.
};

} // Cfdp

} // Fw

#endif // FW_CFDP_METADATA_HPP
