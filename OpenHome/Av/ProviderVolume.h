#ifndef HEADER_PROVIDER_VOLUME_1
#define HEADER_PROVIDER_VOLUME_1

#include <Generated/DvAvOpenhomeOrgVolume1.h>
#include <OpenHome/Av/ProviderFactory.h>

#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {

namespace Media {
    class IVolumeProfile;
    class IVolume;
    class IBalance;
    class IMute;
}
namespace Net {
    class IDvInvocationResponseInt;
}

namespace Av {

class ProviderVolume : public Net::DvProviderAvOpenhomeOrgVolume1, public IProvider
{
public:
    static const Brn kBalance;
    static const Brn kVolumeLimit;
    static const Brn kVolumeStartup;
    static const Brn kVolumeStartupEnabled;
public:
    ProviderVolume(Net::DvDevice& aDevice, Configuration::IConfigManagerWriter& aConfigManager, Media::IVolumeProfile& aVolumeProfile, Media::IVolume& aVolume, Media::IBalance& aBalance, Media::IMute& aMute);
    ~ProviderVolume();
private: // from DvProviderAvOpenhomeOrgVolume1 (and only ever invoked from base class)
    virtual void Characteristics(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aVolumeMax, Net::IDvInvocationResponseUint& aVolumeUnity, Net::IDvInvocationResponseUint& aVolumeSteps, Net::IDvInvocationResponseUint& aVolumeMilliDbPerStep, Net::IDvInvocationResponseUint& aBalanceMax, Net::IDvInvocationResponseUint& aFadeMax);

    void SetVolume(Net::IDvInvocation& aInvocation, TUint aValue);
    void VolumeInc(Net::IDvInvocation& aInvocation);
    void VolumeDec(Net::IDvInvocation& aInvocation);
    void Volume(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue);

    void SetBalance(Net::IDvInvocation& aInvocation, TInt aValue);
    void BalanceInc(Net::IDvInvocation& aInvocation);
    void BalanceDec(Net::IDvInvocation& aInvocation);
    void Balance(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseInt& aValue);

    void SetFade(Net::IDvInvocation& aInvocation, TInt aValue);
    void FadeInc(Net::IDvInvocation& aInvocation);
    void FadeDec(Net::IDvInvocation& aInvocation);
    void Fade(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseInt& aValue);

    void SetMute(Net::IDvInvocation& aInvocation, TBool aValue);
    void Mute(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aValue);

    void VolumeLimit(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue);
private:
    void HelperSetVolume(Net::IDvInvocation& aInvocation, TUint aVolumeCurrent, TUint aVolumeNew);
    void ConfigBalanceChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void ConfigVolumeLimitChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void ConfigVolumeStartupChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void ConfigVolumeStartupEnabledChanged(Configuration::ConfigChoice::KvpChoice& aKvp);
private:
    static const TUint kVolumeStartupDefault = 10;

    Configuration::IConfigManagerWriter& iConfigManager;
    Media::IVolumeProfile& iVolumeProfile;
    Media::IVolume& iVolumeSetter;
    Media::IBalance& iBalanceSetter; // balance set via volume and configuration services
    Media::IMute& iMuteSetter;

    Configuration::ConfigNum* iConfigBalance;
    Configuration::ConfigNum* iConfigVolumeLimit;
    Configuration::ConfigNum* iConfigVolumeStartup;
    Configuration::ConfigChoice* iConfigVolumeStartupEnabled;

    TUint iListenerIdBalance;
    TUint iListenerIdVolumeLimit;

    TUint iVolumeStartup;
    TUint iVolumeStartupEnabled;
    Mutex iLock;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_VOLUME_1
