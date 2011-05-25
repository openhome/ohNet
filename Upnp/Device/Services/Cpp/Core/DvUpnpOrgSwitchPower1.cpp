#include "DvUpnpOrgSwitchPower1.h"
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome::Net;

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
    
    iPropertyStatus = new PropertyBool(new ParameterBool("Status"));
    iService->AddProperty(iPropertyStatus); // passes ownership
}

void DvProviderUpnpOrgSwitchPower1::EnableActionSetTarget()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetTarget");
    action->AddInputParameter(new ParameterBool("newTargetValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1::DoSetTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1::EnableActionGetTarget()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTarget");
    action->AddOutputParameter(new ParameterBool("RetTargetValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1::DoGetTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1::EnableActionGetStatus()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStatus");
    action->AddOutputParameter(new ParameterRelated("ResultStatus", *iPropertyStatus));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1::DoGetStatus);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1::DoSetTarget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool newTargetValue = aInvocation.InvocationReadBool("newTargetValue");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetTarget(resp, aVersion, newTargetValue);
}

void DvProviderUpnpOrgSwitchPower1::DoGetTarget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respRetTargetValue(aInvocation, "RetTargetValue");
    GetTarget(resp, aVersion, respRetTargetValue);
}

void DvProviderUpnpOrgSwitchPower1::DoGetStatus(IDviInvocation& aInvocation, TUint aVersion)
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

