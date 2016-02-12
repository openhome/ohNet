#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/PipelineObserver.h>

namespace OpenHome {
    class Environment;
    class PowerManager;
    class StoreInt;
namespace Net {
    class DvDevice;
}
namespace Media {
    class PipelineManager;
    class UriProviderSingleTrack;
    class MimeTypeList;
}
namespace Av {

class ISourceRadio
{
public:
    virtual ~ISourceRadio() {}
    virtual TBool TryFetch(TUint aPresetId, const Brx& aUri) = 0;
    virtual void Fetch(const Brx& aUri, const Brx& aMetaData) = 0;
    virtual void Play() = 0;
    virtual void Pause() = 0;
    virtual void Stop() = 0;
    virtual void SeekAbsolute(TUint aSeconds) = 0;
    virtual void SeekRelative(TUint aSeconds) = 0;
};

class PresetDatabase;
class ProviderRadio;
class RadioPresetsTuneIn;
class IMediaPlayer;

class SourceRadio : public Source, private ISourceRadio, private Media::IPipelineObserver, private INonCopyable
{
public:
    SourceRadio(IMediaPlayer& aMediaPlayer, Media::UriProviderSingleTrack& aUriProvider, const Brx& aTuneInPartnerId);
    ~SourceRadio();
private: // from ISource
    void Activate(TBool aAutoPlay) override;
    void Deactivate() override;
    void StandbyEnabled() override;
    void PipelineStopped() override;
private: // from ISourceRadio
    TBool TryFetch(TUint aPresetId, const Brx& aUri) override;
    void Fetch(const Brx& aUri, const Brx& aMetaData) override;
    void Play() override;
    void Pause() override;
    void Stop() override;
    void SeekAbsolute(TUint aSeconds) override;
    void SeekRelative(TUint aSeconds) override;
private:
    void FetchLocked(const Brx& aUri, const Brx& aMetaData);
private: // from IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState) override;
    void NotifyMode(const Brx& aMode, const Media::ModeInfo& aInfo) override;
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo) override;
private:
    Mutex iLock;
    Media::UriProviderSingleTrack& iUriProvider;
    ProviderRadio* iProviderRadio;
    PresetDatabase* iPresetDatabase;
    RadioPresetsTuneIn* iTuneIn;
    Media::Track* iTrack;
    TUint iTrackPosSeconds;
    TUint iStreamId;
    TBool iLive;
    StoreInt* iStorePresetId;
    Media::BwsTrackUri iPresetUri; // only required by Fetch(TUint) but too large for the stack
    Media::BwsTrackMetaData iPresetMetadata; // only required by Fetch(TUint) but too large for the stack
};

} // namespace Av
} // namespace OpenHome

