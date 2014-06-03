#include "CpAvOpenhomeOrgReceiver1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncPlayAvOpenhomeOrgReceiver1 : public SyncProxyAction
{
public:
    SyncPlayAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlayAvOpenhomeOrgReceiver1() {}
private:
    CpProxyAvOpenhomeOrgReceiver1& iService;
};

SyncPlayAvOpenhomeOrgReceiver1::SyncPlayAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy)
    : iService(aProxy)
{
}

void SyncPlayAvOpenhomeOrgReceiver1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncStopAvOpenhomeOrgReceiver1 : public SyncProxyAction
{
public:
    SyncStopAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopAvOpenhomeOrgReceiver1() {}
private:
    CpProxyAvOpenhomeOrgReceiver1& iService;
};

SyncStopAvOpenhomeOrgReceiver1::SyncStopAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy)
    : iService(aProxy)
{
}

void SyncStopAvOpenhomeOrgReceiver1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncSetSenderAvOpenhomeOrgReceiver1 : public SyncProxyAction
{
public:
    SyncSetSenderAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetSenderAvOpenhomeOrgReceiver1() {}
private:
    CpProxyAvOpenhomeOrgReceiver1& iService;
};

SyncSetSenderAvOpenhomeOrgReceiver1::SyncSetSenderAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy)
    : iService(aProxy)
{
}

void SyncSetSenderAvOpenhomeOrgReceiver1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSender(aAsync);
}


class SyncSenderAvOpenhomeOrgReceiver1 : public SyncProxyAction
{
public:
    SyncSenderAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy, Brh& aUri, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSenderAvOpenhomeOrgReceiver1() {}
private:
    CpProxyAvOpenhomeOrgReceiver1& iService;
    Brh& iUri;
    Brh& iMetadata;
};

SyncSenderAvOpenhomeOrgReceiver1::SyncSenderAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy, Brh& aUri, Brh& aMetadata)
    : iService(aProxy)
    , iUri(aUri)
    , iMetadata(aMetadata)
{
}

void SyncSenderAvOpenhomeOrgReceiver1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSender(aAsync, iUri, iMetadata);
}


class SyncProtocolInfoAvOpenhomeOrgReceiver1 : public SyncProxyAction
{
public:
    SyncProtocolInfoAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncProtocolInfoAvOpenhomeOrgReceiver1() {}
private:
    CpProxyAvOpenhomeOrgReceiver1& iService;
    Brh& iValue;
};

SyncProtocolInfoAvOpenhomeOrgReceiver1::SyncProtocolInfoAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncProtocolInfoAvOpenhomeOrgReceiver1::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iValue);
}


class SyncTransportStateAvOpenhomeOrgReceiver1 : public SyncProxyAction
{
public:
    SyncTransportStateAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTransportStateAvOpenhomeOrgReceiver1() {}
private:
    CpProxyAvOpenhomeOrgReceiver1& iService;
    Brh& iValue;
};

SyncTransportStateAvOpenhomeOrgReceiver1::SyncTransportStateAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTransportStateAvOpenhomeOrgReceiver1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTransportState(aAsync, iValue);
}


CpProxyAvOpenhomeOrgReceiver1::CpProxyAvOpenhomeOrgReceiver1(CpDevice& aDevice)
    : CpProxy("av-openhome-org", "Receiver", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionPlay = new Action("Play");

    iActionStop = new Action("Stop");

    iActionSetSender = new Action("SetSender");
    param = new OpenHome::Net::ParameterString("Uri");
    iActionSetSender->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionSetSender->AddInputParameter(param);

    iActionSender = new Action("Sender");
    param = new OpenHome::Net::ParameterString("Uri");
    iActionSender->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionSender->AddOutputParameter(param);

    iActionProtocolInfo = new Action("ProtocolInfo");
    param = new OpenHome::Net::ParameterString("Value");
    iActionProtocolInfo->AddOutputParameter(param);

    iActionTransportState = new Action("TransportState");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Waiting";
    allowedValues[index++] = (TChar*)"Buffering";
    param = new OpenHome::Net::ParameterString("Value", allowedValues, 4);
    iActionTransportState->AddOutputParameter(param);
    delete[] allowedValues;

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgReceiver1::UriPropertyChanged);
    iUri = new PropertyString(aDevice.Device().GetCpStack().Env(), "Uri", functor);
    AddProperty(iUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgReceiver1::MetadataPropertyChanged);
    iMetadata = new PropertyString(aDevice.Device().GetCpStack().Env(), "Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgReceiver1::TransportStatePropertyChanged);
    iTransportState = new PropertyString(aDevice.Device().GetCpStack().Env(), "TransportState", functor);
    AddProperty(iTransportState);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgReceiver1::ProtocolInfoPropertyChanged);
    iProtocolInfo = new PropertyString(aDevice.Device().GetCpStack().Env(), "ProtocolInfo", functor);
    AddProperty(iProtocolInfo);
}

CpProxyAvOpenhomeOrgReceiver1::~CpProxyAvOpenhomeOrgReceiver1()
{
    DestroyService();
    delete iActionPlay;
    delete iActionStop;
    delete iActionSetSender;
    delete iActionSender;
    delete iActionProtocolInfo;
    delete iActionTransportState;
}

void CpProxyAvOpenhomeOrgReceiver1::SyncPlay()
{
    SyncPlayAvOpenhomeOrgReceiver1 sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1::EndPlay(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgReceiver1::SyncStop()
{
    SyncStopAvOpenhomeOrgReceiver1 sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1::EndStop(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgReceiver1::SyncSetSender(const Brx& aUri, const Brx& aMetadata)
{
    SyncSetSenderAvOpenhomeOrgReceiver1 sync(*this);
    BeginSetSender(aUri, aMetadata, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1::BeginSetSender(const Brx& aUri, const Brx& aMetadata, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSender, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSender->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUri));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aMetadata));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1::EndSetSender(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSender"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgReceiver1::SyncSender(Brh& aUri, Brh& aMetadata)
{
    SyncSenderAvOpenhomeOrgReceiver1 sync(*this, aUri, aMetadata);
    BeginSender(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1::BeginSender(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSender, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSender->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1::EndSender(IAsync& aAsync, Brh& aUri, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Sender"));

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

void CpProxyAvOpenhomeOrgReceiver1::SyncProtocolInfo(Brh& aValue)
{
    SyncProtocolInfoAvOpenhomeOrgReceiver1 sync(*this, aValue);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1::EndProtocolInfo(IAsync& aAsync, Brh& aValue)
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

void CpProxyAvOpenhomeOrgReceiver1::SyncTransportState(Brh& aValue)
{
    SyncTransportStateAvOpenhomeOrgReceiver1 sync(*this, aValue);
    BeginTransportState(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1::BeginTransportState(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTransportState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTransportState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1::EndTransportState(IAsync& aAsync, Brh& aValue)
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

void CpProxyAvOpenhomeOrgReceiver1::SetPropertyUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgReceiver1::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetadataChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgReceiver1::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransportStateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgReceiver1::SetPropertyProtocolInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProtocolInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgReceiver1::PropertyUri(Brhz& aUri) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aUri.Set(iUri->Value());
}

void CpProxyAvOpenhomeOrgReceiver1::PropertyMetadata(Brhz& aMetadata) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aMetadata.Set(iMetadata->Value());
}

void CpProxyAvOpenhomeOrgReceiver1::PropertyTransportState(Brhz& aTransportState) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTransportState.Set(iTransportState->Value());
}

void CpProxyAvOpenhomeOrgReceiver1::PropertyProtocolInfo(Brhz& aProtocolInfo) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProtocolInfo.Set(iProtocolInfo->Value());
}

void CpProxyAvOpenhomeOrgReceiver1::UriPropertyChanged()
{
    ReportEvent(iUriChanged);
}

void CpProxyAvOpenhomeOrgReceiver1::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgReceiver1::TransportStatePropertyChanged()
{
    ReportEvent(iTransportStateChanged);
}

void CpProxyAvOpenhomeOrgReceiver1::ProtocolInfoPropertyChanged()
{
    ReportEvent(iProtocolInfoChanged);
}

