#include "DvUpnpOrgSwitchPower1.h"
#include <OhNetTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgSwitchPower1Cpp::SetPropertyStatus(bool aValue)
{
    return SetPropertyBool(*iPropertyStatus, aValue);
}

void DvProviderUpnpOrgSwitchPower1Cpp::GetPropertyStatus(bool& aValue)
{
    aValue = iPropertyStatus->Value();
}

DvProviderUpnpOrgSwitchPower1Cpp::DvProviderUpnpOrgSwitchPower1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "SwitchPower", 1)
{
    
    iPropertyStatus = new PropertyBool(new ParameterBool("Status"));
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

void DvProviderUpnpOrgSwitchPower1Cpp::DoSetTarget(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    bool newTargetValue = aInvocation.InvocationReadBool("newTargetValue");
    aInvocation.InvocationReadEnd();
    SetTarget(aVersion, newTargetValue);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgSwitchPower1Cpp::DoGetTarget(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respRetTargetValue;
    GetTarget(aVersion, respRetTargetValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterRetTargetValue(aInvocation, "RetTargetValue");
    respWriterRetTargetValue.Write(respRetTargetValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgSwitchPower1Cpp::DoGetStatus(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respResultStatus;
    GetStatus(aVersion, respResultStatus);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterResultStatus(aInvocation, "ResultStatus");
    respWriterResultStatus.Write(respResultStatus);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgSwitchPower1Cpp::SetTarget(uint32_t /*aVersion*/, bool /*anewTargetValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgSwitchPower1Cpp::GetTarget(uint32_t /*aVersion*/, bool& /*aRetTargetValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgSwitchPower1Cpp::GetStatus(uint32_t /*aVersion*/, bool& /*aResultStatus*/)
{
    ASSERTS();
}

