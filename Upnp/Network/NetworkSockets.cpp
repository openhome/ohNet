#include <Network.h>
#include <Arch.h>
#include <Os.h>
#include <Debug.h>
#include <Functor.h>
#include <Stream.h>
#include <Stack.h>

using namespace Zapp;

// OS sockets interface

static THandle SocketCreate(ESocketType aSocketType)
{
    LOGF(kNetwork, "SocketCreate  ST = %d, \n", aSocketType);
    THandle handle = Zapp::Os::NetworkCreate(aSocketType);
    LOGF(kNetwork, "SocketCreate  Socket H = %d\n", handle);
    return handle;
}

static void SocketSend(THandle aHandle, const Brx& aBuffer)
{
    LOGF(kNetwork, "SocketSend  H = %d, BC = %d\n", aHandle, aBuffer.Bytes());
    TInt sent = Zapp::Os::NetworkSend(aHandle, aBuffer);
    if(sent < 0) {
        LOG2F(kNetwork, kError, "SocketSend H = %d, RETURN VALUE = %d\n", aHandle, sent);
        THROW(NetworkError);
    }
    if((TUint)sent != aBuffer.Bytes()) {
        LOG2F(kNetwork, kError, "SocketSend H = %d, RETURN VALUE = %d, INCOMPLETE\n", aHandle, sent);
        THROW(NetworkError);
    }
}

static void SocketSendTo(THandle aHandle, const Brx& aBuffer, const Endpoint& aEndpoint)
{
    LOGF(kNetwork, "SocketSendTo  H = %d, BC = %d\n", aHandle, aBuffer.Bytes());
    TInt sent = Zapp::Os::NetworkSendTo(aHandle, aBuffer, aEndpoint);
    if(sent < 0) {
        LOG2F(kNetwork, kError, "SocketSendTo H = %d, RETURN VALUE = %d\n", aHandle, sent);
        THROW(NetworkError);
    }
    if((TUint)sent != aBuffer.Bytes()) {
        LOG2F(kNetwork, kError, "SocketSendTo H = %d, RETURN VALUE = %d, INCOMPLETE\n", aHandle, sent);
        THROW(NetworkError);
    }
}

static void SocketReceive(THandle aHandle, Bwx& aBuffer)
{
    // This variant of Receive will receive any number of bytes in the
    // range [0, aBuffer.MaxBytes()] (0 means socket was closed at the other end)
    LOGF(kNetwork, ">SocketReceive H = %d, MAX = %d\n", aHandle, aBuffer.MaxBytes());
    aBuffer.SetBytes(0);
    TInt received = Zapp::Os::NetworkReceive(aHandle, aBuffer);
    if(received < 0) {
        LOG2F(kNetwork, kError, "SocketReceive H = %d, RETURN VALUE = %d\n", aHandle, received);
        THROW(NetworkError);
    }
    aBuffer.SetBytes(received);
    LOGF(kNetwork, "<SocketReceive H = %d, BC = %d\n", aHandle, aBuffer.Bytes());
}

static void SocketReceive(THandle aHandle, Bwx& aBuffer, TUint aBytes)
{
    // This variant of Receive() expects the specified number of bytes. Therefore it will:
    //  - block until aBytes bytes have been received, or
    //  - throw a NetworkError on a genuine socket error OR if the socket
    //    is closed at the other end
    LOGF(kNetwork, "SocketReceive H = %d, BC = %d\n", aHandle, aBytes);

    ASSERT(aBytes <= aBuffer.MaxBytes());
    TUint received = 0;
    aBuffer.SetBytes(0);
    TByte* ptr = (TByte*)aBuffer.Ptr();
    while(received < aBytes) {
        Bwn buf(ptr+received, aBytes-received);
        TInt ret = Zapp::Os::NetworkReceive(aHandle, buf);
        if(ret < 0) {
            LOG2F(kNetwork, kError, "SocketReceive H = %d, RETURN VALUE = %d\n", aHandle, ret);
            THROW(NetworkError);
        } else if(ret == 0) {
            // not all requested data received before connection closed
            THROW(NetworkError);
        }
        LOGF(kNetwork, "SocketReceive H = %d, BYTES = %d\n", aHandle, ret);
        received += ret;
        aBuffer.SetBytes(received);
    }
}

static void SocketReceiveFrom(THandle aHandle, Bwx& aBuffer, Endpoint& aEndpoint)
{
    LOGF(kNetwork, "SocketReceiveFrom H = %d\n", aHandle);
    TInt received = Zapp::Os::NetworkReceiveFrom(aHandle, aBuffer, aEndpoint);
    if(received < 0) {
        LOG2F(kNetwork, kError, "SocketReceiveFrom H = %d, RETURN VALUE = %d\n", aHandle, received);
        THROW(NetworkError);
    }
    aBuffer.SetBytes(received);
}

static void SocketInterrupt(THandle aHandle, TBool aInterrupt)
{
    LOGF(kNetwork, "SocketShutdown H = %d\n", aHandle);
    TInt err = Zapp::Os::NetworkInterrupt(aHandle, aInterrupt);
    if(err != 0) {
        LOG2F(kNetwork, kError, "SocketShutdown H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

static void SocketClose(THandle aHandle)
{
    LOGF(kNetwork, "SocketClose H = %d\n", aHandle);
    TInt err = Zapp::Os::NetworkClose(aHandle);
    if(err != 0) {
        LOG2F(kNetwork, kError, "SocketClose H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

static void SocketBind(THandle aHandle, TUint& aPort, TIpAddress aInterface)
{
    LOGF(kNetwork, "SocketBind H = %d\n", aHandle);
    Endpoint endpt(aPort, aInterface);
    TInt err = Zapp::Os::NetworkBind(aHandle, endpt);
    if(err != 0) {
        LOG2F(kNetwork, kError, "SocketBind H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
	aPort = endpt.Port();
}

static void SocketListen(THandle aHandle, TUint aSlots)
{
    LOGF(kNetwork, "SocketListen H = %d S = %d\n", aHandle, aSlots);
    TInt err = Zapp::Os::NetworkListen(aHandle, aSlots);
    if(err != 0) {
        LOG2F(kNetwork, kError, "SocketListen H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

static THandle SocketAccept(THandle aHandle)
{
    LOGF(kNetwork, "SocketAccept H = %d\n", aHandle);
    THandle handle = Zapp::Os::NetworkAccept(aHandle);
    LOGF(kNetwork,"SocketAccept Accepted Handle = %d\n", handle);
    if(handle == kHandleNull) {
        LOG2F(kNetwork, kError, "SocketAccept H = %d\n", handle);
        THROW(NetworkError);
    }
    return handle;
}

static TUint32 GetHostByName(const Brx& aAddress)
{
    return Zapp::Os::NetworkGetHostByName(aAddress);
}


// Endpoint

Endpoint::Endpoint()
{
    iAddress = 0;
    iPort = 0;
}

// Construct endpoint with supplied address and port
Endpoint::Endpoint(TUint aPort, const Brx& aAddress)
{
    SetPort(aPort);
    SetAddress(aAddress);
}

Endpoint::Endpoint(TUint aPort, TIpAddress aAddress)
{
    iAddress = aAddress;
    iPort = (TUint16)aPort;
}

// Replace the endpoint port with the supplied port
void Endpoint::SetPort(TUint aPort)
{
    iPort = (TUint16)aPort;
}

// Replace the endpoint port with the port from the supplied endpoint
void Endpoint::SetPort(const Endpoint& aEndpoint)
{
    iPort = aEndpoint.iPort;
}

// Replace the endpoint address with the supplied address string
void Endpoint::SetAddress(const Brx& aAddress)
{
    iAddress = GetHostByName(aAddress);
}

void Endpoint::SetAddress(TIpAddress aAddress)
{
    iAddress = aAddress;
}

// Replace the endpoint address with the address from the supplied endpoint
void Endpoint::SetAddress(const Endpoint& aEndpoint)
{
    iAddress = aEndpoint.iAddress;
}

TIpAddress Endpoint::Address() const
{
    return iAddress;
}

TUint16 Endpoint::Port() const
{
    return iPort;
}

// Replace the endpoint with the supplied endpoint
void Endpoint::Replace(const Endpoint& aEndpoint)
{
    SetAddress(aEndpoint);
    SetPort(aEndpoint);
}

// Test if this endpoint is equal to the specified endpoint
TBool Endpoint::Equals(const Endpoint& aEndpoint) const
{
    return (iAddress==aEndpoint.iAddress && iPort==aEndpoint.iPort);
}

// Socket

Socket::Socket()
{
    iHandle = kHandleNull;
}

void Socket::Interrupt(TBool aInterrupt)
{
    LOGF(kNetwork, "Socket::Shutdown\n");
    SocketInterrupt(iHandle, aInterrupt);
}

void Socket::Close()
{
    LOGF(kNetwork, "Socket::Close\n");
    // close connection and allow caller to handle any exceptions
    SocketClose(iHandle);
    iHandle = kHandleNull;
}

void Socket::SetSendBufBytes(TUint aBytes)
{
    Zapp::Os::NetworkSocketSetSendBufBytes(iHandle, aBytes);
}

void Socket::SetRecvTimeout(TUint aMs)
{
    Zapp::Os::NetworkSocketSetReceiveTimeout(iHandle, aMs);
}

// AutoSocket

AutoSocket::AutoSocket(Socket& aSocket)
    : iSocket(aSocket)
{
}

AutoSocket::~AutoSocket()
{
    iSocket.Close();
}

// Tcp socket base class

SocketTcp::SocketTcp()
{
    LOGF(kNetwork, "SocketTcp::SocketTcp\n");
}

void SocketTcp::Receive(Bwx& aBuffer, TUint aBytes)
{
    LOGF(kNetwork, "SocketTcp::Receive only %d bytes\n", aBytes);
    SocketReceive(iHandle, aBuffer, aBytes);
}

void SocketTcp::Write(TByte aValue)
{
    Brn buf(&aValue, 1);
    Write(buf);
}

void SocketTcp::Write(const Brx& aBuffer)
{
    LOGF(kNetwork, "SocketTcp::Write\n");
    try {
        SocketSend(iHandle, aBuffer);
    }
    catch(NetworkError&) {
        THROW(WriterError);
    }
}

void SocketTcp::WriteFlush()
{
    // all writes go directly to the socket so nothing to flush
}

void SocketTcp::Read(Bwx& aBuffer)
{
    LOGF(kNetwork, ">SocketTcp::Read\n");
    try {
        SocketReceive(iHandle, aBuffer);
    }
    catch(NetworkError&) {
        THROW(ReaderError);
    }

    if (aBuffer.Bytes() == 0) {
        THROW(ReaderError);
    }
    
    LOGF(kNetwork, "<SocketTcp::Read\n");
}

void SocketTcp::ReadFlush()
{
    // no buffering at this level so nothing to flush
}

void SocketTcp::ReadInterrupt()
{
    Interrupt(true);
}


// Tcp client

void SocketTcpClient::Open()
{
    LOGF(kNetwork, "SocketTcpClient::Open\n");
    iHandle = SocketCreate(eSocketTypeStream);
    Zapp::Os::NetworkTcpSetNoDelay(iHandle);
}

void SocketTcpClient::Connect(const Endpoint& aEndpoint, TUint aTimeout)
{
    LOGF(kNetwork, "SocketTcpClient::Connect\n");
    Zapp::Os::NetworkConnect(iHandle, aEndpoint, aTimeout);
}

// Tcp Server

SocketTcpServer::SocketTcpServer(const TChar* aName, TUint aPort, TIpAddress aInterface,
                                 TUint aSessionPriority, TUint aSessionStackBytes, TUint aSlots)
    : iMutex(aName)
    , iSessionPriority(aSessionPriority)
    , iSessionStackBytes(aSessionStackBytes)
    , iTerminating(false)
{
    LOGF(kNetwork, "SocketTcpServer::SocketTcpServer\n");
    iHandle = SocketCreate(eSocketTypeStream);
    Zapp::Os::NetworkSocketSetReuseAddress(iHandle);
    Zapp::Os::NetworkTcpSetNoDelay(iHandle);
	iInterface = aInterface;
    iPort = aPort;
    SocketBind(iHandle, iPort, aInterface);
    SocketListen(iHandle, aSlots);
}

void SocketTcpServer::Add(const TChar* aName, SocketTcpSession* aSession, TInt aPriorityOffset)
{
    LOGF(kNetwork, "SocketTcpServer::Add\n");
    iVector.push_back(aSession);                    // Can only throw std::bad_alloc. Don't bother to cleanup as we consider this
                                                    // a fatal exception anyway.
    try {
        aSession->Add(*this, aName, iSessionPriority + aPriorityOffset, iSessionStackBytes);
    }
    catch ( ... ) {                                 // Don't handle the exception per se, just perform cleanup and pass it on.
        iVector.pop_back();
        delete aSession;
        throw;
    }
}

THandle SocketTcpServer::Accept()
{
    LOGF(kNetwork, "SocketTcpServer::Accept\n");
    iMutex.Wait();                                    // wait to become the single accepting thread
    if (iTerminating) {
        iMutex.Signal();                              // signal for next session thread to become the accepting thread
        THROW(NetworkError);
    }

    THandle handle;
    try {
        handle = SocketAccept(iHandle);    // accept the connection
        iMutex.Signal();
        return (handle);
    }
    catch (NetworkError&) {  // server handle closed by destructor
    }

    iMutex.Signal();    // signal for next session thread to become the accepting thread
    THROW(NetworkError);
}

TBool SocketTcpServer::Terminating()
{
    LOGF(kNetwork, "SocketTcpServer::Terminating %d\n", iTerminating);
    return (iTerminating);
}

SocketTcpServer::~SocketTcpServer()
{
    LOGF(kNetwork, ">SocketTcpServer::~SocketTcpServer\n");
    iTerminating = true;            // indicates terminating phase

    // cause exception in pending AND subsequent accept attempts in session threads.
    Interrupt(true);
    TUint count = iVector.size();
    for (TUint i = 0; i < count; i++) {             // delete all sessions
        delete iVector[i];
    }

    Close();
    LOGF(kNetwork, "<SocketTcpServer::~SocketTcpServer\n");
}

// Tcp Session

SocketTcpSession::SocketTcpSession()
    : iMutex("TCPS"), iOpen(false)
{
}

// Called when the session is added to a server
void SocketTcpSession::Add(SocketTcpServer& aServer, const TChar* aName, TUint aPriority, TUint aStackBytes)
{
    iServer = &aServer;
    iThread = new ThreadFunctor(aName, MakeFunctor(*this, &SocketTcpSession::Start), aPriority, aStackBytes);
    iThread->Start();
}

// Called when the thread for this session starts
void SocketTcpSession::Start()
{
    LOGF(kNetwork, ">SocketTcpSession::Start()\n");
    for (;;) {
        try {
            Open(iServer->Accept());            // accept a connection for this session
        } catch (NetworkError&) {                // server is being destroyed
            LOG2F(kNetwork, kError, "-SocketTcpSession::Start() Network Accept Exception\n");
            break;
        }
        try {
            LOGF(kNetwork, "-SocketTcpSession::Start() Run session\n");
            Run();                              // execute specific session behaviour
        }
        catch (NetworkError&) {                  // session handle has been shutdown or remote client has shutdown
            LOG2F(kNetwork, kError, "-SocketTcpSession::Start() Network Exception\n");
        }
        try {
            Close();    // session complete, close session handle and continue to accept new connection
        } catch (NetworkError&) {
            LOG2F(kNetwork, kError, "-SocketTcpSession::Start() Network Close Exception\n");
        }
    }
    LOGF(kNetwork, "<SocketTcpSession::Start()\n");
}

void SocketTcpSession::Open(THandle aHandle)
{
    LOGF(kNetwork, "SocketTcpSession::Open %d\n", aHandle);
    iMutex.Wait();
    iHandle = aHandle;
    Zapp::Os::NetworkTcpSetNoDelay(iHandle);

    iOpen = true;
    if (iServer->Terminating()) {       // catches the case where the server is destroyed between
        iMutex.Signal();                // accept returning a handle and open assigning this handle
        Close();                        // to the session
        THROW(NetworkError);
    }
    iMutex.Signal();
}

void SocketTcpSession::Close()
{
    LOGF(kNetwork, "SocketTcpSession::Close %d\n", iHandle);
    iMutex.Wait();
    if (iOpen) {
        try {
            Socket::Close();
        }
        catch (NetworkError&) {
            LOG2F(kNetwork, kError, "SocketTcpSession::Close %d Exception on session close\n", iHandle);
        }
        iOpen = false;
    }
    iMutex.Signal();
}

SocketTcpSession::~SocketTcpSession()
{
    LOGF(kNetwork, ">SocketTcpSession::~SocketTcpSession\n");
    iMutex.Wait();
    if (iOpen) {
        Interrupt(true); // should kick the thread out of any network receive or send
    }
    iMutex.Signal();
    delete iThread;
    LOGF(kNetwork, "<SocketTcpSession::~SocketTcpSession\n");
}

// SocketUdpClient

SocketUdpClient::SocketUdpClient(const Endpoint& aEndpoint)
    : iEndpoint(aEndpoint)
{
    LOGF(kNetwork, "> SocketUdpClient::SocketUdpClient\n");
    iHandle = SocketCreate(eSocketTypeDatagram);
    Zapp::Os::NetworkSocketSetReuseAddress(iHandle);
    LOGF(kNetwork, "< SocketUdpClient::SocketUdpClient H = %d\n", iHandle);
}

SocketUdpClient::SocketUdpClient(const Endpoint& aEndpoint, TUint aTtl)
    : iEndpoint(aEndpoint)
{
    LOGF(kNetwork, "> SocketUdpClient::SocketUdpClient aTtl=%d\n", aTtl);
    iHandle = SocketCreate(eSocketTypeDatagram);
    Zapp::Os::NetworkSocketSetMulticastTtl(iHandle, (TByte)aTtl);
    LOGF(kNetwork, "< SocketUdpClient::SocketUdpClient H = %d\n", iHandle);
}

SocketUdpClient::SocketUdpClient(const Endpoint& aEndpoint, TUint aTtl, TIpAddress aInterface)
    : iEndpoint(aEndpoint)
{
    LOGF(kNetwork, "> SocketUdpClient::SocketUdpClient aTtl=%d\n", aTtl);
    iHandle = SocketCreate(eSocketTypeDatagram);
    Zapp::Os::NetworkSocketSetMulticastTtl(iHandle, (TByte)aTtl);
    Zapp::Os::NetworkSocketSetReuseAddress(iHandle);
    TUint port = 0;
	SocketBind(iHandle, port, aInterface);
    LOGF(kNetwork, "< SocketUdpClient::SocketUdpClient H = %d\n", iHandle);
}

SocketUdpClient::~SocketUdpClient()
{
    Close();
}

void SocketUdpClient::Send(const Brx& aBuffer)
{
    LOGF(kNetwork, "> SocketUdpClient::Send\n");
    SocketSendTo(iHandle, aBuffer, iEndpoint);
}

Endpoint SocketUdpClient::Receive(Bwx& aBuffer)
{
    LOGF(kNetwork, "> SocketUdpClient::Receive\n");
    Endpoint endpoint;
    SocketReceiveFrom(iHandle, aBuffer, endpoint);
    return endpoint;
}

// SocketUdpMulticast

SocketUdpMulticast::SocketUdpMulticast(const Endpoint& aEndpoint)
    : SocketUdpClient(aEndpoint)
    , iInterface(0)
{
    Construct();
}

SocketUdpMulticast::SocketUdpMulticast(const Endpoint& aEndpoint, TUint aTtl)
    : SocketUdpClient(aEndpoint, aTtl)
    , iInterface(0)
{
    Construct();
}

SocketUdpMulticast::SocketUdpMulticast(const Endpoint& aEndpoint, TUint aTtl, TIpAddress aInterface)
    : SocketUdpClient(aEndpoint, aTtl)
    , iInterface(aInterface)
{
    LOGF(kNetwork, "SocketUdpMulticast::SocketUdpMulticast\n");
    Construct();
}

SocketUdpMulticast::~SocketUdpMulticast()
{
    LOGF(kNetwork, "SocketUdpMulticast::~SocketUdpMulticast\n");
    Zapp::Os::NetworkSocketMulticastDropMembership(iHandle, iEndpoint.Address(), iInterface);
}

void SocketUdpMulticast::Construct()
{
    LOGF(kNetwork, "SocketUdpMulticast::Construct\n");
    Zapp::Os::NetworkSocketSetReuseAddress(iHandle);
    // Windows expects us to bind to the multicast port but not the address
    // linux doesn't seem to care
    TUint port = iEndpoint.Port();
	SocketBind(iHandle, port, 0);
    Zapp::Os::NetworkSocketMulticastAddMembership(iHandle, iEndpoint.Address(), iInterface);
}

// UdpControllerReader

UdpControllerReader::UdpControllerReader(SocketUdpClient& aSocket)
    : iSocket(aSocket)
    , iOpen(true)
{
}

Endpoint UdpControllerReader::Sender() const
{
    return iSender;
}

void UdpControllerReader::Read(Bwx& aBuffer)
{
    if (iOpen) {
        try {
            iSender = iSocket.Receive(aBuffer);
            iOpen = false;
        }
        catch (NetworkError&) {
            THROW(ReaderError);
        }
    }
    else {
        THROW(ReaderError);
    }
}

void UdpControllerReader::ReadFlush()
{
    iOpen = true;
}

void UdpControllerReader::ReadInterrupt()
{
    iSocket.Interrupt(true);
}

// UdpControllerWriter

UdpControllerWriter::UdpControllerWriter(SocketUdpClient& aSocket)
    : iSocket(aSocket)
    , iOpen(true)
{
}

void UdpControllerWriter::Write(TByte /*aValue*/)
{
    ASSERTS();
}

void UdpControllerWriter::Write(const Brx& aBuffer)
{
    if (iOpen) {
        try {
            iSocket.Send(aBuffer);
            iOpen = false;
        }
        catch (NetworkError&) {
            THROW(WriterError);
        }
    }
    else {
        THROW(WriterError);
    }
}

void UdpControllerWriter::WriteFlush()
{
    iOpen = true;
}
