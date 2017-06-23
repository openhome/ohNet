#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Thread.h>

#include <atomic>
#include <string>
#include <utility>
#include <vector>

EXCEPTION(BitDepthNotSupported);
EXCEPTION(SampleRateNotSupported);
EXCEPTION(ScdError);

namespace OpenHome {
    class IReader;
    class IWriter;
namespace Scd {

class ScdHeader
{
public:
    static const Brn kId;
    static const TUint kHeaderBytes;
public:
    static const TUint kTypeReady;
    static const TUint kTypeMetadataDidl;
    static const TUint kTypeMetadataOh;
    static const TUint kTypeFormat;
    static const TUint kTypeAudio;
    static const TUint kTypeMetatextDidl;
    static const TUint kTypeMetatextOh;
    static const TUint kTypeHalt;
    static const TUint kTypeDisconnect;
    static const TUint kTypeSeek;
    static const TUint kTypeSkip;
public:
    ScdHeader();
    ScdHeader(TUint aType, TUint aMsgBytes);
    void Internalise(IReader& aReader);
    void Externalise(IWriter& aWriter) const;
    TUint Type() const { return iType; }
    TUint Bytes() const { return iBytes - kHeaderBytes; }
private:
    TUint iType;
    TUint iBytes;
};

class ScdMsgReady;
class ScdMsgMetadataDidl;
class ScdMsgMetadataOh;
class ScdMsgFormat;
class ScdMsgAudio;
class ScdMsgMetatextDidl;
class ScdMsgMetatextOh;
class ScdMsgHalt;
class ScdMsgDisconnect;
class ScdMsgSeek;
class ScdMsgSkip;

typedef std::vector<std::pair<std::string, std::string>> OpenHomeMetadata;
typedef std::vector<std::pair<Brn, Brn>> OpenHomeMetadataBuf;

class IScdMsgProcessor
{
public:
    virtual void Process(ScdMsgReady& aMsg) = 0;
    virtual void Process(ScdMsgMetadataDidl& aMsg) = 0;
    virtual void Process(ScdMsgMetadataOh& aMsg) = 0;
    virtual void Process(ScdMsgFormat& aMsg) = 0;
    virtual void Process(ScdMsgAudio& aMsg) = 0;
    virtual void Process(ScdMsgMetatextDidl& aMsg) = 0;
    virtual void Process(ScdMsgMetatextOh& aMsg) = 0;
    virtual void Process(ScdMsgHalt& aMsg) = 0;
    virtual void Process(ScdMsgDisconnect& aMsg) = 0;
    virtual void Process(ScdMsgSeek& aMsg) = 0;
    virtual void Process(ScdMsgSkip& aMsg) = 0;
    virtual ~IScdMsgProcessor() {}
};

class ScdMsg;

class IScdMsgAllocator
{
public:
    virtual void Free(ScdMsg& aMsg) = 0;
    virtual ~IScdMsgAllocator() {}
};

class ScdMsgFactory;

class ScdMsg
{
    friend class ScdMsgFactory;
    friend class ScdMsgQueue;
public:
    void AddRef();
    void RemoveRef();
    virtual void Process(IScdMsgProcessor& aProcessor) = 0;
    virtual void Externalise(IWriter& aWriter) const = 0;
protected:
    ScdMsg(IScdMsgAllocator& aAllocator);
    ~ScdMsg();
    void Initialise();
    void ReadString(IReader& aReader, TUint aLenBytes, Bwx& aBuf);
private:
    virtual void Clear();
private:
    IScdMsgAllocator& iAllocator;
    std::atomic<TUint> iRefCount;
    ScdMsg* iNext;
};

class AutoScdMsg
{
public:
    AutoScdMsg(ScdMsg* aMsg);
    ~AutoScdMsg();
private:
    ScdMsg* iMsg;
};

class ScdMsgReady : public ScdMsg
{
    friend class ScdMsgFactory;
    static const TUint kProtocolVersionMajor;
    static const TUint kProtocolVersionMinor;
public:
    TUint Major() const;
    TUint Minor() const;
private:
    ScdMsgReady(IScdMsgAllocator& aAllocator);
    void Initialise();
    void Initialise(IReader& aReader, const ScdHeader& aHeader);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
    void Clear() override;
private:
    TUint iVersionMajor;
    TUint iVersionMinor;
};

class ScdMsgMetadataDidl : public ScdMsg
{
    friend class ScdMsgFactory;
public:
    static const TUint kMaxUriBytes      = 1024;
    static const TUint kMaxMetadataBytes = 1024 * 4;
public:
    const Brx& Uri() const;
    const Brx& Metadata() const;
private:
    ScdMsgMetadataDidl(IScdMsgAllocator& aAllocator);
    void Initialise(const std::string& aUri, const std::string& aMetadata);
    void Initialise(IReader& aReader, const ScdHeader& aHeader);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
    void Clear() override;
private:
    Bws<kMaxUriBytes> iUri;
    Bws<kMaxMetadataBytes> iMetadata;
};

class ScdMsgKvp : public ScdMsg
{
    friend class ScdMsgFactory;
    static const TUint kMaxBytes = 4 * 1024;
protected:
    ScdMsgKvp(IScdMsgAllocator& aAllocator);
    void Initialise(const OpenHomeMetadata& aKvps);
    void Initialise(IReader& aReader, TUint aBytes);
    void DoExternalise(IWriter& aWriter, TUint aType) const;
private:
private: // from ScdMsg
    void Clear() override;
protected:
    OpenHomeMetadataBuf iKvps;
    Bws<kMaxBytes> iBuf;
};

class ScdMsgMetadataOh : public ScdMsgKvp
{
    friend class ScdMsgFactory;
public:
    const OpenHomeMetadataBuf& Metadata() const;
private:
    ScdMsgMetadataOh(IScdMsgAllocator& aAllocator);
    void Initialise(IReader& aReader, const ScdHeader& aHeader);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
};

class ScdMsgFormat : public ScdMsg
{
    friend class ScdMsgFactory;

    static const TUint kFlagSeekable      = 1;
    static const TUint kFlagLossless      = 1<<1;
    static const TUint kFlagLive          = 1<<2;
    static const TUint kFlagBroadcastable = 1<<3;

    static const TUint kMaxCodecNameBytes = 64;
public:
    TUint BitDepth() const;
    TUint SampleRate() const;
    TUint NumChannels() const;
    TUint BitRate() const;
    TUint64 SampleStart() const;
    TUint64 SamplesTotal() const;
    TBool Seekable() const;
    TBool Lossless() const;
    TBool Live() const;
    TBool BroadcastAllowed() const;
    const Brx& CodecName() const;
private:
    ScdMsgFormat(IScdMsgAllocator& aAllocator);
    void Initialise(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, TUint aBitRate,
                    TUint64 aSampleStart, TUint64 aSamplesTotal, TBool aSeekable, TBool aLossless,
                    TBool aLive, TBool aBroadcastAllowed, const std::string& aCodecName);
    void Initialise(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, TUint aBitRate,
                    TUint64 aSampleStart, TUint64 aSamplesTotal, TBool aSeekable, TBool aLossless,
                    TBool aLive, TBool aBroadcastAllowed, const Brx& aCodecName);
    void DoInitialise(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, TUint aBitRate,
                      TUint64 aSampleStart, TUint64 aSamplesTotal, TBool aSeekable, TBool aLossless,
                      TBool aLive, TBool aBroadcastAllowed);
    void Initialise(IReader& aReader, const ScdHeader& aHeader);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
    void Clear() override;
private:
    TUint iBitDepth;
    TUint iSampleRate;
    TUint iNumChannels;
    TUint iBitRate;
    TUint64 iSampleStart;
    TUint64 iSamplesTotal;
    TBool iSeekable;
    TBool iLossless;
    TBool iLive;
    TBool iBroadcastAllowed;
    Bws<kMaxCodecNameBytes> iCodecName;
};

class ScdMsgAudio : public ScdMsg
{
    friend class ScdMsgFactory;
public:
    static const TUint kMaxBytes = 5760; // 5ms@ 192k, 24-bit packed, 2 channel
public:
    TUint NumSamples() const;
    const Brx& Audio() const;
private:
    ScdMsgAudio(IScdMsgAllocator& aAllocator);
    void Initialise(const std::string& aAudio, TUint aNumSamples);
    void Initialise(IReader& aReader, const ScdHeader& aHeader);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
    void Clear() override;
private:
    TUint iNumSamples;
    Bws<kMaxBytes> iAudio;
};

class ScdMsgMetatextDidl : public ScdMsg
{
    friend class ScdMsgFactory;
    static const TUint kMaxBytes = 1024;
public:
    const Brx& Metatext() const;
private:
    ScdMsgMetatextDidl(IScdMsgAllocator& aAllocator);
    void Initialise(const std::string& aMetatext);
    void Initialise(IReader& aReader, const ScdHeader& aHeader);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
    void Clear() override;
private:
    Bws<kMaxBytes> iMetatext;
};

class ScdMsgMetatextOh : public ScdMsgKvp
{
    friend class ScdMsgFactory;
public:
    const OpenHomeMetadataBuf& Metatext() const;
private:
    ScdMsgMetatextOh(IScdMsgAllocator& aAllocator);
    void Initialise(IReader& aReader, const ScdHeader& aHeader);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
};

class ScdMsgHalt : public ScdMsg
{
    friend class ScdMsgFactory;
private:
    ScdMsgHalt(IScdMsgAllocator& aAllocator);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
};

class ScdMsgDisconnect : public ScdMsg
{
    friend class ScdMsgFactory;
private:
    ScdMsgDisconnect(IScdMsgAllocator& aAllocator);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
};

class ScdMsgSeek : public ScdMsg
{
    friend class ScdMsgFactory;
private:
    ScdMsgSeek(IScdMsgAllocator& aAllocator);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
    void Clear() override;
};

class ScdMsgSkip : public ScdMsg
{
    friend class ScdMsgFactory;
private:
    ScdMsgSkip(IScdMsgAllocator& aAllocator);
private: // from ScdMsg
    void Process(IScdMsgProcessor& aProcessor) override;
    void Externalise(IWriter& aWriter) const override;
    void Clear() override;
};

class ScdMsgFactory : private IScdMsgAllocator
                    , private IScdMsgProcessor
{
public:
    ScdMsgFactory(TUint aCountReady,
                  TUint aCountMetadataDidl,
                  TUint aCountMetadataOh,
                  TUint aCountFormat,
                  TUint aCountAudio,
                  TUint aCountMetatextDidl,
                  TUint aCountMetatextOh,
                  TUint aCountHalt,
                  TUint aCountDisconnect,
                  TUint aCountSeek,
                  TUint aCountSkip);
    ~ScdMsgFactory();
    ScdMsgReady* CreateMsgReady();
    ScdMsgMetadataDidl* CreateMsgMetadataDidl(const std::string& aUri, const std::string& aMetadata);
    ScdMsgMetadataOh* CreateMsgMetadataOh(const OpenHomeMetadata& aMetadata);
    ScdMsgFormat* CreateMsgFormat(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels,
                                  TUint aBitRate, TUint64 aSampleStart, TUint64 aSamplesTotal,
                                  TBool aSeekable, TBool aLossless, TBool aLive,
                                  TBool aBroadcastAllowed, const std::string& aCodecName);
    ScdMsgFormat* CreateMsgFormat(ScdMsgFormat& aFormat, TUint64 aSampleStart);
    ScdMsgAudio* CreateMsgAudio(const std::string& aAudio, TUint aNumSamples);
    ScdMsgMetatextDidl* CreateMsgMetatextDidl(const std::string& aMetatext);
    ScdMsgMetatextOh* CreateMsgMetatextOh(const OpenHomeMetadata& aMetatext);
    ScdMsgHalt* CreateMsgHalt();
    ScdMsgDisconnect* CreateMsgDisconnect();
    ScdMsg* CreateMsg(IReader& aReader);
//    ScdMsgSeek* CreateMsgSeek();
//    ScdMsgSkip* CreateMsgSkip();
private:
    ScdMsgReady* CreateMsgReady(IReader& aReader, const ScdHeader& aHeader);
    ScdMsgMetadataDidl* CreateMsgMetadataDidl(IReader& aReader, const ScdHeader& aHeader);
    ScdMsgMetadataOh* CreateMsgMetadataOh(IReader& aReader, const ScdHeader& aHeader);
    ScdMsgFormat* CreateMsgFormat(IReader& aReader, const ScdHeader& aHeader);
    ScdMsgAudio* CreateMsgAudio(IReader& aReader, const ScdHeader& aHeader);
    ScdMsgMetatextDidl* CreateMsgMetatextDidl(IReader& aReader, const ScdHeader& aHeader);
    ScdMsgMetatextOh* CreateMsgMetatextOh(IReader& aReader, const ScdHeader& aHeader);
    ScdMsgHalt* CreateMsgHalt(IReader& aReader, const ScdHeader& aHeader);
    ScdMsgDisconnect* CreateMsgDisconnect(IReader& aReader, const ScdHeader& aHeader);
private: // from IScdMsgAllocator
    void Free(ScdMsg& aMsg) override;
private: // from IScdMsgProcessor
    void Process(ScdMsgReady& aMsg) override;
    void Process(ScdMsgMetadataDidl& aMsg) override;
    void Process(ScdMsgMetadataOh& aMsg) override;
    void Process(ScdMsgFormat& aMsg) override;
    void Process(ScdMsgAudio& aMsg) override;
    void Process(ScdMsgMetatextDidl& aMsg) override;
    void Process(ScdMsgMetatextOh& aMsg) override;
    void Process(ScdMsgHalt& aMsg) override;
    void Process(ScdMsgDisconnect& aMsg) override;
    void Process(ScdMsgSeek& aMsg) override;
    void Process(ScdMsgSkip& aMsg) override;
private:
    Fifo<ScdMsgReady*>* iFifoReady;
    Fifo<ScdMsgMetadataDidl*>* iFifoMetadataDidl;
    Fifo<ScdMsgMetadataOh*>* iFifoMetadataOh;
    Fifo<ScdMsgFormat*>* iFifoFormat;
    Fifo<ScdMsgAudio*>* iFifoAudio;
    Fifo<ScdMsgMetatextDidl*>* iFifoMetatextDidl;
    Fifo<ScdMsgMetatextOh*>* iFifoMetatextOh;
    Fifo<ScdMsgHalt*>* iFifoHalt;
    Fifo<ScdMsgDisconnect*>* iFifoDisconnect;
//    Fifo<ScdMsgSeek*>* iFifoSeek;
//    Fifo<ScdMsgSkip*>* iFifoSkip;
};

class ScdMsgQueue
{
public:
    ScdMsgQueue();
    ~ScdMsgQueue();
    void Enqueue(ScdMsg* aMsg);
    ScdMsg* Dequeue();
    void EnqueueAtHead(ScdMsg* aMsg);
    TBool IsEmpty() const;
    void Clear();
    TUint NumMsgs() const; // test/debug use only
private:
    mutable Mutex iLock;
    Semaphore iSem;
    ScdMsg* iHead;
    ScdMsg* iTail;
    TUint iNumMsgs;
};

} // namespace Scd
} // namespace OpenHome
