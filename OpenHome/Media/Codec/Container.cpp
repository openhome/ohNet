#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


// ContainerBase

ContainerBase::~ContainerBase()
{
}

ContainerBase::ContainerBase()
    : iContainer(NULL)
{
}

TUint ContainerBase::Process()
{
    return 0;
}

TUint ContainerBase::Split()
{
    return 0;
}

void ContainerBase::Construct(IContainer& aContainer)
{
    iContainer = &aContainer;
}


// Container

Container::Container(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iActiveContainer(NULL)
    , iPendingMsg(NULL)
    , iQuit(false)
    , iCheckForContainer(false)
    , iContainerSize(0)
    , iRemainingContainerSize(0)
    , iAppend(false)
    , iExpectedFlushId(MsgFlush::kIdInvalid)
    , iStreamHandler(NULL)
    , iAudioEncoded(NULL)
{
}

Container::~Container()
{
    for (size_t i=0; i<iContainers.size(); i++) {
        delete iContainers[i];
    }
}

void Container::AddContainer(ContainerBase* aContainer)
{
    aContainer->Construct(*this);
    iContainers.push_back(aContainer);
}

Msg* Container::Pull()
{
    Msg* msg;
    if (!iAudioEncoded && iPendingMsg) {
        // pulled a quit msg through on previous call
        Log::Print("pushing quit msg\n");
        return iPendingMsg;
    }
    do {
        msg = iUpstreamElement.Pull();
        msg = msg->Process(*this);
        if (!msg && iPendingMsg) {
            // pulled a quit msg
            msg = iPendingMsg;
            Log::Print("rcvd and pushing quit msg\n");
        }
        else {
            //Log::Print("sending msg\n");
        }
    } while (msg == NULL);
    return msg;
}

void Container::Read(Bwx& aBuf, TUint aOffset, TUint aBytes)
{
    TUint bytes = aBytes;
    if (iAudioEncoded->Bytes() > sizeof(iReadBuf)) {    // handling of chained msgs
        MsgAudioEncoded* tmp = iAudioEncoded->Split(sizeof(iReadBuf));
        iAudioEncoded->CopyTo(iReadBuf);
        iAudioEncoded->Add(tmp); // reconstitute msg
    }
    else {
        iAudioEncoded->CopyTo(iReadBuf);
        if (iAudioEncoded->Bytes() < aBytes) {
            bytes = iAudioEncoded->Bytes();
        }
    }
    Brn buf(&iReadBuf[aOffset], bytes);
    aBuf.Append(buf);
}

MsgAudioEncoded* Container::StripContainer(MsgAudioEncoded* aMsg)
{
    // strip data from (or dispose of whole) message if some of it belongs to a container
    if (iRemainingContainerSize > 0 && aMsg != NULL) {
        const TUint bytes = aMsg->Bytes();
        if (iRemainingContainerSize < bytes) {
            MsgAudioEncoded* tmp = aMsg->Split(iRemainingContainerSize);
            aMsg->RemoveRef();
            aMsg = tmp;
            iRemainingContainerSize = 0;
        }
        else {
            aMsg->RemoveRef();
            aMsg = NULL;
            iRemainingContainerSize -= bytes;
        }
    }

    return aMsg;
}

void Container::FillBuffer()
{
    //TUint audioBytes = iAudioEncoded->Bytes();
    while (!iPendingMsg && (iAudioEncoded->Bytes() < EncodedAudio::kMaxBytes)) { // ensure there are enough bytes for processing
        Msg* msg = iUpstreamElement.Pull();   // if we do this here, could be at the end of a stream and pull a flush
        msg = msg->Process(*this);
        if (!iAudioEncoded) {   // flush has been received
            return;
        }
    }
    //if (iAudioEncoded->Bytes() == audioBytes) {
    //    aMsg = iAudioEncoded;
    //}
}

void Container::ReleaseAudioEncoded()
{
    if (iAudioEncoded != NULL) {
        iAudioEncoded->RemoveRef();
        iAudioEncoded = NULL;
    }
}

Msg* Container::ProcessMsg(MsgAudioEncoded* aMsg)
{
    if (iExpectedFlushId != MsgFlush::kIdInvalid) {
        // throw away buffered data
        aMsg->RemoveRef();
        return NULL;
    }

    if (iAudioEncoded != NULL) {    // pulling more data as iAudioEncoded->Bytes()<EncodedAudio::kMaxBytes
        iAudioEncoded->Add(aMsg);
        return NULL;
    }

    if (aMsg != NULL) { // don't do anything if we're still processing the previous container

        iAudioEncoded = aMsg;
        //FillBuffer();
        //aMsg = iAudioEncoded;

        if (iCheckForContainer && iAudioEncoded) {

            // try identify a container
            for (size_t i=0; i<iContainers.size(); i++) {
                ContainerBase* container = iContainers[i];
                TBool recognised = container->Recognise();
                if (recognised) {
                    iActiveContainer = container;
                    break;
                }
            }

            // amount to strip off
            if (iActiveContainer) {
                iContainerSize += iRemainingContainerSize = iActiveContainer->Size();
                iAppend = iActiveContainer->AppendDuringSeek();
                LOG(kMedia, "Container iContainerSize: %u, iRemainingContainerSize: %u, iAppend: %u\n", iContainerSize, iRemainingContainerSize, iAppend);
            }

            iCheckForContainer = false;
        }
        if (iAudioEncoded) {    // is this if check req'd?
            aMsg = StripContainer(aMsg);    // strip (some of) container from this (or previous) iteration
            iAudioEncoded = aMsg;
        }
        if (iActiveContainer && (iRemainingContainerSize == 0)) {
            // parse first header, remove it, then split packet and pass just audio, storing remainder for processing next time round
            // continuous processing for containers such as Ogg, which are spread throughout stream
            TUint processBytes = 1;
            while (iRemainingContainerSize == 0 && processBytes > 0) {
                FillBuffer();
                aMsg = iAudioEncoded;
                if (iAudioEncoded) {    // could have been de-ref'd by a flush
                    processBytes = iActiveContainer->Process();
                    iRemainingContainerSize += processBytes;
                    aMsg = StripContainer(aMsg);    // strip further data
                    iAudioEncoded = aMsg;
                } else {
                    processBytes = 0;
                }
            }
        }
        iAudioEncoded = NULL;
    }

    return aMsg;
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

Msg* Container::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // expect this Msg to be generated by a downstream decoder element
    return NULL;
}

Msg* Container::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* Container::ProcessMsg(MsgEncodedStream* aMsg)
{
    iPendingMsg = NULL;
    iQuit = false;
    iCheckForContainer = true;
    iContainerSize = 0;
    iRemainingContainerSize = 0;
    iStreamHandler = aMsg->StreamHandler();
    MsgEncodedStream* msg = iMsgFactory.CreateMsgEncodedStream(aMsg->Uri(), aMsg->MetaText(), aMsg->TotalBytes(), aMsg->StreamId(), aMsg->Seekable(), aMsg->Live(), this);
    aMsg->RemoveRef();
    return msg;
}

Msg* Container::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* Container::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* Container::ProcessMsg(MsgFlush* aMsg)
{
    Log::Print("msg::flush\n");
    ReleaseAudioEncoded();
    if (iExpectedFlushId == aMsg->Id()) {
        iExpectedFlushId = MsgFlush::kIdInvalid;
    }
    return aMsg;
    //aMsg->RemoveRef();
    //return NULL;
}

Msg* Container::ProcessMsg(MsgQuit* aMsg)
{
    Log::Print("msg::quit\n");
    iQuit = true;
    iPendingMsg = aMsg;
    return NULL;
}

EStreamPlay Container::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    return iStreamHandler->OkToPlay(aTrackId, aStreamId);
}

TUint Container::TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset)
{
    TUint64 offset = aOffset;
    if (iAppend) {
        offset += iContainerSize;
    }
    iExpectedFlushId = iStreamHandler->TrySeek(aTrackId, aStreamId, offset);
    return iExpectedFlushId;
}

TUint Container::TryStop(TUint aTrackId, TUint aStreamId)
{
    Log::Print("iStreamHandler: %p\n", iStreamHandler);
    // is a quit msg being sent before this and causing destruction of the pipeline?
    if (!iQuit) {
        return iStreamHandler->TryStop(aTrackId, aStreamId);
    }
    else {
        return 0;
    }
}
