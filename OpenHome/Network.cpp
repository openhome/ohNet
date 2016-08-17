#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Ascii.h>

#include <errno.h>

using namespace OpenHome;

// OS sockets interface

static THandle SocketCreate(Environment& aEnv, ESocketType aSocketType)
{
    LOGF(kNetwork, "SocketCreate  ST = %d, \n", aSocketType);
    THandle handle = OpenHome::Os::NetworkCreate(aEnv.OsCtx(), aSocketType);
    LOGF(kNetwork, "SocketCreate  Socket H = %d\n", handle);
    return handle;
}

static TUint32 GetHostByName(const Brx& aAddress)
{
    return OpenHome::Os::NetworkGetHostByName(aAddress);
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

void Endpoint::AppendAddress(Bwx& aAddressBuffer, TIpAddress aAddress)
{
    ASSERT(aAddressBuffer.MaxBytes() - aAddressBuffer.Bytes() >= kMaxAddressBytes);
#ifdef DEFINE_LITTLE_ENDIAN
    (void)Ascii::AppendDec(aAddressBuffer, aAddress&0xff);
    aAddressBuffer.Append('.');
    (void)Ascii::AppendDec(aAddressBuffer, (aAddress>>8)&0xff);
    aAddressBuffer.Append('.');
    (void)Ascii::AppendDec(aAddressBuffer, (aAddress>>16)&0xff);
    aAddressBuffer.Append('.');
    (void)Ascii::AppendDec(aAddressBuffer, (aAddress>>24)&0xff);
#elif defined DEFINE_BIG_ENDIAN
    (void)Ascii::AppendDec(aAddressBuffer, (aAddress>>24)&0xff);
    aAddressBuffer.Append('.');
    (void)Ascii::AppendDec(aAddressBuffer, (aAddress>>16)&0xff);
    aAddressBuffer.Append('.');
    (void)Ascii::AppendDec(aAddressBuffer, (aAddress>>8)&0xff);
    aAddressBuffer.Append('.');
    (void)Ascii::AppendDec(aAddressBuffer, aAddress&0xff);
#else
# error No endianess defined
#endif
    aAddressBuffer.PtrZ();
}

void Endpoint::AppendAddress(Bwx& aAddress) const
{
    AppendAddress(aAddress, iAddress);
}

void Endpoint::AppendEndpoint(Bwx& aEndpoint) const
{
    ASSERT(aEndpoint.MaxBytes() - aEndpoint.Bytes() >= kMaxEndpointBytes);
    AppendAddress(aEndpoint, iAddress);
    aEndpoint.Append(':');
    (void)Ascii::AppendDec(aEndpoint, iPort);
    aEndpoint.PtrZ();
}

void Endpoint::GetAddressOctets(TByte (&aOctets)[4]) const
{
#ifdef DEFINE_LITTLE_ENDIAN
    aOctets[0] = iAddress&0xff;
    aOctets[1] = (iAddress>>8)&0xff;
    aOctets[2] = (iAddress>>16)&0xff;
    aOctets[3] = (iAddress>>24)&0xff;
#elif defined DEFINE_BIG_ENDIAN
    aOctets[0] = (iAddress>>24)&0xff;
    aOctets[1] = (iAddress>>16)&0xff;
    aOctets[2] = (iAddress>>8)&0xff;
    aOctets[3] = iAddress&0xff;
#else
# error No endianess defined
#endif
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
    : iLock("SKLL")
{
    iHandle = kHandleNull;
    iLog = kLogNone;
}

void Socket::Interrupt(TBool aInterrupt)
{
    AutoMutex a(iLock);
    if (iHandle == kHandleNull) {
        return;
    }
    LOGF(kNetwork, "Socket::Interrupt H = %d\n", iHandle);
    TInt err = OpenHome::Os::NetworkInterrupt(iHandle, aInterrupt);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Socket::Interrupt H = %d, RETURN VALUE = %d\n", iHandle, err);
    }
}

void Socket::Close()
{
    // close connection and allow caller to handle any exceptions
    LOGF(kNetwork, "Socket::Close H = %d\n", iHandle);
    iLock.Wait();
    TInt err = 0;
    THandle handle = iHandle;
    if (iHandle != kHandleNull){
        err = OpenHome::Os::NetworkClose(iHandle);
        iHandle = kHandleNull;
    }
    iLock.Signal();
    if(err != 0) {
        LOG2F(kNetwork, kError, "Socket::Close H = %d, RETURN VALUE = %d\n", handle, err);
        THROW(NetworkError);
    }
}

void Socket::SetSendBufBytes(TUint aBytes)
{
    OpenHome::Os::NetworkSocketSetSendBufBytes(iHandle, aBytes);
}

void Socket::SetRecvBufBytes(TUint aBytes)
{
    OpenHome::Os::NetworkSocketSetRecvBufBytes(iHandle, aBytes);
}

void Socket::SetRecvTimeout(TUint aMs)
{
    OpenHome::Os::NetworkSocketSetReceiveTimeout(iHandle, aMs);
}

void Socket::LogVerbose(TBool aLog, TBool aHex)
{
    if (!aLog) {
        iLog = kLogNone;
        ASSERT(!aHex);
    }
    else if (!aHex) {
        iLog = kLogPlainText;
    }
    else {
        iLog = kLogHex;
    }
}

void Socket::Send(const Brx& aBuffer)
{
    LOGF(kNetwork, "Socket::Send  H = %d, BC = %d\n", iHandle, aBuffer.Bytes());
    Log("Socket::Send, sending\n", aBuffer);
    TInt sent = OpenHome::Os::NetworkSend(iHandle, aBuffer);
    if(sent < 0) {
        LOG2F(kNetwork, kError, "Socket::Send H = %d, RETURN VALUE = %d\n", iHandle, sent);
        THROW(NetworkError);
    }
    if((TUint)sent != aBuffer.Bytes()) {
        LOG2F(kNetwork, kError, "Socket::Send H = %d, RETURN VALUE = %d, INCOMPLETE\n", iHandle, sent);
        THROW(NetworkError);
    }
}

void Socket::SendTo(const Brx& aBuffer, const Endpoint& aEndpoint)
{
    LOGF(kNetwork, "Socket::SendTo  H = %d, BC = %d, E = %x:%d\n", iHandle, aBuffer.Bytes(), aEndpoint.Address(), aEndpoint.Port());
    Log("Socket::SendTo, sending\n", aBuffer);
    TInt sent = OpenHome::Os::NetworkSendTo(iHandle, aBuffer, aEndpoint);
    if(sent < 0) {
        LOG2F(kNetwork, kError, "Socket::SendTo H = %d, RETURN VALUE = %d\n", iHandle, sent);
        THROW(NetworkError);
    }
    if((TUint)sent != aBuffer.Bytes()) {
        LOG2F(kNetwork, kError, "Socket::SendTo H = %d, RETURN VALUE = %d, INCOMPLETE\n", iHandle, sent);
        THROW(NetworkError);
    }
}

void Socket::Receive(Bwx& aBuffer)
{
    // This variant of Receive will receive any number of bytes in the
    // range [0, aBuffer.MaxBytes()] (0 means socket was closed at the other end)
    LOGF(kNetwork, ">Socket::Receive H = %d, MAX = %d\n", iHandle, aBuffer.MaxBytes());
    aBuffer.SetBytes(0);
    TInt received = OpenHome::Os::NetworkReceive(iHandle, aBuffer);
    if(received < 0) {
        Bws<Thread::kMaxNameBytes+1> thName(Thread::CurrentThreadName());
        LOG2F(kNetwork, kError, "Socket::Receive H = %d, thread=%s\n", iHandle, thName.PtrZ());
        THROW(NetworkError);
    }
    aBuffer.SetBytes(received);
    Log("Socket::Receive, got\n", aBuffer);
    LOGF(kNetwork, "<Socket::Receive H = %d, BC = %d\n", iHandle, aBuffer.Bytes());
}

void Socket::Receive(Bwx& aBuffer, TUint aBytes)
{
    // This variant of Receive() expects the specified number of bytes. Therefore it will:
    //  - block until aBytes bytes have been received, or
    //  - throw a NetworkError on a genuine socket error OR if the socket
    //    is closed at the other end
    LOGF(kNetwork, "Socket::Receive H = %d, BC = %d\n", iHandle, aBytes);

    ASSERT(aBytes <= aBuffer.MaxBytes());
    TUint received = 0;
    aBuffer.SetBytes(0);
    TByte* ptr = (TByte*)aBuffer.Ptr();
    while(received < aBytes) {
        Bwn buf(ptr+received, aBytes-received);
        TInt ret = OpenHome::Os::NetworkReceive(iHandle, buf);
        if(ret < 0) {
            LOG2F(kNetwork, kError, "Socket::Receive H = %d, RETURN VALUE = %d\n", iHandle, ret);
            THROW(NetworkError);
        } else if(ret == 0) {
            // not all requested data received before connection closed
            THROW(NetworkError);
        }
        LOGF(kNetwork, "Socket::Receive H = %d, BYTES = %d\n", iHandle, ret);
        received += ret;
        aBuffer.SetBytes(received);
    }
    Log("Socket::Receive, got\n", aBuffer);
}

void Socket::ReceiveFrom(Bwx& aBuffer, Endpoint& aEndpoint)
{
    LOGF(kNetwork, "Socket::ReceiveFrom H = %d\n", iHandle);
    TInt received = OpenHome::Os::NetworkReceiveFrom(iHandle, aBuffer, aEndpoint);
    if(received < 0) {
        LOG2F(kNetwork, kError, "Socket::ReceiveFrom H = %d, RETURN VALUE = %d\n", iHandle, received);
        THROW(NetworkError);
    }
    aBuffer.SetBytes(received);
    Log("Socket::ReceiveFrom, got\n", aBuffer);
    LOGF(kNetwork, "<Socket::ReceiveFrom H = %d\n", iHandle);
}

void Socket::Bind(const Endpoint& aEndpoint)
{
    LOGF(kNetwork, "Socket::Bind H = %d\n", iHandle);
    TInt err = OpenHome::Os::NetworkBind(iHandle, aEndpoint);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Socket::Bind H = %d, RETURN VALUE = %d\n", iHandle, err);
        if (err == -2) {
            THROW(NetworkAddressInUse);
        }
        THROW(NetworkError);
    }
}

void Socket::GetPort(TUint& aPort)
{
    LOGF(kNetwork, "Socket::GetPort H = %d\n", iHandle);
    TInt err = OpenHome::Os::NetworkPort(iHandle, aPort);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Socket::GetPort H = %d, RETURN VALUE = %d\n", iHandle, err);
        THROW(NetworkError);
    }
}

void Socket::Listen(TUint aSlots)
{
    LOGF(kNetwork, "Socket::Listen H = %d S = %d\n", iHandle, aSlots);
    TInt err = OpenHome::Os::NetworkListen(iHandle, aSlots);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Socket::Listen H = %d, RETURN VALUE = %d\n", iHandle, err);
        THROW(NetworkError);
    }
}

THandle Socket::Accept(Endpoint& aClientEndpoint)
{
    LOGF(kNetwork, "Socket::Accept H = %d\n", iHandle);
    THandle handle = OpenHome::Os::NetworkAccept(iHandle, aClientEndpoint);
    LOGF(kNetwork,"Socket::Accept Accepted Handle = %d\n", handle);
    if(handle == kHandleNull) {
        LOG2F(kNetwork, kError, "Socket::Accept H = %d\n", handle);
        THROW(NetworkError);
    }
    return handle;
}

void Socket::Log(const char* aPrefix, const Brx& aBuffer) const
{
    if (iLog == kLogNone) {
        return;
    }
    AutoMutex a(iLock);
    if (iLog == kLogPlainText) {
        Log::Print("%s", aPrefix);
        TUint bytes = aBuffer.Bytes();
        Brn buf(aBuffer);
        while (bytes > 0) {
            const size_t len = (bytes<Log::kMaxPrintBytes? bytes : Log::kMaxPrintBytes);
            Brn rem = buf.Split((TUint)len);
            Log::Print(buf);
            bytes -= buf.Bytes();
            buf.Set(rem);
        }
        Log::Print("\n");
        return;
    }
    ASSERT(iLog == kLogHex);
    Log::Print("%s", aPrefix);
    for (TUint i=0; i<aBuffer.Bytes(); i++) {
        Log::Print(" %02x", aBuffer[i]);
        if ((i&0xf) == 0xf) {
            Log::Print("\n");
        }
    }
    Log::Print("\n");
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


// AutoSocketReader

AutoSocketReader::AutoSocketReader(Socket& aSocket, IReader& aReader)
    : AutoSocket(aSocket)
    , iReader(aReader)
{
}

AutoSocketReader::~AutoSocketReader()
{
    iReader.ReadFlush();
}


// Tcp socket base class

SocketTcp::SocketTcp()
{
    LOGF(kNetwork, "SocketTcp::SocketTcp\n");
}

void SocketTcp::Receive(Bwx& aBuffer, TUint aBytes)
{
    LOGF(kNetwork, "SocketTcp::Receive only %d bytes\n", aBytes);
    Socket::Receive(aBuffer, aBytes);
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
        Send(aBuffer);
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
        Socket::Receive(aBuffer);
    }
    catch(NetworkError&) {
        THROW(ReaderError);
    }

    if (aBuffer.Bytes() == 0) {
        THROW(ReaderError);
    }
    
    LOGF(kNetwork, "<SocketTcp::Read\n");
}

void SocketTcp::Read(Bwx& aBuffer, TUint aBytes)
{
    LOGF(kNetwork, ">SocketTcp::Read\n");
    try {
        Socket::Receive(aBuffer, aBytes);
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

static void TryNetworkTcpSetNoDelay(THandle aHandle)
{
    try {
        OpenHome::Os::NetworkTcpSetNoDelay(aHandle);
    }
    catch (NetworkError&) {
        //LOG2F(kNetwork, kError, "Warning -> could not set TCP NODELAY on %d\n", aHandle);
    }
}

// Tcp client

void SocketTcpClient::Open(Environment& aEnv)
{
    LOGF(kNetwork, "SocketTcpClient::Open\n");
    iHandle = SocketCreate(aEnv, eSocketTypeStream);
    TryNetworkTcpSetNoDelay(iHandle);
}

void SocketTcpClient::Connect(const Endpoint& aEndpoint, TUint aTimeout)
{
    LOGF(kNetwork, "SocketTcpClient::Connect\n");
    OpenHome::Os::NetworkConnect(iHandle, aEndpoint, aTimeout);
}

// Tcp Server

SocketTcpServer::SocketTcpServer(Environment& aEnv, const TChar* aName, TUint aPort, TIpAddress aInterface,
                                 TUint aSessionPriority, TUint aSessionStackBytes, TUint aSlots)
    : iMutex(aName)
    , iSessionPriority(aSessionPriority)
    , iSessionStackBytes(aSessionStackBytes)
    , iTerminating(false)
{
    LOGF(kNetwork, "SocketTcpServer::SocketTcpServer\n");
    iHandle = SocketCreate(aEnv, eSocketTypeStream);
    OpenHome::Os::NetworkSocketSetReuseAddress(iHandle);
    TryNetworkTcpSetNoDelay(iHandle);
    iInterface = aInterface;
    Bind(Endpoint(aPort, aInterface));
    GetPort(iPort);
    Listen(aSlots);
}

void SocketTcpServer::Add(const TChar* aName, SocketTcpSession* aSession, TInt aPriorityOffset)
{
    LOGF(kNetwork, "SocketTcpServer::Add\n");
    iSessions.push_back(aSession);                    // Can only throw std::bad_alloc. Don't bother to cleanup as we consider this
                                                    // a fatal exception anyway.
    try {
        aSession->Add(*this, aName, iSessionPriority + aPriorityOffset, iSessionStackBytes);
    }
    catch ( ... ) {                                 // Don't handle the exception per se, just perform cleanup and pass it on.
        iSessions.pop_back();
        delete aSession;
        throw;
    }
}

THandle SocketTcpServer::Accept(Endpoint& aClientEndpoint)
{
    LOGF(kNetwork, "SocketTcpServer::Accept\n");
    AutoMutex a(iMutex);                        // wait to become the single accepting thread
    if (iTerminating)
        THROW(NetworkError);

    return Socket::Accept(aClientEndpoint);     // accept the connection
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
    TUint count = (TUint)iSessions.size();
    for (TUint i = 0; i < count; i++) {             // delete all sessions
        iSessions[i]->Terminate();                    // Kill and Join the TcpSession thread
        delete iSessions[i];
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
            Open(iServer->Accept(iClientEndpoint));            // accept a connection for this session
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
    TryNetworkTcpSetNoDelay(iHandle);

    iOpen = true;
    if (iServer->Terminating()) {       // catches the case where the server is destroyed between
        iMutex.Signal();                // accept returning a handle and open assigning this handle
        Close();                        // to the session
        THROW(NetworkError);
    }
    iMutex.Signal();
}

Endpoint SocketTcpSession::ClientEndpoint() const
{
    return iClientEndpoint;
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

void SocketTcpSession::Terminate()
{
    LOGF(kNetwork, ">SocketTcpSession::Terminate()\n");
    iMutex.Wait();
    if (iOpen) {
        Interrupt(true); // should kick the thread out of any network receive or send
    }
    iMutex.Signal();

    iThread->Kill();    // mark the thread as 'killed' in case it's checking that too.
    iThread->Join();    // Join the TcpSession thread *before* any subclass dtor is invoked.
    LOGF(kNetwork, "<SocketTcpSession::Terminate()\n");
}

SocketTcpSession::~SocketTcpSession()
{
    LOGF(kNetwork, ">SocketTcpSession::~SocketTcpSession\n");
    delete iThread;
    LOGF(kNetwork, "<SocketTcpSession::~SocketTcpSession\n");
}

// SocketUdpBase

SocketUdpBase::SocketUdpBase(Environment& aEnv)
    : iEnv(aEnv)
{
    LOGF(kNetwork, "> SocketUdpBase::SocketUdpBase\n");
    Create();
    LOGF(kNetwork, "< SocketUdpBase::SocketUdpBase H = %d\n", iHandle);
}

void SocketUdpBase::SetTtl(TUint aTtl)
{
    LOGF(kNetwork, "> SocketUdp::SetTtl T = %d\n", aTtl);
    OpenHome::Os::NetworkSocketSetMulticastTtl(iHandle, (TByte)aTtl);
    LOGF(kNetwork, "< SocketUdp::SetTtl\n");
}

SocketUdpBase::~SocketUdpBase()
{
    Close();
}

TUint SocketUdpBase::Port() const
{
    return iPort;
}

void SocketUdpBase::Send(const Brx& aBuffer, const Endpoint& aEndpoint)
{
    LOGF(kNetwork, "> SocketUdpBase::Send\n");
    SendTo(aBuffer, aEndpoint);
}

Endpoint SocketUdpBase::Receive(Bwx& aBuffer)
{
    LOGF(kNetwork, "> SocketUdpBase::Receive\n");
    Endpoint endpoint;
    ReceiveFrom(aBuffer, endpoint);
    LOGF(kNetwork, "< SocketUdpBase::Receive\n");
    return endpoint;
}

void SocketUdpBase::ReCreate()
{
    Close();
    Create();
}

void SocketUdpBase::Create()
{
    iHandle = SocketCreate(iEnv, eSocketTypeDatagram);
    OpenHome::Os::NetworkSocketSetReuseAddress(iHandle);
}


// SocketUdp

SocketUdp::SocketUdp(Environment& aEnv)
    : SocketUdpBase(aEnv)
{
    LOGF(kNetwork, "> SocketUdp::SocketUdp\n");
    Bind(0, 0);
    GetPort(iPort);
    LOGF(kNetwork, "< SocketUdp::SocketUdp H = %d, P = %d\n", iHandle, iPort);
}

SocketUdp::SocketUdp(Environment& aEnv, TUint aPort)
    : SocketUdpBase(aEnv)
{
    LOGF(kNetwork, "> SocketUdp::SocketUdp P = %d\n", aPort);
    Bind(aPort, 0);
    LOGF(kNetwork, "< SocketUdp::SocketUdp H = %d, P = %d\n", iHandle, iPort);
}

SocketUdp::SocketUdp(Environment& aEnv, TUint aPort, TIpAddress aInterface)
    : SocketUdpBase(aEnv)
{
    LOGF(kNetwork, "> SocketUdp::SocketUdp P = %d, I = %x\n", aPort, aInterface);
    Bind(aPort, aInterface);
    LOGF(kNetwork, "< SocketUdp::SocketUdp H = %d, P = %d\n", iHandle, iPort);
}

void SocketUdp::ReBind(TUint aPort, TIpAddress aInterface)
{
    ReCreate();
    Bind(aPort, aInterface);
}

void SocketUdp::SetMulticastIf(TIpAddress aInterface)
{
    LOGF(kNetwork, "> SocketUdp::SetMulticastIf I = %x\n", aInterface);
    OpenHome::Os::NetworkSocketSetMulticastIf(iHandle, aInterface);
    LOGF(kNetwork, "< SocketUdp::SetMulticastIf\n");
}

void SocketUdp::Bind(TUint aPort, TIpAddress aInterface)
{
    Socket::Bind(Endpoint(aPort, aInterface));
    GetPort(iPort);
}


// SocketUdpMulticast

SocketUdpMulticast::SocketUdpMulticast(Environment& aEnv, TIpAddress aInterface, const Endpoint& aEndpoint)
    : SocketUdpBase(aEnv)
    , iInterface(aInterface)
    , iAddress(aEndpoint.Address())
{
    LOGF(kNetwork, "> SocketUdpMulticast::SocketUdpMulticast I = %x, E = %x:%d\n", iInterface, aEndpoint.Address(), aEndpoint.Port());
    const TUint err = OpenHome::Os::NetworkBindMulticast(iHandle, aInterface, aEndpoint);
    if (err != 0) {
        LOG2(kError, kNetwork, "NetworkBindMulticast for socket %u\n", iHandle);
        THROW(NetworkError);
    }
    GetPort(iPort);
    OpenHome::Os::NetworkSocketMulticastAddMembership(iHandle, iInterface, iAddress);
    LOGF(kNetwork, "< SocketUdpMulticast::SocketUdpMulticast H = %d, I = %x, A = %x, P = %d\n", iHandle, iInterface, iAddress, iPort);
}

SocketUdpMulticast::~SocketUdpMulticast()
{
    LOGF(kNetwork, "> SocketUdpMulticast::~SocketUdpMulticast\n");
    try {
        OpenHome::Os::NetworkSocketMulticastDropMembership(iHandle, iInterface, iAddress);
    }
    catch (NetworkError&) {
        LOG2F(kNetwork, kError, "DropMembership failed H = %d\n", iHandle);
    }
    LOGF(kNetwork, "< SocketUdpMulticast::~SocketUdpMulticast\n");
}

void SocketUdpMulticast::ReCreate()
{
    SocketUdpBase::ReCreate();
    Endpoint ep(iPort, iAddress);
    const TUint err = OpenHome::Os::NetworkBindMulticast(iHandle, iInterface, ep);
    if (err != 0) {
        LOG2(kError, kNetwork, "NetworkBindMulticast for socket %u\n", iHandle);
        THROW(NetworkError);
    }
    OpenHome::Os::NetworkSocketMulticastAddMembership(iHandle, iInterface, iAddress);
}


// UdpReader

UdpReader::UdpReader()
    : iSocket(NULL)
    , iOpen(true)
{
}

UdpReader::UdpReader(SocketUdpBase& aSocket)
    : iSocket(&aSocket)
    , iOpen(true)
{
}

void UdpReader::SetSocket(SocketUdpBase& aSocket)
{
    iSocket = &aSocket;
}

void UdpReader::ClearSocket()
{
    iSocket = NULL;
}

Endpoint UdpReader::Sender() const
{
    return iSender;
}

void UdpReader::Read(Bwx& aBuffer)
{
    if (iOpen) {
        try {
            ASSERT(iSocket != NULL);
            iSender = iSocket->Receive(aBuffer);
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

void UdpReader::ReadFlush()
{
    iOpen = true;
}

void UdpReader::ReadInterrupt()
{
    if (iSocket != NULL) {
        iSocket->Interrupt(true);
    }
}

// UdpWriter

UdpWriter::UdpWriter(SocketUdpBase& aSocket, const Endpoint& aEndpoint)
    : iSocket(aSocket)
    , iEndpoint(aEndpoint)
    , iOpen(true)
{
}

void UdpWriter::Write(TByte /*aValue*/)
{
    ASSERTS();
}

void UdpWriter::Write(const Brx& aBuffer)
{
    if (iOpen) {
        try {
            iSocket.Send(aBuffer, iEndpoint);
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

void UdpWriter::WriteFlush()
{
    iOpen = true;
}
