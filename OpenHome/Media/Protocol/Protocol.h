#ifndef HEADER_PIPELINE_PROTOCOL
#define HEADER_PIPELINE_PROTOCOL

#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
class Environment;
namespace Media {

enum ProtocolStreamResult
{
    EProtocolStreamSuccess
   ,EProtocolErrorNotSupported
   ,EProtocolStreamStopped
   ,EProtocolStreamErrorRecoverable
   ,EProtocolStreamErrorUnrecoverable
};

class IUriStreamer
{
public:
    virtual TBool DoStream(Track& aTrack, const Brx& aMode) = 0;
};

class IProtocolSet
{
public:
    virtual ProtocolStreamResult Stream(const Brx& aUri) = 0;
};

class ContentProcessor;
class IProtocolManager : public IProtocolSet
{
public:
    virtual ContentProcessor* GetContentProcessor(const Brx& aUri, const Brx& aMimeType, const Brx& aData) const = 0;
    virtual ContentProcessor* GetAudioProcessor() const = 0;
    virtual TBool IsCurrentTrack(TUint aTrackId) const = 0;
};

class IProtocolReader : public IReader
{
public:
    virtual Brn ReadRemaining() = 0;
};

class Protocol : protected IStreamHandler, protected INonCopyable
{
public:
    virtual ~Protocol();
    ProtocolStreamResult TryStream(const Brx& aUri);
    void Initialise(IProtocolManager& aProtocolManager, IPipelineIdProvider& aIdProvider, ISupply& aSupply, IFlushIdProvider& aFlushIdProvider);
    TBool Active() const;
protected:
    Protocol(Environment& aEnv);
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
private:
    virtual ProtocolStreamResult Stream(const Brx& aUri) = 0;
protected:
    Environment& iEnv;
    IProtocolManager* iProtocolManager;
    IPipelineIdProvider* iIdProvider;
    ISupply* iSupply;
    IFlushIdProvider* iFlushIdProvider;
private:
    TBool iActive;
private:
    class AutoStream : private INonCopyable
    {
    public:
        AutoStream(Protocol& aProtocol);
        ~AutoStream();
    private:
        Protocol& iProtocol;
    };
};

class ProtocolNetwork : public Protocol
{
protected:
    static const TUint kReadBufferBytes = 8 * 1024; // WMA radio streams (in ProtocolRtsp) require at least an 8k buffer
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 3000;
protected:
	ProtocolNetwork(Environment& aEnv);
    TBool Connect(const OpenHome::Uri& aUri, TUint aDefaultPort);
protected: // from Protocol
    void Interrupt(TBool aInterrupt);
protected:
    void Open();
    void Close();
protected:
    Srs<kReadBufferBytes> iReaderBuf;
    Sws<kWriteBufferBytes> iWriterBuf;
    Mutex iLock;
    SocketTcpClient iTcpClient;
    TBool iSocketIsOpen;
};

class ContentProcessor
{
    static const TUint kMaxLineBytes = 512;
    static const TUint kMaxTagBytes = 512;
public:
    virtual ~ContentProcessor();
    void Initialise(IProtocolSet& aProtocolSet);
    TBool IsActive() const;
    void SetActive();
protected:
    ContentProcessor();
public:
    virtual TBool Recognise(const Brx& aUri, const Brx& aMimeType, const Brx& aData) = 0;
    virtual void Reset();
    virtual ProtocolStreamResult Stream(IProtocolReader& aReader, TUint64 aTotalBytes) = 0;
protected:
    Brn ReadLine(IProtocolReader& aReader, TUint64& aBytesRemaining);
    Brn ReadTag(IProtocolReader& aReader, TUint64& aBytesRemaining);
protected:
    IProtocolSet* iProtocolSet;
    Bws<kMaxLineBytes> iPartialLine;
    Bws<kMaxTagBytes> iPartialTag;
private:
    TBool iActive;
    TBool iInTag;
};

class ProtocolManager : public IUriStreamer, private IProtocolManager, private INonCopyable
{
    static const TUint kMaxUriBytes = 1024;
public:
    static const TUint kStreamIdInvalid = 0;
public:
    ProtocolManager(ISupply& aSupply, IPipelineIdProvider& aIdProvider, IFlushIdProvider& aFlushIdProvider);
    virtual ~ProtocolManager();
    void Add(Protocol* aProtocol);
    void Add(ContentProcessor* aProcessor);
public: // from IUriStreamer
    TBool DoStream(Track& aTrack, const Brx& aMode);
private: // from IProtocolManager
    ProtocolStreamResult Stream(const Brx& aUri);
    ContentProcessor* GetContentProcessor(const Brx& aUri, const Brx& aMimeType, const Brx& aData) const;
    ContentProcessor* GetAudioProcessor() const;
    TBool IsCurrentTrack(TUint aTrackId) const;
private:
    IPipelineIdProvider& iIdProvider;
    IFlushIdProvider& iFlushIdProvider;
    ISupply& iSupply;
    mutable Mutex iLock;
    std::vector<Protocol*> iProtocols;
    std::vector<ContentProcessor*> iContentProcessors;
    ContentProcessor* iAudioProcessor;
    TUint iTrackId;
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL
