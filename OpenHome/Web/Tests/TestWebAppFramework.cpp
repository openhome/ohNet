#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>

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

//class SuiteTabTimeoutDetector : public OpenHome::TestFramework::SuiteUnitTest
//{
//public:
//    SuiteTabTimeoutDetector();
//private: // from SuiteUnitTest
//    void Setup();
//    void TearDown();
//};
//
//class SuiteFrameworkTab : public OpenHome::TestFramework::SuiteUnitTest
//{
//public:
//    SuiteFrameworkTab();
//private: // from SuiteUnitTest
//    void Setup();
//    void TearDown();
//};
//
//class SuiteTabManager : public OpenHome::TestFramework::SuiteUnitTest
//{
//public:
//    SuiteTabManager();
//private: // from SuiteUnitTest
//    void Setup();
//    void TearDown();
//};

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



void TestWebAppFramework()
{
    Runner runner("HTTP Framework tests\n");
    runner.Add(new SuiteFrameworkTabHandler());
    runner.Run();
}
