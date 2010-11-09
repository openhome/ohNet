#include <C/DvLinnCoUkInfo1.h>
#include <Core/DvLinnCoUkInfo1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkInfo1C : public DvProviderLinnCoUkInfo1
{
public:
    DvProviderLinnCoUkInfo1C(DvDevice& aDevice);
    void EnableActionCounters(CallbackInfo1Counters aCallback, void* aPtr);
    void EnableActionTrack(CallbackInfo1Track aCallback, void* aPtr);
    void EnableActionDetails(CallbackInfo1Details aCallback, void* aPtr);
    void EnableActionMetatext(CallbackInfo1Metatext aCallback, void* aPtr);
private:
    void Counters(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTrackCount, IInvocationResponseUint& aaDetailsCount, IInvocationResponseUint& aaMetatextCount);
    void Track(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetadata);
    void Details(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDuration, IInvocationResponseUint& aaBitRate, IInvocationResponseUint& aaBitDepth, IInvocationResponseUint& aaSampleRate, IInvocationResponseBool& aaLossless, IInvocationResponseString& aaCodecName);
    void Metatext(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMetatext);
private:
    CallbackInfo1Counters iCallbackCounters;
    void* iPtrCounters;
    CallbackInfo1Track iCallbackTrack;
    void* iPtrTrack;
    CallbackInfo1Details iCallbackDetails;
    void* iPtrDetails;
    CallbackInfo1Metatext iCallbackMetatext;
    void* iPtrMetatext;
};

DvProviderLinnCoUkInfo1C::DvProviderLinnCoUkInfo1C(DvDevice& aDevice)
    : DvProviderLinnCoUkInfo1(aDevice)
{
}

void DvProviderLinnCoUkInfo1C::EnableActionCounters(CallbackInfo1Counters aCallback, void* aPtr)
{
    iCallbackCounters = aCallback;
    iPtrCounters = aPtr;
    DvProviderLinnCoUkInfo1::EnableActionCounters();
}

void DvProviderLinnCoUkInfo1C::EnableActionTrack(CallbackInfo1Track aCallback, void* aPtr)
{
    iCallbackTrack = aCallback;
    iPtrTrack = aPtr;
    DvProviderLinnCoUkInfo1::EnableActionTrack();
}

void DvProviderLinnCoUkInfo1C::EnableActionDetails(CallbackInfo1Details aCallback, void* aPtr)
{
    iCallbackDetails = aCallback;
    iPtrDetails = aPtr;
    DvProviderLinnCoUkInfo1::EnableActionDetails();
}

void DvProviderLinnCoUkInfo1C::EnableActionMetatext(CallbackInfo1Metatext aCallback, void* aPtr)
{
    iCallbackMetatext = aCallback;
    iPtrMetatext = aPtr;
    DvProviderLinnCoUkInfo1::EnableActionMetatext();
}

void DvProviderLinnCoUkInfo1C::Counters(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTrackCount, IInvocationResponseUint& aaDetailsCount, IInvocationResponseUint& aaMetatextCount)
{
    uint32_t aTrackCount;
    uint32_t aDetailsCount;
    uint32_t aMetatextCount;
    ASSERT(iCallbackCounters != NULL);
    if (0 != iCallbackCounters(iPtrCounters, aVersion, &aTrackCount, &aDetailsCount, &aMetatextCount)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaTrackCount.Write(aTrackCount);
    aaDetailsCount.Write(aDetailsCount);
    aaMetatextCount.Write(aMetatextCount);
    aResponse.End();
}

void DvProviderLinnCoUkInfo1C::Track(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetadata)
{
    char* aUri;
    char* aMetadata;
    ASSERT(iCallbackTrack != NULL);
    if (0 != iCallbackTrack(iPtrTrack, aVersion, &aUri, &aMetadata)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaUri((const TChar*)aUri);
    ZappFreeExternal(aUri);
    aaUri.Write(bufaUri);
    aaUri.WriteFlush();
    Brhz bufaMetadata((const TChar*)aMetadata);
    ZappFreeExternal(aMetadata);
    aaMetadata.Write(bufaMetadata);
    aaMetadata.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkInfo1C::Details(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDuration, IInvocationResponseUint& aaBitRate, IInvocationResponseUint& aaBitDepth, IInvocationResponseUint& aaSampleRate, IInvocationResponseBool& aaLossless, IInvocationResponseString& aaCodecName)
{
    uint32_t aDuration;
    uint32_t aBitRate;
    uint32_t aBitDepth;
    uint32_t aSampleRate;
    uint32_t aLossless;
    char* aCodecName;
    ASSERT(iCallbackDetails != NULL);
    if (0 != iCallbackDetails(iPtrDetails, aVersion, &aDuration, &aBitRate, &aBitDepth, &aSampleRate, &aLossless, &aCodecName)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaDuration.Write(aDuration);
    aaBitRate.Write(aBitRate);
    aaBitDepth.Write(aBitDepth);
    aaSampleRate.Write(aSampleRate);
    aaLossless.Write((aLossless!=0));
    Brhz bufaCodecName((const TChar*)aCodecName);
    ZappFreeExternal(aCodecName);
    aaCodecName.Write(bufaCodecName);
    aaCodecName.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkInfo1C::Metatext(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMetatext)
{
    char* aMetatext;
    ASSERT(iCallbackMetatext != NULL);
    if (0 != iCallbackMetatext(iPtrMetatext, aVersion, &aMetatext)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaMetatext((const TChar*)aMetatext);
    ZappFreeExternal(aMetatext);
    aaMetatext.Write(bufaMetatext);
    aaMetatext.WriteFlush();
    aResponse.End();
}



THandle DvProviderLinnCoUkInfo1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkInfo1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkInfo1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider);
}

void DvProviderLinnCoUkInfo1EnableActionCounters(THandle aProvider, CallbackInfo1Counters aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->EnableActionCounters(aCallback, aPtr);
}

void DvProviderLinnCoUkInfo1EnableActionTrack(THandle aProvider, CallbackInfo1Track aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->EnableActionTrack(aCallback, aPtr);
}

void DvProviderLinnCoUkInfo1EnableActionDetails(THandle aProvider, CallbackInfo1Details aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->EnableActionDetails(aCallback, aPtr);
}

void DvProviderLinnCoUkInfo1EnableActionMetatext(THandle aProvider, CallbackInfo1Metatext aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->EnableActionMetatext(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkInfo1SetPropertyTrackCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertyTrackCount(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertyTrackCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertyTrackCount(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkInfo1SetPropertyDetailsCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertyDetailsCount(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertyDetailsCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertyDetailsCount(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkInfo1SetPropertyMetatextCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertyMetatextCount(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertyMetatextCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertyMetatextCount(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkInfo1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertyUri(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertyUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertyUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkInfo1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertyMetadata(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertyMetadata(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertyMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkInfo1SetPropertyDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertyDuration(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertyDuration(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertyDuration(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkInfo1SetPropertyBitRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertyBitRate(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertyBitRate(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertyBitRate(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkInfo1SetPropertyBitDepth(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertyBitDepth(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertyBitDepth(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertyBitDepth(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkInfo1SetPropertySampleRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertySampleRate(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertySampleRate(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertySampleRate(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkInfo1SetPropertyLossless(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertyLossless((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertyLossless(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertyLossless(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkInfo1SetPropertyCodecName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertyCodecName(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertyCodecName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertyCodecName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkInfo1SetPropertyMetatext(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->SetPropertyMetatext(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkInfo1GetPropertyMetatext(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkInfo1C*>(aProvider)->GetPropertyMetatext(buf);
    *aValue = (char*)buf.Transfer();
}

