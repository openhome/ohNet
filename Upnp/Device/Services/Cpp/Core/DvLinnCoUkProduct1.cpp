#include <Core/DvLinnCoUkProduct1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkProduct1::SetPropertyRoom(const Brx& aValue)
{
    SetPropertyString(*iPropertyRoom, aValue);
}

void DvServiceLinnCoUkProduct1::GetPropertyRoom(Brhz& aValue)
{
    aValue.Set(iPropertyRoom->Value());
}

void DvServiceLinnCoUkProduct1::SetPropertyStandby(TBool aValue)
{
    SetPropertyBool(*iPropertyStandby, aValue);
}

void DvServiceLinnCoUkProduct1::GetPropertyStandby(TBool& aValue)
{
    aValue = iPropertyStandby->Value();
}

DvServiceLinnCoUkProduct1::DvServiceLinnCoUkProduct1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Product", 1)
{
    Functor empty;
    iPropertyRoom = new PropertyString(new ParameterString("Room"), empty);
    iService->AddProperty(iPropertyRoom); // passes ownership
    iPropertyStandby = new PropertyBool(new ParameterBool("Standby"), empty);
    iService->AddProperty(iPropertyStandby); // passes ownership
}

void DvServiceLinnCoUkProduct1::EnableActionRoom()
{
    Zapp::Action* action = new Zapp::Action("Room");
    action->AddOutputParameter(new ParameterRelated("aRoom", *iPropertyRoom));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct1::DoRoom);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct1::EnableActionSetRoom()
{
    Zapp::Action* action = new Zapp::Action("SetRoom");
    action->AddInputParameter(new ParameterRelated("aRoom", *iPropertyRoom));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct1::DoSetRoom);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct1::EnableActionStandby()
{
    Zapp::Action* action = new Zapp::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("aStandby", *iPropertyStandby));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct1::DoStandby);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct1::EnableActionSetStandby()
{
    Zapp::Action* action = new Zapp::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("aStandby", *iPropertyStandby));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkProduct1::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkProduct1::DoRoom(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaRoom(aInvocation, "aRoom");
    Room(resp, aVersion, respaRoom);
}

void DvServiceLinnCoUkProduct1::DoSetRoom(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aRoom;
    aInvocation.InvocationReadString("aRoom", aRoom);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRoom(resp, aVersion, aRoom);
}

void DvServiceLinnCoUkProduct1::DoStandby(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaStandby(aInvocation, "aStandby");
    Standby(resp, aVersion, respaStandby);
}

void DvServiceLinnCoUkProduct1::DoSetStandby(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aStandby = aInvocation.InvocationReadBool("aStandby");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStandby(resp, aVersion, aStandby);
}

void DvServiceLinnCoUkProduct1::Room(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaRoom*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct1::SetRoom(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaRoom*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct1::Standby(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaStandby*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkProduct1::SetStandby(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaStandby*/)
{
    ASSERTS();
}

