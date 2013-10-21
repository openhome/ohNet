#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Configuration/PowerManager.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>
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
    IPowerManager* iPowerManager;
    TUint64 iTime1;
    TUint64 iTime2;
    TUint64 iTime3;
};

class SuiteStoreInt : public SuiteUnitTest, private INonCopyable
{
public:
    SuiteStoreInt();
    static TInt IntFromStore(IStoreReadOnly& aStore, const Brx& aKey);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestValueFromStore();
    void TestValueWrittenToStore();
    void TestGet();
    void TestSet();
    void TestWrite();
private:
    static const TUint kPriority = kPriorityNormal;
    static const TInt kDefault = 50;
    static const Brn kKey;
    IStoreReadWrite* iStore;
    IPowerManager* iPowerManager;
    StoreInt* iStoreInt;
};

class SuiteStoreIntOrdering : public SuiteUnitTest, private INonCopyable
{
public:
    SuiteStoreIntOrdering(Environment& aEnv);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestPriorityPassedCorrectly();
private:
    class OrderingRamStore : public ConfigRamStore
    {
    public:
        OrderingRamStore(Environment& aEnv);
    public: // from IStoreReadWrite
        void Write(const Brx& aKey, const Brx& aSource);
    private:
        static const TUint kSleepTime = 1;
        Environment& iEnv;
    };
private:
    static const TInt kDefault = 50;
    static const Brn kKey1;
    static const Brn kKey2;
    static const Brn kKey3;
    Environment& iEnv;
    IStoreReadWrite* iStore;
    IPowerManager* iPowerManager;
    StoreInt* iStoreInt1;
    StoreInt* iStoreInt2;
    StoreInt* iStoreInt3;
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


// SuiteStoreInt

const Brn SuiteStoreInt::kKey("store.int.key");

SuiteStoreInt::SuiteStoreInt()
    : SuiteUnitTest("SuiteStoreInt")
{
    AddTest(MakeFunctor(*this, &SuiteStoreInt::TestValueFromStore));
    AddTest(MakeFunctor(*this, &SuiteStoreInt::TestValueWrittenToStore));
    AddTest(MakeFunctor(*this, &SuiteStoreInt::TestGet));
    AddTest(MakeFunctor(*this, &SuiteStoreInt::TestSet));
    AddTest(MakeFunctor(*this, &SuiteStoreInt::TestWrite));
}

TInt SuiteStoreInt::IntFromStore(IStoreReadOnly& aStore, const Brx& aKey)
{
    Bws<sizeof(TInt)> buf;
    aStore.Read(aKey, buf);
    TInt val = Converter::BeUint32At(buf, 0);
    return val;
}

void SuiteStoreInt::Setup()
{
    iStore = new ConfigRamStore();
    iPowerManager = new PowerManager();
    iStoreInt = new StoreInt(*iStore, *iPowerManager, kPriority, kKey, kDefault);
}

void SuiteStoreInt::TearDown()
{
    delete iStoreInt;
    delete iPowerManager;
    delete iStore;
}

void SuiteStoreInt::TestValueFromStore()
{
    // Test an existing value in store overwrites the default value at creation.

    // add value to store
    static const Brn key("store.int.key2");
    const TInt storeVal = kDefault*2;
    Bws<sizeof(TInt)> buf;
    buf.Append(Arch::BigEndian4(storeVal));
    iStore->Write(key, buf);

    // create StoreInt and check it uses value from store
    StoreInt storeInt(*iStore, *iPowerManager, kPriority, key, kDefault);
    TEST(storeInt.Get() == storeVal);

    // check store hasn't been overwritten as a side-effect
    TEST(IntFromStore(*iStore, key) == storeVal);
}

void SuiteStoreInt::TestValueWrittenToStore()
{
    // Test that the default value has been written out to store at creation.
    TEST(IntFromStore(*iStore, kKey) == kDefault);
}

void SuiteStoreInt::TestGet()
{
    // Test that correct value is returned.
    TEST(iStoreInt->Get() == kDefault);
}

void SuiteStoreInt::TestSet()
{
    // Test that setting (and retrieving) a value results in a new value.
    static const TInt newVal = kDefault*2;
    iStoreInt->Set(newVal);
    TEST(iStoreInt->Get() == newVal);

    // check store hasn't been updated
    TEST(IntFromStore(*iStore, kKey) == kDefault);
}

void SuiteStoreInt::TestWrite()
{
    // Test that current value is written out when PowerDown() is called.

    // give the StoreInt a new value
    static const TInt newVal = kDefault*2;
    iStoreInt->Set(newVal);

    // write out new value and check store has been updated
    iPowerManager->PowerDown();
    TEST(IntFromStore(*iStore, kKey) == newVal);
    TEST(iStoreInt->Get() == newVal);
}


// SuiteStoreIntOrdering::OrderingRamStore

SuiteStoreIntOrdering::OrderingRamStore::OrderingRamStore(Environment& aEnv)
    : ConfigRamStore()
    , iEnv(aEnv)
{
}

void SuiteStoreIntOrdering::OrderingRamStore::Write(const Brx& aKey, const Brx& /*aSource*/)
{
    TUint time = Os::TimeInMs(iEnv.OsCtx());
    Bws<sizeof(TInt)> buf;
    buf.Append(Arch::BigEndian4(time));
    ConfigRamStore::Write(aKey, buf);
    Thread::Sleep(kSleepTime);
}


// SuiteStoreIntOrdering

const Brn SuiteStoreIntOrdering::kKey1("store.int.key1");
const Brn SuiteStoreIntOrdering::kKey2("store.int.key2");
const Brn SuiteStoreIntOrdering::kKey3("store.int.key3");

SuiteStoreIntOrdering::SuiteStoreIntOrdering(Environment& aEnv)
    : SuiteUnitTest("SuiteStoreIntOrdering")
    , iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuiteStoreIntOrdering::TestPriorityPassedCorrectly));
}

void SuiteStoreIntOrdering::Setup()
{
    iStore = new OrderingRamStore(iEnv);
    iPowerManager = new PowerManager();
    iStoreInt1 = new StoreInt(*iStore, *iPowerManager, kPriorityNormal, kKey1, kDefault);
    iStoreInt2 = new StoreInt(*iStore, *iPowerManager, kPriorityLowest, kKey2, kDefault+1);
    iStoreInt3 = new StoreInt(*iStore, *iPowerManager, kPriorityHighest, kKey3, kDefault+2);
}

void SuiteStoreIntOrdering::TearDown()
{
    delete iStoreInt1;
    delete iStoreInt2;
    delete iStoreInt3;
    delete iPowerManager;
    delete iStore;
}

void SuiteStoreIntOrdering::TestPriorityPassedCorrectly()
{
    // Test that the priority parameter is passed through correctly (i.e., all
    // StoreInts are written in correct order of priority).
    iPowerManager->PowerDown();

    // test the time writers were called in expected order of priority
    // order should now be kKey3->kKey1->kKey2
    TUint time1 = SuiteStoreInt::IntFromStore(*iStore, kKey3);
    TUint time2 = SuiteStoreInt::IntFromStore(*iStore, kKey1);
    TUint time3 = SuiteStoreInt::IntFromStore(*iStore, kKey2);
    Log::Print("TestPriorityPassedCorrectly times (ms): %u | %u | %u\n", time1, time2, time3);
    TEST(time1 < time2);
    TEST(time2 < time3);
}



void TestPowerManager(Environment& aEnv)
{
    Runner runner("PowerManager tests\n");
    runner.Add(new SuitePowerManager(aEnv));
    runner.Add(new SuiteStoreInt());
    runner.Add(new SuiteStoreIntOrdering(aEnv));
    runner.Run();
}
