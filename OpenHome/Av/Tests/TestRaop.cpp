#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Av/Raop/Raop.h>
#include <OpenHome/Av/Raop/ProtocolRaop.h>
#include <OpenHome/Private/Ascii.h>

namespace OpenHome {
namespace Av {

class ITestPipeWritable
{
public:
    virtual void Write(const Brx& aMessage) = 0;
    virtual void Write(const Brx& aMessage, TInt aValue) = 0;
    virtual ~ITestPipeWritable() {}
};

class ITestPipeReadable
{
public:
    virtual TBool Expect(const Brx& aMessage) = 0;
    virtual TBool Expect(const Brx& aMessage, TInt aValue) = 0;
    virtual TBool ExpectEmpty() = 0;
    virtual ~ITestPipeReadable() {}
};

class TestPipeDynamic : public ITestPipeWritable, public ITestPipeReadable
{
public:
    static const TUint kMaxMsgBytes = 256;
private:
    const TUint kIntMaxAsciiBytes = 11;
public:
    TestPipeDynamic(TUint aSlots);
    ~TestPipeDynamic();
    void Print();
public: // from ITestPipeWritable
    void Write(const Brx& aMessage) override;
    void Write(const Brx& aMessage, TInt aValue) override;
public: // from ITestPipeReadable
    TBool Expect(const Brx& aMessage) override;
    TBool Expect(const Brx& aMessage, TInt aValue) override;
    TBool ExpectEmpty() override;
private:
    FifoLiteDynamic<Bwh*> iFifo;
    Mutex iLock;
};

class TestHelperVolumeReporter : public IVolumeReporter, private INonCopyable
{
public:
    static const Brn kAddVolumeObserverPrefix;
public:
    TestHelperVolumeReporter(ITestPipeWritable& aTestPipe);
public: // from IVolumeReporter
    void AddVolumeObserver(IVolumeObserver& aObserver) override;
private:
    ITestPipeWritable& iTestPipe;
};

class TestHelperVolumeOffset : public IVolumeSourceOffset, private INonCopyable
{
public:
    static const Brn kSetVolumeOffsetPrefix;
public:
    TestHelperVolumeOffset(ITestPipeWritable& aTestPipe);
public: // from IVolumeSourceOffset
    void SetVolumeOffset(TInt aOffset) override;
private:
    ITestPipeWritable& iTestPipe;
};

class SuiteRaopVolume : public OpenHome::TestFramework::SuiteUnitTest
{
private:
    static const TUint kMaxTestPipeMessages = 10;
public:
    SuiteRaopVolume();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void TestEnabled();
    void TestRaopMinUserMin();
    void TestRaopMaxUserMax();
    void TestSetRaopVolume();
    void TestSetUserVolume();
    void TestMute();
    void TestVolAboveMax();
    void TestVolBelowMin();
    void TestVolBelowMute();
private:
    TestPipeDynamic* iTestPipe;
    TestHelperVolumeReporter* iHelperVolReporter;
    TestHelperVolumeOffset* iHelperVolOffset;
    RaopVolumeHandler* iRaopVolumeHandler;
};

class MockResendRequester : public IResendRangeRequester, private INonCopyable
{
public:
    MockResendRequester(ITestPipeWritable& aTestPipe);
private: // from IResendRangeRequester
    void RequestResendSequences(const std::vector<const IResendRange*> aRanges) override;
private:
    ITestPipeWritable& iTestPipe;
};

class MockAudioSupply : public IAudioSupply, private INonCopyable
{
public:
    MockAudioSupply(ITestPipeWritable& aTestPipe);
private: // from IAudioSupply
    void OutputAudio(const Brx& aAudio) override;
private:
    ITestPipeWritable& iTestPipe;
};

class MockRepairerTimer : public IRepairerTimer, private INonCopyable
{
public:
    MockRepairerTimer(ITestPipeWritable& aTestPipe);
    void Fire();
private: // from IRepairerTimer
    void Start(Functor aFunctor, TUint aFireInMs) override;
    void Cancel() override;
private:
    ITestPipeWritable& iTestPipe;
    Functor iFunctor;
};

class MockRepairableAllocator;

class MockRepairable : public IRepairable
{
public:
    MockRepairable(ITestPipeWritable& aTestPipe, MockRepairableAllocator& aAllocator, TUint aMaxBytes);
    void Set(TUint aFrame, TBool aResend, const Brx& aData);
public: // from IRepairable
    TUint Frame() const override;
    TBool Resend() const override;
    const Brx& Data() const override;
    void Destroy() override;
private:
    ITestPipeWritable& iTestPipe;
    MockRepairableAllocator& iAllocator;
    TUint iFrame;
    TBool iResend;
    Bwh iData;
};

class MockRepairableAllocator
{
public:
    MockRepairableAllocator(ITestPipeWritable& aTestPipe, TUint aMaxRepairable, TUint aMaxBytes);
    ~MockRepairableAllocator();
    IRepairable* Allocate(TUint aFrame, TBool aResend, const Brx& aData);
    void Deallocate(MockRepairable* aRepairable);
private:
    FifoLiteDynamic<MockRepairable*> iFifo;
};

class SuiteRaopResend : public TestFramework::SuiteUnitTest, private INonCopyable
{
private:
    static const TUint kMaxFrames = 5;
    static const TUint kMaxFrameBytes = 2;  // Only expect to store ASCII chars 0..99.
    static const TUint kMaxTestPipeMessages = 50;
public:
    SuiteRaopResend(Environment& aEnv);
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void TestNoDropouts();
    void TestResendOnePacket();
    void TestResendMultiplePackets();
    void TestResendMulitpleRanges();
    void TestResendBeyondMultipleRangeLimit();
    void TestMultipleResendRecover();
    void TestResendRequest();
    void TestResendPacketBufferOverflowFirst();
    void TestResendPacketBufferOverflowMiddle();
    void TestResendPacketBufferOverflowLast();
    void TestResendBufferOverflowRecover();
    void TestResendPacketsOutOfOrder();
    void TestResendPacketsAlreadySeen();
    void TestStreamReset();   // Receiving a packet already seen but is not a resend.
    void TestStreamResetResendPending();
    void TestDropAudio();
private:
    Environment& iEnv;
    TestPipeDynamic* iTestPipe;
    MockResendRequester* iResendRequester;
    MockAudioSupply* iAudioSupply;
    MockRepairerTimer* iTimer;
    MockRepairableAllocator* iAllocator;
    Repairer<kMaxFrames>* iRepairer;
};

} // namespace Av
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;


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

void TestPipeDynamic::Write(const Brx& aMessage, TInt aValue)
{
    AutoMutex a(iLock);
    Bwh* buf = new Bwh(aMessage.Bytes() + kIntMaxAsciiBytes);
    buf->Replace(aMessage);
    Ascii::AppendDec(*buf, aValue);
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

TBool TestPipeDynamic::Expect(const Brx& aMessage, TInt aValue)
{
    Bwh msg(aMessage.Bytes() + kIntMaxAsciiBytes);
    msg.Replace(aMessage);
    Ascii::AppendDec(msg, aValue);
    return Expect(msg);
}

TBool TestPipeDynamic::ExpectEmpty()
{
    AutoMutex a(iLock);
    return (iFifo.SlotsUsed() == 0);
}


// TestHelperVolumeReporter

const Brn TestHelperVolumeReporter::kAddVolumeObserverPrefix("TestHelperVolumeReporter::AddVolumeObserver");

TestHelperVolumeReporter::TestHelperVolumeReporter(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

void TestHelperVolumeReporter::AddVolumeObserver(IVolumeObserver& /*aObserver*/)
{
    iTestPipe.Write(kAddVolumeObserverPrefix);
}


// TestHelperVolumeOffset

const Brn TestHelperVolumeOffset::kSetVolumeOffsetPrefix("TestHelperVolumeOffset::SetVolumeOffset ");

TestHelperVolumeOffset::TestHelperVolumeOffset(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

void TestHelperVolumeOffset::SetVolumeOffset(TInt aOffset)
{
    iTestPipe.Write(kSetVolumeOffsetPrefix, aOffset);
}


// SuiteRaopVolume

SuiteRaopVolume::SuiteRaopVolume()
    : SuiteUnitTest("SuiteRaopVolume")
{
    AddTest(MakeFunctor(*this, &SuiteRaopVolume::TestEnabled), "TestEnabled");
    AddTest(MakeFunctor(*this, &SuiteRaopVolume::TestRaopMinUserMin), "TestRaopMinUserMin");
    AddTest(MakeFunctor(*this, &SuiteRaopVolume::TestRaopMaxUserMax), "TestRaopMaxUserMax");
    AddTest(MakeFunctor(*this, &SuiteRaopVolume::TestSetRaopVolume), "TestSetRaopVolume");
    AddTest(MakeFunctor(*this, &SuiteRaopVolume::TestSetUserVolume), "TestSetUserVolume");
    AddTest(MakeFunctor(*this, &SuiteRaopVolume::TestMute), "TestMute");
    AddTest(MakeFunctor(*this, &SuiteRaopVolume::TestVolAboveMax), "TestVolAboveMax");
    AddTest(MakeFunctor(*this, &SuiteRaopVolume::TestVolBelowMin), "TestVolBelowMin");
    AddTest(MakeFunctor(*this, &SuiteRaopVolume::TestVolBelowMute), "TestVolBelowMute");
}

void SuiteRaopVolume::Setup()
{
    iTestPipe = new TestPipeDynamic(kMaxTestPipeMessages);
    iHelperVolReporter = new TestHelperVolumeReporter(*iTestPipe);
    iHelperVolOffset = new TestHelperVolumeOffset(*iTestPipe);
    iRaopVolumeHandler = new RaopVolumeHandler(*iHelperVolReporter, *iHelperVolOffset);

    TEST(iTestPipe->Expect(TestHelperVolumeReporter::kAddVolumeObserverPrefix));

    iRaopVolumeHandler->SetVolumeEnabled(true);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopVolume::TearDown()
{
    delete iRaopVolumeHandler;
    delete iHelperVolOffset;
    delete iHelperVolReporter;
    delete iTestPipe;
}

void SuiteRaopVolume::TestEnabled()
{
    iRaopVolumeHandler->SetRaopVolume(-15);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->VolumeChanged(100);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -50));
    TEST(iTestPipe->ExpectEmpty());

    iRaopVolumeHandler->SetVolumeEnabled(false);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->SetRaopVolume(RaopVolumeHandler::kVolMin);
    iRaopVolumeHandler->VolumeChanged(75);
    TEST(iTestPipe->ExpectEmpty());

    iRaopVolumeHandler->SetVolumeEnabled(true);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -75));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopVolume::TestRaopMinUserMin()
{
    iRaopVolumeHandler->VolumeChanged(0);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->SetRaopVolume(RaopVolumeHandler::kVolMin);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopVolume::TestRaopMaxUserMax()
{
    iRaopVolumeHandler->VolumeChanged(100);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -100));

    iRaopVolumeHandler->SetRaopVolume(RaopVolumeHandler::kVolMax);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopVolume::TestSetRaopVolume()
{
    // User vol at 0.
    iRaopVolumeHandler->SetRaopVolume(-30);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->SetRaopVolume(-15);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->SetRaopVolume(0);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));

    // User vol at 25.
    iRaopVolumeHandler->VolumeChanged(25);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->SetRaopVolume(-30);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -25));
    iRaopVolumeHandler->SetRaopVolume(-15);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -13));
    iRaopVolumeHandler->SetRaopVolume(0);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));

    // User vol at 50.
    iRaopVolumeHandler->VolumeChanged(50);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->SetRaopVolume(-30);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -50));
    iRaopVolumeHandler->SetRaopVolume(-15);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -25));
    iRaopVolumeHandler->SetRaopVolume(0);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));

    // User vol at 75.
    iRaopVolumeHandler->VolumeChanged(75);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->SetRaopVolume(-30);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -75));
    iRaopVolumeHandler->SetRaopVolume(-15);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -38));
    iRaopVolumeHandler->SetRaopVolume(0);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));

    // User vol at 100.
    iRaopVolumeHandler->VolumeChanged(100);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->SetRaopVolume(-30);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -100));
    iRaopVolumeHandler->SetRaopVolume(-15);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -50));
    iRaopVolumeHandler->SetRaopVolume(0);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopVolume::TestSetUserVolume()
{
    // Raop vol at min (-30).
    iRaopVolumeHandler->VolumeChanged(0);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->VolumeChanged(25);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -25));
    iRaopVolumeHandler->VolumeChanged(50);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -50));
    iRaopVolumeHandler->VolumeChanged(75);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -75));
    iRaopVolumeHandler->VolumeChanged(100);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -100));

    // Raop vol at -15.
    iRaopVolumeHandler->SetRaopVolume(-15);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -50));
    iRaopVolumeHandler->VolumeChanged(0);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->VolumeChanged(25);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -13));
    iRaopVolumeHandler->VolumeChanged(50);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -25));
    iRaopVolumeHandler->VolumeChanged(75);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -38));
    iRaopVolumeHandler->VolumeChanged(100);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -50));

    // Raop vol at max (0).
    iRaopVolumeHandler->SetRaopVolume(0);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->VolumeChanged(0);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->VolumeChanged(25);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->VolumeChanged(50);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->VolumeChanged(75);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));
    iRaopVolumeHandler->VolumeChanged(100);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, 0));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopVolume::TestMute()
{
    Bws<256> expected;
    // Set user volume to non-zero value.
    iRaopVolumeHandler->VolumeChanged(50);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -50));

    // Set RAOP volume to non-zero value.
    iRaopVolumeHandler->SetRaopVolume(-15);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -25));

    // Set RAOP to be muted.
    iRaopVolumeHandler->SetRaopVolume(RaopVolumeHandler::kMute);
    TEST(iTestPipe->Expect(TestHelperVolumeOffset::kSetVolumeOffsetPrefix, -50));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopVolume::TestVolAboveMax()
{
    TEST_THROWS(iRaopVolumeHandler->SetRaopVolume(RaopVolumeHandler::kVolMax+1), RaopVolumeInvalid);
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopVolume::TestVolBelowMin()
{
    TEST_THROWS(iRaopVolumeHandler->SetRaopVolume(RaopVolumeHandler::kVolMin-1), RaopVolumeInvalid);
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopVolume::TestVolBelowMute()
{
    TEST_THROWS(iRaopVolumeHandler->SetRaopVolume(RaopVolumeHandler::kMute-1), RaopVolumeInvalid);
    TEST(iTestPipe->ExpectEmpty());
}


// MockResendRequester

MockResendRequester::MockResendRequester(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

void MockResendRequester::RequestResendSequences(const std::vector<const IResendRange*> aRanges)
{
    Bws<50> buf("MRR::ReqestResend");
    for (auto range : aRanges) {
        buf.Append(" ");
        Ascii::AppendDec(buf, range->Start());
        buf.Append("->");
        Ascii::AppendDec(buf, range->End());
    }
    iTestPipe.Write(buf);
}


// MockAudioSupply

MockAudioSupply::MockAudioSupply(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

void MockAudioSupply::OutputAudio(const Brx& aAudio)
{
    ASSERT(aAudio.Bytes() > 0);
    Bws<50> buf("MAS::OutputAudio ");
    Ascii::AppendDec(buf, aAudio.Bytes());
    buf.Append(" ");
    buf.Append(aAudio);
    iTestPipe.Write(buf);
}


// MockRepairerTimer

MockRepairerTimer::MockRepairerTimer(ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

void MockRepairerTimer::Fire()
{
    // Must clear iFunctor BEFORE calling it, as callee may call ::Start() on timer.
    // (So, if iFunctor was cleared after call, it would prevent any future calls.)
    Functor functor = iFunctor;
    iFunctor = Functor();
    functor();
}

void MockRepairerTimer::Start(Functor aFunctor, TUint /*aFireInMs*/)
{
    iFunctor = aFunctor;
    //Bws<50> buf("MRT::Start ");
    //Ascii::AppendDec(buf, aFireInMs);
    //iTestPipe.Write(buf);

    // Retry timer duration is randomised when repairs start, so can't test it.
    iTestPipe.Write(Brn("MRT::Start"));
}

void MockRepairerTimer::Cancel()
{
    iTestPipe.Write(Brn("MRT::Cancel"));
    iFunctor = Functor();
}


// MockRepairable

MockRepairable::MockRepairable(ITestPipeWritable& aTestPipe, MockRepairableAllocator& aAllocator, TUint aMaxBytes)
    : iTestPipe(aTestPipe)
    , iAllocator(aAllocator)
    , iData(aMaxBytes)
{
}

void MockRepairable::Set(TUint aFrame, TBool aResend, const Brx& aData)
{
    iFrame = aFrame;
    iResend = aResend;
    iData.Replace(aData);
}

TUint MockRepairable::Frame() const
{
    return iFrame;
}

TBool MockRepairable::Resend() const
{
    return iResend;
}

const Brx& MockRepairable::Data() const
{
    return iData;
}

void MockRepairable::Destroy()
{
    Bws<50> buf("MR::Destroy ");
    Ascii::AppendDec(buf, iFrame);
    iTestPipe.Write(buf);
    iAllocator.Deallocate(this);
}


// MockRepairableAllocator

MockRepairableAllocator::MockRepairableAllocator(ITestPipeWritable& aTestPipe, TUint aMaxRepairable, TUint aMaxBytes)
    : iFifo(aMaxRepairable)
{
    for (TUint i=0; i<aMaxRepairable; i++) {
        iFifo.Write(new MockRepairable(aTestPipe, *this, aMaxBytes));
    }
}

MockRepairableAllocator::~MockRepairableAllocator()
{
    ASSERT(iFifo.SlotsFree() == 0); // All repairables must have been returned.
    while (iFifo.SlotsUsed() > 0) {
        auto repairable = iFifo.Read();
        delete repairable;
    }
}

IRepairable* MockRepairableAllocator::Allocate(TUint aFrame, TBool aResend, const Brx& aData)
{
    auto repairable = iFifo.Read();
    repairable->Set(aFrame, aResend, aData);
    return repairable;
}

void MockRepairableAllocator::Deallocate(MockRepairable* aRepairable)
{
    aRepairable->Set(0, false, Brx::Empty());
    iFifo.Write(aRepairable);
}


// SuiteRaopResend


SuiteRaopResend::SuiteRaopResend(Environment& aEnv)
    : SuiteUnitTest("SuiteRaopResend")
    , iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestNoDropouts), "TestNoDropouts");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestResendOnePacket), "TestResendOnePacket");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestResendMultiplePackets), "TestResendMultiplePackets");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestResendMulitpleRanges), "TestResendMulitpleRanges");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestResendBeyondMultipleRangeLimit), "TestResendBeyondMultipleRangeLimit");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestMultipleResendRecover), "TestMultipleResendRecover");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestResendRequest), "TestResendRequest");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestResendPacketBufferOverflowFirst), "TestResendPacketBufferOverflowFirst");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestResendPacketBufferOverflowMiddle), "TestResendPacketBufferOverflowMiddle");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestResendPacketBufferOverflowLast), "TestResendPacketBufferOverflowLast");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestResendBufferOverflowRecover), "TestResendBufferOverflowRecover");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestResendPacketsOutOfOrder), "TestResendPacketsOutOfOrder");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestResendPacketsAlreadySeen), "TestResendPacketsAlreadySeen");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestStreamReset), "TestStreamReset");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestStreamResetResendPending), "TestStreamResetResendPending");
    AddTest(MakeFunctor(*this, &SuiteRaopResend::TestDropAudio), "TestDropAudio");
}

void SuiteRaopResend::Setup()
{
    iTestPipe = new TestPipeDynamic(kMaxTestPipeMessages);
    iResendRequester = new MockResendRequester(*iTestPipe);
    iAudioSupply = new MockAudioSupply(*iTestPipe);
    iTimer = new MockRepairerTimer(*iTestPipe);
    // Repair buffer stashes first discontinuity frame in a pointer, then proceeds to fill a buffer of kMaxFrameBytes.
    // So, need kMaxFrames+2 to overflow repair buffer.
    iAllocator = new MockRepairableAllocator(*iTestPipe, kMaxFrames+2, kMaxFrameBytes);
    iRepairer = new Repairer<kMaxFrames>(iEnv, *iResendRequester, *iAudioSupply, *iTimer);
}

void SuiteRaopResend::TearDown()
{
    delete iRepairer;
    delete iAllocator;
    delete iTimer;
    delete iAudioSupply;
    delete iResendRequester;
    delete iTestPipe;
}

void SuiteRaopResend::TestNoDropouts()
{
    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));
    iRepairer->OutputAudio(*iAllocator->Allocate(1, false, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
}

void SuiteRaopResend::TestResendOnePacket()
{
    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    // Expect retry logic to kick in.
    TEST(iTestPipe->Expect(Brn("MRT::Start")));
    // Allow repairer to output resend request.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Now, deliver expected packet...
    iRepairer->OutputAudio(*iAllocator->Allocate(1, true, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));

    // FIXME
    // Don't expect timer to be cancelled, as could still be requesting other missing ranges...
    // ...but, would we expect it to be cancelled if the repair buffer was emptied (i.e., after the next packet was output, which is the only packet queued)?
    // ... followed by next that was buffered

    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));

    // Now, resume normal sequence.
    iRepairer->OutputAudio(*iAllocator->Allocate(3, false, Brn("3")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));

    // Fire timer again. Should have no effect as no missing packets.
    iTimer->Fire();
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestResendMultiplePackets()
{
    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a couple of packets.
    iRepairer->OutputAudio(*iAllocator->Allocate(3, false, Brn("3")));
    // Expect retry logic to kick in.
    TEST(iTestPipe->Expect(Brn("MRT::Start")));
    // Allow repairer to output resend request.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->2")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Now, deliver expected packets...
    iRepairer->OutputAudio(*iAllocator->Allocate(1, true, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));
    iRepairer->OutputAudio(*iAllocator->Allocate(2, true, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));

    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));

    // Now, resume normal sequence.
    iRepairer->OutputAudio(*iAllocator->Allocate(4, false, Brn("4")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 4")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 4")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestResendMulitpleRanges()
{
    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a couple of packets.
    // Have a couple of contiguous packets to ensure resend algorithm skips over these.
    iRepairer->OutputAudio(*iAllocator->Allocate(3, false, Brn("3")));
    iRepairer->OutputAudio(*iAllocator->Allocate(4, false, Brn("4")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));
    // Miss more packets.
    iRepairer->OutputAudio(*iAllocator->Allocate(6, false, Brn("6")));

    // Allow repairer to output resend request.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->2 5->5")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Send in the missing packets, which should flush out the buffered packets.
    iRepairer->OutputAudio(*iAllocator->Allocate(1, true, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));
    iRepairer->OutputAudio(*iAllocator->Allocate(2, true, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 4")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 4")));

    iRepairer->OutputAudio(*iAllocator->Allocate(5, false, Brn("5")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 5")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 5")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 6")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 6")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestResendBeyondMultipleRangeLimit()
{
    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));
    // Miss another packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(4, false, Brn("4")));
    // Miss another packet.
    // Can only fit (at most) kMaxFrames/2 resend packet in repair buffer
    // so packet 5 won't be in initial resend request.
    iRepairer->OutputAudio(*iAllocator->Allocate(6, false, Brn("6")));

    // Allow repairer to output resend request.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1 3->3")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Send in the missing packets, which should flush out the buffered packets.
    iRepairer->OutputAudio(*iAllocator->Allocate(1, true, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    iRepairer->OutputAudio(*iAllocator->Allocate(3, true, Brn("3")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 4")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 4")));

    // Now fire timer to allow request for final missing packet.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 5->5")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    iRepairer->OutputAudio(*iAllocator->Allocate(5, true, Brn("5")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 5")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 5")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 6")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 6")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestMultipleResendRecover()
{
    // Test that goes through a few recovery sequences.

    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a couple of packet sequences.
    iRepairer->OutputAudio(*iAllocator->Allocate(3, false, Brn("3")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));
    iRepairer->OutputAudio(*iAllocator->Allocate(5, false, Brn("5")));

    // Allow timer to fire.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->2 4->4")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Resend only the first missing packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(1, true, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));

    // Pass in another packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(6, false, Brn("6")));

    // Fire timer again.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 2->2 4->4")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Send in first missing packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(2, true, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));

    // Pass in another packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(7, false, Brn("7")));

    // Send in last missing packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(4, true, Brn("4")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 4")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 4")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 5")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 5")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 6")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 6")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 7")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 7")));

    // Allow timer to fire again. Nothing should happen as no more missing packets.
    iTimer->Fire();

    // Send in more packets.
    iRepairer->OutputAudio(*iAllocator->Allocate(8, false, Brn("8")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 8")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 8")));
    iRepairer->OutputAudio(*iAllocator->Allocate(9, false, Brn("9")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 9")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 9")));

    // Miss a packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(11, false, Brn("11")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Another packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(12, false, Brn("12")));
    // Allow timer to fire.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 10->10")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));
    // More packets arrive before resend request satisfied.
    iRepairer->OutputAudio(*iAllocator->Allocate(13, false, Brn("13")));
    iRepairer->OutputAudio(*iAllocator->Allocate(14, false, Brn("14")));
    // Resent packet arrives.
    iRepairer->OutputAudio(*iAllocator->Allocate(10, true, Brn("10")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 2 10")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 10")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 2 11")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 11")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 2 12")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 12")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 2 13")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 13")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 2 14")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 14")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestResendRequest()
{
    // Test resend requests are repeated if resend packets not received.
    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Fire timer.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Send another packet in.
    iRepairer->OutputAudio(*iAllocator->Allocate(3, false, Brn("3")));

    // Fire timer again. Resend request should be made again as packet still hasn't arrived.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Send in missed packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(1, true, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestResendPacketBufferOverflowFirst()
{
    // An initial resend packet arrives, but will cause buffer to overflow.
    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a couple of packets.
    iRepairer->OutputAudio(*iAllocator->Allocate(3, false, Brn("3")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Fire timer.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->2")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Fill buffer with packets.
    iRepairer->OutputAudio(*iAllocator->Allocate(4, false, Brn("4")));
    iRepairer->OutputAudio(*iAllocator->Allocate(5, false, Brn("5")));
    iRepairer->OutputAudio(*iAllocator->Allocate(6, false, Brn("6")));
    iRepairer->OutputAudio(*iAllocator->Allocate(7, false, Brn("7")));
    iRepairer->OutputAudio(*iAllocator->Allocate(8, false, Brn("8")));

    // Receive the first packet being waited on. Should cause overflow.
    TEST_THROWS(iRepairer->OutputAudio(*iAllocator->Allocate(2, true, Brn("2"))), RepairerBufferFull);
    TEST(iTestPipe->Expect(Brn("MRT::Cancel")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 4")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 5")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 6")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 7")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 8")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestResendPacketBufferOverflowMiddle()
{
    // A resend request has arrived for somewhere in middle of repair buffer, but subsequent frames have already arrived and filled buffer.

    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Fire timer.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Miss another packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(4, false, Brn("4")));

    // Fire timer again.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1 3->3")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Now, send in some more packets to fill buffer.
    // So, have a packet missing at start and middle of repair buffer.
    iRepairer->OutputAudio(*iAllocator->Allocate(5, false, Brn("5")));
    iRepairer->OutputAudio(*iAllocator->Allocate(6, false, Brn("6")));
    iRepairer->OutputAudio(*iAllocator->Allocate(7, false, Brn("7")));
    iRepairer->OutputAudio(*iAllocator->Allocate(8, false, Brn("8")));

    // Now, send in packet that was missing from middle of sequence (first packet still hasn't arrived).
    TEST_THROWS(iRepairer->OutputAudio(*iAllocator->Allocate(3, true, Brn("3"))), RepairerBufferFull);
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));
    TEST(iTestPipe->Expect(Brn("MRT::Cancel")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 4")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 5")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 6")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 7")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 8")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestResendPacketBufferOverflowLast()
{
    // Packet is missed and packets are pushed in at end of repair buffer until buffer overflows.

    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Fire timer.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Send in packets that should be appended to end of buffer until buffer overflows.
    iRepairer->OutputAudio(*iAllocator->Allocate(3, false, Brn("3")));
    iRepairer->OutputAudio(*iAllocator->Allocate(4, false, Brn("4")));
    iRepairer->OutputAudio(*iAllocator->Allocate(5, false, Brn("5")));
    iRepairer->OutputAudio(*iAllocator->Allocate(6, false, Brn("6")));
    iRepairer->OutputAudio(*iAllocator->Allocate(7, false, Brn("7")));

    TEST_THROWS(iRepairer->OutputAudio(*iAllocator->Allocate(8, false, Brn("8"))), RepairerBufferFull);
    TEST(iTestPipe->Expect(Brn("MRT::Cancel")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 4")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 5")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 6")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 7")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 8")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestResendBufferOverflowRecover()
{
    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Fire timer.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Send in packets that should be appended to end of buffer until buffer overflows.
    iRepairer->OutputAudio(*iAllocator->Allocate(3, false, Brn("3")));
    iRepairer->OutputAudio(*iAllocator->Allocate(4, false, Brn("4")));
    iRepairer->OutputAudio(*iAllocator->Allocate(5, false, Brn("5")));
    iRepairer->OutputAudio(*iAllocator->Allocate(6, false, Brn("6")));
    iRepairer->OutputAudio(*iAllocator->Allocate(7, false, Brn("7")));

    TEST_THROWS(iRepairer->OutputAudio(*iAllocator->Allocate(8, false, Brn("8"))), RepairerBufferFull);
    TEST(iTestPipe->Expect(Brn("MRT::Cancel")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 4")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 5")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 6")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 7")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 8")));

    // Now, continue packet sequence. Should be passed on as normal.
    iRepairer->OutputAudio(*iAllocator->Allocate(9, false, Brn("9")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 9")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 9")));
    iRepairer->OutputAudio(*iAllocator->Allocate(10, false, Brn("10")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 2 10")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 10")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestResendPacketsOutOfOrder()
{
    // Miss a couple of packets and resend out of order.

    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Fire timer.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Miss another packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(4, false, Brn("4")));

    // Fire timer again.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1 3->3")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Now, send in the packets out of order.
    iRepairer->OutputAudio(*iAllocator->Allocate(3, true, Brn("3")));
    TEST(iTestPipe->ExpectEmpty());
    iRepairer->OutputAudio(*iAllocator->Allocate(1, true, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 4")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 4")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestResendPacketsAlreadySeen()
{
    // Miss a couple of packets and have a duplicate resent.

    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));

    // Miss a packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Fire timer.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Miss another packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(4, false, Brn("4")));

    // Fire timer again.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1 3->3")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Act like first request wasn't answered and fire timer again.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1 3->3")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Now, send repair packets in.
    // Pretend race condition where packet 3 was actually sent after first request but just didn't arrive in time.
    iRepairer->OutputAudio(*iAllocator->Allocate(3, true, Brn("3")));
    TEST(iTestPipe->ExpectEmpty());
    // Then, both packets were sent successfully after second request. Duplicate packet 3 should have no effect.
    iRepairer->OutputAudio(*iAllocator->Allocate(1, true, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 4")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 4")));
    iRepairer->OutputAudio(*iAllocator->Allocate(3, true, Brn("3")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 3")));  // Discard resend.

    // Continue sequence.
    iRepairer->OutputAudio(*iAllocator->Allocate(5, false, Brn("5")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 5")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 5")));

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestStreamReset()
{
    // Receiving a packet already seen but is not a resend.

    // Case 1: Normal sequence of packets (none missing) and stream is restarted.
    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));
    iRepairer->OutputAudio(*iAllocator->Allocate(1, false, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));
    // Now, output packet with a seq no. already seen, but that is not a resend.
    TEST_THROWS(iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0"))), RepairerStreamRestarted);
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));
    TEST(iTestPipe->ExpectEmpty());

    // Continue new stream.
    // Retain ownership of msg after a RepairerStreamRestarted.
    iRepairer->OutputAudio(*iAllocator->Allocate(1, false, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestStreamResetResendPending()
{
    // Case 2: Waiting on a missed packet when a stream is restarted.
    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));
    // Miss a packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));
    // Fire timer.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));
    // Send in packet with seq no. already seen, but that is not a resend.
    TEST_THROWS(iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0"))), RepairerStreamRestarted);
    TEST(iTestPipe->Expect(Brn("MRT::Cancel")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));
    TEST(iTestPipe->ExpectEmpty());

    // Continue new stream.
    // Retain ownership of msg after a RepairerStreamRestarted.
    iRepairer->OutputAudio(*iAllocator->Allocate(1, false, Brn("1")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 1")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 1")));
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 2")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));
    TEST(iTestPipe->ExpectEmpty());
}

void SuiteRaopResend::TestDropAudio()
{
    iRepairer->OutputAudio(*iAllocator->Allocate(0, false, Brn("0")));
    TEST(iTestPipe->Expect(Brn("MAS::OutputAudio 1 0")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 0")));
    // Miss a packet.
    iRepairer->OutputAudio(*iAllocator->Allocate(2, false, Brn("2")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));
    // Fire timer.
    iTimer->Fire();
    TEST(iTestPipe->Expect(Brn("MRR::ReqestResend 1->1")));
    TEST(iTestPipe->Expect(Brn("MRT::Start")));

    // Now, tell Repairer to drop audio.
    iRepairer->DropAudio();
    TEST(iTestPipe->Expect(Brn("MRT::Cancel")));
    TEST(iTestPipe->Expect(Brn("MR::Destroy 2")));

    TEST(iTestPipe->ExpectEmpty());
}


void TestRaop(Environment& aEnv)
{
    Runner runner("RAOP tests\n");
    runner.Add(new SuiteRaopVolume());
    runner.Add(new SuiteRaopResend(aEnv));
    runner.Run();
}
