#ifndef HEADER_AV_VOLUME_MANAGER
#define HEADER_AV_VOLUME_MANAGER

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
    virtual TUint VolumeMax() = 0;
    virtual TUint VolumeDefault() = 0;
    virtual TUint VolumeUnity() = 0;
    virtual TUint VolumeDefaultLimit() = 0;
    virtual TUint VolumeStep() = 0;
    virtual TUint VolumeMilliDbPerStep() = 0;
    virtual TUint BalanceMax() = 0;
    virtual TUint FadeMax() = 0;
    virtual ~IVolumeProfile() {}
};

class VolumeInitParams : public IVolumeProfile
{
    friend class VolumeManager;
public:
    VolumeInitParams();
    void SetVolume(IVolume& aVolume, TUint aVolumeMax, TUint aVolumeDefault, TUint aVolumeUnity, TUint aDefaultLimit, TUint aVolumeStep, TUint aVolumeMilliDbPerStep);
    void SetBalance(IBalance& aBalance, TUint aBalanceMax);
    void SetFade(IFade& aFade, TUint aFadeMax);
    void SetUserMute(Media::IMute& aMute);
public: // from IVolumeProfile
    TUint VolumeMax() override;
    TUint VolumeDefault() override;
    TUint VolumeUnity() override;
    TUint VolumeDefaultLimit() override;
    TUint VolumeStep() override;
    TUint VolumeMilliDbPerStep() override;
    TUint BalanceMax() override;
    TUint FadeMax() override;
private:
    IVolume* iVolume;
    TUint iVolumeMax;
    TUint iVolumeDefault;
    TUint iVolumeUnity;
    TUint iVolumeDefaultLimit;
    TUint iVolumeStep;
    TUint iVolumeMilliDbPerStep;
    IBalance* iBalance;
    TUint iBalanceMax;
    IFade* iFade;
    TUint iFadeMax;
    Media::IMute* iMute;
};

class VolumeUser : public IVolume, private INonCopyable
{
public:
    static const Brn kStartupVolumeKey;
    static const Brn kConfigKeyStartup;
    static const Brn kConfigKeyStartupEnabled;
public:
    VolumeUser(IVolume& aVolume, Configuration::IStoreReadWrite& aStore, Configuration::IConfigInitialiser& aConfigInit, IPowerManager& aPowerManager, TUint aMaxVolume, TUint aDefaultVolume);
    ~VolumeUser();
public: // from IVolume
    void SetVolume(TUint aVolume) override;
private:
    void StartupVolumeChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void StartupVolumeEnabledChanged(Configuration::ConfigChoice::KvpChoice& aKvp);
private:
    IVolume& iVolume;
    Configuration::ConfigNum* iConfigStartupVolume;
    Configuration::ConfigChoice* iConfigStartupVolumeEnabled;
    TUint iSubscriberIdStartupVolume;
    TUint iSubscriberIdStartupVolumeEnabled;
    StoreInt iStoreUserVolume;
    TBool iStartupVolumeEnabled;
    TUint iStartupVolume;
    TUint iMaxVolume;
};

// limiter: clip any excess volume
class VolumeLimiter : public IVolume, private INonCopyable
{
public:
    static const Brn kConfigKey;
public:
    VolumeLimiter(IVolume& aVolume, Configuration::IConfigInitialiser& aConfigInit, TUint aDefaultLimit, TUint aMaxVolume);
    ~VolumeLimiter();
public: // from IVolume
    void SetVolume(TUint aValue) override;
private:
    void LimitChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void SetVolume();
private:
    Mutex iLock;
    IVolume& iVolume;
    Configuration::ConfigNum* iConfigLimit;
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

class VolumeReporter : public IVolume, private INonCopyable
{
public:
    VolumeReporter(IVolume& aVolume);
    void AddObserver(IVolumeObserver& aObserver);
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
    static const Brn kConfigKey;
public:
    VolumeUnityGain(IVolume& aVolume, Configuration::IConfigInitialiser& aConfigInit, TUint aUnityGainValue);
    ~VolumeUnityGain();
private:
    void EnabledChanged(Configuration::ConfigChoice::KvpChoice& aKvp);
private:
    Configuration::ConfigChoice* iConfigVolumeControlEnabled;
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
    static const Brn kConfigKey;
public:
    BalanceUser(IBalance& aBalance, Configuration::IConfigInitialiser& aConfigInit, TInt aDefault, TUint aMax);
    ~BalanceUser();
public: // from IBalance
    void SetBalance(TInt aBalance) override;
private:
    void BalanceChanged(Configuration::ConfigNum::KvpNum& aKvp);
private:
    IBalance& iBalance;
    Configuration::ConfigNum* iConfigBalance;
    TUint iSubscriberIdBalance;
};

class FadeUser : public IFade, private INonCopyable
{
public:
    static const Brn kConfigKey;
public:
    FadeUser(IFade& aFade, Configuration::IConfigInitialiser& aConfigInit, TInt aDefault, TUint aMax);
    ~FadeUser();
public: // from IFade
    void SetFade(TInt aFade) override;
private:
    void FadeChanged(Configuration::ConfigNum::KvpNum& aKvp);
private:
    IFade& iFade;
    Configuration::ConfigNum* iConfigFade;
    TUint iSubscriberIdFade;
};

class MuteUser : public Media::IMute, private INonCopyable
{
    static const Brn kStoreKey;
    static const TUint kMuted   = 1;
    static const TUint kUnmuted = 0;
public:
    MuteUser(Media::IMute& aMute, Configuration::IStoreReadWrite& aStore, IPowerManager& aPowerManager);
public: // from Media::IMute
    void Mute() override;
    void Unmute() override;
private:
    Media::IMute& iMute;
    StoreInt iStoreUserMute;
};

class MuteReporter : public Media::IMute, private INonCopyable
{
public:
    MuteReporter(Media::IMute& aMute);
    void AddObserver(Media::IMuteObserver& aObserver);
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

class IVolumeManager : public IVolume, public IVolumeProfile, public Media::IMute
{
public:
    virtual void AddObserver(IVolumeObserver& aObserver) = 0;
    virtual void AddObserver(Media::IMuteObserver& aObserver) = 0;
    virtual ~IVolumeManager() {}
};

class VolumeManager : public IVolumeManager
                    , public IVolumeSourceOffset
                    , public IVolumeSourceUnityGain
                    , private IBalance
                    , private IFade
                    , private INonCopyable
{
public:
    VolumeManager(const VolumeInitParams& aInitParams,
                  Configuration::IStoreReadWrite& aStore,
                  Configuration::IConfigInitialiser& aConfigInit,
                  IPowerManager& aPowerManager,
                  Net::DvDevice& aDevice,
                  Product& aProduct,
                  Configuration::IConfigManager& aConfigReader);
    ~VolumeManager();
public: // from IVolumeManager
    void AddObserver(IVolumeObserver& aObserver) override;
    void AddObserver(Media::IMuteObserver& aObserver) override;
public: // from IVolumeSourceOffset
    void SetVolumeOffset(TInt aValue) override;
public: // from IVolumeSourceUnityGain
    void SetUnityGain(TBool aEnable) override;
private: // from IVolumeProfile
    TUint VolumeMax() override;
    TUint VolumeDefault() override;
    TUint VolumeUnity() override;
    TUint VolumeDefaultLimit() override;
    TUint VolumeStep() override;
    TUint VolumeMilliDbPerStep() override;
    TUint BalanceMax() override;
    TUint FadeMax() override;
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
    const VolumeInitParams iInitParams;
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

} // namespace Av
} // namespace OpenHome

#endif // HEADER_AV_VOLUME_MANAGER
