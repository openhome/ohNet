#include <OpenHome/Av/ProviderVolume.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/StringIds.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Media/MuteManager.h>
#include <OpenHome/Av/VolumeManager.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// ProviderFactory

IProvider* ProviderFactory::NewVolume(Product& aProduct,
                                      Net::DvDevice& aDevice,
                                      Configuration::IConfigManager& aConfigReader,
                                      IVolumeManager& aVolumeManager ,IVolume& aVolume,
                                      TUint aVolumeMax, TUint aVolumeUnity, TUint aVolumeStep, TUint aVolumeMilliDbPerStep,
                                      IBalance* aBalance, TUint aBalanceMax,
                                      IFade* aFade, TUint aFadeMax)
{ // static
    aProduct.AddAttribute("Volume");
    return new ProviderVolume(aDevice, aConfigReader,
                              aVolumeManager, aVolume,
                              aVolumeMax, aVolumeUnity, aVolumeStep, aVolumeMilliDbPerStep,
                              aBalance, aBalanceMax,
                              aFade, aFadeMax);
}


// from older .../Preamp/ServiceVolume.cpp
const TInt kActionNotSupportedCode = 801;
const Brn  kActionNotSupportedMsg("Action not supported");

const TInt kInvalidVolumeCode = 811;
const Brn  kInvalidVolumeMsg("Volume invalid");

const TInt kInvalidBalanceCode = 812;
const Brn  kInvalidBalanceMsg("Balance invalid");

const TInt kInvalidFadeCode = 813;
const Brn  kInvalidFadeMsg("Fade invalid");


ProviderVolume::ProviderVolume(DvDevice& aDevice,
                               IConfigManager& aConfigReader,
                               IVolumeManager& aVolumeManager ,IVolume& aVolume,
                               TUint aVolumeMax, TUint aVolumeUnity, TUint aVolumeStep, TUint aVolumeMilliDbPerStep,
                               IBalance* aBalance, TUint aBalanceMax,
                               IFade* aFade, TUint aFadeMax)
    : DvProviderAvOpenhomeOrgVolume1(aDevice)
    , iLock("PVOL")
    , iVolume(aVolume)
    , iBalance(aBalance)
    , iFade(aFade)
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
    EnablePropertyFadeMax();

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

    aVolumeManager.AddObserver(*this);

    iConfigVolumeLimit = &aConfigReader.GetNum(VolumeLimiter::kConfigKey);
    iSubscriberIdVolumeLimit = iConfigVolumeLimit->Subscribe(MakeFunctorConfigNum(*this, &ProviderVolume::VolumeLimitChanged));
    if (iBalance == NULL) {
        iConfigBalance = NULL;
        SetPropertyBalance(0);
    }
    else {
        iConfigBalance = &aConfigReader.GetNum(BalanceUser::kConfigKey);
        iSubscriberIdBalance = iConfigBalance->Subscribe(MakeFunctorConfigNum(*this, &ProviderVolume::BalanceChanged));
    }
    if (iFade == NULL) {
        iConfigFade = NULL;
        SetPropertyFade(0);
    }
    else {
        iConfigFade = &aConfigReader.GetNum(FadeUser::kConfigKey);
        iSubscriberIdFade = iConfigFade->Subscribe(MakeFunctorConfigNum(*this, &ProviderVolume::FadeChanged));
    }

    SetPropertyMute(false); // FIXME
    SetPropertyVolumeMax(aVolumeMax);
    SetPropertyVolumeUnity(aVolumeUnity);
    SetPropertyVolumeSteps(aVolumeStep);
    SetPropertyVolumeMilliDbPerStep(aVolumeMilliDbPerStep);
    SetPropertyBalanceMax(aBalanceMax);
    SetPropertyFadeMax(aFadeMax);
}

ProviderVolume::~ProviderVolume()
{
    iConfigVolumeLimit->Unsubscribe(iSubscriberIdVolumeLimit);
    if (iConfigBalance != NULL) {
        iConfigBalance->Unsubscribe(iSubscriberIdBalance);
    }
    if (iConfigFade != NULL) {
        iConfigFade->Unsubscribe(iSubscriberIdFade);
    }
}

void ProviderVolume::Characteristics(IDvInvocation& aInvocation, IDvInvocationResponseUint& aVolumeMax, IDvInvocationResponseUint& aVolumeUnity, IDvInvocationResponseUint& aVolumeSteps, IDvInvocationResponseUint& aVolumeMilliDbPerStep, IDvInvocationResponseUint& aBalanceMax, IDvInvocationResponseUint& aFadeMax)
{
    TUint maxVol = 0;
    TUint unityVol = 0;
    TUint volSteps = 0;
    TUint milliDbPerVolStep = 0;
    TUint maxBalance = 0;
    TUint maxFade = 0;

    GetPropertyVolumeMax(maxVol);
    GetPropertyVolumeUnity(unityVol);
    GetPropertyVolumeSteps(volSteps);
    GetPropertyVolumeMilliDbPerStep(milliDbPerVolStep);
    GetPropertyBalanceMax(maxBalance);
    GetPropertyFadeMax(maxFade);

    aInvocation.StartResponse();
    aVolumeMax.Write(maxVol);
    aVolumeUnity.Write(unityVol);
    aVolumeSteps.Write(volSteps);
    aVolumeMilliDbPerStep.Write(milliDbPerVolStep);
    aBalanceMax.Write(maxBalance);
    aFadeMax.Write(maxFade);
    aInvocation.EndResponse();
}

void ProviderVolume::SetVolume(IDvInvocation& aInvocation, TUint aValue)
{
    HelperSetVolume(aInvocation, aValue);
}

void ProviderVolume::VolumeInc(IDvInvocation& aInvocation)
{
    TUint volume = 0;
    GetPropertyVolume(volume);
    HelperSetVolume(aInvocation, volume+1);
}

void ProviderVolume::VolumeDec(IDvInvocation& aInvocation)
{
    TUint volume = 0;
    GetPropertyVolume(volume);
    HelperSetVolume(aInvocation, volume-1);
}

void ProviderVolume::Volume(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    TUint vol = 0;
    GetPropertyVolume(vol);
    aInvocation.StartResponse();
    aValue.Write(vol);
    aInvocation.EndResponse();
}

void ProviderVolume::SetBalance(IDvInvocation& aInvocation, TInt aValue)
{
    HelperSetBalance(aInvocation, aValue);
}

void ProviderVolume::BalanceInc(IDvInvocation& aInvocation)
{
    TInt balance = 0;
    GetPropertyBalance(balance);
    HelperSetBalance(aInvocation, balance+1);
}

void ProviderVolume::BalanceDec(IDvInvocation& aInvocation)
{
    TInt balance = 0;
    GetPropertyBalance(balance);
    HelperSetBalance(aInvocation, balance-1);
}

void ProviderVolume::Balance(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValue)
{
    TInt balance = 0;
    GetPropertyBalance(balance);
    aInvocation.StartResponse();
    aValue.Write(balance);
    aInvocation.EndResponse();
}

void ProviderVolume::SetFade(IDvInvocation& aInvocation, TInt aValue)
{
    HelperSetBalance(aInvocation, aValue);
}

void ProviderVolume::FadeInc(IDvInvocation& aInvocation)
{
    TInt fade = 0;
    GetPropertyFade(fade);
    HelperSetBalance(aInvocation, fade+1);
}

void ProviderVolume::FadeDec(IDvInvocation& aInvocation)
{
    TInt fade = 0;
    GetPropertyFade(fade);
    HelperSetBalance(aInvocation, fade+1);
}

void ProviderVolume::Fade(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValue)
{
    TInt fade = 0;
    GetPropertyFade(fade);
    aInvocation.StartResponse();
    aValue.Write(fade);
    aInvocation.EndResponse();
}

void ProviderVolume::SetMute(IDvInvocation& aInvocation, TBool /*aValue*/)
{
    aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg); // FIXME
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderVolume::Mute(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue)
{
    TBool muted = false;
    GetPropertyMute(muted);
    aInvocation.StartResponse();
    aValue.Write(muted);
    aInvocation.EndResponse();
}

void ProviderVolume::VolumeLimit(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    TUint volLimit = 0;
    GetPropertyVolumeLimit(volLimit);
    aInvocation.StartResponse();
    aValue.Write(volLimit);
    aInvocation.EndResponse();
}

void ProviderVolume::VolumeChanged(TUint aVolume)
{
    SetPropertyVolume(aVolume);
}

void ProviderVolume::HelperSetVolume(IDvInvocation& aInvocation, TUint aVolume)
{
    try {
        iVolume.SetVolume(aVolume);
    }
    catch (VolumeOutOfRange&) {
        aInvocation.Error(kInvalidVolumeCode, kInvalidVolumeMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderVolume::HelperSetBalance(IDvInvocation& aInvocation, TInt aBalance)
{
    if (iBalance == NULL) {
        aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    }
    try {
        iBalance->SetBalance(aBalance);
    }
    catch (BalanceOutOfRange&) {
        aInvocation.Error(kInvalidBalanceCode, kInvalidBalanceMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderVolume::HelperSetFade(IDvInvocation& aInvocation, TInt aFade)
{
    if (iFade == NULL) {
        aInvocation.Error(kActionNotSupportedCode, kActionNotSupportedMsg);
    }
    try {
        iFade->SetFade(aFade);
    }
    catch (FadeOutOfRange&) {
        aInvocation.Error(kInvalidFadeCode, kInvalidFadeMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderVolume::VolumeLimitChanged(ConfigNum::KvpNum& aKvp)
{
    SetPropertyVolumeLimit(aKvp.Value());
}

void ProviderVolume::BalanceChanged(ConfigNum::KvpNum& aKvp)
{
    const TInt balance = aKvp.Value();
    SetPropertyBalance(balance);
}

void ProviderVolume::FadeChanged(ConfigNum::KvpNum& aKvp)
{
    const TInt fade = aKvp.Value();
    SetPropertyFade(fade);
}
