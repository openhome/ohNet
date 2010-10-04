#include <Std/CpLinnCoUkPtest1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncTestComPortLinnCoUkPtest1Cpp : public SyncProxyAction
{
public:
    SyncTestComPortLinnCoUkPtest1Cpp(CpProxyLinnCoUkPtest1Cpp& aService, bool& aaResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPtest1Cpp& iService;
    bool& iaResult;
};

SyncTestComPortLinnCoUkPtest1Cpp::SyncTestComPortLinnCoUkPtest1Cpp(CpProxyLinnCoUkPtest1Cpp& aService, bool& aaResult)
    : iService(aService)
    , iaResult(aaResult)
{
}

void SyncTestComPortLinnCoUkPtest1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTestComPort(aAsync, iaResult);
}


class SyncLedsOnLinnCoUkPtest1Cpp : public SyncProxyAction
{
public:
    SyncLedsOnLinnCoUkPtest1Cpp(CpProxyLinnCoUkPtest1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPtest1Cpp& iService;
};

SyncLedsOnLinnCoUkPtest1Cpp::SyncLedsOnLinnCoUkPtest1Cpp(CpProxyLinnCoUkPtest1Cpp& aService)
    : iService(aService)
{
}

void SyncLedsOnLinnCoUkPtest1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndLedsOn(aAsync);
}


class SyncLedsOffLinnCoUkPtest1Cpp : public SyncProxyAction
{
public:
    SyncLedsOffLinnCoUkPtest1Cpp(CpProxyLinnCoUkPtest1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPtest1Cpp& iService;
};

SyncLedsOffLinnCoUkPtest1Cpp::SyncLedsOffLinnCoUkPtest1Cpp(CpProxyLinnCoUkPtest1Cpp& aService)
    : iService(aService)
{
}

void SyncLedsOffLinnCoUkPtest1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndLedsOff(aAsync);
}


CpProxyLinnCoUkPtest1Cpp::CpProxyLinnCoUkPtest1Cpp(CpDeviceCpp& aDevice)
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

CpProxyLinnCoUkPtest1Cpp::~CpProxyLinnCoUkPtest1Cpp()
{
    delete iService;
    delete iActionTestComPort;
    delete iActionLedsOn;
    delete iActionLedsOff;
}

void CpProxyLinnCoUkPtest1Cpp::SyncTestComPort(uint32_t aaPort, bool& aaResult)
{
    SyncTestComPortLinnCoUkPtest1Cpp sync(*this, aaResult);
    BeginTestComPort(aaPort, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPtest1Cpp::BeginTestComPort(uint32_t aaPort, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkPtest1Cpp::EndTestComPort(IAsync& aAsync, bool& aaResult)
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

void CpProxyLinnCoUkPtest1Cpp::SyncLedsOn()
{
    SyncLedsOnLinnCoUkPtest1Cpp sync(*this);
    BeginLedsOn(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPtest1Cpp::BeginLedsOn(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionLedsOn, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkPtest1Cpp::EndLedsOn(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("LedsOn"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPtest1Cpp::SyncLedsOff()
{
    SyncLedsOffLinnCoUkPtest1Cpp sync(*this);
    BeginLedsOff(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPtest1Cpp::BeginLedsOff(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionLedsOff, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkPtest1Cpp::EndLedsOff(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("LedsOff"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

