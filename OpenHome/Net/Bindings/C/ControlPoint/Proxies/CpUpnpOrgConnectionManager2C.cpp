#include "CpUpnpOrgConnectionManager2.h"
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

class CpProxyUpnpOrgConnectionManager2C : public CpProxyC
{
public:
    CpProxyUpnpOrgConnectionManager2C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgConnectionManager2C();
    //CpProxyUpnpOrgConnectionManager2* Proxy() { return static_cast<CpProxyUpnpOrgConnectionManager2*>(iProxy); }

    void SyncGetProtocolInfo(Brh& aSource, Brh& aSink);
    void BeginGetProtocolInfo(FunctorAsync& aFunctor);
    void EndGetProtocolInfo(IAsync& aAsync, Brh& aSource, Brh& aSink);

    void SyncPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID);
    void BeginPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, FunctorAsync& aFunctor);
    void EndPrepareForConnection(IAsync& aAsync, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID);

    void SyncConnectionComplete(TInt aConnectionID);
    void BeginConnectionComplete(TInt aConnectionID, FunctorAsync& aFunctor);
    void EndConnectionComplete(IAsync& aAsync);

    void SyncGetCurrentConnectionIDs(Brh& aConnectionIDs);
    void BeginGetCurrentConnectionIDs(FunctorAsync& aFunctor);
    void EndGetCurrentConnectionIDs(IAsync& aAsync, Brh& aConnectionIDs);

    void SyncGetCurrentConnectionInfo(TInt aConnectionID, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus);
    void BeginGetCurrentConnectionInfo(TInt aConnectionID, FunctorAsync& aFunctor);
    void EndGetCurrentConnectionInfo(IAsync& aAsync, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus);

    void SetPropertySourceProtocolInfoChanged(Functor& aFunctor);
    void SetPropertySinkProtocolInfoChanged(Functor& aFunctor);
    void SetPropertyCurrentConnectionIDsChanged(Functor& aFunctor);

    void PropertySourceProtocolInfo(Brhz& aSourceProtocolInfo) const;
    void PropertySinkProtocolInfo(Brhz& aSinkProtocolInfo) const;
    void PropertyCurrentConnectionIDs(Brhz& aCurrentConnectionIDs) const;
private:
    void SourceProtocolInfoPropertyChanged();
    void SinkProtocolInfoPropertyChanged();
    void CurrentConnectionIDsPropertyChanged();
private:
    Mutex iLock;
    Action* iActionGetProtocolInfo;
    Action* iActionPrepareForConnection;
    Action* iActionConnectionComplete;
    Action* iActionGetCurrentConnectionIDs;
    Action* iActionGetCurrentConnectionInfo;
    PropertyString* iSourceProtocolInfo;
    PropertyString* iSinkProtocolInfo;
    PropertyString* iCurrentConnectionIDs;
    Functor iSourceProtocolInfoChanged;
    Functor iSinkProtocolInfoChanged;
    Functor iCurrentConnectionIDsChanged;
};


class SyncGetProtocolInfoUpnpOrgConnectionManager2C : public SyncProxyAction
{
public:
    SyncGetProtocolInfoUpnpOrgConnectionManager2C(CpProxyUpnpOrgConnectionManager2C& aProxy, Brh& aSource, Brh& aSink);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetProtocolInfoUpnpOrgConnectionManager2C() {};
private:
    CpProxyUpnpOrgConnectionManager2C& iService;
    Brh& iSource;
    Brh& iSink;
};

SyncGetProtocolInfoUpnpOrgConnectionManager2C::SyncGetProtocolInfoUpnpOrgConnectionManager2C(CpProxyUpnpOrgConnectionManager2C& aProxy, Brh& aSource, Brh& aSink)
    : iService(aProxy)
    , iSource(aSource)
    , iSink(aSink)
{
}

void SyncGetProtocolInfoUpnpOrgConnectionManager2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetProtocolInfo(aAsync, iSource, iSink);
}


class SyncPrepareForConnectionUpnpOrgConnectionManager2C : public SyncProxyAction
{
public:
    SyncPrepareForConnectionUpnpOrgConnectionManager2C(CpProxyUpnpOrgConnectionManager2C& aProxy, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPrepareForConnectionUpnpOrgConnectionManager2C() {};
private:
    CpProxyUpnpOrgConnectionManager2C& iService;
    TInt& iConnectionID;
    TInt& iAVTransportID;
    TInt& iRcsID;
};

SyncPrepareForConnectionUpnpOrgConnectionManager2C::SyncPrepareForConnectionUpnpOrgConnectionManager2C(CpProxyUpnpOrgConnectionManager2C& aProxy, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID)
    : iService(aProxy)
    , iConnectionID(aConnectionID)
    , iAVTransportID(aAVTransportID)
    , iRcsID(aRcsID)
{
}

void SyncPrepareForConnectionUpnpOrgConnectionManager2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrepareForConnection(aAsync, iConnectionID, iAVTransportID, iRcsID);
}


class SyncConnectionCompleteUpnpOrgConnectionManager2C : public SyncProxyAction
{
public:
    SyncConnectionCompleteUpnpOrgConnectionManager2C(CpProxyUpnpOrgConnectionManager2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncConnectionCompleteUpnpOrgConnectionManager2C() {};
private:
    CpProxyUpnpOrgConnectionManager2C& iService;
};

SyncConnectionCompleteUpnpOrgConnectionManager2C::SyncConnectionCompleteUpnpOrgConnectionManager2C(CpProxyUpnpOrgConnectionManager2C& aProxy)
    : iService(aProxy)
{
}

void SyncConnectionCompleteUpnpOrgConnectionManager2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndConnectionComplete(aAsync);
}


class SyncGetCurrentConnectionIDsUpnpOrgConnectionManager2C : public SyncProxyAction
{
public:
    SyncGetCurrentConnectionIDsUpnpOrgConnectionManager2C(CpProxyUpnpOrgConnectionManager2C& aProxy, Brh& aConnectionIDs);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentConnectionIDsUpnpOrgConnectionManager2C() {};
private:
    CpProxyUpnpOrgConnectionManager2C& iService;
    Brh& iConnectionIDs;
};

SyncGetCurrentConnectionIDsUpnpOrgConnectionManager2C::SyncGetCurrentConnectionIDsUpnpOrgConnectionManager2C(CpProxyUpnpOrgConnectionManager2C& aProxy, Brh& aConnectionIDs)
    : iService(aProxy)
    , iConnectionIDs(aConnectionIDs)
{
}

void SyncGetCurrentConnectionIDsUpnpOrgConnectionManager2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentConnectionIDs(aAsync, iConnectionIDs);
}


class SyncGetCurrentConnectionInfoUpnpOrgConnectionManager2C : public SyncProxyAction
{
public:
    SyncGetCurrentConnectionInfoUpnpOrgConnectionManager2C(CpProxyUpnpOrgConnectionManager2C& aProxy, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentConnectionInfoUpnpOrgConnectionManager2C() {};
private:
    CpProxyUpnpOrgConnectionManager2C& iService;
    TInt& iRcsID;
    TInt& iAVTransportID;
    Brh& iProtocolInfo;
    Brh& iPeerConnectionManager;
    TInt& iPeerConnectionID;
    Brh& iDirection;
    Brh& iStatus;
};

SyncGetCurrentConnectionInfoUpnpOrgConnectionManager2C::SyncGetCurrentConnectionInfoUpnpOrgConnectionManager2C(CpProxyUpnpOrgConnectionManager2C& aProxy, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus)
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

void SyncGetCurrentConnectionInfoUpnpOrgConnectionManager2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentConnectionInfo(aAsync, iRcsID, iAVTransportID, iProtocolInfo, iPeerConnectionManager, iPeerConnectionID, iDirection, iStatus);
}

CpProxyUpnpOrgConnectionManager2C::CpProxyUpnpOrgConnectionManager2C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "ConnectionManager", 2, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager2C::SourceProtocolInfoPropertyChanged);
    iSourceProtocolInfo = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "SourceProtocolInfo", functor);
    AddProperty(iSourceProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager2C::SinkProtocolInfoPropertyChanged);
    iSinkProtocolInfo = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "SinkProtocolInfo", functor);
    AddProperty(iSinkProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager2C::CurrentConnectionIDsPropertyChanged);
    iCurrentConnectionIDs = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "CurrentConnectionIDs", functor);
    AddProperty(iCurrentConnectionIDs);
}

CpProxyUpnpOrgConnectionManager2C::~CpProxyUpnpOrgConnectionManager2C()
{
    DestroyService();
    delete iActionGetProtocolInfo;
    delete iActionPrepareForConnection;
    delete iActionConnectionComplete;
    delete iActionGetCurrentConnectionIDs;
    delete iActionGetCurrentConnectionInfo;
}

void CpProxyUpnpOrgConnectionManager2C::SyncGetProtocolInfo(Brh& aSource, Brh& aSink)
{
    SyncGetProtocolInfoUpnpOrgConnectionManager2C sync(*this, aSource, aSink);
    BeginGetProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager2C::BeginGetProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager2C::EndGetProtocolInfo(IAsync& aAsync, Brh& aSource, Brh& aSink)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSource);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSink);
}

void CpProxyUpnpOrgConnectionManager2C::SyncPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID)
{
    SyncPrepareForConnectionUpnpOrgConnectionManager2C sync(*this, aConnectionID, aAVTransportID, aRcsID);
    BeginPrepareForConnection(aRemoteProtocolInfo, aPeerConnectionManager, aPeerConnectionID, aDirection, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager2C::BeginPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPrepareForConnection, aFunctor);
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
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager2C::EndPrepareForConnection(IAsync& aAsync, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID)
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

void CpProxyUpnpOrgConnectionManager2C::SyncConnectionComplete(TInt aConnectionID)
{
    SyncConnectionCompleteUpnpOrgConnectionManager2C sync(*this);
    BeginConnectionComplete(aConnectionID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager2C::BeginConnectionComplete(TInt aConnectionID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionConnectionComplete, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionConnectionComplete->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aConnectionID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager2C::EndConnectionComplete(IAsync& aAsync)
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

void CpProxyUpnpOrgConnectionManager2C::SyncGetCurrentConnectionIDs(Brh& aConnectionIDs)
{
    SyncGetCurrentConnectionIDsUpnpOrgConnectionManager2C sync(*this, aConnectionIDs);
    BeginGetCurrentConnectionIDs(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager2C::BeginGetCurrentConnectionIDs(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetCurrentConnectionIDs, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCurrentConnectionIDs->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager2C::EndGetCurrentConnectionIDs(IAsync& aAsync, Brh& aConnectionIDs)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aConnectionIDs);
}

void CpProxyUpnpOrgConnectionManager2C::SyncGetCurrentConnectionInfo(TInt aConnectionID, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus)
{
    SyncGetCurrentConnectionInfoUpnpOrgConnectionManager2C sync(*this, aRcsID, aAVTransportID, aProtocolInfo, aPeerConnectionManager, aPeerConnectionID, aDirection, aStatus);
    BeginGetCurrentConnectionInfo(aConnectionID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager2C::BeginGetCurrentConnectionInfo(TInt aConnectionID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetCurrentConnectionInfo, aFunctor);
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
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager2C::EndGetCurrentConnectionInfo(IAsync& aAsync, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aProtocolInfo);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPeerConnectionManager);
    aPeerConnectionID = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aDirection);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aStatus);
}

void CpProxyUpnpOrgConnectionManager2C::SetPropertySourceProtocolInfoChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSourceProtocolInfoChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgConnectionManager2C::SetPropertySinkProtocolInfoChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSinkProtocolInfoChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgConnectionManager2C::SetPropertyCurrentConnectionIDsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iCurrentConnectionIDsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgConnectionManager2C::PropertySourceProtocolInfo(Brhz& aSourceProtocolInfo) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aSourceProtocolInfo.Set(iSourceProtocolInfo->Value());
}

void CpProxyUpnpOrgConnectionManager2C::PropertySinkProtocolInfo(Brhz& aSinkProtocolInfo) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aSinkProtocolInfo.Set(iSinkProtocolInfo->Value());
}

void CpProxyUpnpOrgConnectionManager2C::PropertyCurrentConnectionIDs(Brhz& aCurrentConnectionIDs) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aCurrentConnectionIDs.Set(iCurrentConnectionIDs->Value());
}

void CpProxyUpnpOrgConnectionManager2C::SourceProtocolInfoPropertyChanged()
{
    ReportEvent(iSourceProtocolInfoChanged);
}

void CpProxyUpnpOrgConnectionManager2C::SinkProtocolInfoPropertyChanged()
{
    ReportEvent(iSinkProtocolInfoChanged);
}

void CpProxyUpnpOrgConnectionManager2C::CurrentConnectionIDsPropertyChanged()
{
    ReportEvent(iCurrentConnectionIDsChanged);
}


THandle STDCALL CpProxyUpnpOrgConnectionManager2Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgConnectionManager2C(aDevice);
}

void STDCALL CpProxyUpnpOrgConnectionManager2Destroy(THandle aHandle)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager2SyncGetProtocolInfo(THandle aHandle, char** aSource, char** aSink)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSource;
    Brh buf_aSink;
    int32_t err = 0;
    try {
        proxyC->SyncGetProtocolInfo(buf_aSource, buf_aSink);
        *aSource = buf_aSource.Extract();
        *aSink = buf_aSink.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aSource = NULL;
        *aSink = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgConnectionManager2BeginGetProtocolInfo(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetProtocolInfo(functor);
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager2EndGetProtocolInfo(THandle aHandle, OhNetHandleAsync aAsync, char** aSource, char** aSink)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aSource;
    *aSource = NULL;
    Brh buf_aSink;
    *aSink = NULL;
    try {
        proxyC->EndGetProtocolInfo(*async, buf_aSource, buf_aSink);
        *aSource = buf_aSource.Extract();
        *aSink = buf_aSink.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager2SyncPrepareForConnection(THandle aHandle, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRemoteProtocolInfo(aRemoteProtocolInfo);
    Brh buf_aPeerConnectionManager(aPeerConnectionManager);
    Brh buf_aDirection(aDirection);
    int32_t err = 0;
    try {
        proxyC->SyncPrepareForConnection(buf_aRemoteProtocolInfo, buf_aPeerConnectionManager, aPeerConnectionID, buf_aDirection, *aConnectionID, *aAVTransportID, *aRcsID);
    }
    catch (ProxyError& ) {
        err = -1;
        *aConnectionID = 0;
        *aAVTransportID = 0;
        *aRcsID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgConnectionManager2BeginPrepareForConnection(THandle aHandle, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRemoteProtocolInfo(aRemoteProtocolInfo);
    Brh buf_aPeerConnectionManager(aPeerConnectionManager);
    Brh buf_aDirection(aDirection);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPrepareForConnection(buf_aRemoteProtocolInfo, buf_aPeerConnectionManager, aPeerConnectionID, buf_aDirection, functor);
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager2EndPrepareForConnection(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPrepareForConnection(*async, *aConnectionID, *aAVTransportID, *aRcsID);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager2SyncConnectionComplete(THandle aHandle, int32_t aConnectionID)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncConnectionComplete(aConnectionID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgConnectionManager2BeginConnectionComplete(THandle aHandle, int32_t aConnectionID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginConnectionComplete(aConnectionID, functor);
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager2EndConnectionComplete(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndConnectionComplete(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager2SyncGetCurrentConnectionIDs(THandle aHandle, char** aConnectionIDs)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aConnectionIDs;
    int32_t err = 0;
    try {
        proxyC->SyncGetCurrentConnectionIDs(buf_aConnectionIDs);
        *aConnectionIDs = buf_aConnectionIDs.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aConnectionIDs = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgConnectionManager2BeginGetCurrentConnectionIDs(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetCurrentConnectionIDs(functor);
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager2EndGetCurrentConnectionIDs(THandle aHandle, OhNetHandleAsync aAsync, char** aConnectionIDs)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aConnectionIDs;
    *aConnectionIDs = NULL;
    try {
        proxyC->EndGetCurrentConnectionIDs(*async, buf_aConnectionIDs);
        *aConnectionIDs = buf_aConnectionIDs.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager2SyncGetCurrentConnectionInfo(THandle aHandle, int32_t aConnectionID, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aProtocolInfo;
    Brh buf_aPeerConnectionManager;
    Brh buf_aDirection;
    Brh buf_aStatus;
    int32_t err = 0;
    try {
        proxyC->SyncGetCurrentConnectionInfo(aConnectionID, *aRcsID, *aAVTransportID, buf_aProtocolInfo, buf_aPeerConnectionManager, *aPeerConnectionID, buf_aDirection, buf_aStatus);
        *aProtocolInfo = buf_aProtocolInfo.Extract();
        *aPeerConnectionManager = buf_aPeerConnectionManager.Extract();
        *aDirection = buf_aDirection.Extract();
        *aStatus = buf_aStatus.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aRcsID = 0;
        *aAVTransportID = 0;
        *aProtocolInfo = NULL;
        *aPeerConnectionManager = NULL;
        *aPeerConnectionID = 0;
        *aDirection = NULL;
        *aStatus = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgConnectionManager2BeginGetCurrentConnectionInfo(THandle aHandle, int32_t aConnectionID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetCurrentConnectionInfo(aConnectionID, functor);
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager2EndGetCurrentConnectionInfo(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aProtocolInfo;
    *aProtocolInfo = NULL;
    Brh buf_aPeerConnectionManager;
    *aPeerConnectionManager = NULL;
    Brh buf_aDirection;
    *aDirection = NULL;
    Brh buf_aStatus;
    *aStatus = NULL;
    try {
        proxyC->EndGetCurrentConnectionInfo(*async, *aRcsID, *aAVTransportID, buf_aProtocolInfo, buf_aPeerConnectionManager, *aPeerConnectionID, buf_aDirection, buf_aStatus);
        *aProtocolInfo = buf_aProtocolInfo.Extract();
        *aPeerConnectionManager = buf_aPeerConnectionManager.Extract();
        *aDirection = buf_aDirection.Extract();
        *aStatus = buf_aStatus.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgConnectionManager2SetPropertySourceProtocolInfoChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySourceProtocolInfoChanged(functor);
}

void STDCALL CpProxyUpnpOrgConnectionManager2SetPropertySinkProtocolInfoChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySinkProtocolInfoChanged(functor);
}

void STDCALL CpProxyUpnpOrgConnectionManager2SetPropertyCurrentConnectionIDsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyCurrentConnectionIDsChanged(functor);
}

void STDCALL CpProxyUpnpOrgConnectionManager2PropertySourceProtocolInfo(THandle aHandle, char** aSourceProtocolInfo)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aSourceProtocolInfo;
    proxyC->PropertySourceProtocolInfo(buf_aSourceProtocolInfo);
    *aSourceProtocolInfo = buf_aSourceProtocolInfo.Transfer();
}

void STDCALL CpProxyUpnpOrgConnectionManager2PropertySinkProtocolInfo(THandle aHandle, char** aSinkProtocolInfo)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aSinkProtocolInfo;
    proxyC->PropertySinkProtocolInfo(buf_aSinkProtocolInfo);
    *aSinkProtocolInfo = buf_aSinkProtocolInfo.Transfer();
}

void STDCALL CpProxyUpnpOrgConnectionManager2PropertyCurrentConnectionIDs(THandle aHandle, char** aCurrentConnectionIDs)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aCurrentConnectionIDs;
    proxyC->PropertyCurrentConnectionIDs(buf_aCurrentConnectionIDs);
    *aCurrentConnectionIDs = buf_aCurrentConnectionIDs.Transfer();
}

