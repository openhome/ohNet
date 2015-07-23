#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/Tests/ConfigRamStore.h>

#include <climits>

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
    void Setup() override;
    void TearDown() override;
protected:
    virtual void NotifyChanged(KeyValuePair<T>& aKvp);
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
    void Setup() override;
    void TearDown() override;
private:
    void TestNoSubscriptions();
    void TestAddRemoveSubscription();
    void TestAddRemoveMultipleSubscriptions();
    void TestUnsubscribeInvalidId();
private:
    ConfigVal<TInt>* iConfigVal;
};

class TestHelperWriter : public IWriter, public INonCopyable
{
public:
    TestHelperWriter(Bwx& aBuf);
public: // from IWriter
    void Write(TByte aValue) override;
    void Write(const Brx& aBuffer) override;
    void WriteFlush() override;
private:
    Bwx& iBuf;
};

class SuiteConfigNum : public SuiteCVNotify<TInt>
{
public:
    SuiteConfigNum();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:  // from SuiteCVNotify
    void NotifyChanged(ConfigNum::KvpNum& aKvp) override;
private:
    TInt IntFromStore(const Brx& aKey);
    void TestInternalFunctorNotCalledAtConstruction();
    void TestKeyStored();
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
    void TestSerialise();
    void TestSerialiseMaxLengthNegative();
    void TestSerialiseMaxLengthPositive();
    void TestDeserialiseUpdate();
    void TestDeserialiseNoUpdate();
    void TestDeserialiseOutOfRange();
    void TestDeserialiseInvalid();
private:
    static const TInt kMin = -1;
    static const TInt kMax = 2;
    static const TInt kVal = 1;
    static const TInt kIntMin = INT_MIN;
    static const TInt kIntMax = INT_MAX;
    static const TUint kIntMaxLength = 11;
    ConfigNum* iConfigVal;
    TInt iLastChangeVal;
};

class SuiteConfigChoice : public SuiteCVNotify<TUint>
{
public:
    SuiteConfigChoice();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:  // from SuiteCVNotify
    void NotifyChanged(ConfigChoice::KvpChoice& aKvp) override;
private:
    TUint UintFromStore(const Brx& aKey);
    void TestInternalFunctorNotCalledAtConstruction();
    void TestKeyStored();
    void TestSubscription();
    void TestValueFromStore();
    void TestValueWrittenToStore();
    void TestAdd();
    void TestGetNoChoices();
    void TestSetUpdate();
    void TestSetNoUpdate();
    void TestSetNoSuchChoice();
    void TestSerialise();
    void TestSerialiseMaxLength();
    void TestDeserialiseUpdate();
    void TestDeserialiseNoUpdate();
    void TestDeserialiseNoSuchChoice();
    void TestDeserialiseInvalid();
private:
    static const TUint kDefault = 1000;
    static const TUint kUintMin;
    static const TUint kUintMax;
    static const TUint kChoice1;
    static const TUint kChoice2;
    static const TUint kChoice3;
    static const TUint kUintMaxLength = 10;
    ConfigChoice* iConfigVal;
    TUint iLastChangeVal;
};

class SuiteConfigText : public SuiteCVNotify<const Brx&>
{
public:
    SuiteConfigText();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:  // from SuiteCVNotify
    void NotifyChanged(ConfigText::KvpText& aKvp) override;
private:
    void TestInternalFunctorNotCalledAtConstruction();
    void TestKeyStored();
    void TestSubscription();
    void TestValueFromStore();
    void TestValueWrittenToStore();
    void TestMaxLength();
    void TestSetUpdate();
    void TestSetNoUpdate();
    void TestSetValueTooLong();
    void TestSerialise();
    void TestSerialiseMaxLength();
    void TestDeserialiseUpdate();
    void TestDeserialiseNoUpdate();
    void TestDeserialiseValueTooLong();
private:
    static const TUint kMaxLength = 100;
    static const Brn kDefault;
    ConfigText* iConfigVal;
    Bws<kMaxLength> iLastChangeVal;
};

class SuiteSerialisedMap : public SuiteUnitTest
{
public:
    SuiteSerialisedMap();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void TestMapKeyPersists();
private:
    SerialisedMap<TUint>* iMapUint;
};

class SuiteConfigManager : public SuiteUnitTest
{
public:
    SuiteConfigManager();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void NotifyChangedNum(TInt aVal);
    void NotifyChangedChoice(TUint aVal);
    void NotifyChangedText(const Brx& aVal);
    void TestOpen();
    void TestAdd();
    void TestAddDuplicate();
    void TestHasNoVals();
    void TestHasValidKey();
    void TestHasInvalidKey();
    void TestHasMultiple();
    void TestGetNoVals();
    void TestGetValidKey();
    void TestGetInvalidKey();
    void TestGetMultiple();
    void TestReadStoreValExists();
    void TestReadNoStoreValExists();
    void TestWrite();
    void TestDumpToStore();
private:
    static const TUint kMaxNumBytes = 10;
    static const TInt kMinNum = 0;
    static const TInt kMaxNum = 2;
    static const TUint kMaxChoiceBytes = 10;
    static const TUint kChoiceDefault = 0;
    static const TUint kChoice1;
    static const TUint kChoice2;
    static const TUint kChoice3;
    static const TUint kMaxTextBytes = 26;
    static const Brn kText1;
    static const Brn kText2;
    static const Brn kKeyNum1;
    static const Brn kKeyNum2;
    static const Brn kKeyChoice1;
    static const Brn kKeyChoice2;
    static const Brn kKeyText1;
    static const Brn kKeyText2;
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
    void Setup() override;
    void TearDown() override;
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

template <class T> void SuiteCVNotify<T>::NotifyChanged(KeyValuePair<T>& /*aKvp*/)
{
    iChangedCount++;
}


// SuiteCVSubscriptions

SuiteCVSubscriptions::SuiteCVSubscriptions()
    : SuiteCVNotify("SuiteCVSubscriptions")
{
    AddTest(MakeFunctor(*this, &SuiteCVSubscriptions::TestNoSubscriptions), "TestNoSubscriptions");
    AddTest(MakeFunctor(*this, &SuiteCVSubscriptions::TestAddRemoveSubscription), "TestAddRemoveSubscription");
    AddTest(MakeFunctor(*this, &SuiteCVSubscriptions::TestAddRemoveMultipleSubscriptions), "TestAddRemoveMultipleSubscriptions");
    AddTest(MakeFunctor(*this, &SuiteCVSubscriptions::TestUnsubscribeInvalidId), "TestUnsubscribeInvalidId");
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
    iConfigVal = nullptr;
}

void SuiteCVSubscriptions::TestAddRemoveSubscription()
{
    // test adding and removing a single subscription - will assert at
    // destruction if error
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigNum(*this, &SuiteCVSubscriptions::NotifyChanged));
    TEST(id != 0);
    iConfigVal->Unsubscribe(id);
    delete iConfigVal;
    iConfigVal = nullptr;
}

void SuiteCVSubscriptions::TestAddRemoveMultipleSubscriptions()
{
    // test adding and removing multiple (extra) subscriptions (and test id
    // ordering) - will assert at destruction if error

    // Keys should start at 1, and there should be 2 internal subscribers at construction
    TUint id1 = iConfigVal->Subscribe(MakeFunctorConfigNum(*this, &SuiteCVSubscriptions::NotifyChanged));

    TEST(id1 == 2);
    TUint id2 = iConfigVal->Subscribe(MakeFunctorConfigNum(*this, &SuiteCVSubscriptions::NotifyChanged));
    TEST(id2 == 3);
    iConfigVal->Unsubscribe(id1);
    iConfigVal->Unsubscribe(id2);
    delete iConfigVal;
    iConfigVal = nullptr;
}

void SuiteCVSubscriptions::TestUnsubscribeInvalidId()
{
    // test that trying to unsubscribe using an invalid id does nothing
    iConfigVal->Unsubscribe(ConfigManager::kSubscriptionIdInvalid);
    iConfigVal->Unsubscribe(999);
}


// TestHelperWriter

TestHelperWriter::TestHelperWriter(Bwx& aBuf)
    : iBuf(aBuf)
{
}

void TestHelperWriter::Write(TByte aValue)
{
    ASSERT(iBuf.Bytes() < iBuf.MaxBytes());
    iBuf.Append(aValue);
}

void TestHelperWriter::Write(const Brx& aBuffer)
{
    ASSERT(iBuf.MaxBytes()-iBuf.Bytes() >= aBuffer.Bytes());
    iBuf.Append(aBuffer);
}

void TestHelperWriter::WriteFlush()
{
}


// SuiteConfigNum

SuiteConfigNum::SuiteConfigNum()
    : SuiteCVNotify("SuiteConfigNum")
{
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestInternalFunctorNotCalledAtConstruction), "TestInternalFunctorNotCalledAtConstruction");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestKeyStored), "TestKeyStored");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSubscription), "TestSubscription");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestInvalidRange), "TestInvalidRange");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestValueOutOfRangeConstructor), "TestValueOutOfRangeConstructor");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestValueFromStore), "TestValueFromStore");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestValueWrittenToStore), "TestValueWrittenToStore");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestGetMin), "TestGetMin");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestGetMax), "TestGetMax");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSetUpdate), "TestSetUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSetNoUpdate), "TestSetNoUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSetValueOutOfRange), "TestSetValueOutOfRange");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSerialise), "TestSerialise");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSerialiseMaxLengthNegative), "TestSerialiseMaxLengthNegative");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestSerialiseMaxLengthPositive), "TestSerialiseMaxLengthPositive");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestDeserialiseUpdate), "TestDeserialiseUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestDeserialiseNoUpdate), "TestDeserialiseNoUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestDeserialiseOutOfRange), "TestDeserialiseOutOfRange");
    AddTest(MakeFunctor(*this, &SuiteConfigNum::TestDeserialiseInvalid), "TestDeserialiseInvalid");
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

void SuiteConfigNum::NotifyChanged(ConfigNum::KvpNum& aKvp)
{
    SuiteCVNotify::NotifyChanged(aKvp);
    iLastChangeVal = aKvp.Value();
}

TInt SuiteConfigNum::IntFromStore(const Brx& aKey)
{
    Bws<sizeof(TInt)> buf;
    iStore->Read(aKey, buf);
    TInt val = Converter::BeUint32At(buf, 0);
    return val;
}

void SuiteConfigNum::TestInternalFunctorNotCalledAtConstruction()
{
    // there is an internal write functor - check value is not written to store
    // when default
    TEST_THROWS(IntFromStore(kKey), StoreKeyNotFound);
}

void SuiteConfigNum::TestKeyStored()
{
    // test that the id is stored internally; not just wrapping a value
    static const Brn keyConst("temporary.id");
    Bwh keyChangeable(keyConst);
    ConfigNum num(*iConfigManager, keyChangeable, kMin, kMax, kVal);
    TEST(num.Key() == keyConst);
    keyChangeable.SetBytes(0);
    TEST(num.Key() == keyConst);
}

void SuiteConfigNum::TestSubscription()
{
    // test that functor is called back at time of subscription
    TUint changedCount = iChangedCount;
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigNum(*this, &SuiteConfigNum::NotifyChanged));

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
    WriterBuffer writerBuf(valBuf);
    WriterBinary writerBin(writerBuf);
    writerBin.WriteUint32Be(storeVal);
    iStore->Write(key, valBuf);
    ConfigNum num(*iConfigManager, key, kMin, kMax, kVal);
    TUint id = num.Subscribe(MakeFunctorConfigNum(*this, &SuiteConfigNum::NotifyChanged));

    // test value in store hasn't been overwritten
    TEST(IntFromStore(key) == storeVal);
    // test retrieved value is correct
    TEST(iLastChangeVal == storeVal);
    num.Unsubscribe(id);
}

void SuiteConfigNum::TestValueWrittenToStore()
{
    // test that the default value has not been written out to store at creation
    TEST_THROWS(IntFromStore(kKey), StoreKeyNotFound);

    // now change the value
    TInt newVal = kVal+1;
    iConfigVal->Set(newVal);

    // check the change has been written to store
    TEST(IntFromStore(kKey) == newVal);
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
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigNum(*this, &SuiteConfigNum::NotifyChanged));
    TUint changedCount = iChangedCount;
    iConfigVal->Set(newVal);

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

    TUint id = iConfigVal->Subscribe(MakeFunctorConfigNum(*this, &SuiteConfigNum::NotifyChanged));
    TUint changedCount = iChangedCount;
    iConfigVal->Set(iLastChangeVal);

    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == kVal);

    // test still no value in store
    TEST_THROWS(IntFromStore(kKey), StoreKeyNotFound);

    // assign a new value that will be written to store
    TInt newVal = kVal+1;
    iConfigVal->Set(newVal);
    TEST(iChangedCount == changedCount+1);
    TEST(iLastChangeVal == newVal);
    // test that value has been written out to store
    TEST(IntFromStore(kKey) == newVal);

    // try set the same value again
    changedCount = iChangedCount;
    iConfigVal->Set(iLastChangeVal);
    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == newVal);

    // test value in store hasn't changed
    TEST(IntFromStore(kKey) == newVal);

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

void SuiteConfigNum::TestSerialise()
{
    Bws<kIntMaxLength> buf;
    TestHelperWriter writer(buf);
    iConfigVal->Serialise(writer);

    TInt val = Ascii::Int(buf);
    TEST(val == kVal);
}

void SuiteConfigNum::TestSerialiseMaxLengthNegative()
{
    const Brn key("conf.num.2");
    Bws<kIntMaxLength> buf;
    ConfigNum num(*iConfigManager, key, kIntMin, kIntMax, kIntMin);

    TestHelperWriter writer(buf);
    num.Serialise(writer);
    TInt val = Ascii::Int(buf);
    TEST(val == kIntMin);
}

void SuiteConfigNum::TestSerialiseMaxLengthPositive()
{
    const Brn key("conf.num.2");
    Bws<kIntMaxLength> buf;
    ConfigNum num(*iConfigManager, key, kIntMin, kIntMax, kIntMax);

    TestHelperWriter writer(buf);
    num.Serialise(writer);
    TInt val = Ascii::Int(buf);
    TEST(val == kIntMax);
}

void SuiteConfigNum::TestDeserialiseUpdate()
{
    TInt newVal = kVal+1;
    Bws<kIntMaxLength> buf;
    Ascii::AppendDec(buf, newVal);

    TUint id = iConfigVal->Subscribe(MakeFunctorConfigNum(*this, &SuiteConfigNum::NotifyChanged));
    TUint changedCount = iChangedCount;
    iConfigVal->Deserialise(buf);

    TEST(iChangedCount == changedCount+1);
    TEST(iLastChangeVal == newVal);
    // test that value has been written out to store
    TEST(IntFromStore(kKey) == newVal);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigNum::TestDeserialiseNoUpdate()
{
    Bws<kIntMaxLength> buf;
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigNum(*this, &SuiteConfigNum::NotifyChanged));
    Ascii::AppendDec(buf, iLastChangeVal);
    TUint changedCount = iChangedCount;
    iConfigVal->Deserialise(buf);

    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == kVal);

    // test still no value in store
    TEST_THROWS(IntFromStore(kKey), StoreKeyNotFound);

    // assign a new value that will be written to store
    TInt newVal = kVal+1;
    buf.SetBytes(0);
    Ascii::AppendDec(buf, newVal);
    iConfigVal->Deserialise(buf);
    TEST(iChangedCount == changedCount+1);
    TEST(iLastChangeVal == newVal);
    // test that value has been written out to store
    TEST(IntFromStore(kKey) == newVal);

    // try set the same value again
    changedCount = iChangedCount;
    iConfigVal->Deserialise(buf);
    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == newVal);

    // test value in store hasn't changed
    TEST(IntFromStore(kKey) == newVal);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigNum::TestDeserialiseOutOfRange()
{
    Bws<kIntMaxLength> bufMaxOutOfRange;
    Bws<kIntMaxLength> bufMinOutOfRange;
    Ascii::AppendDec(bufMaxOutOfRange, kMax+1);
    Ascii::AppendDec(bufMinOutOfRange, kMin-1);

    TInt valBefore = iLastChangeVal;
    TEST_THROWS(iConfigVal->Deserialise(bufMaxOutOfRange), ConfigValueOutOfRange);
    TInt valAfter = iLastChangeVal;
    TEST(valAfter == valBefore);

    valBefore = iLastChangeVal;
    TEST_THROWS(iConfigVal->Deserialise(bufMinOutOfRange), ConfigValueOutOfRange);
    valAfter = iLastChangeVal;
    TEST(valAfter == valBefore);
}

void SuiteConfigNum::TestDeserialiseInvalid()
{
    Bws<kIntMaxLength> buf;
    buf.Append(Brn("abcd"));

    TInt valBefore = iLastChangeVal;
    TEST_THROWS(iConfigVal->Deserialise(buf), ConfigNotANumber);
    TInt valAfter = iLastChangeVal;
    TEST(valAfter == valBefore);
}


// SuiteConfigChoice

const TUint SuiteConfigChoice::kUintMin = 0x00000000;
const TUint SuiteConfigChoice::kUintMax = UINT_MAX;
const TUint SuiteConfigChoice::kChoice1 = 1000;
const TUint SuiteConfigChoice::kChoice2 = 1001;
const TUint SuiteConfigChoice::kChoice3 = 1002;

SuiteConfigChoice::SuiteConfigChoice()
    : SuiteCVNotify("SuiteConfigChoice")
{
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestInternalFunctorNotCalledAtConstruction), "TestInternalFunctorNotCalledAtConstruction");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestKeyStored), "TestKeyStored");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSubscription), "TestSubscription");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestValueFromStore), "TestValueFromStore");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestValueWrittenToStore), "TestValueWrittenToStore");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestAdd), "TestAdd");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestGetNoChoices), "TestGetNoChoices");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSetUpdate), "TestSetUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSetNoUpdate), "TestSetNoUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSetNoSuchChoice), "TestSetNoSuchChoice");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSerialise), "TestSerialise");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestSerialiseMaxLength), "TestSerialiseMaxLength");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestDeserialiseUpdate), "TestDeserialiseUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestDeserialiseNoUpdate), "TestDeserialiseNoUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestDeserialiseNoSuchChoice), "TestDeserialiseNoSuchChoice");
    AddTest(MakeFunctor(*this, &SuiteConfigChoice::TestDeserialiseInvalid), "TestDeserialiseInvalid");
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

void SuiteConfigChoice::NotifyChanged(ConfigChoice::KvpChoice& aKvp)
{
    SuiteCVNotify::NotifyChanged(aKvp);
    iLastChangeVal = aKvp.Value();
}

TUint SuiteConfigChoice::UintFromStore(const Brx& aKey)
{
    Bws<sizeof(TUint)> buf;
    iStore->Read(aKey, buf);
    TUint val = Converter::BeUint32At(buf, 0);
    return val;
}

void SuiteConfigChoice::TestInternalFunctorNotCalledAtConstruction()
{
    // there is an internal write functor - check value is not written to store
    // when default
    TEST_THROWS(UintFromStore(kKey), StoreKeyNotFound);
}

void SuiteConfigChoice::TestKeyStored()
{
    // test that the id is stored internally; not just wrapping a value
    static const Brn keyConst("temporary.id");
    Bwh keyChangeable(keyConst);
    std::vector<TUint> choices;
    choices.push_back(kChoice1);
    choices.push_back(kChoice2);
    choices.push_back(kChoice3);

    ConfigChoice choice(*iConfigManager, keyChangeable, choices, kDefault);
    TEST(choice.Key() == keyConst);
    keyChangeable.SetBytes(0);
    TEST(choice.Key() == keyConst);
}

void SuiteConfigChoice::TestSubscription()
{
    // test that functor is called back at time of subscription
    TUint changedCount = iChangedCount;
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigChoice(*this, &SuiteConfigChoice::NotifyChanged));

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
    WriterBuffer writerBuf(valBuf);
    WriterBinary writerBin(writerBuf);
    writerBin.WriteUint32Be(storeVal);
    iStore->Write(key, valBuf);

    std::vector<TUint> choices;
    choices.push_back(kChoice1);
    choices.push_back(kChoice2);
    choices.push_back(kChoice3);
    ConfigChoice choice(*iConfigManager, key, choices, kDefault);
    TUint id = choice.Subscribe(MakeFunctorConfigChoice(*this, &SuiteConfigChoice::NotifyChanged));

    // test value in store hasn't been overwritten
    TEST(UintFromStore(key) == storeVal);
    // test retrieved value is correct
    TEST(iLastChangeVal == storeVal);
    choice.Unsubscribe(id);
}

void SuiteConfigChoice::TestValueWrittenToStore()
{
    // test that the default value has not been written out to store at creation
    TEST_THROWS(UintFromStore(kKey), StoreKeyNotFound);

    // now change the value
    TUint newVal = kDefault+1;
    iConfigVal->Set(newVal);

    // check the change has been written to store
    TEST(UintFromStore(kKey) == newVal);
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
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigChoice(*this, &SuiteConfigChoice::NotifyChanged));
    TUint changedCount = iChangedCount;
    iConfigVal->Set(newVal);

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
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigChoice(*this, &SuiteConfigChoice::NotifyChanged));
    TUint changedCount = iChangedCount;
    iConfigVal->Set(kDefault);

    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == kDefault);

    // test still no value in store
    TEST_THROWS(UintFromStore(kKey), StoreKeyNotFound);

    // assign a new value that will be written to store
    TUint newVal = kDefault+1;
    iConfigVal->Set(newVal);
    TEST(iChangedCount == changedCount+1);
    TEST(iLastChangeVal == newVal);
    // test that value has been written out to store
    TEST(UintFromStore(kKey) == newVal);

    // try set the same value again
    changedCount = iChangedCount;
    iConfigVal->Set(iLastChangeVal);
    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == newVal);

    // test value in store hasn't changed
    TEST(UintFromStore(kKey) == newVal);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigChoice::TestSetNoSuchChoice()
{
    // test that attempting to set ConfigChoice to an invalid choice results in
    // an exception
    TUint selectedBefore = iLastChangeVal;
    TEST_THROWS(iConfigVal->Set(kDefault-1), ConfigInvalidSelection);
    TUint selectedAfter = iLastChangeVal;
    TEST(selectedAfter == selectedBefore);
}

void SuiteConfigChoice::TestSerialise()
{
    Bws<kUintMaxLength> buf;
    TestHelperWriter writer(buf);
    iConfigVal->Serialise(writer);

    TUint val = Ascii::Uint(buf);
    TEST(val == kDefault);
}

void SuiteConfigChoice::TestSerialiseMaxLength()
{
    const Brn key("conf.choice.2");
    Bws<kUintMaxLength> buf;

    std::vector<TUint> choices;
    choices.push_back(kUintMin);
    choices.push_back(kUintMax);
    ConfigChoice choice(*iConfigManager, key, choices, kUintMax);

    TestHelperWriter writer(buf);
    choice.Serialise(writer);
    TUint val = Ascii::Uint(buf);
    TEST(val == kUintMax);
}

void SuiteConfigChoice::TestDeserialiseUpdate()
{
    TUint newVal = kDefault+1;
    Bws<kUintMaxLength> buf;
    Ascii::AppendDec(buf, newVal);

    TUint id = iConfigVal->Subscribe(MakeFunctorConfigChoice(*this, &SuiteConfigChoice::NotifyChanged));
    TUint changedCount = iChangedCount;
    iConfigVal->Deserialise(buf);

    TEST(iChangedCount == changedCount+1);
    TEST(iLastChangeVal == newVal);
    // test that value has been written out to store
    TEST(UintFromStore(kKey) == newVal);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigChoice::TestDeserialiseNoUpdate()
{
    Bws<kUintMaxLength> buf;
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigChoice(*this, &SuiteConfigChoice::NotifyChanged));
    Ascii::AppendDec(buf, iLastChangeVal);
    TUint changedCount = iChangedCount;
    iConfigVal->Deserialise(buf);

    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == kDefault);

    // test still no value in store
    TEST_THROWS(UintFromStore(kKey), StoreKeyNotFound);

    // assign a new value that will be written to store
    TUint newVal = kDefault+1;
    buf.SetBytes(0);
    Ascii::AppendDec(buf, newVal);
    iConfigVal->Deserialise(buf);
    TEST(iChangedCount == changedCount+1);
    TEST(iLastChangeVal == newVal);
    // test that value has been written out to store
    TEST(UintFromStore(kKey) == newVal);

    // try set the same value again
    changedCount = iChangedCount;
    iConfigVal->Deserialise(buf);
    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == newVal);

    // test value in store hasn't changed
    TEST(UintFromStore(kKey) == newVal);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigChoice::TestDeserialiseNoSuchChoice()
{
    Bws<kUintMaxLength> buf;
    Ascii::AppendDec(buf, kDefault-1);

    TUint selectedBefore = iLastChangeVal;
    TEST_THROWS(iConfigVal->Deserialise(buf), ConfigInvalidSelection);
    TUint selectedAfter = iLastChangeVal;
    TEST(selectedAfter == selectedBefore);
}

void SuiteConfigChoice::TestDeserialiseInvalid()
{
    Bws<kUintMaxLength> buf;
    buf.Append(Brn("abcd"));

    TUint valBefore = iLastChangeVal;
    TEST_THROWS(iConfigVal->Deserialise(buf), ConfigNotANumber);
    TUint valAfter = iLastChangeVal;
    TEST(valAfter == valBefore);
}


// SuiteConfigText

const Brn SuiteConfigText::kDefault("abcdefghijklmnopqrstuvwxyz");

SuiteConfigText::SuiteConfigText()
    : SuiteCVNotify("SuiteConfigText")
{
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestInternalFunctorNotCalledAtConstruction), "TestInternalFunctorNotCalledAtConstruction");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestKeyStored), "TestKeyStored");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSubscription), "TestSubscription");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestValueFromStore), "TestValueFromStore");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestValueWrittenToStore), "TestValueWrittenToStore");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestMaxLength), "TestMaxLength");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetUpdate), "TestSetUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetNoUpdate), "TestSetNoUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSetValueTooLong), "TestSetValueTooLong");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSerialise), "TestSerialise");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestSerialiseMaxLength), "TestSerialiseMaxLength");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestDeserialiseUpdate), "TestDeserialiseUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestDeserialiseNoUpdate), "TestDeserialiseNoUpdate");
    AddTest(MakeFunctor(*this, &SuiteConfigText::TestDeserialiseValueTooLong), "TestDeserialiseValueTooLong");
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

void SuiteConfigText::NotifyChanged(ConfigText::KvpText& aKvp)
{
    SuiteCVNotify::NotifyChanged(aKvp);
    iLastChangeVal.Replace(aKvp.Value());
}

void SuiteConfigText::TestInternalFunctorNotCalledAtConstruction()
{
    // there is an internal write functor - check value is not written to store
    // when default
    Bwh valBuf(kMaxLength);
    TEST_THROWS(iStore->Read(kKey, valBuf), StoreKeyNotFound);
}

void SuiteConfigText::TestKeyStored()
{
    // test that the id is stored internally; not just wrapping a value
    static const Brn keyConst("temporary.id");
    Bwh keyChangeable(keyConst);
    ConfigText text(*iConfigManager, keyChangeable, kMaxLength, kDefault);
    TEST(text.Key() == keyConst);
    keyChangeable.SetBytes(0);
    TEST(text.Key() == keyConst);
}

void SuiteConfigText::TestSubscription()
{
    // test that functor is called back at time of subscription
    TUint changedCount = iChangedCount;
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigText(*this, &SuiteConfigText::NotifyChanged));

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
    TUint id = text.Subscribe(MakeFunctorConfigText(*this, &SuiteConfigText::NotifyChanged));

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
    // test that the default value has not been written out to store at creation
    Bwh valBuf(kDefault.Bytes());
    TEST_THROWS(iStore->Read(kKey, valBuf), StoreKeyNotFound);

    // now change the value
    Brn newVal("zyxwvutsrqponmlkjihgfedcba");
    iConfigVal->Set(newVal);

    // check the change has been written to store
    iStore->Read(kKey, valBuf);
    TEST(valBuf == newVal);
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
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigText(*this, &SuiteConfigText::NotifyChanged));
    TUint changedCount = iChangedCount;
    iConfigVal->Set(newVal);

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
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigText(*this, &SuiteConfigText::NotifyChanged));
    TUint changedCount = iChangedCount;
    iConfigVal->Set(kDefault);
    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == kDefault);
    // test still no value in store
    Bwh valBuf(kMaxLength);
    TEST_THROWS(iStore->Read(kKey, valBuf), StoreKeyNotFound);
    iConfigVal->Unsubscribe(id);

    Brn text("zyxwvutsrqponmlkjihgfedcba");
    // set new val before then subscribing to changes
    iConfigVal->Set(text);
    changedCount = iChangedCount;
    id = iConfigVal->Subscribe(MakeFunctorConfigText(*this, &SuiteConfigText::NotifyChanged));
    changedCount = iChangedCount;
    // now attempt to set same value again
    iConfigVal->Set(text);
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

void SuiteConfigText::TestSerialise()
{
    Bws<kMaxLength> buf;
    TestHelperWriter writer(buf);
    iConfigVal->Serialise(writer);

    TEST(buf == kDefault);
}

void SuiteConfigText::TestSerialiseMaxLength()
{
    const Brn key("conf.text.2");
    const TUint maxLength = 52;
    Bws<maxLength> val;
    ASSERT(kDefault.Bytes()*2 == val.MaxBytes());
    val.Replace(kDefault);
    val.Append(kDefault);
    Bws<maxLength> buf;
    ConfigText text(*iConfigManager, key, maxLength, val);

    TestHelperWriter writer(buf);
    text.Serialise(writer);
    TEST(buf == val);
}

void SuiteConfigText::TestDeserialiseUpdate()
{
    Brn newVal("zyxwvutsrqponmlkjihgfedcba");
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigText(*this, &SuiteConfigText::NotifyChanged));
    TUint changedCount = iChangedCount;
    iConfigVal->Deserialise(newVal);

    TEST(iChangedCount == changedCount+1);
    TEST(iLastChangeVal == newVal);
    // test that value has been written out to store
    Bwh valBuf(kMaxLength);
    iStore->Read(kKey, valBuf);
    TEST(valBuf == newVal);

    iConfigVal->Unsubscribe(id);
}

void SuiteConfigText::TestDeserialiseNoUpdate()
{
    // test updating the default string, then test updating a string with
    // length > 0
    TUint id = iConfigVal->Subscribe(MakeFunctorConfigText(*this, &SuiteConfigText::NotifyChanged));
    TUint changedCount = iChangedCount;
    iConfigVal->Deserialise(kDefault);
    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == kDefault);
    // test still no value in store
    Bwh valBuf(kMaxLength);
    TEST_THROWS(iStore->Read(kKey, valBuf), StoreKeyNotFound);
    iConfigVal->Unsubscribe(id);

    Brn text("zyxwvutsrqponmlkjihgfedcba");
    // set new val before then subscribing to changes
    iConfigVal->Deserialise(text);
    changedCount = iChangedCount;
    id = iConfigVal->Subscribe(MakeFunctorConfigText(*this, &SuiteConfigText::NotifyChanged));
    changedCount = iChangedCount;
    // now attempt to set same value again
    iConfigVal->Deserialise(text);
    TEST(iChangedCount == changedCount);
    TEST(iLastChangeVal == text);
    // test value in store hasn't changed
    valBuf.SetBytes(0);
    iStore->Read(kKey, valBuf);
    TEST(valBuf == text);
    iConfigVal->Unsubscribe(id);
}

void SuiteConfigText::TestDeserialiseValueTooLong()
{
    Bws<kMaxLength+1> buf;
    buf.SetBytes(buf.MaxBytes());

    const Brx& bufBefore = iLastChangeVal;
    TEST_THROWS(iConfigVal->Deserialise(buf), ConfigValueTooLong);
    const Brx& bufAfter = iLastChangeVal;
    TEST(bufAfter == bufBefore);
}


// SuiteSerialisedMap
SuiteSerialisedMap::SuiteSerialisedMap()
    : SuiteUnitTest("SuiteSerialisedMap")
    , iMapUint(nullptr)
{
    AddTest(MakeFunctor(*this, &SuiteSerialisedMap::TestMapKeyPersists), "TestMapKeyPersists");
}

void SuiteSerialisedMap::Setup()
{
    iMapUint = new SerialisedMap<TUint>();
}

void SuiteSerialisedMap::TearDown()
{
    delete iMapUint;
}

void SuiteSerialisedMap::TestMapKeyPersists()
{
    // test that a key written into the internal map of ConfigManager persists
    // even when the original key is changed.
    Brh key("Test.Map.Key.Original");
    Bwh keyModifiable(key);
    TUint val = 0;

    iMapUint->Add(keyModifiable, val);
    TEST(iMapUint->Has(key) == true);

    // now modify the key for new entry and check it is not a reference that
    // has been stored in the map.
    keyModifiable.Replace("Test.Map.Key.New");
    TEST(iMapUint->Has(key) == true);
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
const Brn SuiteConfigManager::kKeyNum1("cv.num.1");
const Brn SuiteConfigManager::kKeyNum2("cv.num.2");
const Brn SuiteConfigManager::kKeyChoice1("cv.choice.1");
const Brn SuiteConfigManager::kKeyChoice2("cv.choice.2");
const Brn SuiteConfigManager::kKeyText1("cv.text.1");
const Brn SuiteConfigManager::kKeyText2("cv.text.2");

SuiteConfigManager::SuiteConfigManager()
    : SuiteUnitTest("SuiteConfigManager")
{
    // Creating different instances of SuiteConfigManager for each of
    // ConfigNum, ConfigChoice and ConfigText would end up in a lot of boilerplate code.
    // Just group functions for each val class in a single generic unit test
    // for each type of ConfigManager function to maintain clarity and
    // small test size.
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestOpen), "TestOpen");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestAdd), "TestAdd");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestAddDuplicate), "TestAddDuplicate");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestHasNoVals), "TestHasNoVals");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestHasValidKey), "TestHasValidKey");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestHasInvalidKey), "TestHasInvalidKey");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestHasMultiple), "TestHasMultiple");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestGetNoVals), "TestGetNoVals");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestGetValidKey), "TestGetValidKey");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestGetInvalidKey), "TestGetInvalidKey");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestGetMultiple), "TestGetMultiple");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestReadStoreValExists), "TestReadStoreValExists");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestReadNoStoreValExists), "TestReadNoStoreValExists");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestWrite), "TestWrite");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteConfigManager::TestDumpToStore), "TestDumpToStore");
}

void SuiteConfigManager::Setup()
{
    iStore = new ConfigRamStore();
    iConfigManager = new ConfigManager(*iStore);
    iNum1 = new ConfigNum(*iConfigManager, kKeyNum1, kMinNum, kMaxNum, kMinNum);
    iChoices.push_back(kChoice1);
    iChoices.push_back(kChoice2);
    iChoices.push_back(kChoice3);
    iChoice1 = new ConfigChoice(*iConfigManager, kKeyChoice1, iChoices, kChoiceDefault);
    iText1 = new ConfigText(*iConfigManager, kKeyText1, kMaxTextBytes, kText1);
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

void SuiteConfigManager::TestOpen()
{
    // test that ConfigManager ASSERTs when attempting to add a value
    // after it has been opened
    iConfigManager->Open();
    TEST_THROWS(ConfigNum num(*iConfigManager, kKeyNum2, kMinNum, kMaxNum, kMinNum+1), AssertionFailed);
    TEST_THROWS(ConfigChoice choice(*iConfigManager, kKeyChoice2, iChoices, kChoiceDefault+1), AssertionFailed);
    TEST_THROWS(ConfigText text(*iConfigManager, kKeyText2, kMaxTextBytes, kText2), AssertionFailed);
}

void SuiteConfigManager::TestAdd()
{
    // completion of this test without errors suggests adding works
    // Has() and Get() are tested in their own unit tests.
    ConfigNum num(*iConfigManager, kKeyNum2, kMinNum, kMaxNum, kMinNum+1);
    ConfigChoice choice(*iConfigManager, kKeyChoice2, iChoices, kChoiceDefault+1);
    ConfigText text(*iConfigManager, kKeyText2, kMaxTextBytes, kText2);
}

void SuiteConfigManager::TestAddDuplicate()
{
    // test that an exception is throws if an attempt to add a ConfigVal with
    // the same key is made twice
    TEST_THROWS(iConfigManager->Add(*iNum1), ConfigKeyExists);
    TEST_THROWS(iConfigManager->Add(*iChoice1), ConfigKeyExists);
    TEST_THROWS(iConfigManager->Add(*iText1), ConfigKeyExists);

    // attempt to add a ConfigChoice with same key as existing ConfigNum - should fail
    TEST_THROWS(iConfigManager->Add(*iChoice1), ConfigKeyExists);
}

void SuiteConfigManager::TestHasNoVals()
{
    // test that calling Has() when no values are added returns false
    ConfigRamStore store;
    ConfigManager configManager(store);
    TEST(configManager.HasNum(kKeyNum1) == false);
    TEST(configManager.HasChoice(kKeyChoice1) == false);
    TEST(configManager.HasText(kKeyText1) == false);

    TEST(configManager.Has(kKeyNum1) == false);
    TEST(configManager.Has(kKeyChoice1) == false);
    TEST(configManager.Has(kKeyText1) == false);
}

void SuiteConfigManager::TestHasValidKey()
{
    // test Has() returns true when a given key exists
    TEST(iConfigManager->HasNum(kKeyNum1) == true);
    TEST(iConfigManager->HasChoice(kKeyChoice1) == true);
    TEST(iConfigManager->HasText(kKeyText1) == true);

    // test generic Has()
    TEST(iConfigManager->Has(kKeyNum1) == true);
    TEST(iConfigManager->Has(kKeyChoice1) == true);
    TEST(iConfigManager->Has(kKeyText1) == true);
}

void SuiteConfigManager::TestHasInvalidKey()
{
    // test Has() returns false when keys are present, but not the given key

    // test ConfigNum
    TEST(iConfigManager->HasNum(kKeyNum2) == false);

    // test ConfigChoice
    TEST(iConfigManager->HasChoice(kKeyChoice2) == false);

    // test ConfigText
    TEST(iConfigManager->HasText(kKeyText2) == false);

    // try call HasChoice() with the key of ConfigNum
    TEST(iConfigManager->HasChoice(kKeyNum1) == false);

    // test generic Has()
    TEST(iConfigManager->Has(kKeyNum2) == false);
    TEST(iConfigManager->Has(kKeyChoice2) == false);
    TEST(iConfigManager->Has(kKeyText2) == false);
}

void SuiteConfigManager::TestHasMultiple()
{
    // test adding multiple values and calling Has() on the keys

    // test ConfigNum
    ConfigNum num(*iConfigManager, kKeyNum2, kMinNum, kMaxNum, kMinNum+1);
    TEST(iConfigManager->HasNum(kKeyNum1) == true);
    TEST(iConfigManager->HasNum(kKeyNum2) == true);

    // test ConfigChoice
    ConfigChoice choice(*iConfigManager, kKeyChoice2, iChoices, kChoiceDefault+1);
    TEST(iConfigManager->HasChoice(kKeyChoice1) == true);
    TEST(iConfigManager->HasChoice(kKeyChoice2) == true);

    // test ConfigText
    ConfigText text(*iConfigManager, kKeyText2, kMaxTextBytes, kText2);
    TEST(iConfigManager->HasText(kKeyText1) == true);
    TEST(iConfigManager->HasText(kKeyText2) == true);
}

void SuiteConfigManager::TestGetNoVals()
{
    // test that Get() fails with an assertion when no values are present
    ConfigRamStore store;
    ConfigManager configManager(store);
    TEST_THROWS(configManager.GetNum(kKeyNum1), AssertionFailed);
    TEST_THROWS(configManager.GetChoice(kKeyChoice1), AssertionFailed);
    TEST_THROWS(configManager.GetText(kKeyText1), AssertionFailed);

    TEST_THROWS(configManager.Get(kKeyNum1), AssertionFailed);
    TEST_THROWS(configManager.Get(kKeyChoice1), AssertionFailed);
    TEST_THROWS(configManager.Get(kKeyText1), AssertionFailed);
}

void SuiteConfigManager::TestGetValidKey()
{
    // test Get() returns the correct val when key is present

    // test ConfigNum
    ConfigNum& num = iConfigManager->GetNum(kKeyNum1);
    TEST(num == *iNum1);

    // test ConfigChoice
    ConfigChoice& choice = iConfigManager->GetChoice(kKeyChoice1);
    TEST(choice == *iChoice1);

    // test ConfigText
    ConfigText& text = iConfigManager->GetText(kKeyText1);
    TEST(text == *iText1);


    // test generic Get()
    // test ConfigNum
    ISerialisable& serNum = iConfigManager->Get(kKeyNum1);
    Bws<kMaxNumBytes> bufNum;
    TestHelperWriter writerNum(bufNum);
    serNum.Serialise(writerNum);
    TInt valNum = Ascii::Int(bufNum);
    TEST(valNum == kMinNum);

    // test ConfigChoice
    ISerialisable& serChoice = iConfigManager->Get(kKeyChoice1);
    Bws<kMaxChoiceBytes> bufChoice;
    TestHelperWriter writerChoice(bufChoice);
    serChoice.Serialise(writerChoice);
    TUint valChoice = Ascii::Uint(bufChoice);
    TEST(valChoice == kChoiceDefault);

    // test ConfigText
    ISerialisable& serText = iConfigManager->Get(kKeyText1);
    Bws<kMaxTextBytes> bufText;
    TestHelperWriter writerText(bufText);
    serText.Serialise(writerText);
    TEST(bufText == kText1);
}

void SuiteConfigManager::TestGetInvalidKey()
{
    // test that Get() causes an assertion when key is not present
    TEST_THROWS(iConfigManager->GetNum(kKeyNum2), AssertionFailed);
    TEST_THROWS(iConfigManager->GetChoice(kKeyChoice2), AssertionFailed);
    TEST_THROWS(iConfigManager->GetText(kKeyText2), AssertionFailed);

    // try call HasChoice() with the key of ConfigNum
    TEST_THROWS(iConfigManager->GetChoice(kKeyNum1), AssertionFailed);

    // test generic Get()
    TEST_THROWS(iConfigManager->Get(kKeyNum2), AssertionFailed);
    TEST_THROWS(iConfigManager->Get(kKeyChoice2), AssertionFailed);
    TEST_THROWS(iConfigManager->Get(kKeyText2), AssertionFailed);
}

void SuiteConfigManager::TestGetMultiple()
{
    // test adding multiple values and calling Get() on the keys

    // test ConfigNum
    ConfigNum num(*iConfigManager, kKeyNum2, kMinNum, kMaxNum, kMinNum+1);
    ConfigNum& num1 = iConfigManager->GetNum(kKeyNum1);
    TEST(num1 == *iNum1);
    ConfigNum& num2 = iConfigManager->GetNum(kKeyNum2);
    TEST(num2 == num);

    // test ConfigChoice
    ConfigChoice choice(*iConfigManager, kKeyChoice2, iChoices, kChoiceDefault+1);
    ConfigChoice& choice1 = iConfigManager->GetChoice(kKeyChoice1);
    TEST(choice1 == *iChoice1);
    ConfigChoice& choice2 = iConfigManager->GetChoice(kKeyChoice2);
    TEST(choice2 == choice);

    // test ConfigText
    ConfigText text(*iConfigManager, kKeyText2, kMaxTextBytes, kText2);
    ConfigText& text1 = iConfigManager->GetText(kKeyText1);
    TEST(text1 == *iText1);
    ConfigText& text2 = iConfigManager->GetText(kKeyText2);
    TEST(text2 == text);
}

void SuiteConfigManager::TestReadStoreValExists()
{
    // test that reading from a value already in store causes store value to be
    // returned rather than default val.
    iStore->Write(kKeyText1, kText1);
    Bwh buf(kMaxTextBytes);
    iConfigManager->FromStore(kKeyText1, buf, kText2);
    TEST(buf == kText1);

    // check default value hasn't been written to store as a side-effect
    buf.SetBytes(0);
    iStore->Read(kKeyText1, buf);
    TEST(buf == kText1);
}

void SuiteConfigManager::TestReadNoStoreValExists()
{
    // test that reading a value not in store causes default value to be
    // returned, but not written out to store.
    Bwh buf(kMaxTextBytes);

    try { // check key isn't already in store
        iStore->Read(kKeyText2, buf);
        ASSERTS();
    }
    catch (StoreKeyNotFound&) {}

    iConfigManager->FromStore(kKeyText2, buf, kText2);
    TEST(buf == kText2);

    // check value doesn't (yet) exist in store
    buf.SetBytes(0);
    TEST_THROWS(iStore->Read(kKeyText2, buf), StoreKeyNotFound);
}

void SuiteConfigManager::TestWrite()
{
    // test that writing a value via ConfigManager results in value
    // being written to store.
    Bwh buf(kMaxTextBytes);
    iConfigManager->ToStore(kKeyText1, kText2);
    iStore->Read(kKeyText1, buf);
    TEST(buf == kText2);
}

void SuiteConfigManager::TestDumpToStore()
{
    // Test that calling DumpToStore() causes all values to be written to store.

    Bws<kMaxTextBytes> buf;

    // Check no ConfigValues are currently in store - not necessary as covered by other tests.
    TEST_THROWS(iStore->Read(kKeyNum1, buf), StoreKeyNotFound);
    TEST_THROWS(iStore->Read(kKeyChoice1, buf), StoreKeyNotFound);
    TEST_THROWS(iStore->Read(kKeyText1, buf), StoreKeyNotFound);

    iConfigManager->DumpToStore();

    // Check values are now in store.
    iStore->Read(kKeyNum1, buf);
    TInt valNum = Converter::BeUint32At(buf, 0);        // Numerical values should be stored as binary.
    TEST(valNum == kMinNum);

    iStore->Read(kKeyChoice1, buf);
    TUint valChoice = Converter::BeUint32At(buf, 0);    // Numerical values should be stored as binary.
    TEST(valChoice == kChoiceDefault);

    iStore->Read(kKeyText1, buf);
    TEST(buf == kText1);
}


// SuiteRamStore

const Brn SuiteRamStore::kKey1("test.key.1");
const Brn SuiteRamStore::kKey2("test.key.2");
const Brn SuiteRamStore::kVal1("abcdefghijklmnopqrstuvwxyz");
const Brn SuiteRamStore::kVal2("zyxwvutsrqpomnlkjihgfedcba");

SuiteRamStore::SuiteRamStore()
    : SuiteUnitTest("SuiteRamStore")
{
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteRamStore::TestRead), "TestRead");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteRamStore::TestWrite), "TestWrite");
    SuiteUnitTest::AddTest(MakeFunctor(*this, &SuiteRamStore::TestDelete), "TestDelete");
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

    // create a key, write it and a value to the store, then delete the key and
    // check the ram store has persisted the expected key
    Brh* tmpKey = new Brh("temp.key");
    Bwh tmpKeyCopy(*tmpKey);
    iStore->Write(*tmpKey, kVal1);
    delete tmpKey;
    Bwh valOut(kVal1.Bytes());
    iStore->Read(tmpKeyCopy, valOut);
    TEST(valOut == kVal1);
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
    runner.Add(new SuiteSerialisedMap());
    runner.Add(new SuiteConfigManager());
    runner.Add(new SuiteRamStore());
    runner.Run();
}
