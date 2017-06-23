#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Scd {

class SupplyScd : public Media::ISupply, private INonCopyable
{
    static const TUint kAggregateAudioJiffies = 5 * Media::Jiffies::kPerMs;
public:
    SupplyScd(Media::MsgFactory& aMsgFactory,
              Media::IPipelineElementDownstream& aDownStreamElement);
    virtual ~SupplyScd();
    void Flush();
    void Discard();
public: // from Media::ISupply
    void OutputTrack(Media::Track& aTrack, TBool aStartOfStream = true) override;
    void OutputDrain(Functor aCallback) override;
    void OutputDelay(TUint aJiffies) override;
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TUint64 aStartPos, TBool aSeekable, TBool aLive, Media::Multiroom aMultiroom, Media::IStreamHandler& aStreamHandler, TUint aStreamId) override;
    void OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, Media::Multiroom aMultiroom, Media::IStreamHandler& aStreamHandler, TUint aStreamId, const Media::PcmStreamInfo& aPcmStream) override;
    void OutputData(const Brx& aData) override;
    void OutputMetadata(const Brx& aMetadata) override;
    void OutputHalt(TUint aHaltId = Media::MsgHalt::kIdNone) override;
    void OutputFlush(TUint aFlushId) override;
    void OutputWait() override;
protected:
    void Output(Media::Msg* aMsg);
    inline void OutputEncodedAudio();
private:
    Media::MsgFactory& iMsgFactory;
    Media::IPipelineElementDownstream& iDownStreamElement;
    Media::MsgAudioEncoded* iAudioEncoded;
    TUint iBytesPerAudioMsg;
};

};  // namespace Scd
};  // namespace OpenHome
