#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Av/VolumeManager.h>

namespace OpenHome {
namespace Av {
namespace Test {

class MockVolumeReporter : public IVolumeReporter
{
public:
    MockVolumeReporter();
    const IVolumeObserver& Observer() const;
    void Clear();
public: // from IVolumeReporter
    void AddVolumeObserver(IVolumeObserver& aObserver) override;
private:
    IVolumeObserver* iObserver;
};

class MockVolumeOffset : public IVolumeSourceOffset
{
public:
    MockVolumeOffset();
    TInt Offset() const;
public: // from IVolumeSourceOffset
    void SetVolumeOffset(TInt aOffset) override;
private:
    TInt iOffset;
};

class SuiteVolumeScaler : public OpenHome::TestFramework::SuiteUnitTest
{
public:
    SuiteVolumeScaler();
public: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void TestRangeOverflow();
    void TestEnable();
    void TestUserVolumeInvalid();
    void TestExternalVolumeInvalid();
    void TestLimits();
    void TestUserVolumeChanges();
    void TestExternalVolumeChanges();
private:
    MockVolumeReporter* iReporter;
    MockVolumeOffset* iOffset;
};

} // namespace Test
} // namespace Av
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;


// MockVolumeReporter

MockVolumeReporter::MockVolumeReporter()
    : iObserver(nullptr)
{
}

const IVolumeObserver& MockVolumeReporter::Observer() const
{
    return *iObserver;
}

void MockVolumeReporter::Clear()
{
    iObserver = nullptr;
}

void MockVolumeReporter::AddVolumeObserver(IVolumeObserver& aObserver)
{
    ASSERT(iObserver == nullptr);
    iObserver = &aObserver;
}


// MockVolumeOffset

MockVolumeOffset::MockVolumeOffset()
    : iOffset(0)
{
}

TInt MockVolumeOffset::Offset() const
{
    return iOffset;
}

void MockVolumeOffset::SetVolumeOffset(TInt aOffset)
{
    iOffset = aOffset;
}


// SuiteVolumeScaler

SuiteVolumeScaler::SuiteVolumeScaler()
    : SuiteUnitTest("SuiteVolumeScaler")
{
    AddTest(MakeFunctor(*this, &SuiteVolumeScaler::TestRangeOverflow), "TestRangeOverflow");
    AddTest(MakeFunctor(*this, &SuiteVolumeScaler::TestEnable), "TestEnable");
    AddTest(MakeFunctor(*this, &SuiteVolumeScaler::TestUserVolumeInvalid), "TestUserVolumeInvalid");
    AddTest(MakeFunctor(*this, &SuiteVolumeScaler::TestExternalVolumeInvalid), "TestExternalVolumeInvalid");
    AddTest(MakeFunctor(*this, &SuiteVolumeScaler::TestLimits), "TestLimits");
    AddTest(MakeFunctor(*this, &SuiteVolumeScaler::TestUserVolumeChanges), "TestUserVolumeChanges");
    AddTest(MakeFunctor(*this, &SuiteVolumeScaler::TestExternalVolumeChanges), "TestExternalVolumeChanges");
}

void SuiteVolumeScaler::Setup()
{
    iReporter = new MockVolumeReporter();
    iOffset = new MockVolumeOffset();
}

void SuiteVolumeScaler::TearDown()
{
    delete iOffset;
    delete iReporter;
}

void SuiteVolumeScaler::TestRangeOverflow()
{
    static const TUint kMaxUint = std::numeric_limits<TUint>::max();
    // Test on TUint max limit. Shouldn't assert.
    {
        VolumeScaler(*iReporter, *iOffset, kMaxUint, 1);
        iReporter->Clear();
    }
    {
        VolumeScaler(*iReporter, *iOffset, 1, kMaxUint);
        iReporter->Clear();
    }
    {
        VolumeScaler(*iReporter, *iOffset, kMaxUint/2, 2);
        iReporter->Clear();
    }

    // Test overflow by one.
    TEST_THROWS(VolumeScaler(*iReporter, *iOffset, kMaxUint/2+1, 2), AssertionFailed);
    TEST_THROWS(VolumeScaler(*iReporter, *iOffset, 2, kMaxUint/2+1), AssertionFailed);
    
    // Test larger overflows.
    TEST_THROWS(VolumeScaler(*iReporter, *iOffset, kMaxUint, 2), AssertionFailed);
    TEST_THROWS(VolumeScaler(*iReporter, *iOffset, 2, kMaxUint), AssertionFailed);
    TEST_THROWS(VolumeScaler(*iReporter, *iOffset, kMaxUint, kMaxUint), AssertionFailed);
}

void SuiteVolumeScaler::TestEnable()
{
    VolumeScaler scaler(*iReporter, *iOffset, 100, 50);
    TEST(iOffset->Offset() == 0);
    scaler.VolumeChanged(50);
    scaler.SetVolume(25);
    TEST(iOffset->Offset() == 0);
    scaler.SetVolumeEnabled(true);
    TEST(iOffset->Offset() == -25);

    scaler.SetVolumeEnabled(false);
    TEST(iOffset->Offset() == 0);
}

void SuiteVolumeScaler::TestUserVolumeInvalid()
{
    VolumeScaler scaler(*iReporter, *iOffset, 100, 50);
    TEST_THROWS(scaler.VolumeChanged(101), AssertionFailed);
    TEST_THROWS(scaler.VolumeChanged(999), AssertionFailed);
}

void SuiteVolumeScaler::TestExternalVolumeInvalid()
{
    VolumeScaler scaler(*iReporter, *iOffset, 100, 50);
    TEST_THROWS(scaler.SetVolume(51), AssertionFailed);
    TEST_THROWS(scaler.SetVolume(999), AssertionFailed);
}

void SuiteVolumeScaler::TestLimits()
{
    // Max user vol > max external vol.
    {
        VolumeScaler scaler(*iReporter, *iOffset, 100, 50);
        scaler.SetVolumeEnabled(true);
        // User: 0, external: 0.
        scaler.VolumeChanged(0);
        scaler.SetVolume(0);
        TEST(iOffset->Offset() == 0);
        // User: 100, external: 50.
        scaler.VolumeChanged(100);
        scaler.SetVolume(50);
        TEST(iOffset->Offset() == 0);
        iReporter->Clear();
    }
    // Max user vol < max external vol.
    {
        VolumeScaler scaler(*iReporter, *iOffset, 50, 100);
        scaler.SetVolumeEnabled(true);
        // User: 0, external: 0.
        scaler.VolumeChanged(0);
        scaler.SetVolume(0);
        // User: 50, external: 100.
        scaler.VolumeChanged(50);
        scaler.SetVolume(100);
        TEST(iOffset->Offset() == 0);
        iReporter->Clear();
    }
    // Max user vol == max external vol.
    {
        VolumeScaler scaler(*iReporter, *iOffset, 100, 100);
        scaler.SetVolumeEnabled(true);
        // User: 0, external: 0.
        scaler.VolumeChanged(0);
        scaler.SetVolume(0);
        TEST(iOffset->Offset() == 0);
        // User: 100, external: 100.
        scaler.VolumeChanged(100);
        scaler.SetVolume(100);
        TEST(iOffset->Offset() == 0);
        iReporter->Clear();
    }
}

void SuiteVolumeScaler::TestUserVolumeChanges()
{
    VolumeScaler scaler(*iReporter, *iOffset, 100, 100);
    scaler.SetVolumeEnabled(true);

    // External vol at 0.
    scaler.SetVolume(0);
    scaler.VolumeChanged(0);
    TEST(iOffset->Offset() == 0);
    scaler.VolumeChanged(25);
    TEST(iOffset->Offset() == -25);
    scaler.VolumeChanged(50);
    TEST(iOffset->Offset() == -50);
    scaler.VolumeChanged(75);
    TEST(iOffset->Offset() == -75);
    scaler.VolumeChanged(100);
    TEST(iOffset->Offset() == -100);

    // External vol at 50.
    scaler.SetVolume(50);
    scaler.VolumeChanged(0);
    TEST(iOffset->Offset() == 0);
    scaler.VolumeChanged(25);
    TEST(iOffset->Offset() == -13);
    scaler.VolumeChanged(50);
    TEST(iOffset->Offset() == -25);
    scaler.VolumeChanged(75);
    TEST(iOffset->Offset() == -38);
    scaler.VolumeChanged(100);
    TEST(iOffset->Offset() == -50);

    // External vol at 100.
    scaler.SetVolume(100);
    scaler.VolumeChanged(0);
    TEST(iOffset->Offset() == 0);
    scaler.VolumeChanged(25);
    TEST(iOffset->Offset() == 0);
    scaler.VolumeChanged(50);
    TEST(iOffset->Offset() == 0);
    scaler.VolumeChanged(75);
    TEST(iOffset->Offset() == 0);
    scaler.VolumeChanged(100);
    TEST(iOffset->Offset() == 0);
}

void SuiteVolumeScaler::TestExternalVolumeChanges()
{
    VolumeScaler scaler(*iReporter, *iOffset, 100, 100);
    scaler.SetVolumeEnabled(true);

    // User vol at 0.
    scaler.VolumeChanged(0);
    scaler.SetVolume(0);
    TEST(iOffset->Offset() == 0);
    scaler.SetVolume(25);
    TEST(iOffset->Offset() == 0);
    scaler.SetVolume(50);
    TEST(iOffset->Offset() == 0);
    scaler.SetVolume(75);
    TEST(iOffset->Offset() == 0);
    scaler.SetVolume(100);
    TEST(iOffset->Offset() == 0);

    // User vol at 50.
    scaler.VolumeChanged(50);
    scaler.SetVolume(0);
    TEST(iOffset->Offset() == -50);
    scaler.SetVolume(25);
    TEST(iOffset->Offset() == -38);
    scaler.SetVolume(50);
    TEST(iOffset->Offset() == -25);
    scaler.SetVolume(75);
    TEST(iOffset->Offset() == -13);
    scaler.SetVolume(100);
    TEST(iOffset->Offset() == 0);

    // User vol at 100.
    scaler.VolumeChanged(100);
    scaler.SetVolume(0);
    TEST(iOffset->Offset() == -100);
    scaler.SetVolume(25);
    TEST(iOffset->Offset() == -75);
    scaler.SetVolume(50);
    TEST(iOffset->Offset() == -50);
    scaler.SetVolume(75);
    TEST(iOffset->Offset() == -25);
    scaler.SetVolume(100);
    TEST(iOffset->Offset() == 0);
}



void TestVolumeManager()
{
    Runner runner("VolumeManager tests\n");
    runner.Add(new SuiteVolumeScaler());
    runner.Run();
}
