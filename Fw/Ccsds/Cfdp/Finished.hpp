//! ============================================================================
//! @file   Finished.hpp
//! @brief  hpp file for a CFDP file packet Finished data field.
//! @author chownw
//! ============================================================================

#ifndef FW_CFDP_FINISHED_HPP
#define FW_CFDP_FINISHED_HPP

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>

namespace Fw
{

namespace Cfdp
{

//! @brief Delivery code options.
//!
//! DATA_COMPELTE indicates that metadata, all file data, and EOF have been
//! received, and the checksum has been verified.
//!
enum class FilePacket::DeliveryCode
{
  DATA_COMPLETE = 0, //!< Indicates data complete.
  DATA_INCOMPLETE = 1, //!< Indicates data incomplete.
};

//! @brief File status options.
//!
enum class FilePacket::FileStatus
{
  DISCARDED_DELIBERATE = 0, //!< Delivered file discarded deliberately.
  DISCARDED_REJECTED = 1, //!< Delivered file discarded filestore rejection.
  SUCCESS = 2, //!< Delivered file retained in filestore successfully.
  UNREPORTED = 3, //!< Delivered file status unreported.
};

//! @brief A CFDP file packet Finished data field.
//!
class FilePacket::Finished : public DataField
{
  friend FilePacket;

  public:
    //! @brief Construct an empty CFDP file packet Finished data field type.
    //!
    //! This can be used to construct an initially empty data field for
    //! deserialized data.
    //!
    Finished();

    //! @brief Construct a filled CFDP file packet Finished data field type.
    //!
    //! This can be used to construct a data field with values for
    //! serialization.
    //!
    //! @param conditionCode The condition code.
    //! @param deliveryCode The delivery code.
    //! @param fileStatus The file status.
    //!
    Finished(
      ConditionCode conditionCode,
      DeliveryCode deliveryCode,
      FileStatus fileStatus
    );

    //! @brief Get the condition code.
    //!
    ConditionCode getConditionCode() const;

    //! @brief Get the delivery code.
    //!
    DeliveryCode getDeliveryCode() const;

    //! @brief Get the file status.
    //!
    FileStatus getFileStatus() const;

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
    //! @brief Length in bits of fixed-size fields.
    //!
    enum FieldLength : U32
    {
      DIRECTIVE_CODE = 8,
      CONDITION_CODE = 4,
      SPARE = 1,
      DELIVERY_CODE = 1,
      FILE_STATUS = 2,
    };

    //! @brief Total length of fixed-size fields.
    //!
    enum FixedSize : U32
    {
      BITS =
        FieldLength::DIRECTIVE_CODE
        + FieldLength::CONDITION_CODE
        + FieldLength::SPARE
        + FieldLength::DELIVERY_CODE
        + FieldLength::FILE_STATUS,
      BYTES = BITS / 8,
    };

    //! @brief Identifies the data field type.
    //!
    static DirectiveType directiveCode;

    //! @brief Condition code.
    //!
    ConditionCode conditionCode;

    //! @brief Spare bits, set to all zeroes.
    //!
    U8 spare;

    //! @brief Delivery code.
    //!
    DeliveryCode deliveryCode;

    //! @brief Delivered file status.
    //!
    FileStatus fileStatus;

    // NOTE: Filestore responses field not supported.
    // NOTE: Fault location field not supported.
};

} // Cfdp

} // Fw

#endif // FW_CFDP_FINISHED_HPP
