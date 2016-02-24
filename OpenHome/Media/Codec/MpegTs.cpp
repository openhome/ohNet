#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Codec/MpegTs.h>
#include <OpenHome/Media/Codec/ContainerFactory.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Media/MimeTypeList.h>

#include <limits>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

ContainerBase* ContainerFactory::NewMpegTs(IMimeTypeList& aMimeTypeList)
{ // static
    return new MpegTsContainer(aMimeTypeList);
}



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


MpegTsTransportStreamHeader::MpegTsTransportStreamHeader()
{
    Reset();
}

void MpegTsTransportStreamHeader::Parse(const Brx& aHeader)
{
    ASSERT(aHeader.Bytes() == kTransportStreamHeaderBytes);

    //LOG(kCodec, ">MpegTsTransportStreamHeader::Parse 0x%.2x%.2x%.2x%.2x\n", aHeader[0], aHeader[1], aHeader[2], aHeader[3]);

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


// StreamTerminatorDetector

StreamTerminatorDetector::StreamTerminatorDetector()
    : iStreamTerminated(false)
{
}

void StreamTerminatorDetector::Reset()
{
    iStreamTerminated = false;
}

TBool StreamTerminatorDetector::StreamTerminated() const
{
    return iStreamTerminated;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgMode* aMsg)
{
    ASSERT(iStreamTerminated == false);
    iStreamTerminated = true;
    return aMsg;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgTrack* aMsg)
{
    ASSERT(iStreamTerminated == false);
    iStreamTerminated = true;
    return aMsg;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgDrain* aMsg)
{
    ASSERT(iStreamTerminated == false);
    return aMsg;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgDelay* aMsg)
{
    ASSERT(iStreamTerminated == false);
    return aMsg;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgEncodedStream* aMsg)
{
    ASSERT(iStreamTerminated == false);
    iStreamTerminated = true;
    return aMsg;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgAudioEncoded* aMsg)
{
    ASSERT(iStreamTerminated == false);
    return aMsg;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgMetaText* aMsg)
{
    ASSERT(iStreamTerminated == false);
    return aMsg;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    ASSERT(iStreamTerminated == false);
    iStreamTerminated = true;
    return aMsg;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgHalt* aMsg)
{
    ASSERT(iStreamTerminated == false);
    iStreamTerminated = true;
    return aMsg;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgFlush* aMsg)
{
    ASSERT(iStreamTerminated == false);
    iStreamTerminated = true;
    return aMsg;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgWait* aMsg)
{
    ASSERT(iStreamTerminated == false);
    return aMsg;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgBitRate* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* StreamTerminatorDetector::ProcessMsg(MsgQuit* aMsg)
{
    ASSERT(iStreamTerminated == false);
    iStreamTerminated = true;
    return aMsg;
}


// MpegPes

MpegPes::MpegPes(IPipelineElementUpstream& aUpstream, MsgFactory& aMsgFactory)
    : iMsgFactory(aMsgFactory)
    , iCache(aUpstream)
    , iState(eFindSync)
    , iBytesRemaining(0)
{
}

void MpegPes::Reset()
{
    iCache.Reset();
    iHeaderBuf.SetBytes(0);
    iState = eStart;
    iBytesRemaining = 0;
}

Msg* MpegPes::Pull()
{
    while (iState != eComplete) {

        if (iState != eStart) {
            Msg* msg = iCache.Pull();
            if (msg != nullptr) {
                msg = msg->Process(iAudioEncodedRecogniser);
                if (msg != nullptr) {
                    LOG(kCodec, "<MpegPes::Pull pulled non-audio msg: %p\n", msg);
                    return msg;
                }
            }
        }


        if (iState == eStart) {
            iCache.Inspect(iInspectBuf, kPesHeaderFixedBytes);
            iState = eFindSync;
        }
        else if (iState == eFindSync) {
            ASSERT(iHeaderBuf.Bytes()+iInspectBuf.Bytes() == kPesHeaderFixedBytes);
            iHeaderBuf.Append(iInspectBuf);

            Bws<50> buf;
            Ascii::AppendHex(buf, iHeaderBuf);
            LOG(kCodec, "MpegPes::Pull attempting to find sync: %.*s\n", PBUF(buf));

            /**
             * To get to this point, the TS packet in question MUST belong to the
             * stream PID we are decoding (i.e., it must be one of the audio
             * programs).
             *
             * It can only be a PES header if the following conditions are met
             * (to avoid 'start code emulation' problems):
             * - starts with the PES start code (0x000001)
             * - is an audio stream (0xC0)
             * - previous PES packet has been exhausted (iPesBytesRemaining == 0).
             */
            if (iHeaderBuf[0] == 0x00 && iHeaderBuf[1] == 0x00 && iHeaderBuf[2] == 0x01
                && iHeaderBuf[3] == kPesAudioStreamId) {
                iBytesRemaining = iHeaderBuf[4] << 8 | iHeaderBuf[5];    // Zero-length is only allowed for video streams, so this must be a valid length.
                LOG(kCodec, "MpegPes::Pull eFindSync iBytesRemaining: %u\n", iBytesRemaining);
                iHeaderBuf.SetBytes(0);

                if (iBytesRemaining >= kPesHeaderFixedBytes+kPesHeaderOptionalFixedBytes) {
                    iCache.Inspect(iInspectBuf, kPesHeaderOptionalFixedBytes);
                    iState = eInspectOptionalHeader;
                }
                else {
                    iCache.Accumulate(iBytesRemaining);
                    iState = ePullPayload;
                }
            }
            else {
                // Not a PES header. Shift buffer along by one byte and read in next byte.
                iHeaderBuf.Replace(iHeaderBuf.Ptr()+1, iHeaderBuf.Bytes()-1);
                iCache.Inspect(iInspectBuf, 1);
                iState = eFindSync;
            }
        }
        else if (iState == eInspectOptionalHeader) {
            ASSERT(iInspectBuf.Bytes() == kPesHeaderOptionalFixedBytes);
            iBytesRemaining -= iInspectBuf.Bytes();
            const TBool isOptionalPesHeader = (iInspectBuf[0] & 0x80) == 0x80;

            if (isOptionalPesHeader) {
                const TUint length = iInspectBuf[2];
                iCache.Discard(length);
                ASSERT(iBytesRemaining >= length);
                iBytesRemaining -= length;
                iState = ePullPayload;
                iCache.Accumulate(iBytesRemaining);
                LOG(kCodec, "MpegPes::Pull eInspectOptionalHeader optional header found. iBytesRemaining: %u\n", iBytesRemaining);
            }
            else {
                LOG(kCodec, "MpegPes::Pull eInspectOptionalHeader optional header not found. iBytesRemaining: %u\n", iBytesRemaining);
                iState = ePullPayload;
                iCache.Accumulate(iBytesRemaining);
                MsgAudioEncoded* msg = iMsgFactory.CreateMsgAudioEncoded(iInspectBuf);
                return msg;
            }
        }
        else if (iState == ePullPayload) {
            LOG(kCodec, "MpegPes::Pull ePullPayload iBytesRemaining: %u\n", iBytesRemaining);
            MsgAudioEncoded* msg = iAudioEncodedRecogniser.AudioEncoded();
            ASSERT(msg != nullptr);
            ASSERT(msg->Bytes() == iBytesRemaining);
            iBytesRemaining = 0;

            iState = eStart;
            return msg;
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }
    ASSERTS();  // Processing should never be complete.
    return nullptr;
}


// MpegTs

MpegTs::MpegTs(IMsgAudioEncodedCache& aCache, MsgFactory& aMsgFactory)
    : iCache(aCache)
    , iMsgFactory(aMsgFactory)
    , iPmt(kStreamTypeAdtsAac)
    , iProgramMapPid(0)
    , iStreamPid(0)
    , iRemaining(kPacketBytes)
    //, iAudioEncoded(nullptr)
    , iPendingMsg(nullptr)
{
}

MpegTs::~MpegTs()
{
    //if (iAudioEncoded != nullptr) {
    //    iAudioEncoded->RemoveRef();
    //}
    //iAudioEncoded = nullptr;
}

Msg* MpegTs::Recognise()
{
    LOG(kMedia, "MpegTs::Recognise\n");
    if (!iRecognitionStarted) {
        iCache.Inspect(iBuf, kStreamHeaderBytes);
        iRecognitionStarted = true;
    }

    Msg* msg = iCache.Pull();
    if (msg != nullptr) {
        return msg;
    }

    try {
        iStreamHeader.Parse(iBuf);
        iRecognitionSuccess = true;
        return nullptr;
    }
    catch (InvalidMpegTsPacket&) {
        return nullptr;
    }
}

TBool MpegTs::Recognised() const
{
    return iRecognitionSuccess;
}

void MpegTs::Reset()
{
    iState = eStart;
    iEncodedStreamRecogniser.Reset();
    iStreamTerminatorDetector.Reset();
    iAudioEncodedRecogniser.Reset();
    iStreamHeader.Reset();
    iPat.Reset();
    iPmt.Reset();
    iRecognitionStarted = false;
    iRecognitionSuccess = false;
    iProgramMapPid = 0;
    iStreamPid = 0;
    iRemaining = kPacketBytes;
    iBuf.SetBytes(0);
    //if (iAudioEncoded != nullptr) {
    //    iAudioEncoded->RemoveRef();
    //}
    //iAudioEncoded = nullptr;
    iAudioEncoded.SetBytes(0);
    ASSERT(iPendingMsg == nullptr);
}

Msg* MpegTs::Pull()
{
    iStreamTerminatorDetector.Reset();
    while (iState != eComplete) {

        if (iState != eStart) {
            if (iPendingMsg != nullptr) {
                Msg* msg = iPendingMsg;
                iPendingMsg = nullptr;
                LOG(kCodec, "<MpegTs::Pull pulled non-audio msg: %p\n", msg);
                return msg;
            }

            Msg* msg = iCache.Pull();
            if (msg != nullptr) {
                msg = msg->Process(iStreamTerminatorDetector);
                if (iStreamTerminatorDetector.StreamTerminated()) {
                    LOG(kCodec, "MpegTs::Pull detected EoS.\n");
                    if (iAudioEncoded.Bytes() > 0) {
                        LOG(kCodec, "MpegTs::Pull EoS. Returning %u bytes of buffered audio\n.", iAudioEncoded.Bytes());
                        MsgAudioEncoded* msgAudio = iMsgFactory.CreateMsgAudioEncoded(iAudioEncoded);
                        iAudioEncoded.SetBytes(0);
                        iPendingMsg = msg;
                        return msgAudio;
                    }
                    return msg;
                }

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

            iCache.Inspect(iBuf, kStreamHeaderBytes);
            iState = eInspectPacketHeader;
        }
        else if (iState == eInspectPacketHeader) {
            try {
                ASSERT(iBuf.Bytes() >= kStreamHeaderBytes);
                Brn headerBuf(iBuf.Ptr(), kStreamHeaderBytes);
                iStreamHeader.Parse(headerBuf);
                iRemaining -= kStreamHeaderBytes;

                if (iRemaining <= kPacketBytes) {
                    if (iStreamHeader.AdaptationField()) {
                        iCache.Inspect(iBuf, kAdaptionFieldLengthBytes);
                        iState = eInspectAdaptationField;
                    }
                    else {
                        if (!TrySetPayloadState()) {
                            iCache.Discard(iRemaining);
                            iRemaining = 0;
                            iState = eStart;
                        }
                    }
                }
                else {
                    DiscardRemaining();
                }
            }
            catch (InvalidMpegTsPacket&) {
                iCache.Discard(kPacketBytes - kStreamHeaderBytes);
                iState = eStart;
            }
        }
        else if (iState == eInspectAdaptationField) {
            ASSERT(iBuf.Bytes() == kAdaptionFieldLengthBytes);
            TUint const adaptationFieldLength = iBuf[0];

            iRemaining -= iBuf.Bytes();
            iRemaining -= adaptationFieldLength;

            if (iRemaining <= kPacketBytes) {
                TUint discard = adaptationFieldLength;

                if (iRemaining == 0) {
                    // Adaptation field may constitute remainder of packet.
                    iState = eStart;
                }
                else {
                    if (!TrySetPayloadState()) {
                        discard += iRemaining;
                        iRemaining = 0;
                        iState = eStart;
                    }
                }

                iCache.Discard(discard);
            }
            else {
                DiscardRemaining();
            }
        }
        else if (iState == eInspectProgramAssociationTable) {
            ASSERT(iBuf.Bytes() == iRemaining);
            iRemaining -= iBuf.Bytes();

            if (iRemaining <= kPacketBytes) {
                try {
                    iPat.Parse(iBuf);
                    iProgramMapPid = iPat.ProgramMapPid();
                    iState = eStart;    // Read next packet.
                }
                catch (InvalidMpegTsPacket&) {
                    iCache.Discard(iRemaining);
                    iRemaining = 0;
                    iState = eStart;
                }
            }
            else {
                DiscardRemaining();
            }
        }
        else if (iState == eInspectProgramMapTable) {
            ASSERT(iBuf.Bytes() == iRemaining);
            iRemaining -= iBuf.Bytes();

            if (iRemaining <= kPacketBytes) {
                try {
                    iPmt.Parse(iBuf);
                    iStreamPid = iPmt.StreamPid();
                    iState = eStart;    // Read next packet.
                }
                catch (InvalidMpegTsPacket&) {
                    iCache.Discard(iRemaining);
                    iRemaining = 0;
                    iState = eStart;
                }
            }
            else {
                DiscardRemaining();
            }
        }
        else if (iState == ePullPayload) {
            MsgAudioEncoded* msg = iAudioEncodedRecogniser.AudioEncoded();
            ASSERT(msg != nullptr);
            ASSERT(msg->Bytes() == iRemaining);
            iRemaining = 0;

            iState = eStart;
            msg = TryAppendToAudioEncoded(msg);
            if (msg != nullptr) {
                return msg;
            }
        }
        else if (iState == eDiscarding) {
            DiscardRemaining();
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
            iCache.Inspect(iBuf, iRemaining);
            iState = eInspectProgramAssociationTable;
        }
        else if (iProgramMapPid != 0 && iStreamHeader.PacketId() == iProgramMapPid && iStreamPid == 0) {
            iCache.Inspect(iBuf, iRemaining);
            iState = eInspectProgramMapTable;
        }
        else if (iStreamPid != 0 && iStreamHeader.PacketId() == iStreamPid) {
            // Remainder should now be audio.
            iCache.Accumulate(iRemaining);
            iState = ePullPayload;
        }
        else {
            // Unrecognised/unhandled packet.
            return false;
        }
    }
    else if (iStreamPid != 0 && iStreamHeader.PacketId() == iStreamPid) {
        // Remainder should now be audio.
        iCache.Accumulate(iRemaining);
        iState = ePullPayload;
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

void MpegTs::DiscardRemaining()
{
    // This is called when stream corruption is detected, so discard the
    // largest possible number of bytes. If a new stream starts before that
    // number of bytes is discarded, that message should still be passed on so
    // that this container can terminate.
    iCache.Discard(std::numeric_limits<TUint>::max());
    iRemaining = 0;
    iState = eDiscarding;
}

MsgAudioEncoded* MpegTs::TryAppendToAudioEncoded(MsgAudioEncoded* aMsg)
{
    const TUint avail = iAudioEncoded.MaxBytes()-iAudioEncoded.Bytes();
    if (aMsg->Bytes() <= avail) {
        aMsg->CopyTo(const_cast<TByte*>(iAudioEncoded.Ptr())+iAudioEncoded.Bytes());
        iAudioEncoded.SetBytes(iAudioEncoded.Bytes()+aMsg->Bytes());
        aMsg->RemoveRef();

        if (iAudioEncoded.Bytes() == iAudioEncoded.MaxBytes()) {
            MsgAudioEncoded* msg = iMsgFactory.CreateMsgAudioEncoded(iAudioEncoded);
            iAudioEncoded.SetBytes(0);
            return msg;
        }
        return nullptr;
    }
    else { // aMsg->Bytes() > avail
        MsgAudioEncoded* remainder = aMsg->Split(avail);

        aMsg->CopyTo(const_cast<TByte*>(iAudioEncoded.Ptr())+iAudioEncoded.Bytes());
        iAudioEncoded.SetBytes(iAudioEncoded.Bytes()+aMsg->Bytes());
        aMsg->RemoveRef();

        ASSERT(iAudioEncoded.Bytes() == iAudioEncoded.MaxBytes());
        MsgAudioEncoded* msg = iMsgFactory.CreateMsgAudioEncoded(iAudioEncoded);
        iAudioEncoded.SetBytes(0);

        remainder->CopyTo(const_cast<TByte*>(iAudioEncoded.Ptr())+iAudioEncoded.Bytes());
        iAudioEncoded.SetBytes(iAudioEncoded.Bytes()+remainder->Bytes());
        remainder->RemoveRef();

        return msg;
    }
}


// MpegTsContainer

MpegTsContainer::MpegTsContainer(IMimeTypeList& aMimeTypeList)
    : ContainerBase(Brn("MTS"))
    , iMpegTs(nullptr)
    , iMpegPes(nullptr)
{
    aMimeTypeList.Add("application/vnd.apple.mpegurl");
}

MpegTsContainer::~MpegTsContainer()
{
    delete iMpegPes;
    delete iMpegTs;
}


Msg* MpegTsContainer::Recognise()
{
    return iMpegTs->Recognise();
}

TBool MpegTsContainer::Recognised() const
{
    return iMpegTs->Recognised();
}

void MpegTsContainer::Reset()
{
    iMpegTs->Reset();
    iMpegPes->Reset();
}

TBool MpegTsContainer::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    // Seeking currently unsupported.
    return false;
}

Msg* MpegTsContainer::Pull()
{
    return iMpegPes->Pull();
}

void MpegTsContainer::Construct(IMsgAudioEncodedCache& aCache, MsgFactory& aMsgFactory, IContainerSeekHandler& aSeekHandler, IContainerUrlBlockWriter& aUrlBlockWriter)
{
    ContainerBase::Construct(aCache, aMsgFactory, aSeekHandler, aUrlBlockWriter);
    iMpegTs = new MpegTs(*iCache, *iMsgFactory);
    iMpegPes = new MpegPes(*iMpegTs, *iMsgFactory);
}
