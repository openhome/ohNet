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
    , iId(aId)
{
}

const Brx& ContainerBase::Id() const
{
    return iId;
}

void ContainerBase::Construct(IMsgAudioEncodedCache& aCache, MsgFactory& aMsgFactory, IContainerSeekHandler& aSeekHandler, IContainerUrlBlockWriter& aUrlBlockWriter)
{
    iCache = &aCache;
    iMsgFactory = &aMsgFactory;
    iSeekHandler = &aSeekHandler;
    iUrlBlockWriter = &aUrlBlockWriter;
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

void MsgAudioEncodedCache::Reset()
{
    if (iAudioEncoded != nullptr) {
        iAudioEncoded->RemoveRef();
        iAudioEncoded = nullptr;
    }
    iDiscardBytesRemaining = 0;
    iInspectBytesRemaining = 0;
    iAccumulateBytesRemaining = 0;
    if (iBuffer != nullptr) {
        iBuffer->SetBytes(0);
        iBuffer = nullptr;
    }
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

TBool ContainerNull::Recognise()
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
    , iCache(iRewinder)
    , iActiveContainer(nullptr)
    , iContainerNull(nullptr)
    , iStreamHandler(nullptr)
    , iPassThrough(false)
    , iRecognising(false)
    , iExpectedFlushId(MsgFlush::kIdInvalid)
    , iQuit(false)
    , iLock("COCO")
{
    iContainerNull = new ContainerNull();
    iContainerNull->Construct(iCache, iMsgFactory, *this, *this);
    iContainers.push_back(iContainerNull);
    iActiveContainer = iContainerNull;
}

void ContainerController::AddContainer(ContainerBase* aContainer)
{
    aContainer->Construct(iCache, iMsgFactory, *this, *this);

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

void ContainerController::RecogniseContainer()
{
    if (iPassThrough) {
        // No recognition on streams that support latency.
        iActiveContainer = iContainerNull;
        iRewinder.Stop();
        iCache.Reset();
        iActiveContainer->Reset();
    }
    else {
        iActiveContainer = nullptr;
        for (auto& container : iContainers) {
            iRewinder.Rewind();
            iCache.Reset();
            container->Reset();
            try {
                if (container->Recognise()) {
                    iActiveContainer = container;
                    iRewinder.Rewind();
                    iRewinder.Stop();
                    iCache.Reset();
                    return;
                }
            }
            catch (CodecPulledNullMsg&) {
                LOG(kCodec, "ContainerController::RecogniseContainer Rewinder exhausted while attempting to recognise ");
                LOG(kCodec, container->Id());
                LOG(kCodec, "\n");
            }
        }
        ASSERT(iActiveContainer != nullptr);    // Should have been detected by at least ContainerNull.
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
        iRecognising = false;
    }

    if (recognising) { // Pulled MsgEncodedStream
        RecogniseContainer();
    }

    Msg* msg = nullptr;
    while (msg == nullptr) {
        msg = iActiveContainer->Pull();
        msg = msg->Process(*this);
    }

    return msg;
}

Msg* ContainerController::ProcessMsg(MsgMode* aMsg)
{
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
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgDrain* aMsg)
{
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgEncodedStream* aMsg)
{
    iRecognising = true;
    iUrl.Replace(aMsg->Uri());  // Required to allow containers to do an out-of-band read.

    if (iUrl.Bytes() == 0) {
        // Dummy stream; don't attempt recognition as there will be no audio and pipeline will be blocked.
        iPassThrough = true;
    }

    MsgEncodedStream* msg = nullptr;
    if (aMsg->RawPcm()) {
        msg = iMsgFactory.CreateMsgEncodedStream(aMsg->Uri(), aMsg->MetaText(), aMsg->TotalBytes(), aMsg->StreamId(), aMsg->Seekable(), aMsg->Live(), this, aMsg->PcmStream());
    }
    else {
        msg = iMsgFactory.CreateMsgEncodedStream(aMsg->Uri(), aMsg->MetaText(), aMsg->TotalBytes(), aMsg->StreamId(), aMsg->Seekable(), aMsg->Live(), this);
    }

    AutoMutex a(iLock);
    iExpectedFlushId = MsgFlush::kIdInvalid;
    iStreamHandler = aMsg->StreamHandler();
    iQuit = false;
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
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* ContainerController::ProcessMsg(MsgFlush* aMsg)
{
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
    AutoMutex a(iLock);
    iQuit = true;
    return aMsg;
}

EStreamPlay ContainerController::OkToPlay(TUint aStreamId)
{
    LOG(kMedia, "ContainerController::OkToPlay aStreamId: %u\n", aStreamId);
    AutoMutex a(iLock);
    if (iQuit) {
        return ePlayNo;
    }
    ASSERT(iStreamHandler != nullptr);
    EStreamPlay canPlay = iStreamHandler->OkToPlay(aStreamId);
    return canPlay;
}

TUint ContainerController::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    LOG(kMedia, "ContainerController::TrySeek aStreamId: %u, aOffset: %llu\n", aStreamId, aOffset);
    AutoMutex a(iLock);
    if (iQuit) {
        return MsgFlush::kIdInvalid;
    }

    ASSERT(iStreamHandler != nullptr);
    const TBool seek = iActiveContainer->TrySeek(aStreamId, aOffset);
    if (!seek) {
        return MsgFlush::kIdInvalid;
    }
    return iExpectedFlushId;
}

TUint ContainerController::TryStop(TUint aStreamId)
{
    LOG(kMedia, "ContainerController::TryStop aStreamId: %u\n", aStreamId);
    AutoMutex a(iLock);
    if (iQuit) {
        return MsgFlush::kIdInvalid;
    }

    ASSERT(iStreamHandler != nullptr);
    iExpectedFlushId = iStreamHandler->TryStop(aStreamId);
    return iExpectedFlushId;
}

void ContainerController::NotifyStarving(const Brx& aMode, TUint aStreamId)
{
    AutoMutex a(iLock);
    ASSERT(iStreamHandler != nullptr);
    iStreamHandler->NotifyStarving(aMode, aStreamId);
}

TBool ContainerController::TrySeekTo(TUint aStreamId, TUint64 aBytePos)
{
    // Lock not required; will be called back from a ContainerBase while iLock is held in TrySeek.
    if (iQuit) {
        iExpectedFlushId = MsgFlush::kIdInvalid;
        return false;
    }

    ASSERT(iStreamHandler != nullptr);
    iExpectedFlushId = iStreamHandler->TrySeek(aStreamId, aBytePos);
    if (iExpectedFlushId == MsgFlush::kIdInvalid) {
        return false;
    }
    iCache.SetFlushing(iExpectedFlushId);
    return true;
}

TBool ContainerController::TryGetUrl(IWriter& aWriter, TUint64 aOffset, TUint aBytes)
{
    return iUrlBlockWriter.TryGet(aWriter, iUrl, aOffset, aBytes);
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
