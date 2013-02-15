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

class IProtocolManager
{
public:
    virtual ~IProtocolManager() {}
    virtual TBool REVIEW_ME_Stream(const Brx& aUri) = 0;
    virtual TBool REVIEW_ME_Redirect(const Brx& aUri) = 0;
    virtual TUint REVIEW_ME_Start(TUint64 aTotalBytes, ILiveStreamer* aLiveStreamer, IRestreamer* aRestreamer) = 0;
    virtual void REVIEW_ME_OutputData(const Brx& aData) = 0;
    virtual void REVIEW_ME_OutputMetadata(const Brx& aMetadata) = 0;
    virtual void REVIEW_ME_OutputFlush() = 0;
    virtual void REVIEW_ME_End() = 0;
    virtual void REVIEW_ME_Lock() = 0;
    virtual void REVIEW_ME_Unlock() = 0;
};

class ProtocolManager;

class Protocol : public IProtocolManager, protected INonCopyable
{
    friend class ProtocolManager;
protected:
    Protocol(Environment& aEnv, IProtocolManager& aManager);
    const OpenHome::Uri& Uri() const;
protected: // from IProtocolManager
    TBool REVIEW_ME_Stream(const Brx& aUri);
    TBool REVIEW_ME_Redirect(const Brx& aUri);
    TUint REVIEW_ME_Start(TUint64 aTotalBytes, ILiveStreamer* aLiveStreamer, IRestreamer* aRestreamer);
    void REVIEW_ME_OutputData(const Brx& aData);
    void REVIEW_ME_OutputMetadata(const Brx& aMetadata);
    void REVIEW_ME_OutputFlush();
    void REVIEW_ME_End();
    void REVIEW_ME_Lock();
    void REVIEW_ME_Unlock();
protected:
    virtual void REVIEW_ME_Stream() = 0;
    virtual TBool REVIEW_ME_DoStream(const Brx& aUri);
    virtual void REVIEW_ME_DoInterrupt(TBool aInterrupt);
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
    TBool REVIEW_ME_DoStream(const Brx& aUri);
    void REVIEW_ME_DoInterrupt(TBool aInterrupt);
protected: // FIXME - review this
    void Open();
    void Close();
protected:
    Srs<kReadBufferBytes> iReaderBuf;
    Sws<kWriteBufferBytes> iWriterBuf;
    SocketTcpClient iTcpClient;
    TBool iSocketIsOpen;
};

class ISupply
{
public:
    virtual ~ISupply() {}
    virtual void Start(TUint64 aTotalBytes, ILiveStreamer* aLiveStreamer, IRestreamer* aRestreamer, TUint aStreamId) = 0;
    virtual void OutputData(const Brx& aData) = 0;
    virtual void OutputMetadata(const Brx& aMetadata) = 0;
    virtual void OutputFlush() = 0;
    virtual void End() = 0;
};

class ProtocolManager : public IProtocolManager, private INonCopyable
{
    static const TUint kMaxUriBytes = 1024;
public:
    static const TUint kStreamIdInvalid = 0;
public:
    ProtocolManager(ISupply& aSupply);
    virtual ~ProtocolManager();
    void Add(Protocol* aProtocol);
    const Brx& Uri() const;
    void DoStream(const Brx& aUri);
    void DoInterrupt(TBool aInterrupt);
private: // from IProtocolManager
    TBool REVIEW_ME_Stream(const Brx& aUri);
    TBool REVIEW_ME_Redirect(const Brx& aUri);
    TUint REVIEW_ME_Start(TUint64 aTotalBytes, ILiveStreamer* aLiveStreamer, IRestreamer* aRestreamer);
    void REVIEW_ME_OutputData(const Brx& aAudio);
    void REVIEW_ME_OutputMetadata(const Brx& aMetadata);
    void REVIEW_ME_OutputFlush();
    void REVIEW_ME_End();
    void REVIEW_ME_Lock();
    void REVIEW_ME_Unlock();
private:
    TBool SetUri(const Brx& aUri);
private:
    ISupply& iSupply;
    Mutex iMutex;
    std::vector<Protocol*> iProtocols;
    Bws<kMaxUriBytes> iUri;
    Protocol* iProtocol;
    Protocol* iStarted;
    TUint iNextStreamId;
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL
