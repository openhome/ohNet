#include <OpenHome/Av/ProviderTime.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

ProviderTime::ProviderTime(DvDevice& aDevice, PipelineManager& aPipelineManager)
    : DvProviderAvOpenhomeOrgTime1(aDevice)
    , iPipelineManager(aPipelineManager)
    , iLock("PrTm")
{
    EnablePropertyTrackCount();
    EnablePropertyDuration();
    EnablePropertySeconds();

    SetPropertyTrackCount(0);
    SetPropertyDuration(0);
    SetPropertySeconds(0);

    EnableActionTime();

    iPipelineManager.AddObserver(*this);
}

ProviderTime::~ProviderTime()
{
}

void ProviderTime::Time(IDvInvocation& aInvocation, IDvInvocationResponseUint& aTrackCount, IDvInvocationResponseUint& aDuration, IDvInvocationResponseUint& aSeconds)
{
    TUint propTrackCount = 0;
    TUint propDuration = 0;
    TUint propSeconds = 0;

    iLock.Wait();
    GetPropertyTrackCount(propTrackCount);
    GetPropertyDuration(propDuration);
    GetPropertySeconds(propSeconds);
    iLock.Signal();

    aInvocation.StartResponse();
    aTrackCount.Write(propTrackCount);
    aDuration.Write(propDuration);
    aSeconds.Write(propSeconds);
    aInvocation.EndResponse();
}

void ProviderTime::NotifyPipelineState(EPipelineState /*aState*/)
{
    // NOP -- playing, paused, stopped, buffering
}

void ProviderTime::NotifyTrack(Track& /*aTrack*/, const Brx& /*aMode*/, TUint /*aIdPipeline*/)
{
    TUint x = 0;
    iLock.Wait();
    GetPropertyTrackCount(x);
    SetPropertyTrackCount(x + 1);
    iLock.Signal();
}

void ProviderTime::NotifyMetaText(const Brx& /*aText*/)
{
    // NOP -- textual metadata
}

void ProviderTime::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    iLock.Wait();
    SetPropertyDuration(aTrackDurationSeconds);
    SetPropertySeconds(aSeconds);
    iLock.Signal();
}

void ProviderTime::NotifyStreamInfo(const DecodedStreamInfo& /*aStreamInfo*/)
{
    // NOP -- stream parameters not of interest
}
