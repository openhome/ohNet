#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Private/Maths.h>

#include <stdlib.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

static Bwh gNameDevice1("device1");
static Bwh gNameDevice1_1("device1_1");
static Bwh gNameDevice1_2("device1_2");
static Bwh gNameDevice2("device2");

static void RandomiseUdn(Bwh& aUdn)
{
    aUdn.Grow(aUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    aUdn.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    std::vector<NetworkAdapter*>* subnetList = Stack::NetworkAdapterList().CreateSubnetList();
    TUint max = (*subnetList)[0]->Address();
    TUint seed = DviStack::ServerUpnp().Port((*subnetList)[0]->Address());
    SetRandomSeed(seed);
    Stack::NetworkAdapterList().DestroySubnetList(subnetList);
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
    DviDeviceStandard* iDevices[2];
};

DvDevices::DvDevices()
{
    RandomiseUdn(gNameDevice1);
    RandomiseUdn(gNameDevice1_1);
    RandomiseUdn(gNameDevice1_2);
    RandomiseUdn(gNameDevice2);

    DviDeviceStandard* device = new DviDeviceStandard(Brn(gNameDevice1));
    iDevices[0] = device;
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "test1");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", (const TChar*)gNameDevice1.Ptr());
    device->AddService(new DviService("a.b.c", "service1", 1));

    device = new DviDeviceStandard(Brn(gNameDevice1_1));
    iDevices[0]->AddDevice(device);
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "test3");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", (const TChar*)gNameDevice1_1.Ptr());
    device->AddService(new DviService("a.b.c", "service2", 1));
    device->AddService(new DviService("a.b.c", "service3", 1));
    device->SetEnabled();

    device = new DviDeviceStandard(Brn(gNameDevice1_2));
    iDevices[0]->AddDevice(device);
    device->SetAttribute("Upnp.Domain", "a.b.c");
    device->SetAttribute("Upnp.Type", "test4");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", (const TChar*)gNameDevice1_2.Ptr());
    device->AddService(new DviService("a.b.c", "service4", 1));
    device->SetEnabled();
    iDevices[0]->SetEnabled();

    device = new DviDeviceStandard(Brn(gNameDevice2));
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
    const TUint count = (TUint)iList.size();
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



void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    OptionBool loopback("-l", "--loopback", "Use the loopback adapter only");
    parser.AddOption(&loopback);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }
    if (loopback.Value()) {
        aInitParams->SetUseLoopbackNetworkAdapter();
    }
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCombined(subnet);
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
