#ifndef HEADER_PROVIDER_CONNECTIONMANAGER
#define HEADER_PROVIDER_CONNECTIONMANAGER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <Generated/DvUpnpOrgConnectionManager1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>

namespace OpenHome {
namespace Av {

class ProviderConnectionManager : public Net::DvProviderUpnpOrgConnectionManager1
{
    static const TUint kConnectionId = 0; // we don't implement the PrepareForConnection action - only connectionID 0 is valid
public:
    ProviderConnectionManager(Net::DvDevice& aDevice);
    ~ProviderConnectionManager();
    void NotifyProtocolInfo(const Brx& aProtocolInfo);
private: // from Net::DvProviderUpnpOrgConnectionManager1
    void GetProtocolInfo(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aSource, Net::IDvInvocationResponseString& aSink) override;
    void GetCurrentConnectionIDs(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aConnectionIDs) override;
    void GetCurrentConnectionInfo(Net::IDvInvocation& aInvocation, TInt aConnectionID, Net::IDvInvocationResponseInt& aRcsID,
                                  Net::IDvInvocationResponseInt& aAVTransportID, Net::IDvInvocationResponseString& aProtocolInfo,
                                  Net::IDvInvocationResponseString& aPeerConnectionManager, Net::IDvInvocationResponseInt& aPeerConnectionID,
                                  Net::IDvInvocationResponseString& aDirection, Net::IDvInvocationResponseString& aStatus) override;
private:
    Brn iSinkProtocolInfo;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_CONNECTIONMANAGER
