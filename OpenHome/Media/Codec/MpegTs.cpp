#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Codec/MpegTs.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Media/Debug.h>

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


// MpegTsTransportStreamHeader

MpegTsTransportStreamHeader::MpegTsTransportStreamHeader()
{
    Reset();
}

void MpegTsTransportStreamHeader::Parse(const Brx& aHeader)
{
    ASSERT(aHeader.Bytes() == kTransportStreamHeaderBytes);

    if (aHeader[0] != kSyncByte) {
        THROW(InvalidMpegTsPacket); // Expect sync word - should seek if can't find it.
    }

    iPayloadStart = ((aHeader[1] & 0x40) == 0x40);
    LOG(kCodec, "MpegTsTransportStreamHeader::Parse iPayloadStart: %u\n", iPayloadStart);

    iPacketId = (aHeader[1] & 0x1f) << 8 | aHeader[2];
    LOG(kCodec, "MpegTsTransportStreamHeader::Parse iPacketId: %u\n", iPacketId);

    iContainsPayload = ((aHeader[3] & 0x10) != 0x10);
    iAdaptationField = ((aHeader[3] & 0x20) != 0x00);

    iContinuityCounter = aHeader[3] & 0xf;
}

void MpegTsTransportStreamHeader::Reset()
{
    iPayloadStart = 0;
    iPacketId = 0;
    iAdaptationField = false;
    iContainsPayload = false;
    iContinuityCounter = 0;
}

TBool MpegTsTransportStreamHeader::PayloadStart() const
{
    return iPayloadStart;
}

TUint MpegTsTransportStreamHeader::PacketId() const
{
    return iPacketId;
}

TBool MpegTsTransportStreamHeader::AdaptationField() const
{
    return iAdaptationField;
}

TBool MpegTsTransportStreamHeader::ContainsPayload() const
{
    return iContainsPayload;
}

TUint MpegTsTransportStreamHeader::ContinuityCounter() const
{
    return iContinuityCounter;
}


// MpegTsTableHeader

MpegTsTableHeader::MpegTsTableHeader()
{
    Reset();
}

void MpegTsTableHeader::Parse(const Brx& aTableHeader)
{
    if (aTableHeader.Bytes() < kTableHeaderBytes) {
        THROW(InvalidMpegTsPacket);
    }

    // Parse table header.
    TUint offset = aTableHeader[0];
    iTableId = aTableHeader[offset+1];

    // Section syntax indicator.
    if ((aTableHeader[offset+2] & 0x80) != 0x80) {
        THROW(InvalidMpegTsPacket);
    }
    // Private bit.
    if ((aTableHeader[offset+2] & 0x40) != 0x00) {
        THROW(InvalidMpegTsPacket);
    }
    // Reserved bits.
    if ((aTableHeader[offset+2] & 0x30) != 0x30) {
        THROW(InvalidMpegTsPacket);
    }
    // Section length unused bits.
    if ((aTableHeader[offset+2] & 0x0c) != 0x00) {
        THROW(InvalidMpegTsPacket);
    }
    // Section length.
    iSectionLength = (aTableHeader[offset+2] & 0x03) << 8 | (aTableHeader[offset+3]);
    if (iSectionLength > 1021) {
        THROW(InvalidMpegTsPacket);
    }
}

void MpegTsTableHeader::Reset()
{
    iTableId = 0;
    iSectionLength = 0;
}

TUint MpegTsTableHeader::TableId() const
{
    return iTableId;
}

TUint MpegTsTableHeader::SectionLength() const
{
    return iSectionLength;
}


// MpegTsTableSyntax

MpegTsTableSyntax::MpegTsTableSyntax()
{
}

void MpegTsTableSyntax::Parse(const Brx& aTableSyntax)
{
    if (aTableSyntax.Bytes() < kFixedBytes) {
        THROW(InvalidMpegTsPacket);
    }

    // Parse table syntax section.
    //TUint tableIdExt = Converter::BeUint16At(aTableSyntax, 0);
    if ((aTableSyntax[2] & 0xc0) != 0xc0) {
        THROW(InvalidMpegTsPacket);
    }
    //TUint versionNumber = aTableSyntax[2] & 0x3e;
    //TUint currentIndicator = aTableSyntax[2] & 0x01;
    //TUint sectionNumber = aTableSyntax[3];    // starts from 0.
    //TUint sectionNumberLast = aTableSyntax[4];
}


// MpegTsTableBase


MpegTsTableBase::MpegTsTableBase(TUint aTableId)
    : iTableId(aTableId)
{
    Reset();
}

void MpegTsTableBase::Parse(const Brx& aTable)
{
    if (aTable.Bytes() < MpegTsTableHeader::kTableHeaderBytes+MpegTsTableSyntax::kFixedBytes) {
        THROW(InvalidMpegTsPacket);
    }
    Brn tableHeader(aTable.Ptr(), MpegTsTableHeader::kTableHeaderBytes);
    iTableHeader.Parse(tableHeader);

    if (iTableHeader.TableId() != iTableId) {
        THROW(InvalidMpegTsPacket);
    }

    Brn tableSyntax(aTable.Ptr()+MpegTsTableHeader::kTableHeaderBytes, MpegTsTableSyntax::kFixedBytes);
    iTableSyntax.Parse(tableSyntax);
}

void MpegTsTableBase::Reset()
{
    iTableHeader.Reset();
}


// MpegTsProgramAssociationTable

MpegTsProgramAssociationTable::MpegTsProgramAssociationTable()
    : MpegTsTableBase(kTableId)
{
}
void MpegTsProgramAssociationTable::Parse(const Brx& aPat)
{
    MpegTsTableBase::Parse(aPat);

    if (aPat.Bytes() < kFixedHeaderBytes+kBytes) {
        THROW(InvalidMpegTsPacket);
    }
    const TUint offset = kFixedHeaderBytes;

    // PAT-specific data.
    //TUint programNum = Converter::BeUint16At(aBuf, offset);
    if ((aPat[offset+2] & 0xe0) != 0xe0) {  // reserved bits
        THROW(InvalidMpegTsPacket);
    }
    iProgramMapPid = (aPat[offset+2] & 0x1f) << 8 | aPat[offset+3];

    // Ignore checksum.
}

void MpegTsProgramAssociationTable::Reset()
{
    MpegTsTableBase::Reset();
    iProgramMapPid = 0;
}

TUint MpegTsProgramAssociationTable::ProgramMapPid() const
{
    return iProgramMapPid;
}


// MpegTsProgramMapTable

MpegTsProgramMapTable::MpegTsProgramMapTable(TUint aAllowedStreamType)
    : MpegTsTableBase(kTableId)
    , iAllowedStreamType(aAllowedStreamType)
{
    Reset();
}

TUint MpegTsProgramMapTable::StreamPid() const
{
    return iStreamPid;
}

void MpegTsProgramMapTable::Parse(const Brx& aPmt)
{
    MpegTsTableBase::Parse(aPmt);

    if (aPmt.Bytes() < kFixedHeaderBytes+kFixedBytes) {
        THROW(InvalidMpegTsPacket);
    }
    TUint offset = kFixedHeaderBytes;

    // PMT-specific data.
    if ((aPmt[offset] & 0xe0) != 0xe0) {   // reserved bits
        THROW(InvalidMpegTsPacket);
    }
    //TUint progClockRef = (aPmt[offset] & 0x1f) << 8 | aPmt[offset+1];
    if ((aPmt[offset+2] & 0xf0) != 0xf0) {    // reserved bits
        THROW(InvalidMpegTsPacket);
    }
    if ((aPmt[offset+2] & 0x0c) != 0x00) {    // prog info length unused bits
        THROW(InvalidMpegTsPacket);
    }
    TUint progInfoLength = (aPmt[offset+2] & 0x03) << 8 | aPmt[offset+3];


    // Get elementary-stream specific data.
    offset += kFixedBytes+progInfoLength;
    if (iTableHeader.SectionLength()-offset < kFixedBytes) {
        THROW(InvalidMpegTsPacket);
    }
    TUint streamType = aPmt[offset];
    if ((aPmt[offset+1] & 0xe0) != 0xe0) {    // reserved bits
        THROW(InvalidMpegTsPacket);
    }
    TUint elementPid = (aPmt[offset+1] & 0x1f) << 8 | aPmt[offset+2];
    if ((aPmt[offset+3] & 0xf0) != 0xf0) {    // reserved bits
        THROW(InvalidMpegTsPacket);
    }
    if ((aPmt[offset+3] & 0x0c) != 0x00) {    // ES info length unused bits
        THROW(InvalidMpegTsPacket);
    }
    // esInfoLength is no. of stream descriptor bytes.
    //TUint esInfoLength = (aPmt[offset+3] & 0x03) << 8 | aPmt[offset+4];

    // Table finishes with 32-bit CRC.

    if (streamType == iAllowedStreamType) {
        iStreamPid = elementPid;
    }
}

void MpegTsProgramMapTable::Reset()
{
    MpegTsTableBase::Reset();
    iStreamPid = 0;
}


// MpegTs

MpegTs::MpegTs()
    : ContainerBase(Brn("MTS"))
    , iPmt(kStreamTypeAdtsAac)
    , iProgramMapPid(0)
    , iStreamPid(0)
    , iRemaining(kPacketBytes)
    , iAudioEncoded(nullptr)
{
}

MpegTs::~MpegTs()
{
    if (iAudioEncoded != nullptr) {
        iAudioEncoded->RemoveRef();
    }
    iAudioEncoded = nullptr;
}

TBool MpegTs::Recognise()
{
    LOG(kMedia, "MpegTs::Recognise\n");
    iCache->Inspect(iBuf, kStreamHeaderBytes);

    Msg* msg = iCache->Pull();
    while (msg != nullptr) {
        iEncodedStreamRecogniser.Reset();
        msg = msg->Process(iEncodedStreamRecogniser);
        msg->RemoveRef();

        if (iEncodedStreamRecogniser.RecognisedMsgEncodedStream()) {
            // New MsgEncodedStream encountered. Don't keep trying to recognise.
            return false;
        }

        msg = iCache->Pull();
    }

    try {
        iStreamHeader.Parse(iBuf);
        return true;
    }
    catch (InvalidMpegTsPacket&) {
        return false;
    }
}

void MpegTs::Reset()
{
    iState = eStart;
    iEncodedStreamRecogniser.Reset();
    iAudioEncodedRecogniser.Reset();
    iStreamHeader.Reset();
    iPat.Reset();
    iPmt.Reset();
    iProgramMapPid = 0;
    iStreamPid = 0;
    iRemaining = kPacketBytes;
    iBuf.SetBytes(0);
    if (iAudioEncoded != nullptr) {
        iAudioEncoded->RemoveRef();
    }
    iAudioEncoded = nullptr;
}

TBool MpegTs::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    // Seeking currently unsupported.
    return MsgFlush::kIdInvalid;
}

Msg* MpegTs::Pull()
{
    while (iState != eComplete) {

        if (iState != eStart) {
            Msg* msg = iCache->Pull();
            if (msg != nullptr) {
                msg = msg->Process(iAudioEncodedRecogniser);
                if (msg != nullptr) {
                    LOG(kCodec, "<MpegTs::Pull pulled non-audio msg: %p\n", msg);
                    return msg;
                }
            }
        }


        if (iState == eStart) {
            iStreamHeader.Reset();
            iRemaining = kPacketBytes;

            iCache->Inspect(iBuf, kStreamHeaderBytes);
            iState = eInspectPacketHeader;
        }
        else if (iState == eInspectPacketHeader) {
            try {
                ASSERT(iBuf.Bytes() >= kStreamHeaderBytes);
                Brn headerBuf(iBuf.Ptr(), kStreamHeaderBytes);
                iStreamHeader.Parse(headerBuf);
                iRemaining -= kStreamHeaderBytes;
                ASSERT(iRemaining <= kPacketBytes); // Ensure no wrapping.

                if (iStreamHeader.AdaptationField()) {
                    iCache->Inspect(iBuf, kAdaptionFieldLengthBytes);
                    iState = eInspectAdaptationField;
                }
                else {
                    if (!TrySetPayloadState()) {
                        iCache->Discard(iRemaining);
                        iRemaining = 0;
                        iState = eStart;
                    }
                }
            }
            catch (InvalidMpegTsPacket) {
                iCache->Discard(kPacketBytes - kStreamHeaderBytes);
                iState = eStart;
            }
        }
        else if (iState == eInspectAdaptationField) {
            ASSERT(iBuf.Bytes() == kAdaptionFieldLengthBytes);
            TUint const adaptationFieldLength = iBuf[0];

            iRemaining -= iBuf.Bytes();
            iRemaining -= adaptationFieldLength;
            ASSERT(iRemaining <= kPacketBytes); // Ensure no wrapping.

            TUint discard = adaptationFieldLength;
            if (!TrySetPayloadState()) {
                discard += iRemaining;
                iRemaining = 0;
                iState = eStart;
            }

            iCache->Discard(discard);
        }
        else if (iState == eInspectProgramAssociationTable) {
            ASSERT(iBuf.Bytes() == iRemaining);
            iRemaining -= iBuf.Bytes();
            ASSERT(iRemaining <= kPacketBytes); // Ensure no wrapping.

            try {
                iPat.Parse(iBuf);
                iProgramMapPid = iPat.ProgramMapPid();
                iState = eStart;    // Read next packet.
            }
            catch (InvalidMpegTsPacket) {
                iCache->Discard(iRemaining);
                iRemaining = 0;
                iState = eStart;
            }
        }
        else if (iState == eInspectProgramMapTable) {
            ASSERT(iBuf.Bytes() == iRemaining);
            iRemaining -= iBuf.Bytes();
            ASSERT(iRemaining <= kPacketBytes); // Ensure no wrapping.

            try {
                iPmt.Parse(iBuf);
                iStreamPid = iPmt.StreamPid();
                iState = eStart;    // Read next packet.
            }
            catch (InvalidMpegTsPacket) {
                iCache->Discard(iRemaining);
                iRemaining = 0;
                iState = eStart;
            }
        }
        else if (iState == eInspectPesHeader) {
            ASSERT(iBuf.Bytes() == kPesHeaderFixedBytes+kPesHeaderOptionalFixedBytes);
            iRemaining -= iBuf.Bytes();
            ASSERT(iRemaining <= kPacketBytes); // Ensure no wrapping.
            MsgAudioEncoded* msg = nullptr;

            if (iBuf[0] == 0x00 && iBuf[1] == 0x00 && iBuf[2] == 0x01) {
                // PES packet header.
                Brn optionalPesHeader(iBuf.Ptr()+kPesHeaderFixedBytes, iBuf.Bytes()-kPesHeaderFixedBytes);
                const TBool isOptionalPesHeader = (optionalPesHeader[0] & 0x80) == 0x80;

                if (isOptionalPesHeader) {
                    const TUint length = optionalPesHeader[2];
                    iCache->Discard(length);
                    iRemaining -= length;
                    ASSERT(iRemaining <= kPacketBytes); // Ensure no wrapping.
                }
                else {
                    msg = iMsgFactory->CreateMsgAudioEncoded(optionalPesHeader);

                    //msg = TryAppendToAudioEncoded(msg);
                    //if (msg != nullptr) {
                    //    return msg;
                    //}
                }
            }
            else {
                // Must output msg;
                msg = iMsgFactory->CreateMsgAudioEncoded(iBuf);

                //msg = TryAppendToAudioEncoded(msg);
                //if (msg != nullptr) {
                //    return msg;
                //}
            }

            if (iRemaining > 0) {
                // Remainder should now be audio.
                iCache->Accumulate(iRemaining);
                iState = ePullPayload;
            }
            else {
                iState = eStart;
            }


            if (msg != nullptr) {
                return msg;



                //msg = TryAppendToAudioEncoded(msg);
                //if (msg != nullptr) {
                //    return msg;
                //}
            }
        }
        else if (iState == ePullPayload) {
            MsgAudioEncoded* msg = iAudioEncodedRecogniser.AudioEncoded();
            ASSERT(msg != nullptr);
            ASSERT(msg->Bytes() == iRemaining);
            iState = eStart;
            return msg;


            //msg = TryAppendToAudioEncoded(msg);
            //if (msg != nullptr) {
            //    return msg;
            //}
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }
    ASSERTS();  // Processing should never be complete.
    return nullptr;
}

TBool MpegTs::TrySetPayloadState()
{
    //if (iStreamHeader.ContainsPayload()) {
        if (iStreamHeader.PayloadStart()) {
            if (iStreamHeader.PacketId() == 0 && iProgramMapPid == 0) {
                iCache->Inspect(iBuf, iRemaining);
                iState = eInspectProgramAssociationTable;
            }
            else if (iProgramMapPid != 0 && iStreamHeader.PacketId() == iProgramMapPid && iStreamPid == 0) {
                iCache->Inspect(iBuf, iRemaining);
                iState = eInspectProgramMapTable;
            }
            else if (iStreamPid != 0 && iStreamHeader.PacketId() == iStreamPid) {
                if (iState != eInspectPesHeader) {
                    iCache->Inspect(iBuf, kPesHeaderFixedBytes+kPesHeaderOptionalFixedBytes);
                    iState = eInspectPesHeader;
                }
                else {
                    // Remainder should now be audio.
                    iCache->Accumulate(iRemaining);
                    iState = ePullPayload;
                }
            }
            else {
                // Unrecognised/unhandled packet.
                return false;
            }
        }
        else if (iStreamPid != 0 && iStreamHeader.PacketId() == iStreamPid) {
            if (iState != eInspectPesHeader && iRemaining >= kPesHeaderFixedBytes+kPesHeaderOptionalFixedBytes) {
                iCache->Inspect(iBuf, kPesHeaderFixedBytes+kPesHeaderOptionalFixedBytes);
                iState = eInspectPesHeader;
            }
            else {
                // Remainder should now be audio.
                iCache->Accumulate(iRemaining);
                iState = ePullPayload;
            }
        }
        else {
            // Unrecognised payload.
            return false;
        }
        return true;
    //}
    //else { // No payload.
    //    return false;
    //}
    //return true;
}

MsgAudioEncoded* MpegTs::TryAppendToAudioEncoded(MsgAudioEncoded* aMsg)
{
    if (iAudioEncoded == nullptr) {
        iAudioEncoded = aMsg;
        return nullptr;
    }

    aMsg->CopyTo(const_cast<TByte*>(iBuf.Ptr()));
    iBuf.SetBytes(aMsg->Bytes());
    TUint offset = iAudioEncoded->Append(iBuf);

    if (offset == iBuf.Bytes()) {
        // Appended entire msg.
        aMsg->RemoveRef();
        return nullptr;
    }
    else if (offset == 0) {
        // Didn't append any of msg.
        MsgAudioEncoded* msg = iAudioEncoded;
        iAudioEncoded = aMsg;
        return msg;
    }
    else {
        MsgAudioEncoded* remainder = aMsg->Split(offset);
        MsgAudioEncoded* msg = iAudioEncoded;
        iAudioEncoded = remainder;
        aMsg->RemoveRef();
        return msg;
    }
}
