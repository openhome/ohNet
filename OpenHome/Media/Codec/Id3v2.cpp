// IDv3 container
// Based on description from http://id3.org/id3v2.3.0

#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Debug.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

Id3v2::Id3v2()
    : iSize(0)
    , iTotalSize(0)
{
}

TBool Id3v2::Recognise(Brx& aBuf)
{
    // get rid of any existing buffered audio to avoid mem leaks
    // should this have been released as default behaviour if any of the following are recvd (i.e., shouldn't need handled here)?:
    // MsgTrack
    // MsgEncodedStream
    // MsgFlush
    // MsgHalt
    // MsgQuit
    //ReleaseAudioEncoded();
    iSize = 0;

    if (aBuf.Bytes() < kRecogniseBytes) {
        return false; // not enough data to recognise
    }

    static const char* kContainerStart = "ID3";
    if (strncmp((const TChar*)(aBuf.Ptr()), kContainerStart, sizeof(kContainerStart)-1) != 0) {
        return false;
    }
    if (aBuf[3] > 4) { // We only support upto Id3v2.4
        return false;
    }
    const TBool hasFooter = ((aBuf[5] & 0x10) != 0); // FIXME - docs suggest this is an experimental field rather than footer indicator
    // remaining 4 bytes give the size of container data
    // bit 7 of each byte must be zero (to avoid being mistaken for the sync frame of mp3)
    // ...so each byte only holds 7 bits of sizing data
    for (TUint i=6; i<10; i++) {
        if ((aBuf[i] & 0x80) != 0) {
            return false;
        }
    }
    
    iSize = ((aBuf[6] << 21) | (aBuf[7] << 14) | (aBuf[8] << 7) | aBuf[9]);
    iSize += 10; // for header
    if(hasFooter) {
        iSize += 10; // for footer if present
    }
    LOG(kMedia, "Id3v2 header found: %d bytes\n", iSize);
    return true;
}

Msg* Id3v2::ProcessMsg(MsgEncodedStream* aMsg)
{
    Msg* msg = ContainerBase::ProcessMsg(aMsg);
    iTotalSize = 0;
    return msg;
}

Msg* Id3v2::ProcessMsg(MsgAudioEncoded* aMsg)
{
    MsgAudioEncoded* msg = NULL;
    AddToAudioEncoded(aMsg);

    if (!iPulling) {
        iBuf.SetBytes(0);
        Read(iBuf, kRecogniseBytes);
        if (iBuf.Bytes() == kRecogniseBytes) {
            TBool recognised = Recognise(iBuf);
            if (recognised) {
                // discard more MsgAudioEncoded if req'd; could be splitting a large tag (i.e., one containing album art)
                DiscardAudio(iSize-kRecogniseBytes); // kRecogniseBytes already read above
                // can't return remaining iAudioEncoded here; could have another tag following this one
                iTotalSize += iSize;
            }
            else {
                msg = iAudioEncoded;
                iAudioEncoded = NULL;
            }
        }
        else {
            // didn't read a full buffer, so must be at end of stream
            msg = iAudioEncoded;
            iAudioEncoded = NULL;
        }
    }

    return msg;
}

TUint Id3v2::TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset)
{
    TUint64 offset = aOffset + iTotalSize;
    iExpectedFlushId = iStreamHandler->TrySeek(aTrackId, aStreamId, offset);
    return iExpectedFlushId;
}
