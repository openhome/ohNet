#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Core/CpOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Net/Private/Stack.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class ProviderTestBasic : public DvProviderOpenhomeOrgTestBasic1
{
public:
    ProviderTestBasic(DvDevice& aDevice);
private:
    void Increment(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult);
    void Decrement(IDvInvocation& aInvocation, TInt aValue, IDvInvocationResponseInt& aResult);
    void Toggle(IDvInvocation& aInvocation, TBool aValue, IDvInvocationResponseBool& aResult);
    void EchoString(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseString& aResult);
    void EchoBinary(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseBinary& aResult);
};

class DeviceBasic
{
public:
    DeviceBasic();
    ~DeviceBasic();
private:
    DvDeviceStandard* iDevice;
    ProviderTestBasic* iTestBasic;
};


ProviderTestBasic::ProviderTestBasic(DvDevice& aDevice)
    : DvProviderOpenhomeOrgTestBasic1(aDevice)
{
    // Initialise all properties in case external control points decide to subscribe to this service
    EnablePropertyVarUint();
    EnablePropertyVarInt();
    EnablePropertyVarBool();
    EnablePropertyVarStr();
    EnablePropertyVarBin();
    SetPropertyVarUint(0);
    SetPropertyVarInt(0);
    SetPropertyVarBool(false);
    SetPropertyVarStr(Brx::Empty());
    SetPropertyVarBin(Brx::Empty());

    EnableActionIncrement();
    EnableActionDecrement();
    EnableActionToggle();
    EnableActionEchoString();
    EnableActionEchoBinary();
}

void ProviderTestBasic::Increment(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult)
{
    ASSERT(aInvocation.Version() == 1);
    aInvocation.StartResponse();
    aResult.Write(++aValue);
    aInvocation.EndResponse();
}

void ProviderTestBasic::Decrement(IDvInvocation& aInvocation, TInt aValue, IDvInvocationResponseInt& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(--aValue);
    aInvocation.EndResponse();
}

void ProviderTestBasic::Toggle(IDvInvocation& aInvocation, TBool aValue, IDvInvocationResponseBool& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(!aValue);
    aInvocation.EndResponse();
}

void ProviderTestBasic::EchoString(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseString& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTestBasic::EchoBinary(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseBinary& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aInvocation.EndResponse();
}


static Bwh gDeviceName("device");

static void RandomiseUdn(Bwh& aUdn)
{
    aUdn.Grow(aUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    aUdn.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    std::vector<NetworkAdapter*>* subnetList = Stack::NetworkAdapterList().CreateSubnetList();
    TUint max = (*subnetList)[0]->Address();
    Stack::NetworkAdapterList().DestroySubnetList(subnetList);
    (void)Ascii::AppendDec(buf, Random(max));
    aUdn.Append(buf);
    aUdn.PtrZ();
}

DeviceBasic::DeviceBasic()
{
    RandomiseUdn(gDeviceName);
    iDevice = new DvDeviceStandard(gDeviceName);
    iDevice->SetAttribute("Upnp.Domain", "openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Test");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "ohNetTestDevice");
    iDevice->SetAttribute("Upnp.Manufacturer", "None");
    iDevice->SetAttribute("Upnp.ModelName", "ohNet test device");
    iTestBasic = new ProviderTestBasic(*iDevice);
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
    CpDevices(Semaphore& aAddedSem);
    ~CpDevices();
    void Test();
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    Mutex iLock;
    std::vector<CpDevice*> iList;
    Semaphore& iAddedSem;
};

CpDevices::CpDevices(Semaphore& aAddedSem)
    : iLock("DLMX")
    , iAddedSem(aAddedSem)
{
}

CpDevices::~CpDevices()
{
    const TUint count = (TUint)iList.size();
    for (TUint i=0; i<count; i++) {
        iList[i]->RemoveRef();
    }
    iList.clear();
}

void CpDevices::Test()
{
    ASSERT(iList.size() != 0);
    CpProxyOpenhomeOrgTestBasic1* proxy = new CpProxyOpenhomeOrgTestBasic1(*(iList[0]));
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
        proxy->SyncEchoBinary(valBin, result);
        ASSERT(result == valBin);
    }

    delete proxy;
}

void CpDevices::Added(CpDevice& aDevice)
{
    iLock.Wait();
    if (aDevice.Udn() == gDeviceName) {
        iList.push_back(&aDevice);
        aDevice.AddRef();
        iAddedSem.Signal();
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
    aInitParams->SetMsearchTime(1);
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCombined(subnet);

    Print("TestDvInvocation - starting\n");

    Semaphore* sem = new Semaphore("SEM1", 0);
    DeviceBasic* device = new DeviceBasic;
    CpDevices* deviceList = new CpDevices(*sem);;
    FunctorCpDevice added = MakeFunctorCpDevice(*deviceList, &CpDevices::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*deviceList, &CpDevices::Removed);
    Brn domainName("openhome.org");
    Brn serviceType("TestBasic");
    TUint ver = 1;
    CpDeviceListUpnpServiceType* list =
                new CpDeviceListUpnpServiceType(domainName, serviceType, ver, added, removed);
    sem->Wait(30*1000); // allow up to 30 seconds to find our one device
    delete sem;
    deviceList->Test();
    delete list;
    delete deviceList;
    delete device;

    Print("TestDvInvocation - completed\n");
    UpnpLibrary::Close();
}
