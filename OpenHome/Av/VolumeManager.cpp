#include <OpenHome/Av/VolumeManager.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Av/StringIds.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/ProviderVolume.h>
#include <OpenHome/Media/MuteManager.h>
#include <OpenHome/Private/Printer.h>

#include <vector>
#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;

// VolumeConsumer

VolumeConsumer::VolumeConsumer()
    : iVolume(nullptr)
    , iBalance(nullptr)
    , iFade(nullptr)
{
}

void VolumeConsumer::SetVolume(IVolume& aVolume)
{
    iVolume = &aVolume;
}

void VolumeConsumer::SetBalance(IBalance& aBalance)
{
    iBalance = &aBalance;
}

void VolumeConsumer::SetFade(IFade& aFade)
{
    iFade = &aFade;
}

IVolume* VolumeConsumer::Volume()
{
    return iVolume;
}

IBalance* VolumeConsumer::Balance()
{
    return iBalance;
}

IFade* VolumeConsumer::Fade()
{
    return iFade;
}


// VolumeNull

void VolumeNull::SetVolume(TUint /*aVolume*/)
{
}


// VolumeUser

const Brn VolumeUser::kStartupVolumeKey("Startup.Volume");

VolumeUser::VolumeUser(IVolume& aVolume, IConfigManager& aConfigReader, IPowerManager& aPowerManager,
                       StoreInt& aStoreUserVolume, TUint aMaxVolume, TUint aMilliDbPerStep)
    : iVolume(aVolume)
    , iConfigStartupVolume(aConfigReader.GetNum(VolumeConfig::kKeyStartupValue))
    , iConfigStartupVolumeEnabled(aConfigReader.GetChoice(VolumeConfig::kKeyStartupEnabled))
    , iStoreUserVolume(aStoreUserVolume)
    , iMaxVolume(aMaxVolume)
    , iMilliDbPerStep(aMilliDbPerStep)
{
    iSubscriberIdStartupVolume = iConfigStartupVolume.Subscribe(MakeFunctorConfigNum(*this, &VolumeUser::StartupVolumeChanged));
    iSubscriberIdStartupVolumeEnabled = iConfigStartupVolumeEnabled.Subscribe(MakeFunctorConfigChoice(*this, &VolumeUser::StartupVolumeEnabledChanged));
    iStandbyObserver = aPowerManager.RegisterStandbyHandler(*this, kStandbyHandlerPriorityNormal);
    // StandbyDisabled will be called either inside the call above or when we later exit standby
}

VolumeUser::~VolumeUser()
{
    iConfigStartupVolume.Unsubscribe(iSubscriberIdStartupVolume);
    iConfigStartupVolumeEnabled.Unsubscribe(iSubscriberIdStartupVolumeEnabled);
}

void VolumeUser::SetVolume(TUint aVolume)
{
    if (aVolume > iMaxVolume) {
        THROW(VolumeOutOfRange);
    }
    iStoreUserVolume.Set(aVolume);
    iVolume.SetVolume(aVolume);
}

void VolumeUser::StandbyEnabled()
{
    // no need to change volume when we exit standby
}

void VolumeUser::StandbyDisabled(StandbyDisableReason /*aReason*/)
{
    TUint startupVolume;
    if (iStartupVolumeEnabled) {
        startupVolume = iStartupVolume * iMilliDbPerStep;
    }
    else {
        startupVolume = iStoreUserVolume.Get();
    }
    iVolume.SetVolume(startupVolume);
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

VolumeLimiter::VolumeLimiter(IVolume& aVolume, TUint aMilliDbPerStep, IConfigManager& aConfigReader)
    : iLock("VLMT")
    , iVolume(aVolume)
    , iMilliDbPerStep(aMilliDbPerStep)
    , iConfigLimit(aConfigReader.GetNum(VolumeConfig::kKeyLimit))
    , iUpstreamVolume(0)
{
    iSubscriberIdLimit = iConfigLimit.Subscribe(MakeFunctorConfigNum(*this, &VolumeLimiter::LimitChanged));
}

VolumeLimiter::~VolumeLimiter()
{
    iConfigLimit.Unsubscribe(iSubscriberIdLimit);
}

void VolumeLimiter::SetVolume(TUint aValue)
{
    AutoMutex _(iLock);
    if (aValue > iLimit && iUpstreamVolume >= iLimit) {
        THROW(VolumeOutOfRange);
    }
    iUpstreamVolume = aValue;
    SetVolume();
}

void VolumeLimiter::LimitChanged(ConfigNum::KvpNum& aKvp)
{
    AutoMutex _(iLock);
    iLimit = aKvp.Value() * iMilliDbPerStep;
    SetVolume();
}

void VolumeLimiter::SetVolume()
{
    const TUint volume = std::min(iUpstreamVolume, iLimit);
    iVolume.SetVolume(volume);
}


// VolumeReporter

VolumeReporter::VolumeReporter(IVolume& aVolume, TUint aMilliDbPerStep)
    : iVolume(aVolume)
    , iMilliDbPerStep(aMilliDbPerStep)
    , iUpstreamVolume(0)
{
}

void VolumeReporter::AddVolumeObserver(IVolumeObserver& aObserver)
{
    aObserver.VolumeChanged(iUpstreamVolume / iMilliDbPerStep);
    iObservers.push_back(&aObserver);
}

void VolumeReporter::SetVolume(TUint aVolume)
{
    iUpstreamVolume = aVolume;
    const TUint volume = iUpstreamVolume / iMilliDbPerStep;
    for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
        (*it)->VolumeChanged(volume);
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
    TUint volume = iUpstreamVolume + iSourceOffset;
    if (volume > iUpstreamVolume && iSourceOffset < 0) {
        volume = 0;
    }
    else if (volume < iUpstreamVolume && iSourceOffset > 0) {
        volume= iUpstreamVolume;
    }
    iVolume.SetVolume(volume);
}


// VolumeUnityGainBase

VolumeUnityGainBase::VolumeUnityGainBase(IVolume& aVolume, TUint aUnityGainValue)
    : iLock("VUGN")
    , iVolume(aVolume)
    , iUnityGain(aUnityGainValue)
    , iUpstreamVolume(0)
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

VolumeUnityGain::VolumeUnityGain(IVolume& aVolume, IConfigManager& aConfigReader, TUint aUnityGainValue)
    : VolumeUnityGainBase(aVolume, aUnityGainValue)
    , iConfigVolumeControlEnabled(aConfigReader.GetChoice(VolumeConfig::kKeyEnabled))
{
    iSubscriberId = iConfigVolumeControlEnabled.Subscribe(MakeFunctorConfigChoice(*this, &VolumeUnityGain::EnabledChanged));
}

VolumeUnityGain::~VolumeUnityGain()
{
    iConfigVolumeControlEnabled.Unsubscribe(iSubscriberId);
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
    SetEnabled(true);
}

void VolumeSourceUnityGain::SetUnityGain(TBool aEnable)
{
    SetEnabled(!aEnable);
}


// AnalogBypassRamper

AnalogBypassRamper::AnalogBypassRamper(IVolume& aVolume)
    : iVolume(aVolume)
    , iLock("ABVR")
    , iUpstreamVolume(0)
    , iMultiplier(IAnalogBypassVolumeRamper::kMultiplierFull)
{
}

void AnalogBypassRamper::SetVolume(TUint aValue)
{
    AutoMutex _(iLock);
    iUpstreamVolume = aValue;
    SetVolume();
}

void AnalogBypassRamper::ApplyVolumeMultiplier(TUint aValue)
{
    AutoMutex _(iLock);
    if (iMultiplier == aValue) {
        return;
    }
    iMultiplier = aValue;
    SetVolume();
}

void AnalogBypassRamper::SetVolume()
{
    if (iMultiplier == IAnalogBypassVolumeRamper::kMultiplierFull) {
        iVolume.SetVolume(iUpstreamVolume);
    }
    else {
        TUint64 volume = iUpstreamVolume;
        volume *= iMultiplier;
        volume /= IAnalogBypassVolumeRamper::kMultiplierFull;
        iVolume.SetVolume((TUint)volume);
    }
}


// BalanceUser

BalanceUser::BalanceUser(IBalance& aBalance, IConfigManager& aConfigReader)
    : iBalance(aBalance)
    , iConfigBalance(aConfigReader.GetNum(VolumeConfig::kKeyBalance))
{
    iSubscriberIdBalance = iConfigBalance.Subscribe(MakeFunctorConfigNum(*this, &BalanceUser::BalanceChanged));
}

BalanceUser::~BalanceUser()
{
    iConfigBalance.Unsubscribe(iSubscriberIdBalance);
}

void BalanceUser::SetBalance(TInt aBalance)
{
    try {
        iConfigBalance.Set(aBalance);
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

FadeUser::FadeUser(IFade& aFade, IConfigManager& aConfigReader)
    : iFade(aFade)
    , iConfigFade(aConfigReader.GetNum(VolumeConfig::kKeyFade))
{
    iSubscriberIdFade = iConfigFade.Subscribe(MakeFunctorConfigNum(*this, &FadeUser::FadeChanged));
}

FadeUser::~FadeUser()
{
    iConfigFade.Unsubscribe(iSubscriberIdFade);
}

void FadeUser::SetFade(TInt aFade)
{
    try {
        iConfigFade.Set(aFade);
    }
    catch (ConfigValueOutOfRange&) {
        THROW(FadeOutOfRange);
    }
}

void FadeUser::FadeChanged(ConfigNum::KvpNum& aKvp)
{
    iFade.SetFade(aKvp.Value());
}


// MuteUser

MuteUser::MuteUser(Media::IMute& aMute, StoreInt& aStoreUserMute)
    : iMute(aMute)
    , iStoreUserMute(aStoreUserMute)
{
    if (iStoreUserMute.Get() == VolumeConfig::kValueMuted) {
        iMute.Mute();
    }
    else {
        iMute.Unmute();
    }
}

void MuteUser::Mute()
{
    iStoreUserMute.Set(VolumeConfig::kValueMuted);
    iMute.Mute();
}

void MuteUser::Unmute()
{
    iStoreUserMute.Set(VolumeConfig::kValueUnmuted);
    iMute.Unmute();
}


// MuteReporter

MuteReporter::MuteReporter(Media::IMute& aMute)
    : iMute(aMute)
    , iMuted(false)
{
}

void MuteReporter::AddMuteObserver(Media::IMuteObserver& aObserver)
{
    aObserver.MuteChanged(iMuted);
    iObservers.push_back(&aObserver);
}

void MuteReporter::Mute()
{
    if (Report(true)) {
        iMute.Mute();
    }
}

void MuteReporter::Unmute()
{
    if (Report(false)) {
        iMute.Unmute();
    }
}

TBool MuteReporter::Report(TBool aMuted)
{
    if (aMuted == iMuted) {
        return false;
    }
    iMuted = aMuted;
    for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
        (*it)->MuteChanged(iMuted);
    }
    return true;
}


// VolumeConfig

const Brn VolumeConfig::kKeyStartupVolume("Last.Volume");
const Brn VolumeConfig::kKeyStartupMute("Last.Mute");
const Brn VolumeConfig::kKeyStartupValue("Volume.StartupValue");
const Brn VolumeConfig::kKeyStartupEnabled("Volume.StartupEnabled");
const Brn VolumeConfig::kKeyLimit("Volume.Limit");
const Brn VolumeConfig::kKeyEnabled("Volume.Enabled");
const Brn VolumeConfig::kKeyBalance("Volume.Balance");
const Brn VolumeConfig::kKeyFade("Volume.Fade");

VolumeConfig::VolumeConfig(IStoreReadWrite& aStore, IConfigInitialiser& aConfigInit, IPowerManager& aPowerManager, const IVolumeProfile& aProfile)
    : iStoreUserVolume(aStore, aPowerManager, kPowerPriorityHighest, kKeyStartupVolume, aProfile.VolumeDefault())
    , iStoreUserMute(aStore, aPowerManager, kPowerPriorityHighest, kKeyStartupMute, kValueUnmuted)
{
    iVolumeMax            = aProfile.VolumeMax();
    iVolumeDefault        = aProfile.VolumeDefault();
    iVolumeUnity          = aProfile.VolumeUnity();
    iVolumeDefaultLimit   = aProfile.VolumeDefaultLimit();
    iVolumeStep           = aProfile.VolumeStep();
    iVolumeMilliDbPerStep = aProfile.VolumeMilliDbPerStep();
    iBalanceMax           = aProfile.BalanceMax();
    iFadeMax              = aProfile.FadeMax();

    iVolumeStartup = new ConfigNum(aConfigInit, kKeyStartupValue, 0, iVolumeMax, iVolumeDefault);
    std::vector<TUint> choices;
    choices.push_back(eStringIdYes);
    choices.push_back(eStringIdNo);
    iVolumeStartupEnabled = new ConfigChoice(aConfigInit, kKeyStartupEnabled, choices, eStringIdYes);
    iVolumeLimit = new ConfigNum(aConfigInit, kKeyLimit, 0, iVolumeMax, iVolumeDefaultLimit);
    iVolumeEnabled = new ConfigChoice(aConfigInit, kKeyEnabled, choices, eStringIdYes);

    const TUint id = iVolumeEnabled->Subscribe(MakeFunctorConfigChoice(*this, &VolumeConfig::EnabledChanged));
    // EnabledChanged runs inside the call to Subscribe().
    // We don't support runtime change of this value so can immediately unsubscribe.
    iVolumeEnabled->Unsubscribe(id);

    const TInt maxBalance = iBalanceMax;
    if (maxBalance == 0) {
        iBalance = nullptr;
    }
    else {
        iBalance = new ConfigNum(aConfigInit, kKeyBalance, -maxBalance, maxBalance, 0);
    }
    const TInt maxFade = iFadeMax;
    if (maxFade == 0) {
        iFade = nullptr;
    }
    else {
        iFade = new ConfigNum(aConfigInit, kKeyFade, -maxFade, maxFade, 0);
    }
}

VolumeConfig::~VolumeConfig()
{
    delete iVolumeStartup;
    delete iVolumeStartupEnabled;
    delete iVolumeLimit;
    delete iVolumeEnabled;
    delete iBalance;
    delete iFade;
}

StoreInt& VolumeConfig::StoreUserVolume()
{
    return iStoreUserVolume;
}

StoreInt& VolumeConfig::StoreUserMute()
{
    return iStoreUserMute;
}

TBool VolumeConfig::VolumeControlEnabled() const
{
    return iVolumeControlEnabled;
}

TUint VolumeConfig::VolumeMax() const
{
    return iVolumeMax;
}

TUint VolumeConfig::VolumeDefault() const
{
    return iVolumeDefault;
}

TUint VolumeConfig::VolumeUnity() const
{
    return iVolumeUnity;
}

TUint VolumeConfig::VolumeDefaultLimit() const
{
    return iVolumeDefaultLimit;
}

TUint VolumeConfig::VolumeStep() const
{
    return iVolumeStep;
}

TUint VolumeConfig::VolumeMilliDbPerStep() const
{
    return iVolumeMilliDbPerStep;
}

TUint VolumeConfig::BalanceMax() const
{
    return iBalanceMax;
}

TUint VolumeConfig::FadeMax() const
{
    return iFadeMax;
}

void VolumeConfig::EnabledChanged(Configuration::ConfigChoice::KvpChoice& aKvp)
{
    iVolumeControlEnabled = (aKvp.Value() == eStringIdYes);
}


// VolumeManager

VolumeManager::VolumeManager(VolumeConsumer& aVolumeConsumer, IMute* aMute, VolumeConfig& aVolumeConfig,
                             Net::DvDevice& aDevice, Product& aProduct, IConfigManager& aConfigReader,
                             IPowerManager& aPowerManager)
    : iVolumeConfig(aVolumeConfig)
{
    IBalance* balance = aVolumeConsumer.Balance();
    if (balance == nullptr) {
        iBalanceUser = nullptr;
    }
    else {
        iBalanceUser = new BalanceUser(*balance, aConfigReader);
    }
    IFade* fade = aVolumeConsumer.Fade();
    if (fade == nullptr) {
        iFadeUser = nullptr;
    }
    else {
        iFadeUser = new FadeUser(*fade, aConfigReader);
    }
    if (aMute == nullptr) {
        iMuteReporter = nullptr;
        iMuteUser = nullptr;
    }
    else {
        iMuteReporter = new MuteReporter(*aMute);
        iMuteUser = new MuteUser(*iMuteReporter, aVolumeConfig.StoreUserMute());
    }
    iAnalogBypassRamper = new AnalogBypassRamper(*aVolumeConsumer.Volume());
    if (aVolumeConfig.VolumeControlEnabled() && aVolumeConsumer.Volume() != nullptr) {
        const TUint milliDbPerStep = iVolumeConfig.VolumeMilliDbPerStep();
        const TUint volumeUnity = iVolumeConfig.VolumeUnity() * milliDbPerStep;
        iVolumeSourceUnityGain = new VolumeSourceUnityGain(*iAnalogBypassRamper, volumeUnity);
        iVolumeUnityGain = new VolumeUnityGain(*iVolumeSourceUnityGain, aConfigReader, volumeUnity);
        iVolumeSourceOffset = new VolumeSourceOffset(*iVolumeUnityGain);
        iVolumeReporter = new VolumeReporter(*iVolumeSourceOffset, milliDbPerStep);
        iVolumeLimiter = new VolumeLimiter(*iVolumeReporter, milliDbPerStep, aConfigReader);
        iVolumeUser = new VolumeUser(*iVolumeLimiter, aConfigReader, aPowerManager,
                                     aVolumeConfig.StoreUserVolume(),
                                     iVolumeConfig.VolumeMax() * milliDbPerStep, milliDbPerStep);
        iProviderVolume = new ProviderVolume(aDevice, aConfigReader, *this, iBalanceUser, iFadeUser);
        aProduct.AddAttribute("Volume");
    }
    else {
        iVolumeSourceUnityGain = nullptr;
        iVolumeUnityGain = nullptr;
        iVolumeSourceOffset = nullptr;
        iVolumeReporter = nullptr;
        iVolumeLimiter = nullptr;
        iVolumeUser = nullptr;
        iProviderVolume = nullptr;
    }
}

VolumeManager::~VolumeManager()
{
    delete iProviderVolume;
    delete iMuteReporter;
    delete iMuteUser;
    delete iFadeUser;
    delete iBalanceUser;
    delete iVolumeUser;
    delete iVolumeLimiter;
    delete iVolumeReporter;
    delete iVolumeSourceOffset;
    delete iVolumeUnityGain;
    delete iVolumeSourceUnityGain;
    delete iAnalogBypassRamper;
}

void VolumeManager::AddVolumeObserver(IVolumeObserver& aObserver)
{
    if (iVolumeReporter == nullptr) {
        aObserver.VolumeChanged(0);
    }
    else {
        iVolumeReporter->AddVolumeObserver(aObserver);
    }
}

void VolumeManager::AddMuteObserver(Media::IMuteObserver& aObserver)
{
    if (iMuteReporter == nullptr) {
        aObserver.MuteChanged(false);
    }
    else {
        iMuteReporter->AddMuteObserver(aObserver);
    }
}

void VolumeManager::SetVolumeOffset(TInt aValue)
{
    if (iVolumeSourceOffset != nullptr) {
        iVolumeSourceOffset->SetVolumeOffset(aValue);
    }
}

void VolumeManager::SetUnityGain(TBool aEnable)
{
    if (iVolumeSourceUnityGain != nullptr) {
        iVolumeSourceUnityGain->SetUnityGain(aEnable);
    }
}

TUint VolumeManager::VolumeMax() const
{
    return iVolumeConfig.VolumeMax();
}

TUint VolumeManager::VolumeDefault() const
{
    return iVolumeConfig.VolumeDefault();
}

TUint VolumeManager::VolumeUnity() const
{
    return iVolumeConfig.VolumeUnity();
}

TUint VolumeManager::VolumeDefaultLimit() const
{
    return iVolumeConfig.VolumeDefaultLimit();
}

TUint VolumeManager::VolumeStep() const
{
    return iVolumeConfig.VolumeStep();
}

TUint VolumeManager::VolumeMilliDbPerStep() const
{
    return iVolumeConfig.VolumeMilliDbPerStep();
}

TUint VolumeManager::BalanceMax() const
{
    return iVolumeConfig.BalanceMax();
}

TUint VolumeManager::FadeMax() const
{
    return iVolumeConfig.FadeMax();
}

void VolumeManager::SetVolume(TUint aValue)
{
    if (iVolumeUser == nullptr) {
        THROW(VolumeNotSupported);
    }

    // OpenHome Volume service is expected to unmute
    // UPnP AV RenderingControl doesn't want to unmute but that seems ill-considered
    // unmute here to both sources of volume changes the same behaviour
    if (iMuteUser != nullptr) {
        iMuteUser->Unmute();
    }
    
    const TUint volume = aValue * iVolumeConfig.VolumeMilliDbPerStep();
    iVolumeUser->SetVolume(volume);
}

void VolumeManager::SetBalance(TInt aBalance)
{
    if (iBalanceUser == nullptr) {
        THROW(BalanceNotSupported);
    }
    iBalanceUser->SetBalance(aBalance);
}

void VolumeManager::SetFade(TInt aFade)
{
    if (iFadeUser == nullptr) {
        THROW(FadeNotSupported);
    }
    iFadeUser->SetFade(aFade);
}

void VolumeManager::ApplyVolumeMultiplier(TUint aValue)
{
    static_cast<IAnalogBypassVolumeRamper*>(iAnalogBypassRamper)->ApplyVolumeMultiplier(aValue);
}

void VolumeManager::Mute()
{
    if (iMuteUser == nullptr) {
        THROW(MuteNotSupported);
    }
    iMuteUser->Mute();
}

void VolumeManager::Unmute()
{
    if (iMuteUser == nullptr) {
        THROW(MuteNotSupported);
    }
    iMuteUser->Unmute();
}


// VolumeScaler

VolumeScaler::VolumeScaler(IVolumeReporter& aVolumeReporter, IVolumeSourceOffset& aVolumeOffset, TUint aVolMaxUser, TUint aVolMaxExternal)
    : iVolumeOffset(aVolumeOffset)
    , iVolMaxUser(aVolMaxUser)
    , iVolMaxExternal(aVolMaxExternal)
    , iEnabled(false)
    , iVolUser(0)
    , iVolExternal(0)
    , iLock("VSCL")
{
    // Check there is no overflow if max values of both ranges are multiplied together.
    const TUint prod = iVolMaxUser * iVolMaxExternal;
    const TUint div = prod/iVolMaxUser;
    ASSERT(div == iVolMaxExternal);
    aVolumeReporter.AddVolumeObserver(*this);
}

void VolumeScaler::SetVolume(TUint aVolume)
{
    ASSERT(aVolume <= iVolMaxExternal);
    // Scale volume to within range of system volume.
    AutoMutex a(iLock);
    iVolExternal = aVolume;
    if (iEnabled) {
        UpdateOffsetLocked();
    }
}

void VolumeScaler::SetVolumeEnabled(TBool aEnabled)
{
    AutoMutex a(iLock);
    if (aEnabled) {
        if (iEnabled != aEnabled) {
            iEnabled = aEnabled;
            UpdateOffsetLocked();
        }
    }
    else {
        if (iEnabled != aEnabled) {
            iEnabled = aEnabled;
            iVolumeOffset.SetVolumeOffset(0);
        }
    }
}

void VolumeScaler::VolumeChanged(TUint aVolume)
{
    ASSERT(aVolume <= iVolMaxUser);
    AutoMutex a(iLock);
    iVolUser = aVolume;
    if (iEnabled) {
        UpdateOffsetLocked();
    }
}

void VolumeScaler::UpdateOffsetLocked()
{
    // Already know from check in constructor that this can't overflow.
    const TUint volProd = iVolExternal*iVolUser;

    const TUint vol = volProd / iVolMaxExternal;
    ASSERT(iVolUser >= vol);    // Scaled vol must be within user vol.
    const TInt offset = (iVolUser - vol) * -1;

    iVolumeOffset.SetVolumeOffset(offset);
}
