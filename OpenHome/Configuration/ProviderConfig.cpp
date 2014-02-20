#include <OpenHome/Configuration/ProviderConfig.h>
#include <OpenHome/Configuration/ConfigManager.h>

using namespace OpenHome;
using namespace OpenHome::Configuration;
using namespace OpenHome::Net;


// ProviderConfig

const Brn ProviderConfig::kErrorDescInvalidKey("Invalid key");
const Brn ProviderConfig::kErrorDescNotANumber("Expected numerical value");
const Brn ProviderConfig::kErrorDescValueOutOfRange("Value outwith expected range");
const Brn ProviderConfig::kErrorDescInvalidSelection("Expected value selected from list of options");
const Brn ProviderConfig::kErrorDescValueTooLong("Value too long");

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
    catch (ConfigNotANumber&) {
        aInvocation.Error(kErrorCodeNotANumber, kErrorDescNotANumber);
    }
    catch (ConfigValueOutOfRange) {
        aInvocation.Error(kErrorCodeValueOutOfRange, kErrorDescValueOutOfRange);
    }
    catch (ConfigInvalidSelection) {
        aInvocation.Error(kErrorCodeInvalidSelection, kErrorDescInvalidSelection);
    }
    catch (ConfigValueTooLong) {
        aInvocation.Error(kErrorCodeValueTooLong, kErrorDescValueTooLong);
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
