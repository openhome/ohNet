#ifndef HEADER_PIPELINE_CODEC_MPEG_TS
#define HEADER_PIPELINE_CODEC_MPEG_TS

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Codec/Container.h>

EXCEPTION(InvalidMpegTsPacket);

namespace OpenHome {
namespace Media {
namespace Codec {

class MpegTsAdaptationFieldProcessor : public IPipelineElementUpstream
{
private:
    static const TUint kAdaptationFieldLength = 1;
public:
    void AdaptationFieldPresent(TBool aPresent);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
};

class MpegTsTransportStreamHeader
{
public:
    static const TByte kSyncByte = 0x47;
    static const TUint kTransportStreamHeaderBytes = 4;
public:
    MpegTsTransportStreamHeader();
    void Parse(const Brx& aHeader); // THROWS InvalidMpegTsPacket
    void Reset();
    TBool PayloadStart() const;
    TUint PacketId() const;
    TBool AdaptationField() const;
    TBool ContainsPayload() const;
    TUint ContinuityCounter() const;
private:
    TBool iPayloadStart;
    TUint iPacketId;
    TBool iAdaptationField;
    TBool iContainsPayload;
    TUint iContinuityCounter;
};

class MpegTsTableHeader
{
public:
    static const TUint kTableHeaderBytes = 4;
public:
    MpegTsTableHeader();
    void Parse(const Brx& aTableHeader); // THROWS InvalidMpegTsPacket
    void Reset();
    TUint TableId() const;
    TUint SectionLength() const;
private:
    TUint iTableId;
    TUint iSectionLength;
};

class MpegTsTableSyntax
{
public:
    static const TUint kFixedBytes = 5;
public:
    MpegTsTableSyntax();
    void Parse(const Brx& aTableSyntax); // THROWS InvalidMpegTsPacket
};

class MpegTsTableBase : private INonCopyable
{
protected:
    static const TUint kFixedHeaderBytes = MpegTsTableHeader::kTableHeaderBytes+MpegTsTableSyntax::kFixedBytes;
protected:
    MpegTsTableBase(TUint aTableId);
public:
    virtual void Parse(const Brx& aTable); // THROWS InvalidMpegTsPacket
    virtual void Reset();
protected:
    MpegTsTableHeader iTableHeader;
    MpegTsTableSyntax iTableSyntax;
private:
    const TUint iTableId;
};

class MpegTsProgramAssociationTable : public MpegTsTableBase
{
private:
    static const TUint kTableId = 0x00;
    static const TUint kBytes = 4;
public:
    MpegTsProgramAssociationTable();
    TUint ProgramMapPid() const;
public: // from MpegTsTableBase
    void Parse(const Brx& aPat); // THROWS InvalidMpegTsPacket
    void Reset();
private:
    TUint iProgramMapPid;
};

class MpegTsProgramMapTable : public MpegTsTableBase
{
private:
    static const TUint kTableId = 0x02;
    static const TUint kFixedBytes = 4;
public:
    MpegTsProgramMapTable(TUint aAllowedStreamType);
    TUint StreamPid() const;
public: // from MpegTsTableBase
    void Parse(const Brx& aPmt); // THROWS InvalidMpegTsPacket
    void Reset();
private:
    const TUint iAllowedStreamType;
    TUint iStreamPid;
};

// FIXME - bodge for fact that MpegTs buffers EncodedAudio data to allow it to detect when it should push any remaining buffered data.
class StreamTerminatorDetector : public IMsgProcessor
{
public:
    StreamTerminatorDetector();
    void Reset();
    TBool StreamTerminated() const;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgChangeInput* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    TBool iStreamTerminated;
};

class MpegTs : public ContainerBase
{
private:
    static const TUint kPacketBytes = 188;
    static const TUint kAdaptionFieldLengthBytes = 1;
    static const TUint kStreamHeaderBytes = MpegTsTransportStreamHeader::kTransportStreamHeaderBytes;

    static const TUint kStreamSpecificFixedBytes = 5;
    static const TUint kStreamTypeAdtsAac = 0x0f;   // stream type 15/0x0f is ISO/IEC 13818-7 ADTS AAC

    static const TUint kPesHeaderStartCodePrefixBytes = 3;
    static const TUint kPesHeaderFixedBytes = 6;
    static const TUint kPesHeaderOptionalFixedBytes = 3;
public:
    MpegTs();
    ~MpegTs();
public: // from ContainerBase
    TBool Recognise() override;
    void Reset() override;
    TBool TrySeek(TUint aStreamId, TUint64 aOffset) override;
    Msg* Pull() override;
private:
    TBool TrySetPayloadState();
    MsgAudioEncoded* TryAppendToAudioEncoded(MsgAudioEncoded* aMsg);
private:
    enum EState {
        eStart,
        eInspectPacketHeader,
        eInspectAdaptationField,
        eInspectProgramAssociationTable,
        eInspectProgramMapTable,
        eInspectPesHeader,
        ePullPayload,
        eComplete,
    };
private:
    EState iState;
    MsgEncodedStreamRecogniser iEncodedStreamRecogniser;
    StreamTerminatorDetector iStreamTerminatorDetector;
    MsgAudioEncodedRecogniser iAudioEncodedRecogniser;
    MpegTsTransportStreamHeader iStreamHeader;
    MpegTsProgramAssociationTable iPat;
    MpegTsProgramMapTable iPmt;
    TUint iProgramMapPid;
    TUint iStreamPid;
    TUint iRemaining;
    Bws<kPacketBytes> iBuf;
    //MsgAudioEncoded* iAudioEncoded;
    Bws<EncodedAudio::kMaxBytes> iAudioEncoded;
    Msg* iPendingMsg;   // FIXME - bodge to cope with fact that pipeline can't handle lots of small msgs (i.e., lots of <188-byte MsgAudioEncoded being returned, so that any cached audio can be flushed.
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_CODEC_MPEG_TS
