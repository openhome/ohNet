#include <Core/CpUpnpOrgConnectionManager1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncGetProtocolInfoUpnpOrgConnectionManager1 : public SyncProxyAction
{
public:
    SyncGetProtocolInfoUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1& aService, Brh& aSource, Brh& aSink);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgConnectionManager1& iService;
    Brh& iSource;
    Brh& iSink;
};

SyncGetProtocolInfoUpnpOrgConnectionManager1::SyncGetProtocolInfoUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1& aService, Brh& aSource, Brh& aSink)
    : iService(aService)
    , iSource(aSource)
    , iSink(aSink)
{
}

void SyncGetProtocolInfoUpnpOrgConnectionManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetProtocolInfo(aAsync, iSource, iSink);
}


class SyncPrepareForConnectionUpnpOrgConnectionManager1 : public SyncProxyAction
{
public:
    SyncPrepareForConnectionUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1& aService, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgConnectionManager1& iService;
    TInt& iConnectionID;
    TInt& iAVTransportID;
    TInt& iRcsID;
};

SyncPrepareForConnectionUpnpOrgConnectionManager1::SyncPrepareForConnectionUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1& aService, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID)
    : iService(aService)
    , iConnectionID(aConnectionID)
    , iAVTransportID(aAVTransportID)
    , iRcsID(aRcsID)
{
}

void SyncPrepareForConnectionUpnpOrgConnectionManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrepareForConnection(aAsync, iConnectionID, iAVTransportID, iRcsID);
}


class SyncConnectionCompleteUpnpOrgConnectionManager1 : public SyncProxyAction
{
public:
    SyncConnectionCompleteUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgConnectionManager1& iService;
};

SyncConnectionCompleteUpnpOrgConnectionManager1::SyncConnectionCompleteUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1& aService)
    : iService(aService)
{
}

void SyncConnectionCompleteUpnpOrgConnectionManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndConnectionComplete(aAsync);
}


class SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1 : public SyncProxyAction
{
public:
    SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1& aService, Brh& aConnectionIDs);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgConnectionManager1& iService;
    Brh& iConnectionIDs;
};

SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1::SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1& aService, Brh& aConnectionIDs)
    : iService(aService)
    , iConnectionIDs(aConnectionIDs)
{
}

void SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentConnectionIDs(aAsync, iConnectionIDs);
}


class SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1 : public SyncProxyAction
{
public:
    SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1& aService, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgConnectionManager1& iService;
    TInt& iRcsID;
    TInt& iAVTransportID;
    Brh& iProtocolInfo;
    Brh& iPeerConnectionManager;
    TInt& iPeerConnectionID;
    Brh& iDirection;
    Brh& iStatus;
};

SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1::SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1& aService, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus)
    : iService(aService)
    , iRcsID(aRcsID)
    , iAVTransportID(aAVTransportID)
    , iProtocolInfo(aProtocolInfo)
    , iPeerConnectionManager(aPeerConnectionManager)
    , iPeerConnectionID(aPeerConnectionID)
    , iDirection(aDirection)
    , iStatus(aStatus)
{
}

void SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentConnectionInfo(aAsync, iRcsID, iAVTransportID, iProtocolInfo, iPeerConnectionManager, iPeerConnectionID, iDirection, iStatus);
}


CpProxyUpnpOrgConnectionManager1::CpProxyUpnpOrgConnectionManager1(CpDevice& aDevice)
{
    iService = new CpiService("schemas-upnp-org", "ConnectionManager", 1, aDevice.Device());
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionGetProtocolInfo = new Action("GetProtocolInfo");
    param = new Zapp::ParameterString("Source");
    iActionGetProtocolInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("Sink");
    iActionGetProtocolInfo->AddOutputParameter(param);

    iActionPrepareForConnection = new Action("PrepareForConnection");
    param = new Zapp::ParameterString("RemoteProtocolInfo");
    iActionPrepareForConnection->AddInputParameter(param);
    param = new Zapp::ParameterString("PeerConnectionManager");
    iActionPrepareForConnection->AddInputParameter(param);
    param = new Zapp::ParameterInt("PeerConnectionID");
    iActionPrepareForConnection->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Input";
    allowedValues[index++] = (TChar*)"Output";
    param = new Zapp::ParameterString("Direction", allowedValues, 2);
    iActionPrepareForConnection->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterInt("ConnectionID");
    iActionPrepareForConnection->AddOutputParameter(param);
    param = new Zapp::ParameterInt("AVTransportID");
    iActionPrepareForConnection->AddOutputParameter(param);
    param = new Zapp::ParameterInt("RcsID");
    iActionPrepareForConnection->AddOutputParameter(param);

    iActionConnectionComplete = new Action("ConnectionComplete");
    param = new Zapp::ParameterInt("ConnectionID");
    iActionConnectionComplete->AddInputParameter(param);

    iActionGetCurrentConnectionIDs = new Action("GetCurrentConnectionIDs");
    param = new Zapp::ParameterString("ConnectionIDs");
    iActionGetCurrentConnectionIDs->AddOutputParameter(param);

    iActionGetCurrentConnectionInfo = new Action("GetCurrentConnectionInfo");
    param = new Zapp::ParameterInt("ConnectionID");
    iActionGetCurrentConnectionInfo->AddInputParameter(param);
    param = new Zapp::ParameterInt("RcsID");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new Zapp::ParameterInt("AVTransportID");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("ProtocolInfo");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new Zapp::ParameterString("PeerConnectionManager");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    param = new Zapp::ParameterInt("PeerConnectionID");
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Input";
    allowedValues[index++] = (TChar*)"Output";
    param = new Zapp::ParameterString("Direction", allowedValues, 2);
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[5];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"ContentFormatMismatch";
    allowedValues[index++] = (TChar*)"InsufficientBandwidth";
    allowedValues[index++] = (TChar*)"UnreliableChannel";
    allowedValues[index++] = (TChar*)"Unknown";
    param = new Zapp::ParameterString("Status", allowedValues, 5);
    iActionGetCurrentConnectionInfo->AddOutputParameter(param);
    delete[] allowedValues;

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager1::SourceProtocolInfoPropertyChanged);
    iSourceProtocolInfo = new PropertyString("SourceProtocolInfo", functor);
    iService->AddProperty(iSourceProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager1::SinkProtocolInfoPropertyChanged);
    iSinkProtocolInfo = new PropertyString("SinkProtocolInfo", functor);
    iService->AddProperty(iSinkProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager1::CurrentConnectionIDsPropertyChanged);
    iCurrentConnectionIDs = new PropertyString("CurrentConnectionIDs", functor);
    iService->AddProperty(iCurrentConnectionIDs);
}

CpProxyUpnpOrgConnectionManager1::~CpProxyUpnpOrgConnectionManager1()
{
    delete iService;
    delete iActionGetProtocolInfo;
    delete iActionPrepareForConnection;
    delete iActionConnectionComplete;
    delete iActionGetCurrentConnectionIDs;
    delete iActionGetCurrentConnectionInfo;
}

void CpProxyUpnpOrgConnectionManager1::SyncGetProtocolInfo(Brh& aSource, Brh& aSink)
{
    SyncGetProtocolInfoUpnpOrgConnectionManager1 sync(*this, aSource, aSink);
    BeginGetProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1::BeginGetProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgConnectionManager1::EndGetProtocolInfo(IAsync& aAsync, Brh& aSource, Brh& aSink)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetProtocolInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSource);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSink);
}

void CpProxyUpnpOrgConnectionManager1::SyncPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID)
{
    SyncPrepareForConnectionUpnpOrgConnectionManager1 sync(*this, aConnectionID, aAVTransportID, aRcsID);
    BeginPrepareForConnection(aRemoteProtocolInfo, aPeerConnectionManager, aPeerConnectionID, aDirection, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1::BeginPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPrepareForConnection, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionPrepareForConnection->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRemoteProtocolInfo));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aPeerConnectionManager));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aPeerConnectionID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDirection));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPrepareForConnection->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgConnectionManager1::EndPrepareForConnection(IAsync& aAsync, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PrepareForConnection"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aConnectionID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aAVTransportID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aRcsID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgConnectionManager1::SyncConnectionComplete(TInt aConnectionID)
{
    SyncConnectionCompleteUpnpOrgConnectionManager1 sync(*this);
    BeginConnectionComplete(aConnectionID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1::BeginConnectionComplete(TInt aConnectionID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionConnectionComplete, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionConnectionComplete->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aConnectionID));
    invocation->Invoke();
}

void CpProxyUpnpOrgConnectionManager1::EndConnectionComplete(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ConnectionComplete"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgConnectionManager1::SyncGetCurrentConnectionIDs(Brh& aConnectionIDs)
{
    SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1 sync(*this, aConnectionIDs);
    BeginGetCurrentConnectionIDs(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1::BeginGetCurrentConnectionIDs(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetCurrentConnectionIDs, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCurrentConnectionIDs->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgConnectionManager1::EndGetCurrentConnectionIDs(IAsync& aAsync, Brh& aConnectionIDs)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCurrentConnectionIDs"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aConnectionIDs);
}

void CpProxyUpnpOrgConnectionManager1::SyncGetCurrentConnectionInfo(TInt aConnectionID, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus)
{
    SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1 sync(*this, aRcsID, aAVTransportID, aProtocolInfo, aPeerConnectionManager, aPeerConnectionID, aDirection, aStatus);
    BeginGetCurrentConnectionInfo(aConnectionID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1::BeginGetCurrentConnectionInfo(TInt aConnectionID, FunctorAsync& aFunctor)
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
    invocation->Invoke();
}

void CpProxyUpnpOrgConnectionManager1::EndGetCurrentConnectionInfo(IAsync& aAsync, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCurrentConnectionInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aRcsID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aAVTransportID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aProtocolInfo);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPeerConnectionManager);
    aPeerConnectionID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aDirection);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aStatus);
}

void CpProxyUpnpOrgConnectionManager1::SetPropertySourceProtocolInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSourceProtocolInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgConnectionManager1::SetPropertySinkProtocolInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSinkProtocolInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgConnectionManager1::SetPropertyCurrentConnectionIDsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iCurrentConnectionIDsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgConnectionManager1::PropertySourceProtocolInfo(Brhz& aSourceProtocolInfo) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSourceProtocolInfo.Set(iSourceProtocolInfo->Value());
}

void CpProxyUpnpOrgConnectionManager1::PropertySinkProtocolInfo(Brhz& aSinkProtocolInfo) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSinkProtocolInfo.Set(iSinkProtocolInfo->Value());
}

void CpProxyUpnpOrgConnectionManager1::PropertyCurrentConnectionIDs(Brhz& aCurrentConnectionIDs) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aCurrentConnectionIDs.Set(iCurrentConnectionIDs->Value());
}

void CpProxyUpnpOrgConnectionManager1::SourceProtocolInfoPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iSourceProtocolInfoChanged != NULL) {
        iSourceProtocolInfoChanged();
    }
}

void CpProxyUpnpOrgConnectionManager1::SinkProtocolInfoPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iSinkProtocolInfoChanged != NULL) {
        iSinkProtocolInfoChanged();
    }
}

void CpProxyUpnpOrgConnectionManager1::CurrentConnectionIDsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iCurrentConnectionIDsChanged != NULL) {
        iCurrentConnectionIDsChanged();
    }
}

