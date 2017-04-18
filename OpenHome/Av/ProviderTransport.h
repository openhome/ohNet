#pragma once

#include <Generated/DvAvOpenhomeOrgTransport1.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/TransportControl.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/PipelineManager.h>

namespace OpenHome {
    namespace Media {
        class PipelineManager;
    }
namespace Av {

class ProviderTransport : public Net::DvProviderAvOpenhomeOrgTransport1
                        , private Media::IPipelineObserver
                        , private Media::IModeObserver
{
    static const TUint kModesGranularity;
public:
    ProviderTransport(Net::DvDevice& aDevice,
                      Media::PipelineManager& aPipeline,
                      ITransportActivator& aTransportActivator);
    void Start();
private: // from Media::IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState) override;
    void NotifyMode(const Brx& aMode, const Media::ModeInfo& aInfo) override;
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo) override;
private: // from Media::IModeObserver
    void NotifyModeAdded(const Brx& aMode) override;
private: // from Net::DvProviderOpenhomeOrgEriskayTransportControl1
    void PlayAs(Net::IDvInvocation& aInvocation, const Brx& aMode, const Brx& aCommand) override;
    void Play(Net::IDvInvocation& aInvocation) override;
    void Pause(Net::IDvInvocation& aInvocation) override;
    void Stop(Net::IDvInvocation& aInvocation) override;
    void Next(Net::IDvInvocation& aInvocation, TUint aStreamId) override;
    void Prev(Net::IDvInvocation& aInvocation, TUint aStreamId) override;
    void SeekSecondsAbsolute(Net::IDvInvocation& aInvocation, TUint aStreamId, TUint aSecondsAbsolute) override;
    void SeekSecondsRelative(Net::IDvInvocation& aInvocation, TUint aStreamId, TInt aSecondsRelative) override;
    void TransportState(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aState) override;
    void Modes(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aModes) override;
    void ModeInfo(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aNextAvailable, Net::IDvInvocationResponseBool& aPrevAvailable) override;
    void StreamInfo(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aStreamId, Net::IDvInvocationResponseBool& aSeekable, Net::IDvInvocationResponseBool& aPausable) override;
    void StreamId(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aStreamId) override;
private:
    Mutex iLock;
    Media::PipelineManager& iPipeline;
    ITransportActivator& iTransportActivator;
    Media::EPipelineState iTransportState;
    TUint iStreamId;
    TUint iTrackPosSeconds;
    WriterBwh iModes;
};

} // namespace Av
} // namespace OpenHome
