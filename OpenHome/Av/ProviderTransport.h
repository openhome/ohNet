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
                        , private ITransportRepeatRandomObserver
{
    static const TUint kModesGranularity;
    static const TUint kRepeatOff;
    static const TUint kRepeatOnAll;
    static const TUint kShuffleOff;
    static const TUint kShuffleOnAll;
public:
    ProviderTransport(Net::DvDevice& aDevice,
                      Media::PipelineManager& aPipeline,
                      ITransportActivator& aTransportActivator,
                      ITransportRepeatRandom& aTransportRepeatRandom);
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
private: // from ITransportRepeatRandomObserver
    void TransportRepeatChanged(TBool aRepeat) override;
    void TransportRandomChanged(TBool aRandom) override;
private: // from Net::DvProviderOpenhomeOrgEriskayTransportControl1
    void PlayAs(Net::IDvInvocation& aInvocation, const Brx& aMode, const Brx& aCommand) override;
    void Play(Net::IDvInvocation& aInvocation) override;
    void Pause(Net::IDvInvocation& aInvocation) override;
    void Stop(Net::IDvInvocation& aInvocation) override;
    void Next(Net::IDvInvocation& aInvocation) override;
    void Previous(Net::IDvInvocation& aInvocation) override;
    void SetRepeat(Net::IDvInvocation& aInvocation, TUint aRepeat) override;
    void SetShuffle(Net::IDvInvocation& aInvocation, TUint aRandom) override;
    void SeekSecondAbsolute(Net::IDvInvocation& aInvocation, TUint aStreamId, TUint aSecondAbsolute) override;
    void SeekSecondRelative(Net::IDvInvocation& aInvocation, TUint aStreamId, TInt aSecondRelative) override;
    void TransportState(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aState) override;
    void Modes(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aModes) override;
    void ModeInfo(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aNextAvailable, Net::IDvInvocationResponseBool& aPreviousAvailable, Net::IDvInvocationResponseBool& aRepeatAvailable, Net::IDvInvocationResponseBool& aShuffleAvailable) override;
    void StreamInfo(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aStreamId, Net::IDvInvocationResponseBool& aSeekable, Net::IDvInvocationResponseBool& aPausable) override;
    void StreamId(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aStreamId) override;
    void Repeat(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aRepeat) override;
    void Shuffle(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aShuffle) override;
private:
    Mutex iLock;
    Media::PipelineManager& iPipeline;
    ITransportActivator& iTransportActivator;
    ITransportRepeatRandom& iTransportRepeatRandom;
    Media::EPipelineState iTransportState;
    TUint iStreamId;
    TUint iTrackPosSeconds;
    WriterBwh iModes;
};

} // namespace Av
} // namespace OpenHome
