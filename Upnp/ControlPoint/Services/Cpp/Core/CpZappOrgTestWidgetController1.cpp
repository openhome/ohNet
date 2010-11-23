#include <Core/CpZappOrgTestWidgetController1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncCreateWidgetZappOrgTestWidgetController1 : public SyncProxyAction
{
public:
    SyncCreateWidgetZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidgetController1& iService;
};

SyncCreateWidgetZappOrgTestWidgetController1::SyncCreateWidgetZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1& aProxy)
    : iService(aProxy)
{
}

void SyncCreateWidgetZappOrgTestWidgetController1::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateWidget(aAsync);
}


class SyncRemoveWidgetZappOrgTestWidgetController1 : public SyncProxyAction
{
public:
    SyncRemoveWidgetZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidgetController1& iService;
};

SyncRemoveWidgetZappOrgTestWidgetController1::SyncRemoveWidgetZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1& aProxy)
    : iService(aProxy)
{
}

void SyncRemoveWidgetZappOrgTestWidgetController1::CompleteRequest(IAsync& aAsync)
{
    iService.EndRemoveWidget(aAsync);
}


class SyncSetWidgetRegisterZappOrgTestWidgetController1 : public SyncProxyAction
{
public:
    SyncSetWidgetRegisterZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidgetController1& iService;
};

SyncSetWidgetRegisterZappOrgTestWidgetController1::SyncSetWidgetRegisterZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1& aProxy)
    : iService(aProxy)
{
}

void SyncSetWidgetRegisterZappOrgTestWidgetController1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetWidgetRegister(aAsync);
}


class SyncGetWidgetRegisterZappOrgTestWidgetController1 : public SyncProxyAction
{
public:
    SyncGetWidgetRegisterZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1& aProxy, TUint& aRegisterValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidgetController1& iService;
    TUint& iRegisterValue;
};

SyncGetWidgetRegisterZappOrgTestWidgetController1::SyncGetWidgetRegisterZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1& aProxy, TUint& aRegisterValue)
    : iService(aProxy)
    , iRegisterValue(aRegisterValue)
{
}

void SyncGetWidgetRegisterZappOrgTestWidgetController1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetWidgetRegister(aAsync, iRegisterValue);
}


CpProxyZappOrgTestWidgetController1::CpProxyZappOrgTestWidgetController1(CpDevice& aDevice)
    : CpProxy("zapp-org", "TestWidgetController", 1, aDevice.Device())
{
    Zapp::Parameter* param;

    iActionCreateWidget = new Action("CreateWidget");
    param = new Zapp::ParameterString("WidgetUdn");
    iActionCreateWidget->AddInputParameter(param);
    param = new Zapp::ParameterUint("WidgetClass");
    iActionCreateWidget->AddInputParameter(param);

    iActionRemoveWidget = new Action("RemoveWidget");
    param = new Zapp::ParameterString("WidgetUdn");
    iActionRemoveWidget->AddInputParameter(param);

    iActionSetWidgetRegister = new Action("SetWidgetRegister");
    param = new Zapp::ParameterString("WidgetUdn");
    iActionSetWidgetRegister->AddInputParameter(param);
    param = new Zapp::ParameterUint("RegisterIndex");
    iActionSetWidgetRegister->AddInputParameter(param);
    param = new Zapp::ParameterUint("RegisterValue");
    iActionSetWidgetRegister->AddInputParameter(param);

    iActionGetWidgetRegister = new Action("GetWidgetRegister");
    param = new Zapp::ParameterString("WidgetUdn");
    iActionGetWidgetRegister->AddInputParameter(param);
    param = new Zapp::ParameterUint("RegisterIndex");
    iActionGetWidgetRegister->AddInputParameter(param);
    param = new Zapp::ParameterUint("RegisterValue");
    iActionGetWidgetRegister->AddOutputParameter(param);
}

CpProxyZappOrgTestWidgetController1::~CpProxyZappOrgTestWidgetController1()
{
    DestroyService();
    delete iActionCreateWidget;
    delete iActionRemoveWidget;
    delete iActionSetWidgetRegister;
    delete iActionGetWidgetRegister;
}

void CpProxyZappOrgTestWidgetController1::SyncCreateWidget(const Brx& aWidgetUdn, TUint aWidgetClass)
{
    SyncCreateWidgetZappOrgTestWidgetController1 sync(*this);
    BeginCreateWidget(aWidgetUdn, aWidgetClass, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1::BeginCreateWidget(const Brx& aWidgetUdn, TUint aWidgetClass, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateWidget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateWidget->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aWidgetUdn));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aWidgetClass));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidgetController1::EndCreateWidget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateWidget"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestWidgetController1::SyncRemoveWidget(const Brx& aWidgetUdn)
{
    SyncRemoveWidgetZappOrgTestWidgetController1 sync(*this);
    BeginRemoveWidget(aWidgetUdn, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1::BeginRemoveWidget(const Brx& aWidgetUdn, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRemoveWidget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRemoveWidget->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aWidgetUdn));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidgetController1::EndRemoveWidget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("RemoveWidget"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestWidgetController1::SyncSetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue)
{
    SyncSetWidgetRegisterZappOrgTestWidgetController1 sync(*this);
    BeginSetWidgetRegister(aWidgetUdn, aRegisterIndex, aRegisterValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1::BeginSetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetWidgetRegister, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetWidgetRegister->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aWidgetUdn));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidgetController1::EndSetWidgetRegister(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetWidgetRegister"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestWidgetController1::SyncGetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, TUint& aRegisterValue)
{
    SyncGetWidgetRegisterZappOrgTestWidgetController1 sync(*this, aRegisterValue);
    BeginGetWidgetRegister(aWidgetUdn, aRegisterIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1::BeginGetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetWidgetRegister, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetWidgetRegister->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aWidgetUdn));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetWidgetRegister->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidgetController1::EndGetWidgetRegister(IAsync& aAsync, TUint& aRegisterValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetWidgetRegister"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aRegisterValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

