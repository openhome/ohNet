#include "Ohm.h"

using namespace OpenHome;
using namespace OpenHome::Net;

// OhmSocket

OhmSocket::OhmSocket()
    : iRxSocket(0)
	, iTxSocket(0)
	, iReader(0)
{
}

void OhmSocket::OpenUnicast(TIpAddress aInterface, TUint aTtl)
{
    ASSERT(!iRxSocket);
    ASSERT(!iTxSocket);
    ASSERT(!iReader);
    iRxSocket = new SocketUdp(0, aInterface);
	iTxSocket = new SocketUdp(0, aInterface);
    iTxSocket->SetTtl(aTtl);
    iTxSocket->SetSendBufBytes(kSendBufBytes);
    iReader = new UdpReader(*iRxSocket);
    iThis.Replace(Endpoint(iRxSocket->Port(), aInterface));
}

void OhmSocket::OpenMulticast(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint)
{
    ASSERT(!iRxSocket);
    ASSERT(!iTxSocket);
    ASSERT(!iReader);
    iRxSocket = new SocketUdpMulticast(aInterface, aEndpoint);
	iTxSocket = new SocketUdp(0, aInterface);
    iTxSocket->SetTtl(aTtl);
    iTxSocket->SetSendBufBytes(kSendBufBytes);
    iReader = new UdpReader(*iRxSocket);
    iThis.Replace(aEndpoint);
}

void OhmSocket::Send(const Brx& aBuffer, const Endpoint& aEndpoint)
{
    ASSERT(iTxSocket);
    iTxSocket->Send(aBuffer, aEndpoint);
}

Endpoint OhmSocket::This() const
{
    return (iThis);
}

Endpoint OhmSocket::Sender() const
{
    ASSERT(iReader);
    return (iReader->Sender());
}

void OhmSocket::Close()
{
    ASSERT(iRxSocket);
    ASSERT(iTxSocket);
    ASSERT(iReader);
    delete (iRxSocket);
    delete (iTxSocket);
    delete (iReader);
    iRxSocket = 0;
    iTxSocket = 0;
    iReader = 0;
}
    
void OhmSocket::Read(Bwx& aBuffer)
{
    ASSERT(iReader);
    iReader->Read(aBuffer);
}

void OhmSocket::ReadFlush()
{
    ASSERT(iReader);
    iReader->ReadFlush();
}

void OhmSocket::ReadInterrupt()
{
    ASSERT(iReader);
    iReader->ReadInterrupt();
}

OhmSocket::~OhmSocket()
{
    if (iRxSocket != 0) {
        Close();
    }
}


// OhzSocket

OhzSocket::OhzSocket()
	: iRxSocket(0)
	, iTxSocket(0)
	, iEndpoint(51972, Brn("239.255.255.250"))
{
}

void OhzSocket::Open(TIpAddress aInterface, TUint aTtl)
{
    ASSERT(!iRxSocket);
    iRxSocket = new SocketUdpMulticast(aInterface, iEndpoint);
	iTxSocket = new SocketUdp(0, aInterface);
    iTxSocket->SetTtl(aTtl);
    iReader = new UdpReader(*iRxSocket);
}

void OhzSocket::Send(const Brx& aBuffer)
{
    ASSERT(iTxSocket);
    iTxSocket->Send(aBuffer, iEndpoint);
}

void OhzSocket::Close()
{
    ASSERT(iRxSocket);
    delete (iRxSocket);
	delete (iTxSocket);
    delete (iReader);
    iRxSocket = 0;
	iTxSocket = 0;
    iReader = 0;
}
    
void OhzSocket::Read(Bwx& aBuffer)
{
    ASSERT(iRxSocket);
    iReader->Read(aBuffer);
}

void OhzSocket::ReadFlush()
{
    ASSERT(iRxSocket != 0);
    iReader->ReadFlush();
}

void OhzSocket::ReadInterrupt()
{
    ASSERT(iRxSocket != 0);
    iReader->ReadInterrupt();
}

OhzSocket::~OhzSocket()
{
    if (iRxSocket != 0) {
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
                               TUint aSamples,
                               TUint aFrame,
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
    , iTimestamped(false)
    , iSamples(aSamples)
    , iFrame(aFrame)
    , iNetworkTimestamp(0)
    , iMediaLatency(0)
    , iMediaTimestamp(0)
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
    
OhmHeaderAudio::OhmHeaderAudio(TBool aHalt, 
                               TBool aLossless,
                               TUint aSamples,
                               TUint aFrame,
                               TUint aNetworkTimestamp,
                               TUint aMediaLatency,
                               TUint aMediaTimestamp,
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
    , iTimestamped(true)
    , iSamples(aSamples)
    , iFrame(aFrame)
    , iNetworkTimestamp(aNetworkTimestamp)
    , iMediaLatency(aMediaLatency)
    , iMediaTimestamp(aMediaTimestamp)
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
    iNetworkTimestamp = readerBinary.ReadUintBe(4);
    iMediaLatency = readerBinary.ReadUintBe(4);
    iMediaTimestamp = readerBinary.ReadUintBe(4);
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
    writer.WriteUint32Be(iNetworkTimestamp);
    writer.WriteUint32Be(iMediaLatency);
    writer.WriteUint32Be(iMediaTimestamp);
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
    : iSequence(0)
    , iUriBytes(0)
    , iMetadataBytes(0)
{
}

OhmHeaderTrack::OhmHeaderTrack(TUint aSequence, const Brx& aUri, const Brx& aMetadata)
    : iSequence(aSequence)
{
    iUriBytes = aUri.Bytes();
    iMetadataBytes = aMetadata.Bytes();
}

void OhmHeaderTrack::Internalise(IReader& aReader, const OhmHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhmHeader::kMsgTypeTrack);
    
    ReaderBinary readerBinary(aReader);

    iSequence = readerBinary.ReadUintBe(4);
    iUriBytes = readerBinary.ReadUintBe(4);
    iMetadataBytes = readerBinary.ReadUintBe(4);
}

void OhmHeaderTrack::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.WriteUint32Be(iSequence);
    writer.WriteUint32Be(iUriBytes);
    writer.WriteUint32Be(iMetadataBytes);
}

// OhmHeaderMetatext

OhmHeaderMetatext::OhmHeaderMetatext()
    : iSequence(0)
    , iMetatextBytes(0)
{
}
    
OhmHeaderMetatext::OhmHeaderMetatext(TUint aSequence, const Brx& aMetatext)
    : iSequence(aSequence)
{
    iMetatextBytes = aMetatext.Bytes();
}

void OhmHeaderMetatext::Internalise(IReader& aReader, const OhmHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhmHeader::kMsgTypeMetatext);
    
    ReaderBinary readerBinary(aReader);

    iSequence = readerBinary.ReadUintBe(4);
    iMetatextBytes = readerBinary.ReadUintBe(4);
}

void OhmHeaderMetatext::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.WriteUint32Be(iSequence);
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
    : iMsgType(0)
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

    if(iMsgType > kMsgTypePresetInfo) {
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

// OhzHeaderZoneUri

OhzHeaderZoneUri::OhzHeaderZoneUri()
{
}

OhzHeaderZoneUri::OhzHeaderZoneUri(const Brx& aZone, const Brx& aUri)
{
    iZoneBytes = aZone.Bytes();
    iUriBytes = aUri.Bytes();
}

void OhzHeaderZoneUri::Internalise(IReader& aReader, const OhzHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhzHeader::kMsgTypeZoneUri);
    
    ReaderBinary readerBinary(aReader);

    iZoneBytes = readerBinary.ReadUintBe(4);
    iUriBytes = readerBinary.ReadUintBe(4);
}

void OhzHeaderZoneUri::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.WriteUint32Be(iZoneBytes);
    writer.WriteUint32Be(iUriBytes);
}

// OhzHeaderZoneQuery

OhzHeaderZoneQuery::OhzHeaderZoneQuery()
{
}
    
OhzHeaderZoneQuery::OhzHeaderZoneQuery(const Brx& aQuery)
{
    iZoneBytes = aQuery.Bytes();
}

void OhzHeaderZoneQuery::Internalise(IReader& aReader, const OhzHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhzHeader::kMsgTypeZoneQuery);
    
    ReaderBinary readerBinary(aReader);

    iZoneBytes = readerBinary.ReadUintBe(4);
}

void OhzHeaderZoneQuery::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.WriteUint32Be(iZoneBytes);
}
    
// OhzHeaderPresetQuery

OhzHeaderPresetQuery::OhzHeaderPresetQuery()
{
}

OhzHeaderPresetQuery::OhzHeaderPresetQuery(TUint aPreset)
{
	iPreset = aPreset;
}

void OhzHeaderPresetQuery::Internalise(IReader& aReader, const OhzHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhzHeader::kMsgTypePresetQuery);

    ReaderBinary readerBinary(aReader);

	iPreset = readerBinary.ReadUintBe(4);
}

void OhzHeaderPresetQuery::Externalise(IWriter& aWriter) const
{
	WriterBinary writer(aWriter);

	writer.WriteUint32Be(iPreset);
}

// ZonepusHeaderUri

OhzHeaderPresetInfo::OhzHeaderPresetInfo()
{
}

OhzHeaderPresetInfo::OhzHeaderPresetInfo(TUint aPreset, const Brx& aMetadata)
{
	iPreset = aPreset;
    iMetadataBytes = aMetadata.Bytes();
}

void OhzHeaderPresetInfo::Internalise(IReader& aReader, const OhzHeader& aHeader)
{
    ASSERT (aHeader.MsgType() == OhzHeader::kMsgTypePresetInfo);

    ReaderBinary readerBinary(aReader);

    iPreset = readerBinary.ReadUintBe(4);
    iMetadataBytes = readerBinary.ReadUintBe(4);
}

void OhzHeaderPresetInfo::Externalise(IWriter& aWriter) const
{
    WriterBinary writer(aWriter);

    writer.WriteUint32Be(iPreset);
    writer.WriteUint32Be(iMetadataBytes);
}

