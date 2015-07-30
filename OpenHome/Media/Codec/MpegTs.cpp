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
    Clear();
    const TBool recognised = ProcessPacket(aBuf);

    // Clear internal state if recognised as will see this data passed again
    // when processing starts.
    if (recognised) {
        Clear();
    }
    return recognised;
}

Msg* MpegTs::ProcessMsg(MsgAudioEncoded* aMsg)
{
    // FIXME - does not currently attempt to find sync word.
    // Current use does not extend beyond file-based streams with a predictable sync-start.
    MsgAudioEncoded* unpacked = nullptr;
    AddToAudioEncoded(aMsg);

    if (!iPulling) {
        TBool packetsRemaining = true;

        while (packetsRemaining) {
            TBool unpack = false;

            if (unpacked != nullptr && (iAudioEncoded == nullptr || iAudioEncoded->Bytes() < kPacketBytes)) {
                // Don't pull through more encoded audio if not required.
                return unpacked;
            }

            if (iPacketBytes != 0 && iAudioEncoded != nullptr && iPacketBytes+iAudioEncoded->Bytes() > kPacketBytes) {
                // Packet boundary within this message.
                // Must have iAudioEncoded point at start of next msg.
                unpack = true;
            }
            else if (iPacketBytes != 0 && iAudioEncoded != nullptr && iPacketBytes+iAudioEncoded->Bytes() == kPacketBytes) {
                // Consuming remainder of packet.
                // Next time round will be start of new packet.
                iPacketBytes = 0;
                unpacked = AppendAudioEncoded(unpacked);
            }
            else if (iPacketBytes == 0) {
                // At start of next packet.
                unpack = true;
            }
            else {
                // Any remaining audio belongs to current packet (but does not complete current packet)
                if (iAudioEncoded != nullptr) {
                    iPacketBytes += iAudioEncoded->Bytes();
                    unpacked = AppendAudioEncoded(unpacked);
                }
            }

            if (unpack) {
                iBuf.SetBytes(0);
                Read(iBuf, kPacketBytes);   // FIXME - what if this reads fewer bytes than requested?

                if (iBuf.Bytes() == kPacketBytes) {
                    TBool recognised = ProcessPacket(iBuf);
                    if (recognised) {
                        DiscardAudio(iSize);
                        iTotalSize += iSize;
                        iPacketBytes += iSize;

                        ASSERT(iSize <= kPacketBytes);
                        const TUint payloadBytes = kPacketBytes - iSize;

                        if (payloadBytes == 0) {
                            iPacketBytes = 0;

                            if (iAudioEncoded == nullptr) {
                                packetsRemaining = false;
                            }
                        }
                        else if (iAudioEncoded->Bytes() > payloadBytes) {
                            MsgAudioEncoded* remainder = iAudioEncoded->Split(payloadBytes);
                            unpacked = AppendAudioEncoded(unpacked);
                            iAudioEncoded = remainder;
                            iPacketBytes = 0;
                        }
                        else {
                            iPacketBytes += iAudioEncoded->Bytes();
                            if (iPacketBytes == kPacketBytes) {
                                // iAudioEncoded->Bytes() == payloadBytes
                                iPacketBytes = 0;
                            }
                            unpacked = AppendAudioEncoded(unpacked);
                            packetsRemaining = false;
                        }
                    }
                    else {
                        // Couldn't process one of the MPEG-TS 188-byte packets.
                        THROW(CodecStreamCorrupt); // FIXME - don't throw this! It isn't caught anywhere! Instead, quietly discard remainder of stream (or resync on next frame).
                    }
                }
                else {
                    // Didn't read a full buffer, so must be at end of stream.
                    //
                    // Unable to process/parse the container, so discard
                    // this chunk as no codec will handle it correctly.
                    iAudioEncoded->RemoveRef();
                    iAudioEncoded = nullptr;
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

void MpegTs::Clear()
{
    iTotalSize = 0;
    iPacketBytes = 0;
    iProgramMapPid = 0;
    iStreamPid = 0;
}

MsgAudioEncoded* MpegTs::AppendAudioEncoded(MsgAudioEncoded* aMsg)
{
    ASSERT(iAudioEncoded != nullptr);
    if (aMsg == nullptr) {
        aMsg = iAudioEncoded;
    }
    else {
        aMsg->Add(iAudioEncoded);
    }
    iAudioEncoded = nullptr;
    return aMsg;
}

TBool MpegTs::ProcessPacket(const Brx& aPacket)
{
    LOG(kCodec, ">MpegTs::ProcessPacket\n");
    iSize = kMpegHeaderBytes;

    if (aPacket.Bytes() < kPacketBytes) {
        return false; // not enough data to recognise
    }

    if (aPacket[0] != 0x47) {  // expect sync word - should seek if can't find it.
        return false;
    }

    const TBool payloadStart = ((aPacket[1] & 0x40) == 0x40);
    LOG(kCodec, "MpegTs::ProcessPacket payloadStart: %u\n", payloadStart);

    TUint pid = (aPacket[1] & 0x1f) << 8 | aPacket[2];
    LOG(kCodec, "MpegTs::ProcessPacket pid: %u\n", pid);

    if ((aPacket[3] & 0x10) != 0x10) {   // ensure there is a payload.
        return false; // FIXME - should this really be a failure?
    }

    TBool adaptationField = false;
    TUint adaptationFieldBytes = 0;
    if ((aPacket[3] & 0x20) != 0x00) {// && iStreamPid != 0 && pid == iStreamPid) {
        LOG(kCodec, "MpegTs::ProcessPacket adaptation field present\n");
        adaptationField = true;
    }

    //TUint continuityCounter = aBuf[3] & 0xf;

    if (adaptationField) {
        TUint adaptationOffset = kMpegHeaderBytes;
        adaptationFieldBytes = aPacket[adaptationOffset];
        adaptationFieldBytes += 1;  // +1 because adaptation field length doesn't account for the adaptation field length byte!
        iSize += adaptationFieldBytes;
        //TBool startsSeq = ((aBuf[adaptationOffset+1] & 0x40) == 0x40);
        LOG(kCodec, "MpegTs::ProcessPacket adaptationFieldBytes: %u, iSize: %u\n", adaptationFieldBytes, iSize);
    }

    // Not concerned with remainder of fields from header.

    TUint offset = kMpegHeaderBytes+adaptationFieldBytes;

    if (payloadStart) {

        if (pid == 0) {
            Brn table(aPacket.Ptr()+offset, aPacket.Bytes()-offset);
            if (!RecognisePat(table)) {
                return false;
            }
            iSize = kPacketBytes;    // Discard entire packet; padding will follow table.
            LOG(kCodec, "MpegTs::ProcessPacket recognised Program Association Table (PAT) iSectionLength: %u, iSize: %u\n", iSectionLength, iSize);
        }

        else if (iProgramMapPid != 0 && pid == iProgramMapPid) {
            Brn table(aPacket.Ptr()+offset, aPacket.Bytes()-offset);
            if (!RecognisePmt(table)) {
                return false;
            }
            iSize = kPacketBytes;    // Discard entire packet; padding will follow table.
            LOG(kCodec, "MpegTs::ProcessPacket recognised Program Map Table (PMT) iSectionLength: %u, iSize: %u\n", iSectionLength, iSize);
        }

        else if (iStreamPid != 0 && pid == iStreamPid) {
            TUint pesBytes = 0;
            TBool isPesPacketStart = false;
            if (offset < aPacket.Bytes() && aPacket.Bytes()-(offset+1) > kPesHeaderStartCodePrefixBytes) {
                if ((aPacket[offset] == 0x00) && (aPacket[offset+1] == 0x00) && (aPacket[offset+2] == 0x01)) {
                    isPesPacketStart = true;
                    pesBytes = kPesHeaderFixedBytes;
                    LOG(kCodec, "MpegTs::ProcessPacket recognised Packetized Elementary Stream (PES) header\n");

                    //TUint streamId = aBuf[offset+3];
                    //if (streamId != 0xc0) {   // Expect only audio.
                    //    ASSERTS();
                    //}
                }
            }

            if (isPesPacketStart) {
                //TUint streamId = aBuf[offset+3];
                //TUint pesPacketLength = Converter::BeUint16At(aBuf, offset+4);
                if ((aPacket[offset+6] & 0x80) == 0x80) { // Optional PES header found
                    TUint pesOptionalHeaderLength = aPacket[offset+8];
                    pesBytes += kPesHeaderOptionalFixedBytes + pesOptionalHeaderLength;
                    LOG(kCodec, "MpegTs::ProcessPacket kPesHeaderOptionalFixedBytes: %u, pesOptionalHeaderLength: %u\n", kPesHeaderOptionalFixedBytes, pesOptionalHeaderLength);
                    LOG(kCodec, "MpegTs::ProcessPacket pesBytes: %u\n", pesBytes);
                }
            }

            iSize += pesBytes;
            LOG(kCodec, "MpegTs::ProcessPacket pesBytes: %u, iSize: %u\n", pesBytes, iSize);
        }
        else {
            // Unrecognised packet while trying to find payload start.
            // Skip it.
            iSize = kPacketBytes;
            LOG(kCodec, "MpegTs::ProcessPacket expected PAT, PMT or PES, but didn't find any. pid: %u\n", pid);
        }

    }

    ASSERT(iSize <= kPacketBytes);
    LOG(kCodec, "<MpegTs::ProcessPacket true\n");
    return true;
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
    TUint progInfoLength = (aPmt[offset+2] & 0x03) << 8 | aPmt[offset+3];


    // Get elementary-stream specific data.
    offset += kPmtSpecificFixedBytes+progInfoLength;
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
