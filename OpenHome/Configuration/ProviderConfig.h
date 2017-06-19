#pragma once

#include <Generated/DvAvOpenhomeOrgConfig2.h>
#include <OpenHome/Av/ProviderFactory.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Json.h>

namespace OpenHome {
namespace Configuration {
    class IConfigManager;

class KeyWriterJson : public IKeyWriter, private INonCopyable
{
public:
    KeyWriterJson(IWriter& aWriter);
public: // from IKeyWriter
    void WriteKeys(const std::vector<const Brx*>& aKeys);
private:
    IWriter& iWriter;
};

class ProviderConfig : public OpenHome::Net::DvProviderAvOpenhomeOrgConfig2, public Av::IProvider
{
public:
    ProviderConfig(Net::DvDevice& aDevice, Configuration::IConfigManager& aConfigManager);
private: // from DvProviderAvOpenhomeOrgConfiguration1
    void GetKeys(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aKeyList) override;
    void SetValue(Net::IDvInvocation& aInvocation, const Brx& aKey, const Brx& aValue) override;
    void GetValue(Net::IDvInvocation& aInvocation, const Brx& aKey, Net::IDvInvocationResponseString& aValue) override;
    void HasKey(Net::IDvInvocation& aInvocation, const Brx& aKey, Net::IDvInvocationResponseBool& aValue) override;
private:
    static const TUint kErrorCodeInvalidKey = 800;
    static const TUint kErrorCodeNotANumber = 801;
    static const TUint kErrorCodeValueOutOfRange = 802;
    static const TUint kErrorCodeInvalidSelection = 803;
    static const TUint kErrorCodeValueTooLong = 804;
    static const Brn kErrorDescInvalidKey;
    static const Brn kErrorDescNotANumber;
    static const Brn kErrorDescValueOutOfRange;
    static const Brn kErrorDescInvalidSelection;
    static const Brn kErrorDescValueTooLong;
    Configuration::IConfigManager& iConfigManager;
};

}  // namespace Configuration
}  // namespace OpenHome

