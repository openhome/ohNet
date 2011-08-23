#include "DvUpnpOrgSwitchPower1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
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
    DviInvocationResponse resp(aInvocation);
    SetTarget(resp, aVersion, newTargetValue);
}

void DvProviderUpnpOrgSwitchPower1::DoGetTarget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseBool respRetTargetValue(aInvocation, "RetTargetValue");
    GetTarget(resp, aVersion, respRetTargetValue);
}

void DvProviderUpnpOrgSwitchPower1::DoGetStatus(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseBool respResultStatus(aInvocation, "ResultStatus");
    GetStatus(resp, aVersion, respResultStatus);
}

void DvProviderUpnpOrgSwitchPower1::SetTarget(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*anewTargetValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgSwitchPower1::GetTarget(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseBool& /*aRetTargetValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgSwitchPower1::GetStatus(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseBool& /*aResultStatus*/)
{
    ASSERTS();
}

