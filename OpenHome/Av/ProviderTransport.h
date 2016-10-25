#pragma once

#include <Generated/DvAvOpenhomeOrgTransport1.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/PipelineObserver.h>

namespace OpenHome {
    namespace Media {
        class PipelineManager;
    }
namespace Av {

class ProviderTransport : public Net::DvProviderAvOpenhomeOrgTransport1
                        , private Media::IPipelineObserver
{
public:
    ProviderTransport(Net::DvDevice& aDevice, Media::PipelineManager& aPipeline);
private: // from Media::IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState) override;
    void NotifyMode(const Brx& aMode, const Media::ModeInfo& aInfo) override;
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo) override;
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
    void Counters(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aModeCount, Net::IDvInvocationResponseUint& aTrackCount, Net::IDvInvocationResponseUint& aStreamCount, Net::IDvInvocationResponseUint& aMetatextCount) override;
    void ModeInfo(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aNextAvailable, Net::IDvInvocationResponseBool& aPrevAvailable) override;
    void TrackInfo(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aUri, Net::IDvInvocationResponseString& aMetadata) override;
    void StreamInfo(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aStreamId, Net::IDvInvocationResponseString& aUri, Net::IDvInvocationResponseString& aMetadata, Net::IDvInvocationResponseBool& aSeekable, Net::IDvInvocationResponseBool& aPausable, Net::IDvInvocationResponseUint& aDuration, Net::IDvInvocationResponseUint& aBitRate, Net::IDvInvocationResponseUint& aBitDepth, Net::IDvInvocationResponseUint& aSampleRate, Net::IDvInvocationResponseBool& aLossless, Net::IDvInvocationResponseString& aCodecName) override;
    void StreamId(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aStreamId) override;
    void Metatext(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aMetatext) override;
private:
    Mutex iLock;
    Media::PipelineManager& iPipeline;
    Media::EPipelineState iTransportState;
    TUint iStreamId;
    TUint iTrackPosSeconds;
};

} // namespace Av
} // namespace OpenHome
