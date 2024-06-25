//! ============================================================================
//! @file   FilePacket.hpp
//! @brief  hpp file for a CFDP PDU file packet.
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

  /*
   * Enum forward declarations.
   */
  public:
    // Header related enums
    enum class Type;
    enum class Direction;
    enum class TransmissionMode;
    enum class CrcFlag;
    enum class LargeFileFlag;
    enum class SegmentationControl;
    enum class SegmentMetadataFlag;

  /*
   * Nested class forward declarations.
   */
  public:
    class Header;

  /*
   * Public functions.
   */
  public:
    //! @brief Construct a CFDP file packet.
    //!
    FilePacket(Header& header);

    //! @brief Serialize this file packet into a buffer.
    //!
    //! Buffer data should have enough memory allocated to hold the serialized
    //! header.
    //!
    //! @param buf The buffer to hold the serialized data.
    //!
    void serialize(Fw::Buffer& buf);

    //! @brief Deserialize a buffer containing serialized file packet data.
    //!
    //! @param buf The buffer containing serialized data.
    //!
    void deserialize(Fw::Buffer& buf);

  /*
   * Public member variables.
   */
  public:
    //! @brief The PDU header.
    //!
    Header& header;

  /*
   * Internal variable-length field formats.
   */
  PRIVATE:
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
        U8 getLength();

        //! @brief Get a pointer to the value.
        //!
        const U8* getValue();

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
        void serialize(Fw::Buffer& buf, U32 offset);

        //! @brief Deserialize a buffer containing a serialized LV object.
        //!
        //! @param buf The buffer containing serialized data.
        //! @param offset The byte offset to start deserialization from.
        //!
        void deserialize(Fw::Buffer& buf, U32 offset);

        //! @brief Get the length in octets of LV obejct when serialized.
        //!
        U32 getSerializedLength();
    };
};

} // namespace Cfdp

} // namespace Fw

#endif // FW_CFDP_FILEPACKET_HPP
