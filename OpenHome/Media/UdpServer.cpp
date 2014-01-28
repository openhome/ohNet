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

MsgUdp::MsgUdp(TUint aMaxSize, const Endpoint& aEndpoint)
    : iBuf(aMaxSize)
    ,iEndpoint(aEndpoint)
{
}

MsgUdp::~MsgUdp()
{
}

Bwx& MsgUdp::Buffer()
{
    return iBuf;
}

Endpoint& MsgUdp::GetEndpoint()
{
    return iEndpoint;
}

void MsgUdp::Clear()
{
    Endpoint ep(0, 0);
    iEndpoint.Replace(ep);
    iBuf.SetBytes(0);
}


// SocketUdpServer

SocketUdpServer::SocketUdpServer(Environment& aEnv, TUint aMaxSize, TUint aMaxPackets, TUint aPort, TIpAddress aInterface)
    : SocketUdp(aEnv, aPort, aInterface)
    , iEnv(aEnv)
    , iMaxSize(aMaxSize)
    , iOpen(true)
    , iFifoWaiting(aMaxPackets+1)
    , iFifoReady(aMaxPackets)
    , iWaitingLock("UDPW")
    , iReadyLock("UDPR")
    , iQuit(false)
    , iAdapterListenerId(0)
{
    // populate iFifoWaiting with empty packets/bufs
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
    iQuit = true;
    iOpen = false;
    Interrupt(true);
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
}

void SocketUdpServer::Open()
{
    iOpen = true;
}

void SocketUdpServer::Close()
{
    iOpen = false;

    // set an interrupt
    iFifoReady.ReadInterrupt(true);
    iFifoWaiting.ReadInterrupt(true);

    iReadyLock.Wait();
    // clear the interrupt, so next read doesn't throw an exception
    iFifoReady.ReadInterrupt(false);
    iFifoWaiting.ReadInterrupt(false);

    // dispose of all msgs in ready queue
    while (iFifoReady.SlotsUsed() > 0) {
        MsgUdp* msg = iFifoReady.Read();
        ClearAndRequeue(*msg);
    }
    iReadyLock.Signal();
}

Endpoint SocketUdpServer::Receive(Bwx& aBuf)
{
    ASSERT(iOpen);

    // get data from msg
    try {
        iReadyLock.Wait();
        MsgUdp* msg = iFifoReady.Read(); // will block until msg available
        iReadyLock.Signal();
        Endpoint ep;
        CopyMsgToBuf(*msg, aBuf, ep);

        // requeue msg
        ClearAndRequeue(*msg);

        return ep;
    }
    catch (FifoReadError) {
        THROW(NetworkError);
    }
}

void SocketUdpServer::ClearAndRequeue(MsgUdp& aMsg)
{
    // clear a msg and requeue it in the waiting fifo
    aMsg.Clear();
    iWaitingLock.Wait();
    ASSERT(iFifoWaiting.SlotsFree() > 0);
    iFifoWaiting.Write(&aMsg);
    iWaitingLock.Signal();
}

void SocketUdpServer::CopyMsgToBuf(MsgUdp& aMsg, Bwx& aBuf, Endpoint& aEndpoint)
{
    Bwx& buf = aMsg.Buffer();
    ASSERT(aBuf.MaxBytes() >= buf.Bytes());
    aBuf.Replace(buf);
    aEndpoint.Replace(aMsg.GetEndpoint());
}

void SocketUdpServer::ServerThread()
{
    // continually read incoming packets
    while (!iQuit) {

        MsgUdp* msg = NULL;
        // get next msg for reading data into
        try {
            msg = iFifoWaiting.Read();
        }
        catch (FifoReadError&) {
            continue;
        }

        try {
            Bwx& buf = msg->Buffer();
            ASSERT(buf.Bytes() == 0);
            Endpoint& ep = msg->GetEndpoint();
            ep.Replace(SocketUdp::Receive(buf));
        }
        catch (NetworkError&) {
            // nothing we can do to recover packet, or Interrupt has been
            // called as server is quitting
            ClearAndRequeue(*msg);
            continue;
        }

        // if server is open and iFifoReady has a free slot, queue packet
        if (iOpen && (iFifoReady.SlotsFree() > 0)) {
            iFifoReady.Write(msg);
        }
        else {
            ClearAndRequeue(*msg);
        }
    }
}

void SocketUdpServer::CurrentAdapterChanged()
{
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    AutoNetworkAdapterRef ref(iEnv, "UdpServer::UpdateAdapter");
    NetworkAdapter* current = ref.Adapter();

    // get current subnet, otherwise choose first from a list
    if (current == NULL) {
        std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
        if (subnetList->size() > 0) {
            current = (*subnetList)[0];
        }
        NetworkAdapterList::DestroySubnetList(subnetList);
    }

    // don't rebind if we have nothing to rebind to - should this ever be the case?
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
    for (size_t i=0; i<iServers.size(); i++) {
        iServers[i]->Close();
    }
}

void UdpServerManager::OpenAll()
{
    for (size_t i=0; i<iServers.size(); i++) {
        iServers[i]->Open();
    }
}
