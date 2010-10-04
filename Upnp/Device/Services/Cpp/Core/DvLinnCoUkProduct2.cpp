#include <Core/DvLinnCoUkProduct2.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkProduct2::SetPropertyProductName(const Brx& aValue)
{
    SetPropertyString(*iPropertyProductName, aValue);
}

void DvServiceLinnCoUkProduct2::GetPropertyProductName(Brhz& aValue)
{
    aValue.Set(iPropertyProductName->Value());
}

void DvServiceLinnCoUkProduct2::SetPropertyProductRoom(const Brx& aValue)
{
    SetPropertyString(*iPropertyProductRoom, aValue);
}

void DvServiceLinnCoUkProduct2::GetPropertyProductRoom(Brhz& aValue)
{
    aValue.Set(iPropertyProductRoom->Value());
}

void DvServiceLinnCoUkProduct2::SetPropertyProductStandby(TBool aValue)
{
    SetPropertyBool(*iPropertyProductStandby, aValue);
}

void DvServiceLinnCoUkProduct2::GetPropertyProductStandby(TBool& aValue)
{
    aValue = iPropertyProductStandby->Value();
}

void DvServiceLinnCoUkProduct2::SetPropertyProductSourceIndex(TUint aValue)
{
    SetPropertyUint(*iPropertyProductSourceIndex, aValue);
}

void DvServiceLinnCoUkProduct2::GetPropertyProductSourceIndex(TUint& aValue)
{
    aValue = iPropertyProductSourceIndex->Value();
}

DvServiceLinnCoUkProduct2::DvServiceLinnCoUkProduct2(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Product", 2)
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

void DvServiceLinnCoUkProduct2::EnableActionType()
{
    Zapp::Action* action = new Zapp::Action("Type");
    action->AddOutputParameter(new ParameterString("aType"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoType);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::EnableActionModel()
{
    Zapp::Action* action = new Zapp::Action("Model");
    action->AddOutputParameter(new ParameterString("aModel"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoModel);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::EnableActionName()
{
    Zapp::Action* action = new Zapp::Action("Name");
    action->AddOutputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::EnableActionSetName()
{
    Zapp::Action* action = new Zapp::Action("SetName");
    action->AddInputParameter(new ParameterRelated("aName", *iPropertyProductName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoSetName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::EnableActionRoom()
{
    Zapp::Action* action = new Zapp::Action("Room");
    action->AddOutputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoRoom);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::EnableActionSetRoom()
{
    Zapp::Action* action = new Zapp::Action("SetRoom");
    action->AddInputParameter(new ParameterRelated("aRoom", *iPropertyProductRoom));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoSetRoom);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::EnableActionStandby()
{
    Zapp::Action* action = new Zapp::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoStandby);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::EnableActionSetStandby()
{
    Zapp::Action* action = new Zapp::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("aStandby", *iPropertyProductStandby));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::EnableActionSourceCount()
{
    Zapp::Action* action = new Zapp::Action("SourceCount");
    action->AddOutputParameter(new ParameterRelated("aSourceCount", *iPropertyProductSourceIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoSourceCount);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::EnableActionSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("SourceIndex");
    action->AddOutputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoSourceIndex);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::EnableActionSetSourceIndex()
{
    Zapp::Action* action = new Zapp::Action("SetSourceIndex");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoSetSourceIndex);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::EnableActionSourceType()
{
    Zapp::Action* action = new Zapp::Action("SourceType");
    action->AddInputParameter(new ParameterRelated("aSourceIndex", *iPropertyProductSourceIndex));
    action->AddOutputParameter(new ParameterString("aSourceType"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct2::DoSourceType);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct2::DoType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaType(aInvocation, "aType");
    Type(resp, aVersion, respaType);
}

void DvServiceLinnCoUkProduct2::DoModel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaModel(aInvocation, "aModel");
    Model(resp, aVersion, respaModel);
}

void DvServiceLinnCoUkProduct2::DoName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaName(aInvocation, "aName");
    Name(resp, aVersion, respaName);
}

void DvServiceLinnCoUkProduct2::DoSetName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aName;
    aInvocation.InvocationReadString("aName", aName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetName(resp, aVersion, aName);
}

void DvServiceLinnCoUkProduct2::DoRoom(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaRoom(aInvocation, "aRoom");
    Room(resp, aVersion, respaRoom);
}

void DvServiceLinnCoUkProduct2::DoSetRoom(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aRoom;
    aInvocation.InvocationReadString("aRoom", aRoom);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRoom(resp, aVersion, aRoom);
}

void DvServiceLinnCoUkProduct2::DoStandby(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaStandby(aInvocation, "aStandby");
    Standby(resp, aVersion, respaStandby);
}

void DvServiceLinnCoUkProduct2::DoSetStandby(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aStandby = aInvocation.InvocationReadBool("aStandby");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStandby(resp, aVersion, aStandby);
}

void DvServiceLinnCoUkProduct2::DoSourceCount(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaSourceCount(aInvocation, "aSourceCount");
    SourceCount(resp, aVersion, respaSourceCount);
}

void DvServiceLinnCoUkProduct2::DoSourceIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaSourceIndex(aInvocation, "aSourceIndex");
    SourceIndex(resp, aVersion, respaSourceIndex);
}

void DvServiceLinnCoUkProduct2::DoSetSourceIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetSourceIndex(resp, aVersion, aSourceIndex);
}

void DvServiceLinnCoUkProduct2::DoSourceType(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSourceIndex = aInvocation.InvocationReadUint("aSourceIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaSourceType(aInvocation, "aSourceType");
    SourceType(resp, aVersion, aSourceIndex, respaSourceType);
}

void DvServiceLinnCoUkProduct2::Type(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaType*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct2::Model(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaModel*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct2::Name(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct2::SetName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct2::Room(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaRoom*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct2::SetRoom(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaRoom*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct2::Standby(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaStandby*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct2::SetStandby(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaStandby*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct2::SourceCount(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaSourceCount*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct2::SourceIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct2::SetSourceIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct2::SourceType(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSourceIndex*/, IInvocationResponseString& /*aaSourceType*/)
{
    ASSERTS();
}

