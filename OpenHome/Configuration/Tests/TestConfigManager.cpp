#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Configuration/ConfigManager.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Configuration;

namespace OpenHome {
namespace Configuration {

template <class T>
class SuiteCVNotify : public SuiteUnitTest
{
protected:
    SuiteCVNotify(const TChar* aName);
    virtual ~SuiteCVNotify() = 0;
protected: // from SuiteUnitTest
    void Setup();
    void TearDown();
protected:
    virtual void NotifyChanged(T aVal);
protected:
    static const Brn kKey;
    ConfigRamStore* iStore;
    ConfigManager* iConfigManager;
    TUint iChangedCount;
};

class SuiteCVSubscriptions : public SuiteCVNotify<TInt>
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
    ConfigVal<TInt>* iConfigVal;
};

class SuiteConfigNum : public SuiteCVNotify<TInt>
{
public:
    SuiteConfigNum();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:  // from SuiteCVNotify
    void NotifyChanged(TInt aVal);
private:
    TInt IntFromStore(const Brx& aKey);
    void TestInternalFunctorsCalledAtConstruction();
    void TestIdStored();
    void TestSubscription();
    void TestInvalidRange();
    void TestValueOutOfRangeConstructor();
    void TestValueFromStore();
    void TestValueWrittenToStore();
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
    TInt iLastChangeVal;
};

class SuiteConfigChoice : public SuiteCVNotify<TUint>
{
public:
    SuiteConfigChoice();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:  // from SuiteCVNotify
    void NotifyChanged(TUint aVal);
private:
    TUint UintFromStore(const Brx& aKey);
    void TestInternalFunctorsCalledAtConstruction();
    void TestIdStored();
    void TestSubscription();
    void TestValueFromStore();
    void TestValueWrittenToStore();
    void TestAdd();
    void TestGetNoChoices();
    void TestSetUpdate();
    void TestSetNoUpdate();
    void TestSetNoSuchChoice();
private:
    static const TUint kDefault = 1000;
    static const TUint kChoice1;
    static const TUint kChoice2;
    static const TUint kChoice3;
    ConfigChoice* iConfigVal;
    TUint iLastChangeVal;
};

class SuiteConfigText : public SuiteCVNotify<const Brx&>
{
public:
    SuiteConfigText();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:  // from SuiteCVNotify
    void NotifyChanged(const Brx& aVal);
private:
    static const TUint kMaxLength = 100;
    static const Brn kDefault;
    void TestInternalFunctorsCalledAtConstruction();
    void TestIdStored();
    void TestSubscription();
    void TestValueFromStore();
    void TestValueWrittenToStore();
    void TestMaxLength();
    void TestSetUpdate();
    void TestSetNoUpdate();
    void TestSetValueTooLong();
    ConfigText* iConfigVal;
    Bws<kMaxLength> iLastChangeVal;
};

class SuiteConfigManager : public SuiteUnitTest
{
public:
    SuiteConfigManager();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void NotifyChangedNum(TInt aVal);
    void NotifyChangedChoice(TUint aVal);
    void NotifyChangedText(const Brx& aVal);
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
    void TestReadStoreValExists();
    void TestReadNoStoreValExists();
    void TestWrite();
private:
    static const TInt kMinNum = 0;
    static const TInt kMaxNum = 2;
    static const TUint kChoiceDefault = 0;
    static const TUint kChoice1;
    static const TUint kChoice2;
    static const TUint kChoice3;
    static const TUint kMaxText = 26;
    static const Brn kText1;
    static const Brn kText2;
    static const Brn kIdNum1;
    static const Brn kIdNum2;
    static const Brn kIdChoice1;
    static const Brn kIdChoice2;
    static const Brn kIdText1;
    static const Brn kIdText2;
    ConfigRamStore* iStore;
    ConfigManager* iConfigManager;
    ConfigNum* iNum1;
    std::vector<TUint> iChoices;
    ConfigChoice* iChoice1;
    ConfigText* iText1;
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

template <class T> const Brn SuiteCVNotify<T>::kKey("conf.key");

template <class T> SuiteCVNotify<T>::SuiteCVNotify(const TChar* aName)
    : SuiteUnitTest(aName)
{
}

template <class T> SuiteCVNotify<T>::~SuiteCVNotify() {}

template <class T> void SuiteCVNotify<T>::Setup()
{
    iStore = new ConfigRamStore();
    iConfigManager = new ConfigManager(*iStore);
    iChangedCount = 0;
}

template <class T> void SuiteCVNotify<T>::TearDown()
{
    delete iConfigManager;
    delete iStore;
}

template <class T> void SuiteCVNotify<T>::NotifyChanged(T /*aVal*/)
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
    iConfigVal = new ConfigNum(*iConfigManager, kKey, 1, 1, 1);
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
    TUint id = iConfigVal->Subscribe(MakeFunctorGeneric<TInt>(*this, &SuiteCVSubscriptions::NotifyChanged));
    TEST(id != 0);
    iConfigVal->Unsubscribe(id);
    delete iConfigVal;
    iConfigVal = NULL;
}

void SuiteCVSubscriptions::TestAddRemoveMultipleSubscriptions()
{
    // test adding and removing multiple (extra) subscriptions (and test id
    // ordering) - will assert at destruction if error
    // IDs should start at 1, and there should be 2 internal subscribers at construction
    TUint id1 = iConfigVal->Subscribe(MakeFunctorGeneric<TInt>(*this, &SuiteCVSubscriptions::NotifyChanged));
    TEST(id1 == 2);
    TUint id2 = iConfigVal->Subscribe(MakeFunctorGeneric<TInt>(*this, &SuiteCVSubscriptions::NotifyChanged));
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
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestInternalFunctorsCalledAtConstruction));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestIdStored));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSubscription));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestInvalidRange));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestValueOutOfRangeConstructor));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestValueFromStore));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestValueWrittenToStore));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestGetMin));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestGetMax));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSetUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSetNoUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSetValueOutOfRange));
}

void SuiteConfigNum::Setup()
{
    SuiteCVNotify::Setup();
    iLastChangeVal = 0;
    iConfigVal = new ConfigNum(*iConfigManager, kKey, kMin, kMax, kVal);
}

void SuiteConfigNum::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iConfigVal;
}

void SuiteConfigNum::NotifyChanged(TInt aVal)
{
    SuiteCVNotify::NotifyChanged(aVal);
    iLastChangeVal = aVal;
}

TInt SuiteConfigNum::IntFromStore(const Brx& aKey)
{
    Bws<sizeof(TInt)> buf;
    iStore->Read(aKey, buf);
    TInt val = Converter::BeUint32At(buf, 0);
    return val;
}

void SuiteConfigNum::TestInternalFunctorsCalledAtConstruction()
{
    // there is an internal write functor - check value == value in store
    TEST(IntFromStore(kKey) == kVal);
}

void SuiteConfigNum::TestIdStored()
{
    // test that the id is stored internally; not just wrapping a value
    static const Brn keyConst("temporary.id");
    Bwh keyChangeable(keyConst);
    ConfigNum num(*iConfigManager, keyChangeable, kMin, kMax, kVal);
    TEST(num.Id() == keyConst);
    keyChangeable.SetBytes(0);
    TEST(num.Id() == keyConst);
}

void SuiteConfigNum::TestSubscription()
{
    // test that functor is called back at time of subscription
    TUint changedCount = iChangedCount;
    TUint id = iConfigVal->Subscribe(MakeFunctorGeneric<TInt>(*this, &SuiteConfigNum::NotifyChanged));

    TEST(iChangedCount == changedCount+1);
    TEST(iLastChangeVal == kVal);
    iConfigVal->Unsubscribe(id);
}

void SuiteConfigNum::TestInvalidRange()
{
    // test creating a ConfigNum with max < min
    TEST_THROWS(ConfigNum cv(*iConfigManager, kKey, 1, -1, 1), AssertionFailed);
}

void SuiteConfigNum::TestValueOutOfRangeConstructor()
{
    // test creating a ConfigNum with val outside range min..max
    TEST_THROWS(ConfigNum cv(*iConfigManager, kKey, 0, 0, 1), AssertionFailed);
}

void SuiteConfigNum::TestValueFromStore()
{
    // test an existing value in store overwrites the default value at creation
    const Brn key("conf.num.2");
    const TInt storeVal = kVal+1;
    Bws<sizeof(TInt)> valBuf;
    valBuf.Append(Arch::BigEndian4(storeVal));
    iStore->Write(key, valBuf);
    ConfigNum num(*iConfigManager, key, kMin, kMax, kVal);
    TUint id = num.Subscribe(MakeFunctorGeneric<TInt>(*this, &SuiteConfigNum::NotifyChanged));

    // test value in store hasn't been overwritten
    TEST(IntFromStore(key) == storeVal);
    // test retrieved value is correct
    TEST(iLastChangeVal == storeVal);
    num.Unsubscribe(id);
}

void SuiteConfigNum::TestValueWrittenToStore()
{
    // test that the default value has been written out to store at creation
    TEST(IntFromStore(kKey) == kVal);
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
    TInt newVal = kVal+1;
    TUint id = iConfigVal->Subscribe(MakeFunctorGeneric<TInt>(*this, &SuiteConfigNum::NotifyChanged));
    TUint changedCount = iChangedCount;
    TBool updated = iConfigVal->Set(newVal);

    TEST(updated == true);
    TEST(iChangedCount == changedCount+1);

    TEST(iLastChangeVal == newVal);
    // test that value has been written out to store
    TEST(IntFromStore(kKey) == newVal);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigNum::TestSetNoUpdate()
{
    // test that calling set with the existing value of ConfigNum causing no change
    // to the ConfigNum, and that no observers are notified

    TUint id = iConfigVal->Subscribe(MakeFunctorGeneric<TInt>(*this, &SuiteConfigNum::NotifyChanged));
    TUint changedCount = iChangedCount;
    TBool updated = iConfigVal->Set(iLastChangeVal);

    TEST(updated == false);
    TEST(iChangedCount == changedCount);

    TEST(iLastChangeVal == kVal);
    // test value in store hasn't changed
    TEST(IntFromStore(kKey) == kVal);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigNum::TestSetValueOutOfRange()
{
    // test attempting to set ConfigNum's value outwith the range min..max
    TInt valBefore = iLastChangeVal;
    TEST_THROWS(iConfigVal->Set(kMax+1), ConfigValueOutOfRange);
    TInt valAfter = iLastChangeVal;
    TEST(valAfter == valBefore);

    valBefore = iLastChangeVal;
    TEST_THROWS(iConfigVal->Set(kMin-1), ConfigValueOutOfRange);
    valAfter = iLastChangeVal;
    TEST(valAfter == valBefore);
}


// SuiteConfigChoice

const TUint SuiteConfigChoice::kChoice1 = 1000;
const TUint SuiteConfigChoice::kChoice2 = 1001;
const TUint SuiteConfigChoice::kChoice3 = 1002;

SuiteConfigChoice::SuiteConfigChoice()
    : SuiteCVNotify("SuiteConfigChoice")
{
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestInternalFunctorsCalledAtConstruction));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestIdStored));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSubscription));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestValueFromStore));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestValueWrittenToStore));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestAdd));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestGetNoChoices));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSetUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSetNoUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSetNoSuchChoice));
}

void SuiteConfigChoice::Setup()
{
    SuiteCVNotify::Setup();
    std::vector<TUint> choices;
    choices.push_back(kChoice1);
    choices.push_back(kChoice2);
    choices.push_back(kChoice3);
    iLastChangeVal = 0;
    iConfigVal = new ConfigChoice(*iConfigManager, kKey, choices, kDefault);
}

void SuiteConfigChoice::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iConfigVal;
}

void SuiteConfigChoice::NotifyChanged(TUint aVal)
{
    SuiteCVNotify::NotifyChanged(aVal);
    iLastChangeVal = aVal;
}

TUint SuiteConfigChoice::UintFromStore(const Brx& aKey)
{
    Bws<sizeof(TUint)> buf;
    iStore->Read(aKey, buf);
    TUint val = Converter::BeUint32At(buf, 0);
    return val;
}

void SuiteConfigChoice::TestInternalFunctorsCalledAtConstruction()
{
    // there is an internal write functor - check value == value in store
    TEST(UintFromStore(kKey) == kDefault);
}

void SuiteConfigChoice::TestIdStored()
{
    // test that the id is stored internally; not just wrapping a value
    static const Brn keyConst("temporary.id");
    Bwh keyChangeable(keyConst);
    std::vector<TUint> choices;
    choices.push_back(kChoice1);
    choices.push_back(kChoice2);
    choices.push_back(kChoice3);

    ConfigChoice choice(*iConfigManager, keyChangeable, choices, kDefault);
    TEST(choice.Id() == keyConst);
    keyChangeable.SetBytes(0);
    TEST(choice.Id() == keyConst);
}

void SuiteConfigChoice::TestSubscription()
{
    // test that functor is called back at time of subscription
    TUint changedCount = iChangedCount;
    TUint id = iConfigVal->Subscribe(MakeFunctorGeneric<TUint>(*this, &SuiteConfigChoice::NotifyChanged));

    TEST(iChangedCount == changedCount+1);
    TEST(iLastChangeVal == kDefault);
    iConfigVal->Unsubscribe(id);
}

void SuiteConfigChoice::TestValueFromStore()
{
    // test an existing value in store overwrites the default value at creation
    const Brn key("conf.choice.2");
    const TUint storeVal = kDefault+1;
    Bws<sizeof(TUint)> valBuf;
    valBuf.Append(Arch::BigEndian4(storeVal));
    iStore->Write(key, valBuf);

    std::vector<TUint> choices;
    choices.push_back(kChoice1);
    choices.push_back(kChoice2);
    choices.push_back(kChoice3);
    ConfigChoice choice(*iConfigManager, key, choices, kDefault);
    TUint id = choice.Subscribe(MakeFunctorGeneric<TUint>(*this, &SuiteConfigChoice::NotifyChanged));

    // test value in store hasn't been overwritten
    TEST(UintFromStore(key) == storeVal);
    // test retrieved value is correct
    TEST(iLastChangeVal == storeVal);
    choice.Unsubscribe(id);
}

void SuiteConfigChoice::TestValueWrittenToStore()
{
    // test that the default value has been written out to store at creation
    TEST(UintFromStore(kKey) == kDefault);
}

void SuiteConfigChoice::TestAdd()
{
    // test that after choices are added to a ConfigChoice, they are available when
    // Choices() is called
    const std::vector<TUint>& choices = iConfigVal->Choices();
    TEST(choices.size() == 3);
    TEST(choices[0] == kChoice1);
    TEST(choices[1] == kChoice2);
    TEST(choices[2] == kChoice3);
}

void SuiteConfigChoice::TestGetNoChoices()
{
    // test that creating without any choices causes an assert
    std::vector<TUint> choices;
    TEST_THROWS(ConfigChoice cv(*iConfigManager, kKey, choices, kDefault), AssertionFailed);
}

void SuiteConfigChoice::TestSetUpdate()
{
    // test that changing the selected value causes ConfigChoice to be updated (and
    // any observers notified)
    TUint newVal = kDefault+1;
    TUint id = iConfigVal->Subscribe(MakeFunctorGeneric<TUint>(*this, &SuiteConfigChoice::NotifyChanged));
    TUint changedCount = iChangedCount;
    TBool updated = iConfigVal->Set(newVal);

    TEST(updated == true);
    TEST(iChangedCount == changedCount+1);

    TEST(iLastChangeVal == newVal);
    // test that value has been written out to store
    TEST(UintFromStore(kKey) == newVal);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigChoice::TestSetNoUpdate()
{
    // test that setting the same choice value results in no change to ConfigChoice
    // (and observers aren't notified)
    TUint id = iConfigVal->Subscribe(MakeFunctorGeneric<TUint>(*this, &SuiteConfigChoice::NotifyChanged));
    TUint changedCount = iChangedCount;
    TBool updated = iConfigVal->Set(kDefault);

    TEST(updated == false);
    TEST(iChangedCount == changedCount);

    TEST(iLastChangeVal == kDefault);
    // test value in store hasn't changed
    TEST(UintFromStore(kKey) == kDefault);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigChoice::TestSetNoSuchChoice()
{
    // test that attempting to set ConfigChoice to an invalid choice results in
    // an exception
    TUint selectedBefore = iLastChangeVal;
    TEST_THROWS(iConfigVal->Set(kDefault-1), ConfigInvalidChoice);
    TUint selectedAfter = iLastChangeVal;
    TEST(selectedAfter == selectedBefore);
}


// SuiteConfigText

const Brn SuiteConfigText::kDefault("abcdefghijklmnopqrstuvwxyz");

SuiteConfigText::SuiteConfigText()
    : SuiteCVNotify("SuiteConfigText")
{
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestInternalFunctorsCalledAtConstruction));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestIdStored));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSubscription));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestValueFromStore));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestValueWrittenToStore));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestMaxLength));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetNoUpdate));
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetValueTooLong));
}

void SuiteConfigText::Setup()
{
    SuiteCVNotify::Setup();
    iLastChangeVal.SetBytes(0);
    iConfigVal = new ConfigText(*iConfigManager, kKey, kMaxLength, kDefault);
}

void SuiteConfigText::TearDown()
{
    SuiteCVNotify::TearDown();
    delete iConfigVal;
}

void SuiteConfigText::NotifyChanged(const Brx& aVal)
{
    SuiteCVNotify::NotifyChanged(aVal);
    iLastChangeVal.Replace(aVal);
}

void SuiteConfigText::TestInternalFunctorsCalledAtConstruction()
{
    // there is an internal write functor - check value == value in store
    Bwh valBuf(kMaxLength);
    iStore->Read(kKey, valBuf);
    TEST(valBuf == kDefault);
}

void SuiteConfigText::TestIdStored()
{
    // test that the id is stored internally; not just wrapping a value
    static const Brn keyConst("temporary.id");
    Bwh keyChangeable(keyConst);
    ConfigText text(*iConfigManager, keyChangeable, kMaxLength, kDefault);
    TEST(text.Id() == keyConst);
    keyChangeable.SetBytes(0);
    TEST(text.Id() == keyConst);
}

void SuiteConfigText::TestSubscription()
{
    // test that functor is called back at time of subscription
    TUint changedCount = iChangedCount;
    TUint id = iConfigVal->Subscribe(MakeFunctorGeneric<const Brx&>(*this, &SuiteConfigText::NotifyChanged));

    TEST(iChangedCount == changedCount+1);
    TEST(iLastChangeVal == kDefault);
    iConfigVal->Unsubscribe(id);
}

void SuiteConfigText::TestValueFromStore()
{
    // test an existing value in store overwrites the default value at creation
    const Brn key("conf.text.2");
    Brn storeVal("zyxwvutsrqponmlkjihgfedcba");
    iStore->Write(key, storeVal);
    ConfigText text(*iConfigManager, key, kMaxLength, kDefault);
    TUint id = text.Subscribe(MakeFunctorGeneric<const Brx&>(*this, &SuiteConfigText::NotifyChanged));

    // test value in store hasn't been overwritten
    Bwh valBuf(kMaxLength);
    iStore->Read(key, valBuf);
    TEST(valBuf == storeVal);
    // test retrieved value is correct
    TEST(iLastChangeVal == storeVal);
    text.Unsubscribe(id);
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

void SuiteConfigText::TestSetUpdate()
{
    // test that updating ConfigText with a new value results in ConfigText
    // being changed and any observers notified
    Brn newVal("zyxwvutsrqponmlkjihgfedcba");
    TUint id = iConfigVal->Subscribe(MakeFunctorGeneric<const Brx&>(*this, &SuiteConfigText::NotifyChanged));
    TUint changedCount = iChangedCount;
    TBool updated = iConfigVal->Set(newVal);

    TEST(updated == true);
    TEST(iChangedCount == changedCount+1);

    TEST(iLastChangeVal == newVal);
    // test that value has been written out to store
    Bwh valBuf(kMaxLength);
    iStore->Read(kKey, valBuf);
    TEST(valBuf == newVal);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigText::TestSetNoUpdate()
{
    // test that updating ConfigText with the same value results in no change to
    // ConfigText and no observers being notified

    // test updating the default string, then test updating a string with
    // length > 0
    TUint id = iConfigVal->Subscribe(MakeFunctorGeneric<const Brx&>(*this, &SuiteConfigText::NotifyChanged));
    TUint changedCount = iChangedCount;
    TBool updated = iConfigVal->Set(kDefault);
    TEST(updated == false);
    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == kDefault);
    // test value in store hasn't changed
    Bwh valBuf(kMaxLength);
    iStore->Read(kKey, valBuf);
    TEST(valBuf == kDefault);
    iConfigVal->Unsubscribe(id);

    Brn text("zyxwvutsrqponmlkjihgfedcba");
    // set new val before then subscribing to changes
    updated = iConfigVal->Set(text);
    changedCount = iChangedCount;
    id = iConfigVal->Subscribe(MakeFunctorGeneric<const Brx&>(*this, &SuiteConfigText::NotifyChanged));
    changedCount = iChangedCount;
    // now attempt to set same value again
    updated = iConfigVal->Set(text);
    TEST(updated == false);
    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == text);
    // test value in store hasn't changed
    valBuf.SetBytes(0);
    iStore->Read(kKey, valBuf);
    TEST(valBuf == text);
    iConfigVal->Unsubscribe(id);
}

void SuiteConfigText::TestSetValueTooLong()
{
    // test that attempting to set ConfigText to a value with length > maxbytes
    // causes an exception to be thrown
    Bws<kMaxLength+1> buf;
    buf.SetBytes(buf.MaxBytes());

    const Brx& bufBefore = iLastChangeVal;
    TEST_THROWS(iConfigVal->Set(buf), ConfigValueTooLong);
    const Brx& bufAfter = iLastChangeVal;
    TEST(bufAfter == bufBefore);
}


// SuiteConfigManager

/*
 * Note: SerialisedMap is not tested, as ConfigManager is such a thin wrapper
 * around it that all the test cases present here would just be duplicated.
 * These tests essentially test SerialisedMap anyway; just proxied through
 * ConfigManager.
 */

const TUint SuiteConfigManager::kChoice1 = 0;
const TUint SuiteConfigManager::kChoice2 = 1;
const TUint SuiteConfigManager::kChoice3 = 2;
const Brn SuiteConfigManager::kText1("abcdefghijklmnopqrstuvwxyz");
const Brn SuiteConfigManager::kText2("zyxwvutsrqponmlkjihgfedcba");
const Brn SuiteConfigManager::kIdNum1("cv.num.1");
const Brn SuiteConfigManager::kIdNum2("cv.num.2");
const Brn SuiteConfigManager::kIdChoice1("cv.choice.1");
const Brn SuiteConfigManager::kIdChoice2("cv.choice.2");
const Brn SuiteConfigManager::kIdText1("cv.text.1");
const Brn SuiteConfigManager::kIdText2("cv.text.2");

SuiteConfigManager::SuiteConfigManager()
    : SuiteUnitTest("SuiteConfigManager")
{
    // Creating different instances of SuiteConfigManager for each of
    // ConfigNum, ConfigChoice and ConfigText would end up in a lot of boilerplate code.
    // Just group functions for each val class in a single generic unit test
    // for each type of ConfigManager function to maintain clarity and
    // small test size.
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestClose));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestAdd));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestAddDuplicate));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestHasNoVals));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestHasValidId));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestHasInvalidId));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestHasMultiple));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestGetNoVals));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestGetValidId));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestGetInvalidId));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestGetMultiple));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestReadStoreValExists));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestReadNoStoreValExists));
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestWrite));
}

void SuiteConfigManager::Setup()
{
    iStore = new ConfigRamStore();
    iConfigManager = new ConfigManager(*iStore);
    iNum1 = new ConfigNum(*iConfigManager, kIdNum1, kMinNum, kMaxNum, kMinNum);
    iChoices.push_back(kChoice1);
    iChoices.push_back(kChoice2);
    iChoices.push_back(kChoice3);
    iChoice1 = new ConfigChoice(*iConfigManager, kIdChoice1, iChoices, kChoiceDefault);
    iText1 = new ConfigText(*iConfigManager, kIdText1, kMaxText, kText1);
}

void SuiteConfigManager::TearDown()
{
    delete iNum1;
    delete iChoice1;
    delete iText1;
    delete iConfigManager;
    delete iStore;
    iChoices.clear();
}

void SuiteConfigManager::NotifyChangedNum(TInt /*aVal*/)
{
}

void SuiteConfigManager::NotifyChangedChoice(TUint /*aVal*/)
{
}

void SuiteConfigManager::NotifyChangedText(const Brx& /*aVal*/)
{
}

void SuiteConfigManager::TestClose()
{
    // test that ConfigManager ASSERTs when attempting to add a value
    // after it has been closed
    iConfigManager->Close();
    TEST_THROWS(ConfigNum num(*iConfigManager, kIdNum2, kMinNum, kMaxNum, kMinNum+1), AssertionFailed);
    TEST_THROWS(ConfigChoice choice(*iConfigManager, kIdChoice2, iChoices, kChoiceDefault+1), AssertionFailed);
    TEST_THROWS(ConfigText text(*iConfigManager, kIdText2, kMaxText, kText2), AssertionFailed);
}

void SuiteConfigManager::TestAdd()
{
    // completion of this test without errors suggests adding works
    // Has() and Get() are tested in their own unit tests.
    ConfigNum num(*iConfigManager, kIdNum2, kMinNum, kMaxNum, kMinNum+1);
    ConfigChoice choice(*iConfigManager, kIdChoice2, iChoices, kChoiceDefault+1);
    ConfigText text(*iConfigManager, kIdText2, kMaxText, kText2);
}

void SuiteConfigManager::TestAddDuplicate()
{
    // test that an exception is throws if an attempt to add a ConfigVal with
    // the same ID is made twice
    TEST_THROWS(iConfigManager->Add(*iNum1), ConfigIdExists);
    TEST_THROWS(iConfigManager->Add(*iChoice1), ConfigIdExists);
    TEST_THROWS(iConfigManager->Add(*iText1), ConfigIdExists);

    // attempt to add a ConfigChoice with same ID as existing ConfigNum - should fail
    TEST_THROWS(iConfigManager->Add(*iChoice1), ConfigIdExists);
}

void SuiteConfigManager::TestHasNoVals()
{
    // test that calling Has() when no values are added returns false
    ConfigRamStore store;
    ConfigManager configManager(store);
    TEST(configManager.HasNum(kIdNum1) == false);
    TEST(configManager.HasChoice(kIdChoice1) == false);
    TEST(configManager.HasText(kIdText1) == false);
}

void SuiteConfigManager::TestHasValidId()
{
    // test Has() returns true when a given ID exists
    TEST(iConfigManager->HasNum(kIdNum1) == true);
    TEST(iConfigManager->HasChoice(kIdChoice1) == true);
    TEST(iConfigManager->HasText(kIdText1) == true);
}

void SuiteConfigManager::TestHasInvalidId()
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
}

void SuiteConfigManager::TestHasMultiple()
{
    // test adding multiple values and calling Has() on the IDs

    // test ConfigNum
    ConfigNum num(*iConfigManager, kIdNum2, kMinNum, kMaxNum, kMinNum+1);
    TEST(iConfigManager->HasNum(kIdNum1) == true);
    TEST(iConfigManager->HasNum(kIdNum2) == true);

    // test ConfigChoice
    ConfigChoice choice(*iConfigManager, kIdChoice2, iChoices, kChoiceDefault+1);
    TEST(iConfigManager->HasChoice(kIdChoice1) == true);
    TEST(iConfigManager->HasChoice(kIdChoice2) == true);

    // test ConfigText
    ConfigText text(*iConfigManager, kIdText2, kMaxText, kText2);
    TEST(iConfigManager->HasText(kIdText1) == true);
    TEST(iConfigManager->HasText(kIdText2) == true);
}

void SuiteConfigManager::TestGetNoVals()
{
    // test that Get() fails with an assertion when no values are present
    ConfigRamStore store;
    ConfigManager configManager(store);
    TEST_THROWS(configManager.GetNum(kIdNum1), AssertionFailed);
    TEST_THROWS(configManager.GetChoice(kIdChoice1), AssertionFailed);
    TEST_THROWS(configManager.GetText(kIdText1), AssertionFailed);
}

void SuiteConfigManager::TestGetValidId()
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
}

void SuiteConfigManager::TestGetInvalidId()
{
    // test that Get() causes an assertion when ID is not present
    TEST_THROWS(iConfigManager->GetNum(kIdNum2), AssertionFailed);
    TEST_THROWS(iConfigManager->GetChoice(kIdChoice2), AssertionFailed);
    TEST_THROWS(iConfigManager->GetText(kIdText2), AssertionFailed);

    // try call HasChoice() with the ID of ConfigNum
    TEST_THROWS(iConfigManager->GetChoice(kIdNum1), AssertionFailed);
}

void SuiteConfigManager::TestGetMultiple()
{
    // test adding multiple values and calling Get() on the IDs

    // test ConfigNum
    ConfigNum num(*iConfigManager, kIdNum2, kMinNum, kMaxNum, kMinNum+1);
    ConfigNum& num1 = iConfigManager->GetNum(kIdNum1);
    TEST(num1 == *iNum1);
    ConfigNum& num2 = iConfigManager->GetNum(kIdNum2);
    TEST(num2 == num);

    // test ConfigChoice
    ConfigChoice choice(*iConfigManager, kIdChoice2, iChoices, kChoiceDefault+1);
    ConfigChoice& choice1 = iConfigManager->GetChoice(kIdChoice1);
    TEST(choice1 == *iChoice1);
    ConfigChoice& choice2 = iConfigManager->GetChoice(kIdChoice2);
    TEST(choice2 == choice);

    // test ConfigText
    ConfigText text(*iConfigManager, kIdText2, kMaxText, kText2);
    ConfigText& text1 = iConfigManager->GetText(kIdText1);
    TEST(text1 == *iText1);
    ConfigText& text2 = iConfigManager->GetText(kIdText2);
    TEST(text2 == text);
}

void SuiteConfigManager::TestReadStoreValExists()
{
    // test that reading from a value already in store causes store value to be
    // returned rather than default val.
    Bwh buf(kMaxText);
    iConfigManager->FromStore(kIdText1, buf, kText2);
    TEST(buf == kText1);

    // check default value hasn't been written to store as a side-effect
    buf.SetBytes(0);
    iStore->Read(kIdText1, buf);
    TEST(buf == kText1);
}

void SuiteConfigManager::TestReadNoStoreValExists()
{
    // test that reading a value not in store causes default value to be
    // returned, and written out to store.
    Bwh buf(kMaxText);

    try { // check key isn't already in store
        iStore->Read(kIdText2, buf);
        ASSERTS();
    }
    catch (StoreKeyNotFound&) {}

    iConfigManager->FromStore(kIdText2, buf, kText2);
    TEST(buf == kText2);

    // check value has been written to store
    buf.SetBytes(0);
    iStore->Read(kIdText2, buf);
    TEST(buf == kText2);
}

void SuiteConfigManager::TestWrite()
{
    // test that writing a value via ConfigManager results in value
    // being written to store.
    Bwh buf(kMaxText);
    iConfigManager->ToStore(kIdText1, kText2);
    iStore->Read(kIdText1, buf);
    TEST(buf == kText2);
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
    
    // try update with same values again
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
    runner.Add(new SuiteConfigManager());
    runner.Add(new SuiteRamStore());
    runner.Run();
}
