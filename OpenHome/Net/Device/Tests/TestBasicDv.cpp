#include "TestBasicDv.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Cpp/DvOpenhomeOrgTestBasic1.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/TestFramework.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;

// ProviderTestBasic

ProviderTestBasic::ProviderTestBasic(DvDevice& aDevice)
    : DvProviderOpenhomeOrgTestBasic1(aDevice)
{
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
    EnableActionEchoAllowedRangeUint();
    EnableActionDecrement();
    EnableActionToggle();
    EnableActionEchoString();
    EnableActionEchoAllowedValueString();
    EnableActionEchoBinary();
    EnableActionSetUint();
    EnableActionGetUint();
    EnableActionSetInt();
    EnableActionGetInt();
    EnableActionSetBool();
    EnableActionGetBool();
    EnableActionSetMultiple();
    EnableActionGetMultiple();
    EnableActionSetString();
    EnableActionGetString();
    EnableActionSetBinary();
    EnableActionGetBinary();
    EnableActionReportError();
    EnableActionWriteFile();
    EnableActionShutdown();
}

void ProviderTestBasic::Increment(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(++aValue);
    aInvocation.EndResponse();
}

void ProviderTestBasic::EchoAllowedRangeUint(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(aValue);
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

void ProviderTestBasic::EchoAllowedValueString(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseString& aResult)
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

void ProviderTestBasic::SetUint(IDvInvocation& aInvocation, TUint aValueUint)
{
    SetPropertyVarUint(aValueUint);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetUint(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValueUint)
{
    aInvocation.StartResponse();
    TUint val;
    GetPropertyVarUint(val);
    aValueUint.Write(val);
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetInt(IDvInvocation& aInvocation, TInt aValueInt)
{
    SetPropertyVarInt(aValueInt);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetInt(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValueInt)
{
    aInvocation.StartResponse();
    TInt val;
    GetPropertyVarInt(val);
    aValueInt.Write(val);
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetBool(IDvInvocation& aInvocation, TBool aValueBool)
{
    SetPropertyVarBool(aValueBool);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetBool(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValueBool)
{
    aInvocation.StartResponse();
    TBool val;
    GetPropertyVarBool(val);
    aValueBool.Write(val);
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetMultiple(IDvInvocation& aInvocation, TUint aValueUint, TInt aValueInt, TBool aValueBool)
{
    PropertiesLock();
    SetPropertyVarUint(aValueUint);
    SetPropertyVarInt(aValueInt);
    SetPropertyVarBool(aValueBool);
    PropertiesUnlock();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetMultiple(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValueUint, IDvInvocationResponseInt& aValueInt, IDvInvocationResponseBool& aValueBool)
{
    aInvocation.StartResponse();
    TUint valUint;
    GetPropertyVarUint(valUint);
    aValueUint.Write(valUint);
    TInt valInt;
    GetPropertyVarInt(valInt);
    aValueInt.Write(valInt);
    TBool valBool;
    GetPropertyVarBool(valBool);
    aValueBool.Write(valBool);
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetString(IDvInvocation& aInvocation, const Brx& aValueStr)
{
    SetPropertyVarStr(aValueStr);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetString(IDvInvocation& aInvocation, IDvInvocationResponseString& aValueStr)
{
    aInvocation.StartResponse();
    Brhz val;
    GetPropertyVarStr(val);
    aValueStr.Write(val);
    aValueStr.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetBinary(IDvInvocation& aInvocation, const Brx& aValueBin)
{
    SetPropertyVarBin(aValueBin);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetBinary(IDvInvocation& aInvocation, IDvInvocationResponseBinary& aValueBin)
{
    aInvocation.StartResponse();
    Brh val;
    GetPropertyVarBin(val);
    aValueBin.Write(val);
    aValueBin.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTestBasic::ReportError(IDvInvocation& aInvocation)
{
    aInvocation.Error(801, Brn("intentionally throws"));
}

void ProviderTestBasic::WriteFile(IDvInvocation& aInvocation, const Brx& aData, const Brx& aFileFullName)
{
    TUint len = aFileFullName.Bytes();
    char* name = (char*)malloc(len+1);
    (void)memcpy(name, aFileFullName.Ptr(), aFileFullName.Bytes());
    name[len] = 0;
    FILE* fp = fopen(name, "wb");
    free(name);
    (void)fwrite(aData.Ptr(), aData.Bytes(), 1, fp);
    (void)fflush(fp);
    (void)fclose(fp);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::Shutdown(IDvInvocation& aInvocation)
{
    aInvocation.StartResponse();
    aInvocation.EndResponse();
    putchar('q'); // assumes running under a console that is quit via 'q'
}


// DeviceBasic

static Bwh gDeviceName("device");

DeviceBasic::DeviceBasic(DvStack& aDvStack)
{
    TestFramework::RandomiseUdn(aDvStack.Env(), gDeviceName);
    iDevice = new DvDeviceStandard(aDvStack, gDeviceName);
    iDevice->SetAttribute("Upnp.Domain", "openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Test");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "ohNetTestDevice");
    iDevice->SetAttribute("Upnp.Manufacturer", "None");
    iDevice->SetAttribute("Upnp.ModelName", "ohNet test device");
    iTestBasic = new ProviderTestBasic(*iDevice);
    iDevice->SetEnabled();
    // test that calling SetAttribute disables then re-enables the device
    iDevice->SetAttribute("Upnp.SerialNumber", "123456");
    ASSERT(iDevice->Enabled());
}

DeviceBasic::~DeviceBasic()
{
    delete iTestBasic;
    delete iDevice;
}

const Brx& DeviceBasic::Udn() const
{
    return iDevice->Udn();
}

DvDevice& DeviceBasic::Device()
{
    return *iDevice;
}
