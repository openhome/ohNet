#include <OpenHome/Media/VolumeManager.h>

#include <OpenHome/Private/Standard.h>  // ASSERT()
#include <OpenHome/Private/Printer.h>  // Log::Print() for *Logger

using namespace OpenHome;
using namespace OpenHome::Media;

//
// generic classes
//

IVolume::~IVolume()
{
    // NOP default implementation (for convenience)
}

IBalanceUser::~IBalanceUser()
{
    // NOP default implementation (for convenience)
}

IVolumeLimitUser::~IVolumeLimitUser()
{
    // NOP default implementation (for convenience)
}

IVolumeManagerLimits::~IVolumeManagerLimits()
{
    // NOP default implementation (for convenience)
}

IVolumeManager::~IVolumeManager()
{
    // NOP default implementation (for convenience)
}

// VolumeLimiterUser
VolumeLimiterUser::VolumeLimiterUser(IVolume& aVolume, TUint aLimit)
    : iVolume(aVolume)
    , iUpstreamVolume(0)
    , iLimit(aLimit)
{
}

TUint VolumeLimiterUser::UserVolumeLimit() const
{
    return iLimit;
}

void VolumeLimiterUser::SetUserVolumeLimit(TUint aValue)
{
    iLimit = aValue;
    Changed();
}

TUint VolumeLimiterUser::UserVolume() const
{
    return iUpstreamVolume;  // user volume *pre* limiting
}

void VolumeLimiterUser::SetVolume(TUint aValue)
{
    iUpstreamVolume = aValue;
    Changed();
}

void VolumeLimiterUser::Changed()
{
    iVolume.SetVolume((iUpstreamVolume > iLimit) ? iLimit : iUpstreamVolume);
}

// VolumeUser
VolumeUser::VolumeUser(IVolume& aVolume, TUint aScaleFactor)
    : iVolume(aVolume)
    , iScaleFactor(aScaleFactor)
{
}

void VolumeUser::SetVolume(TUint aValue)
{
    // fixed operation (without dynamic parameter)
    iVolume.SetVolume(iScaleFactor * aValue);
}

// VolumeSourceOffset
VolumeSourceOffset::VolumeSourceOffset(IVolume& aVolume)
    : iVolume(aVolume)
    , iUpstreamVolume(0)
    , iSourceOffset(0)
{
}

void VolumeSourceOffset::SetOffset(TUint aValue)
{
    iSourceOffset = aValue;
    Changed();
}

void VolumeSourceOffset::SetVolume(TUint aValue)
{
    iUpstreamVolume = aValue;
    Changed();
}

void VolumeSourceOffset::Changed()
{
    iVolume.SetVolume(iUpstreamVolume + iSourceOffset);
}

// VolumeUnityGain
VolumeUnityGain::VolumeUnityGain(IVolume& aVolume, TUint aUnityGainSystemVolume)
    : iVolume(aVolume)
    , iUnityGainSystemVolume(aUnityGainSystemVolume)
    , iUpstreamVolume(0)
    , iEnabled(false)
{
}

void VolumeUnityGain::SetUnityGain(bool aEnabled)
{
    iEnabled = aEnabled;
    Changed();
}

void VolumeUnityGain::SetVolume(TUint aValue)
{
    iUpstreamVolume = aValue;
    Changed();
}

void VolumeUnityGain::Changed()
{
    if (iEnabled) {
        iVolume.SetVolume(iUnityGainSystemVolume);
    } else {
        iVolume.SetVolume(iUpstreamVolume);
    }
}

// VolumeBalanceUser
VolumeBalanceUser::VolumeBalanceUser(IVolume& aLeftVolume, IVolume& aRightVolume)
    : iLeftVolume(aLeftVolume)
    , iRightVolume(aRightVolume)
    , iUpstreamVolume(0)
    , iUserBalance(0)
    , iLeftOffset(0)
    , iRightOffset(0)
{
}

TInt VolumeBalanceUser::UserBalance() const
{
    return iUserBalance;
}

void VolumeBalanceUser::SetUserBalance(TInt aValue)
{
    iUserBalance = aValue;
    iLeftOffset = LeftOffset(aValue);
    iRightOffset = RightOffset(aValue);
    Changed();
}

void VolumeBalanceUser::SetVolume(TUint aValue)
{
    iUpstreamVolume = aValue;
    Changed();
}

void VolumeBalanceUser::Changed()
{
    TInt nonNegVol = 0;
    nonNegVol = static_cast<TInt>(iUpstreamVolume) + iLeftOffset;
    if (nonNegVol < 0) { nonNegVol = 0; }
    iLeftVolume.SetVolume(nonNegVol);
    nonNegVol = static_cast<TInt>(iUpstreamVolume) + iRightOffset;
    if (nonNegVol < 0) { nonNegVol = 0; }
    iRightVolume.SetVolume(nonNegVol);
}

// VolumeLimiter
VolumeLimiter::VolumeLimiter(IVolume& aVolume, TUint aLimit)
    : iVolume(aVolume)
    , iUpstreamVolume(0)
    , iLimit(aLimit)
{
}

void VolumeLimiter::SetVolume(TUint aValue)
{
    if (iUpstreamVolume != aValue) {
        iUpstreamVolume = aValue;
        if (iUpstreamVolume > iLimit) {
            iVolume.SetVolume(iLimit);
        } else {
            iVolume.SetVolume(iUpstreamVolume);
        }
    }
}

//
// classes providing sensible default factors and value ranges
//

// VolumeLimiterUserDefault
VolumeLimiterUserDefault::VolumeLimiterUserDefault(IVolume& aVolume)
    : VolumeLimiterUser(aVolume, VolumeUserDefault::MaxUserVolume())
{
}

// VolumeUserDefault
TUint VolumeUserDefault::MaxUserVolume()  // static
{
    return 100;
}

TUint VolumeUserDefault::SystemVolumeFactor()  // static
{
    return 1024;
}

TUint VolumeUserDefault::MaxSystemVolume()  // static
{
    return MaxUserVolume() * SystemVolumeFactor();
}

VolumeUserDefault::VolumeUserDefault(IVolume& aVolume)
    : VolumeUser(aVolume, SystemVolumeFactor())
{
}

// VolumeUnityGainDefault
TUint VolumeUnityGainDefault::UnityGainSystemVolume()  // static
{
    return 80 * VolumeUserDefault::SystemVolumeFactor();
}

VolumeUnityGainDefault::VolumeUnityGainDefault(IVolume& aVolume)
    : VolumeUnityGain(aVolume, UnityGainSystemVolume())
{
}

// VolumeBalanceUserDefault
TInt VolumeBalanceUserDefault::MinimumUserBalance()  // static
{
    return -15;
}

TInt VolumeBalanceUserDefault::MaximumUserBalance()  // static
{
    return 15;
}

// from older .../Preamp/SpeakerConfig.h
// hard-coded factor of two to allow integer representation
const TInt VolumeBalanceUserDefault::kBalanceOffsets[] =  // static
{
    -200,  // -15
     -48,  //
     -32,  //
     -25,  //
     -16,  //
     -13,  // -10
     -11,  //
      -9,  //
      -8,  //
      -6,  //
      -5,  // -5
      -4,  //
      -3,  //
      -2,  //
      -1,  //
       0,  // 0
       1,  //
       2,  //
       2,  //
       3,  //
       3,  // +5
       4,  //
       4,  //
       5,  //
       5,  //
       5,  // +10
       5,  //
       5,  //
       6,  //
       6,  //
       6,  // +15
};

VolumeBalanceUserDefault::VolumeBalanceUserDefault(IVolume& aLeftVolume, IVolume& aRightVolume)
    : VolumeBalanceUser(aLeftVolume, aRightVolume)
{
}

TInt VolumeBalanceUserDefault::LeftOffset(TInt aValue) const
{
    ASSERT((MinimumUserBalance() <= aValue) && (aValue <= MaximumUserBalance()));
    // factor two allows integer representation in declaration
    return (static_cast<TInt>(VolumeUserDefault::SystemVolumeFactor()) * kBalanceOffsets[MaximumUserBalance() - aValue]) / 2;
}

TInt VolumeBalanceUserDefault::RightOffset(TInt aValue) const
{
    ASSERT((MinimumUserBalance() <= aValue) && (aValue <= MaximumUserBalance()));
    // factor two allows integer representation in declaration
    return (static_cast<TInt>(VolumeUserDefault::SystemVolumeFactor()) * kBalanceOffsets[MaximumUserBalance() + aValue]) / 2;
}

// VolumeLimiterDefault
TUint VolumeLimiterDefault::MaxLimitSystemVolume()  // static
{
    return 100 * VolumeUserDefault::SystemVolumeFactor();
}

VolumeLimiterDefault::VolumeLimiterDefault(IVolume& aVolume)
    : VolumeLimiter(aVolume, MaxLimitSystemVolume())
{
}

// VolumeManager
VolumeManager::VolumeManager(IVolume& aLeftVolHardware, IVolume& aRightVolHardware)
    : iLeftVolHw(aLeftVolHardware)
    , iRightVolHw(aRightVolHardware)
{
}

TUint VolumeManager::UserVolume() const
{
    return iVolLimitUser->UserVolume();  // sic!
}

TInt VolumeManager::UserBalance() const
{
    return iVolBal->UserBalance();  // -ve .. 0 (neutral) .. +ve
}

TUint VolumeManager::UserVolumeLimit() const
{
    return iVolLimitUser->UserVolumeLimit();
}

void VolumeManager::SetUserVolume(TUint aValue)
{
    iVolUser->SetVolume(aValue);
}

void VolumeManager::SetUserBalance(TInt aValue)
{
    iVolBal->SetUserBalance(aValue);
}

void VolumeManager::SetUserVolumeLimit(TUint aValue)
{
    iVolLimitUser->SetUserVolumeLimit(aValue);
}

// VolumeManagerDefault
VolumeManagerDefault::VolumeManagerDefault(IVolume& aLeftVolHardware, IVolume& aRightVolHardware)
    : VolumeManager(aLeftVolHardware, aRightVolHardware)
{
    iLeftVolLimit = new VolumeLimiterDefault(iLeftVolHw);
    iRightVolLimit = new VolumeLimiterDefault(iRightVolHw);
    iVolBal = new VolumeBalanceUserDefault(*iLeftVolLimit, *iRightVolLimit);
    iVolUnityGain = new VolumeUnityGainDefault(*iVolBal);
    iVolSrcOff = new VolumeSourceOffset(*iVolUnityGain);
    iVolUser = new VolumeUserDefault(*iVolSrcOff);
    iVolLimitUser = new VolumeLimiterUserDefault(*iVolUser);
}

VolumeManagerDefault::~VolumeManagerDefault()
{
    delete iVolLimitUser;
    delete iVolUser;
    delete iVolSrcOff;
    delete iVolUnityGain;
    delete iVolBal;
    delete iLeftVolLimit;
    delete iRightVolLimit;
}

TUint VolumeManagerDefault::MaxUserVolume() const
{
    return VolumeUserDefault::MaxUserVolume();
}

TUint VolumeManagerDefault::VolumeUnity() const
{
    return VolumeUnityGainDefault::UnityGainSystemVolume() / VolumeUserDefault::SystemVolumeFactor();
}

TUint VolumeManagerDefault::VolumeSteps() const
{
    return VolumeUserDefault::MaxUserVolume();  // [0..100] in steps of 1
}

TUint VolumeManagerDefault::VolumeMilliDbPerStep() const
{
    return VolumeUserDefault::SystemVolumeFactor();
}

TInt VolumeManagerDefault::MaxUserBalance() const
{
    return VolumeBalanceUserDefault::MaximumUserBalance();
}

// VolumeSinkLogger
VolumeSinkLogger::VolumeSinkLogger(const TChar* aLabel)
    : iLabel(aLabel)
{
}

void VolumeSinkLogger::SetVolume(TUint aValue)
{
    Log::Print("\n[VolSinkLog:");  Log::Print(iLabel);  Log::Print("] vol = %u\n", aValue);
}
