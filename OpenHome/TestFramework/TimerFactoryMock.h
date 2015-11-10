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

class TimerMock : public OpenHome::ITimer, private OpenHome::INonCopyable
{
    friend class TimerFactoryMock;
public:
    TimerMock(ITimerFactoryMock& aFactory, OpenHome::Functor aCb, const TChar* aId);
private: // from OpenHome::ITimer
    ~TimerMock();
    void FireIn(TUint aMs) override;
    void Cancel() override;
private:
    void AddRef();
    void RemoveRef();
private:
    ITimerFactoryMock& iFactory;
    OpenHome::Functor iCb;
    const TChar* iId;
    OpenHome::Semaphore iBusy;
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
    OpenHome::ITimer* CreateTimer(OpenHome::Functor aCallback, const TChar* aId) override;
private: // from ITimerFactoryMock
    void Queue(TimerMock& aTimer, TUint aIn) override;
    void Cancel(TimerMock& aTimer) override;
    void Remove(TimerMock& aTimer) override;
private:
    void RemoveLocked(TimerMock& aTimer);
private:
    OpenHome::Mutex iLock;
    std::map<TUint, TimerMock*> iTimers;
    TUint iNowMs;
};

} // namespace TestFramework
} // namespace Linn

