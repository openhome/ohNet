#ifndef HEADER_PROVIDER_RADIO
#define HEADER_PROVIDER_RADIO

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <Generated/DvAvOpenhomeOrgReceiver1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>

namespace OpenHome {
using namespace Net;
namespace Av {

class ProviderReceiver : public DvProviderAvOpenhomeOrgReceiver1
{
public:
    ProviderReceiver(Net::DvDevice& aDevice);
private: // from DvProviderAvOpenhomeOrgReceiver1
    void Play(IDvInvocation& aInvocation);
    void Stop(IDvInvocation& aInvocation);
    void SetSender(IDvInvocation& aInvocation, const Brx& aUri, const Brx& aMetadata);
    void Sender(IDvInvocation& aInvocation, IDvInvocationResponseString& aUri, IDvInvocationResponseString& aMetadata);
    void ProtocolInfo(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
    void TransportState(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_RADIO
