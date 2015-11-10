#pragma once

#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Standard.h>

#include <map>
#include <limits.h>

namespace OpenHome {
namespace TestFramework {

class ITimerFactoryMock;

class TimerMock : public ITimer, private INonCopyable
{
    friend class TimerFactoryMock;
public:
    TimerMock(ITimerFactoryMock& aFactory, Functor aCb, const TChar* aId);
    const TChar* Id() const;
private: // from ITimer
    ~TimerMock();
    void FireIn(TUint aMs);
    void Cancel();
private:
    void AddRef();
    void RemoveRef();
private:
    ITimerFactoryMock& iFactory;
    Functor iCb;
    const TChar* iId;
    Semaphore iBusy;
    TUint iRefCount;
};

class ITimerFactoryMock
{
public:
    virtual ~ITimerFactoryMock() {}
    virtual void Queue(TimerMock& aTimer, TUint aIn) = 0;
    virtual void Cancel(TimerMock& aTimer) = 0;
    virtual void Remove(TimerMock& aTimer) = 0;
};

class TimerFactoryMock : public ITimerFactory, private ITimerFactoryMock
{
    friend class TimerMock;
    static const TUint kDueTimeNever;
public:
    TimerFactoryMock();
    ~TimerFactoryMock();
    void Advance(TUint aMs);
public: // from ITimerFactory
    ITimer* CreateTimer(Functor aCallback, const TChar* aId);
private: // from ITimerFactoryMock
    void Queue(TimerMock& aTimer, TUint aIn);
    void Cancel(TimerMock& aTimer);
    void Remove(TimerMock& aTimer);
private:
    void RemoveLocked(TimerMock& aTimer);
private:
    Mutex iLock;
    std::map<TUint, TimerMock*> iTimers;
    TUint iNowMs;
};

} // namespace TestFramework
} // namespace Linn

