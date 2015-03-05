#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/ObservableBrx.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class SuiteObservableBrx : public Suite
{
public:
    SuiteObservableBrx() : Suite("ObservableBrx") {}
    void Test() override;
};

class ObservableHelper
{
public:
    ObservableHelper(IObservableBrx& aObservableBrx, TUint aBytes)
    : iObservableBrx(aObservableBrx)
    , iData(aBytes)
    {
        iFunctor = MakeFunctorGeneric<const Brx&>(*this, &ObservableHelper::BrxObserver);
        iObservableBrx.AddObserver(iFunctor);
    }
    ~ObservableHelper()
    {
        Unsubscribe();
    }
    void Unsubscribe()
    {
        iObservableBrx.RemoveObserver(iFunctor);
    }
    const Brx& LastSeen() const
    {
        return iData;
    }
private:
    void BrxObserver(const Brx& aData)
    {
        iData.Replace(aData);
    }
private:
    IObservableBrx& iObservableBrx;
    Bwh iData;
    IObservableBrx::FunctorBrx iFunctor;
};

void SuiteObservableBrx::Test()
{
    Brn initialValue("initial value");
    ObservableBrx ob(new Bwh(initialValue));
    ObservableHelper oh0(ob, 128);
    ObservableHelper oh1(ob, 128);

    Brn value0("value0");

    ob.Replace(value0);
    TEST(oh0.LastSeen() == value0); // updated
    TEST(oh1.LastSeen() == value0); // updated

    oh1.Unsubscribe();
    Brn value1("value1");
    ob.Replace(value1);
    TEST(oh0.LastSeen() == value1); // updated
    TEST(oh1.LastSeen() == value0); // not updated
}

void TestObservable()
{
    Runner runner("Observable tests\n");
    runner.Add(new SuiteObservableBrx());
    runner.Run();
}
