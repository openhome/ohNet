#include <Core/CpLinnCoUkRadio1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncPlayLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncPlayLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
};

SyncPlayLinnCoUkRadio1::SyncPlayLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService)
    : iService(aService)
{
}

void SyncPlayLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncPauseLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
};

SyncPauseLinnCoUkRadio1::SyncPauseLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService)
    : iService(aService)
{
}

void SyncPauseLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStopLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncStopLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
};

SyncStopLinnCoUkRadio1::SyncStopLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService)
    : iService(aService)
{
}

void SyncStopLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncSeekSecondAbsoluteLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncSeekSecondAbsoluteLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
};

SyncSeekSecondAbsoluteLinnCoUkRadio1::SyncSeekSecondAbsoluteLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService)
    : iService(aService)
{
}

void SyncSeekSecondAbsoluteLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondAbsolute(aAsync);
}


class SyncSeekSecondRelativeLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncSeekSecondRelativeLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
};

SyncSeekSecondRelativeLinnCoUkRadio1::SyncSeekSecondRelativeLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService)
    : iService(aService)
{
}

void SyncSeekSecondRelativeLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondRelative(aAsync);
}


class SyncChannelLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncChannelLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, Brh& aaUri, Brh& aaMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
    Brh& iaUri;
    Brh& iaMetadata;
};

SyncChannelLinnCoUkRadio1::SyncChannelLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, Brh& aaUri, Brh& aaMetadata)
    : iService(aService)
    , iaUri(aaUri)
    , iaMetadata(aaMetadata)
{
}

void SyncChannelLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndChannel(aAsync, iaUri, iaMetadata);
}


class SyncSetChannelLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncSetChannelLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
};

SyncSetChannelLinnCoUkRadio1::SyncSetChannelLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService)
    : iService(aService)
{
}

void SyncSetChannelLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetChannel(aAsync);
}


class SyncProtocolInfoLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncProtocolInfoLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, Brh& aaInfo);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
    Brh& iaInfo;
};

SyncProtocolInfoLinnCoUkRadio1::SyncProtocolInfoLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, Brh& aaInfo)
    : iService(aService)
    , iaInfo(aaInfo)
{
}

void SyncProtocolInfoLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iaInfo);
}


class SyncTransportStateLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncTransportStateLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, Brh& aaState);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
    Brh& iaState;
};

SyncTransportStateLinnCoUkRadio1::SyncTransportStateLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, Brh& aaState)
    : iService(aService)
    , iaState(aaState)
{
}

void SyncTransportStateLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTransportState(aAsync, iaState);
}


class SyncIdLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncIdLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, TUint& aaId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
    TUint& iaId;
};

SyncIdLinnCoUkRadio1::SyncIdLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, TUint& aaId)
    : iService(aService)
    , iaId(aaId)
{
}

void SyncIdLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndId(aAsync, iaId);
}


class SyncSetIdLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncSetIdLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
};

SyncSetIdLinnCoUkRadio1::SyncSetIdLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService)
    : iService(aService)
{
}

void SyncSetIdLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetId(aAsync);
}


class SyncReadLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncReadLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, Brh& aaMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
    Brh& iaMetadata;
};

SyncReadLinnCoUkRadio1::SyncReadLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, Brh& aaMetadata)
    : iService(aService)
    , iaMetadata(aaMetadata)
{
}

void SyncReadLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iaMetadata);
}


class SyncReadListLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncReadListLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, Brh& aaMetadataList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
    Brh& iaMetadataList;
};

SyncReadListLinnCoUkRadio1::SyncReadListLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, Brh& aaMetadataList)
    : iService(aService)
    , iaMetadataList(aaMetadataList)
{
}

void SyncReadListLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iaMetadataList);
}


class SyncIdArrayLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncIdArrayLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, TUint& aaIdArrayToken, Brh& aaIdArray);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
    TUint& iaIdArrayToken;
    Brh& iaIdArray;
};

SyncIdArrayLinnCoUkRadio1::SyncIdArrayLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, TUint& aaIdArrayToken, Brh& aaIdArray)
    : iService(aService)
    , iaIdArrayToken(aaIdArrayToken)
    , iaIdArray(aaIdArray)
{
}

void SyncIdArrayLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArray(aAsync, iaIdArrayToken, iaIdArray);
}


class SyncIdArrayChangedLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncIdArrayChangedLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, TBool& aaIdArrayChanged);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
    TBool& iaIdArrayChanged;
};

SyncIdArrayChangedLinnCoUkRadio1::SyncIdArrayChangedLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, TBool& aaIdArrayChanged)
    : iService(aService)
    , iaIdArrayChanged(aaIdArrayChanged)
{
}

void SyncIdArrayChangedLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArrayChanged(aAsync, iaIdArrayChanged);
}


class SyncIdsMaxLinnCoUkRadio1 : public SyncProxyAction
{
public:
    SyncIdsMaxLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, TUint& aaIdsMax);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1& iService;
    TUint& iaIdsMax;
};

SyncIdsMaxLinnCoUkRadio1::SyncIdsMaxLinnCoUkRadio1(CpProxyLinnCoUkRadio1& aService, TUint& aaIdsMax)
    : iService(aService)
    , iaIdsMax(aaIdsMax)
{
}

void SyncIdsMaxLinnCoUkRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdsMax(aAsync, iaIdsMax);
}


CpProxyLinnCoUkRadio1::CpProxyLinnCoUkRadio1(CpDevice& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1::ChannelUriPropertyChanged);
    iChannelUri = new PropertyString("ChannelUri", functor);
    iService->AddProperty(iChannelUri);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1::ChannelMetadataPropertyChanged);
    iChannelMetadata = new PropertyString("ChannelMetadata", functor);
    iService->AddProperty(iChannelMetadata);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1::TransportStatePropertyChanged);
    iTransportState = new PropertyString("TransportState", functor);
    iService->AddProperty(iTransportState);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1::ProtocolInfoPropertyChanged);
    iProtocolInfo = new PropertyString("ProtocolInfo", functor);
    iService->AddProperty(iProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1::IdPropertyChanged);
    iId = new PropertyUint("Id", functor);
    iService->AddProperty(iId);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary("IdArray", functor);
    iService->AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1::IdsMaxPropertyChanged);
    iIdsMax = new PropertyUint("IdsMax", functor);
    iService->AddProperty(iIdsMax);
}

CpProxyLinnCoUkRadio1::~CpProxyLinnCoUkRadio1()
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

void CpProxyLinnCoUkRadio1::SyncPlay()
{
    SyncPlayLinnCoUkRadio1 sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1::SyncPause()
{
    SyncPauseLinnCoUkRadio1 sync(*this);
    BeginPause(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginPause(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1::SyncStop()
{
    SyncStopLinnCoUkRadio1 sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1::SyncSeekSecondAbsolute(TUint aaSecond)
{
    SyncSeekSecondAbsoluteLinnCoUkRadio1 sync(*this);
    BeginSeekSecondAbsolute(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginSeekSecondAbsolute(TUint aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSecond));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndSeekSecondAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondAbsolute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1::SyncSeekSecondRelative(TInt aaSecond)
{
    SyncSeekSecondRelativeLinnCoUkRadio1 sync(*this);
    BeginSeekSecondRelative(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginSeekSecondRelative(TInt aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaSecond));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndSeekSecondRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondRelative"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1::SyncChannel(Brh& aaUri, Brh& aaMetadata)
{
    SyncChannelLinnCoUkRadio1 sync(*this, aaUri, aaMetadata);
    BeginChannel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginChannel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionChannel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionChannel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndChannel(IAsync& aAsync, Brh& aaUri, Brh& aaMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Channel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaUri);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaMetadata);
}

void CpProxyLinnCoUkRadio1::SyncSetChannel(const Brx& aaUri, const Brx& aaMetadata)
{
    SyncSetChannelLinnCoUkRadio1 sync(*this);
    BeginSetChannel(aaUri, aaMetadata, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginSetChannel(const Brx& aaUri, const Brx& aaMetadata, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetChannel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetChannel->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaUri));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaMetadata));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndSetChannel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetChannel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1::SyncProtocolInfo(Brh& aaInfo)
{
    SyncProtocolInfoLinnCoUkRadio1 sync(*this, aaInfo);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndProtocolInfo(IAsync& aAsync, Brh& aaInfo)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ProtocolInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaInfo);
}

void CpProxyLinnCoUkRadio1::SyncTransportState(Brh& aaState)
{
    SyncTransportStateLinnCoUkRadio1 sync(*this, aaState);
    BeginTransportState(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginTransportState(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTransportState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTransportState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndTransportState(IAsync& aAsync, Brh& aaState)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TransportState"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaState);
}

void CpProxyLinnCoUkRadio1::SyncId(TUint& aaId)
{
    SyncIdLinnCoUkRadio1 sync(*this, aaId);
    BeginId(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginId(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionId, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionId->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndId(IAsync& aAsync, TUint& aaId)
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

void CpProxyLinnCoUkRadio1::SyncSetId(TUint aaId, const Brx& aaUri)
{
    SyncSetIdLinnCoUkRadio1 sync(*this);
    BeginSetId(aaId, aaUri, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginSetId(TUint aaId, const Brx& aaUri, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaUri));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndSetId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1::SyncRead(TUint aaId, Brh& aaMetadata)
{
    SyncReadLinnCoUkRadio1 sync(*this, aaMetadata);
    BeginRead(aaId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginRead(TUint aaId, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkRadio1::EndRead(IAsync& aAsync, Brh& aaMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Read"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaMetadata);
}

void CpProxyLinnCoUkRadio1::SyncReadList(const Brx& aaIdList, Brh& aaMetadataList)
{
    SyncReadListLinnCoUkRadio1 sync(*this, aaMetadataList);
    BeginReadList(aaIdList, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginReadList(const Brx& aaIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaIdList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndReadList(IAsync& aAsync, Brh& aaMetadataList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ReadList"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaMetadataList);
}

void CpProxyLinnCoUkRadio1::SyncIdArray(TUint& aaIdArrayToken, Brh& aaIdArray)
{
    SyncIdArrayLinnCoUkRadio1 sync(*this, aaIdArrayToken, aaIdArray);
    BeginIdArray(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginIdArray(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdArray, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArray->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndIdArray(IAsync& aAsync, TUint& aaIdArrayToken, Brh& aaIdArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArray"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaIdArrayToken = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aaIdArray);
}

void CpProxyLinnCoUkRadio1::SyncIdArrayChanged(TUint aaIdArrayToken, TBool& aaIdArrayChanged)
{
    SyncIdArrayChangedLinnCoUkRadio1 sync(*this, aaIdArrayChanged);
    BeginIdArrayChanged(aaIdArrayToken, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginIdArrayChanged(TUint aaIdArrayToken, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkRadio1::EndIdArrayChanged(IAsync& aAsync, TBool& aaIdArrayChanged)
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

void CpProxyLinnCoUkRadio1::SyncIdsMax(TUint& aaIdsMax)
{
    SyncIdsMaxLinnCoUkRadio1 sync(*this, aaIdsMax);
    BeginIdsMax(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1::BeginIdsMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdsMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdsMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkRadio1::EndIdsMax(IAsync& aAsync, TUint& aaIdsMax)
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

void CpProxyLinnCoUkRadio1::SetPropertyChannelUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iChannelUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1::SetPropertyChannelMetadataChanged(Functor& aFunctor)
{
    iLock->Wait();
    iChannelMetadataChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransportStateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1::SetPropertyProtocolInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProtocolInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1::SetPropertyIdChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdArrayChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1::SetPropertyIdsMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdsMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkRadio1::PropertyChannelUri(Brhz& aChannelUri) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aChannelUri.Set(iChannelUri->Value());
}

void CpProxyLinnCoUkRadio1::PropertyChannelMetadata(Brhz& aChannelMetadata) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aChannelMetadata.Set(iChannelMetadata->Value());
}

void CpProxyLinnCoUkRadio1::PropertyTransportState(Brhz& aTransportState) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTransportState.Set(iTransportState->Value());
}

void CpProxyLinnCoUkRadio1::PropertyProtocolInfo(Brhz& aProtocolInfo) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProtocolInfo.Set(iProtocolInfo->Value());
}

void CpProxyLinnCoUkRadio1::PropertyId(TUint& aId) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aId = iId->Value();
}

void CpProxyLinnCoUkRadio1::PropertyIdArray(Brh& aIdArray) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aIdArray.Set(iIdArray->Value());
}

void CpProxyLinnCoUkRadio1::PropertyIdsMax(TUint& aIdsMax) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aIdsMax = iIdsMax->Value();
}

void CpProxyLinnCoUkRadio1::ChannelUriPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iChannelUriChanged != NULL) {
        iChannelUriChanged();
    }
}

void CpProxyLinnCoUkRadio1::ChannelMetadataPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iChannelMetadataChanged != NULL) {
        iChannelMetadataChanged();
    }
}

void CpProxyLinnCoUkRadio1::TransportStatePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTransportStateChanged != NULL) {
        iTransportStateChanged();
    }
}

void CpProxyLinnCoUkRadio1::ProtocolInfoPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProtocolInfoChanged != NULL) {
        iProtocolInfoChanged();
    }
}

void CpProxyLinnCoUkRadio1::IdPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iIdChanged != NULL) {
        iIdChanged();
    }
}

void CpProxyLinnCoUkRadio1::IdArrayPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iIdArrayChanged != NULL) {
        iIdArrayChanged();
    }
}

void CpProxyLinnCoUkRadio1::IdsMaxPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iIdsMaxChanged != NULL) {
        iIdsMaxChanged();
    }
}

