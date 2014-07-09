#ifndef HEADER_PROVIDER_RECEIVER
#define HEADER_PROVIDER_RECEIVER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <Generated/DvAvOpenhomeOrgReceiver1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
using namespace Net;
namespace Av {

class ISourceReceiver
{
public:
    virtual ~ISourceReceiver() {}
    virtual void Play() = 0;
    virtual void Stop() = 0;
    virtual void SetSender(const Brx& aUri, const Brx& aMetadata) = 0;
};

class ProviderReceiver : public DvProviderAvOpenhomeOrgReceiver1
{
public:
    ProviderReceiver(Net::DvDevice& aDevice, ISourceReceiver& aSource, const TChar* aProtocolInfo);
    void NotifyPipelineState(Media::EPipelineState aState);
private: // from DvProviderAvOpenhomeOrgReceiver1
    void Play(IDvInvocation& aInvocation);
    void Stop(IDvInvocation& aInvocation);
    void SetSender(IDvInvocation& aInvocation, const Brx& aUri, const Brx& aMetadata);
    void Sender(IDvInvocation& aInvocation, IDvInvocationResponseString& aUri, IDvInvocationResponseString& aMetadata);
    void ProtocolInfo(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
    void TransportState(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
private:
    Mutex iLock;
    ISourceReceiver& iSource;
    Brn iProtocolInfo;
    Brn iTransportState;
    Media::BwsTrackUri iSenderUri;
    Media::BwsTrackMetaData iSenderMetadata;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_RECEIVER