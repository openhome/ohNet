#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Codec/MpegTs.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Media/Debug.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

/*
 * http://en.wikipedia.org/wiki/MPEG_transport_stream
 * http://en.wikipedia.org/wiki/Program-specific_information#PMT_.28Program_map_specific_data.29
 * http://en.wikipedia.org/wiki/Packetized_elementary_stream
 *
 * MPEG TS is structured as follows:
 *
 *  - 188-byte MPEG-TS packets:              ====    ====    ====    ====    ====    ====
 *                                          /            \  /            \  /            \
 *  - Variable-length MPEG PES packets:     ==============  ==============  ==============
 *                                         /                                              \
 *  - Raw stream (e.g., AAC):              ================================================
 */


MpegTs::MpegTs()
    : iSize(0)
    , iTotalSize(0)
    , iPacketBytes(0)
    , iProgramMapPid(0)
    , iStreamPid(0)
{
}

TBool MpegTs::Recognise(Brx& aBuf)
{
    iSize = 0;

    if (aBuf.Bytes() < kRecogniseBytes) {
        return false; // not enough data to recognise
    }

    if (aBuf[0] != 0x47) {  // expect sync word - should seek if can't find it.
        return false;
    }

    TUint pid = (aBuf[1] & 0x1f) << 8 | aBuf[2];

    if ((aBuf[3] & 0x10) != 0x10) {   // ensure there is a payload.
        return false; // FIXME - should this really be a failure?
    }

    TBool adaptationField = false;
    TUint adaptationFieldBytes = 0;
    if ((aBuf[3] & 0x20) != 0x00) {// && iStreamPid != 0 && pid == iStreamPid) {
        adaptationField = true;
    }

    //TUint continuityCounter = aBuf[3] & 0xf;

    if (adaptationField) {
        TUint adaptationOffset = kMpegHeaderBytes;
        adaptationFieldBytes = aBuf[adaptationOffset];
        adaptationFieldBytes += 1;  // +1 because adaptation field length doesn't account for the adaptation field length byte!
        iSize += adaptationFieldBytes;
        //TBool startsSeq = ((aBuf[adaptationOffset+1] & 0x40) == 0x40);
    }

    // Not concerned with remainder of fields from header.

    TUint offset = kMpegHeaderBytes+adaptationFieldBytes; 
    iSize = kPacketBytes;
    if (pid == 0) {
        Brn table(aBuf.Ptr()+offset, aBuf.Bytes()-offset);
        if (!RecognisePat(table)) {
            return false;
        }
        //iSize = kRecogniseBytes;
    }

    if (iProgramMapPid != 0 && pid == iProgramMapPid) {
        Brn table(aBuf.Ptr()+offset, aBuf.Bytes()-offset);
        if (!RecognisePmt(table)) {
            return false;
        }
        //iSize = kRecogniseBytes;
    }

    if (iStreamPid != 0 && pid == iStreamPid) {
        TBool isPesPacketStart = false;
        TUint pesBytes = 0;
        if (offset < aBuf.Bytes() && aBuf.Bytes()-(offset+1) > kPesHeaderStartCodePrefixBytes) {
            if ((aBuf[offset] == 0x00) && (aBuf[offset+1] == 0x00) && (aBuf[offset+2] == 0x01)) {
                isPesPacketStart = true;
                pesBytes = kPesHeaderFixedBytes;
            }
        }

        if (isPesPacketStart) {
            //TUint streamId = aBuf[offset+3];
            //TUint pesPacketLength = Converter::BeUint16At(aBuf, offset+4);
            if ((aBuf[offset+6] & 0x80) == 0x80) { // Optional PES header found
                TUint pesOptionalHeaderLength = aBuf[offset+8];
                pesBytes += kPesHeaderOptionalFixedBytes + pesOptionalHeaderLength;
            }
        }

        iSize = kMpegHeaderBytes+adaptationFieldBytes+pesBytes;
    }

    return true;
}

Msg* MpegTs::ProcessMsg(MsgEncodedStream* aMsg)
{
    Msg* msg = ContainerBase::ProcessMsg(aMsg);
    iTotalSize = 0;
    iPacketBytes = 0;
    iProgramMapPid = 0;
    iStreamPid = 0;
    return msg;
}

Msg* MpegTs::ProcessMsg(MsgAudioEncoded* aMsg)
{
    // FIXME - does not currently attempt to find sync word.
    // Current use does not extend beyond file-based streams with a predictable sync-start.

    MsgAudioEncoded* unpacked = NULL;
    AddToAudioEncoded(aMsg);

    if (!iPulling) {
        TBool packetsRemaining = true;

        while (packetsRemaining) {
            TBool unpack = false;

            if (unpacked != NULL && iAudioEncoded->Bytes() < kPacketBytes) {
                // Don't pull through more encoded audio if not required.
                return unpacked;
            }

            //if (iPacketBytes != 0 && iPacketBytes+iAudioEncoded->Bytes() > kPacketBytes+kRecogniseBytes) {
            if (iPacketBytes != 0 && iPacketBytes+iAudioEncoded->Bytes() > kPacketBytes) {
                // Packet boundary within this message.
                // Must have iAudioEncoded point at start of next msg.
                unpack = true;
            }
            else if (iPacketBytes != 0 && iPacketBytes+iAudioEncoded->Bytes() == kPacketBytes) {
                // Consuming remainder of packet.
                // Next time round will be start of new packet.
                iPacketBytes = 0;
                // FIXME - move this if-else block to a helper function
                if (unpacked == NULL) {
                    unpacked = iAudioEncoded;
                }
                else {
                    unpacked->Add(iAudioEncoded);
                }
                iAudioEncoded = NULL;
            }
            else if (iPacketBytes == 0) {
                // At start of next packet.
                unpack = true;
            }
            else {
                // Remaining audio belongs to current packet (but does not complete current packet)
                iPacketBytes += iAudioEncoded->Bytes();
                if (unpacked == NULL) {
                    unpacked = iAudioEncoded;
                }
                else {
                    unpacked->Add(iAudioEncoded);
                }
                iAudioEncoded = NULL;
            }

            if (unpack) {
                iBuf.SetBytes(0);
                Read(iBuf, kRecogniseBytes);

                if (iBuf.Bytes() == kRecogniseBytes) {
                    TBool recognised = Recognise(iBuf);
                    if (recognised) {
                        DiscardAudio(iSize);
                        iTotalSize += iSize;
                        iPacketBytes += iSize;

                        //const TUint payloadBytes = kPacketBytes-kRecogniseBytes;
                        const TUint payloadBytes = kPacketBytes - iSize;
                        MsgAudioEncoded* payload = NULL;
                        if (payloadBytes == 0) {
                            iPacketBytes = 0;
                        }
                        else if (iAudioEncoded->Bytes() > payloadBytes) {
                            MsgAudioEncoded* remainder = iAudioEncoded->Split(payloadBytes);
                            payload = iAudioEncoded;
                            iAudioEncoded = remainder;
                            iPacketBytes = 0;
                        }
                        else {
                            iPacketBytes += iAudioEncoded->Bytes();
                            if (iPacketBytes == kPacketBytes) {
                                // iAudioEncoded->Bytes() == payloadBytes
                                iPacketBytes = 0;
                            }
                            payload = iAudioEncoded;
                            iAudioEncoded = NULL;
                            packetsRemaining = false;
                        }

                        if (unpacked == NULL) {
                            unpacked = payload;
                        }
                        else {
                            unpacked->Add(payload);
                        }
                    }
                    else {
                        // Couldn't Recognise() one of the MPEG-TS 188-byte packets.
                        THROW(CodecStreamCorrupt);
                    }
                }
                else {
                    // Didn't read a full buffer, so must be at end of stream.
                    //
                    // Unable to Recognise()/parse the container, so discard
                    // this chunk as no codec will handle it correctly.
                    iAudioEncoded->RemoveRef();
                    iAudioEncoded = NULL;
                    packetsRemaining = false;
                }
            }
            else {
                packetsRemaining = false;
            }

        }
        return unpacked;

    }

    return unpacked;
}

TUint MpegTs::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    // Seeking currently unsupported.
    return MsgFlush::kIdInvalid;
    //TUint64 offset = aOffset + iTotalSize;
    //iExpectedFlushId = iStreamHandler->TrySeek(aStreamId, offset);
    //return iExpectedFlushId;
}

TBool MpegTs::RecogniseTableHeader(const Brx& aTableHeader)
{
    if (aTableHeader.Bytes() < kTableHeaderBytes) {
        return false;
    }

    // Parse table header.
    TUint offset = aTableHeader[0];
    iTableType = aTableHeader[offset+1];

    // Section syntax indicator.
    if ((aTableHeader[offset+2] & 0x80) != 0x80) {
        return false;
    }
    // Private bit.
    if ((aTableHeader[offset+2] & 0x40) != 0x00) {
        return false;
    }
    // Reserved bits.
    if ((aTableHeader[offset+2] & 0x30) != 0x30) {
        return false;
    }
    // Section length unused bits.
    if ((aTableHeader[offset+2] & 0x0c) != 0x00) {
        return false;
    }
    // Section length.
    iSectionLength = (aTableHeader[offset+2] & 0x03) << 8 | (aTableHeader[offset+3]);
    if (iSectionLength > 1021) {
        return false;
    }
    return true;
}

TBool MpegTs::RecogniseTableSyntax(const Brx& aTableSyntax)
{
    if (aTableSyntax.Bytes() < kTableSyntaxFixedBytes) {
        return false;
    }

    // Parse table syntax section.
    //TUint tableIdExt = Converter::BeUint16At(aTableSyntax, 0);
    if ((aTableSyntax[2] & 0xc0) != 0xc0) {
        return false;
    }
    //TUint versionNumber = aTableSyntax[2] & 0x3e;
    //TUint currentIndicator = aTableSyntax[2] & 0x01;
    //TUint sectionNumber = aTableSyntax[3];    // starts from 0.
    //TUint sectionNumberLast = aTableSyntax[4];

    return true;
}

TBool MpegTs::RecogniseTableHeaderAndSyntax(const Brx& aTable, TUint aTableType)
{
    if (aTable.Bytes() < kTableHeaderBytes+kTableSyntaxFixedBytes) {
        return false;
    }
    Brn tableHeader(aTable.Ptr(), kTableHeaderBytes);
    TBool success = RecogniseTableHeader(tableHeader);
    if (!success) {
        return false;
    }

    if (iTableType != aTableType) {
        return false;
    }

    Brn tableSyntax(aTable.Ptr()+kTableHeaderBytes, kTableSyntaxFixedBytes);
    success = RecogniseTableSyntax(tableSyntax);
    if (!success) {
        return false;
    }

    return true;
}

TBool MpegTs::RecognisePat(const Brx& aPat)
{
    // Program Association Table (PAT)
    if (!RecogniseTableHeaderAndSyntax(aPat, kTableTypePat)) {
        return false;
    }
    TUint offset = kTableHeaderBytes+kTableSyntaxFixedBytes;

    // PAT-specific data.
    //TUint programNum = Converter::BeUint16At(aBuf, offset);
    if ((aPat[offset+2] & 0xe0) != 0xe0) {  // reserved bits
        return false;
    }
    TUint programMapPid = (aPat[offset+2] & 0x1f) << 8 | aPat[offset+3];

    // Ignore checksum.

    iProgramMapPid = programMapPid;

    return true;
}

TBool MpegTs::RecognisePmt(const Brx& aPmt)
{
    // Found Program Map Table (PMT)
    if (!RecogniseTableHeaderAndSyntax(aPmt, kTableTypePmt)) {
        return false;
    }
    TUint offset = kTableHeaderBytes+kTableSyntaxFixedBytes;


    // PMT-specific data.
    if ((aPmt[offset] & 0xe0) != 0xe0) {   // reserved bits
        return false;
    }
    //TUint progClockRef = (aPmt[offset] & 0x1f) << 8 | aPmt[offset+1];
    if ((aPmt[offset+2] & 0xf0) != 0xf0) {    // reserved bits
        return false;
    }
    if ((aPmt[offset+2] & 0x0c) != 0x00) {    // prog info length unused bits
        return false;
    }
    //TUint progInfoLength = (aPmt[offset+2] & 0x03) << 8 | aPmt[offset+3];


    // Get elementary-stream specific data.
    offset += kPmtSpecificFixedBytes;
    if (iSectionLength-offset < kStreamSpecificFixedBytes) {
        return false;
    }
    TUint streamType = aPmt[offset];
    if ((aPmt[offset+1] & 0xe0) != 0xe0) {    // reserved bits
        return false;
    }
    TUint elementPid = (aPmt[offset+1] & 0x1f) << 8 | aPmt[offset+2];
    if ((aPmt[offset+3] & 0xf0) != 0xf0) {    // reserved bits
        return false;
    }
    if ((aPmt[offset+3] & 0x0c) != 0x00) {    // ES info length unused bits
        return false;
    }
    // esInfoLength is no. of stream descriptor bytes.
    //TUint esInfoLength = (aPmt[offset+3] & 0x03) << 8 | aPmt[offset+4];

    // Table finishes with 32-bit CRC.

    if (streamType == kStreamTypeAdtsAac) {
        iStreamPid = elementPid;
    }

    return true;
}
