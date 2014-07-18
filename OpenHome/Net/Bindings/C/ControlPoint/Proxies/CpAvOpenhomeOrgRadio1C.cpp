#include "CpAvOpenhomeOrgRadio1.h"
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/C/CpProxyCPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class CpProxyAvOpenhomeOrgRadio1C : public CpProxyC
{
public:
    CpProxyAvOpenhomeOrgRadio1C(CpDeviceC aDevice);
    ~CpProxyAvOpenhomeOrgRadio1C();
    //CpProxyAvOpenhomeOrgRadio1* Proxy() { return static_cast<CpProxyAvOpenhomeOrgRadio1*>(iProxy); }

    void SyncPlay();
    void BeginPlay(FunctorAsync& aFunctor);
    void EndPlay(IAsync& aAsync);

    void SyncPause();
    void BeginPause(FunctorAsync& aFunctor);
    void EndPause(IAsync& aAsync);

    void SyncStop();
    void BeginStop(FunctorAsync& aFunctor);
    void EndStop(IAsync& aAsync);

    void SyncSeekSecondAbsolute(TUint aValue);
    void BeginSeekSecondAbsolute(TUint aValue, FunctorAsync& aFunctor);
    void EndSeekSecondAbsolute(IAsync& aAsync);

    void SyncSeekSecondRelative(TInt aValue);
    void BeginSeekSecondRelative(TInt aValue, FunctorAsync& aFunctor);
    void EndSeekSecondRelative(IAsync& aAsync);

    void SyncChannel(Brh& aUri, Brh& aMetadata);
    void BeginChannel(FunctorAsync& aFunctor);
    void EndChannel(IAsync& aAsync, Brh& aUri, Brh& aMetadata);

    void SyncSetChannel(const Brx& aUri, const Brx& aMetadata);
    void BeginSetChannel(const Brx& aUri, const Brx& aMetadata, FunctorAsync& aFunctor);
    void EndSetChannel(IAsync& aAsync);

    void SyncTransportState(Brh& aValue);
    void BeginTransportState(FunctorAsync& aFunctor);
    void EndTransportState(IAsync& aAsync, Brh& aValue);

    void SyncId(TUint& aValue);
    void BeginId(FunctorAsync& aFunctor);
    void EndId(IAsync& aAsync, TUint& aValue);

    void SyncSetId(TUint aValue, const Brx& aUri);
    void BeginSetId(TUint aValue, const Brx& aUri, FunctorAsync& aFunctor);
    void EndSetId(IAsync& aAsync);

    void SyncRead(TUint aId, Brh& aMetadata);
    void BeginRead(TUint aId, FunctorAsync& aFunctor);
    void EndRead(IAsync& aAsync, Brh& aMetadata);

    void SyncReadList(const Brx& aIdList, Brh& aChannelList);
    void BeginReadList(const Brx& aIdList, FunctorAsync& aFunctor);
    void EndReadList(IAsync& aAsync, Brh& aChannelList);

    void SyncIdArray(TUint& aToken, Brh& aArray);
    void BeginIdArray(FunctorAsync& aFunctor);
    void EndIdArray(IAsync& aAsync, TUint& aToken, Brh& aArray);

    void SyncIdArrayChanged(TUint aToken, TBool& aValue);
    void BeginIdArrayChanged(TUint aToken, FunctorAsync& aFunctor);
    void EndIdArrayChanged(IAsync& aAsync, TBool& aValue);

    void SyncChannelsMax(TUint& aValue);
    void BeginChannelsMax(FunctorAsync& aFunctor);
    void EndChannelsMax(IAsync& aAsync, TUint& aValue);

    void SyncProtocolInfo(Brh& aValue);
    void BeginProtocolInfo(FunctorAsync& aFunctor);
    void EndProtocolInfo(IAsync& aAsync, Brh& aValue);

    void SetPropertyUriChanged(Functor& aFunctor);
    void SetPropertyMetadataChanged(Functor& aFunctor);
    void SetPropertyTransportStateChanged(Functor& aFunctor);
    void SetPropertyIdChanged(Functor& aFunctor);
    void SetPropertyIdArrayChanged(Functor& aFunctor);
    void SetPropertyChannelsMaxChanged(Functor& aFunctor);
    void SetPropertyProtocolInfoChanged(Functor& aFunctor);

    void PropertyUri(Brhz& aUri) const;
    void PropertyMetadata(Brhz& aMetadata) const;
    void PropertyTransportState(Brhz& aTransportState) const;
    void PropertyId(TUint& aId) const;
    void PropertyIdArray(Brh& aIdArray) const;
    void PropertyChannelsMax(TUint& aChannelsMax) const;
    void PropertyProtocolInfo(Brhz& aProtocolInfo) const;
private:
    void UriPropertyChanged();
    void MetadataPropertyChanged();
    void TransportStatePropertyChanged();
    void IdPropertyChanged();
    void IdArrayPropertyChanged();
    void ChannelsMaxPropertyChanged();
    void ProtocolInfoPropertyChanged();
private:
    Mutex iLock;
    Action* iActionPlay;
    Action* iActionPause;
    Action* iActionStop;
    Action* iActionSeekSecondAbsolute;
    Action* iActionSeekSecondRelative;
    Action* iActionChannel;
    Action* iActionSetChannel;
    Action* iActionTransportState;
    Action* iActionId;
    Action* iActionSetId;
    Action* iActionRead;
    Action* iActionReadList;
    Action* iActionIdArray;
    Action* iActionIdArrayChanged;
    Action* iActionChannelsMax;
    Action* iActionProtocolInfo;
    PropertyString* iUri;
    PropertyString* iMetadata;
    PropertyString* iTransportState;
    PropertyUint* iId;
    PropertyBinary* iIdArray;
    PropertyUint* iChannelsMax;
    PropertyString* iProtocolInfo;
    Functor iUriChanged;
    Functor iMetadataChanged;
    Functor iTransportStateChanged;
    Functor iIdChanged;
    Functor iIdArrayChanged;
    Functor iChannelsMaxChanged;
    Functor iProtocolInfoChanged;
};


class SyncPlayAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncPlayAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlayAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
};

SyncPlayAvOpenhomeOrgRadio1C::SyncPlayAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncPlayAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncPauseAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPauseAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
};

SyncPauseAvOpenhomeOrgRadio1C::SyncPauseAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncPauseAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStopAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncStopAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
};

SyncStopAvOpenhomeOrgRadio1C::SyncStopAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncStopAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
};

SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1C::SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondAbsolute(aAsync);
}


class SyncSeekSecondRelativeAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncSeekSecondRelativeAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekSecondRelativeAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
};

SyncSeekSecondRelativeAvOpenhomeOrgRadio1C::SyncSeekSecondRelativeAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondRelativeAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondRelative(aAsync);
}


class SyncChannelAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncChannelAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, Brh& aUri, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncChannelAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
    Brh& iUri;
    Brh& iMetadata;
};

SyncChannelAvOpenhomeOrgRadio1C::SyncChannelAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, Brh& aUri, Brh& aMetadata)
    : iService(aProxy)
    , iUri(aUri)
    , iMetadata(aMetadata)
{
}

void SyncChannelAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndChannel(aAsync, iUri, iMetadata);
}


class SyncSetChannelAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncSetChannelAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetChannelAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
};

SyncSetChannelAvOpenhomeOrgRadio1C::SyncSetChannelAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetChannelAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetChannel(aAsync);
}


class SyncTransportStateAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncTransportStateAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTransportStateAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
    Brh& iValue;
};

SyncTransportStateAvOpenhomeOrgRadio1C::SyncTransportStateAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTransportStateAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTransportState(aAsync, iValue);
}


class SyncIdAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncIdAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
    TUint& iValue;
};

SyncIdAvOpenhomeOrgRadio1C::SyncIdAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncIdAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndId(aAsync, iValue);
}


class SyncSetIdAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncSetIdAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetIdAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
};

SyncSetIdAvOpenhomeOrgRadio1C::SyncSetIdAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetIdAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetId(aAsync);
}


class SyncReadAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncReadAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncReadAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
    Brh& iMetadata;
};

SyncReadAvOpenhomeOrgRadio1C::SyncReadAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, Brh& aMetadata)
    : iService(aProxy)
    , iMetadata(aMetadata)
{
}

void SyncReadAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iMetadata);
}


class SyncReadListAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncReadListAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, Brh& aChannelList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncReadListAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
    Brh& iChannelList;
};

SyncReadListAvOpenhomeOrgRadio1C::SyncReadListAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, Brh& aChannelList)
    : iService(aProxy)
    , iChannelList(aChannelList)
{
}

void SyncReadListAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iChannelList);
}


class SyncIdArrayAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncIdArrayAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, TUint& aToken, Brh& aArray);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdArrayAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
    TUint& iToken;
    Brh& iArray;
};

SyncIdArrayAvOpenhomeOrgRadio1C::SyncIdArrayAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, TUint& aToken, Brh& aArray)
    : iService(aProxy)
    , iToken(aToken)
    , iArray(aArray)
{
}

void SyncIdArrayAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArray(aAsync, iToken, iArray);
}


class SyncIdArrayChangedAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncIdArrayChangedAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, TBool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdArrayChangedAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
    TBool& iValue;
};

SyncIdArrayChangedAvOpenhomeOrgRadio1C::SyncIdArrayChangedAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, TBool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncIdArrayChangedAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArrayChanged(aAsync, iValue);
}


class SyncChannelsMaxAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncChannelsMaxAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncChannelsMaxAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
    TUint& iValue;
};

SyncChannelsMaxAvOpenhomeOrgRadio1C::SyncChannelsMaxAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncChannelsMaxAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndChannelsMax(aAsync, iValue);
}


class SyncProtocolInfoAvOpenhomeOrgRadio1C : public SyncProxyAction
{
public:
    SyncProtocolInfoAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncProtocolInfoAvOpenhomeOrgRadio1C() {};
private:
    CpProxyAvOpenhomeOrgRadio1C& iService;
    Brh& iValue;
};

SyncProtocolInfoAvOpenhomeOrgRadio1C::SyncProtocolInfoAvOpenhomeOrgRadio1C(CpProxyAvOpenhomeOrgRadio1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncProtocolInfoAvOpenhomeOrgRadio1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iValue);
}

CpProxyAvOpenhomeOrgRadio1C::CpProxyAvOpenhomeOrgRadio1C(CpDeviceC aDevice)
    : CpProxyC("av-openhome-org", "Radio", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionPlay = new Action("Play");

    iActionPause = new Action("Pause");

    iActionStop = new Action("Stop");

    iActionSeekSecondAbsolute = new Action("SeekSecondAbsolute");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSeekSecondAbsolute->AddInputParameter(param);

    iActionSeekSecondRelative = new Action("SeekSecondRelative");
    param = new OpenHome::Net::ParameterInt("Value");
    iActionSeekSecondRelative->AddInputParameter(param);

    iActionChannel = new Action("Channel");
    param = new OpenHome::Net::ParameterString("Uri");
    iActionChannel->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionChannel->AddOutputParameter(param);

    iActionSetChannel = new Action("SetChannel");
    param = new OpenHome::Net::ParameterString("Uri");
    iActionSetChannel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionSetChannel->AddInputParameter(param);

    iActionTransportState = new Action("TransportState");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Buffering";
    param = new OpenHome::Net::ParameterString("Value", allowedValues, 4);
    iActionTransportState->AddOutputParameter(param);
    delete[] allowedValues;

    iActionId = new Action("Id");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionId->AddOutputParameter(param);

    iActionSetId = new Action("SetId");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSetId->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Uri");
    iActionSetId->AddInputParameter(param);

    iActionRead = new Action("Read");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionRead->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionRead->AddOutputParameter(param);

    iActionReadList = new Action("ReadList");
    param = new OpenHome::Net::ParameterString("IdList");
    iActionReadList->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ChannelList");
    iActionReadList->AddOutputParameter(param);

    iActionIdArray = new Action("IdArray");
    param = new OpenHome::Net::ParameterUint("Token");
    iActionIdArray->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterBinary("Array");
    iActionIdArray->AddOutputParameter(param);

    iActionIdArrayChanged = new Action("IdArrayChanged");
    param = new OpenHome::Net::ParameterUint("Token");
    iActionIdArrayChanged->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("Value");
    iActionIdArrayChanged->AddOutputParameter(param);

    iActionChannelsMax = new Action("ChannelsMax");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionChannelsMax->AddOutputParameter(param);

    iActionProtocolInfo = new Action("ProtocolInfo");
    param = new OpenHome::Net::ParameterString("Value");
    iActionProtocolInfo->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1C::UriPropertyChanged);
    iUri = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Uri", functor);
    AddProperty(iUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1C::MetadataPropertyChanged);
    iMetadata = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1C::TransportStatePropertyChanged);
    iTransportState = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "TransportState", functor);
    AddProperty(iTransportState);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1C::IdPropertyChanged);
    iId = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Id", functor);
    AddProperty(iId);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1C::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "IdArray", functor);
    AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1C::ChannelsMaxPropertyChanged);
    iChannelsMax = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "ChannelsMax", functor);
    AddProperty(iChannelsMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1C::ProtocolInfoPropertyChanged);
    iProtocolInfo = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "ProtocolInfo", functor);
    AddProperty(iProtocolInfo);
}

CpProxyAvOpenhomeOrgRadio1C::~CpProxyAvOpenhomeOrgRadio1C()
{
    DestroyService();
    delete iActionPlay;
    delete iActionPause;
    delete iActionStop;
    delete iActionSeekSecondAbsolute;
    delete iActionSeekSecondRelative;
    delete iActionChannel;
    delete iActionSetChannel;
    delete iActionTransportState;
    delete iActionId;
    delete iActionSetId;
    delete iActionRead;
    delete iActionReadList;
    delete iActionIdArray;
    delete iActionIdArrayChanged;
    delete iActionChannelsMax;
    delete iActionProtocolInfo;
}

void CpProxyAvOpenhomeOrgRadio1C::SyncPlay()
{
    SyncPlayAvOpenhomeOrgRadio1C sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlay, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgRadio1C::SyncPause()
{
    SyncPauseAvOpenhomeOrgRadio1C sync(*this);
    BeginPause(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginPause(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPause, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgRadio1C::SyncStop()
{
    SyncStopAvOpenhomeOrgRadio1C sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStop, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgRadio1C::SyncSeekSecondAbsolute(TUint aValue)
{
    SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1C sync(*this);
    BeginSeekSecondAbsolute(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginSeekSecondAbsolute(TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekSecondAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndSeekSecondAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondAbsolute"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgRadio1C::SyncSeekSecondRelative(TInt aValue)
{
    SyncSeekSecondRelativeAvOpenhomeOrgRadio1C sync(*this);
    BeginSeekSecondRelative(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginSeekSecondRelative(TInt aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekSecondRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndSeekSecondRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondRelative"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgRadio1C::SyncChannel(Brh& aUri, Brh& aMetadata)
{
    SyncChannelAvOpenhomeOrgRadio1C sync(*this, aUri, aMetadata);
    BeginChannel(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginChannel(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionChannel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionChannel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndChannel(IAsync& aAsync, Brh& aUri, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Channel"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aUri);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgRadio1C::SyncSetChannel(const Brx& aUri, const Brx& aMetadata)
{
    SyncSetChannelAvOpenhomeOrgRadio1C sync(*this);
    BeginSetChannel(aUri, aMetadata, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginSetChannel(const Brx& aUri, const Brx& aMetadata, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetChannel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetChannel->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUri));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aMetadata));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndSetChannel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetChannel"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgRadio1C::SyncTransportState(Brh& aValue)
{
    SyncTransportStateAvOpenhomeOrgRadio1C sync(*this, aValue);
    BeginTransportState(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginTransportState(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTransportState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTransportState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndTransportState(IAsync& aAsync, Brh& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TransportState"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgRadio1C::SyncId(TUint& aValue)
{
    SyncIdAvOpenhomeOrgRadio1C sync(*this, aValue);
    BeginId(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginId(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionId, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionId->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndId(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Id"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgRadio1C::SyncSetId(TUint aValue, const Brx& aUri)
{
    SyncSetIdAvOpenhomeOrgRadio1C sync(*this);
    BeginSetId(aValue, aUri, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginSetId(TUint aValue, const Brx& aUri, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUri));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndSetId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetId"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgRadio1C::SyncRead(TUint aId, Brh& aMetadata)
{
    SyncReadAvOpenhomeOrgRadio1C sync(*this, aMetadata);
    BeginRead(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginRead(TUint aId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndRead(IAsync& aAsync, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Read"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgRadio1C::SyncReadList(const Brx& aIdList, Brh& aChannelList)
{
    SyncReadListAvOpenhomeOrgRadio1C sync(*this, aChannelList);
    BeginReadList(aIdList, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginReadList(const Brx& aIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aIdList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndReadList(IAsync& aAsync, Brh& aChannelList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ReadList"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aChannelList);
}

void CpProxyAvOpenhomeOrgRadio1C::SyncIdArray(TUint& aToken, Brh& aArray)
{
    SyncIdArrayAvOpenhomeOrgRadio1C sync(*this, aToken, aArray);
    BeginIdArray(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginIdArray(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionIdArray, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArray->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndIdArray(IAsync& aAsync, TUint& aToken, Brh& aArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArray"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aToken = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aArray);
}

void CpProxyAvOpenhomeOrgRadio1C::SyncIdArrayChanged(TUint aToken, TBool& aValue)
{
    SyncIdArrayChangedAvOpenhomeOrgRadio1C sync(*this, aValue);
    BeginIdArrayChanged(aToken, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginIdArrayChanged(TUint aToken, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionIdArrayChanged, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionIdArrayChanged->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aToken));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArrayChanged->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndIdArrayChanged(IAsync& aAsync, TBool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArrayChanged"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgRadio1C::SyncChannelsMax(TUint& aValue)
{
    SyncChannelsMaxAvOpenhomeOrgRadio1C sync(*this, aValue);
    BeginChannelsMax(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginChannelsMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionChannelsMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionChannelsMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndChannelsMax(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ChannelsMax"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgRadio1C::SyncProtocolInfo(Brh& aValue)
{
    SyncProtocolInfoAvOpenhomeOrgRadio1C sync(*this, aValue);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1C::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1C::EndProtocolInfo(IAsync& aAsync, Brh& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ProtocolInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgRadio1C::SetPropertyUriChanged(Functor& aFunctor)
{
    iLock.Wait();
    iUriChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgRadio1C::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetadataChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgRadio1C::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTransportStateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgRadio1C::SetPropertyIdChanged(Functor& aFunctor)
{
    iLock.Wait();
    iIdChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgRadio1C::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock.Wait();
    iIdArrayChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgRadio1C::SetPropertyChannelsMaxChanged(Functor& aFunctor)
{
    iLock.Wait();
    iChannelsMaxChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgRadio1C::SetPropertyProtocolInfoChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProtocolInfoChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgRadio1C::PropertyUri(Brhz& aUri) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aUri.Set(iUri->Value());
}

void CpProxyAvOpenhomeOrgRadio1C::PropertyMetadata(Brhz& aMetadata) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aMetadata.Set(iMetadata->Value());
}

void CpProxyAvOpenhomeOrgRadio1C::PropertyTransportState(Brhz& aTransportState) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aTransportState.Set(iTransportState->Value());
}

void CpProxyAvOpenhomeOrgRadio1C::PropertyId(TUint& aId) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aId = iId->Value();
}

void CpProxyAvOpenhomeOrgRadio1C::PropertyIdArray(Brh& aIdArray) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aIdArray.Set(iIdArray->Value());
}

void CpProxyAvOpenhomeOrgRadio1C::PropertyChannelsMax(TUint& aChannelsMax) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aChannelsMax = iChannelsMax->Value();
}

void CpProxyAvOpenhomeOrgRadio1C::PropertyProtocolInfo(Brhz& aProtocolInfo) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aProtocolInfo.Set(iProtocolInfo->Value());
}

void CpProxyAvOpenhomeOrgRadio1C::UriPropertyChanged()
{
    ReportEvent(iUriChanged);
}

void CpProxyAvOpenhomeOrgRadio1C::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgRadio1C::TransportStatePropertyChanged()
{
    ReportEvent(iTransportStateChanged);
}

void CpProxyAvOpenhomeOrgRadio1C::IdPropertyChanged()
{
    ReportEvent(iIdChanged);
}

void CpProxyAvOpenhomeOrgRadio1C::IdArrayPropertyChanged()
{
    ReportEvent(iIdArrayChanged);
}

void CpProxyAvOpenhomeOrgRadio1C::ChannelsMaxPropertyChanged()
{
    ReportEvent(iChannelsMaxChanged);
}

void CpProxyAvOpenhomeOrgRadio1C::ProtocolInfoPropertyChanged()
{
    ReportEvent(iProtocolInfoChanged);
}


THandle STDCALL CpProxyAvOpenhomeOrgRadio1Create(CpDeviceC aDevice)
{
    return new CpProxyAvOpenhomeOrgRadio1C(aDevice);
}

void STDCALL CpProxyAvOpenhomeOrgRadio1Destroy(THandle aHandle)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncPlay(THandle aHandle)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPlay();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginPlay(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlay(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndPlay(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncPause(THandle aHandle)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPause();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginPause(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPause(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndPause(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncStop(THandle aHandle)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncStop();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginStop(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStop(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndStop(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncSeekSecondAbsolute(THandle aHandle, uint32_t aValue)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSeekSecondAbsolute(aValue);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginSeekSecondAbsolute(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSeekSecondAbsolute(aValue, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndSeekSecondAbsolute(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncSeekSecondRelative(THandle aHandle, int32_t aValue)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSeekSecondRelative(aValue);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginSeekSecondRelative(THandle aHandle, int32_t aValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSeekSecondRelative(aValue, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndSeekSecondRelative(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncChannel(THandle aHandle, char** aUri, char** aMetadata)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri;
    Brh buf_aMetadata;
    int32_t err = 0;
    try {
        proxyC->SyncChannel(buf_aUri, buf_aMetadata);
        *aUri = buf_aUri.Extract();
        *aMetadata = buf_aMetadata.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aUri = NULL;
        *aMetadata = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginChannel(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginChannel(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndChannel(THandle aHandle, OhNetHandleAsync aAsync, char** aUri, char** aMetadata)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aUri;
    *aUri = NULL;
    Brh buf_aMetadata;
    *aMetadata = NULL;
    try {
        proxyC->EndChannel(*async, buf_aUri, buf_aMetadata);
        *aUri = buf_aUri.Extract();
        *aMetadata = buf_aMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncSetChannel(THandle aHandle, const char* aUri, const char* aMetadata)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri(aUri);
    Brh buf_aMetadata(aMetadata);
    int32_t err = 0;
    try {
        proxyC->SyncSetChannel(buf_aUri, buf_aMetadata);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginSetChannel(THandle aHandle, const char* aUri, const char* aMetadata, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri(aUri);
    Brh buf_aMetadata(aMetadata);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetChannel(buf_aUri, buf_aMetadata, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndSetChannel(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncTransportState(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    int32_t err = 0;
    try {
        proxyC->SyncTransportState(buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginTransportState(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginTransportState(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndTransportState(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValue;
    *aValue = NULL;
    try {
        proxyC->EndTransportState(*async, buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncId(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncId(*aValue);
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginId(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginId(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndId(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndId(*async, *aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncSetId(THandle aHandle, uint32_t aValue, const char* aUri)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri(aUri);
    int32_t err = 0;
    try {
        proxyC->SyncSetId(aValue, buf_aUri);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginSetId(THandle aHandle, uint32_t aValue, const char* aUri, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri(aUri);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetId(aValue, buf_aUri, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndSetId(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncRead(THandle aHandle, uint32_t aId, char** aMetadata)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aMetadata;
    int32_t err = 0;
    try {
        proxyC->SyncRead(aId, buf_aMetadata);
        *aMetadata = buf_aMetadata.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aMetadata = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginRead(THandle aHandle, uint32_t aId, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginRead(aId, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndRead(THandle aHandle, OhNetHandleAsync aAsync, char** aMetadata)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aMetadata;
    *aMetadata = NULL;
    try {
        proxyC->EndRead(*async, buf_aMetadata);
        *aMetadata = buf_aMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncReadList(THandle aHandle, const char* aIdList, char** aChannelList)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdList(aIdList);
    Brh buf_aChannelList;
    int32_t err = 0;
    try {
        proxyC->SyncReadList(buf_aIdList, buf_aChannelList);
        *aChannelList = buf_aChannelList.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aChannelList = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginReadList(THandle aHandle, const char* aIdList, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdList(aIdList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginReadList(buf_aIdList, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndReadList(THandle aHandle, OhNetHandleAsync aAsync, char** aChannelList)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aChannelList;
    *aChannelList = NULL;
    try {
        proxyC->EndReadList(*async, buf_aChannelList);
        *aChannelList = buf_aChannelList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncIdArray(THandle aHandle, uint32_t* aToken, char** aArray, uint32_t* aArrayLen)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aArray;
    int32_t err = 0;
    try {
        proxyC->SyncIdArray(*aToken, buf_aArray);
        *aArrayLen = buf_aArray.Bytes();
        *aArray = buf_aArray.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aToken = 0;
        *aArrayLen = 0;
        *aArray = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginIdArray(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginIdArray(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndIdArray(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aToken, char** aArray, uint32_t* aArrayLen)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aArray;
    *aArray = NULL;
    *aArrayLen = 0;
    try {
        proxyC->EndIdArray(*async, *aToken, buf_aArray);
        *aArrayLen = buf_aArray.Bytes();
        *aArray = buf_aArray.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncIdArrayChanged(THandle aHandle, uint32_t aToken, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool Value;
    int32_t err = 0;
    try {
        proxyC->SyncIdArrayChanged(aToken, Value);
        *aValue = Value? 1 : 0;
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = false;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginIdArrayChanged(THandle aHandle, uint32_t aToken, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginIdArrayChanged(aToken, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndIdArrayChanged(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool Value;
    try {
        proxyC->EndIdArrayChanged(*async, Value);
        *aValue = Value? 1 : 0;
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncChannelsMax(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncChannelsMax(*aValue);
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginChannelsMax(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginChannelsMax(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndChannelsMax(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndChannelsMax(*async, *aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1SyncProtocolInfo(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    int32_t err = 0;
    try {
        proxyC->SyncProtocolInfo(buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1BeginProtocolInfo(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginProtocolInfo(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgRadio1EndProtocolInfo(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValue;
    *aValue = NULL;
    try {
        proxyC->EndProtocolInfo(*async, buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgRadio1SetPropertyUriChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyUriChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgRadio1SetPropertyMetadataChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetadataChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgRadio1SetPropertyTransportStateChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTransportStateChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgRadio1SetPropertyIdChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyIdChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgRadio1SetPropertyIdArrayChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyIdArrayChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgRadio1SetPropertyChannelsMaxChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyChannelsMaxChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgRadio1SetPropertyProtocolInfoChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProtocolInfoChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgRadio1PropertyUri(THandle aHandle, char** aUri)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aUri;
    proxyC->PropertyUri(buf_aUri);
    *aUri = buf_aUri.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgRadio1PropertyMetadata(THandle aHandle, char** aMetadata)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetadata;
    proxyC->PropertyMetadata(buf_aMetadata);
    *aMetadata = buf_aMetadata.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgRadio1PropertyTransportState(THandle aHandle, char** aTransportState)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransportState;
    proxyC->PropertyTransportState(buf_aTransportState);
    *aTransportState = buf_aTransportState.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgRadio1PropertyId(THandle aHandle, uint32_t* aId)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyId(*aId);
}

void STDCALL CpProxyAvOpenhomeOrgRadio1PropertyIdArray(THandle aHandle, char** aIdArray, uint32_t* aLen)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdArray;
    proxyC->PropertyIdArray(buf_aIdArray);
    *aLen = buf_aIdArray.Bytes();
    *aIdArray = buf_aIdArray.Extract();
}

void STDCALL CpProxyAvOpenhomeOrgRadio1PropertyChannelsMax(THandle aHandle, uint32_t* aChannelsMax)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyChannelsMax(*aChannelsMax);
}

void STDCALL CpProxyAvOpenhomeOrgRadio1PropertyProtocolInfo(THandle aHandle, char** aProtocolInfo)
{
    CpProxyAvOpenhomeOrgRadio1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProtocolInfo;
    proxyC->PropertyProtocolInfo(buf_aProtocolInfo);
    *aProtocolInfo = buf_aProtocolInfo.Transfer();
}

