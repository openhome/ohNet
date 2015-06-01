#ifndef HEADER_PROVIDER_VOLUME_1
#define HEADER_PROVIDER_VOLUME_1

#include <Generated/DvAvOpenhomeOrgVolume1.h>
#include <OpenHome/Av/ProviderFactory.h>
#include <OpenHome/Av/VolumeManager.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Private/Thread.h>

EXCEPTION(InvalidVolumeLimit);

namespace OpenHome {

namespace Media {
    class IMute;
}
namespace Net {
    class IDvInvocationResponseInt;
}

namespace Av {

class ProviderVolume : public Net::DvProviderAvOpenhomeOrgVolume1, public IProvider, private IVolumeObserver
{
private:
    static const Brn kPowerDownVolume;
    static const Brn kPowerDownMute;
public:
    ProviderVolume(Net::DvDevice& aDevice,
                   Configuration::IConfigManager& aConfigReader,
                   IVolumeManager& aVolumeManager, IVolume& aVolume,
                   TUint aVolumeMax, TUint aVolumeUnity, TUint aVolumeStep, TUint aVolumeMilliDbPerStep,
                   IBalance* aBalance, TUint aBalanceMax,
                   IFade* aFade, TUint aFadeMax);
    ~ProviderVolume();
private: // from DvProviderAvOpenhomeOrgVolume1
    void Characteristics(Net::IDvInvocation& aInvocation
                        ,Net::IDvInvocationResponseUint& aVolumeMax
                        ,Net::IDvInvocationResponseUint& aVolumeUnity
                        ,Net::IDvInvocationResponseUint& aVolumeSteps
                        ,Net::IDvInvocationResponseUint& aVolumeMilliDbPerStep
                        ,Net::IDvInvocationResponseUint& aBalanceMax
                        ,Net::IDvInvocationResponseUint& aFadeMax) override;

    void SetVolume(Net::IDvInvocation& aInvocation, TUint aValue) override;
    void VolumeInc(Net::IDvInvocation& aInvocation) override;
    void VolumeDec(Net::IDvInvocation& aInvocation) override;
    void Volume(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue) override;

    void SetBalance(Net::IDvInvocation& aInvocation, TInt aValue) override;
    void BalanceInc(Net::IDvInvocation& aInvocation) override;
    void BalanceDec(Net::IDvInvocation& aInvocation) override;
    void Balance(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseInt& aValue) override;

    void SetFade(Net::IDvInvocation& aInvocation, TInt aValue) override;
    void FadeInc(Net::IDvInvocation& aInvocation) override;
    void FadeDec(Net::IDvInvocation& aInvocation) override;
    void Fade(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseInt& aValue) override;

    void SetMute(Net::IDvInvocation& aInvocation, TBool aValue) override;
    void Mute(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aValue) override;

    void VolumeLimit(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue) override;
private: // from IVolumeObserver
    void VolumeChanged(TUint aVolume) override;
private:
    void HelperSetVolume(Net::IDvInvocation& aInvocation, TUint aVolume);
    void HelperSetBalance(Net::IDvInvocation& aInvocation, TInt aBalance);
    void HelperSetFade(Net::IDvInvocation& aInvocation, TInt aFade);
    void VolumeLimitChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void BalanceChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void FadeChanged(Configuration::ConfigNum::KvpNum& aKvp);
private:
    Mutex iLock;
    IVolume& iVolume;
    IBalance* iBalance;
    IFade* iFade;
    //Media::IMute& iMuteSetter;
    Configuration::ConfigNum* iConfigVolumeLimit;
    Configuration::ConfigNum* iConfigBalance;
    Configuration::ConfigNum* iConfigFade;
    TUint iSubscriberIdVolumeLimit;
    TUint iSubscriberIdBalance;
    TUint iSubscriberIdFade;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_VOLUME_1
