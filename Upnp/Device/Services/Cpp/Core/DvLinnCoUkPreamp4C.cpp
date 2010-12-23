#include "DvLinnCoUkPreamp4C.h"
#include "DvLinnCoUkPreamp4.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkPreamp4C : public DvProviderLinnCoUkPreamp4
{
public:
    DvProviderLinnCoUkPreamp4C(DvDevice& aDevice);
    void EnableActionVolumeInc(CallbackPreamp4VolumeInc aCallback, void* aPtr);
    void EnableActionVolumeDec(CallbackPreamp4VolumeDec aCallback, void* aPtr);
    void EnableActionSetVolume(CallbackPreamp4SetVolume aCallback, void* aPtr);
    void EnableActionVolume(CallbackPreamp4Volume aCallback, void* aPtr);
    void EnableActionSetMute(CallbackPreamp4SetMute aCallback, void* aPtr);
    void EnableActionMute(CallbackPreamp4Mute aCallback, void* aPtr);
    void EnableActionSetBalance(CallbackPreamp4SetBalance aCallback, void* aPtr);
    void EnableActionBalance(CallbackPreamp4Balance aCallback, void* aPtr);
    void EnableActionSetVolumeLimit(CallbackPreamp4SetVolumeLimit aCallback, void* aPtr);
    void EnableActionVolumeLimit(CallbackPreamp4VolumeLimit aCallback, void* aPtr);
    void EnableActionSetStartupVolume(CallbackPreamp4SetStartupVolume aCallback, void* aPtr);
    void EnableActionStartupVolume(CallbackPreamp4StartupVolume aCallback, void* aPtr);
    void EnableActionSetStartupVolumeEnabled(CallbackPreamp4SetStartupVolumeEnabled aCallback, void* aPtr);
    void EnableActionStartupVolumeEnabled(CallbackPreamp4StartupVolumeEnabled aCallback, void* aPtr);
private:
    void VolumeInc(IInvocationResponse& aResponse, TUint aVersion);
    void VolumeDec(IInvocationResponse& aResponse, TUint aVersion);
    void SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aaVolume);
    void Volume(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaVolume);
    void SetMute(IInvocationResponse& aResponse, TUint aVersion, TBool aaMute);
    void Mute(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaMute);
    void SetBalance(IInvocationResponse& aResponse, TUint aVersion, TInt aaBalance);
    void Balance(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aaBalance);
    void SetVolumeLimit(IInvocationResponse& aResponse, TUint aVersion, TUint aaVolumeLimit);
    void VolumeLimit(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaVolumeLimit);
    void SetStartupVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aaStartupVolume);
    void StartupVolume(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaStartupVolume);
    void SetStartupVolumeEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaStartupVolumeEnabled);
    void StartupVolumeEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStartupVolumeEnabled);
private:
    CallbackPreamp4VolumeInc iCallbackVolumeInc;
    void* iPtrVolumeInc;
    CallbackPreamp4VolumeDec iCallbackVolumeDec;
    void* iPtrVolumeDec;
    CallbackPreamp4SetVolume iCallbackSetVolume;
    void* iPtrSetVolume;
    CallbackPreamp4Volume iCallbackVolume;
    void* iPtrVolume;
    CallbackPreamp4SetMute iCallbackSetMute;
    void* iPtrSetMute;
    CallbackPreamp4Mute iCallbackMute;
    void* iPtrMute;
    CallbackPreamp4SetBalance iCallbackSetBalance;
    void* iPtrSetBalance;
    CallbackPreamp4Balance iCallbackBalance;
    void* iPtrBalance;
    CallbackPreamp4SetVolumeLimit iCallbackSetVolumeLimit;
    void* iPtrSetVolumeLimit;
    CallbackPreamp4VolumeLimit iCallbackVolumeLimit;
    void* iPtrVolumeLimit;
    CallbackPreamp4SetStartupVolume iCallbackSetStartupVolume;
    void* iPtrSetStartupVolume;
    CallbackPreamp4StartupVolume iCallbackStartupVolume;
    void* iPtrStartupVolume;
    CallbackPreamp4SetStartupVolumeEnabled iCallbackSetStartupVolumeEnabled;
    void* iPtrSetStartupVolumeEnabled;
    CallbackPreamp4StartupVolumeEnabled iCallbackStartupVolumeEnabled;
    void* iPtrStartupVolumeEnabled;
};

DvProviderLinnCoUkPreamp4C::DvProviderLinnCoUkPreamp4C(DvDevice& aDevice)
    : DvProviderLinnCoUkPreamp4(aDevice)
{
}

void DvProviderLinnCoUkPreamp4C::EnableActionVolumeInc(CallbackPreamp4VolumeInc aCallback, void* aPtr)
{
    iCallbackVolumeInc = aCallback;
    iPtrVolumeInc = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionVolumeInc();
}

void DvProviderLinnCoUkPreamp4C::EnableActionVolumeDec(CallbackPreamp4VolumeDec aCallback, void* aPtr)
{
    iCallbackVolumeDec = aCallback;
    iPtrVolumeDec = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionVolumeDec();
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetVolume(CallbackPreamp4SetVolume aCallback, void* aPtr)
{
    iCallbackSetVolume = aCallback;
    iPtrSetVolume = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionSetVolume();
}

void DvProviderLinnCoUkPreamp4C::EnableActionVolume(CallbackPreamp4Volume aCallback, void* aPtr)
{
    iCallbackVolume = aCallback;
    iPtrVolume = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionVolume();
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetMute(CallbackPreamp4SetMute aCallback, void* aPtr)
{
    iCallbackSetMute = aCallback;
    iPtrSetMute = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionSetMute();
}

void DvProviderLinnCoUkPreamp4C::EnableActionMute(CallbackPreamp4Mute aCallback, void* aPtr)
{
    iCallbackMute = aCallback;
    iPtrMute = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionMute();
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetBalance(CallbackPreamp4SetBalance aCallback, void* aPtr)
{
    iCallbackSetBalance = aCallback;
    iPtrSetBalance = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionSetBalance();
}

void DvProviderLinnCoUkPreamp4C::EnableActionBalance(CallbackPreamp4Balance aCallback, void* aPtr)
{
    iCallbackBalance = aCallback;
    iPtrBalance = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionBalance();
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetVolumeLimit(CallbackPreamp4SetVolumeLimit aCallback, void* aPtr)
{
    iCallbackSetVolumeLimit = aCallback;
    iPtrSetVolumeLimit = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionSetVolumeLimit();
}

void DvProviderLinnCoUkPreamp4C::EnableActionVolumeLimit(CallbackPreamp4VolumeLimit aCallback, void* aPtr)
{
    iCallbackVolumeLimit = aCallback;
    iPtrVolumeLimit = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionVolumeLimit();
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetStartupVolume(CallbackPreamp4SetStartupVolume aCallback, void* aPtr)
{
    iCallbackSetStartupVolume = aCallback;
    iPtrSetStartupVolume = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionSetStartupVolume();
}

void DvProviderLinnCoUkPreamp4C::EnableActionStartupVolume(CallbackPreamp4StartupVolume aCallback, void* aPtr)
{
    iCallbackStartupVolume = aCallback;
    iPtrStartupVolume = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionStartupVolume();
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetStartupVolumeEnabled(CallbackPreamp4SetStartupVolumeEnabled aCallback, void* aPtr)
{
    iCallbackSetStartupVolumeEnabled = aCallback;
    iPtrSetStartupVolumeEnabled = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionSetStartupVolumeEnabled();
}

void DvProviderLinnCoUkPreamp4C::EnableActionStartupVolumeEnabled(CallbackPreamp4StartupVolumeEnabled aCallback, void* aPtr)
{
    iCallbackStartupVolumeEnabled = aCallback;
    iPtrStartupVolumeEnabled = aPtr;
    DvProviderLinnCoUkPreamp4::EnableActionStartupVolumeEnabled();
}

void DvProviderLinnCoUkPreamp4C::VolumeInc(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackVolumeInc != NULL);
    if (0 != iCallbackVolumeInc(iPtrVolumeInc, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::VolumeDec(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackVolumeDec != NULL);
    if (0 != iCallbackVolumeDec(iPtrVolumeDec, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aaVolume)
{
    ASSERT(iCallbackSetVolume != NULL);
    if (0 != iCallbackSetVolume(iPtrSetVolume, aVersion, aaVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::Volume(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaVolume)
{
    uint32_t aVolume;
    ASSERT(iCallbackVolume != NULL);
    if (0 != iCallbackVolume(iPtrVolume, aVersion, &aVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaVolume.Write(aVolume);
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::SetMute(IInvocationResponse& aResponse, TUint aVersion, TBool aaMute)
{
    ASSERT(iCallbackSetMute != NULL);
    if (0 != iCallbackSetMute(iPtrSetMute, aVersion, aaMute)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::Mute(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaMute)
{
    uint32_t aMute;
    ASSERT(iCallbackMute != NULL);
    if (0 != iCallbackMute(iPtrMute, aVersion, &aMute)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaMute.Write((aMute!=0));
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::SetBalance(IInvocationResponse& aResponse, TUint aVersion, TInt aaBalance)
{
    ASSERT(iCallbackSetBalance != NULL);
    if (0 != iCallbackSetBalance(iPtrSetBalance, aVersion, aaBalance)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::Balance(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aaBalance)
{
    int32_t aBalance;
    ASSERT(iCallbackBalance != NULL);
    if (0 != iCallbackBalance(iPtrBalance, aVersion, &aBalance)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaBalance.Write(aBalance);
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::SetVolumeLimit(IInvocationResponse& aResponse, TUint aVersion, TUint aaVolumeLimit)
{
    ASSERT(iCallbackSetVolumeLimit != NULL);
    if (0 != iCallbackSetVolumeLimit(iPtrSetVolumeLimit, aVersion, aaVolumeLimit)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::VolumeLimit(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaVolumeLimit)
{
    uint32_t aVolumeLimit;
    ASSERT(iCallbackVolumeLimit != NULL);
    if (0 != iCallbackVolumeLimit(iPtrVolumeLimit, aVersion, &aVolumeLimit)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaVolumeLimit.Write(aVolumeLimit);
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::SetStartupVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aaStartupVolume)
{
    ASSERT(iCallbackSetStartupVolume != NULL);
    if (0 != iCallbackSetStartupVolume(iPtrSetStartupVolume, aVersion, aaStartupVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::StartupVolume(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaStartupVolume)
{
    uint32_t aStartupVolume;
    ASSERT(iCallbackStartupVolume != NULL);
    if (0 != iCallbackStartupVolume(iPtrStartupVolume, aVersion, &aStartupVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaStartupVolume.Write(aStartupVolume);
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::SetStartupVolumeEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaStartupVolumeEnabled)
{
    ASSERT(iCallbackSetStartupVolumeEnabled != NULL);
    if (0 != iCallbackSetStartupVolumeEnabled(iPtrSetStartupVolumeEnabled, aVersion, aaStartupVolumeEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPreamp4C::StartupVolumeEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStartupVolumeEnabled)
{
    uint32_t aStartupVolumeEnabled;
    ASSERT(iCallbackStartupVolumeEnabled != NULL);
    if (0 != iCallbackStartupVolumeEnabled(iPtrStartupVolumeEnabled, aVersion, &aStartupVolumeEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaStartupVolumeEnabled.Write((aStartupVolumeEnabled!=0));
    aResponse.End();
}



THandle DvProviderLinnCoUkPreamp4Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkPreamp4C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkPreamp4Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider);
}

void DvProviderLinnCoUkPreamp4EnableActionVolumeInc(THandle aProvider, CallbackPreamp4VolumeInc aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionVolumeInc(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionVolumeDec(THandle aProvider, CallbackPreamp4VolumeDec aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionVolumeDec(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetVolume(THandle aProvider, CallbackPreamp4SetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetVolume(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionVolume(THandle aProvider, CallbackPreamp4Volume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionVolume(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetMute(THandle aProvider, CallbackPreamp4SetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetMute(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionMute(THandle aProvider, CallbackPreamp4Mute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionMute(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetBalance(THandle aProvider, CallbackPreamp4SetBalance aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetBalance(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionBalance(THandle aProvider, CallbackPreamp4Balance aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionBalance(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetVolumeLimit(THandle aProvider, CallbackPreamp4SetVolumeLimit aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetVolumeLimit(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionVolumeLimit(THandle aProvider, CallbackPreamp4VolumeLimit aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionVolumeLimit(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetStartupVolume(THandle aProvider, CallbackPreamp4SetStartupVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetStartupVolume(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionStartupVolume(THandle aProvider, CallbackPreamp4StartupVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionStartupVolume(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetStartupVolumeEnabled(THandle aProvider, CallbackPreamp4SetStartupVolumeEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetStartupVolumeEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionStartupVolumeEnabled(THandle aProvider, CallbackPreamp4StartupVolumeEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionStartupVolumeEnabled(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyVolume(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyVolume(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyVolume(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyVolume(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyMute(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyMute((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyMute(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyMute(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyBalance(THandle aProvider, int32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyBalance(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyBalance(THandle aProvider, int32_t* aValue)
{
    int32_t val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyBalance(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyVolumeLimit(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyVolumeLimit(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyVolumeLimit(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyVolumeLimit(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyStartupVolume(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyStartupVolume(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyStartupVolume(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyStartupVolume(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyStartupVolumeEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyStartupVolumeEnabled((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyStartupVolumeEnabled(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyStartupVolumeEnabled(val);
    *aValue = (val? 1 : 0);
}

