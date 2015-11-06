#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/Tests/ConfigRamStore.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Thread.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Configuration;

namespace OpenHome {

class HelperPowerHandler : public IPowerHandler, public INonCopyable
{
public:
    HelperPowerHandler(Environment& aEnv);
public:
    TUint64 Time() const;
    TUint PowerUpCount() const;
public: // from IPowerHandler
    void PowerUp();
    void PowerDown();
private:
    static const TUint kSleepTime = 1; // sleep time during callbacks to artificially increase env time
    Environment& iEnv;
    TUint64 iTime;
    TUint iPowerUpCount;
};

class HelperStandbyHandler : public IStandbyHandler
{
public:
    HelperStandbyHandler();
    TBool Standby() const;
    TUint EnableCount() const;
    TUint DisableCount() const;
    StandbyDisableReason DisableReason() const;
private: // from IStandbyHandler
    void StandbyEnabled() override;
    void StandbyDisabled(StandbyDisableReason aReason) override;
private:
    TBool iStandby;
    TUint iEnableCount;
    TUint iDisableCount;
    StandbyDisableReason iDisableReason;
};

class ConfigStartupStandby : public IConfigInitialiser, private IStoreReadWrite
{
public:
    ConfigStartupStandby();
private: // from IConfigInitialiser
    IStoreReadWrite& Store() override;
    void Open() override;
    void Add(ConfigNum& aNum) override;
    void Add(ConfigChoice& aChoice) override;
    void Add(ConfigText& aText) override;
    void FromStore(const Brx& aKey, Bwx& aDest, const Brx& aDefault) override;
    void ToStore(const Brx& aKey, const Brx& aValue) override;
private: // from IStoreReadWrite
    void Read(const Brx& aKey, Bwx& aDest) override;
    void Write(const Brx& aKey, const Brx& aSource) override;
    void Delete(const Brx& aKey) override;
private:
    TUint iNumChoice;
};


class SuitePowerManager : public SuiteUnitTest, public INonCopyable
{
public:
    SuitePowerManager(Environment& aEnv);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
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
    void TestPowerUpCalled();
    void TestPowerDownNotCalledTwice();
    void TestPowerDownNotCalledAfterDeregistering();
    void TestRegisterAfterPowerDown();
    void TestNoPowerDown();
    void TestShutdownCallbackOnRegistration();
    void TestShutdownToggleGeneratesCallback();
    void TestShutdownNoCallbackOnDuplicateStateSet();
private:
    Environment& iEnv;
    ConfigStartupStandby* iDummyConfigManager;
    PowerManager* iPowerManager;
    HelperPowerHandler* iHandler1;
    HelperPowerHandler* iHandler2;
    HelperPowerHandler* iHandler3;
};

class SuiteStoreVal : public SuiteUnitTest
{
protected:
    SuiteStoreVal(const TChar* aName);
protected: // from SuiteUnitTest
    void Setup();
    void TearDown();
protected:
    static const TUint kPowerPriority = kPowerPriorityNormal;
    static const Brn kKey;
    ConfigRamStore* iStore;
    ConfigStartupStandby* iDummyConfigManager;
    PowerManager* iPowerManager;
};

class SuiteStoreValOrdering : public SuiteUnitTest, private INonCopyable
{
protected:
    SuiteStoreValOrdering(const TChar* aName, Environment& aEnv);
protected: // from SuiteUnitTest
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
protected:
    static const Brn kKey1;
    static const Brn kKey2;
    static const Brn kKey3;
    OrderingRamStore* iStore;
    ConfigStartupStandby* iDummyConfigManager;
    PowerManager* iPowerManager;
private:
    Environment& iEnv;
};

class SuiteStoreInt : public SuiteStoreVal
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
    void TestNormalShutdown();
private:
    static const TInt kDefault = 1;
    StoreInt* iStoreInt;
};

class SuiteStoreIntOrdering : public SuiteStoreValOrdering
{
public:
    SuiteStoreIntOrdering(Environment& aEnv);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    static const TInt kDefault = 50;
    StoreInt* iStoreInt1;
    StoreInt* iStoreInt2;
    StoreInt* iStoreInt3;
};

class SuiteStoreText : public SuiteStoreVal
{
public:
    SuiteStoreText();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestValueFromStore();
    void TestValueWrittenToStore();
    void TestGet();
    void TestSet();
    void TestWrite();
    void TestNormalShutdown();
private:
    static const TUint kMaxLength = 30;
    static const Brn kDefault;
    StoreText* iStoreText;
};

class SuiteStoreTextOrdering : public SuiteStoreValOrdering
{
public:
    SuiteStoreTextOrdering(Environment& aEnv);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    static const TUint kMaxLength = 30;
    static const Brn kDefault1;
    static const Brn kDefault2;
    static const Brn kDefault3;
    StoreText* iStoreText1;
    StoreText* iStoreText2;
    StoreText* iStoreText3;
};

} // namespace OpenHome



// HelperPowerHandler

HelperPowerHandler::HelperPowerHandler(Environment& aEnv)
    : iEnv(aEnv)
    , iTime(0)
    , iPowerUpCount(0)
{
}

TUint64 HelperPowerHandler::Time() const
{
    return iTime;
}

TUint HelperPowerHandler::PowerUpCount() const
{
    return iPowerUpCount;
}

void HelperPowerHandler::PowerUp()
{
    iPowerUpCount++;
}

void HelperPowerHandler::PowerDown()
{
    iTime = Os::TimeInUs(iEnv.OsCtx());
    Thread::Sleep(kSleepTime);
}


// HelperStandbyHandler

HelperStandbyHandler::HelperStandbyHandler()
    : iEnableCount(0)
    , iDisableCount(0)
{
}

TBool HelperStandbyHandler::Standby() const
{
    ASSERT(iDisableCount > 0 || iEnableCount > 0);
    return iStandby;
}

TUint HelperStandbyHandler::EnableCount() const
{
    return iEnableCount;
}

TUint HelperStandbyHandler::DisableCount() const
{
    return iDisableCount;
}

StandbyDisableReason HelperStandbyHandler::DisableReason() const
{
    ASSERT(iDisableCount > 0);
    return iDisableReason;
}

void HelperStandbyHandler::StandbyEnabled()
{
    iStandby = true;
    iEnableCount++;
}

void HelperStandbyHandler::StandbyDisabled(StandbyDisableReason aReason)
{
    iStandby = false;
    iDisableCount++;
    iDisableReason = aReason;
}


// ConfigStartupStandby

ConfigStartupStandby::ConfigStartupStandby()
    : iNumChoice(0)
{
}

IStoreReadWrite& ConfigStartupStandby::Store()
{
    ASSERTS();
    return *this;
}

void ConfigStartupStandby::Open()
{
}

void ConfigStartupStandby::Add(ConfigNum& /*aNum*/)
{
    ASSERTS();
}

void ConfigStartupStandby::Add(ConfigChoice& /*aChoice*/)
{
    ASSERT(++iNumChoice == 1);
}

void ConfigStartupStandby::Add(ConfigText& /*aText*/)
{
    ASSERTS();
}

void ConfigStartupStandby::FromStore(const Brx& /*aKey*/, Bwx& aDest, const Brx& aDefault)
{
    aDest.Replace(aDefault);
}

void ConfigStartupStandby::ToStore(const Brx& /*aKey*/, const Brx& /*aValue*/)
{
}

void ConfigStartupStandby::Read(const Brx& /*aKey*/, Bwx& /*aDest*/)
{
    ASSERTS();
}

void ConfigStartupStandby::Write(const Brx& /*aKey*/, const Brx& /*aSource*/)
{
    ASSERTS();
}

void ConfigStartupStandby::Delete(const Brx& /*aKey*/)
{
    ASSERTS();
}


// SuitePowerManager

SuitePowerManager::SuitePowerManager(Environment& aEnv)
    : SuiteUnitTest("SuitePowerManager")
    , iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPowerDownNothingRegistered), "TestPowerDownNothingRegistered");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPriorityLowest), "TestPriorityLowest");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPriorityHighest), "TestPriorityHighest");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPriorityTooHigh), "TestPriorityTooHigh");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPriorityNormal), "TestPriorityNormal");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestMultipleFunctorsAddedInOrder), "TestMultipleFunctorsAddedInOrder");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestMultipleFunctorsAddedInReverseOrder), "TestMultipleFunctorsAddedInReverseOrder");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestMultipleFunctorsAddedOutOfOrder), "TestMultipleFunctorsAddedOutOfOrder");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestMultipleFunctorsSamePriority), "TestMultipleFunctorsSamePriority");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPowerDownTwice), "TestPowerDownTwice");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPowerUpCalled), "TestPowerUpCalled");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPowerDownNotCalledTwice), "TestPowerDownNotCalledTwice");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestPowerDownNotCalledAfterDeregistering), "TestPowerDownNotCalledAfterDeregistering");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestRegisterAfterPowerDown), "TestRegisterAfterPowerDown");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestNoPowerDown), "TestNoPowerDown");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestShutdownCallbackOnRegistration), "TestShutdownCallbackOnRegistration");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestShutdownToggleGeneratesCallback), "TestShutdownToggleGeneratesCallback");
    AddTest(MakeFunctor(*this, &SuitePowerManager::TestShutdownNoCallbackOnDuplicateStateSet), "TestShutdownNoCallbackOnDuplicateStateSet");
}

void SuitePowerManager::Setup()
{
    iDummyConfigManager = new ConfigStartupStandby();
    iPowerManager = new PowerManager(*iDummyConfigManager);
    iHandler1 = new HelperPowerHandler(iEnv);
    iHandler2 = new HelperPowerHandler(iEnv);
    iHandler3 = new HelperPowerHandler(iEnv);
}

void SuitePowerManager::TearDown()
{
    delete iHandler3;
    delete iHandler2;
    delete iHandler1;
    delete iPowerManager;
    delete iDummyConfigManager;
}

void SuitePowerManager::TestPowerDownNothingRegistered()
{
    // Successful completion of this test suggests nothing nasty will happen
    // when PowerDown() is called with no callback functors registered.
    iPowerManager->NotifyPowerDown();
}

void SuitePowerManager::TestPriorityLowest()
{
    // Test that a functor with the lowest priority can be registered and called.
    IPowerManagerObserver* observer = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityLowest);
    TEST(iHandler1->PowerUpCount() == 1);
    iPowerManager->NotifyPowerDown();
    TEST(iHandler1->Time() != 0);
    delete observer;
}

void SuitePowerManager::TestPriorityHighest()
{
    // Test that a functor with the highest priority can be registered and called.
    IPowerManagerObserver* observer = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityHighest);
    iPowerManager->NotifyPowerDown();
    TEST(iHandler1->Time() != 0);
    delete observer;
}

void SuitePowerManager::TestPriorityTooHigh()
{
    // Test that PowerManager asserts when a functor with too high a priority
    // is registered.
    TEST_THROWS(iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityHighest+1), AssertionFailed);
}

void SuitePowerManager::TestPriorityNormal()
{
    // Test that a functor with a normal priority can be registered and called.
    IPowerManagerObserver* observer = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityNormal);
    iPowerManager->NotifyPowerDown();
    TEST(iHandler1->Time() != 0);
    delete observer;
}

void SuitePowerManager::TestMultipleFunctorsAddedInOrder()
{
    // Add multiple functors, in order of calling priority, and check they are
    // called in order.
    IPowerManagerObserver* observer1 = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityHighest);
    IPowerManagerObserver* observer2 = iPowerManager->RegisterPowerHandler(*iHandler2, kPowerPriorityNormal);
    IPowerManagerObserver* observer3 = iPowerManager->RegisterPowerHandler(*iHandler3, kPowerPriorityLowest);
    iPowerManager->NotifyPowerDown();
    Log::Print("TestMultipleFunctorsAddedInOrder iTimes (us): %llu | %llu | %llu\n", iHandler1->Time(), iHandler2->Time(), iHandler3->Time());
    TEST((iHandler1->Time() > 0) && (iHandler2->Time() > 0) && (iHandler3->Time() > 0));
    TEST(iHandler1->Time() < iHandler2->Time());
    TEST(iHandler2->Time() < iHandler3->Time());
    delete observer1;
    delete observer2;
    delete observer3;
}

void SuitePowerManager::TestMultipleFunctorsAddedInReverseOrder()
{
    // Add multiple functors, in reverse order of calling priority, and check
    // they are called in order.
    IPowerManagerObserver* observer1 = iPowerManager->RegisterPowerHandler(*iHandler3, kPowerPriorityLowest);
    IPowerManagerObserver* observer2 = iPowerManager->RegisterPowerHandler(*iHandler2, kPowerPriorityNormal);
    IPowerManagerObserver* observer3 = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityHighest);
    iPowerManager->NotifyPowerDown();
    Log::Print("TestMultipleFunctorsAddedInReverseOrder iTimes (us): %llu | %llu | %llu\n",
               iHandler1->Time(), iHandler2->Time(), iHandler3->Time());
    TEST((iHandler1->Time() > 0) && (iHandler2->Time() > 0) && (iHandler3->Time() > 0));
    TEST(iHandler1->Time() < iHandler2->Time());
    TEST(iHandler2->Time() < iHandler3->Time());
    delete observer1;
    delete observer2;
    delete observer3;
}

void SuitePowerManager::TestMultipleFunctorsAddedOutOfOrder()
{
    // Add multiple functors, in a non-linear order of calling, and check they
    // are called in order.
    IPowerManagerObserver* observer1 = iPowerManager->RegisterPowerHandler(*iHandler2, kPowerPriorityNormal);
    IPowerManagerObserver* observer2 = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityHighest);
    IPowerManagerObserver* observer3 = iPowerManager->RegisterPowerHandler(*iHandler3, kPowerPriorityLowest);
    iPowerManager->NotifyPowerDown();
    Log::Print("TestMultipleFunctorsAddedOutOfOrder iTimes (us): %llu | %llu | %llu\n",
               iHandler1->Time(), iHandler2->Time(), iHandler3->Time());
    TEST((iHandler1->Time() > 0) && (iHandler2->Time() > 0) && (iHandler3->Time() > 0));
    TEST(iHandler1->Time() < iHandler2->Time());
    TEST(iHandler2->Time() < iHandler3->Time());
    delete observer1;
    delete observer2;
    delete observer3;
}

void SuitePowerManager::TestMultipleFunctorsSamePriority()
{
    // Add multiple functors, with some having the same priority, and check
    // that functors with the same priority are called in the order they were
    // added.
    IPowerManagerObserver* observer1 = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityHighest);
    IPowerManagerObserver* observer2 = iPowerManager->RegisterPowerHandler(*iHandler2, kPowerPriorityNormal);
    IPowerManagerObserver* observer3 = iPowerManager->RegisterPowerHandler(*iHandler3, kPowerPriorityNormal);
    iPowerManager->NotifyPowerDown();
    Log::Print("TestMultipleFunctorsSamePriority iTimes (us): %llu | %llu | %llu\n",
               iHandler1->Time(), iHandler2->Time(), iHandler3->Time());
    TEST((iHandler1->Time() > 0) && (iHandler2->Time() > 0) && (iHandler3->Time() > 0));
    TEST(iHandler1->Time() < iHandler2->Time());
    TEST(iHandler2->Time() < iHandler3->Time());
    delete observer1;
    delete observer2;
    delete observer3;
}

void SuitePowerManager::TestPowerDownTwice()
{
    // As NotifyPowerDown() should only be called once, test that subsequent calls to
    // it do nothing.
    IPowerManagerObserver* observer = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityNormal);
    iPowerManager->NotifyPowerDown();
    TEST(iHandler1->Time() > 0);

    // Call NotifyPowerDown() again. Should ASSERT this time.
    TEST_THROWS(iPowerManager->NotifyPowerDown(), AssertionFailed);
    delete observer;
}

void SuitePowerManager::TestPowerUpCalled()
{
    // Check that PowerUp() is called before a successful registration completes.
    IPowerManagerObserver* observer = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityNormal);
    TEST(iHandler1->PowerUpCount() == 1);
    iPowerManager->NotifyPowerDown();
    TEST(iHandler1->PowerUpCount() == 1);
    delete observer;
    TEST(iHandler1->PowerUpCount() == 1);
}

void SuitePowerManager::TestPowerDownNotCalledTwice()
{
    // Test that if NotifyPowerDown() is called on the PowerManager and shutdown then
    // proceeds as normal, that NotifyPowerDown() isn't called on the IPowerHandler
    // again when its observer is destroyed.
    IPowerManagerObserver* observer = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityNormal);
    iPowerManager->NotifyPowerDown();
    TUint64 time = iHandler1->Time();
    TEST(time != 0);
    delete observer;
    TEST(iHandler1->Time() == time);
}

void SuitePowerManager::TestPowerDownNotCalledAfterDeregistering()
{
    // Test that if an IPowerHandler deregisters its observer and NotifyPowerDown()
    // is subsequently called on the PowerManager, then PowerDown() is not
    // called on the IPowerHandler again.
    IPowerManagerObserver* observer = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityNormal);
    delete observer;
    TUint64 time = iHandler1->Time();
    TEST(time != 0);
    iPowerManager->NotifyPowerDown();
    TEST(iHandler1->Time() == time);
}

void SuitePowerManager::TestRegisterAfterPowerDown()
{
    // Test that attempting to register after a NotifyPowerDown() has no ill effects,
    // as that is a perfectly valid situation (i.e., PowerDown() could have been
    // called during startup).
    iPowerManager->NotifyPowerDown();
    IPowerManagerObserver* observer = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityNormal);
    TEST(iHandler1->PowerUpCount() == 0);
    delete observer;
    TEST(iHandler1->Time() == 0);
    TEST(iHandler1->PowerUpCount() == 0);
}

void SuitePowerManager::TestNoPowerDown()
{
    // Test that if PowerDown() is not called on the PowerManager, then
    // PowerDown() is called on the IPowerHandler when its observer is
    // destroyed.
    IPowerManagerObserver* observer = iPowerManager->RegisterPowerHandler(*iHandler1, kPowerPriorityNormal);
    TEST(iHandler1->Time() == 0);
    delete observer;
    TEST(iHandler1->Time() != 0);
}

void SuitePowerManager::TestShutdownCallbackOnRegistration()
{
    HelperStandbyHandler observer;
    iPowerManager->RegisterStandbyHandler(observer);
    if (observer.DisableCount() == 0) {
        TEST(observer.EnableCount() > 0);
    }
    else if (observer.EnableCount() == 0) {
        TEST(observer.DisableCount() > 0);
    }
    else {
        ASSERTS();
    }
}

void SuitePowerManager::TestShutdownToggleGeneratesCallback()
{
    HelperStandbyHandler observer;
    iPowerManager->RegisterStandbyHandler(observer);
    TEST(!observer.Standby()); // assume that PowerManager defaults to starting up out of standby

    TEST(observer.DisableCount() == 1);
    TEST(observer.EnableCount() == 0);
    iPowerManager->StandbyEnable();
    TEST(observer.DisableCount() == 1);
    TEST(observer.EnableCount() == 1);
    TEST(observer.Standby());
    iPowerManager->StandbyDisable(eStandbyDisableUser);
    TEST(observer.DisableCount() == 2);
    TEST(observer.EnableCount() == 1);
    TEST(!observer.Standby());
    TEST(observer.DisableReason() == eStandbyDisableUser);
}

void SuitePowerManager::TestShutdownNoCallbackOnDuplicateStateSet()
{
    HelperStandbyHandler observer;
    iPowerManager->RegisterStandbyHandler(observer);
    TEST(!observer.Standby()); // assume that PowerManager defaults to starting up out of standby

    TEST(observer.DisableCount() == 1);
    TEST(observer.EnableCount() == 0);
    iPowerManager->StandbyDisable(eStandbyDisableUser);
    TEST(observer.DisableCount() == 1);
    TEST(observer.EnableCount() == 0);
    TEST(!observer.Standby());
}


// SuiteStoreVal

const Brn SuiteStoreVal::kKey("store.val.key");

SuiteStoreVal::SuiteStoreVal(const TChar* aName)
    : SuiteUnitTest(aName)
{
}

void SuiteStoreVal::Setup()
{
    iStore = new ConfigRamStore();
    iDummyConfigManager = new ConfigStartupStandby();
    iPowerManager = new PowerManager(*iDummyConfigManager);
}

void SuiteStoreVal::TearDown()
{
    delete iPowerManager;
    delete iDummyConfigManager;
    delete iStore;
}


// SuiteStoreValOrdering::OrderingRamStore

SuiteStoreValOrdering::OrderingRamStore::OrderingRamStore(Environment& aEnv)
    : ConfigRamStore()
    , iEnv(aEnv)
{
}

void SuiteStoreValOrdering::OrderingRamStore::Write(const Brx& aKey, const Brx& /*aSource*/)
{
    TUint time = Os::TimeInMs(iEnv.OsCtx());
    Bws<sizeof(TInt)> buf;
    WriterBuffer writerBuf(buf);
    WriterBinary writerBin(writerBuf);
    writerBin.WriteUint32Be(time);
    ConfigRamStore::Write(aKey, buf);
    Thread::Sleep(kSleepTime);
}


// SuiteStoreValOrdering

const Brn SuiteStoreValOrdering::kKey1("store.val.key1");
const Brn SuiteStoreValOrdering::kKey2("store.val.key2");
const Brn SuiteStoreValOrdering::kKey3("store.val.key3");

SuiteStoreValOrdering::SuiteStoreValOrdering(const TChar* aName, Environment& aEnv)
    : SuiteUnitTest(aName)
    , iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuiteStoreValOrdering::TestPriorityPassedCorrectly));
}

void SuiteStoreValOrdering::Setup()
{
    iStore = new OrderingRamStore(iEnv);
    iDummyConfigManager = new ConfigStartupStandby();
    iPowerManager = new PowerManager(*iDummyConfigManager);
}

void SuiteStoreValOrdering::TearDown()
{
    delete iPowerManager;
    delete iDummyConfigManager;
    delete iStore;
}

void SuiteStoreValOrdering::TestPriorityPassedCorrectly()
{
    // Test that the priority parameter is passed through correctly (i.e., all
    // StoreVals are written in correct order of priority).
    iPowerManager->NotifyPowerDown();

    // test the time writers were called in expected order of priority
    // order should now be kKey3->kKey1->kKey2
    TUint time1 = SuiteStoreInt::IntFromStore(*iStore, kKey3);
    TUint time2 = SuiteStoreInt::IntFromStore(*iStore, kKey1);
    TUint time3 = SuiteStoreInt::IntFromStore(*iStore, kKey2);
    Log::Print("TestPriorityPassedCorrectly times (ms): %u | %u | %u\n", time1, time2, time3);
    TEST(time1 < time2);
    TEST(time2 < time3);
}


// SuiteStoreInt

SuiteStoreInt::SuiteStoreInt()
    : SuiteStoreVal("SuiteStoreInt")
{
    AddTest(MakeFunctor(*this, &SuiteStoreInt::TestValueFromStore));
    AddTest(MakeFunctor(*this, &SuiteStoreInt::TestValueWrittenToStore));
    AddTest(MakeFunctor(*this, &SuiteStoreInt::TestGet));
    AddTest(MakeFunctor(*this, &SuiteStoreInt::TestSet));
    AddTest(MakeFunctor(*this, &SuiteStoreInt::TestWrite));
    AddTest(MakeFunctor(*this, &SuiteStoreInt::TestNormalShutdown), "TestNormalShutdown");
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
    SuiteStoreVal::Setup();
    iStoreInt = new StoreInt(*iStore, *iPowerManager, kPowerPriority, kKey, kDefault);
}

void SuiteStoreInt::TearDown()
{
    delete iStoreInt;
    SuiteStoreVal::TearDown();
}

void SuiteStoreInt::TestValueFromStore()
{
    // Test an existing value in store overwrites the default value at creation.

    // add value to store
    static const Brn key("store.int.key2");
    const TInt storeVal = kDefault*2;
    Bws<sizeof(TInt)> buf;
    WriterBuffer writerBuf(buf);
    WriterBinary writerBin(writerBuf);
    writerBin.WriteUint32Be(storeVal);
    iStore->Write(key, buf);

    // create StoreInt and check it uses value from store
    StoreInt storeInt(*iStore, *iPowerManager, kPowerPriority, key, kDefault);
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
    // Test that current value is written out when NotifyPowerDown() is called.

    // give the StoreInt a new value
    static const TInt newVal = kDefault*2;
    iStoreInt->Set(newVal);

    // write out new value and check store has been updated
    iPowerManager->NotifyPowerDown();
    TEST(IntFromStore(*iStore, kKey) == newVal);
    TEST(iStoreInt->Get() == newVal);
}

void SuiteStoreInt::TestNormalShutdown()
{
    // Test that current value is written out during normal shutdown (i.e.,
    // when PowerDown() is not called).
    Brn key("normal.shutdown.key");
    StoreInt* storeInt = new StoreInt(*iStore, *iPowerManager, kPowerPriority, key, kDefault);

    // give the StoreInt a new value
    static const TInt newVal = kDefault*2;
    storeInt->Set(newVal);

    // delete StoreInt, which should write out new value, and check store has
    // been updated
    delete storeInt;
    storeInt = nullptr;
    TEST(IntFromStore(*iStore, key) == newVal);
}


// SuiteStoreIntOrdering

SuiteStoreIntOrdering::SuiteStoreIntOrdering(Environment& aEnv)
    : SuiteStoreValOrdering("SuiteStoreIntOrdering", aEnv)
{
}

void SuiteStoreIntOrdering::Setup()
{
    SuiteStoreValOrdering::Setup();
    iStoreInt1 = new StoreInt(*iStore, *iPowerManager, kPowerPriorityNormal, kKey1, kDefault);
    iStoreInt2 = new StoreInt(*iStore, *iPowerManager, kPowerPriorityLowest, kKey2, kDefault+1);
    iStoreInt3 = new StoreInt(*iStore, *iPowerManager, kPowerPriorityHighest, kKey3, kDefault+2);
}

void SuiteStoreIntOrdering::TearDown()
{
    delete iStoreInt1;
    delete iStoreInt2;
    delete iStoreInt3;
    SuiteStoreValOrdering::TearDown();
}


// SuiteStoreText

const Brn SuiteStoreText::kDefault("abcdefghijklmnopqrstuvwxyz");

SuiteStoreText::SuiteStoreText()
    : SuiteStoreVal("SuiteStoreText")
{
    AddTest(MakeFunctor(*this, &SuiteStoreText::TestValueFromStore));
    AddTest(MakeFunctor(*this, &SuiteStoreText::TestValueWrittenToStore));
    AddTest(MakeFunctor(*this, &SuiteStoreText::TestGet));
    AddTest(MakeFunctor(*this, &SuiteStoreText::TestSet));
    AddTest(MakeFunctor(*this, &SuiteStoreText::TestWrite));
    AddTest(MakeFunctor(*this, &SuiteStoreText::TestNormalShutdown), "TestNormalShutdown");
}

void SuiteStoreText::Setup()
{
    SuiteStoreVal::Setup();
    iStoreText = new StoreText(*iStore, *iPowerManager, kPowerPriority, kKey, kDefault, kMaxLength);
}

void SuiteStoreText::TearDown()
{
    delete iStoreText;
    SuiteStoreVal::TearDown();
}

void SuiteStoreText::TestValueFromStore()
{
    // Test an existing value in store overwrites the default value at creation.

    // add value to store
    static const Brn key("store.text.key2");
    Brn storeVal("zyxwvutsrqponmlkjihgfedcba");
    iStore->Write(key, storeVal);

    // create StoreText and check it uses value from store
    StoreText storeText(*iStore, *iPowerManager, kPowerPriority, key, kDefault, kMaxLength);
    Bws<kMaxLength> val;
    storeText.Get(val);
    TEST(val == storeVal);

    // check store hasn't been overwritten as a side-effect
    Bws<kMaxLength> buf;
    iStore->Read(key, buf);
    TEST(buf == storeVal);
}

void SuiteStoreText::TestValueWrittenToStore()
{
    // Test that the default value has been written out to store at creation.
    Bws<kMaxLength> buf;
    iStore->Read(kKey, buf);
    TEST(buf == kDefault);
}

void SuiteStoreText::TestGet()
{
    // Test that correct value is returned.
    Bws<kMaxLength> val;
    iStoreText->Get(val);
    TEST(val == kDefault);
}

void SuiteStoreText::TestSet()
{
    // Test that setting (and retrieving) a value results in a new value.
    Brn newVal("zyxwvutsrqponmlkjihgfedcba");
    iStoreText->Set(newVal);
    Bws<kMaxLength> val;
    iStoreText->Get(val);
    TEST(val == newVal);

    // check store hasn't been updated
    Bws<kMaxLength> buf;
    iStore->Read(kKey, buf);
    TEST(buf == kDefault);
}

void SuiteStoreText::TestWrite()
{
    // Test that current value is written out when PowerDown() is called.

    // give the StoreText a new value
    Brn newVal("zyxwvutsrqponmlkjihgfedcba");
    iStoreText->Set(newVal);

    // write out new value and check store has been updated
    iPowerManager->NotifyPowerDown();
    Bws<kMaxLength> buf;
    iStore->Read(kKey, buf);
    TEST(buf == newVal);
    Bws<kMaxLength> val;
    iStoreText->Get(val);
    TEST(val == newVal);
}

void SuiteStoreText::TestNormalShutdown()
{
    // Test that current value is written out during normal shutdown (i.e.,
    // when PowerDown() is not called).
    Brn key("normal.shutdown.key");
    StoreText* storeText = new StoreText(*iStore, *iPowerManager, kPowerPriority, key, kDefault, kMaxLength);

    // give the StoreText a new value
    Brn newVal("zyxwvutsrqponmlkjihgfedcba");
    storeText->Set(newVal);

    // delete StoreText, which should write out new value, and check store has
    // been updated
    delete storeText;
    storeText = nullptr;
    Bws<kMaxLength> buf;
    iStore->Read(key, buf);
    TEST(buf == newVal);
}


// SuiteStoreTextOrdering

const Brn SuiteStoreTextOrdering::kDefault1("abc");
const Brn SuiteStoreTextOrdering::kDefault2("def");
const Brn SuiteStoreTextOrdering::kDefault3("ghi");

SuiteStoreTextOrdering::SuiteStoreTextOrdering(Environment& aEnv)
    : SuiteStoreValOrdering("SuiteStoreTextOrdering", aEnv)
{
}

void SuiteStoreTextOrdering::Setup()
{
    SuiteStoreValOrdering::Setup();
    iStoreText1 = new StoreText(*iStore, *iPowerManager, kPowerPriorityNormal, kKey1, kDefault1, kMaxLength);
    iStoreText2 = new StoreText(*iStore, *iPowerManager, kPowerPriorityLowest, kKey2, kDefault2, kMaxLength);
    iStoreText3 = new StoreText(*iStore, *iPowerManager, kPowerPriorityHighest, kKey3, kDefault3, kMaxLength);
}

void SuiteStoreTextOrdering::TearDown()
{
    delete iStoreText1;
    delete iStoreText2;
    delete iStoreText3;
    SuiteStoreValOrdering::TearDown();
}



void TestPowerManager(Environment& aEnv)
{
    Runner runner("PowerManager tests\n");
    runner.Add(new SuitePowerManager(aEnv));
    runner.Add(new SuiteStoreInt());
    runner.Add(new SuiteStoreIntOrdering(aEnv));
    runner.Add(new SuiteStoreText());
    runner.Add(new SuiteStoreTextOrdering(aEnv));
    runner.Run();
}
