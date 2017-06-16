#include <OpenHome/Av/Scd/ScdMsg.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>

#include <atomic>
#include <string>
#include <utility>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Scd;

inline Brn BufferFromString(const std::string& aStr)
{
    Brn buf(reinterpret_cast<const TByte*>(aStr.data()),
            static_cast<TUint>(aStr.size()));
    return buf;
}

// ScdHeader

const Brn ScdHeader::kId("scd ");
const TUint ScdHeader::kHeaderBytes = 11;
const TUint ScdHeader::kTypeReady        = 0;
const TUint ScdHeader::kTypeMetadataDidl = 1;
const TUint ScdHeader::kTypeMetadataOh   = 2;
const TUint ScdHeader::kTypeFormat       = 3;
const TUint ScdHeader::kTypeAudio        = 5;
const TUint ScdHeader::kTypeMetatextDidl = 7;
const TUint ScdHeader::kTypeMetatextOh   = 8;
const TUint ScdHeader::kTypeHalt         = 9;
const TUint ScdHeader::kTypeDisconnect   = 10;
const TUint ScdHeader::kTypeSeek         = 11;
const TUint ScdHeader::kTypeSkip         = 12;

ScdHeader::ScdHeader()
{
}

ScdHeader::ScdHeader(TUint aMsgType, TUint aMsgBytes)
    : iType(aMsgType)
    , iBytes(aMsgBytes)
{
}

void ScdHeader::Internalise(IReader& aReader)
{
    ReaderBinary reader(aReader);
    Bws<4> scd;
    reader.ReadReplace(4, scd);
    if (scd != kId) {
        LOG2(kError, kScd, "SCD - bad header\n");
        THROW(ScdError);
    }
    iType  = reader.ReadUintBe(1);
    if (iType > kTypeSkip) {
        LOG2(kError, kScd, "SCD - unsupported type - %u\n", iType);
        THROW(ScdError);
    }
    iBytes = reader.ReadUintBe(2);
    if (iBytes < kHeaderBytes) {
        LOG2(kError, kScd, "SCD - corrupt header - (only %u bytes)\n", iBytes);
        THROW(ScdError);
    }
    (void)reader.ReadUintBe(4); // reserved, currently unused, bytes
}

void ScdHeader::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);
    writer.Write(kId);
    writer.WriteUint8(iType);
    writer.WriteUint16Be(iBytes);
    writer.WriteUint32Be(0); // reserved, currently unused, bytes
}


// ScdMsg

void ScdMsg::AddRef()
{
    iRefCount++;
}

void ScdMsg::RemoveRef()
{
    ASSERT(iRefCount != 0);
    TBool free = (--iRefCount == 0);
    if (free) {
        Clear();
        iAllocator.Free(*this);
    }
}

ScdMsg::ScdMsg(IScdMsgAllocator& aAllocator)
    : iAllocator(aAllocator)
    , iRefCount(0)
    , iNext(nullptr)
{
}

ScdMsg::~ScdMsg()
{
}

void ScdMsg::Initialise()
{
    iRefCount = 1;
}

void ScdMsg::ReadString(IReader& aReader, TUint aLenBytes, Bwx& aBuf)
{
    ReaderBinary rb(aReader);
    aBuf.Replace(Brx::Empty());
    const TUint bytes = rb.ReadUintBe(aLenBytes);
    ReaderProtocol::Read(aReader, bytes, aBuf);
}

void ScdMsg::Clear()
{
    ASSERT(iRefCount == 0);
    ASSERT(iNext == nullptr);
}


// AutoScdMsg

AutoScdMsg::AutoScdMsg(ScdMsg* aMsg)
    : iMsg(aMsg)
{
    ASSERT(iMsg != nullptr);
}

AutoScdMsg::~AutoScdMsg()
{
    iMsg->RemoveRef();
}


// ScdMsgReady

const TUint ScdMsgReady::kProtocolVersionMajor = 1;
const TUint ScdMsgReady::kProtocolVersionMinor = 0;

TUint ScdMsgReady::Major() const
{
    return iVersionMajor;
}

TUint ScdMsgReady::Minor() const
{
    return iVersionMinor;
}

ScdMsgReady::ScdMsgReady(IScdMsgAllocator& aAllocator)
    : ScdMsg(aAllocator)
{
}

void ScdMsgReady::Initialise()
{
    ScdMsg::Initialise();
    iVersionMajor = kProtocolVersionMajor;
    iVersionMinor = kProtocolVersionMinor;
}

void ScdMsgReady::Initialise(IReader& aReader, const ScdHeader& aHeader)
{
    ScdMsg::Initialise();
    ASSERT(aHeader.Type() == ScdHeader::kTypeReady);
    ReaderBinary reader(aReader);
    iVersionMajor = reader.ReadUintBe(2);
    iVersionMinor = reader.ReadUintBe(2);
}

void ScdMsgReady::Process(IScdMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void ScdMsgReady::Externalise(IWriter& aWriter) const
{
    const TUint bytes = ScdHeader::kHeaderBytes + 8; // +8 for 2* TUint
    ScdHeader header(ScdHeader::kTypeReady, bytes);
    header.Externalise(aWriter);

    WriterBinary writer(aWriter);
    writer.WriteUint16Be(iVersionMajor);
    writer.WriteUint16Be(iVersionMinor);
    
    aWriter.WriteFlush();
}

void ScdMsgReady::Clear()
{
    iVersionMajor = 0;
    iVersionMinor = 0;
}


// ScdMsgMetadataDidl

const Brx& ScdMsgMetadataDidl::Uri() const
{
    return iUri;
}

const Brx& ScdMsgMetadataDidl::Metadata() const
{
    return iMetadata;
}

ScdMsgMetadataDidl::ScdMsgMetadataDidl(IScdMsgAllocator& aAllocator)
    : ScdMsg(aAllocator)
{
}

void ScdMsgMetadataDidl::Initialise(const std::string& aUri, const std::string& aMetadata)
{
    ScdMsg::Initialise();
    iUri.ReplaceThrow(BufferFromString(aUri));
    iMetadata.ReplaceThrow(BufferFromString(aMetadata));
}

void ScdMsgMetadataDidl::Initialise(IReader& aReader, const ScdHeader& aHeader)
{
    ScdMsg::Initialise();
    ASSERT(aHeader.Type() == ScdHeader::kTypeMetadataDidl);
    ReadString(aReader, 2, iUri);
    ReadString(aReader, 2, iMetadata);
}

void ScdMsgMetadataDidl::Process(IScdMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void ScdMsgMetadataDidl::Externalise(IWriter& aWriter) const
{
    const TUint bytes = ScdHeader::kHeaderBytes +
                            2 + iUri.Bytes() +
                            2 + iMetadata.Bytes();
    ScdHeader header(ScdHeader::kTypeReady, bytes);
    header.Externalise(aWriter);

    WriterBinary writer(aWriter);
    writer.WriteUint16Be(iUri.Bytes());
    writer.Write(iUri);
    writer.WriteUint16Be(iMetadata.Bytes());
    writer.Write(iMetadata);

    aWriter.WriteFlush();
}

void ScdMsgMetadataDidl::Clear()
{
    iUri.Replace(Brx::Empty());
    iMetadata.Replace(Brx::Empty());
}


// ScdMsgKvp

ScdMsgKvp::ScdMsgKvp(IScdMsgAllocator& aAllocator)
    : ScdMsg(aAllocator)
{
}

void ScdMsgKvp::Initialise(const OpenHomeMetadata& aKvps)
{
    ScdMsg::Initialise();
    iBuf.SetBytes(0);
    const TByte* ptr = iBuf.Ptr();
    for (auto p : aKvps) {
        Brn key = BufferFromString(p.first);
        Brn val = BufferFromString(p.first);
        iBuf.Append(key);
        iBuf.Append(val);
        key.Set(ptr, key.Bytes());
        ptr += key.Bytes();
        val.Set(ptr, val.Bytes());
        ptr += val.Bytes();
        iKvps.push_back(std::pair<Brn, Brn>(key, val));
    }
}

void ScdMsgKvp::Initialise(IReader& aReader, TUint aBytes)
{
    ScdMsg::Initialise();
    iBuf.SetBytes(0);
    ReaderProtocolN rp(aReader, iBuf);
    Brn buf = rp.Read(aBytes);

    ReaderBuffer reader(buf);
    ReaderBinary rb(reader);
    const TUint count = rb.ReadUintBe(1);
    for (TUint i=0; i<count; i++) {
        const TUint keyBytes = rb.ReadUintBe(1);
        Brn key = reader.Read(keyBytes);
        const TUint valBytes = rb.ReadUintBe(2);
        Brn val = reader.Read(valBytes);
        iKvps.push_back(std::pair<Brn, Brn>(key, val));
    }
}

void ScdMsgKvp::DoExternalise(IWriter& aWriter, TUint aType) const
{
    TUint bytes = ScdHeader::kHeaderBytes;
    bytes += 1; // count of kvps
    for (auto p : iKvps) {
        bytes += 1 + p.first.Bytes() + 2 + p.second.Bytes();
    }
    ScdHeader header(aType, bytes);
    header.Externalise(aWriter);

    WriterBinary writer(aWriter);
    writer.WriteUint8((TUint)iKvps.size());
    for (auto p : iKvps) {
        writer.WriteUint8(p.first.Bytes());
        writer.Write(p.first);
        writer.WriteUint16Be(p.second.Bytes());
        writer.Write(p.second);
    }

    aWriter.WriteFlush();
}

void ScdMsgKvp::Clear()
{
    iKvps.clear();
    iBuf.Replace(Brx::Empty());
}


// ScdMsgMetadataOh

const OpenHomeMetadataBuf& ScdMsgMetadataOh::Metadata() const
{
    return iKvps;
}

ScdMsgMetadataOh::ScdMsgMetadataOh(IScdMsgAllocator& aAllocator)
    : ScdMsgKvp(aAllocator)
{
}

void ScdMsgMetadataOh::Initialise(IReader& aReader, const ScdHeader& aHeader)
{
    ASSERT(aHeader.Type() == ScdHeader::kTypeMetadataOh);
    ScdMsgKvp::Initialise(aReader, aHeader.Bytes());
}

void ScdMsgMetadataOh::Process(IScdMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void ScdMsgMetadataOh::Externalise(IWriter& aWriter) const
{
    DoExternalise(aWriter, ScdHeader::kTypeMetadataOh);
}


// ScdMsgFormat

TUint ScdMsgFormat::BitDepth() const
{
    return iBitDepth;
}

TUint ScdMsgFormat::SampleRate() const
{
    return iSampleRate;
}

TUint ScdMsgFormat::NumChannels() const
{
    return iNumChannels;
}

TUint ScdMsgFormat::BitRate() const
{
    return iBitRate;
}

TUint64 ScdMsgFormat::SampleStart() const
{
    return iSampleStart;
}

TUint64 ScdMsgFormat::SamplesTotal() const
{
    return iSamplesTotal;
}

TBool ScdMsgFormat::Seekable() const
{
    return iSeekable;
}

TBool ScdMsgFormat::Lossless() const
{
    return iLossless;
}

TBool ScdMsgFormat::Live() const
{
    return iLive;
}

TBool ScdMsgFormat::BroadcastAllowed() const
{
    return iBroadcastAllowed;
}

const Brx& ScdMsgFormat::CodecName() const
{
    return iCodecName;
}

ScdMsgFormat::ScdMsgFormat(IScdMsgAllocator& aAllocator)
    : ScdMsg(aAllocator)
{
}

void ScdMsgFormat::Initialise(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, TUint aBitRate,
                              TUint64 aSampleStart, TUint64 aSamplesTotal, TBool aSeekable, TBool aLossless,
                              TBool aLive, TBool aBroadcastAllowed, const std::string& aCodecName)
{
    DoInitialise(aBitDepth, aSampleRate, aNumChannels, aBitRate,
                 aSampleStart, aSamplesTotal, aSeekable, aLossless,
                 aLive, aBroadcastAllowed);
    iCodecName.Replace(BufferFromString(aCodecName));
}

void ScdMsgFormat::Initialise(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, TUint aBitRate,
                              TUint64 aSampleStart, TUint64 aSamplesTotal, TBool aSeekable, TBool aLossless,
                              TBool aLive, TBool aBroadcastAllowed, const Brx& aCodecName)
{
    DoInitialise(aBitDepth, aSampleRate, aNumChannels, aBitRate,
                 aSampleStart, aSamplesTotal, aSeekable, aLossless,
                 aLive, aBroadcastAllowed);
    iCodecName.Replace(aCodecName);
}

void ScdMsgFormat::DoInitialise(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, TUint aBitRate,
                                TUint64 aSampleStart, TUint64 aSamplesTotal, TBool aSeekable, TBool aLossless,
                                TBool aLive, TBool aBroadcastAllowed)
{
    ScdMsg::Initialise();
    switch (aBitDepth)
    {
    case 8:
    case 16:
    case 24:
        break;
    default:
        THROW(BitDepthNotSupported);
    }

    switch (aSampleRate)
    {
    case 7350:
    case 8000:
    case 11025:
    case 12000:
    case 14700:
    case 16000:
    case 22050:
    case 24000:
    case 29400:
    case 32000:
    case 44100:
    case 48000:
    case 88200:
    case 96000:
    case 176400:
    case 192000:
        break;
    default:
        THROW(SampleRateNotSupported);
    }

    iBitDepth         = aBitDepth;
    iSampleRate       = aSampleRate;
    iNumChannels      = aNumChannels;
    iBitRate          = aBitRate;
    iSampleStart      = aSampleStart;
    iSamplesTotal     = aSamplesTotal;
    iSeekable         = aSeekable;
    iLossless         = aLossless;
    iLive             = aLive;
    iBroadcastAllowed = aBroadcastAllowed;
}

void ScdMsgFormat::Initialise(IReader& aReader, const ScdHeader& aHeader)
{
    ScdMsg::Initialise();
    ASSERT(aHeader.Type() == ScdHeader::kTypeFormat);
    ReaderBinary rb(aReader);
    iBitDepth         = rb.ReadUintBe(1);
    iSampleRate       = rb.ReadUintBe(4);
    iNumChannels      = rb.ReadUintBe(1);
    iBitRate          = rb.ReadUintBe(4);
    iSampleStart      = rb.ReadUint64Be(8);
    iSamplesTotal     = rb.ReadUint64Be(8);
    const TUint flags = rb.ReadUintBe(1);
    iSeekable         = (flags & kFlagSeekable) != 0;
    iLossless         = (flags & kFlagLossless) != 0;
    iLive             = (flags & kFlagLive) != 0;
    iBroadcastAllowed = (flags & kFlagBroadcastable) != 0;
    ReadString(aReader, 1, iCodecName);
}

void ScdMsgFormat::Process(IScdMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void ScdMsgFormat::Externalise(IWriter& aWriter) const
{
    const TUint bytes = ScdHeader::kHeaderBytes + 28 + iCodecName.Bytes();
    ScdHeader header(ScdHeader::kTypeFormat, bytes);
    header.Externalise(aWriter);

    WriterBinary writer(aWriter);
    writer.WriteUint8(iBitDepth);
    writer.WriteUint32Be(iSampleRate);
    writer.WriteUint8(iNumChannels);
    writer.WriteUint32Be(iBitRate);
    writer.WriteUint64Be(iSampleStart);
    writer.WriteUint64Be(iSamplesTotal);
    TUint flags = 0;
    if (iSeekable) {
        flags |= kFlagSeekable;
    }
    if (iLossless) {
        flags |= kFlagLossless;
    }
    if (iLive) {
        flags |= kFlagLive;
    }
    if (iBroadcastAllowed) {
        flags |= kFlagBroadcastable;
    }
    writer.WriteUint8(flags);
    writer.WriteUint8(iCodecName.Bytes());
    writer.Write(iCodecName);

    aWriter.WriteFlush();
}

void ScdMsgFormat::Clear()
{
    iBitDepth         = 0;
    iSampleRate       = 0;
    iNumChannels      = 0;
    iBitRate          = 0;
    iSampleStart      = 0;
    iSamplesTotal     = 0;
    iSeekable         = false;
    iLossless         = false;
    iLive             = false;
    iBroadcastAllowed = false;
    iCodecName.Replace(Brx::Empty());
}


// ScdMsgAudio

TUint ScdMsgAudio::NumSamples() const
{
    return iNumSamples;
}

const Brx& ScdMsgAudio::Audio() const
{
    return iAudio;
}

ScdMsgAudio::ScdMsgAudio(IScdMsgAllocator& aAllocator)
    : ScdMsg(aAllocator)
{
}

void ScdMsgAudio::Initialise(const std::string& aAudio, TUint aNumSamples)
{
    ScdMsg::Initialise();
    iNumSamples = aNumSamples;
    iAudio.Replace(BufferFromString(aAudio));
}

void ScdMsgAudio::Initialise(IReader& aReader, const ScdHeader& aHeader)
{
    ScdMsg::Initialise();
    ASSERT(aHeader.Type() == ScdHeader::kTypeAudio);
    ReaderBinary rb(aReader);
    iNumSamples = rb.ReadUintBe(2);
    ReaderProtocol::Read(aReader, aHeader.Bytes() - 2, iAudio);
}

void ScdMsgAudio::Process(IScdMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void ScdMsgAudio::Externalise(IWriter& aWriter) const
{
    const TUint bytes = ScdHeader::kHeaderBytes + 2 + iAudio.Bytes();
    ScdHeader header(ScdHeader::kTypeAudio, bytes);
    header.Externalise(aWriter);

    WriterBinary writer(aWriter);
    writer.WriteUint16Be(iNumSamples);
    writer.Write(iAudio);

    aWriter.WriteFlush();
}

void ScdMsgAudio::Clear()
{
    iNumSamples = 0;
    iAudio.Replace(Brx::Empty());
}
    
    
// ScdMsgMetatext

const Brx& ScdMsgMetatextDidl::Metatext() const
{
    return iMetatext;
}

ScdMsgMetatextDidl::ScdMsgMetatextDidl(IScdMsgAllocator& aAllocator)
    : ScdMsg(aAllocator)
{
}

void ScdMsgMetatextDidl::Initialise(const std::string& aMetatext)
{
    ScdMsg::Initialise();
    iMetatext.Replace(BufferFromString(aMetatext));
}

void ScdMsgMetatextDidl::Initialise(IReader& aReader, const ScdHeader& aHeader)
{
    ScdMsg::Initialise();
    ASSERT(aHeader.Type() == ScdHeader::kTypeMetatextDidl);
    ReadString(aReader, 2, iMetatext);
}

void ScdMsgMetatextDidl::Process(IScdMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void ScdMsgMetatextDidl::Externalise(IWriter& aWriter) const
{
    const TUint bytes = ScdHeader::kHeaderBytes + 2 + iMetatext.Bytes();
    ScdHeader header(ScdHeader::kTypeMetatextDidl, bytes);
    header.Externalise(aWriter);

    WriterBinary writer(aWriter);
    writer.WriteUint16Be(iMetatext.Bytes());
    writer.Write(iMetatext);

    aWriter.WriteFlush();
}

void ScdMsgMetatextDidl::Clear()
{
    iMetatext.Replace(Brx::Empty());
}


// ScdMsgMetatextOh

const OpenHomeMetadataBuf& ScdMsgMetatextOh::Metatext() const
{
    return iKvps;
}

ScdMsgMetatextOh::ScdMsgMetatextOh(IScdMsgAllocator& aAllocator)
    : ScdMsgKvp(aAllocator)
{
}

void ScdMsgMetatextOh::Initialise(IReader& aReader, const ScdHeader& aHeader)
{
    ASSERT(aHeader.Type() == ScdHeader::kTypeMetadataOh);
    ScdMsgKvp::Initialise(aReader, aHeader.Bytes());
}

void ScdMsgMetatextOh::Process(IScdMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void ScdMsgMetatextOh::Externalise(IWriter& aWriter) const
{
    DoExternalise(aWriter, ScdHeader::kTypeMetatextOh);
}


// ScdMsgHalt

ScdMsgHalt::ScdMsgHalt(IScdMsgAllocator& aAllocator)
    : ScdMsg(aAllocator)
{
}

void ScdMsgHalt::Process(IScdMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void ScdMsgHalt::Externalise(IWriter& aWriter) const
{
    ScdHeader header(ScdHeader::kTypeHalt, ScdHeader::kHeaderBytes);
    header.Externalise(aWriter);
}


// ScdMsgDisconnect

ScdMsgDisconnect::ScdMsgDisconnect(IScdMsgAllocator& aAllocator)
    : ScdMsg(aAllocator)
{
}

void ScdMsgDisconnect::Process(IScdMsgProcessor& aProcessor)
{
    aProcessor.Process(*this);
}

void ScdMsgDisconnect::Externalise(IWriter& aWriter) const
{
    ScdHeader header(ScdHeader::kTypeDisconnect, ScdHeader::kHeaderBytes);
    header.Externalise(aWriter);
}

#if 0
class ScdMsgSeek
{
    friend class ScdMsgFactory;
private:
    ScdMsgSeek(IScdMsgAllocator& aAllocator);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
    void Clear() override;
};

class ScdMsgSkip
{
    friend class ScdMsgFactory;
private:
    ScdMsgSkip(IScdMsgAllocator& aAllocator);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
    void Clear() override;
};
#endif

// ScdMsgFactory

ScdMsgFactory::ScdMsgFactory(TUint aCountReady,
                             TUint aCountMetadataDidl,
                             TUint aCountMetadataOh,
                             TUint aCountFormat,
                             TUint aCountAudio,
                             TUint aCountMetatextDidl,
                             TUint aCountMetatextOh,
                             TUint aCountHalt,
                             TUint aCountDisconnect,
                             TUint /*aCountSeek*/,
                             TUint /*aCountSkip*/)
    : iFifoReady(nullptr)
    , iFifoMetadataDidl(nullptr)
    , iFifoMetadataOh(nullptr)
    , iFifoFormat(nullptr)
    , iFifoAudio(nullptr)
    , iFifoMetatextDidl(nullptr)
    , iFifoMetatextOh(nullptr)
    , iFifoHalt(nullptr)
    , iFifoDisconnect(nullptr)
{
    if (aCountReady != 0) {
        iFifoReady = new Fifo<ScdMsgReady*>(aCountReady);
        for (TUint i=0; i<aCountReady; i++) {
            iFifoReady->Write(new ScdMsgReady(*this));
        }
    }
    if (aCountMetadataDidl != 0){
        iFifoMetadataDidl = new Fifo<ScdMsgMetadataDidl*>(aCountMetadataDidl);
        for (TUint i=0; i<aCountMetadataDidl; i++) {
            iFifoMetadataDidl->Write(new ScdMsgMetadataDidl(*this));
        }
    }
    if (aCountMetadataOh != 0) {
        iFifoMetadataOh = new Fifo<ScdMsgMetadataOh*>(aCountMetadataOh);
        for (TUint i=0; i<aCountMetadataOh; i++) {
            iFifoMetadataOh->Write(new ScdMsgMetadataOh(*this));
        }
    }
    if (aCountFormat != 0) {
        iFifoFormat = new Fifo<ScdMsgFormat*>(aCountFormat);
        for (TUint i=0; i<aCountFormat; i++) {
            iFifoFormat->Write(new ScdMsgFormat(*this));
        }
    }
    if (aCountAudio != 0) {
        iFifoAudio = new Fifo<ScdMsgAudio*>(aCountAudio);
        for (TUint i=0; i<aCountAudio; i++) {
            iFifoAudio->Write(new ScdMsgAudio(*this));
        }
    }
    if (aCountMetatextDidl != 0) {
        iFifoMetatextDidl = new Fifo<ScdMsgMetatextDidl*>(aCountMetatextDidl);
        for (TUint i=0; i<aCountMetatextDidl; i++) {
            iFifoMetatextDidl->Write(new ScdMsgMetatextDidl(*this));
        }
    }
    if (aCountMetatextOh != 0) {
        iFifoMetatextOh = new Fifo<ScdMsgMetatextOh*>(aCountMetatextOh);
        for (TUint i=0; i<aCountMetatextOh; i++) {
            iFifoMetatextOh->Write(new ScdMsgMetatextOh(*this));
        }
    }
    if (aCountHalt != 0){
        iFifoHalt = new Fifo<ScdMsgHalt*>(aCountHalt);
        for (TUint i=0; i<aCountHalt; i++) {
            iFifoHalt->Write(new ScdMsgHalt(*this));
        }
    }
    if (aCountDisconnect != 0) {
        iFifoDisconnect = new Fifo<ScdMsgDisconnect*>(aCountDisconnect);
        for (TUint i=0; i<aCountDisconnect; i++) {
            iFifoDisconnect->Write(new ScdMsgDisconnect(*this));
        }
    }
}

ScdMsgFactory::~ScdMsgFactory()
{
    TUint slots = iFifoReady? iFifoReady->Slots() : 0;
    for (TUint i=0; i<slots; i++) {
        delete iFifoReady->Read();
    }
    slots = iFifoMetadataDidl? iFifoMetadataDidl->Slots() : 0;
    for (TUint i=0; i<slots; i++) {
        delete iFifoMetadataDidl->Read();
    }
    slots = iFifoMetadataOh? iFifoMetadataOh->Slots() : 0;
    for (TUint i=0; i<slots; i++) {
        delete iFifoMetadataOh->Read();
    }
    slots = iFifoFormat? iFifoFormat->Slots() : 0;
    for (TUint i=0; i<slots; i++) {
        delete iFifoFormat->Read();
    }
    slots = iFifoAudio? iFifoAudio->Slots() : 0;
    for (TUint i=0; i<slots; i++) {
        delete iFifoAudio->Read();
    }
    slots = iFifoMetatextDidl? iFifoMetatextDidl->Slots() : 0;
    for (TUint i=0; i<slots; i++) {
        delete iFifoMetatextDidl->Read();
    }
    slots = iFifoMetatextOh? iFifoMetatextOh->Slots() : 0;
    for (TUint i=0; i<slots; i++) {
        delete iFifoMetatextOh->Read();
    }
    slots = iFifoHalt? iFifoHalt->Slots() : 0;
    for (TUint i=0; i<slots; i++) {
        delete iFifoHalt->Read();
    }
    slots = iFifoDisconnect? iFifoDisconnect->Slots() : 0;
    for (TUint i=0; i<slots; i++) {
        delete iFifoDisconnect->Read();
    }
}

ScdMsgReady* ScdMsgFactory::CreateMsgReady()
{
    auto msg = iFifoReady->Read();
    msg->Initialise();
    return msg;
}

ScdMsgMetadataDidl* ScdMsgFactory::CreateMsgMetadataDidl(const std::string& aUri, const std::string& aMetadata)
{
    auto msg = iFifoMetadataDidl->Read();
    msg->Initialise(aUri, aMetadata);
    return msg;
}

ScdMsgMetadataOh* ScdMsgFactory::CreateMsgMetadataOh(const OpenHomeMetadata& aMetadata)
{
    auto msg = iFifoMetadataOh->Read();
    static_cast<ScdMsgKvp*>(msg)->Initialise(aMetadata);
    return msg;
}

ScdMsgFormat* ScdMsgFactory::CreateMsgFormat(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels,
                                             TUint aBitRate, TUint64 aSampleStart, TUint64 aSamplesTotal,
                                             TBool aSeekable, TBool aLossless, TBool aLive,
                                             TBool aBroadcastAllowed, const std::string& aCodecName)
{
    auto msg = iFifoFormat->Read();
    msg->Initialise(aBitDepth, aSampleRate, aNumChannels,
                    aBitRate, aSampleStart, aSamplesTotal,
                    aSeekable, aLossless, aLive,
                    aBroadcastAllowed, aCodecName);
    return msg;
}

ScdMsgFormat* ScdMsgFactory::CreateMsgFormat(ScdMsgFormat& aFormat, TUint64 aSampleStart)
{
    auto msg = iFifoFormat->Read();
    msg->Initialise(aFormat.BitDepth(), aFormat.SampleRate(), aFormat.NumChannels(),
                    aFormat.BitRate(), aSampleStart, aFormat.SamplesTotal(),
                    aFormat.Seekable(), aFormat.Lossless(), aFormat.Live(),
                    aFormat.BroadcastAllowed(), aFormat.CodecName());
    return msg;
}

ScdMsgAudio* ScdMsgFactory::CreateMsgAudio(const std::string& aAudio, TUint aNumSamples)
{
    auto msg = iFifoAudio->Read();
    msg->Initialise(aAudio, aNumSamples);
    return msg;
}

ScdMsgMetatextDidl* ScdMsgFactory::CreateMsgMetatextDidl(const std::string& aMetatext)
{
    auto msg = iFifoMetatextDidl->Read();
    msg->Initialise(aMetatext);
    return msg;
}

ScdMsgMetatextOh* ScdMsgFactory::CreateMsgMetatextOh(const OpenHomeMetadata& aMetatext)
{
    auto msg = iFifoMetatextOh->Read();
    static_cast<ScdMsgKvp*>(msg)->Initialise(aMetatext);
    return msg;
}

ScdMsgHalt* ScdMsgFactory::CreateMsgHalt()
{
    auto msg = iFifoHalt->Read();
    return msg;
}

ScdMsgDisconnect* ScdMsgFactory::CreateMsgDisconnect()
{
    auto msg = iFifoDisconnect->Read();
    return msg;
}

ScdMsg* ScdMsgFactory::CreateMsg(IReader& aReader)
{
    ScdHeader header;
    header.Internalise(aReader);
    ScdMsg* msg = nullptr;
    switch (header.Type())
    {
    case ScdHeader::kTypeReady:
        msg = CreateMsgReady(aReader, header);
        break;
    case ScdHeader::kTypeMetadataDidl:
        msg = CreateMsgMetadataDidl(aReader, header);
        break;
    case ScdHeader::kTypeMetadataOh:
        msg = CreateMsgMetadataOh(aReader, header);
        break;
    case ScdHeader::kTypeFormat:
        msg = CreateMsgFormat(aReader, header);
        break;
    case ScdHeader::kTypeAudio:
        msg = CreateMsgAudio(aReader, header);
        break;
    case ScdHeader::kTypeMetatextDidl:
        msg = CreateMsgMetatextDidl(aReader, header);
        break;
    case ScdHeader::kTypeMetatextOh:
        msg = CreateMsgMetatextOh(aReader, header);
        break;
    case ScdHeader::kTypeHalt:
        msg = CreateMsgHalt(aReader, header);
        break;
    case ScdHeader::kTypeDisconnect:
        msg = CreateMsgDisconnect(aReader, header);
        break;
    default:
        THROW(ScdError); // unknown msg type, assume this implies an unsupported protocol version
        break;
    }
    return msg;
}

ScdMsgReady* ScdMsgFactory::CreateMsgReady(IReader& aReader, const ScdHeader& aHeader)
{
    auto msg = iFifoReady->Read();
    try {
        msg->Initialise(aReader, aHeader);
    }
    catch (...) {
        msg->RemoveRef();
        throw;
    }
    return msg;
}

ScdMsgMetadataDidl* ScdMsgFactory::CreateMsgMetadataDidl(IReader& aReader, const ScdHeader& aHeader)
{
    auto msg = iFifoMetadataDidl->Read();
    try {
        msg->Initialise(aReader, aHeader);
    }
    catch (...) {
        msg->RemoveRef();
        throw;
    }
    return msg;
}

ScdMsgMetadataOh* ScdMsgFactory::CreateMsgMetadataOh(IReader& aReader, const ScdHeader& aHeader)
{
    auto msg = iFifoMetadataOh->Read();
    try {
        msg->Initialise(aReader, aHeader);
    }
    catch (...) {
        msg->RemoveRef();
        throw;
    }
    return msg;
}

ScdMsgFormat* ScdMsgFactory::CreateMsgFormat(IReader& aReader, const ScdHeader& aHeader)
{
    auto msg = iFifoFormat->Read();
    try {
        msg->Initialise(aReader, aHeader);
    }
    catch (...) {
        msg->RemoveRef();
        throw;
    }
    return msg;
}

ScdMsgAudio* ScdMsgFactory::CreateMsgAudio(IReader& aReader, const ScdHeader& aHeader)
{
    auto msg = iFifoAudio->Read();
    try {
        msg->Initialise(aReader, aHeader);
    }
    catch (...) {
        msg->RemoveRef();
        throw;
    }
    return msg;
}

ScdMsgMetatextDidl* ScdMsgFactory::CreateMsgMetatextDidl(IReader& aReader, const ScdHeader& aHeader)
{
    auto msg = iFifoMetatextDidl->Read();
    try {
        msg->Initialise(aReader, aHeader);
    }
    catch (...) {
        msg->RemoveRef();
        throw;
    }
    return msg;
}

ScdMsgMetatextOh* ScdMsgFactory::CreateMsgMetatextOh(IReader& aReader, const ScdHeader& aHeader)
{
    auto msg = iFifoMetatextOh->Read();
    try {
        msg->Initialise(aReader, aHeader);
    }
    catch (...) {
        msg->RemoveRef();
        throw;
    }
    return msg;
}

ScdMsgHalt* ScdMsgFactory::CreateMsgHalt(IReader& /*aReader*/, const ScdHeader& /*aHeader*/)
{
    auto msg = iFifoHalt->Read();
    return msg;
}

ScdMsgDisconnect* ScdMsgFactory::CreateMsgDisconnect(IReader& /*aReader*/, const ScdHeader& /*aHeader*/)
{
    auto msg = iFifoDisconnect->Read();
    return msg;
}

//    ScdMsgSeek* CreateMsgSeek();
//    ScdMsgSkip* CreateMsgSkip();

void ScdMsgFactory::Free(ScdMsg& aMsg)
{
    aMsg.Process(*this);
}

void ScdMsgFactory::Process(ScdMsgReady& aMsg)
{
    iFifoReady->Write(&aMsg);
}

void ScdMsgFactory::Process(ScdMsgMetadataDidl& aMsg)
{
    iFifoMetadataDidl->Write(&aMsg);
}

void ScdMsgFactory::Process(ScdMsgMetadataOh& aMsg)
{
    iFifoMetadataOh->Write(&aMsg);
}

void ScdMsgFactory::Process(ScdMsgFormat& aMsg)
{
    iFifoFormat->Write(&aMsg);
}

void ScdMsgFactory::Process(ScdMsgAudio& aMsg)
{
    iFifoAudio->Write(&aMsg);
}

void ScdMsgFactory::Process(ScdMsgMetatextDidl& aMsg)
{
    iFifoMetatextDidl->Write(&aMsg);
}

void ScdMsgFactory::Process(ScdMsgMetatextOh& aMsg)
{
    iFifoMetatextOh->Write(&aMsg);
}

void ScdMsgFactory::Process(ScdMsgHalt& aMsg)
{
    iFifoHalt->Write(&aMsg);
}

void ScdMsgFactory::Process(ScdMsgDisconnect& aMsg)
{
    iFifoDisconnect->Write(&aMsg);
}

void ScdMsgFactory::Process(ScdMsgSeek& /*aMsg*/)
{
    ASSERTS();
}

void ScdMsgFactory::Process(ScdMsgSkip& /*aMsg*/)
{
    ASSERTS();
}


// ScdMsgQueue

ScdMsgQueue::ScdMsgQueue()
    : iLock("SCDQ")
    , iSem("SCDQ", 0)
    , iHead(nullptr)
    , iTail(nullptr)
    , iNumMsgs(0)
{
}

ScdMsgQueue::~ScdMsgQueue()
{
    auto head = iHead;
    while (head != nullptr) {
        iHead = head->iNext;
        head->RemoveRef();
        head = iHead;
    }
}

void ScdMsgQueue::Enqueue(ScdMsg* aMsg)
{
    AutoMutex _(iLock);
    if (iHead == nullptr) {
        iHead = aMsg;
    }
    else {
        iTail->iNext = aMsg;
    }
    iTail = aMsg;
    iNumMsgs++;
    iSem.Signal();
}

ScdMsg* ScdMsgQueue::Dequeue()
{
    iSem.Wait();
    AutoMutex _(iLock);
    ASSERT(iHead != nullptr);
    auto head = iHead;
    iHead = iHead->iNext;
    head->iNext = nullptr; // not strictly necessary but might make debugging simpler
    if (iHead == nullptr) {
        iTail = nullptr;
    }
    iNumMsgs--;
    return head;
}

void ScdMsgQueue::EnqueueAtHead(ScdMsg* aMsg)
{
    AutoMutex _(iLock);
    ASSERT(aMsg != nullptr);
    aMsg->iNext = iHead;
    iHead = aMsg;
    if (iTail == nullptr) {
        iTail = aMsg;
    }
    iNumMsgs++;
    iSem.Signal();
}

TBool ScdMsgQueue::IsEmpty() const
{
    AutoMutex _(iLock);
    const TBool empty = (iHead == nullptr);
    return empty;
}

void ScdMsgQueue::Clear()
{
    AutoMutex _(iLock);
    auto msg = iHead;
    while (msg != nullptr) {
        auto next = msg->iNext;
        msg->RemoveRef();
        msg = next;
    }
    (void)iSem.Clear();
}

TUint ScdMsgQueue::NumMsgs() const
{
    AutoMutex _(iLock);
    return iNumMsgs;
}
