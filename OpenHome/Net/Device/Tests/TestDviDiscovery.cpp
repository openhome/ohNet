#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Standard.h>

#include <stdlib.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

static const TChar* kAdapterCookie = "TestDviDiscovery";

class CpListenerBasic : public ISsdpNotifyHandler
{
public:
    CpListenerBasic();
    TUint TotalAlives() const { return iTotalAlives; }
    TUint TotalByeByes() const { return iTotalByeByes; }
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
    Mutex iLock;
    TUint iTotalAlives;
    TUint iTotalByeByes;
};

class CpListenerMsearch : public ISsdpNotifyHandler
{
public:
    CpListenerMsearch(Environment& aEnv);
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
    Environment& iEnv;
    Mutex iLock;
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
    SuiteAlive(DvStack& aDvStack);
    ~SuiteAlive();
    void Test();
private:
    void Disabled();
private:
    DvStack& iDvStack;
    Semaphore iSem;
};

class SuiteMsearch : public Suite, private INonCopyable
{
public:
    static Bwh gNameDevice1;
    static Bwh gNameDevice2;
    static Bwh gNameDevice2Embedded1;
    static const Brn kNameDummy;
public:
    SuiteMsearch(DvStack& aDvStack);
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
    DvStack& iDvStack;
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
    if (aType1 == NULL || aType2 == NULL) {
        return false;
    }
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

static void AddService(DviDevice* aDevice, DviService* aService)
{
    aDevice->AddService(aService);
    aService->RemoveRef();
}


// CpListenerBasic

CpListenerBasic::CpListenerBasic()
    : iLock("LBMX")
    , iTotalAlives(0)
    , iTotalByeByes(0)
{
}

TBool CpListenerBasic::LogAdd(const Brx& aUuid)
{
    if (aUuid == SuiteAlive::gNameDevice1) {
        iLock.Wait();
        iTotalAlives++;
        iLock.Signal();
        return true;
    }
    return false;
}

TBool CpListenerBasic::LogRemove(const Brx& aUuid)
{
    if (aUuid == SuiteAlive::gNameDevice1) {
        iLock.Wait();
        iTotalByeByes++;
        iLock.Signal();
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


// SuiteAlive

SuiteAlive::SuiteAlive(DvStack& aDvStack)
    : Suite("Alive / ByeBye / Update")
    , iDvStack(aDvStack)
    , iSem("SALV", 0)
{
    RandomiseUdn(iDvStack.Env(), gNameDevice1);
    Print("UDN: ");
    Print(gNameDevice1);
    Print("\n\n");
}

SuiteAlive::~SuiteAlive()
{
}

void SuiteAlive::Test()
{
    Environment& env = iDvStack.Env();
    Blocker* blocker = new Blocker(env);
    CpListenerBasic* listener = new CpListenerBasic;
    NetworkAdapter* nif = env.NetworkAdapterList().CurrentAdapter(kAdapterCookie).Ptr();
    SsdpListenerMulticast* listenerMulticast = new SsdpListenerMulticast(env, nif->Address());
    nif->RemoveRef(kAdapterCookie);
    TInt listenerId = listenerMulticast->AddNotifyHandler(listener);
    listenerMulticast->Start();
    DviDevice* device = new DviDeviceStandard(iDvStack, gNameDevice1);
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "type1");
    device->SetAttribute("Upnp.Version", "1");
    AddService(device, new DviService(iDvStack, "a.b.c", "service1", 1));
    AddService(device, new DviService(iDvStack, "a.b.c", "service2", 1));
    device->SetEnabled();
    blocker->Wait(1);
    /* we expect 5 messages but linux sometimes reports multicast messages from
      all subnets to listeners on any single subnet so just check that we've
      received a multiple of 5 messages */

    TEST(listener->TotalAlives() > 0);
    TEST(listener->TotalAlives() == listener->TotalByeByes());
    TEST(listener->TotalAlives() % 5 == 0);

    TUint byebyes = listener->TotalByeByes();
    Functor disabled = MakeFunctor(*this, &SuiteAlive::Disabled);
    device->SetDisabled(disabled);
    iSem.Wait();
    blocker->Wait(1); /* semaphore being signalled implies that the device has been
                         disabled.  We may require some extra time to receive the
                         multicast byebye confirming this */
    TEST(listener->TotalByeByes() > byebyes);
    TEST(listener->TotalByeByes() % 5 == 0);

    TUint alives = listener->TotalAlives();
    byebyes = listener->TotalByeByes();
    device->SetEnabled();
    blocker->Wait(1);
    TEST(listener->TotalAlives() > alives);
    TEST(listener->TotalAlives() - alives == listener->TotalByeByes() - byebyes);
    TEST(listener->TotalAlives() % 5 == 0);

    // Control point doesn't process ssdp:update notifications
    // check that updates are basically working by counting the extra alive messages instead
    alives = listener->TotalAlives();
    device->SetAttribute("Upnp.TestUpdate", "1");
    blocker->Wait(1);
    TEST(listener->TotalAlives() > alives);
    TEST(listener->TotalAlives() % 5 == 0);

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

CpListenerMsearch::CpListenerMsearch(Environment& aEnv)
    : iEnv(aEnv)
    , iLock("LMMX")
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
    iLock.Wait();
    iTotal = 0;
    iRoot = 0;
    iUdn = 0;
    iDevice = 0;
    iService = 0;
    iUdnsReceived = 0;
    
    free(iDev1Type);
    iDev1Type = NULL;
    free(iDev2Type);
    iDev2Type = NULL;
    free(iDev21Type);
    iDev21Type = NULL;
    for (TUint i=0; i<iServices.size(); i++) {
        free(iServices[i]);
    }
    iServices.clear();
    iLock.Signal();
}

TBool CpListenerMsearch::LogUdn(const Brx& aUuid, const Brx& aLocation)
{
    Uri uri;
    try {
        uri.Replace(aLocation);
    }
    catch (UriError&) {
        Log::Print("CpListenerMsearch: nonsense response - ");
        Log::Print(aLocation);
        Log::Print(" from ");
        Log::Print(aUuid);
        Log::Print("\n");
        return false;
    }
    Endpoint endpt(0, uri.Host());
    NetworkAdapter* nif = iEnv.NetworkAdapterList().CurrentAdapter(kAdapterCookie).Ptr();
    TBool correctSubnet = nif->ContainsAddress(endpt.Address());
    nif->RemoveRef(kAdapterCookie);
    if (!correctSubnet) {
#if 0
        Print("Discarding advertisement from ");
        Print(aUuid);
        Endpoint::EndpointBuf buf;
        endpt.AppendEndpoint(buf);
        Print(" at %s\n", buf.Ptr());
#endif
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
#if 0
        Print("Didn't match advertisement from ");
        Print(aUuid);
        Endpoint::EndpointBuf buf;
        endpt.AppendEndpoint(buf);
        Print(" at %s\n", buf.Ptr());
#endif
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
    AutoMutex a(iLock);
    if (LogUdn(aUuid, aLocation)) {
        iRoot++;
    }
}

void CpListenerMsearch::SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint /*aMaxAge*/)
{
    AutoMutex a(iLock);
    (void)LogUdn(aUuid, aLocation);
}

void CpListenerMsearch::SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint /*aMaxAge*/)
{
    AutoMutex a(iLock);
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
    AutoMutex a(iLock);
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

SuiteMsearch::SuiteMsearch(DvStack& aDvStack)
    : Suite("Msearches")
    , iDvStack(aDvStack)
{
    RandomiseUdn(iDvStack.Env(), gNameDevice1);
    RandomiseUdn(iDvStack.Env(), gNameDevice2);
    RandomiseUdn(iDvStack.Env(), gNameDevice2Embedded1);
    Print("UDNs: \n    ");
    Print(gNameDevice1);
    Print("\n    ");
    Print(gNameDevice2);
    Print("\n    ");
    Print(gNameDevice2Embedded1);
    Print("\n\n");
    Environment& env = iDvStack.Env();
    iBlocker = new Blocker(env);
    iListener = new CpListenerMsearch(env);
    NetworkAdapter* nif = env.NetworkAdapterList().CurrentAdapter(kAdapterCookie).Ptr();
    iListenerUnicast = new SsdpListenerUnicast(env, *iListener, nif->Address());
    nif->RemoveRef(kAdapterCookie);
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
    DviDevice* device = new DviDeviceStandard(iDvStack, gNameDevice1);
    iDevices[0] = device;
    device->SetAttribute("Upnp.Domain", "upnp.org");
    device->SetAttribute("Upnp.Type", "test1");
    device->SetAttribute("Upnp.Version", "1");
    AddService(device, new DviService(iDvStack, "upnp.org", "service1", 1));
    AddService(device, new DviService(iDvStack, "openhome.org", "service2", 3));
    AddService(device, new DviService(iDvStack, "upnp.org", "service3", 1));
    DviService* service = new DviService(iDvStack, "upnp.org", "service1", 1);
    TEST_THROWS(device->AddService(service), AssertionFailed);
    service->RemoveRef();
    device->SetEnabled();
    service = new DviService(iDvStack, "upnp.org", "service4", 1);
    TEST_THROWS(device->AddService(service), AssertionFailed);
    service->RemoveRef();

    device = new DviDeviceStandard(iDvStack, gNameDevice2);
    iDevices[1] = device;
    device->SetAttribute("Upnp.Domain", "openhome.org");
    device->SetAttribute("Upnp.Type", "test2");
    device->SetAttribute("Upnp.Version", "2");
    AddService(device, new DviService(iDvStack, "openhome.org", "service4", 2));
    AddService(device, new DviService(iDvStack, "openhome.org", "service5", 1));

    device = new DviDeviceStandard(iDvStack, gNameDevice2Embedded1);
    iDevices[1]->AddDevice(device);
    device->SetAttribute("Upnp.Domain", "openhome.org");
    device->SetAttribute("Upnp.Type", "test3");
    device->SetAttribute("Upnp.Version", "1");
    AddService(device, new DviService(iDvStack, "upnp.org", "service1", 1));
    AddService(device, new DviService(iDvStack, "openhome.org", "service6", 1));
    AddService(device, new DviService(iDvStack, "openhome.org", "service2", 3));
    service = new DviService(iDvStack, "openhome.org", "service5", 1);
    TEST_THROWS(device->AddService(service), AssertionFailed);
    service->RemoveRef();
    iDevices[1]->SetEnabled();
    device->SetEnabled();
    device = new DviDeviceStandard(iDvStack, kNameDummy);
    TEST_THROWS(iDevices[1]->AddDevice(device), AssertionFailed);
    device->Destroy();
    //Wait(); // allow time for initial annoucements to be delivered

    TestMsearchAll();
    TestMsearchRoot();
    TestMsearchUuid();
    TestMsearchDeviceType();
    TestMsearchServiceType();
}

void SuiteMsearch::Wait()
{
    iBlocker->Wait(iDvStack.Env().InitParams()->MsearchTimeSecs() + 1);
}

void SuiteMsearch::TestMsearchAll()
{
    iListener->Reset();
    iListenerUnicast->MsearchAll();
    Wait();
    if (iListener->RootDeviceCount() != 2) {
        Print("MsearchAll: found %u root devices (expected 2)\n", iListener->RootDeviceCount());
    }
    TEST(iListener->RootDeviceCount() == 2);
    TEST(iListener->DeviceCount() == 3);
    TEST(iListener->ServiceCount() == 8);
    TEST(iListener->Udns() == 7);
    if (iListener->TotalMessages() != 16) {
        Print("MsearchAll: received %u responses (expected 16)\n", iListener->TotalMessages());
    }
    TEST(iListener->TotalMessages() == 16);
    TEST(DeviceTypeMatches(iListener->Dev1Type(), "upnp.org:test1:1"));
    TEST(DeviceTypeMatches(iListener->Dev2Type(), "openhome.org:test2:2"));
    TEST(DeviceTypeMatches(iListener->Dev21Type(), "openhome.org:test3:1"));
    TEST(ServiceVectorContainsType(iListener->Services(), "upnp.org:service1:1"));
    TEST(ServiceVectorContainsType(iListener->Services(), "openhome.org:service2:3"));
    TEST(ServiceVectorContainsType(iListener->Services(), "upnp.org:service3:1"));
    TEST(ServiceVectorContainsType(iListener->Services(), "openhome.org:service4:2"));
    TEST(ServiceVectorContainsType(iListener->Services(), "openhome.org:service5:1"));
    TEST(ServiceVectorContainsType(iListener->Services(), "openhome.org:service6:1"));
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
    iListenerUnicast->MsearchDeviceType(Brn("openhome.org"), Brn("test2"), 2);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 1);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 2);
    TEST(iListener->TotalMessages() == 1);
    TEST(DeviceTypeMatches(iListener->Dev2Type(), "openhome.org:test2:2"));

    iListener->Reset();
    iListenerUnicast->MsearchDeviceType(Brn("openhome.org"), Brn("test3"), 1);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 1);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 4);
    TEST(iListener->TotalMessages() == 1);
    TEST(DeviceTypeMatches(iListener->Dev21Type(), "openhome.org:test3:1"));

    iListener->Reset();
    iListenerUnicast->MsearchDeviceType(Brn("upnp.org"), Brn("test1"), 1);
    iListenerUnicast->MsearchDeviceType(Brn("openhome.org"), Brn("test3"), 1);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 2);
    TEST(iListener->ServiceCount() == 0);
    TEST(iListener->Udns() == 5);
    TEST(iListener->TotalMessages() == 2);
    TEST(DeviceTypeMatches(iListener->Dev1Type(), "upnp.org:test1:1"));
    TEST(DeviceTypeMatches(iListener->Dev21Type(), "openhome.org:test3:1"));
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
    iListenerUnicast->MsearchServiceType(Brn("openhome.org"), Brn("service2"), 3);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 0);
    TEST(iListener->ServiceCount() == 2);
    TEST(iListener->Udns() == 5);
    TEST(iListener->TotalMessages() == 2);
    TEST(iListener->Services().size() == 2);
    TEST(0 == strcmp(iListener->Services()[0], "openhome.org:service2:3"));
    TEST(0 == strcmp(iListener->Services()[1], "openhome.org:service2:3"));

    iListener->Reset();
    iListenerUnicast->MsearchServiceType(Brn("openhome.org"), Brn("service5"), 1);
    Wait();
    TEST(iListener->RootDeviceCount() == 0);
    TEST(iListener->DeviceCount() == 0);
    TEST(iListener->ServiceCount() == 1);
    TEST(iListener->Udns() == 2);
    TEST(iListener->TotalMessages() == 1);
    TEST(iListener->Services().size() == 1);
    TEST(0 == strcmp(iListener->Services()[0], "openhome.org:service5:1"));
}


void TestDviDiscovery(DvStack& aDvStack)
{
    InitialisationParams* initParams = aDvStack.Env().InitParams();
    TUint oldMsearchTime = initParams->MsearchTimeSecs();
    initParams->SetMsearchTime(3); // higher time to give valgrind tests a hope of completing

    //Debug::SetLevel(Debug::kSsdpUnicast);
    Runner runner("SSDP discovery\n");
    runner.Add(new SuiteAlive(aDvStack));
    runner.Add(new SuiteMsearch(aDvStack));
    runner.Run();

    initParams->SetMsearchTime(oldMsearchTime);
}
