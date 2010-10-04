#include <Core/CpLinnCoUkJukebox1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncSetPresetPrefixLinnCoUkJukebox1 : public SyncProxyAction
{
public:
    SyncSetPresetPrefixLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1& iService;
};

SyncSetPresetPrefixLinnCoUkJukebox1::SyncSetPresetPrefixLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService)
    : iService(aService)
{
}

void SyncSetPresetPrefixLinnCoUkJukebox1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetPrefix(aAsync);
}


class SyncPresetPrefixLinnCoUkJukebox1 : public SyncProxyAction
{
public:
    SyncPresetPrefixLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService, Brh& aaUri);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1& iService;
    Brh& iaUri;
};

SyncPresetPrefixLinnCoUkJukebox1::SyncPresetPrefixLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService, Brh& aaUri)
    : iService(aService)
    , iaUri(aaUri)
{
}

void SyncPresetPrefixLinnCoUkJukebox1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetPrefix(aAsync, iaUri);
}


class SyncSetAlbumArtFileNameLinnCoUkJukebox1 : public SyncProxyAction
{
public:
    SyncSetAlbumArtFileNameLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1& iService;
};

SyncSetAlbumArtFileNameLinnCoUkJukebox1::SyncSetAlbumArtFileNameLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService)
    : iService(aService)
{
}

void SyncSetAlbumArtFileNameLinnCoUkJukebox1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAlbumArtFileName(aAsync);
}


class SyncAlbumArtFileNameLinnCoUkJukebox1 : public SyncProxyAction
{
public:
    SyncAlbumArtFileNameLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService, Brh& aaName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1& iService;
    Brh& iaName;
};

SyncAlbumArtFileNameLinnCoUkJukebox1::SyncAlbumArtFileNameLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService, Brh& aaName)
    : iService(aService)
    , iaName(aaName)
{
}

void SyncAlbumArtFileNameLinnCoUkJukebox1::CompleteRequest(IAsync& aAsync)
{
    iService.EndAlbumArtFileName(aAsync, iaName);
}


class SyncSetCurrentPresetLinnCoUkJukebox1 : public SyncProxyAction
{
public:
    SyncSetCurrentPresetLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1& iService;
};

SyncSetCurrentPresetLinnCoUkJukebox1::SyncSetCurrentPresetLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService)
    : iService(aService)
{
}

void SyncSetCurrentPresetLinnCoUkJukebox1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetCurrentPreset(aAsync);
}


class SyncCurrentPresetLinnCoUkJukebox1 : public SyncProxyAction
{
public:
    SyncCurrentPresetLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService, TUint& aaPreset);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1& iService;
    TUint& iaPreset;
};

SyncCurrentPresetLinnCoUkJukebox1::SyncCurrentPresetLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService, TUint& aaPreset)
    : iService(aService)
    , iaPreset(aaPreset)
{
}

void SyncCurrentPresetLinnCoUkJukebox1::CompleteRequest(IAsync& aAsync)
{
    iService.EndCurrentPreset(aAsync, iaPreset);
}


class SyncPresetMetaDataLinnCoUkJukebox1 : public SyncProxyAction
{
public:
    SyncPresetMetaDataLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService, Brh& aaMetaData);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1& iService;
    Brh& iaMetaData;
};

SyncPresetMetaDataLinnCoUkJukebox1::SyncPresetMetaDataLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService, Brh& aaMetaData)
    : iService(aService)
    , iaMetaData(aaMetaData)
{
}

void SyncPresetMetaDataLinnCoUkJukebox1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetMetaData(aAsync, iaMetaData);
}


class SyncLoadManifestLinnCoUkJukebox1 : public SyncProxyAction
{
public:
    SyncLoadManifestLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService, TUint& aaTotalPresets);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1& iService;
    TUint& iaTotalPresets;
};

SyncLoadManifestLinnCoUkJukebox1::SyncLoadManifestLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1& aService, TUint& aaTotalPresets)
    : iService(aService)
    , iaTotalPresets(aaTotalPresets)
{
}

void SyncLoadManifestLinnCoUkJukebox1::CompleteRequest(IAsync& aAsync)
{
    iService.EndLoadManifest(aAsync, iaTotalPresets);
}


CpProxyLinnCoUkJukebox1::CpProxyLinnCoUkJukebox1(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Jukebox", 1, aDevice.Device());
    Zapp::Parameter* param;

    iActionSetPresetPrefix = new Action("SetPresetPrefix");
    param = new Zapp::ParameterString("aUri");
    iActionSetPresetPrefix->AddInputParameter(param);

    iActionPresetPrefix = new Action("PresetPrefix");
    param = new Zapp::ParameterString("aUri");
    iActionPresetPrefix->AddOutputParameter(param);

    iActionSetAlbumArtFileName = new Action("SetAlbumArtFileName");
    param = new Zapp::ParameterString("aName");
    iActionSetAlbumArtFileName->AddInputParameter(param);

    iActionAlbumArtFileName = new Action("AlbumArtFileName");
    param = new Zapp::ParameterString("aName");
    iActionAlbumArtFileName->AddOutputParameter(param);

    iActionSetCurrentPreset = new Action("SetCurrentPreset");
    param = new Zapp::ParameterUint("aPreset");
    iActionSetCurrentPreset->AddInputParameter(param);

    iActionCurrentPreset = new Action("CurrentPreset");
    param = new Zapp::ParameterUint("aPreset");
    iActionCurrentPreset->AddOutputParameter(param);

    iActionPresetMetaData = new Action("PresetMetaData");
    param = new Zapp::ParameterUint("aPreset");
    iActionPresetMetaData->AddInputParameter(param);
    param = new Zapp::ParameterString("aMetaData");
    iActionPresetMetaData->AddOutputParameter(param);

    iActionLoadManifest = new Action("LoadManifest");
    param = new Zapp::ParameterUint("aTotalPresets");
    iActionLoadManifest->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkJukebox1::CurrentPresetPropertyChanged);
    iCurrentPreset = new PropertyUint("CurrentPreset", functor);
    iService->AddProperty(iCurrentPreset);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkJukebox1::PresetPrefixPropertyChanged);
    iPresetPrefix = new PropertyString("PresetPrefix", functor);
    iService->AddProperty(iPresetPrefix);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkJukebox1::AlbumArtFileNamePropertyChanged);
    iAlbumArtFileName = new PropertyString("AlbumArtFileName", functor);
    iService->AddProperty(iAlbumArtFileName);
}

CpProxyLinnCoUkJukebox1::~CpProxyLinnCoUkJukebox1()
{
    delete iService;
    delete iActionSetPresetPrefix;
    delete iActionPresetPrefix;
    delete iActionSetAlbumArtFileName;
    delete iActionAlbumArtFileName;
    delete iActionSetCurrentPreset;
    delete iActionCurrentPreset;
    delete iActionPresetMetaData;
    delete iActionLoadManifest;
}

void CpProxyLinnCoUkJukebox1::SyncSetPresetPrefix(const Brx& aaUri)
{
    SyncSetPresetPrefixLinnCoUkJukebox1 sync(*this);
    BeginSetPresetPrefix(aaUri, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1::BeginSetPresetPrefix(const Brx& aaUri, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPresetPrefix, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetPrefix->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaUri));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1::EndSetPresetPrefix(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetPrefix"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkJukebox1::SyncPresetPrefix(Brh& aaUri)
{
    SyncPresetPrefixLinnCoUkJukebox1 sync(*this, aaUri);
    BeginPresetPrefix(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1::BeginPresetPrefix(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPresetPrefix, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetPrefix->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1::EndPresetPrefix(IAsync& aAsync, Brh& aaUri)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PresetPrefix"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaUri);
}

void CpProxyLinnCoUkJukebox1::SyncSetAlbumArtFileName(const Brx& aaName)
{
    SyncSetAlbumArtFileNameLinnCoUkJukebox1 sync(*this);
    BeginSetAlbumArtFileName(aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1::BeginSetAlbumArtFileName(const Brx& aaName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetAlbumArtFileName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAlbumArtFileName->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaName));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1::EndSetAlbumArtFileName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAlbumArtFileName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkJukebox1::SyncAlbumArtFileName(Brh& aaName)
{
    SyncAlbumArtFileNameLinnCoUkJukebox1 sync(*this, aaName);
    BeginAlbumArtFileName(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1::BeginAlbumArtFileName(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAlbumArtFileName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAlbumArtFileName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1::EndAlbumArtFileName(IAsync& aAsync, Brh& aaName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("AlbumArtFileName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaName);
}

void CpProxyLinnCoUkJukebox1::SyncSetCurrentPreset(TUint aaPreset)
{
    SyncSetCurrentPresetLinnCoUkJukebox1 sync(*this);
    BeginSetCurrentPreset(aaPreset, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1::BeginSetCurrentPreset(TUint aaPreset, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetCurrentPreset, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetCurrentPreset->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaPreset));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1::EndSetCurrentPreset(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetCurrentPreset"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkJukebox1::SyncCurrentPreset(TUint& aaPreset)
{
    SyncCurrentPresetLinnCoUkJukebox1 sync(*this, aaPreset);
    BeginCurrentPreset(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1::BeginCurrentPreset(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCurrentPreset, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCurrentPreset->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1::EndCurrentPreset(IAsync& aAsync, TUint& aaPreset)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CurrentPreset"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaPreset = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkJukebox1::SyncPresetMetaData(TUint aaPreset, Brh& aaMetaData)
{
    SyncPresetMetaDataLinnCoUkJukebox1 sync(*this, aaMetaData);
    BeginPresetMetaData(aaPreset, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1::BeginPresetMetaData(TUint aaPreset, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPresetMetaData, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPresetMetaData->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaPreset));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetMetaData->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1::EndPresetMetaData(IAsync& aAsync, Brh& aaMetaData)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PresetMetaData"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaMetaData);
}

void CpProxyLinnCoUkJukebox1::SyncLoadManifest(TUint& aaTotalPresets)
{
    SyncLoadManifestLinnCoUkJukebox1 sync(*this, aaTotalPresets);
    BeginLoadManifest(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1::BeginLoadManifest(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionLoadManifest, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionLoadManifest->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1::EndLoadManifest(IAsync& aAsync, TUint& aaTotalPresets)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("LoadManifest"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaTotalPresets = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkJukebox1::SetPropertyCurrentPresetChanged(Functor& aFunctor)
{
    iLock->Wait();
    iCurrentPresetChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkJukebox1::SetPropertyPresetPrefixChanged(Functor& aFunctor)
{
    iLock->Wait();
    iPresetPrefixChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkJukebox1::SetPropertyAlbumArtFileNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iAlbumArtFileNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkJukebox1::PropertyCurrentPreset(TUint& aCurrentPreset) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aCurrentPreset = iCurrentPreset->Value();
}

void CpProxyLinnCoUkJukebox1::PropertyPresetPrefix(Brhz& aPresetPrefix) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aPresetPrefix.Set(iPresetPrefix->Value());
}

void CpProxyLinnCoUkJukebox1::PropertyAlbumArtFileName(Brhz& aAlbumArtFileName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aAlbumArtFileName.Set(iAlbumArtFileName->Value());
}

void CpProxyLinnCoUkJukebox1::CurrentPresetPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iCurrentPresetChanged != NULL) {
        iCurrentPresetChanged();
    }
}

void CpProxyLinnCoUkJukebox1::PresetPrefixPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iPresetPrefixChanged != NULL) {
        iPresetPrefixChanged();
    }
}

void CpProxyLinnCoUkJukebox1::AlbumArtFileNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iAlbumArtFileNameChanged != NULL) {
        iAlbumArtFileNameChanged();
    }
}

