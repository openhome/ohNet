#ifndef HEADER_PROVIDER_INFO_1
#define HEADER_PROVIDER_INFO_1

#include <Generated/DvAvOpenhomeOrgInfo1.h>

#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/Msg.h>

#include <OpenHome/Private/Thread.h>

namespace OpenHome {

using namespace Net;
using namespace Media;

namespace Av {

class ProviderInfo : public DvProviderAvOpenhomeOrgInfo1, private IPipelineObserver
{
public:
    ProviderInfo(DvDevice& aDevice, PipelineManager& aPipelineManager);
    ~ProviderInfo();
private: // from DvProviderAvOpenhomeOrgInfo1 (and only ever invoked from base class)
    void Counters(IDvInvocation& aInvocation, IDvInvocationResponseUint& aTrackCount, IDvInvocationResponseUint& aDetailsCount, IDvInvocationResponseUint& aMetatextCount);
    void Track(IDvInvocation& aInvocation, IDvInvocationResponseString& aUri, IDvInvocationResponseString& aMetadata);
    void Details(IDvInvocation& aInvocation, IDvInvocationResponseUint& aDuration, IDvInvocationResponseUint& aBitRate, IDvInvocationResponseUint& aBitDepth, IDvInvocationResponseUint& aSampleRate, IDvInvocationResponseBool& aLossless, IDvInvocationResponseString& aCodecName);
    void Metatext(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private:
    PipelineManager& iPipelineManager;
    Mutex iLock;
    Bws<kTrackUriMaxBytes> iTrackUri;
    Bws<kTrackMetaDataMaxBytes> iMetaData;
    Bws<DecodedStreamInfo::kMaxCodecNameBytes> iCodecName;
    Bws<MsgEncodedStream::kMaxMetaTextBytes> iMetaText;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_INFO_1
