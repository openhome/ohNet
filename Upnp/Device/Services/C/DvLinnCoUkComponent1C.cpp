#include <C/DvLinnCoUkComponent1.h>
#include <Core/DvLinnCoUkComponent1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkComponent1C : public DvServiceLinnCoUkComponent1
{
public:
    DvServiceLinnCoUkComponent1C(DvDevice& aDevice);
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

DvServiceLinnCoUkComponent1C::DvServiceLinnCoUkComponent1C(DvDevice& aDevice)
    : DvServiceLinnCoUkComponent1(aDevice)
{
}

void DvServiceLinnCoUkComponent1C::EnableActionAmplifierEnabled(CallbackComponent1AmplifierEnabled aCallback, void* aPtr)
{
    iCallbackAmplifierEnabled = aCallback;
    iPtrAmplifierEnabled = aPtr;
    DvServiceLinnCoUkComponent1::EnableActionAmplifierEnabled();
}

void DvServiceLinnCoUkComponent1C::EnableActionSetAmplifierEnabled(CallbackComponent1SetAmplifierEnabled aCallback, void* aPtr)
{
    iCallbackSetAmplifierEnabled = aCallback;
    iPtrSetAmplifierEnabled = aPtr;
    DvServiceLinnCoUkComponent1::EnableActionSetAmplifierEnabled();
}

void DvServiceLinnCoUkComponent1C::EnableActionAmplifierAttenuation(CallbackComponent1AmplifierAttenuation aCallback, void* aPtr)
{
    iCallbackAmplifierAttenuation = aCallback;
    iPtrAmplifierAttenuation = aPtr;
    DvServiceLinnCoUkComponent1::EnableActionAmplifierAttenuation();
}

void DvServiceLinnCoUkComponent1C::EnableActionSetAmplifierAttenuation(CallbackComponent1SetAmplifierAttenuation aCallback, void* aPtr)
{
    iCallbackSetAmplifierAttenuation = aCallback;
    iPtrSetAmplifierAttenuation = aPtr;
    DvServiceLinnCoUkComponent1::EnableActionSetAmplifierAttenuation();
}

void DvServiceLinnCoUkComponent1C::EnableActionSetVolumeControlEnabled(CallbackComponent1SetVolumeControlEnabled aCallback, void* aPtr)
{
    iCallbackSetVolumeControlEnabled = aCallback;
    iPtrSetVolumeControlEnabled = aPtr;
    DvServiceLinnCoUkComponent1::EnableActionSetVolumeControlEnabled();
}

void DvServiceLinnCoUkComponent1C::EnableActionVolumeControlEnabled(CallbackComponent1VolumeControlEnabled aCallback, void* aPtr)
{
    iCallbackVolumeControlEnabled = aCallback;
    iPtrVolumeControlEnabled = aPtr;
    DvServiceLinnCoUkComponent1::EnableActionVolumeControlEnabled();
}

void DvServiceLinnCoUkComponent1C::EnableActionSetDigitalAudioOutputRaw(CallbackComponent1SetDigitalAudioOutputRaw aCallback, void* aPtr)
{
    iCallbackSetDigitalAudioOutputRaw = aCallback;
    iPtrSetDigitalAudioOutputRaw = aPtr;
    DvServiceLinnCoUkComponent1::EnableActionSetDigitalAudioOutputRaw();
}

void DvServiceLinnCoUkComponent1C::EnableActionDigitalAudioOutputRaw(CallbackComponent1DigitalAudioOutputRaw aCallback, void* aPtr)
{
    iCallbackDigitalAudioOutputRaw = aCallback;
    iPtrDigitalAudioOutputRaw = aPtr;
    DvServiceLinnCoUkComponent1::EnableActionDigitalAudioOutputRaw();
}

void DvServiceLinnCoUkComponent1C::EnableActionAmplifierOverTemperature(CallbackComponent1AmplifierOverTemperature aCallback, void* aPtr)
{
    iCallbackAmplifierOverTemperature = aCallback;
    iPtrAmplifierOverTemperature = aPtr;
    DvServiceLinnCoUkComponent1::EnableActionAmplifierOverTemperature();
}

void DvServiceLinnCoUkComponent1C::EnableActionEthernetLinkConnected(CallbackComponent1EthernetLinkConnected aCallback, void* aPtr)
{
    iCallbackEthernetLinkConnected = aCallback;
    iPtrEthernetLinkConnected = aPtr;
    DvServiceLinnCoUkComponent1::EnableActionEthernetLinkConnected();
}

void DvServiceLinnCoUkComponent1C::EnableActionLocate(CallbackComponent1Locate aCallback, void* aPtr)
{
    iCallbackLocate = aCallback;
    iPtrLocate = aPtr;
    DvServiceLinnCoUkComponent1::EnableActionLocate();
}

void DvServiceLinnCoUkComponent1C::AmplifierEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled)
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

void DvServiceLinnCoUkComponent1C::SetAmplifierEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled)
{
    ASSERT(iCallbackSetAmplifierEnabled != NULL);
    if (0 != iCallbackSetAmplifierEnabled(iPtrSetAmplifierEnabled, aVersion, aaEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkComponent1C::AmplifierAttenuation(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaAttenuation)
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

void DvServiceLinnCoUkComponent1C::SetAmplifierAttenuation(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaAttenuation)
{
    ASSERT(iCallbackSetAmplifierAttenuation != NULL);
    if (0 != iCallbackSetAmplifierAttenuation(iPtrSetAmplifierAttenuation, aVersion, (const char*)aaAttenuation.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkComponent1C::SetVolumeControlEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled)
{
    ASSERT(iCallbackSetVolumeControlEnabled != NULL);
    if (0 != iCallbackSetVolumeControlEnabled(iPtrSetVolumeControlEnabled, aVersion, aaEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkComponent1C::VolumeControlEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled)
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

void DvServiceLinnCoUkComponent1C::SetDigitalAudioOutputRaw(IInvocationResponse& aResponse, TUint aVersion, TBool aaRaw)
{
    ASSERT(iCallbackSetDigitalAudioOutputRaw != NULL);
    if (0 != iCallbackSetDigitalAudioOutputRaw(iPtrSetDigitalAudioOutputRaw, aVersion, aaRaw)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkComponent1C::DigitalAudioOutputRaw(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaRaw)
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

void DvServiceLinnCoUkComponent1C::AmplifierOverTemperature(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaOverTemperature)
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

void DvServiceLinnCoUkComponent1C::EthernetLinkConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaLinkConnected)
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

void DvServiceLinnCoUkComponent1C::Locate(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackLocate != NULL);
    if (0 != iCallbackLocate(iPtrLocate, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvServiceLinnCoUkComponent1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkComponent1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkComponent1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService);
}

void DvServiceLinnCoUkComponent1EnableActionAmplifierEnabled(THandle aService, CallbackComponent1AmplifierEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->EnableActionAmplifierEnabled(aCallback, aPtr);
}

void DvServiceLinnCoUkComponent1EnableActionSetAmplifierEnabled(THandle aService, CallbackComponent1SetAmplifierEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->EnableActionSetAmplifierEnabled(aCallback, aPtr);
}

void DvServiceLinnCoUkComponent1EnableActionAmplifierAttenuation(THandle aService, CallbackComponent1AmplifierAttenuation aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->EnableActionAmplifierAttenuation(aCallback, aPtr);
}

void DvServiceLinnCoUkComponent1EnableActionSetAmplifierAttenuation(THandle aService, CallbackComponent1SetAmplifierAttenuation aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->EnableActionSetAmplifierAttenuation(aCallback, aPtr);
}

void DvServiceLinnCoUkComponent1EnableActionSetVolumeControlEnabled(THandle aService, CallbackComponent1SetVolumeControlEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->EnableActionSetVolumeControlEnabled(aCallback, aPtr);
}

void DvServiceLinnCoUkComponent1EnableActionVolumeControlEnabled(THandle aService, CallbackComponent1VolumeControlEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->EnableActionVolumeControlEnabled(aCallback, aPtr);
}

void DvServiceLinnCoUkComponent1EnableActionSetDigitalAudioOutputRaw(THandle aService, CallbackComponent1SetDigitalAudioOutputRaw aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->EnableActionSetDigitalAudioOutputRaw(aCallback, aPtr);
}

void DvServiceLinnCoUkComponent1EnableActionDigitalAudioOutputRaw(THandle aService, CallbackComponent1DigitalAudioOutputRaw aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->EnableActionDigitalAudioOutputRaw(aCallback, aPtr);
}

void DvServiceLinnCoUkComponent1EnableActionAmplifierOverTemperature(THandle aService, CallbackComponent1AmplifierOverTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->EnableActionAmplifierOverTemperature(aCallback, aPtr);
}

void DvServiceLinnCoUkComponent1EnableActionEthernetLinkConnected(THandle aService, CallbackComponent1EthernetLinkConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->EnableActionEthernetLinkConnected(aCallback, aPtr);
}

void DvServiceLinnCoUkComponent1EnableActionLocate(THandle aService, CallbackComponent1Locate aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->EnableActionLocate(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkComponent1SetPropertyAmplifierEnabled(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->SetPropertyAmplifierEnabled((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkComponent1GetPropertyAmplifierEnabled(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->GetPropertyAmplifierEnabled(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkComponent1SetPropertyAmplifierAttenuation(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->SetPropertyAmplifierAttenuation(buf);
    return 0;
}

void DvServiceLinnCoUkComponent1GetPropertyAmplifierAttenuation(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->GetPropertyAmplifierAttenuation(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkComponent1SetPropertyVolumeControlEnabled(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->SetPropertyVolumeControlEnabled((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkComponent1GetPropertyVolumeControlEnabled(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->GetPropertyVolumeControlEnabled(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkComponent1SetPropertyDigitalAudioOutputRaw(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->SetPropertyDigitalAudioOutputRaw((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkComponent1GetPropertyDigitalAudioOutputRaw(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkComponent1C*>(aService)->GetPropertyDigitalAudioOutputRaw(val);
    *aValue = (val? 1 : 0);
}

