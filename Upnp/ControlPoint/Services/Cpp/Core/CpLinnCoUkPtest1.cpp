#include <Core/CpLinnCoUkPtest1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncTestComPortLinnCoUkPtest1 : public SyncProxyAction
{
public:
    SyncTestComPortLinnCoUkPtest1(CpProxyLinnCoUkPtest1& aService, TBool& aaResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPtest1& iService;
    TBool& iaResult;
};

SyncTestComPortLinnCoUkPtest1::SyncTestComPortLinnCoUkPtest1(CpProxyLinnCoUkPtest1& aService, TBool& aaResult)
    : iService(aService)
    , iaResult(aaResult)
{
}

void SyncTestComPortLinnCoUkPtest1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTestComPort(aAsync, iaResult);
}


class SyncLedsOnLinnCoUkPtest1 : public SyncProxyAction
{
public:
    SyncLedsOnLinnCoUkPtest1(CpProxyLinnCoUkPtest1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPtest1& iService;
};

SyncLedsOnLinnCoUkPtest1::SyncLedsOnLinnCoUkPtest1(CpProxyLinnCoUkPtest1& aService)
    : iService(aService)
{
}

void SyncLedsOnLinnCoUkPtest1::CompleteRequest(IAsync& aAsync)
{
    iService.EndLedsOn(aAsync);
}


class SyncLedsOffLinnCoUkPtest1 : public SyncProxyAction
{
public:
    SyncLedsOffLinnCoUkPtest1(CpProxyLinnCoUkPtest1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPtest1& iService;
};

SyncLedsOffLinnCoUkPtest1::SyncLedsOffLinnCoUkPtest1(CpProxyLinnCoUkPtest1& aService)
    : iService(aService)
{
}

void SyncLedsOffLinnCoUkPtest1::CompleteRequest(IAsync& aAsync)
{
    iService.EndLedsOff(aAsync);
}


CpProxyLinnCoUkPtest1::CpProxyLinnCoUkPtest1(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Ptest", 1, aDevice.Device());
    Zapp::Parameter* param;

    iActionTestComPort = new Action("TestComPort");
    param = new Zapp::ParameterUint("aPort");
    iActionTestComPort->AddInputParameter(param);
    param = new Zapp::ParameterBool("aResult");
    iActionTestComPort->AddOutputParameter(param);

    iActionLedsOn = new Action("LedsOn");

    iActionLedsOff = new Action("LedsOff");
}

CpProxyLinnCoUkPtest1::~CpProxyLinnCoUkPtest1()
{
    delete iService;
    delete iActionTestComPort;
    delete iActionLedsOn;
    delete iActionLedsOff;
}

void CpProxyLinnCoUkPtest1::SyncTestComPort(TUint aaPort, TBool& aaResult)
{
    SyncTestComPortLinnCoUkPtest1 sync(*this, aaResult);
    BeginTestComPort(aaPort, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPtest1::BeginTestComPort(TUint aaPort, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTestComPort, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionTestComPort->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaPort));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTestComPort->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPtest1::EndTestComPort(IAsync& aAsync, TBool& aaResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TestComPort"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaResult = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPtest1::SyncLedsOn()
{
    SyncLedsOnLinnCoUkPtest1 sync(*this);
    BeginLedsOn(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPtest1::BeginLedsOn(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionLedsOn, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkPtest1::EndLedsOn(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("LedsOn"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPtest1::SyncLedsOff()
{
    SyncLedsOffLinnCoUkPtest1 sync(*this);
    BeginLedsOff(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPtest1::BeginLedsOff(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionLedsOff, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkPtest1::EndLedsOff(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("LedsOff"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

