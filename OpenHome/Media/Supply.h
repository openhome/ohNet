#ifndef HEADER_PIPELINE_SUPPLY
#define HEADER_PIPELINE_SUPPLY

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>

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
    void OutputMode(const Brx& aMode, TBool aSupportsLatency, TBool aRealTime);
    void OutputTrack(Track& aTrack, TUint aTrackId, const Brx& aMode);
    void OutputDelay(TUint aJiffies);
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId);
    void OutputData(const Brx& aData);
    void OutputMetadata(const Brx& aMetadata);
    void OutputFlush(TUint aFlushId);
    void OutputWait();
    void OutputHalt(TUint aHaltId);
    void OutputQuit();
private:
    MsgFactory& iMsgFactory;
    IPipelineElementDownstream& iDownStreamElement;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SUPPLY
