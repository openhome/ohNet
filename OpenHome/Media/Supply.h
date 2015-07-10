#ifndef HEADER_PIPELINE_SUPPLY
#define HEADER_PIPELINE_SUPPLY

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Left-most pipeline element.
Creates pipeline messages based on requests from protocol modules or Pipeline
*/

class Supply : public ISupply, private INonCopyable
{
public:
    Supply(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownStreamElement);
    virtual ~Supply();
public: // from ISupply
    void OutputSession() override;
    void OutputTrack(Track& aTrack, TBool aStartOfStream = true) override;
    void OutputChangeInput(Functor aCallback) override;
    void OutputDelay(TUint aJiffies) override;
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId) override;
    void OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId, const PcmStreamInfo& aPcmStream) override;
    void OutputData(const Brx& aData) override;
    void OutputMetadata(const Brx& aMetadata) override;
    void OutputStreamInterrupted() override;
    void OutputFlush(TUint aFlushId) override;
    void OutputWait() override;
private:
    MsgFactory& iMsgFactory;
    IPipelineElementDownstream& iDownStreamElement;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SUPPLY
