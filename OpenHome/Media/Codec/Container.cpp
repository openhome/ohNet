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

ContainerBase::ContainerBase()
    : iMsgFactory(NULL)
    , iAudioEncoded(NULL)
    , iStreamHandler(NULL)
    , iExpectedFlushId(MsgFlush::kIdInvalid)
    , iPulling(false)
    , iUpstreamElement(NULL)
    , iPendingMsg(NULL)
{
}

ContainerBase::~ContainerBase()
{
    ReleaseAudioEncoded();
    if (iPendingMsg != NULL) {
        iPendingMsg->RemoveRef();
    }
}

Msg* ContainerBase::PullMsg()
{
    Msg* msg = iUpstreamElement->Pull();
    msg = msg->Process(*this);
    return msg;
}

void ContainerBase::AddToAudioEncoded(MsgAudioEncoded* aMsg)
{
    if (iAudioEncoded == NULL) {
        iAudioEncoded = aMsg;
    }
    else {
        iAudioEncoded->Add(aMsg);
    }
}

void ContainerBase::ReleaseAudioEncoded()
{
    if (iAudioEncoded != NULL) {
        iAudioEncoded->RemoveRef();
        iAudioEncoded = NULL;
    }
}

// should return type be TBool, based on whether all aBytes were read?
void ContainerBase::PullAudio(TUint aBytes)
{
    if (iPendingMsg != NULL) {
        return;
    }
    iPulling = true;
    while (iAudioEncoded == NULL || iAudioEncoded->Bytes() < aBytes) {
        Msg* msg = iUpstreamElement->Pull();
        msg = msg->Process(*this);
        if (msg != NULL) {
            ASSERT(iPendingMsg == NULL);
            iPendingMsg = msg;
            break;
        }
    }
    iPulling = false;
}

void ContainerBase::DiscardAudio(TUint aBytes)
{
    if (iPendingMsg != NULL) {
        return;
    }
    iPulling = true;
    TUint bytesRemaining = aBytes;

    while (bytesRemaining > 0) {

        // Work with current buffered data, only then pull more data.
        if (iAudioEncoded != NULL) {
            if (iAudioEncoded->Bytes() <= bytesRemaining) {
                bytesRemaining -= iAudioEncoded->Bytes();
                iAudioEncoded->RemoveRef();
                iAudioEncoded = NULL;
            }
            else {
                MsgAudioEncoded* remainder = iAudioEncoded->Split(bytesRemaining);
                bytesRemaining = 0;
                iAudioEncoded->RemoveRef();
                iAudioEncoded = remainder;
            }
        }

        // Exhausted any buffered data; now pull more if required.
        if (bytesRemaining > 0) {
            Msg* msg = iUpstreamElement->Pull();
            msg = msg->Process(*this);
            if (msg != NULL) {
                ASSERT(iPendingMsg == NULL);
                iPendingMsg = msg;
                break;
            }
        }
    }

    iPulling = false;
}

void ContainerBase::Read(Bwx& aBuf, TUint aBytes)
{
    if (iPendingMsg != NULL) {
        if (ReadFromCachedAudio(aBuf, aBytes)) {
            return;
        }
        return;
    }
    PullAudio(aBytes);
    ReadFromCachedAudio(aBuf, aBytes);
    ASSERT(aBuf.Bytes() == aBytes);
}

//void ContainerBase::Read(Bwx& aBuf, TUint aBytes, TUint aOffset)
//{
//    if (iPendingMsg != NULL) {
//        if (ReadFromCachedAudio(aBuf, aBytes, aOffset)) {
//            return;
//        }
//        return;
//    }
//    TUint toPull = aBytes;
//    if (iAudioEncoded == NULL) {
//        toPull += aOffset;
//    }
//    else if (iAudioEncoded->Bytes() < aOffset) {
//        toPull += aOffset-iAudioEncoded->Bytes();
//    }
//    //const TUint audioEncodedBytesBeforePull = iAudioEncoded->Bytes();
//    //audioEncodedBytesBeforePull;
//    PullAudio(toPull);
//    PullAudio(aOffset+aBytes);  // PullAudio pulls until we have aBytes in iAudioEncoded.
//                                // It does NOT pull aBytes -in addition to- what iAudioEncoded already contains.
//    ASSERT(iAudioEncoded->Bytes() >= aOffset+aBytes);
//    //const TUint audioEncodedBytesAfterPull = iAudioEncoded->Bytes();
//    //audioEncodedBytesAfterPull;
//    ReadFromCachedAudio(aBuf, aBytes, aOffset);
//    ASSERT(aBuf.Bytes() == aBytes);
//}

/*
  try read (up to) aBytes from data currently held in iAudioEncoded
*/
TBool ContainerBase::ReadFromCachedAudio(Bwx& aBuf, TUint aBytes)
{
    if (aBytes == 0) {
        return true;
    }
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
    if (remaining != NULL) {
        iAudioEncoded->Add(remaining);
    }
    ASSERT(aBuf.Bytes() == aBytes);
    return true;
}

//TBool ContainerBase::ReadFromCachedAudio(Bwx& aBuf, TUint aBytes, TUint aOffset)
//{
//    if (aBytes == 0) {
//        return true;
//    }
//    if (iAudioEncoded == NULL) {
//        return false;
//    }
//    if (aOffset >= iAudioEncoded->Bytes()) {
//        return false;
//    }
//    //const TUint audioEncodedBytes = iAudioEncoded->Bytes();
//    //audioEncodedBytes;
//    MsgAudioEncoded* desired = NULL;
//    MsgAudioEncoded* remaining = NULL;
//    if (aOffset > 0) {
//        desired = iAudioEncoded->Split(aOffset);
//    }
//    else {
//        desired = iAudioEncoded;
//        iAudioEncoded = NULL;
//    }
//
//    if (desired->Bytes() > aBytes) {
//        remaining = desired->Split(aBytes);
//    }
//    const TUint bytes = desired->Bytes();
//    ASSERT(aBuf.Bytes() + bytes <= aBuf.MaxBytes());
//    TByte* ptr = const_cast<TByte*>(aBuf.Ptr()) + aBuf.Bytes();
//    desired->CopyTo(ptr);
//    aBuf.SetBytes(aBuf.Bytes() + bytes);
//    if (iAudioEncoded == NULL) {
//        iAudioEncoded = desired;
//    }
//    else {
//        iAudioEncoded->Add(desired);
//    }
//    if (remaining != NULL) {
//        iAudioEncoded->Add(remaining);
//    }
//    ASSERT(aBuf.Bytes() == aBytes);
//    return true;
//}

void ContainerBase::Construct(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IStreamHandler& aStreamHandler)
{
    iMsgFactory = &aMsgFactory;
    iUpstreamElement = &aUpstreamElement;
    iStreamHandler = &aStreamHandler;
}

//TBool ContainerBase::Recognise(Brx& /*aBuf*/)
//{
//    return false; // should help detect if there's a problem
//}

Msg* ContainerBase::Pull()
{
    Msg* msg = NULL;
    // if there is a pending Msg (Track, Stream, Quit), forcibly pass any
    // iAudioEncoded down the pipeline (if a plugin requires further processing
    // before the remaining iAudioEncoded can be handed off, it should override
    // this Pull method)
    while (msg == NULL) {
        if (iPendingMsg != NULL && iAudioEncoded != NULL) {
            msg = iAudioEncoded;
            iAudioEncoded = NULL;
        }
        else if (iPendingMsg != NULL) {
            msg = iPendingMsg;
            iPendingMsg = NULL;
        }
        if (msg == NULL) { // don't have any buffered/pending Msgs
            msg = PullMsg();
        }
    }
    return msg;
}

EStreamPlay ContainerBase::OkToPlay(TUint aStreamId)
{
    LOG(kMedia, "ContainerBase::OkToPlay\n");
    ASSERT(iStreamHandler != NULL);
    EStreamPlay canPlay = iStreamHandler->OkToPlay(aStreamId);
    //Log::Print("ContainerBase::OkToPlay(%u) returned %s\n", aStreamId, kStreamPlayNames[canPlay]);
    return canPlay;
}

TUint ContainerBase::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    LOG(kMedia, "ContainerBase::TrySeek\n");
    // seek to absolute offset in stream by default; containers subclassing this can override
    iExpectedFlushId = iStreamHandler->TrySeek(aStreamId, aOffset);
    return iExpectedFlushId;
}

TUint ContainerBase::TryStop(TUint aStreamId)
{
    LOG(kMedia, "ContainerBase::TryStop\n");
    iExpectedFlushId = iStreamHandler->TryStop(aStreamId);
    return iExpectedFlushId;
}

void ContainerBase::NotifyStarving(const Brx& aMode, TUint aStreamId)
{
    if (iStreamHandler != NULL) {
        iStreamHandler->NotifyStarving(aMode, aStreamId);
    }
}

Msg* ContainerBase::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* ContainerBase::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* ContainerBase::ProcessMsg(MsgTrack* aMsg)
{
    iPendingMsg = aMsg;
    return NULL;
}

Msg* ContainerBase::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* ContainerBase::ProcessMsg(MsgEncodedStream* aMsg)
{
    iPendingMsg = aMsg;
    return NULL;
}

Msg* ContainerBase::ProcessMsg(MsgAudioEncoded* aMsg)
{
    return aMsg;
}

Msg* ContainerBase::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* ContainerBase::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* ContainerBase::ProcessMsg(MsgFlush* aMsg)
{
    ReleaseAudioEncoded();
    if (iExpectedFlushId == aMsg->Id()) {
        iExpectedFlushId = MsgFlush::kIdInvalid;
    }
    return aMsg;
}

Msg* ContainerBase::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* ContainerBase::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // expect this Msg to be generated by a downstream decoder element
    return NULL;
}

Msg* ContainerBase::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* ContainerBase::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* ContainerBase::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* ContainerBase::ProcessMsg(MsgQuit* aMsg)
{
    iPendingMsg = aMsg;
    return NULL;
}


// ContainerNull

ContainerNull::ContainerNull()
    : ContainerBase()
{
}

TBool ContainerNull::Recognise(Brx& /*aBuf*/)
{
    return true;
}


// ContainerFront

ContainerFront::ContainerFront(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iActiveContainer(NULL)
    , iStreamHandler(NULL)
    , iAudioEncoded(NULL)
    , iRecognising(false)
    , iExpectedFlushId(MsgFlush::kIdInvalid)
    , iQuit(false)
{
    iContainerNull = new ContainerNull();
    AddContainer(iContainerNull);
    iActiveContainer = iContainerNull;
}

void ContainerFront::AddContainer(ContainerBase* aContainer)
{
    aContainer->Construct(iMsgFactory, *this, *this);

    IContainerBase* container = aContainer;
    if (iContainers.size() >= 1) {
        // if we have >= 1 container, must have NULL container at end;
        // pop NULL container and re-attach at end
        container = iContainers.back();
        iContainers.pop_back();
        iContainers.push_back(aContainer);
    }
    iContainers.push_back(container);
}

ContainerFront::~ContainerFront()
{
    for (size_t i=0; i<iContainers.size(); i++) {
        delete iContainers[i];
    }
    if (iAudioEncoded != NULL) {
        iAudioEncoded->RemoveRef();
    }
}

Msg* ContainerFront::Pull()
{
    // this is needed to handle a pull coming into the container, and being
    // called on the inner_container, which then calls back into the container
    // i.e., upstream_element <- [container] <- downstream_element
    // where container encapsulates:
    // <- [container <- inner_container <- container] <-
    // but this would require container's Pull() function to have two modes
    // of behaviour, so use this pseudo-element at the front.
    Msg* msg = NULL;
    if (iAudioEncoded && !iRecognising)
    {
        msg = iAudioEncoded;
        iAudioEncoded = NULL;
    }
    while (msg == NULL) {
        msg = iUpstreamElement.Pull();
        msg = msg->Process(*this);
    }
    return msg;
}

Msg* ContainerFront::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* ContainerFront::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* ContainerFront::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* ContainerFront::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* ContainerFront::ProcessMsg(MsgEncodedStream* aMsg)
{
    iRecognising = true;
    iQuit = false;
    iStreamHandler = aMsg->StreamHandler();
    // This doesn't need to add itself as an IStreamHandler.
    // - Inner containers are constructed with this passed as an IStreamHandler
    // and outer Container makes calls directly to active innner container
    // (which calls its IStreamHandler, i.e., this).
    return aMsg;
}

Msg* ContainerFront::ProcessMsg(MsgAudioEncoded* aMsg)
{
    // throw away msg if awaiting a MsgFlush
    if (iExpectedFlushId != MsgFlush::kIdInvalid) {
        aMsg->RemoveRef();
        return NULL;
    }

    // read enough audio for recognise buffer
    // then iterate over containers, calling Recognise
    // once recognised (at least the NULL container, which should be last, MUST recognise ALL streams)
    // pass the audio into the container by calling Pull on it
    // then hand future control over to the container
    Msg* msg = aMsg;
    if (iRecognising && (iAudioEncoded == NULL || iAudioEncoded->Bytes() < kMaxRecogniseBytes)) {
        // still to recognise stream and not enough MsgAudioEncoded data to perform recognition
        if (iAudioEncoded == NULL) {
            iAudioEncoded = aMsg;
        }
        else {
            iAudioEncoded->Add(aMsg);
        }
        msg = NULL;
    }
    // perform recognition with just 1 MsgAudioEncoded, in case of very short
    // stream which would otherwise not be recognised (and cause subsequent
    // MsgQuit to be pulled through, which would require extra state)
    if (iRecognising && (iAudioEncoded != NULL)) {
        // we can only CopyTo a max of kMaxRecogniseBytes bytes. If we have more data than that,
        // split the msg, select a container then add the fragments back together before processing
        MsgAudioEncoded* remaining = NULL;
        if (iAudioEncoded->Bytes() > kMaxRecogniseBytes) {
            remaining = iAudioEncoded->Split(kMaxRecogniseBytes);
        }
        iAudioEncoded->CopyTo(iReadBuf);
        iAudioEncoded->Add(remaining); // reconstitute audio msg
        Brn recogBuf(iReadBuf, kMaxRecogniseBytes);

        // iterate over containers, calling recognise
        for (size_t i=0; i<iContainers.size(); i++) {
            IContainerBase* container = iContainers[i];
            TBool recognised = container->Recognise(recogBuf);
            if (recognised) {
                iActiveContainer = container;
                iRecognising = false;
                break;
            }
        }
        ASSERT(!iRecognising); // all streams should be recognised by ContainerNull if nothing else
        msg = iActiveContainer->Pull(); // get audio into iActiveContainer
    }
    return msg;
}

Msg* ContainerFront::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* ContainerFront::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* ContainerFront::ProcessMsg(MsgFlush* aMsg)
{
    if (iAudioEncoded) {
        iAudioEncoded->RemoveRef();
        iAudioEncoded = NULL;
    }
    if (iExpectedFlushId == aMsg->Id()) {
        iExpectedFlushId = MsgFlush::kIdInvalid;
    }
    return aMsg;
}

Msg* ContainerFront::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* ContainerFront::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // expect this Msg to be generated by a downstream decoder element
    return NULL;
}

Msg* ContainerFront::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* ContainerFront::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* ContainerFront::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* ContainerFront::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    return aMsg;
}

EStreamPlay ContainerFront::OkToPlay(TUint aStreamId)
{
    LOG(kMedia, "ContainerFront::OkToPlay\n");
    if (iQuit) {
        return ePlayNo;
    }
    ASSERT(iStreamHandler != NULL);
    EStreamPlay canPlay = iStreamHandler->OkToPlay(aStreamId);
    //Log::Print("ContainerFront::OkToPlay(%u) returned %s\n", aStreamId, kStreamPlayNames[canPlay]);
    return canPlay;
}

TUint ContainerFront::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    LOG(kMedia, "ContainerFront::TrySeek\n");
    if (!iQuit) {
        iExpectedFlushId = iStreamHandler->TrySeek(aStreamId, aOffset);
        return iExpectedFlushId;
    }
    else {
        return MsgFlush::kIdInvalid;
    }
}

TUint ContainerFront::TryStop(TUint aStreamId)
{
    LOG(kMedia, "ContainerFront::TryStop\n");
    if (iStreamHandler != NULL) {
        iExpectedFlushId = iStreamHandler->TryStop(aStreamId);
        return iExpectedFlushId;
    }
    return MsgFlush::kIdInvalid;
}

void ContainerFront::NotifyStarving(const Brx& aMode, TUint aStreamId)
{
    if (iStreamHandler != NULL) {
        iStreamHandler->NotifyStarving(aMode, aStreamId);
    }
}


// Container

Container::Container(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement)
    : iMsgFactory(aMsgFactory)
    , iNewStream(false)
{
    iContainerFront = new ContainerFront(aMsgFactory, aUpstreamElement);
}

Container::~Container()
{
    delete iContainerFront;
}

void Container::AddContainer(ContainerBase* aContainer)
{
    iContainerFront->AddContainer(aContainer);
}

Msg* Container::Pull()
{
    // can't break the call stack, so after a new MsgEncodedStream comes in and
    // we're put into iRecognising mode, can't just pull through next inner
    // container, otherwise we'd pass on some audio, and any downstream element
    // may start trying to decode it.
    // should pull on iContainerFront here, allowing next inner container to be
    // recognised and slotted in place and only THEN may control be handed over.
    if (iNewStream && iContainerFront->iRecognising) {
        iNewStream = false;
        return iContainerFront->Pull();
    }
    else {
        ASSERT(iContainerFront->iActiveContainer != NULL); // should have at least ContainerNull
        Msg* msg = iContainerFront->iActiveContainer->Pull();
        msg = msg->Process(*this);
        return msg;
    }
}

Msg* Container::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* Container::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* Container::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* Container::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* Container::ProcessMsg(MsgEncodedStream* aMsg)
{
    iNewStream = true;
    // Discarding aMsg->StreamHandler() here - ContainerFront has taken a ptr
    // to it.
    // When any IStreamHandler methods come in via this class, they are passed
    // directly to active inner container (which, in turn, calls the
    // IStreamHandler it was constructed with which happens to be
    // ContainerFront. ContainerFront then calls the ptr it took to
    // aMsg->StreamHandler()).
    MsgEncodedStream* msg = NULL;
    if (aMsg->RawPcm()) {
        msg = iMsgFactory.CreateMsgEncodedStream(aMsg->Uri(), aMsg->MetaText(), aMsg->TotalBytes(), aMsg->StreamId(), aMsg->Seekable(), aMsg->Live(), this, aMsg->PcmStream());
    }
    else {
        msg = iMsgFactory.CreateMsgEncodedStream(aMsg->Uri(), aMsg->MetaText(), aMsg->TotalBytes(), aMsg->StreamId(), aMsg->Seekable(), aMsg->Live(), this);
    }
    aMsg->RemoveRef();
    return msg;
}

Msg* Container::ProcessMsg(MsgAudioEncoded* aMsg)
{
    return aMsg;
}

Msg* Container::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* Container::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* Container::ProcessMsg(MsgFlush* aMsg)
{
    return aMsg;
}

Msg* Container::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* Container::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // expect this Msg to be generated by a downstream decoder element
    return NULL;
}

Msg* Container::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* Container::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* Container::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* Container::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

EStreamPlay Container::OkToPlay(TUint aStreamId)
{
    LOG(kMedia, "Container::OkToPlay\n");
    ASSERT(iContainerFront != NULL);
    ASSERT(iContainerFront->iActiveContainer != NULL);
    EStreamPlay canPlay = iContainerFront->iActiveContainer->OkToPlay(aStreamId);
    //Log::Print("Container::OkToPlay(%u) returned %s\n", aStreamId, kStreamPlayNames[canPlay]);
    return canPlay;
}

TUint Container::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    LOG(kMedia, "Container::TrySeek\n");
    return iContainerFront->iActiveContainer->TrySeek(aStreamId, aOffset);
}

TUint Container::TryStop(TUint aStreamId)
{
    LOG(kMedia, "Container::TryStop\n");
    return iContainerFront->iActiveContainer->TryStop(aStreamId);
}

void Container::NotifyStarving(const Brx& aMode, TUint aStreamId)
{
    if (iContainerFront != NULL) {
        iContainerFront->NotifyStarving(aMode, aStreamId);
    }
}
