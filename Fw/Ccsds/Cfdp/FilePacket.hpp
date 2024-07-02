//! ============================================================================
//! @file   FilePacket.hpp
//! @brief  hpp file for a CFDP file packet.
//! @author chownw
//! ============================================================================

#ifndef FW_CFDP_FILEPACKET_HPP
#define FW_CFDP_FILEPACKET_HPP

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>

namespace Fw
{

namespace Cfdp
{

//! @brief A CFDP PDU file packet.
//!
//! This implementation does not currently support Type Length Value (TLV)
//! fields. Fields with TLV format are ignored and consequently the PDUs do not
//! currently support filestore responses, messages to user, fault handler
//! overrides, flow labels, or other features that require TLV fields.
//!
class FilePacket
{
  public:
    //! @brief Packet data field type options.
    //!
    enum class DataType
    {
      FILE_DIRECTIVE = 0, //!< Indicates a file directive PDU.
      FILE_DATA = 1, //!< Indicates a file data PDU.
    };

    //! @brief File directive type options.
    //!
    enum class DirectiveType
    {
      END_OF_FILE = 0x04,
      FINISHED = 0x05,
      ACK = 0x06,
      METADATA = 0x07,
      NAK = 0x08,
      PROMPT = 0x09,
      KEEP_ALIVE = 0x0C,
    };

    //! @brief File packet type options.
    //!
    //! The F Prime file packet type is a combination of the data field type and
    //! the directive type.
    //!
    enum class Type
    {
      FILE_DATA_PACKET =
        static_cast<U8>(DataType::FILE_DATA) << 8,
      EOF_PACKET =
        (static_cast<U8>(DataType::FILE_DIRECTIVE) << 8)
        | static_cast<U8>(DirectiveType::END_OF_FILE),
      FINISHED_PACKET =
        (static_cast<U8>(DataType::FILE_DIRECTIVE) << 8)
        | static_cast<U8>(DirectiveType::FINISHED),
      ACK_PACKET =
        (static_cast<U8>(DataType::FILE_DIRECTIVE) << 8)
        | static_cast<U8>(DirectiveType::ACK),
      METADATA_PACKET =
        (static_cast<U8>(DataType::FILE_DIRECTIVE) << 8)
        | static_cast<U8>(DirectiveType::METADATA),
      NAK_PACKET =
        (static_cast<U8>(DataType::FILE_DIRECTIVE) << 8)
        | static_cast<U8>(DirectiveType::NAK),
      PROMPT_PACKET =
        (static_cast<U8>(DataType::FILE_DIRECTIVE) << 8)
        | static_cast<U8>(DirectiveType::PROMPT),
      KEEP_ALIVE_PACKET =
        (static_cast<U8>(DataType::FILE_DIRECTIVE) << 8)
        | static_cast<U8>(DirectiveType::KEEP_ALIVE),
    };

    //! @brief Condition code options.
    //!
    enum class ConditionCode
    {
      NO_ERROR = 0, //!< 'No error' condition.
      ACK_LIMIT = 1, //!< 'Positive ACK limit reached' condition.
      KEEP_ALIVE_LIMIT = 2, //!< 'Keep alive limit reached' condition.
      INVALID_TRANSMISSION_MODE = 3, //!< 'Invalid transmission mode' condition.
      FILESTORE_REJECTION = 4, //!< 'Filestore rejection' condition.
      FILE_CHECKSUM_FAIL = 5, //!< 'File checksum failure' condition.
      FILE_SIZE_ERROR = 6, //!< 'File size error' condition.
      NAK_LIMIT = 7, //!< 'NAK limit reached' condition.
      INACTIVITY_DETECTED = 8, //!< 'Inactivity detected' condition.
      INVALID_FILE = 9, //!< 'Invalid file structure' condition.
      CHECK_LIMIT = 10, //!< 'Check limit reached' condition.
      UNSUPPORTED_CHECKSUM = 11, //!< 'Unsupported checksum type' condition.
      SUSPEND_RECEIVED = 14, //!< 'Suspend.request received' condition.
      CANCEL_RECEIVED = 15, //!< 'Cancel.request received' condition.
    };

  /*
   * Enum forward declarations.
   */
  public:
    // Enums used in the Header
    enum class Direction;
    enum class TransmissionMode;
    enum class CrcFlag;
    enum class LargeFileFlag;
    enum class SegmentationControl;
    enum class SegmentMetadataFlag;

    // Enums used in the Finished data field
    enum class DeliveryCode;
    enum class FileStatus;

    // Enums used in the Metadata data field
    enum class ClosureRequested;
    enum class ChecksumType;

  /*
   * Nested class forward declarations.
   */
  public:
    class Header;
    class EndOfFile;
    class Finished;
    class Metadata;

  /*
   * Variable-length field formats.
   */
  public:
    //! @brief A class defining the File Size Sensitive (FSS) object format.
    //!
    //! The serialized size of an FSS object is dependent on the large file flag
    //! in the header. If the large file flag indicates a small file, the
    //! value of an FSS object can be represented by a 32-bit unsigned integer
    //! and its serialized size is 4 octets. If the large file flag indicates
    //! a large file, the value of an FSS object can be represented by a 64-bit
    //! unsigned integer and its serialized size is 8 octets.
    //!
    class FileSizeSensitive
    {
      friend EndOfFile;
      friend Metadata;

      public:
        //! @brief Default constructor for an FSS object.
        //!
        FileSizeSensitive();

        //! @brief Construct an FSS object.
        //!
        //! @param value The value of the FSS object.
        //!
        FileSizeSensitive(U64 value);

        //! @brief Get the value.
        //!
        U64 getValue() const;

      PRIVATE:
        //! @brief The value.
        //!
        //! The value is at most a 64-bit unsigned integer.
        //!
        U64 value;

      PRIVATE:
        //! @brief Serialize this FSS object.
        //!
        //! @param buf The buffer to hold the serialized data.
        //! @param offset The byte offset to start serialization from.
        //!
        void serialize(
          const Fw::Buffer& buf,
          U32 offset,
          const Header& header
        ) const;

        //! @brief Deserialize a buffer containing a serialized FSS object.
        //!
        //! @param buf The buffer containing serialized data.
        //! @param offset The byte offset to start deserialization from.
        //!
        void deserialize(
          const Fw::Buffer& buf,
          U32 offset,
          const Header& header
        );

        //! @brief Get the length in octets when serialized.
        //!
        U32 getSerializedLength(const Header& header) const;
    };

    //! @brief A class defining the Length Value (LV) object format.
    //!
    //! An LV object is a variable length object with an 8-bit 'length' field
    //! and a 'value' field containing 'length' number of octets.
    //!
    //! Pre-serialization, the 'value' field will hold a pointer to the value
    //! supplied during construction. Post-deserialization, 'value' will hold a
    //! pointer to the value in the serialized buffer.
    //!
    class LengthValue
    {
      friend Metadata;

      public:
        //! @brief Maximum length for the value field in an LV object.
        //!
        enum
        {
          MAX_LENGTH = 0xFF, //!< Maximum length in octets.
        };

      public:
        //! @brief Construct an empty LV object.
        //!
        LengthValue();

        //! @brief Construct an LV object.
        //!
        //! @param length The length of value in octets.
        //! @param value A pointer to the value.
        //!
        LengthValue(U8 length, const U8* value);

        //! @brief Get the length of value.
        //!
        U8 getLength() const;

        //! @brief Get a pointer to the value.
        //!
        const U8* getValue() const;

      PRIVATE:
        //! @brief The length of value in octets.
        //!
        U8 length;

        //! @brief A pointer to the value.
        //!
        const U8* value;

      PRIVATE:
        //! @brief Serialize this LV object.
        //!
        //! @param buf The buffer to hold the serialized data.
        //! @param offset The byte offset to start serialization from.
        //!
        void serialize(const Fw::Buffer& buf, U32 offset) const;

        //! @brief Deserialize a buffer containing a serialized LV object.
        //!
        //! @param buf The buffer containing serialized data.
        //! @param offset The byte offset to start deserialization from.
        //!
        void deserialize(const Fw::Buffer& buf, U32 offset);

        //! @brief Get the length in octets of LV obejct when serialized.
        //!
        U32 getSerializedLength() const;
    };

  /*
   * Private data field common type.
   */
  PRIVATE:
    //! @brief A CFDP PDU data field.
    //!
    class DataField
    {
      friend FilePacket;

      /*
       * Funtions that all data field types should have.
       */
      PRIVATE:
        virtual void serialize(
          const Fw::Buffer& buf,
          U32 offset,
          const Header& header
        ) const = 0;

        virtual void deserialize(
          const Fw::Buffer& buf,
          U32 offset,
          const Header& header
        ) = 0;

        virtual U32 getSerializedLength(const Header& header) const = 0;
    };

  /*
   * Public functions.
   */
  public:
    //! @brief Construct a CFDP file packet.
    //!
    FilePacket(Header& header, DataField& dataField);

    //! @brief Serialize this file packet into a buffer.
    //!
    //! Buffer data should have enough memory allocated to hold the serialized
    //! header.
    //!
    //! @param buf The buffer to hold the serialized data.
    //! @param offset The byte offset to start serialization from.
    //!
    void serialize(const Fw::Buffer& buf, U32 offset) const;

    //! @brief Deserialize a buffer containing serialized file packet data.
    //!
    //! @param buf The buffer containing serialized data.
    //! @param offset The byte offset to start deserialization from.
    //!
    void deserialize(const Fw::Buffer& buf, U32 offset);

  /*
   * Public static functions.
   */
  public:
    //! @brief Gets the type of the serialized packet in the buffer.
    //!
    //! @param buf The buffer holding a serialized packet.
    //! @param offset The byte offset to the beginning of the serialized packet.
    //!
    static Type getTypeFromBuffer(const Fw::Buffer& buf, U32 offset);

  /*
   * Public member variables.
   */
  public:
    //! @brief The PDU header.
    //!
    Header& header;

    //! @brief The PDU data field.
    //!
    DataField& dataField;

  /*
   * Private static functions.
   */
  PRIVATE:
    //! @brief Serialize an integer value in big-endian format.
    //!
    //! @param data A pointer to the start of the data.
    //! @param value The integer value to write.
    //! @param size The number of bytes required to store the value.
    //!
    static void serializeValue(U8* data, U64 value, U8 size);

    //! @brief Read a serialized integer value in big-endian format.
    //!
    //! @param data A pointer to the start of the data.
    //! @param size The number of bytes required to store the value.
    //!
    static U64 deserializeValue(const U8* data, U8 size);
};

} // namespace Cfdp

} // namespace Fw

#endif // FW_CFDP_FILEPACKET_HPP
