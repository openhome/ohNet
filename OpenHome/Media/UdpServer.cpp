#include <OpenHome/Media/UdpServer.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace Media;


// MsgUdp

MsgUdp::MsgUdp(TUint aMaxSize)
    : iBuf(aMaxSize)
    , iEndpoint()
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
// FIXME - add an InfoProvider
SocketUdpServer::SocketUdpServer(Environment& aEnv, TUint aMaxSize, TUint aMaxPackets, TUint aPort, TIpAddress aInterface)
    : SocketUdp(aEnv, aPort, aInterface)
    , iEnv(aEnv)
    , iMaxSize(aMaxSize)
    , iOpen(true)
    , iFifoWaiting(aMaxPackets+1)
    , iFifoReady(aMaxPackets)
    , iWaitingLock("UDPW")
    , iReadyLock("UDPR")
    , iLock("UDPL")
    , iQuit(false)
    , iAdapterListenerId(0)
{
    // Populate iFifoWaiting with empty packets/bufs
    while (iFifoWaiting.SlotsFree() > 0) {
        iFifoWaiting.Write(new MsgUdp(iMaxSize));
    }

    Functor functor = MakeFunctor(*this, &SocketUdpServer::CurrentAdapterChanged);
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    iAdapterListenerId = nifList.AddCurrentChangeListener(functor, false);

    iServerThread = new ThreadFunctor("UdpServer", MakeFunctor(*this, &SocketUdpServer::ServerThread));
    iServerThread->Start();
}

SocketUdpServer::~SocketUdpServer()
{
    iLock.Wait();
    iQuit = true;
    iOpen = false;
    iLock.Signal();
    Interrupt(true);
    delete iServerThread;

    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    nifList.RemoveCurrentChangeListener(iAdapterListenerId);

    iReadyLock.Wait();
    while (iFifoReady.SlotsUsed() > 0) {
        MsgUdp* msg = iFifoReady.Read();
        delete msg;
    }
    iReadyLock.Signal();
    iWaitingLock.Wait();
    while (iFifoWaiting.SlotsUsed() > 0) {
        MsgUdp* msg = iFifoWaiting.Read();
        delete msg;
    }
    iWaitingLock.Signal();
}

void SocketUdpServer::Open()
{
    AutoMutex a(iLock);
    iOpen = true;
}

void SocketUdpServer::Close()
{
    iLock.Wait();
    iOpen = false;
    iLock.Signal();

    // Set an interrupt
    iFifoReady.ReadInterrupt(true);
    iFifoWaiting.ReadInterrupt(true);

    // Clear FIFO interrupts, in case no Read() call was interrupted.
    iWaitingLock.Wait();
    iFifoWaiting.ReadInterrupt(false);
    iWaitingLock.Signal();

    iReadyLock.Wait();
    iFifoReady.ReadInterrupt(false);
    // Dispose of all msgs in ready queue
    while (iFifoReady.SlotsUsed() > 0) {
        MsgUdp* msg = iFifoReady.Read();
        Requeue(*msg);
    }
    iReadyLock.Signal();
}

Endpoint SocketUdpServer::Receive(Bwx& aBuf)
{
    iLock.Wait();
    if (!iOpen) { // allows this assertion to be unit testable
        iLock.Signal();
        ASSERTS();
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
        Requeue(*msg);

        return ep;
    }
    catch (FifoReadError) {
        iFifoReady.ReadInterrupt(false);
        iReadyLock.Signal();
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

void SocketUdpServer::Requeue(MsgUdp& aMsg)
{
    // Requeue msg into the waiting fifo
    iWaitingLock.Wait();
    ASSERT(iFifoWaiting.SlotsFree() > 0);
    iFifoWaiting.Write(&aMsg);
    iWaitingLock.Signal();
}

void SocketUdpServer::ServerThread()
{
    // Continually read incoming packets
    for (;;) {

        iLock.Wait();
        if (iQuit) {
            iLock.Signal();
            return;
        }
        iLock.Signal();

        MsgUdp* msg = NULL;
        // Get next msg for reading data into
        try {
            iWaitingLock.Wait();
            msg = iFifoWaiting.Read();
            iWaitingLock.Signal();
        }
        catch (FifoReadError&) {
            iFifoWaiting.ReadInterrupt(false);
            iWaitingLock.Signal();
            continue;
        }

        try {
            msg->Read(*this);
        }
        catch (NetworkError&) {
            // Nothing we can do to recover packet, or Interrupt has been
            // called as server is quitting.
            Requeue(*msg);
            continue;
        }

        // if server is open and iFifoReady has a free slot, queue packet
        iLock.Wait();
        iReadyLock.Wait();
        if (iOpen && (iFifoReady.SlotsFree() > 0)) {
            iFifoReady.Write(msg);
        }
        else {
            Requeue(*msg);
        }
        iReadyLock.Signal();
        iLock.Signal();
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
