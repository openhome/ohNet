#ifndef HEADER_PROVIDER_CONFIG1
#define HEADER_PROVIDER_CONFIG1

#include <Generated/DvAvOpenhomeOrgConfiguration1.h>
#include <OpenHome/Av/ProviderFactory.h>

namespace OpenHome {
namespace Configuration {
    class IConfigManager;

class ProviderConfig : public OpenHome::Net::DvProviderAvOpenhomeOrgConfiguration1, public Av::IProvider
{
public:
    ProviderConfig(Net::DvDevice& aDevice, Configuration::IConfigManager& aConfigManager);
private: // from DvProviderAvOpenhomeOrgConfiguration1
    void SetValue(Net::IDvInvocation& aInvocation, const Brx& aKey, const Brx& aValue) override;
    void GetValue(Net::IDvInvocation& aInvocation, const Brx& aKey, Net::IDvInvocationResponseString& aValue) override;
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

#endif // HEADER_PROVIDER_CONFIG1
