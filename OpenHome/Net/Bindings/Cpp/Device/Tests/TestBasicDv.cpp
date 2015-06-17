#include "TestBasicDv.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Cpp/DvOpenhomeOrgTestBasic1.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Private/TestFramework.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;

class OpenHome::Net::ProviderTestBasic : public DvProviderOpenhomeOrgTestBasic1Cpp
{
public:
    ProviderTestBasic(DvDeviceStd& aDevice);
private:
    void Increment(IDvInvocationStd& aInvocation, uint32_t aValue, uint32_t& aResult);
    void Decrement(IDvInvocationStd& aInvocation, int32_t aValue, int32_t& aResult);
    void Toggle(IDvInvocationStd& aInvocation, bool aValue, bool& aResult);
    void EchoString(IDvInvocationStd& aInvocation, const std::string& aValue, std::string& aResult);
    void EchoBinary(IDvInvocationStd& aInvocation, const std::string& aValue, std::string& aResult);
    void SetUint(IDvInvocationStd& aInvocation, uint32_t aValueUint);
    void GetUint(IDvInvocationStd& aInvocation, uint32_t& aValueUint);
    void SetInt(IDvInvocationStd& aInvocation, int32_t aValueInt);
    void GetInt(IDvInvocationStd& aInvocation, int32_t& aValueInt);
    void SetBool(IDvInvocationStd& aInvocation, bool aValueBool);
    void GetBool(IDvInvocationStd& aInvocation, bool& aValueBool);
    void SetMultiple(IDvInvocationStd& aInvocation, uint32_t aValueUint, int32_t aValueInt, bool aValueBool);
    void SetString(IDvInvocationStd& aInvocation, const std::string& aValueStr);
    void GetString(IDvInvocationStd& aInvocation, std::string& aValueStr);
    void SetBinary(IDvInvocationStd& aInvocation, const std::string& aValueBin);
    void GetBinary(IDvInvocationStd& aInvocation, std::string& aValueBin);
};


ProviderTestBasic::ProviderTestBasic(DvDeviceStd& aDevice)
    : DvProviderOpenhomeOrgTestBasic1Cpp(aDevice)
{
    EnablePropertyVarUint();
    EnablePropertyVarInt();
    EnablePropertyVarBool();
    EnablePropertyVarStr();
    EnablePropertyVarBin();
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

void ProviderTestBasic::Increment(IDvInvocationStd& aInvocation, uint32_t aValue, uint32_t& aResult)
{
    ASSERT(aInvocation.Version() == 1);
    aResult = ++aValue;
}

void ProviderTestBasic::Decrement(IDvInvocationStd& /*aInvocation*/, int32_t aValue, int32_t& aResult)
{
    aResult = --aValue;
}

void ProviderTestBasic::Toggle(IDvInvocationStd& /*aInvocation*/, bool aValue, bool& aResult)
{
    aResult = !aValue;
}

void ProviderTestBasic::EchoString(IDvInvocationStd& /*aInvocation*/, const std::string& aValue, std::string& aResult)
{
    aResult.assign(aValue);
}

void ProviderTestBasic::EchoBinary(IDvInvocationStd& /*aInvocation*/, const std::string& aValue, std::string& aResult)
{
    aResult.assign(aValue);
}

void ProviderTestBasic::SetUint(IDvInvocationStd& /*aInvocation*/, uint32_t aValueUint)
{
    SetPropertyVarUint(aValueUint);
}

void ProviderTestBasic::GetUint(IDvInvocationStd& /*aInvocation*/, uint32_t& aValueUint)
{
    GetPropertyVarUint(aValueUint);
}

void ProviderTestBasic::SetInt(IDvInvocationStd& aInvocation, int32_t aValueInt)
{
    if (aValueInt == 12345) {
        std::string str("custom error");
        aInvocation.ReportError(801, str);
    }
    SetPropertyVarInt(aValueInt);
}

void ProviderTestBasic::GetInt(IDvInvocationStd& /*aInvocation*/, int32_t& aValueInt)
{
    GetPropertyVarInt(aValueInt);
}

void ProviderTestBasic::SetBool(IDvInvocationStd& /*aInvocation*/, bool aValueBool)
{
    SetPropertyVarBool(aValueBool);
}

void ProviderTestBasic::GetBool(IDvInvocationStd& /*aInvocation*/, bool& aValueBool)
{
    GetPropertyVarBool(aValueBool);
}

void ProviderTestBasic::SetMultiple(IDvInvocationStd& /*aInvocation*/, uint32_t aValueUint, int32_t aValueInt, bool aValueBool)
{
    PropertiesLock();
    SetPropertyVarUint(aValueUint);
    SetPropertyVarInt(aValueInt);
    SetPropertyVarBool(aValueBool);
    PropertiesUnlock();
}

void ProviderTestBasic::SetString(IDvInvocationStd& /*aInvocation*/, const std::string& aValueStr)
{
    SetPropertyVarStr(aValueStr);
}

void ProviderTestBasic::GetString(IDvInvocationStd& /*aInvocation*/, std::string& aValueStr)
{
    GetPropertyVarStr(aValueStr);
}

void ProviderTestBasic::SetBinary(IDvInvocationStd& /*aInvocation*/, const std::string& aValueBin)
{
    SetPropertyVarBin(aValueBin);
}

void ProviderTestBasic::GetBinary(IDvInvocationStd& /*aInvocation*/, std::string& aValueBin)
{
    GetPropertyVarBin(aValueBin);
}


static std::string gDeviceName("device");

static void RandomiseUdn(Environment& aEnv, std::string& aUdn)
{
    Bwh udn(aUdn.c_str());
    TestFramework::RandomiseUdn(aEnv, udn);
    aUdn.assign((const char*)udn.Ptr(), udn.Bytes());
}

DeviceBasic::DeviceBasic(Environment& aEnv, EProtocol aProtocol)
{
    RandomiseUdn(aEnv, gDeviceName);
    if (aProtocol == DeviceBasic::eProtocolNone) {
        iDevice = new DvDeviceStd(gDeviceName);
    }
    else { // eProtocolUpnp
        iDevice = new DvDeviceStdStandard(gDeviceName);
        iDevice->SetAttribute("Upnp.Domain", "openhome.org");
        iDevice->SetAttribute("Upnp.Type", "Test");
        iDevice->SetAttribute("Upnp.Version", "1");
        iDevice->SetAttribute("Upnp.FriendlyName", "ohNetTestDevice");
        iDevice->SetAttribute("Upnp.Manufacturer", "None");
        iDevice->SetAttribute("Upnp.ModelName", "ohNet test device");
    }
    iTestBasic = new ProviderTestBasic(*iDevice);
    iDevice->SetEnabled();
}

DeviceBasic::~DeviceBasic()
{
    delete iTestBasic;
    delete iDevice;
}

DvDeviceStd& DeviceBasic::Device()
{
    return *iDevice;
}
