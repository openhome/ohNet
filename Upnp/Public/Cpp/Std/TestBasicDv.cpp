#include <Std/TestBasicDv.h>
#include <ZappTypes.h>
#include <Std/DvDevice.h>
#include <Std/DvOpenhomeOrgTestBasic1.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>

#include <string>

using namespace Zapp;

class Zapp::ProviderTestBasic : public DvProviderOpenhomeOrgTestBasic1Cpp
{
public:
    ProviderTestBasic(DvDeviceStd& aDevice);
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


ProviderTestBasic::ProviderTestBasic(DvDeviceStd& aDevice)
    : DvProviderOpenhomeOrgTestBasic1Cpp(aDevice)
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

void ProviderTestBasic::Increment(uint32_t /*aVersion*/, uint32_t aValue, uint32_t& aResult)
{
    aResult = ++aValue;
}

void ProviderTestBasic::Decrement(uint32_t /*aVersion*/, int32_t aValue, int32_t& aResult)
{
    aResult = --aValue;
}

void ProviderTestBasic::Toggle(uint32_t /*aVersion*/, bool aValue, bool& aResult)
{
    aResult = !aValue;
}

void ProviderTestBasic::EchoString(uint32_t /*aVersion*/, const std::string& aValue, std::string& aResult)
{
    aResult.assign(aValue);
}

void ProviderTestBasic::EchoBinary(uint32_t /*aVersion*/, const std::string& aValue, std::string& aResult)
{
    aResult.assign(aValue);
}

void ProviderTestBasic::SetUint(uint32_t /*aVersion*/, uint32_t aValueUint)
{
    SetPropertyVarUint(aValueUint);
}

void ProviderTestBasic::GetUint(uint32_t /*aVersion*/, uint32_t& aValueUint)
{
    GetPropertyVarUint(aValueUint);
}

void ProviderTestBasic::SetInt(uint32_t /*aVersion*/, int32_t aValueInt)
{
    SetPropertyVarInt(aValueInt);
}

void ProviderTestBasic::GetInt(uint32_t /*aVersion*/, int32_t& aValueInt)
{
    GetPropertyVarInt(aValueInt);
}

void ProviderTestBasic::SetBool(uint32_t /*aVersion*/, bool aValueBool)
{
    SetPropertyVarBool(aValueBool);
}

void ProviderTestBasic::GetBool(uint32_t /*aVersion*/, bool& aValueBool)
{
    GetPropertyVarBool(aValueBool);
}

void ProviderTestBasic::SetMultiple(uint32_t /*aVersion*/, uint32_t aValueUint, int32_t aValueInt, bool aValueBool)
{
    PropertiesLock();
    SetPropertyVarUint(aValueUint);
    SetPropertyVarInt(aValueInt);
    SetPropertyVarBool(aValueBool);
    PropertiesUnlock();
}

void ProviderTestBasic::SetString(uint32_t /*aVersion*/, const std::string& aValueStr)
{
    SetPropertyVarStr(aValueStr);
}

void ProviderTestBasic::GetString(uint32_t /*aVersion*/, std::string& aValueStr)
{
    GetPropertyVarStr(aValueStr);
}

void ProviderTestBasic::SetBinary(uint32_t /*aVersion*/, const std::string& aValueBin)
{
    SetPropertyVarBin(aValueBin);
}

void ProviderTestBasic::GetBinary(uint32_t /*aVersion*/, std::string& aValueBin)
{
    GetPropertyVarBin(aValueBin);
}


static std::string gDeviceName("device");

static void RandomiseUdn(std::string& aUdn)
{
    Bwh udn;
    udn.Grow((TUint)aUdn.length() + 1 + Ascii::kMaxUintStringBytes + 1);
    Brn buf((const TByte*)aUdn.c_str(), (TUint)aUdn.length());
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
    iDevice = new DvDeviceStdStandard(gDeviceName);
    iDevice->SetAttribute("Upnp.Domain", "openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Test");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "ZappTestDevice");
    iDevice->SetAttribute("Upnp.Manufacturer", "None");
    iDevice->SetAttribute("Upnp.ModelName", "Zapp test device");
    iTestBasic = new ProviderTestBasic(*iDevice);
    iDevice->SetEnabled();
}

DeviceBasic::~DeviceBasic()
{
    delete iTestBasic;
    delete iDevice;
}

DvDeviceStdStandard& DeviceBasic::Device()
{
    return *iDevice;
}
