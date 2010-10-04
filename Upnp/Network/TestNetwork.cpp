#include <Standard.h>
#include <Thread.h>
#include <TestFramework.h>
#include <OptionParser.h>
#include <Network.h>
#include <Debug.h>
#include <Os.h>
#include <Arch.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

// SuiteTcpClient

class TestServerSession : public SocketTcpSession
{
public:
    TestServerSession()
        : iSemaphore("TSTS", 0), iTestStarted("TSS2", 0)
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
            iTestDone = true;
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

    TBool TestDone() { return iTestDone; }
    const Brx& Buffer() { return iBuffer; }

private:
    Semaphore iSemaphore;
    Semaphore iTestStarted;
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
    SocketTcpServer server("TSSV", 1234, iInterface);
    TestServerSession* session = new TestServerSession();
    server.Add("TSS1", session);

    SocketTcpClient client;
    client.Open();
    client.Connect(Endpoint(1234, iInterface), 1000);

    // Test 1 - test Receive(Bwx& , TUint ) interface
    session->StartTest(1,32);
    TEST(session->TestDone() == false);
    // send 16 bytes
    client.Write(Brn("abcdefghijklmnop"));
    Thread::Sleep(500);
    TEST(session->TestDone() == false);
    // send 16 bytes
    client.Write(Brn("abcdefghijklmnop"));
    Thread::Sleep(500);
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
    Thread::Sleep(500);
    TEST(session->TestDone() == true);
    TEST(session->Buffer() == Brn("abcdefghijklmnopabcdefghij"));
    session->Close();

    client.Open();
    client.Connect(Endpoint(1234, iInterface), 1000);

    // Test 3 - test Receive(Bwx& ) interface - start the Receive before the send
    session->StartTest(3);
    TEST(session->TestDone() == false);
    // send 16 bytes
    client.Write(Brn("abcdefghijklmnop"));
    Thread::Sleep(500);
    TEST(session->TestDone() == true);
    TEST(session->Buffer() == Brn("abcdefghijklmnop"));

    // Test 3 - test Receive(Bwx& ) interface - send 2 messages and receive 1
    // send 16 bytes twice
    client.Write(Brn("abcdefghijklmnop"));
    client.Write(Brn("abcdefghijklmnop"));
    Thread::Sleep(500);
    // signal the receive
    session->StartTest(3);
    Thread::Sleep(10); // short sleep to avoid dependency on session running in a higher priority thread
    TEST(session->TestDone() == true);
    TEST(session->Buffer() == Brn("abcdefghijklmnopabcdefghijklmnop"));

    // Test 3 - test Receive(Bwx& ) interface - send nothing and close
    session->StartTest(3);
    TEST(session->TestDone() == false);
    // close the sending socket
    client.Close();
    Thread::Sleep(500);
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
    SuiteSocketServer(TIpAddress aInterface) : Suite("Zapp Socket Server Tests"), iInterface(aInterface) {}
    void Test();
private:
    TIpAddress iInterface;
};

void SuiteSocketServer::Test()
{
    Bws<26> rx;
    Bws<26> tx("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    SocketTcpServer server("TSSX", 1999, iInterface);
    Log::Print("Server created\n");
    server.Add("TSS1", new TcpSessionEcho());
    Log::Print("Session 1 added\n");

    // Two clients serially accessing one session

    Endpoint endpoint = Endpoint(1999, iInterface);

    SocketTcpClient client1;
    client1.Open();
    client1.Connect(endpoint, 1000);
    Log::Print("Client 1 connected\n");

    SocketTcpClient client2;
    client2.Open();
    client2.Connect(endpoint, 1000);
    Log::Print("Client 2 connected\n");

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
    Log::Print("Session 2 added\n");

    // Two clients accessing two sessions in parallel
    
    client1.Open();
    client1.Connect(endpoint, 1000);
    Log::Print("Client 1 connected\n");

    client2.Open();
    client2.Connect(endpoint, 1000);
    Log::Print("Client 2 connected\n");

    client1.Write(tx);
    client2.Write(tx);
    client2.Read(rx);
    TEST(rx == tx);

    client1.Read(rx);
    TEST(rx == tx);

    client1.Close();
    client2.Close();
    
    // Send large message
    
    client1.Open();
    client1.Connect(endpoint, 1000);
    Log::Print("Client 1 connected\n");
    
    Bws<1000> largetx;
    Bws<1000> largerx;
    
    largetx.SetBytes(largetx.MaxBytes());
    largetx.Fill('X');
    
    client1.Write(largetx);
    client1.Read(largerx);
    TEST(largerx == largetx);

    // Send/receive multiple times

    tx.SetBytes(25);
    
    for (TInt i=0; i<10; i++) {
        client1.Write(tx);
        client1.Receive(rx, 25);
        Log::Print(rx);
        Log::Print("\n");
        TEST(rx == tx);
    }
    
    // Send 2, receive 2

    tx.SetBytes(25);
    
    Log::Print("Send 2, then receivd 1\n");
    
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

    client1.Open();
    client1.Connect(endpoint, 1000);
    Log::Print("Client 1 connected\n");

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

    client1.Open();
    client1.Connect(endpoint, 1000);
    Log::Print("Client 1 connected\n");

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
    server = new SocketTcpServer("TSSX", 1998, iInterface, kPriorityNormal + kPriorityMore);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());
    delete server;
    Thread::Sleep(500);
    TEST(1==1);

    if (!Thread::SupportsPriorities()) {
        // no point in repeating the same test for varying priorities if we don't support priorities
        return;
    }

    server = new SocketTcpServer("TSSX", 1997, iInterface, kPriorityNormal + kPriorityLess);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());
    delete server;
    Thread::Sleep(500);
    TEST(1==1);

    // server thread priority == main thread priority - no sessions open
    server = new SocketTcpServer("TSSX", 1996, iInterface, kPriorityNormal);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());
    delete server;
    Thread::Sleep(500);
    TEST(1==1);


    // server thread priority > main thread priority - one session open
    server = new SocketTcpServer("TSSX", 1995, iInterface, kPriorityNormal + kPriorityMore);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());

    SocketTcpClient client1;
    client1.Open();
    client1.Connect(Endpoint(1995, iInterface), 1000);
    delete server;
    Thread::Sleep(500);
    client1.Close();
    TEST(1==1);

    // server thread priority < main thread priority - one session open
    server = new SocketTcpServer("TSSX", 1994, iInterface, kPriorityNormal + kPriorityLess);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());
    SocketTcpClient client2;
    client2.Open();
    client2.Connect(Endpoint(1994, iInterface), 1000);
    delete server;
    Thread::Sleep(500);
    client2.Close();
    TEST(1==1);

    // server thread priority == main thread priority - one session open
    server = new SocketTcpServer("TSSX", 1993, iInterface, kPriorityNormal);
    server->Add("TSS1", new TcpSessionTest());
    server->Add("TSS2", new TcpSessionTest());
    SocketTcpClient client3;
    client3.Open();
    client3.Connect(Endpoint(1993, iInterface), 1000);
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
    TEST_THROWS(ep.SetAddress(Brn("baddomainname")), NetworkError);
    TEST_THROWS(Endpoint ep2(1234, Brn("baddomainname")); (void)ep2, NetworkError);
}

const TUint kMulticastPort = 2000;
const Brn kMulticastAddress("239.252.0.0");

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

    static const TUint kBufBytes = 1004;
    static const TUint kMsgBytes = 1000;
    static const TUint kQuit = 0xFFFFFFFF;

    Bwh iExp;
};

SuiteMulticast::SuiteMulticast() :
    Suite("Multicast Tests")
    , iSender("MCTS", 0)
    , iReceiver("MCTR", 0)
    , iExp(kBufBytes)
{
    iThread0 = new ThreadFunctor("MUL1", MakeFunctor(*this, &SuiteMulticast::Receiver));
    iThread1 = new ThreadFunctor("MUL2", MakeFunctor(*this, &SuiteMulticast::Receiver));

    TUint i;
    iExp.AppendUint32(0); //save space for count
    for( i=0; i < kMsgBytes/4; i++) { //prefill iExp with expected values
        iExp.AppendUint32(i);
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

    SocketUdpClient send(Endpoint(kMulticastPort, kMulticastAddress), 1);

    Bwn buf(iExp);
    TUint i;
    for( i=0; i < kMsgBytes; i++) {
        buf.SetBytes(0);
        buf.AppendUint32(i); //num of bytes in this message
        buf.SetBytes(i + sizeof(TUint)); //use prefilled values
        send.Send(buf);
        // assume that a delay of 500ms without response implies that the message wasn't delivered
        try {
            iSender.Wait(500);
            iSender.Wait(500);
        }
        catch (Timeout&) {
            Log::Print("SuiteMulticast - message(s) not delivered\n");
            TEST(1 == 0);
        }

        if (iSender.Clear()) {
            TEST(1 == 0);
            Log::Print("SuiteMulticast - sent one message, received mnore than once\n");
        }
    }

    buf.SetBytes(0);
    buf.AppendUint32(kQuit);
    send.Send(buf);

    try {
        iSender.Wait(500);
        iSender.Wait(500);
    }
    catch (Timeout&) {
        Log::Print("SuiteMulticast - quit message(s) not delivered\n");
    }
}

void SuiteMulticast::Receiver()
{
    SocketUdpMulticast recv(Endpoint(kMulticastPort, kMulticastAddress), 1);

    iSender.Signal(); // signal ready to begin receiving

    Bwh buf(kBufBytes);
    Brn exp = iExp.Split(4);
    while(1) {
        recv.Receive(buf);
        TUint num = Arch::BigEndian4(*((TUint32*)(buf.Ptr())));
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

class MainTestThread : public Thread
{
public:
    MainTestThread(TIpAddress aInterface) : Thread("MAIN", kPriorityNormal), iInterface(aInterface) {}
    void Run();
private:
    TIpAddress iInterface;
};

void MainTestThread::Run()
{
//    Debug::SetLevel(Debug::kNetwork);
    Runner runner("Network System");
    runner.Add(new SuiteTcpClient(iInterface));
    runner.Add(new SuiteSocketServer(iInterface));
    runner.Add(new SuiteTcpServerShutdown(iInterface));
    runner.Add(new SuiteEndpoint());
    runner.Add(new SuiteMulticast());
    runner.Run();
    Signal();
}

void Zapp::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    OptionUint adapter("-i", "--interface", 0, "index of network adapter to use");
    parser.AddOption(&adapter);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }

    UpnpLibrary::InitialiseMinimal(aInitParams);

    std::vector<NetworkInterface*>* ifs = Os::NetworkListInterfaces();
    ASSERT(ifs->size() > 0 && adapter.Value() < ifs->size());
    TIpAddress addr = (*ifs)[adapter.Value()]->Address();
    Print("Using network interface %d.%d.%d.%d\n", addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff);
    MainTestThread th(addr);
    th.Start();
    th.Wait();
    delete ifs;

    UpnpLibrary::Close();
}
