#include <OpenHome/Av/ProviderVolume.h>

#include <OpenHome/Buffer.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

// from older .../Preamp/ServiceVolume.cpp
const TInt kInvalidSourceIndexCode = 800;
const Brn  kInvalidSourceIndexMsg("Source index invalid");

const TInt kActionNotSupportedCode = 801;
const Brn  kActionNotSupportedMsg("Action not supported");

const TInt kInvalidStringCode = 810;
const Brn  kInvalidStringMsg("String too long");

const TInt kInvalidVolumeCode = 811;
const Brn  kInvalidVolumeMsg("Volume invalid");

const TInt kInvalidBalanceCode = 812;
const Brn  kInvalidBalanceMsg("Balance invalid");

const TInt kInvalidFadeCode = 813;
const Brn  kInvalidFadeMsg("Fade invalid");

ProviderVolume::ProviderVolume(DvDevice& aDevice, IMuteManager& aMuteManager, IVolumeManagerLimits& aVolumeManager)
    : DvProviderAvOpenhomeOrgVolume1(aDevice)
    , iMuteManager(aMuteManager)
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
    SetPropertyFadeMax(0);  // fixed, since effectively unsupported (see above)

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
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
    (void) aVolumeMax;
    (void) aVolumeUnity;
    (void) aVolumeSteps;
    (void) aVolumeMilliDbPerStep;
    (void) aBalanceMax;
    (void) aFadeMax;
}

void ProviderVolume::SetVolume(IDvInvocation& aInvocation, TUint aValue)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
    (void) aValue;
}

void ProviderVolume::VolumeInc(IDvInvocation& aInvocation)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
}

void ProviderVolume::VolumeDec(IDvInvocation& aInvocation)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
}

void ProviderVolume::Volume(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
    (void) aValue;
}

void ProviderVolume::SetBalance(IDvInvocation& aInvocation, TInt aValue)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
    (void) aValue;
}

void ProviderVolume::BalanceInc(IDvInvocation& aInvocation)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
}

void ProviderVolume::BalanceDec(IDvInvocation& aInvocation)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
}

void ProviderVolume::Balance(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValue)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
    (void) aValue;
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
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
    (void) aValue;
}

void ProviderVolume::Mute(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
    (void) aValue;
}

void ProviderVolume::VolumeLimit(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    // TODO
    (void) aValue;
}
