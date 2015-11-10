#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/TimerFactoryMock.h>
#include <vector>
#include <memory>

using namespace OpenHome;
using namespace OpenHome::TestFramework;


class EventRecorder
{
public:
    void Push0() {
        iEvents.push_back(0);
    }
    void Push1() {
        iEvents.push_back(1);
    }
    Functor Get0() {
        return MakeFunctor(*this, &EventRecorder::Push0);
    }
    Functor Get1() {
        return MakeFunctor(*this, &EventRecorder::Push1);
    }
    TBool Compare(const std::vector<TUint>& aExpected) {
        return iEvents == aExpected;
    }
private:
    std::vector<TUint> iEvents;
};

// Repeater pushes an incrementing TUint into a vector, which
// can be checked with Compare(). This happens after first period,
// then periodically thereafter, until dtor.
class Repeater
{
public:
    Repeater(ITimerFactory& aTimerFactory, TUint aPeriodMs)
        : iPeriodMs(aPeriodMs)
        , iCount(0)
    {
        iTimer = aTimerFactory.CreateTimer(
            MakeFunctor(*this, &Repeater::PushIncAndRepeat), "PushIncAndRepeat");
        iTimer->FireIn(iPeriodMs);
    }
    ~Repeater() {
        delete iTimer;
    }
    TBool Compare(const std::vector<TUint>& aExpected) {
        return iEvents == aExpected;
    }
private:
    void PushIncAndRepeat() {
        iEvents.push_back(iCount++);
        iTimer->FireIn(iPeriodMs);
    }
private:
    TUint iPeriodMs;
    TUint iCount;
    ITimer* iTimer;
    std::vector<TUint> iEvents;
};

class SuiteTimerMock : public Suite
{
public:
    SuiteTimerMock() : Suite("Test TimerMock") {}
    void Test();
};

void SuiteTimerMock::Test()
{
    {
        TimerFactoryMock tmm;
        ITimerFactory& tm = tmm;
        EventRecorder er;
        std::vector<TUint> expected;

        ITimer* t0 = tm.CreateTimer(er.Get0(), "0");
        ITimer* t1 = tm.CreateTimer(er.Get1(), "1");

        t0->FireIn(100);
        t1->FireIn(200);

        tmm.Advance(99);        // nothing should fire yet
        TEST(er.Compare(expected));   // check no events

        tmm.Advance(1);         // t0 should fire
        expected.push_back(0);
        TEST(er.Compare(expected));  // check single event0

        tmm.Advance(99);        // t1 still waiting
        TEST(er.Compare(expected));  // check no change
        tmm.Advance(1);         // t0 should fire
        expected.push_back(1);
        TEST(er.Compare(expected));  // check t1 has fired.

        delete t0;
        delete t1;
    }

    {
        TimerFactoryMock tmm;
        Repeater r(tmm, 100);
        std::vector<TUint> expected;

        tmm.Advance(99);
        TEST(r.Compare(expected)); // no events
        tmm.Advance(1);
        expected.push_back(0);
        TEST(r.Compare(expected)); // first firing.

        tmm.Advance(300); // now at 400ms
        expected.push_back(1);
        expected.push_back(2);
        expected.push_back(3);
        TEST(r.Compare(expected)); // should have fired at 100ms, 200ms, 300ms and 400ms.
    }
}

void TestTimerMock()
{
    Runner runner("TestTimerMock");
    runner.Add(new SuiteTimerMock());
    runner.Run();
}
