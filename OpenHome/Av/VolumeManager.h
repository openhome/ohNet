#pragma once

#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Media/MuteManager.h>
#include <OpenHome/Media/Pipeline/AnalogBypassRamper.h>
#include <OpenHome/Media/Pipeline/MuterVolume.h>

#include <functional>
#include <vector>

//
// volume elements are linearly chained and any contributing change
// propagates downstream to actual HW driver via SetVolume() calls;
// invidual volume elements have specific methods to set their contribution
//
// [defaults]     0..100                        mibidB         on/off        -15..+15    +--> [VolLim] --> [HW] .
//                   |                             |              |             |       /                       .
// 0..100 --> [VolLimitUser] --> [VolUser] --> [SrcOff] --> [UnityGain] --> [Balance] -+                        .
//                                                                                      \                       .
//            where --> means SetVolume(TUint)                                           +--> [VolLim] --> [HW] .
//
// for best audio performance, SetVolume() for volume propagation and Set*() for parameter
// adjustment, respectively, should not supply the same value in consecutive calls
// (i.e. invocations should always signal genuine change)
//
// client code is free to choose an appropriate scale factor for converting from user
// to system volume and must apply this consistently whenever volume offsets, etc.
// are supplied in invocations;  classes are provided that encapsulate sensible
// default factors and value ranges
//

EXCEPTION(VolumeNotSupported);
EXCEPTION(BalanceNotSupported);
EXCEPTION(FadeNotSupported);
EXCEPTION(MuteNotSupported);
EXCEPTION(VolumeOutOfRange);
EXCEPTION(BalanceOutOfRange);
EXCEPTION(FadeOutOfRange);

namespace OpenHome {
namespace Configuration {
    class IConfigInitialiser;
    class IStoreReadWrite;
    class IConfigManager;
}
namespace Net {
    class DvDevice;
}
namespace Av {
    class IVolumeOffsetter;
    class Product;
    class ProviderVolume;

class IVolume
{
public:
    virtual void SetVolume(TUint aVolume) = 0; // volume is in binary-milli-db (1/1024 db)
    virtual ~IVolume() {}
};

// Internal balance is expressed as a signed integer on [-max..+max], with negative balance implying
// a shift to the left, positive balance implying a shift to the right.
class IBalance
{
public:
    virtual void SetBalance(TInt aBalance) = 0; // -ve, 0, +ve
    virtual ~IBalance() {}
};

class IFade
{
public:
    virtual void SetFade(TInt aFade) = 0; // -ve, 0, +ve
    virtual ~IFade() {}
};

class IVolumeProfile
{
public:
    virtual TUint VolumeMax() const = 0;
    virtual TUint VolumeDefault() const = 0;
    virtual TUint VolumeUnity() const = 0;
    virtual TUint VolumeDefaultLimit() const = 0;
    virtual TUint VolumeStep() const = 0;
    virtual TUint VolumeMilliDbPerStep() const = 0;
    virtual TUint ThreadPriority() const = 0;
    virtual TUint BalanceMax() const = 0;
    virtual TUint FadeMax() const = 0;
    virtual TUint OffsetMax() const = 0;
    virtual TBool AlwaysOn() const = 0;
    virtual ~IVolumeProfile() {}
};

class VolumeConsumer : private INonCopyable
{
public:
    VolumeConsumer();
    void SetVolume(IVolume& aVolume);
    void SetBalance(IBalance& aBalance);
    void SetFade(IFade& aFade);
    void SetVolumeOffsetter(IVolumeOffsetter& aVolumeOffsetter);
    IVolume* Volume();
    IBalance* Balance();
    IFade* Fade();
    IVolumeOffsetter* VolumeOffsetter();
private:
    IVolume* iVolume;
    IBalance* iBalance;
    IFade* iFade;
    IVolumeOffsetter* iVolumeOffsetter;
};

class VolumeNull : public IVolume
{
private: // from IVolume
    void SetVolume(TUint aVolume) override;
};

class VolumeProfileNull : public IVolumeProfile
{
private: // from IVolumeProfile
    TUint VolumeMax() const override            { return 0; }
    TUint VolumeDefault() const override        { return 0; }
    TUint VolumeUnity() const override          { return 0; }
    TUint VolumeDefaultLimit() const override   { return 0; }
    TUint VolumeStep() const override           { return 0; }
    TUint VolumeMilliDbPerStep() const override { return 0; }
    TUint ThreadPriority() const override       { return kPriorityNormal; }
    TUint BalanceMax() const override           { return 0; }
    TUint FadeMax() const override              { return 0; }
    TUint OffsetMax() const override            { return 0; }
    TBool AlwaysOn() const override             { return false; }
};

class VolumeUser : public IVolume, private IStandbyHandler, private INonCopyable
{
public:
    static const Brn kStartupVolumeKey;
public:
    VolumeUser(IVolume& aVolume, Configuration::IConfigManager& aConfigReader, IPowerManager& aPowerManager,
               StoreInt& aStoreUserVolume, TUint aMaxVolume, TUint aMilliDbPerStep);
    ~VolumeUser();
public: // from IVolume
    void SetVolume(TUint aVolume) override;
private: // from IStandbyHandler
    void StandbyEnabled() override;
    void StandbyDisabled(StandbyDisableReason aReason) override;
private:
    void StartupVolumeChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void StartupVolumeEnabledChanged(Configuration::ConfigChoice::KvpChoice& aKvp);
    void ApplyStartupVolume();
private:
    IVolume& iVolume;
    Configuration::ConfigNum& iConfigStartupVolume;
    Configuration::ConfigChoice& iConfigStartupVolumeEnabled;
    IStandbyObserver* iStandbyObserver;
    TUint iSubscriberIdStartupVolume;
    TUint iSubscriberIdStartupVolumeEnabled;
    StoreInt& iStoreUserVolume;
    TBool iStartupVolumeEnabled;
    TBool iStartupVolumeReported;
    TUint iStartupVolume;
    const TUint iMaxVolume;
    const TUint iMilliDbPerStep;
};

class VolumeLimiter : public IVolume, private INonCopyable
{
public:
    VolumeLimiter(IVolume& aVolume, TUint aMilliDbPerStep, Configuration::IConfigManager& aConfigReader);
    ~VolumeLimiter();
public: // from IVolume
    void SetVolume(TUint aValue) override;
private:
    void LimitChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void DoSetVolume();
private:
    Mutex iLock;
    IVolume& iVolume;
    const TUint iMilliDbPerStep;
    Configuration::ConfigNum& iConfigLimit;
    TUint iSubscriberIdLimit;
    TUint iCurrentVolume;
    TUint iLimit;
};

class IVolumeValue
{
public:
    virtual TUint VolumeUser() const = 0;
    virtual TUint VolumeBinaryMilliDb() const = 0;
};

class IVolumeObserver
{
public:
    virtual void VolumeChanged(const IVolumeValue& aVolume) = 0;
    virtual ~IVolumeObserver() {}
};

class IVolumeReporter
{
public:
    virtual void AddVolumeObserver(IVolumeObserver& aObserver) = 0;
    virtual ~IVolumeReporter() {}
};

class VolumeValue : public IVolumeValue, private INonCopyable
{
public:
    VolumeValue(TUint aVolumeUser, TUint aBinaryMilliDb);
public: // from IVolumeValue
    TUint VolumeUser() const override;
    TUint VolumeBinaryMilliDb() const override;
private:
    const TUint iVolumeUser;
    const TUint iVolumeBinaryMilliDb;
};

class VolumeReporter : public IVolumeReporter, public IVolume, private INonCopyable
{
public:
    VolumeReporter(IVolume& aVolume, TUint aMilliDbPerStep);
public: // from IVolumeReporter
    void AddVolumeObserver(IVolumeObserver& aObserver) override;
private: // from IVolume
    void SetVolume(TUint aValue) override;
private:
    IVolume& iVolume;
    const TUint iMilliDbPerStep;
    std::vector<IVolumeObserver*> iObservers;
    TUint iUpstreamVolume;
};

class IVolumeSourceOffset
{
public:
    virtual void SetVolumeOffset(TInt aOffset) = 0;
    virtual ~IVolumeSourceOffset() {}
};

class VolumeSourceOffset : public IVolume, public IVolumeSourceOffset, private INonCopyable
{
public:
    VolumeSourceOffset(IVolume& aVolume);
public:  // from IVolume
    void SetVolume(TUint aValue) override;
public: // from IVolumeSourceOffset
    void SetVolumeOffset(TInt aOffset) override;
private:
    void DoSetVolume(TUint aValue);
private:
    Mutex iLock;
    IVolume& iVolume;
    TUint iUpstreamVolume;
    TInt iSourceOffset;
};

class IVolumeSurroundBoost
{
public:
    virtual void SetVolumeBoost(TUint aBoost) = 0;
    virtual ~IVolumeSurroundBoost() {}
};

class VolumeSurroundBoost : public IVolume, public IVolumeSurroundBoost, private INonCopyable
{
public:
    VolumeSurroundBoost(IVolume& aVolume);
public:  // from IVolume
    void SetVolume(TUint aValue) override;
public: // from IVolumeSurroundBoost
    void SetVolumeBoost(TUint aBoost) override;
private:
    void DoSetVolume(TUint aValue);
private:
    Mutex iLock;
    IVolume& iVolume;
    TUint iUpstreamVolume;
    TUint iBoost;
};

class VolumeUnityGainBase : public IVolume, private INonCopyable
{
public:
    VolumeUnityGainBase(IVolume& aVolume, TUint aUnityGainValue);
public:  // from IVolume
    void SetVolume(TUint aValue) override;
protected:
    void SetVolumeControlEnabled(TBool aEnabled);
    TBool VolumeControlEnabled() const;
private:
    mutable Mutex iLock;
    IVolume& iVolume;
    const TUint iUnityGain;
    TUint iUpstreamVolume;
    TBool iVolumeControlEnabled;
};

// switch between pass-through and override with unity gain
class VolumeUnityGain : public VolumeUnityGainBase
{
public:
    VolumeUnityGain(IVolume& aVolume, Configuration::IConfigManager& aConfigReader, TUint aUnityGainValue);
    ~VolumeUnityGain();
private:
    void EnabledChanged(Configuration::ConfigChoice::KvpChoice& aKvp);
private:
    Configuration::ConfigChoice& iConfigVolumeControlEnabled;
};

class IUnityGainObserver
{
public:
    virtual void UnityGainChanged(TBool aValue) = 0;
    virtual ~IUnityGainObserver() {}
};

class IUnityGainReporter
{
public:
    virtual void AddUnityGainObserver(IUnityGainObserver& aObserver) = 0;
    virtual ~IUnityGainReporter() {}    
};

class IVolumeSourceUnityGain : public IUnityGainReporter
{
public:
    virtual void SetUnityGain(TBool aEnabled) = 0;
    virtual ~IVolumeSourceUnityGain() {}
public: //from IUnityGainReporter
    virtual void AddUnityGainObserver(IUnityGainObserver& aObserver) = 0;
};

// per-source switch between pass-through and override with unity gain
class VolumeSourceUnityGain : public VolumeUnityGainBase, public IVolumeSourceUnityGain
{
public:
    VolumeSourceUnityGain(IVolume& aVolume, TUint aUnityGainValue);
public: // from IVolumeSourceUnityGain
    void SetUnityGain(TBool aEnable) override;
    void AddUnityGainObserver(IUnityGainObserver& aObserver) override;
private:
    std::vector<std::reference_wrapper<IUnityGainObserver>> iObservers;
};

class AnalogBypassRamper : public IVolume
                         , public Media::IAnalogBypassVolumeRamper
                         , private INonCopyable
{
public:
    AnalogBypassRamper(IVolume& aVolume);
private: // from IVolume
    void SetVolume(TUint aValue) override;
private: // from Media::IAnalogBypassVolumeRamper
    void ApplyVolumeMultiplier(TUint aValue) override;
private:
    void SetVolume();
private:
    IVolume& iVolume;
    Mutex iLock;
    TUint iUpstreamVolume;
    TUint iMultiplier;
};

class VolumeRamper : public IVolume
                   , public Media::IVolumeRamper
                   , private INonCopyable
{
    friend class SuiteVolumeRamper;

    static const TUint kJiffiesPerVolumeStep;
public:
    VolumeRamper(IVolume& aVolume, TUint aMilliDbPerStep, TUint aThreadPriority);
    ~VolumeRamper();
private: // from IVolume
    void SetVolume(TUint aValue) override;
private: // from Media::IVolumeRamper
    Media::IVolumeRamper::Status BeginMute() override;
    Media::IVolumeRamper::Status StepMute(TUint aJiffies) override;
    void SetMuted() override;
    Media::IVolumeRamper::Status BeginUnmute() override;
    Media::IVolumeRamper::Status StepUnmute(TUint aJiffies) override;
    void SetUnmuted() override;
private:
    inline TUint VolumeStepLocked() const;
    void Run();
private:
    enum class Status
    {
        eRunning,
        eMuting,
        eUnmuting,
        eMuted
    };
private:
    IVolume& iVolume;
    Mutex iLock;
    ThreadFunctor* iThread;
    const TUint iMilliDbPerStep;
    TUint iUpstreamVolume;
    TUint iPendingVolume;
    TUint iCurrentVolume;
    TUint iJiffiesUntilStep;
    Status iStatus;
    TBool iMuted;
};

class BalanceUser : public IBalance, private INonCopyable
{
public:
    BalanceUser(IBalance& aBalance, Configuration::IConfigManager& aConfigReader);
    ~BalanceUser();
public: // from IBalance
    void SetBalance(TInt aBalance) override;
private:
    void BalanceChanged(Configuration::ConfigNum::KvpNum& aKvp);
private:
    IBalance& iBalance;
    Configuration::ConfigNum& iConfigBalance;
    TUint iSubscriberIdBalance;
};

class FadeUser : public IFade, private INonCopyable
{
public:
    FadeUser(IFade& aFade, Configuration::IConfigManager& aConfigReader);
    ~FadeUser();
public: // from IFade
    void SetFade(TInt aFade) override;
private:
    void FadeChanged(Configuration::ConfigNum::KvpNum& aKvp);
private:
    IFade& iFade;
    Configuration::ConfigNum& iConfigFade;
    TUint iSubscriberIdFade;
};

class MuteUser : public Media::IMute, private IStandbyHandler, private INonCopyable
{
public:
    MuteUser(Media::IMute& aMute, IPowerManager& aPowerManager);
    ~MuteUser();
public: // from Media::IMute
    void Mute() override;
    void Unmute() override;
private: // from IStandbyHandler
    void StandbyEnabled() override;
    void StandbyDisabled(StandbyDisableReason aReason) override;
private:
    Media::IMute& iMute;
    IStandbyObserver* iStandbyObserver;
};

class IMuteReporter
{
public:
    virtual void AddMuteObserver(Media::IMuteObserver& aObserver) = 0;
    virtual ~IMuteReporter() {}
};

class MuteReporter : public IMuteReporter, public Media::IMute, private INonCopyable
{
public:
    MuteReporter(Media::IMute& aMute);
public: // from IMuteReporter
    void AddMuteObserver(Media::IMuteObserver& aObserver) override;
private: // from Media::IMute
    void Mute() override;
    void Unmute() override;
private:
    TBool Report(TBool aMuted);
private:
    Media::IMute& iMute;
    std::vector<Media::IMuteObserver*> iObservers;
    TBool iMuted;
};

class VolumeConfig : public IVolumeProfile
{
public:
    static const Brn kKeyStartupVolume;
    static const Brn kKeyStartupValue;
    static const Brn kKeyStartupEnabled;
    static const Brn kKeyLimit;
    static const Brn kKeyEnabled;
    static const Brn kKeyBalance;
    static const Brn kKeyFade;
    static const TInt kValueMuted   = 1;
    static const TInt kValueUnmuted = 0;
public:
    VolumeConfig(Configuration::IStoreReadWrite& aStore, Configuration::IConfigInitialiser& aConfigInit, IPowerManager& aPowerManager, const IVolumeProfile& aProfile);
    ~VolumeConfig();
    StoreInt& StoreUserVolume();
    TBool VolumeControlEnabled() const;
public: // from IVolumeProfile
    TUint VolumeMax() const override;
    TUint VolumeDefault() const override;
    TUint VolumeUnity() const override;
    TUint VolumeDefaultLimit() const override;
    TUint VolumeStep() const override;
    TUint VolumeMilliDbPerStep() const override;
    TUint ThreadPriority() const override;
    TUint BalanceMax() const override;
    TUint FadeMax() const override;
    TUint OffsetMax() const override;
    TBool AlwaysOn() const override;
private:
    void EnabledChanged(Configuration::ConfigChoice::KvpChoice& aKvp);
private:
    StoreInt iStoreUserVolume;
    Configuration::ConfigNum* iVolumeStartup;
    Configuration::ConfigChoice* iVolumeStartupEnabled;
    Configuration::ConfigNum* iVolumeLimit;
    Configuration::ConfigChoice* iVolumeEnabled;
    Configuration::ConfigNum* iBalance;
    Configuration::ConfigNum* iFade;
    TUint iVolumeMax;
    TUint iVolumeDefault;
    TUint iVolumeUnity;
    TUint iVolumeDefaultLimit;
    TUint iVolumeStep;
    TUint iVolumeMilliDbPerStep;
    TUint iThreadPriority;
    TUint iBalanceMax;
    TUint iFadeMax;
    TUint iOffsetMax;
    TBool iAlwaysOn;
    TBool iVolumeControlEnabled;
};

class IVolumeManager : public IVolumeReporter
                     , public IMuteReporter
                     , public IVolume
                     , public IVolumeProfile
                     , public IVolumeSourceOffset
                     , public IVolumeSurroundBoost
                     , public IVolumeSourceUnityGain
                     , public Media::IAnalogBypassVolumeRamper
                     , public Media::IVolumeRamper
                     , public Media::IMute
{
public:
    virtual ~IVolumeManager() {}
};

class VolumeManager : public IVolumeManager
                    , private IBalance
                    , private IFade
                    , private INonCopyable
{
public:
    VolumeManager(VolumeConsumer& aVolumeConsumer, Media::IMute* aMute, VolumeConfig& aVolumeConfig,
                  Net::DvDevice& aDevice, Product& aProduct, Configuration::IConfigManager& aConfigReader,
                  IPowerManager& aPowerManager);
    ~VolumeManager();
public: // from IVolumeReporter
    void AddVolumeObserver(IVolumeObserver& aObserver) override;
public: // from IMuteReporter
    void AddMuteObserver(Media::IMuteObserver& aObserver) override;
public: // from IVolumeSourceOffset
    void SetVolumeOffset(TInt aValue) override;
public: // from IVolumeSurroundBoost
    void SetVolumeBoost(TUint aValue) override;
public: // from IVolumeSourceUnityGain
    void SetUnityGain(TBool aEnable) override;
    void AddUnityGainObserver(IUnityGainObserver& aObserver) override;
private: // from IVolumeProfile
    TUint VolumeMax() const override;
    TUint VolumeDefault() const override;
    TUint VolumeUnity() const override;
    TUint VolumeDefaultLimit() const override;
    TUint VolumeStep() const override;
    TUint VolumeMilliDbPerStep() const override;
    TUint ThreadPriority() const override;
    TUint BalanceMax() const override;
    TUint FadeMax() const override;
    TUint OffsetMax() const override;
    TBool AlwaysOn() const override;
private: // from IVolume
    void SetVolume(TUint aValue) override;
private: // from IBalance
    void SetBalance(TInt aBalance) override;
private: // from IFade
    void SetFade(TInt aFade) override;
private: // from Media::IAnalogBypassVolumeRamper
    void ApplyVolumeMultiplier(TUint aValue) override;
private: // from Media::IVolumeRamper
    Media::IVolumeRamper::Status BeginMute() override;
    Media::IVolumeRamper::Status StepMute(TUint aJiffies) override;
    void SetMuted() override;
    Media::IVolumeRamper::Status BeginUnmute() override;
    Media::IVolumeRamper::Status StepUnmute(TUint aJiffies) override;
    void SetUnmuted() override;
private: // from Media::IMute
    void Mute() override;
    void Unmute() override;
private:
    VolumeConfig& iVolumeConfig;
    VolumeRamper* iVolumeRamper;
    AnalogBypassRamper* iAnalogBypassRamper;
    VolumeSourceUnityGain* iVolumeSourceUnityGain;
    VolumeUnityGain* iVolumeUnityGain;
    VolumeSurroundBoost* iVolumeSurroundBoost;
    VolumeSourceOffset* iVolumeSourceOffset;
    VolumeReporter* iVolumeReporter;
    VolumeLimiter* iVolumeLimiter;
    VolumeUser* iVolumeUser;
    BalanceUser* iBalanceUser;
    FadeUser* iFadeUser;
    MuteReporter* iMuteReporter;
    MuteUser* iMuteUser;
    ProviderVolume* iProviderVolume;
};

class IVolumeScalerEnabler
{
public:
    virtual void SetVolumeEnabled(TBool aEnabled) = 0;
    virtual ~IVolumeScalerEnabler() {}
};

/**
 * Class that scales volumes to within range of current user volume.
 * Expects that user volume and volume range to be scaled both start at 0.
 */
class VolumeScaler : public IVolume, public IVolumeScalerEnabler, public IVolumeObserver
{
public:
    VolumeScaler(IVolumeReporter& aVolumeReporter, IVolumeSourceOffset& aVolumeOffset, TUint aVolMaxMilliDb, TUint aVolMaxExternal);
public: // from IVolume
    void SetVolume(TUint aVolume) override;
public: // from IVolumeScalerEnabler
    void SetVolumeEnabled(TBool aEnabled) override;
public: // from IVolumeObserver
    void VolumeChanged(const IVolumeValue& aVolume) override;
private:
    void UpdateOffsetLocked();
private:
    IVolumeSourceOffset& iVolumeOffset;
    const TUint iVolMaxMilliDb;
    const TUint iVolMaxExternal;
    TBool iEnabled;
    TUint iVolUser;
    TUint iVolExternal;
    Mutex iLock;
};

} // namespace Av
} // namespace OpenHome
