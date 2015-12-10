#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/FriendlyNameAdapter.h>
#include <OpenHome/Net/Private/DviStack.h>



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
    SuiteFriendlyNameManager(Net::CpStack& aCpStack, Net::DvStack& aDvStack);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestRegisterDeregister();
    void TestUpdate();  // Deregister one observer for second update.
    void TestDvUpdate();
private:
    Net::CpStack& iCpStack;
    Net::DvStack& iDvStack;
    FriendlyNameManager* iFriendlyNameManager;
    MockProductNameObservable* iObservable;
};

} // namespace Test
} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Net;
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

SuiteFriendlyNameManager::SuiteFriendlyNameManager(CpStack& aCpStack, DvStack& aDvStack)
    : SuiteUnitTest("SuiteFriendlyNameManager")
    , iCpStack(aCpStack)
    , iDvStack(aDvStack)
{
    AddTest(MakeFunctor(*this, &SuiteFriendlyNameManager::TestRegisterDeregister), "TestRegisterDeregister");
    AddTest(MakeFunctor(*this, &SuiteFriendlyNameManager::TestUpdate), "TestUpdate");
    AddTest(MakeFunctor(*this, &SuiteFriendlyNameManager::TestDvUpdate), "TestDvUpdate");
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

// SuiteFriendlyNameManager
class DeviceBasic
{
public:
    DeviceBasic(DvStack& aDvStack);
    ~DeviceBasic();
    DvDevice& Device();
private:
    DvDeviceStandard* iDevice;
};


static Bwh gDeviceName("device");

DeviceBasic::DeviceBasic(DvStack& aDvStack)
{
    TestFramework::RandomiseUdn(aDvStack.Env(), gDeviceName);
    iDevice = new DvDeviceStandard(aDvStack, gDeviceName);
    iDevice->SetAttribute("Upnp.Domain", "openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Test");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "ohNetTestDevice");
    iDevice->SetAttribute("Upnp.Manufacturer", "None");
    iDevice->SetAttribute("Upnp.ModelName", "ohNet test device");
    iDevice->SetEnabled();
}

DeviceBasic::~DeviceBasic()
{
    delete iDevice;
}

DvDevice& DeviceBasic::Device()
{
    return *iDevice;
}

void SuiteFriendlyNameManager::TestDvUpdate()
{
    const TChar* updatedName;

    DeviceBasic* deviceBasic1 = new DeviceBasic(iDvStack);
    DvDevice& dvDevice1 = deviceBasic1->Device();
    DeviceBasic* deviceBasic2 = new DeviceBasic(iDvStack);
    DvDevice& dvDevice2 = deviceBasic2->Device();

    iObservable->SetRoomName(Brn("Room"));
    iObservable->SetProductName(Brn("Product"));

    // construct updaters for different device types
    auto updater1 = new FriendlyNameAttributeUpdater(*iFriendlyNameManager, dvDevice1);
    auto updater2 = new FriendlyNameAttributeUpdater(*iFriendlyNameManager, dvDevice2, Brn(":MediaRenderer"));

    // check initial updates
    dvDevice1.GetAttribute("Upnp.FriendlyName", &updatedName);
    TEST(Brn(updatedName) == Brn("Room:Product"));
    dvDevice2.GetAttribute("Upnp.FriendlyName", &updatedName);
    TEST(Brn(updatedName) == Brn("Room:Product:MediaRenderer"));

    iObservable->SetRoomName(Brn("NewRoom"));

    // check updates after room name modified
    dvDevice1.GetAttribute("Upnp.FriendlyName", &updatedName);
    TEST(Brn(updatedName) == Brn("NewRoom:Product"));
    dvDevice2.GetAttribute("Upnp.FriendlyName", &updatedName);
    TEST(Brn(updatedName) == Brn("NewRoom:Product:MediaRenderer"));

    delete updater2;
    delete updater1;
    delete deviceBasic2;
    delete deviceBasic1;
}


 //   FriendlyNameAttributeUpdater(*iFriendlyNameManager, dvDevice);
  //  TEST(Brn(updatedName) == Brn("NewRoom:Product:MediaRenderer")); //appends correctly

void TestFriendlyNameManager(CpStack& aCpStack, DvStack& aDvStack)
{
    Runner runner("FriendlyNameManager tests\n");
    runner.Add(new SuiteFriendlyNameManager(aCpStack, aDvStack));
    runner.Run();
}
