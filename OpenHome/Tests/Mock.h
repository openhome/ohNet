#pragma once

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Timer.h>

namespace OpenHome {

namespace Test {
    class ITestPipeWritable;
};

namespace Test {

class MockTimer : public OpenHome::ITimer, private OpenHome::INonCopyable
{
public:
    MockTimer(ITestPipeWritable& aTestPipe, OpenHome::Functor aCallback, const TChar* aId);
    const TChar* Id() const;
    void Fire();
public: // from ITimer
    void FireIn(TUint aMs) override;
    void Cancel() override;
private:
    ITestPipeWritable& iTestPipe;
    OpenHome::Functor iCallback;
    const TChar* iId;
};

class MockTimerFactory : public OpenHome::ITimerFactory, private OpenHome::INonCopyable
{
public:
    MockTimerFactory(ITestPipeWritable& aTestPipe);
    void FireTimer(const TChar* aId);
public: // from ITimerFactory
    OpenHome::ITimer* CreateTimer(OpenHome::Functor aCallback, const TChar* aId) override;
private:
    ITestPipeWritable& iTestPipe;
    std::vector<std::reference_wrapper<MockTimer>> iTimers;
};

} // namespace Test
} // namespace OpenHome
