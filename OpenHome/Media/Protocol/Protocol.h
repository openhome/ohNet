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

class ISupply
{
public:
    virtual void Start(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId) = 0;
    virtual void OutputData(const Brx& aData) = 0;
    virtual void OutputMetadata(const Brx& aMetadata) = 0;
    virtual void OutputFlush() = 0;
};

enum ProtocolStreamResult
{
    EProtocolStreamSuccess
   ,EProtocolErrorNotSupported
   ,EProtocolStreamStopped
   ,EProtocolStreamErrorRecoverable
   ,EProtocolStreamErrorUnrecoverable
};

class IProtocolSet
{
public:
    virtual ProtocolStreamResult Stream(const Brx& aUri, TUint aTrackId) = 0;
};

class ContentProcessor;
class IProtocolManager : public IProtocolSet
{
public:
    virtual ContentProcessor* GetContentProcessor(const Brx& aUri, const Brx& aMimeType, const Brx& aData) = 0;
};

class IPipelineIdProvider // FIXME - move to more appropriate header
{
public:
    virtual TUint NextTrackId() = 0;
    virtual TUint NextStreamId() = 0;
    virtual TBool OkToPlay(TUint aTrackId, TUint aStreamId) = 0;
};

class Protocol : protected IStreamHandler, protected INonCopyable
{
public:
    ProtocolStreamResult TryStream(const Brx& aUri, TUint aTrackId);
    void Initialise(IProtocolManager& aProtocolManager, IPipelineIdProvider& aIdProvider, ISupply& aSupply);
    TBool Active() const;
protected:
    Protocol(Environment& aEnv);
private: // from IProtocolManager
    TBool Seekable() const;
    TBool Seek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TBool Live() const;
private:
    virtual ProtocolStreamResult Stream(const Brx& aUri, TUint aTrackId) = 0;
protected:
    Environment& iEnv;
    IProtocolManager* iProtocolManager;
    IPipelineIdProvider* iIdProvider;
    ISupply* iSupply;
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
    static const TUint kReadBufferBytes = 8 * 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 3000;
protected:
	ProtocolNetwork(Environment& aEnv);
    TBool Connect(const OpenHome::Uri& aUri, TUint aDefaultPort);
protected: // from Protocol
    TBool REVIEW_ME_DoStream(const Brx& aUri);
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
public:
    virtual ~ContentProcessor();
    void Initialise(IProtocolSet& aProtocolSet);
    TBool Active() const;
protected:
    ContentProcessor();
public:
    virtual TBool Recognise(const Brx& aUri, const Brx& aMimeType, const Brx& aData) = 0;
    ProtocolStreamResult TryStream(Srx& aReaderStream, TUint64 aRemainingBytes, TUint aMaxReadBytes);
private:
    virtual ProtocolStreamResult Stream(Srx& aReaderStream, TUint64 aTotalBytes, TUint aMaxReadBytes) = 0;
protected:
    IProtocolSet* iProtocolSet;
private:
    TBool iActive;
private:
    class AutoStream : private INonCopyable
    {
    public:
        AutoStream(ContentProcessor& aProcessor);
        ~AutoStream();
    private:
        ContentProcessor& iProcessor;
    };
};

class ProtocolManager : private IProtocolManager, private INonCopyable
{
    static const TUint kMaxUriBytes = 1024;
public:
    static const TUint kStreamIdInvalid = 0;
public:
    ProtocolManager(ISupply& aSupply, IPipelineIdProvider& aIdProvider);
    virtual ~ProtocolManager();
    void Add(Protocol* aProtocol);
    void Add(ContentProcessor* aProcessor);
    TBool DoStream(const Brx& aUri);
private: // from IProtocolManager
    ProtocolStreamResult Stream(const Brx& aUri, TUint aTrackId);
    ContentProcessor* GetContentProcessor(const Brx& aUri, const Brx& aMimeType, const Brx& aData);
private:
    IPipelineIdProvider& iIdProvider;
    ISupply& iSupply;
    std::vector<Protocol*> iProtocols;
    std::vector<ContentProcessor*> iContentProcessors;
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL
