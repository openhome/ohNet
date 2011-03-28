#include <C/TestBasicDv.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <TestFramework.h>
#include <DviDevice.h>
#include <C/DvProvider.h>
#include <C/DvZappOrgTestBasic1.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>

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
    uint32_t changed;
    return DvProviderZappOrgTestBasic1SetPropertyVarUint((THandle)aPtr, aValueUint, &changed);
}

static int32_t getUint(void* aPtr, uint32_t /*aVersion*/, uint32_t* aValueUint)
{
    DvProviderZappOrgTestBasic1GetPropertyVarUint((THandle)aPtr, aValueUint);
    return 0;
}

static int32_t setInt(void* aPtr, uint32_t /*aVersion*/, int32_t aValueInt)
{
    uint32_t changed;
    return DvProviderZappOrgTestBasic1SetPropertyVarInt((THandle)aPtr, aValueInt, &changed);
}

static int32_t getInt(void* aPtr, uint32_t /*aVersion*/, int32_t* aValueInt)
{
    DvProviderZappOrgTestBasic1GetPropertyVarInt((THandle)aPtr, aValueInt);
    return 0;
}

static int32_t setBool(void* aPtr, uint32_t /*aVersion*/, uint32_t aValueBool)
{
    uint32_t changed;
    return DvProviderZappOrgTestBasic1SetPropertyVarBool((THandle)aPtr, aValueBool, &changed);
}

static int32_t getBool(void* aPtr, uint32_t /*aVersion*/, uint32_t* aValueBool)
{
    DvProviderZappOrgTestBasic1GetPropertyVarBool((THandle)aPtr, aValueBool);
    return 0;
}

static int32_t setMultiple(void* aPtr, uint32_t /*aVersion*/, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool)
{
    uint32_t changed1;
    uint32_t changed2;
    uint32_t changed3;
    DvProviderPropertiesLock((THandle)aPtr);
    int32_t err = (0 == DvProviderZappOrgTestBasic1SetPropertyVarUint((THandle)aPtr, aValueUint, &changed1) &&
                   0 == DvProviderZappOrgTestBasic1SetPropertyVarInt((THandle)aPtr, aValueInt, &changed2)   &&
                   0 == DvProviderZappOrgTestBasic1SetPropertyVarBool((THandle)aPtr, aValueBool, &changed3)) ? 0 : -1;
    DvProviderPropertiesUnlock((THandle)aPtr);
    return err;
}

static int32_t setString(void* aPtr, uint32_t /*aVersion*/, const char* aValueStr)
{
    uint32_t changed;
    return DvProviderZappOrgTestBasic1SetPropertyVarStr((THandle)aPtr, aValueStr, &changed);
}

static int32_t getString(void* aPtr, uint32_t /*aVersion*/, char** aValueStr)
{
    DvProviderZappOrgTestBasic1GetPropertyVarStr((THandle)aPtr, aValueStr);
    return 0;
}

static int32_t setBinary(void* aPtr, uint32_t /*aVersion*/, const char* aValueBin, uint32_t aValueBinLen)
{
    uint32_t changed;
    return DvProviderZappOrgTestBasic1SetPropertyVarBin((THandle)aPtr, aValueBin, aValueBinLen, &changed);
}

static int32_t getBinary(void* aPtr, uint32_t /*aVersion*/, char** aValueBin, uint32_t* aValueBinLen)
{
    DvProviderZappOrgTestBasic1GetPropertyVarBin((THandle)aPtr, aValueBin, aValueBinLen);
    return 0;
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

DeviceBasicC::DeviceBasicC()
{
    Bwh udn("device");
    RandomiseUdn(udn);
    iDevice = DvDeviceCreate((const char*)udn.Ptr(), NULL, NULL);
    DvDeviceSetAttribute(iDevice, "Upnp.Domain", "zapp.org");
    DvDeviceSetAttribute(iDevice, "Upnp.Type", "Test");
    DvDeviceSetAttribute(iDevice, "Upnp.Version", "1");
    DvDeviceSetAttribute(iDevice, "Upnp.FriendlyName", "ZappTestDevice");
    DvDeviceSetAttribute(iDevice, "Upnp.Manufacturer", "None");
    DvDeviceSetAttribute(iDevice, "Upnp.ModelName", "Zapp test device");
    iTestBasic = DvProviderZappOrgTestBasic1Create(iDevice);

    uint32_t ignore;
    (void)DvProviderZappOrgTestBasic1SetPropertyVarUint(iTestBasic, 0, &ignore);
    (void)DvProviderZappOrgTestBasic1SetPropertyVarInt(iTestBasic, 0, &ignore);
    (void)DvProviderZappOrgTestBasic1SetPropertyVarBool(iTestBasic, 0, &ignore);
    (void)DvProviderZappOrgTestBasic1SetPropertyVarStr(iTestBasic, "", &ignore);
    (void)DvProviderZappOrgTestBasic1SetPropertyVarBin(iTestBasic, "", 0, &ignore);
    DvProviderZappOrgTestBasic1EnableActionIncrement(iTestBasic, increment, NULL);
    DvProviderZappOrgTestBasic1EnableActionDecrement(iTestBasic, decrement, NULL);
    DvProviderZappOrgTestBasic1EnableActionToggle(iTestBasic, toggle, NULL);
    DvProviderZappOrgTestBasic1EnableActionEchoString(iTestBasic, echoString, NULL);
    DvProviderZappOrgTestBasic1EnableActionEchoBinary(iTestBasic, echoBinary, NULL);
    DvProviderZappOrgTestBasic1EnableActionSetUint(iTestBasic, setUint, (void*)iTestBasic);
    DvProviderZappOrgTestBasic1EnableActionGetUint(iTestBasic, getUint, (void*)iTestBasic);
    DvProviderZappOrgTestBasic1EnableActionSetInt(iTestBasic, setInt, (void*)iTestBasic);
    DvProviderZappOrgTestBasic1EnableActionGetInt(iTestBasic, getInt, (void*)iTestBasic);
    DvProviderZappOrgTestBasic1EnableActionSetBool(iTestBasic, setBool, (void*)iTestBasic);
    DvProviderZappOrgTestBasic1EnableActionGetBool(iTestBasic, getBool, (void*)iTestBasic);
    DvProviderZappOrgTestBasic1EnableActionSetMultiple(iTestBasic, setMultiple, (void*)iTestBasic);
    DvProviderZappOrgTestBasic1EnableActionSetString(iTestBasic, setString, (void*)iTestBasic);
    DvProviderZappOrgTestBasic1EnableActionGetString(iTestBasic, getString, (void*)iTestBasic);
    DvProviderZappOrgTestBasic1EnableActionSetBinary(iTestBasic, setBinary, (void*)iTestBasic);
    DvProviderZappOrgTestBasic1EnableActionGetBinary(iTestBasic, getBinary, (void*)iTestBasic);

    DvDeviceSetEnabled(iDevice);
}

DeviceBasicC::~DeviceBasicC()
{
    DvProviderZappOrgTestBasic1Destroy(iTestBasic);
    DvDeviceDestroy(iDevice);
}

DvDeviceC DeviceBasicC::Device()
{
    return iDevice;
}
