//! ============================================================================
//! @file   Ack.hpp
//! @brief  hpp file for a CFDP file packet Ack data field.
//! @author chownw
//! ============================================================================

#ifndef FW_CFDP_ACK_HPP
#define FW_CFDP_ACK_HPP

#include <FpConfig.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Ccsds/Cfdp/FilePacket.hpp>

namespace Fw
{

namespace Cfdp
{

//! @brief Directive subtype options.
//!
enum class FilePacket::DirectiveSubtypeCode
{
  ACK_OTHER = 0, //!< Acknowledges all other file directive packets.
  ACK_FINISHED = 1, //!< Acknowledges a Finished file directive packet.
};

//! @brief Transaction status options.
//!
enum class FilePacket::TransactionStatus
{
  UNDEFINED = 0, //!< Transaction is not currently active.
  ACTIVE = 1, //!< Transaction is currently active.
  TERMINATED = 2, //!< Transaction was formerly active and has been terminated.
  UNRECOGNIZED = 3, //!< Transaction was never active.
};

//! @brief A CFDP file packet Ack data field.
//!
class FilePacket::Ack : public DataField
{
  friend FilePacket;

  public:
    //! @brief Construct an empty CFDP file packet Ack data field type.
    //!
    //! This can be used to construct an initially empty data field for
    //! deserialized data.
    //!
    Ack();

    //! @brief Construct a filled CFDP file packet Ack data field type.
    //!
    //! This can be used to construct a data field with values for
    //! serialization.
    //!
    //! @param directiveCode The directive code of packet being acknowledged.
    //! @param subtypeCode The directive subtype code.
    //! @param conditionCode The condition code of packet being acknowledged.
    //! @param status The status of the transaction at the Ack issuing entity.
    //!
    Ack(
      DirectiveType directiveCode,
      DirectiveSubtypeCode subtypeCode,
      ConditionCode conditionCode,
      TransactionStatus status
    );

    //! @brief Get the directive code of the packet being acknowledged.
    //!
    DirectiveType getDirectiveCode() const;

    //! @brief Get the directive subtype code of the packet being acknowledged.
    //!
    DirectiveSubtypeCode getSubtypeCode() const;

    //! @brief Get the condition code of the file packet being acknowledged.
    //!
    ConditionCode getConditionCode() const;

    //! @brief Get the status of the transaction at the Ack issuing entity.
    //!
    TransactionStatus getTransactionStatus() const;

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
      ACK_DIRECTIVE_CODE = 4,
      SUBTYPE_CODE = 4,
      CONDITION_CODE = 4,
      SPARE = 2,
      TRANSACTION_STATUS = 2,
    };

    //! @brief Total length of fixed-size fields.
    //!
    enum FixedSize : U32
    {
      BITS =
        FieldLength::DIRECTIVE_CODE
        + FieldLength::ACK_DIRECTIVE_CODE
        + FieldLength::SUBTYPE_CODE
        + FieldLength::CONDITION_CODE
        + FieldLength::SPARE
        + FieldLength::TRANSACTION_STATUS,
      BYTES = BITS / 8,
    };

    //! @brief Identifies the data field type.
    //!
    static DirectiveType directiveCode;

    //! @brief Directive code of the file packet being acknowledged.
    //!
    DirectiveType ackDirectiveCode;

    //! @brief Directive subtype code of the file packet being acknowledged.
    //!
    DirectiveSubtypeCode subtypeCode;

    //! @brief Condition code of the file packet being acknowledged.
    //!
    ConditionCode conditionCode;

    //! @brief Spare bits, set to all zeroes.
    //!
    U8 spare;

    //! @brief Status of the transaction at the Ack issuing entity.
    //!
    TransactionStatus transactionStatus;
};

} // Cfdp

} // Fw

#endif // FW_CFDP_ACK_HPP
