#include <Core/DvUpnpOrgSwitchPower1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

TBool DvProviderUpnpOrgSwitchPower1::SetPropertyStatus(TBool aValue)
{
    return SetPropertyBool(*iPropertyStatus, aValue);
}

void DvProviderUpnpOrgSwitchPower1::GetPropertyStatus(TBool& aValue)
{
    aValue = iPropertyStatus->Value();
}

DvProviderUpnpOrgSwitchPower1::DvProviderUpnpOrgSwitchPower1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "SwitchPower", 1)
{
    Functor empty;
    iPropertyStatus = new PropertyBool(new ParameterBool("Status"), empty);
    iService->AddProperty(iPropertyStatus); // passes ownership
}

void DvProviderUpnpOrgSwitchPower1::EnableActionSetTarget()
{
    Zapp::Action* action = new Zapp::Action("SetTarget");
    action->AddInputParameter(new ParameterBool("newTargetValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgSwitchPower1::DoSetTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1::EnableActionGetTarget()
{
    Zapp::Action* action = new Zapp::Action("GetTarget");
    action->AddOutputParameter(new ParameterBool("RetTargetValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgSwitchPower1::DoGetTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1::EnableActionGetStatus()
{
    Zapp::Action* action = new Zapp::Action("GetStatus");
    action->AddOutputParameter(new ParameterRelated("ResultStatus", *iPropertyStatus));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgSwitchPower1::DoGetStatus);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1::DoSetTarget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool newTargetValue = aInvocation.InvocationReadBool("newTargetValue");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetTarget(resp, aVersion, newTargetValue);
}

void DvProviderUpnpOrgSwitchPower1::DoGetTarget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respRetTargetValue(aInvocation, "RetTargetValue");
    GetTarget(resp, aVersion, respRetTargetValue);
}

void DvProviderUpnpOrgSwitchPower1::DoGetStatus(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respResultStatus(aInvocation, "ResultStatus");
    GetStatus(resp, aVersion, respResultStatus);
}

void DvProviderUpnpOrgSwitchPower1::SetTarget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*anewTargetValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgSwitchPower1::GetTarget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aRetTargetValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgSwitchPower1::GetStatus(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aResultStatus*/)
{
    ASSERTS();
}

