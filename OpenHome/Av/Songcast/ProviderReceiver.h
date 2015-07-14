#ifndef HEADER_PROVIDER_RECEIVER
#define HEADER_PROVIDER_RECEIVER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <Generated/DvAvOpenhomeOrgReceiver1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Av {

class ISourceReceiver
{
public:
    virtual ~ISourceReceiver() {}
    virtual void Play() = 0;
    virtual void Stop() = 0;
    virtual void SetSender(const Brx& aUri, const Brx& aMetadata) = 0;
};

class ProviderReceiver : public Net::DvProviderAvOpenhomeOrgReceiver1
{
public:
    ProviderReceiver(Net::DvDevice& aDevice, ISourceReceiver& aSource, const TChar* aProtocolInfo);
    void NotifyPipelineState(Media::EPipelineState aState);
private: // from DvProviderAvOpenhomeOrgReceiver1
    void Play(Net::IDvInvocation& aInvocation) override;
    void Stop(Net::IDvInvocation& aInvocation) override;
    void SetSender(Net::IDvInvocation& aInvocation, const Brx& aUri, const Brx& aMetadata) override;
    void Sender(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aUri, Net::IDvInvocationResponseString& aMetadata) override;
    void ProtocolInfo(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
    void TransportState(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
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
