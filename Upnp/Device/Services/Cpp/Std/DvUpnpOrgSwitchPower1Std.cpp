#include <Std/DvUpnpOrgSwitchPower1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgSwitchPower1Cpp::SetPropertyStatus(bool aValue)
{
    SetPropertyBool(*iPropertyStatus, aValue);
}

void DvServiceUpnpOrgSwitchPower1Cpp::GetPropertyStatus(bool& aValue)
{
    aValue = iPropertyStatus->Value();
}

DvServiceUpnpOrgSwitchPower1Cpp::DvServiceUpnpOrgSwitchPower1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "SwitchPower", 1)
{
    Functor empty;
    iPropertyStatus = new PropertyBool(new ParameterBool("Status"), empty);
    iService->AddProperty(iPropertyStatus); // passes ownership
}

void DvServiceUpnpOrgSwitchPower1Cpp::EnableActionSetTarget()
{
    Zapp::Action* action = new Zapp::Action("SetTarget");
    action->AddInputParameter(new ParameterBool("newTargetValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgSwitchPower1Cpp::DoSetTarget);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgSwitchPower1Cpp::EnableActionGetTarget()
{
    Zapp::Action* action = new Zapp::Action("GetTarget");
    action->AddOutputParameter(new ParameterBool("RetTargetValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgSwitchPower1Cpp::DoGetTarget);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgSwitchPower1Cpp::EnableActionGetStatus()
{
    Zapp::Action* action = new Zapp::Action("GetStatus");
    action->AddOutputParameter(new ParameterRelated("ResultStatus", *iPropertyStatus));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgSwitchPower1Cpp::DoGetStatus);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgSwitchPower1Cpp::DoSetTarget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool newTargetValue = aInvocation.InvocationReadBool("newTargetValue");
    aInvocation.InvocationReadEnd();
    SetTarget(aVersion, newTargetValue);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgSwitchPower1Cpp::DoGetTarget(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgSwitchPower1Cpp::DoGetStatus(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgSwitchPower1Cpp::SetTarget(uint32_t /*aVersion*/, bool /*anewTargetValue*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgSwitchPower1Cpp::GetTarget(uint32_t /*aVersion*/, bool& /*aRetTargetValue*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgSwitchPower1Cpp::GetStatus(uint32_t /*aVersion*/, bool& /*aResultStatus*/)
{
    ASSERTS();
}

