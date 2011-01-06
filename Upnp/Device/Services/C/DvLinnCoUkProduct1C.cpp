#include "DvLinnCoUkProduct1.h"
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

class DvProviderLinnCoUkProduct1C : public DvProvider
{
public:
    DvProviderLinnCoUkProduct1C(DvDeviceC aDevice);
    TBool SetPropertyRoom(const Brx& aValue);
    void GetPropertyRoom(Brhz& aValue);
    TBool SetPropertyStandby(TBool aValue);
    void GetPropertyStandby(TBool& aValue);
    void EnableActionRoom(CallbackProduct1Room aCallback, void* aPtr);
    void EnableActionSetRoom(CallbackProduct1SetRoom aCallback, void* aPtr);
    void EnableActionStandby(CallbackProduct1Standby aCallback, void* aPtr);
    void EnableActionSetStandby(CallbackProduct1SetStandby aCallback, void* aPtr);
private:
    void DoRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoStandby(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStandby(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackProduct1Room iCallbackRoom;
    void* iPtrRoom;
    CallbackProduct1SetRoom iCallbackSetRoom;
    void* iPtrSetRoom;
    CallbackProduct1Standby iCallbackStandby;
    void* iPtrStandby;
    CallbackProduct1SetStandby iCallbackSetStandby;
    void* iPtrSetStandby;
    PropertyString* iPropertyRoom;
    PropertyBool* iPropertyStandby;
};

DvProviderLinnCoUkProduct1C::DvProviderLinnCoUkProduct1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Product", 1)
{
    
    iPropertyRoom = new PropertyString(new ParameterString("Room"));
    iService->AddProperty(iPropertyRoom); // passes ownership
    iPropertyStandby = new PropertyBool(new ParameterBool("Standby"));
    iService->AddProperty(iPropertyStandby); // passes ownership
}

TBool DvProviderLinnCoUkProduct1C::SetPropertyRoom(const Brx& aValue)
{
    return SetPropertyString(*iPropertyRoom, aValue);
}

void DvProviderLinnCoUkProduct1C::GetPropertyRoom(Brhz& aValue)
{
    aValue.Set(iPropertyRoom->Value());
}

TBool DvProviderLinnCoUkProduct1C::SetPropertyStandby(TBool aValue)
{
    return SetPropertyBool(*iPropertyStandby, aValue);
}

void DvProviderLinnCoUkProduct1C::GetPropertyStandby(TBool& aValue)
{
    aValue = iPropertyStandby->Value();
}

void DvProviderLinnCoUkProduct1C::EnableActionRoom(CallbackProduct1Room aCallback, void* aPtr)
{
    iCallbackRoom = aCallback;
    iPtrRoom = aPtr;
    Zapp::Action* action = new Zapp::Action("Room");
    action->AddOutputParameter(new ParameterRelated("aRoom", *iPropertyRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1C::DoRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1C::EnableActionSetRoom(CallbackProduct1SetRoom aCallback, void* aPtr)
{
    iCallbackSetRoom = aCallback;
    iPtrSetRoom = aPtr;
    Zapp::Action* action = new Zapp::Action("SetRoom");
    action->AddInputParameter(new ParameterRelated("aRoom", *iPropertyRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1C::DoSetRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1C::EnableActionStandby(CallbackProduct1Standby aCallback, void* aPtr)
{
    iCallbackStandby = aCallback;
    iPtrStandby = aPtr;
    Zapp::Action* action = new Zapp::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("aStandby", *iPropertyStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1C::DoStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1C::EnableActionSetStandby(CallbackProduct1SetStandby aCallback, void* aPtr)
{
    iCallbackSetStandby = aCallback;
    iPtrSetStandby = aPtr;
    Zapp::Action* action = new Zapp::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("aStandby", *iPropertyStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1C::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1C::DoRoom(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aRoom;
    ASSERT(iCallbackRoom != NULL);
    if (0 != iCallbackRoom(iPtrRoom, aVersion, &aRoom)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaRoom(aInvocation, "aRoom");
    resp.Start();
    Brhz bufaRoom((const TChar*)aRoom);
    ZappFreeExternal(aRoom);
    respaRoom.Write(bufaRoom);
    respaRoom.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkProduct1C::DoSetRoom(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aRoom;
    aInvocation.InvocationReadString("aRoom", aRoom);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetRoom != NULL);
    if (0 != iCallbackSetRoom(iPtrSetRoom, aVersion, (const char*)aRoom.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProduct1C::DoStandby(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aStandby;
    ASSERT(iCallbackStandby != NULL);
    if (0 != iCallbackStandby(iPtrStandby, aVersion, &aStandby)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaStandby(aInvocation, "aStandby");
    resp.Start();
    respaStandby.Write((aStandby!=0));
    resp.End();
}

void DvProviderLinnCoUkProduct1C::DoSetStandby(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aStandby = aInvocation.InvocationReadBool("aStandby");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetStandby != NULL);
    if (0 != iCallbackSetStandby(iPtrSetStandby, aVersion, aStandby)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}



THandle DvProviderLinnCoUkProduct1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkProduct1C(aDevice);
}

void DvProviderLinnCoUkProduct1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aProvider);
}

void DvProviderLinnCoUkProduct1EnableActionRoom(THandle aProvider, CallbackProduct1Room aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aProvider)->EnableActionRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct1EnableActionSetRoom(THandle aProvider, CallbackProduct1SetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aProvider)->EnableActionSetRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct1EnableActionStandby(THandle aProvider, CallbackProduct1Standby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aProvider)->EnableActionStandby(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct1EnableActionSetStandby(THandle aProvider, CallbackProduct1SetStandby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aProvider)->EnableActionSetStandby(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkProduct1SetPropertyRoom(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aProvider)->SetPropertyRoom(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct1GetPropertyRoom(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aProvider)->GetPropertyRoom(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct1SetPropertyStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aProvider)->SetPropertyStandby((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct1GetPropertyStandby(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkProduct1C*>(aProvider)->GetPropertyStandby(val);
    *aValue = (val? 1 : 0);
}

