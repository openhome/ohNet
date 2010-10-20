#include <Core/CpZappOrgTestWidget1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncSetReadWriteRegisterZappOrgTestWidget1 : public SyncProxyAction
{
public:
    SyncSetReadWriteRegisterZappOrgTestWidget1(CpProxyZappOrgTestWidget1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestWidget1& iService;
};

SyncSetReadWriteRegisterZappOrgTestWidget1::SyncSetReadWriteRegisterZappOrgTestWidget1(CpProxyZappOrgTestWidget1& aService)
    : iService(aService)
{
}

void SyncSetReadWriteRegisterZappOrgTestWidget1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetReadWriteRegister(aAsync);
}


CpProxyZappOrgTestWidget1::CpProxyZappOrgTestWidget1(CpDevice& aDevice)
    : CpProxy("zapp-org", "TestWidget", 1, aDevice.Device())
{
    Zapp::Parameter* param;

    iActionSetReadWriteRegister = new Action("SetReadWriteRegister");
    param = new Zapp::ParameterUint("RegisterIndex");
    iActionSetReadWriteRegister->AddInputParameter(param);
    param = new Zapp::ParameterUint("RegisterValue");
    iActionSetReadWriteRegister->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1::ReadWriteRegister0PropertyChanged);
    iReadWriteRegister0 = new PropertyUint("ReadWriteRegister0", functor);
    iService->AddProperty(iReadWriteRegister0);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1::ReadWriteRegister1PropertyChanged);
    iReadWriteRegister1 = new PropertyUint("ReadWriteRegister1", functor);
    iService->AddProperty(iReadWriteRegister1);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1::ReadWriteRegister2PropertyChanged);
    iReadWriteRegister2 = new PropertyUint("ReadWriteRegister2", functor);
    iService->AddProperty(iReadWriteRegister2);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1::ReadWriteRegister3PropertyChanged);
    iReadWriteRegister3 = new PropertyUint("ReadWriteRegister3", functor);
    iService->AddProperty(iReadWriteRegister3);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1::ReadOnlyRegister4PropertyChanged);
    iReadOnlyRegister4 = new PropertyUint("ReadOnlyRegister4", functor);
    iService->AddProperty(iReadOnlyRegister4);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1::ReadOnlyRegister5PropertyChanged);
    iReadOnlyRegister5 = new PropertyUint("ReadOnlyRegister5", functor);
    iService->AddProperty(iReadOnlyRegister5);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1::ReadOnlyRegister6PropertyChanged);
    iReadOnlyRegister6 = new PropertyUint("ReadOnlyRegister6", functor);
    iService->AddProperty(iReadOnlyRegister6);
    functor = MakeFunctor(*this, &CpProxyZappOrgTestWidget1::ReadOnlyRegister7PropertyChanged);
    iReadOnlyRegister7 = new PropertyUint("ReadOnlyRegister7", functor);
    iService->AddProperty(iReadOnlyRegister7);
}

CpProxyZappOrgTestWidget1::~CpProxyZappOrgTestWidget1()
{
    DestroyService();
    delete iActionSetReadWriteRegister;
}

void CpProxyZappOrgTestWidget1::SyncSetReadWriteRegister(TUint aRegisterIndex, TUint aRegisterValue)
{
    SyncSetReadWriteRegisterZappOrgTestWidget1 sync(*this);
    BeginSetReadWriteRegister(aRegisterIndex, aRegisterValue, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestWidget1::BeginSetReadWriteRegister(TUint aRegisterIndex, TUint aRegisterValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetReadWriteRegister, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetReadWriteRegister->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRegisterValue));
    invocation->Invoke();
}

void CpProxyZappOrgTestWidget1::EndSetReadWriteRegister(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetReadWriteRegister"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestWidget1::SetPropertyReadWriteRegister0Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadWriteRegister0Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1::SetPropertyReadWriteRegister1Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadWriteRegister1Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1::SetPropertyReadWriteRegister2Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadWriteRegister2Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1::SetPropertyReadWriteRegister3Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadWriteRegister3Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1::SetPropertyReadOnlyRegister4Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadOnlyRegister4Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1::SetPropertyReadOnlyRegister5Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadOnlyRegister5Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1::SetPropertyReadOnlyRegister6Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadOnlyRegister6Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1::SetPropertyReadOnlyRegister7Changed(Functor& aFunctor)
{
    iLock->Wait();
    iReadOnlyRegister7Changed = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestWidget1::PropertyReadWriteRegister0(TUint& aReadWriteRegister0) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadWriteRegister0 = iReadWriteRegister0->Value();
}

void CpProxyZappOrgTestWidget1::PropertyReadWriteRegister1(TUint& aReadWriteRegister1) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadWriteRegister1 = iReadWriteRegister1->Value();
}

void CpProxyZappOrgTestWidget1::PropertyReadWriteRegister2(TUint& aReadWriteRegister2) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadWriteRegister2 = iReadWriteRegister2->Value();
}

void CpProxyZappOrgTestWidget1::PropertyReadWriteRegister3(TUint& aReadWriteRegister3) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadWriteRegister3 = iReadWriteRegister3->Value();
}

void CpProxyZappOrgTestWidget1::PropertyReadOnlyRegister4(TUint& aReadOnlyRegister4) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadOnlyRegister4 = iReadOnlyRegister4->Value();
}

void CpProxyZappOrgTestWidget1::PropertyReadOnlyRegister5(TUint& aReadOnlyRegister5) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadOnlyRegister5 = iReadOnlyRegister5->Value();
}

void CpProxyZappOrgTestWidget1::PropertyReadOnlyRegister6(TUint& aReadOnlyRegister6) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadOnlyRegister6 = iReadOnlyRegister6->Value();
}

void CpProxyZappOrgTestWidget1::PropertyReadOnlyRegister7(TUint& aReadOnlyRegister7) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReadOnlyRegister7 = iReadOnlyRegister7->Value();
}

void CpProxyZappOrgTestWidget1::ReadWriteRegister0PropertyChanged()
{
    ReportEvent(iReadWriteRegister0Changed);
}

void CpProxyZappOrgTestWidget1::ReadWriteRegister1PropertyChanged()
{
    ReportEvent(iReadWriteRegister1Changed);
}

void CpProxyZappOrgTestWidget1::ReadWriteRegister2PropertyChanged()
{
    ReportEvent(iReadWriteRegister2Changed);
}

void CpProxyZappOrgTestWidget1::ReadWriteRegister3PropertyChanged()
{
    ReportEvent(iReadWriteRegister3Changed);
}

void CpProxyZappOrgTestWidget1::ReadOnlyRegister4PropertyChanged()
{
    ReportEvent(iReadOnlyRegister4Changed);
}

void CpProxyZappOrgTestWidget1::ReadOnlyRegister5PropertyChanged()
{
    ReportEvent(iReadOnlyRegister5Changed);
}

void CpProxyZappOrgTestWidget1::ReadOnlyRegister6PropertyChanged()
{
    ReportEvent(iReadOnlyRegister6Changed);
}

void CpProxyZappOrgTestWidget1::ReadOnlyRegister7PropertyChanged()
{
    ReportEvent(iReadOnlyRegister7Changed);
}

