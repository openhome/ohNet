#include "DvUpnpOrgSwitchPower1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgSwitchPower1Cpp::SetPropertyStatus(bool aValue)
{
    ASSERT(iPropertyStatus != NULL);
    return SetPropertyBool(*iPropertyStatus, aValue);
}

void DvProviderUpnpOrgSwitchPower1Cpp::GetPropertyStatus(bool& aValue)
{
    ASSERT(iPropertyStatus != NULL);
    aValue = iPropertyStatus->Value();
}

DvProviderUpnpOrgSwitchPower1Cpp::DvProviderUpnpOrgSwitchPower1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "SwitchPower", 1)
{
    iPropertyStatus = NULL;
}

void DvProviderUpnpOrgSwitchPower1Cpp::EnablePropertyStatus()
{
    iPropertyStatus = new PropertyBool(iDvStack.Env(), new ParameterBool("Status"));
    iService->AddProperty(iPropertyStatus); // passes ownership
}

void DvProviderUpnpOrgSwitchPower1Cpp::EnableActionSetTarget()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetTarget");
    action->AddInputParameter(new ParameterBool("newTargetValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1Cpp::DoSetTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1Cpp::EnableActionGetTarget()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTarget");
    action->AddOutputParameter(new ParameterBool("RetTargetValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1Cpp::DoGetTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1Cpp::EnableActionGetStatus()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStatus");
    action->AddOutputParameter(new ParameterRelated("ResultStatus", *iPropertyStatus));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1Cpp::DoGetStatus);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1Cpp::DoSetTarget(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    bool newTargetValue = aInvocation.InvocationReadBool("newTargetValue");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetTarget(invocation, newTargetValue);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgSwitchPower1Cpp::DoGetTarget(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respRetTargetValue;
    DvInvocationStd invocation(aInvocation);
    GetTarget(invocation, respRetTargetValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterRetTargetValue(aInvocation, "RetTargetValue");
    respWriterRetTargetValue.Write(respRetTargetValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgSwitchPower1Cpp::DoGetStatus(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respResultStatus;
    DvInvocationStd invocation(aInvocation);
    GetStatus(invocation, respResultStatus);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterResultStatus(aInvocation, "ResultStatus");
    respWriterResultStatus.Write(respResultStatus);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgSwitchPower1Cpp::SetTarget(IDvInvocationStd& /*aInvocation*/, bool /*anewTargetValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgSwitchPower1Cpp::GetTarget(IDvInvocationStd& /*aInvocation*/, bool& /*aRetTargetValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgSwitchPower1Cpp::GetStatus(IDvInvocationStd& /*aInvocation*/, bool& /*aResultStatus*/)
{
    ASSERTS();
}

