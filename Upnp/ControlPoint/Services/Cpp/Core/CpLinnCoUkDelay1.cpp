#include <Core/CpLinnCoUkDelay1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncPresetXmlLinnCoUkDelay1 : public SyncProxyAction
{
public:
    SyncPresetXmlLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService, Brh& aaPresetXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1& iService;
    Brh& iaPresetXml;
};

SyncPresetXmlLinnCoUkDelay1::SyncPresetXmlLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService, Brh& aaPresetXml)
    : iService(aService)
    , iaPresetXml(aaPresetXml)
{
}

void SyncPresetXmlLinnCoUkDelay1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetXml(aAsync, iaPresetXml);
}


class SyncPresetIndexLinnCoUkDelay1 : public SyncProxyAction
{
public:
    SyncPresetIndexLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService, TUint& aaIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1& iService;
    TUint& iaIndex;
};

SyncPresetIndexLinnCoUkDelay1::SyncPresetIndexLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService, TUint& aaIndex)
    : iService(aService)
    , iaIndex(aaIndex)
{
}

void SyncPresetIndexLinnCoUkDelay1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetIndex(aAsync, iaIndex);
}


class SyncSetPresetIndexLinnCoUkDelay1 : public SyncProxyAction
{
public:
    SyncSetPresetIndexLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1& iService;
};

SyncSetPresetIndexLinnCoUkDelay1::SyncSetPresetIndexLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService)
    : iService(aService)
{
}

void SyncSetPresetIndexLinnCoUkDelay1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetIndex(aAsync);
}


class SyncSetPresetDelayLinnCoUkDelay1 : public SyncProxyAction
{
public:
    SyncSetPresetDelayLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1& iService;
};

SyncSetPresetDelayLinnCoUkDelay1::SyncSetPresetDelayLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService)
    : iService(aService)
{
}

void SyncSetPresetDelayLinnCoUkDelay1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetDelay(aAsync);
}


class SyncSetPresetVisibleLinnCoUkDelay1 : public SyncProxyAction
{
public:
    SyncSetPresetVisibleLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1& iService;
};

SyncSetPresetVisibleLinnCoUkDelay1::SyncSetPresetVisibleLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService)
    : iService(aService)
{
}

void SyncSetPresetVisibleLinnCoUkDelay1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetVisible(aAsync);
}


class SyncSetPresetNameLinnCoUkDelay1 : public SyncProxyAction
{
public:
    SyncSetPresetNameLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1& iService;
};

SyncSetPresetNameLinnCoUkDelay1::SyncSetPresetNameLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService)
    : iService(aService)
{
}

void SyncSetPresetNameLinnCoUkDelay1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetName(aAsync);
}


class SyncDelayMinimumLinnCoUkDelay1 : public SyncProxyAction
{
public:
    SyncDelayMinimumLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService, TUint& aaDelay);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1& iService;
    TUint& iaDelay;
};

SyncDelayMinimumLinnCoUkDelay1::SyncDelayMinimumLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService, TUint& aaDelay)
    : iService(aService)
    , iaDelay(aaDelay)
{
}

void SyncDelayMinimumLinnCoUkDelay1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDelayMinimum(aAsync, iaDelay);
}


class SyncDelayMaximumLinnCoUkDelay1 : public SyncProxyAction
{
public:
    SyncDelayMaximumLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService, TUint& aaDelay);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1& iService;
    TUint& iaDelay;
};

SyncDelayMaximumLinnCoUkDelay1::SyncDelayMaximumLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService, TUint& aaDelay)
    : iService(aService)
    , iaDelay(aaDelay)
{
}

void SyncDelayMaximumLinnCoUkDelay1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDelayMaximum(aAsync, iaDelay);
}


class SyncPresetCountLinnCoUkDelay1 : public SyncProxyAction
{
public:
    SyncPresetCountLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService, TUint& aaCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1& iService;
    TUint& iaCount;
};

SyncPresetCountLinnCoUkDelay1::SyncPresetCountLinnCoUkDelay1(CpProxyLinnCoUkDelay1& aService, TUint& aaCount)
    : iService(aService)
    , iaCount(aaCount)
{
}

void SyncPresetCountLinnCoUkDelay1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetCount(aAsync, iaCount);
}


CpProxyLinnCoUkDelay1::CpProxyLinnCoUkDelay1(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Delay", 1, aDevice.Device());
    Zapp::Parameter* param;

    iActionPresetXml = new Action("PresetXml");
    param = new Zapp::ParameterString("aPresetXml");
    iActionPresetXml->AddOutputParameter(param);

    iActionPresetIndex = new Action("PresetIndex");
    param = new Zapp::ParameterUint("aIndex");
    iActionPresetIndex->AddOutputParameter(param);

    iActionSetPresetIndex = new Action("SetPresetIndex");
    param = new Zapp::ParameterUint("aIndex");
    iActionSetPresetIndex->AddInputParameter(param);

    iActionSetPresetDelay = new Action("SetPresetDelay");
    param = new Zapp::ParameterUint("aIndex");
    iActionSetPresetDelay->AddInputParameter(param);
    param = new Zapp::ParameterUint("aDelay");
    iActionSetPresetDelay->AddInputParameter(param);

    iActionSetPresetVisible = new Action("SetPresetVisible");
    param = new Zapp::ParameterUint("aIndex");
    iActionSetPresetVisible->AddInputParameter(param);
    param = new Zapp::ParameterBool("aVisible");
    iActionSetPresetVisible->AddInputParameter(param);

    iActionSetPresetName = new Action("SetPresetName");
    param = new Zapp::ParameterUint("aIndex");
    iActionSetPresetName->AddInputParameter(param);
    param = new Zapp::ParameterString("aName");
    iActionSetPresetName->AddInputParameter(param);

    iActionDelayMinimum = new Action("DelayMinimum");
    param = new Zapp::ParameterUint("aDelay");
    iActionDelayMinimum->AddOutputParameter(param);

    iActionDelayMaximum = new Action("DelayMaximum");
    param = new Zapp::ParameterUint("aDelay");
    iActionDelayMaximum->AddOutputParameter(param);

    iActionPresetCount = new Action("PresetCount");
    param = new Zapp::ParameterUint("aCount");
    iActionPresetCount->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDelay1::PresetXmlPropertyChanged);
    iPresetXml = new PropertyString("PresetXml", functor);
    iService->AddProperty(iPresetXml);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDelay1::PresetIndexPropertyChanged);
    iPresetIndex = new PropertyUint("PresetIndex", functor);
    iService->AddProperty(iPresetIndex);
}

CpProxyLinnCoUkDelay1::~CpProxyLinnCoUkDelay1()
{
    delete iService;
    delete iActionPresetXml;
    delete iActionPresetIndex;
    delete iActionSetPresetIndex;
    delete iActionSetPresetDelay;
    delete iActionSetPresetVisible;
    delete iActionSetPresetName;
    delete iActionDelayMinimum;
    delete iActionDelayMaximum;
    delete iActionPresetCount;
}

void CpProxyLinnCoUkDelay1::SyncPresetXml(Brh& aaPresetXml)
{
    SyncPresetXmlLinnCoUkDelay1 sync(*this, aaPresetXml);
    BeginPresetXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1::BeginPresetXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPresetXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1::EndPresetXml(IAsync& aAsync, Brh& aaPresetXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PresetXml"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaPresetXml);
}

void CpProxyLinnCoUkDelay1::SyncPresetIndex(TUint& aaIndex)
{
    SyncPresetIndexLinnCoUkDelay1 sync(*this, aaIndex);
    BeginPresetIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1::BeginPresetIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPresetIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1::EndPresetIndex(IAsync& aAsync, TUint& aaIndex)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PresetIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaIndex = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkDelay1::SyncSetPresetIndex(TUint aaIndex)
{
    SyncSetPresetIndexLinnCoUkDelay1 sync(*this);
    BeginSetPresetIndex(aaIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1::BeginSetPresetIndex(TUint aaIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPresetIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1::EndSetPresetIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1::SyncSetPresetDelay(TUint aaIndex, TUint aaDelay)
{
    SyncSetPresetDelayLinnCoUkDelay1 sync(*this);
    BeginSetPresetDelay(aaIndex, aaDelay, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1::BeginSetPresetDelay(TUint aaIndex, TUint aaDelay, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPresetDelay, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetDelay->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaDelay));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1::EndSetPresetDelay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetDelay"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1::SyncSetPresetVisible(TUint aaIndex, TBool aaVisible)
{
    SyncSetPresetVisibleLinnCoUkDelay1 sync(*this);
    BeginSetPresetVisible(aaIndex, aaVisible, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1::BeginSetPresetVisible(TUint aaIndex, TBool aaVisible, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPresetVisible, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetVisible->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaVisible));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1::EndSetPresetVisible(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetVisible"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1::SyncSetPresetName(TUint aaIndex, const Brx& aaName)
{
    SyncSetPresetNameLinnCoUkDelay1 sync(*this);
    BeginSetPresetName(aaIndex, aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1::BeginSetPresetName(TUint aaIndex, const Brx& aaName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPresetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaName));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1::EndSetPresetName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1::SyncDelayMinimum(TUint& aaDelay)
{
    SyncDelayMinimumLinnCoUkDelay1 sync(*this, aaDelay);
    BeginDelayMinimum(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1::BeginDelayMinimum(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDelayMinimum, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDelayMinimum->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1::EndDelayMinimum(IAsync& aAsync, TUint& aaDelay)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DelayMinimum"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaDelay = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkDelay1::SyncDelayMaximum(TUint& aaDelay)
{
    SyncDelayMaximumLinnCoUkDelay1 sync(*this, aaDelay);
    BeginDelayMaximum(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1::BeginDelayMaximum(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDelayMaximum, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDelayMaximum->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1::EndDelayMaximum(IAsync& aAsync, TUint& aaDelay)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DelayMaximum"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaDelay = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkDelay1::SyncPresetCount(TUint& aaCount)
{
    SyncPresetCountLinnCoUkDelay1 sync(*this, aaCount);
    BeginPresetCount(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1::BeginPresetCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPresetCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1::EndPresetCount(IAsync& aAsync, TUint& aaCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PresetCount"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkDelay1::SetPropertyPresetXmlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iPresetXmlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDelay1::SetPropertyPresetIndexChanged(Functor& aFunctor)
{
    iLock->Wait();
    iPresetIndexChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDelay1::PropertyPresetXml(Brhz& aPresetXml) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aPresetXml.Set(iPresetXml->Value());
}

void CpProxyLinnCoUkDelay1::PropertyPresetIndex(TUint& aPresetIndex) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aPresetIndex = iPresetIndex->Value();
}

void CpProxyLinnCoUkDelay1::PresetXmlPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iPresetXmlChanged != NULL) {
        iPresetXmlChanged();
    }
}

void CpProxyLinnCoUkDelay1::PresetIndexPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iPresetIndexChanged != NULL) {
        iPresetIndexChanged();
    }
}

