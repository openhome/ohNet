#include "OhmSocket.h"
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Av;

// OhmSocket

// Sends on same socket in Unicast mode, but different socket in Multicast mode

OhmSocket::OhmSocket(Environment& aEnv)
    : iEnv(aEnv)
    , iRxSocket(0)
    , iTxSocket(0)
    , iReader(0)
    , iLock("OHMS")
    , iInterrupt(false)
{
}

OhmSocket::~OhmSocket()
{
    if (iRxSocket != 0) {
        Close();
    }
}

void OhmSocket::OpenUnicast(TIpAddress aInterface, TUint aTtl)
{
    AutoMutex _(iLock);
    ASSERT(!iRxSocket);
    ASSERT(!iTxSocket);
    ASSERT(!iReader);
    iRxSocket = new SocketUdp(iEnv, 0, aInterface);
    iRxSocket->SetTtl(aTtl);
    iRxSocket->SetRecvBufBytes(kReceiveBufBytes);
    if (iInterrupt) {
        iRxSocket->Interrupt(true);
    }
//    iRxSocket->SetSendBufBytes(kSendBufBytes);    // hangs in lwip, use default allocation for now - ToDo
    iReader = new UdpReader(*iRxSocket);
    iThis.Replace(Endpoint(iRxSocket->Port(), aInterface));
}

void OhmSocket::OpenMulticast(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint)
{
    AutoMutex _(iLock);
    ASSERT(!iRxSocket);
    ASSERT(!iTxSocket);
    ASSERT(!iReader);
    iRxSocket = new SocketUdpMulticast(iEnv, aInterface, aEndpoint);
    iRxSocket->SetRecvBufBytes(kReceiveBufBytes);
    iTxSocket = new SocketUdp(iEnv, 0, aInterface);
    iTxSocket->SetTtl(aTtl);
    if (iInterrupt) {
        iRxSocket->Interrupt(true);
        iTxSocket->Interrupt(true);
    }
//    iTxSocket->SetSendBufBytes(kSendBufBytes);    // hangs in lwip, use default allocation for now - ToDo
    iReader = new UdpReader(*iRxSocket);
    iThis.Replace(aEndpoint);
}

void OhmSocket::Send(const Brx& aBuffer, const Endpoint& aEndpoint)
{
    if (iTxSocket != nullptr) {
        iTxSocket->Send(aBuffer, aEndpoint);
    }
    else if (iRxSocket != nullptr) {
        iRxSocket->Send(aBuffer, aEndpoint);
    }
}

Endpoint OhmSocket::This() const
{
    return iThis;
}

Endpoint OhmSocket::Sender() const
{
    ASSERT(iReader);
    return iReader->Sender();
}

void OhmSocket::Close()
{
    AutoMutex _(iLock);
    iInterrupt = false;
    delete iReader;
    iReader = nullptr;
    delete iRxSocket;
    iRxSocket = nullptr;
    delete iTxSocket;
    iTxSocket = nullptr;
}

void OhmSocket::Interrupt(TBool aInterrupt)
{
    AutoMutex _(iLock);
    iInterrupt = aInterrupt;
    if (iRxSocket != nullptr) {
        iRxSocket->Interrupt(aInterrupt);
    }
    if (iTxSocket != nullptr) {
        iTxSocket->Interrupt(aInterrupt);
    }
}

void OhmSocket::Read(Bwx& aBuffer)
{
    ASSERT(iReader);
    iReader->Read(aBuffer);
}

void OhmSocket::ReadFlush()
{
    if (iReader != nullptr) {
        iReader->ReadFlush();
    }
}

void OhmSocket::ReadInterrupt()
{
    if (iReader != nullptr) {
        iReader->ReadInterrupt();
    }
}


// OhzSocket

OhzSocket::OhzSocket(Environment& aEnv)
    : iEnv(aEnv)
    , iRxSocket(0)
    , iTxSocket(0)
    , iEndpoint(51972, Brn("239.255.255.250"))
{
}

OhzSocket::~OhzSocket()
{
    if (iRxSocket != 0) {
        Close();
    }
}

const Endpoint& OhzSocket::This() const
{
    return iEndpoint;
}

void OhzSocket::Open(TIpAddress aInterface, TUint aTtl)
{
    ASSERT(!iRxSocket);
    iRxSocket = new SocketUdpMulticast(iEnv, aInterface, iEndpoint);
    iTxSocket = new SocketUdp(iEnv, 0, aInterface);
    iTxSocket->SetTtl(aTtl);
    iReader = new UdpReader(*iRxSocket);
}

void OhzSocket::Send(const Brx& aBuffer)
{
    ASSERT(iTxSocket);
    iTxSocket->Send(aBuffer, iEndpoint);
}

void OhzSocket::Close()
{
    ASSERT(iRxSocket);
    delete iRxSocket;
    delete iTxSocket;
    delete iReader;
    iRxSocket = 0;
    iTxSocket = 0;
    iReader = 0;
}
    
void OhzSocket::Read(Bwx& aBuffer)
{
    ASSERT(iRxSocket);
    iReader->Read(aBuffer);
}

void OhzSocket::ReadFlush()
{
    ASSERT(iRxSocket != 0);
    iReader->ReadFlush();
}

void OhzSocket::ReadInterrupt()
{
    ASSERT(iRxSocket != 0);
    iReader->ReadInterrupt();
}
