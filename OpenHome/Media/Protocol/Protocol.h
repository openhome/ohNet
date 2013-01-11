#ifndef HEADER_PIPELINE_PROTOCOL
#define HEADER_PIPELINE_PROTOCOL

#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
class Environment;
namespace Media {

class IProtocolManager
{
public:
    virtual ~IProtocolManager() {}
    virtual TBool Stream(const Brx& aUri) = 0;
    virtual TBool Redirect(const Brx& aUri) = 0;
    virtual TBool Start(TUint64 aTotalBytes, TBool aLiveStream, TBool aSeekableStream) = 0;
    virtual void OutputData(const Brx& aData) = 0;
    virtual void OutputMetadata(const Brx& aMetadata) = 0;
    virtual void End() = 0;
    virtual TBool Interrupt() const = 0;
    virtual void Lock() = 0;
    virtual void Unlock() = 0;
};

class ProtocolManager;

class Protocol : public IProtocolManager, protected INonCopyable
{
    friend class ProtocolManager;
protected:
    Protocol(Environment& aEnv, IProtocolManager& aManager);
    const OpenHome::Uri& Uri() const;
protected: // from IProtocolManager
    TBool Stream(const Brx& aUri);
    TBool Redirect(const Brx& aUri);
    TBool Start(TUint64 aTotalBytes, TBool aLiveStream, TBool aSeekableStream);
    void OutputData(const Brx& aData);
    void OutputMetadata(const Brx& aMetadata);
    void End();
    TBool Interrupt() const;
    void Lock();
    void Unlock();
protected:
    virtual void Stream() = 0;
    virtual TBool Restream(TUint64 aOffset); // default implementation ASSERTS
    virtual TBool DoStream(const Brx& aUri);
    virtual TBool DoRestream(TUint64 aOffset);
    virtual void DoInterrupt();
protected:
    Environment& iEnv;
private:
    IProtocolManager& iManager;
    TBool iEnabled;
    OpenHome::Uri iUri;
};

class ProtocolNetwork : public Protocol
{
protected:
    static const TUint kReadBufferBytes = 8 * 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 3000;
protected:
	ProtocolNetwork(Environment& aEnv, IProtocolManager& aManager);
    TBool Connect(TUint aDefaultPort);
protected: // from Protocol
    TBool DoStream(const Brx& aUri);
    TBool DoRestream(TUint64 aOffset);
    void DoInterrupt();
private:
    void Open();
    void Close();
protected:
    Srs<kReadBufferBytes> iReaderBuf;
    Sws<kWriteBufferBytes> iWriterBuf;
private:
    SocketTcpClient iTcpClient;
    TBool iSocketIsOpen;
};

class ISupply
{
public:
    virtual ~ISupply() {}
    virtual TBool Start(TUint64 aTotalBytes, TBool aLiveStream, TBool aSeekable) = 0;
    virtual void OutputData(const Brx& aData) = 0;
    virtual void OutputMetadata(const Brx& aMetadata) = 0;
    virtual void End() = 0;
    virtual TBool Interrupt() = 0;
};

class ProtocolManager : public IProtocolManager, private INonCopyable
{
    static const TUint kMaxUriBytes = 1024;
public:
    ProtocolManager(ISupply& aSupply);
    virtual ~ProtocolManager();
    void Add(Protocol* aProtocol);
    const Brx& Uri() const;
    void DoStream(const Brx& aUri);
    TBool DoRestream(TUint64 aOffset);
    void DoInterrupt();
private: // from IProtocolManager
    TBool Stream(const Brx& aUri);
    TBool Redirect(const Brx& aUri);
    TBool Start(TUint64 aTotalBytes, TBool aLiveStream, TBool aSeekableStream);
    void OutputData(const Brx& aAudio);
    void OutputMetadata(const Brx& aMetadata);
    void End();
    TBool Interrupt() const;
    void Lock();
    void Unlock();
private:
    TBool SetUri(const Brx& aUri);
private:
    ISupply& iSupply;
    Mutex iMutex;
    std::vector<Protocol*> iProtocols;
    Bws<kMaxUriBytes> iUri;
    Protocol* iProtocol;
    Protocol* iStarted;
};

}; // namespace Media
}; // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL
