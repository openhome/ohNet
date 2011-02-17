#include "CpLinnCoUkRadio1.h"
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

class CpProxyLinnCoUkRadio1C : public CpProxyC
{
public:
    CpProxyLinnCoUkRadio1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkRadio1C();
    //CpProxyLinnCoUkRadio1* Proxy() { return static_cast<CpProxyLinnCoUkRadio1*>(iProxy); }

    void SyncPlay();
    void BeginPlay(FunctorAsync& aFunctor);
    void EndPlay(IAsync& aAsync);

    void SyncPause();
    void BeginPause(FunctorAsync& aFunctor);
    void EndPause(IAsync& aAsync);

    void SyncStop();
    void BeginStop(FunctorAsync& aFunctor);
    void EndStop(IAsync& aAsync);

    void SyncSeekSecondAbsolute(TUint aaSecond);
    void BeginSeekSecondAbsolute(TUint aaSecond, FunctorAsync& aFunctor);
    void EndSeekSecondAbsolute(IAsync& aAsync);

    void SyncSeekSecondRelative(TInt aaSecond);
    void BeginSeekSecondRelative(TInt aaSecond, FunctorAsync& aFunctor);
    void EndSeekSecondRelative(IAsync& aAsync);

    void SyncChannel(Brh& aaUri, Brh& aaMetadata);
    void BeginChannel(FunctorAsync& aFunctor);
    void EndChannel(IAsync& aAsync, Brh& aaUri, Brh& aaMetadata);

    void SyncSetChannel(const Brx& aaUri, const Brx& aaMetadata);
    void BeginSetChannel(const Brx& aaUri, const Brx& aaMetadata, FunctorAsync& aFunctor);
    void EndSetChannel(IAsync& aAsync);

    void SyncProtocolInfo(Brh& aaInfo);
    void BeginProtocolInfo(FunctorAsync& aFunctor);
    void EndProtocolInfo(IAsync& aAsync, Brh& aaInfo);

    void SyncTransportState(Brh& aaState);
    void BeginTransportState(FunctorAsync& aFunctor);
    void EndTransportState(IAsync& aAsync, Brh& aaState);

    void SyncId(TUint& aaId);
    void BeginId(FunctorAsync& aFunctor);
    void EndId(IAsync& aAsync, TUint& aaId);

    void SyncSetId(TUint aaId, const Brx& aaUri);
    void BeginSetId(TUint aaId, const Brx& aaUri, FunctorAsync& aFunctor);
    void EndSetId(IAsync& aAsync);

    void SyncRead(TUint aaId, Brh& aaMetadata);
    void BeginRead(TUint aaId, FunctorAsync& aFunctor);
    void EndRead(IAsync& aAsync, Brh& aaMetadata);

    void SyncReadList(const Brx& aaIdList, Brh& aaMetadataList);
    void BeginReadList(const Brx& aaIdList, FunctorAsync& aFunctor);
    void EndReadList(IAsync& aAsync, Brh& aaMetadataList);

    void SyncIdArray(TUint& aaIdArrayToken, Brh& aaIdArray);
    void BeginIdArray(FunctorAsync& aFunctor);
    void EndIdArray(IAsync& aAsync, TUint& aaIdArrayToken, Brh& aaIdArray);

    void SyncIdArrayChanged(TUint aaIdArrayToken, TBool& aaIdArrayChanged);
    void BeginIdArrayChanged(TUint aaIdArrayToken, FunctorAsync& aFunctor);
    void EndIdArrayChanged(IAsync& aAsync, TBool& aaIdArrayChanged);

    void SyncIdsMax(TUint& aaIdsMax);
    void BeginIdsMax(FunctorAsync& aFunctor);
    void EndIdsMax(IAsync& aAsync, TUint& aaIdsMax);

    void SetPropertyChannelUriChanged(Functor& aFunctor);
    void SetPropertyChannelMetadataChanged(Functor& aFunctor);
    void SetPropertyTransportStateChanged(Functor& aFunctor);
    void SetPropertyProtocolInfoChanged(Functor& aFunctor);
    void SetPropertyIdChanged(Functor& aFunctor);
    void SetPropertyIdArrayChanged(Functor& aFunctor);
    void SetPropertyIdsMaxChanged(Functor& aFunctor);

    void PropertyChannelUri(Brhz& aChannelUri) const;
    void PropertyChannelMetadata(Brhz& aChannelMetadata) const;
    void PropertyTransportState(Brhz& aTransportState) const;
    void PropertyProtocolInfo(Brhz& aProtocolInfo) const;
    void PropertyId(TUint& aId) const;
    void PropertyIdArray(Brh& aIdArray) const;
    void PropertyIdsMax(TUint& aIdsMax) const;
private:
    void ChannelUriPropertyChanged();
    void ChannelMetadataPropertyChanged();
    void TransportStatePropertyChanged();
    void ProtocolInfoPropertyChanged();
    void IdPropertyChanged();
    void IdArrayPropertyChanged();
    void IdsMaxPropertyChanged();
private:
    Mutex iLock;
    Action* iActionPlay;
    Action* iActionPause;
    Action* iActionStop;
    Action* iActionSeekSecondAbsolute;
    Action* iActionSeekSecondRelative;
    Action* iActionChannel;
    Action* iActionSetChannel;
    Action* iActionProtocolInfo;
    Action* iActionTransportState;
    Action* iActionId;
    Action* iActionSetId;
    Action* iActionRead;
    Action* iActionReadList;
    Action* iActionIdArray;
    Action* iActionIdArrayChanged;
    Action* iActionIdsMax;
    PropertyString* iChannelUri;
    PropertyString* iChannelMetadata;
    PropertyString* iTransportState;
    PropertyString* iProtocolInfo;
    PropertyUint* iId;
    PropertyBinary* iIdArray;
    PropertyUint* iIdsMax;
    Functor iChannelUriChanged;
    Functor iChannelMetadataChanged;
    Functor iTransportStateChanged;
    Functor iProtocolInfoChanged;
    Functor iIdChanged;
    Functor iIdArrayChanged;
    Functor iIdsMaxChanged;
};


class SyncPlayLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncPlayLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
};

SyncPlayLinnCoUkRadio1C::SyncPlayLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncPlayLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncPauseLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
};

SyncPauseLinnCoUkRadio1C::SyncPauseLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncPauseLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStopLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncStopLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
};

SyncStopLinnCoUkRadio1C::SyncStopLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncStopLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncSeekSecondAbsoluteLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncSeekSecondAbsoluteLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
};

SyncSeekSecondAbsoluteLinnCoUkRadio1C::SyncSeekSecondAbsoluteLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondAbsoluteLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondAbsolute(aAsync);
}


class SyncSeekSecondRelativeLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncSeekSecondRelativeLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
};

SyncSeekSecondRelativeLinnCoUkRadio1C::SyncSeekSecondRelativeLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondRelativeLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondRelative(aAsync);
}


class SyncChannelLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncChannelLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, Brh& aaUri, Brh& aaMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
    Brh& iaUri;
    Brh& iaMetadata;
};

SyncChannelLinnCoUkRadio1C::SyncChannelLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, Brh& aaUri, Brh& aaMetadata)
    : iService(aProxy)
    , iaUri(aaUri)
    , iaMetadata(aaMetadata)
{
}

void SyncChannelLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndChannel(aAsync, iaUri, iaMetadata);
}


class SyncSetChannelLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncSetChannelLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
};

SyncSetChannelLinnCoUkRadio1C::SyncSetChannelLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetChannelLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetChannel(aAsync);
}


class SyncProtocolInfoLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncProtocolInfoLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, Brh& aaInfo);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
    Brh& iaInfo;
};

SyncProtocolInfoLinnCoUkRadio1C::SyncProtocolInfoLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, Brh& aaInfo)
    : iService(aProxy)
    , iaInfo(aaInfo)
{
}

void SyncProtocolInfoLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iaInfo);
}


class SyncTransportStateLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncTransportStateLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, Brh& aaState);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
    Brh& iaState;
};

SyncTransportStateLinnCoUkRadio1C::SyncTransportStateLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, Brh& aaState)
    : iService(aProxy)
    , iaState(aaState)
{
}

void SyncTransportStateLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTransportState(aAsync, iaState);
}


class SyncIdLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncIdLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, TUint& aaId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
    TUint& iaId;
};

SyncIdLinnCoUkRadio1C::SyncIdLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, TUint& aaId)
    : iService(aProxy)
    , iaId(aaId)
{
}

void SyncIdLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndId(aAsync, iaId);
}


class SyncSetIdLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncSetIdLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
};

SyncSetIdLinnCoUkRadio1C::SyncSetIdLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetIdLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetId(aAsync);
}


class SyncReadLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncReadLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, Brh& aaMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
    Brh& iaMetadata;
};

SyncReadLinnCoUkRadio1C::SyncReadLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, Brh& aaMetadata)
    : iService(aProxy)
    , iaMetadata(aaMetadata)
{
}

void SyncReadLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iaMetadata);
}


class SyncReadListLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncReadListLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, Brh& aaMetadataList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
    Brh& iaMetadataList;
};

SyncReadListLinnCoUkRadio1C::SyncReadListLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, Brh& aaMetadataList)
    : iService(aProxy)
    , iaMetadataList(aaMetadataList)
{
}

void SyncReadListLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iaMetadataList);
}


class SyncIdArrayLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncIdArrayLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, TUint& aaIdArrayToken, Brh& aaIdArray);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
    TUint& iaIdArrayToken;
    Brh& iaIdArray;
};

SyncIdArrayLinnCoUkRadio1C::SyncIdArrayLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, TUint& aaIdArrayToken, Brh& aaIdArray)
    : iService(aProxy)
    , iaIdArrayToken(aaIdArrayToken)
    , iaIdArray(aaIdArray)
{
}

void SyncIdArrayLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArray(aAsync, iaIdArrayToken, iaIdArray);
}


class SyncIdArrayChangedLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncIdArrayChangedLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, TBool& aaIdArrayChanged);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
    TBool& iaIdArrayChanged;
};

SyncIdArrayChangedLinnCoUkRadio1C::SyncIdArrayChangedLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, TBool& aaIdArrayChanged)
    : iService(aProxy)
    , iaIdArrayChanged(aaIdArrayChanged)
{
}

void SyncIdArrayChangedLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArrayChanged(aAsync, iaIdArrayChanged);
}


class SyncIdsMaxLinnCoUkRadio1C : public SyncProxyAction
{
public:
    SyncIdsMaxLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, TUint& aaIdsMax);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkRadio1C& iService;
    TUint& iaIdsMax;
};

SyncIdsMaxLinnCoUkRadio1C::SyncIdsMaxLinnCoUkRadio1C(CpProxyLinnCoUkRadio1C& aProxy, TUint& aaIdsMax)
    : iService(aProxy)
    , iaIdsMax(aaIdsMax)
{
}

void SyncIdsMaxLinnCoUkRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdsMax(aAsync, iaIdsMax);
}

CpProxyLinnCoUkRadio1C::CpProxyLinnCoUkRadio1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Radio", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1C::ChannelUriPropertyChanged);
    iChannelUri = new PropertyString("ChannelUri", functor);
    AddProperty(iChannelUri);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1C::ChannelMetadataPropertyChanged);
    iChannelMetadata = new PropertyString("ChannelMetadata", functor);
    AddProperty(iChannelMetadata);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1C::TransportStatePropertyChanged);
    iTransportState = new PropertyString("TransportState", functor);
    AddProperty(iTransportState);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1C::ProtocolInfoPropertyChanged);
    iProtocolInfo = new PropertyString("ProtocolInfo", functor);
    AddProperty(iProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1C::IdPropertyChanged);
    iId = new PropertyUint("Id", functor);
    AddProperty(iId);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1C::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary("IdArray", functor);
    AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkRadio1C::IdsMaxPropertyChanged);
    iIdsMax = new PropertyUint("IdsMax", functor);
    AddProperty(iIdsMax);
}

CpProxyLinnCoUkRadio1C::~CpProxyLinnCoUkRadio1C()
{
    DestroyService();
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

void CpProxyLinnCoUkRadio1C::SyncPlay()
{
    SyncPlayLinnCoUkRadio1C sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlay, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1C::SyncPause()
{
    SyncPauseLinnCoUkRadio1C sync(*this);
    BeginPause(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginPause(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPause, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1C::SyncStop()
{
    SyncStopLinnCoUkRadio1C sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStop, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1C::SyncSeekSecondAbsolute(TUint aaSecond)
{
    SyncSeekSecondAbsoluteLinnCoUkRadio1C sync(*this);
    BeginSeekSecondAbsolute(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginSeekSecondAbsolute(TUint aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekSecondAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSecond));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndSeekSecondAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondAbsolute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1C::SyncSeekSecondRelative(TInt aaSecond)
{
    SyncSeekSecondRelativeLinnCoUkRadio1C sync(*this);
    BeginSeekSecondRelative(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginSeekSecondRelative(TInt aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekSecondRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaSecond));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndSeekSecondRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondRelative"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1C::SyncChannel(Brh& aaUri, Brh& aaMetadata)
{
    SyncChannelLinnCoUkRadio1C sync(*this, aaUri, aaMetadata);
    BeginChannel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginChannel(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionChannel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionChannel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndChannel(IAsync& aAsync, Brh& aaUri, Brh& aaMetadata)
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

void CpProxyLinnCoUkRadio1C::SyncSetChannel(const Brx& aaUri, const Brx& aaMetadata)
{
    SyncSetChannelLinnCoUkRadio1C sync(*this);
    BeginSetChannel(aaUri, aaMetadata, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginSetChannel(const Brx& aaUri, const Brx& aaMetadata, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetChannel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetChannel->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaUri));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaMetadata));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndSetChannel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetChannel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1C::SyncProtocolInfo(Brh& aaInfo)
{
    SyncProtocolInfoLinnCoUkRadio1C sync(*this, aaInfo);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndProtocolInfo(IAsync& aAsync, Brh& aaInfo)
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

void CpProxyLinnCoUkRadio1C::SyncTransportState(Brh& aaState)
{
    SyncTransportStateLinnCoUkRadio1C sync(*this, aaState);
    BeginTransportState(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginTransportState(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTransportState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTransportState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndTransportState(IAsync& aAsync, Brh& aaState)
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

void CpProxyLinnCoUkRadio1C::SyncId(TUint& aaId)
{
    SyncIdLinnCoUkRadio1C sync(*this, aaId);
    BeginId(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginId(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionId, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionId->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndId(IAsync& aAsync, TUint& aaId)
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

void CpProxyLinnCoUkRadio1C::SyncSetId(TUint aaId, const Brx& aaUri)
{
    SyncSetIdLinnCoUkRadio1C sync(*this);
    BeginSetId(aaId, aaUri, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginSetId(TUint aaId, const Brx& aaUri, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaUri));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndSetId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkRadio1C::SyncRead(TUint aaId, Brh& aaMetadata)
{
    SyncReadLinnCoUkRadio1C sync(*this, aaMetadata);
    BeginRead(aaId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginRead(TUint aaId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndRead(IAsync& aAsync, Brh& aaMetadata)
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

void CpProxyLinnCoUkRadio1C::SyncReadList(const Brx& aaIdList, Brh& aaMetadataList)
{
    SyncReadListLinnCoUkRadio1C sync(*this, aaMetadataList);
    BeginReadList(aaIdList, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginReadList(const Brx& aaIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaIdList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndReadList(IAsync& aAsync, Brh& aaMetadataList)
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

void CpProxyLinnCoUkRadio1C::SyncIdArray(TUint& aaIdArrayToken, Brh& aaIdArray)
{
    SyncIdArrayLinnCoUkRadio1C sync(*this, aaIdArrayToken, aaIdArray);
    BeginIdArray(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginIdArray(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionIdArray, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArray->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndIdArray(IAsync& aAsync, TUint& aaIdArrayToken, Brh& aaIdArray)
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

void CpProxyLinnCoUkRadio1C::SyncIdArrayChanged(TUint aaIdArrayToken, TBool& aaIdArrayChanged)
{
    SyncIdArrayChangedLinnCoUkRadio1C sync(*this, aaIdArrayChanged);
    BeginIdArrayChanged(aaIdArrayToken, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginIdArrayChanged(TUint aaIdArrayToken, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionIdArrayChanged, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionIdArrayChanged->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaIdArrayToken));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArrayChanged->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndIdArrayChanged(IAsync& aAsync, TBool& aaIdArrayChanged)
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

void CpProxyLinnCoUkRadio1C::SyncIdsMax(TUint& aaIdsMax)
{
    SyncIdsMaxLinnCoUkRadio1C sync(*this, aaIdsMax);
    BeginIdsMax(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkRadio1C::BeginIdsMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionIdsMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdsMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkRadio1C::EndIdsMax(IAsync& aAsync, TUint& aaIdsMax)
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

void CpProxyLinnCoUkRadio1C::SetPropertyChannelUriChanged(Functor& aFunctor)
{
    iLock.Wait();
    iChannelUriChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkRadio1C::SetPropertyChannelMetadataChanged(Functor& aFunctor)
{
    iLock.Wait();
    iChannelMetadataChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkRadio1C::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTransportStateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkRadio1C::SetPropertyProtocolInfoChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProtocolInfoChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkRadio1C::SetPropertyIdChanged(Functor& aFunctor)
{
    iLock.Wait();
    iIdChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkRadio1C::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock.Wait();
    iIdArrayChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkRadio1C::SetPropertyIdsMaxChanged(Functor& aFunctor)
{
    iLock.Wait();
    iIdsMaxChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkRadio1C::PropertyChannelUri(Brhz& aChannelUri) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aChannelUri.Set(iChannelUri->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkRadio1C::PropertyChannelMetadata(Brhz& aChannelMetadata) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aChannelMetadata.Set(iChannelMetadata->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkRadio1C::PropertyTransportState(Brhz& aTransportState) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aTransportState.Set(iTransportState->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkRadio1C::PropertyProtocolInfo(Brhz& aProtocolInfo) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aProtocolInfo.Set(iProtocolInfo->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkRadio1C::PropertyId(TUint& aId) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aId = iId->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkRadio1C::PropertyIdArray(Brh& aIdArray) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aIdArray.Set(iIdArray->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkRadio1C::PropertyIdsMax(TUint& aIdsMax) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aIdsMax = iIdsMax->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkRadio1C::ChannelUriPropertyChanged()
{
    ReportEvent(iChannelUriChanged);
}

void CpProxyLinnCoUkRadio1C::ChannelMetadataPropertyChanged()
{
    ReportEvent(iChannelMetadataChanged);
}

void CpProxyLinnCoUkRadio1C::TransportStatePropertyChanged()
{
    ReportEvent(iTransportStateChanged);
}

void CpProxyLinnCoUkRadio1C::ProtocolInfoPropertyChanged()
{
    ReportEvent(iProtocolInfoChanged);
}

void CpProxyLinnCoUkRadio1C::IdPropertyChanged()
{
    ReportEvent(iIdChanged);
}

void CpProxyLinnCoUkRadio1C::IdArrayPropertyChanged()
{
    ReportEvent(iIdArrayChanged);
}

void CpProxyLinnCoUkRadio1C::IdsMaxPropertyChanged()
{
    ReportEvent(iIdsMaxChanged);
}


THandle CpProxyLinnCoUkRadio1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkRadio1C(aDevice);
}

void CpProxyLinnCoUkRadio1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkRadio1SyncPlay(THandle aHandle)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncPlay();
}

void CpProxyLinnCoUkRadio1BeginPlay(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginPlay(functor);
}

int32_t CpProxyLinnCoUkRadio1EndPlay(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPlay(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncPause(THandle aHandle)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncPause();
}

void CpProxyLinnCoUkRadio1BeginPause(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginPause(functor);
}

int32_t CpProxyLinnCoUkRadio1EndPause(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPause(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncStop(THandle aHandle)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStop();
}

void CpProxyLinnCoUkRadio1BeginStop(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStop(functor);
}

int32_t CpProxyLinnCoUkRadio1EndStop(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStop(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncSeekSecondAbsolute(THandle aHandle, uint32_t aaSecond)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSeekSecondAbsolute(aaSecond);
}

void CpProxyLinnCoUkRadio1BeginSeekSecondAbsolute(THandle aHandle, uint32_t aaSecond, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSeekSecondAbsolute(aaSecond, functor);
}

int32_t CpProxyLinnCoUkRadio1EndSeekSecondAbsolute(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeekSecondAbsolute(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncSeekSecondRelative(THandle aHandle, int32_t aaSecond)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSeekSecondRelative(aaSecond);
}

void CpProxyLinnCoUkRadio1BeginSeekSecondRelative(THandle aHandle, int32_t aaSecond, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSeekSecondRelative(aaSecond, functor);
}

int32_t CpProxyLinnCoUkRadio1EndSeekSecondRelative(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeekSecondRelative(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncChannel(THandle aHandle, char** aaUri, char** aaMetadata)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri;
    Brh buf_aaMetadata;
    proxyC->SyncChannel(buf_aaUri, buf_aaMetadata);
    *aaUri = buf_aaUri.Extract();
    *aaMetadata = buf_aaMetadata.Extract();
}

void CpProxyLinnCoUkRadio1BeginChannel(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginChannel(functor);
}

int32_t CpProxyLinnCoUkRadio1EndChannel(THandle aHandle, ZappHandleAsync aAsync, char** aaUri, char** aaMetadata)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaUri;
    *aaUri = NULL;
    Brh buf_aaMetadata;
    *aaMetadata = NULL;
    try {
        proxyC->EndChannel(*async, buf_aaUri, buf_aaMetadata);
        *aaUri = buf_aaUri.Extract();
        *aaMetadata = buf_aaMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncSetChannel(THandle aHandle, const char* aaUri, const char* aaMetadata)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    Brh buf_aaMetadata(aaMetadata);
    proxyC->SyncSetChannel(buf_aaUri, buf_aaMetadata);
}

void CpProxyLinnCoUkRadio1BeginSetChannel(THandle aHandle, const char* aaUri, const char* aaMetadata, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    Brh buf_aaMetadata(aaMetadata);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetChannel(buf_aaUri, buf_aaMetadata, functor);
}

int32_t CpProxyLinnCoUkRadio1EndSetChannel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetChannel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncProtocolInfo(THandle aHandle, char** aaInfo)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaInfo;
    proxyC->SyncProtocolInfo(buf_aaInfo);
    *aaInfo = buf_aaInfo.Extract();
}

void CpProxyLinnCoUkRadio1BeginProtocolInfo(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginProtocolInfo(functor);
}

int32_t CpProxyLinnCoUkRadio1EndProtocolInfo(THandle aHandle, ZappHandleAsync aAsync, char** aaInfo)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaInfo;
    *aaInfo = NULL;
    try {
        proxyC->EndProtocolInfo(*async, buf_aaInfo);
        *aaInfo = buf_aaInfo.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncTransportState(THandle aHandle, char** aaState)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaState;
    proxyC->SyncTransportState(buf_aaState);
    *aaState = buf_aaState.Extract();
}

void CpProxyLinnCoUkRadio1BeginTransportState(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginTransportState(functor);
}

int32_t CpProxyLinnCoUkRadio1EndTransportState(THandle aHandle, ZappHandleAsync aAsync, char** aaState)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaState;
    *aaState = NULL;
    try {
        proxyC->EndTransportState(*async, buf_aaState);
        *aaState = buf_aaState.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncId(THandle aHandle, uint32_t* aaId)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncId(*aaId);
}

void CpProxyLinnCoUkRadio1BeginId(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginId(functor);
}

int32_t CpProxyLinnCoUkRadio1EndId(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaId)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndId(*async, *aaId);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncSetId(THandle aHandle, uint32_t aaId, const char* aaUri)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    proxyC->SyncSetId(aaId, buf_aaUri);
}

void CpProxyLinnCoUkRadio1BeginSetId(THandle aHandle, uint32_t aaId, const char* aaUri, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetId(aaId, buf_aaUri, functor);
}

int32_t CpProxyLinnCoUkRadio1EndSetId(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetId(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncRead(THandle aHandle, uint32_t aaId, char** aaMetadata)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMetadata;
    proxyC->SyncRead(aaId, buf_aaMetadata);
    *aaMetadata = buf_aaMetadata.Extract();
}

void CpProxyLinnCoUkRadio1BeginRead(THandle aHandle, uint32_t aaId, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginRead(aaId, functor);
}

int32_t CpProxyLinnCoUkRadio1EndRead(THandle aHandle, ZappHandleAsync aAsync, char** aaMetadata)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMetadata;
    *aaMetadata = NULL;
    try {
        proxyC->EndRead(*async, buf_aaMetadata);
        *aaMetadata = buf_aaMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncReadList(THandle aHandle, const char* aaIdList, char** aaMetadataList)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdList(aaIdList);
    Brh buf_aaMetadataList;
    proxyC->SyncReadList(buf_aaIdList, buf_aaMetadataList);
    *aaMetadataList = buf_aaMetadataList.Extract();
}

void CpProxyLinnCoUkRadio1BeginReadList(THandle aHandle, const char* aaIdList, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdList(aaIdList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginReadList(buf_aaIdList, functor);
}

int32_t CpProxyLinnCoUkRadio1EndReadList(THandle aHandle, ZappHandleAsync aAsync, char** aaMetadataList)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMetadataList;
    *aaMetadataList = NULL;
    try {
        proxyC->EndReadList(*async, buf_aaMetadataList);
        *aaMetadataList = buf_aaMetadataList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncIdArray(THandle aHandle, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdArray;
    proxyC->SyncIdArray(*aaIdArrayToken, buf_aaIdArray);
    *aaIdArrayLen = buf_aaIdArray.Bytes();
    *aaIdArray = buf_aaIdArray.Extract();
}

void CpProxyLinnCoUkRadio1BeginIdArray(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginIdArray(functor);
}

int32_t CpProxyLinnCoUkRadio1EndIdArray(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaIdArray;
    *aaIdArray = NULL;
    *aaIdArrayLen = 0;
    try {
        proxyC->EndIdArray(*async, *aaIdArrayToken, buf_aaIdArray);
        *aaIdArrayLen = buf_aaIdArray.Bytes();
        *aaIdArray = buf_aaIdArray.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncIdArrayChanged(THandle aHandle, uint32_t aaIdArrayToken, uint32_t* aaIdArrayChanged)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaIdArrayChanged = 0;
    proxyC->SyncIdArrayChanged(aaIdArrayToken, *(TBool*)aaIdArrayChanged);
}

void CpProxyLinnCoUkRadio1BeginIdArrayChanged(THandle aHandle, uint32_t aaIdArrayToken, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginIdArrayChanged(aaIdArrayToken, functor);
}

int32_t CpProxyLinnCoUkRadio1EndIdArrayChanged(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdArrayChanged)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaIdArrayChanged = 0;
    try {
        proxyC->EndIdArrayChanged(*async, *(TBool*)aaIdArrayChanged);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncIdsMax(THandle aHandle, uint32_t* aaIdsMax)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncIdsMax(*aaIdsMax);
}

void CpProxyLinnCoUkRadio1BeginIdsMax(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginIdsMax(functor);
}

int32_t CpProxyLinnCoUkRadio1EndIdsMax(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdsMax)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndIdsMax(*async, *aaIdsMax);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SetPropertyChannelUriChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyChannelUriChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyChannelMetadataChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyChannelMetadataChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyTransportStateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTransportStateChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyProtocolInfoChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProtocolInfoChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyIdChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyIdChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyIdArrayChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyIdArrayChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyIdsMaxChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyIdsMaxChanged(functor);
}

void CpProxyLinnCoUkRadio1PropertyChannelUri(THandle aHandle, char** aChannelUri)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aChannelUri;
    proxyC->PropertyChannelUri(buf_aChannelUri);
    *aChannelUri = buf_aChannelUri.Transfer();
}

void CpProxyLinnCoUkRadio1PropertyChannelMetadata(THandle aHandle, char** aChannelMetadata)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aChannelMetadata;
    proxyC->PropertyChannelMetadata(buf_aChannelMetadata);
    *aChannelMetadata = buf_aChannelMetadata.Transfer();
}

void CpProxyLinnCoUkRadio1PropertyTransportState(THandle aHandle, char** aTransportState)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransportState;
    proxyC->PropertyTransportState(buf_aTransportState);
    *aTransportState = buf_aTransportState.Transfer();
}

void CpProxyLinnCoUkRadio1PropertyProtocolInfo(THandle aHandle, char** aProtocolInfo)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProtocolInfo;
    proxyC->PropertyProtocolInfo(buf_aProtocolInfo);
    *aProtocolInfo = buf_aProtocolInfo.Transfer();
}

void CpProxyLinnCoUkRadio1PropertyId(THandle aHandle, uint32_t* aId)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyId(*aId);
}

void CpProxyLinnCoUkRadio1PropertyIdArray(THandle aHandle, char** aIdArray, uint32_t* aLen)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdArray;
    proxyC->PropertyIdArray(buf_aIdArray);
    *aLen = buf_aIdArray.Bytes();
    *aIdArray = buf_aIdArray.Extract();
}

void CpProxyLinnCoUkRadio1PropertyIdsMax(THandle aHandle, uint32_t* aIdsMax)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyIdsMax(*aIdsMax);
}

