#ifndef HEADER_PROVIDER_VOLUME_1
#define HEADER_PROVIDER_VOLUME_1

#include <Generated/DvAvOpenhomeOrgVolume1.h>

#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Media/MuteManager.h>
#include <OpenHome/Media/VolumeManager.h>

#include <OpenHome/Private/Thread.h>

namespace OpenHome {

using namespace Net;
using namespace Media;

namespace Av {

class ProviderVolume : public DvProviderAvOpenhomeOrgVolume1
{
public:
    ProviderVolume(DvDevice& aDevice, IMuteManager& aMuteManager, IVolumeManagerLimits& aVolumeManager);
    ~ProviderVolume();
private: // from DvProviderAvOpenhomeOrgVolume1 (and only ever invoked from base class)
    virtual void Characteristics(IDvInvocation& aInvocation, IDvInvocationResponseUint& aVolumeMax, IDvInvocationResponseUint& aVolumeUnity, IDvInvocationResponseUint& aVolumeSteps, IDvInvocationResponseUint& aVolumeMilliDbPerStep, IDvInvocationResponseUint& aBalanceMax, IDvInvocationResponseUint& aFadeMax);

    void SetVolume(IDvInvocation& aInvocation, TUint aValue);
    void VolumeInc(IDvInvocation& aInvocation);
    void VolumeDec(IDvInvocation& aInvocation);
    void Volume(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);

    void SetBalance(IDvInvocation& aInvocation, TInt aValue);
    void BalanceInc(IDvInvocation& aInvocation);
    void BalanceDec(IDvInvocation& aInvocation);
    void Balance(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValue);

    void SetFade(IDvInvocation& aInvocation, TInt aValue);
    void FadeInc(IDvInvocation& aInvocation);
    void FadeDec(IDvInvocation& aInvocation);
    void Fade(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValue);

    void SetMute(IDvInvocation& aInvocation, TBool aValue);
    void Mute(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue);

    void VolumeLimit(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
private:
    IMuteManager& iMuteManager;
    IVolumeManagerLimits& iVolumeManager;
    Mutex iLock;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_VOLUME_1
