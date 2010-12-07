#include <Core/DvLinnCoUkProduct1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkProduct1::SetPropertyRoom(const Brx& aValue)
{
    return SetPropertyString(*iPropertyRoom, aValue);
}

void DvProviderLinnCoUkProduct1::GetPropertyRoom(Brhz& aValue)
{
    aValue.Set(iPropertyRoom->Value());
}

TBool DvProviderLinnCoUkProduct1::SetPropertyStandby(TBool aValue)
{
    return SetPropertyBool(*iPropertyStandby, aValue);
}

void DvProviderLinnCoUkProduct1::GetPropertyStandby(TBool& aValue)
{
    aValue = iPropertyStandby->Value();
}

DvProviderLinnCoUkProduct1::DvProviderLinnCoUkProduct1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Product", 1)
{
    
    iPropertyRoom = new PropertyString(new ParameterString("Room"));
    iService->AddProperty(iPropertyRoom); // passes ownership
    iPropertyStandby = new PropertyBool(new ParameterBool("Standby"));
    iService->AddProperty(iPropertyStandby); // passes ownership
}

void DvProviderLinnCoUkProduct1::EnableActionRoom()
{
    Zapp::Action* action = new Zapp::Action("Room");
    action->AddOutputParameter(new ParameterRelated("aRoom", *iPropertyRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1::DoRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1::EnableActionSetRoom()
{
    Zapp::Action* action = new Zapp::Action("SetRoom");
    action->AddInputParameter(new ParameterRelated("aRoom", *iPropertyRoom));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1::DoSetRoom);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1::EnableActionStandby()
{
    Zapp::Action* action = new Zapp::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("aStandby", *iPropertyStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1::DoStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1::EnableActionSetStandby()
{
    Zapp::Action* action = new Zapp::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("aStandby", *iPropertyStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProduct1::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProduct1::DoRoom(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaRoom(aInvocation, "aRoom");
    Room(resp, aVersion, respaRoom);
}

void DvProviderLinnCoUkProduct1::DoSetRoom(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aRoom;
    aInvocation.InvocationReadString("aRoom", aRoom);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRoom(resp, aVersion, aRoom);
}

void DvProviderLinnCoUkProduct1::DoStandby(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaStandby(aInvocation, "aStandby");
    Standby(resp, aVersion, respaStandby);
}

void DvProviderLinnCoUkProduct1::DoSetStandby(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aStandby = aInvocation.InvocationReadBool("aStandby");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStandby(resp, aVersion, aStandby);
}

void DvProviderLinnCoUkProduct1::Room(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaRoom*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct1::SetRoom(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaRoom*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct1::Standby(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaStandby*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkProduct1::SetStandby(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaStandby*/)
{
    ASSERTS();
}

