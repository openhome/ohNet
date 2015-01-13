#include <OpenHome/Private/TestFramework.h>

#include <OpenHome/Media/VolumeManager.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/Tests/ConfigRamStore.h>
#include <OpenHome/Private/Converter.h>

// include "SuiteUnitTest.h"

using namespace OpenHome::TestFramework;
using namespace OpenHome;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;

//
// declaration of test suites (and auxiliary test class)
//

namespace OpenHome {
namespace Media {

class VolumeTap : public IVolume, public INonCopyable
{
public:
    VolumeTap(IVolume& aVolume);
    TUint Volume() const;  // latest volume propagated
public:  // from IVolume
    void SetVolume(TUint aValue);  // propagating unchanged
private:
    IVolume& iVolume;
    TUint iUpstreamVolume;
};

class VolumeSink : public IVolume
{
public:
    VolumeSink();
    TUint Volume() const;  // latest volume received
public:  // from IVolume
    void SetVolume(TUint aValue);  // non-propagating
private:
    TUint iUpstreamVolume;
};

class SuiteVolumeManager : public Suite
{
public:
    SuiteVolumeManager();
public:  // from Suite
    void Test();
private:
    TUint UintFromStoreInt(const Brx& aKey);
    void TestTaps(TUint aUser, TUint aSrc, TUint aUnityGain, TUint aLeftBal, TUint aRightBal, TUint aLeftSink, TUint aRightSink);
private:
    ConfigRamStore iStore;
    PowerManager iPowerManager;
    VolumeSink iLeftVolSink;
    VolumeSink iRightVolSink;
    VolumeLimiterDefault iLeftVolLimitDfl;   // derived from
    VolumeLimiterDefault iRightVolLimitDfl;  // VolumeLimiter
    VolumeTap iLeftTapPostBalDfl;
    VolumeTap iRightTapPostBalDfl;
    VolumeBalanceUserDefault iVolBalDfl;  // uses VolumeBalance
    VolumeTap iTapPostUnityGainDfl;
    VolumeUnityGainDefault iVolUnityGainDfl;  // derived from VolumeUnityGain
    VolumeTap iTapPostSrcOff;
    VolumeSourceOffset iVolSrcOff;
    VolumeTap iTapPostUserDfl;
    VolumeUserDefault iVolUserDfl;  // derived from VolumeUser
};

}  // namespace Media
}  // namespace OpenHome

//
// implementation of test suites (and auxiliary test class)
//

VolumeTap::VolumeTap(IVolume& aVolume)
    : iVolume(aVolume)
    , iUpstreamVolume(0)
{
}

TUint VolumeTap::Volume() const
{
    return iUpstreamVolume;
}

void VolumeTap::SetVolume(TUint aValue)
{
    iUpstreamVolume = aValue;
    iVolume.SetVolume(aValue);
}

VolumeSink::VolumeSink()
    : iUpstreamVolume(0)
{
}

TUint VolumeSink::Volume() const
{
    return iUpstreamVolume;
}

void VolumeSink::SetVolume(TUint aValue)
{
    iUpstreamVolume = aValue;
    // sink: no further propagation
}

// SuiteVolumeManager
SuiteVolumeManager::SuiteVolumeManager()
    : Suite("two-channel volume chain")
    , iLeftVolSink()
    , iRightVolSink()
    , iLeftVolLimitDfl(iLeftVolSink)
    , iRightVolLimitDfl(iRightVolSink)
    , iLeftTapPostBalDfl(iLeftVolLimitDfl)
    , iRightTapPostBalDfl(iRightVolLimitDfl)
    , iVolBalDfl(iLeftTapPostBalDfl, iRightTapPostBalDfl)
    , iTapPostUnityGainDfl(iVolBalDfl)
    , iVolUnityGainDfl(iTapPostUnityGainDfl)
    , iTapPostSrcOff(iVolUnityGainDfl)
    , iVolSrcOff(iTapPostSrcOff)
    , iTapPostUserDfl(iVolSrcOff)
    , iVolUserDfl(iTapPostUserDfl, iStore, iPowerManager)
{
}

TUint SuiteVolumeManager::UintFromStoreInt(const Brx& aKey)
{
    Bws<sizeof(TInt)> buf;
    iStore.Read(aKey, buf);
    TUint val = Converter::BeUint32At(buf, 0);
    return val;
}

void SuiteVolumeManager::TestTaps(TUint aUser, TUint aSrc, TUint aUnityGain, TUint aLeftBal, TUint aRightBal, TUint aLeftSink, TUint aRightSink)
{
    TEST(iTapPostUserDfl.Volume() == aUser * VolumeUserDefault::SystemVolumeFactor());
    TEST(iTapPostSrcOff.Volume() == aSrc * VolumeUserDefault::SystemVolumeFactor());
    TEST(iTapPostUnityGainDfl.Volume() == aUnityGain * VolumeUserDefault::SystemVolumeFactor());
    TEST((iLeftTapPostBalDfl.Volume() == aLeftBal * VolumeUserDefault::SystemVolumeFactor()) \
        && (iRightTapPostBalDfl.Volume() == aRightBal * VolumeUserDefault::SystemVolumeFactor()));
    TEST((iLeftVolSink.Volume() == aLeftSink * VolumeUserDefault::SystemVolumeFactor()) \
        && (iRightVolSink.Volume() == aRightSink * VolumeUserDefault::SystemVolumeFactor()));
}

void SuiteVolumeManager::Test()
{
    // sane initial state
    TestTaps(/*user*/0, /*src*/0, /*unity*/0, /*leftBal*/0, /*rightBal*/0, /*leftSink*/0, /*rightSink*/0);
    // user volume propagated
    iVolUserDfl.SetVolume(40);
    TestTaps(/*user*/40, /*src*/40, /*unity*/40, /*leftBal*/40, /*rightBal*/40, /*leftSink*/40, /*rightSink*/40);
    // additional source offset
    iVolSrcOff.SetOffset(20 * VolumeUserDefault::SystemVolumeFactor());
    TestTaps(/*user*/40, /*src*/60, /*unity*/60, /*leftBal*/60, /*rightBal*/60, /*leftSink*/60, /*rightSink*/60);
    // unity gain overrides user volume
    iVolUnityGainDfl.SetUnityGain(true);
    TestTaps(/*user*/40, /*src*/60, /*unity*/80, /*leftBal*/80, /*rightBal*/80, /*leftSink*/80, /*rightSink*/80);
    // unity gain keeps overriding user volume
    iVolUserDfl.SetVolume(100);
    TestTaps(/*user*/100, /*src*/120, /*unity*/80, /*leftBal*/80, /*rightBal*/80, /*leftSink*/80, /*rightSink*/80);
    // limiter clips excessive volume
    iVolUnityGainDfl.SetUnityGain(false);
    TestTaps(/*user*/100, /*src*/120, /*unity*/120, /*leftBal*/120, /*rightBal*/120, /*leftSink*/100, /*rightSink*/100);
    // sane listening volume and adjust balance maximally to left
    iVolUserDfl.SetVolume(40);
    iVolBalDfl.SetUserBalance(VolumeBalanceUserDefault::MinimumUserBalance());  // amplify left, attenuate right
    TestTaps(/*user*/40, /*src*/60, /*unity*/60, /*leftBal*/63, /*rightBal*/0, /*leftSink*/63, /*rightSink*/0);
    // adjust balance maximally to right
    iVolBalDfl.SetUserBalance(VolumeBalanceUserDefault::MaximumUserBalance());  // attenuate left, amplify right
    TestTaps(/*user*/40, /*src*/60, /*unity*/60, /*leftBal*/0, /*rightBal*/63, /*leftSink*/0, /*rightSink*/63);
    // adjust balance slightly to left
    iVolBalDfl.SetUserBalance(-6);  // attenuate left, amplify right
    TestTaps(/*user*/40, /*src*/60, /*unity*/60, /*leftBal*/62, /*rightBal*/57, /*leftSink*/62, /*rightSink*/57);

    // test current volume is written out at PowerDown event
    TEST(UintFromStoreInt(VolumeUser::kStartupVolumeKey) == VolumeUser::kDefaultStartupVolume);
    iPowerManager.PowerDown();
    TEST(UintFromStoreInt(VolumeUser::kStartupVolumeKey) == 40);
}

class VolumeRecorder : public IVolume
{
public:
    TUint Volume() const { return iVolume; }
public:  // IVolume
    void SetVolume(TUint aVolume) override { iVolume = aVolume; }
private:
    TUint iVolume;
};

class SuiteVolumeBalanceStereo : public Suite
{
public:
    SuiteVolumeBalanceStereo();
    void Test();
private:
    TBool Check(TUint aVolume, TInt aBalance, TUint aExpectedVolumeLeft, TUint aExpectedVolumeRight);
private:
    VolumeRecorder iLeft;
    VolumeRecorder iRight;
    VolumeBalanceStereo iVolumeBalanceStero;
};

SuiteVolumeBalanceStereo::SuiteVolumeBalanceStereo()
: Suite("VolumeBalanceStereo")
, iVolumeBalanceStero(iLeft, iRight)
{
}

TBool SuiteVolumeBalanceStereo::Check(TUint aVolume, TInt aBalance, TUint aExpectedVolumeLeft, TUint aExpectedVolumeRight)
{
    iVolumeBalanceStero.SetVolume(aVolume);
    iVolumeBalanceStero.SetBalance(aBalance);
    return (iLeft.Volume() == aExpectedVolumeLeft && iRight.Volume() == aExpectedVolumeRight);
}

void SuiteVolumeBalanceStereo::Test()
{
    //         INPUT      EXPECTED
    //         vol  bal    l    r
    TEST(Check( 80,   0,  80,  80));
    TEST(Check(100,   0, 100, 100));
    TEST(Check(100,  15,   0, 100));
    TEST(Check(100, -15, 100,   0));
    TEST(Check(100,   5,  66, 100));
    TEST(Check(100,  -5, 100,  66));
    TEST(Check(100,  10,  33, 100));
    TEST(Check(100, -10, 100,  33));
}

//
// sequential execution of test suites
//

void TestVolumeManager()
{
    Runner runner("Volume subsystem tests\n");
    runner.Add(new SuiteVolumeManager());
    runner.Add(new SuiteVolumeBalanceStereo());
    runner.Run();
}
