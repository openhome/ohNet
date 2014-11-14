#ifndef HEADER_PROVIDER_CONNECTIONMANAGER
#define HEADER_PROVIDER_CONNECTIONMANAGER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <Generated/DvUpnpOrgConnectionManager1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>

namespace OpenHome {
using namespace Net;
namespace Av {

class ProviderConnectionManager : public DvProviderUpnpOrgConnectionManager1
{
    static const TUint kConnectionId = 0; // we don't implement the PrepareForConnection action - only connectionID 0 is valid
public:
    ProviderConnectionManager(Net::DvDevice& aDevice, const Brx& aSinkProtocolInfo);
    ~ProviderConnectionManager();
private: // from DvProviderUpnpOrgConnectionManager1
    void GetProtocolInfo(IDvInvocation& aInvocation, IDvInvocationResponseString& aSource, IDvInvocationResponseString& aSink) override;
    void GetCurrentConnectionIDs(IDvInvocation& aInvocation, IDvInvocationResponseString& aConnectionIDs) override;
    void GetCurrentConnectionInfo(IDvInvocation& aInvocation, TInt aConnectionID, IDvInvocationResponseInt& aRcsID,
                                  IDvInvocationResponseInt& aAVTransportID, IDvInvocationResponseString& aProtocolInfo,
                                  IDvInvocationResponseString& aPeerConnectionManager, IDvInvocationResponseInt& aPeerConnectionID,
                                  IDvInvocationResponseString& aDirection, IDvInvocationResponseString& aStatus) override;
private:
    Brn iSinkProtocolInfo;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_CONNECTIONMANAGER
