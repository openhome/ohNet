#include "CpOpenhomeOrgOhNet1.h"
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncGetWebSocketPortOpenhomeOrgOhNet1Cpp : public SyncProxyAction
{
public:
    SyncGetWebSocketPortOpenhomeOrgOhNet1Cpp(CpProxyOpenhomeOrgOhNet1Cpp& aProxy, uint32_t& aPort);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgOhNet1Cpp& iService;
    uint32_t& iPort;
};

SyncGetWebSocketPortOpenhomeOrgOhNet1Cpp::SyncGetWebSocketPortOpenhomeOrgOhNet1Cpp(CpProxyOpenhomeOrgOhNet1Cpp& aProxy, uint32_t& aPort)
    : iService(aProxy)
    , iPort(aPort)
{
}

void SyncGetWebSocketPortOpenhomeOrgOhNet1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetWebSocketPort(aAsync, iPort);
}


CpProxyOpenhomeOrgOhNet1Cpp::CpProxyOpenhomeOrgOhNet1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("openhome-org", "OhNet", 1, aDevice.Device())
{
    Zapp::Parameter* param;

    iActionGetWebSocketPort = new Action("GetWebSocketPort");
    param = new Zapp::ParameterUint("Port");
    iActionGetWebSocketPort->AddOutputParameter(param);
}

CpProxyOpenhomeOrgOhNet1Cpp::~CpProxyOpenhomeOrgOhNet1Cpp()
{
    DestroyService();
    delete iActionGetWebSocketPort;
}

void CpProxyOpenhomeOrgOhNet1Cpp::SyncGetWebSocketPort(uint32_t& aPort)
{
    SyncGetWebSocketPortOpenhomeOrgOhNet1Cpp sync(*this, aPort);
    BeginGetWebSocketPort(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgOhNet1Cpp::BeginGetWebSocketPort(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetWebSocketPort, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetWebSocketPort->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgOhNet1Cpp::EndGetWebSocketPort(IAsync& aAsync, uint32_t& aPort)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetWebSocketPort"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aPort = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

