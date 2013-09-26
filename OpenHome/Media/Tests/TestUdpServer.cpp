#include <OpenHome/Media/UdpServer.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/SuiteUnitTest.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::TestFramework;


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
    //void TestSubnetChanged();
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
    //AddTest(MakeFunctor(*this, &SuiteSocketUdpServer::TestSubnetChanged));
}

void SuiteSocketUdpServer::Setup()
{
    iSender = new SocketUdp(iEnv);
    iServer = new SocketUdpServer(iEnv, kMaxMsgSize, kMaxMsgCount, kPort, iInterface);
    try {
        iServer->SetRecvBufBytes(kUdpRecvBufSize);
    }
    catch (NetworkError&) {
        Log::Print("Failed to set UDP receive buffer size to %u bytes\n", kUdpRecvBufSize);
    }
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

//void SuiteSocketUdpServer::TestSubnetChanged()
//{
//    // test that attempting to change the subnet adapter succeeds.
//    // there is no way to verify the server has changed subnet, so this test
//    // running to completion without crashing is the best that can be done
//    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
//    TUint newSubnet = 0; // dummy subnet
//    nifList.SetCurrentSubnet(newSubnet);
//}


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



void TestUdpServer(Environment& aEnv)
{
    NetworkAdapterList& nifList = aEnv.NetworkAdapterList();
    AutoNetworkAdapterRef ref(aEnv, "TestUdpServer");
    NetworkAdapter* current = ref.Adapter();

    // get current subnet, otherwise choose first from a list
    if (current == NULL) {
        std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
        if (subnetList->size() > 0) {
            current = (*subnetList)[0];
        }
        NetworkAdapterList::DestroySubnetList(subnetList);
    }

    ASSERT(current != NULL); // should probably never be the case, but tests would fail if it was

    Runner runner("UdpServer tests");
    runner.Add(new SuiteMsgUdp());
    runner.Add(new SuiteSocketUdpServer(aEnv, current->Address()));
    runner.Add(new SuiteUdpServerManager(aEnv, current->Address()));
    runner.Run();
}
