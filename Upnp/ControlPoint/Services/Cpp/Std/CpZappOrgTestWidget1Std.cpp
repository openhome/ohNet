#include "CpZappOrgTestWidget1.h"
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncSetReadWriteRegisterZappOrgTestWidget1Cpp : public SyncProxyAction
{
public:
    SyncSetReadWriteRegisterZappOrgTestWidget1Cpp(CpProxyZappOrgTestWidget1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidget1Cpp& iService;
};

SyncSetReadWriteRegisterZappOrgTestWidget1Cpp::SyncSetReadWriteRegisterZappOrgTestWidget1Cpp(CpProxyZappOrgTestWidget1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetReadWriteRegisterZappOrgTestWidget1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetReadWriteRegister(aAsync);
}


class SyncGetWidgetClassZappOrgTestWidget1Cpp : public SyncProxyAction
{
public:
    SyncGetWidgetClassZappOrgTestWidget1Cpp(CpProxyZappOrgTestWidget1Cpp& aProxy, uint32_t& aWidgetClass);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidget1Cpp& iService;
    uint32_t& iWidgetClass;
};

SyncGetWidgetClassZappOrgTestWidget1Cpp::SyncGetWidgetClassZappOrgTestWidget1Cpp(CpProxyZappOrgTestWidget1Cpp& aProxy, uint32_t& aWidgetClass)
    : iService(aProxy)
    , iWidgetClass(aWidgetClass)
{
}

void SyncGetWidgetClassZappOrgTestWidget1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetWidgetClass(aAsync, iWidgetClass);
}


CpProxyZappOrgTestWidget1Cpp::CpProxyZappOrgTestWidget1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("zapp-org", "TestWidget", 1, aDevice.Device())
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
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1Cpp::ReadWriteRegister0PropertyChanged);
    iReadWriteRegister0 = new PropertyUint("ReadWriteRegister0", functor);
    AddProperty(iReadWriteRegister0);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1Cpp::ReadWriteRegister1PropertyChanged);
    iReadWriteRegister1 = new PropertyUint("ReadWriteRegister1", functor);
    AddProperty(iReadWriteRegister1);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1Cpp::ReadWriteRegister2PropertyChanged);
    iReadWriteRegister2 = new PropertyUint("ReadWriteRegister2", functor);
    AddProperty(iReadWriteRegister2);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1Cpp::ReadWriteRegister3PropertyChanged);
    iReadWriteRegister3 = new PropertyUint("ReadWriteRegister3", functor);
    AddProperty(iReadWriteRegister3);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1Cpp::ReadOnlyRegister4PropertyChanged);
    iReadOnlyRegister4 = new PropertyUint("ReadOnlyRegister4", functor);
    AddProperty(iReadOnlyRegister4);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1Cpp::ReadOnlyRegister5PropertyChanged);
    iReadOnlyRegister5 = new PropertyUint("ReadOnlyRegister5", functor);
    AddProperty(iReadOnlyRegister5);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1Cpp::ReadOnlyRegister6PropertyChanged);
    iReadOnlyRegister6 = new PropertyUint("ReadOnlyRegister6", functor);
    AddProperty(iReadOnlyRegister6);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1Cpp::ReadOnlyRegister7PropertyChanged);
    iReadOnlyRegister7 = new PropertyUint("ReadOnlyRegister7", functor);
    AddProperty(iReadOnlyRegister7);
}

CpProxyZappOrgTestWidget1Cpp::~CpProxyZappOrgTestWidget1Cpp()
{
    DestroyService();
    delete iActionSetReadWriteRegister;
    delete iActionGetWidgetClass;
}

void CpProxyZappOrgTestWidget1Cpp::SyncSetReadWriteRegister(uint32_t aRegisterIndex, uint32_t aRegisterValue)
{
    SyncSetReadWriteRegisterZappOrgTestWidget1Cpp sync(*this);
    BeginSetReadWriteRegister(aRegisterIndex, aRegisterValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidget1Cpp::BeginSetReadWriteRegister(uint32_t aRegisterIndex, uint32_t aRegisterValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetReadWriteRegister, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetReadWriteRegister->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidget1Cpp::EndSetReadWriteRegister(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetReadWriteRegister"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestWidget1Cpp::SyncGetWidgetClass(uint32_t& aWidgetClass)
{
    SyncGetWidgetClassZappOrgTestWidget1Cpp sync(*this, aWidgetClass);
    BeginGetWidgetClass(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidget1Cpp::BeginGetWidgetClass(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetWidgetClass, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetWidgetClass->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyZappOrgTestWidget1Cpp::EndGetWidgetClass(IAsync& aAsync, uint32_t& aWidgetClass)
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

void CpProxyZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister0Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadWriteRegister0Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister1Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadWriteRegister1Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister2Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadWriteRegister2Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister3Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadWriteRegister3Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister4Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadOnlyRegister4Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister5Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadOnlyRegister5Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister6Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadOnlyRegister6Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister7Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadOnlyRegister7Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::PropertyReadWriteRegister0(uint32_t& aReadWriteRegister0) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadWriteRegister0 = iReadWriteRegister0->Value();
    iPropertyLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::PropertyReadWriteRegister1(uint32_t& aReadWriteRegister1) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadWriteRegister1 = iReadWriteRegister1->Value();
    iPropertyLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::PropertyReadWriteRegister2(uint32_t& aReadWriteRegister2) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadWriteRegister2 = iReadWriteRegister2->Value();
    iPropertyLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::PropertyReadWriteRegister3(uint32_t& aReadWriteRegister3) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadWriteRegister3 = iReadWriteRegister3->Value();
    iPropertyLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::PropertyReadOnlyRegister4(uint32_t& aReadOnlyRegister4) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadOnlyRegister4 = iReadOnlyRegister4->Value();
    iPropertyLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::PropertyReadOnlyRegister5(uint32_t& aReadOnlyRegister5) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadOnlyRegister5 = iReadOnlyRegister5->Value();
    iPropertyLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::PropertyReadOnlyRegister6(uint32_t& aReadOnlyRegister6) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadOnlyRegister6 = iReadOnlyRegister6->Value();
    iPropertyLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::PropertyReadOnlyRegister7(uint32_t& aReadOnlyRegister7) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadOnlyRegister7 = iReadOnlyRegister7->Value();
    iPropertyLock->Signal();
}

void CpProxyZappOrgTestWidget1Cpp::ReadWriteRegister0PropertyChanged()
{
    ReportEvent(iReadWriteRegister0Changed);
}

void CpProxyZappOrgTestWidget1Cpp::ReadWriteRegister1PropertyChanged()
{
    ReportEvent(iReadWriteRegister1Changed);
}

void CpProxyZappOrgTestWidget1Cpp::ReadWriteRegister2PropertyChanged()
{
    ReportEvent(iReadWriteRegister2Changed);
}

void CpProxyZappOrgTestWidget1Cpp::ReadWriteRegister3PropertyChanged()
{
    ReportEvent(iReadWriteRegister3Changed);
}

void CpProxyZappOrgTestWidget1Cpp::ReadOnlyRegister4PropertyChanged()
{
    ReportEvent(iReadOnlyRegister4Changed);
}

void CpProxyZappOrgTestWidget1Cpp::ReadOnlyRegister5PropertyChanged()
{
    ReportEvent(iReadOnlyRegister5Changed);
}

void CpProxyZappOrgTestWidget1Cpp::ReadOnlyRegister6PropertyChanged()
{
    ReportEvent(iReadOnlyRegister6Changed);
}

void CpProxyZappOrgTestWidget1Cpp::ReadOnlyRegister7PropertyChanged()
{
    ReportEvent(iReadOnlyRegister7Changed);
}

