#ifndef HEADER_PROVIDER_TIME_1
#define HEADER_PROVIDER_TIME_1

#include <Generated/DvAvOpenhomeOrgTime1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {

using namespace Net;
using namespace Media;

namespace Av {

class ProviderTime : public DvProviderAvOpenhomeOrgTime1, private IPipelineObserver
{
public:
    ProviderTime(DvDevice& aDevice, PipelineManager& aPipelineManager);
    ~ProviderTime();
private: // from DvProviderAvOpenhomeOrgTime1
    void Time(IDvInvocation& aInvocation, IDvInvocationResponseUint& aTrackCount, IDvInvocationResponseUint& aDuration, IDvInvocationResponseUint& aSeconds) override;
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState) override;
    void NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) override;
private:
    PipelineManager& iPipelineManager;
    Mutex iLock;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_TIME_1
