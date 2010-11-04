#include <Std/CpZappOrgTestWidgetController1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncCreateWidgetZappOrgTestWidgetController1Cpp : public SyncProxyAction
{
public:
    SyncCreateWidgetZappOrgTestWidgetController1Cpp(CpProxyZappOrgTestWidgetController1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidgetController1Cpp& iService;
};

SyncCreateWidgetZappOrgTestWidgetController1Cpp::SyncCreateWidgetZappOrgTestWidgetController1Cpp(CpProxyZappOrgTestWidgetController1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncCreateWidgetZappOrgTestWidgetController1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateWidget(aAsync);
}


class SyncRemoveWidgetZappOrgTestWidgetController1Cpp : public SyncProxyAction
{
public:
    SyncRemoveWidgetZappOrgTestWidgetController1Cpp(CpProxyZappOrgTestWidgetController1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidgetController1Cpp& iService;
};

SyncRemoveWidgetZappOrgTestWidgetController1Cpp::SyncRemoveWidgetZappOrgTestWidgetController1Cpp(CpProxyZappOrgTestWidgetController1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncRemoveWidgetZappOrgTestWidgetController1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRemoveWidget(aAsync);
}


class SyncSetWidgetRegisterZappOrgTestWidgetController1Cpp : public SyncProxyAction
{
public:
    SyncSetWidgetRegisterZappOrgTestWidgetController1Cpp(CpProxyZappOrgTestWidgetController1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidgetController1Cpp& iService;
};

SyncSetWidgetRegisterZappOrgTestWidgetController1Cpp::SyncSetWidgetRegisterZappOrgTestWidgetController1Cpp(CpProxyZappOrgTestWidgetController1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetWidgetRegisterZappOrgTestWidgetController1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetWidgetRegister(aAsync);
}


CpProxyZappOrgTestWidgetController1Cpp::CpProxyZappOrgTestWidgetController1Cpp(CpDeviceCpp& aDevice)
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

CpProxyZappOrgTestWidgetController1Cpp::~CpProxyZappOrgTestWidgetController1Cpp()
{
    DestroyService();
    delete iActionCreateWidget;
    delete iActionRemoveWidget;
    delete iActionSetWidgetRegister;
}

void CpProxyZappOrgTestWidgetController1Cpp::SyncCreateWidget(const std::string& aWidgetUdn)
{
    SyncCreateWidgetZappOrgTestWidgetController1Cpp sync(*this);
    BeginCreateWidget(aWidgetUdn, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1Cpp::BeginCreateWidget(const std::string& aWidgetUdn, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateWidget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateWidget->InputParameters();
    {
        Brn buf((const TByte*)aWidgetUdn.c_str(), (TUint)aWidgetUdn.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyZappOrgTestWidgetController1Cpp::EndCreateWidget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateWidget"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestWidgetController1Cpp::SyncRemoveWidget(const std::string& aWidgetUdn)
{
    SyncRemoveWidgetZappOrgTestWidgetController1Cpp sync(*this);
    BeginRemoveWidget(aWidgetUdn, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1Cpp::BeginRemoveWidget(const std::string& aWidgetUdn, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRemoveWidget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRemoveWidget->InputParameters();
    {
        Brn buf((const TByte*)aWidgetUdn.c_str(), (TUint)aWidgetUdn.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyZappOrgTestWidgetController1Cpp::EndRemoveWidget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("RemoveWidget"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestWidgetController1Cpp::SyncSetWidgetRegister(const std::string& aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue)
{
    SyncSetWidgetRegisterZappOrgTestWidgetController1Cpp sync(*this);
    BeginSetWidgetRegister(aWidgetUdn, aRegisterIndex, aRegisterValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1Cpp::BeginSetWidgetRegister(const std::string& aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetWidgetRegister, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetWidgetRegister->InputParameters();
    {
        Brn buf((const TByte*)aWidgetUdn.c_str(), (TUint)aWidgetUdn.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterValue));
    invocation->Invoke();
}

void CpProxyZappOrgTestWidgetController1Cpp::EndSetWidgetRegister(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetWidgetRegister"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

