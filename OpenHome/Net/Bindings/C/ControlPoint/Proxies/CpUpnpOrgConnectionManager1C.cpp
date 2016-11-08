#include "CpUpnpOrgConnectionManager1.h"
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

class CpProxyUpnpOrgConnectionManager1C : public CpProxyC
{
public:
    CpProxyUpnpOrgConnectionManager1C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgConnectionManager1C();
    //CpProxyUpnpOrgConnectionManager1* Proxy() { return static_cast<CpProxyUpnpOrgConnectionManager1*>(iProxy); }

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


class SyncGetProtocolInfoUpnpOrgConnectionManager1C : public SyncProxyAction
{
public:
    SyncGetProtocolInfoUpnpOrgConnectionManager1C(CpProxyUpnpOrgConnectionManager1C& aProxy, Brh& aSource, Brh& aSink);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetProtocolInfoUpnpOrgConnectionManager1C() {};
private:
    CpProxyUpnpOrgConnectionManager1C& iService;
    Brh& iSource;
    Brh& iSink;
};

SyncGetProtocolInfoUpnpOrgConnectionManager1C::SyncGetProtocolInfoUpnpOrgConnectionManager1C(CpProxyUpnpOrgConnectionManager1C& aProxy, Brh& aSource, Brh& aSink)
    : iService(aProxy)
    , iSource(aSource)
    , iSink(aSink)
{
}

void SyncGetProtocolInfoUpnpOrgConnectionManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetProtocolInfo(aAsync, iSource, iSink);
}


class SyncPrepareForConnectionUpnpOrgConnectionManager1C : public SyncProxyAction
{
public:
    SyncPrepareForConnectionUpnpOrgConnectionManager1C(CpProxyUpnpOrgConnectionManager1C& aProxy, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPrepareForConnectionUpnpOrgConnectionManager1C() {};
private:
    CpProxyUpnpOrgConnectionManager1C& iService;
    TInt& iConnectionID;
    TInt& iAVTransportID;
    TInt& iRcsID;
};

SyncPrepareForConnectionUpnpOrgConnectionManager1C::SyncPrepareForConnectionUpnpOrgConnectionManager1C(CpProxyUpnpOrgConnectionManager1C& aProxy, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID)
    : iService(aProxy)
    , iConnectionID(aConnectionID)
    , iAVTransportID(aAVTransportID)
    , iRcsID(aRcsID)
{
}

void SyncPrepareForConnectionUpnpOrgConnectionManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPrepareForConnection(aAsync, iConnectionID, iAVTransportID, iRcsID);
}


class SyncConnectionCompleteUpnpOrgConnectionManager1C : public SyncProxyAction
{
public:
    SyncConnectionCompleteUpnpOrgConnectionManager1C(CpProxyUpnpOrgConnectionManager1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncConnectionCompleteUpnpOrgConnectionManager1C() {};
private:
    CpProxyUpnpOrgConnectionManager1C& iService;
};

SyncConnectionCompleteUpnpOrgConnectionManager1C::SyncConnectionCompleteUpnpOrgConnectionManager1C(CpProxyUpnpOrgConnectionManager1C& aProxy)
    : iService(aProxy)
{
}

void SyncConnectionCompleteUpnpOrgConnectionManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndConnectionComplete(aAsync);
}


class SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1C : public SyncProxyAction
{
public:
    SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1C(CpProxyUpnpOrgConnectionManager1C& aProxy, Brh& aConnectionIDs);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1C() {};
private:
    CpProxyUpnpOrgConnectionManager1C& iService;
    Brh& iConnectionIDs;
};

SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1C::SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1C(CpProxyUpnpOrgConnectionManager1C& aProxy, Brh& aConnectionIDs)
    : iService(aProxy)
    , iConnectionIDs(aConnectionIDs)
{
}

void SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentConnectionIDs(aAsync, iConnectionIDs);
}


class SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1C : public SyncProxyAction
{
public:
    SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1C(CpProxyUpnpOrgConnectionManager1C& aProxy, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1C() {};
private:
    CpProxyUpnpOrgConnectionManager1C& iService;
    TInt& iRcsID;
    TInt& iAVTransportID;
    Brh& iProtocolInfo;
    Brh& iPeerConnectionManager;
    TInt& iPeerConnectionID;
    Brh& iDirection;
    Brh& iStatus;
};

SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1C::SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1C(CpProxyUpnpOrgConnectionManager1C& aProxy, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus)
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

void SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCurrentConnectionInfo(aAsync, iRcsID, iAVTransportID, iProtocolInfo, iPeerConnectionManager, iPeerConnectionID, iDirection, iStatus);
}

CpProxyUpnpOrgConnectionManager1C::CpProxyUpnpOrgConnectionManager1C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "ConnectionManager", 1, *reinterpret_cast<CpiDevice*>(aDevice))
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager1C::SourceProtocolInfoPropertyChanged);
    iSourceProtocolInfo = new PropertyString("SourceProtocolInfo", functor);
    AddProperty(iSourceProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager1C::SinkProtocolInfoPropertyChanged);
    iSinkProtocolInfo = new PropertyString("SinkProtocolInfo", functor);
    AddProperty(iSinkProtocolInfo);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgConnectionManager1C::CurrentConnectionIDsPropertyChanged);
    iCurrentConnectionIDs = new PropertyString("CurrentConnectionIDs", functor);
    AddProperty(iCurrentConnectionIDs);
}

CpProxyUpnpOrgConnectionManager1C::~CpProxyUpnpOrgConnectionManager1C()
{
    DestroyService();
    delete iActionGetProtocolInfo;
    delete iActionPrepareForConnection;
    delete iActionConnectionComplete;
    delete iActionGetCurrentConnectionIDs;
    delete iActionGetCurrentConnectionInfo;
}

void CpProxyUpnpOrgConnectionManager1C::SyncGetProtocolInfo(Brh& aSource, Brh& aSink)
{
    SyncGetProtocolInfoUpnpOrgConnectionManager1C sync(*this, aSource, aSink);
    BeginGetProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1C::BeginGetProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager1C::EndGetProtocolInfo(IAsync& aAsync, Brh& aSource, Brh& aSink)
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

void CpProxyUpnpOrgConnectionManager1C::SyncPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID)
{
    SyncPrepareForConnectionUpnpOrgConnectionManager1C sync(*this, aConnectionID, aAVTransportID, aRcsID);
    BeginPrepareForConnection(aRemoteProtocolInfo, aPeerConnectionManager, aPeerConnectionID, aDirection, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1C::BeginPrepareForConnection(const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgConnectionManager1C::EndPrepareForConnection(IAsync& aAsync, TInt& aConnectionID, TInt& aAVTransportID, TInt& aRcsID)
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

void CpProxyUpnpOrgConnectionManager1C::SyncConnectionComplete(TInt aConnectionID)
{
    SyncConnectionCompleteUpnpOrgConnectionManager1C sync(*this);
    BeginConnectionComplete(aConnectionID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1C::BeginConnectionComplete(TInt aConnectionID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionConnectionComplete, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionConnectionComplete->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aConnectionID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager1C::EndConnectionComplete(IAsync& aAsync)
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

void CpProxyUpnpOrgConnectionManager1C::SyncGetCurrentConnectionIDs(Brh& aConnectionIDs)
{
    SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1C sync(*this, aConnectionIDs);
    BeginGetCurrentConnectionIDs(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1C::BeginGetCurrentConnectionIDs(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetCurrentConnectionIDs, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCurrentConnectionIDs->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgConnectionManager1C::EndGetCurrentConnectionIDs(IAsync& aAsync, Brh& aConnectionIDs)
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

void CpProxyUpnpOrgConnectionManager1C::SyncGetCurrentConnectionInfo(TInt aConnectionID, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus)
{
    SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1C sync(*this, aRcsID, aAVTransportID, aProtocolInfo, aPeerConnectionManager, aPeerConnectionID, aDirection, aStatus);
    BeginGetCurrentConnectionInfo(aConnectionID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgConnectionManager1C::BeginGetCurrentConnectionInfo(TInt aConnectionID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgConnectionManager1C::EndGetCurrentConnectionInfo(IAsync& aAsync, TInt& aRcsID, TInt& aAVTransportID, Brh& aProtocolInfo, Brh& aPeerConnectionManager, TInt& aPeerConnectionID, Brh& aDirection, Brh& aStatus)
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

void CpProxyUpnpOrgConnectionManager1C::SetPropertySourceProtocolInfoChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSourceProtocolInfoChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgConnectionManager1C::SetPropertySinkProtocolInfoChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSinkProtocolInfoChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgConnectionManager1C::SetPropertyCurrentConnectionIDsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iCurrentConnectionIDsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgConnectionManager1C::PropertySourceProtocolInfo(Brhz& aSourceProtocolInfo) const
{
    AutoMutex a(GetPropertyReadLock());
    CheckSubscribed();
    aSourceProtocolInfo.Set(iSourceProtocolInfo->Value());
}

void CpProxyUpnpOrgConnectionManager1C::PropertySinkProtocolInfo(Brhz& aSinkProtocolInfo) const
{
    AutoMutex a(GetPropertyReadLock());
    CheckSubscribed();
    aSinkProtocolInfo.Set(iSinkProtocolInfo->Value());
}

void CpProxyUpnpOrgConnectionManager1C::PropertyCurrentConnectionIDs(Brhz& aCurrentConnectionIDs) const
{
    AutoMutex a(GetPropertyReadLock());
    CheckSubscribed();
    aCurrentConnectionIDs.Set(iCurrentConnectionIDs->Value());
}

void CpProxyUpnpOrgConnectionManager1C::SourceProtocolInfoPropertyChanged()
{
    ReportEvent(iSourceProtocolInfoChanged);
}

void CpProxyUpnpOrgConnectionManager1C::SinkProtocolInfoPropertyChanged()
{
    ReportEvent(iSinkProtocolInfoChanged);
}

void CpProxyUpnpOrgConnectionManager1C::CurrentConnectionIDsPropertyChanged()
{
    ReportEvent(iCurrentConnectionIDsChanged);
}


THandle STDCALL CpProxyUpnpOrgConnectionManager1Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgConnectionManager1C(aDevice);
}

void STDCALL CpProxyUpnpOrgConnectionManager1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager1SyncGetProtocolInfo(THandle aHandle, char** aSource, char** aSink)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgConnectionManager1BeginGetProtocolInfo(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetProtocolInfo(functor);
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager1EndGetProtocolInfo(THandle aHandle, OhNetHandleAsync aAsync, char** aSource, char** aSink)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgConnectionManager1SyncPrepareForConnection(THandle aHandle, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgConnectionManager1BeginPrepareForConnection(THandle aHandle, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRemoteProtocolInfo(aRemoteProtocolInfo);
    Brh buf_aPeerConnectionManager(aPeerConnectionManager);
    Brh buf_aDirection(aDirection);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPrepareForConnection(buf_aRemoteProtocolInfo, buf_aPeerConnectionManager, aPeerConnectionID, buf_aDirection, functor);
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager1EndPrepareForConnection(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgConnectionManager1SyncConnectionComplete(THandle aHandle, int32_t aConnectionID)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgConnectionManager1BeginConnectionComplete(THandle aHandle, int32_t aConnectionID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginConnectionComplete(aConnectionID, functor);
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager1EndConnectionComplete(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgConnectionManager1SyncGetCurrentConnectionIDs(THandle aHandle, char** aConnectionIDs)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgConnectionManager1BeginGetCurrentConnectionIDs(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetCurrentConnectionIDs(functor);
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager1EndGetCurrentConnectionIDs(THandle aHandle, OhNetHandleAsync aAsync, char** aConnectionIDs)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgConnectionManager1SyncGetCurrentConnectionInfo(THandle aHandle, int32_t aConnectionID, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgConnectionManager1BeginGetCurrentConnectionInfo(THandle aHandle, int32_t aConnectionID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetCurrentConnectionInfo(aConnectionID, functor);
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager1EndGetCurrentConnectionInfo(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgConnectionManager1SetPropertySourceProtocolInfoChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySourceProtocolInfoChanged(functor);
}

void STDCALL CpProxyUpnpOrgConnectionManager1SetPropertySinkProtocolInfoChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySinkProtocolInfoChanged(functor);
}

void STDCALL CpProxyUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyCurrentConnectionIDsChanged(functor);
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager1PropertySourceProtocolInfo(THandle aHandle, char** aSourceProtocolInfo)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aSourceProtocolInfo;
    try {
        proxyC->PropertySourceProtocolInfo(buf_aSourceProtocolInfo);
    }
    catch (ProxyNotSubscribed&) {
        return -1;
    }
    *aSourceProtocolInfo = buf_aSourceProtocolInfo.Transfer();
    return 0;
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager1PropertySinkProtocolInfo(THandle aHandle, char** aSinkProtocolInfo)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aSinkProtocolInfo;
    try {
        proxyC->PropertySinkProtocolInfo(buf_aSinkProtocolInfo);
    }
    catch (ProxyNotSubscribed&) {
        return -1;
    }
    *aSinkProtocolInfo = buf_aSinkProtocolInfo.Transfer();
    return 0;
}

int32_t STDCALL CpProxyUpnpOrgConnectionManager1PropertyCurrentConnectionIDs(THandle aHandle, char** aCurrentConnectionIDs)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aCurrentConnectionIDs;
    try {
        proxyC->PropertyCurrentConnectionIDs(buf_aCurrentConnectionIDs);
    }
    catch (ProxyNotSubscribed&) {
        return -1;
    }
    *aCurrentConnectionIDs = buf_aCurrentConnectionIDs.Transfer();
    return 0;
}

