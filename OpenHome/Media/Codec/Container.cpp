#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


// ContainerBase

ContainerBase::ContainerBase(const Brx& aId)
    : iCache(nullptr)
    , iMsgFactory(nullptr)
    , iSeekHandler(nullptr)
    , iUrlBlockWriter(nullptr)
    , iStopper(nullptr)
    , iId(aId)
{
}

const Brx& ContainerBase::Id() const
{
    return iId;
}

void ContainerBase::Construct(IMsgAudioEncodedCache& aCache, MsgFactory& aMsgFactory, IContainerSeekHandler& aSeekHandler, IContainerUrlBlockWriter& aUrlBlockWriter, IContainerStopper& aContainerStopper)
{
    iCache = &aCache;
    iMsgFactory = &aMsgFactory;
    iSeekHandler = &aSeekHandler;
    iUrlBlockWriter = &aUrlBlockWriter;
    iStopper = &aContainerStopper;
}


// MsgAudioEncodedCache

MsgAudioEncodedCache::MsgAudioEncodedCache(IPipelineElementUpstream& aUpstreamElement)
    : iUpstreamElement(aUpstreamElement)
    , iAudioEncoded(nullptr)
    , iDiscardBytesRemaining(0)
    , iInspectBytesRemaining(0)
    , iAccumulateBytesRemaining(0)
    , iBuffer(nullptr)
    , iExpectedFlushId(MsgFlush::kIdInvalid)
    , iLock("AECL")
{
}

MsgAudioEncodedCache::~MsgAudioEncodedCache()
{
    ASSERT(iAudioEncoded == nullptr);
}

void MsgAudioEncodedCache::Reset()
{
    if (iAudioEncoded != nullptr) {
        iAudioEncoded->RemoveRef();
        iAudioEncoded = nullptr;
    }
    iDiscardBytesRemaining = 0;
    iInspectBytesRemaining = 0;
    iAccumulateBytesRemaining = 0;
    iBuffer = nullptr;  // Acutal buffer is owned by another class.
    iExpectedFlushId = MsgFlush::kIdInvalid;
}

void MsgAudioEncodedCache::SetFlushing(TUint aFlushId)
{
    AutoMutex a(iLock);
    Reset();
    iExpectedFlushId = aFlushId;
}

TUint MsgAudioEncodedCache::CacheBytes() const
{
    if (iAudioEncoded == nullptr) {
        return 0;
    }
    return iAudioEncoded->Bytes();
}

MsgAudioEncoded* MsgAudioEncodedCache::ProcessCache()
{
    if (iDiscardBytesRemaining > 0) {
        if (CacheBytes() > 0) {
            TUint discard = iDiscardBytesRemaining;
            if (discard > CacheBytes()) {
                discard = CacheBytes();
            }
            iDiscardBytesRemaining -= discard;
            MsgAudioEncoded* msg = ExtractMsgAudioEncoded(discard);
            msg->RemoveRef();
        }
        if (iDiscardBytesRemaining > 0) {
            return nullptr;
        }
    }

    if (iInspectBytesRemaining > 0) {
        if (CacheBytes() >= iInspectBytesRemaining) {
            MsgAudioEncoded* msg = ExtractMsgAudioEncoded(iInspectBytesRemaining);
            msg->CopyTo(const_cast<TByte*>(iBuffer->Ptr()));
            iBuffer->SetBytes(iInspectBytesRemaining);
            msg->RemoveRef();
            iInspectBytesRemaining = 0;
        }
        return nullptr;
    }

    if (iAccumulateBytesRemaining > 0) {
        if (CacheBytes() >= iAccumulateBytesRemaining) {
            MsgAudioEncoded* msg = ExtractMsgAudioEncoded(iAccumulateBytesRemaining);
            iAccumulateBytesRemaining = 0;
            return msg;
        }
        return nullptr;
    }

    if (CacheBytes() > 0) {
        MsgAudioEncoded* msg = iAudioEncoded;
        iAudioEncoded = nullptr;
        return msg;
    }

    return nullptr;
}

TBool MsgAudioEncodedCache::PendingInspectionBuffer() const
{
    return iInspectBytesRemaining > 0;
}

TBool MsgAudioEncodedCache::InspectionBufferFilled() const
{
    ASSERT(iBuffer != nullptr);
    return iBuffer->Bytes() == iInspectBufferBytes;
}

MsgAudioEncoded* MsgAudioEncodedCache::ExtractMsgAudioEncoded(TUint aBytes)
{
    MsgAudioEncoded* msg = nullptr;
    ASSERT(aBytes <= CacheBytes());
    if (aBytes == CacheBytes()) {
        msg = iAudioEncoded;
        iAudioEncoded = nullptr;
    }
    else {
        MsgAudioEncoded* remaining = iAudioEncoded->Split(aBytes);
        msg = iAudioEncoded;
        iAudioEncoded = remaining;
    }
    return msg;
}

Msg* MsgAudioEncodedCache::PullUpstreamMsg()
{
    // Must NOT be pulling another msg unless exhausted cached audio.
    ASSERT(iAudioEncoded == nullptr || (iDiscardBytesRemaining > iAudioEncoded->Bytes() || iInspectBytesRemaining > iAudioEncoded->Bytes() || iAccumulateBytesRemaining > iAudioEncoded->Bytes()));
    Msg* msg = iUpstreamElement.Pull();
    if (msg == nullptr) {
        THROW(CodecPulledNullMsg);
    }
    msg = msg->Process(*this);
    return msg;
}

void MsgAudioEncodedCache::Discard(TUint aBytes)
{
    //Log::Print("MsgAudioEncodedCache::Discard %u bytes\n", aBytes);
    ASSERT(iDiscardBytesRemaining == 0);
    iDiscardBytesRemaining = aBytes;
}

void MsgAudioEncodedCache::Inspect(Bwx& aBuf, TUint aBytes)
{
    //Log::Print("MsgAudioEncodedCache::Inspect %u bytes\n", aBytes);
    ASSERT(iBuffer == nullptr);
    ASSERT(aBytes != 0);
    ASSERT(aBuf.MaxBytes() >= aBytes);
    iBuffer = &aBuf;
    iBuffer->SetBytes(0);
    iInspectBytesRemaining = aBytes;
    iInspectBufferBytes = aBytes;
}

void MsgAudioEncodedCache::Accumulate(TUint aBytes)
{
    //Log::Print("MsgAudioEncodedCache::Accumulate %u bytes\n", aBytes);
    ASSERT(iAccumulateBytesRemaining == 0);
    iAccumulateBytesRemaining = aBytes;
}

Msg* MsgAudioEncodedCache::Pull()
{
    //Log::Print(">MsgAudioEncodedCache::Pull iDiscardBytesRemaining: %u, iInspectBytesRemaining: %u, iAccumulateBytesRemaining: %u\n", iDiscardBytesRemaining, iInspectBytesRemaining, iAccumulateBytesRemaining);

    Msg* msg = nullptr;
    while (msg == nullptr) {

        msg = ProcessCache();

        if (msg == nullptr && iBuffer != nullptr && InspectionBufferFilled()) {
            iBuffer = nullptr;
            iInspectBufferBytes = 0;
            return nullptr;
        }
        else if (msg != nullptr) {
            return msg;
        }


        if (iInspectBytesRemaining > 0) {
            if (iInspectBytesRemaining > CacheBytes()) {
                msg = PullUpstreamMsg();
            }
        }
        else if (iAccumulateBytesRemaining > 0) {
            if (iAccumulateBytesRemaining > CacheBytes()) {
                msg = PullUpstreamMsg();
            }
        }
        else {
            msg = PullUpstreamMsg();
        }

    }
    return msg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgDrain* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgEncodedStream* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgAudioEncoded* aMsg)
{
    AutoMutex a(iLock);
    if (iExpectedFlushId != MsgFlush::kIdInvalid) {
        aMsg->RemoveRef();
        return nullptr;
    }

    if (iAudioEncoded == nullptr) {
        iAudioEncoded = aMsg;
    }
    else {
        iAudioEncoded->Add(aMsg);
    }
    return nullptr;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgFlush* aMsg)
{
    AutoMutex a(iLock);
    if (iExpectedFlushId == aMsg->Id()) {
        iExpectedFlushId = MsgFlush::kIdInvalid;
    }
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgDecodedStream* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgBitRate* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgAudioPcm* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgPlayable* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedCache::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}


// ContainerNull

ContainerNull::ContainerNull()
    : ContainerBase(Brn("NULL"))
{
}

Msg* ContainerNull::Recognise()
{
    return nullptr;
}

TBool ContainerNull::Recognised() const
{
    return true;
}

void ContainerNull::Reset()
{
}

TBool ContainerNull::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    return iSeekHandler->TrySeekTo(aStreamId, aOffset);
}

Msg* ContainerNull::Pull()
{
    // Just keep pulling messages.
    Msg* msg = iCache->Pull();
    return msg;
}


// ContainerController

ContainerController::ContainerController(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IUrlBlockWriter& aUrlBlockWriter)
    : iMsgFactory(aMsgFactory)
    , iUrlBlockWriter(aUrlBlockWriter)
    , iRewinder(iMsgFactory, aUpstreamElement)
    , iLoggerRewinder(iRewinder, "Codec Container Rewinder")
    , iCache(iLoggerRewinder)
    , iActiveContainer(nullptr)
    , iContainerNull(nullptr)
    , iStreamHandler(nullptr)
    , iPassThrough(false)
    , iRecognising(false)
    , iState(eRecognitionStart)
    , iRecogIdx(0)
    , iStreamEnded(false)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iExpectedFlushId(MsgFlush::kIdInvalid)
    , iLock("COCO")
{
    iContainerNull = new ContainerNull();
    iContainerNull->Construct(iCache, iMsgFactory, *this, *this, *this);
    iContainers.push_back(iContainerNull);
    iActiveContainer = iContainerNull;

    //iLoggerRewinder.SetEnabled(true);
    //iLoggerRewinder.SetFilter(Logger::EMsgAll);
}

void ContainerController::AddContainer(ContainerBase* aContainer)
{
    aContainer->Construct(iCache, iMsgFactory, *this, *this, *this);

     // Pop ContainerNull from end and re-attach after aContainer.
     ASSERT(iContainers.size() >= 1);
     ContainerBase* containerNull = iContainers.back();
     iContainers.pop_back();
     iContainers.push_back(aContainer);
     iContainers.push_back(containerNull);
}

ContainerController::~ContainerController()
{
    for (auto container : iContainers) {
        delete container;
    }
    iCache.Reset();
}

Msg* ContainerController::RecogniseContainer()
{
    if (iPassThrough) {
        // No recognition on streams that support latency.
        iActiveContainer = iContainerNull;
        iRewinder.Stop();
        iCache.Reset();
        iActiveContainer->Reset();
        return nullptr;
    }
    else {
        iActiveContainer = nullptr;
        while (iState != eRecognitionComplete) {
            if (iState == eRecognitionStart) {
                iRecogIdx = 0;
                iState = eRecognitionSelectContainer;
            }
            else if (iState == eRecognitionSelectContainer) {
                ASSERT(iRecogIdx < iContainers.size()); // ContainerNull should always recognise.
                auto& container = iContainers[iRecogIdx];
                iStreamEnded = false;
                iRewinder.Rewind();
                iCache.Reset();
                container->Reset();
                iState = eRecognitionContainer;
            }
            else if (iState == eRecognitionContainer) {
                if (!iStreamEnded) {
                    auto& container = iContainers[iRecogIdx];
                    try {
                        Msg* msg = container->Recognise();
                        if (msg != nullptr) {
                            return msg;
                        }

                        if (container->Recognised()) {
                            iActiveContainer = container;
                            iRewinder.Rewind();
                            iRewinder.Stop();
                            iCache.Reset();
                            iState = eRecognitionComplete;
                            return nullptr;
                        }
                        else {
                            iRecogIdx++;
                            iState = eRecognitionSelectContainer;
                        }
                    }
                    catch (CodecPulledNullMsg&) {
                        const Brx& id = container->Id();
                        LOG(kMedia, "ContainerController::RecogniseContainer Rewinder exhausted while attempting to recognise %.*s\n", PBUF(id));

                        iRecogIdx++;
                        iState = eRecognitionSelectContainer;
                    }
                }
                else {
                    // iStreamEnded during recognition; move to next container.
                    iRecogIdx++;
                    iState = eRecognitionSelectContainer;
                }
            }
            else { // Unhandled state.
                ASSERTS();
                return nullptr;
            }
        }
        ASSERT(iActiveContainer != nullptr);    // Should have been detected by at least ContainerNull.
        return nullptr;
    }
}

Msg* ContainerController::Pull()
{
    TBool recognising = false;
    {
        // Don't hold iLock during recognition;
        // might block acquiring mutex in IStreamHandler calls.
        AutoMutex a(iLock);
        recognising = iRecognising;
    }

    Msg* msg = nullptr;
    while (recognising) {
        msg = RecogniseContainer();
        if (msg == nullptr) { // Completed recognition.
            iRecognising = false;
            iStreamEnded = false;
            recognising = false;
        }
        else {
            msg = msg->Process(*this);
            if (msg != nullptr) {
                return msg;
            }
        }
    }

    while (msg == nullptr) {
        ASSERT(iActiveContainer != nullptr);
        msg = iActiveContainer->Pull();
        ASSERT(msg != nullptr);
        msg = msg->Process(*this);
    }

    return msg;
}

Msg* ContainerController::ProcessMsg(MsgMode* aMsg)
{
    if (iRecognising) {
        iStreamEnded = true;
        aMsg->RemoveRef();
        return nullptr;
    }

    if (aMsg->Info().SupportsLatency()) {
        // Don't perform any recognition on streams that support latency.
        iPassThrough = true;
    }
    else {
        iPassThrough = false;
    }
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgTrack* aMsg)
{
    if (iRecognising) {
        if (aMsg->StartOfStream()) {
            iStreamEnded = true;
        }
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgDrain* aMsg)
{
    if (iRecognising) {
        iStreamEnded = true;
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgDelay* aMsg)
{
    if (iRecognising) {
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgEncodedStream* aMsg)
{
    iStreamEnded = true;
    if (iRecognising) {
        aMsg->RemoveRef();
        return nullptr;
    }
    iRecognising = true;
    iState = eRecognitionStart;
    iUrl.Replace(aMsg->Uri());  // Required to allow containers to do an out-of-band read.

    if (iUrl.Bytes() == 0) {
        // Dummy stream; don't attempt recognition as there will be no audio and pipeline will be blocked.
        iPassThrough = true;
    }

    auto msg = iMsgFactory.CreateMsgEncodedStream(aMsg, this);

    AutoMutex a(iLock);
    iStreamId = aMsg->StreamId();
    iExpectedFlushId = MsgFlush::kIdInvalid;
    iStreamHandler.store(aMsg->StreamHandler());
    aMsg->RemoveRef();

    return msg;
}

Msg* ContainerController::ProcessMsg(MsgAudioEncoded* aMsg)
{
    AutoMutex a(iLock);
    if (iExpectedFlushId != MsgFlush::kIdInvalid) {
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgMetaText* aMsg)
{
    if (iRecognising) {
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iStreamEnded = true;
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgHalt* aMsg)
{
    iStreamEnded = true;
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgFlush* aMsg)
{
    iStreamEnded = true;
    if (iRecognising) {
        aMsg->RemoveRef();
        return nullptr;
    }
    AutoMutex a(iLock);
    if (iExpectedFlushId == aMsg->Id()) {
        iExpectedFlushId = MsgFlush::kIdInvalid;
    }
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // expect this Msg to be generated by a downstream decoder element
    return nullptr;
}

Msg* ContainerController::ProcessMsg(MsgBitRate* /*aMsg*/)
{
    ASSERTS(); // expect this Msg to be generated by a downstream decoder element
    return nullptr;
}

Msg* ContainerController::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return nullptr;
}

Msg* ContainerController::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return nullptr;
}

Msg* ContainerController::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return nullptr;
}

Msg* ContainerController::ProcessMsg(MsgQuit* aMsg)
{
    //iStreamEnded = true;    // Will cause container to quit prematurely.
    return aMsg;
}

EStreamPlay ContainerController::OkToPlay(TUint aStreamId)
{
    LOG(kMedia, "ContainerController::OkToPlay aStreamId: %u\n", aStreamId);
    auto streamHandler = iStreamHandler.load();
    EStreamPlay canPlay = streamHandler->OkToPlay(aStreamId);
    return canPlay;
}

TUint ContainerController::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    LOG(kMedia, "ContainerController::TrySeek aStreamId: %u, aOffset: %llu\n", aStreamId, aOffset);
    AutoMutex a(iLock);
    const TBool seek = iActiveContainer->TrySeek(aStreamId, aOffset);
    if (!seek) {
        return MsgFlush::kIdInvalid;
    }
    return iExpectedFlushId;
}

TUint ContainerController::TryDiscard(TUint /*aJiffies*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint ContainerController::TryStop(TUint aStreamId)
{
    LOG(kMedia, "ContainerController::TryStop aStreamId: %u\n", aStreamId);
    AutoMutex a(iLock);
    auto streamHandler = iStreamHandler.load();
    ASSERT(streamHandler != nullptr);
    const TUint flushId = streamHandler->TryStop(aStreamId);
    if (flushId == MsgFlush::kIdInvalid) {
        return MsgFlush::kIdInvalid;
    }
    iExpectedFlushId = flushId;
    return iExpectedFlushId;
}

void ContainerController::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    auto streamHandler = iStreamHandler.load();
    ASSERT(streamHandler != nullptr);
    streamHandler->NotifyStarving(aMode, aStreamId, aStarving);
}

TBool ContainerController::TrySeekTo(TUint aStreamId, TUint64 aBytePos)
{
    // Lock not required; will be called back from a ContainerBase while iLock is held in TrySeek.
    auto streamHandler = iStreamHandler.load();
    ASSERT(streamHandler != nullptr);
    const TUint flushId = streamHandler->TrySeek(aStreamId, aBytePos);
    if (flushId == MsgFlush::kIdInvalid) {
        return false;
    }
    iExpectedFlushId = flushId;
    iCache.SetFlushing(iExpectedFlushId);
    return true;
}

TBool ContainerController::TryGetUrl(IWriter& aWriter, TUint64 aOffset, TUint aBytes)
{
    return iUrlBlockWriter.TryGet(aWriter, iUrl, aOffset, aBytes);
}

void ContainerController::ContainerTryStop()
{
    AutoMutex a(iLock);
    auto streamHandler = iStreamHandler.load();
    ASSERT(streamHandler != nullptr);
    LOG(kMedia, "ContainerController::ContainerTryStop iStreamId: %u\n", iStreamId);
    const TUint flushId = streamHandler->TryStop(iStreamId);
    if (flushId != MsgFlush::kIdInvalid) {
        // Could try consume this flush ID, as no downstream elements should care about it.
        iExpectedFlushId = flushId;
        iCache.SetFlushing(iExpectedFlushId);
    }
}


// MsgAudioEncodedRecogniser

MsgAudioEncodedRecogniser::MsgAudioEncodedRecogniser()
    : iAudioEncoded(nullptr)
{
}

void MsgAudioEncodedRecogniser::Reset()
{
    if (iAudioEncoded != nullptr) {
        iAudioEncoded->RemoveRef();
        iAudioEncoded = nullptr;
    }
}

MsgAudioEncoded* MsgAudioEncodedRecogniser::AudioEncoded()
{
    ASSERT(iAudioEncoded != nullptr);
    MsgAudioEncoded* msg = iAudioEncoded;
    iAudioEncoded = nullptr;
    return msg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgDrain* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgEncodedStream* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgAudioEncoded* aMsg)
{
    ASSERT(iAudioEncoded == nullptr);
    iAudioEncoded = aMsg;
    return nullptr;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgFlush* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgDecodedStream* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgBitRate* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgAudioPcm* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgPlayable* aMsg)
{
    return aMsg;
}

Msg* MsgAudioEncodedRecogniser::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}


// MsgEncodedStreamRecogniser

MsgEncodedStreamRecogniser::MsgEncodedStreamRecogniser()
    : iRecognisedMsgEncodedStream(false)
{
}

void MsgEncodedStreamRecogniser::Reset()
{
    iRecognisedMsgEncodedStream = false;
}

const TBool MsgEncodedStreamRecogniser::RecognisedMsgEncodedStream()
{
    return iRecognisedMsgEncodedStream;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgMode* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgTrack* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgDrain* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgDelay* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgEncodedStream* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    iRecognisedMsgEncodedStream = true;
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgAudioEncoded* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgMetaText* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgHalt* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgFlush* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgWait* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgBitRate* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgAudioPcm* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgSilence* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}

Msg* MsgEncodedStreamRecogniser::ProcessMsg(MsgQuit* aMsg)
{
    ASSERT(iRecognisedMsgEncodedStream == false);
    return aMsg;
}
