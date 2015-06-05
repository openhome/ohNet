#ifndef HEADER_PROVIDER_RENDERINGCONTROL
#define HEADER_PROVIDER_RENDERINGCONTROL

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <Generated/DvUpnpOrgRenderingControl1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Av/VolumeManager.h>

namespace OpenHome {
using namespace Net;
namespace Av {

class ProviderRenderingControl : public DvProviderUpnpOrgRenderingControl1, private IVolumeObserver, private Media::IMuteObserver
{
public:
    static const Brn kChannelMaster;
    static const Brn kPresetNameFactoryDefaults;
    static const TUint kEventModerationMs = 200;
    static const TUint kVolumeReportedSteps = 100;
public:
    ProviderRenderingControl(Net::DvDevice& aDevice, Environment& aEnv, IVolumeManager& aVolumeManager);
    ~ProviderRenderingControl();
private: // from DvProviderUpnpOrgRenderingControl1
    void ListPresets(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseString& aCurrentPresetNameList) override;
    void SelectPreset(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aPresetName) override;
    void GetMute(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, IDvInvocationResponseBool& aCurrentMute) override;
    void SetMute(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute) override;
    void GetVolume(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, IDvInvocationResponseUint& aCurrentVolume) override;
    void SetVolume(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume) override;
    void GetVolumeDB(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, IDvInvocationResponseInt& aCurrentVolume) override;
    void SetVolumeDB(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume) override;
    void GetVolumeDBRange(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, IDvInvocationResponseInt& aMinValue, IDvInvocationResponseInt& aMaxValue) override;
private: // from IVolumeObserver
    void VolumeChanged(TUint aVolume) override;
private: // from Media::IMuteObserver
    void MuteChanged(TBool aValue) override;
private:
    void UpdateVolumeDb();
    void ScheduleUpdate();
    void ModerationTimerExpired();
    void UpdateLastChange();
    void AppendInt(TInt aValue);
private:
    Mutex iLock;
    Timer* iModerationTimer;
    Bws<1024> iLastChange;
    IVolume& iVolume;
    TUint iVolumeCurrent;
    TInt iVolumeDb; // deviation from iVolumeUnity.  256 units per 1 volume unit.
    const TUint iVolumeMax;
    const TUint iVolumeUnity;
    const TUint iVolumeMilliDbPerStep;
    Media::IMute& iUserMute;
    TBool iMuted;
    TBool iModerationTimerStarted;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_RENDERINGCONTROL
