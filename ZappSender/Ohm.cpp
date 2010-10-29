#include "Ohm.h"

using namespace Zapp;

namespace Zapp
{

	class ReaderBinary 
	{
	public:
	    ReaderBinary(IReader& aReader);
	    const Brn Read(TUint aBytes);
	    TUint ReadUintBe(TUint aBytes);
	    TUint ReadUintLe(TUint aBytes);
	    TUint64 ReadUint64Be(TUint aBytes);
	    TUint64 ReadUint64Le(TUint aBytes);
	private:
	    IReader& iReader;
	};
	
	class WriterBinary
	{
	public:
	    WriterBinary(IWriter& aWriter);
	    void Write(const Brx& aBuffer);
	    void WriteUint8(TUint8 aValue);
	    void WriteUint16Be(TUint16 aValue);
	    void WriteUint24Be(TUint32 aValue);
	    void WriteUint32Be(TUint32 aValue);
	    void WriteUint64Be(TUint64 aValue);
	private:
	    IWriter& iWriter;
	};

}

// ReaderBinary

ReaderBinary::ReaderBinary(IReader& aReader)
    : iReader(aReader)
{
}

const Brn ReaderBinary::Read(TUint aBytes)
{
    return iReader.Read(aBytes);    
}

TUint ReaderBinary::ReadUintBe(TUint aBytes)
{
    ASSERT(aBytes <= sizeof(TUint));
    TUint val = 0;
    TUint count = 0;
    while(count < aBytes) {
        TUint byte = iReader.Read(1).At(0);
        val += byte << ((aBytes - count - 1)*8);
        count++;
    }
    return val;
}

TUint ReaderBinary::ReadUintLe(TUint aBytes)
{
    ASSERT(aBytes <= sizeof(TUint));
    TUint val = 0;
    TUint shift = 0;
    while(shift < aBytes) {
        TUint byte = iReader.Read(1).At(0);
        val += byte << (shift*8);
        shift++;
    }
    return val;
}

TUint64 ReaderBinary::ReadUint64Be(TUint aBytes)
{
    ASSERT(aBytes <= sizeof(TUint64));
    TUint64 val = 0;
    TUint count = 0;
    while(count < aBytes) {
        TUint byte = iReader.Read(1).At(0);
        val += byte << ((aBytes - count - 1)*8);
        count++;
    }
    return val;
}

TUint64 ReaderBinary::ReadUint64Le(TUint aBytes)
{
    ASSERT(aBytes <= sizeof(TUint64));
    TUint64 val = 0;
    TUint shift = 0;
    while(shift < aBytes) {
        TUint byte = iReader.Read(1).At(0);
        val += byte << (shift*8);
        shift++;
    }
    return val;
}

// WriterBinary

WriterBinary::WriterBinary(IWriter& aWriter)
    : iWriter(aWriter)
{
}

void WriterBinary::Write(const Brx& aBuf)
{
    iWriter.Write(aBuf);
}

void WriterBinary::WriteUint8(TUint8 aValue)
{
    iWriter.Write(aValue);
}

void WriterBinary::WriteUint16Be(TUint16 aValue)
{
    iWriter.Write(aValue >> 8);
    iWriter.Write(aValue);
}

void WriterBinary::WriteUint24Be(TUint aValue)
{
    iWriter.Write(aValue >> 16);
    iWriter.Write(aValue >> 8);
    iWriter.Write(aValue);
}

void WriterBinary::WriteUint32Be(TUint aValue)
{
    iWriter.Write(aValue >> 24);
    iWriter.Write(aValue >> 16);
    iWriter.Write(aValue >> 8);
    iWriter.Write(aValue);
}

void WriterBinary::WriteUint64Be(TUint64 aValue)
{
    iWriter.Write(aValue >> 56);
    iWriter.Write(aValue >> 48);
    iWriter.Write(aValue >> 40);
    iWriter.Write(aValue >> 32);
    iWriter.Write(aValue >> 24);
    iWriter.Write(aValue >> 16);
    iWriter.Write(aValue >> 8);
    iWriter.Write(aValue);
}

const Brn OhmHeader::kMpus("Mpus");

// OhmHeader

OhmHeader::OhmHeader()
    : iMsgType(kMsgTypeJoin)
    , iBytes(kHeaderBytes)
{
}

OhmHeader::OhmHeader(TUint aMsgType, TUint aMsgBytes)
    : iMsgType(aMsgType)
    , iBytes(kHeaderBytes + aMsgBytes)
{
}

void OhmHeader::Internalise(IReader& aReader)
{
    ReaderBinary reader(aReader);

    Brn mpus = reader.Read(4);

    if(mpus != kMpus) {
        THROW(OhmHeaderInvalid);
    }

    TUint major = reader.ReadUintBe(1);

    if(major != kMajor) {
        THROW(OhmHeaderInvalid);
    }

    iMsgType  = reader.ReadUintBe(1);

    if(iMsgType > kMsgTypeMetatext) {
        THROW(OhmHeaderInvalid);
    }

    iBytes = reader.ReadUintBe(2);
    
    if (iBytes < kHeaderBytes) {
        THROW(OhmHeaderInvalid);
    }
}

void OhmHeader::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.Write(kMpus);
    writer.WriteUint8(kMajor);
    writer.WriteUint8(iMsgType);
    writer.WriteUint16Be(iBytes);
}

// OhmMsgAudio


OhmHeaderAudio::OhmHeaderAudio()
{
}

OhmHeaderAudio::OhmHeaderAudio(TBool aHalt, 
                               TBool aLossless,
                               TUint aSamples,
                               TUint aFrame,
                               TUint aTxTimestampPrev,
                               TUint64 aSampleStart,
                               TUint64 aSamplesTotal,
                               TUint aSampleRate,
                               TUint aBitRate,
                               TUint aBitDepth,
                               TUint aChannels,
                               const Brx& aCodecName)
    : iHalt(aHalt)
    , iLossless(aLossless)
    , iSamples(aSamples)
    , iFrame(aFrame)
    , iTxTimestampPrev(aTxTimestampPrev)
    , iSampleStart(aSampleStart)
    , iSamplesTotal(aSamplesTotal)
    , iSampleRate(aSampleRate)
    , iBitRate(aBitRate)
    , iBitDepth(aBitDepth)
    , iChannels(aChannels)
    , iCodecName(aCodecName)
{
    iAudioBytes = iSamples * iBitDepth * iChannels / 8;
}
    

void OhmHeaderAudio::Internalise(IReader& aReader, const OhmHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhmHeader::kMsgTypeAudio);
    
    ReaderBinary readerBinary(aReader);

    TUint headerBytes = readerBinary.ReadUintBe(1);

    if (headerBytes != kHeaderBytes) {
        THROW(OhmHeaderInvalid);
    }

    iHalt = false;
    iLossless = false;

    TUint flags = readerBinary.ReadUintBe(1);
    
    if (flags & kFlagHalt) {
        iHalt = true;
    }

    if (flags & kFlagLossless) {
        iLossless = true;
    }

    iSamples = readerBinary.ReadUintBe(2);
    iFrame = readerBinary.ReadUintBe(4);
    iTxTimestampPrev = readerBinary.ReadUintBe(4);
    iSampleStart = readerBinary.ReadUint64Be(8);
    iSamplesTotal = readerBinary.ReadUint64Be(8);
    iSampleRate = readerBinary.ReadUintBe(4);
    iBitRate = readerBinary.ReadUintBe(4);
    iBitDepth = readerBinary.ReadUintBe(1);
    iChannels = readerBinary.ReadUintBe(1);
    
    TUint reserved = readerBinary.ReadUintBe(1);
    
    if(reserved != kReserved) {
        THROW(OhmHeaderInvalid);
    }
    
    TUint bytes = readerBinary.ReadUintBe(1);
    
    if(bytes > 0) {
        iCodecName.Replace(aReader.Read(bytes));
    }
    else {
        iCodecName.Replace(Brx::Empty());
    }
    
    iAudioBytes = aHeader.MsgBytes() - kHeaderBytes - iCodecName.Bytes();
}

void OhmHeaderAudio::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    TUint flags = 0;
    
    if (iHalt) {
        flags |= kFlagHalt;
    }
    
    if (iLossless) {
        flags |= kFlagLossless;
    }
    
    writer.WriteUint8(kHeaderBytes);
    writer.WriteUint8(flags);
    writer.WriteUint16Be(iSamples);
    writer.WriteUint32Be(iFrame);
    writer.WriteUint32Be(iTxTimestampPrev);
    writer.WriteUint64Be(iSampleStart);
    writer.WriteUint64Be(iSamplesTotal);
    writer.WriteUint32Be(iSampleRate);
    writer.WriteUint32Be(iBitRate);
    writer.WriteUint8(iBitDepth);
    writer.WriteUint8(iChannels);
    writer.WriteUint8(kReserved);
    
    TUint bytes = iCodecName.Bytes();
    
    writer.WriteUint8(bytes);
    
    if (bytes > 0) {
        aWriter.Write(iCodecName);
    }
}

// OhmHeaderTrack

OhmHeaderTrack::OhmHeaderTrack()
{
}

OhmHeaderTrack::OhmHeaderTrack(const Brx& aUri, const Brx& aMetadata)
{
    iUriBytes = aUri.Bytes();
    iMetadataBytes = aMetadata.Bytes();
}

void OhmHeaderTrack::Internalise(IReader& aReader, const OhmHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhmHeader::kMsgTypeTrack);
    
    ReaderBinary readerBinary(aReader);

    iUriBytes = readerBinary.ReadUintBe(4);
    iMetadataBytes = readerBinary.ReadUintBe(4);
}

void OhmHeaderTrack::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.WriteUint32Be(iUriBytes);
    writer.WriteUint32Be(iMetadataBytes);
}

// OhmHeaderMetatext

OhmHeaderMetatext::OhmHeaderMetatext()
{
}
    
OhmHeaderMetatext::OhmHeaderMetatext(const Brx& aMetatext)
{
    iMetatextBytes = aMetatext.Bytes();
}

void OhmHeaderMetatext::Internalise(IReader& aReader, const OhmHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhmHeader::kMsgTypeMetatext);
    
    ReaderBinary readerBinary(aReader);

    iMetatextBytes = readerBinary.ReadUintBe(4);
}

void OhmHeaderMetatext::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.WriteUint32Be(iMetatextBytes);
}
    
