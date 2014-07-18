#include "DvUpnpOrgSwitchPower1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderUpnpOrgSwitchPower1::SetPropertyStatus(TBool aValue)
{
    ASSERT(iPropertyStatus != NULL);
    return SetPropertyBool(*iPropertyStatus, aValue);
}

void DvProviderUpnpOrgSwitchPower1::GetPropertyStatus(TBool& aValue)
{
    ASSERT(iPropertyStatus != NULL);
    aValue = iPropertyStatus->Value();
}

DvProviderUpnpOrgSwitchPower1::DvProviderUpnpOrgSwitchPower1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "SwitchPower", 1)
{
    Construct();
}

DvProviderUpnpOrgSwitchPower1::DvProviderUpnpOrgSwitchPower1(DviDevice& aDevice)
    : DvProvider(aDevice, "upnp.org", "SwitchPower", 1)
{
    Construct();
}

void DvProviderUpnpOrgSwitchPower1::Construct()
{
    iPropertyStatus = NULL;
}

void DvProviderUpnpOrgSwitchPower1::EnablePropertyStatus()
{
    iPropertyStatus = new PropertyBool(iDvStack.Env(), new ParameterBool("Status"));
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

void DvProviderUpnpOrgSwitchPower1::DoSetTarget(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TBool newTargetValue = aInvocation.InvocationReadBool("newTargetValue");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetTarget(invocation, newTargetValue);
}

void DvProviderUpnpOrgSwitchPower1::DoGetTarget(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respRetTargetValue(aInvocation, "RetTargetValue");
    GetTarget(invocation, respRetTargetValue);
}

void DvProviderUpnpOrgSwitchPower1::DoGetStatus(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respResultStatus(aInvocation, "ResultStatus");
    GetStatus(invocation, respResultStatus);
}

void DvProviderUpnpOrgSwitchPower1::SetTarget(IDvInvocation& /*aResponse*/, TBool /*anewTargetValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgSwitchPower1::GetTarget(IDvInvocation& /*aResponse*/, IDvInvocationResponseBool& /*aRetTargetValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgSwitchPower1::GetStatus(IDvInvocation& /*aResponse*/, IDvInvocationResponseBool& /*aResultStatus*/)
{
    ASSERTS();
}

