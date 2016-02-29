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
    HelperDynamicTabAllocator();
    ~HelperDynamicTabAllocator();
    HelperTabMessage& Allocate();
public: // from IHelperTabDeallocator
    void Deallocate(ITabMessage& aMessage);
private:
    std::vector<HelperTabMessage*> iMsgs;
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
    void Destroy(TUint aId) override;
private:
    ITestPipeWritable& iTestPipe;
};

class TestHelperFrameworkSemaphore : public IFrameworkSemaphore
{
public:
    TestHelperFrameworkSemaphore(const TChar* aId, ITestPipeWritable& aTestPipe);
    void BlockUntilWait();
public: // from IFrameworkSemaphore
    void Wait() override;
    TBool Clear() override;
    void Signal() override;
private:
    const TChar* iId;
    ITestPipeWritable& iTestPipe;
    Semaphore iSem;
    Semaphore iSemBlock;
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

class MockWriterThrowsWriterError : public OpenHome::IWriter
{
public: // from IWriter
    void Write(TByte aValue) override;
    void Write(const OpenHome::Brx& aBuffer) override;
    void WriteFlush() override;
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
    void TestSendWhileDisabled();
    void TestBlockingQueueEmpty();
    void TestDisableWhileBlockingSend();
    void TestBlockingSendOneMessage();
    void TestBlockingSendMultipleMessages();
    void TestBlockingSendQueueFull();
    void TestBlockingSendNewMessageQueued();
    void TestWriterError();
private:
    void LongPollThread();
private:
    TestPipeDynamic* iTestPipe;
    HelperBufferWriter* iHelperBufferWriter;
    HelperDynamicTabAllocator* iTabAllocator;
    TestHelperFrameworkSemaphore* iSemRead;
    TestHelperFrameworkSemaphore* iSemWrite;
    TestHelperFrameworkTimer* iTimer;
    FrameworkTabHandler* iTabHandler;
    Semaphore* iSemLpComplete;
};

class TestHelperResourceHandler : public IResourceHandler
{
public: // from IResourceHandler
    TBool Allocated() override;
    void SetResource(const Brx& aUri) override;
    TUint Bytes() override;
    void Write(IWriter& aWriter) override;
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
    ITab& Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList) override;
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

class TestHelperTabHandler : public IFrameworkTabHandler, private INonCopyable
{
public:
    TestHelperTabHandler(ITestPipeWritable& aTestPipe);
private: // from IFrameworkTabHandler
    void Send(ITabMessage& aMessage);
    void LongPoll(IWriter& aWriter);
    void Enable();
    void Disable();
private:
    ITestPipeWritable& iTestPipe;
};

class TestHelperTab : public ITab, private INonCopyable
{
public:
    TestHelperTab(ITestPipeWritable& aTestPipe);
public: // from ITab
    void Receive(const OpenHome::Brx& aMessage) override;
    void Destroy() override;
private:
    ITestPipeWritable& iTestPipe;
};

class TestHelperTabCreator : public ITabCreator, private INonCopyable
{
public:
    TestHelperTabCreator(ITestPipeWritable& aTestPipe);
public: // from ITabCreator
    ITab& Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList) override;
private:
    ITestPipeWritable& iTestPipe;
};

/**
* Always throws TabAllocatorFull when Create() is called.
*/
class TestHelperTabCreatorEmpty : public ITabCreator
{
public: // from ITabCreator
    ITab& Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList) override;
};

class TestHelperTabMessage : public ITabMessage, private INonCopyable
{
public:
    TestHelperTabMessage(ITestPipeWritable& aTestPipe, const Brx& aMessage);
public: // from ITabMessage
    void Send(IWriter& aWriter);
    void Destroy();
private:
    ITestPipeWritable& iTestPipe;
    Bws<20> iMsg;
};

class SuiteFrameworkTab : public TestFramework::SuiteUnitTest, private INonCopyable
{
public:
    SuiteFrameworkTab();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestCreateTab();
    void TestReuseTab();
    void TestCreateTabAllocatorEmpty();
    void TestSessionId();
    void TestReceive();
    void TestLongPoll();
    void TestSend();
    void TestTabTimeout();
    void TestDeleteWhileTabAllocated();
private:
    TestPipeDynamic* iTestPipe;
    TestHelperDestroyHandler* iDestroyHandler;
    TestHelperFrameworkTimer* iFrameworkTimer;
    TestHelperTabHandler* iTabHandler;
    TestHelperTabCreator* iTabCreator;
    const std::vector<char*> iLanguages;
    FrameworkTab* iFrameworkTab;
};

class TestHelperFrameworkTab : public IFrameworkTab, private INonCopyable
{
public:
    TestHelperFrameworkTab(ITestPipeWritable& aTestPipe, TUint aId);
    void CallDestroyHandler();
public: // from IFrameworkTab
    TUint SessionId() const override;
    void CreateTab(TUint aSessionId, ITabCreator& aTabCreator, ITabDestroyHandler& aDestroyHandler, const std::vector<char*>& aLanguages) override;
    void Clear() override;
    void Receive(const Brx& aMessage) override;
    void LongPoll(IWriter& aWriter) override;
private:
    ITestPipeWritable& iTestPipe;
    const TUint iId;
    TUint iSessionId;
    ITabDestroyHandler* iDestroyHandler;
};

class TestHelperFrameworkTabFull: public IFrameworkTab, private INonCopyable
{
public: // from IFrameworkTab
    TUint SessionId() const override;
    void CreateTab(TUint aSessionId, ITabCreator& aTabCreator, ITabDestroyHandler& aDestroyHandler, const std::vector<char*>& aLanguages) override;
    void Clear() override;
    void Receive(const Brx& aMessage) override;
    void LongPoll(IWriter& aWriter) override;
};

class SuiteTabManager : public TestFramework::SuiteUnitTest, private INonCopyable
{
public:
    SuiteTabManager();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestCreateTab();
    void TestDisableNoTabsAllocated();
    void TestDisable();
    void TestTabTimeout();
    void TestTabIdsIncrement();
    void TestCreateTabManagerFull();
    void TestCreateTabAllocatorEmpty();
    void TestInvalidTabId();
    void TestDeleteWhileTabsAllocated();
private:
    TestPipeDynamic* iTestPipe;
    std::vector<TestHelperFrameworkTab*> iTabs;
    TabManager* iTabManager;
    TestHelperWebApp* iWebApp;
};

class SuiteWebAppFramework : public TestFramework::SuiteUnitTest, private INonCopyable
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

HelperDynamicTabAllocator::HelperDynamicTabAllocator()
{
}

HelperDynamicTabAllocator::~HelperDynamicTabAllocator()
{
    if (iMsgs.size() > 0) {
        Log::Print("~HelperDynamicTabAllocator msgs not deallocated:\n");
        for (auto* m : iMsgs) {
            Log::Print("\t%p\n", m);
        }
        Log::Print("\n");

        ASSERTS();  // All msgs must have been deallocated.
    }
}

HelperTabMessage& HelperDynamicTabAllocator::Allocate()
{
    HelperTabMessage* msg = new HelperTabMessage(*this);
    iMsgs.push_back(msg);
    return *msg;
}

void HelperDynamicTabAllocator::Deallocate(ITabMessage& aMessage)
{
    auto it = iMsgs.begin();
    for (; it != iMsgs.end(); ++it) {
        if (*it == &aMessage) {
            (void)iMsgs.erase(it);
            return;
        }
    }

    ASSERTS();  // Couldn't find aMessage in list of allocated msgs.
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


// MockWriterThrowsWriterError

void MockWriterThrowsWriterError::Write(TByte /*aValue*/)
{
    THROW(WriterError);
}

void MockWriterThrowsWriterError::Write(const Brx& /*aBuffer*/)
{
    THROW(WriterError);
}

void MockWriterThrowsWriterError::WriteFlush()
{
    THROW(WriterError);
}


// SuiteFrameworkTabHandler

SuiteFrameworkTabHandler::SuiteFrameworkTabHandler()
    : SuiteUnitTest("SuiteFrameworkTabHandler")
{
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestDestroyNoMessages), "TestDestroyNoMessages");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestDestroyUnsentMessages), "TestDestroyUnsentMessages");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestSendWhileDisabled), "TestSendWhileDisabled");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestBlockingQueueEmpty), "TestBlockingQueueEmpty");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestDisableWhileBlockingSend), "TestDisableWhileBlockingSend");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestBlockingSendOneMessage), "TestBlockingSendOneMessage");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestBlockingSendMultipleMessages), "TestBlockingSendMultipleMessages");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestBlockingSendQueueFull), "TestBlockingSendQueueFull");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestBlockingSendNewMessageQueued), "TestBlockingSendNewMessageQueued");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTabHandler::TestWriterError), "TestWriterError");
}

void SuiteFrameworkTabHandler::Setup()
{
    iTestPipe = new TestPipeDynamic();
    iHelperBufferWriter = new HelperBufferWriter(kRecvBufBytes);
    iTabAllocator = new HelperDynamicTabAllocator();
    iSemRead = new TestHelperFrameworkSemaphore("READ", *iTestPipe);
    iSemWrite = new TestHelperFrameworkSemaphore("WRITE", *iTestPipe);
    iTimer = new TestHelperFrameworkTimer(*iTestPipe);
    iTabHandler = new FrameworkTabHandler(*iSemRead, *iSemWrite, *iTimer, kSendQueueSize, kSendTimeoutMs);
    iSemLpComplete = new Semaphore("FTHS", 0);

    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Clear READ")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Clear WRITE")));
    for (TUint i=0; i<kSendQueueSize; i++) {
        TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal WRITE")));
    }
}

void SuiteFrameworkTabHandler::TearDown()
{
    IFrameworkTabHandler& tabHandler = *iTabHandler;
    tabHandler.Disable();

    delete iSemLpComplete;
    delete iTabHandler;
    delete iTimer;
    delete iSemWrite;
    delete iSemRead;
    delete iTabAllocator;
    delete iHelperBufferWriter;
    delete iTestPipe;
}


void SuiteFrameworkTabHandler::TestDestroyNoMessages()
{
    // Completion of this without hanging shows an empty tab handler can be successfully deleted.
}

void SuiteFrameworkTabHandler::TestDestroyUnsentMessages()
{
    // Memory leak if tab is not destroyed.
    IFrameworkTabHandler& tabHandler = *iTabHandler;
    tabHandler.Enable();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Clear READ")));
    HelperTabMessage& msg = iTabAllocator->Allocate();
    msg.Set(0);
    tabHandler.Send(msg);
}

void SuiteFrameworkTabHandler::TestSendWhileDisabled()
{
    IFrameworkTabHandler& tabHandler = *iTabHandler;
    tabHandler.Disable();
    HelperTabMessage& msg = iTabAllocator->Allocate();
    msg.Set(0);
    tabHandler.Send(msg);
}

void SuiteFrameworkTabHandler::TestBlockingQueueEmpty()
{
    // Queue no msgs, but try a blocking send. Should block until timer fired.
    IFrameworkTabHandler& tabHandler = *iTabHandler;
    tabHandler.Enable();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Clear READ")));
    ThreadFunctor thread("LP thread", MakeFunctor(*this, &SuiteFrameworkTabHandler::LongPollThread));
    thread.Start();
    iSemRead->BlockUntilWait(); // LongPoll() should block on read Semaphore.
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait READ")));

    IFrameworkTimerHandler& timerHandler = *iTabHandler;
    timerHandler.Complete();    // Signal timeout.

    iSemLpComplete->Wait();

    TEST(iHelperBufferWriter->Buffer().Bytes() == 0);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal READ")));  // Caused by calling Complete().
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTabHandler::TestDisableWhileBlockingSend()
{
    // Queue no msgs, but try a blocking send. Should block until timer fired.
    IFrameworkTabHandler& tabHandler = *iTabHandler;
    tabHandler.Enable();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Clear READ")));
    ThreadFunctor thread("LP thread", MakeFunctor(*this, &SuiteFrameworkTabHandler::LongPollThread));
    thread.Start();
    iSemRead->BlockUntilWait(); // LongPoll() should block on read Semaphore.
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait READ")));

    tabHandler.Disable();   // Should terminate long poll.
    iSemLpComplete->Wait();
    TEST(iHelperBufferWriter->Buffer().Bytes() == 0);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal READ")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTabHandler::TestBlockingSendOneMessage()
{
    IFrameworkTabHandler& tabHandler = *iTabHandler;
    tabHandler.Enable();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Clear READ")));

    // Queue up msg.
    HelperTabMessage& msg = iTabAllocator->Allocate();
    msg.Set(0);
    tabHandler.Send(msg);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait WRITE")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal READ")));   // Msg was queued.

    ThreadFunctor thread("LP thread", MakeFunctor(*this, &SuiteFrameworkTabHandler::LongPollThread));
    thread.Start();

    iSemLpComplete->Wait();

    // Check message was written out.
    TEST(iHelperBufferWriter->Buffer() == Brn("[0]"));

    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait READ")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal WRITE")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTabHandler::TestBlockingSendMultipleMessages()
{
    IFrameworkTabHandler& tabHandler = *iTabHandler;
    tabHandler.Enable();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Clear READ")));

    // Queue up msg.
    HelperTabMessage& msg1 = iTabAllocator->Allocate();
    msg1.Set(0);
    tabHandler.Send(msg1);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait WRITE")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal READ")));

    HelperTabMessage& msg2 = iTabAllocator->Allocate();
    msg2.Set(1);
    tabHandler.Send(msg2);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait WRITE")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal READ")));

    ThreadFunctor thread("LP thread", MakeFunctor(*this, &SuiteFrameworkTabHandler::LongPollThread));
    thread.Start();

    iSemLpComplete->Wait();

    // Check message was written out.
    TEST(iHelperBufferWriter->Buffer() == Brn("[0,1]"));

    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait READ")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal WRITE")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait READ")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal WRITE")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTabHandler::TestBlockingSendQueueFull()
{
    IFrameworkTabHandler& tabHandler = *iTabHandler;
    tabHandler.Enable();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Clear READ")));

    for (TUint i=0; i<kSendQueueSize; i++) {
        HelperTabMessage& msg = iTabAllocator->Allocate();
        msg.Set(i);
        tabHandler.Send(msg);
        TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait WRITE")));
        TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal READ")));
    }

    ThreadFunctor thread("LP thread", MakeFunctor(*this, &SuiteFrameworkTabHandler::LongPollThread));
    thread.Start();

    iSemLpComplete->Wait();

    // Check message was written out.
    TEST(iHelperBufferWriter->Buffer() == Brn("[0,1,2,3,4,5,6,7,8,9]"));

    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait READ")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal WRITE")));
    for (TUint i=0; i<kSendQueueSize-1; i++) {
        TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait READ")));
        TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal WRITE")));
    }
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTabHandler::TestBlockingSendNewMessageQueued()
{
    // Try blocking send with no msgs ready, and then queue msg while blocking.
    IFrameworkTabHandler& tabHandler = *iTabHandler;
    tabHandler.Enable();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Clear READ")));

    // Start long polling without message queued.
    ThreadFunctor thread("LP thread", MakeFunctor(*this, &SuiteFrameworkTabHandler::LongPollThread));
    thread.Start();
    iSemRead->BlockUntilWait();

    // Now, send msg.
    HelperTabMessage& msg = iTabAllocator->Allocate();
    msg.Set(0);
    tabHandler.Send(msg);

    iSemLpComplete->Wait();

    // Check message was written out.
    TEST(iHelperBufferWriter->Buffer() == Brn("[0]"));

    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait READ")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait WRITE")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal READ")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal WRITE")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTabHandler::TestWriterError()
{
    IFrameworkTabHandler& tabHandler = *iTabHandler;
    tabHandler.Enable();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Clear READ")));

    // Allocate and send msg.
    HelperTabMessage& msg = iTabAllocator->Allocate();
    msg.Set(0);
    tabHandler.Send(msg);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait WRITE")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal READ")));

    // Now, attempt to long-poll tab handler with an IWriter that will throw a WriterError (to simulate a network error).
    MockWriterThrowsWriterError writer;
    TEST_THROWS(tabHandler.LongPoll(writer), WriterError);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Wait READ")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkSemaphore::Signal WRITE")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTabHandler::LongPollThread()
{
    IFrameworkTabHandler& tabHandler = *iTabHandler;
    tabHandler.LongPoll(*iHelperBufferWriter);
    iSemLpComplete->Signal();
}


// TestHelperResourceHandler

TBool TestHelperResourceHandler::Allocated()
{
    return true;
}

void TestHelperResourceHandler::SetResource(const Brx& /*aUri*/)
{
}

TUint TestHelperResourceHandler::Bytes()
{
    return 0;
}

void TestHelperResourceHandler::Write(IWriter& /*aWriter*/)
{
}

void TestHelperResourceHandler::Destroy()
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

ITab& TestHelperWebApp::Create(ITabHandler& /*aHandler*/, const std::vector<Bws<10>>& /*aLanguageList*/)
{
    //ITab* tab = new TestHelperTab();
    //iTabs.push_back(tab);
    //return *tab;
    ITab* tab = nullptr;
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
    Uri uri(aUri.AbsoluteUri());
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
        if (!match) {
            Log::Print("TestPipeDynamic::Expect ERROR: expected: ");
            Log::Print(aMessage);
            Log::Print(" got: ");
            Log::Print(*buf);
            Log::Print("\n");
        }
        delete buf;
        return match;
    }
    Log::Print("TestPipeDynamic::Expect ERROR: msg list empty; expected: ");
    Log::Print(aMessage);
    Log::Print("\n");
    return false;
}

TBool TestPipeDynamic::ExpectEmpty()
{
    AutoMutex a(iLock);
    const TUint msgs = iFifo.SlotsUsed();
    if (msgs > 0) {
        Log::Print("TestPipeDynamic::ExpectEmpty ERROR: %u msgs remaining:\n", msgs);
        for (TUint i=0; i<iFifo.SlotsUsed(); i++) {
            Bwh* buf = iFifo.Read();
            Log::Print("\t");
            Log::Print(*buf);
            Log::Print("\n");
            iFifo.Write(buf);
        }
        return false;
    }
    return true;
}


// TestHelperDestroyHandler

TestHelperDestroyHandler::TestHelperDestroyHandler(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

void TestHelperDestroyHandler::Destroy(TUint aId)
{
    Bws<100> buf("TestHelperDestroyHandler::Destroy ");
    Ascii::AppendDec(buf, aId);
    iTestPipe.Write(buf);
}


// TestHelperFrameworkSemaphore

TestHelperFrameworkSemaphore::TestHelperFrameworkSemaphore(const TChar* aId, ITestPipeWritable& aTestPipe)
    : iId(aId)
    , iTestPipe(aTestPipe)
    , iSem("THFS", 0)
    , iSemBlock("THFB", 0)
{
}

void TestHelperFrameworkSemaphore::BlockUntilWait()
{
    iSemBlock.Wait();
}

void TestHelperFrameworkSemaphore::Wait()
{
    Bws<50> buf("TestHelperFrameworkSemaphore::Wait ");
    buf.Append(iId);
    iTestPipe.Write(buf);
    iSemBlock.Signal();
    iSem.Wait();
}

TBool TestHelperFrameworkSemaphore::Clear()
{
    Bws<50> buf("TestHelperFrameworkSemaphore::Clear ");
    buf.Append(iId);
    iTestPipe.Write(buf);
    return iSem.Clear();
}

void TestHelperFrameworkSemaphore::Signal()
{
    Bws<50> buf("TestHelperFrameworkSemaphore::Signal ");
    buf.Append(iId);
    iTestPipe.Write(buf);
    iSem.Signal();
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


// TestHelperTabHandler

TestHelperTabHandler::TestHelperTabHandler(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

void TestHelperTabHandler::Send(ITabMessage& aMessage)
{
    Bws<100> buf("TabHandler::Send ");
    WriterBuffer writerBuffer(buf);
    aMessage.Send(writerBuffer);
    aMessage.Destroy();
    iTestPipe.Write(buf);
}

void TestHelperTabHandler::LongPoll(IWriter& /*aWriter*/)
{
    iTestPipe.Write(Brn("TabHandler::LongPoll"));
}

void TestHelperTabHandler::Enable()
{
    iTestPipe.Write(Brn("TabHandler::Enable"));
}

void TestHelperTabHandler::Disable()
{
    iTestPipe.Write(Brn("TabHandler::Disable"));
}


// TestHelperTab

TestHelperTab::TestHelperTab(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

void TestHelperTab::Receive(const OpenHome::Brx& aMessage)
{
    Bws<100> buf("Tab::Receive ");
    buf.Append(aMessage);
    iTestPipe.Write(buf);
}

void TestHelperTab::Destroy()
{
    iTestPipe.Write(Brn("Tab::Destroy"));
    delete this;
}


// TestHelperTabCreator

TestHelperTabCreator::TestHelperTabCreator(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

ITab& TestHelperTabCreator::Create(ITabHandler& /*aHandler*/, const std::vector<Bws<10>>& /*aLanguageList*/)
{
    TestHelperTab* tab = new TestHelperTab(iTestPipe);
    return *tab;
}


// TestHelperTabCreatorEmpty

ITab& TestHelperTabCreatorEmpty::Create(ITabHandler& /*aHandler*/, const std::vector<Bws<10>>& /*aLanguageList*/)
{
    THROW(TabAllocatorFull);
}


// TestHelperTabMessage

TestHelperTabMessage::TestHelperTabMessage(ITestPipeWritable& aTestPipe, const Brx& aMessage)
    : iTestPipe(aTestPipe)
    , iMsg(aMessage)
{
}

void TestHelperTabMessage::Send(IWriter& aWriter)
{
    Bws<50> buf("HelperTabMessage::Send ");
    buf.Append(iMsg);
    iTestPipe.Write(buf);
    aWriter.Write(iMsg);
}

void TestHelperTabMessage::Destroy()
{
    iTestPipe.Write(Brn("HelperTabMessage::Destroy"));
}


// SuiteFrameworkTab

SuiteFrameworkTab::SuiteFrameworkTab()
    : SuiteUnitTest("SuiteFrameworkTab")
{
    AddTest(MakeFunctor(*this, &SuiteFrameworkTab::TestCreateTab), "TestCreateTab");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTab::TestReuseTab), "TestReuseTab");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTab::TestCreateTabAllocatorEmpty), "TestCreateTabAllocatorEmpty");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTab::TestSessionId), "TestSessionId");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTab::TestReceive), "TestReceive");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTab::TestLongPoll), "TestLongPoll");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTab::TestSend), "TestSend");
    AddTest(MakeFunctor(*this, &SuiteFrameworkTab::TestTabTimeout), "TestTabTimeout");
    //AddTest(MakeFunctor(*this, &SuiteFrameworkTab::TestDeleteWhileTabAllocated), "TestDeleteWhileTabAllocated");
}

void SuiteFrameworkTab::Setup()
{
    iTestPipe = new TestPipeDynamic();
    iDestroyHandler = new TestHelperDestroyHandler(*iTestPipe);
    iFrameworkTimer = new TestHelperFrameworkTimer(*iTestPipe);
    iTabHandler = new TestHelperTabHandler(*iTestPipe);
    iTabCreator = new TestHelperTabCreator(*iTestPipe);

    iFrameworkTab = new FrameworkTab(0, *iFrameworkTimer, *iTabHandler, 5000);
}

void SuiteFrameworkTab::TearDown()
{
    delete iFrameworkTab;
    delete iTabCreator;
    delete iTabHandler;
    delete iFrameworkTimer;
    delete iDestroyHandler;
    delete iTestPipe;
}

void SuiteFrameworkTab::TestCreateTab()
{
    // Try create tab with invalid tab ID.
    TEST_THROWS(iFrameworkTab->CreateTab(FrameworkTab::kInvalidTabId, *iTabCreator, *iDestroyHandler, iLanguages), AssertionFailed);

    // Create tab with valid tab ID.
    iFrameworkTab->CreateTab(1, *iTabCreator, *iDestroyHandler, iLanguages);
    TEST(iTestPipe->Expect(Brn("TabHandler::Enable")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5000")));

    iFrameworkTab->Clear();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TabHandler::Disable")));
    TEST(iTestPipe->Expect(Brn("Tab::Destroy")));

    // Try do some operations on a Clear()ed tab.
    TEST_THROWS(iFrameworkTab->Receive(Brn("TestCreateTab Receive")), AssertionFailed);
    Bws<1> buf;
    WriterBuffer writerBuffer(buf);
    TEST_THROWS(iFrameworkTab->LongPoll(writerBuffer), AssertionFailed);
    iFrameworkTab->Clear(); // No effect.

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTab::TestReuseTab()
{
    iFrameworkTab->CreateTab(1, *iTabCreator, *iDestroyHandler, iLanguages);
    TEST(iTestPipe->Expect(Brn("TabHandler::Enable")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5000")));
    iFrameworkTab->Clear();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TabHandler::Disable")));
    TEST(iTestPipe->Expect(Brn("Tab::Destroy")));

    iFrameworkTab->CreateTab(2, *iTabCreator, *iDestroyHandler, iLanguages);
    TEST(iTestPipe->Expect(Brn("TabHandler::Enable")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5000")));
    iFrameworkTab->Clear();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TabHandler::Disable")));
    TEST(iTestPipe->Expect(Brn("Tab::Destroy")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTab::TestCreateTabAllocatorEmpty()
{
    TestHelperTabCreatorEmpty tabCreator;
    TEST_THROWS(iFrameworkTab->CreateTab(1, tabCreator, *iDestroyHandler, iLanguages), TabAllocatorFull);
    // TabHandler should be enabled/disabled as it must be active before attempting to pass it into tab at allocation time.
    TEST(iTestPipe->Expect(Brn("TabHandler::Enable")));
    TEST(iTestPipe->Expect(Brn("TabHandler::Disable")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTab::TestSessionId()
{
    TEST(iFrameworkTab->SessionId() == FrameworkTab::kInvalidTabId);
    iFrameworkTab->CreateTab(1, *iTabCreator, *iDestroyHandler, iLanguages);
    TEST(iTestPipe->Expect(Brn("TabHandler::Enable")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5000")));
    TEST(iFrameworkTab->SessionId() == 1);
    iFrameworkTab->Clear();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TabHandler::Disable")));
    TEST(iTestPipe->Expect(Brn("Tab::Destroy")));
    TEST(iFrameworkTab->SessionId() == FrameworkTab::kInvalidTabId);
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTab::TestReceive()
{
    iFrameworkTab->CreateTab(1, *iTabCreator, *iDestroyHandler, iLanguages);
    TEST(iTestPipe->Expect(Brn("TabHandler::Enable")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5000")));
    iFrameworkTab->Receive(Brn("TestReceive"));
    TEST(iTestPipe->Expect(Brn("Tab::Receive TestReceive")));
    iFrameworkTab->Clear();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TabHandler::Disable")));
    TEST(iTestPipe->Expect(Brn("Tab::Destroy")));
}

void SuiteFrameworkTab::TestLongPoll()
{
    Bws<1> buf;
    WriterBuffer writerBuffer(buf);
    iFrameworkTab->CreateTab(1, *iTabCreator, *iDestroyHandler, iLanguages);
    TEST(iTestPipe->Expect(Brn("TabHandler::Enable")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5000")));
    iFrameworkTab->LongPoll(writerBuffer);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TabHandler::LongPoll")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5000")));
    TEST(buf.Bytes() == 0);
    iFrameworkTab->Clear();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TabHandler::Disable")));
    TEST(iTestPipe->Expect(Brn("Tab::Destroy")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTab::TestSend()
{
    iFrameworkTab->CreateTab(1, *iTabCreator, *iDestroyHandler, iLanguages);
    TEST(iTestPipe->Expect(Brn("TabHandler::Enable")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5000")));

    TestHelperTabMessage msg(*iTestPipe, Brn("TestSend"));
    ITabHandler& tabHandler = *iFrameworkTab;
    tabHandler.Send(msg);
    TEST(iTestPipe->Expect(Brn("HelperTabMessage::Send TestSend")));
    TEST(iTestPipe->Expect(Brn("HelperTabMessage::Destroy")));
    TEST(iTestPipe->Expect(Brn("TabHandler::Send TestSend")));

    iFrameworkTab->Clear();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TabHandler::Disable")));
    TEST(iTestPipe->Expect(Brn("Tab::Destroy")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteFrameworkTab::TestTabTimeout()
{
    IFrameworkTimerHandler& timerHandler = *iFrameworkTab;
    iFrameworkTab->CreateTab(1, *iTabCreator, *iDestroyHandler, iLanguages);
    TEST(iTestPipe->Expect(Brn("TabHandler::Enable")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5000")));
    // Simulate tab timeout.
    timerHandler.Complete();

    // Check destroy handler has been called (and then call Clear() from here).
    // In production code, the destroy handler MUST call Clear() on the tab.
    TEST(iTestPipe->Expect(Brn("TestHelperDestroyHandler::Destroy 1")));
    iFrameworkTab->Clear();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TabHandler::Disable")));
    TEST(iTestPipe->Expect(Brn("Tab::Destroy")));
    // Check tab cleared.
    TEST(iFrameworkTab->SessionId() == FrameworkTab::kInvalidTabId);


    Bws<1> buf;
    WriterBuffer writerBuffer(buf);
    iFrameworkTab->CreateTab(2, *iTabCreator, *iDestroyHandler, iLanguages);
    TEST(iTestPipe->Expect(Brn("TabHandler::Enable")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5000")));
    iFrameworkTab->LongPoll(writerBuffer);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TabHandler::LongPoll")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Start 5000")));
    // Simulate tab timeout.
    timerHandler.Complete();
    TEST(iTestPipe->Expect(Brn("TestHelperDestroyHandler::Destroy 2")));
    iFrameworkTab->Clear();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTimer::Cancel")));
    TEST(iTestPipe->Expect(Brn("TabHandler::Disable")));
    TEST(iTestPipe->Expect(Brn("Tab::Destroy")));
}

void SuiteFrameworkTab::TestDeleteWhileTabAllocated()
{
    // Set a tab, then don't bother calling RemoveRef() or Destroy().
    // i.e., let TearDown() call delete on the FrameworkTab while a tab is still allocated.
    iFrameworkTab->CreateTab(1, *iTabCreator, *iDestroyHandler, iLanguages);
    TEST_THROWS(delete iFrameworkTab, AssertionFailed);
}


// TestHelperFrameworkTab

TestHelperFrameworkTab::TestHelperFrameworkTab(ITestPipeWritable& aTestPipe, TUint aId)
    : iTestPipe(aTestPipe)
    , iId(aId)
    , iSessionId(IFrameworkTab::kInvalidTabId)
    , iDestroyHandler(nullptr)
{
}

void TestHelperFrameworkTab::CallDestroyHandler()
{
    // Used to simulate a polling timeout.
    ASSERT(iDestroyHandler != nullptr);
    iDestroyHandler->Destroy(iSessionId);
}

TUint TestHelperFrameworkTab::SessionId() const
{
    Bws<50> buf("TestHelperFrameworkTab::SessionId ");
    Ascii::AppendDec(buf, iId);
    buf.Append(" ");
    Ascii::AppendDec(buf, iSessionId);
    iTestPipe.Write(buf);
    return iSessionId;
}

void TestHelperFrameworkTab::CreateTab(TUint aSessionId, ITabCreator& /*aTabCreator*/, ITabDestroyHandler& aDestroyHandler, const std::vector<char*>& /*aLanguages*/)
{
    Bws<50> buf("TestHelperFrameworkTab::CreateTab ");
    Ascii::AppendDec(buf, iId);
    buf.Append(" ");
    Ascii::AppendDec(buf, aSessionId);
    iTestPipe.Write(buf);
    iSessionId = aSessionId;
    iDestroyHandler = &aDestroyHandler;
}

void TestHelperFrameworkTab::Clear()
{
    Bws<50> buf("TestHelperFrameworkTab::Clear ");
    Ascii::AppendDec(buf, iId);
    iTestPipe.Write(buf);
    iSessionId = IFrameworkTab::kInvalidTabId;
    iDestroyHandler = nullptr;
}

void TestHelperFrameworkTab::Receive(const Brx& aMessage)
{
    Bws<50> buf("TestHelperFrameworkTab::Receive ");
    Ascii::AppendDec(buf, iId);
    buf.Append(" ");
    buf.Append(aMessage);
    iTestPipe.Write(buf);
}

void TestHelperFrameworkTab::LongPoll(IWriter& /*aWriter*/)
{
    Bws<50> buf("TestHelperFrameworkTab::LongPoll ");
    Ascii::AppendDec(buf, iId);
    iTestPipe.Write(buf);
}


// TestHelperFrameworkTabFull

TUint TestHelperFrameworkTabFull::SessionId() const
{
    return IFrameworkTab::kInvalidTabId;
}

void TestHelperFrameworkTabFull::CreateTab(TUint /*aSessionId*/, ITabCreator& /*aTabCreator*/, ITabDestroyHandler& /*aDestroyHandler*/, const std::vector<char*>& /*aLanguages*/)
{
    THROW(TabAllocatorFull);
}

void TestHelperFrameworkTabFull::Clear()
{
}

void TestHelperFrameworkTabFull::Receive(const Brx& /*aMessage*/)
{
    ASSERTS();
}

void TestHelperFrameworkTabFull::LongPoll(IWriter& /*aWriter*/)
{
    ASSERTS();
}


// SuiteTabManager

SuiteTabManager::SuiteTabManager()
    : SuiteUnitTest("SuiteTabManager")
{
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestCreateTab), "TestCreateTab");
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestDisableNoTabsAllocated), "TestDisableNoTabsAllocated");
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestDisable), "TestDisable");
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestTabTimeout), "TestTabTimeout");
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestTabIdsIncrement), "TestTabIdsIncrement");
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestCreateTabManagerFull), "TestCreateTabManagerFull");
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestCreateTabAllocatorEmpty), "TestCreateTabAllocatorEmpty");
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestInvalidTabId), "TestInvalidTabId");
    AddTest(MakeFunctor(*this, &SuiteTabManager::TestDeleteWhileTabsAllocated), "TestDeleteWhileTabsAllocated");
}

void SuiteTabManager::Setup()
{
    iTestPipe = new TestPipeDynamic();
    iWebApp = new TestHelperWebApp();
    for (TUint i=0; i<4; i++) {
        iTabs.push_back(new TestHelperFrameworkTab(*iTestPipe, i));
    }

    // Copy from std::vector of TestHelperFrameworkTab to std::vector of IFrameworkTab for TabManager.
    std::vector<IFrameworkTab*> tabs;
    for (TUint i=0; i<4; i++) {
        tabs.push_back(iTabs[i]);
    }
    iTabManager = new TabManager(tabs);    // Takes ownership of tabs.
}

void SuiteTabManager::TearDown()
{
    delete iTabManager;
    iTabs.clear();
    delete iWebApp;
    delete iTestPipe;
}

void SuiteTabManager::TestCreateTab()
{
    std::vector<char*> languages;
    const TUint id = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id == 1);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 0 1")));

    // Now, perform available actions on the tab.
    Bws<1> buf;
    WriterBuffer writerBuffer(buf);
    iTabManager->LongPoll(id, writerBuffer);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::LongPoll 0")));

    iTabManager->Receive(id, Brn("TestCreateTab"));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Receive 0 TestCreateTab")));

    iTabManager->Destroy(id);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 0")));

    TEST(iTestPipe->ExpectEmpty());
    iTabManager->Disable();
}

void SuiteTabManager::TestDisableNoTabsAllocated()
{
    iTabManager->Disable();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteTabManager::TestDisable()
{
    // Allocate a tab, then call disable while active.
    std::vector<char*> languages;
    (void)iTabManager->CreateTab(*iWebApp, languages);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 0 1")));
    iTabManager->Disable();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteTabManager::TestTabTimeout()
{
    std::vector<char*> languages;
    const TUint id1 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id1 == 1);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 0 1")));

    TEST(iTestPipe->ExpectEmpty());
    // Simulate tab timeout (normally triggered via timer).
    // Should notify TabManager.
    iTabs[0]->CallDestroyHandler();
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 0")));

    // Now, try allocate next tab. Firstc tab should be re-allocated.
    const TUint id2 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id2 == 2);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 0 2")));
    TEST(iTabs[0]->SessionId() == id2);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 2")));

    TEST(iTestPipe->ExpectEmpty());

    iTabManager->Disable();
}

void SuiteTabManager::TestTabIdsIncrement()
{
    // Allocate a few tabs.
    std::vector<char*> languages;
    const TUint id1 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id1 == 1);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 0 1")));
    TUint id2 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id2 == 2);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 1 2")));
    TUint id3 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id3 == 3);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 2 3")));

    // Destroy last tab and check numbering resumes from that point.
    iTabManager->Destroy(id3);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 3")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 2")));
    id3 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id3 == 4);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 2 4")));

    // Destroy tab from middle and check numbering resumes from that point, and skips over next allocated tab.
    iTabManager->Destroy(id2);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 1")));
    id2 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id2 == 5);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 1 5")));

    const TUint id4 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(id4 == 6);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 5")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 4")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 3 6")));

    // Destroy all tabs to clean up.
    iTabManager->Destroy(id1);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 0")));
    iTabManager->Destroy(id2);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 5")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 1")));
    iTabManager->Destroy(id3);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 4")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 2")));
    iTabManager->Destroy(id4);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 6")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 3")));

    TEST(iTestPipe->ExpectEmpty());

    iTabManager->Disable();
}

void SuiteTabManager::TestCreateTabManagerFull()
{
    // Allocate all tabs.
    std::vector<char*> languages;
    const TUint id1 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 0 1")));
    const TUint id2 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 1 2")));
    const TUint id3 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 2 3")));
    const TUint id4 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 3")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 3 4")));

    // Then try allocate another.
    TEST_THROWS(iTabManager->CreateTab(*iWebApp, languages), TabManagerFull);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 3")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 4")));

    // Destroy all tabs.
    iTabManager->Destroy(id1);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 0")));
    iTabManager->Destroy(id2);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 1")));
    iTabManager->Destroy(id3);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 3")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 2")));
    iTabManager->Destroy(id4);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 4")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 3")));

    TEST(iTestPipe->ExpectEmpty());

    iTabManager->Disable();
}

void SuiteTabManager::TestCreateTabAllocatorEmpty()
{
    // Create a new TabManager with an IFrameworkTab that always reports TabAllocatorFull.
    // Ignoring iTabManager for this test.
    std::vector<IFrameworkTab*> tabs;
    tabs.push_back(new TestHelperFrameworkTabFull());
    TabManager tabManager(tabs);
    std::vector<char*> languages;

    TEST_THROWS(tabManager.CreateTab(*iWebApp, languages), TabAllocatorFull);
    tabManager.Disable();

    iTabManager->Disable();
}

void SuiteTabManager::TestInvalidTabId()
{
    std::vector<char*> languages;

    // Try perform actions when no tabs allocated.
    Bws<1> buf;
    WriterBuffer writerBuffer(buf);
    TEST_THROWS(iTabManager->LongPoll(1, writerBuffer), InvalidTabId);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));
    TEST_THROWS(iTabManager->Receive(1, Brn("TestInvalidTabId")), InvalidTabId);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));
    TEST_THROWS(iTabManager->Destroy(1), InvalidTabId);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));

    // Allocate a couple of tabs, then try access an unallocated session ID.
    (void)iTabManager->CreateTab(*iWebApp, languages);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 0 1")));
    const TUint id2 = iTabManager->CreateTab(*iWebApp, languages);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 1 2")));
    TEST_THROWS(iTabManager->LongPoll(3, writerBuffer), InvalidTabId);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));
    TEST_THROWS(iTabManager->Receive(3, Brn("TestInvalidTabId")), InvalidTabId);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));
    TEST_THROWS(iTabManager->Destroy(3), InvalidTabId);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));

    // Destroy a tab, and then try reusing that session ID (mimicking a web browser that was slow to respond to a long poll).
    iTabManager->Destroy(id2);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 2")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::Clear 1")));
    TEST_THROWS(iTabManager->LongPoll(id2, writerBuffer), InvalidTabId);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));
    TEST_THROWS(iTabManager->Receive(id2, Brn("TestInvalidTabId")), InvalidTabId);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));
    TEST_THROWS(iTabManager->Destroy(id2), InvalidTabId);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 1")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 1 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 2 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 3 0")));
    TEST(iTestPipe->ExpectEmpty());
    iTabManager->Disable();
}

void SuiteTabManager::TestDeleteWhileTabsAllocated()
{
    // Test case where client is holding a tab open, but the WebAppFramework is being destroyed.
    // Allocate tab and don't do any cleanup here; allow TearDown() to delete TabManager and it should quietly cleanup allocated tabs.
    std::vector<char*> languages;
    (void)iTabManager->CreateTab(*iWebApp, languages);
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::SessionId 0 0")));
    TEST(iTestPipe->Expect(Brn("TestHelperFrameworkTab::CreateTab 0 1")));
    TEST(iTestPipe->ExpectEmpty());
    iTabManager->Disable();
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
}



void TestWebAppFramework(Environment& aEnv)
{
    Runner runner("WebApp Framework tests\n");
    runner.Add(new SuiteFrameworkTabHandler());
    runner.Add(new SuiteFrameworkTab());
    runner.Add(new SuiteTabManager());
    runner.Add(new SuiteWebAppFramework(aEnv));
    runner.Run();
}
