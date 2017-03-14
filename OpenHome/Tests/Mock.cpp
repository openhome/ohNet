#include <OpenHome/Tests/Mock.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Tests/TestPipe.h>
#include <OpenHome/Private/Ascii.h>

#include <functional>

using namespace OpenHome;
using namespace OpenHome::Test;


// MockTimer

MockTimer::MockTimer(ITestPipeWritable& aTestPipe, Functor aCallback, const TChar* aId)
    : iTestPipe(aTestPipe)
    , iCallback(aCallback)
    , iId(aId)
{
}

const TChar* MockTimer::Id() const
{
    return iId;
}

void MockTimer::Fire()
{
    iCallback();
}

void MockTimer::FireIn(TUint aMs)
{
    Bws<64> buf("MT::FireIn ");
    buf.Append(iId);
    buf.Append(' ');
    Ascii::AppendDec(buf, aMs);
    iTestPipe.Write(buf);
}

void MockTimer::Cancel()
{
    Bws<64> buf("MT::Cancel ");
    buf.Append(iId);
    iTestPipe.Write(buf);
}


// MockTimerFactory

MockTimerFactory::MockTimerFactory(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

void MockTimerFactory::FireTimer(const TChar* aId)
{
    for (MockTimer& t : iTimers) {
        if (*aId == *t.Id()) {
            t.Fire();
            return;
        }
    }
    ASSERTS(); // No such timer.
}

ITimer* MockTimerFactory::CreateTimer(Functor aCallback, const TChar* aId)
{
    // The ITimer that is returned from here must not be destroyed until all
    // calls to FireTimer() have been made.
    MockTimer* timer = new MockTimer(iTestPipe, aCallback, aId);
    iTimers.push_back(*timer);
    return timer;
}
