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
    : ContainerBase(Brn("ID3"))
{
}

TBool Id3v2::Recognise()
{
    LOG(kMedia, "Id3v2::Recognise\n");
    iCache->Inspect(iBuf, iBuf.MaxBytes());

    //Msg* msg = iCache->Pull();
    //while (msg != nullptr) {
    //    msg->RemoveRef();
    //    msg = iCache->Pull();
    //}

    Msg* msg = iCache->Pull();
    if (msg != nullptr) {
        msg->RemoveRef();
        return false;
    }

    if (RecogniseTag()) {
        iSize = 0;
        return true;
    }
    return false;
}

void Id3v2::Reset()
{
    iSize = 0;
    iTotalSize = 0;
    iBuf.SetBytes(0);
    iParsingComplete = false;
    iInspectPending = false;
}

Msg* Id3v2::Pull()
{
    /**
     * Keep attempting to recognise ID3 tags until fail to recognise tags.
     * (In case there are multiple tags in a file.)
     */
    Msg* msg = nullptr;
    while (msg == nullptr) {
        if (iSize > 0) {
            iCache->Discard(iSize-kRecogniseBytes);
            iSize = 0;
        }
        if (!iParsingComplete) {
            if (!iInspectPending) {
                iBuf.SetBytes(0);
                iCache->Inspect(iBuf, iBuf.MaxBytes());
            }
        }

        msg = iCache->Pull();
        if (msg == nullptr) {
            // Inspect buffer must have been filled.
            const TBool recognised = RecogniseTag();
            iInspectPending = false;
            if (recognised) {
                iTotalSize += iSize;
            }
            else {
                iParsingComplete = true;
            }

        }
    }
    return msg;
}

TBool Id3v2::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    TUint64 offset = aOffset + iTotalSize;
    return iSeekHandler->TrySeekTo(aStreamId, offset);
}


TBool Id3v2::RecogniseTag()
{
    if (iBuf.Bytes() < kRecogniseBytes) {
        return false; // not enough data to recognise
    }

    static const char* kContainerStart = "ID3";
    if (strncmp((const TChar*)(iBuf.Ptr()), kContainerStart, sizeof(kContainerStart)-1) != 0) {
        return false;
    }
    if (iBuf[3] > 4) { // We only support upto Id3v2.4
        return false;
    }
    // NOTE: docs suggest this is an experimental field rather than footer indicator.
    const TBool hasFooter = ((iBuf[5] & 0x10) != 0);
    // remaining 4 bytes give the size of container data
    // bit 7 of each byte must be zero (to avoid being mistaken for the sync frame of mp3)
    // ...so each byte only holds 7 bits of sizing data
    for (TUint i=6; i<10; i++) {
        if ((iBuf[i] & 0x80) != 0) {
            return false;
        }
    }

    iSize = ((iBuf[6] << 21) | (iBuf[7] << 14) | (iBuf[8] << 7) | iBuf[9]);
    iSize += 10; // for header
    if (hasFooter) {
        iSize += 10; // for footer if present
    }
    LOG(kMedia, "Id3v2 header found: %d bytes\n", iSize);
    return true;
}
