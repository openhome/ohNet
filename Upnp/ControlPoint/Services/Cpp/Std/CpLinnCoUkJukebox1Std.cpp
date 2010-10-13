#include <Std/CpLinnCoUkJukebox1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncSetPresetPrefixLinnCoUkJukebox1Cpp : public SyncProxyAction
{
public:
    SyncSetPresetPrefixLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1Cpp& iService;
};

SyncSetPresetPrefixLinnCoUkJukebox1Cpp::SyncSetPresetPrefixLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService)
    : iService(aService)
{
}

void SyncSetPresetPrefixLinnCoUkJukebox1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetPresetPrefix(aAsync);
}


class SyncPresetPrefixLinnCoUkJukebox1Cpp : public SyncProxyAction
{
public:
    SyncPresetPrefixLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService, std::string& aaUri);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1Cpp& iService;
    std::string& iaUri;
};

SyncPresetPrefixLinnCoUkJukebox1Cpp::SyncPresetPrefixLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService, std::string& aaUri)
    : iService(aService)
    , iaUri(aaUri)
{
}

void SyncPresetPrefixLinnCoUkJukebox1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetPrefix(aAsync, iaUri);
}


class SyncSetAlbumArtFileNameLinnCoUkJukebox1Cpp : public SyncProxyAction
{
public:
    SyncSetAlbumArtFileNameLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1Cpp& iService;
};

SyncSetAlbumArtFileNameLinnCoUkJukebox1Cpp::SyncSetAlbumArtFileNameLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService)
    : iService(aService)
{
}

void SyncSetAlbumArtFileNameLinnCoUkJukebox1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAlbumArtFileName(aAsync);
}


class SyncAlbumArtFileNameLinnCoUkJukebox1Cpp : public SyncProxyAction
{
public:
    SyncAlbumArtFileNameLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService, std::string& aaName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1Cpp& iService;
    std::string& iaName;
};

SyncAlbumArtFileNameLinnCoUkJukebox1Cpp::SyncAlbumArtFileNameLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService, std::string& aaName)
    : iService(aService)
    , iaName(aaName)
{
}

void SyncAlbumArtFileNameLinnCoUkJukebox1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndAlbumArtFileName(aAsync, iaName);
}


class SyncSetCurrentPresetLinnCoUkJukebox1Cpp : public SyncProxyAction
{
public:
    SyncSetCurrentPresetLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1Cpp& iService;
};

SyncSetCurrentPresetLinnCoUkJukebox1Cpp::SyncSetCurrentPresetLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService)
    : iService(aService)
{
}

void SyncSetCurrentPresetLinnCoUkJukebox1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetCurrentPreset(aAsync);
}


class SyncCurrentPresetLinnCoUkJukebox1Cpp : public SyncProxyAction
{
public:
    SyncCurrentPresetLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService, uint32_t& aaPreset);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1Cpp& iService;
    uint32_t& iaPreset;
};

SyncCurrentPresetLinnCoUkJukebox1Cpp::SyncCurrentPresetLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService, uint32_t& aaPreset)
    : iService(aService)
    , iaPreset(aaPreset)
{
}

void SyncCurrentPresetLinnCoUkJukebox1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCurrentPreset(aAsync, iaPreset);
}


class SyncPresetMetaDataLinnCoUkJukebox1Cpp : public SyncProxyAction
{
public:
    SyncPresetMetaDataLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService, std::string& aaMetaData);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1Cpp& iService;
    std::string& iaMetaData;
};

SyncPresetMetaDataLinnCoUkJukebox1Cpp::SyncPresetMetaDataLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService, std::string& aaMetaData)
    : iService(aService)
    , iaMetaData(aaMetaData)
{
}

void SyncPresetMetaDataLinnCoUkJukebox1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresetMetaData(aAsync, iaMetaData);
}


class SyncLoadManifestLinnCoUkJukebox1Cpp : public SyncProxyAction
{
public:
    SyncLoadManifestLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService, uint32_t& aaTotalPresets);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkJukebox1Cpp& iService;
    uint32_t& iaTotalPresets;
};

SyncLoadManifestLinnCoUkJukebox1Cpp::SyncLoadManifestLinnCoUkJukebox1Cpp(CpProxyLinnCoUkJukebox1Cpp& aService, uint32_t& aaTotalPresets)
    : iService(aService)
    , iaTotalPresets(aaTotalPresets)
{
}

void SyncLoadManifestLinnCoUkJukebox1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndLoadManifest(aAsync, iaTotalPresets);
}


CpProxyLinnCoUkJukebox1Cpp::CpProxyLinnCoUkJukebox1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkJukebox1Cpp::CurrentPresetPropertyChanged);
    iCurrentPreset = new PropertyUint("CurrentPreset", functor);
    iService->AddProperty(iCurrentPreset);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkJukebox1Cpp::PresetPrefixPropertyChanged);
    iPresetPrefix = new PropertyString("PresetPrefix", functor);
    iService->AddProperty(iPresetPrefix);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkJukebox1Cpp::AlbumArtFileNamePropertyChanged);
    iAlbumArtFileName = new PropertyString("AlbumArtFileName", functor);
    iService->AddProperty(iAlbumArtFileName);
}

CpProxyLinnCoUkJukebox1Cpp::~CpProxyLinnCoUkJukebox1Cpp()
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

void CpProxyLinnCoUkJukebox1Cpp::SyncSetPresetPrefix(const std::string& aaUri)
{
    SyncSetPresetPrefixLinnCoUkJukebox1Cpp sync(*this);
    BeginSetPresetPrefix(aaUri, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1Cpp::BeginSetPresetPrefix(const std::string& aaUri, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetPresetPrefix, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetPresetPrefix->InputParameters();
    {
        Brn buf((const TByte*)aaUri.c_str(), aaUri.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1Cpp::EndSetPresetPrefix(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetPresetPrefix"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkJukebox1Cpp::SyncPresetPrefix(std::string& aaUri)
{
    SyncPresetPrefixLinnCoUkJukebox1Cpp sync(*this, aaUri);
    BeginPresetPrefix(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1Cpp::BeginPresetPrefix(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPresetPrefix, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresetPrefix->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1Cpp::EndPresetPrefix(IAsync& aAsync, std::string& aaUri)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PresetPrefix"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaUri.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkJukebox1Cpp::SyncSetAlbumArtFileName(const std::string& aaName)
{
    SyncSetAlbumArtFileNameLinnCoUkJukebox1Cpp sync(*this);
    BeginSetAlbumArtFileName(aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1Cpp::BeginSetAlbumArtFileName(const std::string& aaName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetAlbumArtFileName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAlbumArtFileName->InputParameters();
    {
        Brn buf((const TByte*)aaName.c_str(), aaName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1Cpp::EndSetAlbumArtFileName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAlbumArtFileName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkJukebox1Cpp::SyncAlbumArtFileName(std::string& aaName)
{
    SyncAlbumArtFileNameLinnCoUkJukebox1Cpp sync(*this, aaName);
    BeginAlbumArtFileName(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1Cpp::BeginAlbumArtFileName(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAlbumArtFileName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAlbumArtFileName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1Cpp::EndAlbumArtFileName(IAsync& aAsync, std::string& aaName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("AlbumArtFileName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkJukebox1Cpp::SyncSetCurrentPreset(uint32_t aaPreset)
{
    SyncSetCurrentPresetLinnCoUkJukebox1Cpp sync(*this);
    BeginSetCurrentPreset(aaPreset, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1Cpp::BeginSetCurrentPreset(uint32_t aaPreset, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetCurrentPreset, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetCurrentPreset->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaPreset));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1Cpp::EndSetCurrentPreset(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetCurrentPreset"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkJukebox1Cpp::SyncCurrentPreset(uint32_t& aaPreset)
{
    SyncCurrentPresetLinnCoUkJukebox1Cpp sync(*this, aaPreset);
    BeginCurrentPreset(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1Cpp::BeginCurrentPreset(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCurrentPreset, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCurrentPreset->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1Cpp::EndCurrentPreset(IAsync& aAsync, uint32_t& aaPreset)
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

void CpProxyLinnCoUkJukebox1Cpp::SyncPresetMetaData(uint32_t aaPreset, std::string& aaMetaData)
{
    SyncPresetMetaDataLinnCoUkJukebox1Cpp sync(*this, aaMetaData);
    BeginPresetMetaData(aaPreset, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1Cpp::BeginPresetMetaData(uint32_t aaPreset, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkJukebox1Cpp::EndPresetMetaData(IAsync& aAsync, std::string& aaMetaData)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PresetMetaData"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaMetaData.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkJukebox1Cpp::SyncLoadManifest(uint32_t& aaTotalPresets)
{
    SyncLoadManifestLinnCoUkJukebox1Cpp sync(*this, aaTotalPresets);
    BeginLoadManifest(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkJukebox1Cpp::BeginLoadManifest(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionLoadManifest, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionLoadManifest->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkJukebox1Cpp::EndLoadManifest(IAsync& aAsync, uint32_t& aaTotalPresets)
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

void CpProxyLinnCoUkJukebox1Cpp::SetPropertyCurrentPresetChanged(Functor& aFunctor)
{
    iLock->Wait();
    iCurrentPresetChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkJukebox1Cpp::SetPropertyPresetPrefixChanged(Functor& aFunctor)
{
    iLock->Wait();
    iPresetPrefixChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkJukebox1Cpp::SetPropertyAlbumArtFileNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iAlbumArtFileNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkJukebox1Cpp::PropertyCurrentPreset(uint32_t& aCurrentPreset) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aCurrentPreset = iCurrentPreset->Value();
}

void CpProxyLinnCoUkJukebox1Cpp::PropertyPresetPrefix(std::string& aPresetPrefix) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iPresetPrefix->Value();
    aPresetPrefix.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkJukebox1Cpp::PropertyAlbumArtFileName(std::string& aAlbumArtFileName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iAlbumArtFileName->Value();
    aAlbumArtFileName.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkJukebox1Cpp::CurrentPresetPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iCurrentPresetChanged != NULL) {
        iCurrentPresetChanged();
    }
}

void CpProxyLinnCoUkJukebox1Cpp::PresetPrefixPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iPresetPrefixChanged != NULL) {
        iPresetPrefixChanged();
    }
}

void CpProxyLinnCoUkJukebox1Cpp::AlbumArtFileNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iAlbumArtFileNameChanged != NULL) {
        iAlbumArtFileNameChanged();
    }
}

