#include <OpenHome/Net/Private/DviServer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/TIpAddressUtils.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DviServer

DviServer::~DviServer()
{
}

void DviServer::Deinitialise()
{
    iLock.Wait();
    iDvStack.Env().NetworkAdapterList().RemoveCurrentChangeListener(iCurrentAdapterChangeListenerId);
    iDvStack.Env().NetworkAdapterList().RemoveSubnetListChangeListener(iSubnetListChangeListenerId);
    iLock.Signal();
    for (TUint i=0; i<iServers.size(); i++) {
        DviServer::Server* server = iServers[i];
        NotifyServerDeleted(server->Interface());
        delete server;
    }
    iServers.clear();
}

TUint DviServer::Port(const TIpAddress& aInterface)
{
    AutoMutex a(iLock);
    for (TUint i=0; i<iServers.size(); i++) {
        DviServer::Server* server = iServers[i];
        if (TIpAddressUtils::Equal(server->Interface(), aInterface)) {
            return server->Port();
        }
    }
    return 0;
}

DviServer::DviServer(DvStack& aDvStack)
    : iDvStack(aDvStack)
    , iLock("DSUM")
    , iSubnetListChangeListenerId(NetworkAdapterList::kListenerIdNull)
    , iCurrentAdapterChangeListenerId(NetworkAdapterList::kListenerIdNull)
{
}

void DviServer::Initialise()
{
    AutoMutex a(iLock); // ensure initialisation completes before change listeners are run
    Functor functor = MakeFunctor(*this, &DviServer::SubnetListChanged);
    NetworkAdapterList& nifList = iDvStack.Env().NetworkAdapterList();
    iCurrentAdapterChangeListenerId = nifList.AddCurrentChangeListener(functor, "DviServer-current");
    iSubnetListChangeListenerId = nifList.AddSubnetListChangeListener(functor, "DviServer-subnet");
    SubnetListChangedLocked();
}

void DviServer::NotifyServerDeleted(const TIpAddress& /*aInterface*/)
{
}

void DviServer::NotifyServerCreated(const TIpAddress& /*aInterface*/)
{
}

void DviServer::AddServer(NetworkAdapter& aNif)
{
    SocketTcpServer* tcpServer = CreateServer(aNif);
    DviServer::Server* server = new DviServer::Server(tcpServer, aNif);
    iServers.push_back(server);
    NotifyServerCreated(aNif.Address());
}

void DviServer::SubnetListChanged()
{
    AutoMutex a(iLock);
    SubnetListChangedLocked();
}

void DviServer::SubnetListChangedLocked()
{
    /* DviProtocolUpnp relies on servers being available on all appropriate interfaces.
       We assume this happens through DviServer being created before any devices
       so registering for subnet change notification earlier.  Assuming NetworkAdapterList
       always runs its listeners in the order they registered, we'll have updated before
       any device listeners are run. */

    TIpAddress kLoopbackAddr;
    kLoopbackAddr.family = kFamilyV4;
    kLoopbackAddr.v4 = MakeIpAddress(127, 0, 0, 1);
    NetworkAdapterList& adapterList = iDvStack.Env().NetworkAdapterList();
    AutoNetworkAdapterRef ref(iDvStack.Env(), "DviServer::SubnetListChanged");
    NetworkAdapter* current = ref.Adapter();
    std::vector<NetworkAdapter*>* subnetList = adapterList.CreateSubnetList();
    std::vector<NetworkAdapter*>* nifList = adapterList.CreateNetworkAdapterList();
    TInt i;
    // remove servers whose interface is no longer available
    for (i = (TInt)iServers.size() - 1; i >= 0; i--) {
        DviServer::Server* server = iServers[i];
        if (FindInterface(server->Interface(), *nifList) == -1
            || (adapterList.SingleSubnetModeEnabled()
            && (current == NULL || !TIpAddressUtils::Equal(server->Interface(), current->Address())))) {
            NotifyServerDeleted(server->Interface());
            delete server;
            iServers.erase(iServers.begin() + i);
        }
    }
    // add servers for new subnets
    for (i = 0; i < (TInt)subnetList->size(); i++) {
        NetworkAdapter* subnet = (*subnetList)[i];
        if (FindServer(subnet->Subnet()) == -1
            && (!adapterList.SingleSubnetModeEnabled() ||
               (current != NULL && TIpAddressUtils::Equal(subnet->Address(), current->Address())) ||
                TIpAddressUtils::Equal(subnet->Address(), kLoopbackAddr))) {
                AddServer(*subnet);
        }
    }
    NetworkAdapterList::DestroyNetworkAdapterList(nifList);
    NetworkAdapterList::DestroySubnetList(subnetList);
}

TInt DviServer::FindInterface(const TIpAddress& aInterface, const std::vector<NetworkAdapter*>& aNifList)
{
    for (TUint i=0; i<aNifList.size(); i++) {
        if (TIpAddressUtils::Equal(aNifList[i]->Address(), aInterface)) {
            return i;
        }
    }
    return -1;
}

TInt DviServer::FindServer(const TIpAddress& aSubnet)
{
    for (TUint i=0; i<iServers.size(); i++) {
        if (TIpAddressUtils::Equal(iServers[i]->Subnet(), aSubnet)) {
            return i;
        }
    }
    return -1;
}


//  DviServer::Server

DviServer::Server::Server(SocketTcpServer* aTcpServer, NetworkAdapter& aNif)
    : iNif(aNif)
{
    iServer = aTcpServer;
    iNif.AddRef("DviServer::Server");

    /*Endpoint endpt(aTcpServer->Port(), aNif.Address());
    Endpoint::EndpointBuf buf;
    endpt.AppendEndpoint(buf);
    Log::Print("--new server at %s\n\n", buf.Ptr());*/
}

DviServer::Server::~Server()
{
    try {
        delete iServer;
        iNif.RemoveRef("DviServer::Server");
    }
    catch (NetworkError& aEx) {
        Log::Print("Error: DviServer::Server::~Server threw NetworkError from %s:%u\n", aEx.File(), aEx.Line());
        ASSERTS();
    }
}
