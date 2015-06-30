#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Av/Raop/Raop.h>
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
        return (*buf == aMessage);
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


void TestRaop()
{
    Runner runner("RAOP tests\n");
    runner.Add(new SuiteRaopVolume());
    runner.Run();
}
