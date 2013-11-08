#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Configuration/FunctorGeneric.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Configuration;

namespace OpenHome {
namespace Configuration {

class SuiteFunctorGenericInt : public SuiteUnitTest
{
public:
    SuiteFunctorGenericInt();
protected: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void CallbackInt(TInt& aInt);
    void TestInt();
private:
    TInt iInt;
};

class SuiteFunctorGenericBuf : public SuiteUnitTest
{
public:
    SuiteFunctorGenericBuf();
protected: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void CallbackBuf(const Brx& aBuf);
    void TestBuf();
private:
    static const TUint kMaxBufSize = 26;
    static const Brn kBuf;
    Bws<kMaxBufSize> iBuf;
};

} // namespace Configuration
} // namespace OpenHome


// SuiteFunctorGenericInt
SuiteFunctorGenericInt::SuiteFunctorGenericInt()
    : SuiteUnitTest("SuiteFunctorGenericInt")
{
    AddTest(MakeFunctor(*this, &SuiteFunctorGenericInt::TestInt));
}

void SuiteFunctorGenericInt::Setup()
{
    iInt = 0;
}

void SuiteFunctorGenericInt::TearDown()
{
}

void SuiteFunctorGenericInt::CallbackInt(TInt& aInt)
{
    iInt = aInt;
}

void SuiteFunctorGenericInt::TestInt()
{
    // Test that we can pass an int value through a generic functor.
    TInt val = 1234;
    FunctorGeneric<TInt> funcInt = MakeFunctorGeneric(*this, &SuiteFunctorGenericInt::CallbackInt);
    funcInt(val);
    TEST(iInt == val);
}


// SuiteFunctorGenericBuf
const Brn SuiteFunctorGenericBuf::kBuf("abcdefghijklmnopqrstuvwxyz");

SuiteFunctorGenericBuf::SuiteFunctorGenericBuf()
    : SuiteUnitTest("SuiteFunctorGenericBuf")
{
    AddTest(MakeFunctor(*this, &SuiteFunctorGenericBuf::TestBuf));
}

void SuiteFunctorGenericBuf::Setup()
{
    iBuf.SetBytes(0);
}

void SuiteFunctorGenericBuf::TearDown()
{
}

void SuiteFunctorGenericBuf::CallbackBuf(const Brx& aBuf)
{
    iBuf.Replace(aBuf);
}

void SuiteFunctorGenericBuf::TestBuf()
{
    // Test that we can pass a buffer through a generic functor.
    FunctorGeneric<const Brx> funcBuf = MakeFunctorGeneric(*this, &SuiteFunctorGenericBuf::CallbackBuf);
    funcBuf(kBuf);
    TEST(iBuf == kBuf);
}



void TestFunctorGeneric()
{
    Runner runner("FunctorGeneric tests\n");
    runner.Add(new SuiteFunctorGenericInt());
    runner.Add(new SuiteFunctorGenericBuf());
    runner.Run();
}
