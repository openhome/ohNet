#include <OpenHome/Configuration/ProviderConfig.h>
#include <OpenHome/Av/Product.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Net;


// ProviderFactory

IProvider* ProviderFactory::NewConfiguration(DvDevice& aDevice, IConfigManager& aConfigReader)
{ // static
    return new ProviderConfig(aDevice, aConfigReader);
}


// KeyWriterJson

KeyWriterJson::KeyWriterJson(IWriter& aWriter)
    : iWriter(aWriter)
{
}

void KeyWriterJson::WriteKeys(const std::vector<const Brx*>& aKeys)
{
    iWriter.Write('[');
    auto it = aKeys.cbegin();
    for (;;) {
        iWriter.Write(Brn("\""));
        Json::Escape(iWriter, **it);
        iWriter.Write(Brn("\""));
        ++it;

        if (it != aKeys.cend()) {
            iWriter.Write(Brn(", "));
        }
        else {
            break;
        }
    }
    iWriter.Write(']');
    iWriter.WriteFlush();
}


// ProviderConfig

const Brn ProviderConfig::kErrorDescInvalidKey("Invalid key");
const Brn ProviderConfig::kErrorDescNotANumber("Expected numerical value");
const Brn ProviderConfig::kErrorDescValueOutOfRange("Value outwith expected range");
const Brn ProviderConfig::kErrorDescInvalidSelection("Expected value selected from list of options");
const Brn ProviderConfig::kErrorDescValueTooLong("Value too long");

ProviderConfig::ProviderConfig(DvDevice& aDevice, Configuration::IConfigManager& aConfigManager)
    : DvProviderAvOpenhomeOrgConfig2(aDevice)
    , iConfigManager(aConfigManager)
{
    EnableActionGetKeys();
    EnableActionSetValue();
    EnableActionGetValue();
    EnableActionHasKey();
}

void ProviderConfig::GetKeys(IDvInvocation& aInvocation, IDvInvocationResponseString& aKeyList)
{
    KeyWriterJson keyWriter(aKeyList);
    aInvocation.StartResponse();
    iConfigManager.WriteKeys(keyWriter);
    aInvocation.EndResponse();
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
    catch (ConfigValueOutOfRange&) {
        aInvocation.Error(kErrorCodeValueOutOfRange, kErrorDescValueOutOfRange);
    }
    catch (ConfigInvalidSelection&) {
        aInvocation.Error(kErrorCodeInvalidSelection, kErrorDescInvalidSelection);
    }
    catch (ConfigValueTooLong&) {
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

void ProviderConfig::HasKey(Net::IDvInvocation& aInvocation, const Brx& aKey, Net::IDvInvocationResponseBool& aValue) 
{
    aInvocation.StartResponse();
    aValue.Write(iConfigManager.Has(aKey));
    aInvocation.EndResponse();
}
