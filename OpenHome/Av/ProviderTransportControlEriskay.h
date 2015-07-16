#ifndef PROVIDER_TRANSPORT_CONTROL_ERISKAY
#define PROVIDER_TRANSPORT_CONTROL_ERISKAY

#include <Generated/DvOpenhomeOrgEriskayTransportControl1.h>
#include <OpenHome/Av/TransportControl.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/PipelineObserver.h>

namespace OpenHome {
namespace Av {

class ProviderTransportControlEriskay : public Net::DvProviderOpenhomeOrgEriskayTransportControl1
{
public:
    ProviderTransportControlEriskay(Net::DvDevice& aDevice, ITransportControl& aTransportControl);
    void NotifyMode(); // play/stop/next/prev supported
    void NotifyStream(TUint aStreamId, TBool aPauseSupported, TBool aSeekSupported);
    void NotifyState(Media::EPipelineState aState);
private: // from Net::DvProviderOpenhomeOrgEriskayTransportControl1
    void Characteristics(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aPlaySupported, Net::IDvInvocationResponseBool& aPauseSupported,
                         Net::IDvInvocationResponseBool& aStopSupported, Net::IDvInvocationResponseBool& aNextSupported, Net::IDvInvocationResponseBool& aPrevSupported,
                         Net::IDvInvocationResponseBool& aSeekSupported) override;
    void Play(Net::IDvInvocation& aInvocation) override;
    void Pause(Net::IDvInvocation& aInvocation, TUint aStreamId) override;
    void Stop(Net::IDvInvocation& aInvocation, TUint aStreamId) override;
    void Next(Net::IDvInvocation& aInvocation, TUint aStreamId) override;
    void Prev(Net::IDvInvocation& aInvocation, TUint aStreamId) override;
    void SeekSecondsAbsolute(Net::IDvInvocation& aInvocation, TUint aStreamId, TUint aSecondsAbsolute) override;
    void SeekSecondsRelative(Net::IDvInvocation& aInvocation, TUint aStreamId, TInt aSecondsRelative) override;
    void StreamId(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue) override;
    void TransportState(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
private:
    Mutex iLock;
    ITransportControl& iTransportControl;
    Media::EPipelineState iState;
};

} // namespace Av
} // namespace OpenHome

#endif // PROVIDER_TRANSPORT_CONTROL_ERISKAY
