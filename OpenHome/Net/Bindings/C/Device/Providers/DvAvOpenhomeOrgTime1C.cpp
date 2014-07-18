#include "DvAvOpenhomeOrgTime1.h"
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

class DvProviderAvOpenhomeOrgTime1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgTime1C(DvDeviceC aDevice);
    TBool SetPropertyTrackCount(TUint aValue);
    void GetPropertyTrackCount(TUint& aValue);
    TBool SetPropertyDuration(TUint aValue);
    void GetPropertyDuration(TUint& aValue);
    TBool SetPropertySeconds(TUint aValue);
    void GetPropertySeconds(TUint& aValue);
    void EnablePropertyTrackCount();
    void EnablePropertyDuration();
    void EnablePropertySeconds();
    void EnableActionTime(CallbackTime1Time aCallback, void* aPtr);
private:
    void DoTime(IDviInvocation& aInvocation);
private:
    CallbackTime1Time iCallbackTime;
    void* iPtrTime;
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertySeconds;
};

DvProviderAvOpenhomeOrgTime1C::DvProviderAvOpenhomeOrgTime1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "Time", 1)
{
    iPropertyTrackCount = NULL;
    iPropertyDuration = NULL;
    iPropertySeconds = NULL;
}

TBool DvProviderAvOpenhomeOrgTime1C::SetPropertyTrackCount(TUint aValue)
{
    ASSERT(iPropertyTrackCount != NULL);
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderAvOpenhomeOrgTime1C::GetPropertyTrackCount(TUint& aValue)
{
    ASSERT(iPropertyTrackCount != NULL);
    aValue = iPropertyTrackCount->Value();
}

TBool DvProviderAvOpenhomeOrgTime1C::SetPropertyDuration(TUint aValue)
{
    ASSERT(iPropertyDuration != NULL);
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderAvOpenhomeOrgTime1C::GetPropertyDuration(TUint& aValue)
{
    ASSERT(iPropertyDuration != NULL);
    aValue = iPropertyDuration->Value();
}

TBool DvProviderAvOpenhomeOrgTime1C::SetPropertySeconds(TUint aValue)
{
    ASSERT(iPropertySeconds != NULL);
    return SetPropertyUint(*iPropertySeconds, aValue);
}

void DvProviderAvOpenhomeOrgTime1C::GetPropertySeconds(TUint& aValue)
{
    ASSERT(iPropertySeconds != NULL);
    aValue = iPropertySeconds->Value();
}

void DvProviderAvOpenhomeOrgTime1C::EnablePropertyTrackCount()
{
    iPropertyTrackCount = new PropertyUint(iDvStack.Env(), new ParameterUint("TrackCount"));
    iService->AddProperty(iPropertyTrackCount); // passes ownership
}

void DvProviderAvOpenhomeOrgTime1C::EnablePropertyDuration()
{
    iPropertyDuration = new PropertyUint(iDvStack.Env(), new ParameterUint("Duration"));
    iService->AddProperty(iPropertyDuration); // passes ownership
}

void DvProviderAvOpenhomeOrgTime1C::EnablePropertySeconds()
{
    iPropertySeconds = new PropertyUint(iDvStack.Env(), new ParameterUint("Seconds"));
    iService->AddProperty(iPropertySeconds); // passes ownership
}

void DvProviderAvOpenhomeOrgTime1C::EnableActionTime(CallbackTime1Time aCallback, void* aPtr)
{
    iCallbackTime = aCallback;
    iPtrTime = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Time");
    action->AddOutputParameter(new ParameterRelated("TrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("Duration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("Seconds", *iPropertySeconds));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgTime1C::DoTime);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgTime1C::DoTime(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t TrackCount;
    uint32_t Duration;
    uint32_t Seconds;
    ASSERT(iCallbackTime != NULL);
    if (0 != iCallbackTime(iPtrTime, invocationC, invocationCPtr, &TrackCount, &Duration, &Seconds)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respTrackCount(aInvocation, "TrackCount");
    DviInvocationResponseUint respDuration(aInvocation, "Duration");
    DviInvocationResponseUint respSeconds(aInvocation, "Seconds");
    invocation.StartResponse();
    respTrackCount.Write(TrackCount);
    respDuration.Write(Duration);
    respSeconds.Write(Seconds);
    invocation.EndResponse();
}



THandle STDCALL DvProviderAvOpenhomeOrgTime1Create(DvDeviceC aDevice)
{
    return new DvProviderAvOpenhomeOrgTime1C(aDevice);
}

void STDCALL DvProviderAvOpenhomeOrgTime1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider);
}

void STDCALL DvProviderAvOpenhomeOrgTime1EnableActionTime(THandle aProvider, CallbackTime1Time aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->EnableActionTime(aCallback, aPtr);
}

int32_t STDCALL DvProviderAvOpenhomeOrgTime1SetPropertyTrackCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->SetPropertyTrackCount(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgTime1GetPropertyTrackCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->GetPropertyTrackCount(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgTime1SetPropertyDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->SetPropertyDuration(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgTime1GetPropertyDuration(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->GetPropertyDuration(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgTime1SetPropertySeconds(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->SetPropertySeconds(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgTime1GetPropertySeconds(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->GetPropertySeconds(val);
    *aValue = val;
}

void STDCALL DvProviderAvOpenhomeOrgTime1EnablePropertyTrackCount(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->EnablePropertyTrackCount();
}

void STDCALL DvProviderAvOpenhomeOrgTime1EnablePropertyDuration(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->EnablePropertyDuration();
}

void STDCALL DvProviderAvOpenhomeOrgTime1EnablePropertySeconds(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->EnablePropertySeconds();
}

