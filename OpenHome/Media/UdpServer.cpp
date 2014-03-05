#include <OpenHome/Media/UdpServer.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace Media;


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
    : SocketUdp(aEnv, aPort, aInterface)
    , iEnv(aEnv)
    , iMaxSize(aMaxSize)
    , iOpen(true)
    , iFifoWaiting(aMaxPackets)
    , iFifoReady(aMaxPackets)
    , iLock("UDPL")
    , iSemaphore("UDPS", 0)
    , iQuit(false)
    , iAdapterListenerId(0)
{
    // Populate iFifoWaiting with empty packets/bufs
    while (iFifoWaiting.SlotsFree() > 0) {
        iFifoWaiting.Write(new MsgUdp(iMaxSize));
    }

    iDiscard = new MsgUdp(iMaxSize);

    Functor functor = MakeFunctor(*this, &SocketUdpServer::CurrentAdapterChanged);
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    iAdapterListenerId = nifList.AddCurrentChangeListener(functor, false);

    iServerThread = new ThreadFunctor("UdpServer", MakeFunctor(*this, &SocketUdpServer::ServerThread));
    iServerThread->Start();
}

SocketUdpServer::~SocketUdpServer()
{
    iLock.Wait();

    if (iQuit)
    {
        iLock.Signal();
        ASSERTS();
    }

    iQuit = true;

    iLock.Signal();

    Interrupt(true);
    iFifoReady.ReadInterrupt(true);

    delete iServerThread;

    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    nifList.RemoveCurrentChangeListener(iAdapterListenerId);

    while (iFifoReady.SlotsUsed() > 0) {
        MsgUdp* msg = iFifoReady.Read();
        delete msg;
    }

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
    Interrupt(true);

    iLock.Signal();

    iSemaphore.Wait();
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

    Interrupt(true);
    iFifoReady.ReadInterrupt(true);

    iLock.Signal();

    iSemaphore.Wait();

    Interrupt(false);
    iFifoReady.ReadInterrupt(false);
}

Endpoint SocketUdpServer::Receive(Bwx& aBuf)
{
    iLock.Wait();

    if (iQuit || !iOpen) { // allows this assertion to be unit testable
        iLock.Signal();
        ASSERTS();
    }

    iLock.Signal();

    // Get data from msg
    try {
        MsgUdp* msg = iFifoReady.Read(); // will block until msg available

        Endpoint ep;
        CopyMsgToBuf(*msg, aBuf, ep);

        // Requeue msg
        iLock.Wait();

        iFifoWaiting.Write(msg);

        iLock.Signal();

        return ep;
    }
    catch (FifoReadError&) {
        THROW(NetworkError);
    }
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
    for (;;) {

        // opened

        Interrupt(false);

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
                iDiscard->Read(*this);
            }
            catch (NetworkError&) {
                continue;
            }

            if (iFifoWaiting.SlotsUsed() == 0) {
                continue;
            }

            MsgUdp* msg = iFifoWaiting.Read();
            iFifoReady.Write(iDiscard);
            iDiscard = msg;
        }

        iFifoReady.ReadInterrupt(false);
        // Move all messages from ready queue back to waiting queue

        while (iFifoReady.SlotsUsed() > 0) {
            MsgUdp* msg = iFifoReady.Read();
            iFifoWaiting.Write(msg);
        }

        iSemaphore.Signal();


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
                iDiscard->Read(*this);
            }
            catch (NetworkError&) {
            }
        }

        iSemaphore.Signal();
    }
}

void SocketUdpServer::CurrentAdapterChanged()
{
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    AutoNetworkAdapterRef ref(iEnv, "UdpServer::UpdateAdapter");
    NetworkAdapter* current = ref.Adapter();

    // Get current subnet, otherwise choose first from a list
    if (current == NULL) {
        std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
        if (subnetList->size() > 0) {
            current = (*subnetList)[0];
        }
        NetworkAdapterList::DestroySubnetList(subnetList);
    }

    // Don't rebind if we have nothing to rebind to - should this ever be the case?
    if (current != NULL) {
        ReBind(iPort, current->Address());
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
