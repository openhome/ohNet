#ifndef HEADER_OHM
#define HEADER_OHM

#include <ZappTypes.h>
#include <Buffer.h>
#include <Stream.h>
#include <Network.h>

EXCEPTION(OhmError);
EXCEPTION(OhzError);

namespace Zapp {

class Ohm
{
public:
    static const TUint kPort = 51972;
    static const TUint kMaxUriBytes = 30;
    static const TUint kMaxTrackUriBytes = 1000;
    static const TUint kMaxTrackMetadataBytes = 5000;
    static const TUint kMaxTrackMetatextBytes = 1000;
    static const TUint kMaxCodecNameBytes = 256;
};

class OhmSocket : public IReaderSource, public IWriter, public INonCopyable
{
    static const TUint kSendBufBytes = 32 * 1024;

public:
    OhmSocket(TUint aTtl, TIpAddress aInterface);

    void AddMembership(Endpoint& aEndpoint);
    void DropMembership();
    
    // IReaderSource
    virtual void Read(Bwx& aBuffer);
    virtual void ReadFlush();
    virtual void ReadInterrupt();
    
    // IWriter
    virtual void Write(TByte aValue);
    virtual void Write(const Brx& aBuffer);
    virtual void WriteFlush();

    ~OhmSocket();
    
private:
    TUint iTtl;
    TIpAddress iInterface;
    SocketUdpMulticast* iSocket;
    UdpControllerReader* iReader;
    UdpControllerWriter* iWriter;
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
    static const TUint8 kMsgTypeAudio = 2;
    static const TUint8 kMsgTypeTrack = 3;
    static const TUint8 kMsgTypeMetatext = 4;

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
    //OhmHeader
    //ByteStart Bytes                   Desc
    //0         4                       "Ohm "
    //4         1                       OhmHeader Major Version
    //5         1                       Msg Type (2 = OhmMsgAudio)
    //6         2                       Total Bytes (Absolutely all bytes in the entire frame)
};

class OhmHeaderAudio
{
public:
    static const TUint kHeaderBytes = 46; // not including codec name
    static const TUint kReserved = 0;
    static const TUint kFlagHalt = 1;
    static const TUint kFlagLossless = 2;
    static const TUint kFlagSync = 4;

public:
    OhmHeaderAudio();
    OhmHeaderAudio(TBool aHalt, 
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
                   const Brx& aCodecName);
    
    void Internalise(IReader& aReader, const OhmHeader& aHeader);
    void Externalise(IWriter& aWriter) const;
    
    TBool Halt() const {return (iHalt);}
    TBool Lossless() const {return (iLossless);}
    TBool Sync() const {return (iSync);}
    TUint Samples() const {return (iSamples);}
    TUint Frame() const {return (iFrame);}
    TUint TxTimestampPrev() const {return (iTxTimestampPrev);}
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
    //OhmMsgAudio
    //ByteStart Bytes                   Desc
    //0         1                       Msg Header Bytes (without the codec name)
    //1         1                       Flags (lsb first: halt flag, lossless flag, sync flag all other bits 0)
    //2         2                       Samples in this msg
    //4         4                       Frame
    //8         4                       Sender timestamp of previous frame
    //12        4                       Sync time of first sample in message
    //16        8                       Sample Start (first sample's offset from the beginiing of this track)
    //24        8                       Samples Total (total samples for this track)
    //32        4                       Sample Rate
    //36        4                       Bit Rate
    //40		2						Volume Offset
    //42        1                       Bit depth of audio (16, 24)
    //43        1                       Channels
    //44        1                       Reserved (must be zero)
    //45        1                       Codec Name Bytes
    //46        n                       Codec Name
    //46 + n    Msg Total Bytes - Msg Header Bytes - Code Name Bytes (Sample data in big endian, channels interleaved, packed)

    TBool iHalt;
    TBool iLossless;
    TBool iSync;
    TUint iSamples;
    TUint iFrame;
    TUint iTxTimestampPrev;
    TUint iSyncTimestamp;
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
    static const TUint kHeaderBytes = 8;

public:
    OhmHeaderTrack();
    OhmHeaderTrack(const Brx& aUri, const Brx& aMetadata);
    
    void Internalise(IReader& aReader, const OhmHeader& aHeader);
    void Externalise(IWriter& aWriter) const;
    
    TUint UriBytes() const {return (iUriBytes);}
    TUint MetadataBytes() const {return (iMetadataBytes);}
    TUint MsgBytes() const {return (kHeaderBytes + iUriBytes + iMetadataBytes);}

private:
    //OhmHeaderTrack
    //ByteStart Bytes                   Desc
    //0         4                       Uri Bytes (n)
    //4         4                       Metadata Bytes (m)
    //8         n                       n bytes of uri
    //8 + n     m                       m bytes of didl lite metadata

    TUint iUriBytes;
    TUint iMetadataBytes;
};

class OhmHeaderMetatext
{
public:
    static const TUint kHeaderBytes = 4;

public:
    OhmHeaderMetatext();
    OhmHeaderMetatext(const Brx& aMetatext);
    
    void Internalise(IReader& aReader, const OhmHeader& aHeader);
    void Externalise(IWriter& aWriter) const;
    
    TUint MetatextBytes() const {return (iMetatextBytes);}
    TUint MsgBytes() const {return (kHeaderBytes + iMetatextBytes);}

private:
    //OhmMsgMetatext
    //ByteStart Bytes                   Desc
    //0         4                       Metatext Bytes (n)
    //4         n                       n bytes of metatext

    TUint iMetatextBytes;
};

class OhzHeader
{
public:
    static const Brn kOhz;
    static const TUint8 kMajor = 1;
    static const TUint kHeaderBytes = 8;
    
public:
    static const TUint8 kMsgTypeQuery = 0;
    static const TUint8 kMsgTypeUri = 1;

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
    //OhzHeader
    //ByteStart Bytes                   Desc
    //0         4                       "Ohz "
    //4         1                       OhzHeader Major Version
    //5         1                       Msg Type (0 = Query, 1 = Uri)
    //6         2                       Total Bytes (Absolutely all bytes in the entire frame)
};

class OhzHeaderQuery
{
public:
    static const TUint kHeaderBytes = 4;

public:
    OhzHeaderQuery();
    OhzHeaderQuery(const Brx& aZone);
    
    void Internalise(IReader& aReader, const OhzHeader& aHeader);
    void Externalise(IWriter& aWriter) const;
    
    TUint ZoneBytes() const {return (iZoneBytes);}
    TUint MsgBytes() const {return (kHeaderBytes + iZoneBytes);}

private:
    //OhzMsgQuery
    //ByteStart Bytes                   Desc
    //0         4                       Query Bytes (n)
    //4         n                       n bytes of zone

    TUint iZoneBytes;
};

class OhzHeaderUri
{
public:
    static const TUint kHeaderBytes = 8;

public:
    OhzHeaderUri();
    OhzHeaderUri(const Brx& aZone, const Brx& aUri);
    
    void Internalise(IReader& aReader, const OhzHeader& aHeader);
    void Externalise(IWriter& aWriter) const;
    
    TUint ZoneBytes() const {return (iZoneBytes);}
    TUint UriBytes() const {return (iUriBytes);}
    TUint MsgBytes() const {return (kHeaderBytes + iZoneBytes + iUriBytes);}

private:
    //OhzHeaderUri
    //ByteStart Bytes                   Desc
    //0         4                       Zone Bytes (n)
    //4         4                       Uri Bytes (m)
    //8         n                       n bytes of zone
    //8 + n     m                       m bytes of uri

    TUint iZoneBytes;
    TUint iUriBytes;
};

} // namespace Zapp

#endif // HEADER_OHM

