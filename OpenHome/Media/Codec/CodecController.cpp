#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/Media/Rewinder.h>
#include <OpenHome/Media/Logger.h>

#include <algorithm>

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

void CodecBase::Construct(ICodecController& aController)
{
    iController = &aController;
}


// CodecController

CodecController::CodecController(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IPipelineElementDownstream& aDownstreamElement)
    : iMsgFactory(aMsgFactory)
    , iRewinder(aMsgFactory, aUpstreamElement)
    , iDownstreamElement(aDownstreamElement)
    , iLock("CDCC")
    , iActiveCodec(NULL)
    , iPendingMsg(NULL)
    , iPostSeekStreamInfo(NULL)
    , iAudioEncoded(NULL)
    , iSeekable(false)
    , iLive(false)
    , iStreamHandler(NULL)
    , iStreamId(0)
    , iSampleRate(0)
    , iStreamLength(0)
    , iStreamPos(0)
{
    iDecoderThread = new ThreadFunctor("CodecController", MakeFunctor(*this, &CodecController::CodecThread));
    iLoggerRewinder = new Logger(iRewinder, "Rewinder");
    //iLoggerRewinder->SetEnabled(true);
    //iLoggerRewinder->SetFilter(Logger::EMsgAll);
}

CodecController::~CodecController()
{
    delete iDecoderThread;
    ASSERT(iPendingMsg == NULL);
    for (size_t i=0; i<iCodecs.size(); i++) {
        delete iCodecs[i];
    }
    ReleaseAudioEncoded();
    if (iPostSeekStreamInfo != NULL) {
        iPostSeekStreamInfo->RemoveRef();
    }
    delete iLoggerRewinder;
}

void CodecController::AddCodec(CodecBase* aCodec)
{
    aCodec->Construct(*this);
    iCodecs.push_back(aCodec);
}

void CodecController::Start()
{
    iDecoderThread->Start();
}

TBool CodecController::Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute)
{
    AutoMutex a(iLock);
    if (iTrackId != aTrackId || aStreamId != iStreamId) {
        return false;
    }
    if (iActiveCodec == NULL || !iSeekable) {
        return false;
    }
    iSeek = true;
    iSeekSeconds = aSecondsAbsolute;
    /* If we're very near the end of the track, we may return success here but later fail to seek.
       Its hard to imagine what sort of UI would display error indication from seek so it doesn't
       seem worth worrying about this. */
    return true;
}

TBool CodecController::SupportsMimeType(const Brx& aMimeType)
{
    for (TUint i=0; i<iCodecs.size(); i++) {
        if (iCodecs[i]->SupportsMimeType(aMimeType)) {
            return true;
        }
    }
    return false;
}

void CodecController::CodecThread()
{
    iStreamStarted = false;
    iQuit = false;
    iExpectedFlushId = MsgFlush::kIdInvalid;
    iConsumeExpectedFlush = false;
    while (!iQuit) {
        try {
            iLock.Wait();
            iQueueTrackData = iStreamEnded = iStreamStopped = iSeekable = iLive = iSeek = iRecognising = false;
            iActiveCodec = NULL;
            iStreamId = iSampleRate = iSeekSeconds = 0;
            iStreamLength = iStreamPos = 0LL;
            ReleaseAudioEncoded();
            iLock.Signal();

            // Find next start of stream marker, ignoring any audio or meta data we encounter
            while (!iStreamStarted && !iQuit) {
                Msg* msg = PullMsg();
                if (msg != NULL) {
                    Queue(msg);
                }
            }
            if (iQuit) {
                break;
            }
            iQueueTrackData = true;
            iStreamStarted = iStreamEnded = false;
            iRecognising = true;

            for (size_t i=0; i<iCodecs.size() && !iQuit && !iStreamStopped; i++) {
                CodecBase* codec = iCodecs[i];
                TBool recognised = false;
                try {
                    recognised = codec->Recognise();
                }
                catch (CodecStreamStart&) {}
                catch (CodecStreamEnded&) {}
                catch (CodecStreamStopped&) {}
                catch (CodecStreamSeek&) {
                    ASSERTS();
                }
                catch (CodecStreamFlush&) {
                    ASSERTS();
                }
                catch (CodecStreamCorrupt&) {}
                catch (CodecStreamFeatureUnsupported&) {}
                iLock.Wait();
                iStreamStarted = iStreamEnded = false; // Rewind() will result in us receiving any additional Track or EncodedStream msgs again
                Rewind();
                iLock.Signal();
                if (recognised) {
                    iActiveCodec = codec;
                    break;
                }
            }
            iRecognising = false;
            iRewinder.Stop(iTrackId, iStreamId); // stop buffering audio
            if (iQuit) {
                break;
            }
            if (iActiveCodec == NULL) {
                Log::Print("Failed to recognise audio format, flushing stream...\n");
                // FIXME - send error indication down the pipeline?
                iExpectedFlushId = iStreamHandler->TryStop(iTrackId, iStreamId);
                if (iExpectedFlushId != MsgFlush::kIdInvalid) {
                    iConsumeExpectedFlush = true;
                }
                continue;
            }

            // tell codec to process audio data
            // (blocks until end of stream or a flush)
            try {
                iActiveCodec->StreamInitialise();
                for (;;) {
                    try {
                        iLock.Wait();
                        TBool seek = iSeek;
                        iLock.Signal();
                        if (seek) {
                            iSeek = false;
                            TUint64 sampleNum = iSeekSeconds * iSampleRate;
                            (void)iActiveCodec->TrySeek(iStreamId, sampleNum);
                        }
                        else {
                            iActiveCodec->Process();
                        }
                    }
                    catch (CodecStreamStart&) {}
                    catch (CodecStreamEnded&) {
                        iStreamEnded = true;
                    }
                    catch (CodecStreamCorrupt&) {
                        iStreamEnded = true;
                    }
                    catch (CodecStreamFeatureUnsupported&) {
                        iStreamEnded = true;
                    }
                    if (iStreamEnded) {
                        break;
                    }
                }
            }
            catch (CodecStreamCorrupt&) {
                // CodecStreamCorrupt thrown during StreamInitialise()
                // don't break here - might be waiting on a quit msg or similar
            }
            catch (CodecStreamFeatureUnsupported&) {
                // copy behaviour for Corrupt
            }
        }
        catch (CodecStreamStopped&) {}
        catch (CodecStreamFlush&) {}
        if (iActiveCodec != NULL) {
            iActiveCodec->StreamCompleted();
        }
        if (!iStreamStarted && !iStreamEnded) {
            iExpectedFlushId = iStreamHandler->TryStop(iTrackId, iStreamId);
            if (iExpectedFlushId != MsgFlush::kIdInvalid) {
                iConsumeExpectedFlush = true;
            }
        }
        // push out any pending msgs, such as a quit
        if (iPendingMsg != NULL) {
            Queue(iPendingMsg);
            iPendingMsg = NULL;
        }
    }
    if (iPendingMsg != NULL) {
        Queue(iPendingMsg);
        iPendingMsg = NULL;
    }
}

void CodecController::Rewind()
{
    iRewinder.Rewind();
    ReleaseAudioEncoded();
    iStreamPos = 0;
}

Msg* CodecController::PullMsg()
{
    Msg* msg = iLoggerRewinder->Pull();
    {
        AutoMutex a(iLock);
        msg = msg->Process(*this);
    }
    return msg;
}

void CodecController::Queue(Msg* aMsg)
{
    iDownstreamElement.Push(aMsg);
}

TBool CodecController::QueueTrackData() const
{
    return (iQueueTrackData && iExpectedFlushId == MsgFlush::kIdInvalid);
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
        THROW(CodecStreamEnded);
    }
    if (iStreamEnded || iStreamStopped) {
        if (DoRead(aBuf, aBytes)) {
            return;
        }
        if (iStreamStopped) {
            THROW(CodecStreamStopped);
        }
        if (iStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
    }
    while (!iStreamEnded && (iAudioEncoded == NULL || iAudioEncoded->Bytes() < aBytes)) {
        Msg* msg = PullMsg();
        if (msg != NULL) {
            iPendingMsg = msg;
            break;
        }
    }
    (void)DoRead(aBuf, aBytes);
}

TBool CodecController::DoRead(Bwx& aBuf, TUint aBytes)
{
    if (aBytes == 0) {
        return true;
    }
    if (iAudioEncoded == NULL) {
        return false;
    }
    MsgAudioEncoded* remaining = NULL;
    const TUint bufSpace = aBuf.MaxBytes() - aBuf.Bytes();
    const TUint toRead = std::min(bufSpace, aBytes);
    if (toRead < iAudioEncoded->Bytes()) {
        remaining = iAudioEncoded->Split(toRead);
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

void CodecController::ReadNextMsg(Bwx& aBuf)
{
    while (iAudioEncoded == NULL) {
        Msg* msg = PullMsg();
        if (msg != NULL) {
            Queue(msg);
        }
        if (iStreamEnded || iQuit) {
            THROW(CodecStreamEnded);
        }
    }
    DoRead(aBuf, iAudioEncoded->Bytes());
}

TBool CodecController::TrySeek(TUint aStreamId, TUint64 aBytePos)
{
    TUint flushId = iStreamHandler->TrySeek(iTrackId, aStreamId, aBytePos);
    if (flushId != MsgFlush::kIdInvalid) {
        ReleaseAudioEncoded();
        iExpectedFlushId = flushId;
        iStreamPos = aBytePos;
        return true;
    }
    return false;
}

TUint64 CodecController::StreamLength() const
{
    return iStreamLength;
}

TUint64 CodecController::StreamPos() const
{
    return iStreamPos;
}

void CodecController::OutputDecodedStream(TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless)
{
    MsgDecodedStream* msg = iMsgFactory.CreateMsgDecodedStream(iStreamId, aBitRate, aBitDepth, aSampleRate, aNumChannels, aCodecName, aTrackLength, aSampleStart, aLossless, iSeekable, iLive);
    iLock.Wait();
    iSampleRate = aSampleRate;
    if (iExpectedFlushId == MsgFlush::kIdInvalid) {
        Queue(msg);
    }
    else {
        if (iPostSeekStreamInfo != NULL) {
            iPostSeekStreamInfo->RemoveRef();
        }
        iPostSeekStreamInfo = msg;
    }
    iLock.Signal();
}

TUint64 CodecController::OutputAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset)
{
    MsgAudioPcm* audio = iMsgFactory.CreateMsgAudioPcm(aData, aChannels, aSampleRate, aBitDepth, aEndian, aTrackOffset);
    TUint jiffies= audio->Jiffies();
    Queue(audio);
    return jiffies;
}

TUint64 CodecController::OutputAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset,
                                        TUint aRxTimestamp, TUint aLatency, TUint aNetworkTimestamp, TUint aMediaTimestamp)
{
    MsgAudioPcm* audio = iMsgFactory.CreateMsgAudioPcm(aData, aChannels, aSampleRate, aBitDepth, aEndian, aTrackOffset, aRxTimestamp, aLatency, aNetworkTimestamp, aMediaTimestamp);
    TUint jiffies= audio->Jiffies();
    Queue(audio);
    return jiffies;
}

void CodecController::OutputHalt()
{
    MsgHalt* halt = iMsgFactory.CreateMsgHalt();
    Queue(halt);
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
    if (iRecognising) {
        aMsg->RemoveRef();
        return NULL;
    }

    iTrackId = aMsg->IdPipeline();
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgEncodedStream* aMsg)
{
//    Log::Print("CodecController::ProcessMsg(MsgEncodedStream*) iRecognising=%u\n", iRecognising);
    iStreamStarted = iStreamEnded = true;
    if (iRecognising) {
        aMsg->RemoveRef();
        return NULL;
    }

    iStreamId = aMsg->StreamId();
    iSeek = false; // clear any pending seek - it'd have been against a previous track now
    iStreamLength = aMsg->TotalBytes();
    iSeekable = aMsg->Seekable();
    iLive = aMsg->Live();
    iStreamHandler = aMsg->StreamHandler();
    MsgEncodedStream* msg = iMsgFactory.CreateMsgEncodedStream(aMsg->Uri(), aMsg->MetaText(), aMsg->TotalBytes(), aMsg->StreamId(), aMsg->Seekable(), aMsg->Live(), this);
    aMsg->RemoveRef();
    return msg;
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
    if (iExpectedFlushId == MsgFlush::kIdInvalid) {
        Queue(aMsg);
        THROW(CodecStreamFlush);
    }
    if (iExpectedFlushId != aMsg->Id()) {
        Queue(aMsg);
    }
    else {
        iExpectedFlushId = MsgFlush::kIdInvalid;
        if (iConsumeExpectedFlush) {
            iConsumeExpectedFlush = false;
            aMsg->RemoveRef();
        }
        else {
            Queue(aMsg);
            if (iPostSeekStreamInfo != NULL) {
                Queue(iPostSeekStreamInfo);
                iPostSeekStreamInfo = NULL;
            }
        }
    }
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    //iStreamEnded = true;  // will cause codec to quit prematurely
    return aMsg;
}

EStreamPlay CodecController::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    return iStreamHandler->OkToPlay(aTrackId, aStreamId);
}

TUint CodecController::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS(); // expect Seek requests to come to this class' public API, not from downstream
    return MsgFlush::kIdInvalid;
}

TUint CodecController::TryStop(TUint aTrackId, TUint aStreamId)
{
    AutoMutex a(iLock);
    if (iTrackId == aTrackId && iStreamId == aStreamId) {
        iStreamStopped = true;
    }
    if (iStreamHandler == NULL) {
        return MsgFlush::kIdInvalid;
    }
    const TUint flushId = iStreamHandler->TryStop(aTrackId, aStreamId);
    if (flushId != MsgFlush::kIdInvalid) {
        iExpectedFlushId = flushId;
        iConsumeExpectedFlush = false;
    }

    return flushId;
}
