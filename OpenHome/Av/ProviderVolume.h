#pragma once

#include <Generated/DvAvOpenhomeOrgVolume3.h>
#include <OpenHome/Av/ProviderFactory.h>
#include <OpenHome/Av/VolumeManager.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/VolumeOffsets.h>
#include <OpenHome/Json.h>

EXCEPTION(InvalidVolumeLimit);

namespace OpenHome {

namespace Media {
    class IMute;
}
namespace Net {
    class IDvInvocationResponseInt;
}

namespace Av {

class OffsetsWriterJson : public IVolumeOffsetterVisitor
{
private:
    static const TChar* kKeyChannel;
    static const TChar* kKeyOffset;
public:
    OffsetsWriterJson(IWriter& aWriter);
    void WriteStart();
    void WriteEnd();
public: // from IVolumeOffsetterVisitor
    void Visit(const Brx& aChannel, TInt aOffsetBinaryMilliDb) override;
private:
    WriterJsonArray iWriter;
};

class ProviderVolume : public Net::DvProviderAvOpenhomeOrgVolume3, public IProvider, private IVolumeObserver, private Media::IMuteObserver, private IUnityGainObserver, private IVolumeOffsetterObserver
{
private:
    static const Brn kPowerDownVolume;
    static const Brn kPowerDownMute;
public:
    ProviderVolume(Net::DvDevice& aDevice, Configuration::IConfigManager& aConfigReader,
        IVolumeManager& aVolumeManager, IBalance* aBalance, IFade* aFade, IVolumeOffsetter* aVolumeOffsetter);
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

    void UnityGain(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aValue) override;

    void VolumeOffset(Net::IDvInvocation& aInvocation, const Brx& aChannel, Net::IDvInvocationResponseInt& aVolumeOffsetBinaryMilliDb) override;
    void SetVolumeOffset(Net::IDvInvocation& aInvocation, const Brx& aChannel, TInt aVolumeOffsetBinaryMilliDb) override;
private: // from IVolumeObserver
    void VolumeChanged(const IVolumeValue& aVolume) override;
private: // from Media::IMuteObserver
    void MuteChanged(TBool aValue) override;
private: // from IUnityGainObserver
    void UnityGainChanged(TBool aValue) override;
private: // from IVolumeOffsetterObserver
    void VolumeOffsetsChanged(IVolumeOffsetterVisitable& aVisitable) override;
private:
    enum class ErrorOutOfRange {
        Report,
        Ignore
    };
private:
    void HelperSetVolume(Net::IDvInvocation& aInvocation, TUint aVolume, ErrorOutOfRange aReportOutOfRange);
    void HelperSetBalance(Net::IDvInvocation& aInvocation, TInt aBalance, ErrorOutOfRange aReportOutOfRange);
    void HelperSetFade(Net::IDvInvocation& aInvocation, TInt aFade, ErrorOutOfRange aReportOutOfRange);
    void VolumeLimitChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void BalanceChanged(Configuration::ConfigNum::KvpNum& aKvp);
    void FadeChanged(Configuration::ConfigNum::KvpNum& aKvp);
private:
    Mutex iLock;
    IVolume& iVolume;
    IBalance* iBalance;
    IFade* iFade;
    IVolumeOffsetter* iVolumeOffsetter;
    Media::IMute& iUserMute;
    const TUint iVolumeMax;
    Configuration::ConfigNum* iConfigVolumeLimit;
    Configuration::ConfigNum* iConfigBalance;
    Configuration::ConfigNum* iConfigFade;
    TUint iSubscriberIdVolumeLimit;
    TUint iSubscriberIdBalance;
    TUint iSubscriberIdFade;
};

} // namespace Av
} // namespace OpenHome
