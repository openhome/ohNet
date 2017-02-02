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
#include <OpenHome/Av/Debug.h>

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
    , iVolumeOffsetter(nullptr)
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

void VolumeConsumer::SetVolumeOffsetter(IVolumeOffsetter& aVolumeOffsetter)
{
    iVolumeOffsetter = &aVolumeOffsetter;
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

IVolumeOffsetter* VolumeConsumer::VolumeOffsetter()
{
    return iVolumeOffsetter;
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
    , iStartupVolumeReported(false)
    , iMaxVolume(aMaxVolume)
    , iMilliDbPerStep(aMilliDbPerStep)
{
    iSubscriberIdStartupVolume = iConfigStartupVolume.Subscribe(MakeFunctorConfigNum(*this, &VolumeUser::StartupVolumeChanged));
    iSubscriberIdStartupVolumeEnabled = iConfigStartupVolumeEnabled.Subscribe(MakeFunctorConfigChoice(*this, &VolumeUser::StartupVolumeEnabledChanged));
    iStandbyObserver = aPowerManager.RegisterStandbyHandler(*this, kStandbyHandlerPriorityNormal, "VolumeUser");
    if (!iStartupVolumeReported) {
        ApplyStartupVolume(); // set volume immediately to avoid reporting volume==0 until we exit standby
    }
}

VolumeUser::~VolumeUser()
{
    delete iStandbyObserver;
    iConfigStartupVolume.Unsubscribe(iSubscriberIdStartupVolume);
    iConfigStartupVolumeEnabled.Unsubscribe(iSubscriberIdStartupVolumeEnabled);
}

void VolumeUser::SetVolume(TUint aVolume)
{
    LOG(kVolume, "VolumeUser::SetVolume aVolume: %u\n", aVolume);
    if (aVolume > iMaxVolume) {
        THROW(VolumeOutOfRange);
    }
    iVolume.SetVolume(aVolume);
    iStoreUserVolume.Set(aVolume);
}

void VolumeUser::StandbyEnabled()
{
    // no need to change volume when we enter standby
}

void VolumeUser::StandbyDisabled(StandbyDisableReason /*aReason*/)
{
    ApplyStartupVolume();
}

void VolumeUser::StartupVolumeChanged(ConfigNum::KvpNum& aKvp)
{
    iStartupVolume = aKvp.Value();
}

void VolumeUser::StartupVolumeEnabledChanged(ConfigChoice::KvpChoice& aKvp)
{
    iStartupVolumeEnabled = (aKvp.Value() == eStringIdYes);
}

void VolumeUser::ApplyStartupVolume()
{
    TUint startupVolume;
    if (iStartupVolumeEnabled) {
        startupVolume = iStartupVolume * iMilliDbPerStep;
    }
    else {
        startupVolume = iStoreUserVolume.Get();
    }

    try {
        iVolume.SetVolume(startupVolume);
        iStartupVolumeReported = true;
    }
    catch (VolumeNotSupported&) {}
    catch (VolumeOutOfRange&) {} // ignore any errors caused by volume limit being set lower than startup volume
}


// VolumeLimiter

VolumeLimiter::VolumeLimiter(IVolume& aVolume, TUint aMilliDbPerStep, IConfigManager& aConfigReader)
    : iLock("VLMT")
    , iVolume(aVolume)
    , iMilliDbPerStep(aMilliDbPerStep)
    , iConfigLimit(aConfigReader.GetNum(VolumeConfig::kKeyLimit))
    , iCurrentVolume(0)
{
    iSubscriberIdLimit = iConfigLimit.Subscribe(MakeFunctorConfigNum(*this, &VolumeLimiter::LimitChanged));
}

VolumeLimiter::~VolumeLimiter()
{
    iConfigLimit.Unsubscribe(iSubscriberIdLimit);
}

void VolumeLimiter::SetVolume(TUint aValue)
{
    LOG(kVolume, "VolumeLimiter::SetVolume aValue: %u\n", aValue);
    AutoMutex _(iLock);
    if (aValue > iLimit && iCurrentVolume >= iLimit) {
        THROW(VolumeOutOfRange);
    }
    iCurrentVolume = aValue;
    DoSetVolume();
}

void VolumeLimiter::LimitChanged(ConfigNum::KvpNum& aKvp)
{
    AutoMutex _(iLock);
    iLimit = aKvp.Value() * iMilliDbPerStep;
    try {
        DoSetVolume();
    }
    catch (VolumeNotSupported&) {}
}

void VolumeLimiter::DoSetVolume()
{
    iCurrentVolume = std::min(iCurrentVolume, iLimit);
    iVolume.SetVolume(iCurrentVolume);
}


// VolumeValue

VolumeValue::VolumeValue(TUint aVolumeUser, TUint aBinaryMilliDb)
    : iVolumeUser(aVolumeUser)
    , iVolumeBinaryMilliDb(aBinaryMilliDb)
{
}

TUint VolumeValue::VolumeUser() const
{
    return iVolumeUser;
}

TUint VolumeValue::VolumeBinaryMilliDb() const
{
    return iVolumeBinaryMilliDb;
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
    const VolumeValue vol(iUpstreamVolume / iMilliDbPerStep, iUpstreamVolume);
    aObserver.VolumeChanged(vol);
    iObservers.push_back(&aObserver);
}

void VolumeReporter::SetVolume(TUint aVolume)
{
    LOG(kVolume, "VolumeReporter::SetVolume aVolume: %u\n", aVolume);
    iVolume.SetVolume(aVolume);
    iUpstreamVolume = aVolume;
    const VolumeValue vol(iUpstreamVolume / iMilliDbPerStep, iUpstreamVolume);
    for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
        (*it)->VolumeChanged(vol);
    }
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
    LOG(kVolume, "VolumeSourceOffset::SetVolume aValue: %u\n", aValue);
    AutoMutex _(iLock);
    DoSetVolume(aValue);
    iUpstreamVolume = aValue;
}

void VolumeSourceOffset::SetVolumeOffset(TInt aOffset)
{
    AutoMutex _(iLock);
    iSourceOffset = aOffset;
    try {
        DoSetVolume(iUpstreamVolume);
    }
    catch (VolumeNotSupported&) {}
}

void VolumeSourceOffset::DoSetVolume(TUint aValue)
{
    TUint volume = aValue + iSourceOffset;
    if (aValue == 0) {
        volume = 0; // upstream volume of 0 should mean we output silence
    }
    if (volume > aValue && iSourceOffset < 0) {
        volume = 0;
    }
    else if (volume < aValue && iSourceOffset > 0) {
        volume = aValue;
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
    LOG(kVolume, "VolumeUnityGainBase::SetVolume aValue: %u\n", aValue);
    AutoMutex _(iLock);
    if (!iVolumeControlEnabled) {
        THROW(VolumeNotSupported);
    }
    iVolume.SetVolume(aValue);
    iUpstreamVolume = aValue;
}

void VolumeUnityGainBase::SetVolumeControlEnabled(TBool aEnabled)
{
    AutoMutex _(iLock);
    iVolumeControlEnabled = aEnabled;
    try {
        if (iVolumeControlEnabled) {
            iVolume.SetVolume(iUpstreamVolume);
        }
        else {
            iVolume.SetVolume(iUnityGain);
        }
    }
    catch (VolumeNotSupported&) {}
}

TBool VolumeUnityGainBase::VolumeControlEnabled() const
{
    AutoMutex _(iLock);
    return iVolumeControlEnabled;
}


// VolumeUnityGain

VolumeUnityGain::VolumeUnityGain(IVolume& aVolume, IConfigManager& aConfigReader, TUint aUnityGainValue)
    : VolumeUnityGainBase(aVolume, aUnityGainValue)
    , iConfigVolumeControlEnabled(aConfigReader.GetChoice(VolumeConfig::kKeyEnabled))
{
    TUint subscriberId = iConfigVolumeControlEnabled.Subscribe(MakeFunctorConfigChoice(*this, &VolumeUnityGain::EnabledChanged));
    iConfigVolumeControlEnabled.Unsubscribe(subscriberId);
}

VolumeUnityGain::~VolumeUnityGain()
{

}

void VolumeUnityGain::EnabledChanged(ConfigChoice::KvpChoice& aKvp)
{
    const TBool enabled = (aKvp.Value() == eStringIdYes);
    SetVolumeControlEnabled(enabled);
}


// VolumeSourceUnityGain

VolumeSourceUnityGain::VolumeSourceUnityGain(IVolume& aVolume, TUint aUnityGainValue)
    : VolumeUnityGainBase(aVolume, aUnityGainValue)
{
    SetVolumeControlEnabled(true);
}

void VolumeSourceUnityGain::SetUnityGain(TBool aEnable)
{
    SetVolumeControlEnabled(!aEnable);
    const TBool unityGain = !VolumeControlEnabled();
    for (auto observer: iObservers){
        observer.get().UnityGainChanged(unityGain);
    }
}

void VolumeSourceUnityGain::AddUnityGainObserver(IUnityGainObserver& aObserver)
{
    const TBool unityGain = !VolumeControlEnabled();
    aObserver.UnityGainChanged(unityGain);
    iObservers.push_back(aObserver);
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
    LOG(kVolume, "AnalogBypassRamper::SetVolume aValue: %u\n", aValue);
    AutoMutex _(iLock);
    iUpstreamVolume = aValue;
    SetVolume();
}

void AnalogBypassRamper::ApplyVolumeMultiplier(TUint aValue)
{
    LOG(kVolume, "AnalogBypassRamper::ApplyVolumeMultiplier aValue: %u\n", aValue);
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


// VolumeRamper

const TUint VolumeRamper::kJiffiesPerVolumeStep = 10 * Media::Jiffies::kPerMs;

VolumeRamper::VolumeRamper(IVolume& aVolume, TUint aMilliDbPerStep, TUint aThreadPriority)
    : iVolume(aVolume)
    , iLock("VOLR")
    , iMilliDbPerStep(aMilliDbPerStep)
    , iUpstreamVolume(0)
    , iPendingVolume(0)
    , iCurrentVolume(0)
    , iJiffiesUntilStep(0)
    , iStatus(Status::eRunning)
    , iMuted(false)
{
    iThread = new ThreadFunctor("VolumeRamper", MakeFunctor(*this, &VolumeRamper::Run), aThreadPriority);
    iThread->Start();
}

VolumeRamper::~VolumeRamper()
{
    delete iThread;
}

void VolumeRamper::SetVolume(TUint aValue)
{
    AutoMutex _(iLock);
    iUpstreamVolume = aValue;
    if (iStatus == Status::eRunning) {
        iPendingVolume = aValue;
        iThread->Signal();
    }
}

inline TUint VolumeRamper::VolumeStepLocked() const
{
    // values and threshold for change copied from Linn volkano1
    if (iCurrentVolume < 20 * iMilliDbPerStep) {
        return 4 * iMilliDbPerStep;
    }
    return 2 * iMilliDbPerStep;
}

Media::IVolumeRamper::Status VolumeRamper::BeginMute()
{
    AutoMutex _(iLock);
    if (iStatus == Status::eMuted) {
        return IVolumeRamper::Status::eComplete;
    }
    else if (iStatus != Status::eMuting) {
        iJiffiesUntilStep = kJiffiesPerVolumeStep;
        iStatus = Status::eMuting;
    }
    return IVolumeRamper::Status::eInProgress;
}

Media::IVolumeRamper::Status VolumeRamper::StepMute(TUint aJiffies)
{
    AutoMutex _(iLock);
    if (iStatus == Status::eMuted) {
        return IVolumeRamper::Status::eComplete;
    }
    if (iJiffiesUntilStep <= aJiffies) {
        aJiffies -= iJiffiesUntilStep;
        const auto step = VolumeStepLocked();
        if (step > iPendingVolume) {
            iPendingVolume = 0;
        }
        else {
            iPendingVolume -= step;
        }
        iThread->Signal();

        ASSERT(aJiffies < kJiffiesPerVolumeStep); // we're not effectively ramping volume if a single call here results in a large volume adjustment
        iJiffiesUntilStep = kJiffiesPerVolumeStep;
    }
    iJiffiesUntilStep -= aJiffies;
    return IVolumeRamper::Status::eInProgress;
}

void VolumeRamper::SetMuted()
{
    AutoMutex _(iLock);
    iStatus = Status::eMuted;
    if (iPendingVolume != 0) {
        iPendingVolume = 0;
        iThread->Signal();
    }
}

Media::IVolumeRamper::Status VolumeRamper::BeginUnmute()
{
    AutoMutex _(iLock);
    if (iStatus == Status::eRunning) {
        return IVolumeRamper::Status::eComplete;
    }
    else if (iStatus != Status::eUnmuting) {
        iJiffiesUntilStep = kJiffiesPerVolumeStep;
        iStatus = Status::eUnmuting;
    }
    return IVolumeRamper::Status::eInProgress;
}

Media::IVolumeRamper::Status VolumeRamper::StepUnmute(TUint aJiffies)
{
    AutoMutex _(iLock);
    if (iStatus == Status::eRunning) {
        return IVolumeRamper::Status::eComplete;
    }
    if (iJiffiesUntilStep <= aJiffies) {
        aJiffies -= iJiffiesUntilStep;
        iPendingVolume += VolumeStepLocked();
        iPendingVolume = std::min(iPendingVolume, iUpstreamVolume);
        iThread->Signal();

        ASSERT(aJiffies < kJiffiesPerVolumeStep); // we're not effectively ramping volume if a single call here results in a large volume adjustment
        iJiffiesUntilStep = kJiffiesPerVolumeStep;
    }
    iJiffiesUntilStep -= aJiffies;
    return IVolumeRamper::Status::eInProgress;
}

void VolumeRamper::SetUnmuted()
{
    AutoMutex _(iLock);
    iStatus = Status::eRunning;
    if (iPendingVolume != iUpstreamVolume) {
        iPendingVolume = iUpstreamVolume;
        iThread->Signal();
    }
}

void VolumeRamper::Run()
{
    try {
        for (;;) {
            iThread->Wait();
            TUint pendingVolume;
            {
                AutoMutex _(iLock);
                pendingVolume = iPendingVolume;
                iCurrentVolume = iPendingVolume;
                if (iStatus == Status::eMuting) {
                    if (iCurrentVolume == 0) {
                        iStatus = Status::eMuted;
                    }
                }
                else if (iStatus == Status::eUnmuting) {
                    if (iCurrentVolume == iUpstreamVolume) {
                        iStatus = Status::eRunning;
                    }
                }
            }
            iVolume.SetVolume(pendingVolume);
        }
    }
    catch (ThreadKill&) {}
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
    try {
        iBalance.SetBalance(aKvp.Value());
    }
    catch (BalanceNotSupported&) {}
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
    try {
        iFade.SetFade(aKvp.Value());
    }
    catch (FadeNotSupported&) {}
}


// MuteUser

MuteUser::MuteUser(Media::IMute& aMute, IPowerManager& aPowerManager)
    : iMute(aMute)
{
    iStandbyObserver = aPowerManager.RegisterStandbyHandler(*this, kStandbyHandlerPriorityNormal, "MuteUser");
}

MuteUser::~MuteUser()
{
    delete iStandbyObserver;
}

void MuteUser::Mute()
{
    iMute.Mute();
}

void MuteUser::Unmute()
{
    iMute.Unmute();
}

void MuteUser::StandbyEnabled()
{
    // no need to change mute when we enter standby
}

void MuteUser::StandbyDisabled(StandbyDisableReason /*aReason*/)
{
    // clear any previous mute when we leave standby
    Unmute();
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
const Brn VolumeConfig::kKeyStartupValue("Volume.StartupValue");
const Brn VolumeConfig::kKeyStartupEnabled("Volume.StartupEnabled");
const Brn VolumeConfig::kKeyLimit("Volume.Limit");
const Brn VolumeConfig::kKeyEnabled("Volume.Enabled");
const Brn VolumeConfig::kKeyBalance("Volume.Balance");
const Brn VolumeConfig::kKeyFade("Volume.Fade");

VolumeConfig::VolumeConfig(IStoreReadWrite& aStore, IConfigInitialiser& aConfigInit, IPowerManager& aPowerManager, const IVolumeProfile& aProfile)
    : iStoreUserVolume(aStore, aPowerManager, kPowerPriorityHighest, kKeyStartupVolume, aProfile.VolumeDefault())
{
    iVolumeMax            = aProfile.VolumeMax();
    iVolumeDefault        = aProfile.VolumeDefault();
    iVolumeUnity          = aProfile.VolumeUnity();
    iVolumeDefaultLimit   = aProfile.VolumeDefaultLimit();
    iVolumeStep           = aProfile.VolumeStep();
    iVolumeMilliDbPerStep = aProfile.VolumeMilliDbPerStep();
    iThreadPriority       = aProfile.ThreadPriority();
    iBalanceMax           = aProfile.BalanceMax();
    iFadeMax              = aProfile.FadeMax();
    iOffsetMax            = aProfile.OffsetMax();
    iAlwaysOn             = aProfile.AlwaysOn();


    std::vector<TUint> choices;
    choices.push_back(eStringIdYes);
    choices.push_back(eStringIdNo);

    if (iAlwaysOn) {
        iVolumeControlEnabled = true;
    }
    else {
        iVolumeEnabled = new ConfigChoice(aConfigInit, kKeyEnabled, choices, eStringIdYes);

        const TUint id = iVolumeEnabled->Subscribe(MakeFunctorConfigChoice(*this, &VolumeConfig::EnabledChanged));
        // EnabledChanged runs inside the call to Subscribe().
        // We don't support runtime change of this value so can immediately unsubscribe.
        iVolumeEnabled->Unsubscribe(id);
    }

    if (iVolumeControlEnabled)
    {
        iVolumeStartup = new ConfigNum(aConfigInit, kKeyStartupValue, 0, iVolumeMax, iVolumeDefault);

        iVolumeStartupEnabled = new ConfigChoice(aConfigInit, kKeyStartupEnabled, choices, eStringIdYes);
        iVolumeLimit = new ConfigNum(aConfigInit, kKeyLimit, 0, iVolumeMax, iVolumeDefaultLimit);


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
}

VolumeConfig::~VolumeConfig()
{
    if (iVolumeControlEnabled) {
        delete iVolumeStartup;
        delete iVolumeStartupEnabled;
        delete iVolumeLimit;
        delete iBalance;
        delete iFade;
    }

    if (!iAlwaysOn) {
        delete iVolumeEnabled;
    }
}

StoreInt& VolumeConfig::StoreUserVolume()
{
    return iStoreUserVolume;
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

TUint VolumeConfig::ThreadPriority() const
{
    return iThreadPriority;
}

TUint VolumeConfig::BalanceMax() const
{
    return iBalanceMax;
}

TUint VolumeConfig::FadeMax() const
{
    return iFadeMax;
}

TUint VolumeConfig::OffsetMax() const
{
    return iOffsetMax;
}

TBool VolumeConfig::AlwaysOn() const
{
    return iAlwaysOn;
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
    TBool volumeControlEnabled = aVolumeConfig.VolumeControlEnabled();

    iBalanceUser = nullptr;
    iFadeUser = nullptr;

    if (volumeControlEnabled)
    {
        IBalance* balance = aVolumeConsumer.Balance();
        if (balance != nullptr) {
            iBalanceUser = new BalanceUser(*balance, aConfigReader);
        }

        IFade* fade = aVolumeConsumer.Fade();
        if (fade != nullptr) {
            iFadeUser = new FadeUser(*fade, aConfigReader);
        }
    }

    if (aMute == nullptr) {
        iMuteReporter = nullptr;
        iMuteUser = nullptr;
    }
    else {
        iMuteReporter = new MuteReporter(*aMute);
        iMuteUser = new MuteUser(*iMuteReporter, aPowerManager);
    }
    const TUint milliDbPerStep = iVolumeConfig.VolumeMilliDbPerStep();
    const TUint volumeUnity = iVolumeConfig.VolumeUnity() * milliDbPerStep;
    iVolumeRamper = new VolumeRamper(*aVolumeConsumer.Volume(), milliDbPerStep, iVolumeConfig.ThreadPriority());
    iAnalogBypassRamper = new AnalogBypassRamper(*iVolumeRamper);
    if (aVolumeConfig.VolumeControlEnabled() && aVolumeConsumer.Volume() != nullptr) {
        if (iVolumeConfig.AlwaysOn()) {
            iVolumeSourceUnityGain = new VolumeSourceUnityGain(*iAnalogBypassRamper, volumeUnity);
        }
        else {
            iVolumeUnityGain = new VolumeUnityGain(*iAnalogBypassRamper, aConfigReader, volumeUnity);
            iVolumeSourceUnityGain = new VolumeSourceUnityGain(*iVolumeUnityGain, volumeUnity);
        }
        iVolumeSourceOffset = new VolumeSourceOffset(*iVolumeSourceUnityGain);
        iVolumeReporter = new VolumeReporter(*iVolumeSourceOffset, milliDbPerStep);
        iVolumeLimiter = new VolumeLimiter(*iVolumeReporter, milliDbPerStep, aConfigReader);
        iVolumeUser = new VolumeUser(*iVolumeLimiter, aConfigReader, aPowerManager,
                                     aVolumeConfig.StoreUserVolume(),
                                     iVolumeConfig.VolumeMax() * milliDbPerStep, milliDbPerStep);
        iProviderVolume = new ProviderVolume(aDevice, aConfigReader, *this, iBalanceUser, iFadeUser, aVolumeConsumer.VolumeOffsetter());
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
        static_cast<IVolume*>(iAnalogBypassRamper)->SetVolume(volumeUnity);
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
    delete iVolumeRamper;
}

void VolumeManager::AddVolumeObserver(IVolumeObserver& aObserver)
{
    if (iVolumeReporter == nullptr) {
        const VolumeValue vol(0, 0);
        aObserver.VolumeChanged(vol);
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

void VolumeManager::AddUnityGainObserver(IUnityGainObserver& aObserver)
{
    if(iVolumeSourceUnityGain == nullptr){
        aObserver.UnityGainChanged(false);
    }
    else{
        iVolumeSourceUnityGain->AddUnityGainObserver(aObserver);
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

TUint VolumeManager::ThreadPriority() const
{
    return iVolumeConfig.ThreadPriority();
}

TUint VolumeManager::BalanceMax() const
{
    return iVolumeConfig.BalanceMax();
}

TUint VolumeManager::FadeMax() const
{
    return iVolumeConfig.FadeMax();
}

TUint VolumeManager::OffsetMax() const
{
    return iVolumeConfig.OffsetMax();
}

TBool VolumeManager::AlwaysOn() const
{
    return iVolumeConfig.AlwaysOn();
}

void VolumeManager::SetVolume(TUint aValue)
{
    LOG(kVolume, "VolumeManager::SetVolume aValue: %u\n", aValue);
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

Media::IVolumeRamper::Status VolumeManager::BeginMute()
{
    return static_cast<IVolumeRamper*>(iVolumeRamper)->BeginMute();
}

Media::IVolumeRamper::Status VolumeManager::StepMute(TUint aJiffies)
{
    return static_cast<IVolumeRamper*>(iVolumeRamper)->StepMute(aJiffies);
}

void VolumeManager::SetMuted()
{
    static_cast<IVolumeRamper*>(iVolumeRamper)->SetMuted();
}

Media::IVolumeRamper::Status VolumeManager::BeginUnmute()
{
    return static_cast<IVolumeRamper*>(iVolumeRamper)->BeginUnmute();
}

Media::IVolumeRamper::Status VolumeManager::StepUnmute(TUint aJiffies)
{
    return static_cast<IVolumeRamper*>(iVolumeRamper)->StepUnmute(aJiffies);
}

void VolumeManager::SetUnmuted()
{
    static_cast<IVolumeRamper*>(iVolumeRamper)->SetUnmuted();
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

VolumeScaler::VolumeScaler(IVolumeReporter& aVolumeReporter, IVolumeSourceOffset& aVolumeOffset, TUint aVolMaxMilliDb, TUint aVolMaxExternal)
    : iVolumeOffset(aVolumeOffset)
    , iVolMaxMilliDb(aVolMaxMilliDb)
    , iVolMaxExternal(aVolMaxExternal)
    , iEnabled(false)
    , iVolUser(0)
    , iVolExternal(0)
    , iLock("VSCL")
{
    // Check there is no overflow if max values of both ranges are multiplied together.
    const TUint prod = iVolMaxMilliDb * iVolMaxExternal;
    const TUint div = prod/iVolMaxMilliDb;
    ASSERT(div == iVolMaxExternal);
    aVolumeReporter.AddVolumeObserver(*this);
}

void VolumeScaler::SetVolume(TUint aVolume)
{
    LOG(kVolume, "VolumeScaler::SetVolume aVolume: %u\n", aVolume);
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

void VolumeScaler::VolumeChanged(const IVolumeValue& aVolume)
{
    ASSERT(aVolume.VolumeBinaryMilliDb() <= iVolMaxMilliDb);
    AutoMutex a(iLock);
    iVolUser = aVolume.VolumeBinaryMilliDb();
    if (iEnabled) {
        UpdateOffsetLocked();
    }
}

void VolumeScaler::UpdateOffsetLocked()
{
    // Already know from check in constructor that this can't overflow.
    const TUint volProd = iVolExternal * iVolUser;

    const TUint vol = volProd / iVolMaxExternal;
    ASSERT(iVolUser >= vol);    // Scaled vol must be within user vol.
    const TInt offset = (iVolUser - vol) * -1;

    iVolumeOffset.SetVolumeOffset(offset);
}
