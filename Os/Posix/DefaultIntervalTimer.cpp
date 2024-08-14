// ======================================================================
// \title Os/Posix/DefaultIntervalTimer.cpp
// \brief sets default Os::IntervalTimer Posix implementation via linker
// ======================================================================
#include "Os/Posix/IntervalTimer.hpp"
#include "Os/Delegate.hpp"
namespace Os {

//! \brief get a delegate for IntervalTimerInterface that intercepts calls for Posix
//! \param aligned_new_memory: aligned memory to fill
//! \return: pointer to delegate
IntervalTimerInterface *IntervalTimerInterface::getDelegate(HandleStorage& aligned_new_memory) {
    return Os::Delegate::makeDelegate<IntervalTimerInterface, Os::Posix::IntervalTimer::PosixIntervalTimer>(
            aligned_new_memory
    );
}
}
