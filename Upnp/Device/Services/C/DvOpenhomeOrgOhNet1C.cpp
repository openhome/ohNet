#include "DvOpenhomeOrgOhNet1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderOpenhomeOrgOhNet1C : public DvProvider
{
public:
    DvProviderOpenhomeOrgOhNet1C(DvDeviceC aDevice);
    void EnableActionGetWebSocketPort(CallbackOhNet1GetWebSocketPort aCallback, void* aPtr);
private:
    void DoGetWebSocketPort(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackOhNet1GetWebSocketPort iCallbackGetWebSocketPort;
    void* iPtrGetWebSocketPort;
};

DvProviderOpenhomeOrgOhNet1C::DvProviderOpenhomeOrgOhNet1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "openhome.org", "OhNet", 1)
{
    
}

void DvProviderOpenhomeOrgOhNet1C::EnableActionGetWebSocketPort(CallbackOhNet1GetWebSocketPort aCallback, void* aPtr)
{
    iCallbackGetWebSocketPort = aCallback;
    iPtrGetWebSocketPort = aPtr;
    Zapp::Action* action = new Zapp::Action("GetWebSocketPort");
    action->AddOutputParameter(new ParameterUint("Port"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgOhNet1C::DoGetWebSocketPort);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgOhNet1C::DoGetWebSocketPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Port;
    ASSERT(iCallbackGetWebSocketPort != NULL);
    if (0 != iCallbackGetWebSocketPort(iPtrGetWebSocketPort, aVersion, &Port)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respPort(aInvocation, "Port");
    resp.Start();
    respPort.Write(Port);
    resp.End();
}



THandle DvProviderOpenhomeOrgOhNet1Create(DvDeviceC aDevice)
{
	return new DvProviderOpenhomeOrgOhNet1C(aDevice);
}

void DvProviderOpenhomeOrgOhNet1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderOpenhomeOrgOhNet1C*>(aProvider);
}

void DvProviderOpenhomeOrgOhNet1EnableActionGetWebSocketPort(THandle aProvider, CallbackOhNet1GetWebSocketPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgOhNet1C*>(aProvider)->EnableActionGetWebSocketPort(aCallback, aPtr);
}

