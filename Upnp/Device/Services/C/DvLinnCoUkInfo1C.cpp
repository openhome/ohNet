#include "DvLinnCoUkInfo1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderLinnCoUkInfo1C : public DvProvider
{
public:
    DvProviderLinnCoUkInfo1C(DvDeviceC aDevice);
    TBool SetPropertyTrackCount(TUint aValue);
    void GetPropertyTrackCount(TUint& aValue);
    TBool SetPropertyDetailsCount(TUint aValue);
    void GetPropertyDetailsCount(TUint& aValue);
    TBool SetPropertyMetatextCount(TUint aValue);
    void GetPropertyMetatextCount(TUint& aValue);
    TBool SetPropertyUri(const Brx& aValue);
    void GetPropertyUri(Brhz& aValue);
    TBool SetPropertyMetadata(const Brx& aValue);
    void GetPropertyMetadata(Brhz& aValue);
    TBool SetPropertyDuration(TUint aValue);
    void GetPropertyDuration(TUint& aValue);
    TBool SetPropertyBitRate(TUint aValue);
    void GetPropertyBitRate(TUint& aValue);
    TBool SetPropertyBitDepth(TUint aValue);
    void GetPropertyBitDepth(TUint& aValue);
    TBool SetPropertySampleRate(TUint aValue);
    void GetPropertySampleRate(TUint& aValue);
    TBool SetPropertyLossless(TBool aValue);
    void GetPropertyLossless(TBool& aValue);
    TBool SetPropertyCodecName(const Brx& aValue);
    void GetPropertyCodecName(Brhz& aValue);
    TBool SetPropertyMetatext(const Brx& aValue);
    void GetPropertyMetatext(Brhz& aValue);
    void EnableActionCounters(CallbackInfo1Counters aCallback, void* aPtr);
    void EnableActionTrack(CallbackInfo1Track aCallback, void* aPtr);
    void EnableActionDetails(CallbackInfo1Details aCallback, void* aPtr);
    void EnableActionMetatext(CallbackInfo1Metatext aCallback, void* aPtr);
private:
    void DoCounters(IDviInvocation& aInvocation, TUint aVersion);
    void DoTrack(IDviInvocation& aInvocation, TUint aVersion);
    void DoDetails(IDviInvocation& aInvocation, TUint aVersion);
    void DoMetatext(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackInfo1Counters iCallbackCounters;
    void* iPtrCounters;
    CallbackInfo1Track iCallbackTrack;
    void* iPtrTrack;
    CallbackInfo1Details iCallbackDetails;
    void* iPtrDetails;
    CallbackInfo1Metatext iCallbackMetatext;
    void* iPtrMetatext;
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDetailsCount;
    PropertyUint* iPropertyMetatextCount;
    PropertyString* iPropertyUri;
    PropertyString* iPropertyMetadata;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertyBitRate;
    PropertyUint* iPropertyBitDepth;
    PropertyUint* iPropertySampleRate;
    PropertyBool* iPropertyLossless;
    PropertyString* iPropertyCodecName;
    PropertyString* iPropertyMetatext;
};

DvProviderLinnCoUkInfo1C::DvProviderLinnCoUkInfo1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Info", 1)
{
    
    iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"));
    iService->AddProperty(iPropertyTrackCount); // passes ownership
    iPropertyDetailsCount = new PropertyUint(new ParameterUint("DetailsCount"));
    iService->AddProperty(iPropertyDetailsCount); // passes ownership
    iPropertyMetatextCount = new PropertyUint(new ParameterUint("MetatextCount"));
    iService->AddProperty(iPropertyMetatextCount); // passes ownership
    iPropertyUri = new PropertyString(new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
    iPropertyMetadata = new PropertyString(new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
    iPropertyDuration = new PropertyUint(new ParameterUint("Duration"));
    iService->AddProperty(iPropertyDuration); // passes ownership
    iPropertyBitRate = new PropertyUint(new ParameterUint("BitRate"));
    iService->AddProperty(iPropertyBitRate); // passes ownership
    iPropertyBitDepth = new PropertyUint(new ParameterUint("BitDepth"));
    iService->AddProperty(iPropertyBitDepth); // passes ownership
    iPropertySampleRate = new PropertyUint(new ParameterUint("SampleRate"));
    iService->AddProperty(iPropertySampleRate); // passes ownership
    iPropertyLossless = new PropertyBool(new ParameterBool("Lossless"));
    iService->AddProperty(iPropertyLossless); // passes ownership
    iPropertyCodecName = new PropertyString(new ParameterString("CodecName"));
    iService->AddProperty(iPropertyCodecName); // passes ownership
    iPropertyMetatext = new PropertyString(new ParameterString("Metatext"));
    iService->AddProperty(iPropertyMetatext); // passes ownership
}

TBool DvProviderLinnCoUkInfo1C::SetPropertyTrackCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertyTrackCount(TUint& aValue)
{
    aValue = iPropertyTrackCount->Value();
}

TBool DvProviderLinnCoUkInfo1C::SetPropertyDetailsCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyDetailsCount, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertyDetailsCount(TUint& aValue)
{
    aValue = iPropertyDetailsCount->Value();
}

TBool DvProviderLinnCoUkInfo1C::SetPropertyMetatextCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyMetatextCount, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertyMetatextCount(TUint& aValue)
{
    aValue = iPropertyMetatextCount->Value();
}

TBool DvProviderLinnCoUkInfo1C::SetPropertyUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyUri, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertyUri(Brhz& aValue)
{
    aValue.Set(iPropertyUri->Value());
}

TBool DvProviderLinnCoUkInfo1C::SetPropertyMetadata(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderLinnCoUkInfo1C::SetPropertyDuration(TUint aValue)
{
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertyDuration(TUint& aValue)
{
    aValue = iPropertyDuration->Value();
}

TBool DvProviderLinnCoUkInfo1C::SetPropertyBitRate(TUint aValue)
{
    return SetPropertyUint(*iPropertyBitRate, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertyBitRate(TUint& aValue)
{
    aValue = iPropertyBitRate->Value();
}

TBool DvProviderLinnCoUkInfo1C::SetPropertyBitDepth(TUint aValue)
{
    return SetPropertyUint(*iPropertyBitDepth, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertyBitDepth(TUint& aValue)
{
    aValue = iPropertyBitDepth->Value();
}

TBool DvProviderLinnCoUkInfo1C::SetPropertySampleRate(TUint aValue)
{
    return SetPropertyUint(*iPropertySampleRate, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertySampleRate(TUint& aValue)
{
    aValue = iPropertySampleRate->Value();
}

TBool DvProviderLinnCoUkInfo1C::SetPropertyLossless(TBool aValue)
{
    return SetPropertyBool(*iPropertyLossless, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertyLossless(TBool& aValue)
{
    aValue = iPropertyLossless->Value();
}

TBool DvProviderLinnCoUkInfo1C::SetPropertyCodecName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyCodecName, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertyCodecName(Brhz& aValue)
{
    aValue.Set(iPropertyCodecName->Value());
}

TBool DvProviderLinnCoUkInfo1C::SetPropertyMetatext(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetatext, aValue);
}

void DvProviderLinnCoUkInfo1C::GetPropertyMetatext(Brhz& aValue)
{
    aValue.Set(iPropertyMetatext->Value());
}

void DvProviderLinnCoUkInfo1C::EnableActionCounters(CallbackInfo1Counters aCallback, void* aPtr)
{
    iCallbackCounters = aCallback;
    iPtrCounters = aPtr;
    Zapp::Action* action = new Zapp::Action("Counters");
    action->AddOutputParameter(new ParameterRelated("aTrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("aDetailsCount", *iPropertyDetailsCount));
    action->AddOutputParameter(new ParameterRelated("aMetatextCount", *iPropertyMetatextCount));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkInfo1C::DoCounters);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1C::EnableActionTrack(CallbackInfo1Track aCallback, void* aPtr)
{
    iCallbackTrack = aCallback;
    iPtrTrack = aPtr;
    Zapp::Action* action = new Zapp::Action("Track");
    action->AddOutputParameter(new ParameterRelated("aUri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkInfo1C::DoTrack);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1C::EnableActionDetails(CallbackInfo1Details aCallback, void* aPtr)
{
    iCallbackDetails = aCallback;
    iPtrDetails = aPtr;
    Zapp::Action* action = new Zapp::Action("Details");
    action->AddOutputParameter(new ParameterRelated("aDuration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("aBitRate", *iPropertyBitRate));
    action->AddOutputParameter(new ParameterRelated("aBitDepth", *iPropertyBitDepth));
    action->AddOutputParameter(new ParameterRelated("aSampleRate", *iPropertySampleRate));
    action->AddOutputParameter(new ParameterRelated("aLossless", *iPropertyLossless));
    action->AddOutputParameter(new ParameterRelated("aCodecName", *iPropertyCodecName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkInfo1C::DoDetails);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1C::EnableActionMetatext(CallbackInfo1Metatext aCallback, void* aPtr)
{
    iCallbackMetatext = aCallback;
    iPtrMetatext = aPtr;
    Zapp::Action* action = new Zapp::Action("Metatext");
    action->AddOutputParameter(new ParameterRelated("aMetatext", *iPropertyMetatext));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkInfo1C::DoMetatext);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1C::DoCounters(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aTrackCount;
    uint32_t aDetailsCount;
    uint32_t aMetatextCount;
    ASSERT(iCallbackCounters != NULL);
    if (0 != iCallbackCounters(iPtrCounters, aVersion, &aTrackCount, &aDetailsCount, &aMetatextCount)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaTrackCount(aInvocation, "aTrackCount");
    InvocationResponseUint respaDetailsCount(aInvocation, "aDetailsCount");
    InvocationResponseUint respaMetatextCount(aInvocation, "aMetatextCount");
    resp.Start();
    respaTrackCount.Write(aTrackCount);
    respaDetailsCount.Write(aDetailsCount);
    respaMetatextCount.Write(aMetatextCount);
    resp.End();
}

void DvProviderLinnCoUkInfo1C::DoTrack(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aUri;
    char* aMetadata;
    ASSERT(iCallbackTrack != NULL);
    if (0 != iCallbackTrack(iPtrTrack, aVersion, &aUri, &aMetadata)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaUri(aInvocation, "aUri");
    InvocationResponseString respaMetadata(aInvocation, "aMetadata");
    resp.Start();
    Brhz bufaUri((const TChar*)aUri);
    ZappFreeExternal(aUri);
    respaUri.Write(bufaUri);
    respaUri.WriteFlush();
    Brhz bufaMetadata((const TChar*)aMetadata);
    ZappFreeExternal(aMetadata);
    respaMetadata.Write(bufaMetadata);
    respaMetadata.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkInfo1C::DoDetails(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aDuration;
    uint32_t aBitRate;
    uint32_t aBitDepth;
    uint32_t aSampleRate;
    uint32_t aLossless;
    char* aCodecName;
    ASSERT(iCallbackDetails != NULL);
    if (0 != iCallbackDetails(iPtrDetails, aVersion, &aDuration, &aBitRate, &aBitDepth, &aSampleRate, &aLossless, &aCodecName)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaDuration(aInvocation, "aDuration");
    InvocationResponseUint respaBitRate(aInvocation, "aBitRate");
    InvocationResponseUint respaBitDepth(aInvocation, "aBitDepth");
    InvocationResponseUint respaSampleRate(aInvocation, "aSampleRate");
    InvocationResponseBool respaLossless(aInvocation, "aLossless");
    InvocationResponseString respaCodecName(aInvocation, "aCodecName");
    resp.Start();
    respaDuration.Write(aDuration);
    respaBitRate.Write(aBitRate);
    respaBitDepth.Write(aBitDepth);
    respaSampleRate.Write(aSampleRate);
    respaLossless.Write((aLossless!=0));
    Brhz bufaCodecName((const TChar*)aCodecName);
    ZappFreeExternal(aCodecName);
    respaCodecName.Write(bufaCodecName);
    respaCodecName.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkInfo1C::DoMetatext(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aMetatext;
    ASSERT(iCallbackMetatext != NULL);
    if (0 != iCallbackMetatext(iPtrMetatext, aVersion, &aMetatext)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaMetatext(aInvocation, "aMetatext");
    resp.Start();
    Brhz bufaMetatext((const TChar*)aMetatext);
    ZappFreeExternal(aMetatext);
    respaMetatext.Write(bufaMetatext);
    respaMetatext.WriteFlush();
    resp.End();
}



THandle DvProviderLinnCoUkInfo1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkInfo1C(aDevice);
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

