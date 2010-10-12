#include <TestFramework.h>
#include <ZappTypes.h>
#include <Core/DvDevice.h>
#include <Core/DvZappOrgTestBasic1.h>
#include <Core/CpZappOrgTestBasic1.h>
#include <Zapp.h>
#include <Core/CpDevice.h>
#include <Core/CpDeviceUpnp.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>

#include <vector>

using namespace Zapp;
using namespace Zapp::TestFramework;

class ServiceTestBasic : public DvServiceZappOrgTestBasic1
{
public:
    ServiceTestBasic(DvDevice& aDevice);
private:
    void Increment(IInvocationResponse& aResponse, TUint aVersion, TUint aValue, IInvocationResponseUint& aResult);
    void Decrement(IInvocationResponse& aResponse, TUint aVersion, TInt aValue, IInvocationResponseInt& aResult);
    void Toggle(IInvocationResponse& aResponse, TUint aVersion, TBool aValue, IInvocationResponseBool& aResult);
    void EchoString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseString& aResult);
    void EchoBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseBinary& aResult);
};

class DeviceBasic
{
public:
    DeviceBasic();
    ~DeviceBasic();
private:
    DvDevice* iDevice;
    ServiceTestBasic* iTestBasic;
};


ServiceTestBasic::ServiceTestBasic(DvDevice& aDevice)
    : DvServiceZappOrgTestBasic1(aDevice)
{
    EnableActionIncrement();
    EnableActionDecrement();
    EnableActionToggle();
    EnableActionEchoString();
    EnableActionEchoBinary();
}

void ServiceTestBasic::Increment(IInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValue, IInvocationResponseUint& aResult)
{
    aResponse.Start();
    aResult.Write(++aValue);
    aResponse.End();
}

void ServiceTestBasic::Decrement(IInvocationResponse& aResponse, TUint /*aVersion*/, TInt aValue, IInvocationResponseInt& aResult)
{
    aResponse.Start();
    aResult.Write(--aValue);
    aResponse.End();
}

void ServiceTestBasic::Toggle(IInvocationResponse& aResponse, TUint /*aVersion*/, TBool aValue, IInvocationResponseBool& aResult)
{
    aResponse.Start();
    aResult.Write(!aValue);
    aResponse.End();
}

void ServiceTestBasic::EchoString(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValue, IInvocationResponseString& aResult)
{
    aResponse.Start();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aResponse.End();
}

void ServiceTestBasic::EchoBinary(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValue, IInvocationResponseBinary& aResult)
{
    aResponse.Start();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aResponse.End();
}


static Bwh gDeviceName("device");

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

DeviceBasic::DeviceBasic()
{
    RandomiseUdn(gDeviceName);
    iDevice = new DvDevice(gDeviceName);
    iDevice->SetAttribute("Upnp.Domain", "zapp.org");
    iDevice->SetAttribute("Upnp.Type", "Test");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "ZappTestDevice");
    iDevice->SetAttribute("Upnp.Manufacturer", "None");
    iDevice->SetAttribute("Upnp.ManufacturerUrl", "http://www.linn.co.uk");
    iDevice->SetAttribute("Upnp.ModelDescription", "Test service");
    iDevice->SetAttribute("Upnp.ModelName", "Zapp test device");
    iDevice->SetAttribute("Upnp.ModelNumber", "1");
    iDevice->SetAttribute("Upnp.ModelUrl", "http://www.linn.co.uk");
    iDevice->SetAttribute("Upnp.SerialNumber", "123456");
    iDevice->SetAttribute("Upnp.Upc", "123456654321");
    iTestBasic = new ServiceTestBasic(*iDevice);
    iDevice->SetEnabled();
}

DeviceBasic::~DeviceBasic()
{
    delete iTestBasic;
    delete iDevice;
}


class CpDevices
{
    static const TUint kTestIterations = 10;
public:
    CpDevices();
    ~CpDevices();
    void Test();
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
    const TUint count = iList.size();
    for (TUint i=0; i<count; i++) {
        iList[i]->RemoveRef();
    }
    iList.clear();
}

void CpDevices::Test()
{
    ASSERT(iList.size() != 0);
    CpProxyZappOrgTestBasic1* proxy = new CpProxyZappOrgTestBasic1(*(iList[0]));
    TUint i;

    Print("Unsigned integer arguments...\n");
    TUint valUint = 15;
    for (i=0; i<kTestIterations; i++) {
        TUint result;
        proxy->SyncIncrement(valUint, result);
        ASSERT(result == valUint+1);
        valUint = result;
    }

    Print("Integer arguments...\n");
    TInt valInt = 3;
    for (i=0; i<kTestIterations; i++) {
        TInt result;
        proxy->SyncDecrement(valInt, result);
        ASSERT(result == valInt-1);
        valInt = result;
    }

    Print("Boolean arguments...\n");
    TBool valBool = true;
    for (i=0; i<kTestIterations; i++) {
        TBool result;
        proxy->SyncToggle(valBool, result);
        ASSERT(result == !valBool);
        valBool = result;
    }

    Print("String arguments...\n");
    Brn valStr("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut "
               "labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco "
               "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
               "voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
               "non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valStr, result);
        ASSERT(result == valStr);
    }

    Print("Binary arguments...\n");
    char bin[256];
    for (i=0; i<256; i++) {
        bin[i] = (char)i;
    }
    Brn valBin((const TByte*)&bin[0], 256);
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoBinary(valStr, result);
        ASSERT(result == valStr);
    }

    delete proxy;
}

void CpDevices::Added(CpDevice& aDevice)
{
    iLock.Wait();
    if (aDevice.Udn() == gDeviceName) {
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
    aInitParams->SetMsearchTime(1);
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartCombined();

    Print("TestDvInvocation - starting\n");

    DeviceBasic* device = new DeviceBasic;
    CpDevices* deviceList = new CpDevices;
    FunctorCpDevice added = MakeFunctorCpDevice(*deviceList, &CpDevices::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*deviceList, &CpDevices::Removed);
    Brn domainName("zapp.org");
    Brn serviceType("TestBasic");
    TUint ver = 1;
    CpDeviceListUpnpServiceType* list =
                new CpDeviceListUpnpServiceType(domainName, serviceType, ver, added, removed);
    Blocker* blocker = new Blocker;
    blocker->Wait(aInitParams->MsearchTimeSecs());
    delete blocker;
    deviceList->Test();
    delete list;
    delete deviceList;
    delete device;

    Print("TestDvInvocation - completed\n");
    UpnpLibrary::Close();
}
