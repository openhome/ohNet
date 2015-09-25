#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <Generated/DvUpnpOrgRenderingControl1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Av/VolumeManager.h>

namespace OpenHome {
namespace Av {

class ProviderRenderingControl : public Net::DvProviderUpnpOrgRenderingControl1, private IVolumeObserver, private Media::IMuteObserver
{
public:
    static const Brn kChannelMaster;
    static const Brn kPresetNameFactoryDefaults;
    static const TUint kEventModerationMs = 200;
    static const TUint kVolumeReportedSteps = 100;
public:
    ProviderRenderingControl(Net::DvDevice& aDevice, Environment& aEnv, IVolumeManager& aVolumeManager);
    ~ProviderRenderingControl();
private: // from Net::DvProviderUpnpOrgRenderingControl1
    void ListPresets(Net::IDvInvocation& aInvocation, TUint aInstanceID, Net::IDvInvocationResponseString& aCurrentPresetNameList) override;
    void SelectPreset(Net::IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aPresetName) override;
    void GetMute(Net::IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, Net::IDvInvocationResponseBool& aCurrentMute) override;
    void SetMute(Net::IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute) override;
    void GetVolume(Net::IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, Net::IDvInvocationResponseUint& aCurrentVolume) override;
    void SetVolume(Net::IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume) override;
    void GetVolumeDB(Net::IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, Net::IDvInvocationResponseInt& aCurrentVolume) override;
    void SetVolumeDB(Net::IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume) override;
    void GetVolumeDBRange(Net::IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aChannel, Net::IDvInvocationResponseInt& aMinValue, Net::IDvInvocationResponseInt& aMaxValue) override;
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

