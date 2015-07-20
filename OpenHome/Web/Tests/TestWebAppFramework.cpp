#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Private/Standard.h>

#include <OpenHome/Web/WebAppFramework.h>

namespace OpenHome {
namespace Web {
namespace Test {

class IHelperTabDeallocator
{
public:
    virtual void Deallocate(ITabMessage& aMessage) = 0;
    virtual ~IHelperTabDeallocator() {}
};

class HelperTabMessage;

class HelperDynamicTabAllocator : public IHelperTabDeallocator
{
public:
    HelperTabMessage& Allocate();
public: // from IHelperTabDeallocator
    void Deallocate(ITabMessage& aMessage);
};

class HelperTabMessage : public ITabMessage, public OpenHome::INonCopyable
{
    friend class HelperDynamicTabAllocator;
public:
    void Set(TUint aValue);
protected:
    HelperTabMessage(IHelperTabDeallocator& aDeallocator);
public: // from ITabMessage
    void Send(OpenHome::IWriter& aWriter);
    void Destroy();
private:
    IHelperTabDeallocator& iDeallocator;
    TUint iValue;
};

class HelperBufferWriter : public OpenHome::IWriter
{
public:
    HelperBufferWriter(TUint aMaxBytes);
    const OpenHome::Brx& Buffer();
    void Clear();
public: // from IWriter
    void Write(TByte aValue);
    void Write(const OpenHome::Brx& aBuffer);
    void WriteFlush();
private:
    OpenHome::Bwh iBuf;
};

class HelperSemaphore : public IFrameworkSemaphore
{
private:
    enum EMode {
        eNone,
        eSignal,
        eTimeout,
        eQueue
    };
public:
    HelperSemaphore();
    void SetModeSignalImmediately();
    void SetModeTimeout();
    void SetModeQueueMessageAndSignal(ITabHandler& aHandler, ITabMessage& aMessage);
    void ClearState();
    TUint ClearCount();
    TUint SignalCount();
public: // from IFrameworkSemaphore
    void Wait();
    void Wait(TUint aTimeoutMs);
    TBool Clear();
    void Signal();
private:
    EMode iMode;
    TUint iWaitCount;
    TUint iClearCount;
    TUint iSignalCount;
    ITabHandler* iHandler;
    ITabMessage* iPendingMsg;
};

class SuiteFrameworkTabHandler : public OpenHome::TestFramework::SuiteUnitTest
{
public:
    static const TUint kRecvBufBytes = 100;
    static const TUint kSendQueueSize = 10;
    static const TUint kSendTimeoutMs = 5;
public:
    SuiteFrameworkTabHandler();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestDestroyNoMessages();
    void TestDestroyUnsentMessages();
    void TestBlockingQueueEmpty();
    void TestBlockingSendOneMessage();
    void TestBlockingSendMultipleMessages();
    void TestBlockingSendQueueFull();
    void TestBlockingSendNewMessageQueued();
private:
    HelperBufferWriter* iHelperBufferWriter;
    HelperDynamicTabAllocator* iTabAllocator;
    HelperSemaphore* iHelperSemaphore;
    FrameworkTabHandler* iTabHandler;
};

class TestHelperResourceHandler : public IResourceHandler
{
private:
    static const Brn kMimeType;
public: // from IResourceHandler
    const OpenHome::Brx& MimeType() override;
    void Write(OpenHome::IWriter& aWriter, TUint aOffset, TUint aBytes) override;
    void Destroy() override;
};

class TestHelperTab : public ITab
{
public: // from ITab
    void Receive(const OpenHome::Brx& aMessage) override;
    void Destroy() override;
};

class TestHelperWebApp : public IWebApp
{
public:
    static const Brn kPrefix;
public:
    ~TestHelperWebApp();
public: // from IWebApp
    IResourceHandler& CreateResourceHandler(const Brx& aResource) override;
    ITab& Create(ITabHandler& aHandler, std::vector<const Brx*>& aLanguageList) override;
    const Brx& ResourcePrefix() const override;
private:
    std::vector<IResourceHandler*> iResourceHandlers;
    std::vector<ITab*> iTabs;
};

class TestHelperHttpReader : public IReader
{
public:
    enum ERequestType {
        EGet,
        EPost,
    };
private:
    static const TUint kHttpPort = 80;
    static const TUint kReadBufferBytes = 9 * 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 3000;
    static const TUint kResponseTimeoutMs = 60 * 1000;
public:
    TestHelperHttpReader(Environment& aEnv);
    ~TestHelperHttpReader();
    TUint Connect(const Uri& aUri, ERequestType aRequestType);
    void Close();
    TUint ContentLength() const;
public: // from IReader
    Brn Read(TUint aBytes);
    void ReadFlush();
    void ReadInterrupt();
private:
    TUint WriteRequest(const Uri& aUri, ERequestType aRequestType);
    TUint ConnectAndProcessHeader(const Uri& aUri, ERequestType aRequestType);
    TBool Connect(Endpoint aEndpoint);
    void Open();
private:
    Environment& iEnv;
    SocketTcpClient iTcpClient;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderLocation iHeaderLocation;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    Srs<1024> iReadBuffer;
    ReaderUntilS<1024> iReaderUntil;
    ReaderHttpResponse iReaderResponse;
    Sws<kWriteBufferBytes> iWriteBuffer;
    WriterHttpRequest iWriterRequest;
    ReaderHttpChunked iDechunker;
    TBool iSocketIsOpen;
    TBool iConnected;
    TUint iTotalBytes;
};

class ITestPipeWritable
{
public:
    virtual void Write(const Brx& aMessage) = 0;
    virtual ~ITestPipeWritable() {}
};

class ITestPipeReadable
{
public:
    virtual TBool Expect(const Brx& aMessage) = 0;
    virtual TBool ExpectEmpty() = 0;
    virtual ~ITestPipeReadable() {}
};

class TestPipeDynamic : public ITestPipeWritable, public ITestPipeReadable
{
public:
    static const TUint kMaxMsgBytes = 256;
public:
    TestPipeDynamic(TUint aSlots = 1024);
    ~TestPipeDynamic();
    void Print();
public: // from ITestPipeWritable
    void Write(const Brx& aMessage) override;
public: // from ITestPipeReadable
    TBool Expect(const Brx& aMessage) override;
    TBool ExpectEmpty() override;
private:
    FifoLiteDynamic<Bwh*> iFifo;
    Mutex iLock;
};

class TestHelperDestroyHandler : public ITabDestroyHandler, private INonCopyable
{
public:
    TestHelperDestroyHandler(ITestPipeWritable& aTestPipe);
public: // from ITabDestroyHandler
    void Destroy(IRefCountableUnlocked& aRefCountable) override;
private:
    ITestPipeWritable& iTestPipe;
};

class TestHelperFrameworkTimer : public IFrameworkTimer, private INonCopyable
{
public:
    TestHelperFrameworkTimer(ITestPipeWritable& aTestPipe);
public: // from IFrameworkTimer
    void Start(TUint aDurationMs, IFrameworkTimerHandler& aHandler) override;
    void Cancel() override;
private:
    ITestPipeWritable& iTestPipe;
};

//class SuiteTabTimeoutDetector : public OpenHome::TestFramework::SuiteUnitTest
//{
//public:
//    SuiteTabTimeoutDetector();
//private: // from SuiteUnitTest
//    void Setup();
//    void TearDown();
//};

class SuiteFrameworkTab : public OpenHome::TestFramework::SuiteUnitTest, private OpenHome::INonCopyable
{
public:
    SuiteFrameworkTab();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestTabDestroyed();
    void TestAllocatedTabDestroyed();   // Test Destroy() is called on underlying tab when FrameworkTab deleted.
    void TestDeleteWhileTabAllocated();
private:
    TestPipeDynamic* iTestPipe;
    TestHelperDestroyHandler* iDestroyHandler;
    TestHelperFrameworkTimer* iFrameworkTimer;
    TestHelperTab* iAppTab;
    const std::vector<const Brx*> iLanguages;
    FrameworkTab* iFrameworkTab;
};

class SuiteTabManager : public OpenHome::TestFramework::SuiteUnitTest, private INonCopyable
{
public:
    SuiteTabManager(Environment& aEnv);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestCreateAndGetTab();
    void TestTabIdsIncrement();
    void TestCreateTabManagerFull();
    void TestGetTab();
    void TestGetTabInvalidId();
    void TestDeleteWhileTabsAllocated();
private:
    Environment& iEnv;
    TabManager* iTabManager;
    TestHelperWebApp* iWebApp;
};

class SuiteWebAppFramework : public OpenHome::TestFramework::SuiteUnitTest, private INonCopyable
{
public:
    SuiteWebAppFramework(Environment& aEnv);
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void PresentationUrlChanged(const Brx& aUrl);
    void TestPort();
    void TestInterface();
    void TestPresentationUrl();
    void TestDeleteWhileClientTabOpen();
private:
    Environment& iEnv;
    Bws<Uri::kMaxUriBytes> iPresentationUrl;
    WebAppFramework* iFramework;
};

} // namespace Test
} // namespace Web
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Web;
using namespace OpenHome::Web::Test;


// HelperDynamicTabAllocator

HelperTabMessage& HelperDynamicTabAllocator::Allocate()
{
    HelperTabMessage* msg = new HelperTabMessage(*this);
    return *msg;
}

void HelperDynamicTabAllocator::Deallocate(ITabMessage& aMessage)
{
    delete &aMessage;
}


// HelperTabMessage

HelperTabMessage::HelperTabMessage(IHelperTabDeallocator& aDeallocator)
    : iDeallocator(aDeallocator)
    , iValue(0)
{
}

void HelperTabMessage::Set(TUint aValue)
{
    iValue = aValue;
}

void HelperTabMessage::Send(IWriter& aWriter)
{
    Bws<sizeof(iValue)> buf;
    Ascii::AppendDec(buf, iValue);
    aWriter.Write(buf);
}

void HelperTabMessage::Destroy()
{
    iDeallocator.Deallocate(*this);
}


// HelperBufferWriter

HelperBufferWriter::HelperBufferWriter(TUint aMaxBytes)
    : iBuf(aMaxBytes)
{
}

const Brx& HelperBufferWriter::Buffer()
{
    return iBuf;
}

void HelperBufferWriter::Clear()
{
    iBuf.SetBytes(0);
}

void HelperBufferWriter::Write(TByte aValue)
{
    iBuf.Append(aValue);
}

void HelperBufferWriter::Write(const Brx& aBuffer)
{
    iBuf.Append(aBuffer);
}

void HelperBufferWriter::WriteFlush()
{
}


// HelperSemaphore

HelperSemaphore::HelperSemaphore()
    : iMode(eNone)
    , iWaitCount(0)
    , iClearCount(0)
    , iSignalCount(0)
    , iHandler(NULL)
    , iPendingMsg(NULL)
{
}

void HelperSemaphore::SetModeSignalImmediately()
{
    iMode = eSignal;
}

void HelperSemaphore::SetModeTimeout()
{
    iMode = eTimeout;
}

void HelperSemaphore::SetModeQueueMessageAndSignal(ITabHandler& aHandler, ITabMessage& aMessage)
{
    iMode = eQueue;
    iHandler = &aHandler;
    iPendingMsg = &aMessage;
}

void HelperSemaphore::ClearState()
{
    iMode = eNone;
    iWaitCount = 0;
    iClearCount = 0;
    iSignalCount = 0;
    iHandler = NULL;
    iPendingMsg = NULL;
}

TUint HelperSemaphore::ClearCount()
{
    return iClearCount;
}

TUint HelperSemaphore::SignalCount()
{
    return iSignalCount;
}

void HelperSemaphore::Wait()
{
    // This shouldn't be called by the code being tested.
    ASSERTS();
}

void HelperSemaphore::Wait(TUint /*aTimeoutMs*/)
{
    iWaitCount++;
    if (iMode == eSignal) {
        ASSERT(iSignalCount > 0);
        return;
    }
    else if (iMode == eTimeout) {
        THROW(Timeout);
    }
    else if (iMode == eQueue) {
        iHandler->Send(*iPendingMsg);
    }
    else { // iMode == eNone
        ASSERTS(); // a mode hasn't been set
    }
}

TBool HelperSemaphore::Clear()
{
    iClearCount++;
    if (iSignalCount > iWaitCount) {
        return true;
    }
    return false;
}

void HelperSemaphore::Signal()
{
    iSignalCount++;
}


// SuiteFrameworkTabHandler

SuiteFrameworkTabHandler::SuiteFrameworkTabHandler()
    : SuiteUnitTest("SuiteFrameworkTabHandler")
{
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestDestroyNoMessages), "TestDestroyNoMessages");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestDestroyUnsentMessages), "TestDestroyUnsentMessages");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestBlockingQueueEmpty), "TestBlockingQueueEmpty");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestBlockingSendOneMessage), "TestBlockingSendOneMessage");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestBlockingSendMultipleMessages), "TestBlockingSendMultipleMessages");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestBlockingSendQueueFull), "TestBlockingSendQueueFull");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestBlockingSendNewMessageQueued), "TestBlockingSendNewMessageQueued");
}

void SuiteFrameworkTabHandler::Setup()
{
    iHelperBufferWriter = new HelperBufferWriter(kRecvBufBytes);
    iTabAllocator = new HelperDynamicTabAllocator();
    iHelperSemaphore = new HelperSemaphore();
    iTabHandler = new FrameworkTabHandler(*iHelperSemaphore, kSendQueueSize, kSendTimeoutMs);
}

void SuiteFrameworkTabHandler::TearDown()
{
    delete iTabHandler;
    delete iHelperSemaphore;
    delete iTabAllocator;
    delete iHelperBufferWriter;
}


void SuiteFrameworkTabHandler::TestDestroyNoMessages()
{
    // Completion of this without hanging shows an empty tab handler can be successfully deleted.
}

void SuiteFrameworkTabHandler::TestDestroyUnsentMessages()
{
    HelperTabMessage& msg = iTabAllocator->Allocate();
    msg.Set(0);
    iTabHandler->Send(msg);
}

void SuiteFrameworkTabHandler::TestBlockingQueueEmpty()
{
    // Queue no msgs, but try a blocking send. Should time out.
    iHelperSemaphore->SetModeTimeout();
    TEST_THROWS(iTabHandler->BlockingSend(*iHelperBufferWriter), Timeout);
    TEST(iHelperBufferWriter->Buffer().Bytes() == 0);
}

void SuiteFrameworkTabHandler::TestBlockingSendOneMessage()
{
    iHelperSemaphore->SetModeSignalImmediately();
    HelperTabMessage& msg = iTabAllocator->Allocate();
    msg.Set(0);
    const Brn bufIn("[0]");

    iTabHandler->Send(msg);
    iTabHandler->BlockingSend(*iHelperBufferWriter);
    TEST(iHelperBufferWriter->Buffer() == bufIn);
    TEST(iHelperSemaphore->SignalCount() == 1);
}

void SuiteFrameworkTabHandler::TestBlockingSendMultipleMessages()
{
    iHelperSemaphore->SetModeSignalImmediately();

    HelperTabMessage& msg1 = iTabAllocator->Allocate();
    msg1.Set(0);
    iTabHandler->Send(msg1);
    HelperTabMessage& msg2 = iTabAllocator->Allocate();
    msg2.Set(1);
    iTabHandler->Send(msg2);
    const Brn bufIn("[0,1]");

    iTabHandler->BlockingSend(*iHelperBufferWriter);

    TEST(iHelperBufferWriter->Buffer() == bufIn);
    TEST(iHelperSemaphore->SignalCount() == 2);
}

void SuiteFrameworkTabHandler::TestBlockingSendQueueFull()
{
    iHelperSemaphore->SetModeSignalImmediately();

    Bws<kRecvBufBytes> bufIn("[");
    for (TUint i=0; i<kSendQueueSize; i++) {
        HelperTabMessage& msg = iTabAllocator->Allocate();
        msg.Set(i);
        iTabHandler->Send(msg);

        Ascii::AppendDec(bufIn, i);
        if (i < kSendQueueSize-1) {
            bufIn.Append(",");
        }
    }
    bufIn.Append("]");

    iTabHandler->BlockingSend(*iHelperBufferWriter);
    TEST(iHelperBufferWriter->Buffer() == bufIn);
    TEST(iHelperSemaphore->SignalCount() == kSendQueueSize);
}

void SuiteFrameworkTabHandler::TestBlockingSendNewMessageQueued()
{
    // Try blocking send with no msgs ready, and then queue msg while blocking.
    // Custom semaphore will do the queueing of msg when its Wait() method is
    // called.

    HelperTabMessage& msg = iTabAllocator->Allocate();
    msg.Set(0);
    const Brn bufIn("[0]");

    iHelperSemaphore->SetModeQueueMessageAndSignal(*iTabHandler, msg);
    iTabHandler->BlockingSend(*iHelperBufferWriter);

    TEST(iHelperBufferWriter->Buffer() == bufIn);
    TEST(iHelperSemaphore->SignalCount() == 1);
}


// TestHelperResourceHandler

const Brn TestHelperResourceHandler::kMimeType("text/html");

const Brx& TestHelperResourceHandler::MimeType()
{
    return kMimeType;
}

void TestHelperResourceHandler::Write(IWriter& /*aWriter*/, TUint /*aOffset*/, TUint /*aBytes*/)
{
}

void TestHelperResourceHandler::Destroy()
{
}


// TestHelperTab

void TestHelperTab::Receive(const Brx& /*aMessage*/)
{
}

void TestHelperTab::Destroy()
{
}


// TestHelperWebApp

const Brn TestHelperWebApp::kPrefix("TestHelperWebApp");

TestHelperWebApp::~TestHelperWebApp()
{
    for (TUint i=0; i<iResourceHandlers.size(); i++) {
        delete iResourceHandlers[i];
    }
    for (TUint i=0; i<iTabs.size(); i++) {
        delete iTabs[i];
    }
}

IResourceHandler& TestHelperWebApp::CreateResourceHandler(const Brx& /*aResource*/)
{
    // Currently no tests that retrieve valid static resources.
    THROW(ResourceInvalid);

    //IResourceHandler* handler = new TestHelperResourceHandler();
    //iResourceHandlers.push_back(handler);
    //return *handler;
}

ITab& TestHelperWebApp::Create(ITabHandler& /*aHandler*/, std::vector<const Brx*>& /*aLanguageList*/)
{
    ITab* tab = new TestHelperTab();
    iTabs.push_back(tab);
    return *tab;
}

const Brx& TestHelperWebApp::ResourcePrefix() const
{
    return kPrefix;
}


// TestHelperHttpReader

TestHelperHttpReader::TestHelperHttpReader(Environment& aEnv)
    : iEnv(aEnv)
    , iReadBuffer(iTcpClient)
    , iReaderUntil(iReadBuffer)
    , iReaderResponse(aEnv, iReaderUntil)
    , iWriteBuffer(iTcpClient)
    , iWriterRequest(iWriteBuffer)
    , iDechunker(iReaderUntil)
    , iSocketIsOpen(false)
    , iConnected(false)
    , iTotalBytes(0)
{
    iReaderResponse.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderLocation);
    iReaderResponse.AddHeader(iHeaderTransferEncoding);
}

TestHelperHttpReader::~TestHelperHttpReader()
{
    if (iSocketIsOpen) {
        Close();
    }
}

TUint TestHelperHttpReader::Connect(const Uri& aUri, ERequestType aRequestType)
{
    if (iConnected) {
        Close();
    }

    TUint code = ConnectAndProcessHeader(aUri, aRequestType);
    if (code == 0) {
        Close();
        return code;
    }
    iConnected = true;

    return code;
}

void TestHelperHttpReader::Close()
{
    if (iSocketIsOpen) {
        iSocketIsOpen = false;
        iConnected = false;
        iTcpClient.Close();
    }
}

TUint TestHelperHttpReader::ContentLength() const
{
    ASSERT(iConnected);
    return iTotalBytes;
}

TBool TestHelperHttpReader::Connect(Endpoint aEndpoint)
{
    Open();
    try {
        iTcpClient.Connect(aEndpoint, kConnectTimeoutMs);
    }
    catch (NetworkTimeout&) {
        Close();
        return false;
    }
    catch (NetworkError&) {
        Close();
        return false;
    }

    return true;
}

void TestHelperHttpReader::Open()
{
    iTcpClient.Open(iEnv);
    ASSERT(!iSocketIsOpen);
    iSocketIsOpen = true;
}

Brn TestHelperHttpReader::Read(TUint aBytes)
{
    ASSERT(iConnected);
    return iDechunker.Read(aBytes);
}

void TestHelperHttpReader::ReadFlush()
{
    if (iConnected) {
        iDechunker.ReadFlush();
    }
}

void TestHelperHttpReader::ReadInterrupt()
{
    if (iConnected) {
        iDechunker.ReadInterrupt();
    }
}

TUint TestHelperHttpReader::WriteRequest(const Uri& aUri, ERequestType aRequestType)
{
    TInt port = aUri.Port();
    if (port == Uri::kPortNotSpecified) {
        port = kHttpPort;
    }

    Close();
    Endpoint ep;
    try {
        ep.Replace(Endpoint(port, aUri.Host()));
    }
    catch (NetworkError&) {
        return 0;
    }
    if (!Connect(ep)) {
        return 0;
    }

    try {
        Brn method;
        if (aRequestType == EGet) {
            method.Set(Http::kMethodGet);
        }
        else if (aRequestType == EPost) {
            method.Set(Http::kMethodPost);
        }
        else {
            ASSERTS();
        }
        iWriterRequest.WriteMethod(method, aUri.PathAndQuery(), Http::eHttp11);
        Http::WriteHeaderHostAndPort(iWriterRequest, aUri.Host(), port);
        Http::WriteHeaderConnectionClose(iWriterRequest);
        iWriterRequest.WriteFlush();
    }
    catch (WriterError&) {
        return 0;
    }

    try {
        iReaderResponse.Read(kResponseTimeoutMs);
    }
    catch (HttpError&) {
        return 0;
    }
    catch (ReaderError&) {
        return 0;
    }

    const TUint code = iReaderResponse.Status().Code();
    return code;
}

TUint TestHelperHttpReader::ConnectAndProcessHeader(const Uri& aUri, ERequestType aRequestType)
{
    Uri uri(aUri);
    TUint code = 0;

    iDechunker.SetChunked(false);
    for (;;) { // loop until we don't get a redirection response (i.e. normally don't loop at all!)
        code = WriteRequest(uri, aRequestType);
        if (code == 0) {
            return code;
        }
        // Check for redirection
        if (code >= HttpStatus::kRedirectionCodes && code < HttpStatus::kClientErrorCodes) {
            if (!iHeaderLocation.Received()) {
                return code;
            }

            uri.Replace(iHeaderLocation.Location());
            continue;
        }
        else if (code >= HttpStatus::kClientErrorCodes) {
            return code;
        }
        if (code != 0) {
            if (iHeaderTransferEncoding.IsChunked()) {
                iDechunker.SetChunked(true);
            }
            iTotalBytes = iHeaderContentLength.ContentLength();
            break;
        }
    }
    return code;
}


// TestPipeDynamic

TestPipeDynamic::TestPipeDynamic(TUint aSlots)
    : iFifo(aSlots)
    , iLock("TPDL")
{
}

TestPipeDynamic::~TestPipeDynamic()
{
    AutoMutex a(iLock);
    while (iFifo.SlotsUsed() > 0) {
        Bwh* buf = iFifo.Read();
        delete buf;
    }
}

void TestPipeDynamic::Print()
{
    AutoMutex a(iLock);
    const TUint slots = iFifo.SlotsUsed();
    Log::Print("\nTestPipeDynamic::Print\n");
    Log::Print("[\n");
    for (TUint i=0; i<slots; i++) {
        Bwh* buf = iFifo.Read();
        Log::Print("\t");
        Log::Print(*buf);
        Log::Print("\n");
        iFifo.Write(buf);
    }
    Log::Print("]\n");
}

void TestPipeDynamic::Write(const Brx& aMessage)
{
    AutoMutex a(iLock);
    Bwh* buf = new Bwh(aMessage);
    iFifo.Write(buf);
}

TBool TestPipeDynamic::Expect(const Brx& aMessage)
{
    AutoMutex a(iLock);
    if (iFifo.SlotsUsed() > 0) {
        Bwh* buf = iFifo.Read();
        const TBool match = (*buf == aMessage);
        delete buf;
        return match;
    }
    return false;
}

TBool TestPipeDynamic::ExpectEmpty()
{
    AutoMutex a(iLock);
    return (iFifo.SlotsUsed() == 0);
}


// TestHelperDestroyHandler

TestHelperDestroyHandler::TestHelperDestroyHandler(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

void TestHelperDestroyHandler::Destroy(IRefCountableUnlocked& /*aRefCountable*/)
{
    iTestPipe.Write(Brn("TestHelperDestroyHandler::Destroy"));
}


// TestHelperFrameworkTimer

TestHelperFrameworkTimer::TestHelperFrameworkTimer(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

void TestHelperFrameworkTimer::Start(TUint aDurationMs, IFrameworkTimerHandler& /*aHandler*/)
{
    Bws<TestPipeDynamic::kMaxMsgBytes> buf("TestHelperFrameworkTimer::Start ");
    Ascii::AppendDec(buf, aDurationMs);
    iTestPipe.Write(buf);
}

void TestHelperFrameworkTimer::Cancel()
{
    iTestPipe.Write(Brn("TestHelperFrameworkTimer::Cancel"));
}


//class SuiteTabTimeoutDetector : public OpenHome::TestFramework::SuiteUnitTest
//{
//public:
//    SuiteTabTimeoutDetector();
//private: // from SuiteUnitTest
//    void Setup();
//    void TearDown();
//};


// SuiteFrameworkTab

SuiteFrameworkTab::SuiteFrameworkTab()
    : SuiteUnitTest("SuiteFrameworkTab")
{
    AddTest(MakeFunctor(*this, &SuiteFrameworkTab::TestDeleteWhileTabAllocated), "TestDeleteWhileTabAllocated");
    //AddTest(MakeFunctor(*this, &SuiteFrameworkTab::), "");
}

void SuiteFrameworkTab::Setup()
{
    iTestPipe = new TestPipeDynamic();
    iDestroyHandler = new TestHelperDestroyHandler(*iTestPipe);
    iFrameworkTimer = new TestHelperFrameworkTimer(*iTestPipe);

    iAppTab = new TestHelperTab();

    iFrameworkTab = new FrameworkTab(0, *iDestroyHandler, *iFrameworkTimer, 32, 50, 5000);
}

void SuiteFrameworkTab::TearDown()
{
    delete iFrameworkTab;
    delete iAppTab;
    delete iFrameworkTimer;
    delete iDestroyHandler;
    delete iTestPipe;
}

void SuiteFrameworkTab::TestDeleteWhileTabAllocated()
{
    // Set a tab, then don't bother calling RemoveRef() or Destroy().
    // i.e., let TearDown() call delete on the FrameworkTab while a tab is still allocated.
    iFrameworkTab->Set(*iAppTab, iLanguages);
}


// SuiteTabManager

SuiteTabManager::SuiteTabManager(Environment& aEnv)
    : SuiteUnitTest("SuiteTabManager")
    , iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestCreateAndGetTab), "TestCreateAndGetTab");
    //AddTest(MakeFunctor(*this, &SuiteTabManager::TestTabIdsIncrement), "TestTabIdsIncrement");
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestCreateTabManagerFull), "TestCreateTabManagerFull");
    //AddTest(MakeFunctor(*this, &SuiteTabManager::TestGetTabInvalidId), "TestGetTabInvalidId");
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestDeleteWhileTabsAllocated), "TestDeleteWhileTabsAllocated");
}

void SuiteTabManager::Setup()
{
    iWebApp = new TestHelperWebApp();
    iTabManager = new TabManager(iEnv, 4, 10, 500, 5000);
}

void SuiteTabManager::TearDown()
{
    delete iTabManager;
    delete iWebApp;
}

void SuiteTabManager::TestCreateAndGetTab()
{
    std::vector<const Brx*> languages;
    const TUint id1 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id1 == 1);

    IFrameworkTab& tab = iTabManager->GetTab(id1);
    tab.Destroy();
}

void SuiteTabManager::TestTabIdsIncrement()
{
    // Allocate a few tabs.
    std::vector<const Brx*> languages;
    const TUint id1 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id1 == 1);
    TUint id2 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id2 == 2);
    TUint id3 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id3 == 3);

    // Destroy last tab and check numbering resumes from that point.
    IFrameworkTab& tab = iTabManager->GetTab(id3);
    tab.Destroy();
    id3 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id3 == 3);

    // Destroy tab from middle and check numbering resumes from that point, and skips over next allocated tab.
    tab = iTabManager->GetTab(id2);
    tab.Destroy();
    id2 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id2 == 2);

    const TUint id4 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id4 == 4);

    // Destroy all tabs to clean up.
    tab = iTabManager->GetTab(id1);
    tab.Destroy();
    tab = iTabManager->GetTab(id2);
    tab.Destroy();
    tab = iTabManager->GetTab(id3);
    tab.Destroy();
    tab = iTabManager->GetTab(id4);
    tab.Destroy();
}

void SuiteTabManager::TestCreateTabManagerFull()
{
    // Allocate all tabs.
    std::vector<const Brx*> languages;
    const TUint id1 = iTabManager->CreateTab(*iWebApp, languages);
    const TUint id2 = iTabManager->CreateTab(*iWebApp, languages);
    const TUint id3 = iTabManager->CreateTab(*iWebApp, languages);
    const TUint id4 = iTabManager->CreateTab(*iWebApp, languages);

    // Then try allocate another.
    TEST_THROWS(iTabManager->CreateTab(*iWebApp, languages), TabManagerFull);

    // Destroy all tabs.
    IFrameworkTab& tab1 = iTabManager->GetTab(id1);
    tab1.Destroy();
    IFrameworkTab& tab2 = iTabManager->GetTab(id2);
    tab2.Destroy();
    IFrameworkTab& tab3 = iTabManager->GetTab(id3);
    tab3.Destroy();
    IFrameworkTab& tab4 = iTabManager->GetTab(id4);
    tab4.Destroy();
}

void SuiteTabManager::TestGetTabInvalidId()
{
    // Try get tab when none allocated.
    TEST_THROWS(iTabManager->GetTab(0), InvalidTabId);
    TEST_THROWS(iTabManager->GetTab(1), InvalidTabId);

    // Allocate tabs, then try retrieve unallocated tab.
    std::vector<const Brx*> languages;
    const TUint id1 = iTabManager->CreateTab(*iWebApp, languages);
    const TUint id2 = iTabManager->CreateTab(*iWebApp, languages);
    TEST_THROWS(iTabManager->GetTab(3), InvalidTabId);

    // Test that tab can't be retrieved after Destroy() has been called.
    IFrameworkTab& tab = iTabManager->GetTab(id2);
    tab.Destroy();
    TEST_THROWS(iTabManager->GetTab(id2), InvalidTabId);

    // Cleanup.
    tab = iTabManager->GetTab(id1);
    tab.Destroy();
}

void SuiteTabManager::TestDeleteWhileTabsAllocated()
{
    // Test case where client is holding a tab open, but the WebAppFramework is being destroyed.
    // Allocate tab and don't do any cleanup here; allow TearDown() to delete TabManager and it should quietly cleanup allocated tabs.
    std::vector<const Brx*> languages;
    (void)iTabManager->CreateTab(*iWebApp, languages);
    //(void)iTabManager->GetTab(1);
}


// SuiteWebAppFramework

SuiteWebAppFramework::SuiteWebAppFramework(Environment& aEnv)
    : SuiteUnitTest("SuiteWebAppFramework")
    , iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuiteWebAppFramework::TestPort), "TestPort");
    AddTest(MakeFunctor(*this, &SuiteWebAppFramework::TestInterface), "TestInterface");
    AddTest(MakeFunctor(*this, &SuiteWebAppFramework::TestPresentationUrl), "TestPresentationUrl");
    AddTest(MakeFunctor(*this, &SuiteWebAppFramework::TestDeleteWhileClientTabOpen), "TestDeleteWhileClientTabOpen");
}

void SuiteWebAppFramework::Setup()
{
    iPresentationUrl.SetBytes(0);
    iFramework = new WebAppFramework(iEnv);
    TestHelperWebApp* webApp = new TestHelperWebApp();
    iFramework->Add(webApp, MakeFunctorGeneric(*this, &SuiteWebAppFramework::PresentationUrlChanged));
    iFramework->Start();
}

void SuiteWebAppFramework::TearDown()
{
    delete iFramework;
}

void SuiteWebAppFramework::PresentationUrlChanged(const Brx& aUrl)
{
    iPresentationUrl.Replace(aUrl);
}

void SuiteWebAppFramework::TestPort()
{

}

void SuiteWebAppFramework::TestInterface()
{

}

void SuiteWebAppFramework::TestPresentationUrl()
{
    Bws<Uri::kMaxUriBytes> expectedUrl;
    expectedUrl.Append("http://");
    Endpoint ep(iFramework->Port(), iFramework->Interface());
    ep.AppendEndpoint(expectedUrl);
    expectedUrl.Append("/");
    expectedUrl.Append(TestHelperWebApp::kPrefix);
    expectedUrl.Append("/index.html");

    TEST(iPresentationUrl == expectedUrl);
}

//void TestGetValidStaticResource();
//void TestGetInvalidStaticResource();
//// FIXME - the following uses Thread::Sleep - undesirable!
//// Instead, maybe test the WebAppFramework or FrameworkTab directly with a mock Timer to ensure they time out tabs appropriately when it hasn't been retrieved/touched within the timeout time.
//void TestClientTabTimeout();

void SuiteWebAppFramework::TestDeleteWhileClientTabOpen()
{
    TestHelperHttpReader httpReader(iEnv);

    Bws<Uri::kMaxUriBytes> lpUrl;
    lpUrl.Append("http://");
    Endpoint ep(iFramework->Port(), iFramework->Interface());
    ep.AppendEndpoint(lpUrl);
    lpUrl.Append("/");
    lpUrl.Append(TestHelperWebApp::kPrefix);
    lpUrl.Append("/lpcreate");

    Uri uri(lpUrl);
    // This does a GET. As there should be no lpcreate file, should get a 404 response.
    TUint code = httpReader.Connect(uri, TestHelperHttpReader::EGet);
    TEST(code == HttpStatus::kNotFound.Code());
    httpReader.Close();

    code = httpReader.Connect(uri, TestHelperHttpReader::EPost);
    TEST(code == HttpStatus::kOk.Code());
    httpReader.Close();

    // Tab should be automatically de-allocated if long-poll times out.
    //Thread::Sleep(6000); // FIXME - add test to FrameworkTab tests.
}



void TestWebAppFramework(Environment& aEnv)
{
    Runner runner("HTTP Framework tests\n");
    runner.Add(new SuiteFrameworkTabHandler());
    runner.Add(new SuiteFrameworkTab());
    runner.Add(new SuiteTabManager(aEnv));
    runner.Add(new SuiteWebAppFramework(aEnv));
    runner.Run();
}
