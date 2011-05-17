#include "CpAvOpenhomeOrgRadio1.h"
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncPlayAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncPlayAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
};

SyncPlayAvOpenhomeOrgRadio1::SyncPlayAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy)
    : iService(aProxy)
{
}

void SyncPlayAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncPauseAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
};

SyncPauseAvOpenhomeOrgRadio1::SyncPauseAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy)
    : iService(aProxy)
{
}

void SyncPauseAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStopAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncStopAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
};

SyncStopAvOpenhomeOrgRadio1::SyncStopAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy)
    : iService(aProxy)
{
}

void SyncStopAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
};

SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1::SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondAbsolute(aAsync);
}


class SyncSeekSecondRelativeAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncSeekSecondRelativeAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
};

SyncSeekSecondRelativeAvOpenhomeOrgRadio1::SyncSeekSecondRelativeAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondRelativeAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondRelative(aAsync);
}


class SyncChannelAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncChannelAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, Brh& aUri, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
    Brh& iUri;
    Brh& iMetadata;
};

SyncChannelAvOpenhomeOrgRadio1::SyncChannelAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, Brh& aUri, Brh& aMetadata)
    : iService(aProxy)
    , iUri(aUri)
    , iMetadata(aMetadata)
{
}

void SyncChannelAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndChannel(aAsync, iUri, iMetadata);
}


class SyncSetChannelAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncSetChannelAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
};

SyncSetChannelAvOpenhomeOrgRadio1::SyncSetChannelAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy)
    : iService(aProxy)
{
}

void SyncSetChannelAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetChannel(aAsync);
}


class SyncTransportStateAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncTransportStateAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
    Brh& iValue;
};

SyncTransportStateAvOpenhomeOrgRadio1::SyncTransportStateAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTransportStateAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTransportState(aAsync, iValue);
}


class SyncIdAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncIdAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
    TUint& iValue;
};

SyncIdAvOpenhomeOrgRadio1::SyncIdAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncIdAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndId(aAsync, iValue);
}


class SyncSetIdAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncSetIdAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
};

SyncSetIdAvOpenhomeOrgRadio1::SyncSetIdAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy)
    : iService(aProxy)
{
}

void SyncSetIdAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetId(aAsync);
}


class SyncReadAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncReadAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
    Brh& iMetadata;
};

SyncReadAvOpenhomeOrgRadio1::SyncReadAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, Brh& aMetadata)
    : iService(aProxy)
    , iMetadata(aMetadata)
{
}

void SyncReadAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iMetadata);
}


class SyncReadListAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncReadListAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, Brh& aChannelList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
    Brh& iChannelList;
};

SyncReadListAvOpenhomeOrgRadio1::SyncReadListAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, Brh& aChannelList)
    : iService(aProxy)
    , iChannelList(aChannelList)
{
}

void SyncReadListAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iChannelList);
}


class SyncIdArrayAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncIdArrayAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, TUint& aToken, Brh& aArray);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
    TUint& iToken;
    Brh& iArray;
};

SyncIdArrayAvOpenhomeOrgRadio1::SyncIdArrayAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, TUint& aToken, Brh& aArray)
    : iService(aProxy)
    , iToken(aToken)
    , iArray(aArray)
{
}

void SyncIdArrayAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArray(aAsync, iToken, iArray);
}


class SyncIdArrayChangedAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncIdArrayChangedAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, TBool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
    TBool& iValue;
};

SyncIdArrayChangedAvOpenhomeOrgRadio1::SyncIdArrayChangedAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, TBool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncIdArrayChangedAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArrayChanged(aAsync, iValue);
}


class SyncChannelsMaxAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncChannelsMaxAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
    TUint& iValue;
};

SyncChannelsMaxAvOpenhomeOrgRadio1::SyncChannelsMaxAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncChannelsMaxAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndChannelsMax(aAsync, iValue);
}


class SyncProtocolInfoAvOpenhomeOrgRadio1 : public SyncProxyAction
{
public:
    SyncProtocolInfoAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgRadio1& iService;
    Brh& iValue;
};

SyncProtocolInfoAvOpenhomeOrgRadio1::SyncProtocolInfoAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncProtocolInfoAvOpenhomeOrgRadio1::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iValue);
}


CpProxyAvOpenhomeOrgRadio1::CpProxyAvOpenhomeOrgRadio1(CpDevice& aDevice)
    : CpProxy("av-openhome-org", "Radio", 1, aDevice.Device())
{
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionPlay = new Action("Play");

    iActionPause = new Action("Pause");

    iActionStop = new Action("Stop");

    iActionSeekSecondAbsolute = new Action("SeekSecondAbsolute");
    param = new Zapp::ParameterUint("Value");
    iActionSeekSecondAbsolute->AddInputParameter(param);

    iActionSeekSecondRelative = new Action("SeekSecondRelative");
    param = new Zapp::ParameterInt("Value");
    iActionSeekSecondRelative->AddInputParameter(param);

    iActionChannel = new Action("Channel");
    param = new Zapp::ParameterString("Uri");
    iActionChannel->AddOutputParameter(param);
    param = new Zapp::ParameterString("Metadata");
    iActionChannel->AddOutputParameter(param);

    iActionSetChannel = new Action("SetChannel");
    param = new Zapp::ParameterString("Uri");
    iActionSetChannel->AddInputParameter(param);
    param = new Zapp::ParameterString("Metadata");
    iActionSetChannel->AddInputParameter(param);

    iActionTransportState = new Action("TransportState");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Buffering";
    param = new Zapp::ParameterString("Value", allowedValues, 4);
    iActionTransportState->AddOutputParameter(param);
    delete[] allowedValues;

    iActionId = new Action("Id");
    param = new Zapp::ParameterUint("Value");
    iActionId->AddOutputParameter(param);

    iActionSetId = new Action("SetId");
    param = new Zapp::ParameterUint("Value");
    iActionSetId->AddInputParameter(param);
    param = new Zapp::ParameterString("Uri");
    iActionSetId->AddInputParameter(param);

    iActionRead = new Action("Read");
    param = new Zapp::ParameterUint("Id");
    iActionRead->AddInputParameter(param);
    param = new Zapp::ParameterString("Metadata");
    iActionRead->AddOutputParameter(param);

    iActionReadList = new Action("ReadList");
    param = new Zapp::ParameterString("IdList");
    iActionReadList->AddInputParameter(param);
    param = new Zapp::ParameterString("ChannelList");
    iActionReadList->AddOutputParameter(param);

    iActionIdArray = new Action("IdArray");
    param = new Zapp::ParameterUint("Token");
    iActionIdArray->AddOutputParameter(param);
    param = new Zapp::ParameterBinary("Array");
    iActionIdArray->AddOutputParameter(param);

    iActionIdArrayChanged = new Action("IdArrayChanged");
    param = new Zapp::ParameterUint("Token");
    iActionIdArrayChanged->AddInputParameter(param);
    param = new Zapp::ParameterBool("Value");
    iActionIdArrayChanged->AddOutputParameter(param);

    iActionChannelsMax = new Action("ChannelsMax");
    param = new Zapp::ParameterUint("Value");
    iActionChannelsMax->AddOutputParameter(param);

    iActionProtocolInfo = new Action("ProtocolInfo");
    param = new Zapp::ParameterString("Value");
    iActionProtocolInfo->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1::UriPropertyChanged);
    iUri = new PropertyString("Uri", functor);
    AddProperty(iUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1::MetadataPropertyChanged);
    iMetadata = new PropertyString("Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1::TransportStatePropertyChanged);
    iTransportState = new PropertyString("TransportState", functor);
    AddProperty(iTransportState);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1::IdPropertyChanged);
    iId = new PropertyUint("Id", functor);
    AddProperty(iId);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary("IdArray", functor);
    AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1::ChannelsMaxPropertyChanged);
    iChannelsMax = new PropertyUint("ChannelsMax", functor);
    AddProperty(iChannelsMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1::ProtocolInfoPropertyChanged);
    iProtocolInfo = new PropertyString("ProtocolInfo", functor);
    AddProperty(iProtocolInfo);
}

CpProxyAvOpenhomeOrgRadio1::~CpProxyAvOpenhomeOrgRadio1()
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

void CpProxyAvOpenhomeOrgRadio1::SyncPlay()
{
    SyncPlayAvOpenhomeOrgRadio1 sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgRadio1::SyncPause()
{
    SyncPauseAvOpenhomeOrgRadio1 sync(*this);
    BeginPause(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginPause(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgRadio1::SyncStop()
{
    SyncStopAvOpenhomeOrgRadio1 sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgRadio1::SyncSeekSecondAbsolute(TUint aValue)
{
    SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1 sync(*this);
    BeginSeekSecondAbsolute(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginSeekSecondAbsolute(TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndSeekSecondAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondAbsolute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgRadio1::SyncSeekSecondRelative(TInt aValue)
{
    SyncSeekSecondRelativeAvOpenhomeOrgRadio1 sync(*this);
    BeginSeekSecondRelative(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginSeekSecondRelative(TInt aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndSeekSecondRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondRelative"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgRadio1::SyncChannel(Brh& aUri, Brh& aMetadata)
{
    SyncChannelAvOpenhomeOrgRadio1 sync(*this, aUri, aMetadata);
    BeginChannel(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginChannel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionChannel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionChannel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndChannel(IAsync& aAsync, Brh& aUri, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Channel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aUri);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgRadio1::SyncSetChannel(const Brx& aUri, const Brx& aMetadata)
{
    SyncSetChannelAvOpenhomeOrgRadio1 sync(*this);
    BeginSetChannel(aUri, aMetadata, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginSetChannel(const Brx& aUri, const Brx& aMetadata, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetChannel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetChannel->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUri));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aMetadata));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndSetChannel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetChannel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgRadio1::SyncTransportState(Brh& aValue)
{
    SyncTransportStateAvOpenhomeOrgRadio1 sync(*this, aValue);
    BeginTransportState(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginTransportState(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTransportState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTransportState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndTransportState(IAsync& aAsync, Brh& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TransportState"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgRadio1::SyncId(TUint& aValue)
{
    SyncIdAvOpenhomeOrgRadio1 sync(*this, aValue);
    BeginId(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginId(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionId, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionId->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndId(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Id"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgRadio1::SyncSetId(TUint aValue, const Brx& aUri)
{
    SyncSetIdAvOpenhomeOrgRadio1 sync(*this);
    BeginSetId(aValue, aUri, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginSetId(TUint aValue, const Brx& aUri, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUri));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndSetId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgRadio1::SyncRead(TUint aId, Brh& aMetadata)
{
    SyncReadAvOpenhomeOrgRadio1 sync(*this, aMetadata);
    BeginRead(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginRead(TUint aId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRead, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRead->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRead->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndRead(IAsync& aAsync, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Read"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgRadio1::SyncReadList(const Brx& aIdList, Brh& aChannelList)
{
    SyncReadListAvOpenhomeOrgRadio1 sync(*this, aChannelList);
    BeginReadList(aIdList, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginReadList(const Brx& aIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aIdList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndReadList(IAsync& aAsync, Brh& aChannelList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ReadList"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aChannelList);
}

void CpProxyAvOpenhomeOrgRadio1::SyncIdArray(TUint& aToken, Brh& aArray)
{
    SyncIdArrayAvOpenhomeOrgRadio1 sync(*this, aToken, aArray);
    BeginIdArray(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginIdArray(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdArray, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArray->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndIdArray(IAsync& aAsync, TUint& aToken, Brh& aArray)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArray"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aToken = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aArray);
}

void CpProxyAvOpenhomeOrgRadio1::SyncIdArrayChanged(TUint aToken, TBool& aValue)
{
    SyncIdArrayChangedAvOpenhomeOrgRadio1 sync(*this, aValue);
    BeginIdArrayChanged(aToken, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginIdArrayChanged(TUint aToken, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdArrayChanged, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionIdArrayChanged->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aToken));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArrayChanged->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndIdArrayChanged(IAsync& aAsync, TBool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("IdArrayChanged"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgRadio1::SyncChannelsMax(TUint& aValue)
{
    SyncChannelsMaxAvOpenhomeOrgRadio1 sync(*this, aValue);
    BeginChannelsMax(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginChannelsMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionChannelsMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionChannelsMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndChannelsMax(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ChannelsMax"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgRadio1::SyncProtocolInfo(Brh& aValue)
{
    SyncProtocolInfoAvOpenhomeOrgRadio1 sync(*this, aValue);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1::EndProtocolInfo(IAsync& aAsync, Brh& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ProtocolInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgRadio1::SetPropertyUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetadataChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransportStateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1::SetPropertyIdChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdArrayChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1::SetPropertyChannelsMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iChannelsMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1::SetPropertyProtocolInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProtocolInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1::PropertyUri(Brhz& aUri) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aUri.Set(iUri->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgRadio1::PropertyMetadata(Brhz& aMetadata) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aMetadata.Set(iMetadata->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgRadio1::PropertyTransportState(Brhz& aTransportState) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTransportState.Set(iTransportState->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgRadio1::PropertyId(TUint& aId) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aId = iId->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgRadio1::PropertyIdArray(Brh& aIdArray) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aIdArray.Set(iIdArray->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgRadio1::PropertyChannelsMax(TUint& aChannelsMax) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aChannelsMax = iChannelsMax->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgRadio1::PropertyProtocolInfo(Brhz& aProtocolInfo) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProtocolInfo.Set(iProtocolInfo->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgRadio1::UriPropertyChanged()
{
    ReportEvent(iUriChanged);
}

void CpProxyAvOpenhomeOrgRadio1::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgRadio1::TransportStatePropertyChanged()
{
    ReportEvent(iTransportStateChanged);
}

void CpProxyAvOpenhomeOrgRadio1::IdPropertyChanged()
{
    ReportEvent(iIdChanged);
}

void CpProxyAvOpenhomeOrgRadio1::IdArrayPropertyChanged()
{
    ReportEvent(iIdArrayChanged);
}

void CpProxyAvOpenhomeOrgRadio1::ChannelsMaxPropertyChanged()
{
    ReportEvent(iChannelsMaxChanged);
}

void CpProxyAvOpenhomeOrgRadio1::ProtocolInfoPropertyChanged()
{
    ReportEvent(iProtocolInfoChanged);
}

