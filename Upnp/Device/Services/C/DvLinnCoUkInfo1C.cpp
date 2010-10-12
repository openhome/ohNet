#include <C/DvLinnCoUkInfo1.h>
#include <Core/DvLinnCoUkInfo1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkInfo1C : public DvServiceLinnCoUkInfo1
{
public:
    DvServiceLinnCoUkInfo1C(DvDevice& aDevice);
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

DvServiceLinnCoUkInfo1C::DvServiceLinnCoUkInfo1C(DvDevice& aDevice)
    : DvServiceLinnCoUkInfo1(aDevice)
{
}

void DvServiceLinnCoUkInfo1C::EnableActionCounters(CallbackInfo1Counters aCallback, void* aPtr)
{
    iCallbackCounters = aCallback;
    iPtrCounters = aPtr;
    DvServiceLinnCoUkInfo1::EnableActionCounters();
}

void DvServiceLinnCoUkInfo1C::EnableActionTrack(CallbackInfo1Track aCallback, void* aPtr)
{
    iCallbackTrack = aCallback;
    iPtrTrack = aPtr;
    DvServiceLinnCoUkInfo1::EnableActionTrack();
}

void DvServiceLinnCoUkInfo1C::EnableActionDetails(CallbackInfo1Details aCallback, void* aPtr)
{
    iCallbackDetails = aCallback;
    iPtrDetails = aPtr;
    DvServiceLinnCoUkInfo1::EnableActionDetails();
}

void DvServiceLinnCoUkInfo1C::EnableActionMetatext(CallbackInfo1Metatext aCallback, void* aPtr)
{
    iCallbackMetatext = aCallback;
    iPtrMetatext = aPtr;
    DvServiceLinnCoUkInfo1::EnableActionMetatext();
}

void DvServiceLinnCoUkInfo1C::Counters(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTrackCount, IInvocationResponseUint& aaDetailsCount, IInvocationResponseUint& aaMetatextCount)
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

void DvServiceLinnCoUkInfo1C::Track(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetadata)
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

void DvServiceLinnCoUkInfo1C::Details(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDuration, IInvocationResponseUint& aaBitRate, IInvocationResponseUint& aaBitDepth, IInvocationResponseUint& aaSampleRate, IInvocationResponseBool& aaLossless, IInvocationResponseString& aaCodecName)
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

void DvServiceLinnCoUkInfo1C::Metatext(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMetatext)
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



THandle DvServiceLinnCoUkInfo1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkInfo1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkInfo1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService);
}

void DvServiceLinnCoUkInfo1EnableActionCounters(THandle aService, CallbackInfo1Counters aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->EnableActionCounters(aCallback, aPtr);
}

void DvServiceLinnCoUkInfo1EnableActionTrack(THandle aService, CallbackInfo1Track aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->EnableActionTrack(aCallback, aPtr);
}

void DvServiceLinnCoUkInfo1EnableActionDetails(THandle aService, CallbackInfo1Details aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->EnableActionDetails(aCallback, aPtr);
}

void DvServiceLinnCoUkInfo1EnableActionMetatext(THandle aService, CallbackInfo1Metatext aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->EnableActionMetatext(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkInfo1SetPropertyTrackCount(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertyTrackCount(aValue);
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertyTrackCount(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertyTrackCount(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkInfo1SetPropertyDetailsCount(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertyDetailsCount(aValue);
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertyDetailsCount(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertyDetailsCount(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkInfo1SetPropertyMetatextCount(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertyMetatextCount(aValue);
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertyMetatextCount(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertyMetatextCount(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkInfo1SetPropertyUri(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertyUri(buf);
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertyUri(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertyUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkInfo1SetPropertyMetadata(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertyMetadata(buf);
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertyMetadata(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertyMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkInfo1SetPropertyDuration(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertyDuration(aValue);
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertyDuration(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertyDuration(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkInfo1SetPropertyBitRate(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertyBitRate(aValue);
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertyBitRate(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertyBitRate(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkInfo1SetPropertyBitDepth(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertyBitDepth(aValue);
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertyBitDepth(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertyBitDepth(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkInfo1SetPropertySampleRate(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertySampleRate(aValue);
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertySampleRate(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertySampleRate(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkInfo1SetPropertyLossless(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertyLossless((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertyLossless(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertyLossless(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkInfo1SetPropertyCodecName(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertyCodecName(buf);
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertyCodecName(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertyCodecName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkInfo1SetPropertyMetatext(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->SetPropertyMetatext(buf);
    return 0;
}

void DvServiceLinnCoUkInfo1GetPropertyMetatext(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkInfo1C*>(aService)->GetPropertyMetatext(buf);
    *aValue = (char*)buf.Transfer();
}

