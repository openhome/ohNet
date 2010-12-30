#include "CpZappOrgTestWidget1.h"
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

class CpProxyZappOrgTestWidget1C : public CpProxyC
{
public:
    CpProxyZappOrgTestWidget1C(CpDeviceC aDevice);
    ~CpProxyZappOrgTestWidget1C();
    //CpProxyZappOrgTestWidget1* Proxy() { return static_cast<CpProxyZappOrgTestWidget1*>(iProxy); }

    void SyncSetReadWriteRegister(TUint aRegisterIndex, TUint aRegisterValue);
    void BeginSetReadWriteRegister(TUint aRegisterIndex, TUint aRegisterValue, FunctorAsync& aFunctor);
    void EndSetReadWriteRegister(IAsync& aAsync);

    void SyncGetWidgetClass(TUint& aWidgetClass);
    void BeginGetWidgetClass(FunctorAsync& aFunctor);
    void EndGetWidgetClass(IAsync& aAsync, TUint& aWidgetClass);

    void SetPropertyReadWriteRegister0Changed(Functor& aFunctor);
    void SetPropertyReadWriteRegister1Changed(Functor& aFunctor);
    void SetPropertyReadWriteRegister2Changed(Functor& aFunctor);
    void SetPropertyReadWriteRegister3Changed(Functor& aFunctor);
    void SetPropertyReadOnlyRegister4Changed(Functor& aFunctor);
    void SetPropertyReadOnlyRegister5Changed(Functor& aFunctor);
    void SetPropertyReadOnlyRegister6Changed(Functor& aFunctor);
    void SetPropertyReadOnlyRegister7Changed(Functor& aFunctor);

    void PropertyReadWriteRegister0(TUint& aReadWriteRegister0) const;
    void PropertyReadWriteRegister1(TUint& aReadWriteRegister1) const;
    void PropertyReadWriteRegister2(TUint& aReadWriteRegister2) const;
    void PropertyReadWriteRegister3(TUint& aReadWriteRegister3) const;
    void PropertyReadOnlyRegister4(TUint& aReadOnlyRegister4) const;
    void PropertyReadOnlyRegister5(TUint& aReadOnlyRegister5) const;
    void PropertyReadOnlyRegister6(TUint& aReadOnlyRegister6) const;
    void PropertyReadOnlyRegister7(TUint& aReadOnlyRegister7) const;
private:
    void ReadWriteRegister0PropertyChanged();
    void ReadWriteRegister1PropertyChanged();
    void ReadWriteRegister2PropertyChanged();
    void ReadWriteRegister3PropertyChanged();
    void ReadOnlyRegister4PropertyChanged();
    void ReadOnlyRegister5PropertyChanged();
    void ReadOnlyRegister6PropertyChanged();
    void ReadOnlyRegister7PropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionSetReadWriteRegister;
    Action* iActionGetWidgetClass;
    PropertyUint* iReadWriteRegister0;
    PropertyUint* iReadWriteRegister1;
    PropertyUint* iReadWriteRegister2;
    PropertyUint* iReadWriteRegister3;
    PropertyUint* iReadOnlyRegister4;
    PropertyUint* iReadOnlyRegister5;
    PropertyUint* iReadOnlyRegister6;
    PropertyUint* iReadOnlyRegister7;
    Functor iReadWriteRegister0Changed;
    Functor iReadWriteRegister1Changed;
    Functor iReadWriteRegister2Changed;
    Functor iReadWriteRegister3Changed;
    Functor iReadOnlyRegister4Changed;
    Functor iReadOnlyRegister5Changed;
    Functor iReadOnlyRegister6Changed;
    Functor iReadOnlyRegister7Changed;
};


class SyncSetReadWriteRegisterZappOrgTestWidget1C : public SyncProxyAction
{
public:
    SyncSetReadWriteRegisterZappOrgTestWidget1C(CpProxyZappOrgTestWidget1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidget1C& iService;
};

SyncSetReadWriteRegisterZappOrgTestWidget1C::SyncSetReadWriteRegisterZappOrgTestWidget1C(CpProxyZappOrgTestWidget1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetReadWriteRegisterZappOrgTestWidget1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetReadWriteRegister(aAsync);
}


class SyncGetWidgetClassZappOrgTestWidget1C : public SyncProxyAction
{
public:
    SyncGetWidgetClassZappOrgTestWidget1C(CpProxyZappOrgTestWidget1C& aProxy, TUint& aWidgetClass);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidget1C& iService;
    TUint& iWidgetClass;
};

SyncGetWidgetClassZappOrgTestWidget1C::SyncGetWidgetClassZappOrgTestWidget1C(CpProxyZappOrgTestWidget1C& aProxy, TUint& aWidgetClass)
    : iService(aProxy)
    , iWidgetClass(aWidgetClass)
{
}

void SyncGetWidgetClassZappOrgTestWidget1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetWidgetClass(aAsync, iWidgetClass);
}

CpProxyZappOrgTestWidget1C::CpProxyZappOrgTestWidget1C(CpDeviceC aDevice)
    : CpProxyC("zapp-org", "TestWidget", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
    Zapp::Parameter* param;

    iActionSetReadWriteRegister = new Action("SetReadWriteRegister");
    param = new Zapp::ParameterUint("RegisterIndex");
    iActionSetReadWriteRegister->AddInputParameter(param);
    param = new Zapp::ParameterUint("RegisterValue");
    iActionSetReadWriteRegister->AddInputParameter(param);

    iActionGetWidgetClass = new Action("GetWidgetClass");
    param = new Zapp::ParameterUint("WidgetClass");
    iActionGetWidgetClass->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1C::ReadWriteRegister0PropertyChanged);
    iReadWriteRegister0 = new PropertyUint("ReadWriteRegister0", functor);
    AddProperty(iReadWriteRegister0);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1C::ReadWriteRegister1PropertyChanged);
    iReadWriteRegister1 = new PropertyUint("ReadWriteRegister1", functor);
    AddProperty(iReadWriteRegister1);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1C::ReadWriteRegister2PropertyChanged);
    iReadWriteRegister2 = new PropertyUint("ReadWriteRegister2", functor);
    AddProperty(iReadWriteRegister2);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1C::ReadWriteRegister3PropertyChanged);
    iReadWriteRegister3 = new PropertyUint("ReadWriteRegister3", functor);
    AddProperty(iReadWriteRegister3);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1C::ReadOnlyRegister4PropertyChanged);
    iReadOnlyRegister4 = new PropertyUint("ReadOnlyRegister4", functor);
    AddProperty(iReadOnlyRegister4);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1C::ReadOnlyRegister5PropertyChanged);
    iReadOnlyRegister5 = new PropertyUint("ReadOnlyRegister5", functor);
    AddProperty(iReadOnlyRegister5);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1C::ReadOnlyRegister6PropertyChanged);
    iReadOnlyRegister6 = new PropertyUint("ReadOnlyRegister6", functor);
    AddProperty(iReadOnlyRegister6);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1C::ReadOnlyRegister7PropertyChanged);
    iReadOnlyRegister7 = new PropertyUint("ReadOnlyRegister7", functor);
    AddProperty(iReadOnlyRegister7);
}

CpProxyZappOrgTestWidget1C::~CpProxyZappOrgTestWidget1C()
{
    DestroyService();
    delete iActionSetReadWriteRegister;
    delete iActionGetWidgetClass;
}

void CpProxyZappOrgTestWidget1C::SyncSetReadWriteRegister(TUint aRegisterIndex, TUint aRegisterValue)
{
    SyncSetReadWriteRegisterZappOrgTestWidget1C sync(*this);
    BeginSetReadWriteRegister(aRegisterIndex, aRegisterValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidget1C::BeginSetReadWriteRegister(TUint aRegisterIndex, TUint aRegisterValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetReadWriteRegister, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetReadWriteRegister->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidget1C::EndSetReadWriteRegister(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetReadWriteRegister"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestWidget1C::SyncGetWidgetClass(TUint& aWidgetClass)
{
    SyncGetWidgetClassZappOrgTestWidget1C sync(*this, aWidgetClass);
    BeginGetWidgetClass(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidget1C::BeginGetWidgetClass(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetWidgetClass, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetWidgetClass->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidget1C::EndGetWidgetClass(IAsync& aAsync, TUint& aWidgetClass)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetWidgetClass"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aWidgetClass = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyZappOrgTestWidget1C::SetPropertyReadWriteRegister0Changed(Functor& aFunctor)
{
    iLock.Wait();
    iReadWriteRegister0Changed = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestWidget1C::SetPropertyReadWriteRegister1Changed(Functor& aFunctor)
{
    iLock.Wait();
    iReadWriteRegister1Changed = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestWidget1C::SetPropertyReadWriteRegister2Changed(Functor& aFunctor)
{
    iLock.Wait();
    iReadWriteRegister2Changed = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestWidget1C::SetPropertyReadWriteRegister3Changed(Functor& aFunctor)
{
    iLock.Wait();
    iReadWriteRegister3Changed = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestWidget1C::SetPropertyReadOnlyRegister4Changed(Functor& aFunctor)
{
    iLock.Wait();
    iReadOnlyRegister4Changed = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestWidget1C::SetPropertyReadOnlyRegister5Changed(Functor& aFunctor)
{
    iLock.Wait();
    iReadOnlyRegister5Changed = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestWidget1C::SetPropertyReadOnlyRegister6Changed(Functor& aFunctor)
{
    iLock.Wait();
    iReadOnlyRegister6Changed = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestWidget1C::SetPropertyReadOnlyRegister7Changed(Functor& aFunctor)
{
    iLock.Wait();
    iReadOnlyRegister7Changed = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestWidget1C::PropertyReadWriteRegister0(TUint& aReadWriteRegister0) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aReadWriteRegister0 = iReadWriteRegister0->Value();
    iPropertyLock.Signal();
}

void CpProxyZappOrgTestWidget1C::PropertyReadWriteRegister1(TUint& aReadWriteRegister1) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aReadWriteRegister1 = iReadWriteRegister1->Value();
    iPropertyLock.Signal();
}

void CpProxyZappOrgTestWidget1C::PropertyReadWriteRegister2(TUint& aReadWriteRegister2) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aReadWriteRegister2 = iReadWriteRegister2->Value();
    iPropertyLock.Signal();
}

void CpProxyZappOrgTestWidget1C::PropertyReadWriteRegister3(TUint& aReadWriteRegister3) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aReadWriteRegister3 = iReadWriteRegister3->Value();
    iPropertyLock.Signal();
}

void CpProxyZappOrgTestWidget1C::PropertyReadOnlyRegister4(TUint& aReadOnlyRegister4) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aReadOnlyRegister4 = iReadOnlyRegister4->Value();
    iPropertyLock.Signal();
}

void CpProxyZappOrgTestWidget1C::PropertyReadOnlyRegister5(TUint& aReadOnlyRegister5) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aReadOnlyRegister5 = iReadOnlyRegister5->Value();
    iPropertyLock.Signal();
}

void CpProxyZappOrgTestWidget1C::PropertyReadOnlyRegister6(TUint& aReadOnlyRegister6) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aReadOnlyRegister6 = iReadOnlyRegister6->Value();
    iPropertyLock.Signal();
}

void CpProxyZappOrgTestWidget1C::PropertyReadOnlyRegister7(TUint& aReadOnlyRegister7) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aReadOnlyRegister7 = iReadOnlyRegister7->Value();
    iPropertyLock.Signal();
}

void CpProxyZappOrgTestWidget1C::ReadWriteRegister0PropertyChanged()
{
    ReportEvent(iReadWriteRegister0Changed);
}

void CpProxyZappOrgTestWidget1C::ReadWriteRegister1PropertyChanged()
{
    ReportEvent(iReadWriteRegister1Changed);
}

void CpProxyZappOrgTestWidget1C::ReadWriteRegister2PropertyChanged()
{
    ReportEvent(iReadWriteRegister2Changed);
}

void CpProxyZappOrgTestWidget1C::ReadWriteRegister3PropertyChanged()
{
    ReportEvent(iReadWriteRegister3Changed);
}

void CpProxyZappOrgTestWidget1C::ReadOnlyRegister4PropertyChanged()
{
    ReportEvent(iReadOnlyRegister4Changed);
}

void CpProxyZappOrgTestWidget1C::ReadOnlyRegister5PropertyChanged()
{
    ReportEvent(iReadOnlyRegister5Changed);
}

void CpProxyZappOrgTestWidget1C::ReadOnlyRegister6PropertyChanged()
{
    ReportEvent(iReadOnlyRegister6Changed);
}

void CpProxyZappOrgTestWidget1C::ReadOnlyRegister7PropertyChanged()
{
    ReportEvent(iReadOnlyRegister7Changed);
}


THandle CpProxyZappOrgTestWidget1Create(CpDeviceC aDevice)
{
    return new CpProxyZappOrgTestWidget1C(aDevice);
}

void CpProxyZappOrgTestWidget1Destroy(THandle aHandle)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    delete proxyC;
}

void CpProxyZappOrgTestWidget1SyncSetReadWriteRegister(THandle aHandle, uint32_t aRegisterIndex, uint32_t aRegisterValue)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetReadWriteRegister(aRegisterIndex, aRegisterValue);
}

void CpProxyZappOrgTestWidget1BeginSetReadWriteRegister(THandle aHandle, uint32_t aRegisterIndex, uint32_t aRegisterValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetReadWriteRegister(aRegisterIndex, aRegisterValue, functor);
}

int32_t CpProxyZappOrgTestWidget1EndSetReadWriteRegister(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetReadWriteRegister(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestWidget1SyncGetWidgetClass(THandle aHandle, uint32_t* aWidgetClass)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetWidgetClass(*aWidgetClass);
}

void CpProxyZappOrgTestWidget1BeginGetWidgetClass(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetWidgetClass(functor);
}

int32_t CpProxyZappOrgTestWidget1EndGetWidgetClass(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aWidgetClass)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetWidgetClass(*async, *aWidgetClass);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister0Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyReadWriteRegister0Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister1Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyReadWriteRegister1Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister2Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyReadWriteRegister2Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister3Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyReadWriteRegister3Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister4Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyReadOnlyRegister4Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister5Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyReadOnlyRegister5Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister6Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyReadOnlyRegister6Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister7Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyReadOnlyRegister7Changed(functor);
}

void CpProxyZappOrgTestWidget1PropertyReadWriteRegister0(THandle aHandle, uint32_t* aReadWriteRegister0)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyReadWriteRegister0(*aReadWriteRegister0);
}

void CpProxyZappOrgTestWidget1PropertyReadWriteRegister1(THandle aHandle, uint32_t* aReadWriteRegister1)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyReadWriteRegister1(*aReadWriteRegister1);
}

void CpProxyZappOrgTestWidget1PropertyReadWriteRegister2(THandle aHandle, uint32_t* aReadWriteRegister2)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyReadWriteRegister2(*aReadWriteRegister2);
}

void CpProxyZappOrgTestWidget1PropertyReadWriteRegister3(THandle aHandle, uint32_t* aReadWriteRegister3)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyReadWriteRegister3(*aReadWriteRegister3);
}

void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister4(THandle aHandle, uint32_t* aReadOnlyRegister4)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyReadOnlyRegister4(*aReadOnlyRegister4);
}

void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister5(THandle aHandle, uint32_t* aReadOnlyRegister5)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyReadOnlyRegister5(*aReadOnlyRegister5);
}

void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister6(THandle aHandle, uint32_t* aReadOnlyRegister6)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyReadOnlyRegister6(*aReadOnlyRegister6);
}

void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister7(THandle aHandle, uint32_t* aReadOnlyRegister7)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyReadOnlyRegister7(*aReadOnlyRegister7);
}

