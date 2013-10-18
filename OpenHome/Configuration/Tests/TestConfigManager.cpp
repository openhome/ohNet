#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Configuration/ConfigManager.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Configuration;

namespace OpenHome {
namespace Configuration {

class SuiteCVNotify : public SuiteUnitTest
{
protected:
    SuiteCVNotify(const TChar* aName);
    virtual ~SuiteCVNotify() = 0;
protected: // from SuiteUnitTest
    void Setup();
    void TearDown();
protected:
    void NotifyChanged();
    void OwnerFunctor();
protected:
    static const Brn kKey;
    ConfigRamStore* iStore;
    ConfigurationManager* iConfigManager;
    TUint iChangedCount;
    TUint iOwnerFunctorCount;
};

class SuiteCVSubscriptions : public SuiteCVNotify
{
public:
    SuiteCVSubscriptions();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestNoSubscriptions();
    void TestAddRemoveSubscription();
    void TestAddRemoveMultipleSubscriptions();
    void TestRemoveInvalidId();
private:
    ConfigVal* iConfigVal;
};

class SuiteConfigNum : public SuiteCVNotify
{
public:
    SuiteConfigNum();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestFunctorsCalled();
    void TestInvalidRange();
    void TestValueOutOfRangeConstructor();
    void TestValueFromStore();
    void TestValueWrittenToStore();
    void TestGet();
    void TestGetMin();
    void TestGetMax();
    void TestSetUpdate(); // FIXME - test Write() here
    void TestSetNoUpdate(); // and here
    void TestSetValueOutOfRange();
private:
    static const TInt kMin = -1;
    static const TInt kMax = 2;
    static const TInt kVal = 1;
    ConfigNum* iConfigVal;
};

class SuiteConfigChoice : public SuiteCVNotify
{
public:
    SuiteConfigChoice();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestFunctorsCalled();
    void TestValueFromStore();
    void TestValueWrittenToStore();
    void TestAdd();
    void TestAddDuplicate();
    void TestGet();
    void TestGetNoOptions();
    void TestSetUpdate();
    void TestSetNoUpdate();
    void TestSetIndexOutOfRange();
private:
    static const TUint kDefault = 0;
    static const Brn kOption1;
    static const Brn kOption2;
    static const Brn kOption3;
    ConfigChoice* iConfigVal;
};

class SuiteConfigText : public SuiteCVNotify
{
public:
    SuiteConfigText();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    static const TUint kMaxLength = 100;
    static const Brn kDefault;
    void TestFunctorsCalled();
    void TestValueFromStore();
    void TestValueWrittenToStore();
    void TestMaxLength();
    void TestGet();
    void TestSetUpdate();
    void TestSetNoUpdate();
    void TestSetValueTooLong();
    ConfigText* iConfigVal;
};

class SuiteConfigurationManager : public SuiteUnitTest
{
public:
    SuiteConfigurationManager();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void OwnerFunctor();
    void TestClose();
    void TestAdd();
    void TestAddDuplicate();
    void TestHasNoVals();
    void TestHasValidId();
    void TestHasInvalidId();
    void TestHasMultiple();
    void TestGetNoVals();
    void TestGetValidId();
    void TestGetInvalidId();
    void TestGetMultiple();
private:
    static const TInt kMinNum = 0;
    static const TInt kMaxNum = 2;
    static const TUint kChoiceDefault = 0;
    static const TUint kMaxText = 26;
    static const Brn kOption1;
    static const Brn kOption2;
    static const Brn kOption3;
    static const Brn kText1;
    static const Brn kText2;
    static const Brn kIdNum1;
    static const Brn kIdNum2;
    static const Brn kIdChoice1;
    static const Brn kIdChoice2;
    static const Brn kIdText1;
    static const Brn kIdText2;
    ConfigRamStore* iStore;
    ConfigurationManager* iConfigManager;
    ConfigNum* iNum1;
    std::vector<const Brx*> iOptions;
    ConfigChoice* iChoice1;
    ConfigText* iText1;
    TUint iOwnerFunctorCount;
};

class SuiteRamStore : public SuiteUnitTest
{
public:
    SuiteRamStore();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestRead();
    void TestWrite();
    void TestDelete();
private:
    static const Brn kKey1;
    static const Brn kKey2;
    static const Brn kVal1;
    static const Brn kVal2;
    ConfigRamStore* iStore;
};

} // namespace Configuration
} // namespace OpenHome



// SuiteCVNotify

const Brn SuiteCVNotify::kKey("conf.key");

SuiteCVNotify::SuiteCVNotify(const TChar* aName)
    : SuiteUnitTest(aName)
{
}

SuiteCVNotify::~SuiteCVNotify() {}

void SuiteCVNotify::Setup()
{
    iStore = new ConfigRamStore();
    iConfigManager = new ConfigurationManager(*iStore);
    iChangedCount = 0;
    iOwnerFunctorCount = 0;
}

void SuiteCVNotify::TearDown()
{
    delete iConfigManager;
    delete iStore;
}

void SuiteCVNotify::NotifyChanged()
{
    iChangedCount++;
}

void SuiteCVNotify::OwnerFunctor()
{
    iOwnerFunctorCount++;
}


// SuiteCVSubscriptions

SuiteCVSubscriptions::SuiteCVSubscriptions()
    : SuiteCVNotify("SuiteCVSubscriptions")
{
    AddTest(MakeFunctor(*this, &SuiteCVSubscriptions::TestNoSubscriptions));
    AddTest(MakeFunctor(*this, &SuiteCVSubscriptions::TestAddRemoveSubscription));
    AddTest(MakeFunctor(*this, &SuiteCVSubscriptions::TestAddRemoveMultipleSubscriptions));
    AddTest(MakeFunctor(*this, &SuiteCVSubscriptions::TestRemoveInvalidId));
}

void SuiteCVSubscriptions::Setup()
{
    SuiteCVNotify::Setup();
    iConfigVal = new ConfigNum(*iConfigManager, kKey, MakeFunctor(*this, &SuiteCVSubscriptions::OwnerFunctor), 1, 1, 1);
}

void SuiteCVSubscriptions::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iConfigVal;
}

void SuiteCVSubscriptions::TestNoSubscriptions()
{
    // test that a ConfigVal can be successfully destructed without ever having a
    // subscription on it.
    delete iConfigVal;
    iConfigVal = NULL;
}

void SuiteCVSubscriptions::TestAddRemoveSubscription()
{
    // test adding and removing a single subscription - will assert at
    // destruction if error
    TUint id = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteCVSubscriptions::NotifyChanged));
    iConfigVal->Unsubscribe(id);
    delete iConfigVal;
    iConfigVal = NULL;
}

void SuiteCVSubscriptions::TestAddRemoveMultipleSubscriptions()
{
    // test adding and removing multiple (extra) subscriptions (and test id
    // ordering) - will assert at destruction if error
    TUint id1 = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteCVSubscriptions::NotifyChanged));
    TEST(id1 == 2);
    TUint id2 = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteCVSubscriptions::NotifyChanged));
    TEST(id2 == 3);
    iConfigVal->Unsubscribe(id1);
    iConfigVal->Unsubscribe(id2);
    delete iConfigVal;
    iConfigVal = NULL;
}

void SuiteCVSubscriptions::TestRemoveInvalidId()
{
    // test that trying to unsubscribe using an invalid id does nothing
    iConfigVal->Unsubscribe(0);
}


// SuiteConfigNum

SuiteConfigNum::SuiteConfigNum()
    : SuiteCVNotify("SuiteConfigNum")
{
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestFunctorsCalled));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestInvalidRange));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestValueOutOfRangeConstructor));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestValueFromStore));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestValueWrittenToStore));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestGet));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestGetMin));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestGetMax));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSetUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSetNoUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSetValueOutOfRange));
}

void SuiteConfigNum::Setup()
{
    SuiteCVNotify::Setup();
    iConfigVal = new ConfigNum(*iConfigManager, kKey, MakeFunctor(*this, &SuiteConfigNum::OwnerFunctor), kMin, kMax, kVal);
}

void SuiteConfigNum::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iConfigVal;
}

void SuiteConfigNum::TestFunctorsCalled()
{
    TEST(iChangedCount == 0);
    TEST(iOwnerFunctorCount == 1);

    // there is an internal write functor - check value == value in store
    Bws<sizeof(TInt)> valBuf;
    iStore->Read(kKey, valBuf);
    TInt val = Converter::BeUint32At(valBuf, 0);
    TEST(val == iConfigVal->Get());
}

void SuiteConfigNum::TestInvalidRange()
{
    // test creating a ConfigNum with max < min
    TEST_THROWS(ConfigNum cv(*iConfigManager, kKey, MakeFunctor(*this, &SuiteConfigNum::OwnerFunctor), 1, -1, 1), AvConfigInvalidRange);
}

void SuiteConfigNum::TestValueOutOfRangeConstructor()
{
    // test creating a ConfigNum with val outside range min..max
    TEST_THROWS(ConfigNum cv(*iConfigManager, kKey, MakeFunctor(*this, &SuiteConfigNum::OwnerFunctor), 0, 0, 1), AvConfigValueOutOfRange);
}

void SuiteConfigNum::TestValueFromStore()
{
    // test an existing value in store overwrites the default value at creation
    const Brn key("conf.num.2");
    const TInt storeVal = kVal+1;
    Bws<sizeof(TInt)> valBuf;
    valBuf.Append(Arch::BigEndian4(storeVal));
    iStore->Write(key, valBuf);
    ConfigNum num(*iConfigManager, key, MakeFunctor(*this, &SuiteConfigNum::OwnerFunctor), kMin, kMax, kVal);

    // test value in store hasn't been overwritten
    valBuf.SetBytes(0);
    iStore->Read(key, valBuf);
    TInt val = Converter::BeUint32At(valBuf, 0);
    TEST(val == storeVal);
    // test retrieved value is correct
    TEST(num.Get() == storeVal);
}

void SuiteConfigNum::TestValueWrittenToStore()
{
    // test that the default value has been written out to store at creation
    Bws<sizeof(TInt)> valBuf;
    iStore->Read(kKey, valBuf);
    TInt storeVal = Converter::BeUint32At(valBuf, 0);
    TEST(storeVal == kVal);
}

void SuiteConfigNum::TestGet()
{
    // test the correct value of the ConfigNum is returned
    TInt val = iConfigVal->Get();
    TEST(val == kVal);
}

void SuiteConfigNum::TestGetMin()
{
    // test the correct value for min is returned
    TInt min = iConfigVal->Min();
    TEST(min == kMin);
}

void SuiteConfigNum::TestGetMax()
{
    // test the correct value for max is returned
    TInt max = iConfigVal->Max();
    TEST(max == kMax);
}

void SuiteConfigNum::TestSetUpdate()
{
    // test that calling set with a new value updates the value of the ConfigNum
    // (and that any observers are notified)
    TUint changedCount = iChangedCount;
    TUint id = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteConfigNum::NotifyChanged));
    TBool updated = iConfigVal->Set(kVal+1);

    TEST(updated == true);
    TEST(iChangedCount == changedCount+1);

    TInt val = iConfigVal->Get();
    TEST(val == kVal+1);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigNum::TestSetNoUpdate()
{
    // test that calling set with the existing value of ConfigNum causing no change
    // to the ConfigNum, and that no observers are notified
    TUint changedCount = iChangedCount;
    TUint id = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteConfigNum::NotifyChanged));
    TBool updated = iConfigVal->Set(iConfigVal->Get());

    TEST(updated == false);
    TEST(iChangedCount == changedCount);

    TInt val = iConfigVal->Get();
    TEST(val == kVal);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigNum::TestSetValueOutOfRange()
{
    // test attempting to set ConfigNum's value outwith the range min..max
    TInt valBefore = iConfigVal->Get();
    TEST_THROWS(iConfigVal->Set(kMax+1), AvConfigValueOutOfRange);
    TInt valAfter = iConfigVal->Get();
    TEST(valAfter == valBefore);

    valBefore = iConfigVal->Get();
    TEST_THROWS(iConfigVal->Set(kMin-1), AvConfigValueOutOfRange);
    valAfter = iConfigVal->Get();
    TEST(valAfter == valBefore);
}


// SuiteConfigChoice

const Brn SuiteConfigChoice::kOption1("Option1");
const Brn SuiteConfigChoice::kOption2("Option2");
const Brn SuiteConfigChoice::kOption3("Option3");

SuiteConfigChoice::SuiteConfigChoice()
    : SuiteCVNotify("SuiteConfigChoice")
{
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestFunctorsCalled));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestValueFromStore));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestValueWrittenToStore));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestAdd));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestAddDuplicate));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestGet));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestGetNoOptions));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSetUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSetNoUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSetIndexOutOfRange));
}

void SuiteConfigChoice::Setup()
{
    SuiteCVNotify::Setup();
    std::vector<const Brx*> options;
    options.push_back(&kOption1);
    options.push_back(&kOption2);
    options.push_back(&kOption3);
    iConfigVal = new ConfigChoice(*iConfigManager, kKey, MakeFunctor(*this, &SuiteConfigChoice::OwnerFunctor), options, kDefault);
}

void SuiteConfigChoice::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iConfigVal;
}

void SuiteConfigChoice::TestFunctorsCalled()
{
    TEST(iChangedCount == 0);
    TEST(iOwnerFunctorCount == 1);

    // there is an internal write functor - check value == value in store
    Bws<sizeof(TUint)> valBuf;
    iStore->Read(kKey, valBuf);
    TUint val = Converter::BeUint32At(valBuf, 0);
    TEST(val == iConfigVal->Get());
}

void SuiteConfigChoice::TestValueFromStore()
{
    // test an existing value in store overwrites the default value at creation
    const Brn key("conf.choice.2");
    const TInt storeVal = kDefault+1;
    Bws<sizeof(TUint)> valBuf;
    valBuf.Append(Arch::BigEndian4(storeVal));
    iStore->Write(key, valBuf);

    std::vector<const Brx*> options;
    options.push_back(&kOption1);
    options.push_back(&kOption2);
    options.push_back(&kOption3);
    ConfigChoice choice(*iConfigManager, key, MakeFunctor(*this, &SuiteConfigChoice::OwnerFunctor), options, kDefault);

    // test value in store hasn't been overwritten
    valBuf.SetBytes(0);
    iStore->Read(key, valBuf);
    TUint val = Converter::BeUint32At(valBuf, 0);
    TEST(val == storeVal);
    // test retrieved value is correct
    TEST(choice.Get() == storeVal);
}

void SuiteConfigChoice::TestValueWrittenToStore()
{
    // test that the default value has been written out to store at creation
    Bws<sizeof(TInt)> valBuf;
    iStore->Read(kKey, valBuf);
    TInt storeVal = Converter::BeUint32At(valBuf, 0);
    TEST(storeVal == kDefault);
}

void SuiteConfigChoice::TestAdd()
{
    // test that after options are added to a ConfigChoice, they are available when
    // Options() is called
    std::vector<const Brx*> options = iConfigVal->Options();

    TEST(options.size() == 3);
    TEST(*options[0] == kOption1);
    TEST(*options[1] == kOption2);
    TEST(*options[2] == kOption3);
}

void SuiteConfigChoice::TestAddDuplicate()
{
    // test that creating a ConfigChoice with a duplicate option fails
    std::vector<const Brx*> options;
    options.push_back(&kOption1);
    options.push_back(&kOption1);
    TEST_THROWS(ConfigChoice cv(*iConfigManager, kKey, MakeFunctor(*this, &SuiteConfigChoice::OwnerFunctor), options, kDefault);, AvConfigValueExists);
}

void SuiteConfigChoice::TestGet()
{
    // test that adding some options and then calling Get() (without a prior
    // Set()) returns the first option
    TUint selected = iConfigVal->Get();
    TEST(selected == kDefault); // the first option should be the default
}

void SuiteConfigChoice::TestGetNoOptions()
{
    // test that creating without any options causes an assert
    std::vector<const Brx*> options;
    TEST_THROWS(ConfigChoice cv(*iConfigManager, kKey, MakeFunctor(*this, &SuiteConfigChoice::OwnerFunctor), options, kDefault), AssertionFailed);
}

void SuiteConfigChoice::TestSetUpdate()
{
    // test that changing the selected value causes ConfigChoice to be updated (and
    // any observers notified)
    TUint changedCount = iChangedCount;
    TUint id = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteConfigChoice::NotifyChanged));
    TBool updated = iConfigVal->Set(1);

    TEST(updated == true);
    TEST(iChangedCount == changedCount+1);

    TUint selected = iConfigVal->Get();
    TEST(selected == 1);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigChoice::TestSetNoUpdate()
{
    // test that setting the same option index results in no change to ConfigChoice
    // (and observers aren't notified)
    TUint changedCount = iChangedCount;
    TUint id = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteConfigChoice::NotifyChanged));
    TBool updated = iConfigVal->Set(0);

    TEST(updated == false);
    TEST(iChangedCount == changedCount);

    TUint selected = iConfigVal->Get();
    TEST(selected == 0);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigChoice::TestSetIndexOutOfRange()
{
    // test that attempting to set ConfigChoice to an invalid option index results
    // in an exception
    TUint selectedBefore = iConfigVal->Get();
    TEST_THROWS(iConfigVal->Set(3), AvConfigIndexOutOfRange);
    TUint selectedAfter = iConfigVal->Get();
    TEST(selectedAfter == selectedBefore);
}


// SuiteConfigText

const Brn SuiteConfigText::kDefault("abcdefghijklmnopqrstuvwxyz");

SuiteConfigText::SuiteConfigText()
    : SuiteCVNotify("SuiteConfigText")
{
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestFunctorsCalled));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestValueFromStore));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestValueWrittenToStore));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestMaxLength));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestGet));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetNoUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetValueTooLong));
}

void SuiteConfigText::Setup()
{
    SuiteCVNotify::Setup();
    iConfigVal = new ConfigText(*iConfigManager, kKey, MakeFunctor(*this, &SuiteConfigText::OwnerFunctor), kMaxLength, kDefault);
}

void SuiteConfigText::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iConfigVal;
}

void SuiteConfigText::TestFunctorsCalled()
{
    TEST(iChangedCount == 0);
    TEST(iOwnerFunctorCount == 1);

    // there is an internal write functor - check value == value in store
    Bwh valBuf(kMaxLength);
    iStore->Read(kKey, valBuf);
    TEST(valBuf == iConfigVal->Get());
}

void SuiteConfigText::TestValueFromStore()
{
    // test an existing value in store overwrites the default value at creation
    const Brn key("conf.text.2");
    Brn storeVal("zyxwvutsrqponmlkjihgfedcba");
    iStore->Write(key, storeVal);
    ConfigText text(*iConfigManager, key, MakeFunctor(*this, &SuiteConfigText::OwnerFunctor), kMaxLength, kDefault);

    // test value in store hasn't been overwritten
    Bwh valBuf(kMaxLength);
    iStore->Read(key, valBuf);
    TEST(valBuf == storeVal);
    // test retrieved value is correct
    TEST(text.Get() == storeVal);
}

void SuiteConfigText::TestValueWrittenToStore()
{
    // test that the default value has been written out to store at creation
    Bwh valBuf(kDefault.Bytes());
    iStore->Read(kKey, valBuf);
    TEST(valBuf == kDefault);
}

void SuiteConfigText::TestMaxLength()
{
    // test that the max possible length of the text buf matches init params
    TEST(iConfigVal->MaxLength() == kMaxLength);
}

void SuiteConfigText::TestGet()
{
    // test that calling Get() on a value set as default results in correct
    // value being returned
    const Brx& buf = iConfigVal->Get();
    TEST(buf == kDefault);
}

void SuiteConfigText::TestSetUpdate()
{
    // test that updating ConfigText with a new value results in ConfigText
    // being changed and any observers notified
    TUint changedCount = iChangedCount;
    Brn text("zyxwvutsrqponmlkjihgfedcba");
    TUint id = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteConfigText::NotifyChanged));
    TBool updated = iConfigVal->Set(text);

    TEST(updated == true);
    TEST(iChangedCount == changedCount+1);

    const Brx& buf = iConfigVal->Get();
    TEST(buf == text);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigText::TestSetNoUpdate()
{
    // test that updating ConfigText with the same value results in no change to
    // ConfigText and no observers being notified
    TUint changedCount = iChangedCount;

    // test updating the empty string, then test updating a string with
    // length > 0
    TUint id = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteConfigText::NotifyChanged));
    TBool updated = iConfigVal->Set(kDefault);
    TEST(updated == false);
    TEST(iChangedCount == changedCount);
    const Brx& buf1 = iConfigVal->Get();
    TEST(buf1 == kDefault);
    iConfigVal->Unsubscribe(id);

    Brn text("zyxwvutsrqponmlkjihgfedcba");
    updated = iConfigVal->Set(text);
    id = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteConfigText::NotifyChanged));
    updated = iConfigVal->Set(text);
    TEST(updated == false);
    TEST(iChangedCount == changedCount);
    const Brx& buf2 = iConfigVal->Get();
    TEST(buf2 == text);
    iConfigVal->Unsubscribe(id);
}

void SuiteConfigText::TestSetValueTooLong()
{
    // test that attempting to set ConfigText to a value with length > maxbytes
    // causes an exception to be thrown
    Bws<kMaxLength+1> buf;
    buf.SetBytes(buf.MaxBytes());

    const Brx& bufBefore = iConfigVal->Get();
    TEST_THROWS(iConfigVal->Set(buf), AvConfigValueTooLong);
    const Brx& bufAfter = iConfigVal->Get();
    TEST(bufAfter == bufBefore);
}


// SuiteConfigurationManager

/*
 * Note: SerialisedMap is not tested, as ConfigManager is such a thin wrapper
 * around it that all the test cases present here would just be duplicated.
 * These tests essentially test SerialisedMap anyway; just proxied through
 * ConfigManager.
 */

const Brn SuiteConfigurationManager::kOption1("Option1");
const Brn SuiteConfigurationManager::kOption2("Option2");
const Brn SuiteConfigurationManager::kOption3("Option3");
const Brn SuiteConfigurationManager::kText1("abcdefghijklmnopqrstuvwxyz");
const Brn SuiteConfigurationManager::kText2("zyxwvutsrqponmlkjihgfedcba");
const Brn SuiteConfigurationManager::kIdNum1("cv.num.1");
const Brn SuiteConfigurationManager::kIdNum2("cv.num.2");
const Brn SuiteConfigurationManager::kIdChoice1("cv.choice.1");
const Brn SuiteConfigurationManager::kIdChoice2("cv.choice.2");
const Brn SuiteConfigurationManager::kIdText1("cv.text.1");
const Brn SuiteConfigurationManager::kIdText2("cv.text.2");

SuiteConfigurationManager::SuiteConfigurationManager()
    : SuiteUnitTest("SuiteConfigurationManager")
{
    // Creating different instances of SuiteConfigurationManager for each of
    // ConfigNum, ConfigChoice and ConfigText would end up in a lot of boilerplate code.
    // Just group functions for each val class in a single generic unit test
    // for each type of ConfigurationManager function to maintain clarity and
    // small test size.
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigurationManager::TestClose));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigurationManager::TestAdd));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigurationManager::TestAddDuplicate));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigurationManager::TestHasNoVals));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigurationManager::TestHasValidId));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigurationManager::TestHasInvalidId));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigurationManager::TestHasMultiple));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigurationManager::TestGetNoVals));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigurationManager::TestGetValidId));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigurationManager::TestGetInvalidId));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigurationManager::TestGetMultiple));
}

void SuiteConfigurationManager::Setup()
{
    iStore = new ConfigRamStore();
    iConfigManager = new ConfigurationManager(*iStore);
    iNum1 = new ConfigNum(*iConfigManager, kIdNum1, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), kMinNum, kMaxNum, kMinNum);
    iOptions.push_back(&kOption1);
    iOptions.push_back(&kOption2);
    iOptions.push_back(&kOption3);
    iChoice1 = new ConfigChoice(*iConfigManager, kIdChoice1, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), iOptions, kChoiceDefault);
    iText1 = new ConfigText(*iConfigManager, kIdText1, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), kMaxText, kText1);
}

void SuiteConfigurationManager::TearDown()
{
    delete iNum1;
    delete iChoice1;
    delete iText1;
    delete iConfigManager;
    delete iStore;
    iOptions.clear();
}

void SuiteConfigurationManager::OwnerFunctor()
{
    iOwnerFunctorCount++;
}

void SuiteConfigurationManager::TestClose()
{
    // test that ConfigurationManager ASSERTs when attempting to add a value
    // after it has been closed
    iConfigManager->Close();
    TEST_THROWS(ConfigNum num(*iConfigManager, kIdNum2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), kMinNum, kMaxNum, kMinNum+1), AssertionFailed);
    TEST_THROWS(ConfigChoice choice(*iConfigManager, kIdChoice2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), iOptions, kChoiceDefault+1), AssertionFailed);
    TEST_THROWS(ConfigText text(*iConfigManager, kIdText2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), kMaxText, kText2), AssertionFailed);
}

void SuiteConfigurationManager::TestAdd()
{
    // completion of this test without errors suggests adding works
    // Has() and Get() are tested in their own unit tests.
    ConfigNum num(*iConfigManager, kIdNum2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), kMinNum, kMaxNum, kMinNum+1);
    ConfigChoice choice(*iConfigManager, kIdChoice2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), iOptions, kChoiceDefault+1);
    ConfigText text(*iConfigManager, kIdText2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), kMaxText, kText2);
}

void SuiteConfigurationManager::TestAddDuplicate()
{
    // test that an exception is throws if an attempt to add a ConfigVal with
    // the same ID is made twice
    TEST_THROWS(iConfigManager->Add(*iNum1), AvConfigIdExists);
    TEST_THROWS(iConfigManager->Add(*iChoice1), AvConfigIdExists);
    TEST_THROWS(iConfigManager->Add(*iText1), AvConfigIdExists);

    // attempt to add a ConfigChoice with same ID as existing ConfigNum - should fail
    TEST_THROWS(iConfigManager->Add(*iChoice1), AvConfigIdExists);
}

void SuiteConfigurationManager::TestHasNoVals()
{
    // test that calling Has() when no values are added returns false
    ConfigRamStore store;
    ConfigurationManager configManager(store);
    TEST(configManager.HasNum(kIdNum1) == false);
    TEST(configManager.HasChoice(kIdChoice1) == false);
    TEST(configManager.HasText(kIdText1) == false);
    TEST(configManager.Has(kIdNum1) == false);
    TEST(configManager.Has(kIdChoice1) == false);
    TEST(configManager.Has(kIdText1) == false);
}

void SuiteConfigurationManager::TestHasValidId()
{
    // test Has() returns true when a given ID exists
    TEST(iConfigManager->HasNum(kIdNum1) == true);
    TEST(iConfigManager->HasChoice(kIdChoice1) == true);
    TEST(iConfigManager->HasText(kIdText1) == true);

    // test generic Has()
    TEST(iConfigManager->Has(kIdNum1) == true);
    TEST(iConfigManager->Has(kIdChoice1) == true);
    TEST(iConfigManager->Has(kIdText1) == true);
}

void SuiteConfigurationManager::TestHasInvalidId()
{
    // test Has() returns false when IDs are present, but not the given ID

    // test ConfigNum
    TEST(iConfigManager->HasNum(kIdNum2) == false);

    // test ConfigChoice
    TEST(iConfigManager->HasChoice(kIdChoice2) == false);

    // test ConfigText
    TEST(iConfigManager->HasText(kIdText2) == false);

    // try call HasChoice() with the ID of ConfigNum
    TEST(iConfigManager->HasChoice(kIdNum1) == false);

    // test generic Has()
    TEST(iConfigManager->Has(kIdNum2) == false);
    TEST(iConfigManager->Has(kIdChoice2) == false);
    TEST(iConfigManager->Has(kIdText2) == false);
}

void SuiteConfigurationManager::TestHasMultiple()
{
    // test adding multiple values and calling Has() on the IDs

    // test ConfigNum
    ConfigNum num(*iConfigManager, kIdNum2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), kMinNum, kMaxNum, kMinNum+1);
    TEST(iConfigManager->HasNum(kIdNum1) == true);
    TEST(iConfigManager->HasNum(kIdNum2) == true);

    // test ConfigChoice
    ConfigChoice choice(*iConfigManager, kIdChoice2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), iOptions, kChoiceDefault+1);
    TEST(iConfigManager->HasChoice(kIdChoice1) == true);
    TEST(iConfigManager->HasChoice(kIdChoice2) == true);

    // test ConfigText
    ConfigText text(*iConfigManager, kIdText2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), kMaxText, kText2);
    TEST(iConfigManager->HasText(kIdText1) == true);
    TEST(iConfigManager->HasText(kIdText2) == true);
}

void SuiteConfigurationManager::TestGetNoVals()
{
    // test that Get() fails with an assertion when no values are present
    ConfigRamStore store;
    ConfigurationManager configManager(store);
    TEST_THROWS(configManager.GetNum(kIdNum1), AssertionFailed);
    TEST_THROWS(configManager.GetChoice(kIdChoice1), AssertionFailed);
    TEST_THROWS(configManager.GetText(kIdText1), AssertionFailed);
    TEST_THROWS(configManager.Get(kIdNum1), AssertionFailed);
    TEST_THROWS(configManager.Get(kIdChoice1), AssertionFailed);
    TEST_THROWS(configManager.Get(kIdText1), AssertionFailed);
}

void SuiteConfigurationManager::TestGetValidId()
{
    // test Get() returns the correct val when ID is present

    // test ConfigNum
    ConfigNum& num = iConfigManager->GetNum(kIdNum1);
    TEST(num == *iNum1);

    // test ConfigChoice
    ConfigChoice& choice = iConfigManager->GetChoice(kIdChoice1);
    TEST(choice == *iChoice1);

    // test ConfigText
    ConfigText& text = iConfigManager->GetText(kIdText1);
    TEST(text == *iText1);

    // test generic Get()
    ConfigVal& valNum = iConfigManager->Get(kIdNum1);
    TEST(dynamic_cast<ConfigNum&>(valNum) == *iNum1);
    ConfigVal& valChoice = iConfigManager->Get(kIdChoice1);
    TEST(dynamic_cast<ConfigChoice&>(valChoice) == *iChoice1);
    ConfigVal& valText = iConfigManager->Get(kIdText1);
    TEST(dynamic_cast<ConfigText&>(valText) == *iText1);
}

void SuiteConfigurationManager::TestGetInvalidId()
{
    // test that Get() causes an assertion when ID is not present
    TEST_THROWS(iConfigManager->GetNum(kIdNum2), AssertionFailed);
    TEST_THROWS(iConfigManager->GetChoice(kIdChoice2), AssertionFailed);
    TEST_THROWS(iConfigManager->GetText(kIdText2), AssertionFailed);

    // try call HasChoice() with the ID of ConfigNum
    TEST_THROWS(iConfigManager->GetChoice(kIdNum1), AssertionFailed);

    // test generic Get()
    TEST_THROWS(iConfigManager->Get(kIdNum2), AssertionFailed);
    TEST_THROWS(iConfigManager->Get(kIdChoice2), AssertionFailed);
    TEST_THROWS(iConfigManager->Get(kIdText2), AssertionFailed);
}

void SuiteConfigurationManager::TestGetMultiple()
{
    // test adding multiple values and calling Get() on the IDs

    // test ConfigNum
    ConfigNum num(*iConfigManager, kIdNum2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), kMinNum, kMaxNum, kMinNum+1);
    ConfigNum& num1 = iConfigManager->GetNum(kIdNum1);
    TEST(num1 == *iNum1);
    ConfigNum& num2 = iConfigManager->GetNum(kIdNum2);
    TEST(num2 == num);

    // test ConfigChoice
    ConfigChoice choice(*iConfigManager, kIdChoice2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), iOptions, kChoiceDefault+1);
    ConfigChoice& choice1 = iConfigManager->GetChoice(kIdChoice1);
    TEST(choice1 == *iChoice1);
    ConfigChoice& choice2 = iConfigManager->GetChoice(kIdChoice2);
    TEST(choice2 == choice);

    // test ConfigText
    ConfigText text(*iConfigManager, kIdText2, MakeFunctor(*this, &SuiteConfigurationManager::OwnerFunctor), kMaxText, kText2);
    ConfigText& text1 = iConfigManager->GetText(kIdText1);
    TEST(text1 == *iText1);
    ConfigText& text2 = iConfigManager->GetText(kIdText2);
    TEST(text2 == text);
}


// SuiteRamStore

const Brn SuiteRamStore::kKey1("test.key.1");
const Brn SuiteRamStore::kKey2("test.key.2");
const Brn SuiteRamStore::kVal1("abcdefghijklmnopqrstuvwxyz");
const Brn SuiteRamStore::kVal2("zyxwvutsrqpomnlkjihgfedcba");

SuiteRamStore::SuiteRamStore()
    : SuiteUnitTest("SuiteRamStore")
{
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteRamStore::TestRead));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteRamStore::TestWrite));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteRamStore::TestDelete));
}

void SuiteRamStore::Setup()
{
    iStore = new ConfigRamStore();
}

void SuiteRamStore::TearDown()
{
    delete iStore;
}

void SuiteRamStore::TestRead()
{
    // write some values to the store, then attempt to read them (and also induce exceptions)
    Bwh val1(kVal1.Bytes());
    Bwh val2(kVal2.Bytes());

    // try reading a value prior to adding anything
    TEST_THROWS(iStore->Read(kKey1, val1), StoreKeyNotFound);

    // add some values
    iStore->Write(kKey1, kVal1);
    iStore->Write(kKey2, kVal2);

    // try reading an invalid key after some values exist
    Brn keyInvalid("a.invalid.key");
    TEST_THROWS(iStore->Read(keyInvalid, val1), StoreKeyNotFound);

    // try reading a valid key with a buffer that's too small
    Bwh bufSmall(kVal1.Bytes()-1);
    TEST_THROWS(iStore->Read(kKey1, bufSmall), StoreReadBufferUndersized);

    // check the correct written values are returned
    iStore->Read(kKey1, val1);
    TEST(val1 == kVal1);
    iStore->Read(kKey2, val2);
    TEST(val2 == kVal2);
}

void SuiteRamStore::TestWrite()
{
    // add some values - TestRead should show they can be read back correctly
    iStore->Write(kKey1, kVal1);
    iStore->Write(kKey2, kVal2);

    // update values
    Brn val1New("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"); // longer value
    Brn val2New("abc"); // shorter value
    iStore->Write(kKey1, val1New);
    iStore->Write(kKey2, val2New);

    // read and test new values
    Bwh val1(val1New.Bytes());
    Bwh val2(val2New.Bytes());
    iStore->Read(kKey1, val1);
    TEST(val1 == val1New);
    iStore->Read(kKey2, val2);
    TEST(val2 == val2New);
}

void SuiteRamStore::TestDelete()
{
    // write some values, delete them, try retrieve them, then re-add them
    Bwh val1(kVal1.Bytes());
    Bwh val2(kVal2.Bytes());

    // add some values - TestRead should show they can be read back correctly
    iStore->Write(kKey1, kVal1);
    iStore->Write(kKey2, kVal2);

    // delete each val and check StoreKeyNotFound is thrown when retrieving it
    iStore->Delete(kKey1);
    TEST_THROWS(iStore->Read(kKey1, val1), StoreKeyNotFound);
    iStore->Delete(kKey2);
    TEST_THROWS(iStore->Read(kKey2, val2), StoreKeyNotFound);

    // re-add vals and attempt to read
    iStore->Write(kKey1, kVal1);
    iStore->Write(kKey2, kVal2);

    iStore->Read(kKey1, val1);
    TEST(val1 == kVal1);
    iStore->Read(kKey2, val2);
    TEST(val2 == kVal2);
}



void TestConfigManager()
{
    Runner runner("ConfigManager tests\n");
    runner.Add(new SuiteCVSubscriptions());
    runner.Add(new SuiteConfigNum());
    runner.Add(new SuiteConfigChoice());
    runner.Add(new SuiteConfigText());
    runner.Add(new SuiteConfigurationManager());
    runner.Add(new SuiteRamStore());
    runner.Run();
}
