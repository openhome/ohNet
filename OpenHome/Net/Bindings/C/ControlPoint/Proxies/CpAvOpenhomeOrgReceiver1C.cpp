#include "CpAvOpenhomeOrgReceiver1.h"
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

class CpProxyAvOpenhomeOrgReceiver1C : public CpProxyC
{
public:
    CpProxyAvOpenhomeOrgReceiver1C(CpDeviceC aDevice);
    ~CpProxyAvOpenhomeOrgReceiver1C();
    //CpProxyAvOpenhomeOrgReceiver1* Proxy() { return static_cast<CpProxyAvOpenhomeOrgReceiver1*>(iProxy); }

    void SyncPlay();
    void BeginPlay(FunctorAsync& aFunctor);
    void EndPlay(IAsync& aAsync);

    void SyncStop();
    void BeginStop(FunctorAsync& aFunctor);
    void EndStop(IAsync& aAsync);

    void SyncSetSender(const Brx& aUri, const Brx& aMetadata);
    void BeginSetSender(const Brx& aUri, const Brx& aMetadata, FunctorAsync& aFunctor);
    void EndSetSender(IAsync& aAsync);

    void SyncSender(Brh& aUri, Brh& aMetadata);
    void BeginSender(FunctorAsync& aFunctor);
    void EndSender(IAsync& aAsync, Brh& aUri, Brh& aMetadata);

    void SyncProtocolInfo(Brh& aValue);
    void BeginProtocolInfo(FunctorAsync& aFunctor);
    void EndProtocolInfo(IAsync& aAsync, Brh& aValue);

    void SyncTransportState(Brh& aValue);
    void BeginTransportState(FunctorAsync& aFunctor);
    void EndTransportState(IAsync& aAsync, Brh& aValue);

    void SetPropertyUriChanged(Functor& aFunctor);
    void SetPropertyMetadataChanged(Functor& aFunctor);
    void SetPropertyTransportStateChanged(Functor& aFunctor);
    void SetPropertyProtocolInfoChanged(Functor& aFunctor);

    void PropertyUri(Brhz& aUri) const;
    void PropertyMetadata(Brhz& aMetadata) const;
    void PropertyTransportState(Brhz& aTransportState) const;
    void PropertyProtocolInfo(Brhz& aProtocolInfo) const;
private:
    void UriPropertyChanged();
    void MetadataPropertyChanged();
    void TransportStatePropertyChanged();
    void ProtocolInfoPropertyChanged();
private:
    Mutex iLock;
    Action* iActionPlay;
    Action* iActionStop;
    Action* iActionSetSender;
    Action* iActionSender;
    Action* iActionProtocolInfo;
    Action* iActionTransportState;
    PropertyString* iUri;
    PropertyString* iMetadata;
    PropertyString* iTransportState;
    PropertyString* iProtocolInfo;
    Functor iUriChanged;
    Functor iMetadataChanged;
    Functor iTransportStateChanged;
    Functor iProtocolInfoChanged;
};


class SyncPlayAvOpenhomeOrgReceiver1C : public SyncProxyAction
{
public:
    SyncPlayAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPlayAvOpenhomeOrgReceiver1C() {};
private:
    CpProxyAvOpenhomeOrgReceiver1C& iService;
};

SyncPlayAvOpenhomeOrgReceiver1C::SyncPlayAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy)
    : iService(aProxy)
{
}

void SyncPlayAvOpenhomeOrgReceiver1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncStopAvOpenhomeOrgReceiver1C : public SyncProxyAction
{
public:
    SyncStopAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopAvOpenhomeOrgReceiver1C() {};
private:
    CpProxyAvOpenhomeOrgReceiver1C& iService;
};

SyncStopAvOpenhomeOrgReceiver1C::SyncStopAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy)
    : iService(aProxy)
{
}

void SyncStopAvOpenhomeOrgReceiver1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncSetSenderAvOpenhomeOrgReceiver1C : public SyncProxyAction
{
public:
    SyncSetSenderAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetSenderAvOpenhomeOrgReceiver1C() {};
private:
    CpProxyAvOpenhomeOrgReceiver1C& iService;
};

SyncSetSenderAvOpenhomeOrgReceiver1C::SyncSetSenderAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetSenderAvOpenhomeOrgReceiver1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSender(aAsync);
}


class SyncSenderAvOpenhomeOrgReceiver1C : public SyncProxyAction
{
public:
    SyncSenderAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy, Brh& aUri, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSenderAvOpenhomeOrgReceiver1C() {};
private:
    CpProxyAvOpenhomeOrgReceiver1C& iService;
    Brh& iUri;
    Brh& iMetadata;
};

SyncSenderAvOpenhomeOrgReceiver1C::SyncSenderAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy, Brh& aUri, Brh& aMetadata)
    : iService(aProxy)
    , iUri(aUri)
    , iMetadata(aMetadata)
{
}

void SyncSenderAvOpenhomeOrgReceiver1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSender(aAsync, iUri, iMetadata);
}


class SyncProtocolInfoAvOpenhomeOrgReceiver1C : public SyncProxyAction
{
public:
    SyncProtocolInfoAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncProtocolInfoAvOpenhomeOrgReceiver1C() {};
private:
    CpProxyAvOpenhomeOrgReceiver1C& iService;
    Brh& iValue;
};

SyncProtocolInfoAvOpenhomeOrgReceiver1C::SyncProtocolInfoAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncProtocolInfoAvOpenhomeOrgReceiver1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iValue);
}


class SyncTransportStateAvOpenhomeOrgReceiver1C : public SyncProxyAction
{
public:
    SyncTransportStateAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTransportStateAvOpenhomeOrgReceiver1C() {};
private:
    CpProxyAvOpenhomeOrgReceiver1C& iService;
    Brh& iValue;
};

SyncTransportStateAvOpenhomeOrgReceiver1C::SyncTransportStateAvOpenhomeOrgReceiver1C(CpProxyAvOpenhomeOrgReceiver1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncTransportStateAvOpenhomeOrgReceiver1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTransportState(aAsync, iValue);
}

CpProxyAvOpenhomeOrgReceiver1C::CpProxyAvOpenhomeOrgReceiver1C(CpDeviceC aDevice)
    : CpProxyC("av-openhome-org", "Receiver", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
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
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgReceiver1C::UriPropertyChanged);
    iUri = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Uri", functor);
    AddProperty(iUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgReceiver1C::MetadataPropertyChanged);
    iMetadata = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgReceiver1C::TransportStatePropertyChanged);
    iTransportState = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "TransportState", functor);
    AddProperty(iTransportState);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgReceiver1C::ProtocolInfoPropertyChanged);
    iProtocolInfo = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "ProtocolInfo", functor);
    AddProperty(iProtocolInfo);
}

CpProxyAvOpenhomeOrgReceiver1C::~CpProxyAvOpenhomeOrgReceiver1C()
{
    DestroyService();
    delete iActionPlay;
    delete iActionStop;
    delete iActionSetSender;
    delete iActionSender;
    delete iActionProtocolInfo;
    delete iActionTransportState;
}

void CpProxyAvOpenhomeOrgReceiver1C::SyncPlay()
{
    SyncPlayAvOpenhomeOrgReceiver1C sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1C::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlay, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1C::EndPlay(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgReceiver1C::SyncStop()
{
    SyncStopAvOpenhomeOrgReceiver1C sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1C::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStop, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1C::EndStop(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgReceiver1C::SyncSetSender(const Brx& aUri, const Brx& aMetadata)
{
    SyncSetSenderAvOpenhomeOrgReceiver1C sync(*this);
    BeginSetSender(aUri, aMetadata, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1C::BeginSetSender(const Brx& aUri, const Brx& aMetadata, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetSender, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSender->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUri));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aMetadata));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1C::EndSetSender(IAsync& aAsync)
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

void CpProxyAvOpenhomeOrgReceiver1C::SyncSender(Brh& aUri, Brh& aMetadata)
{
    SyncSenderAvOpenhomeOrgReceiver1C sync(*this, aUri, aMetadata);
    BeginSender(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1C::BeginSender(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSender, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSender->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1C::EndSender(IAsync& aAsync, Brh& aUri, Brh& aMetadata)
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

void CpProxyAvOpenhomeOrgReceiver1C::SyncProtocolInfo(Brh& aValue)
{
    SyncProtocolInfoAvOpenhomeOrgReceiver1C sync(*this, aValue);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1C::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1C::EndProtocolInfo(IAsync& aAsync, Brh& aValue)
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

void CpProxyAvOpenhomeOrgReceiver1C::SyncTransportState(Brh& aValue)
{
    SyncTransportStateAvOpenhomeOrgReceiver1C sync(*this, aValue);
    BeginTransportState(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgReceiver1C::BeginTransportState(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTransportState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTransportState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgReceiver1C::EndTransportState(IAsync& aAsync, Brh& aValue)
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

void CpProxyAvOpenhomeOrgReceiver1C::SetPropertyUriChanged(Functor& aFunctor)
{
    iLock.Wait();
    iUriChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgReceiver1C::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetadataChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgReceiver1C::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTransportStateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgReceiver1C::SetPropertyProtocolInfoChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProtocolInfoChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgReceiver1C::PropertyUri(Brhz& aUri) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aUri.Set(iUri->Value());
}

void CpProxyAvOpenhomeOrgReceiver1C::PropertyMetadata(Brhz& aMetadata) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aMetadata.Set(iMetadata->Value());
}

void CpProxyAvOpenhomeOrgReceiver1C::PropertyTransportState(Brhz& aTransportState) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aTransportState.Set(iTransportState->Value());
}

void CpProxyAvOpenhomeOrgReceiver1C::PropertyProtocolInfo(Brhz& aProtocolInfo) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aProtocolInfo.Set(iProtocolInfo->Value());
}

void CpProxyAvOpenhomeOrgReceiver1C::UriPropertyChanged()
{
    ReportEvent(iUriChanged);
}

void CpProxyAvOpenhomeOrgReceiver1C::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgReceiver1C::TransportStatePropertyChanged()
{
    ReportEvent(iTransportStateChanged);
}

void CpProxyAvOpenhomeOrgReceiver1C::ProtocolInfoPropertyChanged()
{
    ReportEvent(iProtocolInfoChanged);
}


THandle STDCALL CpProxyAvOpenhomeOrgReceiver1Create(CpDeviceC aDevice)
{
    return new CpProxyAvOpenhomeOrgReceiver1C(aDevice);
}

void STDCALL CpProxyAvOpenhomeOrgReceiver1Destroy(THandle aHandle)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1SyncPlay(THandle aHandle)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
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

void STDCALL CpProxyAvOpenhomeOrgReceiver1BeginPlay(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPlay(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1EndPlay(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1SyncStop(THandle aHandle)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
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

void STDCALL CpProxyAvOpenhomeOrgReceiver1BeginStop(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStop(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1EndStop(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1SyncSetSender(THandle aHandle, const char* aUri, const char* aMetadata)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri(aUri);
    Brh buf_aMetadata(aMetadata);
    int32_t err = 0;
    try {
        proxyC->SyncSetSender(buf_aUri, buf_aMetadata);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgReceiver1BeginSetSender(THandle aHandle, const char* aUri, const char* aMetadata, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri(aUri);
    Brh buf_aMetadata(aMetadata);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetSender(buf_aUri, buf_aMetadata, functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1EndSetSender(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetSender(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1SyncSender(THandle aHandle, char** aUri, char** aMetadata)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri;
    Brh buf_aMetadata;
    int32_t err = 0;
    try {
        proxyC->SyncSender(buf_aUri, buf_aMetadata);
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

void STDCALL CpProxyAvOpenhomeOrgReceiver1BeginSender(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSender(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1EndSender(THandle aHandle, OhNetHandleAsync aAsync, char** aUri, char** aMetadata)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aUri;
    *aUri = NULL;
    Brh buf_aMetadata;
    *aMetadata = NULL;
    try {
        proxyC->EndSender(*async, buf_aUri, buf_aMetadata);
        *aUri = buf_aUri.Extract();
        *aMetadata = buf_aMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1SyncProtocolInfo(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
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

void STDCALL CpProxyAvOpenhomeOrgReceiver1BeginProtocolInfo(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginProtocolInfo(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1EndProtocolInfo(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
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

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1SyncTransportState(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
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

void STDCALL CpProxyAvOpenhomeOrgReceiver1BeginTransportState(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginTransportState(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgReceiver1EndTransportState(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
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

void STDCALL CpProxyAvOpenhomeOrgReceiver1SetPropertyUriChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyUriChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgReceiver1SetPropertyMetadataChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetadataChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgReceiver1SetPropertyTransportStateChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTransportStateChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgReceiver1SetPropertyProtocolInfoChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProtocolInfoChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgReceiver1PropertyUri(THandle aHandle, char** aUri)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aUri;
    proxyC->PropertyUri(buf_aUri);
    *aUri = buf_aUri.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgReceiver1PropertyMetadata(THandle aHandle, char** aMetadata)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetadata;
    proxyC->PropertyMetadata(buf_aMetadata);
    *aMetadata = buf_aMetadata.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgReceiver1PropertyTransportState(THandle aHandle, char** aTransportState)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransportState;
    proxyC->PropertyTransportState(buf_aTransportState);
    *aTransportState = buf_aTransportState.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgReceiver1PropertyProtocolInfo(THandle aHandle, char** aProtocolInfo)
{
    CpProxyAvOpenhomeOrgReceiver1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgReceiver1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProtocolInfo;
    proxyC->PropertyProtocolInfo(buf_aProtocolInfo);
    *aProtocolInfo = buf_aProtocolInfo.Transfer();
}

