// ======================================================================
// \title Os/Stub/DefaultIntervalTimer.cpp
// \brief sets default Os::IntervalTimer to no-op stub implementation via linker
// ======================================================================
#include "Os/Stub/IntervalTimer.hpp"
#include "Os/Delegate.hpp"
namespace Os {

//! \brief get a delegate for IntervalTimerInterface that intercepts calls for stub file usage
//! \param aligned_new_memory: aligned memory to fill
//! \param to_copy: pointer to copy-constructor input
//! \return: pointer to delegate
IntervalTimerInterface *IntervalTimerInterface::getDelegate(HandleStorage& aligned_new_memory) {
    return Os::Delegate::makeDelegate<IntervalTimerInterface, Os::Stub::IntervalTimer::StubIntervalTimer>(
            aligned_new_memory
    );
}
}
