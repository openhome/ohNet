#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Codec/Id3v2.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

// CodecBase

CodecBase::~CodecBase()
{
}

void CodecBase::StreamInitialise()
{
}

void CodecBase::StreamCompleted()
{
}

CodecBase::CodecBase()
    : iController(NULL)
{
}

void CodecBase::Construct(ICodecController& aController, MsgFactory& aMsgFactory)
{
    iController = &aController;
    iMsgFactory = &aMsgFactory;
}


// CodecController

CodecController::CodecController(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IPipelineElementDownstream& aDownstreamElement)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iDownstreamElement(aDownstreamElement)
    , iLock("CDCC")
    , iActiveCodec(NULL)
    , iPendingMsg(NULL)
    , iPostSeekStreamInfo(NULL)
    , iAudioEncoded(NULL)
    , iRestreamer(NULL)
    , iLiveStreamer(NULL)
    , iStreamId(0)
    , iSampleRate(0)
    , iStreamLength(0)
    , iStreamPos(0)
{
    iDecoderThread = new ThreadFunctor("CDEC", MakeFunctor(*this, &CodecController::CodecThread));
    iDecoderThread->Start();
}

CodecController::~CodecController()
{
    for (size_t i=0; i<iCodecs.size(); i++) {
        delete iCodecs[i];
    }
    delete iDecoderThread;
    ReleaseAudioEncoded();
    if (iPostSeekStreamInfo != NULL) {
        iPostSeekStreamInfo->RemoveRef();
    }
}

void CodecController::AddCodec(CodecBase* aCodec)
{
    aCodec->Construct(*this, iMsgFactory);
    iCodecs.push_back(aCodec);
}

TBool CodecController::Seek(TUint /*aTrackId*/, TUint aStreamId, TUint aSecondsAbsolute)
{
    AutoMutex a(iLock);
    // FIXME - check aTrackId
    if (aStreamId != iStreamId) {
        return false;
    }
    if (iActiveCodec == NULL || iRestreamer == NULL) {
        return false;
    }
    iSeek = true;
    iSeekSeconds = aSecondsAbsolute;
    /* If we're very near the end of the track, we may return success here but later fail to seek.
       Its hard to imagine what sort of UI would display error indication from seek so it doesn't
       seem worth worrying about this. */
    return true;
}

void CodecController::CodecThread()
{
    iStreamStarted = false;
    iQuit = false;
    while (!iQuit) {
        try {
            iLock.Wait();
            iQueueTrackData = false;
            iStreamEnded = false;
            iSeek = false;
            iActiveCodec = NULL;
            iRestreamer = NULL;
            iLiveStreamer = NULL;
            iStreamId = 0;
            iSampleRate = 0;
            iStreamLength = 0;
            iStreamPos = 0;
            iSeek = false;
            iSeekSeconds = 0;
            iFlushExpectedCount = 0;
            ReleaseAudioEncoded();
            iLock.Signal();

            // Find next start of stream marker, ignoring any audio or meta data we encounter
            while (!iStreamStarted && !iQuit) {
                Msg* msg = iUpstreamElement.Pull();
                msg = msg->Process(*this);
                if (msg != NULL) {
                    Queue(msg);
                }
            }
            if (iQuit) {
                break;
            }
            iQueueTrackData = true;
            iStreamStarted = iStreamEnded = false;

            // Read audio data then attempt to recognise it
            do {
                Msg* msg = iUpstreamElement.Pull();
                msg = msg->Process(*this);
                if (msg != NULL) {
                    Queue(msg);
                }
            } while (!iStreamEnded && (iAudioEncoded == NULL || iAudioEncoded->Bytes() < kMaxRecogniseBytes));
            if (iQuit) {
                break;
            }
            if (iStreamEnded) {
                continue;
            }
            /* we can only CopyTo a max of kMaxRecogniseBytes bytes.  If we have more data than this, 
                split the msg, select a codec then add the fragments back together before processing */
            MsgAudioEncoded* remaining = NULL;
            if (iAudioEncoded->Bytes() > kMaxRecogniseBytes) {
                remaining = iAudioEncoded->Split(kMaxRecogniseBytes);
            }
            iAudioEncoded->CopyTo(iReadBuf);
            Brn recogBuf(iReadBuf, kMaxRecogniseBytes);
            for (size_t i=0; i<iCodecs.size(); i++) {
                CodecBase* codec = iCodecs[i];
                if (codec->Recognise(recogBuf)) {
                    iActiveCodec = codec;
                    break;
                }
            }
            iAudioEncoded->Add(remaining);
            if (iActiveCodec == NULL) {
                // FIXME - send error indication down the pipeline?
                continue;
            }

            // tell codec to process audio data
            // (blocks until end of stream or a flush)
            iActiveCodec->StreamInitialise();
            for (;;) {
                try {
                    iLock.Wait();
                    TBool seek = iSeek;
                    iLock.Signal();
                    if (seek) {
                        iSeek = false;
                        TUint64 sampleNum = iSeekSeconds * iSampleRate;
                        /*iLock.Wait();
                        // need to increment iFlushExpectedCount now in case TrySeek results in updated DecodedStreamInfo being output
                        iFlushExpectedCount++;
                        iLock.Signal();*/
                        if (!iActiveCodec->TrySeek(iStreamId, sampleNum)) {
                            /*iLock.Wait();
                            iFlushExpectedCount--;
                            iLock.Signal();*/
                        }
                    }
                    else {
                        iActiveCodec->Process();
                    }
                }
                catch (CodecStreamStart&) { }
                catch (CodecStreamEnded&) { }
                catch (CodecStreamCorrupt&) {
                    iStreamEnded = true;
                }
                if (iStreamEnded) {
                    iActiveCodec->StreamCompleted();
                    break;
                }
            }
        }
        catch (CodecStreamFlush&) {
            // FIXME
        }
    }
}

void CodecController::PullMsg()
{
    Msg* msg = iUpstreamElement.Pull();
    msg = msg->Process(*this);
    ASSERT_DEBUG(msg == NULL);
}

void CodecController::Queue(Msg* aMsg)
{
    iDownstreamElement.Push(aMsg);
}

TBool CodecController::QueueTrackData() const
{
    return (iQueueTrackData && iFlushExpectedCount == 0);
}

void CodecController::ReleaseAudioEncoded()
{
    if (iAudioEncoded != NULL) {
        iAudioEncoded->RemoveRef();
        iAudioEncoded = NULL;
    }
}

void CodecController::Read(Bwx& aBuf, TUint aBytes)
{
    if (iPendingMsg != NULL) {
        if (DoRead(aBuf, aBytes)) {
            return;
        }
        Queue(iPendingMsg);
        iPendingMsg = NULL;
    }
    if (iStreamEnded) {
        if (DoRead(aBuf, aBytes)) {
            return;
        }
        if (iStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
    }
    while (!iStreamEnded && (iAudioEncoded == NULL || iAudioEncoded->Bytes() < aBytes)) {
        Msg* msg = iUpstreamElement.Pull();
        msg = msg->Process(*this);
        if (msg != NULL) {
            iPendingMsg = msg;
            break;
        }
    }
    (void)DoRead(aBuf, aBytes);
}

TBool CodecController::DoRead(Bwx& aBuf, TUint aBytes)
{
    if (iAudioEncoded == NULL) {
        return false;
    }
    MsgAudioEncoded* remaining = NULL;
    if (iAudioEncoded->Bytes() > aBytes) {
        remaining = iAudioEncoded->Split(aBytes);
    }
    const TUint bytes = iAudioEncoded->Bytes();
    ASSERT(aBuf.Bytes() + bytes <= aBuf.MaxBytes());
    TByte* ptr = const_cast<TByte*>(aBuf.Ptr()) + aBuf.Bytes();
    iAudioEncoded->CopyTo(ptr);
    aBuf.SetBytes(aBuf.Bytes() + bytes);
    iAudioEncoded->RemoveRef();
    iAudioEncoded = remaining;
    iStreamPos += bytes;
    return true;
}

TBool CodecController::TrySeek(TUint aStreamId, TUint64 aBytePos)
{
    ReleaseAudioEncoded();
    iLock.Wait();
    // need to increment iFlushExpectedCount now in case TrySeek results in updated DecodedStreamInfo being output
    iFlushExpectedCount++;
    iLock.Signal();
    const TBool canSeek = iRestreamer->Restream(aStreamId, aBytePos);
    if (canSeek) {
        iStreamPos = aBytePos;
    }
    else {
        iLock.Wait();
        iFlushExpectedCount--;
        iLock.Signal();
    }
    return canSeek;
}

TUint64 CodecController::StreamLength() const
{
    return iStreamLength;
}

TUint64 CodecController::StreamPos() const
{
    // FIXME doesn't work with containers.  Need to be told when a container consumes data from a stream.
    return iStreamPos;
}

void CodecController::OutputDecodedStream(TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless)
{
    MsgDecodedStream* msg = iMsgFactory.CreateMsgDecodedStream(iStreamId, aBitRate, aBitDepth, aSampleRate, aNumChannels, aCodecName, aTrackLength, aSampleStart, aLossless, iLiveStreamer);
    iLock.Wait();
    iSampleRate = aSampleRate;
    if (iFlushExpectedCount > 0) {
        if (iPostSeekStreamInfo != NULL) {
            iPostSeekStreamInfo->RemoveRef();
        }
        iPostSeekStreamInfo = msg;
    }
    else {
        Queue(msg);
    }
    iLock.Signal();
}

void CodecController::Output(MsgAudioPcm* aMsg)
{
    Queue(aMsg);
}

Msg* CodecController::ProcessMsg(MsgAudioEncoded* aMsg)
{
    if (!QueueTrackData()) {
        aMsg->RemoveRef();
    }
    else if (iAudioEncoded == NULL) {
        iAudioEncoded = aMsg;
    }
    else {
        iAudioEncoded->Add(aMsg);
    }
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); // not expected at this stage of the pipeline
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // not expected at this stage of the pipeline
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // not expected at this stage of the pipeline
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // expect this to be generated by a codec
    // FIXME - volkano has containers which also generate this
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgEncodedStream* aMsg)
{
    iStreamStarted = iStreamEnded = true;
    iStreamId = aMsg->StreamId();
    iSeek = false; // clear any pending seek - it'd have been against a previous track now
    iStreamLength = aMsg->TotalBytes();
    iRestreamer = aMsg->Restreamer();
    iLiveStreamer = aMsg->LiveStreamer();
    aMsg->RemoveRef();
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgMetaText* aMsg)
{
    if (!QueueTrackData()) {
        aMsg->RemoveRef();
    }
    else {
        Queue(aMsg);
    }
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgHalt* aMsg)
{
    iStreamEnded = true;
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgFlush* aMsg)
{
    ReleaseAudioEncoded();
    Queue(aMsg);
    AutoMutex a(iLock);
    if (iFlushExpectedCount == 0) {
        THROW(CodecStreamFlush);
    }
    if (--iFlushExpectedCount == 0) {
        if (iPostSeekStreamInfo != NULL) {
            Queue(iPostSeekStreamInfo);
            iPostSeekStreamInfo = NULL;
        }
    }
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    iStreamEnded = true;
    return aMsg;
}
