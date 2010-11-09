#include <C/DvLinnCoUkComponent1.h>
#include <Core/DvLinnCoUkComponent1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkComponent1C : public DvProviderLinnCoUkComponent1
{
public:
    DvProviderLinnCoUkComponent1C(DvDevice& aDevice);
    void EnableActionAmplifierEnabled(CallbackComponent1AmplifierEnabled aCallback, void* aPtr);
    void EnableActionSetAmplifierEnabled(CallbackComponent1SetAmplifierEnabled aCallback, void* aPtr);
    void EnableActionAmplifierAttenuation(CallbackComponent1AmplifierAttenuation aCallback, void* aPtr);
    void EnableActionSetAmplifierAttenuation(CallbackComponent1SetAmplifierAttenuation aCallback, void* aPtr);
    void EnableActionSetVolumeControlEnabled(CallbackComponent1SetVolumeControlEnabled aCallback, void* aPtr);
    void EnableActionVolumeControlEnabled(CallbackComponent1VolumeControlEnabled aCallback, void* aPtr);
    void EnableActionSetDigitalAudioOutputRaw(CallbackComponent1SetDigitalAudioOutputRaw aCallback, void* aPtr);
    void EnableActionDigitalAudioOutputRaw(CallbackComponent1DigitalAudioOutputRaw aCallback, void* aPtr);
    void EnableActionAmplifierOverTemperature(CallbackComponent1AmplifierOverTemperature aCallback, void* aPtr);
    void EnableActionEthernetLinkConnected(CallbackComponent1EthernetLinkConnected aCallback, void* aPtr);
    void EnableActionLocate(CallbackComponent1Locate aCallback, void* aPtr);
private:
    void AmplifierEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled);
    void SetAmplifierEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    void AmplifierAttenuation(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaAttenuation);
    void SetAmplifierAttenuation(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaAttenuation);
    void SetVolumeControlEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    void VolumeControlEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled);
    void SetDigitalAudioOutputRaw(IInvocationResponse& aResponse, TUint aVersion, TBool aaRaw);
    void DigitalAudioOutputRaw(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaRaw);
    void AmplifierOverTemperature(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaOverTemperature);
    void EthernetLinkConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaLinkConnected);
    void Locate(IInvocationResponse& aResponse, TUint aVersion);
private:
    CallbackComponent1AmplifierEnabled iCallbackAmplifierEnabled;
    void* iPtrAmplifierEnabled;
    CallbackComponent1SetAmplifierEnabled iCallbackSetAmplifierEnabled;
    void* iPtrSetAmplifierEnabled;
    CallbackComponent1AmplifierAttenuation iCallbackAmplifierAttenuation;
    void* iPtrAmplifierAttenuation;
    CallbackComponent1SetAmplifierAttenuation iCallbackSetAmplifierAttenuation;
    void* iPtrSetAmplifierAttenuation;
    CallbackComponent1SetVolumeControlEnabled iCallbackSetVolumeControlEnabled;
    void* iPtrSetVolumeControlEnabled;
    CallbackComponent1VolumeControlEnabled iCallbackVolumeControlEnabled;
    void* iPtrVolumeControlEnabled;
    CallbackComponent1SetDigitalAudioOutputRaw iCallbackSetDigitalAudioOutputRaw;
    void* iPtrSetDigitalAudioOutputRaw;
    CallbackComponent1DigitalAudioOutputRaw iCallbackDigitalAudioOutputRaw;
    void* iPtrDigitalAudioOutputRaw;
    CallbackComponent1AmplifierOverTemperature iCallbackAmplifierOverTemperature;
    void* iPtrAmplifierOverTemperature;
    CallbackComponent1EthernetLinkConnected iCallbackEthernetLinkConnected;
    void* iPtrEthernetLinkConnected;
    CallbackComponent1Locate iCallbackLocate;
    void* iPtrLocate;
};

DvProviderLinnCoUkComponent1C::DvProviderLinnCoUkComponent1C(DvDevice& aDevice)
    : DvProviderLinnCoUkComponent1(aDevice)
{
}

void DvProviderLinnCoUkComponent1C::EnableActionAmplifierEnabled(CallbackComponent1AmplifierEnabled aCallback, void* aPtr)
{
    iCallbackAmplifierEnabled = aCallback;
    iPtrAmplifierEnabled = aPtr;
    DvProviderLinnCoUkComponent1::EnableActionAmplifierEnabled();
}

void DvProviderLinnCoUkComponent1C::EnableActionSetAmplifierEnabled(CallbackComponent1SetAmplifierEnabled aCallback, void* aPtr)
{
    iCallbackSetAmplifierEnabled = aCallback;
    iPtrSetAmplifierEnabled = aPtr;
    DvProviderLinnCoUkComponent1::EnableActionSetAmplifierEnabled();
}

void DvProviderLinnCoUkComponent1C::EnableActionAmplifierAttenuation(CallbackComponent1AmplifierAttenuation aCallback, void* aPtr)
{
    iCallbackAmplifierAttenuation = aCallback;
    iPtrAmplifierAttenuation = aPtr;
    DvProviderLinnCoUkComponent1::EnableActionAmplifierAttenuation();
}

void DvProviderLinnCoUkComponent1C::EnableActionSetAmplifierAttenuation(CallbackComponent1SetAmplifierAttenuation aCallback, void* aPtr)
{
    iCallbackSetAmplifierAttenuation = aCallback;
    iPtrSetAmplifierAttenuation = aPtr;
    DvProviderLinnCoUkComponent1::EnableActionSetAmplifierAttenuation();
}

void DvProviderLinnCoUkComponent1C::EnableActionSetVolumeControlEnabled(CallbackComponent1SetVolumeControlEnabled aCallback, void* aPtr)
{
    iCallbackSetVolumeControlEnabled = aCallback;
    iPtrSetVolumeControlEnabled = aPtr;
    DvProviderLinnCoUkComponent1::EnableActionSetVolumeControlEnabled();
}

void DvProviderLinnCoUkComponent1C::EnableActionVolumeControlEnabled(CallbackComponent1VolumeControlEnabled aCallback, void* aPtr)
{
    iCallbackVolumeControlEnabled = aCallback;
    iPtrVolumeControlEnabled = aPtr;
    DvProviderLinnCoUkComponent1::EnableActionVolumeControlEnabled();
}

void DvProviderLinnCoUkComponent1C::EnableActionSetDigitalAudioOutputRaw(CallbackComponent1SetDigitalAudioOutputRaw aCallback, void* aPtr)
{
    iCallbackSetDigitalAudioOutputRaw = aCallback;
    iPtrSetDigitalAudioOutputRaw = aPtr;
    DvProviderLinnCoUkComponent1::EnableActionSetDigitalAudioOutputRaw();
}

void DvProviderLinnCoUkComponent1C::EnableActionDigitalAudioOutputRaw(CallbackComponent1DigitalAudioOutputRaw aCallback, void* aPtr)
{
    iCallbackDigitalAudioOutputRaw = aCallback;
    iPtrDigitalAudioOutputRaw = aPtr;
    DvProviderLinnCoUkComponent1::EnableActionDigitalAudioOutputRaw();
}

void DvProviderLinnCoUkComponent1C::EnableActionAmplifierOverTemperature(CallbackComponent1AmplifierOverTemperature aCallback, void* aPtr)
{
    iCallbackAmplifierOverTemperature = aCallback;
    iPtrAmplifierOverTemperature = aPtr;
    DvProviderLinnCoUkComponent1::EnableActionAmplifierOverTemperature();
}

void DvProviderLinnCoUkComponent1C::EnableActionEthernetLinkConnected(CallbackComponent1EthernetLinkConnected aCallback, void* aPtr)
{
    iCallbackEthernetLinkConnected = aCallback;
    iPtrEthernetLinkConnected = aPtr;
    DvProviderLinnCoUkComponent1::EnableActionEthernetLinkConnected();
}

void DvProviderLinnCoUkComponent1C::EnableActionLocate(CallbackComponent1Locate aCallback, void* aPtr)
{
    iCallbackLocate = aCallback;
    iPtrLocate = aPtr;
    DvProviderLinnCoUkComponent1::EnableActionLocate();
}

void DvProviderLinnCoUkComponent1C::AmplifierEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled)
{
    uint32_t aEnabled;
    ASSERT(iCallbackAmplifierEnabled != NULL);
    if (0 != iCallbackAmplifierEnabled(iPtrAmplifierEnabled, aVersion, &aEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaEnabled.Write((aEnabled!=0));
    aResponse.End();
}

void DvProviderLinnCoUkComponent1C::SetAmplifierEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled)
{
    ASSERT(iCallbackSetAmplifierEnabled != NULL);
    if (0 != iCallbackSetAmplifierEnabled(iPtrSetAmplifierEnabled, aVersion, aaEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkComponent1C::AmplifierAttenuation(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaAttenuation)
{
    char* aAttenuation;
    ASSERT(iCallbackAmplifierAttenuation != NULL);
    if (0 != iCallbackAmplifierAttenuation(iPtrAmplifierAttenuation, aVersion, &aAttenuation)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaAttenuation((const TChar*)aAttenuation);
    ZappFreeExternal(aAttenuation);
    aaAttenuation.Write(bufaAttenuation);
    aaAttenuation.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkComponent1C::SetAmplifierAttenuation(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaAttenuation)
{
    ASSERT(iCallbackSetAmplifierAttenuation != NULL);
    if (0 != iCallbackSetAmplifierAttenuation(iPtrSetAmplifierAttenuation, aVersion, (const char*)aaAttenuation.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkComponent1C::SetVolumeControlEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled)
{
    ASSERT(iCallbackSetVolumeControlEnabled != NULL);
    if (0 != iCallbackSetVolumeControlEnabled(iPtrSetVolumeControlEnabled, aVersion, aaEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkComponent1C::VolumeControlEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled)
{
    uint32_t aEnabled;
    ASSERT(iCallbackVolumeControlEnabled != NULL);
    if (0 != iCallbackVolumeControlEnabled(iPtrVolumeControlEnabled, aVersion, &aEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaEnabled.Write((aEnabled!=0));
    aResponse.End();
}

void DvProviderLinnCoUkComponent1C::SetDigitalAudioOutputRaw(IInvocationResponse& aResponse, TUint aVersion, TBool aaRaw)
{
    ASSERT(iCallbackSetDigitalAudioOutputRaw != NULL);
    if (0 != iCallbackSetDigitalAudioOutputRaw(iPtrSetDigitalAudioOutputRaw, aVersion, aaRaw)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkComponent1C::DigitalAudioOutputRaw(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaRaw)
{
    uint32_t aRaw;
    ASSERT(iCallbackDigitalAudioOutputRaw != NULL);
    if (0 != iCallbackDigitalAudioOutputRaw(iPtrDigitalAudioOutputRaw, aVersion, &aRaw)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaRaw.Write((aRaw!=0));
    aResponse.End();
}

void DvProviderLinnCoUkComponent1C::AmplifierOverTemperature(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaOverTemperature)
{
    uint32_t aOverTemperature;
    ASSERT(iCallbackAmplifierOverTemperature != NULL);
    if (0 != iCallbackAmplifierOverTemperature(iPtrAmplifierOverTemperature, aVersion, &aOverTemperature)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaOverTemperature.Write((aOverTemperature!=0));
    aResponse.End();
}

void DvProviderLinnCoUkComponent1C::EthernetLinkConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaLinkConnected)
{
    uint32_t aLinkConnected;
    ASSERT(iCallbackEthernetLinkConnected != NULL);
    if (0 != iCallbackEthernetLinkConnected(iPtrEthernetLinkConnected, aVersion, &aLinkConnected)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaLinkConnected.Write((aLinkConnected!=0));
    aResponse.End();
}

void DvProviderLinnCoUkComponent1C::Locate(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackLocate != NULL);
    if (0 != iCallbackLocate(iPtrLocate, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvProviderLinnCoUkComponent1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkComponent1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkComponent1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider);
}

void DvProviderLinnCoUkComponent1EnableActionAmplifierEnabled(THandle aProvider, CallbackComponent1AmplifierEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionAmplifierEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionSetAmplifierEnabled(THandle aProvider, CallbackComponent1SetAmplifierEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionSetAmplifierEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionAmplifierAttenuation(THandle aProvider, CallbackComponent1AmplifierAttenuation aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionAmplifierAttenuation(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionSetAmplifierAttenuation(THandle aProvider, CallbackComponent1SetAmplifierAttenuation aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionSetAmplifierAttenuation(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionSetVolumeControlEnabled(THandle aProvider, CallbackComponent1SetVolumeControlEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionSetVolumeControlEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionVolumeControlEnabled(THandle aProvider, CallbackComponent1VolumeControlEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionVolumeControlEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionSetDigitalAudioOutputRaw(THandle aProvider, CallbackComponent1SetDigitalAudioOutputRaw aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionSetDigitalAudioOutputRaw(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionDigitalAudioOutputRaw(THandle aProvider, CallbackComponent1DigitalAudioOutputRaw aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionDigitalAudioOutputRaw(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionAmplifierOverTemperature(THandle aProvider, CallbackComponent1AmplifierOverTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionAmplifierOverTemperature(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionEthernetLinkConnected(THandle aProvider, CallbackComponent1EthernetLinkConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionEthernetLinkConnected(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionLocate(THandle aProvider, CallbackComponent1Locate aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionLocate(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkComponent1SetPropertyAmplifierEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->SetPropertyAmplifierEnabled((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkComponent1GetPropertyAmplifierEnabled(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->GetPropertyAmplifierEnabled(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkComponent1SetPropertyAmplifierAttenuation(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->SetPropertyAmplifierAttenuation(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkComponent1GetPropertyAmplifierAttenuation(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->GetPropertyAmplifierAttenuation(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkComponent1SetPropertyVolumeControlEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->SetPropertyVolumeControlEnabled((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkComponent1GetPropertyVolumeControlEnabled(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->GetPropertyVolumeControlEnabled(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkComponent1SetPropertyDigitalAudioOutputRaw(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->SetPropertyDigitalAudioOutputRaw((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkComponent1GetPropertyDigitalAudioOutputRaw(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->GetPropertyDigitalAudioOutputRaw(val);
    *aValue = (val? 1 : 0);
}

