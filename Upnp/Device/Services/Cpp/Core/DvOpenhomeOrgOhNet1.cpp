#include "DvOpenhomeOrgOhNet1.h"
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

DvProviderOpenhomeOrgOhNet1::DvProviderOpenhomeOrgOhNet1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "OhNet", 1)
{
    
}

void DvProviderOpenhomeOrgOhNet1::EnableActionGetWebSocketPort()
{
    Zapp::Action* action = new Zapp::Action("GetWebSocketPort");
    action->AddOutputParameter(new ParameterUint("Port"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgOhNet1::DoGetWebSocketPort);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgOhNet1::DoGetWebSocketPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respPort(aInvocation, "Port");
    GetWebSocketPort(resp, aVersion, respPort);
}

void DvProviderOpenhomeOrgOhNet1::GetWebSocketPort(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aPort*/)
{
    ASSERTS();
}

