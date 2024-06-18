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
    //! If the file is a LARGE_FILE, then it cannot be represented in an
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
    FilePacket(Header& header) : header(header)
    {
    };

    //! @brief The PDU header.
    //!
    Header& header;
};

} // namespace Cfdp

} // namespace Fw

#endif // FW_CFDP_FILEPACKET_HPP
