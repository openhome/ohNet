#ifndef HEADER_OHM
#define HEADER_OHM

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Network.h>

EXCEPTION(OhmError);
EXCEPTION(OhzError);

namespace OpenHome {
namespace Net {

class Ohm
{
public:
    static const TUint kPort = 51970;
    static const TUint kMaxUriBytes = 30;
    static const TUint kMaxTrackUriBytes = 1000;
    static const TUint kMaxTrackMetadataBytes = 5000;
    static const TUint kMaxTrackMetatextBytes = 1000;
    static const TUint kMaxCodecNameBytes = 256;
};

class OhmSocket : public IReaderSource, public INonCopyable
{
    static const TUint kSendBufBytes = 16392;

public:
    OhmSocket();
    void OpenUnicast(TIpAddress aInterface, TUint aTtl);
    void OpenMulticast(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint);
    Endpoint This() const;
    Endpoint Sender() const;
    void Send(const Brx& aBuffer, const Endpoint& aEndpoint);
    void Close();
    ~OhmSocket();

public:
	// IReaderSource
    virtual void Read(Bwx& aBuffer);
    virtual void ReadFlush();
    virtual void ReadInterrupt();

private:
    SocketUdp* iRxSocket;
	SocketUdp* iTxSocket;
    UdpReader* iReader;
    Endpoint iThis;
};

class OhzSocket : public IReaderSource, public INonCopyable
{
    static const TUint kSendBufBytes = 1024;

public:
    OhzSocket();

	void Open(TIpAddress aInterface, TUint aTtl);
    void Send(const Brx& aBuffer);
    void Close();

    // IReaderSource
    virtual void Read(Bwx& aBuffer);
    virtual void ReadFlush();
    virtual void ReadInterrupt();
    
    ~OhzSocket();

private:
    SocketUdpMulticast* iRxSocket;
    SocketUdp* iTxSocket;
    Endpoint iEndpoint;
    UdpReader* iReader;
};

class OhmHeader
{
public:
    static const Brn kOhm;
    static const TUint8 kMajor = 1;
    static const TUint kHeaderBytes = 8;
    
public:
    static const TUint8 kMsgTypeJoin = 0;
    static const TUint8 kMsgTypeListen = 1;
    static const TUint8 kMsgTypeLeave = 2;
    static const TUint8 kMsgTypeAudio = 3;
    static const TUint8 kMsgTypeTrack = 4;
    static const TUint8 kMsgTypeMetatext = 5;
    static const TUint8 kMsgTypeSlave = 6;

public:
    OhmHeader();
    OhmHeader(TUint aMsgType, TUint aMsgBytes);
    
    void Internalise(IReader& aReader);
    void Externalise(IWriter& aWriter) const;

    TUint MsgType() const {return (iMsgType);}
    TUint MsgBytes() const {return (iBytes - kHeaderBytes);}
    
private:
    TUint iMsgType;
    TUint iBytes;
    
private:
    //Offset    Bytes                   Desc
    //0         4                       "Ohm "
    //4         1                       OhmHeader Major Version
    //5         1                       Msg Type (2 = OhmMsgAudio)
    //6         2                       Total Bytes (Absolutely all bytes in the entire frame)
};

class OhmHeaderAudio
{
public:
    static const TUint kHeaderBytes = 50; // not including codec name
    static const TUint kReserved = 0;
    static const TUint kFlagHalt = 1;
    static const TUint kFlagLossless = 2;
    static const TUint kFlagTimestamp = 4;

public:
    OhmHeaderAudio();
    OhmHeaderAudio(TBool aHalt, 
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
                   const Brx& aCodecName);
    
    OhmHeaderAudio(TBool aHalt, 
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
                   const Brx& aCodecName);
    
    void Internalise(IReader& aReader, const OhmHeader& aHeader);
    void Externalise(IWriter& aWriter) const;
    
    TBool Halt() const {return (iHalt);}
    TBool Lossless() const {return (iLossless);}
    TBool Timestamped() const {return (iTimestamped);}
    TUint Samples() const {return (iSamples);}
    TUint Frame() const {return (iFrame);}
    TUint NetworkTimestamp() const {return (iNetworkTimestamp);}
    TUint MediaLatency() const {return (iMediaLatency);}
    TUint MediaTimestamp() const {return (iMediaTimestamp);}
    TUint64 SampleStart() const {return (iSampleStart);}
    TUint64 SamplesTotal() const {return (iSamplesTotal);}
    TUint SampleRate() const {return (iSampleRate);}
    TUint BitRate() const {return (iBitRate);}
    TInt VolumeOffset() const {return (iVolumeOffset);}
    TUint BitDepth() const {return (iBitDepth);}
    TUint Channels() const {return (iChannels);}
    const Brx& CodecName() const {return (iCodecName);}
    
    TUint AudioBytes() const {return (iAudioBytes);}
    TUint MsgBytes() const {return (kHeaderBytes + iCodecName.Bytes() + iAudioBytes);}

private:
    //Offset    Bytes                   Desc
    //0         1                       Msg Header Bytes (without the codec name)
    //1         1                       Flags (lsb first: halt flag, lossless flag, timestamped flag all other bits 0)
    //2         2                       Samples in this msg
    //4         4                       Frame
    //8         4                       Network timestamp
    //12        4                       Media Latency
    //16        4                       Media Timestamp
    //20        8                       Sample Start (first sample's offset from the beginiing of this track)
    //28        8                       Samples Total (total samples for this track)
    //36        4                       Sample Rate
    //40        4                       Bit Rate
    //44		2						Volume Offset
    //46        1                       Bit depth of audio (16, 24)
    //47        1                       Channels
    //48        1                       Reserved (must be zero)
    //49        1                       Codec Name Bytes
    //50        n                       Codec Name
    //50 + n    Msg Total Bytes - Msg Header Bytes - Code Name Bytes (Sample data in big endian, channels interleaved, packed)

    TBool iHalt;
    TBool iLossless;
    TBool iTimestamped;
    TUint iSamples;
    TUint iFrame;
    TUint iNetworkTimestamp;
    TUint iMediaLatency;
    TUint iMediaTimestamp;
    TUint64 iSampleStart;
    TUint64 iSamplesTotal;
    TUint iSampleRate;
    TUint iBitRate;
    TInt iVolumeOffset;
    TUint iBitDepth;
    TUint iChannels;
    Bws<Ohm::kMaxCodecNameBytes> iCodecName;
    TUint iAudioBytes;
};

class OhmHeaderTrack
{
public:
    static const TUint kHeaderBytes = 12;

public:
    OhmHeaderTrack();
    OhmHeaderTrack(TUint aSequence, const Brx& aUri, const Brx& aMetadata);
    
    void Internalise(IReader& aReader, const OhmHeader& aHeader);
    void Externalise(IWriter& aWriter) const;
    
    TUint Sequence() const {return (iSequence);}
    TUint UriBytes() const {return (iUriBytes);}
    TUint MetadataBytes() const {return (iMetadataBytes);}
    TUint MsgBytes() const {return (kHeaderBytes + iUriBytes + iMetadataBytes);}

private:
    //Offset    Bytes                   Desc
    //0         4                       Sequence
    //4         4                       Uri Bytes (n)
    //8         4                       Metadata Bytes (m)
    //12        n                       n bytes of uri
    //12 + n    m                       m bytes of didl lite metadata

    TUint iSequence;
    TUint iUriBytes;
    TUint iMetadataBytes;
};

class OhmHeaderMetatext
{
public:
    static const TUint kHeaderBytes = 8;

public:
    OhmHeaderMetatext();
    OhmHeaderMetatext(TUint aSequence, const Brx& aMetatext);
    
    void Internalise(IReader& aReader, const OhmHeader& aHeader);
    void Externalise(IWriter& aWriter) const;
    
    TUint Sequence() const {return (iSequence);}
    TUint MetatextBytes() const {return (iMetatextBytes);}
    TUint MsgBytes() const {return (kHeaderBytes + iMetatextBytes);}

private:
    //Offset    Bytes                   Desc
    //0         4                       Sequence (n)
    //4         4                       Metatext Bytes (n)
    //8         n                       n bytes of metatext

    TUint iSequence;
    TUint iMetatextBytes;
};

class OhmHeaderSlave
{
public:
    static const TUint kHeaderBytes = 4;

public:
    OhmHeaderSlave();
    OhmHeaderSlave(TUint aSlaveCount);

    void Internalise(IReader& aReader, const OhmHeader& aHeader);
    void Externalise(IWriter& aWriter) const;

    TUint SlaveCount() const {return (iSlaveCount);}
    TUint MsgBytes() const {return (kHeaderBytes + (iSlaveCount * 6));}

private:
    //Offset    Bytes                   Desc
    //0         4                       Slave count (n)
    //4         6 * n                   Slave address/port list

    TUint iSlaveCount;
};

class OhzHeader
{
public:
    static const Brn kOhz;
    static const TUint8 kMajor = 1;
    static const TUint kHeaderBytes = 8;
    
public:
    static const TUint8 kMsgTypeZoneQuery = 0;
    static const TUint8 kMsgTypeZoneUri = 1;
    static const TUint8 kMsgTypePresetQuery = 2;
    static const TUint8 kMsgTypePresetInfo = 3;

public:
    OhzHeader();
    OhzHeader(TUint aMsgType, TUint aMsgBytes);
    
    void Internalise(IReader& aReader);
    void Externalise(IWriter& aWriter) const;

    TUint MsgType() const {return (iMsgType);}
    TUint MsgBytes() const {return (iBytes - kHeaderBytes);}
    
private:
    TUint iMsgType;
    TUint iBytes;
    
private:
    //Offset    Bytes                   Desc
    //0         4                       "Ohz "
    //4         1                       OhzHeader Major Version
    //5         1                       Msg Type (0 = Query, 1 = Uri)
    //6         2                       Total Bytes (Absolutely all bytes in the entire frame)
};

class OhzHeaderZoneQuery
{
public:
    static const TUint kHeaderBytes = 4;

public:
    OhzHeaderZoneQuery();
    OhzHeaderZoneQuery(const Brx& aZone);
    
    void Internalise(IReader& aReader, const OhzHeader& aHeader);
    void Externalise(IWriter& aWriter) const;
    
    TUint ZoneBytes() const {return (iZoneBytes);}
    TUint MsgBytes() const {return (kHeaderBytes + iZoneBytes);}

private:
    //Offset    Bytes                   Desc
    //0         4                       Query Bytes (n)
    //4         n                       n bytes of zone

    TUint iZoneBytes;
};

class OhzHeaderZoneUri
{
public:
    static const TUint kHeaderBytes = 8;

public:
    OhzHeaderZoneUri();
    OhzHeaderZoneUri(const Brx& aZone, const Brx& aUri);
    
    void Internalise(IReader& aReader, const OhzHeader& aHeader);
    void Externalise(IWriter& aWriter) const;
    
    TUint ZoneBytes() const {return (iZoneBytes);}
    TUint UriBytes() const {return (iUriBytes);}
    TUint MsgBytes() const {return (kHeaderBytes + iZoneBytes + iUriBytes);}

private:
    //Offset    Bytes                   Desc
    //0         4                       Zone Bytes (n)
    //4         4                       Uri Bytes (m)
    //8         n                       n bytes of zone
    //8 + n     m                       m bytes of uri

    TUint iZoneBytes;
    TUint iUriBytes;
};

class OhzHeaderPresetQuery
{
public:
    static const TUint kHeaderBytes = 4;

public:
    OhzHeaderPresetQuery();
    OhzHeaderPresetQuery(TUint aPreset);

    void Internalise(IReader& aReader, const OhzHeader& aHeader);
    void Externalise(IWriter& aWriter) const;

    TUint MsgBytes() const {return (kHeaderBytes);}

    TUint Preset() const {return (iPreset);}

private:
    //Offset    Bytes                   Desc
	//0         4                       Preset Number (query)

	TUint iPreset;
};

class OhzHeaderPresetInfo
{
public:
    static const TUint kHeaderBytes = 8;

public:
    OhzHeaderPresetInfo();
    OhzHeaderPresetInfo(TUint aPreset, const Brx& aMetadata);

    void Internalise(IReader& aReader, const OhzHeader& aHeader);
    void Externalise(IWriter& aWriter) const;

    TUint MsgBytes() const {return (kHeaderBytes + iMetadataBytes);}

    TUint Preset() const {return (iPreset);}
    TUint MetadataBytes() const {return (iMetadataBytes);}

private:
    //ZonepusHeaderPresetResponse
    //ByteStart Bytes                   Desc
    //0         4                       Preset Number (response)
    //4         4						Metadata Bytes (n)
    //8         n                       n bytes of metadata

    TUint iPreset;
    TUint iMetadataBytes;
};


} // namespace Net
} // namespace OpenHome

#endif // HEADER_OHM

