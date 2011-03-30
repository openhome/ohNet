#include "Ohm.h"

using namespace Zapp;

// OhmSocket

OhmSocket::OhmSocket()
    : iSocket(0)
{
}

void OhmSocket::OpenUnicast(TIpAddress aInterface, TUint aTtl)
{
    ASSERT(!iSocket);
    iSocket = new SocketUdp(0, aInterface);
    iSocket->SetTtl(aTtl);
    iSocket->SetSendBufBytes(kSendBufBytes);
    iReader = new UdpReader(*iSocket);
    iThis.Replace(Endpoint(iSocket->Port(), aInterface));
}

void OhmSocket::OpenMulticast(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint)
{
    ASSERT(!iSocket);
    iSocket = new SocketUdpMulticast(aInterface, aEndpoint);
    iSocket->SetTtl(aTtl);
    iSocket->SetSendBufBytes(kSendBufBytes);
    iReader = new UdpReader(*iSocket);
    iThis.Replace(aEndpoint);
}

void OhmSocket::Send(const Brx& aBuffer, const Endpoint& aEndpoint)
{
    ASSERT(iSocket);
    iSocket->Send(aBuffer, aEndpoint);
}

Endpoint OhmSocket::This() const
{
    ASSERT(iSocket);
    return (iThis);
}

Endpoint OhmSocket::Sender() const
{
    ASSERT(iReader);
    return (iReader->Sender());
}

void OhmSocket::Close()
{
    ASSERT(iSocket);
    delete (iReader);
    delete (iSocket);
    iReader = 0;
    iSocket = 0;
}
    
void OhmSocket::Read(Bwx& aBuffer)
{
    ASSERT(iSocket);
    iReader->Read(aBuffer);
}

void OhmSocket::ReadFlush()
{
    ASSERT(iSocket != 0);
    iReader->ReadFlush();
}

void OhmSocket::ReadInterrupt()
{
    ASSERT(iSocket != 0);
    iReader->ReadInterrupt();
}

OhmSocket::~OhmSocket()
{
    if (iSocket != 0) {
        Close();
    }
}


////////////////////////////////////////////////////////
// OHM Protocol                        
    


// OhmHeader

const Brn OhmHeader::kOhm("Ohm ");

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

    Brn ohm = reader.Read(4);
    
    if(ohm != kOhm) {
        THROW(OhmError);
    }

    TUint major = reader.ReadUintBe(1);

    if(major != kMajor) {
        THROW(OhmError);
    }

    iMsgType  = reader.ReadUintBe(1);

    if(iMsgType > kMsgTypeMetatext) {
        THROW(OhmError);
    }

    iBytes = reader.ReadUintBe(2);
    
    if (iBytes < kHeaderBytes) {
        THROW(OhmError);
    }
}

void OhmHeader::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.Write(kOhm);
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
                               TBool aSync,
                               TUint aSamples,
                               TUint aFrame,
                               TUint aTxTimestampPrev,
                               TUint aSyncTimestamp,
                               TUint64 aSampleStart,
                               TUint64 aSamplesTotal,
                               TUint aSampleRate,
                               TUint aBitRate,
                               TUint aVolumeOffset,
                               TUint aBitDepth,
                               TUint aChannels,
                               const Brx& aCodecName)
    : iHalt(aHalt)
    , iLossless(aLossless)
    , iSync(aSync)
    , iSamples(aSamples)
    , iFrame(aFrame)
    , iTxTimestampPrev(aTxTimestampPrev)
    , iSyncTimestamp(aSyncTimestamp)
    , iSampleStart(aSampleStart)
    , iSamplesTotal(aSamplesTotal)
    , iSampleRate(aSampleRate)
    , iBitRate(aBitRate)
    , iVolumeOffset(aVolumeOffset)
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
        THROW(OhmError);
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
    iSyncTimestamp = readerBinary.ReadUintBe(4);
    iSampleStart = readerBinary.ReadUint64Be(8);
    iSamplesTotal = readerBinary.ReadUint64Be(8);
    iSampleRate = readerBinary.ReadUintBe(4);
    iBitRate = readerBinary.ReadUintBe(4);
    iVolumeOffset = readerBinary.ReadIntBe(2);
    iBitDepth = readerBinary.ReadUintBe(1);
    iChannels = readerBinary.ReadUintBe(1);
    
    TUint reserved = readerBinary.ReadUintBe(1);
    
    if(reserved != kReserved) {
        THROW(OhmError);
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
    writer.WriteUint32Be(iSyncTimestamp);
    writer.WriteUint64Be(iSampleStart);
    writer.WriteUint64Be(iSamplesTotal);
    writer.WriteUint32Be(iSampleRate);
    writer.WriteUint32Be(iBitRate);
    writer.WriteInt16Be(iVolumeOffset);
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
    
// OhmHeaderSlave

OhmHeaderSlave::OhmHeaderSlave()
{
}

OhmHeaderSlave::OhmHeaderSlave(TUint aSlaveCount)
    : iSlaveCount(aSlaveCount)
{
}
    
void OhmHeaderSlave::Internalise(IReader& aReader, const OhmHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhmHeader::kMsgTypeSlave);
    
    ReaderBinary readerBinary(aReader);

    iSlaveCount = readerBinary.ReadUintBe(4);
}

void OhmHeaderSlave::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.WriteUint32Be(iSlaveCount);
}
    
    

////////////////////////////////////////////////////////
// OHZ Protocol                        
    
    
// OhzHeader

const Brn OhzHeader::kOhz("Ohz ");

OhzHeader::OhzHeader()
    : iMsgType(kMsgTypeQuery)
    , iBytes(kHeaderBytes)
{
}

OhzHeader::OhzHeader(TUint aMsgType, TUint aMsgBytes)
    : iMsgType(aMsgType)
    , iBytes(kHeaderBytes + aMsgBytes)
{
}

void OhzHeader::Internalise(IReader& aReader)
{
    ReaderBinary reader(aReader);

    Brn ohz = reader.Read(4);

    if(ohz != kOhz) {
        THROW(OhzError);
    }

    TUint major = reader.ReadUintBe(1);

    if(major != kMajor) {
        THROW(OhzError);
    }

    iMsgType  = reader.ReadUintBe(1);

    if(iMsgType > kMsgTypeUri) {
        THROW(OhzError);
    }

    iBytes = reader.ReadUintBe(2);
    
    if (iBytes < kHeaderBytes) {
        THROW(OhzError);
    }
}

void OhzHeader::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.Write(kOhz);
    writer.WriteUint8(kMajor);
    writer.WriteUint8(iMsgType);
    writer.WriteUint16Be(iBytes);
}

// OhzHeaderUri

OhzHeaderUri::OhzHeaderUri()
{
}

OhzHeaderUri::OhzHeaderUri(const Brx& aZone, const Brx& aUri)
{
    iZoneBytes = aZone.Bytes();
    iUriBytes = aUri.Bytes();
}

void OhzHeaderUri::Internalise(IReader& aReader, const OhzHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhzHeader::kMsgTypeUri);
    
    ReaderBinary readerBinary(aReader);

    iZoneBytes = readerBinary.ReadUintBe(4);
    iUriBytes = readerBinary.ReadUintBe(4);
}

void OhzHeaderUri::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.WriteUint32Be(iZoneBytes);
    writer.WriteUint32Be(iUriBytes);
}

// OhzHeaderQuery

OhzHeaderQuery::OhzHeaderQuery()
{
}
    
OhzHeaderQuery::OhzHeaderQuery(const Brx& aQuery)
{
    iZoneBytes = aQuery.Bytes();
}

void OhzHeaderQuery::Internalise(IReader& aReader, const OhzHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhzHeader::kMsgTypeQuery);
    
    ReaderBinary readerBinary(aReader);

    iZoneBytes = readerBinary.ReadUintBe(4);
}

void OhzHeaderQuery::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.WriteUint32Be(iZoneBytes);
}
    
    
    