#include <Std/CpLinnCoUkProxyManager1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncKontrolProductConnectedLinnCoUkProxyManager1Cpp : public SyncProxyAction
{
public:
    SyncKontrolProductConnectedLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, std::string& aaConnected);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1Cpp& iService;
    std::string& iaConnected;
};

SyncKontrolProductConnectedLinnCoUkProxyManager1Cpp::SyncKontrolProductConnectedLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, std::string& aaConnected)
    : iService(aService)
    , iaConnected(aaConnected)
{
}

void SyncKontrolProductConnectedLinnCoUkProxyManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndKontrolProductConnected(aAsync, iaConnected);
}


class SyncSetKontrolProductConnectedLinnCoUkProxyManager1Cpp : public SyncProxyAction
{
public:
    SyncSetKontrolProductConnectedLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1Cpp& iService;
};

SyncSetKontrolProductConnectedLinnCoUkProxyManager1Cpp::SyncSetKontrolProductConnectedLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService)
    : iService(aService)
{
}

void SyncSetKontrolProductConnectedLinnCoUkProxyManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetKontrolProductConnected(aAsync);
}


class SyncKontrolProductComPortLinnCoUkProxyManager1Cpp : public SyncProxyAction
{
public:
    SyncKontrolProductComPortLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, uint32_t& aaPort);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1Cpp& iService;
    uint32_t& iaPort;
};

SyncKontrolProductComPortLinnCoUkProxyManager1Cpp::SyncKontrolProductComPortLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, uint32_t& aaPort)
    : iService(aService)
    , iaPort(aaPort)
{
}

void SyncKontrolProductComPortLinnCoUkProxyManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndKontrolProductComPort(aAsync, iaPort);
}


class SyncSetKontrolProductComPortLinnCoUkProxyManager1Cpp : public SyncProxyAction
{
public:
    SyncSetKontrolProductComPortLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1Cpp& iService;
};

SyncSetKontrolProductComPortLinnCoUkProxyManager1Cpp::SyncSetKontrolProductComPortLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService)
    : iService(aService)
{
}

void SyncSetKontrolProductComPortLinnCoUkProxyManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetKontrolProductComPort(aAsync);
}


class SyncDiscPlayerConnectedLinnCoUkProxyManager1Cpp : public SyncProxyAction
{
public:
    SyncDiscPlayerConnectedLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, std::string& aaConnected);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1Cpp& iService;
    std::string& iaConnected;
};

SyncDiscPlayerConnectedLinnCoUkProxyManager1Cpp::SyncDiscPlayerConnectedLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, std::string& aaConnected)
    : iService(aService)
    , iaConnected(aaConnected)
{
}

void SyncDiscPlayerConnectedLinnCoUkProxyManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDiscPlayerConnected(aAsync, iaConnected);
}


class SyncSetDiscPlayerConnectedLinnCoUkProxyManager1Cpp : public SyncProxyAction
{
public:
    SyncSetDiscPlayerConnectedLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1Cpp& iService;
};

SyncSetDiscPlayerConnectedLinnCoUkProxyManager1Cpp::SyncSetDiscPlayerConnectedLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService)
    : iService(aService)
{
}

void SyncSetDiscPlayerConnectedLinnCoUkProxyManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDiscPlayerConnected(aAsync);
}


class SyncDiscPlayerComPortLinnCoUkProxyManager1Cpp : public SyncProxyAction
{
public:
    SyncDiscPlayerComPortLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, uint32_t& aaPort);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1Cpp& iService;
    uint32_t& iaPort;
};

SyncDiscPlayerComPortLinnCoUkProxyManager1Cpp::SyncDiscPlayerComPortLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, uint32_t& aaPort)
    : iService(aService)
    , iaPort(aaPort)
{
}

void SyncDiscPlayerComPortLinnCoUkProxyManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDiscPlayerComPort(aAsync, iaPort);
}


class SyncSetDiscPlayerComPortLinnCoUkProxyManager1Cpp : public SyncProxyAction
{
public:
    SyncSetDiscPlayerComPortLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1Cpp& iService;
};

SyncSetDiscPlayerComPortLinnCoUkProxyManager1Cpp::SyncSetDiscPlayerComPortLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService)
    : iService(aService)
{
}

void SyncSetDiscPlayerComPortLinnCoUkProxyManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDiscPlayerComPort(aAsync);
}


class SyncTestKontrolProductConnectionLinnCoUkProxyManager1Cpp : public SyncProxyAction
{
public:
    SyncTestKontrolProductConnectionLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, bool& aaResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1Cpp& iService;
    bool& iaResult;
};

SyncTestKontrolProductConnectionLinnCoUkProxyManager1Cpp::SyncTestKontrolProductConnectionLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, bool& aaResult)
    : iService(aService)
    , iaResult(aaResult)
{
}

void SyncTestKontrolProductConnectionLinnCoUkProxyManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTestKontrolProductConnection(aAsync, iaResult);
}


class SyncTestDiscPlayerConnectionLinnCoUkProxyManager1Cpp : public SyncProxyAction
{
public:
    SyncTestDiscPlayerConnectionLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, bool& aaResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1Cpp& iService;
    bool& iaResult;
};

SyncTestDiscPlayerConnectionLinnCoUkProxyManager1Cpp::SyncTestDiscPlayerConnectionLinnCoUkProxyManager1Cpp(CpProxyLinnCoUkProxyManager1Cpp& aService, bool& aaResult)
    : iService(aService)
    , iaResult(aaResult)
{
}

void SyncTestDiscPlayerConnectionLinnCoUkProxyManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTestDiscPlayerConnection(aAsync, iaResult);
}


CpProxyLinnCoUkProxyManager1Cpp::CpProxyLinnCoUkProxyManager1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1Cpp::KontrolProductConnectedPropertyChanged);
    iKontrolProductConnected = new PropertyString("KontrolProductConnected", functor);
    iService->AddProperty(iKontrolProductConnected);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1Cpp::KontrolProductComPortPropertyChanged);
    iKontrolProductComPort = new PropertyUint("KontrolProductComPort", functor);
    iService->AddProperty(iKontrolProductComPort);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1Cpp::DiscPlayerConnectedPropertyChanged);
    iDiscPlayerConnected = new PropertyString("DiscPlayerConnected", functor);
    iService->AddProperty(iDiscPlayerConnected);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1Cpp::DiscPlayerComPortPropertyChanged);
    iDiscPlayerComPort = new PropertyUint("DiscPlayerComPort", functor);
    iService->AddProperty(iDiscPlayerComPort);
}

CpProxyLinnCoUkProxyManager1Cpp::~CpProxyLinnCoUkProxyManager1Cpp()
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

void CpProxyLinnCoUkProxyManager1Cpp::SyncKontrolProductConnected(std::string& aaConnected)
{
    SyncKontrolProductConnectedLinnCoUkProxyManager1Cpp sync(*this, aaConnected);
    BeginKontrolProductConnected(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1Cpp::BeginKontrolProductConnected(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionKontrolProductConnected, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionKontrolProductConnected->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1Cpp::EndKontrolProductConnected(IAsync& aAsync, std::string& aaConnected)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("KontrolProductConnected"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaConnected.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkProxyManager1Cpp::SyncSetKontrolProductConnected(const std::string& aaConnected)
{
    SyncSetKontrolProductConnectedLinnCoUkProxyManager1Cpp sync(*this);
    BeginSetKontrolProductConnected(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1Cpp::BeginSetKontrolProductConnected(const std::string& aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetKontrolProductConnected, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetKontrolProductConnected->InputParameters();
    {
        Brn buf((const TByte*)aaConnected.c_str(), aaConnected.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1Cpp::EndSetKontrolProductConnected(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetKontrolProductConnected"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1Cpp::SyncKontrolProductComPort(uint32_t& aaPort)
{
    SyncKontrolProductComPortLinnCoUkProxyManager1Cpp sync(*this, aaPort);
    BeginKontrolProductComPort(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1Cpp::BeginKontrolProductComPort(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionKontrolProductComPort, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionKontrolProductComPort->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1Cpp::EndKontrolProductComPort(IAsync& aAsync, uint32_t& aaPort)
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

void CpProxyLinnCoUkProxyManager1Cpp::SyncSetKontrolProductComPort(uint32_t aaConnected)
{
    SyncSetKontrolProductComPortLinnCoUkProxyManager1Cpp sync(*this);
    BeginSetKontrolProductComPort(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1Cpp::BeginSetKontrolProductComPort(uint32_t aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetKontrolProductComPort, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetKontrolProductComPort->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaConnected));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1Cpp::EndSetKontrolProductComPort(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetKontrolProductComPort"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1Cpp::SyncDiscPlayerConnected(std::string& aaConnected)
{
    SyncDiscPlayerConnectedLinnCoUkProxyManager1Cpp sync(*this, aaConnected);
    BeginDiscPlayerConnected(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1Cpp::BeginDiscPlayerConnected(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDiscPlayerConnected, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDiscPlayerConnected->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1Cpp::EndDiscPlayerConnected(IAsync& aAsync, std::string& aaConnected)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DiscPlayerConnected"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaConnected.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkProxyManager1Cpp::SyncSetDiscPlayerConnected(const std::string& aaConnected)
{
    SyncSetDiscPlayerConnectedLinnCoUkProxyManager1Cpp sync(*this);
    BeginSetDiscPlayerConnected(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1Cpp::BeginSetDiscPlayerConnected(const std::string& aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDiscPlayerConnected, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDiscPlayerConnected->InputParameters();
    {
        Brn buf((const TByte*)aaConnected.c_str(), aaConnected.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1Cpp::EndSetDiscPlayerConnected(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDiscPlayerConnected"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1Cpp::SyncDiscPlayerComPort(uint32_t& aaPort)
{
    SyncDiscPlayerComPortLinnCoUkProxyManager1Cpp sync(*this, aaPort);
    BeginDiscPlayerComPort(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1Cpp::BeginDiscPlayerComPort(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDiscPlayerComPort, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDiscPlayerComPort->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1Cpp::EndDiscPlayerComPort(IAsync& aAsync, uint32_t& aaPort)
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

void CpProxyLinnCoUkProxyManager1Cpp::SyncSetDiscPlayerComPort(uint32_t aaConnected)
{
    SyncSetDiscPlayerComPortLinnCoUkProxyManager1Cpp sync(*this);
    BeginSetDiscPlayerComPort(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1Cpp::BeginSetDiscPlayerComPort(uint32_t aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDiscPlayerComPort, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDiscPlayerComPort->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaConnected));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1Cpp::EndSetDiscPlayerComPort(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDiscPlayerComPort"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1Cpp::SyncTestKontrolProductConnection(bool& aaResult)
{
    SyncTestKontrolProductConnectionLinnCoUkProxyManager1Cpp sync(*this, aaResult);
    BeginTestKontrolProductConnection(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1Cpp::BeginTestKontrolProductConnection(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTestKontrolProductConnection, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTestKontrolProductConnection->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1Cpp::EndTestKontrolProductConnection(IAsync& aAsync, bool& aaResult)
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

void CpProxyLinnCoUkProxyManager1Cpp::SyncTestDiscPlayerConnection(bool& aaResult)
{
    SyncTestDiscPlayerConnectionLinnCoUkProxyManager1Cpp sync(*this, aaResult);
    BeginTestDiscPlayerConnection(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1Cpp::BeginTestDiscPlayerConnection(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTestDiscPlayerConnection, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTestDiscPlayerConnection->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProxyManager1Cpp::EndTestDiscPlayerConnection(IAsync& aAsync, bool& aaResult)
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

void CpProxyLinnCoUkProxyManager1Cpp::SetPropertyKontrolProductConnectedChanged(Functor& aFunctor)
{
    iLock->Wait();
    iKontrolProductConnectedChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProxyManager1Cpp::SetPropertyKontrolProductComPortChanged(Functor& aFunctor)
{
    iLock->Wait();
    iKontrolProductComPortChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProxyManager1Cpp::SetPropertyDiscPlayerConnectedChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDiscPlayerConnectedChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProxyManager1Cpp::SetPropertyDiscPlayerComPortChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDiscPlayerComPortChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProxyManager1Cpp::PropertyKontrolProductConnected(std::string& aKontrolProductConnected) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iKontrolProductConnected->Value();
    aKontrolProductConnected.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkProxyManager1Cpp::PropertyKontrolProductComPort(uint32_t& aKontrolProductComPort) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aKontrolProductComPort = iKontrolProductComPort->Value();
}

void CpProxyLinnCoUkProxyManager1Cpp::PropertyDiscPlayerConnected(std::string& aDiscPlayerConnected) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iDiscPlayerConnected->Value();
    aDiscPlayerConnected.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkProxyManager1Cpp::PropertyDiscPlayerComPort(uint32_t& aDiscPlayerComPort) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDiscPlayerComPort = iDiscPlayerComPort->Value();
}

void CpProxyLinnCoUkProxyManager1Cpp::KontrolProductConnectedPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iKontrolProductConnectedChanged != NULL) {
        iKontrolProductConnectedChanged();
    }
}

void CpProxyLinnCoUkProxyManager1Cpp::KontrolProductComPortPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iKontrolProductComPortChanged != NULL) {
        iKontrolProductComPortChanged();
    }
}

void CpProxyLinnCoUkProxyManager1Cpp::DiscPlayerConnectedPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDiscPlayerConnectedChanged != NULL) {
        iDiscPlayerConnectedChanged();
    }
}

void CpProxyLinnCoUkProxyManager1Cpp::DiscPlayerComPortPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDiscPlayerComPortChanged != NULL) {
        iDiscPlayerComPortChanged();
    }
}

