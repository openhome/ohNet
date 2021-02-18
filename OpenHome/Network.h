#ifndef HEADER_NETWORK
#define HEADER_NETWORK

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/TIpAddressUtils.h>

#include <vector>

EXCEPTION(NetworkError)
EXCEPTION(NetworkAddressInUse)
EXCEPTION(NetworkTimeout)

#ifdef DEFINE_BIG_ENDIAN
# define MakeIpAddress(aByte1, aByte2, aByte3, aByte4) \
        (aByte4 | (aByte3<<8) | (aByte2<<16) | (aByte1<<24))
#elif defined(DEFINE_LITTLE_ENDIAN)
# define MakeIpAddress(aByte1, aByte2, aByte3, aByte4) \
        (aByte1 | (aByte2<<8) | (aByte3<<16) | (aByte4<<24))
#else
# error "Endianness must be defined."
#endif

namespace OpenHome {

enum ESocketType
{
    eSocketTypeStream = 1,              /// Tcp stream
    eSocketTypeDatagram = 2,            /// Udp
};

// Addressing

// The Endpoint class has been designed with a restricted interface in order to facilitate
// the move to different addressing schemes in the future (IPv6)

class Endpoint
{
public:
    static const TUint kMaxAddressBytes = TIpAddressUtils::kMaxAddressBytes; // Potentially 32 Hex characters + 7 colon de-limiters + terminator for IPv6 addr
    static const TUint kMaxEndpointBytes = 48;                               // As above with de-limiter before port of 5 characters and '[]' enclosing the address
    typedef Bws<TIpAddressUtils::kMaxAddressBytes> AddressBuf;
    typedef Bws<kMaxEndpointBytes> EndpointBuf;
public:
    Endpoint();
    Endpoint(TUint aPort, const Brx& aAddress);          // specify port, specify ip address from string e.g. "192.168.0.1"
    Endpoint(TUint aPort, TIpAddress aAddress);          // specify port, specify ip address from uint
    void SetPort(TUint aPort);                           // set port
    void SetPort(const Endpoint& aEndpoint);             // set port from other endpoint
    void SetAddress(const Brx& aAddress);                // set address from string e.g. "192.168.0.1"
    void SetAddress(TIpAddress aAddress);
    void SetAddress(const Endpoint& aEndpoint);          // set address from other endpoint
    void Replace(const Endpoint& aEndpoint);             // set endpoint from other endpoint
    TBool Equals(const Endpoint& aEndpoint) const;       // test if this endpoint is equal to the specified endpoint
    inline TBool operator==(const Endpoint& aEndpoint) const { return Equals(aEndpoint); }
    TIpAddress Address() const;
    TUint16 Port() const;                                // return port as a network order uint16
    void AppendAddress(Bwx& aAddress) const;
    void AppendEndpoint(Bwx& aEndpoint) const;
    void GetAddressOctets(TByte (&aOctets)[4]) const;    // return individual octets for an IPv4 address
    void GetAddressFields(TUint (&aFields)[8]) const;    // return individual fields for an IPv6 address
    void Externalise(IWriter& aWriter);
    void Internalise(IReader& aReader);
    void InternaliseIPv6(IReader& aReader);
    static void AppendAddress(Bwx& aAddressBuffer, const TIpAddress& aAddress);
private:
    TIpAddress iAddress;
    TUint16 iPort;
};

class Socket : public INonCopyable
{
public:
    /**
     * Close the socket, freeing any associated memory.
     * Can only be called after any other calls to this socket from other
     * threads have returned.
     */
    void Close();
    void CloseThrows();
    void Interrupt(TBool aInterrupt);
    void SetSendBufBytes(TUint aBytes);
    void SetRecvBufBytes(TUint aBytes);
    void SetRecvTimeout(TUint aMs);
    void LogVerbose(TBool aLog, TBool aHex = false);
protected:
    Socket();
    virtual ~Socket() {}
    void Create(Environment& aEnv, ESocketType aSocketType);
    void Send(const Brx& aBuffer);
    void SendTo(const Brx& aBuffer, const Endpoint& aEndpoint);
    void Receive(Bwx& aBuffer);
    void Receive(Bwx& aBuffer, TUint aBytes);
    void ReceiveFrom(Bwx& aBuffer, Endpoint& aEndpoint);
    void Bind(const Endpoint& aEndpoint);
    void GetPort(TUint& aPort);
    void Listen(TUint aSlots);
    THandle Accept(Endpoint& aClientEndpoint);
    TBool IsInterrupted() const;
private:
    void Log(const char* aPrefix, const Brx& aBuffer) const;
protected:
    THandle iHandle;
private:
    static const uint32_t kLogNone      = 0;
    static const uint32_t kLogPlainText = 1;
    static const uint32_t kLogHex       = 2;
    static const uint32_t kLogMask      = 3;
    static const uint32_t kInterrupted  = 1 << 30;
    uint32_t iFlags;
    mutable Mutex iLock;
};

/**
 * Utility class.
 *
 * Create an AutoSocket on the stack using a reference to an opened Socket.
 * It will automatically be closed on stack cleanup (ie on return or when
 * an exception passes up).
 */
class AutoSocket : public INonCopyable
{
public:
    AutoSocket(Socket& aSocket);
    ~AutoSocket();
private:
    Socket& iSocket;
};

/**
* Utility class.
*
* Calls ReadFlush() on its IReader and Close() on its Socket on destruction.
*/
class AutoSocketReader : public AutoSocket
{
public:
    AutoSocketReader(Socket& aSocket, IReader& aReader);
    ~AutoSocketReader();
private:
    IReader& iReader;
};

/// Shared Tcp client / Tcp session base class
class SocketTcp : public Socket, public IWriter, public IReaderSource
{
public:
    /**
     * Block until aBytes bytes are received, replace buffer
     * Throw NetworkError on network error
     * Throw NetworkError on remote socket close - returns with aBuffer.Bytes() < aBytes
     */
    void Receive(Bwx& aBuffer, TUint aBytes);

    // IWriter
    /**
     * Send the buffer, block until all bytes are sent
     * Throw NetworkError on network error
     */
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();

    // IReaderSource
    /**
     * Receive between [0, aBuffer.MaxBytes()] bytes, replace buffer
     * Throw NetworkError on network error
     * On return, aBuffer.Bytes() == 0 means remote socket closed
     */
    void Read(Bwx& aBuffer);
    void Read(Bwx& aBuffer, TUint aBytes);
    void ReadFlush();
    void ReadInterrupt();
protected:
    SocketTcp();
};

class Environment;

/// Tcp client

class SocketTcpClient : public SocketTcp
{
public:
    void Open(Environment& aEnv);
    void Connect(const Endpoint& aEndpoint, TUint aTimeoutMs);
};

/// Tcp Session

class SocketTcpServer;

class SocketTcpSession : public SocketTcp /// Derive from this class to instantiate tcp server behaviour
{
    friend class SocketTcpServer;
protected:
    SocketTcpSession();
    virtual void Run() = 0;
    virtual ~SocketTcpSession();
    Endpoint ClientEndpoint() const;
private:
    void Add(SocketTcpServer& aServer, const TChar* aName, TUint aPriority, TUint aStackBytes);
    void Start();
    void Open(THandle aHandle);
    void Close();
    void Terminate();   /// Called by owning TcpServer *before* invoking dtor. Waits for TcpSession::Run() to exit.
private:
    Mutex iMutex;
    TBool iOpen;
    SocketTcpServer* iServer;
    ThreadFunctor* iThread;
    Endpoint iClientEndpoint;
};

// Tcp Server

class SocketTcpServer : public Socket
{
    friend class SocketTcpSession;
public:
    SocketTcpServer(Environment& aEnv, const TChar* aName, TUint aPort, const TIpAddress& aInterface,
                    TUint aSessionPriority = kPriorityHigh, TUint aSessionStackBytes = Thread::kDefaultStackBytes,
                    TUint aSlots = 128);
    // Add is not thread safe, but why would you want that?
    void Add(const TChar* aName, SocketTcpSession* aSession, TInt aPriorityOffset = 0);
    TUint Port() const { return iPort; }
    const TIpAddress& Interface() const { return iInterface; }
    ~SocketTcpServer(); // Closes the server
private:
    TBool Terminating();            // indicates server is in process of being destroyed
    THandle Accept(Endpoint& aClientEndpoint); // accept a connection and return the session handle
private:
    Mutex iMutex;                   // allows one thread to accept at a time
    TUint iSessionPriority;         // priority given to all session threads
    TUint iSessionStackBytes;       // stack bytes given to all session threads
    TBool iTerminating;
    std::vector<SocketTcpSession*> iSessions;
    TUint iPort;
    TIpAddress iInterface;
};

// general udp socket;

class SocketUdpBase : public Socket
{
public:
    void SetTtl(TUint aTtl);
    void Send(const Brx& aBuffer, const Endpoint& aEndpoint);
    Endpoint Receive(Bwx& aBuffer);
    TUint Port() const;
    ~SocketUdpBase();
    void ReCreate();
protected:
    SocketUdpBase(Environment& aEnv);
private:
    void Create();
protected:
    Environment& iEnv;
    TUint iPort;
};

class SocketUdp : public SocketUdpBase
{
public:
    SocketUdp(Environment& aEnv); // lets the os select a port
    SocketUdp(Environment& aEnv, TUint aPort); // stipulate a port
    SocketUdp(Environment& aEnv, TUint aPort, const TIpAddress& aInterface); // stipulate a port and an interface
    void ReBind(TUint aPort, const TIpAddress& aInterface);
    void SetMulticastIf(const TIpAddress& aInterface);
private:
    void Bind(TUint aPort, const TIpAddress& aInterface);
};

// multicast receiver
class SocketUdpMulticast : public SocketUdpBase
{
public:
    SocketUdpMulticast(Environment& aEnv, const TIpAddress& aInterface, const Endpoint& aEndpoint);
    ~SocketUdpMulticast();
    void ReCreate();
private:
    TIpAddress iInterface;
    TIpAddress iAddress;
};

/**
 * Utility class which enforces the Read() - ReadFlush() useage pattern
 * This class may be useful to subclasses of SocketUdpClient or
 * SocketUdpMulticast but its use is entirely optional
 */
class UdpReader : public IReaderSource, public INonCopyable
{
public:
    UdpReader();
    UdpReader(SocketUdpBase& aSocket);
    void SetSocket(SocketUdpBase& aSocket);
    void ClearSocket();
    Endpoint Sender() const; // sender of last completed Read()
public: // from IReaderSource
    void Read(Bwx& aBuffer);
    void ReadFlush();
    void ReadInterrupt();
protected:
    SocketUdpBase* iSocket;
private:
    Endpoint iSender;
    TBool iOpen;
};

/**
 * Utility class which enforces the Write() - WriteFlush() useage pattern
 * This class may be useful to subclasses of SocketUdp or SocketUdpMulticast
 */
class UdpWriter : public IWriter, public INonCopyable
{
public:
    UdpWriter(SocketUdpBase& aSocket, const Endpoint& aEndpoint);
    virtual void Write(TByte aValue);
    virtual void Write(const Brx& aBuffer);
    virtual void WriteFlush();
private:
    SocketUdpBase& iSocket;
    Endpoint iEndpoint;
    TBool iOpen;
};

} // namespace OpenHome

#endif // HEADER_NETWORK
