// ======================================================================
// \title Os/IntervalTimer.hpp
// \brief common definitions for Os::IntervalTimer
// ======================================================================
#ifndef Os_IntervalTimer_hpp
#define Os_IntervalTimer_hpp

#include <FpConfig.hpp>
#include <Os/Os.hpp>

namespace Os {

struct IntervalTimerHandle {};

class IntervalTimerInterface {
  public:
  /**
   * RawTime:
   *
   * Most time is stored as an upper and lower part of this raw time object. The
   * semantic meaning of this "RawTime" is platform-dependent.
   */
      typedef struct {
          U32 upper;  //!< Upper 32-bits part of time value. Platform dependent.
          U32 lower; //!< Lower 32-bits part of time value. Platform dependent.
      } RawTime;

  public:
    //! \brief default constructor
    IntervalTimerInterface() = default;

    //! \brief default virtual destructor
    virtual ~IntervalTimerInterface() = default;

    //! \brief copy constructor is forbidden
    IntervalTimerInterface(const IntervalTimerInterface& other) = delete;

    //! \brief assignment operator is forbidden
    IntervalTimerInterface& operator=(const IntervalTimerInterface& other) = delete;

    //! \brief return the underlying IntervalTimer handle (implementation specific)
    //! \return internal IntervalTimer handle representation
    virtual IntervalTimerHandle* getHandle() = 0;

    //! \brief provide a pointer to a IntervalTimer delegate object
    static IntervalTimerInterface* getDelegate(HandleStorage& aligned_new_memory);


    //------------ Platform Functions ------------
    // Platform functions, typically do need to be implemented by an OS support package, as
    // they are dependent on the platform definition of "RawTime".
    //------------------------------------------

    /**
     * Returns the difference in microseconds between the supplied times t1, and t2. This
     * calculation is done with respect to the semantic meaning of the times, and thus is
     * dependent on the platform's representation of the RawTime object.
     * \return U32 microsecond difference between two supplied values, t1-t2.
     */
    static U32 getDiffUsec(const RawTime& t1, const RawTime& t2);

    /**
     * Fills the RawTime object supplied with the current raw time in a platform dependent
     * way.
     */
    static void getRawTime(RawTime& time);

};

class IntervalTimer final : public IntervalTimerInterface {
  public:
    IntervalTimer();    //!<  Constructor. IntervalTimer is unlocked when created
    ~IntervalTimer() final;  //!<  Destructor

    //! \brief return the underlying IntervalTimer handle (implementation specific)
    //! \return internal IntervalTimer handle representation
    IntervalTimerHandle* getHandle() override;

    //------------ Common Functions ------------
    // Common functions, typically do not need to be implemented by an OS support package.
    // Common implementations in IntervalTimerCommon.cpp.
    //------------------------------------------
    /**
     * Capture a start time of the interval timed by the interval timer. This fills the
     * start RawTime of the interval.
     */
    void start();
    /**
     * Capture a stop time of the interval timed by the interval timer. This fills the
     * stop RawTime of the interval.
     */
    void stop();
    /**
     * Returns the difference in usecond difference between start and stop times. The caller
     * must have called start and stop previously.
     * \return U32: microseconds difference in the interval
     */
    U32 getDiffUsec();

    //------------ Platform Functions ------------
    // Platform functions, typically do need to be implemented by an OS support package, as
    // they are dependent on the platform definition of "RawTime".
    //------------------------------------------

    /**
     * Returns the difference in microseconds between the supplied times t1, and t2. This
     * calculation is done with respect to the semantic meaning of the times, and thus is
     * dependent on the platform's representation of the RawTime object.
     * \return U32 microsecond difference between two supplied values, t1-t2.
     */
    static U32 getDiffUsec(const RawTime& t1, const RawTime& t2);
    /**
     * Fills the RawTime object supplied with the current raw time in a platform dependent
     * way.
     */
    static void getRawTime(RawTime& time);


    // static void getTime(RawTime& time);


  PRIVATE:
    //------------ Internal Member Variables ------------
    RawTime m_startTime; //!<  Stored start time
    RawTime m_stopTime; //!<  Stored end time

  private:
    // This section is used to store the implementation-defined IntervalTimer handle. To Os::IntervalTimer and fprime, this type is
    // opaque and thus normal allocation cannot be done. Instead, we allow the implementor to store then handle in
    // the byte-array here and set `handle` to that address for storage.
    //
    alignas(FW_HANDLE_ALIGNMENT) HandleStorage m_handle_storage;  //!< IntervalTimer handle storage
    IntervalTimerInterface& m_delegate;                           //!< Delegate for the real implementation
};
}  // namespace Os

#endif
