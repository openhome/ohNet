#ifndef HEADER_OHM_SOCKET
#define HEADER_OHM_SOCKET

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Network.h>

#include "Ohm.h"

namespace OpenHome {
class Environment;
namespace Av {

class OhmSocket : public IReaderSource, public INonCopyable
{
    static const TUint kSendBufBytes = 16392;
    static const TUint kReceiveBufBytes = 16392;

public:
    OhmSocket(Environment& aEnv);
    void OpenUnicast(TIpAddress aInterface, TUint aTtl);
    void OpenMulticast(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint);
    Endpoint This() const;
    Endpoint Sender() const;
    void Send(const Brx& aBuffer, const Endpoint& aEndpoint);
    void Close();
    ~OhmSocket();

public:
	// IReaderSource
    virtual void Read(Bwx& aBuffer);
    virtual void ReadFlush();
    virtual void ReadInterrupt();

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

	const Endpoint& This() const;
	void Open(TIpAddress aInterface, TUint aTtl);
    void Send(const Brx& aBuffer);
    void Close();

    // IReaderSource
    virtual void Read(Bwx& aBuffer);
    virtual void ReadFlush();
    virtual void ReadInterrupt();
    
    ~OhzSocket();

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

