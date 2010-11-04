#include <Core/DvLinnCoUkProduct3.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkProduct3::SetPropertyProductType(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductType, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyProductType(Brhz& aValue)
{
    aValue.Set(iPropertyProductType->Value());
}

TBool DvProviderLinnCoUkProduct3::SetPropertyProductModel(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductModel, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyProductModel(Brhz& aValue)
{
    aValue.Set(iPropertyProductModel->Value());
}

TBool DvProviderLinnCoUkProduct3::SetPropertyProductName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductName, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyProductName(Brhz& aValue)
{
    aValue.Set(iPropertyProductName->Value());
}

TBool DvProviderLinnCoUkProduct3::SetPropertyProductRoom(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductRoom, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyProductRoom(Brhz& aValue)
{
    aValue.Set(iPropertyProductRoom->Value());
}

TBool DvProviderLinnCoUkProduct3::SetPropertyProductStandby(TBool aValue)
{
    return SetPropertyBool(*iPropertyProductStandby, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyProductStandby(TBool& aValue)
{
    aValue = iPropertyProductStandby->Value();
}

TBool DvProviderLinnCoUkProduct3::SetPropertyProductSourceIndex(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductSourceIndex, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyProductSourceIndex(TUint& aValue)
{
    aValue = iPropertyProductSourceIndex->Value();
}

TBool DvProviderLinnCoUkProduct3::SetPropertyProductSourceCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductSourceCount, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyProductSourceCount(TUint& aValue)
{
    aValue = iPropertyProductSourceCount->Value();
}

TBool DvProviderLinnCoUkProduct3::SetPropertyProductSourceXml(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductSourceXml, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyProductSourceXml(Brhz& aValue)
{
    aValue.Set(iPropertyProductSourceXml->Value());
}

TBool DvProviderLinnCoUkProduct3::SetPropertyStartupSourceIndex(TUint aValue)
{
    return SetPropertyUint(*iPropertyStartupSourceIndex, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyStartupSourceIndex(TUint& aValue)
{
    aValue = iPropertyStartupSourceIndex->Value();
}

TBool DvProviderLinnCoUkProduct3::SetPropertyStartupSourceEnabled(TBool aValue)
{
    return SetPropertyBool(*iPropertyStartupSourceEnabled, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyStartupSourceEnabled(TBool& aValue)
{
    aValue = iPropertyStartupSourceEnabled->Value();
}

TBool DvProviderLinnCoUkProduct3::SetPropertyProductAnySourceName(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductAnySourceName, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyProductAnySourceName(TUint& aValue)
{
    aValue = iPropertyProductAnySourceName->Value();
}

TBool DvProviderLinnCoUkProduct3::SetPropertyProductAnySourceVisible(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductAnySourceVisible, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyProductAnySourceVisible(TUint& aValue)
{
    aValue = iPropertyProductAnySourceVisible->Value();
}

TBool DvProviderLinnCoUkProduct3::SetPropertyProductAnySourceType(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductAnySourceType, aValue);
}

void DvProviderLinnCoUkProduct3::GetPropertyProductAnySourceType(TUint& aValue)
{
    aValue = iPropertyProductAnySourceType->Value();
}

DvProviderLinnCoUkProduct3::DvProviderLinnCoUkProduct3(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Product", 3)
{
    Functor empty;
    iPropertyProductType = new PropertyString(new ParameterString("ProductType"), empty);
    iService->AddProperty(iPropertyProductType); // passes ownership
    iPropertyProductModel = new PropertyString(new ParameterString("ProductModel"), empty);
    iService->AddProperty(iPropertyProductModel); // passes ownership
    iPropertyProductName = new PropertyString(new ParameterString("ProductName"), empty);
    iService->AddProperty(iPropertyProductName); // passes ownership
    iPropertyProductRoom = new PropertyString(new ParameterString("ProductRoom"), empty);
    iService->AddProperty(iPropertyProductRoom); // passes ownership
    iPropertyProductStandby = new PropertyBool(new ParameterBool("ProductStandby"), empty);
    iService->AddProperty(iPropertyProductStandby); // passes ownership
    iPropertyProductSourceIndex = new PropertyUint(new ParameterUint("ProductSourceIndex"), empty);
    iService->AddProperty(iPropertyProductSourceIndex); // passes ownership
    iPropertyProductSourceCount = new PropertyUint(new ParameterUint("ProductSourceCount"), empty);
    iService->AddProperty(iPropertyProductSourceCount); // passes ownership
    iPropertyProductSourceXml = new PropertyString(new ParameterString("ProductSourceXml"), empty);
    iService->AddProperty(iPropertyProductSourceXml); // passes ownership
    iPropertyStartupSourceIndex = new PropertyUint(new ParameterUint("StartupSourceIndex"), empty);
    iService->AddProperty(iPropertyStartupSourceIndex); // passes ownership
    iPropertyStartupSourceEnabled = new PropertyBool(new ParameterBool("StartupSourceEnabled"), empty);
    iService->AddProperty(iPropertyStartupSourceEnabled); // passes ownership
    iPropertyProductAnySourceName = new PropertyUint(new ParameterUint("ProductAnySourceName"), empty);
    iService->AddProperty(iPropertyProductAnySourceName); // passes ownership
    iPropertyProductAnySourceVisible = new PropertyUint(new ParameterUint("ProductAnySourceVisible"), empty);
    iService->AddProperty(iPropertyProductAnySourceVisible); // passes ownership
    iPropertyProductAnySourceType = new PropertyUint(new ParameterUint("ProductAnySourceType"), empty);
    iService->AddProperty(iPropertyProductAnySourceType); // passes ownership
}

void DvProviderLinnCoUkProduct3::EnableActionType()
{
    Zapp::Action* action = new Zapp::Action("Type");
    action->AddOutputParameter(new ParameterRelated("aType", *iPropertyProductType));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionModel()
{
    Zapp::Action* action = new Zapp::Action("Model");
    action->AddOutputParameter(new ParameterRelated("aModel", *iPropertyProductModel));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoModel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionName()
{
    Zapp::Action* action = new Zapp::Action("Name");
    action->AddOutputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSetName()
{
    Zapp::Action* action = new Zapp::Action("SetName");
    action->AddInputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSetName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionRoom()
{
    Zapp::Action* action = new Zapp::Action("Room");
    action->AddOutputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSetRoom()
{
    Zapp::Action* action = new Zapp::Action("SetRoom");
    action->AddInputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSetRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionStandby()
{
    Zapp::Action* action = new Zapp::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSetStandby()
{
    Zapp::Action* action = new Zapp::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSourceCount()
{
    Zapp::Action* action = new Zapp::Action("SourceCount");
    action->AddOutputParameter(new ParameterRelated("aSourceCount", *iPropertyProductSourceCount));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSourceCount);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSourceXml()
{
    Zapp::Action* action = new Zapp::Action("SourceXml");
    action->AddOutputParameter(new ParameterRelated("aSourceXml", *iPropertyProductSourceXml));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSourceXml);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("SourceIndex");
    action->AddOutputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSetSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("SetSourceIndex");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSetSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSetSourceIndexByName()
{
    Zapp::Action* action = new Zapp::Action("SetSourceIndexByName");
    action->AddInputParameter(new ParameterString("aSourceName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSetSourceIndexByName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSetStartupSourceIndexByName()
{
    Zapp::Action* action = new Zapp::Action("SetStartupSourceIndexByName");
    action->AddInputParameter(new ParameterString("aSourceName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSetStartupSourceIndexByName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionStartupSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("StartupSourceIndex");
    action->AddOutputParameter(new ParameterRelated("aSourceIndex", *iPropertyStartupSourceIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoStartupSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSetStartupSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("SetStartupSourceIndex");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyStartupSourceIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSetStartupSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionStartupSourceEnabled()
{
    Zapp::Action* action = new Zapp::Action("StartupSourceEnabled");
    action->AddOutputParameter(new ParameterRelated("aStartupSourceEnabled", *iPropertyStartupSourceEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoStartupSourceEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSetStartupSourceEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetStartupSourceEnabled");
    action->AddInputParameter(new ParameterRelated("aStartupSourceEnabled", *iPropertyStartupSourceEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSetStartupSourceEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSourceSystemName()
{
    Zapp::Action* action = new Zapp::Action("SourceSystemName");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSourceSystemName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSourceName()
{
    Zapp::Action* action = new Zapp::Action("SourceName");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSourceName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSetSourceName()
{
    Zapp::Action* action = new Zapp::Action("SetSourceName");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddInputParameter(new ParameterString("aSourceName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSetSourceName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSourceType()
{
    Zapp::Action* action = new Zapp::Action("SourceType");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceType"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSourceType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSourceVisible()
{
    Zapp::Action* action = new Zapp::Action("SourceVisible");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterBool("aSourceVisible"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSourceVisible);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::EnableActionSetSourceVisible()
{
    Zapp::Action* action = new Zapp::Action("SetSourceVisible");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddInputParameter(new ParameterBool("aSourceVisible"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkProduct3::DoSetSourceVisible);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct3::DoType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaType(aInvocation, "aType");
    Type(resp, aVersion, respaType);
}

void DvProviderLinnCoUkProduct3::DoModel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaModel(aInvocation, "aModel");
    Model(resp, aVersion, respaModel);
}

void DvProviderLinnCoUkProduct3::DoName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaName(aInvocation, "aName");
    Name(resp, aVersion, respaName);
}

void DvProviderLinnCoUkProduct3::DoSetName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aName;
    aInvocation.InvocationReadString("aName", aName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetName(resp, aVersion, aName);
}

void DvProviderLinnCoUkProduct3::DoRoom(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaRoom(aInvocation, "aRoom");
    Room(resp, aVersion, respaRoom);
}

void DvProviderLinnCoUkProduct3::DoSetRoom(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aRoom;
    aInvocation.InvocationReadString("aRoom", aRoom);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRoom(resp, aVersion, aRoom);
}

void DvProviderLinnCoUkProduct3::DoStandby(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaStandby(aInvocation, "aStandby");
    Standby(resp, aVersion, respaStandby);
}

void DvProviderLinnCoUkProduct3::DoSetStandby(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aStandby = aInvocation.InvocationReadBool("aStandby");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStandby(resp, aVersion, aStandby);
}

void DvProviderLinnCoUkProduct3::DoSourceCount(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaSourceCount(aInvocation, "aSourceCount");
    SourceCount(resp, aVersion, respaSourceCount);
}

void DvProviderLinnCoUkProduct3::DoSourceXml(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaSourceXml(aInvocation, "aSourceXml");
    SourceXml(resp, aVersion, respaSourceXml);
}

void DvProviderLinnCoUkProduct3::DoSourceIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaSourceIndex(aInvocation, "aSourceIndex");
    SourceIndex(resp, aVersion, respaSourceIndex);
}

void DvProviderLinnCoUkProduct3::DoSetSourceIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetSourceIndex(resp, aVersion, aSourceIndex);
}

void DvProviderLinnCoUkProduct3::DoSetSourceIndexByName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aSourceName;
    aInvocation.InvocationReadString("aSourceName", aSourceName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetSourceIndexByName(resp, aVersion, aSourceName);
}

void DvProviderLinnCoUkProduct3::DoSetStartupSourceIndexByName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aSourceName;
    aInvocation.InvocationReadString("aSourceName", aSourceName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStartupSourceIndexByName(resp, aVersion, aSourceName);
}

void DvProviderLinnCoUkProduct3::DoStartupSourceIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaSourceIndex(aInvocation, "aSourceIndex");
    StartupSourceIndex(resp, aVersion, respaSourceIndex);
}

void DvProviderLinnCoUkProduct3::DoSetStartupSourceIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStartupSourceIndex(resp, aVersion, aSourceIndex);
}

void DvProviderLinnCoUkProduct3::DoStartupSourceEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaStartupSourceEnabled(aInvocation, "aStartupSourceEnabled");
    StartupSourceEnabled(resp, aVersion, respaStartupSourceEnabled);
}

void DvProviderLinnCoUkProduct3::DoSetStartupSourceEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aStartupSourceEnabled = aInvocation.InvocationReadBool("aStartupSourceEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStartupSourceEnabled(resp, aVersion, aStartupSourceEnabled);
}

void DvProviderLinnCoUkProduct3::DoSourceSystemName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaSourceName(aInvocation, "aSourceName");
    SourceSystemName(resp, aVersion, aSourceIndex, respaSourceName);
}

void DvProviderLinnCoUkProduct3::DoSourceName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaSourceName(aInvocation, "aSourceName");
    SourceName(resp, aVersion, aSourceIndex, respaSourceName);
}

void DvProviderLinnCoUkProduct3::DoSetSourceName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    Brhz aSourceName;
    aInvocation.InvocationReadString("aSourceName", aSourceName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetSourceName(resp, aVersion, aSourceIndex, aSourceName);
}

void DvProviderLinnCoUkProduct3::DoSourceType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaSourceType(aInvocation, "aSourceType");
    SourceType(resp, aVersion, aSourceIndex, respaSourceType);
}

void DvProviderLinnCoUkProduct3::DoSourceVisible(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaSourceVisible(aInvocation, "aSourceVisible");
    SourceVisible(resp, aVersion, aSourceIndex, respaSourceVisible);
}

void DvProviderLinnCoUkProduct3::DoSetSourceVisible(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    TBool aSourceVisible = aInvocation.InvocationReadBool("aSourceVisible");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetSourceVisible(resp, aVersion, aSourceIndex, aSourceVisible);
}

void DvProviderLinnCoUkProduct3::Type(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaType*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::Model(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaModel*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::Name(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SetName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::Room(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaRoom*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SetRoom(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaRoom*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::Standby(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaStandby*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SetStandby(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaStandby*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SourceCount(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaSourceCount*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SourceXml(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaSourceXml*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SourceIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SetSourceIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SetSourceIndexByName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaSourceName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SetStartupSourceIndexByName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaSourceName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::StartupSourceIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SetStartupSourceIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::StartupSourceEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaStartupSourceEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SetStartupSourceEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaStartupSourceEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SourceSystemName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/, IInvocationResponseString& /*aaSourceName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SourceName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/, IInvocationResponseString& /*aaSourceName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SetSourceName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/, const Brx& /*aaSourceName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SourceType(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/, IInvocationResponseString& /*aaSourceType*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SourceVisible(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/, IInvocationResponseBool& /*aaSourceVisible*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct3::SetSourceVisible(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/, TBool /*aaSourceVisible*/)
{
    ASSERTS();
}

