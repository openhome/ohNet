#include <TestFramework.h>
#include <ZappTypes.h>
#include <Std/DvDevice.h>
#include <Std/DvZappOrgTestBasic1.h>
#include <Std/CpZappOrgTestBasic1.h>
#include <Zapp.h>
#include <Std/CpDevice.h>
#include <Std/CpDeviceUpnp.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>

#include <string>
#include <vector>

using namespace Zapp;
using namespace Zapp::TestFramework;

class ServiceTestBasic : public DvServiceZappOrgTestBasic1Cpp
{
public:
    ServiceTestBasic(DvDeviceStd& aDevice);
private:
    void Increment(uint32_t aVersion, uint32_t aValue, uint32_t& aResult);
    void Decrement(uint32_t aVersion, int32_t aValue, int32_t& aResult);
    void Toggle(uint32_t aVersion, bool aValue, bool& aResult);
    void EchoString(uint32_t aVersion, const std::string& aValue, std::string& aResult);
    void EchoBinary(uint32_t aVersion, const std::string& aValue, std::string& aResult);
    void SetUint(uint32_t aVersion, uint32_t aValueUint);
    void GetUint(uint32_t aVersion, uint32_t& aValueUint);
    void SetInt(uint32_t aVersion, int32_t aValueInt);
    void GetInt(uint32_t aVersion, int32_t& aValueInt);
    void SetBool(uint32_t aVersion, bool aValueBool);
    void GetBool(uint32_t aVersion, bool& aValueBool);
    void SetMultiple(uint32_t aVersion, uint32_t aValueUint, int32_t aValueInt, bool aValueBool);
    void SetString(uint32_t aVersion, const std::string& aValueStr);
    void GetString(uint32_t aVersion, std::string& aValueStr);
    void SetBinary(uint32_t aVersion, const std::string& aValueBin);
    void GetBinary(uint32_t aVersion, std::string& aValueBin);
};

class DeviceBasic
{
public:
    DeviceBasic();
    ~DeviceBasic();
private:
    DvDeviceStd* iDevice;
    ServiceTestBasic* iTestBasic;
};


ServiceTestBasic::ServiceTestBasic(DvDeviceStd& aDevice)
    : DvServiceZappOrgTestBasic1Cpp(aDevice)
{
    SetPropertyVarUint(0);
    SetPropertyVarInt(0);
    SetPropertyVarBool(false);
	std::string empty;
    SetPropertyVarStr(empty);
    SetPropertyVarBin(empty);

    EnableActionIncrement();
    EnableActionDecrement();
    EnableActionToggle();
    EnableActionEchoString();
    EnableActionEchoBinary();
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

void ServiceTestBasic::Increment(uint32_t /*aVersion*/, uint32_t aValue, uint32_t& aResult)
{
    aResult = ++aValue;
}

void ServiceTestBasic::Decrement(uint32_t /*aVersion*/, int32_t aValue, int32_t& aResult)
{
    aResult = --aValue;
}

void ServiceTestBasic::Toggle(uint32_t /*aVersion*/, bool aValue, bool& aResult)
{
    aResult = !aValue;
}

void ServiceTestBasic::EchoString(uint32_t /*aVersion*/, const std::string& aValue, std::string& aResult)
{
    aResult.assign(aValue);
}

void ServiceTestBasic::EchoBinary(uint32_t /*aVersion*/, const std::string& aValue, std::string& aResult)
{
    aResult.assign(aValue);
}

void ServiceTestBasic::SetUint(uint32_t /*aVersion*/, uint32_t aValueUint)
{
    SetPropertyVarUint(aValueUint);
}

void ServiceTestBasic::GetUint(uint32_t /*aVersion*/, uint32_t& aValueUint)
{
    GetPropertyVarUint(aValueUint);
}

void ServiceTestBasic::SetInt(uint32_t /*aVersion*/, int32_t aValueInt)
{
    SetPropertyVarInt(aValueInt);
}

void ServiceTestBasic::GetInt(uint32_t /*aVersion*/, int32_t& aValueInt)
{
    GetPropertyVarInt(aValueInt);
}

void ServiceTestBasic::SetBool(uint32_t /*aVersion*/, bool aValueBool)
{
    SetPropertyVarBool(aValueBool);
}

void ServiceTestBasic::GetBool(uint32_t /*aVersion*/, bool& aValueBool)
{
    GetPropertyVarBool(aValueBool);
}

void ServiceTestBasic::SetMultiple(uint32_t /*aVersion*/, uint32_t aValueUint, int32_t aValueInt, bool aValueBool)
{
    SetPropertyVarUint(aValueUint);
    SetPropertyVarInt(aValueInt);
    SetPropertyVarBool(aValueBool);
}

void ServiceTestBasic::SetString(uint32_t /*aVersion*/, const std::string& aValueStr)
{
    SetPropertyVarStr(aValueStr);
}

void ServiceTestBasic::GetString(uint32_t /*aVersion*/, std::string& aValueStr)
{
    GetPropertyVarStr(aValueStr);
}

void ServiceTestBasic::SetBinary(uint32_t /*aVersion*/, const std::string& aValueBin)
{
    SetPropertyVarBin(aValueBin);
}

void ServiceTestBasic::GetBinary(uint32_t /*aVersion*/, std::string& aValueBin)
{
    GetPropertyVarBin(aValueBin);
}


static std::string gDeviceName("device");

static void RandomiseUdn(std::string& aUdn)
{
    Bwh udn;
    udn.Grow(aUdn.length() + 1 + Ascii::kMaxUintStringBytes + 1);
    Brn buf((const TByte*)aUdn.c_str(), aUdn.length());
    udn.Append(buf);
    udn.Append('-');
    Bws<Ascii::kMaxUintStringBytes> addr;
    NetworkInterface* nif = Stack::NetworkInterfaceList().CurrentInterface();
    TUint max = nif->Address();
    delete nif;
    (void)Ascii::AppendDec(addr, Random(max));
    udn.Append(addr);
    udn.PtrZ();
    aUdn.assign((const char*)udn.Ptr(), udn.Bytes());
}

DeviceBasic::DeviceBasic()
{
    RandomiseUdn(gDeviceName);
    iDevice = new DvDeviceStd(gDeviceName);
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
    void TestActions();
    void TestSubscriptions();
    void Added(CpDeviceCpp& aDevice);
    void Removed(CpDeviceCpp& aDevice);
private:
    void SingleChanged();
    void UpdatesComplete();
private:
    Mutex iLock;
    std::vector<CpDeviceCpp*> iList;
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

void CpDevices::TestActions()
{
    Print("  Actions\n");
    ASSERT(iList.size() != 0);
    CpProxyZappOrgTestBasic1Cpp* proxy = new CpProxyZappOrgTestBasic1Cpp(*(iList[0]));
    TUint i;

    Print("    Unsigned integer arguments...\n");
    TUint valUint = 15;
    for (i=0; i<kTestIterations; i++) {
        TUint result;
        proxy->SyncIncrement(valUint, result);
        ASSERT(result == valUint+1);
        valUint = result;
    }

    Print("    Integer arguments...\n");
    TInt valInt = 3;
    for (i=0; i<kTestIterations; i++) {
        TInt result;
        proxy->SyncDecrement(valInt, result);
        ASSERT(result == valInt-1);
        valInt = result;
    }

    Print("    Boolean arguments...\n");
    TBool valBool = true;
    for (i=0; i<kTestIterations; i++) {
        TBool result;
        proxy->SyncToggle(valBool, result);
        ASSERT(result == !valBool);
        valBool = result;
    }

    Print("    String arguments...\n");
    std::string valStr("<&'tag\">");
    for (i=0; i<kTestIterations; i++) {
        std::string result;
        proxy->SyncEchoString(valStr, result);
        ASSERT(result == valStr);
    }

    Print("    Binary arguments...\n");
    char bin[256];
    for (i=0; i<256; i++) {
        bin[i] = (char)i;
    }
    std::string valBin(&bin[0], 256);
    for (i=0; i<kTestIterations; i++) {
        std::string result;
        proxy->SyncEchoBinary(valStr, result);
        ASSERT(result == valStr);
    }

    delete proxy;
}

void CpDevices::TestSubscriptions()
{
    Print("  Subscriptions\n");
    ASSERT(iList.size() == 1);
    CpProxyZappOrgTestBasic1Cpp* proxy = new CpProxyZappOrgTestBasic1Cpp(*(iList[0]));
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

    Print("    Uint...\n");
    proxy->SyncSetUint(1);
    iSingleChanged.Wait();
    TUint propUint;
    proxy->PropertyVarUint(propUint);
    ASSERT(propUint == 1);
    TUint valUint;
    proxy->SyncGetUint(valUint);
    ASSERT(propUint == valUint);

    Print("    Int...\n");
    proxy->SyncSetInt(-99);
    iSingleChanged.Wait();
    TInt propInt;
    proxy->PropertyVarInt(propInt);
    ASSERT(propInt == -99);
    TInt valInt;
    proxy->SyncGetInt(valInt);
    ASSERT(propInt == valInt);

    Print("    Bool...\n");
    proxy->SyncSetBool(true);
    iSingleChanged.Wait();
    TBool propBool;
    proxy->PropertyVarBool(propBool);
    ASSERT(propBool);
    TBool valBool;
    proxy->SyncGetBool(valBool);
    ASSERT(valBool);

    Print("    String...\n");
    std::string str("<&'tag\">");
    proxy->SyncSetString(str);
    iSingleChanged.Wait();
    std::string propStr;
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    // test again to check that PropertyVarStr didn't TransferTo the property
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    std::string valStr;
    proxy->SyncGetString(valStr);
    ASSERT(propStr == valStr);

    Print("    Binary...\n");
    char bin[256];
    for (TUint i=0; i<256; i++) {
        bin[i] = (char)i;
    }
    std::string bufBin(&bin[0], 256);
    proxy->SyncSetBinary(bufBin);
    iSingleChanged.Wait();
    std::string propBin;
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    // test again to check that PropertyVarBin didn't TransferTo the property
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    std::string valBin;
    proxy->SyncGetBinary(valBin);
    ASSERT(propBin == valBin);

    Print("    Multiple...\n");
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

void CpDevices::Added(CpDeviceCpp& aDevice)
{
    iLock.Wait();
    if (aDevice.Udn() == gDeviceName) {
        iList.push_back(&aDevice);
        aDevice.AddRef();
    }
    iLock.Signal();
}

void CpDevices::Removed(CpDeviceCpp& /*aDevice*/)
{
}

void CpDevices::SingleChanged()
{
    //Log::Print("SingleChanged\n");
    iSingleChanged.Signal();
}

void CpDevices::UpdatesComplete()
{
    //Log::Print("UpdatesComplete\n");
    iUpdatesComplete.Signal();
}


void Zapp::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    aInitParams->SetMsearchTime(1);
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartCombined();
	//Debug::SetLevel(Debug::kEvent | Debug::kDvEvent);

    Print("TestDvDeviceStd - starting\n");

    DeviceBasic* device = new DeviceBasic;
    CpDevices* deviceList = new CpDevices;
    FunctorCpDeviceCpp added = MakeFunctorCpDeviceCpp(*deviceList, &CpDevices::Added);
    FunctorCpDeviceCpp removed = MakeFunctorCpDeviceCpp(*deviceList, &CpDevices::Removed);
    std::string domainName("zapp.org");
    std::string serviceType("TestBasic");
    TUint ver = 1;
    CpDeviceListCppUpnpServiceType* list =
                new CpDeviceListCppUpnpServiceType(domainName, serviceType, ver, added, removed);
    Blocker* blocker = new Blocker;
    blocker->Wait(aInitParams->MsearchTimeSecs());
    delete blocker;
    try {
		deviceList->TestActions();
		deviceList->TestSubscriptions();
	}
	catch (Exception& e) {
		Print("Exception %s from %s:%u\n", e.Message(), e.File(), e.Line());
		ASSERTS();
	}
    delete list;
    delete deviceList;
    delete device;

    Print("TestDvDeviceStd - completed\n");
    UpnpLibrary::Close();
}
