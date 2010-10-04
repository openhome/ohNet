#include <Std/CpLinnCoUkDelay1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncPresetXmlLinnCoUkDelay1Cpp : public SyncProxyAction
{
public:
    SyncPresetXmlLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService, std::string& aaPresetXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1Cpp& iService;
    std::string& iaPresetXml;
};

SyncPresetXmlLinnCoUkDelay1Cpp::SyncPresetXmlLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService, std::string& aaPresetXml)
    : iService(aService)
    , iaPresetXml(aaPresetXml)
{
}

void SyncPresetXmlLinnCoUkDelay1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetXml(aAsync, iaPresetXml);
}


class SyncPresetIndexLinnCoUkDelay1Cpp : public SyncProxyAction
{
public:
    SyncPresetIndexLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService, uint32_t& aaIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1Cpp& iService;
    uint32_t& iaIndex;
};

SyncPresetIndexLinnCoUkDelay1Cpp::SyncPresetIndexLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService, uint32_t& aaIndex)
    : iService(aService)
    , iaIndex(aaIndex)
{
}

void SyncPresetIndexLinnCoUkDelay1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetIndex(aAsync, iaIndex);
}


class SyncSetPresetIndexLinnCoUkDelay1Cpp : public SyncProxyAction
{
public:
    SyncSetPresetIndexLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1Cpp& iService;
};

SyncSetPresetIndexLinnCoUkDelay1Cpp::SyncSetPresetIndexLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService)
    : iService(aService)
{
}

void SyncSetPresetIndexLinnCoUkDelay1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetIndex(aAsync);
}


class SyncSetPresetDelayLinnCoUkDelay1Cpp : public SyncProxyAction
{
public:
    SyncSetPresetDelayLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1Cpp& iService;
};

SyncSetPresetDelayLinnCoUkDelay1Cpp::SyncSetPresetDelayLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService)
    : iService(aService)
{
}

void SyncSetPresetDelayLinnCoUkDelay1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetDelay(aAsync);
}


class SyncSetPresetVisibleLinnCoUkDelay1Cpp : public SyncProxyAction
{
public:
    SyncSetPresetVisibleLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1Cpp& iService;
};

SyncSetPresetVisibleLinnCoUkDelay1Cpp::SyncSetPresetVisibleLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService)
    : iService(aService)
{
}

void SyncSetPresetVisibleLinnCoUkDelay1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetVisible(aAsync);
}


class SyncSetPresetNameLinnCoUkDelay1Cpp : public SyncProxyAction
{
public:
    SyncSetPresetNameLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1Cpp& iService;
};

SyncSetPresetNameLinnCoUkDelay1Cpp::SyncSetPresetNameLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService)
    : iService(aService)
{
}

void SyncSetPresetNameLinnCoUkDelay1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetName(aAsync);
}


class SyncDelayMinimumLinnCoUkDelay1Cpp : public SyncProxyAction
{
public:
    SyncDelayMinimumLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService, uint32_t& aaDelay);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1Cpp& iService;
    uint32_t& iaDelay;
};

SyncDelayMinimumLinnCoUkDelay1Cpp::SyncDelayMinimumLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService, uint32_t& aaDelay)
    : iService(aService)
    , iaDelay(aaDelay)
{
}

void SyncDelayMinimumLinnCoUkDelay1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDelayMinimum(aAsync, iaDelay);
}


class SyncDelayMaximumLinnCoUkDelay1Cpp : public SyncProxyAction
{
public:
    SyncDelayMaximumLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService, uint32_t& aaDelay);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1Cpp& iService;
    uint32_t& iaDelay;
};

SyncDelayMaximumLinnCoUkDelay1Cpp::SyncDelayMaximumLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService, uint32_t& aaDelay)
    : iService(aService)
    , iaDelay(aaDelay)
{
}

void SyncDelayMaximumLinnCoUkDelay1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDelayMaximum(aAsync, iaDelay);
}


class SyncPresetCountLinnCoUkDelay1Cpp : public SyncProxyAction
{
public:
    SyncPresetCountLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService, uint32_t& aaCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDelay1Cpp& iService;
    uint32_t& iaCount;
};

SyncPresetCountLinnCoUkDelay1Cpp::SyncPresetCountLinnCoUkDelay1Cpp(CpProxyLinnCoUkDelay1Cpp& aService, uint32_t& aaCount)
    : iService(aService)
    , iaCount(aaCount)
{
}

void SyncPresetCountLinnCoUkDelay1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetCount(aAsync, iaCount);
}


CpProxyLinnCoUkDelay1Cpp::CpProxyLinnCoUkDelay1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDelay1Cpp::PresetXmlPropertyChanged);
    iPresetXml = new PropertyString("PresetXml", functor);
    iService->AddProperty(iPresetXml);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDelay1Cpp::PresetIndexPropertyChanged);
    iPresetIndex = new PropertyUint("PresetIndex", functor);
    iService->AddProperty(iPresetIndex);
}

CpProxyLinnCoUkDelay1Cpp::~CpProxyLinnCoUkDelay1Cpp()
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

void CpProxyLinnCoUkDelay1Cpp::SyncPresetXml(std::string& aaPresetXml)
{
    SyncPresetXmlLinnCoUkDelay1Cpp sync(*this, aaPresetXml);
    BeginPresetXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1Cpp::BeginPresetXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPresetXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1Cpp::EndPresetXml(IAsync& aAsync, std::string& aaPresetXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PresetXml"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaPresetXml.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkDelay1Cpp::SyncPresetIndex(uint32_t& aaIndex)
{
    SyncPresetIndexLinnCoUkDelay1Cpp sync(*this, aaIndex);
    BeginPresetIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1Cpp::BeginPresetIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPresetIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1Cpp::EndPresetIndex(IAsync& aAsync, uint32_t& aaIndex)
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

void CpProxyLinnCoUkDelay1Cpp::SyncSetPresetIndex(uint32_t aaIndex)
{
    SyncSetPresetIndexLinnCoUkDelay1Cpp sync(*this);
    BeginSetPresetIndex(aaIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1Cpp::BeginSetPresetIndex(uint32_t aaIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPresetIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1Cpp::EndSetPresetIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1Cpp::SyncSetPresetDelay(uint32_t aaIndex, uint32_t aaDelay)
{
    SyncSetPresetDelayLinnCoUkDelay1Cpp sync(*this);
    BeginSetPresetDelay(aaIndex, aaDelay, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1Cpp::BeginSetPresetDelay(uint32_t aaIndex, uint32_t aaDelay, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPresetDelay, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetDelay->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaDelay));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1Cpp::EndSetPresetDelay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetDelay"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1Cpp::SyncSetPresetVisible(uint32_t aaIndex, bool aaVisible)
{
    SyncSetPresetVisibleLinnCoUkDelay1Cpp sync(*this);
    BeginSetPresetVisible(aaIndex, aaVisible, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1Cpp::BeginSetPresetVisible(uint32_t aaIndex, bool aaVisible, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPresetVisible, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetVisible->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaVisible));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1Cpp::EndSetPresetVisible(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetVisible"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1Cpp::SyncSetPresetName(uint32_t aaIndex, const std::string& aaName)
{
    SyncSetPresetNameLinnCoUkDelay1Cpp sync(*this);
    BeginSetPresetName(aaIndex, aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1Cpp::BeginSetPresetName(uint32_t aaIndex, const std::string& aaName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPresetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIndex));
    {
        Brn buf((const TByte*)aaName.c_str(), aaName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1Cpp::EndSetPresetName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDelay1Cpp::SyncDelayMinimum(uint32_t& aaDelay)
{
    SyncDelayMinimumLinnCoUkDelay1Cpp sync(*this, aaDelay);
    BeginDelayMinimum(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1Cpp::BeginDelayMinimum(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDelayMinimum, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDelayMinimum->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1Cpp::EndDelayMinimum(IAsync& aAsync, uint32_t& aaDelay)
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

void CpProxyLinnCoUkDelay1Cpp::SyncDelayMaximum(uint32_t& aaDelay)
{
    SyncDelayMaximumLinnCoUkDelay1Cpp sync(*this, aaDelay);
    BeginDelayMaximum(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1Cpp::BeginDelayMaximum(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDelayMaximum, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDelayMaximum->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1Cpp::EndDelayMaximum(IAsync& aAsync, uint32_t& aaDelay)
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

void CpProxyLinnCoUkDelay1Cpp::SyncPresetCount(uint32_t& aaCount)
{
    SyncPresetCountLinnCoUkDelay1Cpp sync(*this, aaCount);
    BeginPresetCount(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDelay1Cpp::BeginPresetCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPresetCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDelay1Cpp::EndPresetCount(IAsync& aAsync, uint32_t& aaCount)
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

void CpProxyLinnCoUkDelay1Cpp::SetPropertyPresetXmlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iPresetXmlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDelay1Cpp::SetPropertyPresetIndexChanged(Functor& aFunctor)
{
    iLock->Wait();
    iPresetIndexChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDelay1Cpp::PropertyPresetXml(std::string& aPresetXml) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iPresetXml->Value();
    aPresetXml.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkDelay1Cpp::PropertyPresetIndex(uint32_t& aPresetIndex) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aPresetIndex = iPresetIndex->Value();
}

void CpProxyLinnCoUkDelay1Cpp::PresetXmlPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iPresetXmlChanged != NULL) {
        iPresetXmlChanged();
    }
}

void CpProxyLinnCoUkDelay1Cpp::PresetIndexPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iPresetIndexChanged != NULL) {
        iPresetIndexChanged();
    }
}

