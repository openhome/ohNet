#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/Media/Codec/Mpeg4.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

// Container

Container::Container(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iCheckForContainer(false)
    , iContainerSize(0)
    , iRemainingContainerSize(0)
    , iExpectedFlushId(MsgFlush::kIdInvalid)
    , iStreamHandler(NULL)
    , iAudioEncoded(NULL)
{
}

Container::~Container()
{
}

Msg* Container::Pull()
{
    Msg* msg;
    do {
        msg = iUpstreamElement.Pull();
        msg = msg->Process(*this);
    } while (msg == NULL);
    return msg;
}

void Container::Read(Bwx& aBuf, TUint aOffset, TUint aBytes)
{
    if (iAudioEncoded->Bytes() > sizeof(iReadBuf)) {    // handling of chained msgs
        MsgAudioEncoded* tmp = iAudioEncoded->Split(sizeof(iReadBuf));
        iAudioEncoded->CopyTo(iReadBuf);
        iAudioEncoded->Add(tmp); // reconstitute msg
    }
    else {
        iAudioEncoded->CopyTo(iReadBuf);
    }
    Brn buf(&iReadBuf[aOffset], aBytes);
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

Msg* Container::ProcessMsg(MsgAudioEncoded* aMsg)
{
    if (iExpectedFlushId != MsgFlush::kIdInvalid) {
        // throw away buffered data
        aMsg->RemoveRef();
        return NULL;
    }

    if (iAudioEncoded != NULL) {    // pulling more data in as iAudioEncoded->Bytes()<EncodedAudio::kMaxBytes
        iAudioEncoded->Add(aMsg);
        return NULL;
    }

    // Process any remaining container bytes in next msg,
    // potentially allowing check below for subsequent containers.
    // Otherwise, if only did this at end of function, could pass data with a container down to codec.
    aMsg = StripContainer(aMsg);

    //iCheckForContainer = true;

    if (aMsg != NULL) { // don't do anything if we're still processing the previous container
        if (iCheckForContainer) {
            iAudioEncoded = aMsg;

            if (iAudioEncoded->Bytes() < EncodedAudio::kMaxBytes) { // ensure there are enough bytes for processing
                TUint audioBytes = iAudioEncoded->Bytes();
                Msg* msg = iUpstreamElement.Pull();
                msg = msg->Process(*this);
                if (iAudioEncoded->Bytes() == audioBytes) {
                    // pulled a msg other than audio
                    iAudioEncoded->RemoveRef();
                    iAudioEncoded = NULL;
                    return msg;
                }
                else {
                    aMsg = iAudioEncoded;
                }
            }

            try {
                //Attempt to construct an id3 tag -- this will throw if not present
                Id3v2 id3(*this);
                LOG(kMedia, "Container::ProcessMsg found id3 tag of %u bytes -- skipping\n", id3.ContainerSize());
                iContainerSize += iRemainingContainerSize = id3.ContainerSize();
                iCheckForContainer = false;
            }
            catch(MediaCodecId3v2NotFound) { //thrown from Id3v2 constructor
                LOG(kMedia, "Container::ProcessMsg MediaCodecId3v2NotFound\n");
            }
            if (iCheckForContainer) {
                try {
                    // Check for an MPEG4 header.
                    Mpeg4Start mp4(*this);
                    LOG(kMedia, "Container::ProcessMsg found MPEG4 header of %u bytes -- skipping\n", mp4.ContainerSize());
                    // only size of partial MPEG4 container, up to mdhd atom (codec-specific data is contained after this point)
                    iContainerSize += 0;
                    iRemainingContainerSize = mp4.ContainerSize();
                    iCheckForContainer = false;
                }
                catch (MediaMpeg4FileInvalid) { // thrown from Mpeg4 constructor
                    LOG(kMedia, "Container::ProcessMsg MediaMpeg4FileInvalid\n");
                }
            }
            iAudioEncoded = NULL;
            if (iRemainingContainerSize > 0) {  // could be another container after this
                iCheckForContainer = true;
            }
            else {
                iCheckForContainer = false;
            }
        }
        aMsg = StripContainer(aMsg);    // strip (some of) container data that may have been found
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
    iCheckForContainer = true;
    return aMsg;
}

Msg* Container::ProcessMsg(MsgEncodedStream* aMsg)
{
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
    if (iExpectedFlushId == aMsg->Id()) {
        iExpectedFlushId = MsgFlush::kIdInvalid;
        iCheckForContainer = true; // need to reset containersize here too?
    }
    return aMsg;
}

Msg* Container::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

EStreamPlay Container::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    return iStreamHandler->OkToPlay(aTrackId, aStreamId);
}

TUint Container::TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset)
{
    iExpectedFlushId = iStreamHandler->TrySeek(aTrackId, aStreamId, aOffset + iContainerSize);
    return iExpectedFlushId;
}

TUint Container::TryStop(TUint aTrackId, TUint aStreamId)
{
    return iStreamHandler->TryStop(aTrackId, aStreamId);
}
