#pragma once

#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Media/MuteManager.h>

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
    class Product;
    class ProviderVolume;

class IVolume
{
public:
    virtual void SetVolume(TUint aVolume) = 0;
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
    virtual TUint BalanceMax() const = 0;
    virtual TUint FadeMax() const = 0;
    virtual ~IVolumeProfile() {}
};

class VolumeConsumer : private INonCopyable
{
public:
    VolumeConsumer();
    void SetVolume(IVolume& aVolume);
    void SetBalance(IBalance& aBalance);
    void SetFade(IFade& aFade);
    IVolume* Volume();
    IBalance* Balance();
    IFade* Fade();
private:
    IVolume* iVolume;
    IBalance* iBalance;
    IFade* iFade;
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
    TUint BalanceMax() const override           { return 0; }
    TUint FadeMax() const override              { return 0; }
};

class VolumeUser : public IVolume, private INonCopyable
{
public:
    static const Brn kStartupVolumeKey;
public:
    VolumeUser(IVolume& aVolume, Configuration::IConfigManager& aConfigReader, StoreInt& aStoreUserVolume, TUint aMaxVolume);
    ~VolumeUser();
public: // from IVolume
    void SetVolume(TUint aVolume) override;
private:
    void StartupVolumeChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void StartupVolumeEnabledChanged(Configuration::ConfigChoice::KvpChoice& aKvp);
private:
    IVolume& iVolume;
    Configuration::ConfigNum& iConfigStartupVolume;
    Configuration::ConfigChoice& iConfigStartupVolumeEnabled;
    TUint iSubscriberIdStartupVolume;
    TUint iSubscriberIdStartupVolumeEnabled;
    StoreInt& iStoreUserVolume;
    TBool iStartupVolumeEnabled;
    TUint iStartupVolume;
    TUint iMaxVolume;
};

class VolumeLimiter : public IVolume, private INonCopyable
{
public:
    VolumeLimiter(IVolume& aVolume, Configuration::IConfigManager& aConfigReader);
    ~VolumeLimiter();
public: // from IVolume
    void SetVolume(TUint aValue) override;
private:
    void LimitChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void SetVolume();
private:
    Mutex iLock;
    IVolume& iVolume;
    Configuration::ConfigNum& iConfigLimit;
    TUint iSubscriberIdLimit;
    TUint iUpstreamVolume;
    TUint iLimit;
};

class IVolumeObserver
{
public:
    virtual void VolumeChanged(TUint aVolume) = 0;
    virtual ~IVolumeObserver() {}
};

class IVolumeReporter
{
public:
    virtual void AddVolumeObserver(IVolumeObserver& aObserver) = 0;
    virtual ~IVolumeReporter() {}
};

class VolumeReporter : public IVolumeReporter, public IVolume, private INonCopyable
{
public:
    VolumeReporter(IVolume& aVolume);
public: // from IVolumeReporter
    void AddVolumeObserver(IVolumeObserver& aObserver) override;
private: // from IVolume
    void SetVolume(TUint aValue) override;
private:
    IVolume& iVolume;
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
    void SetVolume();
private:
    Mutex iLock;
    IVolume& iVolume;
    TUint iUpstreamVolume;
    TInt iSourceOffset;
};

class VolumeUnityGainBase : public IVolume, private INonCopyable
{
public:
    VolumeUnityGainBase(IVolume& aVolume, TUint aUnityGainValue);
public:  // from IVolume
    void SetVolume(TUint aValue) override;
protected:
    void SetEnabled(TBool aEnabled);
private:
    Mutex iLock;
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
    TUint iSubscriberId;
};

class IVolumeSourceUnityGain
{
public:
    virtual void SetUnityGain(TBool aEnabled) = 0;
    virtual ~IVolumeSourceUnityGain() {}
};

// per-source switch between pass-through and override with unity gain
class VolumeSourceUnityGain : public VolumeUnityGainBase, public IVolumeSourceUnityGain
{
public:
    VolumeSourceUnityGain(IVolume& aVolume, TUint aUnityGainValue);
public: // from IVolumeSourceUnityGain
    void SetUnityGain(TBool aEnable) override;
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

class MuteUser : public Media::IMute, private INonCopyable
{
public:
    MuteUser(Media::IMute& aMute, StoreInt& aStoreUserMute);
public: // from Media::IMute
    void Mute() override;
    void Unmute() override;
private:
    Media::IMute& iMute;
    StoreInt& iStoreUserMute;
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
    static const Brn kKeyStartupMute;
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
    StoreInt& StoreUserMute();
    TBool VolumeControlEnabled() const;
public: // from IVolumeProfile
    TUint VolumeMax() const override;
    TUint VolumeDefault() const override;
    TUint VolumeUnity() const override;
    TUint VolumeDefaultLimit() const override;
    TUint VolumeStep() const override;
    TUint VolumeMilliDbPerStep() const override;
    TUint BalanceMax() const override;
    TUint FadeMax() const override;
private:
    void EnabledChanged(Configuration::ConfigChoice::KvpChoice& aKvp);
private:
    StoreInt iStoreUserVolume;
    StoreInt iStoreUserMute;
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
    TUint iBalanceMax;
    TUint iFadeMax;
    TBool iVolumeControlEnabled;
};

class IVolumeManager : public IVolumeReporter, public IMuteReporter, public IVolume, public IVolumeProfile, public IVolumeSourceOffset, public Media::IMute
{
public:
    virtual ~IVolumeManager() {}
};

class VolumeManager : public IVolumeManager
                    , public IVolumeSourceUnityGain
                    , private IBalance
                    , private IFade
                    , private INonCopyable
{
public:
    VolumeManager(VolumeConsumer& aVolumeConsumer, Media::IMute* aMute, VolumeConfig& aVolumeConfig,
                  Net::DvDevice& aDevice, Product& aProduct, Configuration::IConfigManager& aConfigReader);
    ~VolumeManager();
public: // from IVolumeReporter
    void AddVolumeObserver(IVolumeObserver& aObserver) override;
public: // from IMuteReporter
    void AddMuteObserver(Media::IMuteObserver& aObserver) override;
public: // from IVolumeSourceOffset
    void SetVolumeOffset(TInt aValue) override;
public: // from IVolumeSourceUnityGain
    void SetUnityGain(TBool aEnable) override;
private: // from IVolumeProfile
    TUint VolumeMax() const override;
    TUint VolumeDefault() const override;
    TUint VolumeUnity() const override;
    TUint VolumeDefaultLimit() const override;
    TUint VolumeStep() const override;
    TUint VolumeMilliDbPerStep() const override;
    TUint BalanceMax() const override;
    TUint FadeMax() const override;
private: // from IVolume
    void SetVolume(TUint aValue) override;
private: // from IBalance
    void SetBalance(TInt aBalance) override;
private: // from IFade
    void SetFade(TInt aFade) override;
private: // from Media::IMute
    void Mute() override;
    void Unmute() override;
private:
    VolumeConfig& iVolumeConfig;
    VolumeSourceUnityGain* iVolumeSourceUnityGain;
    VolumeUnityGain* iVolumeUnityGain;
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
    VolumeScaler(IVolumeReporter& aVolumeReporter, IVolumeSourceOffset& aVolumeOffset, TUint aVolMaxUser, TUint aVolMaxExternal);
public: // from IVolume
    void SetVolume(TUint aVolume) override;
public: // from IVolumeScalerEnabler
    void SetVolumeEnabled(TBool aEnabled) override;
public: // from IVolumeObserver
    void VolumeChanged(TUint aVolume) override;
private:
    void UpdateOffsetLocked();
private:
    IVolumeSourceOffset& iVolumeOffset;
    const TUint iVolMaxUser;
    const TUint iVolMaxExternal;
    TBool iEnabled;
    TUint iVolUser;
    TUint iVolExternal;
    Mutex iLock;
};

} // namespace Av
} // namespace OpenHome
