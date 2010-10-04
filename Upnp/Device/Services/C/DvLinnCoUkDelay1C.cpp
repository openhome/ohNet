#include <C/DvLinnCoUkDelay1.h>
#include <Core/DvLinnCoUkDelay1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkDelay1C : public DvServiceLinnCoUkDelay1
{
public:
    DvServiceLinnCoUkDelay1C(DvDevice& aDevice);
    void EnableActionPresetXml(CallbackDelay1PresetXml aCallback, void* aPtr);
    void EnableActionPresetIndex(CallbackDelay1PresetIndex aCallback, void* aPtr);
    void EnableActionSetPresetIndex(CallbackDelay1SetPresetIndex aCallback, void* aPtr);
    void EnableActionSetPresetDelay(CallbackDelay1SetPresetDelay aCallback, void* aPtr);
    void EnableActionSetPresetVisible(CallbackDelay1SetPresetVisible aCallback, void* aPtr);
    void EnableActionSetPresetName(CallbackDelay1SetPresetName aCallback, void* aPtr);
    void EnableActionDelayMinimum(CallbackDelay1DelayMinimum aCallback, void* aPtr);
    void EnableActionDelayMaximum(CallbackDelay1DelayMaximum aCallback, void* aPtr);
    void EnableActionPresetCount(CallbackDelay1PresetCount aCallback, void* aPtr);
private:
    void PresetXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaPresetXml);
    void PresetIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIndex);
    void SetPresetIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex);
    void SetPresetDelay(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, TUint aaDelay);
    void SetPresetVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, TBool aaVisible);
    void SetPresetName(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, const Brx& aaName);
    void DelayMinimum(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDelay);
    void DelayMaximum(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDelay);
    void PresetCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaCount);
private:
    CallbackDelay1PresetXml iCallbackPresetXml;
    void* iPtrPresetXml;
    CallbackDelay1PresetIndex iCallbackPresetIndex;
    void* iPtrPresetIndex;
    CallbackDelay1SetPresetIndex iCallbackSetPresetIndex;
    void* iPtrSetPresetIndex;
    CallbackDelay1SetPresetDelay iCallbackSetPresetDelay;
    void* iPtrSetPresetDelay;
    CallbackDelay1SetPresetVisible iCallbackSetPresetVisible;
    void* iPtrSetPresetVisible;
    CallbackDelay1SetPresetName iCallbackSetPresetName;
    void* iPtrSetPresetName;
    CallbackDelay1DelayMinimum iCallbackDelayMinimum;
    void* iPtrDelayMinimum;
    CallbackDelay1DelayMaximum iCallbackDelayMaximum;
    void* iPtrDelayMaximum;
    CallbackDelay1PresetCount iCallbackPresetCount;
    void* iPtrPresetCount;
};

DvServiceLinnCoUkDelay1C::DvServiceLinnCoUkDelay1C(DvDevice& aDevice)
    : DvServiceLinnCoUkDelay1(aDevice)
{
}

void DvServiceLinnCoUkDelay1C::EnableActionPresetXml(CallbackDelay1PresetXml aCallback, void* aPtr)
{
    iCallbackPresetXml = aCallback;
    iPtrPresetXml = aPtr;
    DvServiceLinnCoUkDelay1::EnableActionPresetXml();
}

void DvServiceLinnCoUkDelay1C::EnableActionPresetIndex(CallbackDelay1PresetIndex aCallback, void* aPtr)
{
    iCallbackPresetIndex = aCallback;
    iPtrPresetIndex = aPtr;
    DvServiceLinnCoUkDelay1::EnableActionPresetIndex();
}

void DvServiceLinnCoUkDelay1C::EnableActionSetPresetIndex(CallbackDelay1SetPresetIndex aCallback, void* aPtr)
{
    iCallbackSetPresetIndex = aCallback;
    iPtrSetPresetIndex = aPtr;
    DvServiceLinnCoUkDelay1::EnableActionSetPresetIndex();
}

void DvServiceLinnCoUkDelay1C::EnableActionSetPresetDelay(CallbackDelay1SetPresetDelay aCallback, void* aPtr)
{
    iCallbackSetPresetDelay = aCallback;
    iPtrSetPresetDelay = aPtr;
    DvServiceLinnCoUkDelay1::EnableActionSetPresetDelay();
}

void DvServiceLinnCoUkDelay1C::EnableActionSetPresetVisible(CallbackDelay1SetPresetVisible aCallback, void* aPtr)
{
    iCallbackSetPresetVisible = aCallback;
    iPtrSetPresetVisible = aPtr;
    DvServiceLinnCoUkDelay1::EnableActionSetPresetVisible();
}

void DvServiceLinnCoUkDelay1C::EnableActionSetPresetName(CallbackDelay1SetPresetName aCallback, void* aPtr)
{
    iCallbackSetPresetName = aCallback;
    iPtrSetPresetName = aPtr;
    DvServiceLinnCoUkDelay1::EnableActionSetPresetName();
}

void DvServiceLinnCoUkDelay1C::EnableActionDelayMinimum(CallbackDelay1DelayMinimum aCallback, void* aPtr)
{
    iCallbackDelayMinimum = aCallback;
    iPtrDelayMinimum = aPtr;
    DvServiceLinnCoUkDelay1::EnableActionDelayMinimum();
}

void DvServiceLinnCoUkDelay1C::EnableActionDelayMaximum(CallbackDelay1DelayMaximum aCallback, void* aPtr)
{
    iCallbackDelayMaximum = aCallback;
    iPtrDelayMaximum = aPtr;
    DvServiceLinnCoUkDelay1::EnableActionDelayMaximum();
}

void DvServiceLinnCoUkDelay1C::EnableActionPresetCount(CallbackDelay1PresetCount aCallback, void* aPtr)
{
    iCallbackPresetCount = aCallback;
    iPtrPresetCount = aPtr;
    DvServiceLinnCoUkDelay1::EnableActionPresetCount();
}

void DvServiceLinnCoUkDelay1C::PresetXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaPresetXml)
{
    char* aPresetXml;
    ASSERT(iCallbackPresetXml != NULL);
    if (0 != iCallbackPresetXml(iPtrPresetXml, aVersion, &aPresetXml)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaPresetXml((const TChar*)aPresetXml);
    ZappFreeExternal(aPresetXml);
    aaPresetXml.Write(bufaPresetXml);
    aaPresetXml.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkDelay1C::PresetIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIndex)
{
    uint32_t aIndex;
    ASSERT(iCallbackPresetIndex != NULL);
    if (0 != iCallbackPresetIndex(iPtrPresetIndex, aVersion, &aIndex)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaIndex.Write(aIndex);
    aResponse.End();
}

void DvServiceLinnCoUkDelay1C::SetPresetIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex)
{
    ASSERT(iCallbackSetPresetIndex != NULL);
    if (0 != iCallbackSetPresetIndex(iPtrSetPresetIndex, aVersion, aaIndex)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDelay1C::SetPresetDelay(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, TUint aaDelay)
{
    ASSERT(iCallbackSetPresetDelay != NULL);
    if (0 != iCallbackSetPresetDelay(iPtrSetPresetDelay, aVersion, aaIndex, aaDelay)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDelay1C::SetPresetVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, TBool aaVisible)
{
    ASSERT(iCallbackSetPresetVisible != NULL);
    if (0 != iCallbackSetPresetVisible(iPtrSetPresetVisible, aVersion, aaIndex, aaVisible)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDelay1C::SetPresetName(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, const Brx& aaName)
{
    ASSERT(iCallbackSetPresetName != NULL);
    if (0 != iCallbackSetPresetName(iPtrSetPresetName, aVersion, aaIndex, (const char*)aaName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDelay1C::DelayMinimum(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDelay)
{
    uint32_t aDelay;
    ASSERT(iCallbackDelayMinimum != NULL);
    if (0 != iCallbackDelayMinimum(iPtrDelayMinimum, aVersion, &aDelay)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaDelay.Write(aDelay);
    aResponse.End();
}

void DvServiceLinnCoUkDelay1C::DelayMaximum(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDelay)
{
    uint32_t aDelay;
    ASSERT(iCallbackDelayMaximum != NULL);
    if (0 != iCallbackDelayMaximum(iPtrDelayMaximum, aVersion, &aDelay)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaDelay.Write(aDelay);
    aResponse.End();
}

void DvServiceLinnCoUkDelay1C::PresetCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaCount)
{
    uint32_t aCount;
    ASSERT(iCallbackPresetCount != NULL);
    if (0 != iCallbackPresetCount(iPtrPresetCount, aVersion, &aCount)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaCount.Write(aCount);
    aResponse.End();
}



THandle DvServiceLinnCoUkDelay1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkDelay1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkDelay1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService);
}

void DvServiceLinnCoUkDelay1EnableActionPresetXml(THandle aService, CallbackDelay1PresetXml aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->EnableActionPresetXml(aCallback, aPtr);
}

void DvServiceLinnCoUkDelay1EnableActionPresetIndex(THandle aService, CallbackDelay1PresetIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->EnableActionPresetIndex(aCallback, aPtr);
}

void DvServiceLinnCoUkDelay1EnableActionSetPresetIndex(THandle aService, CallbackDelay1SetPresetIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->EnableActionSetPresetIndex(aCallback, aPtr);
}

void DvServiceLinnCoUkDelay1EnableActionSetPresetDelay(THandle aService, CallbackDelay1SetPresetDelay aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->EnableActionSetPresetDelay(aCallback, aPtr);
}

void DvServiceLinnCoUkDelay1EnableActionSetPresetVisible(THandle aService, CallbackDelay1SetPresetVisible aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->EnableActionSetPresetVisible(aCallback, aPtr);
}

void DvServiceLinnCoUkDelay1EnableActionSetPresetName(THandle aService, CallbackDelay1SetPresetName aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->EnableActionSetPresetName(aCallback, aPtr);
}

void DvServiceLinnCoUkDelay1EnableActionDelayMinimum(THandle aService, CallbackDelay1DelayMinimum aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->EnableActionDelayMinimum(aCallback, aPtr);
}

void DvServiceLinnCoUkDelay1EnableActionDelayMaximum(THandle aService, CallbackDelay1DelayMaximum aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->EnableActionDelayMaximum(aCallback, aPtr);
}

void DvServiceLinnCoUkDelay1EnableActionPresetCount(THandle aService, CallbackDelay1PresetCount aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->EnableActionPresetCount(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkDelay1SetPropertyPresetXml(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->SetPropertyPresetXml(buf);
    return 0;
}

void DvServiceLinnCoUkDelay1GetPropertyPresetXml(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->GetPropertyPresetXml(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkDelay1SetPropertyPresetIndex(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->SetPropertyPresetIndex(aValue);
    return 0;
}

void DvServiceLinnCoUkDelay1GetPropertyPresetIndex(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkDelay1C*>(aService)->GetPropertyPresetIndex(val);
    *aValue = val;
}

