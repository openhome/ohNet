#include "CpAvOpenhomeOrgNetworkMonitor1.h"
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

class CpProxyAvOpenhomeOrgNetworkMonitor1C : public CpProxyC
{
public:
    CpProxyAvOpenhomeOrgNetworkMonitor1C(CpDeviceC aDevice);
    ~CpProxyAvOpenhomeOrgNetworkMonitor1C();
    //CpProxyAvOpenhomeOrgNetworkMonitor1* Proxy() { return static_cast<CpProxyAvOpenhomeOrgNetworkMonitor1*>(iProxy); }

    void SyncName(Brh& aName);
    void BeginName(FunctorAsync& aFunctor);
    void EndName(IAsync& aAsync, Brh& aName);

    void SyncPorts(TUint& aSender, TUint& aReceiver, TUint& aResults);
    void BeginPorts(FunctorAsync& aFunctor);
    void EndPorts(IAsync& aAsync, TUint& aSender, TUint& aReceiver, TUint& aResults);

    void SetPropertyNameChanged(Functor& aFunctor);
    void SetPropertySenderChanged(Functor& aFunctor);
    void SetPropertyReceiverChanged(Functor& aFunctor);
    void SetPropertyResultsChanged(Functor& aFunctor);

    void PropertyName(Brhz& aName) const;
    void PropertySender(TUint& aSender) const;
    void PropertyReceiver(TUint& aReceiver) const;
    void PropertyResults(TUint& aResults) const;
private:
    void NamePropertyChanged();
    void SenderPropertyChanged();
    void ReceiverPropertyChanged();
    void ResultsPropertyChanged();
private:
    Mutex iLock;
    Action* iActionName;
    Action* iActionPorts;
    PropertyString* iName;
    PropertyUint* iSender;
    PropertyUint* iReceiver;
    PropertyUint* iResults;
    Functor iNameChanged;
    Functor iSenderChanged;
    Functor iReceiverChanged;
    Functor iResultsChanged;
};


class SyncNameAvOpenhomeOrgNetworkMonitor1C : public SyncProxyAction
{
public:
    SyncNameAvOpenhomeOrgNetworkMonitor1C(CpProxyAvOpenhomeOrgNetworkMonitor1C& aProxy, Brh& aName);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncNameAvOpenhomeOrgNetworkMonitor1C() {};
private:
    CpProxyAvOpenhomeOrgNetworkMonitor1C& iService;
    Brh& iName;
};

SyncNameAvOpenhomeOrgNetworkMonitor1C::SyncNameAvOpenhomeOrgNetworkMonitor1C(CpProxyAvOpenhomeOrgNetworkMonitor1C& aProxy, Brh& aName)
    : iService(aProxy)
    , iName(aName)
{
}

void SyncNameAvOpenhomeOrgNetworkMonitor1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndName(aAsync, iName);
}


class SyncPortsAvOpenhomeOrgNetworkMonitor1C : public SyncProxyAction
{
public:
    SyncPortsAvOpenhomeOrgNetworkMonitor1C(CpProxyAvOpenhomeOrgNetworkMonitor1C& aProxy, TUint& aSender, TUint& aReceiver, TUint& aResults);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPortsAvOpenhomeOrgNetworkMonitor1C() {};
private:
    CpProxyAvOpenhomeOrgNetworkMonitor1C& iService;
    TUint& iSender;
    TUint& iReceiver;
    TUint& iResults;
};

SyncPortsAvOpenhomeOrgNetworkMonitor1C::SyncPortsAvOpenhomeOrgNetworkMonitor1C(CpProxyAvOpenhomeOrgNetworkMonitor1C& aProxy, TUint& aSender, TUint& aReceiver, TUint& aResults)
    : iService(aProxy)
    , iSender(aSender)
    , iReceiver(aReceiver)
    , iResults(aResults)
{
}

void SyncPortsAvOpenhomeOrgNetworkMonitor1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPorts(aAsync, iSender, iReceiver, iResults);
}

CpProxyAvOpenhomeOrgNetworkMonitor1C::CpProxyAvOpenhomeOrgNetworkMonitor1C(CpDeviceC aDevice)
    : CpProxyC("av-openhome-org", "NetworkMonitor", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;

    iActionName = new Action("Name");
    param = new OpenHome::Net::ParameterString("Name");
    iActionName->AddOutputParameter(param);

    iActionPorts = new Action("Ports");
    param = new OpenHome::Net::ParameterUint("Sender");
    iActionPorts->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("Receiver");
    iActionPorts->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("Results");
    iActionPorts->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgNetworkMonitor1C::NamePropertyChanged);
    iName = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Name", functor);
    AddProperty(iName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgNetworkMonitor1C::SenderPropertyChanged);
    iSender = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Sender", functor);
    AddProperty(iSender);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgNetworkMonitor1C::ReceiverPropertyChanged);
    iReceiver = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Receiver", functor);
    AddProperty(iReceiver);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgNetworkMonitor1C::ResultsPropertyChanged);
    iResults = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Results", functor);
    AddProperty(iResults);
}

CpProxyAvOpenhomeOrgNetworkMonitor1C::~CpProxyAvOpenhomeOrgNetworkMonitor1C()
{
    DestroyService();
    delete iActionName;
    delete iActionPorts;
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::SyncName(Brh& aName)
{
    SyncNameAvOpenhomeOrgNetworkMonitor1C sync(*this, aName);
    BeginName(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::BeginName(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::EndName(IAsync& aAsync, Brh& aName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Name"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aName);
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::SyncPorts(TUint& aSender, TUint& aReceiver, TUint& aResults)
{
    SyncPortsAvOpenhomeOrgNetworkMonitor1C sync(*this, aSender, aReceiver, aResults);
    BeginPorts(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::BeginPorts(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPorts, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPorts->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::EndPorts(IAsync& aAsync, TUint& aSender, TUint& aReceiver, TUint& aResults)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Ports"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aSender = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aReceiver = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aResults = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::SetPropertyNameChanged(Functor& aFunctor)
{
    iLock.Wait();
    iNameChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::SetPropertySenderChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSenderChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::SetPropertyReceiverChanged(Functor& aFunctor)
{
    iLock.Wait();
    iReceiverChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::SetPropertyResultsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iResultsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::PropertyName(Brhz& aName) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aName.Set(iName->Value());
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::PropertySender(TUint& aSender) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aSender = iSender->Value();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::PropertyReceiver(TUint& aReceiver) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aReceiver = iReceiver->Value();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::PropertyResults(TUint& aResults) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aResults = iResults->Value();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::NamePropertyChanged()
{
    ReportEvent(iNameChanged);
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::SenderPropertyChanged()
{
    ReportEvent(iSenderChanged);
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::ReceiverPropertyChanged()
{
    ReportEvent(iReceiverChanged);
}

void CpProxyAvOpenhomeOrgNetworkMonitor1C::ResultsPropertyChanged()
{
    ReportEvent(iResultsChanged);
}


THandle STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1Create(CpDeviceC aDevice)
{
    return new CpProxyAvOpenhomeOrgNetworkMonitor1C(aDevice);
}

void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1Destroy(THandle aHandle)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SyncName(THandle aHandle, char** aName)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aName;
    int32_t err = 0;
    try {
        proxyC->SyncName(buf_aName);
        *aName = buf_aName.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aName = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1BeginName(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginName(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1EndName(THandle aHandle, OhNetHandleAsync aAsync, char** aName)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aName;
    *aName = NULL;
    try {
        proxyC->EndName(*async, buf_aName);
        *aName = buf_aName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SyncPorts(THandle aHandle, uint32_t* aSender, uint32_t* aReceiver, uint32_t* aResults)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPorts(*aSender, *aReceiver, *aResults);
    }
    catch (ProxyError& ) {
        err = -1;
        *aSender = 0;
        *aReceiver = 0;
        *aResults = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1BeginPorts(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPorts(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1EndPorts(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aSender, uint32_t* aReceiver, uint32_t* aResults)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPorts(*async, *aSender, *aReceiver, *aResults);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SetPropertyNameChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyNameChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SetPropertySenderChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySenderChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SetPropertyReceiverChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyReceiverChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SetPropertyResultsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyResultsChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1PropertyName(THandle aHandle, char** aName)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aName;
    proxyC->PropertyName(buf_aName);
    *aName = buf_aName.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1PropertySender(THandle aHandle, uint32_t* aSender)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertySender(*aSender);
}

void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1PropertyReceiver(THandle aHandle, uint32_t* aReceiver)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyReceiver(*aReceiver);
}

void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1PropertyResults(THandle aHandle, uint32_t* aResults)
{
    CpProxyAvOpenhomeOrgNetworkMonitor1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgNetworkMonitor1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyResults(*aResults);
}

