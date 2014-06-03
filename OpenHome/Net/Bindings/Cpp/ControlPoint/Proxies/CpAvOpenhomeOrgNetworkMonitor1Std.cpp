#include "CpAvOpenhomeOrgNetworkMonitor1.h"
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


class SyncNameAvOpenhomeOrgNetworkMonitor1Cpp : public SyncProxyAction
{
public:
    SyncNameAvOpenhomeOrgNetworkMonitor1Cpp(CpProxyAvOpenhomeOrgNetworkMonitor1Cpp& aProxy, std::string& aName);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncNameAvOpenhomeOrgNetworkMonitor1Cpp() {}
private:
    CpProxyAvOpenhomeOrgNetworkMonitor1Cpp& iService;
    std::string& iName;
};

SyncNameAvOpenhomeOrgNetworkMonitor1Cpp::SyncNameAvOpenhomeOrgNetworkMonitor1Cpp(CpProxyAvOpenhomeOrgNetworkMonitor1Cpp& aProxy, std::string& aName)
    : iService(aProxy)
    , iName(aName)
{
}

void SyncNameAvOpenhomeOrgNetworkMonitor1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndName(aAsync, iName);
}


class SyncPortsAvOpenhomeOrgNetworkMonitor1Cpp : public SyncProxyAction
{
public:
    SyncPortsAvOpenhomeOrgNetworkMonitor1Cpp(CpProxyAvOpenhomeOrgNetworkMonitor1Cpp& aProxy, uint32_t& aSender, uint32_t& aReceiver, uint32_t& aResults);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPortsAvOpenhomeOrgNetworkMonitor1Cpp() {}
private:
    CpProxyAvOpenhomeOrgNetworkMonitor1Cpp& iService;
    uint32_t& iSender;
    uint32_t& iReceiver;
    uint32_t& iResults;
};

SyncPortsAvOpenhomeOrgNetworkMonitor1Cpp::SyncPortsAvOpenhomeOrgNetworkMonitor1Cpp(CpProxyAvOpenhomeOrgNetworkMonitor1Cpp& aProxy, uint32_t& aSender, uint32_t& aReceiver, uint32_t& aResults)
    : iService(aProxy)
    , iSender(aSender)
    , iReceiver(aReceiver)
    , iResults(aResults)
{
}

void SyncPortsAvOpenhomeOrgNetworkMonitor1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPorts(aAsync, iSender, iReceiver, iResults);
}


CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::CpProxyAvOpenhomeOrgNetworkMonitor1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("av-openhome-org", "NetworkMonitor", 1, aDevice.Device())
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
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::NamePropertyChanged);
    iName = new PropertyString(aDevice.Device().GetCpStack().Env(), "Name", functor);
    AddProperty(iName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::SenderPropertyChanged);
    iSender = new PropertyUint(aDevice.Device().GetCpStack().Env(), "Sender", functor);
    AddProperty(iSender);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::ReceiverPropertyChanged);
    iReceiver = new PropertyUint(aDevice.Device().GetCpStack().Env(), "Receiver", functor);
    AddProperty(iReceiver);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::ResultsPropertyChanged);
    iResults = new PropertyUint(aDevice.Device().GetCpStack().Env(), "Results", functor);
    AddProperty(iResults);
}

CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::~CpProxyAvOpenhomeOrgNetworkMonitor1Cpp()
{
    DestroyService();
    delete iActionName;
    delete iActionPorts;
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::SyncName(std::string& aName)
{
    SyncNameAvOpenhomeOrgNetworkMonitor1Cpp sync(*this, aName);
    BeginName(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::BeginName(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::EndName(IAsync& aAsync, std::string& aName)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::SyncPorts(uint32_t& aSender, uint32_t& aReceiver, uint32_t& aResults)
{
    SyncPortsAvOpenhomeOrgNetworkMonitor1Cpp sync(*this, aSender, aReceiver, aResults);
    BeginPorts(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::BeginPorts(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPorts, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPorts->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::EndPorts(IAsync& aAsync, uint32_t& aSender, uint32_t& aReceiver, uint32_t& aResults)
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

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::SetPropertyNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::SetPropertySenderChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSenderChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::SetPropertyReceiverChanged(Functor& aFunctor)
{
    iLock->Wait();
    iReceiverChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::SetPropertyResultsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iResultsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::PropertyName(std::string& aName) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iName->Value();
    aName.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::PropertySender(uint32_t& aSender) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSender = iSender->Value();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::PropertyReceiver(uint32_t& aReceiver) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aReceiver = iReceiver->Value();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::PropertyResults(uint32_t& aResults) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aResults = iResults->Value();
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::NamePropertyChanged()
{
    ReportEvent(iNameChanged);
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::SenderPropertyChanged()
{
    ReportEvent(iSenderChanged);
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::ReceiverPropertyChanged()
{
    ReportEvent(iReceiverChanged);
}

void CpProxyAvOpenhomeOrgNetworkMonitor1Cpp::ResultsPropertyChanged()
{
    ReportEvent(iResultsChanged);
}

