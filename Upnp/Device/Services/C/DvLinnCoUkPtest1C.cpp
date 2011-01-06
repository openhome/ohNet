#include "DvLinnCoUkPtest1.h"
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

class DvProviderLinnCoUkPtest1C : public DvProvider
{
public:
    DvProviderLinnCoUkPtest1C(DvDeviceC aDevice);
    void EnableActionTestComPort(CallbackPtest1TestComPort aCallback, void* aPtr);
    void EnableActionLedsOn(CallbackPtest1LedsOn aCallback, void* aPtr);
    void EnableActionLedsOff(CallbackPtest1LedsOff aCallback, void* aPtr);
private:
    void DoTestComPort(IDviInvocation& aInvocation, TUint aVersion);
    void DoLedsOn(IDviInvocation& aInvocation, TUint aVersion);
    void DoLedsOff(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackPtest1TestComPort iCallbackTestComPort;
    void* iPtrTestComPort;
    CallbackPtest1LedsOn iCallbackLedsOn;
    void* iPtrLedsOn;
    CallbackPtest1LedsOff iCallbackLedsOff;
    void* iPtrLedsOff;
};

DvProviderLinnCoUkPtest1C::DvProviderLinnCoUkPtest1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Ptest", 1)
{
    
}

void DvProviderLinnCoUkPtest1C::EnableActionTestComPort(CallbackPtest1TestComPort aCallback, void* aPtr)
{
    iCallbackTestComPort = aCallback;
    iPtrTestComPort = aPtr;
    Zapp::Action* action = new Zapp::Action("TestComPort");
    action->AddInputParameter(new ParameterUint("aPort"));
    action->AddOutputParameter(new ParameterBool("aResult"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPtest1C::DoTestComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPtest1C::EnableActionLedsOn(CallbackPtest1LedsOn aCallback, void* aPtr)
{
    iCallbackLedsOn = aCallback;
    iPtrLedsOn = aPtr;
    Zapp::Action* action = new Zapp::Action("LedsOn");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPtest1C::DoLedsOn);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPtest1C::EnableActionLedsOff(CallbackPtest1LedsOff aCallback, void* aPtr)
{
    iCallbackLedsOff = aCallback;
    iPtrLedsOff = aPtr;
    Zapp::Action* action = new Zapp::Action("LedsOff");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPtest1C::DoLedsOff);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPtest1C::DoTestComPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aPort = aInvocation.InvocationReadUint("aPort");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aResult;
    ASSERT(iCallbackTestComPort != NULL);
    if (0 != iCallbackTestComPort(iPtrTestComPort, aVersion, aPort, &aResult)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaResult(aInvocation, "aResult");
    resp.Start();
    respaResult.Write((aResult!=0));
    resp.End();
}

void DvProviderLinnCoUkPtest1C::DoLedsOn(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackLedsOn != NULL);
    if (0 != iCallbackLedsOn(iPtrLedsOn, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPtest1C::DoLedsOff(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackLedsOff != NULL);
    if (0 != iCallbackLedsOff(iPtrLedsOff, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}



THandle DvProviderLinnCoUkPtest1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkPtest1C(aDevice);
}

void DvProviderLinnCoUkPtest1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkPtest1C*>(aProvider);
}

void DvProviderLinnCoUkPtest1EnableActionTestComPort(THandle aProvider, CallbackPtest1TestComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPtest1C*>(aProvider)->EnableActionTestComPort(aCallback, aPtr);
}

void DvProviderLinnCoUkPtest1EnableActionLedsOn(THandle aProvider, CallbackPtest1LedsOn aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPtest1C*>(aProvider)->EnableActionLedsOn(aCallback, aPtr);
}

void DvProviderLinnCoUkPtest1EnableActionLedsOff(THandle aProvider, CallbackPtest1LedsOff aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPtest1C*>(aProvider)->EnableActionLedsOff(aCallback, aPtr);
}

