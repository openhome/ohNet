#include <TestFramework.h>
#include <ZappTypes.h>
#include <Zapp.h>
#include <Debug.h>
#include <DviDevice.h>
#include <DviService.h>
#include <Stack.h>
#include <Core/CpDevice.h>
#include <Core/CpDeviceUpnp.h>
#include <Maths.h>

#include <stdlib.h>
#include <vector>

using namespace Zapp;
using namespace Zapp::TestFramework;

static Bwh gNameDevice1("device1");
static Bwh gNameDevice1_1("device1_1");
static Bwh gNameDevice1_2("device1_2");
static Bwh gNameDevice2("device2");

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

class DvDevices
{
public:
    DvDevices();
    ~DvDevices();
private:
    DviDevice* iDevices[2];
};

DvDevices::DvDevices()
{
    RandomiseUdn(gNameDevice1);
    RandomiseUdn(gNameDevice1_1);
    RandomiseUdn(gNameDevice1_2);
    RandomiseUdn(gNameDevice2);

    DviDevice* device = new DviDevice(Brn(gNameDevice1));
    iDevices[0] = device;
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "test1");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", (const TChar*)gNameDevice1.Ptr());
    device->AddService(new DviService("a.b.c", "service1", 1));

    device = new DviDevice(Brn(gNameDevice1_1));
    iDevices[0]->AddDevice(device);
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "test3");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", (const TChar*)gNameDevice1_1.Ptr());
    device->AddService(new DviService("a.b.c", "service2", 1));
    device->AddService(new DviService("a.b.c", "service3", 1));
    device->SetEnabled();

    device = new DviDevice(Brn(gNameDevice1_2));
    iDevices[0]->AddDevice(device);
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "test4");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", (const TChar*)gNameDevice1_2.Ptr());
    device->AddService(new DviService("a.b.c", "service4", 1));
    device->SetEnabled();
    iDevices[0]->SetEnabled();

    device = new DviDevice(Brn(gNameDevice2));
    iDevices[1] = device;
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "test2");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", (const TChar*)gNameDevice2.Ptr());
    device->AddService(new DviService("a.b.c", "service1", 1));
    device->AddService(new DviService("a.b.c", "service2", 1));
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
};

CpDevices::CpDevices()
    : iLock("DLMX")
{
}

CpDevices::~CpDevices()
{
    Clear();
}

void CpDevices::Clear()
{
    iLock.Wait();
    const TUint count = iList.size();
    for (TUint i=0; i<count; i++) {
        iList[i]->RemoveRef();
    }
    iList.clear();
    iLock.Signal();
}

void CpDevices::Validate(std::vector<const char*>& aExpectedUdns)
{
    ASSERT(aExpectedUdns.size() == iList.size());
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
    iLock.Signal();
}

void CpDevices::Removed(CpDevice& /*aDevice*/)
{
}



void Zapp::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartCombined();
    //Debug::SetLevel(Debug::kDevice/*Debug::kXmlFetch | Debug::kHttp*/);

    Print("TestDviDeviceList - starting\n");

    DvDevices* devices = new DvDevices;
    CpDevices* deviceList = new CpDevices;
    FunctorCpDevice added = MakeFunctorCpDevice(*deviceList, &CpDevices::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*deviceList, &CpDevices::Removed);

    Print("Count devices implementing service1\n");
    Brn domainName("a.b.c");
    Brn serviceType("service1");
    TUint ver = 1;
    CpDeviceListUpnpServiceType* list =
                new CpDeviceListUpnpServiceType(domainName, serviceType, ver, added, removed);
    Blocker* blocker = new Blocker;
    blocker->Wait(aInitParams->MsearchTimeSecs());
    std::vector<const char*> udns;
    udns.push_back((const char*)gNameDevice1.Ptr());
    udns.push_back((const char*)gNameDevice2.Ptr());
    deviceList->Validate(udns);
    udns.clear();
    delete list;
    deviceList->Clear();

    Print("Count devices implementing service2\n");
    serviceType.Set("service2");
    list = new CpDeviceListUpnpServiceType(domainName, serviceType, ver, added, removed);
    blocker->Wait(aInitParams->MsearchTimeSecs());
    udns.push_back((const char*)gNameDevice1_1.Ptr());
    udns.push_back((const char*)gNameDevice2.Ptr());
    deviceList->Validate(udns);
    udns.clear();
    delete list;

    delete blocker;
    delete deviceList;
    delete devices;

    Print("TestDviDeviceList - completed\n");
    UpnpLibrary::Close();
}
