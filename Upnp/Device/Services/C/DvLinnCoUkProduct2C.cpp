#include "DvLinnCoUkProduct2.h"
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

class DvProviderLinnCoUkProduct2C : public DvProvider
{
public:
    DvProviderLinnCoUkProduct2C(DvDeviceC aDevice);
    TBool SetPropertyProductName(const Brx& aValue);
    void GetPropertyProductName(Brhz& aValue);
    TBool SetPropertyProductRoom(const Brx& aValue);
    void GetPropertyProductRoom(Brhz& aValue);
    TBool SetPropertyProductStandby(TBool aValue);
    void GetPropertyProductStandby(TBool& aValue);
    TBool SetPropertyProductSourceIndex(TUint aValue);
    void GetPropertyProductSourceIndex(TUint& aValue);
    void EnableActionType(CallbackProduct2Type aCallback, void* aPtr);
    void EnableActionModel(CallbackProduct2Model aCallback, void* aPtr);
    void EnableActionName(CallbackProduct2Name aCallback, void* aPtr);
    void EnableActionSetName(CallbackProduct2SetName aCallback, void* aPtr);
    void EnableActionRoom(CallbackProduct2Room aCallback, void* aPtr);
    void EnableActionSetRoom(CallbackProduct2SetRoom aCallback, void* aPtr);
    void EnableActionStandby(CallbackProduct2Standby aCallback, void* aPtr);
    void EnableActionSetStandby(CallbackProduct2SetStandby aCallback, void* aPtr);
    void EnableActionSourceCount(CallbackProduct2SourceCount aCallback, void* aPtr);
    void EnableActionSourceIndex(CallbackProduct2SourceIndex aCallback, void* aPtr);
    void EnableActionSetSourceIndex(CallbackProduct2SetSourceIndex aCallback, void* aPtr);
    void EnableActionSourceType(CallbackProduct2SourceType aCallback, void* aPtr);
private:
    void DoType(IDviInvocation& aInvocation, TUint aVersion);
    void DoModel(IDviInvocation& aInvocation, TUint aVersion);
    void DoName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetName(IDviInvocation& aInvocation, TUint aVersion);
    void DoRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoStandby(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStandby(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceCount(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceType(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackProduct2Type iCallbackType;
    void* iPtrType;
    CallbackProduct2Model iCallbackModel;
    void* iPtrModel;
    CallbackProduct2Name iCallbackName;
    void* iPtrName;
    CallbackProduct2SetName iCallbackSetName;
    void* iPtrSetName;
    CallbackProduct2Room iCallbackRoom;
    void* iPtrRoom;
    CallbackProduct2SetRoom iCallbackSetRoom;
    void* iPtrSetRoom;
    CallbackProduct2Standby iCallbackStandby;
    void* iPtrStandby;
    CallbackProduct2SetStandby iCallbackSetStandby;
    void* iPtrSetStandby;
    CallbackProduct2SourceCount iCallbackSourceCount;
    void* iPtrSourceCount;
    CallbackProduct2SourceIndex iCallbackSourceIndex;
    void* iPtrSourceIndex;
    CallbackProduct2SetSourceIndex iCallbackSetSourceIndex;
    void* iPtrSetSourceIndex;
    CallbackProduct2SourceType iCallbackSourceType;
    void* iPtrSourceType;
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductRoom;
    PropertyBool* iPropertyProductStandby;
    PropertyUint* iPropertyProductSourceIndex;
};

DvProviderLinnCoUkProduct2C::DvProviderLinnCoUkProduct2C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Product", 2)
{
    
    iPropertyProductName = new PropertyString(new ParameterString("ProductName"));
    iService->AddProperty(iPropertyProductName); // passes ownership
    iPropertyProductRoom = new PropertyString(new ParameterString("ProductRoom"));
    iService->AddProperty(iPropertyProductRoom); // passes ownership
    iPropertyProductStandby = new PropertyBool(new ParameterBool("ProductStandby"));
    iService->AddProperty(iPropertyProductStandby); // passes ownership
    iPropertyProductSourceIndex = new PropertyUint(new ParameterUint("ProductSourceIndex"));
    iService->AddProperty(iPropertyProductSourceIndex); // passes ownership
}

TBool DvProviderLinnCoUkProduct2C::SetPropertyProductName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductName, aValue);
}

void DvProviderLinnCoUkProduct2C::GetPropertyProductName(Brhz& aValue)
{
    aValue.Set(iPropertyProductName->Value());
}

TBool DvProviderLinnCoUkProduct2C::SetPropertyProductRoom(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductRoom, aValue);
}

void DvProviderLinnCoUkProduct2C::GetPropertyProductRoom(Brhz& aValue)
{
    aValue.Set(iPropertyProductRoom->Value());
}

TBool DvProviderLinnCoUkProduct2C::SetPropertyProductStandby(TBool aValue)
{
    return SetPropertyBool(*iPropertyProductStandby, aValue);
}

void DvProviderLinnCoUkProduct2C::GetPropertyProductStandby(TBool& aValue)
{
    aValue = iPropertyProductStandby->Value();
}

TBool DvProviderLinnCoUkProduct2C::SetPropertyProductSourceIndex(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductSourceIndex, aValue);
}

void DvProviderLinnCoUkProduct2C::GetPropertyProductSourceIndex(TUint& aValue)
{
    aValue = iPropertyProductSourceIndex->Value();
}

void DvProviderLinnCoUkProduct2C::EnableActionType(CallbackProduct2Type aCallback, void* aPtr)
{
    iCallbackType = aCallback;
    iPtrType = aPtr;
    Zapp::Action* action = new Zapp::Action("Type");
    action->AddOutputParameter(new ParameterString("aType"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::EnableActionModel(CallbackProduct2Model aCallback, void* aPtr)
{
    iCallbackModel = aCallback;
    iPtrModel = aPtr;
    Zapp::Action* action = new Zapp::Action("Model");
    action->AddOutputParameter(new ParameterString("aModel"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoModel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::EnableActionName(CallbackProduct2Name aCallback, void* aPtr)
{
    iCallbackName = aCallback;
    iPtrName = aPtr;
    Zapp::Action* action = new Zapp::Action("Name");
    action->AddOutputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::EnableActionSetName(CallbackProduct2SetName aCallback, void* aPtr)
{
    iCallbackSetName = aCallback;
    iPtrSetName = aPtr;
    Zapp::Action* action = new Zapp::Action("SetName");
    action->AddInputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoSetName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::EnableActionRoom(CallbackProduct2Room aCallback, void* aPtr)
{
    iCallbackRoom = aCallback;
    iPtrRoom = aPtr;
    Zapp::Action* action = new Zapp::Action("Room");
    action->AddOutputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::EnableActionSetRoom(CallbackProduct2SetRoom aCallback, void* aPtr)
{
    iCallbackSetRoom = aCallback;
    iPtrSetRoom = aPtr;
    Zapp::Action* action = new Zapp::Action("SetRoom");
    action->AddInputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoSetRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::EnableActionStandby(CallbackProduct2Standby aCallback, void* aPtr)
{
    iCallbackStandby = aCallback;
    iPtrStandby = aPtr;
    Zapp::Action* action = new Zapp::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::EnableActionSetStandby(CallbackProduct2SetStandby aCallback, void* aPtr)
{
    iCallbackSetStandby = aCallback;
    iPtrSetStandby = aPtr;
    Zapp::Action* action = new Zapp::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::EnableActionSourceCount(CallbackProduct2SourceCount aCallback, void* aPtr)
{
    iCallbackSourceCount = aCallback;
    iPtrSourceCount = aPtr;
    Zapp::Action* action = new Zapp::Action("SourceCount");
    action->AddOutputParameter(new ParameterRelated("aSourceCount", *iPropertyProductSourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoSourceCount);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::EnableActionSourceIndex(CallbackProduct2SourceIndex aCallback, void* aPtr)
{
    iCallbackSourceIndex = aCallback;
    iPtrSourceIndex = aPtr;
    Zapp::Action* action = new Zapp::Action("SourceIndex");
    action->AddOutputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::EnableActionSetSourceIndex(CallbackProduct2SetSourceIndex aCallback, void* aPtr)
{
    iCallbackSetSourceIndex = aCallback;
    iPtrSetSourceIndex = aPtr;
    Zapp::Action* action = new Zapp::Action("SetSourceIndex");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoSetSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::EnableActionSourceType(CallbackProduct2SourceType aCallback, void* aPtr)
{
    iCallbackSourceType = aCallback;
    iPtrSourceType = aPtr;
    Zapp::Action* action = new Zapp::Action("SourceType");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceType"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2C::DoSourceType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2C::DoType(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aType;
    ASSERT(iCallbackType != NULL);
    if (0 != iCallbackType(iPtrType, aVersion, &aType)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaType(aInvocation, "aType");
    resp.Start();
    Brhz bufaType((const TChar*)aType);
    ZappFreeExternal(aType);
    respaType.Write(bufaType);
    respaType.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkProduct2C::DoModel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aModel;
    ASSERT(iCallbackModel != NULL);
    if (0 != iCallbackModel(iPtrModel, aVersion, &aModel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaModel(aInvocation, "aModel");
    resp.Start();
    Brhz bufaModel((const TChar*)aModel);
    ZappFreeExternal(aModel);
    respaModel.Write(bufaModel);
    respaModel.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkProduct2C::DoName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aName;
    ASSERT(iCallbackName != NULL);
    if (0 != iCallbackName(iPtrName, aVersion, &aName)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaName(aInvocation, "aName");
    resp.Start();
    Brhz bufaName((const TChar*)aName);
    ZappFreeExternal(aName);
    respaName.Write(bufaName);
    respaName.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkProduct2C::DoSetName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aName;
    aInvocation.InvocationReadString("aName", aName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetName != NULL);
    if (0 != iCallbackSetName(iPtrSetName, aVersion, (const char*)aName.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProduct2C::DoRoom(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct2C::DoSetRoom(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct2C::DoStandby(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct2C::DoSetStandby(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct2C::DoSourceCount(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aSourceCount;
    ASSERT(iCallbackSourceCount != NULL);
    if (0 != iCallbackSourceCount(iPtrSourceCount, aVersion, &aSourceCount)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaSourceCount(aInvocation, "aSourceCount");
    resp.Start();
    respaSourceCount.Write(aSourceCount);
    resp.End();
}

void DvProviderLinnCoUkProduct2C::DoSourceIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aSourceIndex;
    ASSERT(iCallbackSourceIndex != NULL);
    if (0 != iCallbackSourceIndex(iPtrSourceIndex, aVersion, &aSourceIndex)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaSourceIndex(aInvocation, "aSourceIndex");
    resp.Start();
    respaSourceIndex.Write(aSourceIndex);
    resp.End();
}

void DvProviderLinnCoUkProduct2C::DoSetSourceIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetSourceIndex != NULL);
    if (0 != iCallbackSetSourceIndex(iPtrSetSourceIndex, aVersion, aSourceIndex)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProduct2C::DoSourceType(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aSourceType;
    ASSERT(iCallbackSourceType != NULL);
    if (0 != iCallbackSourceType(iPtrSourceType, aVersion, aSourceIndex, &aSourceType)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaSourceType(aInvocation, "aSourceType");
    resp.Start();
    Brhz bufaSourceType((const TChar*)aSourceType);
    ZappFreeExternal(aSourceType);
    respaSourceType.Write(bufaSourceType);
    respaSourceType.WriteFlush();
    resp.End();
}



THandle DvProviderLinnCoUkProduct2Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkProduct2C(aDevice);
}

void DvProviderLinnCoUkProduct2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider);
}

void DvProviderLinnCoUkProduct2EnableActionType(THandle aProvider, CallbackProduct2Type aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionType(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionModel(THandle aProvider, CallbackProduct2Model aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionModel(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionName(THandle aProvider, CallbackProduct2Name aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSetName(THandle aProvider, CallbackProduct2SetName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionSetName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionRoom(THandle aProvider, CallbackProduct2Room aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSetRoom(THandle aProvider, CallbackProduct2SetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionSetRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionStandby(THandle aProvider, CallbackProduct2Standby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionStandby(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSetStandby(THandle aProvider, CallbackProduct2SetStandby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionSetStandby(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSourceCount(THandle aProvider, CallbackProduct2SourceCount aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionSourceCount(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSourceIndex(THandle aProvider, CallbackProduct2SourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSetSourceIndex(THandle aProvider, CallbackProduct2SetSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionSetSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct2EnableActionSourceType(THandle aProvider, CallbackProduct2SourceType aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->EnableActionSourceType(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkProduct2SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->SetPropertyProductName(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct2GetPropertyProductName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->GetPropertyProductName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct2SetPropertyProductRoom(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->SetPropertyProductRoom(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct2GetPropertyProductRoom(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->GetPropertyProductRoom(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct2SetPropertyProductStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->SetPropertyProductStandby((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct2GetPropertyProductStandby(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->GetPropertyProductStandby(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkProduct2SetPropertyProductSourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->SetPropertyProductSourceIndex(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct2GetPropertyProductSourceIndex(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct2C*>(aProvider)->GetPropertyProductSourceIndex(val);
    *aValue = val;
}

