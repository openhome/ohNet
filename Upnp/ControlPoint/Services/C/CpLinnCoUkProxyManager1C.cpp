#include "CpLinnCoUkProxyManager1.h"
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

class CpProxyLinnCoUkProxyManager1C : public CpProxyC
{
public:
    CpProxyLinnCoUkProxyManager1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkProxyManager1C();
    //CpProxyLinnCoUkProxyManager1* Proxy() { return static_cast<CpProxyLinnCoUkProxyManager1*>(iProxy); }

    void SyncKontrolProductConnected(Brh& aaConnected);
    void BeginKontrolProductConnected(FunctorAsync& aFunctor);
    void EndKontrolProductConnected(IAsync& aAsync, Brh& aaConnected);

    void SyncSetKontrolProductConnected(const Brx& aaConnected);
    void BeginSetKontrolProductConnected(const Brx& aaConnected, FunctorAsync& aFunctor);
    void EndSetKontrolProductConnected(IAsync& aAsync);

    void SyncKontrolProductComPort(TUint& aaPort);
    void BeginKontrolProductComPort(FunctorAsync& aFunctor);
    void EndKontrolProductComPort(IAsync& aAsync, TUint& aaPort);

    void SyncSetKontrolProductComPort(TUint aaConnected);
    void BeginSetKontrolProductComPort(TUint aaConnected, FunctorAsync& aFunctor);
    void EndSetKontrolProductComPort(IAsync& aAsync);

    void SyncDiscPlayerConnected(Brh& aaConnected);
    void BeginDiscPlayerConnected(FunctorAsync& aFunctor);
    void EndDiscPlayerConnected(IAsync& aAsync, Brh& aaConnected);

    void SyncSetDiscPlayerConnected(const Brx& aaConnected);
    void BeginSetDiscPlayerConnected(const Brx& aaConnected, FunctorAsync& aFunctor);
    void EndSetDiscPlayerConnected(IAsync& aAsync);

    void SyncDiscPlayerComPort(TUint& aaPort);
    void BeginDiscPlayerComPort(FunctorAsync& aFunctor);
    void EndDiscPlayerComPort(IAsync& aAsync, TUint& aaPort);

    void SyncSetDiscPlayerComPort(TUint aaConnected);
    void BeginSetDiscPlayerComPort(TUint aaConnected, FunctorAsync& aFunctor);
    void EndSetDiscPlayerComPort(IAsync& aAsync);

    void SyncTestKontrolProductConnection(TBool& aaResult);
    void BeginTestKontrolProductConnection(FunctorAsync& aFunctor);
    void EndTestKontrolProductConnection(IAsync& aAsync, TBool& aaResult);

    void SyncTestDiscPlayerConnection(TBool& aaResult);
    void BeginTestDiscPlayerConnection(FunctorAsync& aFunctor);
    void EndTestDiscPlayerConnection(IAsync& aAsync, TBool& aaResult);

    void SetPropertyKontrolProductConnectedChanged(Functor& aFunctor);
    void SetPropertyKontrolProductComPortChanged(Functor& aFunctor);
    void SetPropertyDiscPlayerConnectedChanged(Functor& aFunctor);
    void SetPropertyDiscPlayerComPortChanged(Functor& aFunctor);

    void PropertyKontrolProductConnected(Brhz& aKontrolProductConnected) const;
    void PropertyKontrolProductComPort(TUint& aKontrolProductComPort) const;
    void PropertyDiscPlayerConnected(Brhz& aDiscPlayerConnected) const;
    void PropertyDiscPlayerComPort(TUint& aDiscPlayerComPort) const;
private:
    void KontrolProductConnectedPropertyChanged();
    void KontrolProductComPortPropertyChanged();
    void DiscPlayerConnectedPropertyChanged();
    void DiscPlayerComPortPropertyChanged();
private:
    Mutex iLock;
    Action* iActionKontrolProductConnected;
    Action* iActionSetKontrolProductConnected;
    Action* iActionKontrolProductComPort;
    Action* iActionSetKontrolProductComPort;
    Action* iActionDiscPlayerConnected;
    Action* iActionSetDiscPlayerConnected;
    Action* iActionDiscPlayerComPort;
    Action* iActionSetDiscPlayerComPort;
    Action* iActionTestKontrolProductConnection;
    Action* iActionTestDiscPlayerConnection;
    PropertyString* iKontrolProductConnected;
    PropertyUint* iKontrolProductComPort;
    PropertyString* iDiscPlayerConnected;
    PropertyUint* iDiscPlayerComPort;
    Functor iKontrolProductConnectedChanged;
    Functor iKontrolProductComPortChanged;
    Functor iDiscPlayerConnectedChanged;
    Functor iDiscPlayerComPortChanged;
};


class SyncKontrolProductConnectedLinnCoUkProxyManager1C : public SyncProxyAction
{
public:
    SyncKontrolProductConnectedLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, Brh& aaConnected);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1C& iService;
    Brh& iaConnected;
};

SyncKontrolProductConnectedLinnCoUkProxyManager1C::SyncKontrolProductConnectedLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, Brh& aaConnected)
    : iService(aProxy)
    , iaConnected(aaConnected)
{
}

void SyncKontrolProductConnectedLinnCoUkProxyManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndKontrolProductConnected(aAsync, iaConnected);
}


class SyncSetKontrolProductConnectedLinnCoUkProxyManager1C : public SyncProxyAction
{
public:
    SyncSetKontrolProductConnectedLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1C& iService;
};

SyncSetKontrolProductConnectedLinnCoUkProxyManager1C::SyncSetKontrolProductConnectedLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetKontrolProductConnectedLinnCoUkProxyManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetKontrolProductConnected(aAsync);
}


class SyncKontrolProductComPortLinnCoUkProxyManager1C : public SyncProxyAction
{
public:
    SyncKontrolProductComPortLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, TUint& aaPort);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1C& iService;
    TUint& iaPort;
};

SyncKontrolProductComPortLinnCoUkProxyManager1C::SyncKontrolProductComPortLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, TUint& aaPort)
    : iService(aProxy)
    , iaPort(aaPort)
{
}

void SyncKontrolProductComPortLinnCoUkProxyManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndKontrolProductComPort(aAsync, iaPort);
}


class SyncSetKontrolProductComPortLinnCoUkProxyManager1C : public SyncProxyAction
{
public:
    SyncSetKontrolProductComPortLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1C& iService;
};

SyncSetKontrolProductComPortLinnCoUkProxyManager1C::SyncSetKontrolProductComPortLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetKontrolProductComPortLinnCoUkProxyManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetKontrolProductComPort(aAsync);
}


class SyncDiscPlayerConnectedLinnCoUkProxyManager1C : public SyncProxyAction
{
public:
    SyncDiscPlayerConnectedLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, Brh& aaConnected);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1C& iService;
    Brh& iaConnected;
};

SyncDiscPlayerConnectedLinnCoUkProxyManager1C::SyncDiscPlayerConnectedLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, Brh& aaConnected)
    : iService(aProxy)
    , iaConnected(aaConnected)
{
}

void SyncDiscPlayerConnectedLinnCoUkProxyManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDiscPlayerConnected(aAsync, iaConnected);
}


class SyncSetDiscPlayerConnectedLinnCoUkProxyManager1C : public SyncProxyAction
{
public:
    SyncSetDiscPlayerConnectedLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1C& iService;
};

SyncSetDiscPlayerConnectedLinnCoUkProxyManager1C::SyncSetDiscPlayerConnectedLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetDiscPlayerConnectedLinnCoUkProxyManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDiscPlayerConnected(aAsync);
}


class SyncDiscPlayerComPortLinnCoUkProxyManager1C : public SyncProxyAction
{
public:
    SyncDiscPlayerComPortLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, TUint& aaPort);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1C& iService;
    TUint& iaPort;
};

SyncDiscPlayerComPortLinnCoUkProxyManager1C::SyncDiscPlayerComPortLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, TUint& aaPort)
    : iService(aProxy)
    , iaPort(aaPort)
{
}

void SyncDiscPlayerComPortLinnCoUkProxyManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDiscPlayerComPort(aAsync, iaPort);
}


class SyncSetDiscPlayerComPortLinnCoUkProxyManager1C : public SyncProxyAction
{
public:
    SyncSetDiscPlayerComPortLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1C& iService;
};

SyncSetDiscPlayerComPortLinnCoUkProxyManager1C::SyncSetDiscPlayerComPortLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetDiscPlayerComPortLinnCoUkProxyManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDiscPlayerComPort(aAsync);
}


class SyncTestKontrolProductConnectionLinnCoUkProxyManager1C : public SyncProxyAction
{
public:
    SyncTestKontrolProductConnectionLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, TBool& aaResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1C& iService;
    TBool& iaResult;
};

SyncTestKontrolProductConnectionLinnCoUkProxyManager1C::SyncTestKontrolProductConnectionLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, TBool& aaResult)
    : iService(aProxy)
    , iaResult(aaResult)
{
}

void SyncTestKontrolProductConnectionLinnCoUkProxyManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTestKontrolProductConnection(aAsync, iaResult);
}


class SyncTestDiscPlayerConnectionLinnCoUkProxyManager1C : public SyncProxyAction
{
public:
    SyncTestDiscPlayerConnectionLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, TBool& aaResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProxyManager1C& iService;
    TBool& iaResult;
};

SyncTestDiscPlayerConnectionLinnCoUkProxyManager1C::SyncTestDiscPlayerConnectionLinnCoUkProxyManager1C(CpProxyLinnCoUkProxyManager1C& aProxy, TBool& aaResult)
    : iService(aProxy)
    , iaResult(aaResult)
{
}

void SyncTestDiscPlayerConnectionLinnCoUkProxyManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTestDiscPlayerConnection(aAsync, iaResult);
}

CpProxyLinnCoUkProxyManager1C::CpProxyLinnCoUkProxyManager1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "ProxyManager", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1C::KontrolProductConnectedPropertyChanged);
    iKontrolProductConnected = new PropertyString("KontrolProductConnected", functor);
    AddProperty(iKontrolProductConnected);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1C::KontrolProductComPortPropertyChanged);
    iKontrolProductComPort = new PropertyUint("KontrolProductComPort", functor);
    AddProperty(iKontrolProductComPort);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1C::DiscPlayerConnectedPropertyChanged);
    iDiscPlayerConnected = new PropertyString("DiscPlayerConnected", functor);
    AddProperty(iDiscPlayerConnected);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProxyManager1C::DiscPlayerComPortPropertyChanged);
    iDiscPlayerComPort = new PropertyUint("DiscPlayerComPort", functor);
    AddProperty(iDiscPlayerComPort);
}

CpProxyLinnCoUkProxyManager1C::~CpProxyLinnCoUkProxyManager1C()
{
    DestroyService();
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

void CpProxyLinnCoUkProxyManager1C::SyncKontrolProductConnected(Brh& aaConnected)
{
    SyncKontrolProductConnectedLinnCoUkProxyManager1C sync(*this, aaConnected);
    BeginKontrolProductConnected(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1C::BeginKontrolProductConnected(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionKontrolProductConnected, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionKontrolProductConnected->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProxyManager1C::EndKontrolProductConnected(IAsync& aAsync, Brh& aaConnected)
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

void CpProxyLinnCoUkProxyManager1C::SyncSetKontrolProductConnected(const Brx& aaConnected)
{
    SyncSetKontrolProductConnectedLinnCoUkProxyManager1C sync(*this);
    BeginSetKontrolProductConnected(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1C::BeginSetKontrolProductConnected(const Brx& aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetKontrolProductConnected, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetKontrolProductConnected->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaConnected));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProxyManager1C::EndSetKontrolProductConnected(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetKontrolProductConnected"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1C::SyncKontrolProductComPort(TUint& aaPort)
{
    SyncKontrolProductComPortLinnCoUkProxyManager1C sync(*this, aaPort);
    BeginKontrolProductComPort(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1C::BeginKontrolProductComPort(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionKontrolProductComPort, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionKontrolProductComPort->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProxyManager1C::EndKontrolProductComPort(IAsync& aAsync, TUint& aaPort)
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

void CpProxyLinnCoUkProxyManager1C::SyncSetKontrolProductComPort(TUint aaConnected)
{
    SyncSetKontrolProductComPortLinnCoUkProxyManager1C sync(*this);
    BeginSetKontrolProductComPort(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1C::BeginSetKontrolProductComPort(TUint aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetKontrolProductComPort, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetKontrolProductComPort->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaConnected));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProxyManager1C::EndSetKontrolProductComPort(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetKontrolProductComPort"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1C::SyncDiscPlayerConnected(Brh& aaConnected)
{
    SyncDiscPlayerConnectedLinnCoUkProxyManager1C sync(*this, aaConnected);
    BeginDiscPlayerConnected(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1C::BeginDiscPlayerConnected(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDiscPlayerConnected, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDiscPlayerConnected->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProxyManager1C::EndDiscPlayerConnected(IAsync& aAsync, Brh& aaConnected)
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

void CpProxyLinnCoUkProxyManager1C::SyncSetDiscPlayerConnected(const Brx& aaConnected)
{
    SyncSetDiscPlayerConnectedLinnCoUkProxyManager1C sync(*this);
    BeginSetDiscPlayerConnected(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1C::BeginSetDiscPlayerConnected(const Brx& aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetDiscPlayerConnected, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDiscPlayerConnected->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaConnected));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProxyManager1C::EndSetDiscPlayerConnected(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDiscPlayerConnected"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1C::SyncDiscPlayerComPort(TUint& aaPort)
{
    SyncDiscPlayerComPortLinnCoUkProxyManager1C sync(*this, aaPort);
    BeginDiscPlayerComPort(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1C::BeginDiscPlayerComPort(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDiscPlayerComPort, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDiscPlayerComPort->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProxyManager1C::EndDiscPlayerComPort(IAsync& aAsync, TUint& aaPort)
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

void CpProxyLinnCoUkProxyManager1C::SyncSetDiscPlayerComPort(TUint aaConnected)
{
    SyncSetDiscPlayerComPortLinnCoUkProxyManager1C sync(*this);
    BeginSetDiscPlayerComPort(aaConnected, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1C::BeginSetDiscPlayerComPort(TUint aaConnected, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetDiscPlayerComPort, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDiscPlayerComPort->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaConnected));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProxyManager1C::EndSetDiscPlayerComPort(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDiscPlayerComPort"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProxyManager1C::SyncTestKontrolProductConnection(TBool& aaResult)
{
    SyncTestKontrolProductConnectionLinnCoUkProxyManager1C sync(*this, aaResult);
    BeginTestKontrolProductConnection(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1C::BeginTestKontrolProductConnection(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTestKontrolProductConnection, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTestKontrolProductConnection->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProxyManager1C::EndTestKontrolProductConnection(IAsync& aAsync, TBool& aaResult)
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

void CpProxyLinnCoUkProxyManager1C::SyncTestDiscPlayerConnection(TBool& aaResult)
{
    SyncTestDiscPlayerConnectionLinnCoUkProxyManager1C sync(*this, aaResult);
    BeginTestDiscPlayerConnection(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProxyManager1C::BeginTestDiscPlayerConnection(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTestDiscPlayerConnection, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTestDiscPlayerConnection->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProxyManager1C::EndTestDiscPlayerConnection(IAsync& aAsync, TBool& aaResult)
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

void CpProxyLinnCoUkProxyManager1C::SetPropertyKontrolProductConnectedChanged(Functor& aFunctor)
{
    iLock.Wait();
    iKontrolProductConnectedChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProxyManager1C::SetPropertyKontrolProductComPortChanged(Functor& aFunctor)
{
    iLock.Wait();
    iKontrolProductComPortChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProxyManager1C::SetPropertyDiscPlayerConnectedChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDiscPlayerConnectedChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProxyManager1C::SetPropertyDiscPlayerComPortChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDiscPlayerComPortChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProxyManager1C::PropertyKontrolProductConnected(Brhz& aKontrolProductConnected) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aKontrolProductConnected.Set(iKontrolProductConnected->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProxyManager1C::PropertyKontrolProductComPort(TUint& aKontrolProductComPort) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aKontrolProductComPort = iKontrolProductComPort->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProxyManager1C::PropertyDiscPlayerConnected(Brhz& aDiscPlayerConnected) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aDiscPlayerConnected.Set(iDiscPlayerConnected->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProxyManager1C::PropertyDiscPlayerComPort(TUint& aDiscPlayerComPort) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aDiscPlayerComPort = iDiscPlayerComPort->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkProxyManager1C::KontrolProductConnectedPropertyChanged()
{
    ReportEvent(iKontrolProductConnectedChanged);
}

void CpProxyLinnCoUkProxyManager1C::KontrolProductComPortPropertyChanged()
{
    ReportEvent(iKontrolProductComPortChanged);
}

void CpProxyLinnCoUkProxyManager1C::DiscPlayerConnectedPropertyChanged()
{
    ReportEvent(iDiscPlayerConnectedChanged);
}

void CpProxyLinnCoUkProxyManager1C::DiscPlayerComPortPropertyChanged()
{
    ReportEvent(iDiscPlayerComPortChanged);
}


THandle CpProxyLinnCoUkProxyManager1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkProxyManager1C(aDevice);
}

void CpProxyLinnCoUkProxyManager1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkProxyManager1SyncKontrolProductConnected(THandle aHandle, char** aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected;
    proxyC->SyncKontrolProductConnected(buf_aaConnected);
    *aaConnected = buf_aaConnected.Extract();
}

void CpProxyLinnCoUkProxyManager1BeginKontrolProductConnected(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginKontrolProductConnected(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndKontrolProductConnected(THandle aHandle, ZappHandleAsync aAsync, char** aaConnected)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaConnected;
    *aaConnected = NULL;
    try {
        proxyC->EndKontrolProductConnected(*async, buf_aaConnected);
        *aaConnected = buf_aaConnected.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductConnected(THandle aHandle, const char* aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected(aaConnected);
    proxyC->SyncSetKontrolProductConnected(buf_aaConnected);
}

void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductConnected(THandle aHandle, const char* aaConnected, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected(aaConnected);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetKontrolProductConnected(buf_aaConnected, functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndSetKontrolProductConnected(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetKontrolProductConnected(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncKontrolProductComPort(THandle aHandle, uint32_t* aaPort)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncKontrolProductComPort(*aaPort);
}

void CpProxyLinnCoUkProxyManager1BeginKontrolProductComPort(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginKontrolProductComPort(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndKontrolProductComPort(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaPort)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndKontrolProductComPort(*async, *aaPort);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductComPort(THandle aHandle, uint32_t aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetKontrolProductComPort(aaConnected);
}

void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductComPort(THandle aHandle, uint32_t aaConnected, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetKontrolProductComPort(aaConnected, functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndSetKontrolProductComPort(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetKontrolProductComPort(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncDiscPlayerConnected(THandle aHandle, char** aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected;
    proxyC->SyncDiscPlayerConnected(buf_aaConnected);
    *aaConnected = buf_aaConnected.Extract();
}

void CpProxyLinnCoUkProxyManager1BeginDiscPlayerConnected(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDiscPlayerConnected(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndDiscPlayerConnected(THandle aHandle, ZappHandleAsync aAsync, char** aaConnected)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaConnected;
    *aaConnected = NULL;
    try {
        proxyC->EndDiscPlayerConnected(*async, buf_aaConnected);
        *aaConnected = buf_aaConnected.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerConnected(THandle aHandle, const char* aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected(aaConnected);
    proxyC->SyncSetDiscPlayerConnected(buf_aaConnected);
}

void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerConnected(THandle aHandle, const char* aaConnected, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected(aaConnected);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetDiscPlayerConnected(buf_aaConnected, functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndSetDiscPlayerConnected(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetDiscPlayerConnected(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncDiscPlayerComPort(THandle aHandle, uint32_t* aaPort)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDiscPlayerComPort(*aaPort);
}

void CpProxyLinnCoUkProxyManager1BeginDiscPlayerComPort(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDiscPlayerComPort(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndDiscPlayerComPort(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaPort)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDiscPlayerComPort(*async, *aaPort);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerComPort(THandle aHandle, uint32_t aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetDiscPlayerComPort(aaConnected);
}

void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerComPort(THandle aHandle, uint32_t aaConnected, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetDiscPlayerComPort(aaConnected, functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndSetDiscPlayerComPort(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetDiscPlayerComPort(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncTestKontrolProductConnection(THandle aHandle, uint32_t* aaResult)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaResult = 0;
    proxyC->SyncTestKontrolProductConnection(*(TBool*)aaResult);
}

void CpProxyLinnCoUkProxyManager1BeginTestKontrolProductConnection(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginTestKontrolProductConnection(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndTestKontrolProductConnection(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaResult)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaResult = 0;
    try {
        proxyC->EndTestKontrolProductConnection(*async, *(TBool*)aaResult);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncTestDiscPlayerConnection(THandle aHandle, uint32_t* aaResult)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaResult = 0;
    proxyC->SyncTestDiscPlayerConnection(*(TBool*)aaResult);
}

void CpProxyLinnCoUkProxyManager1BeginTestDiscPlayerConnection(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginTestDiscPlayerConnection(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndTestDiscPlayerConnection(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaResult)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaResult = 0;
    try {
        proxyC->EndTestDiscPlayerConnection(*async, *(TBool*)aaResult);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductConnectedChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyKontrolProductConnectedChanged(functor);
}

void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductComPortChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyKontrolProductComPortChanged(functor);
}

void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerConnectedChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDiscPlayerConnectedChanged(functor);
}

void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerComPortChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDiscPlayerComPortChanged(functor);
}

void CpProxyLinnCoUkProxyManager1PropertyKontrolProductConnected(THandle aHandle, char** aKontrolProductConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aKontrolProductConnected;
    proxyC->PropertyKontrolProductConnected(buf_aKontrolProductConnected);
    *aKontrolProductConnected = buf_aKontrolProductConnected.Transfer();
}

void CpProxyLinnCoUkProxyManager1PropertyKontrolProductComPort(THandle aHandle, uint32_t* aKontrolProductComPort)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyKontrolProductComPort(*aKontrolProductComPort);
}

void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerConnected(THandle aHandle, char** aDiscPlayerConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aDiscPlayerConnected;
    proxyC->PropertyDiscPlayerConnected(buf_aDiscPlayerConnected);
    *aDiscPlayerConnected = buf_aDiscPlayerConnected.Transfer();
}

void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerComPort(THandle aHandle, uint32_t* aDiscPlayerComPort)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyDiscPlayerComPort(*aDiscPlayerComPort);
}

