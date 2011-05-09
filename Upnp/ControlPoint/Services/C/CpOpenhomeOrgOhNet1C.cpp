#include "CpOpenhomeOrgOhNet1.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;

class CpProxyOpenhomeOrgOhNet1C : public CpProxyC
{
public:
    CpProxyOpenhomeOrgOhNet1C(CpDeviceC aDevice);
    ~CpProxyOpenhomeOrgOhNet1C();
    //CpProxyOpenhomeOrgOhNet1* Proxy() { return static_cast<CpProxyOpenhomeOrgOhNet1*>(iProxy); }

    void SyncGetWebSocketPort(TUint& aPort);
    void BeginGetWebSocketPort(FunctorAsync& aFunctor);
    void EndGetWebSocketPort(IAsync& aAsync, TUint& aPort);


private:
private:
    Mutex iLock;
    Action* iActionGetWebSocketPort;
};


class SyncGetWebSocketPortOpenhomeOrgOhNet1C : public SyncProxyAction
{
public:
    SyncGetWebSocketPortOpenhomeOrgOhNet1C(CpProxyOpenhomeOrgOhNet1C& aProxy, TUint& aPort);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgOhNet1C& iService;
    TUint& iPort;
};

SyncGetWebSocketPortOpenhomeOrgOhNet1C::SyncGetWebSocketPortOpenhomeOrgOhNet1C(CpProxyOpenhomeOrgOhNet1C& aProxy, TUint& aPort)
    : iService(aProxy)
    , iPort(aPort)
{
}

void SyncGetWebSocketPortOpenhomeOrgOhNet1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetWebSocketPort(aAsync, iPort);
}

CpProxyOpenhomeOrgOhNet1C::CpProxyOpenhomeOrgOhNet1C(CpDeviceC aDevice)
    : CpProxyC("openhome-org", "OhNet", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    Zapp::Parameter* param;

    iActionGetWebSocketPort = new Action("GetWebSocketPort");
    param = new Zapp::ParameterUint("Port");
    iActionGetWebSocketPort->AddOutputParameter(param);
}

CpProxyOpenhomeOrgOhNet1C::~CpProxyOpenhomeOrgOhNet1C()
{
    DestroyService();
    delete iActionGetWebSocketPort;
}

void CpProxyOpenhomeOrgOhNet1C::SyncGetWebSocketPort(TUint& aPort)
{
    SyncGetWebSocketPortOpenhomeOrgOhNet1C sync(*this, aPort);
    BeginGetWebSocketPort(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgOhNet1C::BeginGetWebSocketPort(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetWebSocketPort, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetWebSocketPort->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgOhNet1C::EndGetWebSocketPort(IAsync& aAsync, TUint& aPort)
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


THandle CpProxyOpenhomeOrgOhNet1Create(CpDeviceC aDevice)
{
    return new CpProxyOpenhomeOrgOhNet1C(aDevice);
}

void CpProxyOpenhomeOrgOhNet1Destroy(THandle aHandle)
{
    CpProxyOpenhomeOrgOhNet1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgOhNet1C*>(aHandle);
    delete proxyC;
}

void CpProxyOpenhomeOrgOhNet1SyncGetWebSocketPort(THandle aHandle, uint32_t* aPort)
{
    CpProxyOpenhomeOrgOhNet1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgOhNet1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetWebSocketPort(*aPort);
}

void CpProxyOpenhomeOrgOhNet1BeginGetWebSocketPort(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgOhNet1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgOhNet1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetWebSocketPort(functor);
}

int32_t CpProxyOpenhomeOrgOhNet1EndGetWebSocketPort(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aPort)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgOhNet1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgOhNet1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetWebSocketPort(*async, *aPort);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

