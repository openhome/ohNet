#include <Std/CpLinnCoUkRadio1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncPlayLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncPlayLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
};

SyncPlayLinnCoUkRadio1Cpp::SyncPlayLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService)
    : iService(aService)
{
}

void SyncPlayLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncPauseLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
};

SyncPauseLinnCoUkRadio1Cpp::SyncPauseLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService)
    : iService(aService)
{
}

void SyncPauseLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStopLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncStopLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
};

SyncStopLinnCoUkRadio1Cpp::SyncStopLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService)
    : iService(aService)
{
}

void SyncStopLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncSeekSecondAbsoluteLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncSeekSecondAbsoluteLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
};

SyncSeekSecondAbsoluteLinnCoUkRadio1Cpp::SyncSeekSecondAbsoluteLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService)
    : iService(aService)
{
}

void SyncSeekSecondAbsoluteLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondAbsolute(aAsync);
}


class SyncSeekSecondRelativeLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncSeekSecondRelativeLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
};

SyncSeekSecondRelativeLinnCoUkRadio1Cpp::SyncSeekSecondRelativeLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService)
    : iService(aService)
{
}

void SyncSeekSecondRelativeLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondRelative(aAsync);
}


class SyncChannelLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncChannelLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, std::string& aaUri, std::string& aaMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
    std::string& iaUri;
    std::string& iaMetadata;
};

SyncChannelLinnCoUkRadio1Cpp::SyncChannelLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, std::string& aaUri, std::string& aaMetadata)
    : iService(aService)
    , iaUri(aaUri)
    , iaMetadata(aaMetadata)
{
}

void SyncChannelLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndChannel(aAsync, iaUri, iaMetadata);
}


class SyncSetChannelLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncSetChannelLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
};

SyncSetChannelLinnCoUkRadio1Cpp::SyncSetChannelLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService)
    : iService(aService)
{
}

void SyncSetChannelLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetChannel(aAsync);
}


class SyncProtocolInfoLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncProtocolInfoLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, std::string& aaInfo);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
    std::string& iaInfo;
};

SyncProtocolInfoLinnCoUkRadio1Cpp::SyncProtocolInfoLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, std::string& aaInfo)
    : iService(aService)
    , iaInfo(aaInfo)
{
}

void SyncProtocolInfoLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iaInfo);
}


class SyncTransportStateLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncTransportStateLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, std::string& aaState);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
    std::string& iaState;
};

SyncTransportStateLinnCoUkRadio1Cpp::SyncTransportStateLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, std::string& aaState)
    : iService(aService)
    , iaState(aaState)
{
}

void SyncTransportStateLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTransportState(aAsync, iaState);
}


class SyncIdLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncIdLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, uint32_t& aaId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
    uint32_t& iaId;
};

SyncIdLinnCoUkRadio1Cpp::SyncIdLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, uint32_t& aaId)
    : iService(aService)
    , iaId(aaId)
{
}

void SyncIdLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndId(aAsync, iaId);
}


class SyncSetIdLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncSetIdLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
};

SyncSetIdLinnCoUkRadio1Cpp::SyncSetIdLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService)
    : iService(aService)
{
}

void SyncSetIdLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetId(aAsync);
}


class SyncReadLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncReadLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, std::string& aaMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
    std::string& iaMetadata;
};

SyncReadLinnCoUkRadio1Cpp::SyncReadLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, std::string& aaMetadata)
    : iService(aService)
    , iaMetadata(aaMetadata)
{
}

void SyncReadLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iaMetadata);
}


class SyncReadListLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncReadListLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, std::string& aaMetadataList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
    std::string& iaMetadataList;
};

SyncReadListLinnCoUkRadio1Cpp::SyncReadListLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, std::string& aaMetadataList)
    : iService(aService)
    , iaMetadataList(aaMetadataList)
{
}

void SyncReadListLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iaMetadataList);
}


class SyncIdArrayLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncIdArrayLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, uint32_t& aaIdArrayToken, std::string& aaIdArray);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
    uint32_t& iaIdArrayToken;
    std::string& iaIdArray;
};

SyncIdArrayLinnCoUkRadio1Cpp::SyncIdArrayLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, uint32_t& aaIdArrayToken, std::string& aaIdArray)
    : iService(aService)
    , iaIdArrayToken(aaIdArrayToken)
    , iaIdArray(aaIdArray)
{
}

void SyncIdArrayLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArray(aAsync, iaIdArrayToken, iaIdArray);
}


class SyncIdArrayChangedLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncIdArrayChangedLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, bool& aaIdArrayChanged);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
    bool& iaIdArrayChanged;
};

SyncIdArrayChangedLinnCoUkRadio1Cpp::SyncIdArrayChangedLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, bool& aaIdArrayChanged)
    : iService(aService)
    , iaIdArrayChanged(aaIdArrayChanged)
{
}

void SyncIdArrayChangedLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArrayChanged(aAsync, iaIdArrayChanged);
}


class SyncIdsMaxLinnCoUkRadio1Cpp : public SyncProxyAction
{
public:
    SyncIdsMaxLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, uint32_t& aaIdsMax);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1Cpp& iService;
    uint32_t& iaIdsMax;
};

SyncIdsMaxLinnCoUkRadio1Cpp::SyncIdsMaxLinnCoUkRadio1Cpp(CpProxyLinnCoUkRadio1Cpp& aService, uint32_t& aaIdsMax)
    : iService(aService)
    , iaIdsMax(aaIdsMax)
{
}

void SyncIdsMaxLinnCoUkRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdsMax(aAsync, iaIdsMax);
}


CpProxyLinnCoUkRadio1Cpp::CpProxyLinnCoUkRadio1Cpp(CpDeviceCpp& aDevice)
{
    iService = new CpiService("linn-co-uk", "Radio", 1, aDevice.Device());
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionPlay = new Action("Play");

    iActionPause = new Action("Pause");

    iActionStop = new Action("Stop");

    iActionSeekSecondAbsolute = new Action("SeekSecondAbsolute");
    param = new Zapp::ParameterUint("aSecond");
    iActionSeekSecondAbsolute->AddInputParameter(param);

    iActionSeekSecondRelative = new Action("SeekSecondRelative");
    param = new Zapp::ParameterInt("aSecond");
    iActionSeekSecondRelative->AddInputParameter(param);

    iActionChannel = new Action("Channel");
    param = new Zapp::ParameterString("aUri");
    iActionChannel->AddOutputParameter(param);
    param = new Zapp::ParameterString("aMetadata");
    iActionChannel->AddOutputParameter(param);

    iActionSetChannel = new Action("SetChannel");
    param = new Zapp::ParameterString("aUri");
    iActionSetChannel->AddInputParameter(param);
    param = new Zapp::ParameterString("aMetadata");
    iActionSetChannel->AddInputParameter(param);

    iActionProtocolInfo = new Action("ProtocolInfo");
    param = new Zapp::ParameterString("aInfo");
    iActionProtocolInfo->AddOutputParameter(param);

    iActionTransportState = new Action("TransportState");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Buffering";
    param = new Zapp::ParameterString("aState", allowedValues, 4);
    iActionTransportState->AddOutputParameter(param);
    delete[] allowedValues;

    iActionId = new Action("Id");
    param = new Zapp::ParameterUint("aId");
    iActionId->AddOutputParameter(param);

    iActionSetId = new Action("SetId");
    param = new Zapp::ParameterUint("aId");
    iActionSetId->AddInputParameter(param);
    param = new Zapp::ParameterString("aUri");
    iActionSetId->AddInputParameter(param);

    iActionRead = new Action("Read");
    param = new Zapp::ParameterUint("aId");
    iActionRead->AddInputParameter(param);
    param = new Zapp::ParameterString("aMetadata");
    iActionRead->AddOutputParameter(param);

    iActionReadList = new Action("ReadList");
    param = new Zapp::ParameterString("aIdList");
    iActionReadList->AddInputParameter(param);
    param = new Zapp::ParameterString("aMetadataList");
    iActionReadList->AddOutputParameter(param);

    iActionIdArray = new Action("IdArray");
    param = new Zapp::ParameterUint("aIdArrayToken");
    iActionIdArray->AddOutputParameter(param);
    param = new Zapp::ParameterBinary("aIdArray");
    iActionIdArray->AddOutputParameter(param);

    iActionIdArrayChanged = new Action("IdArrayChanged");
    param = new Zapp::ParameterUint("aIdArrayToken");
    iActionIdArrayChanged->AddInputParameter(param);
    param = new Zapp::ParameterBool("aIdArrayChanged");
    iActionIdArrayChanged->AddOutputParameter(param);

    iActionIdsMax = new Action("IdsMax");
    param = new Zapp::ParameterUint("aIdsMax");
    iActionIdsMax->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1Cpp::ChannelUriPropertyChanged);
    iChannelUri = new PropertyString("ChannelUri", functor);
    iService->AddProperty(iChannelUri);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1Cpp::ChannelMetadataPropertyChanged);
    iChannelMetadata = new PropertyString("ChannelMetadata", functor);
    iService->AddProperty(iChannelMetadata);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1Cpp::TransportStatePropertyChanged);
    iTransportState = new PropertyString("TransportState", functor);
    iService->AddProperty(iTransportState);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1Cpp::ProtocolInfoPropertyChanged);
    iProtocolInfo = new PropertyString("ProtocolInfo", functor);
    iService->AddProperty(iProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1Cpp::IdPropertyChanged);
    iId = new PropertyUint("Id", functor);
    iService->AddProperty(iId);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1Cpp::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary("IdArray", functor);
    iService->AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1Cpp::IdsMaxPropertyChanged);
    iIdsMax = new PropertyUint("IdsMax", functor);
    iService->AddProperty(iIdsMax);
}

CpProxyLinnCoUkRadio1Cpp::~CpProxyLinnCoUkRadio1Cpp()
{
    delete iService;
    delete iActionPlay;
    delete iActionPause;
    delete iActionStop;
    delete iActionSeekSecondAbsolute;
    delete iActionSeekSecondRelative;
    delete iActionChannel;
    delete iActionSetChannel;
    delete iActionProtocolInfo;
    delete iActionTransportState;
    delete iActionId;
    delete iActionSetId;
    delete iActionRead;
    delete iActionReadList;
    delete iActionIdArray;
    delete iActionIdArrayChanged;
    delete iActionIdsMax;
}

void CpProxyLinnCoUkRadio1Cpp::SyncPlay()
{
    SyncPlayLinnCoUkRadio1Cpp sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncPause()
{
    SyncPauseLinnCoUkRadio1Cpp sync(*this);
    BeginPause(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginPause(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncStop()
{
    SyncStopLinnCoUkRadio1Cpp sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncSeekSecondAbsolute(uint32_t aaSecond)
{
    SyncSeekSecondAbsoluteLinnCoUkRadio1Cpp sync(*this);
    BeginSeekSecondAbsolute(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginSeekSecondAbsolute(uint32_t aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSecond));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndSeekSecondAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondAbsolute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncSeekSecondRelative(int32_t aaSecond)
{
    SyncSeekSecondRelativeLinnCoUkRadio1Cpp sync(*this);
    BeginSeekSecondRelative(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginSeekSecondRelative(int32_t aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaSecond));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndSeekSecondRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondRelative"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncChannel(std::string& aaUri, std::string& aaMetadata)
{
    SyncChannelLinnCoUkRadio1Cpp sync(*this, aaUri, aaMetadata);
    BeginChannel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginChannel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionChannel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionChannel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndChannel(IAsync& aAsync, std::string& aaUri, std::string& aaMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Channel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaUri.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaMetadata.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncSetChannel(const std::string& aaUri, const std::string& aaMetadata)
{
    SyncSetChannelLinnCoUkRadio1Cpp sync(*this);
    BeginSetChannel(aaUri, aaMetadata, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginSetChannel(const std::string& aaUri, const std::string& aaMetadata, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetChannel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetChannel->InputParameters();
    {
        Brn buf((const TByte*)aaUri.c_str(), aaUri.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aaMetadata.c_str(), aaMetadata.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndSetChannel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetChannel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncProtocolInfo(std::string& aaInfo)
{
    SyncProtocolInfoLinnCoUkRadio1Cpp sync(*this, aaInfo);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndProtocolInfo(IAsync& aAsync, std::string& aaInfo)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ProtocolInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaInfo.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncTransportState(std::string& aaState)
{
    SyncTransportStateLinnCoUkRadio1Cpp sync(*this, aaState);
    BeginTransportState(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginTransportState(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTransportState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTransportState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndTransportState(IAsync& aAsync, std::string& aaState)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TransportState"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaState.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncId(uint32_t& aaId)
{
    SyncIdLinnCoUkRadio1Cpp sync(*this, aaId);
    BeginId(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginId(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionId, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionId->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndId(IAsync& aAsync, uint32_t& aaId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Id"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkRadio1Cpp::SyncSetId(uint32_t aaId, const std::string& aaUri)
{
    SyncSetIdLinnCoUkRadio1Cpp sync(*this);
    BeginSetId(aaId, aaUri, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginSetId(uint32_t aaId, const std::string& aaUri, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaId));
    {
        Brn buf((const TByte*)aaUri.c_str(), aaUri.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndSetId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncRead(uint32_t aaId, std::string& aaMetadata)
{
    SyncReadLinnCoUkRadio1Cpp sync(*this, aaMetadata);
    BeginRead(aaId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginRead(uint32_t aaId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndRead(IAsync& aAsync, std::string& aaMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Read"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaMetadata.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncReadList(const std::string& aaIdList, std::string& aaMetadataList)
{
    SyncReadListLinnCoUkRadio1Cpp sync(*this, aaMetadataList);
    BeginReadList(aaIdList, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginReadList(const std::string& aaIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    {
        Brn buf((const TByte*)aaIdList.c_str(), aaIdList.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndReadList(IAsync& aAsync, std::string& aaMetadataList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ReadList"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaMetadataList.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncIdArray(uint32_t& aaIdArrayToken, std::string& aaIdArray)
{
    SyncIdArrayLinnCoUkRadio1Cpp sync(*this, aaIdArrayToken, aaIdArray);
    BeginIdArray(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginIdArray(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdArray, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArray->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndIdArray(IAsync& aAsync, uint32_t& aaIdArrayToken, std::string& aaIdArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArray"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaIdArrayToken = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaIdArray.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkRadio1Cpp::SyncIdArrayChanged(uint32_t aaIdArrayToken, bool& aaIdArrayChanged)
{
    SyncIdArrayChangedLinnCoUkRadio1Cpp sync(*this, aaIdArrayChanged);
    BeginIdArrayChanged(aaIdArrayToken, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginIdArrayChanged(uint32_t aaIdArrayToken, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdArrayChanged, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionIdArrayChanged->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIdArrayToken));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArrayChanged->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndIdArrayChanged(IAsync& aAsync, bool& aaIdArrayChanged)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArrayChanged"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaIdArrayChanged = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkRadio1Cpp::SyncIdsMax(uint32_t& aaIdsMax)
{
    SyncIdsMaxLinnCoUkRadio1Cpp sync(*this, aaIdsMax);
    BeginIdsMax(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1Cpp::BeginIdsMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdsMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdsMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1Cpp::EndIdsMax(IAsync& aAsync, uint32_t& aaIdsMax)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdsMax"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaIdsMax = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkRadio1Cpp::SetPropertyChannelUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iChannelUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1Cpp::SetPropertyChannelMetadataChanged(Functor& aFunctor)
{
    iLock->Wait();
    iChannelMetadataChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1Cpp::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransportStateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1Cpp::SetPropertyProtocolInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProtocolInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1Cpp::SetPropertyIdChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1Cpp::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdArrayChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1Cpp::SetPropertyIdsMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdsMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1Cpp::PropertyChannelUri(std::string& aChannelUri) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iChannelUri->Value();
    aChannelUri.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkRadio1Cpp::PropertyChannelMetadata(std::string& aChannelMetadata) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iChannelMetadata->Value();
    aChannelMetadata.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkRadio1Cpp::PropertyTransportState(std::string& aTransportState) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iTransportState->Value();
    aTransportState.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkRadio1Cpp::PropertyProtocolInfo(std::string& aProtocolInfo) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProtocolInfo->Value();
    aProtocolInfo.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkRadio1Cpp::PropertyId(uint32_t& aId) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aId = iId->Value();
}

void CpProxyLinnCoUkRadio1Cpp::PropertyIdArray(std::string& aIdArray) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iIdArray->Value();
    aIdArray.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkRadio1Cpp::PropertyIdsMax(uint32_t& aIdsMax) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aIdsMax = iIdsMax->Value();
}

void CpProxyLinnCoUkRadio1Cpp::ChannelUriPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iChannelUriChanged != NULL) {
        iChannelUriChanged();
    }
}

void CpProxyLinnCoUkRadio1Cpp::ChannelMetadataPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iChannelMetadataChanged != NULL) {
        iChannelMetadataChanged();
    }
}

void CpProxyLinnCoUkRadio1Cpp::TransportStatePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTransportStateChanged != NULL) {
        iTransportStateChanged();
    }
}

void CpProxyLinnCoUkRadio1Cpp::ProtocolInfoPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProtocolInfoChanged != NULL) {
        iProtocolInfoChanged();
    }
}

void CpProxyLinnCoUkRadio1Cpp::IdPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iIdChanged != NULL) {
        iIdChanged();
    }
}

void CpProxyLinnCoUkRadio1Cpp::IdArrayPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iIdArrayChanged != NULL) {
        iIdArrayChanged();
    }
}

void CpProxyLinnCoUkRadio1Cpp::IdsMaxPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iIdsMaxChanged != NULL) {
        iIdsMaxChanged();
    }
}

