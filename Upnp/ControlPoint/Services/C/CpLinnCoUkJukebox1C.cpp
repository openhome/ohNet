#include "CpLinnCoUkJukebox1.h"
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

class CpProxyLinnCoUkJukebox1C : public CpProxyC
{
public:
    CpProxyLinnCoUkJukebox1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkJukebox1C();
    //CpProxyLinnCoUkJukebox1* Proxy() { return static_cast<CpProxyLinnCoUkJukebox1*>(iProxy); }

    void SyncSetPresetPrefix(const Brx& aaUri);
    void BeginSetPresetPrefix(const Brx& aaUri, FunctorAsync& aFunctor);
    void EndSetPresetPrefix(IAsync& aAsync);

    void SyncPresetPrefix(Brh& aaUri);
    void BeginPresetPrefix(FunctorAsync& aFunctor);
    void EndPresetPrefix(IAsync& aAsync, Brh& aaUri);

    void SyncSetAlbumArtFileName(const Brx& aaName);
    void BeginSetAlbumArtFileName(const Brx& aaName, FunctorAsync& aFunctor);
    void EndSetAlbumArtFileName(IAsync& aAsync);

    void SyncAlbumArtFileName(Brh& aaName);
    void BeginAlbumArtFileName(FunctorAsync& aFunctor);
    void EndAlbumArtFileName(IAsync& aAsync, Brh& aaName);

    void SyncSetCurrentPreset(TUint aaPreset);
    void BeginSetCurrentPreset(TUint aaPreset, FunctorAsync& aFunctor);
    void EndSetCurrentPreset(IAsync& aAsync);

    void SyncCurrentPreset(TUint& aaPreset);
    void BeginCurrentPreset(FunctorAsync& aFunctor);
    void EndCurrentPreset(IAsync& aAsync, TUint& aaPreset);

    void SyncPresetMetaData(TUint aaPreset, Brh& aaMetaData);
    void BeginPresetMetaData(TUint aaPreset, FunctorAsync& aFunctor);
    void EndPresetMetaData(IAsync& aAsync, Brh& aaMetaData);

    void SyncLoadManifest(TUint& aaTotalPresets);
    void BeginLoadManifest(FunctorAsync& aFunctor);
    void EndLoadManifest(IAsync& aAsync, TUint& aaTotalPresets);

    void SetPropertyCurrentPresetChanged(Functor& aFunctor);
    void SetPropertyPresetPrefixChanged(Functor& aFunctor);
    void SetPropertyAlbumArtFileNameChanged(Functor& aFunctor);

    void PropertyCurrentPreset(TUint& aCurrentPreset) const;
    void PropertyPresetPrefix(Brhz& aPresetPrefix) const;
    void PropertyAlbumArtFileName(Brhz& aAlbumArtFileName) const;
private:
    void CurrentPresetPropertyChanged();
    void PresetPrefixPropertyChanged();
    void AlbumArtFileNamePropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionSetPresetPrefix;
    Action* iActionPresetPrefix;
    Action* iActionSetAlbumArtFileName;
    Action* iActionAlbumArtFileName;
    Action* iActionSetCurrentPreset;
    Action* iActionCurrentPreset;
    Action* iActionPresetMetaData;
    Action* iActionLoadManifest;
    PropertyUint* iCurrentPreset;
    PropertyString* iPresetPrefix;
    PropertyString* iAlbumArtFileName;
    Functor iCurrentPresetChanged;
    Functor iPresetPrefixChanged;
    Functor iAlbumArtFileNameChanged;
};


class SyncSetPresetPrefixLinnCoUkJukebox1C : public SyncProxyAction
{
public:
    SyncSetPresetPrefixLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1C& iService;
};

SyncSetPresetPrefixLinnCoUkJukebox1C::SyncSetPresetPrefixLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetPresetPrefixLinnCoUkJukebox1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetPrefix(aAsync);
}


class SyncPresetPrefixLinnCoUkJukebox1C : public SyncProxyAction
{
public:
    SyncPresetPrefixLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy, Brh& aaUri);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1C& iService;
    Brh& iaUri;
};

SyncPresetPrefixLinnCoUkJukebox1C::SyncPresetPrefixLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy, Brh& aaUri)
    : iService(aProxy)
    , iaUri(aaUri)
{
}

void SyncPresetPrefixLinnCoUkJukebox1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetPrefix(aAsync, iaUri);
}


class SyncSetAlbumArtFileNameLinnCoUkJukebox1C : public SyncProxyAction
{
public:
    SyncSetAlbumArtFileNameLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1C& iService;
};

SyncSetAlbumArtFileNameLinnCoUkJukebox1C::SyncSetAlbumArtFileNameLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetAlbumArtFileNameLinnCoUkJukebox1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAlbumArtFileName(aAsync);
}


class SyncAlbumArtFileNameLinnCoUkJukebox1C : public SyncProxyAction
{
public:
    SyncAlbumArtFileNameLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy, Brh& aaName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1C& iService;
    Brh& iaName;
};

SyncAlbumArtFileNameLinnCoUkJukebox1C::SyncAlbumArtFileNameLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy, Brh& aaName)
    : iService(aProxy)
    , iaName(aaName)
{
}

void SyncAlbumArtFileNameLinnCoUkJukebox1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndAlbumArtFileName(aAsync, iaName);
}


class SyncSetCurrentPresetLinnCoUkJukebox1C : public SyncProxyAction
{
public:
    SyncSetCurrentPresetLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1C& iService;
};

SyncSetCurrentPresetLinnCoUkJukebox1C::SyncSetCurrentPresetLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetCurrentPresetLinnCoUkJukebox1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetCurrentPreset(aAsync);
}


class SyncCurrentPresetLinnCoUkJukebox1C : public SyncProxyAction
{
public:
    SyncCurrentPresetLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy, TUint& aaPreset);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1C& iService;
    TUint& iaPreset;
};

SyncCurrentPresetLinnCoUkJukebox1C::SyncCurrentPresetLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy, TUint& aaPreset)
    : iService(aProxy)
    , iaPreset(aaPreset)
{
}

void SyncCurrentPresetLinnCoUkJukebox1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCurrentPreset(aAsync, iaPreset);
}


class SyncPresetMetaDataLinnCoUkJukebox1C : public SyncProxyAction
{
public:
    SyncPresetMetaDataLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy, Brh& aaMetaData);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1C& iService;
    Brh& iaMetaData;
};

SyncPresetMetaDataLinnCoUkJukebox1C::SyncPresetMetaDataLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy, Brh& aaMetaData)
    : iService(aProxy)
    , iaMetaData(aaMetaData)
{
}

void SyncPresetMetaDataLinnCoUkJukebox1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetMetaData(aAsync, iaMetaData);
}


class SyncLoadManifestLinnCoUkJukebox1C : public SyncProxyAction
{
public:
    SyncLoadManifestLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy, TUint& aaTotalPresets);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1C& iService;
    TUint& iaTotalPresets;
};

SyncLoadManifestLinnCoUkJukebox1C::SyncLoadManifestLinnCoUkJukebox1C(CpProxyLinnCoUkJukebox1C& aProxy, TUint& aaTotalPresets)
    : iService(aProxy)
    , iaTotalPresets(aaTotalPresets)
{
}

void SyncLoadManifestLinnCoUkJukebox1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndLoadManifest(aAsync, iaTotalPresets);
}

CpProxyLinnCoUkJukebox1C::CpProxyLinnCoUkJukebox1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Jukebox", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkJukebox1C::CurrentPresetPropertyChanged);
    iCurrentPreset = new PropertyUint("CurrentPreset", functor);
    AddProperty(iCurrentPreset);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkJukebox1C::PresetPrefixPropertyChanged);
    iPresetPrefix = new PropertyString("PresetPrefix", functor);
    AddProperty(iPresetPrefix);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkJukebox1C::AlbumArtFileNamePropertyChanged);
    iAlbumArtFileName = new PropertyString("AlbumArtFileName", functor);
    AddProperty(iAlbumArtFileName);
}

CpProxyLinnCoUkJukebox1C::~CpProxyLinnCoUkJukebox1C()
{
    delete iActionSetPresetPrefix;
    delete iActionPresetPrefix;
    delete iActionSetAlbumArtFileName;
    delete iActionAlbumArtFileName;
    delete iActionSetCurrentPreset;
    delete iActionCurrentPreset;
    delete iActionPresetMetaData;
    delete iActionLoadManifest;
}

void CpProxyLinnCoUkJukebox1C::SyncSetPresetPrefix(const Brx& aaUri)
{
    SyncSetPresetPrefixLinnCoUkJukebox1C sync(*this);
    BeginSetPresetPrefix(aaUri, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1C::BeginSetPresetPrefix(const Brx& aaUri, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetPresetPrefix, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetPrefix->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaUri));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkJukebox1C::EndSetPresetPrefix(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetPrefix"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkJukebox1C::SyncPresetPrefix(Brh& aaUri)
{
    SyncPresetPrefixLinnCoUkJukebox1C sync(*this, aaUri);
    BeginPresetPrefix(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1C::BeginPresetPrefix(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPresetPrefix, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetPrefix->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkJukebox1C::EndPresetPrefix(IAsync& aAsync, Brh& aaUri)
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

void CpProxyLinnCoUkJukebox1C::SyncSetAlbumArtFileName(const Brx& aaName)
{
    SyncSetAlbumArtFileNameLinnCoUkJukebox1C sync(*this);
    BeginSetAlbumArtFileName(aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1C::BeginSetAlbumArtFileName(const Brx& aaName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetAlbumArtFileName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAlbumArtFileName->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkJukebox1C::EndSetAlbumArtFileName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAlbumArtFileName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkJukebox1C::SyncAlbumArtFileName(Brh& aaName)
{
    SyncAlbumArtFileNameLinnCoUkJukebox1C sync(*this, aaName);
    BeginAlbumArtFileName(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1C::BeginAlbumArtFileName(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionAlbumArtFileName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAlbumArtFileName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkJukebox1C::EndAlbumArtFileName(IAsync& aAsync, Brh& aaName)
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

void CpProxyLinnCoUkJukebox1C::SyncSetCurrentPreset(TUint aaPreset)
{
    SyncSetCurrentPresetLinnCoUkJukebox1C sync(*this);
    BeginSetCurrentPreset(aaPreset, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1C::BeginSetCurrentPreset(TUint aaPreset, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetCurrentPreset, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetCurrentPreset->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaPreset));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkJukebox1C::EndSetCurrentPreset(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetCurrentPreset"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkJukebox1C::SyncCurrentPreset(TUint& aaPreset)
{
    SyncCurrentPresetLinnCoUkJukebox1C sync(*this, aaPreset);
    BeginCurrentPreset(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1C::BeginCurrentPreset(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCurrentPreset, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCurrentPreset->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkJukebox1C::EndCurrentPreset(IAsync& aAsync, TUint& aaPreset)
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

void CpProxyLinnCoUkJukebox1C::SyncPresetMetaData(TUint aaPreset, Brh& aaMetaData)
{
    SyncPresetMetaDataLinnCoUkJukebox1C sync(*this, aaMetaData);
    BeginPresetMetaData(aaPreset, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1C::BeginPresetMetaData(TUint aaPreset, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPresetMetaData, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPresetMetaData->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaPreset));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetMetaData->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkJukebox1C::EndPresetMetaData(IAsync& aAsync, Brh& aaMetaData)
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

void CpProxyLinnCoUkJukebox1C::SyncLoadManifest(TUint& aaTotalPresets)
{
    SyncLoadManifestLinnCoUkJukebox1C sync(*this, aaTotalPresets);
    BeginLoadManifest(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1C::BeginLoadManifest(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionLoadManifest, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionLoadManifest->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkJukebox1C::EndLoadManifest(IAsync& aAsync, TUint& aaTotalPresets)
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

void CpProxyLinnCoUkJukebox1C::SetPropertyCurrentPresetChanged(Functor& aFunctor)
{
    iLock.Wait();
    iCurrentPresetChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkJukebox1C::SetPropertyPresetPrefixChanged(Functor& aFunctor)
{
    iLock.Wait();
    iPresetPrefixChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkJukebox1C::SetPropertyAlbumArtFileNameChanged(Functor& aFunctor)
{
    iLock.Wait();
    iAlbumArtFileNameChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkJukebox1C::PropertyCurrentPreset(TUint& aCurrentPreset) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aCurrentPreset = iCurrentPreset->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkJukebox1C::PropertyPresetPrefix(Brhz& aPresetPrefix) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aPresetPrefix.Set(iPresetPrefix->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkJukebox1C::PropertyAlbumArtFileName(Brhz& aAlbumArtFileName) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aAlbumArtFileName.Set(iAlbumArtFileName->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkJukebox1C::CurrentPresetPropertyChanged()
{
    ReportEvent(iCurrentPresetChanged);
}

void CpProxyLinnCoUkJukebox1C::PresetPrefixPropertyChanged()
{
    ReportEvent(iPresetPrefixChanged);
}

void CpProxyLinnCoUkJukebox1C::AlbumArtFileNamePropertyChanged()
{
    ReportEvent(iAlbumArtFileNameChanged);
}


THandle CpProxyLinnCoUkJukebox1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkJukebox1C(aDevice);
}

void CpProxyLinnCoUkJukebox1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkJukebox1SyncSetPresetPrefix(THandle aHandle, const char* aaUri)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    proxyC->SyncSetPresetPrefix(buf_aaUri);
}

void CpProxyLinnCoUkJukebox1BeginSetPresetPrefix(THandle aHandle, const char* aaUri, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetPresetPrefix(buf_aaUri, functor);
}

int32_t CpProxyLinnCoUkJukebox1EndSetPresetPrefix(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetPresetPrefix(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncPresetPrefix(THandle aHandle, char** aaUri)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri;
    proxyC->SyncPresetPrefix(buf_aaUri);
    *aaUri = buf_aaUri.Extract();
}

void CpProxyLinnCoUkJukebox1BeginPresetPrefix(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginPresetPrefix(functor);
}

int32_t CpProxyLinnCoUkJukebox1EndPresetPrefix(THandle aHandle, ZappHandleAsync aAsync, char** aaUri)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaUri;
    *aaUri = NULL;
    try {
        proxyC->EndPresetPrefix(*async, buf_aaUri);
        *aaUri = buf_aaUri.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncSetAlbumArtFileName(THandle aHandle, const char* aaName)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    proxyC->SyncSetAlbumArtFileName(buf_aaName);
}

void CpProxyLinnCoUkJukebox1BeginSetAlbumArtFileName(THandle aHandle, const char* aaName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetAlbumArtFileName(buf_aaName, functor);
}

int32_t CpProxyLinnCoUkJukebox1EndSetAlbumArtFileName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetAlbumArtFileName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncAlbumArtFileName(THandle aHandle, char** aaName)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName;
    proxyC->SyncAlbumArtFileName(buf_aaName);
    *aaName = buf_aaName.Extract();
}

void CpProxyLinnCoUkJukebox1BeginAlbumArtFileName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginAlbumArtFileName(functor);
}

int32_t CpProxyLinnCoUkJukebox1EndAlbumArtFileName(THandle aHandle, ZappHandleAsync aAsync, char** aaName)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaName;
    *aaName = NULL;
    try {
        proxyC->EndAlbumArtFileName(*async, buf_aaName);
        *aaName = buf_aaName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncSetCurrentPreset(THandle aHandle, uint32_t aaPreset)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetCurrentPreset(aaPreset);
}

void CpProxyLinnCoUkJukebox1BeginSetCurrentPreset(THandle aHandle, uint32_t aaPreset, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetCurrentPreset(aaPreset, functor);
}

int32_t CpProxyLinnCoUkJukebox1EndSetCurrentPreset(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetCurrentPreset(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncCurrentPreset(THandle aHandle, uint32_t* aaPreset)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncCurrentPreset(*aaPreset);
}

void CpProxyLinnCoUkJukebox1BeginCurrentPreset(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginCurrentPreset(functor);
}

int32_t CpProxyLinnCoUkJukebox1EndCurrentPreset(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaPreset)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndCurrentPreset(*async, *aaPreset);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncPresetMetaData(THandle aHandle, uint32_t aaPreset, char** aaMetaData)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMetaData;
    proxyC->SyncPresetMetaData(aaPreset, buf_aaMetaData);
    *aaMetaData = buf_aaMetaData.Extract();
}

void CpProxyLinnCoUkJukebox1BeginPresetMetaData(THandle aHandle, uint32_t aaPreset, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginPresetMetaData(aaPreset, functor);
}

int32_t CpProxyLinnCoUkJukebox1EndPresetMetaData(THandle aHandle, ZappHandleAsync aAsync, char** aaMetaData)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMetaData;
    *aaMetaData = NULL;
    try {
        proxyC->EndPresetMetaData(*async, buf_aaMetaData);
        *aaMetaData = buf_aaMetaData.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncLoadManifest(THandle aHandle, uint32_t* aaTotalPresets)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncLoadManifest(*aaTotalPresets);
}

void CpProxyLinnCoUkJukebox1BeginLoadManifest(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginLoadManifest(functor);
}

int32_t CpProxyLinnCoUkJukebox1EndLoadManifest(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTotalPresets)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndLoadManifest(*async, *aaTotalPresets);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SetPropertyCurrentPresetChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyCurrentPresetChanged(functor);
}

void CpProxyLinnCoUkJukebox1SetPropertyPresetPrefixChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyPresetPrefixChanged(functor);
}

void CpProxyLinnCoUkJukebox1SetPropertyAlbumArtFileNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyAlbumArtFileNameChanged(functor);
}

void CpProxyLinnCoUkJukebox1PropertyCurrentPreset(THandle aHandle, uint32_t* aCurrentPreset)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyCurrentPreset(*aCurrentPreset);
}

void CpProxyLinnCoUkJukebox1PropertyPresetPrefix(THandle aHandle, char** aPresetPrefix)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aPresetPrefix;
    proxyC->PropertyPresetPrefix(buf_aPresetPrefix);
    *aPresetPrefix = buf_aPresetPrefix.Transfer();
}

void CpProxyLinnCoUkJukebox1PropertyAlbumArtFileName(THandle aHandle, char** aAlbumArtFileName)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aAlbumArtFileName;
    proxyC->PropertyAlbumArtFileName(buf_aAlbumArtFileName);
    *aAlbumArtFileName = buf_aAlbumArtFileName.Transfer();
}

