//! ============================================================================
//! @file   EndOfFile.hpp
//! @brief  hpp file for a CFDP file packet End-of-file data field.
//! @author chownw
//! ============================================================================

#ifndef FW_CFDP_ENDOFFILE_HPP
#define FW_CFDP_ENDOFFILE_HPP

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>

namespace Fw
{

namespace Cfdp
{

//! @brief A CFDP file packet End-of-file data field.
//!
class FilePacket::EndOfFile : public DataField
{
  friend FilePacket;

  public:
    //! @brief Construct an empty CFDP End-of-file PDU.
    //!
    //! This can be used to construct an End-of-file PDU to hold deserialized
    //! data.
    //!
    EndOfFile();

    //! @brief Construct a filled CFDP End-of-file PDU.
    //!
    //! This can be used to construct an End-of-file PDU for serialization.
    //!
    //! @param conditionCode The condition code.
    //! @param fileChecksum The file checksum.
    //! @param fileSize The number of file data octets transmitted by sender.
    //!
    EndOfFile(
      ConditionCode conditionCode,
      U32 fileChecksum,
      U64 fileSize
    );

    //! @brief Get the condition code.
    //!
    ConditionCode getConditionCode() const;

    //! @brief Get the file checksum.
    //!
    U32 getFileChecksum() const;

    //! @brief Get the file size.
    //!
    U64 getFileSize() const;

  PRIVATE:
    //! @brief Serialize this End-of-file PDU into a buffer.
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

    //! @brief Deserialize a buffer containing serialized End-of-file PDU data.
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

    //! @brief Get the length in octets of this End-of-file PDU when serialized.
    //!
    //! @param header The header attached to this PDU.
    //!
    U32 getSerializedLength(const Header& header) const;

  PRIVATE:
    //! @brief Length in bits of fixed-size End-of-file PDU fields.
    //!
    enum FieldLength : U32
    {
      DIRECTIVE_CODE = 8,
      CONDITION_CODE = 4,
      SPARE = 4,
      FILE_CHECKSUM = 32,
    };

    //! @brief Total length of fixed-size End-of-file PDU fields.
    //!
    enum FixedSize : U32
    {
      BITS =
        FieldLength::DIRECTIVE_CODE
        + FieldLength::CONDITION_CODE
        + FieldLength::SPARE
        + FieldLength::FILE_CHECKSUM,
      BYTES = BITS / 8,
    };

    //! @brief Indicates that the data field contains an End-of-file PDU.
    //!
    static DirectiveType directiveCode;

    //! @brief Condition code.
    //!
    ConditionCode conditionCode;

    //! @brief Spare bits, set to all zeroes.
    //!
    U8 spare;

    //! @brief File checksum.
    //!
    U32 fileChecksum;

    //! @brief Number of file data octets transmitted by sender.
    //!
    FileSizeSensitive fileSize;

    // NOTE: Fault location field not supported.
};

} // Cfdp

} // Fw

#endif // FW_CFDP_ENDOFFILE_HPP
