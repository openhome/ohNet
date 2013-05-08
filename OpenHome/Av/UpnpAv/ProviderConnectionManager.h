#ifndef HEADER_PROVIDER_CONNECTIONMANAGER
#define HEADER_PROVIDER_CONNECTIONMANAGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <Generated/DvUpnpOrgConnectionManager1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Av/Product.h>

namespace OpenHome {
using namespace Net;
namespace Av {

class ProviderConnectionManager : public Net::DvProviderUpnpOrgConnectionManager1
{
    static const TUint kConnectionId = 0; // we don't implement the PrepareForConnection action - only connectionID 0 is valid
public:
    ProviderConnectionManager(Net::DvDevice& aDevice, const TChar* aSinkProtocolInfo);
    ~ProviderConnectionManager();
private: // from DvProviderUpnpOrgConnectionManager1
    void GetProtocolInfo(IDvInvocation& aInvocation, IDvInvocationResponseString& aSource, IDvInvocationResponseString& aSink);
    void GetCurrentConnectionIDs(IDvInvocation& aInvocation, IDvInvocationResponseString& aConnectionIDs);
    void GetCurrentConnectionInfo(IDvInvocation& aInvocation, TInt aConnectionID, IDvInvocationResponseInt& aRcsID,
                                  IDvInvocationResponseInt& aAVTransportID, IDvInvocationResponseString& aProtocolInfo,
                                  IDvInvocationResponseString& aPeerConnectionManager, IDvInvocationResponseInt& aPeerConnectionID,
                                  IDvInvocationResponseString& aDirection, IDvInvocationResponseString& aStatus);
private:
    Brn iSinkProtocolInfo;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_CONNECTIONMANAGER
