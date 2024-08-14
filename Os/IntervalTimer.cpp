// ======================================================================
// \title Os/IntervalTimer.cpp
// \brief common function implementation for Os::IntervalTimer
// ======================================================================
#include <Fw/Types/Assert.hpp>
#include <Os/IntervalTimer.hpp>
#include <cstring>

namespace Os {

IntervalTimer::IntervalTimer() : m_handle_storage(), m_delegate(*IntervalTimerInterface::getDelegate(m_handle_storage)) {
    FW_ASSERT(&this->m_delegate == reinterpret_cast<IntervalTimerInterface*>(&this->m_handle_storage[0]));
    memset(&this->m_startTime,0,sizeof(this->m_startTime));
    memset(&this->m_stopTime,0,sizeof(this->m_stopTime));
}

IntervalTimer::~IntervalTimer() {
    FW_ASSERT(&this->m_delegate == reinterpret_cast<IntervalTimerInterface*>(&this->m_handle_storage[0]));
    m_delegate.~IntervalTimerInterface();
}

IntervalTimerHandle* IntervalTimer::getHandle() {
    FW_ASSERT(&this->m_delegate == reinterpret_cast<IntervalTimerInterface*>(&this->m_handle_storage[0]));
    return this->m_delegate.getHandle();
}

void IntervalTimer::start() {
    this->m_delegate.getRawTime(this->m_startTime);
}

void IntervalTimer::stop() {
    this->m_delegate.getRawTime(this->m_stopTime);
}

// void IntervalTimer::getRawTime(RawTime& time) {
//     this->m_delegate.getRawTime(time);
// }

// U32 IntervalTimer::getDiffUsec(const RawTime& t1, const RawTime& t2) {
//     return this->m_delegate.getDiffUsec(t1, t2);
// }

U32 IntervalTimer::getDiffUsec() {
    return this->m_delegate.getDiffUsec(this->m_stopTime, this->m_startTime);
}

// void IntervalTimer::getRawTime(RawTime& time) {
//     this->m_delegate.getRawTime(time);
// }

}  // namespace Os
