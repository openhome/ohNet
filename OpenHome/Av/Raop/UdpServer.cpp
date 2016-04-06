#include <OpenHome/Av/Raop/UdpServer.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace Av;


// MsgUdp

MsgUdp::MsgUdp(TUint aMaxSize)
    : iBuf(aMaxSize)
{
}

MsgUdp::~MsgUdp()
{
}

void MsgUdp::Read(SocketUdp& aSocket)
{
    iEndpoint.Replace(aSocket.Receive(iBuf));
}

const Brx& MsgUdp::Buffer()
{
    return iBuf;
}

Endpoint& MsgUdp::Endpoint()
{
    return iEndpoint;
}


// SocketUdpServer
SocketUdpServer::SocketUdpServer(Environment& aEnv, TUint aMaxSize, TUint aMaxPackets, TUint aPort, TIpAddress aInterface)
    : iEnv(aEnv)
    , iSocket(aEnv, aPort, aInterface)
    , iMaxSize(aMaxSize)
    , iOpen(false)
    , iFifoWaiting(aMaxPackets)
    , iFifoReady(aMaxPackets)
    , iLock("UDPL")
    , iReadyLock("UDPR")
    , iSemaphore("UDPS", 0)
    , iSemaphoreOpen("UDPO", 0)
    , iQuit(false)
    , iAdapterListenerId(0)
{
    // Populate iFifoWaiting with empty packets/bufs
    while (iFifoWaiting.SlotsFree() > 0) {
        iFifoWaiting.Write(new MsgUdp(iMaxSize));
    }

    iDiscard = new MsgUdp(iMaxSize);

    iServerThread = new ThreadFunctor("UdpServer", MakeFunctor(*this, &SocketUdpServer::ServerThread));
    iServerThread->Start();
    iSemaphore.Wait();

    Functor functor = MakeFunctor(*this, &SocketUdpServer::CurrentAdapterChanged);
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    iAdapterListenerId = nifList.AddCurrentChangeListener(functor, false);
}

SocketUdpServer::~SocketUdpServer()
{
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    nifList.RemoveCurrentChangeListener(iAdapterListenerId);

    iLock.Wait();

    if (iQuit)
    {
        iLock.Signal();
        ASSERTS();
    }

    iQuit = true;

    iLock.Signal();

    iSocket.Interrupt(true);
    iFifoReady.ReadInterrupt(true);

    delete iServerThread;

    iReadyLock.Wait();
    while (iFifoReady.SlotsUsed() > 0) {
        MsgUdp* msg = iFifoReady.Read();
        delete msg;
    }
    iReadyLock.Signal();

    while (iFifoWaiting.SlotsUsed() > 0) {
        MsgUdp* msg = iFifoWaiting.Read();
        delete msg;
    }

    delete iDiscard;
}

void SocketUdpServer::Open()
{
    iLock.Wait();

    if (iQuit || iOpen)
    {
        iLock.Signal();
        ASSERTS();
    }

    iOpen = true;
    iSocket.Interrupt(true);

    iLock.Signal();

    iSemaphore.Wait();
    iSemaphoreOpen.Signal();
}

void SocketUdpServer::Close()
{
    iLock.Wait();

    if (iQuit || !iOpen)
    {
        iLock.Signal();
        ASSERTS();
    }

    iOpen = false;

    iSocket.Interrupt(true);
    iFifoReady.ReadInterrupt(true);

    iLock.Signal();

    iSemaphore.Wait();
}

TBool SocketUdpServer::IsOpen()
{
    AutoMutex a(iLock);
    return iOpen;
}

void SocketUdpServer::WaitForOpen()
{
    iSemaphoreOpen.Wait();
}

void SocketUdpServer::ClearWaitForOpen()
{
    iSemaphoreOpen.Signal();
}

void SocketUdpServer::Send(const Brx& aBuffer, const Endpoint& aEndpoint)
{
    iSocket.Send(aBuffer, aEndpoint);
}

Endpoint SocketUdpServer::Receive(Bwx& aBuf)
{
    iLock.Wait();

    if (iQuit) {
        iLock.Signal();
        ASSERTS();
    }

    if (!iOpen) {
        iLock.Signal();
        THROW(UdpServerClosed);
    }

    iLock.Signal();

    // Get data from msg
    try {
        iReadyLock.Wait();
        MsgUdp* msg = iFifoReady.Read(); // will block until msg available
        iReadyLock.Signal();

        Endpoint ep;
        CopyMsgToBuf(*msg, aBuf, ep);

        // Requeue msg
        iLock.Wait();

        iFifoWaiting.Write(msg);

        iLock.Signal();

        return ep;
    }
    catch (FifoReadError&) {
        iReadyLock.Signal();
        THROW(ReaderError);
    }
}

Endpoint SocketUdpServer::Sender() const
{
    AutoMutex a(iLock);
    return iSender;
}

TUint SocketUdpServer::Port() const
{
    return iSocket.Port();
}

void SocketUdpServer::SetSendBufBytes(TUint aBytes)
{
    iSocket.SetSendBufBytes(aBytes);
}

void SocketUdpServer::SetRecvBufBytes(TUint aBytes)
{
    iSocket.SetRecvBufBytes(aBytes);
}

void SocketUdpServer::SetRecvTimeout(TUint aMs)
{
    iSocket.SetRecvTimeout(aMs);
}

void SocketUdpServer::SetTtl(TUint aTtl)
{
    iSocket.SetTtl(aTtl);
}

void SocketUdpServer::Read(Bwx& aBuffer)
{
    try {
        Endpoint ep = Receive(aBuffer);
        iLock.Wait();
        iSender.Replace(ep);
        iLock.Signal();
    }
    catch (UdpServerClosed&) {
        THROW(ReaderError);
    }
}

void SocketUdpServer::ReadFlush()
{
}

void SocketUdpServer::ReadInterrupt()
{
    // Clients read from iFifoReady - never iSocket, so interrupt any waiting
    // Read()s on the FIFO.

    iFifoReady.ReadInterrupt(true);

    iReadyLock.Wait();
    iFifoReady.ReadInterrupt(false);
    iReadyLock.Signal();
}

void SocketUdpServer::CopyMsgToBuf(MsgUdp& aMsg, Bwx& aBuf, Endpoint& aEndpoint)
{
    const Brx& buf = aMsg.Buffer();
    ASSERT(aBuf.MaxBytes() >= buf.Bytes());
    aBuf.Replace(buf);
    aEndpoint.Replace(aMsg.Endpoint());
}

void SocketUdpServer::ServerThread()
{
    iSemaphore.Signal();

    for (;;) {

        // closed

        for (;;) {
            iLock.Wait();

            if (iQuit) {
                iLock.Signal();
                return;
            }

            if (iOpen)
            {
                iLock.Signal();
                break;
            }

            iLock.Signal();

            try {
                iDiscard->Read(iSocket);
            }
            catch (NetworkError&) {
                CheckRebind();
            }
        }

        iSocket.Interrupt(false);
        iSemaphore.Signal();

        // opened

        for (;;) {
            iLock.Wait();

            if (iQuit) {
                iLock.Signal();
                return;
            }

            if (!iOpen)
            {
                iLock.Signal();
                break;
            }

            iLock.Signal();

            try {
                iDiscard->Read(iSocket);
            }
            catch (NetworkError&) {
                CheckRebind();
                continue;
            }

            if (iFifoWaiting.SlotsUsed() == 0) {
                continue;
            }

            iFifoReady.Write(iDiscard);
            iDiscard = iFifoWaiting.Read();
        }

        iReadyLock.Wait();
        iFifoReady.ReadInterrupt(false);
        // Move all messages from ready queue back to waiting queue

        while (iFifoReady.SlotsUsed() > 0) {
            MsgUdp* msg = iFifoReady.Read();
            iFifoWaiting.Write(msg);
        }

        iFifoReady.ReadInterrupt(false);
        iReadyLock.Signal();

        iSocket.Interrupt(false);
        iSemaphore.Signal();
    }
}

void SocketUdpServer::PostRebind(TIpAddress aAddress, TUint aPort, Functor aCompleteFunctor)
{
    AutoMutex amx(iLock);

    iRebindJob = {
        .iAddress = aAddress,
        .iPort = aPort,
        .iCompleteFunctor = aCompleteFunctor,
    };

    iRebindPosted = true;
    iSocket.Interrupt(true);
}

void SocketUdpServer::CheckRebind()
{
    AutoMutex amx(iLock);

    if (iRebindPosted)
    {
        iSocket.ReBind(iRebindJob.iPort, iRebindJob.iAddress);
        iRebindPosted = false;
        iRebindJob.iCompleteFunctor(); // we have to call this with iLock held. Should be ok unless the
    }                                  // functor tries to take the lock: We have control of this, so it's cool.
}

void SocketUdpServer::CurrentAdapterChanged()
{
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    AutoNetworkAdapterRef ref(iEnv, "UdpServer::UpdateAdapter");
    NetworkAdapter* current = ref.Adapter();

    // Get current subnet, otherwise choose first from a list
    if (current == nullptr) {
        std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
        if (subnetList->size() > 0) {
            current = (*subnetList)[0];
        }
        NetworkAdapterList::DestroySubnetList(subnetList);
    }

    // Don't rebind if we have nothing to rebind to - should this ever be the case?
    if (current != nullptr) {
        Semaphore waiter("", 0);
        PostRebind(current->Address(), iSocket.Port(), MakeFunctor(waiter, &Semaphore::Signal));
        waiter.Wait();
    }
}


// UdpServerManager

UdpServerManager::UdpServerManager(Environment& aEnv, TUint aMaxSize, TUint aMaxPackets)
    : iEnv(aEnv)
    , iMaxSize(aMaxSize)
    , iMaxPackets(aMaxPackets)
    , iLock("USML")
{
}

UdpServerManager::~UdpServerManager()
{
    AutoMutex a(iLock);
    for (size_t i=0; i<iServers.size(); i++) {
        delete iServers[i];
    }
}

TUint UdpServerManager::CreateServer(TUint aPort, TIpAddress aInterface)
{
    AutoMutex a(iLock);
    SocketUdpServer* server = new SocketUdpServer(iEnv, iMaxSize, iMaxPackets, aPort, aInterface);
    iServers.push_back(server);
    return iServers.size()-1;
}

SocketUdpServer& UdpServerManager::Find(TUint aId)
{
    AutoMutex a(iLock);
    ASSERT(aId < iServers.size());
    return *(iServers[aId]);
}

void UdpServerManager::CloseAll()
{
    AutoMutex a(iLock);
    for (size_t i=0; i<iServers.size(); i++) {
        iServers[i]->Close();
    }
}

void UdpServerManager::OpenAll()
{
    AutoMutex a(iLock);
    for (size_t i=0; i<iServers.size(); i++) {
        iServers[i]->Open();
    }
}
