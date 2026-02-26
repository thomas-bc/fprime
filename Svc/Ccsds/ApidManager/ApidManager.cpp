// ======================================================================
// \title  ApidManager.cpp
// \author thomas-bc
// \brief  cpp file for ApidManager component implementation class
// ======================================================================

#include "Svc/Ccsds/ApidManager/ApidManager.hpp"
#include "Svc/Ccsds/Types/FppConstantsAc.hpp"

namespace Svc {

namespace Ccsds {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ApidManager ::ApidManager(const char* const compName) : ApidManagerComponentBase(compName) {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

U16 ApidManager ::validateApidSeqCountIn_handler(FwIndexType portNum, const ComCfg::Apid& apid, U16 receivedSeqCount) {
    U16 expectedSequenceCount = this->getAndIncrementSeqCount(apid);
    if (receivedSeqCount != expectedSequenceCount && receivedSeqCount != SEQUENCE_COUNT_ERROR) {
        // Likely a packet was dropped or out of order
        this->log_WARNING_LO_UnexpectedSequenceCount(receivedSeqCount, expectedSequenceCount);
        // Synchronize onboard count with received number so that count can keep going
        this->setNextSeqCount(apid, this->calculateNextSeqCount(receivedSeqCount));
    }
    return receivedSeqCount;
}

U16 ApidManager ::getApidSeqCountIn_handler(FwIndexType portNum, const ComCfg::Apid& apid, U16 unused) {
    return this->getAndIncrementSeqCount(apid);
}

// ----------------------------------------------------------------------
// Helpers
// ----------------------------------------------------------------------

U16 ApidManager ::getAndIncrementSeqCount(ComCfg::Apid::T apid) {
    U16 seqCount = 0;
    const Fw::Success found = this->m_apidSeqCountMap.find(apid, seqCount);
    if (found == Fw::Success::FAILURE) {
        // APID not yet tracked — try to insert it with initial count 0
        if (this->m_apidSeqCountMap.insert(apid, 0) != Fw::Success::SUCCESS) {
            this->log_WARNING_HI_ApidTableFull(apid);
            return SEQUENCE_COUNT_ERROR;
        }
    }
    // Update the map entry with the next sequence count (wrapping at 14 bits)
    const U16 nextSeqCount = this->calculateNextSeqCount(seqCount);
    this->m_apidSeqCountMap.insert(apid, nextSeqCount);
    return seqCount;
}

void ApidManager::setNextSeqCount(ComCfg::Apid::T apid, U16 seqCount) {
    // insert() updates the value if the key already exists
    const Fw::Success status = this->m_apidSeqCountMap.insert(apid, seqCount);
    FW_ASSERT(status == Fw::Success::SUCCESS, static_cast<FwAssertArgType>(apid));
}

U16 ApidManager::calculateNextSeqCount(U16 seqCount) {
    return static_cast<U16>((seqCount + 1) % (1 << SpacePacketSubfields::SeqCountWidth));
}

}  // namespace Ccsds
}  // namespace Svc
