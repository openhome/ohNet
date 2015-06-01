#include <OpenHome/Av/VolumeManager.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Av/StringIds.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/ProviderVolume.h>

#include <vector>
#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;

// VolumeInitParams

VolumeInitParams::VolumeInitParams()
    : iVolume(NULL) 
    , iVolumeMax(0)
    , iVolumeDefault(0)
    , iVolumeUnity(0)
    , iVolumeDefaultLimit(0)
    , iVolumeStep(0)
    , iVolumeMilliDbPerStep(0)
    , iBalance(NULL)
    , iBalanceMax(0)
    , iFade(NULL)
    , iFadeMax(0)
{
}

void VolumeInitParams::SetVolume(IVolume& aVolume, TUint aVolumeMax, TUint aVolumeDefault, TUint aVolumeUnity, TUint aDefaultLimit, TUint aVolumeStep, TUint aVolumeMilliDbPerStep)
{
    iVolume               = &aVolume; 
    iVolumeMax            = aVolumeMax;
    iVolumeDefault        = aVolumeDefault;
    iVolumeUnity          = aVolumeUnity;
    iVolumeDefaultLimit   = aDefaultLimit;
    iVolumeStep           = aVolumeStep;
    iVolumeMilliDbPerStep = aVolumeMilliDbPerStep;
}

void VolumeInitParams::SetBalance(IBalance& aBalance, TUint aBalanceMax)
{
    iBalance    = &aBalance;
    iBalanceMax = aBalanceMax;
}

void VolumeInitParams::SetFade(IFade& aFade, TUint aFadeMax)
{
    iFade    = &aFade;
    iFadeMax = aFadeMax;
}


// VolumeUser

const Brn VolumeUser::kStartupVolumeKey("Startup.Volume");
const Brn VolumeUser::kConfigKeyStartup("Volume.StartupValue");
const Brn VolumeUser::kConfigKeyStartupEnabled("Volume.StartupEnabled");

VolumeUser::VolumeUser(IVolume& aVolume, IStoreReadWrite& aStore, IConfigInitialiser& aConfigInit, IPowerManager& aPowerManager, TUint aMaxVolume, TUint aDefaultVolume)
    : iVolume(aVolume)
    , iStoreUserVolume(aStore, aPowerManager, kPowerPriorityHighest, kStartupVolumeKey, aDefaultVolume)
    , iMaxVolume(aMaxVolume)
{
    iConfigStartupVolume = new ConfigNum(aConfigInit, kConfigKeyStartup, 0, aMaxVolume, aDefaultVolume);
    iSubscriberIdStartupVolume = iConfigStartupVolume->Subscribe(MakeFunctorConfigNum(*this, &VolumeUser::StartupVolumeChanged));
    std::vector<TUint> choices;
    choices.push_back(eStringIdYes);
    choices.push_back(eStringIdNo);
    iConfigStartupVolumeEnabled = new ConfigChoice(aConfigInit, kConfigKeyStartupEnabled, choices, eStringIdNo);
    iSubscriberIdStartupVolumeEnabled = iConfigStartupVolumeEnabled->Subscribe(MakeFunctorConfigChoice(*this, &VolumeUser::StartupVolumeEnabledChanged));

    const TUint startupVolume = (iStartupVolumeEnabled? iStartupVolume : iStoreUserVolume.Get());
    iVolume.SetVolume(startupVolume);
}

VolumeUser::~VolumeUser()
{
    iConfigStartupVolume->Unsubscribe(iSubscriberIdStartupVolume);
    iConfigStartupVolumeEnabled->Unsubscribe(iSubscriberIdStartupVolumeEnabled);
}

void VolumeUser::SetVolume(TUint aVolume)
{
    if (aVolume > iMaxVolume) {
        THROW(VolumeOutOfRange);
    }
    iStoreUserVolume.Set(aVolume);
    iVolume.SetVolume(aVolume);
}

void VolumeUser::StartupVolumeChanged(ConfigNum::KvpNum& aKvp)
{
    iStartupVolume = aKvp.Value();
}

void VolumeUser::StartupVolumeEnabledChanged(ConfigChoice::KvpChoice& aKvp)
{
    iStartupVolumeEnabled = (aKvp.Value() == eStringIdYes);
}


// VolumeLimiter

const Brn VolumeLimiter::kConfigKey("Volume.Limit");

VolumeLimiter::VolumeLimiter(IVolume& aVolume, IConfigInitialiser& aConfigInit, TUint aDefaultLimit, TUint aMaxVolume)
    : iLock("VLMT")
    , iVolume(aVolume)
    , iUpstreamVolume(0)
{
    iConfigLimit = new ConfigNum(aConfigInit, kConfigKey, 0, aMaxVolume, aDefaultLimit);
    iSubscriberIdLimit = iConfigLimit->Subscribe(MakeFunctorConfigNum(*this, &VolumeLimiter::LimitChanged));
}

VolumeLimiter::~VolumeLimiter()
{
    iConfigLimit->Unsubscribe(iSubscriberIdLimit);
}

void VolumeLimiter::SetVolume(TUint aValue)
{
    AutoMutex _(iLock);
    iUpstreamVolume = aValue;
    SetVolume();
}

void VolumeLimiter::LimitChanged(ConfigNum::KvpNum& aKvp)
{
    AutoMutex _(iLock);
    iLimit = aKvp.Value();
    SetVolume();
}

void VolumeLimiter::SetVolume()
{
    const TUint volume = std::min(iUpstreamVolume, iLimit);
    iVolume.SetVolume(volume);
}


// VolumeReporter

VolumeReporter::VolumeReporter(IVolume& aVolume)
    : iVolume(aVolume)
    , iUpstreamVolume(0)
{
}

void VolumeReporter::AddObserver(IVolumeObserver& aObserver)
{
    aObserver.VolumeChanged(iUpstreamVolume);
    iObservers.push_back(&aObserver);
}

void VolumeReporter::SetVolume(TUint aVolume)
{
    iUpstreamVolume = aVolume;
    for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
        (*it)->VolumeChanged(aVolume);
    }
    iVolume.SetVolume(aVolume);
}


// VolumeSourceOffset

VolumeSourceOffset::VolumeSourceOffset(IVolume& aVolume)
    : iLock("VSOF")
    , iVolume(aVolume)
    , iUpstreamVolume(0)
    , iSourceOffset(0)
{
}

void VolumeSourceOffset::SetVolume(TUint aValue)
{
    AutoMutex _(iLock);
    iUpstreamVolume = aValue;
    SetVolume();
}

void VolumeSourceOffset::SetVolumeOffset(TInt aOffset)
{
    AutoMutex _(iLock);
    iSourceOffset = aOffset;
    SetVolume();
}

void VolumeSourceOffset::SetVolume()
{
    const TUint volume = iUpstreamVolume + iSourceOffset;
    iVolume.SetVolume(volume);
}


// VolumeUnityGainBase

VolumeUnityGainBase::VolumeUnityGainBase(IVolume& aVolume, TUint aUnityGainValue)
    : iLock("VUGN")
    , iVolume(aVolume)
    , iUnityGain(aUnityGainValue)
{
}

void VolumeUnityGainBase::SetVolume(TUint aValue)
{
    AutoMutex _(iLock);
    iUpstreamVolume = aValue;
    if (iVolumeControlEnabled) {
        iVolume.SetVolume(aValue);
    }
}

void VolumeUnityGainBase::SetEnabled(TBool aEnabled)
{
    AutoMutex _(iLock);
    iVolumeControlEnabled = aEnabled;
    if (iVolumeControlEnabled) {
        iVolume.SetVolume(iUpstreamVolume);
    }
    else {
        iVolume.SetVolume(iUnityGain);
    }
}

// VolumeUnityGain

const Brn VolumeUnityGain::kConfigKey("Volume.Enabled");

VolumeUnityGain::VolumeUnityGain(IVolume& aVolume, IConfigInitialiser& aConfigInit, TUint aUnityGainValue)
    : VolumeUnityGainBase(aVolume, aUnityGainValue)
{
    std::vector<TUint> choices;
    choices.push_back(eStringIdYes);
    choices.push_back(eStringIdNo);
    iConfigVolumeControlEnabled = new ConfigChoice(aConfigInit, kConfigKey, choices, eStringIdYes);
    iSubscriberId = iConfigVolumeControlEnabled->Subscribe(MakeFunctorConfigChoice(*this, &VolumeUnityGain::EnabledChanged));
}

VolumeUnityGain::~VolumeUnityGain()
{
    iConfigVolumeControlEnabled->Unsubscribe(iSubscriberId);
}

void VolumeUnityGain::EnabledChanged(ConfigChoice::KvpChoice& aKvp)
{
    const TBool enabled = (aKvp.Value() == eStringIdYes);
    SetEnabled(enabled);
}


// VolumeSourceUnityGain

VolumeSourceUnityGain::VolumeSourceUnityGain(IVolume& aVolume, TUint aUnityGainValue)
    : VolumeUnityGainBase(aVolume, aUnityGainValue)
{
}

void VolumeSourceUnityGain::SetUnityGain(TBool aEnable)
{
    SetEnabled(!aEnable);
}


// BalanceUser

const Brn BalanceUser::kConfigKey("Volume.Balance");

BalanceUser::BalanceUser(IBalance& aBalance, IConfigInitialiser& aConfigInit, TInt aDefault, TUint aMax)
    : iBalance(aBalance)
{
    iConfigBalance = new ConfigNum(aConfigInit, kConfigKey, -(TInt)aMax, aMax, aDefault);
    iSubscriberIdBalance = iConfigBalance->Subscribe(MakeFunctorConfigNum(*this, &BalanceUser::BalanceChanged));
}

BalanceUser::~BalanceUser()
{
    iConfigBalance->Unsubscribe(iSubscriberIdBalance);
}

void BalanceUser::SetBalance(TInt aBalance)
{
    try {
        iConfigBalance->Set(aBalance);
    }
    catch (ConfigValueOutOfRange&) {
        THROW(BalanceOutOfRange);
    }
}

void BalanceUser::BalanceChanged(ConfigNum::KvpNum& aKvp)
{
    iBalance.SetBalance(aKvp.Value());
}


// FadeUser

const Brn FadeUser::kConfigKey("Volume.Fade");

FadeUser::FadeUser(IFade& aFade, IConfigInitialiser& aConfigInit, TInt aDefault, TUint aMax)
    : iFade(aFade)
{
    iConfigFade = new ConfigNum(aConfigInit, kConfigKey, -(TInt)aMax, aMax, aDefault);
    iSubscriberIdFade = iConfigFade->Subscribe(MakeFunctorConfigNum(*this, &FadeUser::FadeChanged));
}

FadeUser::~FadeUser()
{
    iConfigFade->Unsubscribe(iSubscriberIdFade);
}

void FadeUser::SetFade(TInt aFade)
{
    try {
        iConfigFade->Set(aFade);
    }
    catch (ConfigValueOutOfRange&) {
        THROW(FadeOutOfRange);
    }
}

void FadeUser::FadeChanged(ConfigNum::KvpNum& aKvp)
{
    iFade.SetFade(aKvp.Value());
}


// VolumeManager

VolumeManager::VolumeManager(const VolumeInitParams& aInitParams, IStoreReadWrite& aStore, IConfigInitialiser& aConfigInit,
                             IPowerManager& aPowerManager, Net::DvDevice& aDevice, Product& aProduct,
                             Configuration::IConfigManager& aConfigReader)
{
    if (aInitParams.iBalance == NULL) {
        iBalanceUser = NULL;
    }
    else {
        iBalanceUser = new BalanceUser(*aInitParams.iBalance, aConfigInit, 0, aInitParams.iBalanceMax);
    }
    if (aInitParams.iFade == NULL) {
        iFadeUser = NULL;
    }
    else {
        iFadeUser = new FadeUser(*aInitParams.iFade, aConfigInit, 0, aInitParams.iFadeMax);
    }
    if (aInitParams.iVolume == NULL) {
        iVolumeSourceUnityGain = NULL;
        iVolumeUnityGain = NULL;
        iVolumeSourceOffset = NULL;
        iVolumeReporter = NULL;
        iVolumeLimiter = NULL;
        iVolumeUser = NULL;
        iProviderVolume = NULL;
    }
    else {
        iVolumeSourceUnityGain = new VolumeSourceUnityGain(*aInitParams.iVolume, aInitParams.iVolumeUnity);
        iVolumeUnityGain = new VolumeUnityGain(*iVolumeSourceUnityGain, aConfigInit, aInitParams.iVolumeUnity);
        iVolumeSourceOffset = new VolumeSourceOffset(*iVolumeUnityGain);
        iVolumeReporter = new VolumeReporter(*iVolumeSourceOffset);
        iVolumeLimiter = new VolumeLimiter(*iVolumeReporter, aConfigInit, aInitParams.iVolumeDefaultLimit, aInitParams.iVolumeMax);
        iVolumeUser = new VolumeUser(*iVolumeLimiter, aStore, aConfigInit, aPowerManager, aInitParams.iVolumeMax, aInitParams.iVolumeDefault);
        // FIXME - missing a store item saying whether we were muted on last power down (used to be in ProviderVolume)
        iProviderVolume = new ProviderVolume(aDevice, aConfigReader, *this, *this,
                                             aInitParams.iVolumeMax, aInitParams.iVolumeUnity,
                                             aInitParams.iVolumeStep, aInitParams.iVolumeMilliDbPerStep,
                                             this, aInitParams.iBalanceMax,
                                             this, aInitParams.iFadeMax);
        aProduct.AddAttribute("Volume");
    }
}

VolumeManager::~VolumeManager()
{
    delete iProviderVolume;
    delete iFadeUser;
    delete iBalanceUser;
    delete iVolumeUser;
    delete iVolumeLimiter;
    delete iVolumeReporter;
    delete iVolumeSourceOffset;
    delete iVolumeUnityGain;
    delete iVolumeSourceUnityGain;
}

void VolumeManager::AddObserver(IVolumeObserver& aObserver)
{
    if (iVolumeReporter == NULL) {
        aObserver.VolumeChanged(0);
    }
    else {
        iVolumeReporter->AddObserver(aObserver);
    }
}

void VolumeManager::SetVolumeOffset(TInt aValue)
{
    if (iVolumeSourceOffset != NULL) {
        iVolumeSourceOffset->SetVolumeOffset(aValue);
    }
}

void VolumeManager::SetUnityGain(TBool aEnable)
{
    if (iVolumeSourceUnityGain != NULL) {
        iVolumeSourceUnityGain->SetUnityGain(aEnable);
    }
}

void VolumeManager::SetVolume(TUint aValue)
{
    if (iVolumeUser == NULL) {
        THROW(VolumeNotSupported);
    }
    iVolumeUser->SetVolume(aValue);
}

void VolumeManager::SetBalance(TInt aBalance)
{
    if (iBalanceUser == NULL) {
        THROW(BalanceNotSupported);
    }
    iBalanceUser->SetBalance(aBalance);
}

void VolumeManager::SetFade(TInt aFade)
{
    if (iFadeUser == NULL) {
        THROW(FadeNotSupported);
    }
    iFadeUser->SetFade(aFade);
}
