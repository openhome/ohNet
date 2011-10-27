#ifndef HEADER_NETWORK
#define HEADER_NETWORK

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/OsTypes.h>

#include <vector>

EXCEPTION(NetworkError);
EXCEPTION(NetworkAddressInUse);
EXCEPTION(NetworkTimeout);

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
    static const TUint kMaxAddressBytes = 16;
    static const TUint kMaxEndpointBytes = 22;
    typedef Bws<kMaxAddressBytes> AddressBuf;
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
    TIpAddress Address() const;
    TUint16 Port() const;                                // return port as a network order uint16
    void AppendAddress(Bwx& aAddress) const;
    void AppendEndpoint(Bwx& aEndpoint) const;
    void GetAddressOctets(TByte (&aOctets)[4]) const;
private:
    TIpAddress iAddress;
    TUint16 iPort;
};

class Socket
{
public:
    void Close();
    void Interrupt(TBool aInterrupt);
    void SetSendBufBytes(TUint aBytes);
    void SetRecvBufBytes(TUint aBytes);
    void SetRecvTimeout(TUint aMs);
    void LogVerbose(TBool aLog, TBool aHex = false);
protected:
    Socket();
    virtual ~Socket() {}
    TBool TryClose();
    void Send(const Brx& aBuffer);
    void SendTo(const Brx& aBuffer, const Endpoint& aEndpoint);
    void Receive(Bwx& aBuffer);
    void Receive(Bwx& aBuffer, TUint aBytes);
    void ReceiveFrom(Bwx& aBuffer, Endpoint& aEndpoint);
    void Bind(const Endpoint& aEndpoint);
    void GetPort(TUint& aPort);
    void Listen(TUint aSlots);
    THandle Accept();
private:
    void Log(const char* aPrefix, const Brx& aBuffer);
protected:
    THandle iHandle;
private:
    static const uint32_t kLogNone      = 0;
    static const uint32_t kLogPlainText = 1;
    static const uint32_t kLogHex       = 2;
    uint32_t iLog;
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

/// Tcp client

class SocketTcpClient : public SocketTcp
{
public:
    void Open();                                                /// Open
    void Connect(const Endpoint& aEndpoint, TUint aTimeout);    /// Connect to a given IP address and port number (timeout in milliseconds)
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
private:
    void Add(SocketTcpServer& aServer, const TChar* aName, TUint aPriority, TUint aStackBytes);
    void Start();
    void Open(THandle aHandle);
    void Close();
private:
    Mutex iMutex;
    TBool iOpen;
    SocketTcpServer* iServer;
    ThreadFunctor* iThread;
};

// Tcp Server

class SocketTcpServer : public Socket
{
    friend class SocketTcpSession;
public:
    SocketTcpServer(const TChar* aName, TUint aPort, TIpAddress aInterface, TUint aSessionPriority = kPriorityHigh,
                    TUint aSessionStackBytes = Thread::kDefaultStackBytes, TUint aSlots = 10);
    // Add is not thread safe, but why would you want that?
    void Add(const TChar* aName, SocketTcpSession* aSession, TInt aPriorityOffset = 0);
	TUint Port() const { return iPort; }
	TIpAddress Interface() const { return iInterface; }
    ~SocketTcpServer(); // Closes the server
private:
    TBool Terminating();            // indicates server is in process of being destroyed
    THandle Accept();               // accept a connection and return the session handle
private:
    Mutex iMutex;                   // allows one thread to accept at a time
    TUint iSessionPriority;         // priority given to all session threads
    TUint iSessionStackBytes;       // stack bytes given to all session threads
    TBool iTerminating;
    typedef std::vector<SocketTcpSession*> Vector;
    Vector iVector;
    TUint iPort;
    TIpAddress iInterface;
};

// general udp socket;

class SocketUdp : public Socket
{
public:
    SocketUdp(); // lets the os select a port
    SocketUdp(TUint aPort); // stipulate a port
    SocketUdp(TUint aPort, TIpAddress aInterface); // stipulate a port and an interface
    void SetTtl(TUint aTtl);
    void Send(const Brx& aBuffer, const Endpoint& aEndpoint);
    Endpoint Receive(Bwx& aBuffer);
    TUint Port() const;
    ~SocketUdp();
protected:
    TUint iPort;
};

// multicast receiver
class SocketUdpMulticast : public SocketUdp
{
public:
    SocketUdpMulticast(TIpAddress aInterface, const Endpoint& aEndpoint);
    ~SocketUdpMulticast();
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
    UdpReader(SocketUdp& aSocket);
    Endpoint Sender() const; // sender of last completed Read()
    virtual void Read(Bwx& aBuffer);
    virtual void ReadFlush();
    virtual void ReadInterrupt();
protected:
    SocketUdp& iSocket;
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
    UdpWriter(SocketUdp& aSocket, const Endpoint& aEndpoint);
    virtual void Write(TByte aValue);
    virtual void Write(const Brx& aBuffer);
    virtual void WriteFlush();
private:
    SocketUdp& iSocket;
    Endpoint iEndpoint;
    TBool iOpen;
};

} // namespace OpenHome

#endif // HEADER_NETWORK
