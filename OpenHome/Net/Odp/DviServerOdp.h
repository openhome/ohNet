#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviServer.h>
#include <OpenHome/Net/Odp/DviOdp.h>

namespace OpenHome {
namespace Net {
    class DvStack;

class DviSessionOdp : public SocketTcpSession
                    , private IOdpSession
{
    static const Brn kUserAgentDefault;
public:
    DviSessionOdp(DvStack& aDvStack, TIpAddress aAdapter);
    ~DviSessionOdp();
private: // from SocketTcpSession
    void Run() override;
private: // from IOdpSession
    IWriter& WriteLock() override;
    void WriteUnlock() override;
    void WriteEnd() override;
    TIpAddress Adapter() const override;
    const Brx& ClientUserAgentDefault() const override;
private:
    static const TUint kMaxReadBytes = 12 * 1024;
    static const TUint kWriteBufferBytes = 4000;
    TIpAddress iAdapter;
    Mutex iWriteLock;
    Semaphore iShutdownSem;
    Srx* iReadBuffer;
    ReaderUntil* iReaderUntil;
    Sws<kWriteBufferBytes>* iWriteBuffer;
    DviOdp* iProtocol;
};

class DviServerOdp : public DviServer
{
public:
    DviServerOdp(DvStack& aDvStack, TUint aNumSessions, TUint aPort = 0);
    ~DviServerOdp();
    TUint Port() const;
private: // from DviServerUpnp
    SocketTcpServer* CreateServer(const NetworkAdapter& aNif) override;
    void NotifyServerDeleted(TIpAddress aInterface) override;
private:
    const TUint iNumSessions;
    TUint iPort;
};

} // namespace Net
} // namespace OpenHome
