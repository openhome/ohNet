#ifndef HEADER_PROVIDER_RENDERINGCONTROL
#define HEADER_PROVIDER_RENDERINGCONTROL

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <Generated/DvUpnpOrgRenderingControl1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>

namespace OpenHome {
using namespace Net;
namespace Av {

class ProviderRenderingControl : public DvProviderUpnpOrgRenderingControl1
{
public:
    static const Brn kChannelMaster;
    static const Brn kPresetNameFactoryDefaults;
public:
    ProviderRenderingControl(Net::DvDevice& aDevice);
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
private:
    void UpdateLastChange();
private:
    Bws<1024> iLastChange;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_RENDERINGCONTROL
