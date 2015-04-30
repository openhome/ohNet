#include "CpUpnpOrgConnectionManager1.h"
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


class SyncGetProtocolInfoUpnpOrgConnectionManager1Cpp : public SyncProxyAction
{
public:
    SyncGetProtocolInfoUpnpOrgConnectionManager1Cpp(CpProxyUpnpOrgConnectionManager1Cpp& aProxy, std::string& aSource, std::string& aSink);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetProtocolInfoUpnpOrgConnectionManager1Cpp() {}
private:
    CpProxyUpnpOrgConnectionManager1Cpp& iService;
    std::string& iSource;
    std::string& iSink;
};

SyncGetProtocolInfoUpnpOrgConnectionManager1Cpp::SyncGetProtocolInfoUpnpOrgConnectionManager1Cpp(CpProxyUpnpOrgConnectionManager1Cpp& aProxy, std::string& aSource, std::string& aSink)
    : iService(aProxy)
    , iSource(aSource)
    , iSink(aSink)
{
}

void SyncGetProtocolInfoUpnpOrgConnectionManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetProtocolInfo(aAsync, iSource, iSink);
}


class SyncPrepareForConnectionUpnpOrgConnectionManager1Cpp : public SyncProxyAction
{
public:
    SyncPrepareForConnectionUpnpOrgConnectionManager1Cpp(CpProxyUpnpOrgConnectionManager1Cpp& aProxy, int32_t& aConnectionID, int32_t& aAVTransportID, int32_t& aRcsID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPrepareForConnectionUpnpOrgConnectionManager1Cpp() {}
private:
    CpProxyUpnpOrgConnectionManager1Cpp& iService;
    int32_t& iConnectionID;
    int32_t& iAVTransportID;
    int32_t& iRcsID;
};

SyncPrepareForConnectionUpnpOrgConnectionManager1Cpp::SyncPrepareForConnectionUpnpOrgConnectionManager1Cpp(CpProxyUpnpOrgConnectionManager1Cpp& aProxy, int32_t& aConnectionID, int32_t& aAVTransportID, int32_t& aRcsID)
    : iService(aProxy)
    , iConnectionID(aConnectionID)
    , iAVTransportID(aAVTransportID)
    , iRcsID(aRcsID)
{
}

void SyncPrepareForConnectionUpnpOrgConnectionManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrepareForConnection(aAsync, iConnectionID, iAVTransportID, iRcsID);
}


class SyncConnectionCompleteUpnpOrgConnectionManager1Cpp : public SyncProxyAction
{
public:
    SyncConnectionCompleteUpnpOrgConnectionManager1Cpp(CpProxyUpnpOrgConnectionManager1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncConnectionCompleteUpnpOrgConnectionManager1Cpp() {}
private:
    CpProxyUpnpOrgConnectionManager1Cpp& iService;
};

SyncConnectionCompleteUpnpOrgConnectionManager1Cpp::SyncConnectionCompleteUpnpOrgConnectionManager1Cpp(CpProxyUpnpOrgConnectionManager1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncConnectionCompleteUpnpOrgConnectionManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndConnectionComplete(aAsync);
}


class SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1Cpp : public SyncProxyAction
{
public:
    SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1Cpp(CpProxyUpnpOrgConnectionManager1Cpp& aProxy, std::string& aConnectionIDs);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1Cpp() {}
private:
    CpProxyUpnpOrgConnectionManager1Cpp& iService;
    std::string& iConnectionIDs;
};

SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1Cpp::SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1Cpp(CpProxyUpnpOrgConnectionManager1Cpp& aProxy, std::string& aConnectionIDs)
    : iService(aProxy)
    , iConnectionIDs(aConnectionIDs)
{
}

void SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentConnectionIDs(aAsync, iConnectionIDs);
}


class SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1Cpp : public SyncProxyAction
{
public:
    SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1Cpp(CpProxyUpnpOrgConnectionManager1Cpp& aProxy, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1Cpp() {}
private:
    CpProxyUpnpOrgConnectionManager1Cpp& iService;
    int32_t& iRcsID;
    int32_t& iAVTransportID;
    std::string& iProtocolInfo;
    std::string& iPeerConnectionManager;
    int32_t& iPeerConnectionID;
    std::string& iDirection;
    std::string& iStatus;
};

SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1Cpp::SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1Cpp(CpProxyUpnpOrgConnectionManager1Cpp& aProxy, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus)
    : iService(aProxy)
    , iRcsID(aRcsID)
    , iAVTransportID(aAVTransportID)
    , iProtocolInfo(aProtocolInfo)
    , iPeerConnectionManager(aPeerConnectionManager)
    , iPeerConnectionID(aPeerConnectionID)
    , iDirection(aDirection)
    , iStatus(aStatus)
{
}

void SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentConnectionInfo(aAsync, iRcsID, iAVTransportID, iProtocolInfo, iPeerConnectionManager, iPeerConnectionID, iDirection, iStatus);
}


CpProxyUpnpOrgConnectionManager1Cpp::CpProxyUpnpOrgConnectionManager1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("schemas-upnp-org", "ConnectionManager", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionGetProtocolInfo = new Action("GetProtocolInfo");
    param = new OpenHome::Net::ParameterString("Source");
    iActionGetProtocolInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Sink");
    iActionGetProtocolInfo->AddOutputParameter(param);

    iActionPrepareForConnection = new Action("PrepareForConnection");
    param = new OpenHome::Net::ParameterString("RemoteProtocolInfo");
    iActionPrepareForConnection->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("PeerConnectionManager");
    iActionPrepareForConnection->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("PeerConnectionID");
    iActionPrepareForConnection->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Input";
    allowedValues[index++] = (TChar*)"Output";
    param = new OpenHome::Net::ParameterString("Direction", allowedValues, 2);
    iActionPrepareForConnection->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterInt("ConnectionID");
    iActionPrepareForConnection->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("AVTransportID");
    iActionPrepareForConnection->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("RcsID");
    iActionPrepareForConnection->AddOutputParameter(param);

    iActionConnectionComplete = new Action("ConnectionComplete");
    param = new OpenHome::Net::ParameterInt("ConnectionID");
    iActionConnectionComplete->AddInputParameter(param);

    iActionGetCurrentConnectionIDs = new Action("GetCurrentConnectionIDs");
    param = new OpenHome::Net::ParameterString("ConnectionIDs");
    iActionGetCurrentConnectionIDs->AddOutputParameter(param);

    iActionGetCurrentConnectionInfo = new Action("GetCurrentConnectionInfo");
    param = new OpenHome::Net::ParameterInt("ConnectionID");
    iActionGetCurrentConnectionInfo->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("RcsID");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("AVTransportID");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("ProtocolInfo");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("PeerConnectionManager");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("PeerConnectionID");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Input";
    allowedValues[index++] = (TChar*)"Output";
    param = new OpenHome::Net::ParameterString("Direction", allowedValues, 2);
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[5];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"ContentFormatMismatch";
    allowedValues[index++] = (TChar*)"InsufficientBandwidth";
    allowedValues[index++] = (TChar*)"UnreliableChannel";
    allowedValues[index++] = (TChar*)"Unknown";
    param = new OpenHome::Net::ParameterString("Status", allowedValues, 5);
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    delete[] allowedValues;

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager1Cpp::SourceProtocolInfoPropertyChanged);
    iSourceProtocolInfo = new PropertyString("SourceProtocolInfo", functor);
    AddProperty(iSourceProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager1Cpp::SinkProtocolInfoPropertyChanged);
    iSinkProtocolInfo = new PropertyString("SinkProtocolInfo", functor);
    AddProperty(iSinkProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager1Cpp::CurrentConnectionIDsPropertyChanged);
    iCurrentConnectionIDs = new PropertyString("CurrentConnectionIDs", functor);
    AddProperty(iCurrentConnectionIDs);
}

CpProxyUpnpOrgConnectionManager1Cpp::~CpProxyUpnpOrgConnectionManager1Cpp()
{
    DestroyService();
    delete iActionGetProtocolInfo;
    delete iActionPrepareForConnection;
    delete iActionConnectionComplete;
    delete iActionGetCurrentConnectionIDs;
    delete iActionGetCurrentConnectionInfo;
}

void CpProxyUpnpOrgConnectionManager1Cpp::SyncGetProtocolInfo(std::string& aSource, std::string& aSink)
{
    SyncGetProtocolInfoUpnpOrgConnectionManager1Cpp sync(*this, aSource, aSink);
    BeginGetProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1Cpp::BeginGetProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager1Cpp::EndGetProtocolInfo(IAsync& aAsync, std::string& aSource, std::string& aSink)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetProtocolInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSource.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSink.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgConnectionManager1Cpp::SyncPrepareForConnection(const std::string& aRemoteProtocolInfo, const std::string& aPeerConnectionManager, int32_t aPeerConnectionID, const std::string& aDirection, int32_t& aConnectionID, int32_t& aAVTransportID, int32_t& aRcsID)
{
    SyncPrepareForConnectionUpnpOrgConnectionManager1Cpp sync(*this, aConnectionID, aAVTransportID, aRcsID);
    BeginPrepareForConnection(aRemoteProtocolInfo, aPeerConnectionManager, aPeerConnectionID, aDirection, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1Cpp::BeginPrepareForConnection(const std::string& aRemoteProtocolInfo, const std::string& aPeerConnectionManager, int32_t aPeerConnectionID, const std::string& aDirection, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPrepareForConnection, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPrepareForConnection->InputParameters();
    {
        Brn buf((const TByte*)aRemoteProtocolInfo.c_str(), (TUint)aRemoteProtocolInfo.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aPeerConnectionManager.c_str(), (TUint)aPeerConnectionManager.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aPeerConnectionID));
    {
        Brn buf((const TByte*)aDirection.c_str(), (TUint)aDirection.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPrepareForConnection->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager1Cpp::EndPrepareForConnection(IAsync& aAsync, int32_t& aConnectionID, int32_t& aAVTransportID, int32_t& aRcsID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PrepareForConnection"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aConnectionID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aAVTransportID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aRcsID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgConnectionManager1Cpp::SyncConnectionComplete(int32_t aConnectionID)
{
    SyncConnectionCompleteUpnpOrgConnectionManager1Cpp sync(*this);
    BeginConnectionComplete(aConnectionID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1Cpp::BeginConnectionComplete(int32_t aConnectionID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionConnectionComplete, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionConnectionComplete->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aConnectionID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager1Cpp::EndConnectionComplete(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ConnectionComplete"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgConnectionManager1Cpp::SyncGetCurrentConnectionIDs(std::string& aConnectionIDs)
{
    SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1Cpp sync(*this, aConnectionIDs);
    BeginGetCurrentConnectionIDs(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1Cpp::BeginGetCurrentConnectionIDs(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetCurrentConnectionIDs, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCurrentConnectionIDs->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager1Cpp::EndGetCurrentConnectionIDs(IAsync& aAsync, std::string& aConnectionIDs)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCurrentConnectionIDs"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aConnectionIDs.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgConnectionManager1Cpp::SyncGetCurrentConnectionInfo(int32_t aConnectionID, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus)
{
    SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1Cpp sync(*this, aRcsID, aAVTransportID, aProtocolInfo, aPeerConnectionManager, aPeerConnectionID, aDirection, aStatus);
    BeginGetCurrentConnectionInfo(aConnectionID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1Cpp::BeginGetCurrentConnectionInfo(int32_t aConnectionID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetCurrentConnectionInfo, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetCurrentConnectionInfo->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aConnectionID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCurrentConnectionInfo->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager1Cpp::EndGetCurrentConnectionInfo(IAsync& aAsync, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCurrentConnectionInfo"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aRcsID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aAVTransportID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aProtocolInfo.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPeerConnectionManager.assign((const char*)val.Ptr(), val.Bytes());
    }
    aPeerConnectionID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aDirection.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aStatus.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgConnectionManager1Cpp::SetPropertySourceProtocolInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSourceProtocolInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgConnectionManager1Cpp::SetPropertySinkProtocolInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSinkProtocolInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgConnectionManager1Cpp::SetPropertyCurrentConnectionIDsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iCurrentConnectionIDsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgConnectionManager1Cpp::PropertySourceProtocolInfo(std::string& aSourceProtocolInfo) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iSourceProtocolInfo->Value();
    aSourceProtocolInfo.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgConnectionManager1Cpp::PropertySinkProtocolInfo(std::string& aSinkProtocolInfo) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iSinkProtocolInfo->Value();
    aSinkProtocolInfo.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgConnectionManager1Cpp::PropertyCurrentConnectionIDs(std::string& aCurrentConnectionIDs) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iCurrentConnectionIDs->Value();
    aCurrentConnectionIDs.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgConnectionManager1Cpp::SourceProtocolInfoPropertyChanged()
{
    ReportEvent(iSourceProtocolInfoChanged);
}

void CpProxyUpnpOrgConnectionManager1Cpp::SinkProtocolInfoPropertyChanged()
{
    ReportEvent(iSinkProtocolInfoChanged);
}

void CpProxyUpnpOrgConnectionManager1Cpp::CurrentConnectionIDsPropertyChanged()
{
    ReportEvent(iCurrentConnectionIDsChanged);
}

