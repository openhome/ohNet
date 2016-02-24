// IDv3 container
// Based on description from http://id3.org/id3v2.3.0

#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/Media/Codec/ContainerFactory.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Debug.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

ContainerBase* ContainerFactory::NewId3v2()
{ // static
    return new Id3v2();
}



Id3v2::Id3v2()
    : ContainerBase(Brn("ID3"))
{
}

Msg* Id3v2::Recognise()
{
    LOG(kMedia, "Id3v2::Recognise\n");

    if (!iRecognitionStarted) {
        iCache->Inspect(iBuf, iBuf.MaxBytes());
        iRecognitionStarted = true;
    }

    Msg* msg = iCache->Pull();
    if (msg != nullptr) {
        return msg;
    }

    if (RecogniseTag()) {
        iSize = 0;
        iRecognitionSuccess = true;
        return nullptr;
    }
    return nullptr;
}

TBool Id3v2::Recognised() const
{
    return iRecognitionSuccess;
}

void Id3v2::Reset()
{
    iRecognitionStarted = false;
    iRecognitionSuccess = false;
    iState = eNone;
    iSize = 0;
    iTotalSize = 0;
    iBuf.SetBytes(0);
}

Msg* Id3v2::Pull()
{
    /**
     * Keep attempting to recognise ID3 tags until fail to recognise tags.
     * (In case there are multiple tags in a file.)
     */
    Msg* msg = nullptr;
    while (msg == nullptr) {
        if (iState != eNone) {
            msg = iCache->Pull();
            if (msg != nullptr) {
                return msg;
            }
        }


        if (iState == eNone) {
            iBuf.SetBytes(0);
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eRecognising;
        }
        else if (iState == eRecognising) {
            if (RecogniseTag()) {
                iTotalSize += iSize;
                iCache->Discard(iSize-kRecogniseBytes);
                iSize = 0;
                iState = eNone;
            }
            else {
                // Recognised last in (possible) chain of ID3 tags.
                // Output recognition buffer as it is actually data destined for codec.
                msg = iMsgFactory->CreateMsgAudioEncoded(iBuf);
                iBuf.SetBytes(0);
                iState = ePulling;
                return msg;
            }
        }
        else {
            // Shouldn't encounter any other state.
            // ePulling should always return a msg during iCache->Pull() above.
            ASSERTS();
        }
    }

    return msg;
}

TBool Id3v2::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    const TUint64 offset = aOffset + iTotalSize;
    return iSeekHandler->TrySeekTo(aStreamId, offset);
}


TBool Id3v2::RecogniseTag()
{
    if (iBuf.Bytes() < kRecogniseBytes) {
        return false; // not enough data to recognise
    }

    static const Brn kContainerStart("ID3");
    if (Brn(iBuf.Ptr(), kContainerStart.Bytes()) != kContainerStart) {
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
