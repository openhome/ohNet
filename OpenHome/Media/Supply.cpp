#include <OpenHome/Media/Supply.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Supply

Supply::Supply(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownStreamElement)
    : iMsgFactory(aMsgFactory)
    , iDownStreamElement(aDownStreamElement)

{
}

Supply::~Supply()
{
}

void Supply::OutputSession()
{
    MsgSession* msg = iMsgFactory.CreateMsgSession();
    iDownStreamElement.Push(msg);
}

void Supply::OutputTrack(Track& aTrack, TBool aStartOfStream)
{
    MsgTrack* msg = iMsgFactory.CreateMsgTrack(aTrack, aStartOfStream);
    iDownStreamElement.Push(msg);
}

void Supply::OutputDelay(TUint aJiffies)
{
    MsgDelay* msg = iMsgFactory.CreateMsgDelay(aJiffies);
    iDownStreamElement.Push(msg);
}

void Supply::OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    // FIXME - no metatext available
    MsgEncodedStream* msg = iMsgFactory.CreateMsgEncodedStream(aUri, Brx::Empty(), aTotalBytes, aStreamId, aSeekable, aLive, &aStreamHandler);
    iDownStreamElement.Push(msg);
}

void Supply::OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId, const PcmStreamInfo& aPcmStream)
{
    // FIXME - no metatext available
    MsgEncodedStream* msg = iMsgFactory.CreateMsgEncodedStream(aUri, Brx::Empty(), aTotalBytes, aStreamId, aSeekable, aLive, &aStreamHandler, aPcmStream);
    iDownStreamElement.Push(msg);
}

void Supply::OutputData(const Brx& aData)
{
    if (aData.Bytes() == 0) {
        return;
    }
    MsgAudioEncoded* msg = iMsgFactory.CreateMsgAudioEncoded(aData);
    iDownStreamElement.Push(msg);
}

void Supply::OutputMetadata(const Brx& aMetadata)
{
    MsgMetaText* msg = iMsgFactory.CreateMsgMetaText(aMetadata);
    iDownStreamElement.Push(msg);
}

void Supply::OutputFlush(TUint aFlushId)
{
    MsgFlush* msg = iMsgFactory.CreateMsgFlush(aFlushId);
    iDownStreamElement.Push(msg);
}

void Supply::OutputWait()
{
    MsgWait* msg = iMsgFactory.CreateMsgWait();
    iDownStreamElement.Push(msg);
}
