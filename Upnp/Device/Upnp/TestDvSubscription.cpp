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
    void SetUint(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint);
    void GetUint(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValueUint);
    void SetInt(IInvocationResponse& aResponse, TUint aVersion, TInt aValueInt);
    void GetInt(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aValueInt);
    void SetBool(IInvocationResponse& aResponse, TUint aVersion, TBool aValueBool);
    void GetBool(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValueBool);
    void SetMultiple(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint, TInt aValueInt, TBool aValueBool);
    void SetString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueStr);
    void GetString(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValueStr);
    void SetBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueBin);
    void GetBinary(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aValueBin);
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
    SetPropertyVarUint(0);
    SetPropertyVarInt(0);
    SetPropertyVarBool(false);
    SetPropertyVarStr(Brx::Empty());
    SetPropertyVarBin(Brx::Empty());

    EnableActionSetUint();
    EnableActionGetUint();
    EnableActionSetInt();
    EnableActionGetInt();
    EnableActionSetBool();
    EnableActionGetBool();
    EnableActionSetMultiple();
    EnableActionSetString();
    EnableActionGetString();
    EnableActionSetBinary();
    EnableActionGetBinary();
}

void ServiceTestBasic::SetUint(IInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValueUint)
{
    SetPropertyVarUint(aValueUint);
    aResponse.Start();
    aResponse.End();
}

void ServiceTestBasic::GetUint(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseUint& aValueUint)
{
    aResponse.Start();
    TUint val;
    GetPropertyVarUint(val);
    aValueUint.Write(val);
    aResponse.End();
}

void ServiceTestBasic::SetInt(IInvocationResponse& aResponse, TUint /*aVersion*/, TInt aValueInt)
{
    SetPropertyVarInt(aValueInt);
    aResponse.Start();
    aResponse.End();
}

void ServiceTestBasic::GetInt(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseInt& aValueInt)
{
    aResponse.Start();
    TInt val;
    GetPropertyVarInt(val);
    aValueInt.Write(val);
    aResponse.End();
}

void ServiceTestBasic::SetBool(IInvocationResponse& aResponse, TUint /*aVersion*/, TBool aValueBool)
{
    SetPropertyVarBool(aValueBool);
    aResponse.Start();
    aResponse.End();
}

void ServiceTestBasic::GetBool(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseBool& aValueBool)
{
    aResponse.Start();
    TBool val;
    GetPropertyVarBool(val);
    aValueBool.Write(val);
    aResponse.End();
}

void ServiceTestBasic::SetMultiple(IInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValueUint, TInt aValueInt, TBool aValueBool)
{
    SetPropertyVarUint(aValueUint);
    SetPropertyVarInt(aValueInt);
    SetPropertyVarBool(aValueBool);
    aResponse.Start();
    aResponse.End();
}

void ServiceTestBasic::SetString(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValueStr)
{
    SetPropertyVarStr(aValueStr);
    aResponse.Start();
    aResponse.End();
}

void ServiceTestBasic::GetString(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseString& aValueStr)
{
    aResponse.Start();
    Brhz val;
    GetPropertyVarStr(val);
    aValueStr.Write(val);
    aValueStr.WriteFlush();
    aResponse.End();
}

void ServiceTestBasic::SetBinary(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValueBin)
{
    SetPropertyVarBin(aValueBin);
    aResponse.Start();
    aResponse.End();
}

void ServiceTestBasic::GetBinary(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseBinary& aValueBin)
{
    aResponse.Start();
    Brh val;
    GetPropertyVarBin(val);
    aValueBin.Write(val);
    aValueBin.WriteFlush();
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
public:
    CpDevices();
    ~CpDevices();
    void Test();
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    void SingleChanged();
    void UpdatesComplete();
private:
    Mutex iLock;
    std::vector<CpDevice*> iList;
    Semaphore iSingleChanged;
    Semaphore iUpdatesComplete;
};

CpDevices::CpDevices()
    : iLock("DLMX")
    , iSingleChanged("DSB1", 0)
    , iUpdatesComplete("DSB2", 0)
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
    ASSERT(iList.size() == 1);
    CpProxyZappOrgTestBasic1* proxy = new CpProxyZappOrgTestBasic1(*(iList[0]));
    Functor functor = MakeFunctor(*this, &CpDevices::UpdatesComplete);
    proxy->SetPropertyChanged(functor);
    proxy->Subscribe();
    iUpdatesComplete.Wait(); // wait for initial event

    // set callbacks for individual property changes now to avoid all being run by initial event
    functor = MakeFunctor(*this, &CpDevices::SingleChanged);
    proxy->SetPropertyVarUintChanged(functor);
    proxy->SetPropertyVarIntChanged(functor);
    proxy->SetPropertyVarBoolChanged(functor);
    proxy->SetPropertyVarStrChanged(functor);
    proxy->SetPropertyVarBinChanged(functor);


    /* For each property,
         call the setter action it
         wait on a property being updated
         check that the property matches the value set
         check that the getter action matches the property
    */

    Print("Uint...\n");
    proxy->SyncSetUint(1);
    iSingleChanged.Wait();
    TUint propUint;
    proxy->PropertyVarUint(propUint);
    ASSERT(propUint == 1);
    TUint valUint;
    proxy->SyncGetUint(valUint);
    ASSERT(propUint == valUint);

    Print("Int...\n");
    proxy->SyncSetInt(-99);
    iSingleChanged.Wait();
    TInt propInt;
    proxy->PropertyVarInt(propInt);
    ASSERT(propInt == -99);
    TInt valInt;
    proxy->SyncGetInt(valInt);
    ASSERT(propInt == valInt);

    Print("Bool...\n");
    proxy->SyncSetBool(true);
    iSingleChanged.Wait();
    TBool propBool;
    proxy->PropertyVarBool(propBool);
    ASSERT(propBool);
    TBool valBool;
    proxy->SyncGetBool(valBool);
    ASSERT(valBool);

    Print("String...\n");
    Brn str("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut "
            "labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco "
            "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
            "voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
            "non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    proxy->SyncSetString(str);
    iSingleChanged.Wait();
    Brhz propStr;
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    // test again to check that PropertyVarStr didn't TransferTo the property
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    Brh valStr;
    proxy->SyncGetString(valStr);
    ASSERT(propStr == valStr);

    Print("Binary...\n");
    char bin[256];
    for (TUint i=0; i<256; i++) {
        bin[i] = (char)i;
    }
    Brn bufBin((const TByte*)&bin[0], 256);
    proxy->SyncSetBinary(bufBin);
    iSingleChanged.Wait();
    Brh propBin;
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    // test again to check that PropertyVarBin didn't TransferTo the property
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    Brh valBin;
    proxy->SyncGetBinary(valBin);
    ASSERT(propBin == valBin);

    Print("Multiple...\n");
    (void)iUpdatesComplete.Clear();
    proxy->SyncSetMultiple(15, 658, false);
    iUpdatesComplete.Wait();
    proxy->PropertyVarUint(propUint);
    ASSERT(propUint == 15);
    proxy->SyncGetUint(valUint);
    ASSERT(propUint == valUint);
    proxy->PropertyVarInt(propInt);
    ASSERT(propInt == 658);
    proxy->SyncGetInt(valInt);
    ASSERT(propInt == valInt);
    proxy->PropertyVarBool(propBool);
    ASSERT(!propBool);
    proxy->SyncGetBool(valBool);
    ASSERT(!valBool);

    delete proxy; // automatically unsubscribes
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

void CpDevices::SingleChanged()
{
    iSingleChanged.Signal();
}

void CpDevices::UpdatesComplete()
{
    iUpdatesComplete.Signal();
}




void Zapp::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    aInitParams->SetMsearchTime(1);
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartCombined();
    //Debug::SetLevel(Debug::kError);

    Print("TestDvSubscription - starting\n");

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

    Print("TestDvSubscription - completed\n");
    UpnpLibrary::Close();
}
