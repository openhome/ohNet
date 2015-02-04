#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/Media/Pipeline/Rewinder.h>
#include <OpenHome/Media/Pipeline/Logger.h>
#include <OpenHome/Media/Debug.h>

#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


// class EncodedStreamInfo

TBool EncodedStreamInfo::RawPcm() const
{
    return iRawPcm;
}

TUint EncodedStreamInfo::BitDepth() const
{
    ASSERT(iRawPcm);
    return iBitDepth;
}

TUint EncodedStreamInfo::SampleRate() const
{
    ASSERT(iRawPcm);
    return iSampleRate;
}

TUint EncodedStreamInfo::NumChannels() const
{
    ASSERT(iRawPcm);
    return iNumChannels;
}

EMediaDataEndian EncodedStreamInfo::Endian() const
{
    return iEndian;
}

TUint64 EncodedStreamInfo::StartSample() const
{
    return iStartSample;
}

EncodedStreamInfo::EncodedStreamInfo()
    : iRawPcm(false)
    , iBitDepth(UINT_MAX)
    , iSampleRate(UINT_MAX)
    , iNumChannels(UINT_MAX)
    , iEndian(EMediaDataEndianInvalid)
    , iStartSample(0)
{
}

void EncodedStreamInfo::Set(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, EMediaDataEndian aEndian, TUint64 aStartSample)
{
    iRawPcm = true;
    iBitDepth = aBitDepth;
    iSampleRate = aSampleRate;
    iNumChannels = aNumChannels;
    iEndian = aEndian;
    iStartSample = aStartSample;
}


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

CodecController::CodecController(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IPipelineElementDownstream& aDownstreamElement, TUint aThreadPriority)
    : iMsgFactory(aMsgFactory)
    , iRewinder(aMsgFactory, aUpstreamElement)
    , iDownstreamElement(aDownstreamElement)
    , iLock("CDCC")
    , iActiveCodec(NULL)
    , iPendingMsg(NULL)
    , iSeekObserver(NULL)
    , iSeekHandle(0)
    , iPostSeekStreamInfo(NULL)
    , iAudioEncoded(NULL)
    , iSeekable(false)
    , iLive(false)
    , iRawPcm(false)
    , iStreamHandler(NULL)
    , iStreamId(0)
    , iSampleRate(0)
    , iStreamLength(0)
    , iStreamPos(0)
    , iTrackId(UINT_MAX)
{
    iDecoderThread = new ThreadFunctor("CodecController", MakeFunctor(*this, &CodecController::CodecThread), aThreadPriority);
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

void CodecController::StartSeek(TUint aStreamId, TUint aSecondsAbsolute, ISeekObserver& aObserver, TUint& aHandle)
{
    AutoMutex a(iLock);
    if (aStreamId != iStreamId || iActiveCodec == NULL || !iSeekable) {
        aHandle = ISeeker::kHandleError;
        return;
    }
    aHandle = ++iSeekHandle;
    iSeekObserver = &aObserver;
    iSeek = true;
    iSeekSeconds = aSecondsAbsolute;
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
    iSeek = false;
    iQuit = false;
    iExpectedFlushId = MsgFlush::kIdInvalid;
    iConsumeExpectedFlush = false;
    while (!iQuit) {
        // push out any pending msg (from previous run of loop)
        if (iPendingMsg != NULL) {
            Queue(iPendingMsg);
            iPendingMsg = NULL;
        }
        try {
            iLock.Wait();
            iQueueTrackData = iStreamEnded = iStreamStopped = iSeekable = iLive = iSeek = iRecognising = false;
            iActiveCodec = NULL;
            iStreamId = iSampleRate = iSeekSeconds = 0;
            iStreamLength = iStreamPos = 0LL;
            ReleaseAudioEncoded();
            iLock.Signal();

            LOG(kMedia, "CodecThread - search for new stream\n");
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
            EncodedStreamInfo streamInfo;
            if (iRawPcm) {
                streamInfo.Set(iPcmStream.BitDepth(), iPcmStream.SampleRate(), iPcmStream.NumChannels(), iPcmStream.Endian(), iPcmStream.StartSample());
            }

            LOG(kMedia, "CodecThread: start recognition.  iTrackId=%u, iStreamId=%u\n", iTrackId, iStreamId);

            for (size_t i=0; i<iCodecs.size() && !iQuit && !iStreamStopped; i++) {
                CodecBase* codec = iCodecs[i];
                TBool recognised = false;
                try {
                    recognised = codec->Recognise(streamInfo);
                }
                catch (CodecStreamStart&) {}
                catch (CodecStreamEnded&) {}
                catch (CodecStreamStopped&) {}
                catch (CodecStreamFlush&) {
                    break;
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
            iRewinder.Stop(); // stop buffering audio
            if (iQuit) {
                break;
            }
            LOG(kMedia, "CodecThread: recognition complete\n");
            if (iActiveCodec == NULL) {
                if (iStreamId != 0) { // FIXME - hard-coded assumption about Filler's NullTrack
                    Log::Print("Failed to recognise audio format (iStreamStopped=%u, iExpectedFlushId=%u), flushing stream...\n", iStreamStopped, iExpectedFlushId);
                }
                iLock.Wait();
                if (iExpectedFlushId == MsgFlush::kIdInvalid) {
                    iExpectedFlushId = iStreamHandler->TryStop(iStreamId);
                    if (iExpectedFlushId != MsgFlush::kIdInvalid) {
                        iConsumeExpectedFlush = true;
                    }
                }
                iLock.Signal();
                continue;
            }

            // tell codec to process audio data
            // (blocks until end of stream or a flush)
            try {
                iActiveCodec->StreamInitialise();
                for (;;) {
                    iLock.Wait();
                    TBool seek = iSeek;
                    iSeek = false;
                    ISeekObserver* seekObserver = iSeekObserver;
                    iLock.Signal();
                    if (seek) {
                        TUint64 sampleNum = iSeekSeconds * iSampleRate;
                        (void)iActiveCodec->TrySeek(iStreamId, sampleNum);
                        seekObserver->NotifySeekComplete(iSeekHandle, iExpectedFlushId);
                    }
                    else {
                        iActiveCodec->Process();
                    }
                }
            }
            catch (CodecStreamStart&) {}
            catch (CodecStreamEnded&) {
                iStreamEnded = true;
            }
            catch (CodecStreamCorrupt&) {}
            catch (CodecStreamFeatureUnsupported&) {}
        }
        catch (CodecStreamStopped&) {}
        catch (CodecStreamFlush&) {}
        if (iActiveCodec != NULL) {
            iActiveCodec->StreamCompleted();
        }
        if (!iStreamStarted && !iStreamEnded) {
            iLock.Wait();
            if (iExpectedFlushId == MsgFlush::kIdInvalid) {
                iExpectedFlushId = iStreamHandler->TryStop(iStreamId);
                if (iExpectedFlushId != MsgFlush::kIdInvalid) {
                    iConsumeExpectedFlush = true;
                }
            }
            iLock.Signal();
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
    iLock.Wait();
    if (iRecognising && iExpectedFlushId != MsgFlush::kIdInvalid) {
        /* waiting for a Flush causes QueueTrackData() to discard all msgs.
           If we're trying to recognise a new stream, Rewinder is active and will buffer all
           the msgs we're busily discarding.  We'll probably run out of memory at this point.
           Even if we don't, we don't want to be able to replay msgs that are certain to be
           discarded.  Throwing here allows us to break out of the recognise loop and safely
           allow QueueTrackData() to discard as much data as it wants. */
        iLock.Signal();
        THROW(CodecStreamFlush);
    }
    iLock.Signal();
    Msg* msg = iLoggerRewinder->Pull();
    {
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
            ASSERT(iPendingMsg == NULL);
            iPendingMsg = msg;
            break;
        }
    }
    if (!DoRead(aBuf, aBytes)) {
        if (iStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
     }
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

TBool CodecController::Read(IWriter& aWriter, TUint64 aOffset, TUint aBytes)
{
    if (!iStreamEnded && !iQuit) {
        return iStreamHandler->TryGet(aWriter, iStreamId, aOffset, aBytes);
    }
    return false;
}

TBool CodecController::TrySeekTo(TUint aStreamId, TUint64 aBytePos)
{
    TUint flushId = iStreamHandler->TrySeek(aStreamId, aBytePos);
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
    if (!Jiffies::IsValidSampleRate(aSampleRate)) {
        THROW(CodecStreamCorrupt);
    }
    MsgDecodedStream* msg = iMsgFactory.CreateMsgDecodedStream(iStreamId, aBitRate, aBitDepth, aSampleRate, aNumChannels, aCodecName, aTrackLength, aSampleStart, aLossless, iSeekable, iLive, iStreamHandler);
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

void CodecController::OutputDelay(TUint aJiffies)
{
    iLock.Wait();
    MsgDelay* msg = iMsgFactory.CreateMsgDelay(aJiffies);
    Queue(msg);
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
                                        TUint aRxTimestamp, TUint aNetworkTimestamp)
{
    MsgAudioPcm* audio = iMsgFactory.CreateMsgAudioPcm(aData, aChannels, aSampleRate, aBitDepth, aEndian, aTrackOffset, aRxTimestamp, aNetworkTimestamp);
    TUint jiffies= audio->Jiffies();
    Queue(audio);
    return jiffies;
}

void CodecController::OutputWait()
{
    MsgWait* wait = iMsgFactory.CreateMsgWait();
    Queue(wait);
}

void CodecController::OutputHalt()
{
    MsgHalt* halt = iMsgFactory.CreateMsgHalt();
    Queue(halt);
}

void CodecController::OutputSession()
{
    MsgSession* session = iMsgFactory.CreateMsgSession();
    Queue(session);
}

void CodecController::OutputMetaText(const Brx& aMetaText)
{
    MsgMetaText* text = iMsgFactory.CreateMsgMetaText(aMetaText);
    Queue(text);
}

Msg* CodecController::ProcessMsg(MsgMode* aMsg)
{
    if (iRecognising) {
        iStreamEnded = true;
        aMsg->RemoveRef();
        return NULL;
    }
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgSession* aMsg)
{
    if (iRecognising) {
        iStreamEnded = true;
        aMsg->RemoveRef();
        return NULL;
    }
    Queue(aMsg);
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgTrack* aMsg)
{
    if (iRecognising) {
        aMsg->RemoveRef();
        return NULL;
    }

    iLock.Wait();
    iTrackId = aMsg->Track().Id();
    iLock.Signal();
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgDelay* aMsg)
{
    if (iRecognising) { // FIXME - why discard during recognition?
        aMsg->RemoveRef();
        return NULL;
    }
    Queue(aMsg);
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgEncodedStream* aMsg)
{
    iStreamEnded = true;
    if (iRecognising) {
        aMsg->RemoveRef();
        return NULL;
    }

    iLock.Wait();
    iStreamStarted = true;
    iStreamId = aMsg->StreamId();
    iSeek = false; // clear any pending seek - it'd have been against a previous track now
    iStreamStopped = false; // likewise, if iStreamStopped was set, this was for the previous stream
    iStreamLength = aMsg->TotalBytes();
    iSeekable = aMsg->Seekable();
    iLive = aMsg->Live();
    iStreamHandler = aMsg->StreamHandler();
    iLock.Signal();
    MsgEncodedStream* msg = iMsgFactory.CreateMsgEncodedStream(aMsg->Uri(), aMsg->MetaText(), aMsg->TotalBytes(), aMsg->StreamId(), aMsg->Seekable(), aMsg->Live(), this);
    iRawPcm = aMsg->RawPcm();
    if (iRawPcm) {
        iPcmStream = aMsg->PcmStream();
    }
    else {
        iPcmStream.Clear();
    }
    aMsg->RemoveRef();
    return msg;
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

Msg* CodecController::ProcessMsg(MsgMetaText* aMsg)
{
    Queue(aMsg);
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgHalt* aMsg)
{
    iStreamEnded = true;
    if (iRecognising) {
        aMsg->RemoveRef();
        return NULL;
    }
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgFlush* aMsg)
{
    ReleaseAudioEncoded();
    /* Assuming that flush ids rise over time, receiving a msg with a higher id than we're
       expecting indicates that either we've missed our target msg or it wasn't sent */
    ASSERT(iExpectedFlushId == MsgFlush::kIdInvalid || iExpectedFlushId >= aMsg->Id());
    if (iExpectedFlushId == MsgFlush::kIdInvalid || iExpectedFlushId != aMsg->Id()) {
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

Msg* CodecController::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // expect this to be generated by a codec
    // FIXME - volkano has containers which also generate this
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

Msg* CodecController::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    //iStreamEnded = true;  // will cause codec to quit prematurely
    return aMsg;
}

EStreamPlay CodecController::OkToPlay(TUint aStreamId)
{
    return iStreamHandler->OkToPlay(aStreamId);
}

TUint CodecController::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS(); // expect Seek requests to come to this class' public API, not from downstream
    return MsgFlush::kIdInvalid;
}

TUint CodecController::TryStop(TUint aStreamId)
{
    AutoMutex a(iLock);
    if (iStreamId == aStreamId) {
        iStreamStopped = true;
    }
    if (iStreamHandler == NULL) {
        LOG(kMedia, "CodecController::TryStop returning MsgFlush::kIdInvalid (no stream handler)\n");
        return MsgFlush::kIdInvalid;
    }
    const TUint flushId = iStreamHandler->TryStop(aStreamId);
    if (flushId != MsgFlush::kIdInvalid) {
        iExpectedFlushId = flushId;
        iConsumeExpectedFlush = false;
    }
    LOG(kMedia, "CodecController::TryStop(%u) returning %u.  iStreamId=%u, iStreamStopped=%u\n",
                aStreamId, flushId, iStreamId, iStreamStopped);

    return flushId;
}

TBool CodecController::TryGet(IWriter& /*aWriter*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    ASSERTS();  // expect Get requests to come to this class' public API, not from downstream
                // i.e., nothing downstream of the codec should be requesting arbitrary data
    return false;
}

void CodecController::NotifyStarving(const Brx& aMode, TUint aStreamId)
{
    AutoMutex a(iLock);
    if (iStreamHandler != NULL) {
        iStreamHandler->NotifyStarving(aMode, aStreamId);
    }
}
