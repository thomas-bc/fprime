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
class FilePacket
{

  public:
    //! @brief PDU type options.
    //!
    enum class Type
    {
      FILE_DIRECTIVE = 0, //!< Indicates a file directive PDU.
      FILE_DATA = 1, //!< Indicates a file data PDU.
    };

    //! @brief PDU direction options.
    //!
    //! Used to perform PDU forwarding.
    //!
    enum class Direction
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
    enum class TransmissionMode
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
    enum class CrcFlag
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
    enum class LargeFileFlag
    {
      SMALL_FILE = 0, //!< Indicates a 'small' file.
      LARGE_FILE = 1, //!< Indicates a 'large' file.
    };

    //! @brief Segmentation control options.
    //!
    //! If flag is PRESERVED, then record boundaries are preserved in file data
    //! segmentation.
    //!
    enum class SegmentationControl
    {
      NOT_PRESERVED = 0, //!< Indicates record boundaries are not preserved.
      PRESERVED = 1, //!< Indicates record boundaries are preserved.
    };

    //! @brief Segment metadata flag options.
    //!
    enum class SegmentMetadataFlag
    {
      NOT_PRESENT = 0, //!< Indicates segment metadata is not in the PDU.
      PRESENT = 1, //!< Indicates segment metadata is in the PDU.
    };

  public:
    //! @brief A class defining the Length Value (LV) object format.
    //!
    //! An LV object is a variable length object with an 8-bit length field and
    //! a value field containing length number of octets.
    //!
    //! Pre-serialization, the value field will hold a pointer to the value
    //! supplied during construction. Post-deserialization, value will hold a
    //! pointer to the value in the serialized buffer.
    //!
    class LengthValue
    {
      public:
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

      PROTECTED:
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
        //!
        void serialize(Fw::Buffer& buf);

        //! @brief Deserialize a buffer containing a serialized LV object.
        //!
        //! @param buf The buffer containing serialized data.
        //!
        void deserialize(Fw::Buffer& buf);
    };

    //! @brief A class defining the Type Length Value (TLV) object format.
    //!
    //! A TLV object is an LV object with an added 8-bit type field describing
    //! the nature of the value.
    //!
    class TypeLengthValue : public LengthValue
    {
      public:
        enum class TlvType
        {
          FILESTORE_REQUEST = 0x00, //!< The Filestore Request TLV type.
          FILESTORE_RESPONSE = 0x01, //!< The Filestore Response TLV type.
          MESSAGE_TO_USER = 0x02, //!< The Message to User TLV type.
          FAULT_HANDLER_OVR = 0x04, //!< The Fault Handler Override TLV type.
          FLOW_LABEL = 0x05, //!< The Flow Label TLV type.
          ENTITY_ID = 0x06, //!< The Entity ID TLV type.
        };

      public:
        //! @brief Construct a TLV object.
        //!
        //! @param type The type of the value.
        //! @param length The length of value in octets.
        //! @param value A pointer to the value.
        //!
        TypeLengthValue(TlvType type, U8 length, const U8* value);

        //! @brief Get the type of value.
        //!
        TlvType getType();

      PRIVATE:
        //! @brief The type of value.
        //!
        TlvType type;

      PRIVATE:
        //! @brief Serialize this TLV object.
        //!
        //! @param buf The buffer to hold the serialized data.
        //!
        void serialize(Fw::Buffer& buf);

        //! @brief Deserialize a buffer containing a serialized TLV object.
        //!
        //! @param buf The buffer containing serialized data.
        //!
        void deserialize(Fw::Buffer& buf);
    };

  public:
    class Header;

  public:
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

  public:
    //! @brief Construct a CFDP file packet.
    //!
    FilePacket(Header& header);

    //! @brief The PDU header.
    //!
    Header& header;
};

} // namespace Cfdp

} // namespace Fw

#endif // FW_CFDP_FILEPACKET_HPP
