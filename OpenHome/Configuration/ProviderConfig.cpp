#include <OpenHome/Configuration/ProviderConfig.h>
#include <OpenHome/Configuration/ConfigManager.h>

using namespace OpenHome;
using namespace OpenHome::Configuration;
using namespace OpenHome::Net;


// ProviderConfig

const Brn ProviderConfig::kErrorDescInvalidKey("Invalid key");
const Brn ProviderConfig::kErrorDescInvalidValue("Invalid value");

ProviderConfig::ProviderConfig(DvDevice& aDevice, Configuration::IConfigManagerReader& aConfigManager)
    : DvProviderAvOpenhomeOrgConfiguration1(aDevice)
    , iConfigManager(aConfigManager)
{
    EnableActionSetValue();
    EnableActionGetValue();
}

void ProviderConfig::SetValue(IDvInvocation& aInvocation, const Brx& aKey, const Brx& aValue)
{
    if (!iConfigManager.Has(aKey)) {
        aInvocation.Error(kErrorCodeInvalidKey, kErrorDescInvalidKey);
    }

    ISerialisable& ser = iConfigManager.Get(aKey);
    try {
        ser.Deserialise(aValue);
    }
    catch (ConfigInvalidValue&) {
        aInvocation.Error(kErrorCodeInvalidValue, kErrorDescInvalidValue);
    }
    catch (ConfigValueOutOfRange) {
        aInvocation.Error(kErrorCodeInvalidValue, kErrorDescInvalidValue);
    }
    catch (ConfigInvalidChoice) {
        aInvocation.Error(kErrorCodeInvalidValue, kErrorDescInvalidValue);
    }
    catch (ConfigValueTooLong) {
        aInvocation.Error(kErrorCodeInvalidValue, kErrorDescInvalidValue);
    }

    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderConfig::GetValue(IDvInvocation& aInvocation, const Brx& aKey, IDvInvocationResponseString& aValue)
{
    if (!iConfigManager.Has(aKey)) {
        aInvocation.Error(kErrorCodeInvalidKey, kErrorDescInvalidKey);
    }

    ISerialisable& ser = iConfigManager.Get(aKey);
    aInvocation.StartResponse();
    ser.Serialise(aValue);
    aInvocation.EndResponse();
}
