#ifndef HEADER_DVI_SERVER
#define HEADER_DVI_SERVER

#include <ZappTypes.h>
#include <Network.h>
#include <Zapp.h>
#include <Thread.h>

#include <vector>

namespace Zapp {

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
    void AddServer(const NetworkInterface& aNif);
    void SubnetChanged();
    TInt FindInterface(TIpAddress aInterface, const std::vector<NetworkInterface*>& aNifList);
    TInt FindServer(TIpAddress aSubnet);
private:
    class Server
    {
    public:
        Server(SocketTcpServer* aTcpServer, const NetworkInterface& aNif);
        ~Server();
        TIpAddress Interface() const { return iNif->Address(); }
        TIpAddress Subnet() const { return iNif->Subnet(); }
        TUint Port() const { return iServer->Port(); }
    private:
        Server() {}
    private:
        SocketTcpServer* iServer;
        NetworkInterface* iNif;
    };
private:
    Mutex iLock;
    std::vector<DviServer::Server*> iServers;
    TInt iSubnetChangeListenerId;
};

} // namespace Zapp

#endif // HEADER_DVI_SERVER
