#include "DvUpnpOrgConnectionManager2.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderUpnpOrgConnectionManager2C : public DvProvider
{
public:
    DvProviderUpnpOrgConnectionManager2C(DvDeviceC aDevice);
    TBool SetPropertySourceProtocolInfo(const Brx& aValue);
    void GetPropertySourceProtocolInfo(Brhz& aValue);
    TBool SetPropertySinkProtocolInfo(const Brx& aValue);
    void GetPropertySinkProtocolInfo(Brhz& aValue);
    TBool SetPropertyCurrentConnectionIDs(const Brx& aValue);
    void GetPropertyCurrentConnectionIDs(Brhz& aValue);
    void EnablePropertySourceProtocolInfo();
    void EnablePropertySinkProtocolInfo();
    void EnablePropertyCurrentConnectionIDs();
    void EnableActionGetProtocolInfo(CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr);
    void EnableActionPrepareForConnection(CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr);
    void EnableActionConnectionComplete(CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr);
    void EnableActionGetCurrentConnectionIDs(CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr);
    void EnableActionGetCurrentConnectionInfo(CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr);
private:
    void DoGetProtocolInfo(IDviInvocation& aInvocation);
    void DoPrepareForConnection(IDviInvocation& aInvocation);
    void DoConnectionComplete(IDviInvocation& aInvocation);
    void DoGetCurrentConnectionIDs(IDviInvocation& aInvocation);
    void DoGetCurrentConnectionInfo(IDviInvocation& aInvocation);
private:
    CallbackConnectionManager2GetProtocolInfo iCallbackGetProtocolInfo;
    void* iPtrGetProtocolInfo;
    CallbackConnectionManager2PrepareForConnection iCallbackPrepareForConnection;
    void* iPtrPrepareForConnection;
    CallbackConnectionManager2ConnectionComplete iCallbackConnectionComplete;
    void* iPtrConnectionComplete;
    CallbackConnectionManager2GetCurrentConnectionIDs iCallbackGetCurrentConnectionIDs;
    void* iPtrGetCurrentConnectionIDs;
    CallbackConnectionManager2GetCurrentConnectionInfo iCallbackGetCurrentConnectionInfo;
    void* iPtrGetCurrentConnectionInfo;
    PropertyString* iPropertySourceProtocolInfo;
    PropertyString* iPropertySinkProtocolInfo;
    PropertyString* iPropertyCurrentConnectionIDs;
};

DvProviderUpnpOrgConnectionManager2C::DvProviderUpnpOrgConnectionManager2C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "ConnectionManager", 2)
{
    iPropertySourceProtocolInfo = NULL;
    iPropertySinkProtocolInfo = NULL;
    iPropertyCurrentConnectionIDs = NULL;
}

TBool DvProviderUpnpOrgConnectionManager2C::SetPropertySourceProtocolInfo(const Brx& aValue)
{
    ASSERT(iPropertySourceProtocolInfo != NULL);
    return SetPropertyString(*iPropertySourceProtocolInfo, aValue);
}

void DvProviderUpnpOrgConnectionManager2C::GetPropertySourceProtocolInfo(Brhz& aValue)
{
    ASSERT(iPropertySourceProtocolInfo != NULL);
    aValue.Set(iPropertySourceProtocolInfo->Value());
}

TBool DvProviderUpnpOrgConnectionManager2C::SetPropertySinkProtocolInfo(const Brx& aValue)
{
    ASSERT(iPropertySinkProtocolInfo != NULL);
    return SetPropertyString(*iPropertySinkProtocolInfo, aValue);
}

void DvProviderUpnpOrgConnectionManager2C::GetPropertySinkProtocolInfo(Brhz& aValue)
{
    ASSERT(iPropertySinkProtocolInfo != NULL);
    aValue.Set(iPropertySinkProtocolInfo->Value());
}

TBool DvProviderUpnpOrgConnectionManager2C::SetPropertyCurrentConnectionIDs(const Brx& aValue)
{
    ASSERT(iPropertyCurrentConnectionIDs != NULL);
    return SetPropertyString(*iPropertyCurrentConnectionIDs, aValue);
}

void DvProviderUpnpOrgConnectionManager2C::GetPropertyCurrentConnectionIDs(Brhz& aValue)
{
    ASSERT(iPropertyCurrentConnectionIDs != NULL);
    aValue.Set(iPropertyCurrentConnectionIDs->Value());
}

void DvProviderUpnpOrgConnectionManager2C::EnablePropertySourceProtocolInfo()
{
    iPropertySourceProtocolInfo = new PropertyString(iDvStack.Env(), new ParameterString("SourceProtocolInfo"));
    iService->AddProperty(iPropertySourceProtocolInfo); // passes ownership
}

void DvProviderUpnpOrgConnectionManager2C::EnablePropertySinkProtocolInfo()
{
    iPropertySinkProtocolInfo = new PropertyString(iDvStack.Env(), new ParameterString("SinkProtocolInfo"));
    iService->AddProperty(iPropertySinkProtocolInfo); // passes ownership
}

void DvProviderUpnpOrgConnectionManager2C::EnablePropertyCurrentConnectionIDs()
{
    iPropertyCurrentConnectionIDs = new PropertyString(iDvStack.Env(), new ParameterString("CurrentConnectionIDs"));
    iService->AddProperty(iPropertyCurrentConnectionIDs); // passes ownership
}

void DvProviderUpnpOrgConnectionManager2C::EnableActionGetProtocolInfo(CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr)
{
    iCallbackGetProtocolInfo = aCallback;
    iPtrGetProtocolInfo = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Source", *iPropertySourceProtocolInfo));
    action->AddOutputParameter(new ParameterRelated("Sink", *iPropertySinkProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager2C::DoGetProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager2C::EnableActionPrepareForConnection(CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr)
{
    iCallbackPrepareForConnection = aCallback;
    iPtrPrepareForConnection = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PrepareForConnection");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterString("RemoteProtocolInfo"));
    action->AddInputParameter(new ParameterString("PeerConnectionManager"));
    action->AddInputParameter(new ParameterInt("PeerConnectionID"));
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Input";
    allowedValues[index++] = (TChar*)"Output";
    action->AddInputParameter(new ParameterString("Direction", allowedValues, 2));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterInt("ConnectionID"));
    action->AddOutputParameter(new ParameterInt("AVTransportID"));
    action->AddOutputParameter(new ParameterInt("RcsID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager2C::DoPrepareForConnection);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager2C::EnableActionConnectionComplete(CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr)
{
    iCallbackConnectionComplete = aCallback;
    iPtrConnectionComplete = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ConnectionComplete");
    action->AddInputParameter(new ParameterInt("ConnectionID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager2C::DoConnectionComplete);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager2C::EnableActionGetCurrentConnectionIDs(CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionIDs = aCallback;
    iPtrGetCurrentConnectionIDs = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentConnectionIDs");
    action->AddOutputParameter(new ParameterRelated("ConnectionIDs", *iPropertyCurrentConnectionIDs));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager2C::DoGetCurrentConnectionIDs);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager2C::EnableActionGetCurrentConnectionInfo(CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionInfo = aCallback;
    iPtrGetCurrentConnectionInfo = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentConnectionInfo");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterInt("ConnectionID"));
    action->AddOutputParameter(new ParameterInt("RcsID"));
    action->AddOutputParameter(new ParameterInt("AVTransportID"));
    action->AddOutputParameter(new ParameterString("ProtocolInfo"));
    action->AddOutputParameter(new ParameterString("PeerConnectionManager"));
    action->AddOutputParameter(new ParameterInt("PeerConnectionID"));
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Input";
    allowedValues[index++] = (TChar*)"Output";
    action->AddOutputParameter(new ParameterString("Direction", allowedValues, 2));
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[5];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"ContentFormatMismatch";
    allowedValues[index++] = (TChar*)"InsufficientBandwidth";
    allowedValues[index++] = (TChar*)"UnreliableChannel";
    allowedValues[index++] = (TChar*)"Unknown";
    action->AddOutputParameter(new ParameterString("Status", allowedValues, 5));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager2C::DoGetCurrentConnectionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager2C::DoGetProtocolInfo(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Source;
    char* Sink;
    ASSERT(iCallbackGetProtocolInfo != NULL);
    if (0 != iCallbackGetProtocolInfo(iPtrGetProtocolInfo, invocationC, invocationCPtr, &Source, &Sink)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respSource(aInvocation, "Source");
    DviInvocationResponseString respSink(aInvocation, "Sink");
    invocation.StartResponse();
    Brhz bufSource((const TChar*)Source);
    OhNetFreeExternal(Source);
    respSource.Write(bufSource);
    respSource.WriteFlush();
    Brhz bufSink((const TChar*)Sink);
    OhNetFreeExternal(Sink);
    respSink.Write(bufSink);
    respSink.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgConnectionManager2C::DoPrepareForConnection(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RemoteProtocolInfo;
    aInvocation.InvocationReadString("RemoteProtocolInfo", RemoteProtocolInfo);
    Brhz PeerConnectionManager;
    aInvocation.InvocationReadString("PeerConnectionManager", PeerConnectionManager);
    TInt PeerConnectionID = aInvocation.InvocationReadInt("PeerConnectionID");
    Brhz Direction;
    aInvocation.InvocationReadString("Direction", Direction);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    int32_t ConnectionID;
    int32_t AVTransportID;
    int32_t RcsID;
    ASSERT(iCallbackPrepareForConnection != NULL);
    if (0 != iCallbackPrepareForConnection(iPtrPrepareForConnection, invocationC, invocationCPtr, (const char*)RemoteProtocolInfo.Ptr(), (const char*)PeerConnectionManager.Ptr(), PeerConnectionID, (const char*)Direction.Ptr(), &ConnectionID, &AVTransportID, &RcsID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseInt respConnectionID(aInvocation, "ConnectionID");
    DviInvocationResponseInt respAVTransportID(aInvocation, "AVTransportID");
    DviInvocationResponseInt respRcsID(aInvocation, "RcsID");
    invocation.StartResponse();
    respConnectionID.Write(ConnectionID);
    respAVTransportID.Write(AVTransportID);
    respRcsID.Write(RcsID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgConnectionManager2C::DoConnectionComplete(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TInt ConnectionID = aInvocation.InvocationReadInt("ConnectionID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackConnectionComplete != NULL);
    if (0 != iCallbackConnectionComplete(iPtrConnectionComplete, invocationC, invocationCPtr, ConnectionID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgConnectionManager2C::DoGetCurrentConnectionIDs(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* ConnectionIDs;
    ASSERT(iCallbackGetCurrentConnectionIDs != NULL);
    if (0 != iCallbackGetCurrentConnectionIDs(iPtrGetCurrentConnectionIDs, invocationC, invocationCPtr, &ConnectionIDs)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respConnectionIDs(aInvocation, "ConnectionIDs");
    invocation.StartResponse();
    Brhz bufConnectionIDs((const TChar*)ConnectionIDs);
    OhNetFreeExternal(ConnectionIDs);
    respConnectionIDs.Write(bufConnectionIDs);
    respConnectionIDs.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgConnectionManager2C::DoGetCurrentConnectionInfo(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TInt ConnectionID = aInvocation.InvocationReadInt("ConnectionID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    int32_t RcsID;
    int32_t AVTransportID;
    char* ProtocolInfo;
    char* PeerConnectionManager;
    int32_t PeerConnectionID;
    char* Direction;
    char* Status;
    ASSERT(iCallbackGetCurrentConnectionInfo != NULL);
    if (0 != iCallbackGetCurrentConnectionInfo(iPtrGetCurrentConnectionInfo, invocationC, invocationCPtr, ConnectionID, &RcsID, &AVTransportID, &ProtocolInfo, &PeerConnectionManager, &PeerConnectionID, &Direction, &Status)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseInt respRcsID(aInvocation, "RcsID");
    DviInvocationResponseInt respAVTransportID(aInvocation, "AVTransportID");
    DviInvocationResponseString respProtocolInfo(aInvocation, "ProtocolInfo");
    DviInvocationResponseString respPeerConnectionManager(aInvocation, "PeerConnectionManager");
    DviInvocationResponseInt respPeerConnectionID(aInvocation, "PeerConnectionID");
    DviInvocationResponseString respDirection(aInvocation, "Direction");
    DviInvocationResponseString respStatus(aInvocation, "Status");
    invocation.StartResponse();
    respRcsID.Write(RcsID);
    respAVTransportID.Write(AVTransportID);
    Brhz bufProtocolInfo((const TChar*)ProtocolInfo);
    OhNetFreeExternal(ProtocolInfo);
    respProtocolInfo.Write(bufProtocolInfo);
    respProtocolInfo.WriteFlush();
    Brhz bufPeerConnectionManager((const TChar*)PeerConnectionManager);
    OhNetFreeExternal(PeerConnectionManager);
    respPeerConnectionManager.Write(bufPeerConnectionManager);
    respPeerConnectionManager.WriteFlush();
    respPeerConnectionID.Write(PeerConnectionID);
    Brhz bufDirection((const TChar*)Direction);
    OhNetFreeExternal(Direction);
    respDirection.Write(bufDirection);
    respDirection.WriteFlush();
    Brhz bufStatus((const TChar*)Status);
    OhNetFreeExternal(Status);
    respStatus.Write(bufStatus);
    respStatus.WriteFlush();
    invocation.EndResponse();
}



THandle STDCALL DvProviderUpnpOrgConnectionManager2Create(DvDeviceC aDevice)
{
    return new DvProviderUpnpOrgConnectionManager2C(aDevice);
}

void STDCALL DvProviderUpnpOrgConnectionManager2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider);
}

void STDCALL DvProviderUpnpOrgConnectionManager2EnableActionGetProtocolInfo(THandle aProvider, CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnableActionGetProtocolInfo(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgConnectionManager2EnableActionPrepareForConnection(THandle aProvider, CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnableActionPrepareForConnection(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgConnectionManager2EnableActionConnectionComplete(THandle aProvider, CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnableActionConnectionComplete(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgConnectionManager2EnableActionGetCurrentConnectionIDs(THandle aProvider, CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnableActionGetCurrentConnectionIDs(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgConnectionManager2EnableActionGetCurrentConnectionInfo(THandle aProvider, CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnableActionGetCurrentConnectionInfo(aCallback, aPtr);
}

int32_t STDCALL DvProviderUpnpOrgConnectionManager2SetPropertySourceProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->SetPropertySourceProtocolInfo(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgConnectionManager2GetPropertySourceProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->GetPropertySourceProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderUpnpOrgConnectionManager2SetPropertySinkProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->SetPropertySinkProtocolInfo(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgConnectionManager2GetPropertySinkProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->GetPropertySinkProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderUpnpOrgConnectionManager2SetPropertyCurrentConnectionIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->SetPropertyCurrentConnectionIDs(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgConnectionManager2GetPropertyCurrentConnectionIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->GetPropertyCurrentConnectionIDs(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderUpnpOrgConnectionManager2EnablePropertySourceProtocolInfo(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnablePropertySourceProtocolInfo();
}

void STDCALL DvProviderUpnpOrgConnectionManager2EnablePropertySinkProtocolInfo(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnablePropertySinkProtocolInfo();
}

void STDCALL DvProviderUpnpOrgConnectionManager2EnablePropertyCurrentConnectionIDs(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnablePropertyCurrentConnectionIDs();
}

