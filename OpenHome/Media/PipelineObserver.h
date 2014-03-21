#ifndef HEADER_PIPELINE_OBSERVER
#define HEADER_PIPELINE_OBSERVER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

enum EPipelineState
{
    EPipelinePlaying
   ,EPipelinePaused
   ,EPipelineStopped
   ,EPipelineBuffering
   ,EPipelineWaiting
   ,EPipelineStateCount // Count of available states. Never reported as a state itself
};

class IPipelineObserver
{
public:
    virtual ~IPipelineObserver() {}
    virtual void NotifyPipelineState(EPipelineState aState) = 0;
    virtual void NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline) = 0;
    virtual void NotifyMetaText(const Brx& aText) = 0;
    virtual void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) = 0;
    virtual void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) = 0;
};

class TransportState
{
public:
    static const TChar* FromPipelineState(EPipelineState aState);
};

class NullPipelineObserver : public IPipelineObserver
{
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(const Brx& aUri, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
};

class LoggingPipelineObserver : public IPipelineObserver
{
public:
    LoggingPipelineObserver();
    void Enable(TBool aEnable);
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private:
    TBool iEnable;
};
    
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_OBSERVER
