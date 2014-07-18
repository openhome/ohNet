#include "TestBasicDv.h"
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/C/DvProvider.h>
#include <OpenHome/Net/C/DvOpenhomeOrgTestBasic1.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Net/Private/Globals.h>

#include <stdlib.h>
#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

static int32_t STDCALL increment(void* /*aPtr*/, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue, uint32_t* aResult)
{
    ASSERT(aInvocation->iVersion(aInvocationPtr) == 1);
    *aResult = ++aValue;
    return 0;
}

static int32_t STDCALL decrement(void* /*aPtr*/, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, int32_t aValue, int32_t* aResult)
{
    *aResult = --aValue;
    return 0;
}

static int32_t STDCALL toggle(void* /*aPtr*/, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, uint32_t aValue, uint32_t* aResult)
{
    *aResult = (aValue==0? 1 : 0);
    return 0;
}

static int32_t STDCALL echoString(void* /*aPtr*/, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, const char* aValue, char** aResult)
{
    char* res = (char*)malloc(strlen(aValue)+1);
    (void)strcpy(res, aValue);
    *aResult = res;
    return 0;
}

static int32_t STDCALL echoBinary(void* /*aPtr*/, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, const char* aValue, uint32_t aValueLen, char** aResult, uint32_t* aResultLen)
{
    char* res = (char*)malloc(aValueLen);
    (void)strncpy(res, aValue, aValueLen);
    *aResult = res;
    *aResultLen = aValueLen;
    return 0;
}

static int32_t STDCALL setUint(void* aPtr, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, uint32_t aValueUint)
{
    uint32_t changed;
    return DvProviderOpenhomeOrgTestBasic1SetPropertyVarUint((THandle)aPtr, aValueUint, &changed);
}

static int32_t STDCALL getUint(void* aPtr, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, uint32_t* aValueUint)
{
    DvProviderOpenhomeOrgTestBasic1GetPropertyVarUint((THandle)aPtr, aValueUint);
    return 0;
}

static int32_t STDCALL setInt(void* aPtr, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, int32_t aValueInt)
{
    uint32_t changed;
    return DvProviderOpenhomeOrgTestBasic1SetPropertyVarInt((THandle)aPtr, aValueInt, &changed);
}

static int32_t STDCALL getInt(void* aPtr, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, int32_t* aValueInt)
{
    DvProviderOpenhomeOrgTestBasic1GetPropertyVarInt((THandle)aPtr, aValueInt);
    return 0;
}

static int32_t STDCALL setBool(void* aPtr, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, uint32_t aValueBool)
{
    uint32_t changed;
    return DvProviderOpenhomeOrgTestBasic1SetPropertyVarBool((THandle)aPtr, aValueBool, &changed);
}

static int32_t STDCALL getBool(void* aPtr, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, uint32_t* aValueBool)
{
    DvProviderOpenhomeOrgTestBasic1GetPropertyVarBool((THandle)aPtr, aValueBool);
    return 0;
}

static int32_t STDCALL setMultiple(void* aPtr, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool)
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

static int32_t STDCALL setString(void* aPtr, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, const char* aValueStr)
{
    uint32_t changed;
    return DvProviderOpenhomeOrgTestBasic1SetPropertyVarStr((THandle)aPtr, aValueStr, &changed);
}

static int32_t STDCALL getString(void* aPtr, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, char** aValueStr)
{
    DvProviderOpenhomeOrgTestBasic1GetPropertyVarStr((THandle)aPtr, aValueStr);
    return 0;
}

static int32_t STDCALL setBinary(void* aPtr, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, const char* aValueBin, uint32_t aValueBinLen)
{
    uint32_t changed;
    return DvProviderOpenhomeOrgTestBasic1SetPropertyVarBin((THandle)aPtr, aValueBin, aValueBinLen, &changed);
}

static int32_t STDCALL getBinary(void* aPtr, IDvInvocationC* /*aInvocation*/, void* /*aInvocationPtr*/, char** aValueBin, uint32_t* aValueBinLen)
{
    DvProviderOpenhomeOrgTestBasic1GetPropertyVarBin((THandle)aPtr, aValueBin, aValueBinLen);
    return 0;
}


DeviceBasicC::DeviceBasicC(EProtocol aProtocol)
{
    Bwh udn("device");
    RandomiseUdn(*gEnv, udn);
    Brhz cstr;
    udn.TransferTo(cstr);
    if (aProtocol == eProtocolNone) {
        iDevice = DvDeviceCreate((const char*)cstr.Ptr());
    }
    else { // eProtocolUpnp
        iDevice = DvDeviceStandardCreateNoResources((const char*)cstr.Ptr());
        DvDeviceSetAttribute(iDevice, "Upnp.Domain", "openhome.org");
        DvDeviceSetAttribute(iDevice, "Upnp.Type", "Test");
        DvDeviceSetAttribute(iDevice, "Upnp.Version", "1");
        DvDeviceSetAttribute(iDevice, "Upnp.FriendlyName", "ohNetTestDevice");
        DvDeviceSetAttribute(iDevice, "Upnp.Manufacturer", "None");
        DvDeviceSetAttribute(iDevice, "Upnp.ModelName", "ohNet test device");
    }
    iTestBasic = DvProviderOpenhomeOrgTestBasic1Create(iDevice);

    DvProviderOpenhomeOrgTestBasic1EnablePropertyVarUint(iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnablePropertyVarInt(iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnablePropertyVarBool(iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnablePropertyVarStr(iTestBasic);
    DvProviderOpenhomeOrgTestBasic1EnablePropertyVarBin(iTestBasic);
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
