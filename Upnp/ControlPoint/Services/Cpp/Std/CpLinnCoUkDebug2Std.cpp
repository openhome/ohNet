#include <Std/CpLinnCoUkDebug2.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncSetDebugLevelLinnCoUkDebug2Cpp : public SyncProxyAction
{
public:
    SyncSetDebugLevelLinnCoUkDebug2Cpp(CpProxyLinnCoUkDebug2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDebug2Cpp& iService;
};

SyncSetDebugLevelLinnCoUkDebug2Cpp::SyncSetDebugLevelLinnCoUkDebug2Cpp(CpProxyLinnCoUkDebug2Cpp& aService)
    : iService(aService)
{
}

void SyncSetDebugLevelLinnCoUkDebug2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDebugLevel(aAsync);
}


class SyncDebugLevelLinnCoUkDebug2Cpp : public SyncProxyAction
{
public:
    SyncDebugLevelLinnCoUkDebug2Cpp(CpProxyLinnCoUkDebug2Cpp& aService, uint32_t& aaDebugLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDebug2Cpp& iService;
    uint32_t& iaDebugLevel;
};

SyncDebugLevelLinnCoUkDebug2Cpp::SyncDebugLevelLinnCoUkDebug2Cpp(CpProxyLinnCoUkDebug2Cpp& aService, uint32_t& aaDebugLevel)
    : iService(aService)
    , iaDebugLevel(aaDebugLevel)
{
}

void SyncDebugLevelLinnCoUkDebug2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDebugLevel(aAsync, iaDebugLevel);
}


class SyncMemWriteLinnCoUkDebug2Cpp : public SyncProxyAction
{
public:
    SyncMemWriteLinnCoUkDebug2Cpp(CpProxyLinnCoUkDebug2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDebug2Cpp& iService;
};

SyncMemWriteLinnCoUkDebug2Cpp::SyncMemWriteLinnCoUkDebug2Cpp(CpProxyLinnCoUkDebug2Cpp& aService)
    : iService(aService)
{
}

void SyncMemWriteLinnCoUkDebug2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndMemWrite(aAsync);
}


CpProxyLinnCoUkDebug2Cpp::CpProxyLinnCoUkDebug2Cpp(CpDeviceCpp& aDevice)
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

CpProxyLinnCoUkDebug2Cpp::~CpProxyLinnCoUkDebug2Cpp()
{
    delete iService;
    delete iActionSetDebugLevel;
    delete iActionDebugLevel;
    delete iActionMemWrite;
}

void CpProxyLinnCoUkDebug2Cpp::SyncSetDebugLevel(uint32_t aaDebugLevel)
{
    SyncSetDebugLevelLinnCoUkDebug2Cpp sync(*this);
    BeginSetDebugLevel(aaDebugLevel, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDebug2Cpp::BeginSetDebugLevel(uint32_t aaDebugLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDebugLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDebugLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaDebugLevel));
    invocation->Invoke();
}

void CpProxyLinnCoUkDebug2Cpp::EndSetDebugLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDebugLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDebug2Cpp::SyncDebugLevel(uint32_t& aaDebugLevel)
{
    SyncDebugLevelLinnCoUkDebug2Cpp sync(*this, aaDebugLevel);
    BeginDebugLevel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDebug2Cpp::BeginDebugLevel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDebugLevel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDebugLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDebug2Cpp::EndDebugLevel(IAsync& aAsync, uint32_t& aaDebugLevel)
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

void CpProxyLinnCoUkDebug2Cpp::SyncMemWrite(uint32_t aaMemAddress, const std::string& aaMemData)
{
    SyncMemWriteLinnCoUkDebug2Cpp sync(*this);
    BeginMemWrite(aaMemAddress, aaMemData, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDebug2Cpp::BeginMemWrite(uint32_t aaMemAddress, const std::string& aaMemData, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMemWrite, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionMemWrite->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaMemAddress));
    {
        Brn buf((const TByte*)aaMemData.c_str(), aaMemData.length());
        invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkDebug2Cpp::EndMemWrite(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("MemWrite"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

