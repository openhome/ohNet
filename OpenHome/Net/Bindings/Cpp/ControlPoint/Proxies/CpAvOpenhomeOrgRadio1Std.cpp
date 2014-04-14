#include "CpAvOpenhomeOrgRadio1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncPlayAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncPlayAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlayAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
};

SyncPlayAvOpenhomeOrgRadio1Cpp::SyncPlayAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncPlayAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncPauseAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPauseAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
};

SyncPauseAvOpenhomeOrgRadio1Cpp::SyncPauseAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncPauseAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStopAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncStopAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
};

SyncStopAvOpenhomeOrgRadio1Cpp::SyncStopAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncStopAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
};

SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1Cpp::SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondAbsolute(aAsync);
}


class SyncSeekSecondRelativeAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncSeekSecondRelativeAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSeekSecondRelativeAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
};

SyncSeekSecondRelativeAvOpenhomeOrgRadio1Cpp::SyncSeekSecondRelativeAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondRelativeAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondRelative(aAsync);
}


class SyncChannelAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncChannelAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, std::string& aUri, std::string& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncChannelAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
    std::string& iUri;
    std::string& iMetadata;
};

SyncChannelAvOpenhomeOrgRadio1Cpp::SyncChannelAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, std::string& aUri, std::string& aMetadata)
    : iService(aProxy)
    , iUri(aUri)
    , iMetadata(aMetadata)
{
}

void SyncChannelAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndChannel(aAsync, iUri, iMetadata);
}


class SyncSetChannelAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncSetChannelAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetChannelAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
};

SyncSetChannelAvOpenhomeOrgRadio1Cpp::SyncSetChannelAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetChannelAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetChannel(aAsync);
}


class SyncTransportStateAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncTransportStateAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTransportStateAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
    std::string& iValue;
};

SyncTransportStateAvOpenhomeOrgRadio1Cpp::SyncTransportStateAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTransportStateAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTransportState(aAsync, iValue);
}


class SyncIdAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncIdAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, uint32_t& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
    uint32_t& iValue;
};

SyncIdAvOpenhomeOrgRadio1Cpp::SyncIdAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, uint32_t& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncIdAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndId(aAsync, iValue);
}


class SyncSetIdAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncSetIdAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetIdAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
};

SyncSetIdAvOpenhomeOrgRadio1Cpp::SyncSetIdAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetIdAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetId(aAsync);
}


class SyncReadAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncReadAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, std::string& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncReadAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
    std::string& iMetadata;
};

SyncReadAvOpenhomeOrgRadio1Cpp::SyncReadAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, std::string& aMetadata)
    : iService(aProxy)
    , iMetadata(aMetadata)
{
}

void SyncReadAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRead(aAsync, iMetadata);
}


class SyncReadListAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncReadListAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, std::string& aChannelList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncReadListAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
    std::string& iChannelList;
};

SyncReadListAvOpenhomeOrgRadio1Cpp::SyncReadListAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, std::string& aChannelList)
    : iService(aProxy)
    , iChannelList(aChannelList)
{
}

void SyncReadListAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndReadList(aAsync, iChannelList);
}


class SyncIdArrayAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncIdArrayAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, uint32_t& aToken, std::string& aArray);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdArrayAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
    uint32_t& iToken;
    std::string& iArray;
};

SyncIdArrayAvOpenhomeOrgRadio1Cpp::SyncIdArrayAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, uint32_t& aToken, std::string& aArray)
    : iService(aProxy)
    , iToken(aToken)
    , iArray(aArray)
{
}

void SyncIdArrayAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArray(aAsync, iToken, iArray);
}


class SyncIdArrayChangedAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncIdArrayChangedAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, bool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncIdArrayChangedAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
    bool& iValue;
};

SyncIdArrayChangedAvOpenhomeOrgRadio1Cpp::SyncIdArrayChangedAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, bool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncIdArrayChangedAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndIdArrayChanged(aAsync, iValue);
}


class SyncChannelsMaxAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncChannelsMaxAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, uint32_t& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncChannelsMaxAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
    uint32_t& iValue;
};

SyncChannelsMaxAvOpenhomeOrgRadio1Cpp::SyncChannelsMaxAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, uint32_t& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncChannelsMaxAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndChannelsMax(aAsync, iValue);
}


class SyncProtocolInfoAvOpenhomeOrgRadio1Cpp : public SyncProxyAction
{
public:
    SyncProtocolInfoAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncProtocolInfoAvOpenhomeOrgRadio1Cpp() {}
private:
    CpProxyAvOpenhomeOrgRadio1Cpp& iService;
    std::string& iValue;
};

SyncProtocolInfoAvOpenhomeOrgRadio1Cpp::SyncProtocolInfoAvOpenhomeOrgRadio1Cpp(CpProxyAvOpenhomeOrgRadio1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncProtocolInfoAvOpenhomeOrgRadio1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iValue);
}


CpProxyAvOpenhomeOrgRadio1Cpp::CpProxyAvOpenhomeOrgRadio1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("av-openhome-org", "Radio", 1, aDevice.Device())
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
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1Cpp::UriPropertyChanged);
    iUri = new PropertyString(aDevice.Device().GetCpStack().Env(), "Uri", functor);
    AddProperty(iUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1Cpp::MetadataPropertyChanged);
    iMetadata = new PropertyString(aDevice.Device().GetCpStack().Env(), "Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1Cpp::TransportStatePropertyChanged);
    iTransportState = new PropertyString(aDevice.Device().GetCpStack().Env(), "TransportState", functor);
    AddProperty(iTransportState);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1Cpp::IdPropertyChanged);
    iId = new PropertyUint(aDevice.Device().GetCpStack().Env(), "Id", functor);
    AddProperty(iId);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1Cpp::IdArrayPropertyChanged);
    iIdArray = new PropertyBinary(aDevice.Device().GetCpStack().Env(), "IdArray", functor);
    AddProperty(iIdArray);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1Cpp::ChannelsMaxPropertyChanged);
    iChannelsMax = new PropertyUint(aDevice.Device().GetCpStack().Env(), "ChannelsMax", functor);
    AddProperty(iChannelsMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgRadio1Cpp::ProtocolInfoPropertyChanged);
    iProtocolInfo = new PropertyString(aDevice.Device().GetCpStack().Env(), "ProtocolInfo", functor);
    AddProperty(iProtocolInfo);
}

CpProxyAvOpenhomeOrgRadio1Cpp::~CpProxyAvOpenhomeOrgRadio1Cpp()
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

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncPlay()
{
    SyncPlayAvOpenhomeOrgRadio1Cpp sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndPlay(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncPause()
{
    SyncPauseAvOpenhomeOrgRadio1Cpp sync(*this);
    BeginPause(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginPause(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndPause(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncStop()
{
    SyncStopAvOpenhomeOrgRadio1Cpp sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndStop(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncSeekSecondAbsolute(uint32_t aValue)
{
    SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1Cpp sync(*this);
    BeginSeekSecondAbsolute(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginSeekSecondAbsolute(uint32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndSeekSecondAbsolute(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncSeekSecondRelative(int32_t aValue)
{
    SyncSeekSecondRelativeAvOpenhomeOrgRadio1Cpp sync(*this);
    BeginSeekSecondRelative(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginSeekSecondRelative(int32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndSeekSecondRelative(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncChannel(std::string& aUri, std::string& aMetadata)
{
    SyncChannelAvOpenhomeOrgRadio1Cpp sync(*this, aUri, aMetadata);
    BeginChannel(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginChannel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionChannel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionChannel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndChannel(IAsync& aAsync, std::string& aUri, std::string& aMetadata)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aUri.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aMetadata.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncSetChannel(const std::string& aUri, const std::string& aMetadata)
{
    SyncSetChannelAvOpenhomeOrgRadio1Cpp sync(*this);
    BeginSetChannel(aUri, aMetadata, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginSetChannel(const std::string& aUri, const std::string& aMetadata, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetChannel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetChannel->InputParameters();
    {
        Brn buf((const TByte*)aUri.c_str(), (TUint)aUri.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aMetadata.c_str(), (TUint)aMetadata.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndSetChannel(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncTransportState(std::string& aValue)
{
    SyncTransportStateAvOpenhomeOrgRadio1Cpp sync(*this, aValue);
    BeginTransportState(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginTransportState(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTransportState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTransportState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndTransportState(IAsync& aAsync, std::string& aValue)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aValue.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncId(uint32_t& aValue)
{
    SyncIdAvOpenhomeOrgRadio1Cpp sync(*this, aValue);
    BeginId(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginId(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionId, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionId->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndId(IAsync& aAsync, uint32_t& aValue)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncSetId(uint32_t aValue, const std::string& aUri)
{
    SyncSetIdAvOpenhomeOrgRadio1Cpp sync(*this);
    BeginSetId(aValue, aUri, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginSetId(uint32_t aValue, const std::string& aUri, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    {
        Brn buf((const TByte*)aUri.c_str(), (TUint)aUri.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndSetId(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncRead(uint32_t aId, std::string& aMetadata)
{
    SyncReadAvOpenhomeOrgRadio1Cpp sync(*this, aMetadata);
    BeginRead(aId, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginRead(uint32_t aId, FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::EndRead(IAsync& aAsync, std::string& aMetadata)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aMetadata.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncReadList(const std::string& aIdList, std::string& aChannelList)
{
    SyncReadListAvOpenhomeOrgRadio1Cpp sync(*this, aChannelList);
    BeginReadList(aIdList, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginReadList(const std::string& aIdList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReadList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReadList->InputParameters();
    {
        Brn buf((const TByte*)aIdList.c_str(), (TUint)aIdList.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionReadList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndReadList(IAsync& aAsync, std::string& aChannelList)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aChannelList.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncIdArray(uint32_t& aToken, std::string& aArray)
{
    SyncIdArrayAvOpenhomeOrgRadio1Cpp sync(*this, aToken, aArray);
    BeginIdArray(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginIdArray(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionIdArray, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionIdArray->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndIdArray(IAsync& aAsync, uint32_t& aToken, std::string& aArray)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aArray.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncIdArrayChanged(uint32_t aToken, bool& aValue)
{
    SyncIdArrayChangedAvOpenhomeOrgRadio1Cpp sync(*this, aValue);
    BeginIdArrayChanged(aToken, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginIdArrayChanged(uint32_t aToken, FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::EndIdArrayChanged(IAsync& aAsync, bool& aValue)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncChannelsMax(uint32_t& aValue)
{
    SyncChannelsMaxAvOpenhomeOrgRadio1Cpp sync(*this, aValue);
    BeginChannelsMax(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginChannelsMax(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionChannelsMax, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionChannelsMax->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndChannelsMax(IAsync& aAsync, uint32_t& aValue)
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

void CpProxyAvOpenhomeOrgRadio1Cpp::SyncProtocolInfo(std::string& aValue)
{
    SyncProtocolInfoAvOpenhomeOrgRadio1Cpp sync(*this, aValue);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::EndProtocolInfo(IAsync& aAsync, std::string& aValue)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aValue.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SetPropertyUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetadataChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransportStateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SetPropertyIdChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SetPropertyIdArrayChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIdArrayChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SetPropertyChannelsMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iChannelsMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::SetPropertyProtocolInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProtocolInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::PropertyUri(std::string& aUri) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iUri->Value();
    aUri.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgRadio1Cpp::PropertyMetadata(std::string& aMetadata) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iMetadata->Value();
    aMetadata.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgRadio1Cpp::PropertyTransportState(std::string& aTransportState) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iTransportState->Value();
    aTransportState.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgRadio1Cpp::PropertyId(uint32_t& aId) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aId = iId->Value();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::PropertyIdArray(std::string& aIdArray) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iIdArray->Value();
    aIdArray.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgRadio1Cpp::PropertyChannelsMax(uint32_t& aChannelsMax) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aChannelsMax = iChannelsMax->Value();
}

void CpProxyAvOpenhomeOrgRadio1Cpp::PropertyProtocolInfo(std::string& aProtocolInfo) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProtocolInfo->Value();
    aProtocolInfo.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgRadio1Cpp::UriPropertyChanged()
{
    ReportEvent(iUriChanged);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::TransportStatePropertyChanged()
{
    ReportEvent(iTransportStateChanged);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::IdPropertyChanged()
{
    ReportEvent(iIdChanged);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::IdArrayPropertyChanged()
{
    ReportEvent(iIdArrayChanged);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::ChannelsMaxPropertyChanged()
{
    ReportEvent(iChannelsMaxChanged);
}

void CpProxyAvOpenhomeOrgRadio1Cpp::ProtocolInfoPropertyChanged()
{
    ReportEvent(iProtocolInfoChanged);
}

