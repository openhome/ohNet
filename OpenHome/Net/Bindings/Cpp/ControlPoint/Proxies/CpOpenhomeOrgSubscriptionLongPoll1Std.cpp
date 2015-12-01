#include "CpOpenhomeOrgSubscriptionLongPoll1.h"
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


class SyncSubscribeOpenhomeOrgSubscriptionLongPoll1Cpp : public SyncProxyAction
{
public:
    SyncSubscribeOpenhomeOrgSubscriptionLongPoll1Cpp(CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& aProxy, std::string& aSid, uint32_t& aDuration);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSubscribeOpenhomeOrgSubscriptionLongPoll1Cpp() {}
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& iService;
    std::string& iSid;
    uint32_t& iDuration;
};

SyncSubscribeOpenhomeOrgSubscriptionLongPoll1Cpp::SyncSubscribeOpenhomeOrgSubscriptionLongPoll1Cpp(CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& aProxy, std::string& aSid, uint32_t& aDuration)
    : iService(aProxy)
    , iSid(aSid)
    , iDuration(aDuration)
{
}

void SyncSubscribeOpenhomeOrgSubscriptionLongPoll1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSubscribe(aAsync, iSid, iDuration);
}


class SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1Cpp : public SyncProxyAction
{
public:
    SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1Cpp(CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1Cpp() {}
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& iService;
};

SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1Cpp::SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1Cpp(CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndUnsubscribe(aAsync);
}


class SyncRenewOpenhomeOrgSubscriptionLongPoll1Cpp : public SyncProxyAction
{
public:
    SyncRenewOpenhomeOrgSubscriptionLongPoll1Cpp(CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& aProxy, uint32_t& aDuration);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncRenewOpenhomeOrgSubscriptionLongPoll1Cpp() {}
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& iService;
    uint32_t& iDuration;
};

SyncRenewOpenhomeOrgSubscriptionLongPoll1Cpp::SyncRenewOpenhomeOrgSubscriptionLongPoll1Cpp(CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& aProxy, uint32_t& aDuration)
    : iService(aProxy)
    , iDuration(aDuration)
{
}

void SyncRenewOpenhomeOrgSubscriptionLongPoll1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRenew(aAsync, iDuration);
}


class SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1Cpp : public SyncProxyAction
{
public:
    SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1Cpp(CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& aProxy, std::string& aUpdates);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1Cpp() {}
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& iService;
    std::string& iUpdates;
};

SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1Cpp::SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1Cpp(CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp& aProxy, std::string& aUpdates)
    : iService(aProxy)
    , iUpdates(aUpdates)
{
}

void SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPropertyUpdates(aAsync, iUpdates);
}


CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp(CpDeviceCpp& aDevice)
    : iCpProxy("openhome-org", "SubscriptionLongPoll", 1, aDevice.Device())
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

CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::~CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp()
{
    DestroyService();
    delete iActionSubscribe;
    delete iActionUnsubscribe;
    delete iActionRenew;
    delete iActionGetPropertyUpdates;
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::SyncSubscribe(const std::string& aClientId, const std::string& aUdn, const std::string& aService, uint32_t aRequestedDuration, std::string& aSid, uint32_t& aDuration)
{
    SyncSubscribeOpenhomeOrgSubscriptionLongPoll1Cpp sync(*this, aSid, aDuration);
    BeginSubscribe(aClientId, aUdn, aService, aRequestedDuration, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::BeginSubscribe(const std::string& aClientId, const std::string& aUdn, const std::string& aService, uint32_t aRequestedDuration, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionSubscribe, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSubscribe->InputParameters();
    {
        Brn buf((const TByte*)aClientId.c_str(), (TUint)aClientId.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aUdn.c_str(), (TUint)aUdn.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aService.c_str(), (TUint)aService.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedDuration));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSubscribe->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::EndSubscribe(IAsync& aAsync, std::string& aSid, uint32_t& aDuration)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSid.assign((const char*)val.Ptr(), val.Bytes());
    }
    aDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::SyncUnsubscribe(const std::string& aSid)
{
    SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1Cpp sync(*this);
    BeginUnsubscribe(aSid, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::BeginUnsubscribe(const std::string& aSid, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionUnsubscribe, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionUnsubscribe->InputParameters();
    {
        Brn buf((const TByte*)aSid.c_str(), (TUint)aSid.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::EndUnsubscribe(IAsync& aAsync)
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

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::SyncRenew(const std::string& aSid, uint32_t aRequestedDuration, uint32_t& aDuration)
{
    SyncRenewOpenhomeOrgSubscriptionLongPoll1Cpp sync(*this, aDuration);
    BeginRenew(aSid, aRequestedDuration, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::BeginRenew(const std::string& aSid, uint32_t aRequestedDuration, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionRenew, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRenew->InputParameters();
    {
        Brn buf((const TByte*)aSid.c_str(), (TUint)aSid.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedDuration));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRenew->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::EndRenew(IAsync& aAsync, uint32_t& aDuration)
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

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::SyncGetPropertyUpdates(const std::string& aClientId, std::string& aUpdates)
{
    SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1Cpp sync(*this, aUpdates);
    BeginGetPropertyUpdates(aClientId, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::BeginGetPropertyUpdates(const std::string& aClientId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iCpProxy.GetService().Invocation(*iActionGetPropertyUpdates, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetPropertyUpdates->InputParameters();
    {
        Brn buf((const TByte*)aClientId.c_str(), (TUint)aClientId.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetPropertyUpdates->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iCpProxy.GetInvocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::EndGetPropertyUpdates(IAsync& aAsync, std::string& aUpdates)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aUpdates.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::Subscribe()
{
  iCpProxy.Subscribe();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::Unsubscribe()
{
 iCpProxy.Unsubscribe();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::SetPropertyChanged(Functor& aFunctor)
{
  iCpProxy.SetPropertyChanged(aFunctor);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::SetPropertyInitialEvent(Functor& aFunctor)
{
  iCpProxy.SetPropertyInitialEvent(aFunctor);
}
void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::AddProperty(Property* aProperty)
{
  iCpProxy.AddProperty(aProperty);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::DestroyService()
{
  iCpProxy.DestroyService();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::ReportEvent(Functor aFunctor)
{
  iCpProxy.ReportEvent(aFunctor);
}

TUint CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp::Version() const
{
  return iCpProxy.Version();
}

