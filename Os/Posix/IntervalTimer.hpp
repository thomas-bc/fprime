// ======================================================================
// \title Os/Posix/IntervalTimer.hpp
// \brief Posix definitions for Os::IntervalTimer
// ======================================================================
#ifndef OS_POSIX_INTERVALTIMER_HPP
#define OS_POSIX_INTERVALTIMER_HPP

#include <Os/IntervalTimer.hpp>

namespace Os {
namespace Posix {
namespace IntervalTimer {

struct PosixIntervalTimerHandle : public IntervalTimerHandle {};

//! \brief Posix implementation of Os::IntervalTimer
//!
//! Posix implementation of `IntervalTimerInterface` for use as a delegate class handling error-only file operations.
//!
class PosixIntervalTimer : public IntervalTimerInterface {
  public:
    //! \brief constructor
    //!
    PosixIntervalTimer() = default;

    //! \brief destructor
    //!
    ~PosixIntervalTimer() override = default;

    //! \brief return the underlying mutex handle (implementation specific)
    //! \return internal mutex handle representation
    IntervalTimerHandle* getHandle() override;

    static void getRawTime(RawTime& time);
    static U32 getDiffUsec(const RawTime& t1, const RawTime& t2);


  private:
    //! Handle for PosixIntervalTimer
    PosixIntervalTimerHandle m_handle;
};

}  // namespace IntervalTimer
}  // namespace Posix
}  // namespace Os
#endif  // OS_POSIX_INTERVALTIMER_HPP
