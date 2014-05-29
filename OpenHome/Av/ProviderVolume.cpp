#include <OpenHome/Av/ProviderVolume.h>

#include <OpenHome/Buffer.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

//
// design notes:
// volume and mute manager backends are single sources of truth,
// respectively, and UPnP state variables merely track their state,
// resyncing whenever backend manipulated;
// absolute bounds checking on value ranges is done at UPnP level
// in order to generate error response (if necessary), but dynamic
// volume limiting is under control of volume manager
//
// known limitations:
// volume and mute manager do not (yet?) have API to notify changes,
// so current assumption is that settings are manipulated only via UPnP;
// MuteManager not yet populated with actual mute elements,
// so operating on dummy MuteNull element;
// IMuteManager does not yet support querying of mute state,
// so currently only manipulating UPnP state variable, not system backend
// currently assuming two-channel audio,
// so "fade" property not applicable;
//

// from older .../Preamp/ServiceVolume.cpp
#if 0 // FIXME - are these codes still needed?
const TInt kInvalidSourceIndexCode = 800;
const Brn  kInvalidSourceIndexMsg("Source index invalid");

const TInt kInvalidStringCode = 810;
const Brn  kInvalidStringMsg("String too long");

const TInt kInvalidFadeCode = 813;
const Brn  kInvalidFadeMsg("Fade invalid");
#endif

const TInt kActionNotSupportedCode = 801;
const Brn  kActionNotSupportedMsg("Action not supported");

const TInt kInvalidVolumeCode = 811;
const Brn  kInvalidVolumeMsg("Volume invalid");

const TInt kInvalidBalanceCode = 812;
const Brn  kInvalidBalanceMsg("Balance invalid");

ProviderVolume::ProviderVolume(DvDevice& aDevice, IMuteManager& /*aMuteManager*/, IVolumeManagerLimits& aVolumeManager)
    : DvProviderAvOpenhomeOrgVolume1(aDevice)
    //, iMuteManager(aMuteManager)
    , iVolumeManager(aVolumeManager)
    , iLock("PrVm")
{
    EnablePropertyVolume();
    EnablePropertyMute();
    EnablePropertyBalance();
    EnablePropertyFade();
    EnablePropertyVolumeLimit();
    EnablePropertyVolumeMax();
    EnablePropertyVolumeUnity();
    EnablePropertyVolumeSteps();
    EnablePropertyVolumeMilliDbPerStep();
    EnablePropertyBalanceMax();
    EnablePropertyFadeMax();  // N/A to two-channel audio, but required by ohNet

    SetPropertyVolume(iVolumeManager.UserVolume());
    SetPropertyMute(false);  // XXX enhance IMuteManager to allow query of actual setting
    SetPropertyBalance(iVolumeManager.UserBalance());
    SetPropertyFade(0);
    SetPropertyVolumeLimit(iVolumeManager.UserVolumeLimit());
    SetPropertyVolumeMax(iVolumeManager.MaxUserVolume());
    SetPropertyVolumeUnity(iVolumeManager.VolumeUnity());
    SetPropertyVolumeSteps(iVolumeManager.VolumeSteps());
    SetPropertyVolumeMilliDbPerStep(iVolumeManager.VolumeMilliDbPerStep());
    SetPropertyBalanceMax(iVolumeManager.MaxUserBalance());
    SetPropertyFadeMax(0);

    EnableActionCharacteristics();

    EnableActionSetVolume();
    EnableActionVolumeInc();
    EnableActionVolumeDec();
    EnableActionVolume();

    EnableActionSetBalance();
    EnableActionBalanceInc();
    EnableActionBalanceDec();
    EnableActionBalance();

    EnableActionSetFade();
    EnableActionFadeInc();
    EnableActionFadeDec();
    EnableActionFade();

    EnableActionSetMute();
    EnableActionMute();

    EnableActionVolumeLimit();
}

ProviderVolume::~ProviderVolume()
{
}

void ProviderVolume::Characteristics(IDvInvocation& aInvocation, IDvInvocationResponseUint& aVolumeMax, IDvInvocationResponseUint& aVolumeUnity, IDvInvocationResponseUint& aVolumeSteps, IDvInvocationResponseUint& aVolumeMilliDbPerStep, IDvInvocationResponseUint& aBalanceMax, IDvInvocationResponseUint& aFadeMax)
{
    TUint propMaxUserVol = 0;
    TUint propUnityVol = 0;
    TUint propVolSteps = 0;
    TUint propMilliDbPerVolStep = 0;
    TUint propMaxUserBalance = 0;
    TUint propMaxFade = 0;

    // assuming all these properties fixed at start-up,
    // so locking unnecessary

    GetPropertyVolumeMax(propMaxUserVol);
    GetPropertyVolumeUnity(propUnityVol);
    GetPropertyVolumeSteps(propVolSteps);
    GetPropertyVolumeMilliDbPerStep(propMilliDbPerVolStep);
    GetPropertyBalanceMax(propMaxUserBalance);
    GetPropertyFadeMax(propMaxFade);

    aInvocation.StartResponse();
    aVolumeMax.Write(propMaxUserVol);
    aVolumeUnity.Write(propUnityVol);
    aVolumeSteps.Write(propVolSteps);
    aVolumeMilliDbPerStep.Write(propMilliDbPerVolStep);
    aBalanceMax.Write(propMaxUserBalance);
    aFadeMax.Write(propMaxFade);
    aInvocation.EndResponse();
}

void ProviderVolume::SetVolume(IDvInvocation& aInvocation, TUint aValue)
{
    AutoMutex mutex(iLock);
    if (aValue > iVolumeManager.MaxUserVolume()) {
        aInvocation.Error(kInvalidVolumeCode, kInvalidVolumeMsg);
    }
    iVolumeManager.SetUserVolume(aValue);
    SetPropertyVolume(iVolumeManager.UserVolume());
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderVolume::VolumeInc(IDvInvocation& aInvocation)
{
    AutoMutex mutex(iLock);
    TUint vol = iVolumeManager.UserVolume();
    if (!(vol < iVolumeManager.MaxUserVolume())) {
        aInvocation.Error(kInvalidVolumeCode, kInvalidVolumeMsg);
    }
    ++vol;
    iVolumeManager.SetUserVolume(vol);
    SetPropertyVolume(iVolumeManager.UserVolume());
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderVolume::VolumeDec(IDvInvocation& aInvocation)
{
    AutoMutex mutex(iLock);
    TUint vol = iVolumeManager.UserVolume();
    if (0 == vol) {
        aInvocation.Error(kInvalidVolumeCode, kInvalidVolumeMsg);
    }
    --vol;
    iVolumeManager.SetUserVolume(vol);
    SetPropertyVolume(iVolumeManager.UserVolume());
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderVolume::Volume(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    AutoMutex mutex(iLock);
    TUint vol = iVolumeManager.UserVolume();
    SetPropertyVolume(vol);
    aInvocation.StartResponse();
    aValue.Write(vol);
    aInvocation.EndResponse();
}

void ProviderVolume::SetBalance(IDvInvocation& aInvocation, TInt aValue)
{
    AutoMutex mutex(iLock);
    TInt maxUserBal = iVolumeManager.MaxUserBalance();
    if (!((-maxUserBal <= aValue) && (aValue <= maxUserBal))) {
        aInvocation.Error(kInvalidBalanceCode, kInvalidBalanceMsg);
    }
    iVolumeManager.SetUserBalance(aValue);
    SetPropertyBalance(aValue);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderVolume::BalanceInc(IDvInvocation& aInvocation)
{
    AutoMutex mutex(iLock);
    TInt maxUserBal = iVolumeManager.MaxUserBalance();
    TInt bal = iVolumeManager.UserBalance() + 1;
    if (!((-maxUserBal <= bal) && (bal <= maxUserBal))) {
        aInvocation.Error(kInvalidBalanceCode, kInvalidBalanceMsg);
    }
    iVolumeManager.SetUserBalance(bal);
    SetPropertyBalance(bal);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderVolume::BalanceDec(IDvInvocation& aInvocation)
{
    AutoMutex mutex(iLock);
    TInt maxUserBal = iVolumeManager.MaxUserBalance();
    TInt bal = iVolumeManager.UserBalance() - 1;
    if (!((-maxUserBal <= bal) && (bal <= maxUserBal))) {
        aInvocation.Error(kInvalidBalanceCode, kInvalidBalanceMsg);
    }
    iVolumeManager.SetUserBalance(bal);
    SetPropertyBalance(bal);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderVolume::Balance(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValue)
{
    AutoMutex mutex(iLock);
    TInt bal = iVolumeManager.UserBalance();
    SetPropertyBalance(bal);
    aInvocation.StartResponse();
    aValue.Write(bal);
    aInvocation.EndResponse();
}

void ProviderVolume::SetFade(IDvInvocation& aInvocation, TInt /*aValue*/)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
}

void ProviderVolume::FadeInc(IDvInvocation& aInvocation)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
}

void ProviderVolume::FadeDec(IDvInvocation& aInvocation)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
}

void ProviderVolume::Fade(IDvInvocation& aInvocation, IDvInvocationResponseInt& /*aValue*/)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
}

void ProviderVolume::SetMute(IDvInvocation& aInvocation, TBool aValue)
{
    AutoMutex mutex(iLock);
#if 0
    IMute& userMute = iMuteManager.Find("USERMUTE");  // XXX
#else
    MuteNull userMute;
#endif
    if (aValue) {
        userMute.Mute();
    } else {
        userMute.Unmute();
    }
    SetPropertyMute(aValue);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderVolume::Mute(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue)
{
    TBool propMuted = false;  // XXX enhance IMuteManager to allow query of setting
    AutoMutex mutex(iLock);
    GetPropertyMute(propMuted);
    aInvocation.StartResponse();
    aValue.Write(propMuted);
    aInvocation.EndResponse();
}

void ProviderVolume::VolumeLimit(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    AutoMutex mutex(iLock);
    TUint volLimit = iVolumeManager.UserVolumeLimit();
    SetPropertyVolumeLimit(volLimit);
    aInvocation.StartResponse();
    aValue.Write(volLimit);
    aInvocation.EndResponse();
}
