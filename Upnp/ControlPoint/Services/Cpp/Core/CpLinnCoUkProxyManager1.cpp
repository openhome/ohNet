#include <Core/CpLinnCoUkProxyManager1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncKontrolProductConnectedLinnCoUkProxyManager1 : public SyncProxyAction
{
public:
    SyncKontrolProductConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, Brh& aaConnected);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1& iService;
    Brh& iaConnected;
};

SyncKontrolProductConnectedLinnCoUkProxyManager1::SyncKontrolProductConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, Brh& aaConnected)
    : iService(aService)
    , iaConnected(aaConnected)
{
}

void SyncKontrolProductConnectedLinnCoUkProxyManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndKontrolProductConnected(aAsync, iaConnected);
}


class SyncSetKontrolProductConnectedLinnCoUkProxyManager1 : public SyncProxyAction
{
public:
    SyncSetKontrolProductConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1& iService;
};

SyncSetKontrolProductConnectedLinnCoUkProxyManager1::SyncSetKontrolProductConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService)
    : iService(aService)
{
}

void SyncSetKontrolProductConnectedLinnCoUkProxyManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetKontrolProductConnected(aAsync);
}


class SyncKontrolProductComPortLinnCoUkProxyManager1 : public SyncProxyAction
{
public:
    SyncKontrolProductComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, TUint& aaPort);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1& iService;
    TUint& iaPort;
};

SyncKontrolProductComPortLinnCoUkProxyManager1::SyncKontrolProductComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, TUint& aaPort)
    : iService(aService)
    , iaPort(aaPort)
{
}

void SyncKontrolProductComPortLinnCoUkProxyManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndKontrolProductComPort(aAsync, iaPort);
}


class SyncSetKontrolProductComPortLinnCoUkProxyManager1 : public SyncProxyAction
{
public:
    SyncSetKontrolProductComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1& iService;
};

SyncSetKontrolProductComPortLinnCoUkProxyManager1::SyncSetKontrolProductComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService)
    : iService(aService)
{
}

void SyncSetKontrolProductComPortLinnCoUkProxyManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetKontrolProductComPort(aAsync);
}


class SyncDiscPlayerConnectedLinnCoUkProxyManager1 : public SyncProxyAction
{
public:
    SyncDiscPlayerConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, Brh& aaConnected);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1& iService;
    Brh& iaConnected;
};

SyncDiscPlayerConnectedLinnCoUkProxyManager1::SyncDiscPlayerConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, Brh& aaConnected)
    : iService(aService)
    , iaConnected(aaConnected)
{
}

void SyncDiscPlayerConnectedLinnCoUkProxyManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDiscPlayerConnected(aAsync, iaConnected);
}


class SyncSetDiscPlayerConnectedLinnCoUkProxyManager1 : public SyncProxyAction
{
public:
    SyncSetDiscPlayerConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1& iService;
};

SyncSetDiscPlayerConnectedLinnCoUkProxyManager1::SyncSetDiscPlayerConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService)
    : iService(aService)
{
}

void SyncSetDiscPlayerConnectedLinnCoUkProxyManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDiscPlayerConnected(aAsync);
}


class SyncDiscPlayerComPortLinnCoUkProxyManager1 : public SyncProxyAction
{
public:
    SyncDiscPlayerComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, TUint& aaPort);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1& iService;
    TUint& iaPort;
};

SyncDiscPlayerComPortLinnCoUkProxyManager1::SyncDiscPlayerComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, TUint& aaPort)
    : iService(aService)
    , iaPort(aaPort)
{
}

void SyncDiscPlayerComPortLinnCoUkProxyManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDiscPlayerComPort(aAsync, iaPort);
}


class SyncSetDiscPlayerComPortLinnCoUkProxyManager1 : public SyncProxyAction
{
public:
    SyncSetDiscPlayerComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1& iService;
};

SyncSetDiscPlayerComPortLinnCoUkProxyManager1::SyncSetDiscPlayerComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService)
    : iService(aService)
{
}

void SyncSetDiscPlayerComPortLinnCoUkProxyManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDiscPlayerComPort(aAsync);
}


class SyncTestKontrolProductConnectionLinnCoUkProxyManager1 : public SyncProxyAction
{
public:
    SyncTestKontrolProductConnectionLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, TBool& aaResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1& iService;
    TBool& iaResult;
};

SyncTestKontrolProductConnectionLinnCoUkProxyManager1::SyncTestKontrolProductConnectionLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, TBool& aaResult)
    : iService(aService)
    , iaResult(aaResult)
{
}

void SyncTestKontrolProductConnectionLinnCoUkProxyManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTestKontrolProductConnection(aAsync, iaResult);
}


class SyncTestDiscPlayerConnectionLinnCoUkProxyManager1 : public SyncProxyAction
{
public:
    SyncTestDiscPlayerConnectionLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, TBool& aaResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1& iService;
    TBool& iaResult;
};

SyncTestDiscPlayerConnectionLinnCoUkProxyManager1::SyncTestDiscPlayerConnectionLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1& aService, TBool& aaResult)
    : iService(aService)
    , iaResult(aaResult)
{
}

void SyncTestDiscPlayerConnectionLinnCoUkProxyManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTestDiscPlayerConnection(aAsync, iaResult);
}


CpProxyLinnCoUkProxyManager1::CpProxyLinnCoUkProxyManager1(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "ProxyManager", 1, aDevice.Device());
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionKontrolProductConnected = new Action("KontrolProductConnected");
    index = 0;
    allowedValues = new TChar*[11];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"Klimax Kontrol";
    allowedValues[index++] = (TChar*)"Akurate Kontrol";
    allowedValues[index++] = (TChar*)"Kisto";
    allowedValues[index++] = (TChar*)"Kinos";
    allowedValues[index++] = (TChar*)"Majik Kontrol";
    allowedValues[index++] = (TChar*)"Majik-I";
    allowedValues[index++] = (TChar*)"Unidisk SC";
    allowedValues[index++] = (TChar*)"Classik Movie";
    allowedValues[index++] = (TChar*)"Classik Music";
    allowedValues[index++] = (TChar*)"Roomamp 2";
    param = new Zapp::ParameterString("aConnected", allowedValues, 11);
    iActionKontrolProductConnected->AddOutputParameter(param);
    delete[] allowedValues;

    iActionSetKontrolProductConnected = new Action("SetKontrolProductConnected");
    index = 0;
    allowedValues = new TChar*[11];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"Klimax Kontrol";
    allowedValues[index++] = (TChar*)"Akurate Kontrol";
    allowedValues[index++] = (TChar*)"Kisto";
    allowedValues[index++] = (TChar*)"Kinos";
    allowedValues[index++] = (TChar*)"Majik Kontrol";
    allowedValues[index++] = (TChar*)"Majik-I";
    allowedValues[index++] = (TChar*)"Unidisk SC";
    allowedValues[index++] = (TChar*)"Classik Movie";
    allowedValues[index++] = (TChar*)"Classik Music";
    allowedValues[index++] = (TChar*)"Roomamp 2";
    param = new Zapp::ParameterString("aConnected", allowedValues, 11);
    iActionSetKontrolProductConnected->AddInputParameter(param);
    delete[] allowedValues;

    iActionKontrolProductComPort = new Action("KontrolProductComPort");
    param = new Zapp::ParameterUint("aPort");
    iActionKontrolProductComPort->AddOutputParameter(param);

    iActionSetKontrolProductComPort = new Action("SetKontrolProductComPort");
    param = new Zapp::ParameterUint("aConnected");
    iActionSetKontrolProductComPort->AddInputParameter(param);

    iActionDiscPlayerConnected = new Action("DiscPlayerConnected");
    index = 0;
    allowedValues = new TChar*[9];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"CD12";
    allowedValues[index++] = (TChar*)"Akurate CD";
    allowedValues[index++] = (TChar*)"Unidisk 1.1";
    allowedValues[index++] = (TChar*)"Unidisk 2.1";
    allowedValues[index++] = (TChar*)"Majik CD";
    allowedValues[index++] = (TChar*)"Unidisk SC";
    allowedValues[index++] = (TChar*)"Classik Movie";
    allowedValues[index++] = (TChar*)"Classik Music";
    param = new Zapp::ParameterString("aConnected", allowedValues, 9);
    iActionDiscPlayerConnected->AddOutputParameter(param);
    delete[] allowedValues;

    iActionSetDiscPlayerConnected = new Action("SetDiscPlayerConnected");
    index = 0;
    allowedValues = new TChar*[9];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"CD12";
    allowedValues[index++] = (TChar*)"Akurate CD";
    allowedValues[index++] = (TChar*)"Unidisk 1.1";
    allowedValues[index++] = (TChar*)"Unidisk 2.1";
    allowedValues[index++] = (TChar*)"Majik CD";
    allowedValues[index++] = (TChar*)"Unidisk SC";
    allowedValues[index++] = (TChar*)"Classik Movie";
    allowedValues[index++] = (TChar*)"Classik Music";
    param = new Zapp::ParameterString("aConnected", allowedValues, 9);
    iActionSetDiscPlayerConnected->AddInputParameter(param);
    delete[] allowedValues;

    iActionDiscPlayerComPort = new Action("DiscPlayerComPort");
    param = new Zapp::ParameterUint("aPort");
    iActionDiscPlayerComPort->AddOutputParameter(param);

    iActionSetDiscPlayerComPort = new Action("SetDiscPlayerComPort");
    param = new Zapp::ParameterUint("aConnected");
    iActionSetDiscPlayerComPort->AddInputParameter(param);

    iActionTestKontrolProductConnection = new Action("TestKontrolProductConnection");
    param = new Zapp::ParameterBool("aResult");
    iActionTestKontrolProductConnection->AddOutputParameter(param);

    iActionTestDiscPlayerConnection = new Action("TestDiscPlayerConnection");
    param = new Zapp::ParameterBool("aResult");
    iActionTestDiscPlayerConnection->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1::KontrolProductConnectedPropertyChanged);
    iKontrolProductConnected = new PropertyString("KontrolProductConnected", functor);
    iService->AddProperty(iKontrolProductConnected);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1::KontrolProductComPortPropertyChanged);
    iKontrolProductComPort = new PropertyUint("KontrolProductComPort", functor);
    iService->AddProperty(iKontrolProductComPort);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1::DiscPlayerConnectedPropertyChanged);
    iDiscPlayerConnected = new PropertyString("DiscPlayerConnected", functor);
    iService->AddProperty(iDiscPlayerConnected);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1::DiscPlayerComPortPropertyChanged);
    iDiscPlayerComPort = new PropertyUint("DiscPlayerComPort", functor);
    iService->AddProperty(iDiscPlayerComPort);
}

CpProxyLinnCoUkProxyManager1::~CpProxyLinnCoUkProxyManager1()
{
    delete iService;
    delete iActionKontrolProductConnected;
    delete iActionSetKontrolProductConnected;
    delete iActionKontrolProductComPort;
    delete iActionSetKontrolProductComPort;
    delete iActionDiscPlayerConnected;
    delete iActionSetDiscPlayerConnected;
    delete iActionDiscPlayerComPort;
    delete iActionSetDiscPlayerComPort;
    delete iActionTestKontrolProductConnection;
    delete iActionTestDiscPlayerConnection;
}

void CpProxyLinnCoUkProxyManager1::SyncKontrolProductConnected(Brh& aaConnected)
{
    SyncKontrolProductConnectedLinnCoUkProxyManager1 sync(*this, aaConnected);
    BeginKontrolProductConnected(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1::BeginKontrolProductConnected(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionKontrolProductConnected, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionKontrolProductConnected->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1::EndKontrolProductConnected(IAsync& aAsync, Brh& aaConnected)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("KontrolProductConnected"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaConnected);
}

void CpProxyLinnCoUkProxyManager1::SyncSetKontrolProductConnected(const Brx& aaConnected)
{
    SyncSetKontrolProductConnectedLinnCoUkProxyManager1 sync(*this);
    BeginSetKontrolProductConnected(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1::BeginSetKontrolProductConnected(const Brx& aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetKontrolProductConnected, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetKontrolProductConnected->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaConnected));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1::EndSetKontrolProductConnected(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetKontrolProductConnected"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1::SyncKontrolProductComPort(TUint& aaPort)
{
    SyncKontrolProductComPortLinnCoUkProxyManager1 sync(*this, aaPort);
    BeginKontrolProductComPort(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1::BeginKontrolProductComPort(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionKontrolProductComPort, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionKontrolProductComPort->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1::EndKontrolProductComPort(IAsync& aAsync, TUint& aaPort)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("KontrolProductComPort"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaPort = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProxyManager1::SyncSetKontrolProductComPort(TUint aaConnected)
{
    SyncSetKontrolProductComPortLinnCoUkProxyManager1 sync(*this);
    BeginSetKontrolProductComPort(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1::BeginSetKontrolProductComPort(TUint aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetKontrolProductComPort, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetKontrolProductComPort->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaConnected));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1::EndSetKontrolProductComPort(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetKontrolProductComPort"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1::SyncDiscPlayerConnected(Brh& aaConnected)
{
    SyncDiscPlayerConnectedLinnCoUkProxyManager1 sync(*this, aaConnected);
    BeginDiscPlayerConnected(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1::BeginDiscPlayerConnected(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDiscPlayerConnected, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDiscPlayerConnected->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1::EndDiscPlayerConnected(IAsync& aAsync, Brh& aaConnected)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DiscPlayerConnected"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaConnected);
}

void CpProxyLinnCoUkProxyManager1::SyncSetDiscPlayerConnected(const Brx& aaConnected)
{
    SyncSetDiscPlayerConnectedLinnCoUkProxyManager1 sync(*this);
    BeginSetDiscPlayerConnected(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1::BeginSetDiscPlayerConnected(const Brx& aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDiscPlayerConnected, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDiscPlayerConnected->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaConnected));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1::EndSetDiscPlayerConnected(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDiscPlayerConnected"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1::SyncDiscPlayerComPort(TUint& aaPort)
{
    SyncDiscPlayerComPortLinnCoUkProxyManager1 sync(*this, aaPort);
    BeginDiscPlayerComPort(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1::BeginDiscPlayerComPort(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDiscPlayerComPort, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDiscPlayerComPort->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1::EndDiscPlayerComPort(IAsync& aAsync, TUint& aaPort)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DiscPlayerComPort"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaPort = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProxyManager1::SyncSetDiscPlayerComPort(TUint aaConnected)
{
    SyncSetDiscPlayerComPortLinnCoUkProxyManager1 sync(*this);
    BeginSetDiscPlayerComPort(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1::BeginSetDiscPlayerComPort(TUint aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDiscPlayerComPort, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDiscPlayerComPort->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaConnected));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1::EndSetDiscPlayerComPort(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDiscPlayerComPort"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1::SyncTestKontrolProductConnection(TBool& aaResult)
{
    SyncTestKontrolProductConnectionLinnCoUkProxyManager1 sync(*this, aaResult);
    BeginTestKontrolProductConnection(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1::BeginTestKontrolProductConnection(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTestKontrolProductConnection, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTestKontrolProductConnection->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1::EndTestKontrolProductConnection(IAsync& aAsync, TBool& aaResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TestKontrolProductConnection"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaResult = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProxyManager1::SyncTestDiscPlayerConnection(TBool& aaResult)
{
    SyncTestDiscPlayerConnectionLinnCoUkProxyManager1 sync(*this, aaResult);
    BeginTestDiscPlayerConnection(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1::BeginTestDiscPlayerConnection(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTestDiscPlayerConnection, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTestDiscPlayerConnection->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1::EndTestDiscPlayerConnection(IAsync& aAsync, TBool& aaResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TestDiscPlayerConnection"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaResult = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProxyManager1::SetPropertyKontrolProductConnectedChanged(Functor& aFunctor)
{
    iLock->Wait();
    iKontrolProductConnectedChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProxyManager1::SetPropertyKontrolProductComPortChanged(Functor& aFunctor)
{
    iLock->Wait();
    iKontrolProductComPortChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProxyManager1::SetPropertyDiscPlayerConnectedChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDiscPlayerConnectedChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProxyManager1::SetPropertyDiscPlayerComPortChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDiscPlayerComPortChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProxyManager1::PropertyKontrolProductConnected(Brhz& aKontrolProductConnected) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aKontrolProductConnected.Set(iKontrolProductConnected->Value());
}

void CpProxyLinnCoUkProxyManager1::PropertyKontrolProductComPort(TUint& aKontrolProductComPort) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aKontrolProductComPort = iKontrolProductComPort->Value();
}

void CpProxyLinnCoUkProxyManager1::PropertyDiscPlayerConnected(Brhz& aDiscPlayerConnected) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDiscPlayerConnected.Set(iDiscPlayerConnected->Value());
}

void CpProxyLinnCoUkProxyManager1::PropertyDiscPlayerComPort(TUint& aDiscPlayerComPort) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDiscPlayerComPort = iDiscPlayerComPort->Value();
}

void CpProxyLinnCoUkProxyManager1::KontrolProductConnectedPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iKontrolProductConnectedChanged != NULL) {
        iKontrolProductConnectedChanged();
    }
}

void CpProxyLinnCoUkProxyManager1::KontrolProductComPortPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iKontrolProductComPortChanged != NULL) {
        iKontrolProductComPortChanged();
    }
}

void CpProxyLinnCoUkProxyManager1::DiscPlayerConnectedPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDiscPlayerConnectedChanged != NULL) {
        iDiscPlayerConnectedChanged();
    }
}

void CpProxyLinnCoUkProxyManager1::DiscPlayerComPortPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDiscPlayerComPortChanged != NULL) {
        iDiscPlayerComPortChanged();
    }
}

