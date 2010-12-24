#include "CpLinnCoUkDelay1.h"
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

class CpProxyLinnCoUkDelay1C : public CpProxyC
{
public:
    CpProxyLinnCoUkDelay1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkDelay1C();
    //CpProxyLinnCoUkDelay1* Proxy() { return static_cast<CpProxyLinnCoUkDelay1*>(iProxy); }

    void SyncPresetXml(Brh& aaPresetXml);
    void BeginPresetXml(FunctorAsync& aFunctor);
    void EndPresetXml(IAsync& aAsync, Brh& aaPresetXml);

    void SyncPresetIndex(TUint& aaIndex);
    void BeginPresetIndex(FunctorAsync& aFunctor);
    void EndPresetIndex(IAsync& aAsync, TUint& aaIndex);

    void SyncSetPresetIndex(TUint aaIndex);
    void BeginSetPresetIndex(TUint aaIndex, FunctorAsync& aFunctor);
    void EndSetPresetIndex(IAsync& aAsync);

    void SyncSetPresetDelay(TUint aaIndex, TUint aaDelay);
    void BeginSetPresetDelay(TUint aaIndex, TUint aaDelay, FunctorAsync& aFunctor);
    void EndSetPresetDelay(IAsync& aAsync);

    void SyncSetPresetVisible(TUint aaIndex, TBool aaVisible);
    void BeginSetPresetVisible(TUint aaIndex, TBool aaVisible, FunctorAsync& aFunctor);
    void EndSetPresetVisible(IAsync& aAsync);

    void SyncSetPresetName(TUint aaIndex, const Brx& aaName);
    void BeginSetPresetName(TUint aaIndex, const Brx& aaName, FunctorAsync& aFunctor);
    void EndSetPresetName(IAsync& aAsync);

    void SyncDelayMinimum(TUint& aaDelay);
    void BeginDelayMinimum(FunctorAsync& aFunctor);
    void EndDelayMinimum(IAsync& aAsync, TUint& aaDelay);

    void SyncDelayMaximum(TUint& aaDelay);
    void BeginDelayMaximum(FunctorAsync& aFunctor);
    void EndDelayMaximum(IAsync& aAsync, TUint& aaDelay);

    void SyncPresetCount(TUint& aaCount);
    void BeginPresetCount(FunctorAsync& aFunctor);
    void EndPresetCount(IAsync& aAsync, TUint& aaCount);

    void SetPropertyPresetXmlChanged(Functor& aFunctor);
    void SetPropertyPresetIndexChanged(Functor& aFunctor);

    void PropertyPresetXml(Brhz& aPresetXml) const;
    void PropertyPresetIndex(TUint& aPresetIndex) const;
private:
    void PresetXmlPropertyChanged();
    void PresetIndexPropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionPresetXml;
    Action* iActionPresetIndex;
    Action* iActionSetPresetIndex;
    Action* iActionSetPresetDelay;
    Action* iActionSetPresetVisible;
    Action* iActionSetPresetName;
    Action* iActionDelayMinimum;
    Action* iActionDelayMaximum;
    Action* iActionPresetCount;
    PropertyString* iPresetXml;
    PropertyUint* iPresetIndex;
    Functor iPresetXmlChanged;
    Functor iPresetIndexChanged;
};


class SyncPresetXmlLinnCoUkDelay1C : public SyncProxyAction
{
public:
    SyncPresetXmlLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy, Brh& aaPresetXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1C& iService;
    Brh& iaPresetXml;
};

SyncPresetXmlLinnCoUkDelay1C::SyncPresetXmlLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy, Brh& aaPresetXml)
    : iService(aProxy)
    , iaPresetXml(aaPresetXml)
{
}

void SyncPresetXmlLinnCoUkDelay1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetXml(aAsync, iaPresetXml);
}


class SyncPresetIndexLinnCoUkDelay1C : public SyncProxyAction
{
public:
    SyncPresetIndexLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy, TUint& aaIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1C& iService;
    TUint& iaIndex;
};

SyncPresetIndexLinnCoUkDelay1C::SyncPresetIndexLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy, TUint& aaIndex)
    : iService(aProxy)
    , iaIndex(aaIndex)
{
}

void SyncPresetIndexLinnCoUkDelay1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetIndex(aAsync, iaIndex);
}


class SyncSetPresetIndexLinnCoUkDelay1C : public SyncProxyAction
{
public:
    SyncSetPresetIndexLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1C& iService;
};

SyncSetPresetIndexLinnCoUkDelay1C::SyncSetPresetIndexLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetPresetIndexLinnCoUkDelay1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetIndex(aAsync);
}


class SyncSetPresetDelayLinnCoUkDelay1C : public SyncProxyAction
{
public:
    SyncSetPresetDelayLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1C& iService;
};

SyncSetPresetDelayLinnCoUkDelay1C::SyncSetPresetDelayLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetPresetDelayLinnCoUkDelay1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetDelay(aAsync);
}


class SyncSetPresetVisibleLinnCoUkDelay1C : public SyncProxyAction
{
public:
    SyncSetPresetVisibleLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1C& iService;
};

SyncSetPresetVisibleLinnCoUkDelay1C::SyncSetPresetVisibleLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetPresetVisibleLinnCoUkDelay1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetVisible(aAsync);
}


class SyncSetPresetNameLinnCoUkDelay1C : public SyncProxyAction
{
public:
    SyncSetPresetNameLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1C& iService;
};

SyncSetPresetNameLinnCoUkDelay1C::SyncSetPresetNameLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetPresetNameLinnCoUkDelay1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetName(aAsync);
}


class SyncDelayMinimumLinnCoUkDelay1C : public SyncProxyAction
{
public:
    SyncDelayMinimumLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy, TUint& aaDelay);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1C& iService;
    TUint& iaDelay;
};

SyncDelayMinimumLinnCoUkDelay1C::SyncDelayMinimumLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy, TUint& aaDelay)
    : iService(aProxy)
    , iaDelay(aaDelay)
{
}

void SyncDelayMinimumLinnCoUkDelay1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDelayMinimum(aAsync, iaDelay);
}


class SyncDelayMaximumLinnCoUkDelay1C : public SyncProxyAction
{
public:
    SyncDelayMaximumLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy, TUint& aaDelay);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1C& iService;
    TUint& iaDelay;
};

SyncDelayMaximumLinnCoUkDelay1C::SyncDelayMaximumLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy, TUint& aaDelay)
    : iService(aProxy)
    , iaDelay(aaDelay)
{
}

void SyncDelayMaximumLinnCoUkDelay1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDelayMaximum(aAsync, iaDelay);
}


class SyncPresetCountLinnCoUkDelay1C : public SyncProxyAction
{
public:
    SyncPresetCountLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy, TUint& aaCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1C& iService;
    TUint& iaCount;
};

SyncPresetCountLinnCoUkDelay1C::SyncPresetCountLinnCoUkDelay1C(CpProxyLinnCoUkDelay1C& aProxy, TUint& aaCount)
    : iService(aProxy)
    , iaCount(aaCount)
{
}

void SyncPresetCountLinnCoUkDelay1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetCount(aAsync, iaCount);
}

CpProxyLinnCoUkDelay1C::CpProxyLinnCoUkDelay1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Delay", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDelay1C::PresetXmlPropertyChanged);
    iPresetXml = new PropertyString("PresetXml", functor);
    AddProperty(iPresetXml);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDelay1C::PresetIndexPropertyChanged);
    iPresetIndex = new PropertyUint("PresetIndex", functor);
    AddProperty(iPresetIndex);
}

CpProxyLinnCoUkDelay1C::~CpProxyLinnCoUkDelay1C()
{
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

void CpProxyLinnCoUkDelay1C::SyncPresetXml(Brh& aaPresetXml)
{
    SyncPresetXmlLinnCoUkDelay1C sync(*this, aaPresetXml);
    BeginPresetXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1C::BeginPresetXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPresetXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDelay1C::EndPresetXml(IAsync& aAsync, Brh& aaPresetXml)
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

void CpProxyLinnCoUkDelay1C::SyncPresetIndex(TUint& aaIndex)
{
    SyncPresetIndexLinnCoUkDelay1C sync(*this, aaIndex);
    BeginPresetIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1C::BeginPresetIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPresetIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDelay1C::EndPresetIndex(IAsync& aAsync, TUint& aaIndex)
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

void CpProxyLinnCoUkDelay1C::SyncSetPresetIndex(TUint aaIndex)
{
    SyncSetPresetIndexLinnCoUkDelay1C sync(*this);
    BeginSetPresetIndex(aaIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1C::BeginSetPresetIndex(TUint aaIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetPresetIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDelay1C::EndSetPresetIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1C::SyncSetPresetDelay(TUint aaIndex, TUint aaDelay)
{
    SyncSetPresetDelayLinnCoUkDelay1C sync(*this);
    BeginSetPresetDelay(aaIndex, aaDelay, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1C::BeginSetPresetDelay(TUint aaIndex, TUint aaDelay, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetPresetDelay, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetDelay->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaDelay));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDelay1C::EndSetPresetDelay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetDelay"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1C::SyncSetPresetVisible(TUint aaIndex, TBool aaVisible)
{
    SyncSetPresetVisibleLinnCoUkDelay1C sync(*this);
    BeginSetPresetVisible(aaIndex, aaVisible, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1C::BeginSetPresetVisible(TUint aaIndex, TBool aaVisible, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetPresetVisible, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetVisible->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaVisible));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDelay1C::EndSetPresetVisible(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetVisible"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1C::SyncSetPresetName(TUint aaIndex, const Brx& aaName)
{
    SyncSetPresetNameLinnCoUkDelay1C sync(*this);
    BeginSetPresetName(aaIndex, aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1C::BeginSetPresetName(TUint aaIndex, const Brx& aaName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetPresetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDelay1C::EndSetPresetName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1C::SyncDelayMinimum(TUint& aaDelay)
{
    SyncDelayMinimumLinnCoUkDelay1C sync(*this, aaDelay);
    BeginDelayMinimum(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1C::BeginDelayMinimum(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDelayMinimum, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDelayMinimum->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDelay1C::EndDelayMinimum(IAsync& aAsync, TUint& aaDelay)
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

void CpProxyLinnCoUkDelay1C::SyncDelayMaximum(TUint& aaDelay)
{
    SyncDelayMaximumLinnCoUkDelay1C sync(*this, aaDelay);
    BeginDelayMaximum(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1C::BeginDelayMaximum(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDelayMaximum, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDelayMaximum->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDelay1C::EndDelayMaximum(IAsync& aAsync, TUint& aaDelay)
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

void CpProxyLinnCoUkDelay1C::SyncPresetCount(TUint& aaCount)
{
    SyncPresetCountLinnCoUkDelay1C sync(*this, aaCount);
    BeginPresetCount(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1C::BeginPresetCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPresetCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDelay1C::EndPresetCount(IAsync& aAsync, TUint& aaCount)
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

void CpProxyLinnCoUkDelay1C::SetPropertyPresetXmlChanged(Functor& aFunctor)
{
    iLock.Wait();
    iPresetXmlChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDelay1C::SetPropertyPresetIndexChanged(Functor& aFunctor)
{
    iLock.Wait();
    iPresetIndexChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDelay1C::PropertyPresetXml(Brhz& aPresetXml) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aPresetXml.Set(iPresetXml->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkDelay1C::PropertyPresetIndex(TUint& aPresetIndex) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aPresetIndex = iPresetIndex->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkDelay1C::PresetXmlPropertyChanged()
{
    ReportEvent(iPresetXmlChanged);
}

void CpProxyLinnCoUkDelay1C::PresetIndexPropertyChanged()
{
    ReportEvent(iPresetIndexChanged);
}


THandle CpProxyLinnCoUkDelay1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkDelay1C(aDevice);
}

void CpProxyLinnCoUkDelay1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkDelay1SyncPresetXml(THandle aHandle, char** aaPresetXml)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaPresetXml;
    proxyC->SyncPresetXml(buf_aaPresetXml);
    *aaPresetXml = buf_aaPresetXml.Extract();
}

void CpProxyLinnCoUkDelay1BeginPresetXml(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginPresetXml(functor);
}

int32_t CpProxyLinnCoUkDelay1EndPresetXml(THandle aHandle, ZappHandleAsync aAsync, char** aaPresetXml)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaPresetXml;
    *aaPresetXml = NULL;
    try {
        proxyC->EndPresetXml(*async, buf_aaPresetXml);
        *aaPresetXml = buf_aaPresetXml.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncPresetIndex(THandle aHandle, uint32_t* aaIndex)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncPresetIndex(*aaIndex);
}

void CpProxyLinnCoUkDelay1BeginPresetIndex(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginPresetIndex(functor);
}

int32_t CpProxyLinnCoUkDelay1EndPresetIndex(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIndex)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPresetIndex(*async, *aaIndex);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncSetPresetIndex(THandle aHandle, uint32_t aaIndex)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetPresetIndex(aaIndex);
}

void CpProxyLinnCoUkDelay1BeginSetPresetIndex(THandle aHandle, uint32_t aaIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetPresetIndex(aaIndex, functor);
}

int32_t CpProxyLinnCoUkDelay1EndSetPresetIndex(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetPresetIndex(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncSetPresetDelay(THandle aHandle, uint32_t aaIndex, uint32_t aaDelay)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetPresetDelay(aaIndex, aaDelay);
}

void CpProxyLinnCoUkDelay1BeginSetPresetDelay(THandle aHandle, uint32_t aaIndex, uint32_t aaDelay, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetPresetDelay(aaIndex, aaDelay, functor);
}

int32_t CpProxyLinnCoUkDelay1EndSetPresetDelay(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetPresetDelay(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncSetPresetVisible(THandle aHandle, uint32_t aaIndex, uint32_t aaVisible)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetPresetVisible(aaIndex, (aaVisible==0? false : true));
}

void CpProxyLinnCoUkDelay1BeginSetPresetVisible(THandle aHandle, uint32_t aaIndex, uint32_t aaVisible, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetPresetVisible(aaIndex, (aaVisible==0? false : true), functor);
}

int32_t CpProxyLinnCoUkDelay1EndSetPresetVisible(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetPresetVisible(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncSetPresetName(THandle aHandle, uint32_t aaIndex, const char* aaName)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    proxyC->SyncSetPresetName(aaIndex, buf_aaName);
}

void CpProxyLinnCoUkDelay1BeginSetPresetName(THandle aHandle, uint32_t aaIndex, const char* aaName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetPresetName(aaIndex, buf_aaName, functor);
}

int32_t CpProxyLinnCoUkDelay1EndSetPresetName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetPresetName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncDelayMinimum(THandle aHandle, uint32_t* aaDelay)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDelayMinimum(*aaDelay);
}

void CpProxyLinnCoUkDelay1BeginDelayMinimum(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDelayMinimum(functor);
}

int32_t CpProxyLinnCoUkDelay1EndDelayMinimum(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaDelay)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDelayMinimum(*async, *aaDelay);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncDelayMaximum(THandle aHandle, uint32_t* aaDelay)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDelayMaximum(*aaDelay);
}

void CpProxyLinnCoUkDelay1BeginDelayMaximum(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDelayMaximum(functor);
}

int32_t CpProxyLinnCoUkDelay1EndDelayMaximum(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaDelay)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDelayMaximum(*async, *aaDelay);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncPresetCount(THandle aHandle, uint32_t* aaCount)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncPresetCount(*aaCount);
}

void CpProxyLinnCoUkDelay1BeginPresetCount(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginPresetCount(functor);
}

int32_t CpProxyLinnCoUkDelay1EndPresetCount(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaCount)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPresetCount(*async, *aaCount);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SetPropertyPresetXmlChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyPresetXmlChanged(functor);
}

void CpProxyLinnCoUkDelay1SetPropertyPresetIndexChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyPresetIndexChanged(functor);
}

void CpProxyLinnCoUkDelay1PropertyPresetXml(THandle aHandle, char** aPresetXml)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aPresetXml;
    proxyC->PropertyPresetXml(buf_aPresetXml);
    *aPresetXml = buf_aPresetXml.Transfer();
}

void CpProxyLinnCoUkDelay1PropertyPresetIndex(THandle aHandle, uint32_t* aPresetIndex)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyPresetIndex(*aPresetIndex);
}

