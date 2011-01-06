#include "DvLinnCoUkMediaTime1.h"
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

class DvProviderLinnCoUkMediaTime1C : public DvProvider
{
public:
    DvProviderLinnCoUkMediaTime1C(DvDeviceC aDevice);
    TBool SetPropertySeconds(TUint aValue);
    void GetPropertySeconds(TUint& aValue);
    void EnableActionSeconds(CallbackMediaTime1Seconds aCallback, void* aPtr);
private:
    void DoSeconds(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackMediaTime1Seconds iCallbackSeconds;
    void* iPtrSeconds;
    PropertyUint* iPropertySeconds;
};

DvProviderLinnCoUkMediaTime1C::DvProviderLinnCoUkMediaTime1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "MediaTime", 1)
{
    
    iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"));
    iService->AddProperty(iPropertySeconds); // passes ownership
}

TBool DvProviderLinnCoUkMediaTime1C::SetPropertySeconds(TUint aValue)
{
    return SetPropertyUint(*iPropertySeconds, aValue);
}

void DvProviderLinnCoUkMediaTime1C::GetPropertySeconds(TUint& aValue)
{
    aValue = iPropertySeconds->Value();
}

void DvProviderLinnCoUkMediaTime1C::EnableActionSeconds(CallbackMediaTime1Seconds aCallback, void* aPtr)
{
    iCallbackSeconds = aCallback;
    iPtrSeconds = aPtr;
    Zapp::Action* action = new Zapp::Action("Seconds");
    action->AddOutputParameter(new ParameterRelated("aSeconds", *iPropertySeconds));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkMediaTime1C::DoSeconds);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkMediaTime1C::DoSeconds(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aSeconds;
    ASSERT(iCallbackSeconds != NULL);
    if (0 != iCallbackSeconds(iPtrSeconds, aVersion, &aSeconds)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaSeconds(aInvocation, "aSeconds");
    resp.Start();
    respaSeconds.Write(aSeconds);
    resp.End();
}



THandle DvProviderLinnCoUkMediaTime1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkMediaTime1C(aDevice);
}

void DvProviderLinnCoUkMediaTime1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkMediaTime1C*>(aProvider);
}

void DvProviderLinnCoUkMediaTime1EnableActionSeconds(THandle aProvider, CallbackMediaTime1Seconds aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkMediaTime1C*>(aProvider)->EnableActionSeconds(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkMediaTime1SetPropertySeconds(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkMediaTime1C*>(aProvider)->SetPropertySeconds(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkMediaTime1GetPropertySeconds(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkMediaTime1C*>(aProvider)->GetPropertySeconds(val);
    *aValue = val;
}

