#include <OpenHome/Private/SuiteUnitTest.h>
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
protected:
    TUint iChangedCount;
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
    void TestInvalidRange();
    void TestValueOutOfRangeConstructor();
    void TestGet();
    void TestGetMin();
    void TestGetMax();
    void TestSetUpdate();
    void TestSetNoUpdate();
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
    void TestAdd();
    void TestAddDuplicate();
    void TestGet();
    void TestGetNoOptions();
    void TestSetUpdate();
    void TestSetNoUpdate();
    void TestSetIndexOutOfRange();
private:
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
    static const TUint kMinNum = 0;
    static const TUint kMaxNum = 2;
    static const TUint kMaxText = 10;
    static const Brn kIdNum1;
    static const Brn kIdNum2;
    static const Brn kIdChoice1;
    static const Brn kIdChoice2;
    static const Brn kIdText1;
    static const Brn kIdText2;
    ConfigurationManager* iConfigManager;
    ConfigNum* iNum1;
    ConfigNum* iNum2;
    ConfigChoice* iChoice1;
    ConfigChoice* iChoice2;
    ConfigText* iText1;
    ConfigText* iText2;
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

class SuiteStoreVal : public SuiteUnitTest
{
public:
    SuiteStoreVal();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestUpdateImmediate();
    void TestUpdateDeferred();
private:
    static const Brn kKey1;
    ConfigRamStore* iStore;
    ConfigNum* iConfigVal;
};

class SuiteStoreNum : public SuiteUnitTest
{
public:
    SuiteStoreNum();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestWriteNoUpdatePending();
    void TestWriteUpdatePending();
private:
    static const Brn kKey;
    ConfigRamStore* iStore;
    ConfigNum* iConfigVal;
    StoreNum* iStoreVal;
};

class SuiteStoreChoice : public SuiteUnitTest
{
public:
    SuiteStoreChoice();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestWriteNoUpdatePending();
    void TestWriteUpdatePending();
private:
    static const Brn kKey;
    static const Brn kOption1;
    static const Brn kOption2;
    ConfigRamStore* iStore;
    ConfigChoice* iConfigVal;
    StoreChoice* iStoreVal;
};

class SuiteStoreText : public SuiteUnitTest
{
public:
    SuiteStoreText();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestWriteNoUpdatePending();
    void TestWriteUpdatePending();
private:
    static const Brn kKey;
    static const Brn kText;
    ConfigRamStore* iStore;
    ConfigText* iConfigVal;
    StoreText* iStoreVal;
};

class SuiteStoreManager : public SuiteUnitTest
{
public:
    SuiteStoreManager();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void NotifyChanged();
    ConfigNum& CreateNum(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, ConfigNum& aNum, TInt& aInitial);
    ConfigChoice& CreateChoice(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, ConfigChoice& aChoice, TUint& aInitial);
    ConfigText& CreateText(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, ConfigText& aText, Bwx& aInitial);
    TBool MatchesStoreVal(const Brx& aId, TInt aExpected);
    TBool MatchesStoreVal(const Brx& aId, TUint aExpected);
    TBool MatchesStoreVal(const Brx& aId, const Brx& aExpected);
    void TestCreateNum();
    void TestWriteImmediateNum();
    void TestWriteDeferredNum();
    void TestCreateChoice();
    void TestWriteImmediateChoice();
    void TestWriteDeferredChoice();
    void TestCreateText();
    void TestWriteImmediateText();
    void TestWriteDeferredText();
    void TestCreateDiffTypesSameKey();
    void TestWritePendingUpdates();
private:
    static const Brn kKey1;
    static const Brn kKey2;
    static const Brn kKey3;
    static const Brn kFalse;
    static const Brn kTrue;
    static const TUint kTextMaxBytes = 26;
    static const Brn kText1;
    static const Brn kText2;
    ConfigRamStore* iStore;
    ConfigurationManager* iConfigManager;
    StoreManager* iStoreManager;
    TUint iChangedCount;
};

} // namespace Configuration
} // namespace OpenHome



// SuiteCVNotify

SuiteCVNotify::SuiteCVNotify(const TChar* aName)
    : SuiteUnitTest(aName)
{
}

SuiteCVNotify::~SuiteCVNotify() {}

void SuiteCVNotify::Setup()
{
    iChangedCount = 0;
}

void SuiteCVNotify::TearDown() {}

void SuiteCVNotify::NotifyChanged()
{
    iChangedCount++;
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
    iConfigVal = new ConfigNum(1,1,1);
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
    // test adding and removing multiple subscriptions (and test id ordering)
    // - will assert at destruction if error
    TUint id1 = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteCVSubscriptions::NotifyChanged));
    TEST(id1 == 0);
    TUint id2 = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteCVSubscriptions::NotifyChanged));
    TEST(id2 == 1);
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
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestInvalidRange));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestValueOutOfRangeConstructor));
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
    iConfigVal = new ConfigNum(kMin, kMax, kVal);
    iChangedCount = 0;
}

void SuiteConfigNum::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iConfigVal;
}

void SuiteConfigNum::TestInvalidRange()
{
    // test creating a ConfigNum with max < min
    TEST_THROWS(ConfigNum cv(1, -1, 1), AvConfigInvalidRange);
}

void SuiteConfigNum::TestValueOutOfRangeConstructor()
{
    // test creating a ConfigNum with val outside range min..max
    TEST_THROWS(ConfigNum cv(0, 0, 1), AvConfigValueOutOfRange);
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
    iConfigVal = new ConfigChoice();
}

void SuiteConfigChoice::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iConfigVal;
}

void SuiteConfigChoice::TestAdd()
{
    // test that after options are added to a ConfigChoice, they are available when
    // Options() is called
    iConfigVal->Add(kOption1);
    std::vector<const Brx*> options = iConfigVal->Options();

    iConfigVal->Add(kOption2);
    options = iConfigVal->Options();
    TEST(options.size() == 2);
    TEST(*options[0] == kOption1);
    TEST(*options[1] == kOption2);

    iConfigVal->Add(kOption3);
    options = iConfigVal->Options();
    TEST(options.size() == 3);
    TEST(*options[0] == kOption1);
    TEST(*options[1] == kOption2);
    TEST(*options[2] == kOption3);
}

void SuiteConfigChoice::TestAddDuplicate()
{
    // test that attempting to add a duplicate option fails
    iConfigVal->Add(kOption1);
    TEST_THROWS(iConfigVal->Add(kOption1), AvConfigValueExists);
}

void SuiteConfigChoice::TestGet()
{
    // test that adding some options and then calling Get() (without a prior
    // Set()) returns the first option

    iConfigVal->Add(kOption1);
    iConfigVal->Add(kOption2);
    iConfigVal->Add(kOption3);

    TUint selected = iConfigVal->Get();
    TEST(selected == 0); // the first option should be the default
}

void SuiteConfigChoice::TestGetNoOptions()
{
    // test that calling Get() before any options are added causes an assert
    TEST_THROWS(iConfigVal->Get(), AssertionFailed);
}

void SuiteConfigChoice::TestSetUpdate()
{
    // test that changing the selected value causes ConfigChoice to be updated (and
    // any observers notified)
    iConfigVal->Add(kOption1);
    iConfigVal->Add(kOption2);
    iConfigVal->Add(kOption3);

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
    iConfigVal->Add(kOption1);
    iConfigVal->Add(kOption2);
    iConfigVal->Add(kOption3);

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
    iConfigVal->Add(kOption1);
    iConfigVal->Add(kOption2);
    iConfigVal->Add(kOption3);

    TUint selectedBefore = iConfigVal->Get();
    TEST_THROWS(iConfigVal->Set(3), AvConfigIndexOutOfRange);
    TUint selectedAfter = iConfigVal->Get();
    TEST(selectedAfter == selectedBefore);
}


// SuiteConfigText

SuiteConfigText::SuiteConfigText()
    : SuiteCVNotify("SuiteConfigText")
{
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestMaxLength));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestGet));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetNoUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetValueTooLong));
}

void SuiteConfigText::Setup()
{
    SuiteCVNotify::Setup();
    iConfigVal = new ConfigText(kMaxLength);
}

void SuiteConfigText::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iConfigVal;
}

void SuiteConfigText::TestMaxLength()
{
    // test that the max possible length of the text buf matches init params
    TEST(iConfigVal->MaxLength() == kMaxLength);
}

void SuiteConfigText::TestGet()
{
    // test that calling Get() before Set() results in empty buffer being
    // returned
    const Brx& buf = iConfigVal->Get();

    TEST(buf.Bytes() == 0);
}

void SuiteConfigText::TestSetUpdate()
{
    // test that updating ConfigText with a new value results in ConfigText
    // being changed and any observers notified
    TUint changedCount = iChangedCount;
    Brn text("abcdefghijklmnopqrstuvwxyz");
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
    Brn empty("");
    TUint id = iConfigVal->Subscribe(MakeFunctor(*this, &SuiteConfigText::NotifyChanged));
    TBool updated = iConfigVal->Set(empty);
    TEST(updated == false);
    TEST(iChangedCount == changedCount);
    const Brx& buf1 = iConfigVal->Get();
    TEST(buf1 == empty);
    iConfigVal->Unsubscribe(id);

    Brn text("abcdefghijklmnopqrstuvwxyz");
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
    iConfigManager = new ConfigurationManager();
    iNum1 = new ConfigNum(kMinNum, kMaxNum, kMinNum);
    iNum2 = new ConfigNum(kMinNum, kMaxNum, kMinNum+1);
    iChoice1 = new ConfigChoice();
    iChoice2 = new ConfigChoice();
    iText1 = new ConfigText(kMaxText);
    iText2 = new ConfigText(kMaxText);
}

void SuiteConfigurationManager::TearDown()
{
    delete iConfigManager;
    delete iNum1;
    delete iNum2;
    delete iChoice1;
    delete iChoice2;
    delete iText1;
    delete iText2;
}

void SuiteConfigurationManager::TestAdd()
{
    // completion of this test without errors suggests adding works
    // Has() and Get() are tested in their own unit tests.
    iConfigManager->Add(kIdNum1, *iNum1);
    iConfigManager->Add(kIdChoice1, *iChoice1);
    iConfigManager->Add(kIdText1, *iText1);
}

void SuiteConfigurationManager::TestAddDuplicate()
{
    // test that an exception is throws if an attempt to add a ConfigVal with
    // the same ID is made twice

    // test ConfigNum
    iConfigManager->Add(kIdNum1, *iNum1);
    TEST(iConfigManager->HasNum(kIdNum1) == true);
    ConfigNum& num = iConfigManager->GetNum(kIdNum1);
    TEST(num == *iNum1);

    TEST_THROWS(iConfigManager->Add(kIdNum1, *iNum1), AvConfigIdExists);

    // test ConfigChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    TEST(iConfigManager->HasChoice(kIdChoice1) == true);
    ConfigChoice& choice = iConfigManager->GetChoice(kIdChoice1);
    TEST(choice == *iChoice1);

    TEST_THROWS(iConfigManager->Add(kIdChoice1, *iChoice1), AvConfigIdExists);

    // test ConfigText
    iConfigManager->Add(kIdText1, *iText1);
    TEST(iConfigManager->HasText(kIdText1) == true);
    ConfigText& text = iConfigManager->GetText(kIdText1);
    TEST(text == *iText1);

    TEST_THROWS(iConfigManager->Add(kIdText1, *iText1), AvConfigIdExists);

    // attempt to add a ConfigChoice with same ID as existing ConfigNum - should fail
    TEST_THROWS(iConfigManager->Add(kIdNum1, *iChoice1), AvConfigIdExists);
}

void SuiteConfigurationManager::TestHasNoVals()
{
    // test that calling Has() when no values are added returns false
    TEST(iConfigManager->HasNum(kIdNum1) == false);
    TEST(iConfigManager->HasChoice(kIdChoice1) == false);
    TEST(iConfigManager->HasText(kIdText1) == false);
    TEST(iConfigManager->Has(kIdNum1) == false);
    TEST(iConfigManager->Has(kIdChoice1) == false);
    TEST(iConfigManager->Has(kIdText1) == false);
}

void SuiteConfigurationManager::TestHasValidId()
{
    // test Has() returns true when a given ID exists

    // test ConfigNum
    iConfigManager->Add(kIdNum1, *iNum1);
    TEST(iConfigManager->HasNum(kIdNum1) == true);

    // test ConfigChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    TEST(iConfigManager->HasChoice(kIdChoice1) == true);

    // test ConfigText
    iConfigManager->Add(kIdText1, *iText1);
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
    iConfigManager->Add(kIdNum1, *iNum1);
    TEST(iConfigManager->HasNum(kIdNum2) == false);

    // test ConfigChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    TEST(iConfigManager->HasChoice(kIdChoice2) == false);

    // test ConfigText
    iConfigManager->Add(kIdText1, *iText1);
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
    iConfigManager->Add(kIdNum1, *iNum1);
    iConfigManager->Add(kIdNum2, *iNum2);
    TEST(iConfigManager->HasNum(kIdNum1) == true);
    TEST(iConfigManager->HasNum(kIdNum2) == true);

    // test ConfigChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    iConfigManager->Add(kIdChoice2, *iChoice2);
    TEST(iConfigManager->HasChoice(kIdChoice1) == true);
    TEST(iConfigManager->HasChoice(kIdChoice2) == true);

    // test ConfigText
    iConfigManager->Add(kIdText1, *iText1);
    iConfigManager->Add(kIdText2, *iText2);
    TEST(iConfigManager->HasText(kIdText1) == true);
    TEST(iConfigManager->HasText(kIdText2) == true);
}

void SuiteConfigurationManager::TestGetNoVals()
{
    // test that Get() fails with an assertion when no values are present
    TEST_THROWS(iConfigManager->GetNum(kIdNum1), AssertionFailed);
    TEST_THROWS(iConfigManager->GetChoice(kIdChoice1), AssertionFailed);
    TEST_THROWS(iConfigManager->GetText(kIdText1), AssertionFailed);
    TEST_THROWS(iConfigManager->Get(kIdNum1), AssertionFailed);
    TEST_THROWS(iConfigManager->Get(kIdChoice1), AssertionFailed);
    TEST_THROWS(iConfigManager->Get(kIdText1), AssertionFailed);
}

void SuiteConfigurationManager::TestGetValidId()
{
    // test Get() returns the correct val when ID is present

    // test ConfigNum
    iConfigManager->Add(kIdNum1, *iNum1);
    ConfigNum& num = iConfigManager->GetNum(kIdNum1);
    TEST(num == *iNum1);

    // test ConfigChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    ConfigChoice& choice = iConfigManager->GetChoice(kIdChoice1);
    TEST(choice == *iChoice1);

    // test ConfigText
    iConfigManager->Add(kIdText1, *iText1);
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

    // test ConfigNum
    iConfigManager->Add(kIdNum1, *iNum1);
    TEST_THROWS(iConfigManager->GetNum(kIdNum2), AssertionFailed);

    // test ConfigChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    TEST_THROWS(iConfigManager->GetChoice(kIdChoice2), AssertionFailed);

    // test ConfigText
    iConfigManager->Add(kIdText1, *iText1);
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
    iConfigManager->Add(kIdNum1, *iNum1);
    iConfigManager->Add(kIdNum2, *iNum2);
    ConfigNum& num1 = iConfigManager->GetNum(kIdNum1);
    TEST(num1 == *iNum1);
    ConfigNum& num2 = iConfigManager->GetNum(kIdNum2);
    TEST(num2 == *iNum2);

    // test ConfigChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    iConfigManager->Add(kIdChoice2, *iChoice2);
    ConfigChoice& choice1 = iConfigManager->GetChoice(kIdChoice1);
    TEST(choice1 == *iChoice1);
    ConfigChoice& choice2 = iConfigManager->GetChoice(kIdChoice2);
    TEST(choice2 == *iChoice2);

    // test ConfigText
    iConfigManager->Add(kIdText1, *iText1);
    iConfigManager->Add(kIdText2, *iText2);
    ConfigText& text1 = iConfigManager->GetText(kIdText1);
    TEST(text1 == *iText1);
    ConfigText& text2 = iConfigManager->GetText(kIdText2);
    TEST(text2 == *iText2);
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


// SuiteStoreVal

const Brn SuiteStoreVal::kKey1("store.key.1");

SuiteStoreVal::SuiteStoreVal()
    : SuiteUnitTest("SuiteStoreVal")
{
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreVal::TestUpdateImmediate));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreVal::TestUpdateDeferred));
}

void SuiteStoreVal::Setup()
{
    iStore = new ConfigRamStore();
    iConfigVal = new ConfigNum(0, 1, 0);
}

void SuiteStoreVal::TearDown()
{
    // StoreVal takes ownership of iConfigVal
    delete iStore;
}

void SuiteStoreVal::TestUpdateImmediate()
{
    // test the immediate update functionality of StoreVals
    // using a StoreNum here as StoreVal is abstract
    StoreNum sVal(*iStore, kKey1, false, iConfigVal);
    Bws<sizeof(TInt)> valBuf;

    // make a change to the ConfigVal
    iConfigVal->Set(1);

    // update should have been written immediately
    TEST(sVal.UpdatePending() == false);

    // check updated value from store
    Bws<sizeof(TInt)> expectedBuf;
    TInt expectedVal = 1;
    expectedBuf.Append(expectedVal);
    iStore->Read(kKey1, valBuf);
    TEST(valBuf == expectedBuf);
}

void SuiteStoreVal::TestUpdateDeferred()
{
    StoreNum sVal(*iStore, kKey1, true, iConfigVal);
    Bws<sizeof(TInt)> valBuf;

    // make a change to the ConfigVal
    iConfigVal->Set(1);

    // update should be pending; nothing should be in store yet
    TEST(sVal.UpdatePending() == true);
    TEST_THROWS(iStore->Read(kKey1, valBuf), StoreKeyNotFound);
}


// SuiteStoreNum

const Brn SuiteStoreNum::kKey("num.key.1");

SuiteStoreNum::SuiteStoreNum()
    : SuiteUnitTest("SuiteStoreNum")
{
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreNum::TestWriteNoUpdatePending));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreNum::TestWriteUpdatePending));
}

void SuiteStoreNum::Setup()
{
    iStore = new ConfigRamStore();
    iConfigVal = new ConfigNum(0, 1, 0);
    iStoreVal = new StoreNum(*iStore, kKey, true, iConfigVal);
}

void SuiteStoreNum::TearDown()
{
    // StoreVal takes ownership of iConfigVal
    delete iStoreVal;
    delete iStore;
}

void SuiteStoreNum::TestWriteNoUpdatePending()
{
    // try do a Write() when there is no update pending
    Bws<sizeof(TInt)> valBuf;

    TEST(iStoreVal->UpdatePending() == false);
    iStoreVal->Write();
    TEST_THROWS(iStore->Read(kKey, valBuf), StoreKeyNotFound);
}

void SuiteStoreNum::TestWriteUpdatePending()
{
    // try do a Write() when there is a (deferred) update pending
    Bws<sizeof(TInt)> valBuf;
    Bws<sizeof(TInt)> expectedBuf;
    TInt expectedVal = 1;
    expectedBuf.Append(expectedVal);

    iConfigVal->Set(1);
    TEST(iStoreVal->UpdatePending() == true);
    iStoreVal->Write();
    TEST(iStoreVal->UpdatePending() == false);

    // check the value written
    iStore->Read(kKey, valBuf);
    TEST(valBuf == expectedBuf);
}


// SuiteStoreChoice

const Brn SuiteStoreChoice::kKey("choice.key.1");
const Brn SuiteStoreChoice::kOption1("false");
const Brn SuiteStoreChoice::kOption2("true");

SuiteStoreChoice::SuiteStoreChoice()
    : SuiteUnitTest("SuiteStoreChoice")
{
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreChoice::TestWriteNoUpdatePending));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreChoice::TestWriteUpdatePending));
}

void SuiteStoreChoice::Setup()
{
    iStore = new ConfigRamStore();
    iConfigVal = new ConfigChoice();
    iConfigVal->Add(kOption1);
    iConfigVal->Add(kOption2);
    iStoreVal = new StoreChoice(*iStore, kKey, true, iConfigVal);
}

void SuiteStoreChoice::TearDown()
{
    // StoreVal takes ownership of iConfigVal
    delete iStoreVal;
    delete iStore;
}

void SuiteStoreChoice::TestWriteNoUpdatePending()
{
    // try do a Write() when there is no update pending
    Bws<sizeof(TUint)> valBuf;

    TEST(iStoreVal->UpdatePending() == false);
    iStoreVal->Write();
    TEST_THROWS(iStore->Read(kKey, valBuf), StoreKeyNotFound);
}

void SuiteStoreChoice::TestWriteUpdatePending()
{
    // try do a Write() when there is a (deferred) update pending
    Bws<sizeof(TUint)> valBuf;
    Bws<sizeof(TUint)> expectedBuf;
    TUint expectedVal = 1;
    expectedBuf.Append(expectedVal);

    iConfigVal->Set(1);
    TEST(iStoreVal->UpdatePending() == true);
    iStoreVal->Write();
    TEST(iStoreVal->UpdatePending() == false);

    // check the value written
    iStore->Read(kKey, valBuf);
    TEST(valBuf == expectedBuf);
}


// SuiteStoreText

const Brn SuiteStoreText::kKey("text.key.1");
const Brn SuiteStoreText::kText("Dummy Config Text");

SuiteStoreText::SuiteStoreText()
    : SuiteUnitTest("SuiteStoreText")
{
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreText::TestWriteNoUpdatePending));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreText::TestWriteUpdatePending));
}

void SuiteStoreText::Setup()
{
    iStore = new ConfigRamStore();
    iConfigVal = new ConfigText(kText.Bytes());
    iStoreVal = new StoreText(*iStore, kKey, true, iConfigVal);
}

void SuiteStoreText::TearDown()
{
    // StoreVal takes ownership of iConfigVal
    delete iStoreVal;
    delete iStore;
}

void SuiteStoreText::TestWriteNoUpdatePending()
{
    // try do a Write() when there is no update pending
    Bwh valBuf(kText.Bytes());

    TEST(iStoreVal->UpdatePending() == false);
    iStoreVal->Write();
    TEST_THROWS(iStore->Read(kKey, valBuf), StoreKeyNotFound);
}

void SuiteStoreText::TestWriteUpdatePending()
{
    // try do a Write() when there is a (deferred) update pending
    Bwh valBuf(kText.Bytes());

    iConfigVal->Set(kText);
    TEST(iStoreVal->UpdatePending() == true);
    iStoreVal->Write();
    TEST(iStoreVal->UpdatePending() == false);

    // check the value written
    iStore->Read(kKey, valBuf);
    TEST(valBuf == kText);
}


// SuiteStoreManager

const Brn SuiteStoreManager::kKey1("ssm.id.1");
const Brn SuiteStoreManager::kKey2("ssm.id.2");
const Brn SuiteStoreManager::kKey3("ssm.id.3");
const Brn SuiteStoreManager::kFalse("false");
const Brn SuiteStoreManager::kTrue("true");
const Brn SuiteStoreManager::kText1("abcdefghijklmnopqrstuvwxyz");
const Brn SuiteStoreManager::kText2("zyxwvutsrqponmlkjihgfedcba");

SuiteStoreManager::SuiteStoreManager()
    : SuiteUnitTest("SuiteStoreManager")
{
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreManager::TestCreateNum));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreManager::TestWriteImmediateNum));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreManager::TestWriteDeferredNum));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreManager::TestCreateChoice));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreManager::TestWriteImmediateChoice));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreManager::TestWriteDeferredChoice));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreManager::TestCreateText));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreManager::TestWriteImmediateText));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreManager::TestWriteDeferredText));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreManager::TestCreateDiffTypesSameKey));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteStoreManager::TestWritePendingUpdates));
}

void SuiteStoreManager::Setup()
{
    iStore = new ConfigRamStore();
    iConfigManager = new ConfigurationManager();
    iStoreManager = new StoreManager(*iStore, *iConfigManager);
    iChangedCount = 0;
}

void SuiteStoreManager::TearDown()
{
    delete iStoreManager;
    delete iConfigManager;
    delete iStore;
}

void SuiteStoreManager::NotifyChanged()
{
    iChangedCount++;
}

ConfigNum& SuiteStoreManager::CreateNum(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, ConfigNum& aNum, TInt& aInitial)
{
    aInitial = iStoreManager->CreateNum(aId, aUpdatesDeferred, aFunc, aNum.Min(), aNum.Max(), aNum.Get());
    ASSERT(iConfigManager->HasNum(aId) == true); // if the value we put in doesn't exist, there's a problem
    return iConfigManager->GetNum(aId);
}

ConfigChoice& SuiteStoreManager::CreateChoice(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, ConfigChoice& aChoice, TUint& aInitial)
{
    aInitial = iStoreManager->CreateChoice(aId, aUpdatesDeferred, aFunc, aChoice.Options(), aChoice.Get());
    ASSERT(iConfigManager->HasChoice(aId) == true); // if the value we put in doesn't exist, there's a problem
    return iConfigManager->GetChoice(aId);
}

ConfigText& SuiteStoreManager::CreateText(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, ConfigText& aText, Bwx& aInitial)
{
    aInitial.Replace(iStoreManager->CreateText(aId, aUpdatesDeferred, aFunc, aText.MaxLength(), aText.Get()));
    ASSERT(iConfigManager->HasText(aId) == true); // if the value we put in doesn't exist, there's a problem
    return iConfigManager->GetText(aId);
}

TBool SuiteStoreManager::MatchesStoreVal(const Brx& aId, TInt aExpected)
{
    Bws<sizeof(TInt)> expectedBuf;
    Bws<sizeof(TInt)> valBuf;
    expectedBuf.Append(aExpected);
    iStore->Read(aId, valBuf);
    return (valBuf == expectedBuf);
}

TBool SuiteStoreManager::MatchesStoreVal(const Brx& aId, TUint aExpected)
{
    Bws<sizeof(TUint)> expectedBuf;
    Bws<sizeof(TUint)> valBuf;
    expectedBuf.Append(aExpected);
    iStore->Read(aId, valBuf);
    return (valBuf == expectedBuf);
}

TBool SuiteStoreManager::MatchesStoreVal(const Brx& aId, const Brx& aExpected)
{
    Bwh valBuf(aExpected.Bytes());
    iStore->Read(aId, valBuf);
    return (valBuf == aExpected);
}

void SuiteStoreManager::TestCreateNum()
{
    ConfigNum val(0, 1, 0);

    // try creating value that doesn't yet exist in store
    TInt initial;
    ConfigNum& confVal = CreateNum(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val, initial);
    TEST(initial == val.Get());
    TEST(confVal == val);

    // try creating from key that already exists as a config value
    TEST_THROWS(iStoreManager->CreateNum(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val.Min(), val.Max(), val.Get()), AvConfigIdExists);
}

void SuiteStoreManager::TestWriteImmediateNum()
{
    // test that immediate writes work
    ConfigNum val(0, 1, 0);

    // create value in store and check callback works
    TInt initial;
    ConfigNum& confVal = CreateNum(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val, initial);
    confVal.Set(1);
    TEST(iChangedCount == 1);

    // test that non-deferred write worked
    TEST(MatchesStoreVal(kKey1, confVal.Get()) == true);
}

void SuiteStoreManager::TestWriteDeferredNum()
{
    // test that deferred writes work as expected
    ConfigNum val(0, 1, 0);

    // create a value
    TInt initial;
    ConfigNum& confVal = CreateNum(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val, initial);

    // get original val and change config val - value in store should NOT be updated yet
    TInt expected = confVal.Get();
    confVal.Set(1);
    TEST(iChangedCount == 1); // check callback works
    TEST(MatchesStoreVal(kKey1, expected) == true);

    // write updates to store
    expected = confVal.Get();
    iStoreManager->WritePendingUpdates();
    TEST(MatchesStoreVal(kKey1, expected) == true);
}

void SuiteStoreManager::TestCreateChoice()
{
    ConfigChoice val;
    val.Add(kFalse);
    val.Add(kTrue);

    // try creating value that doesn't yet exist in store
    TUint initial;
    ConfigChoice& confVal = CreateChoice(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val, initial);
    TEST(initial == val.Get());
    TEST(confVal == val);

    // try creating from key that already exists as a config value
    TEST_THROWS(iStoreManager->CreateChoice(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val.Options(), val.Get()), AvConfigIdExists);
}

void SuiteStoreManager::TestWriteImmediateChoice()
{
    // test that immediate writes work
    ConfigChoice val;
    val.Add(kFalse);
    val.Add(kTrue);

    // create value in store and check callback works
    TUint initial;
    ConfigChoice& confVal = CreateChoice(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val, initial);
    confVal.Set(1);
    TEST(iChangedCount == 1);

    // test that non-deferred write worked
    TEST(MatchesStoreVal(kKey1, confVal.Get()) == true);
}

void SuiteStoreManager::TestWriteDeferredChoice()
{
    // test that deferred writes work as expected
    ConfigChoice val;
    val.Add(kFalse);
    val.Add(kTrue);

    // create a value
    TUint initial;
    ConfigChoice& confVal = CreateChoice(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val, initial);

    // get original val and change config val - value in store should NOT be updated yet
    TUint expected = confVal.Get();
    confVal.Set(1);
    TEST(iChangedCount == 1); // check callback works
    TEST(MatchesStoreVal(kKey1, expected) == true);

    // write updates to store
    expected = confVal.Get();
    iStoreManager->WritePendingUpdates();
    TEST(MatchesStoreVal(kKey1, expected) == true);
}

void SuiteStoreManager::TestCreateText()
{
    ConfigText val(kTextMaxBytes);
    val.Set(kText1);

    // try creating value that doesn't yet exist in store
    Bwh initial(kText1.Bytes());
    ConfigText& confVal = CreateText(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val, initial);
    TEST(initial == val.Get());
    TEST(confVal == val);

    // try creating from key that already exists as a config value
    TEST_THROWS(iStoreManager->CreateText(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), kTextMaxBytes, val.Get()), AvConfigIdExists);
}

void SuiteStoreManager::TestWriteImmediateText()
{
    // test that immediate writes work
    ConfigText val(kTextMaxBytes);
    val.Set(kText1);

    // create value in store and check callback works
    Bwh initial(kText1.Bytes());
    ConfigText& confVal = CreateText(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val, initial);
    confVal.Set(kText2);
    TEST(iChangedCount == 1);

    // test that non-deferred write worked
    TEST(MatchesStoreVal(kKey1, confVal.Get()) == true);
}

void SuiteStoreManager::TestWriteDeferredText()
{
    // test that deferred writes work as expected
    ConfigText val(kTextMaxBytes);
    val.Set(kText1);

    // create a value
    Bwh initial(kText1.Bytes());
    ConfigText& confVal = CreateText(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val, initial);

    // update the config value - value in store should NOT be updated
    Bwh expected(kTextMaxBytes);
    expected.Append(confVal.Get());
    // change config val
    confVal.Set(kText2);
    TEST(iChangedCount == 1); // check callback works
    TEST(MatchesStoreVal(kKey1, expected) == true);

    // write updates to store
    expected.Replace(confVal.Get());
    iStoreManager->WritePendingUpdates();
    TEST(MatchesStoreVal(kKey1, expected) == true);
}

void SuiteStoreManager::TestCreateDiffTypesSameKey()
{
    // test attempting to create multiple different types of value from the
    // store using the same key fails

    // create a num
    ConfigNum valNum(0, 1, 0);
    TInt initialNum;
    CreateNum(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), valNum, initialNum);

    // try create a choice with same key
    std::vector<const Brx*> options;
    options.push_back(&kFalse);
    options.push_back(&kTrue);
    TEST_THROWS(iStoreManager->CreateChoice(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), options, 0), AvConfigIdExists);

    // try create a text with same key
    TEST_THROWS(iStoreManager->CreateText(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), kTextMaxBytes, kText1), AvConfigIdExists);
}

void SuiteStoreManager::TestWritePendingUpdates()
{
    // test writing pending updates for multiple different values

    // create a num
    ConfigNum valNum(0, 1, 0);
    TInt initialNum;
    ConfigNum& confValNum = CreateNum(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), valNum, initialNum);

    // create a choice
    ConfigChoice valChoice;
    valChoice.Add(kFalse);
    valChoice.Add(kTrue);
    TUint initialChoice;
    ConfigChoice& confValChoice = CreateChoice(kKey2, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), valChoice, initialChoice);

    // create a text
    ConfigText valText(kTextMaxBytes);
    valText.Set(kText1);
    Bwh initialText(kText1.Bytes());
    ConfigText& confValText = CreateText(kKey3, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), valText, initialText);

    // change all config vals
    TInt expectedNum = confValNum.Get();
    confValNum.Set(1);
    TEST(iChangedCount == 1); // check callback works
    TEST(MatchesStoreVal(kKey1, expectedNum) == true);

    TUint expectedChoice = confValChoice.Get();
    confValChoice.Set(1);
    TEST(iChangedCount == 2); // check callback works
    TEST(MatchesStoreVal(kKey2, expectedChoice) == true);

    Bwh expectedText(kTextMaxBytes);
    expectedText.Append(confValText.Get());
    confValText.Set(kText2);
    TEST(iChangedCount == 3); // check callback works
    TEST(MatchesStoreVal(kKey3, expectedText) == true);

    // write the pending updates to store
    expectedNum = confValNum.Get();
    expectedChoice = confValChoice.Get();
    expectedText.Replace(confValText.Get());
    iStoreManager->WritePendingUpdates();
    // check values have been updated in store
    TEST(MatchesStoreVal(kKey1, expectedNum) == true);
    TEST(MatchesStoreVal(kKey2, expectedChoice) == true);
    TEST(MatchesStoreVal(kKey3, expectedText) == true);
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
    runner.Add(new SuiteStoreVal());
    runner.Add(new SuiteStoreNum());
    runner.Add(new SuiteStoreChoice());
    runner.Add(new SuiteStoreText());
    runner.Add(new SuiteStoreManager());
    runner.Run();
}
