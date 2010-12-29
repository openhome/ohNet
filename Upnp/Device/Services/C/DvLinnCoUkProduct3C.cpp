#include "DvLinnCoUkProduct3.h"
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

class DvProviderLinnCoUkProduct3C : public DvProvider
{
public:
    DvProviderLinnCoUkProduct3C(DvDeviceC aDevice);
    TBool SetPropertyProductType(const Brx& aValue);
    void GetPropertyProductType(Brhz& aValue);
    TBool SetPropertyProductModel(const Brx& aValue);
    void GetPropertyProductModel(Brhz& aValue);
    TBool SetPropertyProductName(const Brx& aValue);
    void GetPropertyProductName(Brhz& aValue);
    TBool SetPropertyProductRoom(const Brx& aValue);
    void GetPropertyProductRoom(Brhz& aValue);
    TBool SetPropertyProductStandby(TBool aValue);
    void GetPropertyProductStandby(TBool& aValue);
    TBool SetPropertyProductSourceIndex(TUint aValue);
    void GetPropertyProductSourceIndex(TUint& aValue);
    TBool SetPropertyProductSourceCount(TUint aValue);
    void GetPropertyProductSourceCount(TUint& aValue);
    TBool SetPropertyProductSourceXml(const Brx& aValue);
    void GetPropertyProductSourceXml(Brhz& aValue);
    TBool SetPropertyStartupSourceIndex(TUint aValue);
    void GetPropertyStartupSourceIndex(TUint& aValue);
    TBool SetPropertyStartupSourceEnabled(TBool aValue);
    void GetPropertyStartupSourceEnabled(TBool& aValue);
    TBool SetPropertyProductAnySourceName(TUint aValue);
    void GetPropertyProductAnySourceName(TUint& aValue);
    TBool SetPropertyProductAnySourceVisible(TUint aValue);
    void GetPropertyProductAnySourceVisible(TUint& aValue);
    TBool SetPropertyProductAnySourceType(TUint aValue);
    void GetPropertyProductAnySourceType(TUint& aValue);
    void EnableActionType(CallbackProduct3Type aCallback, void* aPtr);
    void EnableActionModel(CallbackProduct3Model aCallback, void* aPtr);
    void EnableActionName(CallbackProduct3Name aCallback, void* aPtr);
    void EnableActionSetName(CallbackProduct3SetName aCallback, void* aPtr);
    void EnableActionRoom(CallbackProduct3Room aCallback, void* aPtr);
    void EnableActionSetRoom(CallbackProduct3SetRoom aCallback, void* aPtr);
    void EnableActionStandby(CallbackProduct3Standby aCallback, void* aPtr);
    void EnableActionSetStandby(CallbackProduct3SetStandby aCallback, void* aPtr);
    void EnableActionSourceCount(CallbackProduct3SourceCount aCallback, void* aPtr);
    void EnableActionSourceXml(CallbackProduct3SourceXml aCallback, void* aPtr);
    void EnableActionSourceIndex(CallbackProduct3SourceIndex aCallback, void* aPtr);
    void EnableActionSetSourceIndex(CallbackProduct3SetSourceIndex aCallback, void* aPtr);
    void EnableActionSetSourceIndexByName(CallbackProduct3SetSourceIndexByName aCallback, void* aPtr);
    void EnableActionSetStartupSourceIndexByName(CallbackProduct3SetStartupSourceIndexByName aCallback, void* aPtr);
    void EnableActionStartupSourceIndex(CallbackProduct3StartupSourceIndex aCallback, void* aPtr);
    void EnableActionSetStartupSourceIndex(CallbackProduct3SetStartupSourceIndex aCallback, void* aPtr);
    void EnableActionStartupSourceEnabled(CallbackProduct3StartupSourceEnabled aCallback, void* aPtr);
    void EnableActionSetStartupSourceEnabled(CallbackProduct3SetStartupSourceEnabled aCallback, void* aPtr);
    void EnableActionSourceSystemName(CallbackProduct3SourceSystemName aCallback, void* aPtr);
    void EnableActionSourceName(CallbackProduct3SourceName aCallback, void* aPtr);
    void EnableActionSetSourceName(CallbackProduct3SetSourceName aCallback, void* aPtr);
    void EnableActionSourceType(CallbackProduct3SourceType aCallback, void* aPtr);
    void EnableActionSourceVisible(CallbackProduct3SourceVisible aCallback, void* aPtr);
    void EnableActionSetSourceVisible(CallbackProduct3SetSourceVisible aCallback, void* aPtr);
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
    void DoSourceXml(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSourceIndexByName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupSourceIndexByName(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartupSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartupSourceEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupSourceEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceSystemName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSourceName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceType(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceVisible(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSourceVisible(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackProduct3Type iCallbackType;
    void* iPtrType;
    CallbackProduct3Model iCallbackModel;
    void* iPtrModel;
    CallbackProduct3Name iCallbackName;
    void* iPtrName;
    CallbackProduct3SetName iCallbackSetName;
    void* iPtrSetName;
    CallbackProduct3Room iCallbackRoom;
    void* iPtrRoom;
    CallbackProduct3SetRoom iCallbackSetRoom;
    void* iPtrSetRoom;
    CallbackProduct3Standby iCallbackStandby;
    void* iPtrStandby;
    CallbackProduct3SetStandby iCallbackSetStandby;
    void* iPtrSetStandby;
    CallbackProduct3SourceCount iCallbackSourceCount;
    void* iPtrSourceCount;
    CallbackProduct3SourceXml iCallbackSourceXml;
    void* iPtrSourceXml;
    CallbackProduct3SourceIndex iCallbackSourceIndex;
    void* iPtrSourceIndex;
    CallbackProduct3SetSourceIndex iCallbackSetSourceIndex;
    void* iPtrSetSourceIndex;
    CallbackProduct3SetSourceIndexByName iCallbackSetSourceIndexByName;
    void* iPtrSetSourceIndexByName;
    CallbackProduct3SetStartupSourceIndexByName iCallbackSetStartupSourceIndexByName;
    void* iPtrSetStartupSourceIndexByName;
    CallbackProduct3StartupSourceIndex iCallbackStartupSourceIndex;
    void* iPtrStartupSourceIndex;
    CallbackProduct3SetStartupSourceIndex iCallbackSetStartupSourceIndex;
    void* iPtrSetStartupSourceIndex;
    CallbackProduct3StartupSourceEnabled iCallbackStartupSourceEnabled;
    void* iPtrStartupSourceEnabled;
    CallbackProduct3SetStartupSourceEnabled iCallbackSetStartupSourceEnabled;
    void* iPtrSetStartupSourceEnabled;
    CallbackProduct3SourceSystemName iCallbackSourceSystemName;
    void* iPtrSourceSystemName;
    CallbackProduct3SourceName iCallbackSourceName;
    void* iPtrSourceName;
    CallbackProduct3SetSourceName iCallbackSetSourceName;
    void* iPtrSetSourceName;
    CallbackProduct3SourceType iCallbackSourceType;
    void* iPtrSourceType;
    CallbackProduct3SourceVisible iCallbackSourceVisible;
    void* iPtrSourceVisible;
    CallbackProduct3SetSourceVisible iCallbackSetSourceVisible;
    void* iPtrSetSourceVisible;
    PropertyString* iPropertyProductType;
    PropertyString* iPropertyProductModel;
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductRoom;
    PropertyBool* iPropertyProductStandby;
    PropertyUint* iPropertyProductSourceIndex;
    PropertyUint* iPropertyProductSourceCount;
    PropertyString* iPropertyProductSourceXml;
    PropertyUint* iPropertyStartupSourceIndex;
    PropertyBool* iPropertyStartupSourceEnabled;
    PropertyUint* iPropertyProductAnySourceName;
    PropertyUint* iPropertyProductAnySourceVisible;
    PropertyUint* iPropertyProductAnySourceType;
};

DvProviderLinnCoUkProduct3C::DvProviderLinnCoUkProduct3C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Product", 3)
{
    
    iPropertyProductType = new PropertyString(new ParameterString("ProductType"));
    iService->AddProperty(iPropertyProductType); // passes ownership
    iPropertyProductModel = new PropertyString(new ParameterString("ProductModel"));
    iService->AddProperty(iPropertyProductModel); // passes ownership
    iPropertyProductName = new PropertyString(new ParameterString("ProductName"));
    iService->AddProperty(iPropertyProductName); // passes ownership
    iPropertyProductRoom = new PropertyString(new ParameterString("ProductRoom"));
    iService->AddProperty(iPropertyProductRoom); // passes ownership
    iPropertyProductStandby = new PropertyBool(new ParameterBool("ProductStandby"));
    iService->AddProperty(iPropertyProductStandby); // passes ownership
    iPropertyProductSourceIndex = new PropertyUint(new ParameterUint("ProductSourceIndex"));
    iService->AddProperty(iPropertyProductSourceIndex); // passes ownership
    iPropertyProductSourceCount = new PropertyUint(new ParameterUint("ProductSourceCount"));
    iService->AddProperty(iPropertyProductSourceCount); // passes ownership
    iPropertyProductSourceXml = new PropertyString(new ParameterString("ProductSourceXml"));
    iService->AddProperty(iPropertyProductSourceXml); // passes ownership
    iPropertyStartupSourceIndex = new PropertyUint(new ParameterUint("StartupSourceIndex"));
    iService->AddProperty(iPropertyStartupSourceIndex); // passes ownership
    iPropertyStartupSourceEnabled = new PropertyBool(new ParameterBool("StartupSourceEnabled"));
    iService->AddProperty(iPropertyStartupSourceEnabled); // passes ownership
    iPropertyProductAnySourceName = new PropertyUint(new ParameterUint("ProductAnySourceName"));
    iService->AddProperty(iPropertyProductAnySourceName); // passes ownership
    iPropertyProductAnySourceVisible = new PropertyUint(new ParameterUint("ProductAnySourceVisible"));
    iService->AddProperty(iPropertyProductAnySourceVisible); // passes ownership
    iPropertyProductAnySourceType = new PropertyUint(new ParameterUint("ProductAnySourceType"));
    iService->AddProperty(iPropertyProductAnySourceType); // passes ownership
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyProductType(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductType, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyProductType(Brhz& aValue)
{
    aValue.Set(iPropertyProductType->Value());
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyProductModel(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductModel, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyProductModel(Brhz& aValue)
{
    aValue.Set(iPropertyProductModel->Value());
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyProductName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductName, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyProductName(Brhz& aValue)
{
    aValue.Set(iPropertyProductName->Value());
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyProductRoom(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductRoom, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyProductRoom(Brhz& aValue)
{
    aValue.Set(iPropertyProductRoom->Value());
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyProductStandby(TBool aValue)
{
    return SetPropertyBool(*iPropertyProductStandby, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyProductStandby(TBool& aValue)
{
    aValue = iPropertyProductStandby->Value();
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyProductSourceIndex(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductSourceIndex, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyProductSourceIndex(TUint& aValue)
{
    aValue = iPropertyProductSourceIndex->Value();
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyProductSourceCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductSourceCount, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyProductSourceCount(TUint& aValue)
{
    aValue = iPropertyProductSourceCount->Value();
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyProductSourceXml(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductSourceXml, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyProductSourceXml(Brhz& aValue)
{
    aValue.Set(iPropertyProductSourceXml->Value());
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyStartupSourceIndex(TUint aValue)
{
    return SetPropertyUint(*iPropertyStartupSourceIndex, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyStartupSourceIndex(TUint& aValue)
{
    aValue = iPropertyStartupSourceIndex->Value();
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyStartupSourceEnabled(TBool aValue)
{
    return SetPropertyBool(*iPropertyStartupSourceEnabled, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyStartupSourceEnabled(TBool& aValue)
{
    aValue = iPropertyStartupSourceEnabled->Value();
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyProductAnySourceName(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductAnySourceName, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyProductAnySourceName(TUint& aValue)
{
    aValue = iPropertyProductAnySourceName->Value();
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyProductAnySourceVisible(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductAnySourceVisible, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyProductAnySourceVisible(TUint& aValue)
{
    aValue = iPropertyProductAnySourceVisible->Value();
}

TBool DvProviderLinnCoUkProduct3C::SetPropertyProductAnySourceType(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductAnySourceType, aValue);
}

void DvProviderLinnCoUkProduct3C::GetPropertyProductAnySourceType(TUint& aValue)
{
    aValue = iPropertyProductAnySourceType->Value();
}

void DvProviderLinnCoUkProduct3C::EnableActionType(CallbackProduct3Type aCallback, void* aPtr)
{
    iCallbackType = aCallback;
    iPtrType = aPtr;
    Zapp::Action* action = new Zapp::Action("Type");
    action->AddOutputParameter(new ParameterRelated("aType", *iPropertyProductType));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionModel(CallbackProduct3Model aCallback, void* aPtr)
{
    iCallbackModel = aCallback;
    iPtrModel = aPtr;
    Zapp::Action* action = new Zapp::Action("Model");
    action->AddOutputParameter(new ParameterRelated("aModel", *iPropertyProductModel));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoModel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionName(CallbackProduct3Name aCallback, void* aPtr)
{
    iCallbackName = aCallback;
    iPtrName = aPtr;
    Zapp::Action* action = new Zapp::Action("Name");
    action->AddOutputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSetName(CallbackProduct3SetName aCallback, void* aPtr)
{
    iCallbackSetName = aCallback;
    iPtrSetName = aPtr;
    Zapp::Action* action = new Zapp::Action("SetName");
    action->AddInputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSetName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionRoom(CallbackProduct3Room aCallback, void* aPtr)
{
    iCallbackRoom = aCallback;
    iPtrRoom = aPtr;
    Zapp::Action* action = new Zapp::Action("Room");
    action->AddOutputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSetRoom(CallbackProduct3SetRoom aCallback, void* aPtr)
{
    iCallbackSetRoom = aCallback;
    iPtrSetRoom = aPtr;
    Zapp::Action* action = new Zapp::Action("SetRoom");
    action->AddInputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSetRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionStandby(CallbackProduct3Standby aCallback, void* aPtr)
{
    iCallbackStandby = aCallback;
    iPtrStandby = aPtr;
    Zapp::Action* action = new Zapp::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSetStandby(CallbackProduct3SetStandby aCallback, void* aPtr)
{
    iCallbackSetStandby = aCallback;
    iPtrSetStandby = aPtr;
    Zapp::Action* action = new Zapp::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceCount(CallbackProduct3SourceCount aCallback, void* aPtr)
{
    iCallbackSourceCount = aCallback;
    iPtrSourceCount = aPtr;
    Zapp::Action* action = new Zapp::Action("SourceCount");
    action->AddOutputParameter(new ParameterRelated("aSourceCount", *iPropertyProductSourceCount));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSourceCount);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceXml(CallbackProduct3SourceXml aCallback, void* aPtr)
{
    iCallbackSourceXml = aCallback;
    iPtrSourceXml = aPtr;
    Zapp::Action* action = new Zapp::Action("SourceXml");
    action->AddOutputParameter(new ParameterRelated("aSourceXml", *iPropertyProductSourceXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSourceXml);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceIndex(CallbackProduct3SourceIndex aCallback, void* aPtr)
{
    iCallbackSourceIndex = aCallback;
    iPtrSourceIndex = aPtr;
    Zapp::Action* action = new Zapp::Action("SourceIndex");
    action->AddOutputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSetSourceIndex(CallbackProduct3SetSourceIndex aCallback, void* aPtr)
{
    iCallbackSetSourceIndex = aCallback;
    iPtrSetSourceIndex = aPtr;
    Zapp::Action* action = new Zapp::Action("SetSourceIndex");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSetSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSetSourceIndexByName(CallbackProduct3SetSourceIndexByName aCallback, void* aPtr)
{
    iCallbackSetSourceIndexByName = aCallback;
    iPtrSetSourceIndexByName = aPtr;
    Zapp::Action* action = new Zapp::Action("SetSourceIndexByName");
    action->AddInputParameter(new ParameterString("aSourceName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSetSourceIndexByName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSetStartupSourceIndexByName(CallbackProduct3SetStartupSourceIndexByName aCallback, void* aPtr)
{
    iCallbackSetStartupSourceIndexByName = aCallback;
    iPtrSetStartupSourceIndexByName = aPtr;
    Zapp::Action* action = new Zapp::Action("SetStartupSourceIndexByName");
    action->AddInputParameter(new ParameterString("aSourceName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSetStartupSourceIndexByName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionStartupSourceIndex(CallbackProduct3StartupSourceIndex aCallback, void* aPtr)
{
    iCallbackStartupSourceIndex = aCallback;
    iPtrStartupSourceIndex = aPtr;
    Zapp::Action* action = new Zapp::Action("StartupSourceIndex");
    action->AddOutputParameter(new ParameterRelated("aSourceIndex", *iPropertyStartupSourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoStartupSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSetStartupSourceIndex(CallbackProduct3SetStartupSourceIndex aCallback, void* aPtr)
{
    iCallbackSetStartupSourceIndex = aCallback;
    iPtrSetStartupSourceIndex = aPtr;
    Zapp::Action* action = new Zapp::Action("SetStartupSourceIndex");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyStartupSourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSetStartupSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionStartupSourceEnabled(CallbackProduct3StartupSourceEnabled aCallback, void* aPtr)
{
    iCallbackStartupSourceEnabled = aCallback;
    iPtrStartupSourceEnabled = aPtr;
    Zapp::Action* action = new Zapp::Action("StartupSourceEnabled");
    action->AddOutputParameter(new ParameterRelated("aStartupSourceEnabled", *iPropertyStartupSourceEnabled));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoStartupSourceEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSetStartupSourceEnabled(CallbackProduct3SetStartupSourceEnabled aCallback, void* aPtr)
{
    iCallbackSetStartupSourceEnabled = aCallback;
    iPtrSetStartupSourceEnabled = aPtr;
    Zapp::Action* action = new Zapp::Action("SetStartupSourceEnabled");
    action->AddInputParameter(new ParameterRelated("aStartupSourceEnabled", *iPropertyStartupSourceEnabled));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSetStartupSourceEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceSystemName(CallbackProduct3SourceSystemName aCallback, void* aPtr)
{
    iCallbackSourceSystemName = aCallback;
    iPtrSourceSystemName = aPtr;
    Zapp::Action* action = new Zapp::Action("SourceSystemName");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSourceSystemName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceName(CallbackProduct3SourceName aCallback, void* aPtr)
{
    iCallbackSourceName = aCallback;
    iPtrSourceName = aPtr;
    Zapp::Action* action = new Zapp::Action("SourceName");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSourceName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSetSourceName(CallbackProduct3SetSourceName aCallback, void* aPtr)
{
    iCallbackSetSourceName = aCallback;
    iPtrSetSourceName = aPtr;
    Zapp::Action* action = new Zapp::Action("SetSourceName");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddInputParameter(new ParameterString("aSourceName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSetSourceName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceType(CallbackProduct3SourceType aCallback, void* aPtr)
{
    iCallbackSourceType = aCallback;
    iPtrSourceType = aPtr;
    Zapp::Action* action = new Zapp::Action("SourceType");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceType"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSourceType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSourceVisible(CallbackProduct3SourceVisible aCallback, void* aPtr)
{
    iCallbackSourceVisible = aCallback;
    iPtrSourceVisible = aPtr;
    Zapp::Action* action = new Zapp::Action("SourceVisible");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterBool("aSourceVisible"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSourceVisible);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::EnableActionSetSourceVisible(CallbackProduct3SetSourceVisible aCallback, void* aPtr)
{
    iCallbackSetSourceVisible = aCallback;
    iPtrSetSourceVisible = aPtr;
    Zapp::Action* action = new Zapp::Action("SetSourceVisible");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddInputParameter(new ParameterBool("aSourceVisible"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct3C::DoSetSourceVisible);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3C::DoType(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoModel(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoName(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoSetName(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoRoom(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoSetRoom(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoStandby(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoSetStandby(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoSourceCount(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoSourceXml(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aSourceXml;
    ASSERT(iCallbackSourceXml != NULL);
    if (0 != iCallbackSourceXml(iPtrSourceXml, aVersion, &aSourceXml)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaSourceXml(aInvocation, "aSourceXml");
    resp.Start();
    Brhz bufaSourceXml((const TChar*)aSourceXml);
    ZappFreeExternal(aSourceXml);
    respaSourceXml.Write(bufaSourceXml);
    respaSourceXml.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkProduct3C::DoSourceIndex(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoSetSourceIndex(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoSetSourceIndexByName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aSourceName;
    aInvocation.InvocationReadString("aSourceName", aSourceName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetSourceIndexByName != NULL);
    if (0 != iCallbackSetSourceIndexByName(iPtrSetSourceIndexByName, aVersion, (const char*)aSourceName.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProduct3C::DoSetStartupSourceIndexByName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aSourceName;
    aInvocation.InvocationReadString("aSourceName", aSourceName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetStartupSourceIndexByName != NULL);
    if (0 != iCallbackSetStartupSourceIndexByName(iPtrSetStartupSourceIndexByName, aVersion, (const char*)aSourceName.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProduct3C::DoStartupSourceIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aSourceIndex;
    ASSERT(iCallbackStartupSourceIndex != NULL);
    if (0 != iCallbackStartupSourceIndex(iPtrStartupSourceIndex, aVersion, &aSourceIndex)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaSourceIndex(aInvocation, "aSourceIndex");
    resp.Start();
    respaSourceIndex.Write(aSourceIndex);
    resp.End();
}

void DvProviderLinnCoUkProduct3C::DoSetStartupSourceIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetStartupSourceIndex != NULL);
    if (0 != iCallbackSetStartupSourceIndex(iPtrSetStartupSourceIndex, aVersion, aSourceIndex)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProduct3C::DoStartupSourceEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aStartupSourceEnabled;
    ASSERT(iCallbackStartupSourceEnabled != NULL);
    if (0 != iCallbackStartupSourceEnabled(iPtrStartupSourceEnabled, aVersion, &aStartupSourceEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaStartupSourceEnabled(aInvocation, "aStartupSourceEnabled");
    resp.Start();
    respaStartupSourceEnabled.Write((aStartupSourceEnabled!=0));
    resp.End();
}

void DvProviderLinnCoUkProduct3C::DoSetStartupSourceEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aStartupSourceEnabled = aInvocation.InvocationReadBool("aStartupSourceEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetStartupSourceEnabled != NULL);
    if (0 != iCallbackSetStartupSourceEnabled(iPtrSetStartupSourceEnabled, aVersion, aStartupSourceEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProduct3C::DoSourceSystemName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aSourceName;
    ASSERT(iCallbackSourceSystemName != NULL);
    if (0 != iCallbackSourceSystemName(iPtrSourceSystemName, aVersion, aSourceIndex, &aSourceName)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaSourceName(aInvocation, "aSourceName");
    resp.Start();
    Brhz bufaSourceName((const TChar*)aSourceName);
    ZappFreeExternal(aSourceName);
    respaSourceName.Write(bufaSourceName);
    respaSourceName.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkProduct3C::DoSourceName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aSourceName;
    ASSERT(iCallbackSourceName != NULL);
    if (0 != iCallbackSourceName(iPtrSourceName, aVersion, aSourceIndex, &aSourceName)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaSourceName(aInvocation, "aSourceName");
    resp.Start();
    Brhz bufaSourceName((const TChar*)aSourceName);
    ZappFreeExternal(aSourceName);
    respaSourceName.Write(bufaSourceName);
    respaSourceName.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkProduct3C::DoSetSourceName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    Brhz aSourceName;
    aInvocation.InvocationReadString("aSourceName", aSourceName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetSourceName != NULL);
    if (0 != iCallbackSetSourceName(iPtrSetSourceName, aVersion, aSourceIndex, (const char*)aSourceName.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProduct3C::DoSourceType(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkProduct3C::DoSourceVisible(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aSourceVisible;
    ASSERT(iCallbackSourceVisible != NULL);
    if (0 != iCallbackSourceVisible(iPtrSourceVisible, aVersion, aSourceIndex, &aSourceVisible)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaSourceVisible(aInvocation, "aSourceVisible");
    resp.Start();
    respaSourceVisible.Write((aSourceVisible!=0));
    resp.End();
}

void DvProviderLinnCoUkProduct3C::DoSetSourceVisible(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    TBool aSourceVisible = aInvocation.InvocationReadBool("aSourceVisible");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetSourceVisible != NULL);
    if (0 != iCallbackSetSourceVisible(iPtrSetSourceVisible, aVersion, aSourceIndex, aSourceVisible)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}



THandle DvProviderLinnCoUkProduct3Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkProduct3C(aDevice);
}

void DvProviderLinnCoUkProduct3Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider);
}

void DvProviderLinnCoUkProduct3EnableActionType(THandle aProvider, CallbackProduct3Type aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionType(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionModel(THandle aProvider, CallbackProduct3Model aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionModel(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionName(THandle aProvider, CallbackProduct3Name aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetName(THandle aProvider, CallbackProduct3SetName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionRoom(THandle aProvider, CallbackProduct3Room aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetRoom(THandle aProvider, CallbackProduct3SetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetRoom(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionStandby(THandle aProvider, CallbackProduct3Standby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionStandby(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetStandby(THandle aProvider, CallbackProduct3SetStandby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetStandby(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceCount(THandle aProvider, CallbackProduct3SourceCount aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceCount(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceXml(THandle aProvider, CallbackProduct3SourceXml aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceXml(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceIndex(THandle aProvider, CallbackProduct3SourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetSourceIndex(THandle aProvider, CallbackProduct3SetSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetSourceIndexByName(THandle aProvider, CallbackProduct3SetSourceIndexByName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetSourceIndexByName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndexByName(THandle aProvider, CallbackProduct3SetStartupSourceIndexByName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetStartupSourceIndexByName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionStartupSourceIndex(THandle aProvider, CallbackProduct3StartupSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionStartupSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndex(THandle aProvider, CallbackProduct3SetStartupSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetStartupSourceIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionStartupSourceEnabled(THandle aProvider, CallbackProduct3StartupSourceEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionStartupSourceEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceEnabled(THandle aProvider, CallbackProduct3SetStartupSourceEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetStartupSourceEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceSystemName(THandle aProvider, CallbackProduct3SourceSystemName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceSystemName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceName(THandle aProvider, CallbackProduct3SourceName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetSourceName(THandle aProvider, CallbackProduct3SetSourceName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetSourceName(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceType(THandle aProvider, CallbackProduct3SourceType aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceType(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSourceVisible(THandle aProvider, CallbackProduct3SourceVisible aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSourceVisible(aCallback, aPtr);
}

void DvProviderLinnCoUkProduct3EnableActionSetSourceVisible(THandle aProvider, CallbackProduct3SetSourceVisible aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->EnableActionSetSourceVisible(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductType(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductType(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductType(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductType(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductModel(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductModel(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductModel(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductModel(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductName(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductRoom(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductRoom(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductRoom(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductRoom(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductStandby((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductStandby(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductStandby(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductSourceIndex(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductSourceIndex(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductSourceIndex(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductSourceCount(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductSourceCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductSourceCount(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceXml(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductSourceXml(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductSourceXml(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductSourceXml(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProduct3SetPropertyStartupSourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyStartupSourceIndex(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyStartupSourceIndex(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyStartupSourceIndex(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProduct3SetPropertyStartupSourceEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyStartupSourceEnabled((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyStartupSourceEnabled(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyStartupSourceEnabled(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceName(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductAnySourceName(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceName(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductAnySourceName(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceVisible(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductAnySourceVisible(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceVisible(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductAnySourceVisible(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceType(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->SetPropertyProductAnySourceType(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceType(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProduct3C*>(aProvider)->GetPropertyProductAnySourceType(val);
    *aValue = val;
}

