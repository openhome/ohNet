#include "DvLinnCoUkDebug2.h"
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

class DvProviderLinnCoUkDebug2C : public DvProvider
{
public:
    DvProviderLinnCoUkDebug2C(DvDeviceC aDevice);
    void EnableActionSetDebugLevel(CallbackDebug2SetDebugLevel aCallback, void* aPtr);
    void EnableActionDebugLevel(CallbackDebug2DebugLevel aCallback, void* aPtr);
    void EnableActionMemWrite(CallbackDebug2MemWrite aCallback, void* aPtr);
private:
    void DoSetDebugLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoDebugLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoMemWrite(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackDebug2SetDebugLevel iCallbackSetDebugLevel;
    void* iPtrSetDebugLevel;
    CallbackDebug2DebugLevel iCallbackDebugLevel;
    void* iPtrDebugLevel;
    CallbackDebug2MemWrite iCallbackMemWrite;
    void* iPtrMemWrite;
};

DvProviderLinnCoUkDebug2C::DvProviderLinnCoUkDebug2C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Debug", 2)
{
    
}

void DvProviderLinnCoUkDebug2C::EnableActionSetDebugLevel(CallbackDebug2SetDebugLevel aCallback, void* aPtr)
{
    iCallbackSetDebugLevel = aCallback;
    iPtrSetDebugLevel = aPtr;
    Zapp::Action* action = new Zapp::Action("SetDebugLevel");
    action->AddInputParameter(new ParameterUint("aDebugLevel"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDebug2C::DoSetDebugLevel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDebug2C::EnableActionDebugLevel(CallbackDebug2DebugLevel aCallback, void* aPtr)
{
    iCallbackDebugLevel = aCallback;
    iPtrDebugLevel = aPtr;
    Zapp::Action* action = new Zapp::Action("DebugLevel");
    action->AddOutputParameter(new ParameterUint("aDebugLevel"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDebug2C::DoDebugLevel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDebug2C::EnableActionMemWrite(CallbackDebug2MemWrite aCallback, void* aPtr)
{
    iCallbackMemWrite = aCallback;
    iPtrMemWrite = aPtr;
    Zapp::Action* action = new Zapp::Action("MemWrite");
    action->AddInputParameter(new ParameterUint("aMemAddress"));
    action->AddInputParameter(new ParameterBinary("aMemData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDebug2C::DoMemWrite);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDebug2C::DoSetDebugLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aDebugLevel = aInvocation.InvocationReadUint("aDebugLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetDebugLevel != NULL);
    if (0 != iCallbackSetDebugLevel(iPtrSetDebugLevel, aVersion, aDebugLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDebug2C::DoDebugLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aDebugLevel;
    ASSERT(iCallbackDebugLevel != NULL);
    if (0 != iCallbackDebugLevel(iPtrDebugLevel, aVersion, &aDebugLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaDebugLevel(aInvocation, "aDebugLevel");
    resp.Start();
    respaDebugLevel.Write(aDebugLevel);
    resp.End();
}

void DvProviderLinnCoUkDebug2C::DoMemWrite(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aMemAddress = aInvocation.InvocationReadUint("aMemAddress");
    Brh aMemData;
    aInvocation.InvocationReadBinary("aMemData", aMemData);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackMemWrite != NULL);
    if (0 != iCallbackMemWrite(iPtrMemWrite, aVersion, aMemAddress, (const char*)aMemData.Ptr(), aMemData.Bytes())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}



THandle DvProviderLinnCoUkDebug2Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkDebug2C(aDevice);
}

void DvProviderLinnCoUkDebug2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkDebug2C*>(aProvider);
}

void DvProviderLinnCoUkDebug2EnableActionSetDebugLevel(THandle aProvider, CallbackDebug2SetDebugLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDebug2C*>(aProvider)->EnableActionSetDebugLevel(aCallback, aPtr);
}

void DvProviderLinnCoUkDebug2EnableActionDebugLevel(THandle aProvider, CallbackDebug2DebugLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDebug2C*>(aProvider)->EnableActionDebugLevel(aCallback, aPtr);
}

void DvProviderLinnCoUkDebug2EnableActionMemWrite(THandle aProvider, CallbackDebug2MemWrite aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDebug2C*>(aProvider)->EnableActionMemWrite(aCallback, aPtr);
}

