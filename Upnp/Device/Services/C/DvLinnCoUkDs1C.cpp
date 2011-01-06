#include "DvLinnCoUkDs1.h"
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

class DvProviderLinnCoUkDs1C : public DvProvider
{
public:
    DvProviderLinnCoUkDs1C(DvDeviceC aDevice);
    TBool SetPropertySupportedProtocols(const Brx& aValue);
    void GetPropertySupportedProtocols(Brhz& aValue);
    TBool SetPropertyTrackDuration(TUint aValue);
    void GetPropertyTrackDuration(TUint& aValue);
    TBool SetPropertyTrackBitRate(TUint aValue);
    void GetPropertyTrackBitRate(TUint& aValue);
    TBool SetPropertyTrackLossless(TBool aValue);
    void GetPropertyTrackLossless(TBool& aValue);
    TBool SetPropertyTrackBitDepth(TUint aValue);
    void GetPropertyTrackBitDepth(TUint& aValue);
    TBool SetPropertyTrackSampleRate(TUint aValue);
    void GetPropertyTrackSampleRate(TUint& aValue);
    TBool SetPropertyTrackCodecName(const Brx& aValue);
    void GetPropertyTrackCodecName(Brhz& aValue);
    TBool SetPropertyTrackId(TUint aValue);
    void GetPropertyTrackId(TUint& aValue);
    TBool SetPropertyTransportState(const Brx& aValue);
    void GetPropertyTransportState(Brhz& aValue);
    void EnableActionPlay(CallbackDs1Play aCallback, void* aPtr);
    void EnableActionPause(CallbackDs1Pause aCallback, void* aPtr);
    void EnableActionStop(CallbackDs1Stop aCallback, void* aPtr);
    void EnableActionSeekSecondAbsolute(CallbackDs1SeekSecondAbsolute aCallback, void* aPtr);
    void EnableActionSeekSecondRelative(CallbackDs1SeekSecondRelative aCallback, void* aPtr);
    void EnableActionSeekTrackId(CallbackDs1SeekTrackId aCallback, void* aPtr);
    void EnableActionSeekTrackAbsolute(CallbackDs1SeekTrackAbsolute aCallback, void* aPtr);
    void EnableActionSeekTrackRelative(CallbackDs1SeekTrackRelative aCallback, void* aPtr);
    void EnableActionState(CallbackDs1State aCallback, void* aPtr);
    void EnableActionProtocolInfo(CallbackDs1ProtocolInfo aCallback, void* aPtr);
private:
    void DoPlay(IDviInvocation& aInvocation, TUint aVersion);
    void DoPause(IDviInvocation& aInvocation, TUint aVersion);
    void DoStop(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekTrackId(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekTrackAbsolute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekTrackRelative(IDviInvocation& aInvocation, TUint aVersion);
    void DoState(IDviInvocation& aInvocation, TUint aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackDs1Play iCallbackPlay;
    void* iPtrPlay;
    CallbackDs1Pause iCallbackPause;
    void* iPtrPause;
    CallbackDs1Stop iCallbackStop;
    void* iPtrStop;
    CallbackDs1SeekSecondAbsolute iCallbackSeekSecondAbsolute;
    void* iPtrSeekSecondAbsolute;
    CallbackDs1SeekSecondRelative iCallbackSeekSecondRelative;
    void* iPtrSeekSecondRelative;
    CallbackDs1SeekTrackId iCallbackSeekTrackId;
    void* iPtrSeekTrackId;
    CallbackDs1SeekTrackAbsolute iCallbackSeekTrackAbsolute;
    void* iPtrSeekTrackAbsolute;
    CallbackDs1SeekTrackRelative iCallbackSeekTrackRelative;
    void* iPtrSeekTrackRelative;
    CallbackDs1State iCallbackState;
    void* iPtrState;
    CallbackDs1ProtocolInfo iCallbackProtocolInfo;
    void* iPtrProtocolInfo;
    PropertyString* iPropertySupportedProtocols;
    PropertyUint* iPropertyTrackDuration;
    PropertyUint* iPropertyTrackBitRate;
    PropertyBool* iPropertyTrackLossless;
    PropertyUint* iPropertyTrackBitDepth;
    PropertyUint* iPropertyTrackSampleRate;
    PropertyString* iPropertyTrackCodecName;
    PropertyUint* iPropertyTrackId;
    PropertyString* iPropertyTransportState;
};

DvProviderLinnCoUkDs1C::DvProviderLinnCoUkDs1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Ds", 1)
{
    
    TChar** allowedValues;
    TUint index;
    iPropertySupportedProtocols = new PropertyString(new ParameterString("SupportedProtocols"));
    iService->AddProperty(iPropertySupportedProtocols); // passes ownership
    iPropertyTrackDuration = new PropertyUint(new ParameterUint("TrackDuration"));
    iService->AddProperty(iPropertyTrackDuration); // passes ownership
    iPropertyTrackBitRate = new PropertyUint(new ParameterUint("TrackBitRate"));
    iService->AddProperty(iPropertyTrackBitRate); // passes ownership
    iPropertyTrackLossless = new PropertyBool(new ParameterBool("TrackLossless"));
    iService->AddProperty(iPropertyTrackLossless); // passes ownership
    iPropertyTrackBitDepth = new PropertyUint(new ParameterUint("TrackBitDepth"));
    iService->AddProperty(iPropertyTrackBitDepth); // passes ownership
    iPropertyTrackSampleRate = new PropertyUint(new ParameterUint("TrackSampleRate"));
    iService->AddProperty(iPropertyTrackSampleRate); // passes ownership
    iPropertyTrackCodecName = new PropertyString(new ParameterString("TrackCodecName"));
    iService->AddProperty(iPropertyTrackCodecName); // passes ownership
    iPropertyTrackId = new PropertyUint(new ParameterUint("TrackId"));
    iService->AddProperty(iPropertyTrackId); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
}

TBool DvProviderLinnCoUkDs1C::SetPropertySupportedProtocols(const Brx& aValue)
{
    return SetPropertyString(*iPropertySupportedProtocols, aValue);
}

void DvProviderLinnCoUkDs1C::GetPropertySupportedProtocols(Brhz& aValue)
{
    aValue.Set(iPropertySupportedProtocols->Value());
}

TBool DvProviderLinnCoUkDs1C::SetPropertyTrackDuration(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackDuration, aValue);
}

void DvProviderLinnCoUkDs1C::GetPropertyTrackDuration(TUint& aValue)
{
    aValue = iPropertyTrackDuration->Value();
}

TBool DvProviderLinnCoUkDs1C::SetPropertyTrackBitRate(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackBitRate, aValue);
}

void DvProviderLinnCoUkDs1C::GetPropertyTrackBitRate(TUint& aValue)
{
    aValue = iPropertyTrackBitRate->Value();
}

TBool DvProviderLinnCoUkDs1C::SetPropertyTrackLossless(TBool aValue)
{
    return SetPropertyBool(*iPropertyTrackLossless, aValue);
}

void DvProviderLinnCoUkDs1C::GetPropertyTrackLossless(TBool& aValue)
{
    aValue = iPropertyTrackLossless->Value();
}

TBool DvProviderLinnCoUkDs1C::SetPropertyTrackBitDepth(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackBitDepth, aValue);
}

void DvProviderLinnCoUkDs1C::GetPropertyTrackBitDepth(TUint& aValue)
{
    aValue = iPropertyTrackBitDepth->Value();
}

TBool DvProviderLinnCoUkDs1C::SetPropertyTrackSampleRate(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackSampleRate, aValue);
}

void DvProviderLinnCoUkDs1C::GetPropertyTrackSampleRate(TUint& aValue)
{
    aValue = iPropertyTrackSampleRate->Value();
}

TBool DvProviderLinnCoUkDs1C::SetPropertyTrackCodecName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTrackCodecName, aValue);
}

void DvProviderLinnCoUkDs1C::GetPropertyTrackCodecName(Brhz& aValue)
{
    aValue.Set(iPropertyTrackCodecName->Value());
}

TBool DvProviderLinnCoUkDs1C::SetPropertyTrackId(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackId, aValue);
}

void DvProviderLinnCoUkDs1C::GetPropertyTrackId(TUint& aValue)
{
    aValue = iPropertyTrackId->Value();
}

TBool DvProviderLinnCoUkDs1C::SetPropertyTransportState(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderLinnCoUkDs1C::GetPropertyTransportState(Brhz& aValue)
{
    aValue.Set(iPropertyTransportState->Value());
}

void DvProviderLinnCoUkDs1C::EnableActionPlay(CallbackDs1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    Zapp::Action* action = new Zapp::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1C::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1C::EnableActionPause(CallbackDs1Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    Zapp::Action* action = new Zapp::Action("Pause");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1C::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1C::EnableActionStop(CallbackDs1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    Zapp::Action* action = new Zapp::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1C::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1C::EnableActionSeekSecondAbsolute(CallbackDs1SeekSecondAbsolute aCallback, void* aPtr)
{
    iCallbackSeekSecondAbsolute = aCallback;
    iPtrSeekSecondAbsolute = aPtr;
    Zapp::Action* action = new Zapp::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("aSecond"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1C::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1C::EnableActionSeekSecondRelative(CallbackDs1SeekSecondRelative aCallback, void* aPtr)
{
    iCallbackSeekSecondRelative = aCallback;
    iPtrSeekSecondRelative = aPtr;
    Zapp::Action* action = new Zapp::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("aSecond"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1C::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1C::EnableActionSeekTrackId(CallbackDs1SeekTrackId aCallback, void* aPtr)
{
    iCallbackSeekTrackId = aCallback;
    iPtrSeekTrackId = aPtr;
    Zapp::Action* action = new Zapp::Action("SeekTrackId");
    action->AddInputParameter(new ParameterRelated("aTrackId", *iPropertyTrackId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1C::DoSeekTrackId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1C::EnableActionSeekTrackAbsolute(CallbackDs1SeekTrackAbsolute aCallback, void* aPtr)
{
    iCallbackSeekTrackAbsolute = aCallback;
    iPtrSeekTrackAbsolute = aPtr;
    Zapp::Action* action = new Zapp::Action("SeekTrackAbsolute");
    action->AddInputParameter(new ParameterUint("aTrack"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1C::DoSeekTrackAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1C::EnableActionSeekTrackRelative(CallbackDs1SeekTrackRelative aCallback, void* aPtr)
{
    iCallbackSeekTrackRelative = aCallback;
    iPtrSeekTrackRelative = aPtr;
    Zapp::Action* action = new Zapp::Action("SeekTrackRelative");
    action->AddInputParameter(new ParameterInt("aTrack"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1C::DoSeekTrackRelative);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1C::EnableActionState(CallbackDs1State aCallback, void* aPtr)
{
    iCallbackState = aCallback;
    iPtrState = aPtr;
    Zapp::Action* action = new Zapp::Action("State");
    action->AddOutputParameter(new ParameterRelated("aTransportState", *iPropertyTransportState));
    action->AddOutputParameter(new ParameterRelated("aTrackDuration", *iPropertyTrackDuration));
    action->AddOutputParameter(new ParameterRelated("aTrackBitRate", *iPropertyTrackBitRate));
    action->AddOutputParameter(new ParameterRelated("aTrackLossless", *iPropertyTrackLossless));
    action->AddOutputParameter(new ParameterRelated("aTrackBitDepth", *iPropertyTrackBitDepth));
    action->AddOutputParameter(new ParameterRelated("aTrackSampleRate", *iPropertyTrackSampleRate));
    action->AddOutputParameter(new ParameterRelated("aTrackCodecName", *iPropertyTrackCodecName));
    action->AddOutputParameter(new ParameterRelated("aTrackId", *iPropertyTrackId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1C::DoState);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1C::EnableActionProtocolInfo(CallbackDs1ProtocolInfo aCallback, void* aPtr)
{
    iCallbackProtocolInfo = aCallback;
    iPtrProtocolInfo = aPtr;
    Zapp::Action* action = new Zapp::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("aSupportedProtocols", *iPropertySupportedProtocols));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1C::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1C::DoPlay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDs1C::DoPause(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDs1C::DoStop(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDs1C::DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSecond = aInvocation.InvocationReadUint("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSeekSecondAbsolute != NULL);
    if (0 != iCallbackSeekSecondAbsolute(iPtrSeekSecondAbsolute, aVersion, aSecond)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDs1C::DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aSecond = aInvocation.InvocationReadInt("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSeekSecondRelative != NULL);
    if (0 != iCallbackSeekSecondRelative(iPtrSeekSecondRelative, aVersion, aSecond)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDs1C::DoSeekTrackId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aTrackId = aInvocation.InvocationReadUint("aTrackId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSeekTrackId != NULL);
    if (0 != iCallbackSeekTrackId(iPtrSeekTrackId, aVersion, aTrackId)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDs1C::DoSeekTrackAbsolute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aTrack = aInvocation.InvocationReadUint("aTrack");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSeekTrackAbsolute != NULL);
    if (0 != iCallbackSeekTrackAbsolute(iPtrSeekTrackAbsolute, aVersion, aTrack)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDs1C::DoSeekTrackRelative(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aTrack = aInvocation.InvocationReadInt("aTrack");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSeekTrackRelative != NULL);
    if (0 != iCallbackSeekTrackRelative(iPtrSeekTrackRelative, aVersion, aTrack)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDs1C::DoState(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aTransportState;
    uint32_t aTrackDuration;
    uint32_t aTrackBitRate;
    uint32_t aTrackLossless;
    uint32_t aTrackBitDepth;
    uint32_t aTrackSampleRate;
    char* aTrackCodecName;
    uint32_t aTrackId;
    ASSERT(iCallbackState != NULL);
    if (0 != iCallbackState(iPtrState, aVersion, &aTransportState, &aTrackDuration, &aTrackBitRate, &aTrackLossless, &aTrackBitDepth, &aTrackSampleRate, &aTrackCodecName, &aTrackId)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaTransportState(aInvocation, "aTransportState");
    InvocationResponseUint respaTrackDuration(aInvocation, "aTrackDuration");
    InvocationResponseUint respaTrackBitRate(aInvocation, "aTrackBitRate");
    InvocationResponseBool respaTrackLossless(aInvocation, "aTrackLossless");
    InvocationResponseUint respaTrackBitDepth(aInvocation, "aTrackBitDepth");
    InvocationResponseUint respaTrackSampleRate(aInvocation, "aTrackSampleRate");
    InvocationResponseString respaTrackCodecName(aInvocation, "aTrackCodecName");
    InvocationResponseUint respaTrackId(aInvocation, "aTrackId");
    resp.Start();
    Brhz bufaTransportState((const TChar*)aTransportState);
    ZappFreeExternal(aTransportState);
    respaTransportState.Write(bufaTransportState);
    respaTransportState.WriteFlush();
    respaTrackDuration.Write(aTrackDuration);
    respaTrackBitRate.Write(aTrackBitRate);
    respaTrackLossless.Write((aTrackLossless!=0));
    respaTrackBitDepth.Write(aTrackBitDepth);
    respaTrackSampleRate.Write(aTrackSampleRate);
    Brhz bufaTrackCodecName((const TChar*)aTrackCodecName);
    ZappFreeExternal(aTrackCodecName);
    respaTrackCodecName.Write(bufaTrackCodecName);
    respaTrackCodecName.WriteFlush();
    respaTrackId.Write(aTrackId);
    resp.End();
}

void DvProviderLinnCoUkDs1C::DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aSupportedProtocols;
    ASSERT(iCallbackProtocolInfo != NULL);
    if (0 != iCallbackProtocolInfo(iPtrProtocolInfo, aVersion, &aSupportedProtocols)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaSupportedProtocols(aInvocation, "aSupportedProtocols");
    resp.Start();
    Brhz bufaSupportedProtocols((const TChar*)aSupportedProtocols);
    ZappFreeExternal(aSupportedProtocols);
    respaSupportedProtocols.Write(bufaSupportedProtocols);
    respaSupportedProtocols.WriteFlush();
    resp.End();
}



THandle DvProviderLinnCoUkDs1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkDs1C(aDevice);
}

void DvProviderLinnCoUkDs1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider);
}

void DvProviderLinnCoUkDs1EnableActionPlay(THandle aProvider, CallbackDs1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionPause(THandle aProvider, CallbackDs1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->EnableActionPause(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionStop(THandle aProvider, CallbackDs1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackDs1SeekSecondAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->EnableActionSeekSecondAbsolute(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionSeekSecondRelative(THandle aProvider, CallbackDs1SeekSecondRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->EnableActionSeekSecondRelative(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionSeekTrackId(THandle aProvider, CallbackDs1SeekTrackId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->EnableActionSeekTrackId(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionSeekTrackAbsolute(THandle aProvider, CallbackDs1SeekTrackAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->EnableActionSeekTrackAbsolute(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionSeekTrackRelative(THandle aProvider, CallbackDs1SeekTrackRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->EnableActionSeekTrackRelative(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionState(THandle aProvider, CallbackDs1State aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->EnableActionState(aCallback, aPtr);
}

void DvProviderLinnCoUkDs1EnableActionProtocolInfo(THandle aProvider, CallbackDs1ProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->EnableActionProtocolInfo(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkDs1SetPropertySupportedProtocols(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->SetPropertySupportedProtocols(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertySupportedProtocols(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->GetPropertySupportedProtocols(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->SetPropertyTrackDuration(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackDuration(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->GetPropertyTrackDuration(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackBitRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->SetPropertyTrackBitRate(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackBitRate(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->GetPropertyTrackBitRate(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackLossless(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->SetPropertyTrackLossless((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackLossless(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->GetPropertyTrackLossless(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackBitDepth(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->SetPropertyTrackBitDepth(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackBitDepth(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->GetPropertyTrackBitDepth(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackSampleRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->SetPropertyTrackSampleRate(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackSampleRate(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->GetPropertyTrackSampleRate(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackCodecName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->SetPropertyTrackCodecName(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackCodecName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->GetPropertyTrackCodecName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkDs1SetPropertyTrackId(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->SetPropertyTrackId(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTrackId(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->GetPropertyTrackId(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkDs1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->SetPropertyTransportState(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDs1GetPropertyTransportState(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkDs1C*>(aProvider)->GetPropertyTransportState(buf);
    *aValue = (char*)buf.Transfer();
}

