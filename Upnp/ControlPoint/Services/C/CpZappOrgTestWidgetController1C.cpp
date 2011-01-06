#include "CpZappOrgTestWidgetController1.h"
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

class CpProxyZappOrgTestWidgetController1C : public CpProxyC
{
public:
    CpProxyZappOrgTestWidgetController1C(CpDeviceC aDevice);
    ~CpProxyZappOrgTestWidgetController1C();
    //CpProxyZappOrgTestWidgetController1* Proxy() { return static_cast<CpProxyZappOrgTestWidgetController1*>(iProxy); }

    void SyncCreateWidget(const Brx& aWidgetUdn, TUint aWidgetClass);
    void BeginCreateWidget(const Brx& aWidgetUdn, TUint aWidgetClass, FunctorAsync& aFunctor);
    void EndCreateWidget(IAsync& aAsync);

    void SyncRemoveWidget(const Brx& aWidgetUdn);
    void BeginRemoveWidget(const Brx& aWidgetUdn, FunctorAsync& aFunctor);
    void EndRemoveWidget(IAsync& aAsync);

    void SyncSetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue);
    void BeginSetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue, FunctorAsync& aFunctor);
    void EndSetWidgetRegister(IAsync& aAsync);

    void SyncGetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, TUint& aRegisterValue);
    void BeginGetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, FunctorAsync& aFunctor);
    void EndGetWidgetRegister(IAsync& aAsync, TUint& aRegisterValue);


private:
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionCreateWidget;
    Action* iActionRemoveWidget;
    Action* iActionSetWidgetRegister;
    Action* iActionGetWidgetRegister;
};


class SyncCreateWidgetZappOrgTestWidgetController1C : public SyncProxyAction
{
public:
    SyncCreateWidgetZappOrgTestWidgetController1C(CpProxyZappOrgTestWidgetController1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidgetController1C& iService;
};

SyncCreateWidgetZappOrgTestWidgetController1C::SyncCreateWidgetZappOrgTestWidgetController1C(CpProxyZappOrgTestWidgetController1C& aProxy)
    : iService(aProxy)
{
}

void SyncCreateWidgetZappOrgTestWidgetController1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateWidget(aAsync);
}


class SyncRemoveWidgetZappOrgTestWidgetController1C : public SyncProxyAction
{
public:
    SyncRemoveWidgetZappOrgTestWidgetController1C(CpProxyZappOrgTestWidgetController1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidgetController1C& iService;
};

SyncRemoveWidgetZappOrgTestWidgetController1C::SyncRemoveWidgetZappOrgTestWidgetController1C(CpProxyZappOrgTestWidgetController1C& aProxy)
    : iService(aProxy)
{
}

void SyncRemoveWidgetZappOrgTestWidgetController1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRemoveWidget(aAsync);
}


class SyncSetWidgetRegisterZappOrgTestWidgetController1C : public SyncProxyAction
{
public:
    SyncSetWidgetRegisterZappOrgTestWidgetController1C(CpProxyZappOrgTestWidgetController1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidgetController1C& iService;
};

SyncSetWidgetRegisterZappOrgTestWidgetController1C::SyncSetWidgetRegisterZappOrgTestWidgetController1C(CpProxyZappOrgTestWidgetController1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetWidgetRegisterZappOrgTestWidgetController1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetWidgetRegister(aAsync);
}


class SyncGetWidgetRegisterZappOrgTestWidgetController1C : public SyncProxyAction
{
public:
    SyncGetWidgetRegisterZappOrgTestWidgetController1C(CpProxyZappOrgTestWidgetController1C& aProxy, TUint& aRegisterValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidgetController1C& iService;
    TUint& iRegisterValue;
};

SyncGetWidgetRegisterZappOrgTestWidgetController1C::SyncGetWidgetRegisterZappOrgTestWidgetController1C(CpProxyZappOrgTestWidgetController1C& aProxy, TUint& aRegisterValue)
    : iService(aProxy)
    , iRegisterValue(aRegisterValue)
{
}

void SyncGetWidgetRegisterZappOrgTestWidgetController1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetWidgetRegister(aAsync, iRegisterValue);
}

CpProxyZappOrgTestWidgetController1C::CpProxyZappOrgTestWidgetController1C(CpDeviceC aDevice)
    : CpProxyC("zapp-org", "TestWidgetController", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
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

CpProxyZappOrgTestWidgetController1C::~CpProxyZappOrgTestWidgetController1C()
{
    DestroyService();
    delete iActionCreateWidget;
    delete iActionRemoveWidget;
    delete iActionSetWidgetRegister;
    delete iActionGetWidgetRegister;
}

void CpProxyZappOrgTestWidgetController1C::SyncCreateWidget(const Brx& aWidgetUdn, TUint aWidgetClass)
{
    SyncCreateWidgetZappOrgTestWidgetController1C sync(*this);
    BeginCreateWidget(aWidgetUdn, aWidgetClass, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1C::BeginCreateWidget(const Brx& aWidgetUdn, TUint aWidgetClass, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCreateWidget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateWidget->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aWidgetUdn));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aWidgetClass));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidgetController1C::EndCreateWidget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateWidget"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestWidgetController1C::SyncRemoveWidget(const Brx& aWidgetUdn)
{
    SyncRemoveWidgetZappOrgTestWidgetController1C sync(*this);
    BeginRemoveWidget(aWidgetUdn, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1C::BeginRemoveWidget(const Brx& aWidgetUdn, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRemoveWidget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRemoveWidget->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aWidgetUdn));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidgetController1C::EndRemoveWidget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("RemoveWidget"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestWidgetController1C::SyncSetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue)
{
    SyncSetWidgetRegisterZappOrgTestWidgetController1C sync(*this);
    BeginSetWidgetRegister(aWidgetUdn, aRegisterIndex, aRegisterValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1C::BeginSetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetWidgetRegister, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetWidgetRegister->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aWidgetUdn));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidgetController1C::EndSetWidgetRegister(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetWidgetRegister"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestWidgetController1C::SyncGetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, TUint& aRegisterValue)
{
    SyncGetWidgetRegisterZappOrgTestWidgetController1C sync(*this, aRegisterValue);
    BeginGetWidgetRegister(aWidgetUdn, aRegisterIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidgetController1C::BeginGetWidgetRegister(const Brx& aWidgetUdn, TUint aRegisterIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetWidgetRegister, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetWidgetRegister->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aWidgetUdn));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetWidgetRegister->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidgetController1C::EndGetWidgetRegister(IAsync& aAsync, TUint& aRegisterValue)
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


THandle CpProxyZappOrgTestWidgetController1Create(CpDeviceC aDevice)
{
    return new CpProxyZappOrgTestWidgetController1C(aDevice);
}

void CpProxyZappOrgTestWidgetController1Destroy(THandle aHandle)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    delete proxyC;
}

void CpProxyZappOrgTestWidgetController1SyncCreateWidget(THandle aHandle, const char* aWidgetUdn, uint32_t aWidgetClass)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    proxyC->SyncCreateWidget(buf_aWidgetUdn, aWidgetClass);
}

void CpProxyZappOrgTestWidgetController1BeginCreateWidget(THandle aHandle, const char* aWidgetUdn, uint32_t aWidgetClass, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginCreateWidget(buf_aWidgetUdn, aWidgetClass, functor);
}

int32_t CpProxyZappOrgTestWidgetController1EndCreateWidget(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndCreateWidget(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestWidgetController1SyncRemoveWidget(THandle aHandle, const char* aWidgetUdn)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    proxyC->SyncRemoveWidget(buf_aWidgetUdn);
}

void CpProxyZappOrgTestWidgetController1BeginRemoveWidget(THandle aHandle, const char* aWidgetUdn, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginRemoveWidget(buf_aWidgetUdn, functor);
}

int32_t CpProxyZappOrgTestWidgetController1EndRemoveWidget(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndRemoveWidget(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestWidgetController1SyncSetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    proxyC->SyncSetWidgetRegister(buf_aWidgetUdn, aRegisterIndex, aRegisterValue);
}

void CpProxyZappOrgTestWidgetController1BeginSetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetWidgetRegister(buf_aWidgetUdn, aRegisterIndex, aRegisterValue, functor);
}

int32_t CpProxyZappOrgTestWidgetController1EndSetWidgetRegister(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetWidgetRegister(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestWidgetController1SyncGetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t* aRegisterValue)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    proxyC->SyncGetWidgetRegister(buf_aWidgetUdn, aRegisterIndex, *aRegisterValue);
}

void CpProxyZappOrgTestWidgetController1BeginGetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetWidgetRegister(buf_aWidgetUdn, aRegisterIndex, functor);
}

int32_t CpProxyZappOrgTestWidgetController1EndGetWidgetRegister(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aRegisterValue)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetWidgetRegister(*async, *aRegisterValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

