#include <Core/DvUpnpOrgSwitchPower1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgSwitchPower1::SetPropertyStatus(TBool aValue)
{
    SetPropertyBool(*iPropertyStatus, aValue);
}

void DvServiceUpnpOrgSwitchPower1::GetPropertyStatus(TBool& aValue)
{
    aValue = iPropertyStatus->Value();
}

DvServiceUpnpOrgSwitchPower1::DvServiceUpnpOrgSwitchPower1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "SwitchPower", 1)
{
    Functor empty;
    iPropertyStatus = new PropertyBool(new ParameterBool("Status"), empty);
    iService->AddProperty(iPropertyStatus); // passes ownership
}

void DvServiceUpnpOrgSwitchPower1::EnableActionSetTarget()
{
    Zapp::Action* action = new Zapp::Action("SetTarget");
    action->AddInputParameter(new ParameterBool("newTargetValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgSwitchPower1::DoSetTarget);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgSwitchPower1::EnableActionGetTarget()
{
    Zapp::Action* action = new Zapp::Action("GetTarget");
    action->AddOutputParameter(new ParameterBool("RetTargetValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgSwitchPower1::DoGetTarget);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgSwitchPower1::EnableActionGetStatus()
{
    Zapp::Action* action = new Zapp::Action("GetStatus");
    action->AddOutputParameter(new ParameterRelated("ResultStatus", *iPropertyStatus));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgSwitchPower1::DoGetStatus);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgSwitchPower1::DoSetTarget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool newTargetValue = aInvocation.InvocationReadBool("newTargetValue");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetTarget(resp, aVersion, newTargetValue);
}

void DvServiceUpnpOrgSwitchPower1::DoGetTarget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respRetTargetValue(aInvocation, "RetTargetValue");
    GetTarget(resp, aVersion, respRetTargetValue);
}

void DvServiceUpnpOrgSwitchPower1::DoGetStatus(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respResultStatus(aInvocation, "ResultStatus");
    GetStatus(resp, aVersion, respResultStatus);
}

void DvServiceUpnpOrgSwitchPower1::SetTarget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*anewTargetValue*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgSwitchPower1::GetTarget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aRetTargetValue*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgSwitchPower1::GetStatus(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aResultStatus*/)
{
    ASSERTS();
}

