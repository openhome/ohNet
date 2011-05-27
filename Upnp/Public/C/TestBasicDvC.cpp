#include <C/TestBasicDv.h>
#include <C/OhNet.h>
#include <OhNetTypes.h>
#include <TestFramework.h>
#include <DviDevice.h>
#include <C/DvProvider.h>
#include <C/DvOpenhomeOrgTestBasic1.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>

#include <stdlib.h>
#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

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
    return DvProviderOpenhomeOrgTestBasic1SetPropertyVarUint((THandle)aPtr, aValueUint, &changed);
}

static int32_t getUint(void* aPtr, uint32_t /*aVersion*/, uint32_t* aValueUint)
{
    DvProviderOpenhomeOrgTestBasic1GetPropertyVarUint((THandle)aPtr, aValueUint);
    return 0;
}

static int32_t setInt(void* aPtr, uint32_t /*aVersion*/, int32_t aValueInt)
{
    uint32_t changed;
    return DvProviderOpenhomeOrgTestBasic1SetPropertyVarInt((THandle)aPtr, aValueInt, &changed);
}

static int32_t getInt(void* aPtr, uint32_t /*aVersion*/, int32_t* aValueInt)
{
    DvProviderOpenhomeOrgTestBasic1GetPropertyVarInt((THandle)aPtr, aValueInt);
    return 0;
}

static int32_t setBool(void* aPtr, uint32_t /*aVersion*/, uint32_t aValueBool)
{
    uint32_t changed;
    return DvProviderOpenhomeOrgTestBasic1SetPropertyVarBool((THandle)aPtr, aValueBool, &changed);
}

static int32_t getBool(void* aPtr, uint32_t /*aVersion*/, uint32_t* aValueBool)
{
    DvProviderOpenhomeOrgTestBasic1GetPropertyVarBool((THandle)aPtr, aValueBool);
    return 0;
}

static int32_t setMultiple(void* aPtr, uint32_t /*aVersion*/, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool)
{
    uint32_t changed1;
    uint32_t changed2;
    uint32_t changed3;
    DvProviderPropertiesLock((THandle)aPtr);
    int32_t err = (0 == DvProviderOpenhomeOrgTestBasic1SetPropertyVarUint((THandle)aPtr, aValueUint, &changed1) &&
                   0 == DvProviderOpenhomeOrgTestBasic1SetPropertyVarInt((THandle)aPtr, aValueInt, &changed2)   &&
                   0 == DvProviderOpenhomeOrgTestBasic1SetPropertyVarBool((THandle)aPtr, aValueBool, &changed3)) ? 0 : -1;
    DvProviderPropertiesUnlock((THandle)aPtr);
    return err;
}

static int32_t setString(void* aPtr, uint32_t /*aVersion*/, const char* aValueStr)
{
    uint32_t changed;
    return DvProviderOpenhomeOrgTestBasic1SetPropertyVarStr((THandle)aPtr, aValueStr, &changed);
}

static int32_t getString(void* aPtr, uint32_t /*aVersion*/, char** aValueStr)
{
    DvProviderOpenhomeOrgTestBasic1GetPropertyVarStr((THandle)aPtr, aValueStr);
    return 0;
}

static int32_t setBinary(void* aPtr, uint32_t /*aVersion*/, const char* aValueBin, uint32_t aValueBinLen)
{
    uint32_t changed;
    return DvProviderOpenhomeOrgTestBasic1SetPropertyVarBin((THandle)aPtr, aValueBin, aValueBinLen, &changed);
}

static int32_t getBinary(void* aPtr, uint32_t /*aVersion*/, char** aValueBin, uint32_t* aValueBinLen)
{
    DvProviderOpenhomeOrgTestBasic1GetPropertyVarBin((THandle)aPtr, aValueBin, aValueBinLen);
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

DeviceBasicC::DeviceBasicC(EProtocol aProtocol)
{
    Bwh udn("device");
    RandomiseUdn(udn);
    if (aProtocol == eProtocolNone) {
        iDevice = DvDeviceCreate((const char*)udn.Ptr());
    }
    else { // eProtocolUpnp
        iDevice = DvDeviceStandardCreateNoResources((const char*)udn.Ptr());
        DvDeviceSetAttribute(iDevice, "Upnp.Domain", "openhome.org");
        DvDeviceSetAttribute(iDevice, "Upnp.Type", "Test");
        DvDeviceSetAttribute(iDevice, "Upnp.Version", "1");
        DvDeviceSetAttribute(iDevice, "Upnp.FriendlyName", "ohNetTestDevice");
        DvDeviceSetAttribute(iDevice, "Upnp.Manufacturer", "None");
        DvDeviceSetAttribute(iDevice, "Upnp.ModelName", "ohNet test device");
    }
    iTestBasic = DvProviderOpenhomeOrgTestBasic1Create(iDevice);

    uint32_t ignore;
    (void)DvProviderOpenhomeOrgTestBasic1SetPropertyVarUint(iTestBasic, 0, &ignore);
    (void)DvProviderOpenhomeOrgTestBasic1SetPropertyVarInt(iTestBasic, 0, &ignore);
    (void)DvProviderOpenhomeOrgTestBasic1SetPropertyVarBool(iTestBasic, 0, &ignore);
    (void)DvProviderOpenhomeOrgTestBasic1SetPropertyVarStr(iTestBasic, "", &ignore);
    (void)DvProviderOpenhomeOrgTestBasic1SetPropertyVarBin(iTestBasic, "", 0, &ignore);
    DvProviderOpenhomeOrgTestBasic1EnableActionIncrement(iTestBasic, increment, NULL);
    DvProviderOpenhomeOrgTestBasic1EnableActionDecrement(iTestBasic, decrement, NULL);
    DvProviderOpenhomeOrgTestBasic1EnableActionToggle(iTestBasic, toggle, NULL);
    DvProviderOpenhomeOrgTestBasic1EnableActionEchoString(iTestBasic, echoString, NULL);
    DvProviderOpenhomeOrgTestBasic1EnableActionEchoBinary(iTestBasic, echoBinary, NULL);
    DvProviderOpenhomeOrgTestBasic1EnableActionSetUint(iTestBasic, setUint, (void*)iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnableActionGetUint(iTestBasic, getUint, (void*)iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnableActionSetInt(iTestBasic, setInt, (void*)iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnableActionGetInt(iTestBasic, getInt, (void*)iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnableActionSetBool(iTestBasic, setBool, (void*)iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnableActionGetBool(iTestBasic, getBool, (void*)iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnableActionSetMultiple(iTestBasic, setMultiple, (void*)iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnableActionSetString(iTestBasic, setString, (void*)iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnableActionGetString(iTestBasic, getString, (void*)iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnableActionSetBinary(iTestBasic, setBinary, (void*)iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnableActionGetBinary(iTestBasic, getBinary, (void*)iTestBasic);

    DvDeviceSetEnabled(iDevice);
}

DeviceBasicC::~DeviceBasicC()
{
    DvProviderOpenhomeOrgTestBasic1Destroy(iTestBasic);
    DvDeviceDestroy(iDevice);
}

DvDeviceC DeviceBasicC::Device()
{
    return iDevice;
}
