// ======================================================================
// \title Os/Stub/IntervalTimer.hpp
// \brief Stub definitions for Os::IntervalTimer
// ======================================================================
#ifndef OS_STUB_INTERVALTIMER_HPP
#define OS_STUB_INTERVALTIMER_HPP
#include <Os/IntervalTimer.hpp>

namespace Os {
namespace Stub {
namespace IntervalTimer {

struct StubIntervalTimerHandle : public IntervalTimerHandle {};

//! \brief Stub implementation of Os::IntervalTimer
//!
//! Stub implementation of `IntervalTimerInterface` for use as a delegate class handling error-only file operations.
//!
class StubIntervalTimer : public IntervalTimerInterface {
  public:
    //! \brief constructor
    //!
    StubIntervalTimer() = default;

    //! \brief destructor
    //!
    ~StubIntervalTimer() override = default;

    //! \brief return the underlying mutex handle (implementation specific)
    //! \return internal mutex handle representation
    IntervalTimerHandle* getHandle() override;


    //! \brief Stub implementation - will always return diff=0
    static U32 getDiffUsec(const RawTime& t1, const RawTime& t2);
    //! \brief Stub implementation - will always use time=0
    static void getRawTime(RawTime& time);


  private:
    //! Handle for StubIntervalTimer
    StubIntervalTimerHandle m_handle;
};

}  // namespace IntervalTimer
}  // namespace Stub
}  // namespace Os
#endif  // OS_STUB_INTERVALTIMER_HPP
