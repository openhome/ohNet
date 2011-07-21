#include "DvUpnpOrgConnectionManager2.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

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
    void EnableActionGetProtocolInfo(CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr);
    void EnableActionPrepareForConnection(CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr);
    void EnableActionConnectionComplete(CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr);
    void EnableActionGetCurrentConnectionIDs(CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr);
    void EnableActionGetCurrentConnectionInfo(CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr);
private:
    void DoGetProtocolInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoPrepareForConnection(IDviInvocation& aInvocation, TUint aVersion);
    void DoConnectionComplete(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetCurrentConnectionIDs(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetCurrentConnectionInfo(IDviInvocation& aInvocation, TUint aVersion);
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
    
    iPropertySourceProtocolInfo = new PropertyString(new ParameterString("SourceProtocolInfo"));
    iService->AddProperty(iPropertySourceProtocolInfo); // passes ownership
    iPropertySinkProtocolInfo = new PropertyString(new ParameterString("SinkProtocolInfo"));
    iService->AddProperty(iPropertySinkProtocolInfo); // passes ownership
    iPropertyCurrentConnectionIDs = new PropertyString(new ParameterString("CurrentConnectionIDs"));
    iService->AddProperty(iPropertyCurrentConnectionIDs); // passes ownership
}

TBool DvProviderUpnpOrgConnectionManager2C::SetPropertySourceProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertySourceProtocolInfo, aValue);
}

void DvProviderUpnpOrgConnectionManager2C::GetPropertySourceProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertySourceProtocolInfo->Value());
}

TBool DvProviderUpnpOrgConnectionManager2C::SetPropertySinkProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertySinkProtocolInfo, aValue);
}

void DvProviderUpnpOrgConnectionManager2C::GetPropertySinkProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertySinkProtocolInfo->Value());
}

TBool DvProviderUpnpOrgConnectionManager2C::SetPropertyCurrentConnectionIDs(const Brx& aValue)
{
    return SetPropertyString(*iPropertyCurrentConnectionIDs, aValue);
}

void DvProviderUpnpOrgConnectionManager2C::GetPropertyCurrentConnectionIDs(Brhz& aValue)
{
    aValue.Set(iPropertyCurrentConnectionIDs->Value());
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

void DvProviderUpnpOrgConnectionManager2C::DoGetProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Source;
    char* Sink;
    ASSERT(iCallbackGetProtocolInfo != NULL);
    if (0 != iCallbackGetProtocolInfo(iPtrGetProtocolInfo, aVersion, &Source, &Sink)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respSource(aInvocation, "Source");
    InvocationResponseString respSink(aInvocation, "Sink");
    resp.Start();
    Brhz bufSource((const TChar*)Source);
    OhNetFreeExternal(Source);
    respSource.Write(bufSource);
    respSource.WriteFlush();
    Brhz bufSink((const TChar*)Sink);
    OhNetFreeExternal(Sink);
    respSink.Write(bufSink);
    respSink.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgConnectionManager2C::DoPrepareForConnection(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RemoteProtocolInfo;
    aInvocation.InvocationReadString("RemoteProtocolInfo", RemoteProtocolInfo);
    Brhz PeerConnectionManager;
    aInvocation.InvocationReadString("PeerConnectionManager", PeerConnectionManager);
    TInt PeerConnectionID = aInvocation.InvocationReadInt("PeerConnectionID");
    Brhz Direction;
    aInvocation.InvocationReadString("Direction", Direction);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    int32_t ConnectionID;
    int32_t AVTransportID;
    int32_t RcsID;
    ASSERT(iCallbackPrepareForConnection != NULL);
    if (0 != iCallbackPrepareForConnection(iPtrPrepareForConnection, aVersion, (const char*)RemoteProtocolInfo.Ptr(), (const char*)PeerConnectionManager.Ptr(), PeerConnectionID, (const char*)Direction.Ptr(), &ConnectionID, &AVTransportID, &RcsID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseInt respConnectionID(aInvocation, "ConnectionID");
    InvocationResponseInt respAVTransportID(aInvocation, "AVTransportID");
    InvocationResponseInt respRcsID(aInvocation, "RcsID");
    resp.Start();
    respConnectionID.Write(ConnectionID);
    respAVTransportID.Write(AVTransportID);
    respRcsID.Write(RcsID);
    resp.End();
}

void DvProviderUpnpOrgConnectionManager2C::DoConnectionComplete(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt ConnectionID = aInvocation.InvocationReadInt("ConnectionID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackConnectionComplete != NULL);
    if (0 != iCallbackConnectionComplete(iPtrConnectionComplete, aVersion, ConnectionID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgConnectionManager2C::DoGetCurrentConnectionIDs(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* ConnectionIDs;
    ASSERT(iCallbackGetCurrentConnectionIDs != NULL);
    if (0 != iCallbackGetCurrentConnectionIDs(iPtrGetCurrentConnectionIDs, aVersion, &ConnectionIDs)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respConnectionIDs(aInvocation, "ConnectionIDs");
    resp.Start();
    Brhz bufConnectionIDs((const TChar*)ConnectionIDs);
    OhNetFreeExternal(ConnectionIDs);
    respConnectionIDs.Write(bufConnectionIDs);
    respConnectionIDs.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgConnectionManager2C::DoGetCurrentConnectionInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt ConnectionID = aInvocation.InvocationReadInt("ConnectionID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    int32_t RcsID;
    int32_t AVTransportID;
    char* ProtocolInfo;
    char* PeerConnectionManager;
    int32_t PeerConnectionID;
    char* Direction;
    char* Status;
    ASSERT(iCallbackGetCurrentConnectionInfo != NULL);
    if (0 != iCallbackGetCurrentConnectionInfo(iPtrGetCurrentConnectionInfo, aVersion, ConnectionID, &RcsID, &AVTransportID, &ProtocolInfo, &PeerConnectionManager, &PeerConnectionID, &Direction, &Status)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseInt respRcsID(aInvocation, "RcsID");
    InvocationResponseInt respAVTransportID(aInvocation, "AVTransportID");
    InvocationResponseString respProtocolInfo(aInvocation, "ProtocolInfo");
    InvocationResponseString respPeerConnectionManager(aInvocation, "PeerConnectionManager");
    InvocationResponseInt respPeerConnectionID(aInvocation, "PeerConnectionID");
    InvocationResponseString respDirection(aInvocation, "Direction");
    InvocationResponseString respStatus(aInvocation, "Status");
    resp.Start();
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
    resp.End();
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

