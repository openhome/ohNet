#ifndef HEADER_OHM_SOCKET
#define HEADER_OHM_SOCKET

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Network.h>

#include "Ohm.h"

namespace OpenHome {
class Environment;
namespace Av {

class OhmSocket : public IReaderSource, public INonCopyable
{
    static const TUint kSendBufBytes = 16 * 1024;
    static const TUint kReceiveBufBytes = 64 * 1024;
public:
    OhmSocket(Environment& aEnv);
    ~OhmSocket();
    void OpenUnicast(TIpAddress aInterface, TUint aTtl);
    void OpenMulticast(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint);
    Endpoint This() const;
    Endpoint Sender() const;
    void Send(const Brx& aBuffer, const Endpoint& aEndpoint);
    void Close();
    void Interrupt(TBool aInterrupt);
public: // from IReaderSource
    void Read(Bwx& aBuffer) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    Environment& iEnv;
    SocketUdpBase* iRxSocket;
    SocketUdpBase* iTxSocket;
    UdpReader* iReader;
    Endpoint iThis;
};

class OhzSocket : public IReaderSource, public INonCopyable
{
    static const TUint kSendBufBytes = 1024;
public:
    OhzSocket(Environment& aEnv);
    ~OhzSocket();

    const Endpoint& This() const;
    void Open(TIpAddress aInterface, TUint aTtl);
    void Send(const Brx& aBuffer);
    void Close();
public: // from IReaderSource
    void Read(Bwx& aBuffer) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    Environment& iEnv;
    SocketUdpMulticast* iRxSocket;
    SocketUdp* iTxSocket;
    Endpoint iEndpoint;
    UdpReader* iReader;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_OHM_SOCKET
