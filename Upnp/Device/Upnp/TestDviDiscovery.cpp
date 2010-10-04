#include <TestFramework.h>
#include <ZappTypes.h>
#include <Zapp.h>
#include <Discovery.h>
#include <DviDevice.h>
#include <DviService.h>
#include <Stack.h>
#include <Maths.h>

#include <stdlib.h>
#include <vector>

using namespace Zapp;
using namespace Zapp::TestFramework;

class CpListenerBasic : public ISsdpNotifyHandler
{
public:
    CpListenerBasic();
    TUint TotalMessages() const { return iTotal; }
private:
    TBool LogAdd(const Brx& aUuid);
    TBool LogRemove(const Brx& aUuid);
    void SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyRootByeBye(const Brx& aUuid);
    void SsdpNotifyUuidByeBye(const Brx& aUuid);
    void SsdpNotifyDeviceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion);
    void SsdpNotifyServiceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion);
private:
    TUint iTotal;
};

class CpListenerMsearch : public ISsdpNotifyHandler
{
public:
    CpListenerMsearch();
    ~CpListenerMsearch();
    TUint TotalMessages() const { return iTotal; }
    TUint RootDeviceCount() const {return iRoot; }
    TUint DeviceCount() const { return iDevice; }
    TUint ServiceCount() const { return iService; }
    TUint Udns() const; // bitmask for SuiteMsearch::kNameDevice1 etc
    const TChar* Dev1Type() const { return iDev1Type; }
    const TChar* Dev2Type() const { return iDev2Type; }
    const TChar* Dev21Type() const { return iDev21Type; }
    const std::vector<TChar*>& Services() const { return iServices; }
    void Reset();
private:
    TBool LogUdn(const Brx& aUuid, const Brx& aLocation);
    TChar* CreateTypeString(const Brx& aDomain, const Brx& aType, TUint aVersion);
    void SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyRootByeBye(const Brx& aUuid);
    void SsdpNotifyUuidByeBye(const Brx& aUuid);
    void SsdpNotifyDeviceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion);
    void SsdpNotifyServiceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion);
private:
    TUint iTotal;
    TUint iRoot;
    TUint iUdn;
    TUint iDevice;
    TUint iService;
    TUint iUdnsReceived;

    TChar* iDev1Type;
    TChar* iDev2Type;
    TChar* iDev21Type;
    std::vector<TChar*> iServices;
};

class SuiteAlive : public Suite
{
public:
    static Bwh gNameDevice1;
public:
    SuiteAlive();
    ~SuiteAlive();
    void Test();
private:
    void Disabled();
private:
    Semaphore iSem;
};

class SuiteMsearch : public Suite
{
public:
    static Bwh gNameDevice1;
    static Bwh gNameDevice2;
    static Bwh gNameDevice2Embedded1;
    static const Brn kNameDummy;
public:
    SuiteMsearch();
    ~SuiteMsearch();
    void Test();
private:
    void Wait();
    void TestMsearchAll();
    void TestMsearchRoot();
    void TestMsearchUuid();
    void TestMsearchDeviceType();
    void TestMsearchServiceType();
private:
    DviDevice* iDevices[2];
    Blocker* iBlocker;
    CpListenerMsearch* iListener;
    SsdpListenerUnicast* iListenerUnicast;
};

Bwh SuiteAlive::gNameDevice1("TestAlive");
Bwh SuiteMsearch::gNameDevice1("TestDevice1");
Bwh SuiteMsearch::gNameDevice2("TestDevice2");
Bwh SuiteMsearch::gNameDevice2Embedded1("TestDevice2.Embedded.1");
const Brn SuiteMsearch::kNameDummy("Dummy");

static TBool DeviceTypeMatches(const TChar* aType1, const TChar* aType2)
{
    return (0 == strcmp(aType1, aType2));
}

static TBool ServiceVectorContainsType(const std::vector<TChar*>& aVector, const TChar* aType)
{
    for (TUint i=0; i<aVector.size(); i++) {
        if (0 == strcmp(aVector[i], aType)) {
            return true;
        }
    }
    return false;
}


// CpListenerBasic

CpListenerBasic::CpListenerBasic()
    : iTotal(0)
{
}

TBool CpListenerBasic::LogAdd(const Brx& aUuid)
{
    if (aUuid == SuiteAlive::gNameDevice1) {
        iTotal++;
        return true;
    }
    return false;
}

TBool CpListenerBasic::LogRemove(const Brx& aUuid)
{
    if (aUuid == SuiteAlive::gNameDevice1) {
        ASSERT(iTotal != 0);
        iTotal--;
        return true;
    }
    return false;
}

void CpListenerBasic::SsdpNotifyRootAlive(const Brx& aUuid, const Brx& /*aLocation*/, TUint /*aMaxAge*/)
{
    LogAdd(aUuid);
}

void CpListenerBasic::SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& /*aLocation*/, TUint /*aMaxAge*/)
{
    LogAdd(aUuid);
}

void CpListenerBasic::SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& /*aDomain*/, const Brx& /*aType*/, TUint /*aVersion*/, const Brx& /*aLocation*/, TUint /*aMaxAge*/)
{
    LogAdd(aUuid);
}

void CpListenerBasic::SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& /*aDomain*/, const Brx& /*aType*/, TUint /*aVersion*/, const Brx& /*aLocation*/, TUint /*aMaxAge*/)
{
    LogAdd(aUuid);
}

void CpListenerBasic::SsdpNotifyRootByeBye(const Brx& aUuid)
{
    LogRemove(aUuid);
}

void CpListenerBasic::SsdpNotifyUuidByeBye(const Brx& aUuid)
{
    LogRemove(aUuid);
}

void CpListenerBasic::SsdpNotifyDeviceTypeByeBye(const Brx& aUuid, const Brx& /*aDomain*/, const Brx& /*aType*/, TUint /*aVersion*/)
{
    LogRemove(aUuid);
}

void CpListenerBasic::SsdpNotifyServiceTypeByeBye(const Brx& aUuid, const Brx& /*aDomain*/, const Brx& /*aType*/, TUint /*aVersion*/)
{
    LogRemove(aUuid);
}


static void RandomiseUdn(Bwh& aUdn)
{
    aUdn.Grow(aUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    aUdn.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    NetworkInterface* nif = Stack::NetworkInterfaceList().CurrentInterface();
    TUint max = nif->Address();
    delete nif;
    (void)Ascii::AppendDec(buf, Random(max));
    aUdn.Append(buf);
    aUdn.PtrZ();
}

// SuiteAlive

SuiteAlive::SuiteAlive()
    : Suite("Alive / ByeBye / Update")
    , iSem("SALV", 0)
{
    RandomiseUdn(gNameDevice1);
}

SuiteAlive::~SuiteAlive()
{
}

void SuiteAlive::Test()
{
    Blocker* blocker = new Blocker;
    CpListenerBasic* listener = new CpListenerBasic;
    NetworkInterface* nif = Stack::NetworkInterfaceList().CurrentInterface();
    SsdpListenerMulticast* listenerMulticast = new SsdpListenerMulticast(nif->Address());
    delete nif;
    TInt listenerId = listenerMulticast->AddNotifyHandler(listener);
    listenerMulticast->Start();

    DviDevice* device = new DviDevice(gNameDevice1);
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "type1");
    device->SetAttribute("Upnp.Version", "1");
    device->AddService(new DviService("a.b.c", "service1", 1));
    device->AddService(new DviService("a.b.c", "service2", 1));
    device->SetEnabled();
    blocker->Wait(1);
    /* we expect 5 messages but linux sometimes reports multicast messages from
      all subnets to listeners on any single subnet so just check that we've
      received a multiple of 5 messages */
    TEST(listener->TotalMessages() % 5 == 0);

    Functor disabled = MakeFunctor(*this, &SuiteAlive::Disabled);
    device->SetDisabled(disabled);
    iSem.Wait();
    blocker->Wait(1); /* semaphore being signalled implies that the device has been
                         disabled.  We may require some extra time to receive the
                         multicast byebye confirming this */
    TEST(listener->TotalMessages() == 0);

    device->SetEnabled();
    blocker->Wait(1);
    TEST(listener->TotalMessages() % 5 == 0);

    // Control point doesn't process ssdp:update notifications
    // check that updates are basically working by counting the extra alive messages instead
    TUint oldTotal = listener->TotalMessages();
    device->SetAttribute("Upnp.TestUpdate", "1");
    blocker->Wait(1);
    TEST(listener->TotalMessages() > oldTotal);
    TEST(listener->TotalMessages() % 5 == 0);

    device->Destroy();
    listenerMulticast->RemoveNotifyHandler(listenerId);
    delete listenerMulticast;
    delete listener;
    delete blocker;
}

void SuiteAlive::Disabled()
{
    iSem.Signal();
}


// CpListenerMsearch

CpListenerMsearch::CpListenerMsearch()
{
    iDev1Type = iDev2Type = iDev21Type = NULL;
    Reset();
}

CpListenerMsearch::~CpListenerMsearch()
{
    Reset();
}

TUint CpListenerMsearch::Udns() const
{
    return iUdnsReceived;
}

void CpListenerMsearch::Reset()
{
    iTotal = 0;
    iRoot = 0;
    iUdn = 0;
    iDevice = 0;
    iService = 0;
    iUdnsReceived = 0;
    
    delete iDev1Type;
    iDev1Type = NULL;
    delete iDev2Type;
    iDev2Type = NULL;
    delete iDev21Type;
    iDev21Type = NULL;
    TUint i;
    for (i=0; i<iServices.size(); i++) {
        delete iServices[i];
    }
    iServices.clear();
}

TBool CpListenerMsearch::LogUdn(const Brx& aUuid, const Brx& aLocation)
{
    Uri uri(aLocation);
    Endpoint endpt(0, uri.Host());
    NetworkInterface* nif = Stack::NetworkInterfaceList().CurrentInterface();
    TBool correctSubnet = nif->ContainsAddress(endpt.Address());
    delete nif;
    if (!correctSubnet) {
        return false;
    }

    if (aUuid == SuiteMsearch::gNameDevice1){
        iUdnsReceived |= 1;
    }
    else if (aUuid == SuiteMsearch::gNameDevice2){
        iUdnsReceived |= 2;
    }
    else if (aUuid == SuiteMsearch::gNameDevice2Embedded1) {
        iUdnsReceived |= 4;
    }
    else {
        return false;
    }
    iTotal++;
    return true;
}

TChar* CpListenerMsearch::CreateTypeString(const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    TChar* type = (TChar*)malloc(aDomain.Bytes() + aType.Bytes() + 2 + Ascii::kMaxUintStringBytes + 1);
    TChar* ptr = type;
    (void)strncpy(ptr, (const TChar*)aDomain.Ptr(), aDomain.Bytes());
    ptr += aDomain.Bytes();
    *ptr = ':';
    ptr++;
    (void)strncpy(ptr, (const TChar*)aType.Ptr(), aType.Bytes());
    ptr += aType.Bytes();
    *ptr = ':';
    ptr++;
    Bws<Ascii::kMaxUintStringBytes> ver;
    Ascii::AppendDec(ver, aVersion);
    (void)strncpy(ptr, (const TChar*)ver.Ptr(), ver.Bytes());
    ptr += ver.Bytes();
    *ptr = '\0';
    return type;
}

void CpListenerMsearch::SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint /*aMaxAge*/)
{
    if (LogUdn(aUuid, aLocation)) {
        iRoot++;
    }
}

void CpListenerMsearch::SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint /*aMaxAge*/)
{
    (void)LogUdn(aUuid, aLocation);
}

void CpListenerMsearch::SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint /*aMaxAge*/)
{
    if (LogUdn(aUuid, aLocation)) {
        iDevice++;
        TChar* type = CreateTypeString(aDomain, aType, aVersion);
        if (aUuid == SuiteMsearch::gNameDevice1){
            delete iDev1Type;
            iDev1Type = type;
        }
        else if (aUuid == SuiteMsearch::gNameDevice2){
            delete iDev2Type;
            iDev2Type = type;
        }
        else if (aUuid == SuiteMsearch::gNameDevice2Embedded1) {
            delete iDev21Type;
            iDev21Type = type;
        }
    }
}

void CpListenerMsearch::SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint /*aMaxAge*/)
{
    if (LogUdn(aUuid, aLocation)) {
        iService++;
        TChar* type = CreateTypeString(aDomain, aType, aVersion);
        iServices.push_back(type);
    }
}

void CpListenerMsearch::SsdpNotifyRootByeBye(const Brx& /*aUuid*/)
{
}

void CpListenerMsearch::SsdpNotifyUuidByeBye(const Brx& /*aUuid*/)
{
}

void CpListenerMsearch::SsdpNotifyDeviceTypeByeBye(const Brx& /*aUuid*/, const Brx& /*aDomain*/, const Brx& /*aType*/, TUint /*aVersion*/)
{
}

void CpListenerMsearch::SsdpNotifyServiceTypeByeBye(const Brx& /*aUuid*/, const Brx& /*aDomain*/, const Brx& /*aType*/, TUint /*aVersion*/)
{
}


// SuiteMsearch

SuiteMsearch::SuiteMsearch()
    : Suite("Msearches")
{
    RandomiseUdn(gNameDevice1);
    RandomiseUdn(gNameDevice2);
    RandomiseUdn(gNameDevice2Embedded1);
    Stack::InitParams().SetMsearchTime(1);
    iBlocker = new Blocker;
    iListener = new CpListenerMsearch;
    NetworkInterface* nif = Stack::NetworkInterfaceList().CurrentInterface();
    iListenerUnicast = new SsdpListenerUnicast(*iListener, nif->Address());
    delete nif;
    iListenerUnicast->Start();
}

SuiteMsearch::~SuiteMsearch()
{
    delete iBlocker;
    delete iListenerUnicast;
    delete iListener;
    iDevices[0]->Destroy();
    iDevices[1]->Destroy();
}

void SuiteMsearch::Test()
{
    DviDevice* device = new DviDevice(gNameDevice1);
    iDevices[0] = device;
    device->SetAttribute("Upnp.Domain", "upnp.org");
    device->SetAttribute("Upnp.Type", "test1");
    device->SetAttribute("Upnp.Version", "1");
    device->AddService(new DviService("upnp.org", "service1", 1));
    device->AddService(new DviService("linn.co.uk", "service2", 3));
    device->AddService(new DviService("upnp.org", "service3", 1));
    TEST_THROWS(device->AddService(new DviService("upnp.org", "service1", 1)), AssertionFailed);
    device->SetEnabled();
    TEST_THROWS(device->AddService(new DviService("upnp.org", "service4", 1)), AssertionFailed);

    device = new DviDevice(gNameDevice2);
    iDevices[1] = device;
    device->SetAttribute("Upnp.Domain", "linn.co.uk");
    device->SetAttribute("Upnp.Type", "test2");
    device->SetAttribute("Upnp.Version", "2");
    device->AddService(new DviService("linn.co.uk", "service4", 2));
    device->AddService(new DviService("linn.co.uk", "service5", 1));

    device = new DviDevice(gNameDevice2Embedded1);
    iDevices[1]->AddDevice(device);
    device->SetAttribute("Upnp.Domain", "linn.co.uk");
    device->SetAttribute("Upnp.Type", "test3");
    device->SetAttribute("Upnp.Version", "1");
    device->AddService(new DviService("upnp.org", "service1", 1));
    device->AddService(new DviService("linn.co.uk", "service6", 1));
    device->AddService(new DviService("linn.co.uk", "service2", 3));
    TEST_THROWS(device->AddService(new DviService("linn.co.uk", "service5", 1)), AssertionFailed);
    iDevices[1]->SetEnabled();
    device->SetEnabled();
    device = new DviDevice(kNameDummy);
    TEST_THROWS(iDevices[1]->AddDevice(device), AssertionFailed);
    device->Destroy();

    TestMsearchAll();
    TestMsearchRoot();
    TestMsearchUuid();
    TestMsearchDeviceType();
    TestMsearchServiceType();
}

void SuiteMsearch::Wait()
{
    iBlocker->Wait(Stack::InitParams().MsearchTimeSecs() + 1);
}

void SuiteMsearch::TestMsearchAll()
{
    iListener->Reset();
    iListenerUnicast->MsearchAll();
    Wait();
    TEST(iListener->RootDeviceCount() == 2);
    TEST(iListener->DeviceCount() == 3);
    TEST(iListener->ServiceCount() == 8);
    TEST(iListener->Udns() == 7);
    TEST(iListener->TotalMessages() == 16);
    TEST(DeviceTypeMatches(iListener->Dev1Type(), "upnp.org:test1:1"));
    TEST(DeviceTypeMatches(iListener->Dev2Type(), "linn.co.uk:test2:2"));
    TEST(DeviceTypeMatches(iListener->Dev21Type(), "linn.co.uk:test3:1"));
    TEST(ServiceVectorContainsType(iListener->Services(), "upnp.org:service1:1"));
    TEST(ServiceVectorContainsType(iListener->Services(), "linn.co.uk:service2:3"));
    TEST(ServiceVectorContainsType(iListener->Services(), "upnp.org:service3:1"));
    TEST(ServiceVectorContainsType(iListener->Services(), "linn.co.uk:service4:2"));
    TEST(ServiceVectorContainsType(iListener->Services(), "linn.co.uk:service5:1"));
    TEST(ServiceVectorContainsType(iListener->Services(), "linn.co.uk:service6:1"));
}

void SuiteMsearch::TestMsearchRoot()
{
    iListener->Reset();
    iListenerUnicast->MsearchRoot();
    Wait();
    TEST(iListener->RootDeviceCount() == 2);
    TEST(iListener->DeviceCount() == 0);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 3);
    TEST(iListener->TotalMessages() == 2);
}

void SuiteMsearch::TestMsearchUuid()
{
    iListener->Reset();
    iListenerUnicast->MsearchUuid(gNameDevice1);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 0);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 1);
    TEST(iListener->TotalMessages() == 1);

    iListener->Reset();
    iListenerUnicast->MsearchUuid(gNameDevice2);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 0);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 2);
    TEST(iListener->TotalMessages() == 1);

    iListener->Reset();
    iListenerUnicast->MsearchUuid(gNameDevice2Embedded1);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 0);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 4);
    TEST(iListener->TotalMessages() == 1);

    iListener->Reset();
    iListenerUnicast->MsearchUuid(gNameDevice1);
    iListenerUnicast->MsearchUuid(gNameDevice2);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 0);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 3);
    TEST(iListener->TotalMessages() == 2);
}

void SuiteMsearch::TestMsearchDeviceType()
{
    iListener->Reset();
    iListenerUnicast->MsearchDeviceType(Brn("upnp.org"), Brn("test1"), 1);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 1);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 1);
    TEST(iListener->TotalMessages() == 1);
    TEST(DeviceTypeMatches(iListener->Dev1Type(), "upnp.org:test1:1"));

    iListener->Reset();
    iListenerUnicast->MsearchDeviceType(Brn("linn.co.uk"), Brn("test2"), 2);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 1);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 2);
    TEST(iListener->TotalMessages() == 1);
    TEST(DeviceTypeMatches(iListener->Dev2Type(), "linn.co.uk:test2:2"));

    iListener->Reset();
    iListenerUnicast->MsearchDeviceType(Brn("linn.co.uk"), Brn("test3"), 1);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 1);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 4);
    TEST(iListener->TotalMessages() == 1);
    TEST(DeviceTypeMatches(iListener->Dev21Type(), "linn.co.uk:test3:1"));

    iListener->Reset();
    iListenerUnicast->MsearchDeviceType(Brn("upnp.org"), Brn("test1"), 1);
    iListenerUnicast->MsearchDeviceType(Brn("linn.co.uk"), Brn("test3"), 1);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 2);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 5);
    TEST(iListener->TotalMessages() == 2);
    TEST(DeviceTypeMatches(iListener->Dev1Type(), "upnp.org:test1:1"));
    TEST(DeviceTypeMatches(iListener->Dev21Type(), "linn.co.uk:test3:1"));
}

void SuiteMsearch::TestMsearchServiceType()
{
    iListener->Reset();
    iListenerUnicast->MsearchServiceType(Brn("upnp.org"), Brn("service1"), 1);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 0);
    TEST(iListener->ServiceCount() == 2);
    TEST(iListener->Udns() == 5);
    TEST(iListener->TotalMessages() == 2);
    TEST(iListener->Services().size() == 2);
    TEST(0 == strcmp(iListener->Services()[0], "upnp.org:service1:1"));
    TEST(0 == strcmp(iListener->Services()[1], "upnp.org:service1:1"));

    iListener->Reset();
    iListenerUnicast->MsearchServiceType(Brn("linn.co.uk"), Brn("service2"), 3);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 0);
    TEST(iListener->ServiceCount() == 2);
    TEST(iListener->Udns() == 5);
    TEST(iListener->TotalMessages() == 2);
    TEST(iListener->Services().size() == 2);
    TEST(0 == strcmp(iListener->Services()[0], "linn.co.uk:service2:3"));
    TEST(0 == strcmp(iListener->Services()[1], "linn.co.uk:service2:3"));

    iListener->Reset();
    iListenerUnicast->MsearchServiceType(Brn("linn.co.uk"), Brn("service5"), 1);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 0);
    TEST(iListener->ServiceCount() == 1);
    TEST(iListener->Udns() == 2);
    TEST(iListener->TotalMessages() == 1);
    TEST(iListener->Services().size() == 1);
    TEST(0 == strcmp(iListener->Services()[0], "linn.co.uk:service5:1"));
}


void Zapp::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartDv();

    //Debug::SetLevel(Debug::kNetwork);
    Runner runner("SSDP discovery\n");
    runner.Add(new SuiteAlive());
    runner.Add(new SuiteMsearch());
    runner.Run();

    UpnpLibrary::Close();
}
