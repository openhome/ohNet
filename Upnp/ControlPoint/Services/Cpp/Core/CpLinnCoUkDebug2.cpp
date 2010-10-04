#include <Core/CpLinnCoUkDebug2.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncSetDebugLevelLinnCoUkDebug2 : public SyncProxyAction
{
public:
    SyncSetDebugLevelLinnCoUkDebug2(CpProxyLinnCoUkDebug2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDebug2& iService;
};

SyncSetDebugLevelLinnCoUkDebug2::SyncSetDebugLevelLinnCoUkDebug2(CpProxyLinnCoUkDebug2& aService)
    : iService(aService)
{
}

void SyncSetDebugLevelLinnCoUkDebug2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDebugLevel(aAsync);
}


class SyncDebugLevelLinnCoUkDebug2 : public SyncProxyAction
{
public:
    SyncDebugLevelLinnCoUkDebug2(CpProxyLinnCoUkDebug2& aService, TUint& aaDebugLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDebug2& iService;
    TUint& iaDebugLevel;
};

SyncDebugLevelLinnCoUkDebug2::SyncDebugLevelLinnCoUkDebug2(CpProxyLinnCoUkDebug2& aService, TUint& aaDebugLevel)
    : iService(aService)
    , iaDebugLevel(aaDebugLevel)
{
}

void SyncDebugLevelLinnCoUkDebug2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDebugLevel(aAsync, iaDebugLevel);
}


class SyncMemWriteLinnCoUkDebug2 : public SyncProxyAction
{
public:
    SyncMemWriteLinnCoUkDebug2(CpProxyLinnCoUkDebug2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDebug2& iService;
};

SyncMemWriteLinnCoUkDebug2::SyncMemWriteLinnCoUkDebug2(CpProxyLinnCoUkDebug2& aService)
    : iService(aService)
{
}

void SyncMemWriteLinnCoUkDebug2::CompleteRequest(IAsync& aAsync)
{
    iService.EndMemWrite(aAsync);
}


CpProxyLinnCoUkDebug2::CpProxyLinnCoUkDebug2(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Debug", 2, aDevice.Device());
    Zapp::Parameter* param;

    iActionSetDebugLevel = new Action("SetDebugLevel");
    param = new Zapp::ParameterUint("aDebugLevel");
    iActionSetDebugLevel->AddInputParameter(param);

    iActionDebugLevel = new Action("DebugLevel");
    param = new Zapp::ParameterUint("aDebugLevel");
    iActionDebugLevel->AddOutputParameter(param);

    iActionMemWrite = new Action("MemWrite");
    param = new Zapp::ParameterUint("aMemAddress");
    iActionMemWrite->AddInputParameter(param);
    param = new Zapp::ParameterBinary("aMemData");
    iActionMemWrite->AddInputParameter(param);
}

CpProxyLinnCoUkDebug2::~CpProxyLinnCoUkDebug2()
{
    delete iService;
    delete iActionSetDebugLevel;
    delete iActionDebugLevel;
    delete iActionMemWrite;
}

void CpProxyLinnCoUkDebug2::SyncSetDebugLevel(TUint aaDebugLevel)
{
    SyncSetDebugLevelLinnCoUkDebug2 sync(*this);
    BeginSetDebugLevel(aaDebugLevel, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDebug2::BeginSetDebugLevel(TUint aaDebugLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDebugLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDebugLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaDebugLevel));
    invocation->Invoke();
}

void CpProxyLinnCoUkDebug2::EndSetDebugLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDebugLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDebug2::SyncDebugLevel(TUint& aaDebugLevel)
{
    SyncDebugLevelLinnCoUkDebug2 sync(*this, aaDebugLevel);
    BeginDebugLevel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDebug2::BeginDebugLevel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDebugLevel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDebugLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDebug2::EndDebugLevel(IAsync& aAsync, TUint& aaDebugLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DebugLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaDebugLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkDebug2::SyncMemWrite(TUint aaMemAddress, const Brx& aaMemData)
{
    SyncMemWriteLinnCoUkDebug2 sync(*this);
    BeginMemWrite(aaMemAddress, aaMemData, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDebug2::BeginMemWrite(TUint aaMemAddress, const Brx& aaMemData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMemWrite, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionMemWrite->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaMemAddress));
    invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], aaMemData));
    invocation->Invoke();
}

void CpProxyLinnCoUkDebug2::EndMemWrite(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("MemWrite"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

