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


CpProxyZappOrgTestWidgetController1::CpProxyZappOrgTestWidgetController1(CpDevice& aDevice)
    : CpProxy("zapp-org", "TestWidgetController", 1, aDevice.Device())
{
    Zapp::Parameter* param;

    iActionCreateWidget = new Action("CreateWidget");
    param = new Zapp::ParameterString("WidgetUdn");
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
}

CpProxyZappOrgTestWidgetController1::~CpProxyZappOrgTestWidgetController1()
{
    DestroyService();
    delete iActionCreateWidget;
    delete iActionRemoveWidget;
    delete iActionSetWidgetRegister;
}

void CpProxyZappOrgTestWidgetController1::SyncCreateWidget(const Brx& aWidgetUdn)
{
    SyncCreateWidgetZappOrgTestWidgetController1 sync(*this);
    BeginCreateWidget(aWidgetUdn, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1::BeginCreateWidget(const Brx& aWidgetUdn, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateWidget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateWidget->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aWidgetUdn));
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

