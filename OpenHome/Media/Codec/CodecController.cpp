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

const TChar* CodecBase::Id() const
{
    return iId;
}

CodecBase::CodecBase(const TChar* aId, RecognitionComplexity aRecognitionCost)
    : iController(nullptr)
    , iId(aId)
    , iRecognitionCost(aRecognitionCost)
{
}

void CodecBase::Construct(ICodecController& aController)
{
    iController = &aController;
}


// CodecController

CodecController::CodecController(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IPipelineElementDownstream& aDownstreamElement,
                                 IUrlBlockWriter& aUrlBlockWriter, TUint aThreadPriority)
    : iMsgFactory(aMsgFactory)
    , iRewinder(aMsgFactory, aUpstreamElement)
    , iDownstreamElement(aDownstreamElement)
    , iUrlBlockWriter(aUrlBlockWriter)
    , iLock("CDCC")
    , iActiveCodec(nullptr)
    , iPendingMsg(nullptr)
    , iSeekObserver(nullptr)
    , iSeekHandle(0)
    , iPostSeekStreamInfo(nullptr)
    , iAudioEncoded(nullptr)
    , iSeekable(false)
    , iLive(false)
    , iRawPcm(false)
    , iStreamHandler(nullptr)
    , iStreamId(0)
    , iChannels(0)
    , iSampleRate(0)
    , iBitDepth(0)
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
    ASSERT(iPendingMsg == nullptr);
    for (size_t i=0; i<iCodecs.size(); i++) {
        delete iCodecs[i];
    }
    ReleaseAudioEncoded();
    if (iPostSeekStreamInfo != nullptr) {
        iPostSeekStreamInfo->RemoveRef();
    }
    delete iLoggerRewinder;
}

void CodecController::AddCodec(CodecBase* aCodec)
{
    aCodec->Construct(*this);
    const CodecBase::RecognitionComplexity cost = aCodec->iRecognitionCost;
    auto it = iCodecs.begin();
    for (; it!=iCodecs.end(); ++it) {
        if ((*it)->iRecognitionCost > cost) {
            break;
        }
    }
    iCodecs.insert(it, aCodec);
#if 0
    Log::Print("Sorted codecs are: ");
    it = iCodecs.begin();
    for (; it!=iCodecs.end(); ++it) {
        Log::Print("%s, ", (*it)->iId);
    }
    Log::Print("\n");
#endif
}

void CodecController::Start()
{
    iDecoderThread->Start();
}

void CodecController::StartSeek(TUint aStreamId, TUint aSecondsAbsolute, ISeekObserver& aObserver, TUint& aHandle)
{
    AutoMutex a(iLock);
    if (aStreamId != iStreamId) {
        LOG2(kMedia, kError, "CodecController::StartSeek(%u, %u) fail - wrong stream id (current %u)\n", aStreamId, aSecondsAbsolute, iStreamId);
        aHandle = ISeeker::kHandleError;
        return;
    }
    if (iActiveCodec == nullptr) {
        LOG2(kMedia, kError, "CodecController::StartSeek(%u, %u) fail - no active codec\n", aStreamId, aSecondsAbsolute);
        aHandle = ISeeker::kHandleError;
        return;
    }
    if (!iSeekable) {
        LOG2(kMedia, kError, "CodecController::StartSeek(%u, %u) fail - stream not seekable\n", aStreamId, aSecondsAbsolute);
        aHandle = ISeeker::kHandleError;
        return;
    }
    if (iSeek) {
        LOG2(kMedia, kError, "CodecController::StartSeek(%u, %u) fail - seek already in progress\n", aStreamId, aSecondsAbsolute);
        aHandle = ISeeker::kHandleError;
        return;
    }
    aHandle = ++iSeekHandle;
    iSeekObserver = &aObserver;
    iSeek = true;
    iSeekSeconds = aSecondsAbsolute;
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
        if (iPendingMsg != nullptr) {
            Queue(iPendingMsg);
            iPendingMsg = nullptr;
        }
        try {
            iLock.Wait();
            iQueueTrackData = iStreamEnded = iStreamStopped = iSeekable = iLive = iSeek = iRecognising = false;
            iActiveCodec = nullptr;
            iChannels = iBitDepth = 0;
            iSampleRate = iSeekSeconds = 0;
            iStreamId = IPipelineIdProvider::kStreamIdInvalid;
            iStreamLength = iStreamPos = 0LL;
            ReleaseAudioEncoded();
            iLock.Signal();

            LOG(kMedia, "CodecThread - search for new stream\n");
            // Find next start of stream marker, ignoring any audio or meta data we encounter
            while (!iStreamStarted && !iQuit) {
                Msg* msg = PullMsg();
                if (msg != nullptr) {
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
            TBool streamEnded = false;

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
                catch (CodecRecognitionOutOfData&) {
                    Log::Print("WARNING: codec %s filled Rewinder during recognition\n", codec->Id());
                }
                iLock.Wait();
                if (iStreamStarted || iStreamEnded) {
                    streamEnded = true;
                }
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
            if (iActiveCodec == nullptr) {
                if (iStreamId != 0  && // FIXME - hard-coded assumption about Filler's NullTrack
                    !iStreamStopped && // we wouldn't necessarily expect to recognise a track if we're told to stop
                    !streamEnded) {    // ...or reach the track end during recognition
                    Log::Print("Failed to recognise audio format (iStreamStopped=%u, iExpectedFlushId=%u), flushing stream...\n", iStreamStopped, iExpectedFlushId);
                }
                iLock.Wait();
                if (iExpectedFlushId == MsgFlush::kIdInvalid) {
                    (void)iStreamHandler->OkToPlay(iStreamId);
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
                    const TUint seekHandle = iSeekHandle;
                    iLock.Signal();
                    if (!seek) {
                        iActiveCodec->Process();
                    }
                    else {
                        iExpectedSeekFlushId = MsgFlush::kIdInvalid;
                        TUint64 sampleNum = iSeekSeconds * iSampleRate;
                        try {
                            (void)iActiveCodec->TrySeek(iStreamId, sampleNum);
                        }
                        catch (Exception&) {
                            iSeekObserver->NotifySeekComplete(seekHandle, MsgFlush::kIdInvalid);
                            throw;
                        }
                        iLock.Wait();
                        const TBool notify = (iSeek && iSeekHandle == seekHandle);
                        if (notify) {
                            iSeek = false;
                        }
                        const TUint flushId = iExpectedSeekFlushId;
                        ISeekObserver* seekObserver = iSeekObserver;
                        iLock.Signal();
                        if (notify) {
                            seekObserver->NotifySeekComplete(seekHandle, flushId);
                        }
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
        if (iActiveCodec != nullptr) {
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
    if (iPendingMsg != nullptr) {
        Queue(iPendingMsg);
        iPendingMsg = nullptr;
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
    if (msg == nullptr) {
        ASSERT(iRecognising);
        THROW(CodecRecognitionOutOfData);
    }
    msg = msg->Process(*this);
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
    if (iAudioEncoded != nullptr) {
        iAudioEncoded->RemoveRef();
        iAudioEncoded = nullptr;
    }
}

void CodecController::Read(Bwx& aBuf, TUint aBytes)
{
    if (iPendingMsg != nullptr) {
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
    while (!iStreamEnded && (iAudioEncoded == nullptr || iAudioEncoded->Bytes() < aBytes)) {
        Msg* msg = PullMsg();
        if (msg != nullptr) {
            ASSERT(iPendingMsg == nullptr);
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
    if (iAudioEncoded == nullptr) {
        return false;
    }
    MsgAudioEncoded* remaining = nullptr;
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
    while (iAudioEncoded == nullptr) {
        Msg* msg = PullMsg();
        if (msg != nullptr) {
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
        return iUrlBlockWriter.TryGet(aWriter, iTrackUri, aOffset, aBytes);
    }
    return false;
}

TBool CodecController::TrySeekTo(TUint aStreamId, TUint64 aBytePos)
{
    TUint flushId = iStreamHandler->TrySeek(aStreamId, aBytePos);
    if (flushId != MsgFlush::kIdInvalid) {
        ReleaseAudioEncoded();
        iExpectedFlushId = flushId;
        iConsumeExpectedFlush = false;
        iExpectedSeekFlushId = flushId;
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
    iChannels = aNumChannels;
    iSampleRate = aSampleRate;
    iBitDepth = aBitDepth;
    if (iExpectedFlushId == MsgFlush::kIdInvalid) {
        Queue(msg);
    }
    else {
        if (iPostSeekStreamInfo != nullptr) {
            iPostSeekStreamInfo->RemoveRef();
        }
        iPostSeekStreamInfo = msg;
        if (iSeek) {
            iSeekObserver->NotifySeekComplete(iSeekHandle, iExpectedSeekFlushId);
            iSeek = false;
        }
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
    ASSERT(aChannels == iChannels);
    ASSERT(aSampleRate == iSampleRate);
    ASSERT(aBitDepth == iBitDepth);
    if (iPostSeekStreamInfo != nullptr) {
        Queue(iPostSeekStreamInfo);
        iPostSeekStreamInfo = nullptr;
    }
    MsgAudioPcm* audio = iMsgFactory.CreateMsgAudioPcm(aData, aChannels, aSampleRate, aBitDepth, aEndian, aTrackOffset);
    TUint jiffies= audio->Jiffies();
    Queue(audio);
    return jiffies;
}

TUint64 CodecController::OutputAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset,
                                        TUint aRxTimestamp, TUint aNetworkTimestamp)
{
    ASSERT(aChannels == iChannels);
    ASSERT(aSampleRate == iSampleRate);
    ASSERT(aBitDepth == iBitDepth);
    if (iPostSeekStreamInfo != nullptr) {
        Queue(iPostSeekStreamInfo);
        iPostSeekStreamInfo = nullptr;
    }
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
        return nullptr;
    }
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgTrack* aMsg)
{
    if (iRecognising) {
        if (aMsg->StartOfStream()) {
            iStreamEnded = true;
        }
        aMsg->RemoveRef();
        return nullptr;
    }

    iLock.Wait();
    iTrackId = aMsg->Track().Id();
    iLock.Signal();
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgDrain* aMsg)
{
    Queue(aMsg);
    return nullptr;
}

Msg* CodecController::ProcessMsg(MsgDelay* aMsg)
{
    if (iRecognising) { // FIXME - why discard during recognition?
        aMsg->RemoveRef();
        return nullptr;
    }
    Queue(aMsg);
    return nullptr;
}

Msg* CodecController::ProcessMsg(MsgEncodedStream* aMsg)
{
    iStreamEnded = true;
    iTrackUri.Replace(aMsg->Uri());
    if (iRecognising) {
        aMsg->RemoveRef();
        return nullptr;
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
    else if (iAudioEncoded == nullptr) {
        iAudioEncoded = aMsg;
    }
    else {
        iAudioEncoded->Add(aMsg);
    }
    return nullptr;
}

Msg* CodecController::ProcessMsg(MsgMetaText* aMsg)
{
    Queue(aMsg);
    return nullptr;
}

Msg* CodecController::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iStreamEnded = true;
    Queue(aMsg);
    return nullptr;
}

Msg* CodecController::ProcessMsg(MsgHalt* aMsg)
{
    iStreamEnded = true;
    Queue(aMsg);
    return nullptr;
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
        }
    }
    return nullptr;
}

Msg* CodecController::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // expect this to be generated by a codec
    // FIXME - volkano has containers which also generate this
    return nullptr;
}

Msg* CodecController::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); // not expected at this stage of the pipeline
    return nullptr;
}

Msg* CodecController::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // not expected at this stage of the pipeline
    return nullptr;
}

Msg* CodecController::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // not expected at this stage of the pipeline
    return nullptr;
}

Msg* CodecController::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    //iStreamEnded = true;  // will cause codec to quit prematurely
    return aMsg;
}

EStreamPlay CodecController::OkToPlay(TUint aStreamId)
{
    ASSERT(iStreamHandler != nullptr);
    EStreamPlay canPlay = iStreamHandler->OkToPlay(aStreamId);
    //Log::Print("CodecController::OkToPlay(%u) returned %s\n", aStreamId, kStreamPlayNames[canPlay]);
    return canPlay;
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
    if (iStreamHandler == nullptr) {
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

void CodecController::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    AutoMutex a(iLock);
    if (iStreamHandler != nullptr) {
        iStreamHandler->NotifyStarving(aMode, aStreamId, aStarving);
    }
}


// CodecBufferedReader

CodecBufferedReader::CodecBufferedReader(ICodecController& aCodecController, Bwx& aBuf)
    : iCodecController(aCodecController)
    , iBuf(aBuf)
    , iState(eReading)
{
}

Brn CodecBufferedReader::Read(TUint aBytes)
{
    if (iState == eEos) {
        iState = eBeyondEos;
        return Brx::Empty();
    }
    else if (iState == eBeyondEos) {
        THROW(ReaderError); // Reading beyond EoS is an error.
    }
    else if (iState == eReading) {
        iBuf.SetBytes(0);
        // Valid to return up to aBytes, so if aBytes > iBuf.Bytes(), only return iBuf.Bytes().
        TUint bytes = aBytes;
        if (bytes > iBuf.MaxBytes()) {
            bytes = iBuf.MaxBytes();
        }

        iCodecController.Read(iBuf, bytes);
        if (iBuf.Bytes() < bytes) {
            // Reached end of stream.
            iState = eEos;
        }
        return Brn(iBuf.Ptr(), iBuf.Bytes());
    }

    ASSERTS();              // Uknown state.
    return Brx::Empty();    // Unreachable code.
}

void CodecBufferedReader::ReadFlush()
{
    iBuf.SetBytes(0);
}

void CodecBufferedReader::ReadInterrupt()
{
    ASSERTS();
}
