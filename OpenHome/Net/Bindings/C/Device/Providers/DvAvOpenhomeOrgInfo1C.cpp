#include "DvAvOpenhomeOrgInfo1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderAvOpenhomeOrgInfo1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgInfo1C(DvDeviceC aDevice);
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
    void EnablePropertyTrackCount();
    void EnablePropertyDetailsCount();
    void EnablePropertyMetatextCount();
    void EnablePropertyUri();
    void EnablePropertyMetadata();
    void EnablePropertyDuration();
    void EnablePropertyBitRate();
    void EnablePropertyBitDepth();
    void EnablePropertySampleRate();
    void EnablePropertyLossless();
    void EnablePropertyCodecName();
    void EnablePropertyMetatext();
    void EnableActionCounters(CallbackInfo1Counters aCallback, void* aPtr);
    void EnableActionTrack(CallbackInfo1Track aCallback, void* aPtr);
    void EnableActionDetails(CallbackInfo1Details aCallback, void* aPtr);
    void EnableActionMetatext(CallbackInfo1Metatext aCallback, void* aPtr);
private:
    void DoCounters(IDviInvocation& aInvocation);
    void DoTrack(IDviInvocation& aInvocation);
    void DoDetails(IDviInvocation& aInvocation);
    void DoMetatext(IDviInvocation& aInvocation);
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

DvProviderAvOpenhomeOrgInfo1C::DvProviderAvOpenhomeOrgInfo1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "Info", 1)
{
    iPropertyTrackCount = NULL;
    iPropertyDetailsCount = NULL;
    iPropertyMetatextCount = NULL;
    iPropertyUri = NULL;
    iPropertyMetadata = NULL;
    iPropertyDuration = NULL;
    iPropertyBitRate = NULL;
    iPropertyBitDepth = NULL;
    iPropertySampleRate = NULL;
    iPropertyLossless = NULL;
    iPropertyCodecName = NULL;
    iPropertyMetatext = NULL;
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertyTrackCount(TUint aValue)
{
    ASSERT(iPropertyTrackCount != NULL);
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertyTrackCount(TUint& aValue)
{
    ASSERT(iPropertyTrackCount != NULL);
    aValue = iPropertyTrackCount->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertyDetailsCount(TUint aValue)
{
    ASSERT(iPropertyDetailsCount != NULL);
    return SetPropertyUint(*iPropertyDetailsCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertyDetailsCount(TUint& aValue)
{
    ASSERT(iPropertyDetailsCount != NULL);
    aValue = iPropertyDetailsCount->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertyMetatextCount(TUint aValue)
{
    ASSERT(iPropertyMetatextCount != NULL);
    return SetPropertyUint(*iPropertyMetatextCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertyMetatextCount(TUint& aValue)
{
    ASSERT(iPropertyMetatextCount != NULL);
    aValue = iPropertyMetatextCount->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertyUri(const Brx& aValue)
{
    ASSERT(iPropertyUri != NULL);
    return SetPropertyString(*iPropertyUri, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertyUri(Brhz& aValue)
{
    ASSERT(iPropertyUri != NULL);
    aValue.Set(iPropertyUri->Value());
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertyMetadata(const Brx& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertyMetadata(Brhz& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertyDuration(TUint aValue)
{
    ASSERT(iPropertyDuration != NULL);
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertyDuration(TUint& aValue)
{
    ASSERT(iPropertyDuration != NULL);
    aValue = iPropertyDuration->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertyBitRate(TUint aValue)
{
    ASSERT(iPropertyBitRate != NULL);
    return SetPropertyUint(*iPropertyBitRate, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertyBitRate(TUint& aValue)
{
    ASSERT(iPropertyBitRate != NULL);
    aValue = iPropertyBitRate->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertyBitDepth(TUint aValue)
{
    ASSERT(iPropertyBitDepth != NULL);
    return SetPropertyUint(*iPropertyBitDepth, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertyBitDepth(TUint& aValue)
{
    ASSERT(iPropertyBitDepth != NULL);
    aValue = iPropertyBitDepth->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertySampleRate(TUint aValue)
{
    ASSERT(iPropertySampleRate != NULL);
    return SetPropertyUint(*iPropertySampleRate, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertySampleRate(TUint& aValue)
{
    ASSERT(iPropertySampleRate != NULL);
    aValue = iPropertySampleRate->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertyLossless(TBool aValue)
{
    ASSERT(iPropertyLossless != NULL);
    return SetPropertyBool(*iPropertyLossless, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertyLossless(TBool& aValue)
{
    ASSERT(iPropertyLossless != NULL);
    aValue = iPropertyLossless->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertyCodecName(const Brx& aValue)
{
    ASSERT(iPropertyCodecName != NULL);
    return SetPropertyString(*iPropertyCodecName, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertyCodecName(Brhz& aValue)
{
    ASSERT(iPropertyCodecName != NULL);
    aValue.Set(iPropertyCodecName->Value());
}

TBool DvProviderAvOpenhomeOrgInfo1C::SetPropertyMetatext(const Brx& aValue)
{
    ASSERT(iPropertyMetatext != NULL);
    return SetPropertyString(*iPropertyMetatext, aValue);
}

void DvProviderAvOpenhomeOrgInfo1C::GetPropertyMetatext(Brhz& aValue)
{
    ASSERT(iPropertyMetatext != NULL);
    aValue.Set(iPropertyMetatext->Value());
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertyTrackCount()
{
    iPropertyTrackCount = new PropertyUint(iDvStack.Env(), new ParameterUint("TrackCount"));
    iService->AddProperty(iPropertyTrackCount); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertyDetailsCount()
{
    iPropertyDetailsCount = new PropertyUint(iDvStack.Env(), new ParameterUint("DetailsCount"));
    iService->AddProperty(iPropertyDetailsCount); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertyMetatextCount()
{
    iPropertyMetatextCount = new PropertyUint(iDvStack.Env(), new ParameterUint("MetatextCount"));
    iService->AddProperty(iPropertyMetatextCount); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertyUri()
{
    iPropertyUri = new PropertyString(iDvStack.Env(), new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertyMetadata()
{
    iPropertyMetadata = new PropertyString(iDvStack.Env(), new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertyDuration()
{
    iPropertyDuration = new PropertyUint(iDvStack.Env(), new ParameterUint("Duration"));
    iService->AddProperty(iPropertyDuration); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertyBitRate()
{
    iPropertyBitRate = new PropertyUint(iDvStack.Env(), new ParameterUint("BitRate"));
    iService->AddProperty(iPropertyBitRate); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertyBitDepth()
{
    iPropertyBitDepth = new PropertyUint(iDvStack.Env(), new ParameterUint("BitDepth"));
    iService->AddProperty(iPropertyBitDepth); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertySampleRate()
{
    iPropertySampleRate = new PropertyUint(iDvStack.Env(), new ParameterUint("SampleRate"));
    iService->AddProperty(iPropertySampleRate); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertyLossless()
{
    iPropertyLossless = new PropertyBool(iDvStack.Env(), new ParameterBool("Lossless"));
    iService->AddProperty(iPropertyLossless); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertyCodecName()
{
    iPropertyCodecName = new PropertyString(iDvStack.Env(), new ParameterString("CodecName"));
    iService->AddProperty(iPropertyCodecName); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnablePropertyMetatext()
{
    iPropertyMetatext = new PropertyString(iDvStack.Env(), new ParameterString("Metatext"));
    iService->AddProperty(iPropertyMetatext); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1C::EnableActionCounters(CallbackInfo1Counters aCallback, void* aPtr)
{
    iCallbackCounters = aCallback;
    iPtrCounters = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Counters");
    action->AddOutputParameter(new ParameterRelated("TrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("DetailsCount", *iPropertyDetailsCount));
    action->AddOutputParameter(new ParameterRelated("MetatextCount", *iPropertyMetatextCount));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1C::DoCounters);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1C::EnableActionTrack(CallbackInfo1Track aCallback, void* aPtr)
{
    iCallbackTrack = aCallback;
    iPtrTrack = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Track");
    action->AddOutputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1C::DoTrack);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1C::EnableActionDetails(CallbackInfo1Details aCallback, void* aPtr)
{
    iCallbackDetails = aCallback;
    iPtrDetails = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Details");
    action->AddOutputParameter(new ParameterRelated("Duration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("BitRate", *iPropertyBitRate));
    action->AddOutputParameter(new ParameterRelated("BitDepth", *iPropertyBitDepth));
    action->AddOutputParameter(new ParameterRelated("SampleRate", *iPropertySampleRate));
    action->AddOutputParameter(new ParameterRelated("Lossless", *iPropertyLossless));
    action->AddOutputParameter(new ParameterRelated("CodecName", *iPropertyCodecName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1C::DoDetails);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1C::EnableActionMetatext(CallbackInfo1Metatext aCallback, void* aPtr)
{
    iCallbackMetatext = aCallback;
    iPtrMetatext = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Metatext");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyMetatext));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1C::DoMetatext);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1C::DoCounters(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t TrackCount;
    uint32_t DetailsCount;
    uint32_t MetatextCount;
    ASSERT(iCallbackCounters != NULL);
    if (0 != iCallbackCounters(iPtrCounters, invocationC, invocationCPtr, &TrackCount, &DetailsCount, &MetatextCount)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respTrackCount(aInvocation, "TrackCount");
    DviInvocationResponseUint respDetailsCount(aInvocation, "DetailsCount");
    DviInvocationResponseUint respMetatextCount(aInvocation, "MetatextCount");
    invocation.StartResponse();
    respTrackCount.Write(TrackCount);
    respDetailsCount.Write(DetailsCount);
    respMetatextCount.Write(MetatextCount);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgInfo1C::DoTrack(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Uri;
    char* Metadata;
    ASSERT(iCallbackTrack != NULL);
    if (0 != iCallbackTrack(iPtrTrack, invocationC, invocationCPtr, &Uri, &Metadata)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respUri(aInvocation, "Uri");
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    invocation.StartResponse();
    Brhz bufUri((const TChar*)Uri);
    OhNetFreeExternal(Uri);
    respUri.Write(bufUri);
    respUri.WriteFlush();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgInfo1C::DoDetails(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Duration;
    uint32_t BitRate;
    uint32_t BitDepth;
    uint32_t SampleRate;
    uint32_t Lossless;
    char* CodecName;
    ASSERT(iCallbackDetails != NULL);
    if (0 != iCallbackDetails(iPtrDetails, invocationC, invocationCPtr, &Duration, &BitRate, &BitDepth, &SampleRate, &Lossless, &CodecName)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respDuration(aInvocation, "Duration");
    DviInvocationResponseUint respBitRate(aInvocation, "BitRate");
    DviInvocationResponseUint respBitDepth(aInvocation, "BitDepth");
    DviInvocationResponseUint respSampleRate(aInvocation, "SampleRate");
    DviInvocationResponseBool respLossless(aInvocation, "Lossless");
    DviInvocationResponseString respCodecName(aInvocation, "CodecName");
    invocation.StartResponse();
    respDuration.Write(Duration);
    respBitRate.Write(BitRate);
    respBitDepth.Write(BitDepth);
    respSampleRate.Write(SampleRate);
    respLossless.Write((Lossless!=0));
    Brhz bufCodecName((const TChar*)CodecName);
    OhNetFreeExternal(CodecName);
    respCodecName.Write(bufCodecName);
    respCodecName.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgInfo1C::DoMetatext(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Value;
    ASSERT(iCallbackMetatext != NULL);
    if (0 != iCallbackMetatext(iPtrMetatext, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respValue(aInvocation, "Value");
    invocation.StartResponse();
    Brhz bufValue((const TChar*)Value);
    OhNetFreeExternal(Value);
    respValue.Write(bufValue);
    respValue.WriteFlush();
    invocation.EndResponse();
}



THandle STDCALL DvProviderAvOpenhomeOrgInfo1Create(DvDeviceC aDevice)
{
    return new DvProviderAvOpenhomeOrgInfo1C(aDevice);
}

void STDCALL DvProviderAvOpenhomeOrgInfo1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider);
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnableActionCounters(THandle aProvider, CallbackInfo1Counters aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnableActionCounters(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnableActionTrack(THandle aProvider, CallbackInfo1Track aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnableActionTrack(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnableActionDetails(THandle aProvider, CallbackInfo1Details aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnableActionDetails(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnableActionMetatext(THandle aProvider, CallbackInfo1Metatext aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnableActionMetatext(aCallback, aPtr);
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyTrackCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertyTrackCount(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyTrackCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertyTrackCount(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyDetailsCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertyDetailsCount(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyDetailsCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertyDetailsCount(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyMetatextCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertyMetatextCount(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyMetatextCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertyMetatextCount(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertyUri(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertyUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertyMetadata(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyMetadata(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertyMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertyDuration(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyDuration(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertyDuration(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyBitRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertyBitRate(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyBitRate(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertyBitRate(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyBitDepth(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertyBitDepth(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyBitDepth(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertyBitDepth(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertySampleRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertySampleRate(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertySampleRate(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertySampleRate(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyLossless(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertyLossless((aValue!=0))? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyLossless(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertyLossless(val);
    *aValue = (val? 1 : 0);
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyCodecName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertyCodecName(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyCodecName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertyCodecName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyMetatext(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->SetPropertyMetatext(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyMetatext(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->GetPropertyMetatext(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyTrackCount(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertyTrackCount();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyDetailsCount(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertyDetailsCount();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyMetatextCount(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertyMetatextCount();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyUri(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertyUri();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyMetadata(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertyMetadata();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyDuration(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertyDuration();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyBitRate(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertyBitRate();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyBitDepth(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertyBitDepth();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertySampleRate(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertySampleRate();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyLossless(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertyLossless();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyCodecName(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertyCodecName();
}

void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyMetatext(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgInfo1C*>(aProvider)->EnablePropertyMetatext();
}

