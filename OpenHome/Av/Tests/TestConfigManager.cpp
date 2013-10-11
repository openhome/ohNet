#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Av/ConfigManager.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;


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
    CVal* iCVal;
};

class SuiteCVNum : public SuiteCVNotify
{
public:
    SuiteCVNum();
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
    CVNum* iCVal;
};

class SuiteCVChoice : public SuiteCVNotify
{
public:
    SuiteCVChoice();
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
    CVChoice* iCVal;
};

class SuiteCVText : public SuiteCVNotify
{
public:
    SuiteCVText();
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
    CVText* iCVal;
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
    CVNum* iNum1;
    CVNum* iNum2;
    CVChoice* iChoice1;
    CVChoice* iChoice2;
    CVText* iText1;
    CVText* iText2;
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
    CVNum* iConfigVal;
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
    CVNum* iConfigVal;
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
    CVChoice* iConfigVal;
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
    CVText* iConfigVal;
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
    iCVal = new CVNum(1,1);
}

void SuiteCVSubscriptions::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iCVal;
}

void SuiteCVSubscriptions::TestNoSubscriptions()
{
    // test that a CVal can be successfully destructed without ever having a
    // subscription on it.
    delete iCVal;
    iCVal = NULL;
}

void SuiteCVSubscriptions::TestAddRemoveSubscription()
{
    // test adding and removing a single subscription - will assert at
    // destruction if error
    TUint id = iCVal->Subscribe(MakeFunctor(*this, &SuiteCVSubscriptions::NotifyChanged));
    iCVal->Unsubscribe(id);
    delete iCVal;
    iCVal = NULL;
}

void SuiteCVSubscriptions::TestAddRemoveMultipleSubscriptions()
{
    // test adding and removing multiple subscriptions (and test id ordering)
    // - will assert at destruction if error
    TUint id1 = iCVal->Subscribe(MakeFunctor(*this, &SuiteCVSubscriptions::NotifyChanged));
    TEST(id1 == 0);
    TUint id2 = iCVal->Subscribe(MakeFunctor(*this, &SuiteCVSubscriptions::NotifyChanged));
    TEST(id2 == 1);
    iCVal->Unsubscribe(id1);
    iCVal->Unsubscribe(id2);
    delete iCVal;
    iCVal = NULL;
}

void SuiteCVSubscriptions::TestRemoveInvalidId()
{
    // test that trying to unsubscribe using an invalid id does nothing
    iCVal->Unsubscribe(0);
}


// SuiteCVNum

SuiteCVNum::SuiteCVNum()
    : SuiteCVNotify("SuiteCVNum")
{
    AddTest(MakeFunctor(*this, &SuiteCVNum::TestInvalidRange));
    AddTest(MakeFunctor(*this, &SuiteCVNum::TestValueOutOfRangeConstructor));
    AddTest(MakeFunctor(*this, &SuiteCVNum::TestGet));
    AddTest(MakeFunctor(*this, &SuiteCVNum::TestGetMin));
    AddTest(MakeFunctor(*this, &SuiteCVNum::TestGetMax));
    AddTest(MakeFunctor(*this, &SuiteCVNum::TestSetUpdate));
    AddTest(MakeFunctor(*this, &SuiteCVNum::TestSetNoUpdate));
    AddTest(MakeFunctor(*this, &SuiteCVNum::TestSetValueOutOfRange));
}

void SuiteCVNum::Setup()
{
    SuiteCVNotify::Setup();
    iCVal = new CVNum(kMin, kMax, kVal);
    iChangedCount = 0;
}

void SuiteCVNum::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iCVal;
}

void SuiteCVNum::TestInvalidRange()
{
    // test creating a CVNum with max < min
    TEST_THROWS(CVNum cv(1, -1, 1), AvConfigInvalidRange);
    TEST_THROWS(CVNum cv(1, -1), AvConfigInvalidRange);
}

void SuiteCVNum::TestValueOutOfRangeConstructor()
{
    // test creating a CVNum with val outside range min..max
    TEST_THROWS(CVNum cv(0, 0, 1), AvConfigValueOutOfRange);
}

void SuiteCVNum::TestGet()
{
    // test the correct value of the CVNum is returned
    TInt val = iCVal->Get();
    TEST(val == kVal);
}

void SuiteCVNum::TestGetMin()
{
    // test the correct value for min is returned
    TInt min = iCVal->Min();
    TEST(min == kMin);
}

void SuiteCVNum::TestGetMax()
{
    // test the correct value for max is returned
    TInt max = iCVal->Max();
    TEST(max == kMax);
}

void SuiteCVNum::TestSetUpdate()
{
    // test that calling set with a new value updates the value of the CVNum
    // (and that any observers are notified)
    TUint changedCount = iChangedCount;
    TUint id = iCVal->Subscribe(MakeFunctor(*this, &SuiteCVNum::NotifyChanged));
    TBool updated = iCVal->Set(kVal+1);

    TEST(updated == true);
    TEST(iChangedCount == changedCount+1);

    TInt val = iCVal->Get();
    TEST(val == kVal+1);

    iCVal->Unsubscribe(id);
}

void SuiteCVNum::TestSetNoUpdate()
{
    // test that calling set with the existing value of CVNum causing no change
    // to the CVNum, and that no observers are notified
    TUint changedCount = iChangedCount;
    TUint id = iCVal->Subscribe(MakeFunctor(*this, &SuiteCVNum::NotifyChanged));
    TBool updated = iCVal->Set(iCVal->Get());

    TEST(updated == false);
    TEST(iChangedCount == changedCount);

    TInt val = iCVal->Get();
    TEST(val == kVal);

    iCVal->Unsubscribe(id);
}

void SuiteCVNum::TestSetValueOutOfRange()
{
    // test attempting to set CVNum's value outwith the range min..max
    TInt valBefore = iCVal->Get();
    TEST_THROWS(iCVal->Set(kMax+1), AvConfigValueOutOfRange);
    TInt valAfter = iCVal->Get();
    TEST(valAfter == valBefore);

    valBefore = iCVal->Get();
    TEST_THROWS(iCVal->Set(kMin-1), AvConfigValueOutOfRange);
    valAfter = iCVal->Get();
    TEST(valAfter == valBefore);
}


// SuiteCVChoice

const Brn SuiteCVChoice::kOption1("Option1");
const Brn SuiteCVChoice::kOption2("Option2");
const Brn SuiteCVChoice::kOption3("Option3");

SuiteCVChoice::SuiteCVChoice()
    : SuiteCVNotify("SuiteCVChoice")
{
    AddTest(MakeFunctor(*this, &SuiteCVChoice::TestAdd));
    AddTest(MakeFunctor(*this, &SuiteCVChoice::TestAddDuplicate));
    AddTest(MakeFunctor(*this, &SuiteCVChoice::TestGet));
    AddTest(MakeFunctor(*this, &SuiteCVChoice::TestGetNoOptions));
    AddTest(MakeFunctor(*this, &SuiteCVChoice::TestSetUpdate));
    AddTest(MakeFunctor(*this, &SuiteCVChoice::TestSetNoUpdate));
    AddTest(MakeFunctor(*this, &SuiteCVChoice::TestSetIndexOutOfRange));
}

void SuiteCVChoice::Setup()
{
    SuiteCVNotify::Setup();
    iCVal = new CVChoice();
}

void SuiteCVChoice::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iCVal;
}

void SuiteCVChoice::TestAdd()
{
    // test that after options are added to a CVChoice, they are available when
    // Options() is called
    iCVal->Add(kOption1);
    std::vector<const Brx*> options = iCVal->Options();

    iCVal->Add(kOption2);
    options = iCVal->Options();
    TEST(options.size() == 2);
    TEST(*options[0] == kOption1);
    TEST(*options[1] == kOption2);

    iCVal->Add(kOption3);
    options = iCVal->Options();
    TEST(options.size() == 3);
    TEST(*options[0] == kOption1);
    TEST(*options[1] == kOption2);
    TEST(*options[2] == kOption3);
}

void SuiteCVChoice::TestAddDuplicate()
{
    // test that attempting to add a duplicate option fails
    iCVal->Add(kOption1);
    TEST_THROWS(iCVal->Add(kOption1), AvConfigValueAlreadyExists);
}

void SuiteCVChoice::TestGet()
{
    // test that adding some options and then calling Get() (without a prior
    // Set()) returns the first option

    iCVal->Add(kOption1);
    iCVal->Add(kOption2);
    iCVal->Add(kOption3);

    TUint selected = iCVal->Get();
    TEST(selected == 0); // the first option should be the default
}

void SuiteCVChoice::TestGetNoOptions()
{
    // test that calling Get() before any options are added causes an assert
    TEST_THROWS(iCVal->Get(), AssertionFailed);
}

void SuiteCVChoice::TestSetUpdate()
{
    // test that changing the selected value causes CVChoice to be updated (and
    // any observers notified)
    iCVal->Add(kOption1);
    iCVal->Add(kOption2);
    iCVal->Add(kOption3);

    TUint changedCount = iChangedCount;
    TUint id = iCVal->Subscribe(MakeFunctor(*this, &SuiteCVChoice::NotifyChanged));
    TBool updated = iCVal->Set(1);

    TEST(updated == true);
    TEST(iChangedCount == changedCount+1);

    TUint selected = iCVal->Get();
    TEST(selected == 1);

    iCVal->Unsubscribe(id);
}

void SuiteCVChoice::TestSetNoUpdate()
{
    // test that setting the same option index results in no change to CVChoice
    // (and observers aren't notified)
    iCVal->Add(kOption1);
    iCVal->Add(kOption2);
    iCVal->Add(kOption3);

    TUint changedCount = iChangedCount;
    TUint id = iCVal->Subscribe(MakeFunctor(*this, &SuiteCVChoice::NotifyChanged));
    TBool updated = iCVal->Set(0);

    TEST(updated == false);
    TEST(iChangedCount == changedCount);

    TUint selected = iCVal->Get();
    TEST(selected == 0);

    iCVal->Unsubscribe(id);
}

void SuiteCVChoice::TestSetIndexOutOfRange()
{
    // test that attempting to set CVChoice to an invalid option index results
    // in an exception
    iCVal->Add(kOption1);
    iCVal->Add(kOption2);
    iCVal->Add(kOption3);

    TUint selectedBefore = iCVal->Get();
    TEST_THROWS(iCVal->Set(3), AvConfigIndexOutOfRange);
    TUint selectedAfter = iCVal->Get();
    TEST(selectedAfter == selectedBefore);
}


// SuiteCVText

SuiteCVText::SuiteCVText()
    : SuiteCVNotify("SuiteCVText")
{
    AddTest(MakeFunctor(*this, &SuiteCVText::TestMaxLength));
    AddTest(MakeFunctor(*this, &SuiteCVText::TestGet));
    AddTest(MakeFunctor(*this, &SuiteCVText::TestSetUpdate));
    AddTest(MakeFunctor(*this, &SuiteCVText::TestSetNoUpdate));
    AddTest(MakeFunctor(*this, &SuiteCVText::TestSetValueTooLong));
}

void SuiteCVText::Setup()
{
    SuiteCVNotify::Setup();
    iCVal = new CVText(kMaxLength);
}

void SuiteCVText::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iCVal;
}

void SuiteCVText::TestMaxLength()
{
    // test that the max possible length of the text buf matches init params
    TEST(iCVal->MaxLength() == kMaxLength);
}

void SuiteCVText::TestGet()
{
    // test that calling Get() before Set() results in empty buffer being
    // returned
    const Brx& buf = iCVal->Get();

    TEST(buf.Bytes() == 0);
}

void SuiteCVText::TestSetUpdate()
{
    // test that updating CVText with a new value results in CVText being
    // changed and any observers notified
    TUint changedCount = iChangedCount;
    Brn text("abcdefghijklmnopqrstuvwxyz");
    TUint id = iCVal->Subscribe(MakeFunctor(*this, &SuiteCVText::NotifyChanged));
    TBool updated = iCVal->Set(text);

    TEST(updated == true);
    TEST(iChangedCount == changedCount+1);

    const Brx& buf = iCVal->Get();
    TEST(buf == text);

    iCVal->Unsubscribe(id);
}

void SuiteCVText::TestSetNoUpdate()
{
    // test that updating CVText with the same value results in no change to
    // CVText and no observers being notified
    TUint changedCount = iChangedCount;

    // test updating the empty string, then test updating a string with
    // length > 0
    Brn empty("");
    TUint id = iCVal->Subscribe(MakeFunctor(*this, &SuiteCVText::NotifyChanged));
    TBool updated = iCVal->Set(empty);
    TEST(updated == false);
    TEST(iChangedCount == changedCount);
    const Brx& buf1 = iCVal->Get();
    TEST(buf1 == empty);
    iCVal->Unsubscribe(id);

    Brn text("abcdefghijklmnopqrstuvwxyz");
    updated = iCVal->Set(text);
    id = iCVal->Subscribe(MakeFunctor(*this, &SuiteCVText::NotifyChanged));
    updated = iCVal->Set(text);
    TEST(updated == false);
    TEST(iChangedCount == changedCount);
    const Brx& buf2 = iCVal->Get();
    TEST(buf2 == text);
    iCVal->Unsubscribe(id);
}

void SuiteCVText::TestSetValueTooLong()
{
    // test that attempting to set CVText to a value with length > maxbytes
    // causes an exception to be thrown
    Bws<kMaxLength+1> buf;
    buf.SetBytes(buf.MaxBytes());

    const Brx& bufBefore = iCVal->Get();
    TEST_THROWS(iCVal->Set(buf), AvConfigValueTooLong);
    const Brx& bufAfter = iCVal->Get();
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
    // CVNum, CVChoice and CVText would end up in a lot of boilerplate code.
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
    iNum1 = new CVNum(kMinNum, kMaxNum, kMinNum);
    iNum2 = new CVNum(kMinNum, kMaxNum, kMinNum+1);
    iChoice1 = new CVChoice();
    iChoice2 = new CVChoice();
    iText1 = new CVText(kMaxText);
    iText2 = new CVText(kMaxText);
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
    // test that an exception is throws if an attempt to add a CVal with the
    // same ID is made twice

    // test CVNum
    iConfigManager->Add(kIdNum1, *iNum1);
    TEST(iConfigManager->HasNum(kIdNum1) == true);
    CVNum& num = iConfigManager->GetNum(kIdNum1);
    TEST(num == *iNum1);

    TEST_THROWS(iConfigManager->Add(kIdNum1, *iNum1), AvConfigIdAlreadyExists);

    // test CVChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    TEST(iConfigManager->HasChoice(kIdChoice1) == true);
    CVChoice& choice = iConfigManager->GetChoice(kIdChoice1);
    TEST(choice == *iChoice1);

    TEST_THROWS(iConfigManager->Add(kIdChoice1, *iChoice1), AvConfigIdAlreadyExists);

    // test CVText
    iConfigManager->Add(kIdText1, *iText1);
    TEST(iConfigManager->HasText(kIdText1) == true);
    CVText& text = iConfigManager->GetText(kIdText1);
    TEST(text == *iText1);

    TEST_THROWS(iConfigManager->Add(kIdText1, *iText1), AvConfigIdAlreadyExists);

    // attempt to add a CVChoice with same ID as existing CVNum - should fail
    TEST_THROWS(iConfigManager->Add(kIdNum1, *iChoice1), AvConfigIdAlreadyExists);
}

void SuiteConfigurationManager::TestHasNoVals()
{
    // test that calling Has() when no values are added returns false
    TEST(iConfigManager->HasNum(kIdNum1) == false);
    TEST(iConfigManager->HasChoice(kIdChoice1) == false);
    TEST(iConfigManager->HasText(kIdText1) == false);
}

void SuiteConfigurationManager::TestHasValidId()
{
    // test Has() returns true when a given ID exists

    // test CVNum
    iConfigManager->Add(kIdNum1, *iNum1);
    TEST(iConfigManager->HasNum(kIdNum1) == true);

    // test CVChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    TEST(iConfigManager->HasChoice(kIdChoice1) == true);

    // test CVText
    iConfigManager->Add(kIdText1, *iText1);
    TEST(iConfigManager->HasText(kIdText1) == true);
}

void SuiteConfigurationManager::TestHasInvalidId()
{
    // test Has() returns false when IDs are present, but not the given ID

    // test CVNum
    iConfigManager->Add(kIdNum1, *iNum1);
    TEST(iConfigManager->HasNum(kIdNum2) == false);

    // test CVChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    TEST(iConfigManager->HasChoice(kIdChoice2) == false);

    // test CVText
    iConfigManager->Add(kIdText1, *iText1);
    TEST(iConfigManager->HasText(kIdText2) == false);

    // try call HasChoice() with the ID of CVNum
    TEST(iConfigManager->HasChoice(kIdNum1) == false);
}

void SuiteConfigurationManager::TestHasMultiple()
{
    // test adding multiple values and calling Has() on the IDs

    // test CVNum
    iConfigManager->Add(kIdNum1, *iNum1);
    iConfigManager->Add(kIdNum2, *iNum2);
    TEST(iConfigManager->HasNum(kIdNum1) == true);
    TEST(iConfigManager->HasNum(kIdNum2) == true);

    // test CVChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    iConfigManager->Add(kIdChoice2, *iChoice2);
    TEST(iConfigManager->HasChoice(kIdChoice1) == true);
    TEST(iConfigManager->HasChoice(kIdChoice2) == true);

    // test CVText
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
}

void SuiteConfigurationManager::TestGetValidId()
{
    // test Get() returns the correct val when ID is present

    // test CVNum
    iConfigManager->Add(kIdNum1, *iNum1);
    CVNum& num = iConfigManager->GetNum(kIdNum1);
    TEST(num == *iNum1);

    // test CVChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    CVChoice& choice = iConfigManager->GetChoice(kIdChoice1);
    TEST(choice == *iChoice1);

    // test CVText
    iConfigManager->Add(kIdText1, *iText1);
    CVText& text = iConfigManager->GetText(kIdText1);
    TEST(text == *iText1);
}

void SuiteConfigurationManager::TestGetInvalidId()
{
    // test that Get() causes an assertion when ID is not present

    // test CVNum
    iConfigManager->Add(kIdNum1, *iNum1);
    TEST_THROWS(iConfigManager->GetNum(kIdNum2), AssertionFailed);

    // test CVChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    TEST_THROWS(iConfigManager->GetChoice(kIdChoice2), AssertionFailed);

    // test CVText
    iConfigManager->Add(kIdText1, *iText1);
    TEST_THROWS(iConfigManager->GetText(kIdText2), AssertionFailed);

    // try call HasChoice() with the ID of CVNum
    TEST_THROWS(iConfigManager->GetChoice(kIdNum1), AssertionFailed);
}

void SuiteConfigurationManager::TestGetMultiple()
{
    // test adding multiple values and calling Get() on the IDs

    // test CVNum
    iConfigManager->Add(kIdNum1, *iNum1);
    iConfigManager->Add(kIdNum2, *iNum2);
    CVNum& num1 = iConfigManager->GetNum(kIdNum1);
    TEST(num1 == *iNum1);
    CVNum& num2 = iConfigManager->GetNum(kIdNum2);
    TEST(num2 == *iNum2);

    // test CVChoice
    iConfigManager->Add(kIdChoice1, *iChoice1);
    iConfigManager->Add(kIdChoice2, *iChoice2);
    CVChoice& choice1 = iConfigManager->GetChoice(kIdChoice1);
    TEST(choice1 == *iChoice1);
    CVChoice& choice2 = iConfigManager->GetChoice(kIdChoice2);
    TEST(choice2 == *iChoice2);

    // test CVText
    iConfigManager->Add(kIdText1, *iText1);
    iConfigManager->Add(kIdText2, *iText2);
    CVText& text1 = iConfigManager->GetText(kIdText1);
    TEST(text1 == *iText1);
    CVText& text2 = iConfigManager->GetText(kIdText2);
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
    iConfigVal = new CVNum(0, 1, 0);
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
    expectedBuf.Append(1);
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
    iConfigVal = new CVNum(0, 1, 0);
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
    expectedBuf.Append(1);

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
    iConfigVal = new CVChoice();
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
    expectedBuf.Append(1);

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
    iConfigVal = new CVText(kText.Bytes());
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

void SuiteStoreManager::TestCreateNum()
{
    const CVNum val(0, 1, 0);

    // try creating from key that doesn't exist in store
    TEST_THROWS(iStoreManager->CreateNum(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val.Min(), val.Max()), StoreKeyNotFound);

    // try creating from value that exists in store
    Bwh valBuf(sizeof(TInt));
    valBuf.Append(val.Get());
    iStore->Write(kKey1, valBuf);
    TInt initialVal = iStoreManager->CreateNum(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val.Min(), val.Max());
    TEST(initialVal == val.Get());
    TEST(iConfigManager->HasNum(kKey1) == true);
    CVNum& confVal = iConfigManager->GetNum(kKey1);
    TEST(confVal == val);

    // try creating from key that already exists as a config value
    TEST_THROWS(iStoreManager->CreateNum(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val.Min(), val.Max()), AvConfigIdAlreadyExists);
}

void SuiteStoreManager::TestWriteImmediateNum()
{
    // test that immediate writes work
    const CVNum val(0, 1, 0);

    // create value in store
    Bwh valBuf(sizeof(TInt));
    valBuf.Append(val.Get());
    iStore->Write(kKey1, valBuf);
    iStoreManager->CreateNum(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val.Min(), val.Max());

    // test that callback functor has been added to config val subscribers correctly
    TEST(iConfigManager->HasNum(kKey1) == true);
    CVNum& confVal = iConfigManager->GetNum(kKey1);
    confVal.Set(1);
    TEST(iChangedCount == 1);

    // test that non-deferred write worked
    Bwh expectedBuf(sizeof(TInt));
    expectedBuf.Append(confVal.Get());
    iStore->Read(kKey1, valBuf);
    TEST(valBuf == expectedBuf);
}

void SuiteStoreManager::TestWriteDeferredNum()
{
    // test that deferred writes work as expected
    const CVNum val(0, 1, 0);

    // create a value
    Bwh valBuf(sizeof(TInt));
    valBuf.Append(val.Get());
    iStore->Write(kKey1, valBuf);
    iStoreManager->CreateNum(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), val.Min(), val.Max());

    // update the config value - value in store should NOT be updated
    TEST(iConfigManager->HasNum(kKey1) == true);
    CVNum& confVal = iConfigManager->GetNum(kKey1);
    // get original val
    Bwh expectedBuf(sizeof(TInt));
    expectedBuf.Append(confVal.Get());
    // change config val
    confVal.Set(1);
    TEST(iChangedCount == 1); // check callback works
    // check val hasn't been changed in store
    iStore->Read(kKey1, valBuf);
    TEST(valBuf == expectedBuf);

    // write the pending updates to store
    expectedBuf.SetBytes(0);
    expectedBuf.Append(confVal.Get());
    iStoreManager->WritePendingUpdates();
    // check value has been updated in store
    iStore->Read(kKey1, valBuf);
    TEST(valBuf == expectedBuf);
}

void SuiteStoreManager::TestCreateChoice()
{
    CVChoice val;
    val.Add(kFalse);
    val.Add(kTrue);

    std::vector<const Brx*> options;
    options.push_back(&kFalse);
    options.push_back(&kTrue);

    // try creating from key that doesn't exist in store
    TEST_THROWS(iStoreManager->CreateChoice(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), options), StoreKeyNotFound);

    // try creating from value that exists in store
    Bwh valBuf(sizeof(TUint));
    valBuf.Append(val.Get());
    iStore->Write(kKey1, valBuf);
    TUint initialVal = iStoreManager->CreateChoice(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), options);
    TEST(initialVal == val.Get());
    TEST(iConfigManager->HasChoice(kKey1) == true);
    CVChoice& confVal = iConfigManager->GetChoice(kKey1);
    TEST(confVal == val);

    // try creating from key that already exists as a config value
    TEST_THROWS(iStoreManager->CreateChoice(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), options), AvConfigIdAlreadyExists);
}

void SuiteStoreManager::TestWriteImmediateChoice()
{
    // test that immediate writes work
    CVChoice val;
    val.Add(kFalse);
    val.Add(kTrue);

    std::vector<const Brx*> options;
    options.push_back(&kFalse);
    options.push_back(&kTrue);

    // create value in store
    Bwh valBuf(sizeof(TUint));
    valBuf.Append(val.Get());
    iStore->Write(kKey1, valBuf);
    iStoreManager->CreateChoice(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), options);

    // test that callback functor has been added to config val subscribers correctly
    TEST(iConfigManager->HasChoice(kKey1) == true);
    CVChoice& confVal = iConfigManager->GetChoice(kKey1);
    confVal.Set(1);
    TEST(iChangedCount == 1);

    // test that non-deferred write worked
    Bwh expectedBuf(sizeof(TUint));
    expectedBuf.Append(confVal.Get());
    iStore->Read(kKey1, valBuf);
    TEST(valBuf == expectedBuf);
}

void SuiteStoreManager::TestWriteDeferredChoice()
{
    // test that deferred writes work as expected
    CVChoice val;
    val.Add(kFalse);
    val.Add(kTrue);

    std::vector<const Brx*> options;
    options.push_back(&kFalse);
    options.push_back(&kTrue);

    // create a value
    Bwh valBuf(sizeof(TUint));
    valBuf.Append(val.Get());
    iStore->Write(kKey1, valBuf);
    iStoreManager->CreateChoice(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), options);

    // update the config value - value in store should NOT be updated
    TEST(iConfigManager->HasChoice(kKey1) == true);
    CVChoice& confVal = iConfigManager->GetChoice(kKey1);
    // get original val
    Bwh expectedBuf(sizeof(TUint));
    expectedBuf.Append(confVal.Get());
    // change config val
    confVal.Set(1);
    TEST(iChangedCount == 1); // check callback works
    // check val hasn't been changed in store
    iStore->Read(kKey1, valBuf);
    TEST(valBuf == expectedBuf);

    // write the pending updates to store
    expectedBuf.SetBytes(0);
    expectedBuf.Append(confVal.Get());
    iStoreManager->WritePendingUpdates();
    // check value has been updated in store
    iStore->Read(kKey1, valBuf);
    TEST(valBuf == expectedBuf);
}

void SuiteStoreManager::TestCreateText()
{
    CVText val(kTextMaxBytes);
    val.Set(kText1);

    // try creating from key that doesn't exist in store
    TEST_THROWS(iStoreManager->CreateText(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), kTextMaxBytes), StoreKeyNotFound);

    // try creating from value that exists in store
    Bwh valBuf(kTextMaxBytes);
    valBuf.Append(val.Get());
    iStore->Write(kKey1, valBuf);
    const Brx& initialVal = iStoreManager->CreateText(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), kTextMaxBytes);
    TEST(initialVal == val.Get());
    TEST(iConfigManager->HasText(kKey1) == true);
    CVText& confVal = iConfigManager->GetText(kKey1);
    TEST(confVal == val);

    // try creating from key that already exists as a config value
    TEST_THROWS(iStoreManager->CreateText(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), kTextMaxBytes), AvConfigIdAlreadyExists);
}

void SuiteStoreManager::TestWriteImmediateText()
{
    // test that immediate writes work
    CVText val(kTextMaxBytes);
    val.Set(kText1);

    // create value in store
    Bwh valBuf(kTextMaxBytes);
    valBuf.Append(val.Get());
    iStore->Write(kKey1, valBuf);
    iStoreManager->CreateText(kKey1, false, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), kTextMaxBytes);

    // test that callback functor has been added to config val subscribers correctly
    TEST(iConfigManager->HasText(kKey1) == true);
    CVText& confVal = iConfigManager->GetText(kKey1);
    confVal.Set(kText2);
    TEST(iChangedCount == 1);

    // test that non-deferred write worked
    Bwh expectedBuf(kTextMaxBytes);
    expectedBuf.Append(confVal.Get());
    iStore->Read(kKey1, valBuf);
    TEST(valBuf == expectedBuf);
}

void SuiteStoreManager::TestWriteDeferredText()
{
    // test that deferred writes work as expected
    CVText val(kTextMaxBytes);
    val.Set(kText1);

    // create a value
    Bwh valBuf(kTextMaxBytes);
    valBuf.Append(val.Get());
    iStore->Write(kKey1, valBuf);
    iStoreManager->CreateText(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), kTextMaxBytes);

    // update the config value - value in store should NOT be updated
    TEST(iConfigManager->HasText(kKey1) == true);
    CVText& confVal = iConfigManager->GetText(kKey1);
    // get original val
    Bwh expectedBuf(kTextMaxBytes);
    expectedBuf.Append(confVal.Get());
    // change config val
    confVal.Set(kText2);
    TEST(iChangedCount == 1); // check callback works
    // check val hasn't been changed in store
    iStore->Read(kKey1, valBuf);
    TEST(valBuf == expectedBuf);

    // write the pending updates to store
    expectedBuf.SetBytes(0);
    expectedBuf.Append(confVal.Get());
    iStoreManager->WritePendingUpdates();
    // check value has been updated in store
    iStore->Read(kKey1, valBuf);
    TEST(valBuf == expectedBuf);
}

void SuiteStoreManager::TestCreateDiffTypesSameKey()
{
    // test attempting to create multiple different types of value from the
    // store using the same key fails

    // create a num
    const CVNum valNum(0, 1, 0);
    Bwh valBufNum(sizeof(TInt));
    valBufNum.Append(valNum.Get());
    iStore->Write(kKey1, valBufNum);
    iStoreManager->CreateNum(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), valNum.Min(), valNum.Max());

    // try create a choice with same key
    std::vector<const Brx*> options;
    options.push_back(&kFalse);
    options.push_back(&kTrue);
    TEST_THROWS(iStoreManager->CreateChoice(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), options), AvConfigIdAlreadyExists);

    // try create a text with same key
    TEST_THROWS(iStoreManager->CreateText(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), kTextMaxBytes), AvConfigIdAlreadyExists);
}

void SuiteStoreManager::TestWritePendingUpdates()
{
    // test writing pending updates for multiple different values

    // create a num
    const CVNum valNum(0, 1, 0);
    Bwh valBufNum(sizeof(TInt));
    valBufNum.Append(valNum.Get());
    iStore->Write(kKey1, valBufNum);
    iStoreManager->CreateNum(kKey1, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), valNum.Min(), valNum.Max());
    CVNum& confValNum = iConfigManager->GetNum(kKey1);

    // create a choice
    CVChoice valChoice;
    valChoice.Add(kFalse);
    valChoice.Add(kTrue);
    std::vector<const Brx*> options;
    options.push_back(&kFalse);
    options.push_back(&kTrue);
    Bwh valBufChoice(sizeof(TUint));
    valBufChoice.Append(valChoice.Get());
    iStore->Write(kKey2, valBufChoice);
    iStoreManager->CreateChoice(kKey2, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), options);
    CVChoice& confValChoice = iConfigManager->GetChoice(kKey2);

    // create a text
    CVText valText(kTextMaxBytes);
    valText.Set(kText1);
    Bwh valBufText(kTextMaxBytes);
    valBufText.Append(valText.Get());
    iStore->Write(kKey3, valBufText);
    iStoreManager->CreateText(kKey3, true, MakeFunctor(*this, &SuiteStoreManager::NotifyChanged), kTextMaxBytes);
    CVText& confValText = iConfigManager->GetText(kKey3);

    // change all config vals
    Bwh expectedBufNum(sizeof(TInt));
    expectedBufNum.Append(confValNum.Get());
    confValNum.Set(1);
    TEST(iChangedCount == 1); // check callback works
    iStore->Read(kKey1, valBufNum);
    TEST(valBufNum == expectedBufNum);

    Bwh expectedBufChoice(sizeof(TUint));
    expectedBufChoice.Append(confValChoice.Get());
    confValChoice.Set(1);
    TEST(iChangedCount == 2); // check callback works
    iStore->Read(kKey2, valBufChoice);
    TEST(valBufChoice == expectedBufChoice);

    Bwh expectedBufText(kTextMaxBytes);
    expectedBufText.Append(confValText.Get());
    confValText.Set(kText2);
    TEST(iChangedCount == 3); // check callback works
    iStore->Read(kKey3, valBufText);
    TEST(valBufText == expectedBufText);

    // write the pending updates to store
    expectedBufNum.SetBytes(0);
    expectedBufNum.Append(confValNum.Get());
    expectedBufChoice.SetBytes(0);
    expectedBufChoice.Append(confValChoice.Get());
    expectedBufText.SetBytes(0);
    expectedBufText.Append(confValText.Get());
    iStoreManager->WritePendingUpdates();
    // check values have been updated in store
    iStore->Read(kKey1, valBufNum);
    TEST(valBufNum == expectedBufNum);
    iStore->Read(kKey2, valBufChoice);
    TEST(valBufChoice == expectedBufChoice);
    iStore->Read(kKey3, valBufText);
    TEST(valBufText == expectedBufText);
}



void TestConfigManager()
{
    Runner runner("ConfigManager tests\n");
    runner.Add(new SuiteCVSubscriptions());
    runner.Add(new SuiteCVNum());
    runner.Add(new SuiteCVChoice());
    runner.Add(new SuiteCVText());
    runner.Add(new SuiteConfigurationManager());
    runner.Add(new SuiteRamStore());
    runner.Add(new SuiteStoreVal());
    runner.Add(new SuiteStoreNum());
    runner.Add(new SuiteStoreChoice());
    runner.Add(new SuiteStoreText());
    runner.Add(new SuiteStoreManager());
    runner.Run();
}
