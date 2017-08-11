#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Private/NetworkAdapterList.h>

#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

static Bwh gNameDevice1("device1");
static Bwh gNameDevice1_1("device1_1");
static Bwh gNameDevice1_2("device1_2");
static Bwh gNameDevice2("device2");

static void AddService(DviDevice* aDevice, DviService* aService)
{
    aDevice->AddService(aService);
    aService->RemoveRef();
}


class DvDevices
{
public:
    DvDevices(DvStack& aDvStack);
    ~DvDevices();
private:
    DviDeviceStandard* iDevices[2];
};

DvDevices::DvDevices(DvStack& aDvStack)
{
    RandomiseUdn(aDvStack.Env(), gNameDevice1);
    RandomiseUdn(aDvStack.Env(), gNameDevice1_1);
    RandomiseUdn(aDvStack.Env(), gNameDevice1_2);
    RandomiseUdn(aDvStack.Env(), gNameDevice2);

    DviDeviceStandard* device = new DviDeviceStandard(aDvStack, Brn(gNameDevice1));
    iDevices[0] = device;
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "test1");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", (const TChar*)gNameDevice1.Ptr());
    AddService(device, new DviService(aDvStack, "a.b.c", "service1", 1));

    device = new DviDeviceStandard(aDvStack, Brn(gNameDevice1_1));
    iDevices[0]->AddDevice(device);
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "test3");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", (const TChar*)gNameDevice1_1.Ptr());
    AddService(device, new DviService(aDvStack, "a.b.c", "service2", 1));
    AddService(device, new DviService(aDvStack, "a.b.c", "service3", 1));
    device->SetEnabled();

    device = new DviDeviceStandard(aDvStack, Brn(gNameDevice1_2));
    iDevices[0]->AddDevice(device);
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "test4");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", (const TChar*)gNameDevice1_2.Ptr());
    AddService(device, new DviService(aDvStack, "a.b.c", "service4", 1));
    device->SetEnabled();
    iDevices[0]->SetEnabled();

    device = new DviDeviceStandard(aDvStack, Brn(gNameDevice2));
    iDevices[1] = device;
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "test2");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", (const TChar*)gNameDevice2.Ptr());
    AddService(device, new DviService(aDvStack, "a.b.c", "service1", 1));
    AddService(device, new DviService(aDvStack, "a.b.c", "service2", 1));
    iDevices[1]->SetEnabled();
}

DvDevices::~DvDevices()
{
    iDevices[0]->Destroy();
    iDevices[1]->Destroy();
}



class CpDevices
{
public:
    CpDevices();
    ~CpDevices();
    void Clear();
    void Validate(std::vector<const char*>& aExpectedUdns);
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    Mutex iLock;
    std::vector<CpDevice*> iList;
    Semaphore iSem;
    TUint iTargetCount;
};

CpDevices::CpDevices()
    : iLock("DLMX")
    , iSem("DLSM", 0)
    , iTargetCount(0)
{
}

CpDevices::~CpDevices()
{
    Clear();
}

void CpDevices::Clear()
{
    iLock.Wait();
    const TUint count = (TUint)iList.size();
    for (TUint i=0; i<count; i++) {
        iList[i]->RemoveRef();
    }
    iList.clear();
    (void)iSem.Clear();
    iLock.Signal();
}

void CpDevices::Validate(std::vector<const char*>& aExpectedUdns)
{
    iLock.Wait();
    TBool wait = (aExpectedUdns.size() > iList.size());
    iTargetCount = (TUint)aExpectedUdns.size();
    iLock.Signal();
    if (wait) {
        try {
            iSem.Wait(30 * 1000);
        }
        catch (Timeout&) {
            Print("ERROR: Failed to detect sufficient devices\n");
        }
    }
    if (aExpectedUdns.size() != iList.size()) {
        Print("ERROR: expected %u devices, found %u\n", aExpectedUdns.size(), iList.size());
        ASSERTS();
    }
    while (aExpectedUdns.size() > 0) {
        Brn expected(aExpectedUdns[0]);
        TBool found = false;
        for (TUint i=0; i<iList.size(); i++) {
            if (expected == iList[i]->Udn()) {
                Brh friendlyName;
                iList[i]->GetAttribute("Upnp.FriendlyName", friendlyName);
                ASSERT(friendlyName == expected);
                aExpectedUdns.erase(aExpectedUdns.begin());
                found = true;
                break;
            }
        }
        if (!found) {
            Print("Failed to find target device amongst %u candidates\n", iList.size());
            for (TUint i=0; i<iList.size(); i++) {
                Print("    ");
                Print(iList[i]->Udn());
            }
            Print("\nExpected:");
            for (TUint i=0; i<aExpectedUdns.size(); i++) {
                Print("    %s", aExpectedUdns[i]);
            }
            Print("\n");
        }
        ASSERT(found);
    }
    ASSERT(aExpectedUdns.size() == 0);
}

void CpDevices::Added(CpDevice& aDevice)
{
    iLock.Wait();
    const Brx& udn = aDevice.Udn();
    if (udn == gNameDevice1 || udn == gNameDevice1_1 || udn == gNameDevice1_2 || udn == gNameDevice2) {
        iList.push_back(&aDevice);
        aDevice.AddRef();
    }
    if ((TUint)iList.size() == iTargetCount) {
        iSem.Signal();
    }
    iLock.Signal();
}

void CpDevices::Removed(CpDevice& aDevice)
{
    /* A device sends out byebye messages before alives after being enabled.
    (This is required for many buggy control points which don't spot a change of location otherwise.)
    Its possible that the last of these byebyes may get interleaved with the first msearch responses,
    leading to a device being added, removed, then added again.
    Accept that this is possible and cope with devices being removed. */
    iLock.Wait();
    const Brx& udn = aDevice.Udn();
    for (TUint i=0; i<iList.size(); i++) {
        if (iList[i]->Udn() == udn) {
            iList[i]->RemoveRef();
            iList.erase(iList.begin() + i);
            break;
        }
    }
    iLock.Signal();
}



void TestDviDeviceList(CpStack& aCpStack, DvStack& aDvStack)
{
    InitialisationParams* initParams = aDvStack.Env().InitParams();
    TUint oldMsearchTime = initParams->MsearchTimeSecs();
    initParams->SetMsearchTime(1);

//    Debug::SetLevel(Debug::kDevice | Debug::kDvDevice | Debug::kXmlFetch );
//    Debug::SetSeverity(Debug::kSeverityError);

    Print("TestDviDeviceList - starting\n");

    DvDevices* devices = new DvDevices(aDvStack);
    CpDevices* deviceList = new CpDevices;
    FunctorCpDevice added = MakeFunctorCpDevice(*deviceList, &CpDevices::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*deviceList, &CpDevices::Removed);

    Print("Count devices implementing service1\n");
    Brn domainName("a.b.c");
    Brn serviceType("service1");
    TUint ver = 1;
    CpDeviceListUpnpServiceType* list =
                new CpDeviceListUpnpServiceType(aCpStack, domainName, serviceType, ver, added, removed);
    std::vector<const char*> udns;
    udns.push_back((const char*)gNameDevice1.Ptr());
    udns.push_back((const char*)gNameDevice2.Ptr());
    deviceList->Validate(udns);
    udns.clear();
    delete list;
    deviceList->Clear();

    Print("Count devices implementing service2\n");
    serviceType.Set("service2");
    list = new CpDeviceListUpnpServiceType(aCpStack, domainName, serviceType, ver, added, removed);
    udns.push_back((const char*)gNameDevice1_1.Ptr());
    udns.push_back((const char*)gNameDevice2.Ptr());
    deviceList->Validate(udns);
    udns.clear();
    delete list;

    delete deviceList;
    delete devices;

    Print("TestDviDeviceList - completed\n");
    initParams->SetMsearchTime(oldMsearchTime);
}
