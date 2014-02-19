#ifndef HEADER_PROVIDER_CONFIG1
#define HEADER_PROVIDER_CONFIG1

#include <Generated/DvAvOpenhomeOrgConfiguration1.h>

namespace OpenHome {
namespace Configuration {
    class IConfigManagerReader;

class ProviderConfig : public OpenHome::Net::DvProviderAvOpenhomeOrgConfiguration1
{
public:
    ProviderConfig(Net::DvDevice& aDevice, Configuration::IConfigManagerReader& aConfigManager);
private: // from DvProviderAvOpenhomeOrgConfiguration1
    void SetValue(Net::IDvInvocation& aInvocation, const Brx& aKey, const Brx& aValue);
    void GetValue(Net::IDvInvocation& aInvocation, const Brx& aKey, Net::IDvInvocationResponseString& aValue);
private:
    static const TUint kErrorCodeInvalidKey = 800;
    static const TUint kErrorCodeInvalidValue = 801;
    static const Brn kErrorDescInvalidKey;
    static const Brn kErrorDescInvalidValue;
    Configuration::IConfigManagerReader& iConfigManager;
};

}  // namespace Configuration
}  // namespace OpenHome

#endif // HEADER_PROVIDER_CONFIG1
