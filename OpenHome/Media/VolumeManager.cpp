#include <OpenHome/Media/VolumeManager.h>

#include <OpenHome/Private/Standard.h>  // ASSERT()

using namespace OpenHome;
using namespace OpenHome::Media;

//
// generic classes
//

IVolume::~IVolume()
{
    // NOP default implementation (for convenience)
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

// VolumeBalance
VolumeBalance::VolumeBalance(IVolume& aLeftVolume, IVolume& aRightVolume)
    : iLeftVolume(aLeftVolume)
    , iRightVolume(aRightVolume)
    , iUpstreamVolume(0)
    , iLeftOffset(0)
    , iRightOffset(0)
{
}

void VolumeBalance::SetBalance(TInt aLeftOffset, TInt aRightOffset)
{
    iLeftOffset = aLeftOffset;
    iRightOffset = aRightOffset;
    Changed();
}

void VolumeBalance::SetVolume(TUint aValue)
{
    iUpstreamVolume = aValue;
    Changed();
}

void VolumeBalance::Changed()
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

// VolumeUserDefault
TUint VolumeUserDefault::SystemVolumeFactor()  // static
{
    return 1024;
}

TUint VolumeUserDefault::MaxSystemVolume()  // static
{
    return 100 * SystemVolumeFactor();
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

// VolumeBalanceDefault
TInt VolumeBalanceDefault::MinimumUserBalance()  // static
{
    return -15;
}

TInt VolumeBalanceDefault::MaximumUserBalance()  // static
{
    return 15;
}

// from older .../Preamp/SpeakerConfig.h
// hard-coded factor of two to allow integer representation
const TInt VolumeBalanceDefault::kBalanceOffsets[] =  // static
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

VolumeBalanceDefault::VolumeBalanceDefault(IVolume& aLeftVolume, IVolume& aRightVolume)
    : iVolumeBalance(aLeftVolume, aRightVolume)
{
}

void VolumeBalanceDefault::SetBalance(TInt aValue)
{
    ASSERT((MinimumUserBalance() <= aValue) && (aValue <= MaximumUserBalance()));
    // factor two allows integer representation in declaration
    iVolumeBalance.SetBalance((VolumeUserDefault::SystemVolumeFactor() * kBalanceOffsets[MaximumUserBalance() - aValue]) / 2,
                                (VolumeUserDefault::SystemVolumeFactor() * kBalanceOffsets[MaximumUserBalance() + aValue]) / 2);
}

void VolumeBalanceDefault::SetVolume(TUint aValue)
{
    iVolumeBalance.SetVolume(aValue);
}
