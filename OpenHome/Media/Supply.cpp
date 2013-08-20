#include <OpenHome/Media/Supply.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

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

void Supply::OutputTrack(Track& aTrack, TUint aTrackId, const Brx& aMode)
{
    MsgTrack* msg = iMsgFactory.CreateMsgTrack(aTrack, aTrackId, aMode);
    iDownStreamElement.Push(msg);
}

void Supply::OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    // FIXME - no metatext available
    MsgEncodedStream* msg = iMsgFactory.CreateMsgEncodedStream(aUri, Brx::Empty(), aTotalBytes, aStreamId, aSeekable, aLive, &aStreamHandler);
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

void Supply::OutputHalt()
{
    MsgHalt* msg = iMsgFactory.CreateMsgHalt();
    iDownStreamElement.Push(msg);
}

void Supply::OutputQuit()
{
    MsgQuit* msg = iMsgFactory.CreateMsgQuit();
    iDownStreamElement.Push(msg);
}
