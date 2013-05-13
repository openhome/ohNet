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
};

class IPipelineObserver
{
public:
    virtual ~IPipelineObserver() {}
    virtual void NotifyPipelineState(EPipelineState aState) = 0;
    virtual void NotifyTrack(Track& aTrack, TUint aIdPipeline) = 0;
    virtual void NotifyMetaText(const Brx& aText) = 0;
    virtual void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) = 0;
    virtual void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) = 0;
};
    
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_OBSERVER
