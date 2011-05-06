#include "CpOpenhomeOrgOhNet1.h"
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncGetWebSocketPortOpenhomeOrgOhNet1 : public SyncProxyAction
{
public:
    SyncGetWebSocketPortOpenhomeOrgOhNet1(CpProxyOpenhomeOrgOhNet1& aProxy, TUint& aPort);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgOhNet1& iService;
    TUint& iPort;
};

SyncGetWebSocketPortOpenhomeOrgOhNet1::SyncGetWebSocketPortOpenhomeOrgOhNet1(CpProxyOpenhomeOrgOhNet1& aProxy, TUint& aPort)
    : iService(aProxy)
    , iPort(aPort)
{
}

void SyncGetWebSocketPortOpenhomeOrgOhNet1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetWebSocketPort(aAsync, iPort);
}


CpProxyOpenhomeOrgOhNet1::CpProxyOpenhomeOrgOhNet1(CpDevice& aDevice)
    : CpProxy("openhome-org", "OhNet", 1, aDevice.Device())
{
    Zapp::Parameter* param;

    iActionGetWebSocketPort = new Action("GetWebSocketPort");
    param = new Zapp::ParameterUint("Port");
    iActionGetWebSocketPort->AddOutputParameter(param);
}

CpProxyOpenhomeOrgOhNet1::~CpProxyOpenhomeOrgOhNet1()
{
    DestroyService();
    delete iActionGetWebSocketPort;
}

void CpProxyOpenhomeOrgOhNet1::SyncGetWebSocketPort(TUint& aPort)
{
    SyncGetWebSocketPortOpenhomeOrgOhNet1 sync(*this, aPort);
    BeginGetWebSocketPort(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgOhNet1::BeginGetWebSocketPort(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetWebSocketPort, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetWebSocketPort->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgOhNet1::EndGetWebSocketPort(IAsync& aAsync, TUint& aPort)
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

