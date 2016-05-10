#include "OhmMsg.h"
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Av;

// OhmMsg

OhmMsg::OhmMsg(OhmMsgFactory& aFactory)
    : iFactory(&aFactory)
    , iRefCount(0)
{
    ASSERT(iRefCount.is_lock_free());
}

OhmMsg::~OhmMsg()
{
}

void OhmMsg::AddRef()
{
    iRefCount++;
}

void OhmMsg::RemoveRef()
{
    if (--iRefCount == 0) {
        iFactory->Destroy(*this);
    }
}

void OhmMsg::Create()
{
    iRefCount = 1;
}

// OhmMsgTimestamped

OhmMsgTimestamped::OhmMsgTimestamped(OhmMsgFactory& aFactory)
    : OhmMsg(aFactory)
    , iRxTimestamped(false)
    , iRxTimestamp(0)
{
}

OhmMsgTimestamped::~OhmMsgTimestamped()
{
}

TBool OhmMsgTimestamped::RxTimestamped() const
{
    return iRxTimestamped;
}

TUint OhmMsgTimestamped::RxTimestamp() const
{
    return iRxTimestamp;
}

void OhmMsgTimestamped::SetRxTimestamp(TUint aValue)
{
    iRxTimestamp = aValue;
    iRxTimestamped = true;
}

void OhmMsgTimestamped::Create()
{
    iRxTimestamp = 0;
    iRxTimestamped = false;
    OhmMsg::Create();
}
    
// OhmMsgAudio

OhmMsgAudio::OhmMsgAudio(OhmMsgFactory& aFactory)
    : OhmMsgTimestamped(aFactory)
    , iAudio(iUnifiedBuffer.Ptr() + kStreamHeaderBytes, kMaxSampleBytes)
    , iHeaderSerialised(false)
{
}

void OhmMsgAudio::Create()
{
    OhmMsgTimestamped::Create();
}

void OhmMsgAudio::Create(IReader& aReader, const OhmHeader& aHeader)
{
    OhmMsgTimestamped::Create();
    ASSERT(aHeader.MsgType() == OhmHeader::kMsgTypeAudio ||
           aHeader.MsgType() == OhmHeader::kMsgTypeAudioBlob);

    Bws<kStreamHeaderBytes> headerBuf;
    WriterBuffer writer(headerBuf);
    aHeader.Externalise(writer);
    ReaderBinary reader(aReader);
    Bwn audioHeaderBuf(headerBuf.Ptr() + headerBuf.Bytes(), headerBuf.MaxBytes() - headerBuf.Bytes());
    reader.ReadReplace(kHeaderBytes, audioHeaderBuf);
    headerBuf.SetBytes(headerBuf.Bytes() + audioHeaderBuf.Bytes());
    /* Externalise assumes that iUnifiedBuffer is a single contiguous block and that audio
       starts kStreamHeaderBytes into the buffer.  Left pad the header to achieve this. */
    const TUint codecBytes = headerBuf[headerBuf.Bytes()-1];
    iStreamHeaderOffset = kStreamHeaderBytes - headerBuf.Bytes() - codecBytes;
    iUnifiedBuffer.SetBytes(iStreamHeaderOffset);
    iUnifiedBuffer.Append(headerBuf);
    if (codecBytes > 0) {
        reader.ReadReplace(codecBytes, iCodec);
        iUnifiedBuffer.Append(iCodec);
    }
    else {
        iCodec.Replace(Brx::Empty());
    }

    ReaderBuffer rb(audioHeaderBuf);
    ReaderBinary reader2(rb);
    const TUint headerBytes = reader2.ReadUintBe(1);
    ASSERT(headerBytes == kHeaderBytes);

    iHalt = false;
    iLossless = false;
    iTimestamped = false;
    iResent = false;
    const TUint flags = reader2.ReadUintBe(1);
    if (flags & kFlagHalt) {
        iHalt = true;
    }
    if (flags & kFlagLossless) {
        iLossless = true;
    }
    if (flags & kFlagTimestamped) {
        iTimestamped = true;
    }
    if (flags & kFlagResent) {
        iResent = true;
    }

    iSamples = reader2.ReadUintBe(2);
    iFrame = reader2.ReadUintBe(4);
    iNetworkTimestamp = reader2.ReadUintBe(4);
    iMediaLatency = reader2.ReadUintBe(4);
    iMediaTimestamp = reader2.ReadUintBe(4);
    iSampleStart = reader2.ReadUint64Be(8);
    iSamplesTotal = reader2.ReadUint64Be(8);
    iSampleRate = reader2.ReadUintBe(4);
    iBitRate = reader2.ReadUintBe(4);
    iVolumeOffset = reader2.ReadIntBe(2);
    iBitDepth = reader2.ReadUintBe(1);
    iChannels = reader2.ReadUintBe(1);
    const TUint reserved = reader2.ReadUintBe(1);
    ASSERT (reserved == kReserved);
    
    const TUint audioBytes = aHeader.MsgBytes() - kHeaderBytes - codecBytes;
    iAudio.Set(iUnifiedBuffer.Ptr() + kStreamHeaderBytes, audioBytes);
    reader.ReadReplace(audioBytes, iAudio);
    iUnifiedBuffer.SetBytes(iUnifiedBuffer.Bytes() + iAudio.Bytes());
    iHeaderSerialised = true;
}

void OhmMsgAudio::Create(TBool aHalt, TBool aLossless, TBool aTimestamped, TBool aResent, TUint aSamples,
                         TUint aFrame, TUint aNetworkTimestamp, TUint aMediaLatency, TUint64 aSampleStart,
                         const Brx& aStreamHeader, const Brx& aAudio)
{
    OhmMsgTimestamped::Create();

    iHalt = aHalt;
    iLossless = aLossless;
    iTimestamped = aTimestamped;
    iResent = aResent;
    iSamples = aSamples;
    iFrame = aFrame;
    iNetworkTimestamp = aNetworkTimestamp;
    iMediaLatency = aMediaLatency;
    iMediaTimestamp = 0;
    iSampleStart = aSampleStart;

    iStreamHeaderOffset = kStreamHeaderBytes - aStreamHeader.Bytes();
    iUnifiedBuffer.SetBytes(iStreamHeaderOffset);
    iUnifiedBuffer.Append(aStreamHeader);
    iUnifiedBuffer.Append(aAudio);
    iAudio.SetBytes(aAudio.Bytes());
    iHeaderSerialised = false;
}

void OhmMsgAudio::ReinitialiseFields(TBool aHalt, TBool aLossless, TBool aTimestamped, TBool aResent,
                                     TUint aSamples, TUint aFrame, TUint aNetworkTimestamp, TUint aMediaLatency,
                                     TUint64 aSampleStart, const Brx& aStreamHeader)
{
    iHalt = aHalt;
    iLossless = aLossless;
    iTimestamped = aTimestamped;
    iResent = aResent;
    iSamples = aSamples;
    iFrame = aFrame;
    iNetworkTimestamp = aNetworkTimestamp;
    iMediaLatency = aMediaLatency;
    iMediaTimestamp = 0;
    iSampleStart = aSampleStart;

    iStreamHeaderOffset = kStreamHeaderBytes - aStreamHeader.Bytes();
    iUnifiedBuffer.SetBytes(iStreamHeaderOffset);
    iUnifiedBuffer.Append(aStreamHeader);
    iHeaderSerialised = false;
}

void OhmMsgAudio::GetStreamHeader(Bwx& aBuf, TUint64 aSamplesTotal, TUint aSampleRate, TUint aBitRate,
                                  TUint aVolumeOffset, TUint aBitDepth, TUint aChannels, const Brx& aCodec)
{ // static
    WriterBuffer wb(aBuf);
    WriterBinary writer(wb);
    writer.WriteUint64Be(aSamplesTotal);
    writer.WriteUint32Be(aSampleRate);
    writer.WriteUint32Be(aBitRate);
    writer.WriteInt16Be(aVolumeOffset);
    writer.WriteUint8(aBitDepth);
    writer.WriteUint8(aChannels);
    writer.WriteUint8(kReserved);
    writer.WriteUint8(aCodec.Bytes());
    if (aCodec.Bytes() > 0) {
        writer.Write(aCodec);
    }
}

TBool OhmMsgAudio::Halt() const
{
    return iHalt;
}

TBool OhmMsgAudio::Lossless() const
{
    return iLossless;
}

TBool OhmMsgAudio::Timestamped() const
{
    return iTimestamped;
}

TBool OhmMsgAudio::Resent() const
{
    return iResent;
}

TUint OhmMsgAudio::Samples() const
{
    return iSamples;
}

TUint OhmMsgAudio::Frame() const
{
    return iFrame;
}

TUint OhmMsgAudio::NetworkTimestamp() const
{
    return iNetworkTimestamp;
}

TUint OhmMsgAudio::MediaLatency() const
{
    return iMediaLatency;
}

TUint OhmMsgAudio::MediaTimestamp() const
{
    return iMediaTimestamp;
}

TUint64 OhmMsgAudio::SampleStart() const
{
    return iSampleStart;
}

TUint64 OhmMsgAudio::SamplesTotal() const
{
    return iSamplesTotal;
}

TUint OhmMsgAudio::SampleRate() const
{
    return iSampleRate;
}

TUint OhmMsgAudio::BitRate() const
{
    return iBitRate;
}

TInt OhmMsgAudio::VolumeOffset() const
{
    return iVolumeOffset;
}

TUint OhmMsgAudio::BitDepth() const
{
    return iBitDepth;
}

TUint OhmMsgAudio::Channels() const
{
    return iChannels;
}

const Brx& OhmMsgAudio::Codec() const
{
    return iCodec;
}

const Brx& OhmMsgAudio::Audio() const
{
    return iAudio;
}

Bwx& OhmMsgAudio::Audio()
{
    return iAudio;
}

void OhmMsgAudio::SetResent(TBool aValue)
{
    iResent = aValue;
}

void OhmMsgAudio::Process(IOhmMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void OhmMsgAudio::Externalise(IWriter& aWriter)
{
    Serialise(); // prepends the ohm header, now ready to send!
    iUnifiedBuffer.SetBytes(kStreamHeaderBytes+iAudio.Bytes());
    aWriter.Write(iUnifiedBuffer.Split(iStreamHeaderOffset));
}

void OhmMsgAudio::Serialise()
{
    if (iHeaderSerialised)
        return;

    static const TUint kPerFrameBytes = 28; // binary values written between OhmHeader and iStreamHeader

    const TUint streamHeaderBytes = kStreamHeaderBytes - iStreamHeaderOffset;
    const TUint additionalHeaderBytes = kPerFrameBytes + streamHeaderBytes + iAudio.Bytes();
    OhmHeader header(OhmHeader::kMsgTypeAudio, additionalHeaderBytes);

    // prepare to prepend
    const TUint prependOffset = iStreamHeaderOffset - kPerFrameBytes - OhmHeader::kHeaderBytes;
    const TByte* ptr = iUnifiedBuffer.Ptr() + prependOffset;

    Bwn headerBuffer(ptr, kPerFrameBytes + OhmHeader::kHeaderBytes);

    WriterBuffer writerBuffer(headerBuffer);

    header.Externalise(writerBuffer);
    WriterBinary writer(writerBuffer);

    TUint flags = 0;
    if (iHalt) {
        flags |= kFlagHalt;
    }
    if (iLossless) {
        flags |= kFlagLossless;
    }
    if (iTimestamped) {
        flags |= kFlagTimestamped;
    }
    if (iResent) {
        flags |= kFlagResent;
    }
    
    writer.WriteUint8(kHeaderBytes);
    writer.WriteUint8(flags);
    writer.WriteUint16Be(iSamples);
    writer.WriteUint32Be(iFrame);
    writer.WriteUint32Be(iNetworkTimestamp);
    writer.WriteUint32Be(iMediaLatency);
    writer.WriteUint32Be(iMediaTimestamp);
    writer.WriteUint64Be(iSampleStart);

    iStreamHeaderOffset = prependOffset;

    //Log::PrintHex(iUnifiedBuffer.Split(iStreamHeaderOffset, kStreamHeaderBytes-iStreamHeaderOffset));
    //Log::Print("\n");

    ASSERT(headerBuffer.BytesRemaining() == 0);
    iHeaderSerialised = true;
}

Brn OhmMsgAudio::SendableBuffer()
{
    iUnifiedBuffer.SetBytes(kStreamHeaderBytes + iAudio.Bytes());
    return iUnifiedBuffer.Split(iStreamHeaderOffset);
}

// OhmMsgAudioBlob

void OhmMsgAudioBlob::ExternaliseAsBlob(IWriter& aWriter)
{
    OhmHeader header(OhmHeader::kMsgTypeAudioBlob, iBlob.Bytes());  // deliberately omit RxTimestamp().
    header.Externalise(aWriter);                                    // This allows us to (hackily) reuse OhmMsgAudio's internalise later

    aWriter.Write(iBlob);

    WriterBinary wb(aWriter);
    const TUint8 rxTimeStamped = RxTimestamped()? 1 : 0;
    wb.WriteUint8(rxTimeStamped);
    if (rxTimeStamped) {
        wb.WriteUint32Be(RxTimestamp());
    }
}

void OhmMsgAudioBlob::Process(IOhmMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void OhmMsgAudioBlob::Externalise(IWriter& aWriter)
{
    OhmHeader header(OhmHeader::kMsgTypeAudio, iBlob.Bytes());

    header.Externalise(aWriter);
    aWriter.Write(iBlob);
}

OhmMsgAudioBlob::OhmMsgAudioBlob(OhmMsgFactory& aFactory)
    : OhmMsgTimestamped(aFactory)
    , iFlags(0)
    , iFrame(0)
{
}

void OhmMsgAudioBlob::Create(IReader& aReader, const OhmHeader& aHeader)
{
    OhmMsgTimestamped::Create();
    ASSERT (aHeader.MsgType() == OhmHeader::kMsgTypeAudio);

    ReaderBinary reader(aReader);
    reader.ReadReplace(aHeader.MsgBytes(), iBlob);
    iFlags = iBlob[1];
    iFrame = Converter::BeUint32At(iBlob, 4);
    iSampleStart = Converter::BeUint64At(iBlob, 20);
}

void OhmMsgAudioBlob::Create(OhmMsgAudio& aMsg, IReader& aReader, const OhmHeader& aHeader)
{ // static
    ASSERT(aHeader.MsgType() == OhmHeader::kMsgTypeAudioBlob);
    aMsg.Create(aReader, aHeader);
    ReaderBinary reader(aReader);
    const TBool timestamped = (aReader.Read(1)[0] != 0);
    if (timestamped) {
        aMsg.SetRxTimestamp(reader.ReadUintBe(4));
    }
}


// OhmMsgTrack

OhmMsgTrack::OhmMsgTrack(OhmMsgFactory& aFactory)
    : OhmMsg(aFactory)
{
}

void OhmMsgTrack::Create(IReader& aReader, const OhmHeader& aHeader)
{
    OhmMsg::Create();

    ASSERT (aHeader.MsgType() == OhmHeader::kMsgTypeTrack);
    
    ReaderBinary reader(aReader);
    iSequence = reader.ReadUintBe(4);
    TUint uri = reader.ReadUintBe(4);
    TUint metadata = reader.ReadUintBe(4);
    reader.ReadReplace(uri, iUri);
    reader.ReadReplace(metadata, iMetadata);
}

void OhmMsgTrack::Create(TUint aSequence, const Brx& aUri, const Brx& aMetadata)
{
    OhmMsg::Create();

    iSequence = aSequence;
    iUri.Replace(aUri);
    iMetadata.Replace(aMetadata);
}

TUint OhmMsgTrack::Sequence() const
{
    return iSequence;
}

const Brx& OhmMsgTrack::Uri() const
{
    return iUri;
}

const Brx& OhmMsgTrack::Metadata() const
{
    return iMetadata;
}

void OhmMsgTrack::Process(IOhmMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void OhmMsgTrack::Externalise(IWriter& aWriter)
{
    OhmHeader header(OhmHeader::kMsgTypeTrack, kHeaderBytes + iUri.Bytes() + iMetadata.Bytes());

    header.Externalise(aWriter);

    WriterBinary writer(aWriter);
    writer.WriteUint32Be(iSequence);
    writer.WriteUint32Be(iUri.Bytes());
    writer.WriteUint32Be(iMetadata.Bytes());
    writer.Write(iUri);
    writer.Write(iMetadata);

    aWriter.WriteFlush();
}


// OhmMsgMetatext

OhmMsgMetatext::OhmMsgMetatext(OhmMsgFactory& aFactory)
    : OhmMsg(aFactory)
{
}

void OhmMsgMetatext::Create(IReader& aReader, const OhmHeader& aHeader)
{
    OhmMsg::Create();

    ASSERT (aHeader.MsgType() == OhmHeader::kMsgTypeMetatext);
    
    ReaderBinary reader(aReader);
    iSequence = reader.ReadUintBe(4);
    TUint metatext = reader.ReadUintBe(4);
    reader.ReadReplace(metatext, iMetatext);
}

void OhmMsgMetatext::Create(TUint aSequence, const Brx& aMetatext)
{
    OhmMsg::Create();

    iSequence = aSequence;
    iMetatext.Replace(aMetatext);
}

TUint OhmMsgMetatext::Sequence() const
{
    return iSequence;
}

const Brx& OhmMsgMetatext::Metatext() const
{
    return iMetatext;
}

void OhmMsgMetatext::Process(IOhmMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void OhmMsgMetatext::Externalise(IWriter& aWriter)
{
    OhmHeaderMetatext headerMetatext(iSequence, iMetatext);
    
    OhmHeader header(OhmHeader::kMsgTypeMetatext, kHeaderBytes + iMetatext.Bytes());

    header.Externalise(aWriter);

    WriterBinary writer(aWriter);
    writer.WriteUint32Be(iSequence);
    writer.WriteUint32Be(iMetatext.Bytes());
    writer.Write(iMetatext);

    aWriter.WriteFlush();
}


// OhmMsgFactory

OhmMsgFactory::OhmMsgFactory(TUint aAudioCount, TUint aAudioBlobCount, TUint aTrackCount, TUint aMetatextCount)
    : iFifoAudio(aAudioCount)
    , iFifoAudioBlob(aAudioBlobCount)
    , iFifoTrack(aTrackCount)
    , iFifoMetatext(aMetatextCount)
{
    for (TUint i = 0; i < aAudioCount; i++) {
        iFifoAudio.Write(new OhmMsgAudio(*this));
    }
    for (TUint i = 0; i < aAudioBlobCount; i++) {
        iFifoAudioBlob.Write(new OhmMsgAudioBlob(*this));
    }
    for (TUint i = 0; i < aTrackCount; i++) {
        iFifoTrack.Write(new OhmMsgTrack(*this));
    }
    for (TUint i = 0; i < aMetatextCount; i++) {
        iFifoMetatext.Write(new OhmMsgMetatext(*this));
    }
}

OhmMsgFactory::~OhmMsgFactory()
{
    TUint slots = iFifoAudio.Slots();
    for (TUint i = 0; i < slots; i++) {
        delete iFifoAudio.Read();
    }
    slots = iFifoAudioBlob.Slots();
    for (TUint i = 0; i < slots; i++) {
        delete iFifoAudioBlob.Read();
    }
    slots = iFifoTrack.Slots();
    for (TUint i = 0; i < slots; i++) {
        delete iFifoTrack.Read();
    }
    slots = iFifoMetatext.Slots();
    for (TUint i = 0; i < slots; i++) {
        delete iFifoMetatext.Read();
    }
}

OhmMsg* OhmMsgFactory::Create(IReader& aReader, const OhmHeader& aHeader)
{
    switch (aHeader.MsgType())
    {
    case OhmHeader::kMsgTypeAudio:
        return CreateAudio(aReader, aHeader);
    case OhmHeader::kMsgTypeTrack:
        return CreateTrack(aReader, aHeader);
    case OhmHeader::kMsgTypeMetatext:
        return CreateMetatext(aReader, aHeader);
    default:
        ASSERTS();
    }

    return nullptr;
}

OhmMsgAudio* OhmMsgFactory::CreateAudio(IReader& aReader, const OhmHeader& aHeader)
{
    OhmMsgAudio* msg = iFifoAudio.Read();
    msg->Create(aReader, aHeader);
    return msg;
}

OhmMsgAudioBlob* OhmMsgFactory::CreateAudioBlob(IReader& aReader, const OhmHeader& aHeader)
{
    OhmMsgAudioBlob* msg = iFifoAudioBlob.Read();
    msg->Create(aReader, aHeader);
    return msg;
}

OhmMsgAudio* OhmMsgFactory::CreateAudioFromBlob(IReader& aReader, const OhmHeader& aHeader)
{
    OhmMsgAudio* msg = iFifoAudio.Read();
    OhmMsgAudioBlob::Create(*msg, aReader, aHeader);
    return msg;
}

OhmMsgTrack* OhmMsgFactory::CreateTrack(IReader& aReader, const OhmHeader& aHeader)
{
    OhmMsgTrack* msg = iFifoTrack.Read();
    msg->Create(aReader, aHeader);
    return msg;
}

OhmMsgMetatext* OhmMsgFactory::CreateMetatext(IReader& aReader, const OhmHeader& aHeader)
{
    OhmMsgMetatext* msg = iFifoMetatext.Read();
    msg->Create(aReader, aHeader);
    return msg;
}

OhmMsgAudio* OhmMsgFactory::CreateAudio(TBool aHalt, TBool aLossless, TBool aTimestamped, TBool aResent,
                                        TUint aSamples, TUint aFrame, TUint aNetworkTimestamp, TUint aMediaLatency,
                                        TUint64 aSampleStart, const Brx& aStreamHeader, const Brx& aAudio)
{
    OhmMsgAudio* msg = iFifoAudio.Read();
    msg->Create(aHalt, aLossless, aTimestamped, aResent, aSamples, aFrame, aNetworkTimestamp,
                aMediaLatency, aSampleStart, aStreamHeader, aAudio);
    return msg;
}

OhmMsgAudio* OhmMsgFactory::CreateAudio()
{
    OhmMsgAudio* msg = iFifoAudio.Read();
    msg->Create();
    return msg;
}

OhmMsgTrack* OhmMsgFactory::CreateTrack(TUint aSequence, const Brx& aUri, const Brx& aMetadata)
{
    OhmMsgTrack* msg = iFifoTrack.Read();
    msg->Create(aSequence, aUri, aMetadata);
    return msg;
}

OhmMsgMetatext* OhmMsgFactory::CreateMetatext(TUint aSequence, const Brx& aMetatext)
{
    OhmMsgMetatext* msg = iFifoMetatext.Read();
    msg->Create(aSequence, aMetatext);
    return msg;
}

void OhmMsgFactory::Destroy(OhmMsg& aMsg)
{
    aMsg.Process(*this);
}

void OhmMsgFactory::Process(OhmMsgAudio& aMsg)
{
    iFifoAudio.Write(&aMsg);
}

void OhmMsgFactory::Process(OhmMsgAudioBlob& aMsg)
{
    iFifoAudioBlob.Write(&aMsg);
}

void OhmMsgFactory::Process(OhmMsgTrack& aMsg)
{
    iFifoTrack.Write(&aMsg);
}

void OhmMsgFactory::Process(OhmMsgMetatext& aMsg)
{
    iFifoMetatext.Write(&aMsg);
}
