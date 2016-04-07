#pragma once

#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Network.h>

EXCEPTION(UdpServerClosed);

namespace OpenHome {
namespace Av {

/**
 * Storage class for the output of a UdpSocketBase::Receive call
 */
class MsgUdp
{
public:
    MsgUdp(TUint aMaxSize);
    ~MsgUdp();
    void Read(SocketUdp& aSocket);
    const Brx& Buffer();
    OpenHome::Endpoint& Endpoint();
private:
    Bwh iBuf;
    OpenHome::Endpoint iEndpoint;
};

/**
 * Class for a continuously running server which buffers packets while active
 * and discards packets when deactivated
 */
class SocketUdpServer : public IReaderSource
{
public:
    SocketUdpServer(Environment& aEnv, TUint aMaxSize, TUint aMaxPackets, TUint aPort = 0, TIpAddress aInterface = 0);
    ~SocketUdpServer();
    void Open();
    void Close();
    TBool IsOpen();
    void WaitForOpen();         // it is up to callers to provide sufficient locking so that
    void ClearWaitForOpen();    // WaitForOpen() is not called again after ClearWaitForOpen()
    void Send(const Brx& aBuffer, const Endpoint& aEndpoint);
    Endpoint Receive(Bwx& aBuf);
    Endpoint Sender() const; // sender of last completed Read()
    TUint Port() const;

    void SetSendBufBytes(TUint aBytes);
    void SetRecvBufBytes(TUint aBytes);
    void SetRecvTimeout(TUint aMs);
    void SetTtl(TUint aTtl);
public: // from IReaderSource
    void Read(Bwx& aBuffer) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    static void CopyMsgToBuf(MsgUdp& aMsg, Bwx& aBuf, Endpoint& aEndpoint);
    void ServerThread();
    void CurrentAdapterChanged();
    struct RebindJob {
        TIpAddress iAddress;
        TUint iPort;
        Functor iCompleteFunctor;
    };
    void PostRebind(TIpAddress aAddress, TUint aPort, Functor aCompleteFunctor);
    void CheckRebind();
private:
    Environment& iEnv;
    SocketUdp iSocket;
    TUint iMaxSize;
    TBool iOpen;
    Fifo<MsgUdp*> iFifoWaiting;
    Fifo<MsgUdp*> iFifoReady;
    MsgUdp* iDiscard;
    Endpoint iSender;
    mutable Mutex iLock;
    Mutex iReadyLock;
    Semaphore iSemaphore;
    Semaphore iSemaphoreOpen;
    ThreadFunctor* iServerThread;
    TBool iQuit;
    TUint iAdapterListenerId;
    TBool iRebindPosted;
    RebindJob iRebindJob;
};

/**
 * Class for managing a collection of SocketUdpServers. UdpServerManager owns
 * all the SocketUdpServers contained within it.
 */
class UdpServerManager
{
public:
    UdpServerManager(Environment& aEnv, TUint aMaxSize, TUint aMaxPackets);
    ~UdpServerManager();
    TUint CreateServer(TUint aPort = 0, TIpAddress aInterface = 0); // return ID of server
    SocketUdpServer& Find(TUint aId); // find server by ID
    void CloseAll();
    void OpenAll();
private:
    std::vector<SocketUdpServer*> iServers;
    Environment& iEnv;
    TUint iMaxSize;
    TUint iMaxPackets;
    Mutex iLock;
};

} // namespace Av
} // namespace OpenHome

