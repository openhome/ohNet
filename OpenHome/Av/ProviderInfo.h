#pragma once

#include <Generated/DvAvOpenhomeOrgInfo1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Av {

class ProviderInfo : public Net::DvProviderAvOpenhomeOrgInfo1, private Media::IPipelineObserver
{
    static const TUint kMaxReportedBitDepth;
public:
    ProviderInfo(Net::DvDevice& aDevice, Media::PipelineManager& aPipelineManager);
    ~ProviderInfo();
private:
    void SetTrackInfo(const Brx& aTrackUri, const Brx& aMetaData);
    void ClearStreamInfo(const Brx& aTrackUri, const Brx& aMetaData);
private: // from Net::DvProviderAvOpenhomeOrgInfo1
    void Counters(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aTrackCount, Net::IDvInvocationResponseUint& aDetailsCount, Net::IDvInvocationResponseUint& aMetatextCount) override;
    void Track(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aUri, Net::IDvInvocationResponseString& aMetadata) override;
    void Details(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aDuration, Net::IDvInvocationResponseUint& aBitRate, Net::IDvInvocationResponseUint& aBitDepth, Net::IDvInvocationResponseUint& aSampleRate, Net::IDvInvocationResponseBool& aLossless, Net::IDvInvocationResponseString& aCodecName) override;
    void Metatext(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
private: // from IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState) override;
    void NotifyMode(const Brx& aMode, const Media::ModeInfo& aInfo) override;
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo) override;
private:
    Media::PipelineManager& iPipelineManager;
    Mutex iLock;
    Media::BwsTrackUri iTrackUri;
    Media::BwsTrackMetaData iMetaData;
    Media::BwsCodecName iCodecName;
    Bws<Media::MsgMetaText::kMaxBytes> iMetaText;
};

} // namespace Av
} // namespace OpenHome

