#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/Globals.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

// SuiteTcpClient

class TestServerSession : public SocketTcpSession
{
public:
    TestServerSession(Semaphore& aControllerSem)
        : iSemaphore("TSTS", 0)
        , iTestStarted("TSS2", 0)
        , iControllerSem(aControllerSem)
    {
    }

    void Run()
    {
        LOG(kNetwork, ">TestServerSession::Run\n");
        TBool exit = false;
        while (!exit) {
            LOG(kNetwork, "TestServerSession::Run waiting on semaphore\n");
            iSemaphore.Wait();
            iTestDone = false;
            LOG(kNetwork, "Starting Test %d\n", iTest);
            iTestStarted.Signal();
            switch(iTest)
            {
            case 0:
                exit = true;
                break;
            case 1:
                Receive(iBuffer, iBytes);
                break;
            case 2:
                TEST_THROWS(Receive(iBuffer, iBytes), NetworkError);
                break;
            case 3:
                try {
                    Read(iBuffer);
                }
                catch (ReaderError&) {}
                break;
            }
            gEnv->Mutex().Wait();
            iTestDone = true;
            gEnv->Mutex().Signal();
            iControllerSem.Signal();
        }
        LOG(kNetwork, "<TestServerSession::Run\n");
    }

    void Close()
    {
        StartTest(0);
    }
    void StartTest(TUint aTestIndex, TUint aBytes)
    {
        iBytes = aBytes;
        StartTest(aTestIndex);
    }
    void StartTest(TUint aTestIndex)
    {
        LOG(kNetwork, "Signalling Test %d\n", aTestIndex);
        iTest = aTestIndex;
        iSemaphore.Signal();
        iTestStarted.Wait();
    }

    TBool TestDone()
    {
        gEnv->Mutex().Wait();
        TBool done = iTestDone;
        gEnv->Mutex().Signal();
        return done;
    }
    const Brx& Buffer() { return iBuffer; }

private:
    Semaphore iSemaphore;
    Semaphore iTestStarted;
    Semaphore& iControllerSem;
    TUint iBytes;
    Bws<64> iBuffer;
    TUint iTest;
    TBool iTestDone;
};


class SuiteTcpClient : public Suite, public INonCopyable
{
public:
    SuiteTcpClient(TIpAddress aInterface) : Suite("Basic TcpClient/TcpSocket interface Tests"), iInterface(aInterface) {}
    void Test();
private:
    TIpAddress iInterface;
};

void SuiteTcpClient::Test()
{
    Semaphore sem("TCPS", 0);
    SocketTcpServer server(*gEnv, "TSSV", 0, iInterface);
    const TUint port = server.Port();
    TestServerSession* session = new TestServerSession(sem);
    server.Add("TSS1", session);

    SocketTcpClient client;
    client.Open(*gEnv);
    client.Connect(Endpoint(port, iInterface), 1000);

    // Test 1 - test Receive(Bwx& , TUint ) interface
    session->StartTest(1,32);
    TEST(session->TestDone() == false);
    // send 16 bytes
    client.Write(Brn("abcdefghijklmnop"));
    Thread::Sleep(500);
    TEST(session->TestDone() == false);
    // send 16 bytes
    client.Write(Brn("abcdefghijklmnop"));
    sem.Wait();
    TEST(session->TestDone() == true);
    TEST(session->Buffer() == Brn("abcdefghijklmnopabcdefghijklmnop"));

    // Test 2 - test Receive(Bwx& , TUint ) interface behaviour when
    // remote end closes socket before aBytes are received
    session->StartTest(2,32);
    TEST(session->TestDone() == false);
    // send 16 bytes
    client.Write(Brn("abcdefghijklmnop"));
    Thread::Sleep(500);
    TEST(session->TestDone() == false);
    // send 10 bytes
    client.Write(Brn("abcdefghij"));
    Thread::Sleep(500);
    TEST(session->TestDone() == false);
    // close the sending socket
    client.Close();
    sem.Wait();
    TEST(session->TestDone() == true);
    TEST(session->Buffer() == Brn("abcdefghijklmnopabcdefghij"));
    session->Close();
    sem.Wait();

    client.Open(*gEnv);
    client.Connect(Endpoint(port, iInterface), 1000);

    // Test 3 - test Receive(Bwx& ) interface - start the Receive before the send
    session->StartTest(3);
    TEST(session->TestDone() == false);
    // send 16 bytes
    client.Write(Brn("abcdefghijklmnop"));
    sem.Wait();
    TEST(session->TestDone() == true);
    TEST(session->Buffer() == Brn("abcdefghijklmnop"));

    // Test 3 - test Receive(Bwx& ) interface - send 2 messages and receive 1
    // send 16 bytes twice
    client.Write(Brn("abcdefghijklmnop"));
    client.Write(Brn("abcdefghijklmnop"));
    Thread::Sleep(500);
    // signal the receive
    session->StartTest(3);
    sem.Wait();
    TEST(session->TestDone() == true);
    TEST(session->Buffer() == Brn("abcdefghijklmnopabcdefghijklmnop"));

    // Test 3 - test Receive(Bwx& ) interface - send nothing and close
    session->StartTest(3);
    TEST(session->TestDone() == false);
    // close the sending socket
    client.Close();
    sem.Wait(500);
    TEST(session->TestDone() == true);
    TEST(session->Buffer() == Brx::Empty());
    session->Close();
}


// TcpSocketServer

class TcpSessionEcho : public SocketTcpSession
{
private:
    virtual void Run();
};

void TcpSessionEcho::Run()
{
    Bws<1500> message;
    while (true) {
        Read(message);
        Write(message);
        if (message.Bytes() == 26)  // close session after receiving 26 byte message
            break;
    }
}

class SuiteSocketServer : public Suite, public INonCopyable
{
public:
    SuiteSocketServer(TIpAddress aInterface) : Suite("ohNet Socket Server Tests"), iInterface(aInterface) {}
    void Test();
private:
    TIpAddress iInterface;
};

void SuiteSocketServer::Test()
{
    Bws<26> rx;
    Bws<26> tx("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    SocketTcpServer server(*gEnv, "TSSX", 0, iInterface);
    Print("Server created\n");
    server.Add("TSS1", new TcpSessionEcho());
    Print("Session 1 added\n");

    // Two clients serially accessing one session

    Endpoint endpoint = Endpoint(server.Port(), iInterface);

    SocketTcpClient client1;
    client1.Open(*gEnv);
    client1.Connect(endpoint, 1000);
    Print("Client 1 connected\n");

    SocketTcpClient client2;
    client2.Open(*gEnv);
    client2.Connect(endpoint, 1000);
    Print("Client 2 connected\n");

    client1.Write(tx);
    client1.Read(rx);
    client1.Close();
    TEST(rx == tx);

    client2.Write(tx);
    client2.Read(rx);
    client2.Close();
    TEST(rx == tx);

    // Add second session
    
    server.Add("TSS2", new TcpSessionEcho());
    Print("Session 2 added\n");

    // Two clients accessing two sessions in parallel
    
    client1.Open(*gEnv);
    client1.Connect(endpoint, 1000);
    Print("Client 1 connected\n");

    client2.Open(*gEnv);
    client2.Connect(endpoint, 1000);
    Print("Client 2 connected\n");

    client1.Write(tx);
    client2.Write(tx);
    client2.Read(rx);
    TEST(rx == tx);

    client1.Read(rx);
    TEST(rx == tx);

    client1.Close();
    client2.Close();
    
    // Send large message
    
    client1.Open(*gEnv);
    client1.Connect(endpoint, 1000);
    Print("Client 1 connected\n");
    
    Bwh largetx(1000);
    Bwh largerx(1000);
    
    largetx.SetBytes(largetx.MaxBytes());
    largetx.Fill('X');
    
    client1.Write(largetx);
    client1.Read(largerx, largetx.Bytes());
    TEST(largerx == largetx);

    // Send/receive multiple times

    tx.SetBytes(25);
    
    for (TInt i=0; i<10; i++) {
        client1.Write(tx);
        client1.Receive(rx, 25);
        Print(rx);
        Print("\n");
        TEST(rx == tx);
    }
    
    // Send 2, receive 2

    tx.SetBytes(25);
    
    Print("Send 2, then receivd 1\n");
    
    client1.Write(tx);
    client1.Write(tx);

    Brn rx2("ABCDEFGHIJKLMNOPQRSTUVWXYABCDEFGHIJKLMNOPQRSTUVWXY");
    Bws<50> rx3;
    client1.Receive(rx3, 50);
    TEST(rx3.Bytes() == 50); // receive both messages in one
    TEST(rx3 == rx2);

    // Close session

    tx.SetBytes(26);
    client1.Write(tx);
    client1.Receive(rx, 26);
    TEST(rx == tx);
    client1.Close();

    // Test different variants of Receive function

    // receive buffer is > expected message
    Bws<50> rx4;

    client1.Open(*gEnv);
    client1.Connect(endpoint, 1000);
    Print("Client 1 connected\n");

    // Send 26 bytes (server then closes the session)
    tx.SetBytes(26);
    client1.Write(tx);
    // Receive with 1 arg will read any number of bytes in range [0, maxBufferLen]
    client1.Read(rx4);
    TEST(rx4.Bytes() == 26);
    TEST(rx4 == tx);

    // Subsequent reads should throw, leaving the buffer with size 0 since socket was remotely closed
    TEST_THROWS(client1.Read(rx4), ReaderError);
    TEST(rx4.Bytes() == 0);
    client1.Close();

    client1.Open(*gEnv);
    client1.Connect(endpoint, 1000);
    Print("Client 1 connected\n");

    // Send 26 bytes (server then closes the session)
    tx.SetBytes(26);
    client1.Write(tx);
    // Receive with 2 args expects the number of bytes given. It does one of 2 things:
    //  - block until it gets the specified number of bytes
    //  - throw a NetworkError (on a genuine socket error or if the server closed the session)
    TEST_THROWS(client1.Receive(rx4, 50), NetworkError);
    client1.Close();
    Thread::Sleep(20);
}

// TcpServerShutdown

class TcpSessionTest : public SocketTcpSession
{
private:
    virtual void Run();
};

void TcpSessionTest::Run()
{
    Bws<1> message;
    while (true) {
        Read(message);
    }
}

class SuiteTcpServerShutdown : public Suite, public INonCopyable
{
public:
    SuiteTcpServerShutdown(TIpAddress aInterface) : Suite("Threading tests for the TCP Server"), iInterface(aInterface) {}
    void Test();
private:
    TIpAddress iInterface;
};

void SuiteTcpServerShutdown::Test()
{
    SocketTcpServer *server;

    // server thread priority > main thread priority - no sessions open
    server = new SocketTcpServer(*gEnv, "TSSX", 0, iInterface, kPriorityNormal + kPriorityMore);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());
    delete server;
    Thread::Sleep(500);
    TEST(1==1);

    if (!Thread::SupportsPriorities()) {
        // no point in repeating the same test for varying priorities if we don't support priorities
        return;
    }

    server = new SocketTcpServer(*gEnv, "TSSX", 0, iInterface, kPriorityNormal + kPriorityLess);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());
    delete server;
    Thread::Sleep(500);
    TEST(1==1);

    // server thread priority == main thread priority - no sessions open
    server = new SocketTcpServer(*gEnv, "TSSX", 0, iInterface, kPriorityNormal);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());
    delete server;
    Thread::Sleep(500);
    TEST(1==1);


    // server thread priority > main thread priority - one session open
    server = new SocketTcpServer(*gEnv, "TSSX", 0, iInterface, kPriorityNormal + kPriorityMore);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());

    SocketTcpClient client1;
    client1.Open(*gEnv);
    client1.Connect(Endpoint(1995, iInterface), 1000);
    delete server;
    Thread::Sleep(500);
    client1.Close();
    TEST(1==1);

    // server thread priority < main thread priority - one session open
    server = new SocketTcpServer(*gEnv, "TSSX", 0, iInterface, kPriorityNormal + kPriorityLess);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());
    SocketTcpClient client2;
    client2.Open(*gEnv);
    client2.Connect(Endpoint(server->Port(), iInterface), 1000);
    delete server;
    Thread::Sleep(500);
    client2.Close();
    TEST(1==1);

    // server thread priority == main thread priority - one session open
    server = new SocketTcpServer(*gEnv, "TSSX", 0, iInterface, kPriorityNormal);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());
    SocketTcpClient client3;
    client3.Open(*gEnv);
    client3.Connect(Endpoint(server->Port(), iInterface), 1000);
    delete server;
    Thread::Sleep(500);
    client3.Close();
    TEST(1==1);
}


class SuiteEndpoint : public Suite
{
public:
    SuiteEndpoint() : Suite("Endpoint class tests") {}
    void Test();
};

void SuiteEndpoint::Test()
{
    // Test bad DNS look ups
    Endpoint ep;
    TEST_THROWS(ep.SetAddress(Brn("baddomainname.linn.co.uk")), NetworkError);
    TEST_THROWS(Endpoint ep2(1234, Brn("baddomainname.linn.co.uk")); (void)ep2, NetworkError);

    Bws<32> buffer;
    ep.SetAddress(Brn("127.0.0.1"));

    // Confirm that TIpAddress is network-order.
    TEST(ep.Address() == Arch::BigEndian4(0x7F000001));

    // Check address -> string.
    ep.AppendAddress(buffer);
    TEST(buffer == Brn("127.0.0.1"));

    // Checkout address decomposition.
    TByte ip[4];
    ep.GetAddressOctets(ip);
    TEST((ip[0] == 127) && (ip[1] == 0) && (ip[2] == 0) && (ip[3] == 1));
}

const TUint kMulticastPort = 2000;
const Brn kMulticastAddress("239.252.0.0");

static void AppendUint32(Bwx& aBuf, TUint aNum)
{
    TUint bytes = aBuf.Bytes();
    ASSERT(bytes + sizeof(TUint32) <= aBuf.MaxBytes());
    memcpy(const_cast<TByte*>(aBuf.Ptr()+bytes), &aNum, sizeof(TUint32));
    aBuf.SetBytes(bytes + sizeof(TUint32));
}

class SuiteMulticast : public Suite
{
public:
    SuiteMulticast();
    ~SuiteMulticast();
private:
    void Test();
    void Receiver();
private:
    Semaphore iSender;
    Semaphore iReceiver;
    ThreadFunctor* iThread0;
    ThreadFunctor* iThread1;
    Mutex iPortLock;
    TUint iPort;

    static const TUint kBufBytes = 1004;
    static const TUint kMsgBytes = 1000;
    static const TUint kQuit = 0xFFFFFFFF;

    Bwh iExp;
};

SuiteMulticast::SuiteMulticast() :
    Suite("Multicast Tests")
    , iSender("MCTS", 0)
    , iReceiver("MCTR", 0)
    , iPortLock("MPRT")
    , iPort(0)
    , iExp(kBufBytes)
{
    iThread0 = new ThreadFunctor("MUL1", MakeFunctor(*this, &SuiteMulticast::Receiver));
    iThread1 = new ThreadFunctor("MUL2", MakeFunctor(*this, &SuiteMulticast::Receiver));

    TUint i;
    AppendUint32(iExp, 0); //save space for count
    for( i=0; i < kMsgBytes/4; i++) { //prefill iExp with expected values
        AppendUint32(iExp, i);
    }
}

SuiteMulticast::~SuiteMulticast()
{
    delete iThread0;
    delete iThread1;
}

void SuiteMulticast::Test()
{
    iThread0->Start();
    iThread1->Start();

    iSender.Wait();
    iSender.Wait();

    SocketUdp send(*gEnv);

    Bwn buf(iExp);
    TUint i;
    for( i=0; i < kMsgBytes; i++) {
        buf.SetBytes(0);
        AppendUint32(buf, i); //num of bytes in this message
        buf.SetBytes(i + sizeof(TUint)); //use prefilled values
        send.Send(buf, Endpoint(iPort, kMulticastAddress));
        // assume that a delay of 500ms without response implies that the message wasn't delivered
        try {
            iSender.Wait(500);
            iSender.Wait(500);
        }
        catch (Timeout&) {
            Print("SuiteMulticast - message(s) not delivered\n");
            TEST(1 == 0);
            return; // temp
        }

        if (iSender.Clear()) {
            TEST(1 == 0);
            Print("SuiteMulticast - sent one message, received more than once\n");
        }
    }

    buf.SetBytes(0);
    AppendUint32(buf, kQuit);
    send.Send(buf, Endpoint(iPort, kMulticastAddress));

    try {
        iSender.Wait(500);
        iSender.Wait(500);
    }
    catch (Timeout&) {
        Print("SuiteMulticast - quit message(s) not delivered\n");
    }
}

void SuiteMulticast::Receiver()
{
    iPortLock.Wait();
    SocketUdpMulticast recv(*gEnv, 0, Endpoint(iPort, kMulticastAddress));
    iPort = recv.Port();
    iPortLock.Signal();

    iSender.Signal(); // signal ready to begin receiving

    Bwh buf(kBufBytes);
    Brn exp = iExp.Split(4);
    while(1) {
        recv.Receive(buf);
        TUint num = *((TUint32*)buf.Ptr());
        if(num == kQuit) {
            break;
        }
        Brn exp2 = exp.Split(0, num);
        Brn buf2 = buf.Split(4);
        TEST(buf2 == exp2);
        iSender.Signal();
    }

    iSender.Signal();
}

class SuiteUnicast : public Suite
{
public:
    SuiteUnicast(TIpAddress aInterface);
    ~SuiteUnicast();
private:
    void Test();
    void Receiver();
    void Send(TUint aVal);
private:
    static const TUint kMsgBytes = 256;
    static const TUint kQuit = 0xFFFFFFFF;
    static const TUint kTestIterations = 1000;
private:
    SocketUdp* iSender;
    SocketUdp* iReceiver;
    ThreadFunctor* iReceiverThread;
    TUint iSendVal;
    TUint iLastVal;
    Endpoint iEndpoint;
};

SuiteUnicast::SuiteUnicast(TIpAddress aInterface)
    : Suite("Unicast Tests")
{
    iReceiver = new SocketUdp(*gEnv);
    iReceiver->SetRecvBufBytes(kMsgBytes * kTestIterations * 2);
    iEndpoint = Endpoint(iReceiver->Port(), aInterface);
    Print("Receiver running at port %u\n", iReceiver->Port());
    iSender = new SocketUdp(*gEnv);
    iReceiverThread = new ThreadFunctor("UNIC", MakeFunctor(*this, &SuiteUnicast::Receiver));
    iReceiverThread->Start();
}

SuiteUnicast::~SuiteUnicast()
{
    delete iReceiverThread;
    delete iSender;
    delete iReceiver;
}

void SuiteUnicast::Test()
{
    for (TUint i=0; i<kTestIterations; i++) {
        Send(i);
    }
    Send(kQuit);
}

void SuiteUnicast::Send(TUint aVal)
{
    Bws<kMsgBytes> buf;
    const TUint count = kMsgBytes/sizeof(TUint);
    for (TUint i=0; i<count; i++) {
        AppendUint32(buf, aVal);
    }
    iSendVal = aVal;
    iSender->Send(buf, iEndpoint);
}

void SuiteUnicast::Receiver()
{
    TBool first = true;
    iLastVal = 0;
    TUint val;
    Bws<kMsgBytes> recv;
    do {
        recv.SetBytes(0);
        (void)iReceiver->Receive(recv);
        ASSERT(recv.Bytes() >= sizeof(TUint32));
        val = *((TUint32*)recv.Ptr());
        if (val != kQuit) {
            if (first) {
                TEST(val == 0);
                first = false;
            }
            else {
                TEST(val == iLastVal+1);
            }
        }
        //Print("Received %u, last sent %u\n", val, iSendVal);
        iLastVal = val;
    } while (val != kQuit);
}


// SuiteMsgUdp
class SuiteMsgUdp : public SuiteUnitTest
{
public:
    SuiteMsgUdp();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestBufferSize();
    void TestChangeBuffer();
    void TestReplaceEndpoint();
    void TestClear();
private:
    static const TUint kMaxMsgSize = 1000;
    MsgUdp* iMsg;
};

SuiteMsgUdp::SuiteMsgUdp()
    : SuiteUnitTest("SuiteMsgUdp")
{
    AddTest(MakeFunctor(*this, &SuiteMsgUdp::TestBufferSize));
    AddTest(MakeFunctor(*this, &SuiteMsgUdp::TestChangeBuffer));
    AddTest(MakeFunctor(*this, &SuiteMsgUdp::TestReplaceEndpoint));
    AddTest(MakeFunctor(*this, &SuiteMsgUdp::TestClear));
}

void SuiteMsgUdp::Setup()
{
    iMsg = new MsgUdp(kMaxMsgSize);
}

void SuiteMsgUdp::TearDown()
{
    delete iMsg;
}

void SuiteMsgUdp::TestBufferSize()
{
    // test if a buffer with the correct size is initialised
    TEST(iMsg->Buffer().Bytes() == 0);
    TEST(iMsg->Buffer().MaxBytes() == kMaxMsgSize);
}

void SuiteMsgUdp::TestChangeBuffer()
{
    // test that making changes to the buffer actually results in the buffer
    // being held by the msg being changed
    static const TByte val = 1;
    Bwx& buf1 = iMsg->Buffer();
    memset((void*)buf1.Ptr(), val, buf1.MaxBytes());
    buf1.SetBytes(buf1.MaxBytes());

    Bwx& buf2 = iMsg->Buffer();
    TEST(buf2.Bytes() == kMaxMsgSize);
    TEST(buf2[0] == val);
    TEST(buf2[buf2.Bytes()-1] == val);
}

void SuiteMsgUdp::TestReplaceEndpoint()
{
    // test that making changes to the endpoint results in the endpoint being
    // held by the msg being changed
    Endpoint epNew = Endpoint(1234, 1234);
    Endpoint& epMsg = iMsg->GetEndpoint();

    epMsg.Replace(epNew);

    epMsg = iMsg->GetEndpoint();
    TEST(epMsg.Port() == epNew.Port());
    TEST(epMsg.Address() == epNew.Address());
}

void SuiteMsgUdp::TestClear()
{
    // test that the Clear() method resets the buffer and endpoint held within
    // a msg

    // populate msg with some data
    static const TByte val = 1;
    Bwx& buf1 = iMsg->Buffer();
    memset((void*)buf1.Ptr(), val, buf1.MaxBytes());
    buf1.SetBytes(buf1.MaxBytes());

    Endpoint epNew = Endpoint(1234, 1234);
    Endpoint& epMsg = iMsg->GetEndpoint();
    epMsg.Replace(epNew);


    // now clear it
    iMsg->Clear();
    Bwx& buf2 = iMsg->Buffer();
    TEST(buf2.Bytes() == 0);
    TEST(buf2.MaxBytes() == kMaxMsgSize);

    epMsg = iMsg->GetEndpoint();
    TEST(epMsg.Port() == 0);
    TEST(epMsg.Address() == 0);
}


// SuiteSocketUdpServer

/**
 * Note: this suite assumes all UDP packets are received reliably and in order
 * as the tests will typically be run over loopback. However, this somewhat
 * contravenes the UDP spec, so, if some tests fail due to packet loss/ordering
 * problems, it is likely to be down to poor assumptions in the tests, rather
 * than the classes being tested.
 */
class SuiteSocketUdpServer : public SuiteUnitTest, public INonCopyable
{
public:
    SuiteSocketUdpServer(Environment& aEnv, TIpAddress aInterface);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    static void PrintBufInfo(const char* aMsg, Brx& aBuf);
    void GenerateNextMsg(Bwx& aBuf);
    void SendNextMsg(Bwx& aBuf);
    void CheckMsgValue(Brx& aBuf, TByte aVal);
    void TestOpenWhenInitialised();
    void TestClose();
    void TestReopen();
    void TestMsgQueueClearedWhenClosed();
    void TestMsgOrdering();
    void TestMsgsDisposedStart();
    void TestMsgsDisposed();
    void TestMsgsDisposedCapacityExceeded();
private:
    static const TUint kUdpRecvBufSize = 8192;
    // ensure (kMaxMsgSize+8)*kMaxMsgCount < kUdpRecvBufSize
    static const TUint kMaxMsgSize = 64;
    static const TUint kMaxMsgCount = 50;
    static const TUint kPort = 0;
    static const TUint kSendWaitMs = 3;
    static const TUint kDisposedCount = 10;
    Environment& iEnv;
    TIpAddress iInterface;
    SocketUdp* iSender;
    SocketUdpServer* iServer;
    TByte iCurrentVal;
    Endpoint iEndpoint;
    Bws<kMaxMsgSize> iOutBuf;
    Bws<kMaxMsgSize> iInBuf;
    TByte iMsgCount;
};

SuiteSocketUdpServer::SuiteSocketUdpServer(Environment& aEnv, TIpAddress aInterface)
    : SuiteUnitTest("SuiteSocketUdpServer")
    , iEnv(aEnv)
    , iInterface(aInterface)
{
    AddTest(MakeFunctor(*this, &SuiteSocketUdpServer::TestOpenWhenInitialised));
    AddTest(MakeFunctor(*this, &SuiteSocketUdpServer::TestClose));
    AddTest(MakeFunctor(*this, &SuiteSocketUdpServer::TestReopen));
    AddTest(MakeFunctor(*this, &SuiteSocketUdpServer::TestMsgQueueClearedWhenClosed));
    AddTest(MakeFunctor(*this, &SuiteSocketUdpServer::TestMsgOrdering));
    AddTest(MakeFunctor(*this, &SuiteSocketUdpServer::TestMsgsDisposedStart));
    AddTest(MakeFunctor(*this, &SuiteSocketUdpServer::TestMsgsDisposed));
    AddTest(MakeFunctor(*this, &SuiteSocketUdpServer::TestMsgsDisposedCapacityExceeded));
}

void SuiteSocketUdpServer::Setup()
{
    iSender = new SocketUdp(iEnv);
    iServer = new SocketUdpServer(iEnv, kMaxMsgSize, kMaxMsgCount, kPort, iInterface);
    iServer->SetRecvBufBytes(kUdpRecvBufSize);
    iCurrentVal = 0;
    Endpoint ep(iServer->Port(), iInterface);
    iEndpoint.Replace(ep);
    iOutBuf.SetBytes(0);
    iInBuf.SetBytes(0);
    iMsgCount = 0;
}

void SuiteSocketUdpServer::TearDown()
{
    delete iSender;
    delete iServer;
}

void SuiteSocketUdpServer::PrintBufInfo(const char* aMsg, Brx& aBuf)
{
    Log::Print("%s: aBuf[0]: %d, aBuf[aBuf.Bytes()-1]: %d, aBuf.Bytes(): %u\n", aMsg, aBuf[0], aBuf[aBuf.Bytes()-1], aBuf.Bytes());
}

void SuiteSocketUdpServer::GenerateNextMsg(Bwx& aBuf)
{
    ASSERT(aBuf.MaxBytes() == kMaxMsgSize);
    memset((void*)(aBuf.Ptr()), iCurrentVal++, aBuf.MaxBytes());
    aBuf.SetBytes(aBuf.MaxBytes());
}

void SuiteSocketUdpServer::SendNextMsg(Bwx& aBuf)
{
    GenerateNextMsg(aBuf);
    iSender->Send(aBuf, iEndpoint);
    // have an artificial sleep, giving receiver a chance to pull msgs
    Thread::Sleep(kSendWaitMs);
}

void SuiteSocketUdpServer::CheckMsgValue(Brx& aBuf, TByte aVal)
{
    TEST(aBuf.Bytes() == kMaxMsgSize);
    TEST(aBuf[0] == aVal);
    TEST(aBuf[aBuf.Bytes()-1] == aVal);
}

void SuiteSocketUdpServer::TestOpenWhenInitialised()
{
    // test calls to Receive are allowed immediately after initialisation
    SendNextMsg(iOutBuf);
    iServer->Receive(iInBuf);
    CheckMsgValue(iInBuf, iMsgCount++);
}

void SuiteSocketUdpServer::TestClose()
{
    // test calls to Receive are not allowed when server is closed
    Bws<kMaxMsgSize> buf;
    iServer->Close();
    TEST_THROWS(iServer->Receive(buf), AssertionFailed);
}

void SuiteSocketUdpServer::TestReopen()
{
    // test server can be successfully closed and re-opened
    SendNextMsg(iOutBuf);
    iServer->Receive(iInBuf);
    CheckMsgValue(iInBuf, iMsgCount++);

    iServer->Close();
    iServer->Open();

    SendNextMsg(iOutBuf);
    iServer->Receive(iInBuf);
    CheckMsgValue(iInBuf, iMsgCount++);
}

void SuiteSocketUdpServer::TestMsgQueueClearedWhenClosed()
{
    // test any msgs received by the server, but not yet read by a client, are
    // disposed of when the server is closed and not retrievable when server is
    // re-opened

    // send some msgs with server open, but don't read them
    for (TUint i=0; i<kDisposedCount; i++) {
        SendNextMsg(iOutBuf);
    }
    iMsgCount += kDisposedCount;

    // now close the server, which should clear the msg queue
    iServer->Close();

    // now re-open server and send more msgs - none of the first set of msgs
    // should be retrievable
    iServer->Open();
    TUint totalMsgCount = iMsgCount + 10;
    for (;iMsgCount<totalMsgCount;) {
        SendNextMsg(iOutBuf);
        iServer->Receive(iInBuf);
        // should definitely not receive any of first set of msgs, so if
        // ordering problems occur here and not down to network issues,
        // suggests msg queue wasn't cleared
        CheckMsgValue(iInBuf, iMsgCount++);
    }
}

void SuiteSocketUdpServer::TestMsgOrdering()
{
    // test msgs are received in correct order (when sent in a synchronised manner)
    for (TUint i=0; i<kMaxMsgCount; i++) {
        SendNextMsg(iOutBuf);
        iServer->Receive(iInBuf);
        CheckMsgValue(iInBuf, iMsgCount++);
    }
}

void SuiteSocketUdpServer::TestMsgsDisposedStart()
{
    // test msgs are disposed of when server is closed from start and re-opened
    TUint notDisposed = 0;

    iServer->Close();

    for (TUint i=0; i<kDisposedCount; i++) {
        SendNextMsg(iOutBuf);
    }

    iMsgCount += kDisposedCount;
    iServer->Open();

    // due to timing issues, server may have been re-opened and received one
    // (or more) msgs intended to be dropped - dispose of these
    TUint totalMsgCount = iMsgCount + 10;
    for (;iMsgCount<totalMsgCount;) {
        SendNextMsg(iOutBuf);
        iServer->Receive(iInBuf);
        if (iInBuf[0] < iMsgCount) { // rcvd a msg intended for disposal
            notDisposed++;
            continue;
        }
        CheckMsgValue(iInBuf, iMsgCount++);
    }
    ASSERT(notDisposed < kDisposedCount);
}

void SuiteSocketUdpServer::TestMsgsDisposed()
{
    // test msgs are disposed of when server is closed part-way through execution, then re-opened
    TUint notDisposed = 0;

    for (TUint i=0; i<10; i++) {
        SendNextMsg(iOutBuf);
        iServer->Receive(iInBuf);
        CheckMsgValue(iInBuf, iMsgCount++);
    }

    iServer->Close();
    for (TUint i=0; i<kDisposedCount; i++) {
        SendNextMsg(iOutBuf);
    }

    iMsgCount += kDisposedCount;
    iServer->Open();

    TUint totalMsgCount = iMsgCount + 10;
    for (;iMsgCount<totalMsgCount;) {
        SendNextMsg(iOutBuf);
        iServer->Receive(iInBuf);
        if (iInBuf[0] < iMsgCount) { // rcvd a msg intended for disposal
            notDisposed++;
            continue;
        }
        CheckMsgValue(iInBuf, iMsgCount++);
    }
    ASSERT(notDisposed < kDisposedCount);
}

void SuiteSocketUdpServer::TestMsgsDisposedCapacityExceeded()
{
    // test msgs are disposed of when server capacity exceeded
    TUint notDisposed = 0;

    for (TUint i=0; i<kMaxMsgCount+kDisposedCount; i++) {
        SendNextMsg(iOutBuf);
    }

    for (TUint i=0; i<kMaxMsgCount; i++) {
        iServer->Receive(iInBuf);
        CheckMsgValue(iInBuf, iMsgCount++);
    }

    iMsgCount += kDisposedCount;

    TUint totalMsgCount = iMsgCount + 10;
    for (;iMsgCount<totalMsgCount;) {
        SendNextMsg(iOutBuf);
        iServer->Receive(iInBuf);
        if (iInBuf[0] < iMsgCount) { // rcvd a msg intended for disposal
            notDisposed++;
            continue;
        }
        CheckMsgValue(iInBuf, iMsgCount++);
        ASSERT(notDisposed < kDisposedCount);
    }
}


// SuiteUdpServerManager

class SuiteUdpServerManager : public SuiteUnitTest, public INonCopyable
{
public:
    SuiteUdpServerManager(Environment& aEnv, TIpAddress aInterface);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestEmpty();
    void TestCreateOneServer();
    void TestCreateMultipleServers();
    void TestFindInvalidId();
private:
    static const TUint kMaxMsgSize = 1000;
    static const TUint kMaxMsgCount = 100;
    static const TUint kPort = 0;
    Environment& iEnv;
    TIpAddress iInterface;
    UdpServerManager* iManager;
};

SuiteUdpServerManager::SuiteUdpServerManager(Environment& aEnv, TIpAddress aInterface)
    : SuiteUnitTest("SuiteUdpServerManager")
    , iEnv(aEnv)
    , iInterface(aInterface)
{
    AddTest(MakeFunctor(*this, &SuiteUdpServerManager::TestEmpty));
    AddTest(MakeFunctor(*this, &SuiteUdpServerManager::TestCreateOneServer));
    AddTest(MakeFunctor(*this, &SuiteUdpServerManager::TestCreateMultipleServers));
    AddTest(MakeFunctor(*this, &SuiteUdpServerManager::TestFindInvalidId));
}

void SuiteUdpServerManager::Setup()
{
    iManager = new UdpServerManager(iEnv, kMaxMsgSize, kMaxMsgCount);
}

void SuiteUdpServerManager::TearDown()
{
    delete iManager;
}

void SuiteUdpServerManager::TestEmpty()
{
    // test if the server manager has no servers when initially created
    // - ids should start at 0
    TEST_THROWS(iManager->Find(0), AssertionFailed);
}

void SuiteUdpServerManager::TestCreateOneServer()
{
    // test we can ask the manager to create a server and that it is then
    // findable. there is nothing explicitly testable for this - successful
    // completion of the test signifies correct operation
    TUint id = iManager->CreateServer(kPort, iInterface);
    iManager->Find(id);
}

void SuiteUdpServerManager::TestCreateMultipleServers()
{
    // test that we can ask the manager to create multiple servers and that
    // they remain accessible via the same ids (i.e., ensure there are no
    // problems such as servers being discarded or re-ordered)

    // create the servers (and record their port as we go, as this is a unique
    // enough identifier)
    TUint id1 = iManager->CreateServer(kPort, iInterface);
    TUint port1 = iManager->Find(id1).Port();
    TUint id2 = iManager->CreateServer(kPort, iInterface);
    TUint port2 = iManager->Find(id2).Port();
    TUint id3 = iManager->CreateServer(kPort, iInterface);
    TUint port3 = iManager->Find(id3).Port();

    // retrieve all the servers, checking the ids and ports map correctly
    TEST(iManager->Find(id1).Port() == port1);
    TEST(iManager->Find(id2).Port() == port2);
    TEST(iManager->Find(id3).Port() == port3);
}

void SuiteUdpServerManager::TestFindInvalidId()
{
    // test that trying to access an invalid id causes an assert
    TUint id = iManager->CreateServer(kPort, iInterface);
    TEST_THROWS(iManager->Find(id+1), AssertionFailed);
}


class MainNetworkTestThread : public Thread
{
public:
    MainNetworkTestThread(TIpAddress aInterface) : Thread("MAIN", kPriorityNormal), iInterface(aInterface) {}
    void Run();
private:
    TIpAddress iInterface;
};

void MainNetworkTestThread::Run()
{
    //Debug::SetLevel(Debug::kNetwork);
    Runner runner("Network System");
    runner.Add(new SuiteTcpClient(iInterface));
    runner.Add(new SuiteSocketServer(iInterface));
    runner.Add(new SuiteTcpServerShutdown(iInterface));
    runner.Add(new SuiteEndpoint());
    //runner.Add(new SuiteUnicast(iInterface));
    // SuiteMulticast disabled because Linn network setup means that each multicast message is duplicated when
    // running on a core server (used for automated post-commit tests)
    //runner.Add(new SuiteMulticast());
    runner.Add(new SuiteMsgUdp());
    runner.Add(new SuiteSocketUdpServer(*gEnv, iInterface));
    runner.Add(new SuiteUdpServerManager(*gEnv, iInterface));
    runner.Run();
    Signal();
}

void TestNetwork(const std::vector<Brn>& aArgs)
{
    OptionParser parser;
    OptionUint adapter("-i", "--interface", 0, "index of network adapter to use");
    parser.AddOption(&adapter);
    if (!parser.Parse(aArgs) || parser.HelpDisplayed()) {
        return;
    }

    std::vector<NetworkAdapter*>* ifs = Os::NetworkListAdapters(*gEnv, Net::InitialisationParams::ELoopbackUse, "TestNetwork");
    ASSERT(ifs->size() > 0 && adapter.Value() < ifs->size());
    TIpAddress addr = (*ifs)[adapter.Value()]->Address();
    for (TUint i=0; i<ifs->size(); i++) {
        (*ifs)[i]->RemoveRef("TestNetwork");
    }
    delete ifs;
    Endpoint endpt(0, addr);
    Endpoint::AddressBuf buf;
    endpt.AppendAddress(buf);
    Print("Using network interface %s\n\n", buf.Ptr());
    Thread* th = new MainNetworkTestThread(addr);
    th->Start();
    th->Wait();
    delete th;
}
