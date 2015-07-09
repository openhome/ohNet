#ifndef HEADER_PROVIDER_INFO_1
#define HEADER_PROVIDER_INFO_1

#include <Generated/DvAvOpenhomeOrgInfo1.h>

#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/Pipeline/Msg.h>

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
private:
    void SetTrackInfo(const Brx& aTrackUri, const Brx& aMetaData);
    void ClearStreamInfo(const Brx& aTrackUri, const Brx& aMetaData);
private: // from DvProviderAvOpenhomeOrgInfo1
    void Counters(IDvInvocation& aInvocation, IDvInvocationResponseUint& aTrackCount, IDvInvocationResponseUint& aDetailsCount, IDvInvocationResponseUint& aMetatextCount) override;
    void Track(IDvInvocation& aInvocation, IDvInvocationResponseString& aUri, IDvInvocationResponseString& aMetadata) override;
    void Details(IDvInvocation& aInvocation, IDvInvocationResponseUint& aDuration, IDvInvocationResponseUint& aBitRate, IDvInvocationResponseUint& aBitDepth, IDvInvocationResponseUint& aSampleRate, IDvInvocationResponseBool& aLossless, IDvInvocationResponseString& aCodecName) override;
    void Metatext(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue) override;
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState) override;
    void NotifyMode(const Brx& aMode, const Media::ModeInfo& aInfo) override;
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) override;
private:
    PipelineManager& iPipelineManager;
    Mutex iLock;
    Bws<kTrackUriMaxBytes> iTrackUri;
    Bws<kTrackMetaDataMaxBytes> iMetaData;
    Bws<DecodedStreamInfo::kMaxCodecNameBytes> iCodecName;
    Bws<MsgMetaText::kMaxBytes> iMetaText;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_INFO_1
