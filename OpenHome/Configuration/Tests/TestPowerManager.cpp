#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Configuration/PowerManager.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Thread.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Configuration;

namespace OpenHome {
namespace Configuration {

class SuitePowerManager : public SuiteUnitTest, public INonCopyable
{
public:
    SuitePowerManager(Environment& aEnv);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void NotifyPowerDown1();
    void NotifyPowerDown2();
    void NotifyPowerDown3();
    void TestPowerDownNothingRegistered();
    void TestPriorityLowest();
    void TestPriorityHighest();
    void TestPriorityTooHigh();
    void TestPriorityNormal();
    void TestMultipleFunctorsAddedInOrder();
    void TestMultipleFunctorsAddedInReverseOrder();
    void TestMultipleFunctorsAddedOutOfOrder();
    void TestMultipleFunctorsSamePriority();
    void TestPowerDownTwice();
private:
    static const TUint kSleepTime = 1; // sleep time during callbacks to artificially increase env time
    Environment& iEnv;
    PowerManager* iPowerManager;
    TUint64 iTime1;
    TUint64 iTime2;
    TUint64 iTime3;
};

} // namespace Configuration
} // namespace OpenHome



// SuitePowerManager

SuitePowerManager::SuitePowerManager(Environment& aEnv)
    : SuiteUnitTest("SuitePowerManager")
    , iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPowerDownNothingRegistered));
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPriorityLowest));
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPriorityHighest));
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPriorityTooHigh));
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPriorityNormal));
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestMultipleFunctorsAddedInOrder));
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestMultipleFunctorsAddedInReverseOrder));
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestMultipleFunctorsAddedOutOfOrder));
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestMultipleFunctorsSamePriority));
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPowerDownTwice));
}

void SuitePowerManager::Setup()
{
    iPowerManager = new PowerManager();
    iTime1 = 0;
    iTime2 = 0;
    iTime3 = 0;
}

void SuitePowerManager::TearDown()
{
    delete iPowerManager;
}

void SuitePowerManager::NotifyPowerDown1()
{
    iTime1 = Os::TimeInUs(iEnv.OsCtx());
    Thread::Sleep(kSleepTime);
}

void SuitePowerManager::NotifyPowerDown2()
{
    iTime2 = Os::TimeInUs(iEnv.OsCtx());
    Thread::Sleep(kSleepTime);
}

void SuitePowerManager::NotifyPowerDown3()
{
    iTime3 = Os::TimeInUs(iEnv.OsCtx());
    Thread::Sleep(kSleepTime);
}

void SuitePowerManager::TestPowerDownNothingRegistered()
{
    // Successful completion of this test suggests nothing nasty will happen
    // when PowerDown() is called with no callback functors registered.
    iPowerManager->PowerDown();
}

void SuitePowerManager::TestPriorityLowest()
{
    // Test that a functor with the lowest priority can be registered and called.
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown1), kPriorityLowest);
    iPowerManager->PowerDown();
    TEST(iTime1 != 0);
}

void SuitePowerManager::TestPriorityHighest()
{
    // Test that a functor with the highest priority can be registered and called.
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown1), kPriorityHighest);
    iPowerManager->PowerDown();
    TEST(iTime1 != 0);
}

void SuitePowerManager::TestPriorityNormal()
{
    // Test that a functor with a normal priority can be registered and called.
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown1), kPriorityNormal);
    iPowerManager->PowerDown();
    TEST(iTime1 != 0);
}

void SuitePowerManager::TestPriorityTooHigh()
{
    // Test that PowerManager asserts when a functor with too high a priority
    // is registered.
    TEST_THROWS(iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown1), kPriorityHighest+1), AssertionFailed);
}

void SuitePowerManager::TestMultipleFunctorsAddedInOrder()
{
    // Add multiple functors, in order of calling priority, and check they are
    // called in order.
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown1), kPriorityHighest);
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown2), kPriorityNormal);
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown3), kPriorityLowest);
    iPowerManager->PowerDown();
    Log::Print("TestMultipleFunctorsAddedInOrder iTimes (us): %llu | %llu | %llu\n", iTime1, iTime2, iTime3);
    TEST((iTime1 > 0) && (iTime2 > 0) && (iTime3 > 0));
    TEST(iTime1 < iTime2);
    TEST(iTime2 < iTime3);
}

void SuitePowerManager::TestMultipleFunctorsAddedInReverseOrder()
{
    // Add multiple functors, in reverse order of calling priority, and check
    // they are called in order.
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown3), kPriorityLowest);
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown2), kPriorityNormal);
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown1), kPriorityHighest);
    iPowerManager->PowerDown();
    Log::Print("TestMultipleFunctorsAddedInReverseOrder iTimes (us): %llu | %llu | %llu\n", iTime1, iTime2, iTime3);
    TEST((iTime1 > 0) && (iTime2 > 0) && (iTime3 > 0));
    TEST(iTime1 < iTime2);
    TEST(iTime2 < iTime3);
}

void SuitePowerManager::TestMultipleFunctorsAddedOutOfOrder()
{
    // Add multiple functors, in a non-linear order of calling, and check they
    // are called in order.
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown2), kPriorityNormal);
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown1), kPriorityHighest);
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown3), kPriorityLowest);
    iPowerManager->PowerDown();
    Log::Print("TestMultipleFunctorsAddedOutOfOrder iTimes (us): %llu | %llu | %llu\n", iTime1, iTime2, iTime3);
    TEST((iTime1 > 0) && (iTime2 > 0) && (iTime3 > 0));
    TEST(iTime1 < iTime2);
    TEST(iTime2 < iTime3);
}

void SuitePowerManager::TestMultipleFunctorsSamePriority()
{
    // Add multiple functors, with some having the same priority, and check
    // that functors with the same priority are called in the order they were
    // added.
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown1), kPriorityHighest);
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown2), kPriorityNormal);
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown3), kPriorityNormal);
    iPowerManager->PowerDown();
    Log::Print("TestMultipleFunctorsSamePriority iTimes (us): %llu | %llu | %llu\n", iTime1, iTime2, iTime3);
    TEST((iTime1 > 0) && (iTime2 > 0) && (iTime3 > 0));
    TEST(iTime1 < iTime2);
    TEST(iTime2 < iTime3);
}

void SuitePowerManager::TestPowerDownTwice()
{
    // As PowerDown() should only be called once, test that subsequent calls to
    // it do nothing.
    iPowerManager->RegisterObserver(MakeFunctor(*this, &SuitePowerManager::NotifyPowerDown1), kPriorityNormal);
    iPowerManager->PowerDown();
    TEST(iTime1 > 0);

    // Call PowerDown() again. Should have no effect this time.
    iTime1 = 0;
    iPowerManager->PowerDown();
    TEST(iTime1 == 0);
}



void TestPowerManager(Environment& aEnv)
{
    Runner runner("PowerManager tests\n");
    runner.Add(new SuitePowerManager(aEnv));
    runner.Run();
}
