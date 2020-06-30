#ifndef HEADER_DVI_SERVER
#define HEADER_DVI_SERVER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Thread.h>

#include <vector>

namespace OpenHome {
namespace Net {

class DvStack;

class DviServer
{
public:
    virtual ~DviServer();
    TUint Port(TIpAddress aInterface);
    virtual void Start() = 0;
protected:
    DviServer(DvStack& aDvStack);
    void Initialise();
    void Deinitialise();
    virtual SocketTcpServer* CreateServer(const NetworkAdapter& aNif) = 0;
    virtual void NotifyServerDeleted(TIpAddress aInterface);
    virtual void NotifyServerCreated(TIpAddress aInterface);
private:
    void AddServer(NetworkAdapter& aNif);
    void SubnetListChanged();
    void SubnetListChangedLocked();
    TInt FindInterface(TIpAddress aInterface, const std::vector<NetworkAdapter*>& aNifList);
    TInt FindServer(TIpAddress aSubnet);
private:
    class Server : private INonCopyable
    {
    public:
        Server(SocketTcpServer* aTcpServer, NetworkAdapter& aNif);
        ~Server();
        TIpAddress Interface() const { return iNif.Address(); }
        TIpAddress Subnet() const { return iNif.Subnet(); }
        TUint Port() const { return iServer->Port(); }
    private:
        SocketTcpServer* iServer;
        NetworkAdapter& iNif;
    };
protected:
    DvStack& iDvStack;
private:
    Mutex iLock;
    std::vector<DviServer::Server*> iServers;
    TInt iSubnetListChangeListenerId;
    TInt iCurrentAdapterChangeListenerId;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_SERVER
