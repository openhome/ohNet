#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/PipelineObserver.h>

EXCEPTION(TransportControlIncorrectStreamId);
EXCEPTION(TransportControlActionNotAllowed);

namespace OpenHome {
namespace Net {
    class DvDevice;
}
namespace Media {
    class PipelineManager;
}
namespace Av {

class ITransportControl
{
public:
    virtual void Play() = 0;
    virtual void Pause(TUint aStreamId) = 0;
    virtual void Stop(TUint aStreamId) = 0;
    virtual void Next(TUint aStreamId) = 0;
    virtual void Prev(TUint aStreamId) = 0;
    virtual void SeekSecondsAbsolute(TUint aStreamId, TUint aSeconds) = 0;
    virtual void SeekSecondsRelative(TUint aStreamId, TInt aSeconds) = 0;
};

class ProviderTransportControlEriskay;

class TransportControl : private ITransportControl, private Media::IPipelineObserver, private INonCopyable
{
public:
    TransportControl(Net::DvDevice& aDevice, Media::PipelineManager& aPipeline);
    ~TransportControl();
private: // from ITransportControl
    void Play() override;
    void Pause(TUint aStreamId) override;
    void Stop(TUint aStreamId) override;
    void Next(TUint aStreamId) override;
    void Prev(TUint aStreamId) override;
    void SeekSecondsAbsolute(TUint aStreamId, TUint aSeconds) override;
    void SeekSecondsRelative(TUint aStreamId, TInt aSeconds) override;
private:
    void SeekLocked(TUint aStreamId, TUint aSecondsAbsolute);
private: // from Media::IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState) override;
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo) override;
private:
    Mutex iLock;
    Media::PipelineManager& iPipeline;
    ProviderTransportControlEriskay* iProvider;
    TBool iPlaySupported;
    TBool iPauseSupported;
    TBool iStopSupported;
    TBool iNextSupported;
    TBool iPrevSupported;
    TBool iSeekSupported;
    TUint iStreamId;
    TUint iSeconds;
};

} // namespace Av
} // namespace OpenHome

