#include "DvOpenhomeOrgOhNet1.h"
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

DvProviderOpenhomeOrgOhNet1Cpp::DvProviderOpenhomeOrgOhNet1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "OhNet", 1)
{
    
}

void DvProviderOpenhomeOrgOhNet1Cpp::EnableActionGetWebSocketPort()
{
    Zapp::Action* action = new Zapp::Action("GetWebSocketPort");
    action->AddOutputParameter(new ParameterUint("Port"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgOhNet1Cpp::DoGetWebSocketPort);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgOhNet1Cpp::DoGetWebSocketPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respPort;
    GetWebSocketPort(aVersion, respPort);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterPort(aInvocation, "Port");
    respWriterPort.Write(respPort);
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgOhNet1Cpp::GetWebSocketPort(uint32_t /*aVersion*/, uint32_t& /*aPort*/)
{
    ASSERTS();
}

