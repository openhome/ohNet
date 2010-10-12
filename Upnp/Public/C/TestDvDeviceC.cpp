/* Simple test of C Device APIs
   Written in C++ to give us access to classes like Mutex, blocker, std::vector
   ...but C versions of all APIs being tested are used
*/

#include <C/Zapp.h>
#include <ZappTypes.h>
#include <TestFramework.h>
#include <DviDevice.h>
#include <C/DvZappOrgTestBasic1.h>
#include <C/CpProxy.h>
#include <C/CpZappOrgTestBasic1.h>
#include <C/CpDevice.h>
#include <C/CpDeviceUpnp.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>
#include <Debug.h>

#include <stdlib.h>
#include <string.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

static int32_t increment(void* /*aPtr*/, uint32_t /*aVersion*/, uint32_t aValue, uint32_t* aResult)
{
    *aResult = ++aValue;
    return 0;
}

static int32_t decrement(void* /*aPtr*/, uint32_t /*aVersion*/, int32_t aValue, int32_t* aResult)
{
    *aResult = --aValue;
    return 0;
}

static int32_t toggle(void* /*aPtr*/, uint32_t /*aVersion*/, uint32_t aValue, uint32_t* aResult)
{
    *aResult = (aValue==0? 1 : 0);
    return 0;
}

static int32_t echoString(void* /*aPtr*/, uint32_t /*aVersion*/, const char* aValue, char** aResult)
{
    char* res = (char*)malloc(strlen(aValue)+1);
    (void)strcpy(res, aValue);
    *aResult = res;
    return 0;
}

static int32_t echoBinary(void* /*aPtr*/, uint32_t /*aVersion*/, const char* aValue, uint32_t aValueLen, char** aResult, uint32_t* aResultLen)
{
    char* res = (char*)malloc(aValueLen);
    (void)strncpy(res, aValue, aValueLen);
    *aResult = res;
    *aResultLen = aValueLen;
    return 0;
}

static int32_t setUint(void* aPtr, uint32_t /*aVersion*/, uint32_t aValueUint)
{
    return DvServiceZappOrgTestBasic1SetPropertyVarUint((THandle)aPtr, aValueUint);
}

static int32_t getUint(void* aPtr, uint32_t /*aVersion*/, uint32_t* aValueUint)
{
    DvServiceZappOrgTestBasic1GetPropertyVarUint((THandle)aPtr, aValueUint);
    return 0;
}

static int32_t setInt(void* aPtr, uint32_t /*aVersion*/, int32_t aValueInt)
{
    return DvServiceZappOrgTestBasic1SetPropertyVarInt((THandle)aPtr, aValueInt);
}

static int32_t getInt(void* aPtr, uint32_t /*aVersion*/, int32_t* aValueInt)
{
    DvServiceZappOrgTestBasic1GetPropertyVarInt((THandle)aPtr, aValueInt);
    return 0;
}

static int32_t setBool(void* aPtr, uint32_t /*aVersion*/, uint32_t aValueBool)
{
    return DvServiceZappOrgTestBasic1SetPropertyVarBool((THandle)aPtr, aValueBool);
}

static int32_t getBool(void* aPtr, uint32_t /*aVersion*/, uint32_t* aValueBool)
{
    DvServiceZappOrgTestBasic1GetPropertyVarBool((THandle)aPtr, aValueBool);
    return 0;
}

static int32_t setMultiple(void* aPtr, uint32_t /*aVersion*/, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool)
{
    if (0 == DvServiceZappOrgTestBasic1SetPropertyVarUint((THandle)aPtr, aValueUint) &&
        0 == DvServiceZappOrgTestBasic1SetPropertyVarInt((THandle)aPtr, aValueInt)   &&
        0 == DvServiceZappOrgTestBasic1SetPropertyVarBool((THandle)aPtr, aValueBool)) {
        return 0;
    }
    return -1;
}

static int32_t setString(void* aPtr, uint32_t /*aVersion*/, const char* aValueStr)
{
    return DvServiceZappOrgTestBasic1SetPropertyVarStr((THandle)aPtr, aValueStr);
}

static int32_t getString(void* aPtr, uint32_t /*aVersion*/, char** aValueStr)
{
    DvServiceZappOrgTestBasic1GetPropertyVarStr((THandle)aPtr, aValueStr);
    return 0;
}

static int32_t setBinary(void* aPtr, uint32_t /*aVersion*/, const char* aValueBin, uint32_t aValueBinLen)
{
    return DvServiceZappOrgTestBasic1SetPropertyVarBin((THandle)aPtr, aValueBin, aValueBinLen);
}

static int32_t getBinary(void* aPtr, uint32_t /*aVersion*/, char** aValueBin, uint32_t* aValueBinLen)
{
    DvServiceZappOrgTestBasic1GetPropertyVarBin((THandle)aPtr, aValueBin, aValueBinLen);
    return 0;
}


class DeviceBasic
{
public:
    DeviceBasic();
    ~DeviceBasic();
private:
    DvDeviceC iDevice;
    THandle iTestBasic;
};

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
    iDevice = DvDeviceCreate((const char*)gDeviceName.Ptr(), NULL, NULL);
    DvDeviceSetAttribute(iDevice, "Upnp.Domain", "zapp.org");
    DvDeviceSetAttribute(iDevice, "Upnp.Type", "Test");
    DvDeviceSetAttribute(iDevice, "Upnp.Version", "1");
    DvDeviceSetAttribute(iDevice, "Upnp.FriendlyName", "ZappTestDevice");
    DvDeviceSetAttribute(iDevice, "Upnp.Manufacturer", "None");
    DvDeviceSetAttribute(iDevice, "Upnp.ManufacturerUrl", "http://www.linn.co.uk");
    DvDeviceSetAttribute(iDevice, "Upnp.ModelDescription", "Test service");
    DvDeviceSetAttribute(iDevice, "Upnp.ModelName", "Zapp test device");
    DvDeviceSetAttribute(iDevice, "Upnp.ModelNumber", "1");
    DvDeviceSetAttribute(iDevice, "Upnp.ModelUrl", "http://www.linn.co.uk");
    DvDeviceSetAttribute(iDevice, "Upnp.SerialNumber", "123456");
    DvDeviceSetAttribute(iDevice, "Upnp.Upc", "123456654321");
    iTestBasic = DvServiceZappOrgTestBasic1Create(iDevice);

    (void)DvServiceZappOrgTestBasic1SetPropertyVarUint(iTestBasic, 0);
    (void)DvServiceZappOrgTestBasic1SetPropertyVarInt(iTestBasic, 0);
    (void)DvServiceZappOrgTestBasic1SetPropertyVarBool(iTestBasic, 0);
    (void)DvServiceZappOrgTestBasic1SetPropertyVarStr(iTestBasic, "");
    (void)DvServiceZappOrgTestBasic1SetPropertyVarBin(iTestBasic, "", 0);
    DvServiceZappOrgTestBasic1EnableActionIncrement(iTestBasic, increment, NULL);
    DvServiceZappOrgTestBasic1EnableActionDecrement(iTestBasic, decrement, NULL);
    DvServiceZappOrgTestBasic1EnableActionToggle(iTestBasic, toggle, NULL);
    DvServiceZappOrgTestBasic1EnableActionEchoString(iTestBasic, echoString, NULL);
    DvServiceZappOrgTestBasic1EnableActionEchoBinary(iTestBasic, echoBinary, NULL);
    DvServiceZappOrgTestBasic1EnableActionSetUint(iTestBasic, setUint, (void*)iTestBasic);
    DvServiceZappOrgTestBasic1EnableActionGetUint(iTestBasic, getUint, (void*)iTestBasic);
    DvServiceZappOrgTestBasic1EnableActionSetInt(iTestBasic, setInt, (void*)iTestBasic);
    DvServiceZappOrgTestBasic1EnableActionGetInt(iTestBasic, getInt, (void*)iTestBasic);
    DvServiceZappOrgTestBasic1EnableActionSetBool(iTestBasic, setBool, (void*)iTestBasic);
    DvServiceZappOrgTestBasic1EnableActionGetBool(iTestBasic, getBool, (void*)iTestBasic);
    DvServiceZappOrgTestBasic1EnableActionSetMultiple(iTestBasic, setMultiple, (void*)iTestBasic);
    DvServiceZappOrgTestBasic1EnableActionSetString(iTestBasic, setString, (void*)iTestBasic);
    DvServiceZappOrgTestBasic1EnableActionGetString(iTestBasic, getString, (void*)iTestBasic);
    DvServiceZappOrgTestBasic1EnableActionSetBinary(iTestBasic, setBinary, (void*)iTestBasic);
    DvServiceZappOrgTestBasic1EnableActionGetBinary(iTestBasic, getBinary, (void*)iTestBasic);

    DvDeviceSetEnabled(iDevice);
}

DeviceBasic::~DeviceBasic()
{
    DvServiceZappOrgTestBasic1Destroy(iTestBasic);
    DvDeviceDestroy(iDevice);
}


class DeviceList
{
    static const TUint kTestIterations = 10;
public:
    DeviceList();
    ~DeviceList();
    void Stop();
    void TestActions();
    void TestSubscriptions();
    void Added(CpDeviceC aDevice);
    void Removed(CpDeviceC aDevice);
    void SingleChanged();
    void UpdatesComplete();
private:
    Mutex iLock;
    std::vector<CpDeviceC> iList;
    Semaphore iSingleChanged;
    Semaphore iUpdatesComplete;
};


static void added(void* aPtr, CpDeviceC aDevice)
{
    reinterpret_cast<DeviceList*>(aPtr)->Added(aDevice);
}

static void removed(void* aPtr, CpDeviceC aDevice)
{
    reinterpret_cast<DeviceList*>(aPtr)->Removed(aDevice);
}

static void singleChanged(void* aPtr)
{
    reinterpret_cast<DeviceList*>(aPtr)->SingleChanged();
}

static void updatesComplete(void* aPtr)
{
    reinterpret_cast<DeviceList*>(aPtr)->UpdatesComplete();
}


DeviceList::DeviceList()
    : iLock("DLMX")
    , iSingleChanged("DSB1", 0)
    , iUpdatesComplete("DSB2", 0)
{
}

DeviceList::~DeviceList()
{
    const TUint count = iList.size();
    for (TUint i=0; i<count; i++) {
        CpDeviceCRemoveRef(iList[i]);
    }
}

void DeviceList::TestActions()
{
    Print("  Actions\n");
    ASSERT(iList.size() == 1);
    THandle proxy = CpProxyZappOrgTestBasic1Create(iList[0]);
    TUint i;

    Print("    Unsigned integer arguments...\n");
    uint32_t valUint = 15;
    for (i=0; i<kTestIterations; i++) {
        uint32_t result;
        CpProxyZappOrgTestBasic1SyncIncrement(proxy, valUint, &result);
        ASSERT(result == valUint+1);
        valUint = result;
    }

    Print("    Integer arguments...\n");
    int32_t valInt = 3;
    for (i=0; i<kTestIterations; i++) {
        int32_t result;
        CpProxyZappOrgTestBasic1SyncDecrement(proxy, valInt, &result);
        ASSERT(result == valInt-1);
        valInt = result;
    }

    Print("    Boolean arguments...\n");
    uint32_t valBool = 1;
    for (i=0; i<kTestIterations; i++) {
        uint32_t result;
        CpProxyZappOrgTestBasic1SyncToggle(proxy, valBool, &result);
        ASSERT((result==1 && valBool==0) || (result==0 && valBool==1));
        valBool = result;
    }

    Print("    String arguments...\n");
    const char* valStr = "<&'tag\">";
    for (i=0; i<kTestIterations; i++) {
        char* result;
        CpProxyZappOrgTestBasic1SyncEchoString(proxy, valStr, &result);
        ASSERT(strcmp(result, valStr) == 0);
        free(result);
    }

    Print("    Binary arguments...\n");
    char valBin[256];
    for (i=0; i<256; i++) {
        valBin[i] = (char)i;
    }
    for (i=0; i<kTestIterations; i++) {
        char* result;
        uint32_t resultLen;
        CpProxyZappOrgTestBasic1SyncEchoBinary(proxy, valStr, 256, &result, &resultLen);
        ASSERT(resultLen == 256);
        ASSERT(strncmp(result, valStr, resultLen) == 0);
    }

    CpProxyZappOrgTestBasic1Destroy(proxy);
}

void DeviceList::TestSubscriptions()
{
    Print("  Subscriptions\n");
    ASSERT(iList.size() == 1);
    THandle proxy = CpProxyZappOrgTestBasic1Create(iList[0]);
    CpProxyCSetPropertyChanged(proxy, updatesComplete, this);
    CpProxyCSubscribe(proxy);
    iUpdatesComplete.Wait(); // wait for initial event

    // set callbacks for individual property changes now to avoid all being run by initial event
    CpProxyZappOrgTestBasic1SetPropertyVarUintChanged(proxy, singleChanged, this);
    CpProxyZappOrgTestBasic1SetPropertyVarIntChanged(proxy, singleChanged, this);
    CpProxyZappOrgTestBasic1SetPropertyVarBoolChanged(proxy, singleChanged, this);
    CpProxyZappOrgTestBasic1SetPropertyVarStrChanged(proxy, singleChanged, this);
    CpProxyZappOrgTestBasic1SetPropertyVarBinChanged(proxy, singleChanged, this);


    /* For each property,
         call the setter action it
         wait on a property being updated
         check that the property matches the value set
         check that the getter action matches the property
    */

    Print("    Uint...\n");
    CpProxyZappOrgTestBasic1SyncSetUint(proxy, 1);
    iSingleChanged.Wait();
    uint32_t propUint;
    CpProxyZappOrgTestBasic1PropertyVarUint(proxy, &propUint);
    ASSERT(propUint == 1);
    uint32_t valUint;
    CpProxyZappOrgTestBasic1SyncGetUint(proxy, &valUint);
    ASSERT(propUint == valUint);

    Print("    Int...\n");
    CpProxyZappOrgTestBasic1SyncSetInt(proxy, -99);
    iSingleChanged.Wait();
    int32_t propInt;
    CpProxyZappOrgTestBasic1PropertyVarInt(proxy, &propInt);
    ASSERT(propInt == -99);
    int32_t valInt;
    CpProxyZappOrgTestBasic1SyncGetInt(proxy, &valInt);
    ASSERT(propInt == valInt);

    Print("    Bool...\n");
    CpProxyZappOrgTestBasic1SyncSetBool(proxy, 1);
    iSingleChanged.Wait();
    uint32_t propBool;
    CpProxyZappOrgTestBasic1PropertyVarBool(proxy, &propBool);
    ASSERT(propBool == 1);
    uint32_t valBool;
    CpProxyZappOrgTestBasic1SyncGetBool(proxy, &valBool);
    ASSERT(valBool == 1);

    Print("    String...\n");
    const char* str = "<&'tag\">";
    CpProxyZappOrgTestBasic1SyncSetString(proxy, str);
    iSingleChanged.Wait();
    char* propStr;
    CpProxyZappOrgTestBasic1PropertyVarStr(proxy, &propStr);
    ASSERT(strcmp(propStr, str) == 0);
    // test again to check that PropertyVarStr didn't TransferTo the property
    free(propStr);
    CpProxyZappOrgTestBasic1PropertyVarStr(proxy, &propStr);
    ASSERT(strcmp(propStr, str) == 0);
    char* valStr;
    CpProxyZappOrgTestBasic1SyncGetString(proxy, &valStr);
    ASSERT(strcmp(propStr, valStr) == 0);
    free(propStr);
    free(valStr);

    Print("    Binary...\n");
    char bufBin[256];
    for (TUint i=0; i<256; i++) {
        bufBin[i] = (char)i;
    }
    CpProxyZappOrgTestBasic1SyncSetBinary(proxy, &bufBin[0], 256);
    iSingleChanged.Wait();
    char* propBin;
    uint32_t propBinLen;
    CpProxyZappOrgTestBasic1PropertyVarBin(proxy, &propBin, &propBinLen);
    ASSERT(propBinLen == 256);
    ASSERT(strncmp(propBin, bufBin, propBinLen) == 0);
    // test again to check that PropertyVarBin didn't TransferTo the property
    free(propBin);
    CpProxyZappOrgTestBasic1PropertyVarBin(proxy, &propBin, &propBinLen);
    ASSERT(propBinLen == 256);
    ASSERT(strncmp(propBin, bufBin, propBinLen) == 0);
    char* valBin;
    uint32_t valBinLen;
    CpProxyZappOrgTestBasic1SyncGetBinary(proxy, &valBin, &valBinLen);
    ASSERT(valBinLen == 256)
    ASSERT(strncmp(propBin, valBin, valBinLen) ==0);
    free(propBin);
    free(valBin);

    Print("    Multiple...\n");
    (void)iUpdatesComplete.Clear();
    CpProxyZappOrgTestBasic1SyncSetMultiple(proxy, 15, 658, 0);
    iUpdatesComplete.Wait();
    CpProxyZappOrgTestBasic1PropertyVarUint(proxy, &propUint);
    ASSERT(propUint == 15);
    CpProxyZappOrgTestBasic1SyncGetUint(proxy, &valUint);
    ASSERT(propUint == valUint);
    CpProxyZappOrgTestBasic1PropertyVarInt(proxy, &propInt);
    ASSERT(propInt == 658);
    CpProxyZappOrgTestBasic1SyncGetInt(proxy, &valInt);
    ASSERT(propInt == valInt);
    CpProxyZappOrgTestBasic1PropertyVarBool(proxy, &propBool);
    ASSERT(propBool == 0);
    CpProxyZappOrgTestBasic1SyncGetBool(proxy, &valBool);
    ASSERT(valBool == 0);

    CpProxyZappOrgTestBasic1Destroy(proxy); // automatically unsubscribes
}

void DeviceList::Added(CpDeviceC aDevice)
{
    AutoMutex a(iLock);
    iList.push_back(aDevice);
    CpDeviceCAddRef(aDevice);
}

void DeviceList::Removed(CpDeviceC aDevice)
{
    AutoMutex a(iLock);
    const TUint count = iList.size();
    const char* udn = CpDeviceCUdn(aDevice);
    for (TUint i=0; i<count; i++) {
        CpDeviceC device = iList[i];
        if (0 == strcmp(CpDeviceCUdn(device), udn)) {
            iList.erase(iList.begin()+i);
            CpDeviceCRemoveRef(device);
            break;
        }
    }
}

void DeviceList::SingleChanged()
{
    //Print("SingleChanged\n");
    iSingleChanged.Signal();
}

void DeviceList::UpdatesComplete()
{
    //Print("UpdatesComplete\n");
    iUpdatesComplete.Signal();
}


extern "C" void ZappTestRunner(ZappHandleInitParams aInitParams)
{
    ZappInitParamsSetMsearchTime(aInitParams, 1);
    ZappLibraryInitialise(aInitParams);
    Print("TestDvDeviceC - starting\n");
    ZappLibraryStartCombined();
//    Debug::SetLevel(Debug::kService);

    DeviceBasic* device = new DeviceBasic;
    DeviceList* deviceList = new DeviceList;
    HandleCpDeviceList dlh = CpDeviceListCreateUpnpServiceType("zapp.org", "TestBasic", 1,
                                                               added, deviceList, removed, deviceList);
    Blocker* blocker = new Blocker;
    blocker->Wait(ZappInitParamsMsearchTimeSecs(aInitParams));
    delete blocker;

    deviceList->TestActions();
    deviceList->TestSubscriptions();

    CpDeviceListDestroy(dlh);
    delete deviceList;
    delete device;

    Print("TestDvDeviceC - completed\n");
    ZappLibraryClose();
}
