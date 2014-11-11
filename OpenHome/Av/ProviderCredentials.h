#ifndef HEADER_PROVIDER_CREDENTIALS_1
#define HEADER_PROVIDER_CREDENTIALS_1

#include <Generated/DvAvOpenhomeOrgCredentials1.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>

#if _MSC_VER <= 1600 // <= VS 2010 (VC10)
# pragma warning (disable: 4481)
#endif

namespace OpenHome {
namespace Av {

class ICredentials;

class ProviderCredentials : public Net::DvProviderAvOpenhomeOrgCredentials1
{
public:
    ProviderCredentials(Net::DvDevice& aDevice, ICredentials& aCredentialsManager);
    void AddId(const Brx& aId);
    void SetPublicKey(const Brx& aKey);
    void NotifyCredentialsChanged();
private: // from Net::DvProviderAvOpenhomeOrgCredentials1
    void Set(Net::IDvInvocation& aInvocation, const Brx& aId, const Brx& aUsername, const Brx& aPassword) override;
    void Clear(Net::IDvInvocation& aInvocation, const Brx& aId) override;
    void SetEnabled(Net::IDvInvocation& aInvocation, const Brx& aId, TBool aEnabled) override;
    void Get(Net::IDvInvocation& aInvocation, const Brx& aId, Net::IDvInvocationResponseString& aUsername, Net::IDvInvocationResponseString& aPassword, Net::IDvInvocationResponseBool& aEnabled, Net::IDvInvocationResponseString& aStatus) override;
    void Login(Net::IDvInvocation& aInvocation, const Brx& aId, Net::IDvInvocationResponseString& aToken) override;
    void Logout(Net::IDvInvocation& aInvocation, const Brx& aId, const Brx& aToken) override;
    void GetIds(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aIds) override;
    void GetPublicKey(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aPublicKey) override;
    void GetSequenceNumber(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aSequenceNumber) override;
private:
    ICredentials& iCredentialsManager;
    Bws<256> iIds;
    Bws<1024> iPublicKey;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_CREDENTIALS_1
