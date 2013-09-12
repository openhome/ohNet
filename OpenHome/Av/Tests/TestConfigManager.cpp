#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Av/ConfigManager.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;


class SuiteCVNotify : public SuiteUnitTest
{
public:
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
    void TestSubscriptionsNotRemoved();
private:
    void DummyFunctor();
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
    AddTest(MakeFunctor(*this, &SuiteCVSubscriptions::TestSubscriptionsNotRemoved));
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

void SuiteCVSubscriptions::TestSubscriptionsNotRemoved()
{
    // test adding a subscription and not removing it - should assert at
    // destruction
    iCVal->Subscribe(MakeFunctor(*this, &SuiteCVSubscriptions::NotifyChanged));
    TEST_THROWS(delete iCVal, AssertionFailed);
    iCVal = NULL;
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
    TUint val = iCVal->Get();
    TEST(val == kVal);
}

void SuiteCVNum::TestGetMin()
{
    // test the correct value for min is returned
    TUint min = iCVal->Min();
    TEST(min == kMin);
}

void SuiteCVNum::TestGetMax()
{
    // test the correct value for max is returned
    TUint max = iCVal->Max();
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

    TUint val = iCVal->Get();
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

    TUint val = iCVal->Get();
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

    const Brx& selected = iCVal->Get();
    TEST(selected == kOption1); // the first option should be the default
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

    const Brx& selected = iCVal->Get();
    TEST(selected == kOption2);

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

    const Brx& selected = iCVal->Get();
    TEST(selected == kOption1);

    iCVal->Unsubscribe(id);
}

void SuiteCVChoice::TestSetIndexOutOfRange()
{
    // test that attempting to set CVChoice to an invalid option index results
    // in an exception
    iCVal->Add(kOption1);
    iCVal->Add(kOption2);
    iCVal->Add(kOption3);

    const Brx& selectedBefore = iCVal->Get();
    TEST_THROWS(iCVal->Set(3), AvConfigIndexOutOfRange);
    const Brx& selectedAfter = iCVal->Get();
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



void TestConfigManager()
{
    Runner runner("ConfigManager tests\n");
    runner.Add(new SuiteCVSubscriptions());
    runner.Add(new SuiteCVNum());
    runner.Add(new SuiteCVChoice());
    runner.Add(new SuiteCVText());
    runner.Run();
}
