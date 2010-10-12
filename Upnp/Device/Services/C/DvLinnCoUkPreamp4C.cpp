#include <C/DvLinnCoUkPreamp4.h>
#include <Core/DvLinnCoUkPreamp4.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkPreamp4C : public DvServiceLinnCoUkPreamp4
{
public:
    DvServiceLinnCoUkPreamp4C(DvDevice& aDevice);
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

DvServiceLinnCoUkPreamp4C::DvServiceLinnCoUkPreamp4C(DvDevice& aDevice)
    : DvServiceLinnCoUkPreamp4(aDevice)
{
}

void DvServiceLinnCoUkPreamp4C::EnableActionVolumeInc(CallbackPreamp4VolumeInc aCallback, void* aPtr)
{
    iCallbackVolumeInc = aCallback;
    iPtrVolumeInc = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionVolumeInc();
}

void DvServiceLinnCoUkPreamp4C::EnableActionVolumeDec(CallbackPreamp4VolumeDec aCallback, void* aPtr)
{
    iCallbackVolumeDec = aCallback;
    iPtrVolumeDec = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionVolumeDec();
}

void DvServiceLinnCoUkPreamp4C::EnableActionSetVolume(CallbackPreamp4SetVolume aCallback, void* aPtr)
{
    iCallbackSetVolume = aCallback;
    iPtrSetVolume = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionSetVolume();
}

void DvServiceLinnCoUkPreamp4C::EnableActionVolume(CallbackPreamp4Volume aCallback, void* aPtr)
{
    iCallbackVolume = aCallback;
    iPtrVolume = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionVolume();
}

void DvServiceLinnCoUkPreamp4C::EnableActionSetMute(CallbackPreamp4SetMute aCallback, void* aPtr)
{
    iCallbackSetMute = aCallback;
    iPtrSetMute = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionSetMute();
}

void DvServiceLinnCoUkPreamp4C::EnableActionMute(CallbackPreamp4Mute aCallback, void* aPtr)
{
    iCallbackMute = aCallback;
    iPtrMute = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionMute();
}

void DvServiceLinnCoUkPreamp4C::EnableActionSetBalance(CallbackPreamp4SetBalance aCallback, void* aPtr)
{
    iCallbackSetBalance = aCallback;
    iPtrSetBalance = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionSetBalance();
}

void DvServiceLinnCoUkPreamp4C::EnableActionBalance(CallbackPreamp4Balance aCallback, void* aPtr)
{
    iCallbackBalance = aCallback;
    iPtrBalance = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionBalance();
}

void DvServiceLinnCoUkPreamp4C::EnableActionSetVolumeLimit(CallbackPreamp4SetVolumeLimit aCallback, void* aPtr)
{
    iCallbackSetVolumeLimit = aCallback;
    iPtrSetVolumeLimit = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionSetVolumeLimit();
}

void DvServiceLinnCoUkPreamp4C::EnableActionVolumeLimit(CallbackPreamp4VolumeLimit aCallback, void* aPtr)
{
    iCallbackVolumeLimit = aCallback;
    iPtrVolumeLimit = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionVolumeLimit();
}

void DvServiceLinnCoUkPreamp4C::EnableActionSetStartupVolume(CallbackPreamp4SetStartupVolume aCallback, void* aPtr)
{
    iCallbackSetStartupVolume = aCallback;
    iPtrSetStartupVolume = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionSetStartupVolume();
}

void DvServiceLinnCoUkPreamp4C::EnableActionStartupVolume(CallbackPreamp4StartupVolume aCallback, void* aPtr)
{
    iCallbackStartupVolume = aCallback;
    iPtrStartupVolume = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionStartupVolume();
}

void DvServiceLinnCoUkPreamp4C::EnableActionSetStartupVolumeEnabled(CallbackPreamp4SetStartupVolumeEnabled aCallback, void* aPtr)
{
    iCallbackSetStartupVolumeEnabled = aCallback;
    iPtrSetStartupVolumeEnabled = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionSetStartupVolumeEnabled();
}

void DvServiceLinnCoUkPreamp4C::EnableActionStartupVolumeEnabled(CallbackPreamp4StartupVolumeEnabled aCallback, void* aPtr)
{
    iCallbackStartupVolumeEnabled = aCallback;
    iPtrStartupVolumeEnabled = aPtr;
    DvServiceLinnCoUkPreamp4::EnableActionStartupVolumeEnabled();
}

void DvServiceLinnCoUkPreamp4C::VolumeInc(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackVolumeInc != NULL);
    if (0 != iCallbackVolumeInc(iPtrVolumeInc, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPreamp4C::VolumeDec(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackVolumeDec != NULL);
    if (0 != iCallbackVolumeDec(iPtrVolumeDec, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPreamp4C::SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aaVolume)
{
    ASSERT(iCallbackSetVolume != NULL);
    if (0 != iCallbackSetVolume(iPtrSetVolume, aVersion, aaVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPreamp4C::Volume(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaVolume)
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

void DvServiceLinnCoUkPreamp4C::SetMute(IInvocationResponse& aResponse, TUint aVersion, TBool aaMute)
{
    ASSERT(iCallbackSetMute != NULL);
    if (0 != iCallbackSetMute(iPtrSetMute, aVersion, aaMute)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPreamp4C::Mute(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaMute)
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

void DvServiceLinnCoUkPreamp4C::SetBalance(IInvocationResponse& aResponse, TUint aVersion, TInt aaBalance)
{
    ASSERT(iCallbackSetBalance != NULL);
    if (0 != iCallbackSetBalance(iPtrSetBalance, aVersion, aaBalance)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPreamp4C::Balance(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aaBalance)
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

void DvServiceLinnCoUkPreamp4C::SetVolumeLimit(IInvocationResponse& aResponse, TUint aVersion, TUint aaVolumeLimit)
{
    ASSERT(iCallbackSetVolumeLimit != NULL);
    if (0 != iCallbackSetVolumeLimit(iPtrSetVolumeLimit, aVersion, aaVolumeLimit)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPreamp4C::VolumeLimit(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaVolumeLimit)
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

void DvServiceLinnCoUkPreamp4C::SetStartupVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aaStartupVolume)
{
    ASSERT(iCallbackSetStartupVolume != NULL);
    if (0 != iCallbackSetStartupVolume(iPtrSetStartupVolume, aVersion, aaStartupVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPreamp4C::StartupVolume(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaStartupVolume)
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

void DvServiceLinnCoUkPreamp4C::SetStartupVolumeEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaStartupVolumeEnabled)
{
    ASSERT(iCallbackSetStartupVolumeEnabled != NULL);
    if (0 != iCallbackSetStartupVolumeEnabled(iPtrSetStartupVolumeEnabled, aVersion, aaStartupVolumeEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPreamp4C::StartupVolumeEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStartupVolumeEnabled)
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



THandle DvServiceLinnCoUkPreamp4Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkPreamp4C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkPreamp4Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService);
}

void DvServiceLinnCoUkPreamp4EnableActionVolumeInc(THandle aService, CallbackPreamp4VolumeInc aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionVolumeInc(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionVolumeDec(THandle aService, CallbackPreamp4VolumeDec aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionVolumeDec(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionSetVolume(THandle aService, CallbackPreamp4SetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionSetVolume(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionVolume(THandle aService, CallbackPreamp4Volume aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionVolume(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionSetMute(THandle aService, CallbackPreamp4SetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionSetMute(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionMute(THandle aService, CallbackPreamp4Mute aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionMute(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionSetBalance(THandle aService, CallbackPreamp4SetBalance aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionSetBalance(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionBalance(THandle aService, CallbackPreamp4Balance aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionBalance(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionSetVolumeLimit(THandle aService, CallbackPreamp4SetVolumeLimit aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionSetVolumeLimit(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionVolumeLimit(THandle aService, CallbackPreamp4VolumeLimit aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionVolumeLimit(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionSetStartupVolume(THandle aService, CallbackPreamp4SetStartupVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionSetStartupVolume(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionStartupVolume(THandle aService, CallbackPreamp4StartupVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionStartupVolume(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionSetStartupVolumeEnabled(THandle aService, CallbackPreamp4SetStartupVolumeEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionSetStartupVolumeEnabled(aCallback, aPtr);
}

void DvServiceLinnCoUkPreamp4EnableActionStartupVolumeEnabled(THandle aService, CallbackPreamp4StartupVolumeEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->EnableActionStartupVolumeEnabled(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkPreamp4SetPropertyVolume(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->SetPropertyVolume(aValue);
    return 0;
}

void DvServiceLinnCoUkPreamp4GetPropertyVolume(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->GetPropertyVolume(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkPreamp4SetPropertyMute(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->SetPropertyMute((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkPreamp4GetPropertyMute(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->GetPropertyMute(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkPreamp4SetPropertyBalance(THandle aService, int32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->SetPropertyBalance(aValue);
    return 0;
}

void DvServiceLinnCoUkPreamp4GetPropertyBalance(THandle aService, int32_t* aValue)
{
    int32_t val;
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->GetPropertyBalance(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkPreamp4SetPropertyVolumeLimit(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->SetPropertyVolumeLimit(aValue);
    return 0;
}

void DvServiceLinnCoUkPreamp4GetPropertyVolumeLimit(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->GetPropertyVolumeLimit(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkPreamp4SetPropertyStartupVolume(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->SetPropertyStartupVolume(aValue);
    return 0;
}

void DvServiceLinnCoUkPreamp4GetPropertyStartupVolume(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->GetPropertyStartupVolume(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkPreamp4SetPropertyStartupVolumeEnabled(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->SetPropertyStartupVolumeEnabled((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkPreamp4GetPropertyStartupVolumeEnabled(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkPreamp4C*>(aService)->GetPropertyStartupVolumeEnabled(val);
    *aValue = (val? 1 : 0);
}

