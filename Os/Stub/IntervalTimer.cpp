// ======================================================================
// \title Os/Stub/IntervalTimer.cpp
// \brief Stub implementation for Os::IntervalTimer
// ======================================================================
#include <Os/Stub/IntervalTimer.hpp>
// #include <Os/Stub/error.hpp>
#include <Fw/Types/Assert.hpp>

namespace Os {
namespace Stub {
namespace IntervalTimer {


    U32 StubIntervalTimer:: getDiffUsec(const RawTime& t1, const RawTime& t2) {
        return 0;
    }

    void StubIntervalTimer:: getRawTime(RawTime& time) {
        time.lower = 0;
        time.upper = 0;
        // Or no-op ?? essentially just as useless
    }


IntervalTimerHandle* StubIntervalTimer::getHandle() {
    return &this->m_handle;
}
}  // namespace IntervalTimer
}  // namespace Stub
}  // namespace Os
