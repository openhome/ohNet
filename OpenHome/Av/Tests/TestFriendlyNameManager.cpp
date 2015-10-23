#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Private/Printer.h>

namespace OpenHome {
namespace Av {
namespace Test {

class MockProductNameObservable : public IProductNameObservable
{
public:
    MockProductNameObservable();
    void SetRoomName(const Brx& aRoom);
    void SetProductName(const Brx& aProduct);
public: // from IProductNameObservable
    void AddNameObserver(IProductNameObserver& aObserver) override;
private:
    IProductNameObserver* iObserver;
};

class MockFriendlyNameObserver
{
public:
    const Brx& FriendlyName() const;
    void FriendlyNameChanged(const Brx& aFriendlyName);
private:
    Bws<IFriendlyNameObservable::kMaxFriendlyNameBytes> iFriendlyName;
};

class SuiteFriendlyNameManager : public OpenHome::TestFramework::SuiteUnitTest
{
public:
    SuiteFriendlyNameManager();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestRegisterDeregister();
    void TestRegisterNoDeregister();
    void TestUpdate();  // Deregister one observer for second update.
private:
    MockProductNameObservable* iObservable;
    FriendlyNameManager* iFriendlyNameManager;
};

} // namespace Test
} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;


// MockProductNameObservable

MockProductNameObservable::MockProductNameObservable()
    : iObserver(nullptr)
{
}

void MockProductNameObservable::SetRoomName(const Brx& aRoom)
{
    ASSERT(iObserver != nullptr);
    iObserver->RoomChanged(aRoom);
}

void MockProductNameObservable::SetProductName(const Brx& aProduct)
{
    ASSERT(iObserver != nullptr);
    iObserver->NameChanged(aProduct);
}

void MockProductNameObservable::AddNameObserver(IProductNameObserver& aObserver)
{
    ASSERT(iObserver == nullptr);
    iObserver = &aObserver;
}


// MockFriendlyNameObserver

const Brx& MockFriendlyNameObserver::FriendlyName() const
{
    return iFriendlyName;
}

void MockFriendlyNameObserver::FriendlyNameChanged(const Brx& aFriendlyName)
{
    iFriendlyName.Replace(aFriendlyName);
}


// SuiteFriendlyNameManager

SuiteFriendlyNameManager::SuiteFriendlyNameManager()
    : SuiteUnitTest("SuiteFriendlyNameManager")
{
    AddTest(MakeFunctor(*this, &SuiteFriendlyNameManager::TestRegisterDeregister), "TestRegisterDeregister");
    AddTest(MakeFunctor(*this, &SuiteFriendlyNameManager::TestRegisterNoDeregister), "TestRegisterNoDeregister");
    AddTest(MakeFunctor(*this, &SuiteFriendlyNameManager::TestUpdate), "TestUpdate");
}

void SuiteFriendlyNameManager::Setup()
{
    iObservable = new MockProductNameObservable();
    iFriendlyNameManager = new FriendlyNameManager(*iObservable);
}

void SuiteFriendlyNameManager::TearDown()
{
    delete iFriendlyNameManager;
    delete iObservable;
}

void SuiteFriendlyNameManager::TestRegisterDeregister()
{
    const Brn kFriendlyName("Room:Product");
    IFriendlyNameObservable& observable = *iFriendlyNameManager;
    iObservable->SetRoomName(Brn("Room"));
    iObservable->SetProductName(Brn("Product"));

    MockFriendlyNameObserver observer1;
    MockFriendlyNameObserver observer2;

    const TUint id1 = observable.RegisterFriendlyNameObserver(MakeFunctorGeneric<const Brx&>(observer1, &MockFriendlyNameObserver::FriendlyNameChanged));
    TEST(observer1.FriendlyName() == kFriendlyName);

    const TUint id2 = observable.RegisterFriendlyNameObserver(MakeFunctorGeneric<const Brx&>(observer2, &MockFriendlyNameObserver::FriendlyNameChanged));
    TEST(observer2.FriendlyName() == kFriendlyName);

    observable.DeregisterFriendlyNameObserver(id2);
    observable.DeregisterFriendlyNameObserver(id1);
}

void SuiteFriendlyNameManager::TestRegisterNoDeregister()
{
    IFriendlyNameObservable& observable = *iFriendlyNameManager;
    MockFriendlyNameObserver observer;
    (void)observable.RegisterFriendlyNameObserver(MakeFunctorGeneric<const Brx&>(observer, &MockFriendlyNameObserver::FriendlyNameChanged));
    TEST_THROWS(delete iFriendlyNameManager, AssertionFailed);
    iFriendlyNameManager = nullptr;
}

void SuiteFriendlyNameManager::TestUpdate()
{
    IFriendlyNameObservable& observable = *iFriendlyNameManager;
    iObservable->SetRoomName(Brn("Room"));
    iObservable->SetProductName(Brn("Product"));

    MockFriendlyNameObserver observer1;
    MockFriendlyNameObserver observer2;

    const TUint id1 = observable.RegisterFriendlyNameObserver(MakeFunctorGeneric<const Brx&>(observer1, &MockFriendlyNameObserver::FriendlyNameChanged));
    const TUint id2 = observable.RegisterFriendlyNameObserver(MakeFunctorGeneric<const Brx&>(observer2, &MockFriendlyNameObserver::FriendlyNameChanged));

    iObservable->SetRoomName(Brn("NewRoom"));
    TEST(observer1.FriendlyName() == Brn("NewRoom:Product"));
    TEST(observer2.FriendlyName() == Brn("NewRoom:Product"));

    // Now, deregister the first observer, then issue an update.
    observable.DeregisterFriendlyNameObserver(id1);
    iObservable->SetProductName(Brn("NewProduct"));
    TEST(observer1.FriendlyName() == Brn("NewRoom:Product"));       // Observer 1 shouldn't be updated.
    TEST(observer2.FriendlyName() == Brn("NewRoom:NewProduct"));    // Observer 2 should be updated.

    observable.DeregisterFriendlyNameObserver(id2);

    iObservable->SetRoomName(Brn("RoomName2"));
    // Observers shouldn't have been updated.
    TEST(observer1.FriendlyName() == Brn("NewRoom:Product"));
    TEST(observer2.FriendlyName() == Brn("NewRoom:NewProduct"));
}



void TestFriendlyNameManager()
{
    Runner runner("FriendlyNameManager tests\n");
    runner.Add(new SuiteFriendlyNameManager());
    runner.Run();
}
