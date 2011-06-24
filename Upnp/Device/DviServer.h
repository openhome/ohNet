#ifndef HEADER_DVI_SERVER
#define HEADER_DVI_SERVER

#include <OhNetTypes.h>
#include <Network.h>
#include <OhNet.h>
#include <Thread.h>

#include <vector>

namespace OpenHome {
namespace Net {

class DviServer
{
public:
    ~DviServer();
    TUint Port(TIpAddress aInterface);
protected:
    DviServer();
    void Initialise();
    virtual SocketTcpServer* CreateServer(const NetworkInterface& aNif) = 0;
private:
    void AddServer(NetworkInterface& aNif);
    void SubnetListChanged();
    TInt FindInterface(TIpAddress aInterface, const std::vector<NetworkInterface*>& aNifList);
    TInt FindServer(TIpAddress aSubnet);
private:
    class Server : private INonCopyable
    {
    public:
        Server(SocketTcpServer* aTcpServer, NetworkInterface& aNif);
        ~Server();
        TIpAddress Interface() const { return iNif.Address(); }
        TIpAddress Subnet() const { return iNif.Subnet(); }
        TUint Port() const { return iServer->Port(); }
    private:
        SocketTcpServer* iServer;
        NetworkInterface& iNif;
    };
private:
    Mutex iLock;
    std::vector<DviServer::Server*> iServers;
    TInt iSubnetListChangeListenerId;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_SERVER
