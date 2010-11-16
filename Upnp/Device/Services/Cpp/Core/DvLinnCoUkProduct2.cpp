#include <Core/DvLinnCoUkProduct2.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkProduct2::SetPropertyProductName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductName, aValue);
}

void DvProviderLinnCoUkProduct2::GetPropertyProductName(Brhz& aValue)
{
    aValue.Set(iPropertyProductName->Value());
}

TBool DvProviderLinnCoUkProduct2::SetPropertyProductRoom(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductRoom, aValue);
}

void DvProviderLinnCoUkProduct2::GetPropertyProductRoom(Brhz& aValue)
{
    aValue.Set(iPropertyProductRoom->Value());
}

TBool DvProviderLinnCoUkProduct2::SetPropertyProductStandby(TBool aValue)
{
    return SetPropertyBool(*iPropertyProductStandby, aValue);
}

void DvProviderLinnCoUkProduct2::GetPropertyProductStandby(TBool& aValue)
{
    aValue = iPropertyProductStandby->Value();
}

TBool DvProviderLinnCoUkProduct2::SetPropertyProductSourceIndex(TUint aValue)
{
    return SetPropertyUint(*iPropertyProductSourceIndex, aValue);
}

void DvProviderLinnCoUkProduct2::GetPropertyProductSourceIndex(TUint& aValue)
{
    aValue = iPropertyProductSourceIndex->Value();
}

DvProviderLinnCoUkProduct2::DvProviderLinnCoUkProduct2(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Product", 2)
{
    Functor empty;
    iPropertyProductName = new PropertyString(new ParameterString("ProductName"), empty);
    iService->AddProperty(iPropertyProductName); // passes ownership
    iPropertyProductRoom = new PropertyString(new ParameterString("ProductRoom"), empty);
    iService->AddProperty(iPropertyProductRoom); // passes ownership
    iPropertyProductStandby = new PropertyBool(new ParameterBool("ProductStandby"), empty);
    iService->AddProperty(iPropertyProductStandby); // passes ownership
    iPropertyProductSourceIndex = new PropertyUint(new ParameterUint("ProductSourceIndex"), empty);
    iService->AddProperty(iPropertyProductSourceIndex); // passes ownership
}

void DvProviderLinnCoUkProduct2::EnableActionType()
{
    Zapp::Action* action = new Zapp::Action("Type");
    action->AddOutputParameter(new ParameterString("aType"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::EnableActionModel()
{
    Zapp::Action* action = new Zapp::Action("Model");
    action->AddOutputParameter(new ParameterString("aModel"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoModel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::EnableActionName()
{
    Zapp::Action* action = new Zapp::Action("Name");
    action->AddOutputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::EnableActionSetName()
{
    Zapp::Action* action = new Zapp::Action("SetName");
    action->AddInputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoSetName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::EnableActionRoom()
{
    Zapp::Action* action = new Zapp::Action("Room");
    action->AddOutputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::EnableActionSetRoom()
{
    Zapp::Action* action = new Zapp::Action("SetRoom");
    action->AddInputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoSetRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::EnableActionStandby()
{
    Zapp::Action* action = new Zapp::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::EnableActionSetStandby()
{
    Zapp::Action* action = new Zapp::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::EnableActionSourceCount()
{
    Zapp::Action* action = new Zapp::Action("SourceCount");
    action->AddOutputParameter(new ParameterRelated("aSourceCount", *iPropertyProductSourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoSourceCount);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::EnableActionSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("SourceIndex");
    action->AddOutputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::EnableActionSetSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("SetSourceIndex");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoSetSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::EnableActionSourceType()
{
    Zapp::Action* action = new Zapp::Action("SourceType");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceType"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct2::DoSourceType);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct2::DoType(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaType(aInvocation, "aType");
    Type(resp, aVersion, respaType);
}

void DvProviderLinnCoUkProduct2::DoModel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaModel(aInvocation, "aModel");
    Model(resp, aVersion, respaModel);
}

void DvProviderLinnCoUkProduct2::DoName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaName(aInvocation, "aName");
    Name(resp, aVersion, respaName);
}

void DvProviderLinnCoUkProduct2::DoSetName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aName;
    aInvocation.InvocationReadString("aName", aName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetName(resp, aVersion, aName);
}

void DvProviderLinnCoUkProduct2::DoRoom(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaRoom(aInvocation, "aRoom");
    Room(resp, aVersion, respaRoom);
}

void DvProviderLinnCoUkProduct2::DoSetRoom(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aRoom;
    aInvocation.InvocationReadString("aRoom", aRoom);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRoom(resp, aVersion, aRoom);
}

void DvProviderLinnCoUkProduct2::DoStandby(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaStandby(aInvocation, "aStandby");
    Standby(resp, aVersion, respaStandby);
}

void DvProviderLinnCoUkProduct2::DoSetStandby(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aStandby = aInvocation.InvocationReadBool("aStandby");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStandby(resp, aVersion, aStandby);
}

void DvProviderLinnCoUkProduct2::DoSourceCount(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaSourceCount(aInvocation, "aSourceCount");
    SourceCount(resp, aVersion, respaSourceCount);
}

void DvProviderLinnCoUkProduct2::DoSourceIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaSourceIndex(aInvocation, "aSourceIndex");
    SourceIndex(resp, aVersion, respaSourceIndex);
}

void DvProviderLinnCoUkProduct2::DoSetSourceIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetSourceIndex(resp, aVersion, aSourceIndex);
}

void DvProviderLinnCoUkProduct2::DoSourceType(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaSourceType(aInvocation, "aSourceType");
    SourceType(resp, aVersion, aSourceIndex, respaSourceType);
}

void DvProviderLinnCoUkProduct2::Type(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaType*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct2::Model(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaModel*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct2::Name(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct2::SetName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct2::Room(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaRoom*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct2::SetRoom(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaRoom*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct2::Standby(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaStandby*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct2::SetStandby(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaStandby*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct2::SourceCount(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaSourceCount*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct2::SourceIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct2::SetSourceIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct2::SourceType(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/, IInvocationResponseString& /*aaSourceType*/)
{
    ASSERTS();
}

