#include "CpOpenhomeOrgSubscriptionLongPoll1.h"
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

class CpProxyOpenhomeOrgSubscriptionLongPoll1C : public CpProxyC
{
public:
    CpProxyOpenhomeOrgSubscriptionLongPoll1C(CpDeviceC aDevice);
    ~CpProxyOpenhomeOrgSubscriptionLongPoll1C();
    //CpProxyOpenhomeOrgSubscriptionLongPoll1* Proxy() { return static_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1*>(iProxy); }

    void SyncSubscribe(const Brx& aClientId, const Brx& aUdn, const Brx& aService, TUint aRequestedDuration, Brh& aSid, TUint& aDuration);
    void BeginSubscribe(const Brx& aClientId, const Brx& aUdn, const Brx& aService, TUint aRequestedDuration, FunctorAsync& aFunctor);
    void EndSubscribe(IAsync& aAsync, Brh& aSid, TUint& aDuration);

    void SyncUnsubscribe(const Brx& aSid);
    void BeginUnsubscribe(const Brx& aSid, FunctorAsync& aFunctor);
    void EndUnsubscribe(IAsync& aAsync);

    void SyncRenew(const Brx& aSid, TUint aRequestedDuration, TUint& aDuration);
    void BeginRenew(const Brx& aSid, TUint aRequestedDuration, FunctorAsync& aFunctor);
    void EndRenew(IAsync& aAsync, TUint& aDuration);

    void SyncGetPropertyUpdates(const Brx& aClientId, Brh& aUpdates);
    void BeginGetPropertyUpdates(const Brx& aClientId, FunctorAsync& aFunctor);
    void EndGetPropertyUpdates(IAsync& aAsync, Brh& aUpdates);


private:
private:
    Mutex iLock;
    Action* iActionSubscribe;
    Action* iActionUnsubscribe;
    Action* iActionRenew;
    Action* iActionGetPropertyUpdates;
};


class SyncSubscribeOpenhomeOrgSubscriptionLongPoll1C : public SyncProxyAction
{
public:
    SyncSubscribeOpenhomeOrgSubscriptionLongPoll1C(CpProxyOpenhomeOrgSubscriptionLongPoll1C& aProxy, Brh& aSid, TUint& aDuration);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSubscribeOpenhomeOrgSubscriptionLongPoll1C() {};
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1C& iService;
    Brh& iSid;
    TUint& iDuration;
};

SyncSubscribeOpenhomeOrgSubscriptionLongPoll1C::SyncSubscribeOpenhomeOrgSubscriptionLongPoll1C(CpProxyOpenhomeOrgSubscriptionLongPoll1C& aProxy, Brh& aSid, TUint& aDuration)
    : iService(aProxy)
    , iSid(aSid)
    , iDuration(aDuration)
{
}

void SyncSubscribeOpenhomeOrgSubscriptionLongPoll1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSubscribe(aAsync, iSid, iDuration);
}


class SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1C : public SyncProxyAction
{
public:
    SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1C(CpProxyOpenhomeOrgSubscriptionLongPoll1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1C() {};
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1C& iService;
};

SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1C::SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1C(CpProxyOpenhomeOrgSubscriptionLongPoll1C& aProxy)
    : iService(aProxy)
{
}

void SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndUnsubscribe(aAsync);
}


class SyncRenewOpenhomeOrgSubscriptionLongPoll1C : public SyncProxyAction
{
public:
    SyncRenewOpenhomeOrgSubscriptionLongPoll1C(CpProxyOpenhomeOrgSubscriptionLongPoll1C& aProxy, TUint& aDuration);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncRenewOpenhomeOrgSubscriptionLongPoll1C() {};
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1C& iService;
    TUint& iDuration;
};

SyncRenewOpenhomeOrgSubscriptionLongPoll1C::SyncRenewOpenhomeOrgSubscriptionLongPoll1C(CpProxyOpenhomeOrgSubscriptionLongPoll1C& aProxy, TUint& aDuration)
    : iService(aProxy)
    , iDuration(aDuration)
{
}

void SyncRenewOpenhomeOrgSubscriptionLongPoll1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRenew(aAsync, iDuration);
}


class SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1C : public SyncProxyAction
{
public:
    SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1C(CpProxyOpenhomeOrgSubscriptionLongPoll1C& aProxy, Brh& aUpdates);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1C() {};
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1C& iService;
    Brh& iUpdates;
};

SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1C::SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1C(CpProxyOpenhomeOrgSubscriptionLongPoll1C& aProxy, Brh& aUpdates)
    : iService(aProxy)
    , iUpdates(aUpdates)
{
}

void SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPropertyUpdates(aAsync, iUpdates);
}

CpProxyOpenhomeOrgSubscriptionLongPoll1C::CpProxyOpenhomeOrgSubscriptionLongPoll1C(CpDeviceC aDevice)
    : CpProxyC("openhome-org", "SubscriptionLongPoll", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;

    iActionSubscribe = new Action("Subscribe");
    param = new OpenHome::Net::ParameterString("ClientId");
    iActionSubscribe->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Udn");
    iActionSubscribe->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Service");
    iActionSubscribe->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedDuration");
    iActionSubscribe->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Sid");
    iActionSubscribe->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("Duration");
    iActionSubscribe->AddOutputParameter(param);

    iActionUnsubscribe = new Action("Unsubscribe");
    param = new OpenHome::Net::ParameterString("Sid");
    iActionUnsubscribe->AddInputParameter(param);

    iActionRenew = new Action("Renew");
    param = new OpenHome::Net::ParameterString("Sid");
    iActionRenew->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedDuration");
    iActionRenew->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Duration");
    iActionRenew->AddOutputParameter(param);

    iActionGetPropertyUpdates = new Action("GetPropertyUpdates");
    param = new OpenHome::Net::ParameterString("ClientId");
    iActionGetPropertyUpdates->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Updates");
    iActionGetPropertyUpdates->AddOutputParameter(param);
}

CpProxyOpenhomeOrgSubscriptionLongPoll1C::~CpProxyOpenhomeOrgSubscriptionLongPoll1C()
{
    DestroyService();
    delete iActionSubscribe;
    delete iActionUnsubscribe;
    delete iActionRenew;
    delete iActionGetPropertyUpdates;
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::SyncSubscribe(const Brx& aClientId, const Brx& aUdn, const Brx& aService, TUint aRequestedDuration, Brh& aSid, TUint& aDuration)
{
    SyncSubscribeOpenhomeOrgSubscriptionLongPoll1C sync(*this, aSid, aDuration);
    BeginSubscribe(aClientId, aUdn, aService, aRequestedDuration, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::BeginSubscribe(const Brx& aClientId, const Brx& aUdn, const Brx& aService, TUint aRequestedDuration, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSubscribe, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSubscribe->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aClientId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUdn));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aService));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedDuration));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSubscribe->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::EndSubscribe(IAsync& aAsync, Brh& aSid, TUint& aDuration)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Subscribe"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSid);
    aDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::SyncUnsubscribe(const Brx& aSid)
{
    SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1C sync(*this);
    BeginUnsubscribe(aSid, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::BeginUnsubscribe(const Brx& aSid, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionUnsubscribe, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionUnsubscribe->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSid));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::EndUnsubscribe(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Unsubscribe"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::SyncRenew(const Brx& aSid, TUint aRequestedDuration, TUint& aDuration)
{
    SyncRenewOpenhomeOrgSubscriptionLongPoll1C sync(*this, aDuration);
    BeginRenew(aSid, aRequestedDuration, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::BeginRenew(const Brx& aSid, TUint aRequestedDuration, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRenew, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRenew->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSid));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedDuration));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRenew->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::EndRenew(IAsync& aAsync, TUint& aDuration)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Renew"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::SyncGetPropertyUpdates(const Brx& aClientId, Brh& aUpdates)
{
    SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1C sync(*this, aUpdates);
    BeginGetPropertyUpdates(aClientId, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::BeginGetPropertyUpdates(const Brx& aClientId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetPropertyUpdates, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetPropertyUpdates->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aClientId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetPropertyUpdates->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1C::EndGetPropertyUpdates(IAsync& aAsync, Brh& aUpdates)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetPropertyUpdates"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aUpdates);
}


THandle STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1Create(CpDeviceC aDevice)
{
    return new CpProxyOpenhomeOrgSubscriptionLongPoll1C(aDevice);
}

void STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1Destroy(THandle aHandle)
{
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1SyncSubscribe(THandle aHandle, const char* aClientId, const char* aUdn, const char* aService, uint32_t aRequestedDuration, char** aSid, uint32_t* aDuration)
{
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aClientId(aClientId);
    Brh buf_aUdn(aUdn);
    Brh buf_aService(aService);
    Brh buf_aSid;
    int32_t err = 0;
    try {
        proxyC->SyncSubscribe(buf_aClientId, buf_aUdn, buf_aService, aRequestedDuration, buf_aSid, *aDuration);
        *aSid = buf_aSid.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aSid = NULL;
        *aDuration = 0;
    }
    return err;
}

void STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1BeginSubscribe(THandle aHandle, const char* aClientId, const char* aUdn, const char* aService, uint32_t aRequestedDuration, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aClientId(aClientId);
    Brh buf_aUdn(aUdn);
    Brh buf_aService(aService);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSubscribe(buf_aClientId, buf_aUdn, buf_aService, aRequestedDuration, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1EndSubscribe(THandle aHandle, OhNetHandleAsync aAsync, char** aSid, uint32_t* aDuration)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aSid;
    *aSid = NULL;
    try {
        proxyC->EndSubscribe(*async, buf_aSid, *aDuration);
        *aSid = buf_aSid.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1SyncUnsubscribe(THandle aHandle, const char* aSid)
{
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSid(aSid);
    int32_t err = 0;
    try {
        proxyC->SyncUnsubscribe(buf_aSid);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1BeginUnsubscribe(THandle aHandle, const char* aSid, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSid(aSid);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginUnsubscribe(buf_aSid, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1EndUnsubscribe(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndUnsubscribe(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1SyncRenew(THandle aHandle, const char* aSid, uint32_t aRequestedDuration, uint32_t* aDuration)
{
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSid(aSid);
    int32_t err = 0;
    try {
        proxyC->SyncRenew(buf_aSid, aRequestedDuration, *aDuration);
    }
    catch (ProxyError& ) {
        err = -1;
        *aDuration = 0;
    }
    return err;
}

void STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1BeginRenew(THandle aHandle, const char* aSid, uint32_t aRequestedDuration, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSid(aSid);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginRenew(buf_aSid, aRequestedDuration, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1EndRenew(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aDuration)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndRenew(*async, *aDuration);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1SyncGetPropertyUpdates(THandle aHandle, const char* aClientId, char** aUpdates)
{
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aClientId(aClientId);
    Brh buf_aUpdates;
    int32_t err = 0;
    try {
        proxyC->SyncGetPropertyUpdates(buf_aClientId, buf_aUpdates);
        *aUpdates = buf_aUpdates.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aUpdates = NULL;
    }
    return err;
}

void STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1BeginGetPropertyUpdates(THandle aHandle, const char* aClientId, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aClientId(aClientId);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetPropertyUpdates(buf_aClientId, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1EndGetPropertyUpdates(THandle aHandle, OhNetHandleAsync aAsync, char** aUpdates)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgSubscriptionLongPoll1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgSubscriptionLongPoll1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aUpdates;
    *aUpdates = NULL;
    try {
        proxyC->EndGetPropertyUpdates(*async, buf_aUpdates);
        *aUpdates = buf_aUpdates.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

