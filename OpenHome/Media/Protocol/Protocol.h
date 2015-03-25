#ifndef HEADER_PIPELINE_PROTOCOL
#define HEADER_PIPELINE_PROTOCOL

#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>

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

enum ProtocolGetResult
{
    EProtocolGetSuccess
   ,EProtocolGetErrorNotSupported
   ,EProtocolGetErrorUnrecoverable
};

class IUriStreamer
{
public:
    virtual ProtocolStreamResult DoStream(Track& aTrack) = 0;
    virtual void Interrupt(TBool aInterrupt) = 0;
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
    // GetContentProcessor()/GetAudioProcessor() may return NULL.
    // In the case of these methods, returning a pointer DOES NOT imply ownership.
    virtual ContentProcessor* GetContentProcessor(const Brx& aUri, const Brx& aMimeType, const Brx& aData) const = 0;
    virtual ContentProcessor* GetAudioProcessor() const = 0;
    virtual TBool Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) = 0;
};

/**
 * The start of the pipeline.  Runs in a client thread and feeds data into the pipeline.
 *
 * Does not need to provide any moderation.  Calls to push encoded audio into the pipeline
 * will block if the pipeline reaches its buffering capacity.
 */
class Protocol : protected IStreamHandler, protected INonCopyable
{
public:
    virtual ~Protocol();
    ProtocolGetResult DoGet(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes);
    ProtocolStreamResult TryStream(const Brx& aUri);
    void Initialise(IProtocolManager& aProtocolManager, IPipelineIdProvider& aIdProvider, MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream, IFlushIdProvider& aFlushIdProvider);
    TBool TrySetActive();
    /**
     * Interrupt any stream that is currently in-progress, or cancel a previous interruption.
     *
     * This may be called from a different thread.  The implementor is responsible for any synchronisation.
     *
     * @param[in] aInterrupt       When true, interrupt any potentially blocking calls inside a
     *                             Stream() call, causing them to report EProtocolStreamErrorUnrecoverable.
     */
    virtual void Interrupt(TBool aInterrupt) = 0;
protected:
    Protocol(Environment& aEnv);
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId) override;
private:
    virtual void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream) = 0;
    /**
     * Stream a track.
     *
     * This call should block for as long as it takes to stream the entire resource into the
     * pipeline (or decide that this protocol is not capable of streaming the resource).
     * The protocol should translate received data into calls to ISupply.  Data should be
     * pushed into the pipeline as quickly as possible, relying on the pipeline to apply
     * any moderation
     *
     * @param[in] aUri             Resource to be streamed.
     *
     * @return  Results of attempted stream:
     *              EProtocolStreamSuccess - the entire stream was pushed into the pipeline
                    EProtocolErrorNotSupported - the uri is not supported by this protocol
                    EProtocolStreamStopped - streaming was interrupted by a downstream request to stop (TryStop was called)
                    EProtocolStreamErrorRecoverable - for internal use only; will not be reported here
                    EProtocolStreamErrorUnrecoverable - error in stream; do not attempt to stream via other protocol(s)
     */
    virtual ProtocolStreamResult Stream(const Brx& aUri) = 0;
    /**
     * Read a block of data from a uri.
     *
     * This call should block for as long as it takes to stream the entire resource into the
     * pipeline (or decide that this protocol is not capable of streaming the resource).
     * Data should be returned as quickly as possible.
     *
     * @param[in] aWriter          Interface used to return the requested data.
     * @param[in] aUri             Uri to be read.
     * @param[in] aOffset          Byte offset to start reading from.
     * @param[in] aBytes           Number of bytes to read
     *
     * @return  EProtocolGetSuccess if the data was read.
     *          EProtocolGetErrorNotSupported if the protocol doesn't support the uri.  Another protocol will be tried in this case.
     *          EProtocolGetErrorUnrecoverable if the read failed and no other protocol should be tried.
     */
    virtual ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) = 0;
    /**
     * Inform a protocol it has been deactivated (i.e. its Stream() function has exited)
     */
    virtual void Deactivated();
protected:
    Environment& iEnv;
    IProtocolManager* iProtocolManager;
    IPipelineIdProvider* iIdProvider;
    IFlushIdProvider* iFlushIdProvider;
    TBool iActive;
private:
    Mutex iLockActive;
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
    static const TUint kReadBufferBytes = 1024;
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

class ContentProcessor : protected IReader
{
    static const TUint kMaxLineBytes = 2048;
    static const TUint kMaxTagBytes = 2048;
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
    virtual ProtocolStreamResult Stream(IReader& aReader, TUint64 aTotalBytes) = 0;
protected:
    void SetStream(IReader& aStream);
    Brn ReadLine(ReaderUntil& aReader, TUint64& aBytesRemaining);
    Brn ReadTag(ReaderUntil& aReader, TUint64& aBytesRemaining);
protected: // from IReader
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
protected:
    IProtocolSet* iProtocolSet;
    Bws<kMaxLineBytes> iPartialLine;
    Bws<kMaxTagBytes> iPartialTag;
    IReader* iReader;
private:
    TBool iActive;
    TBool iInTag;
};

class ContentRecogBuf : public IReader, private INonCopyable
{
    static const TUint kMaxBytes = 100;
public:
    ContentRecogBuf(IReader& aReader);
    void Populate(TUint64 aStreamTotalBytes);
    const Brx& Buffer() const;
public: // from IReader
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    IReader& iReader;
    Bws<kMaxBytes> iBuf;
    TUint iBytesRemaining;
};

class ProtocolManager : public IUriStreamer, private IProtocolManager, private INonCopyable
{
    static const TUint kMaxUriBytes = 1024;
public:
    ProtocolManager(IPipelineElementDownstream& aDownstream, MsgFactory& aMsgFactory, IPipelineIdProvider& aIdProvider, IFlushIdProvider& aFlushIdProvider);
    virtual ~ProtocolManager();
    void Add(Protocol* aProtocol);
    void Add(ContentProcessor* aProcessor);
public: // from IUriStreamer
    ProtocolStreamResult DoStream(Track& aTrack);
    void Interrupt(TBool aInterrupt);
private: // from IProtocolManager
    ProtocolStreamResult Stream(const Brx& aUri) override;
    ContentProcessor* GetContentProcessor(const Brx& aUri, const Brx& aMimeType, const Brx& aData) const override;
    ContentProcessor* GetAudioProcessor() const override;
    TBool Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) override;
private:
    IPipelineElementDownstream& iDownstream;
    MsgFactory& iMsgFactory;
    IPipelineIdProvider& iIdProvider;
    IFlushIdProvider& iFlushIdProvider;
    mutable Mutex iLock;
    std::vector<Protocol*> iProtocols;
    std::vector<ContentProcessor*> iContentProcessors;
    ContentProcessor* iAudioProcessor;
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL
