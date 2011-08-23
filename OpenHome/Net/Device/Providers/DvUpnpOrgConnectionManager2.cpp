#include "DvUpnpOrgConnectionManager2.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderUpnpOrgConnectionManager2::SetPropertySourceProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertySourceProtocolInfo, aValue);
}

void DvProviderUpnpOrgConnectionManager2::GetPropertySourceProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertySourceProtocolInfo->Value());
}

TBool DvProviderUpnpOrgConnectionManager2::SetPropertySinkProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertySinkProtocolInfo, aValue);
}

void DvProviderUpnpOrgConnectionManager2::GetPropertySinkProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertySinkProtocolInfo->Value());
}

TBool DvProviderUpnpOrgConnectionManager2::SetPropertyCurrentConnectionIDs(const Brx& aValue)
{
    return SetPropertyString(*iPropertyCurrentConnectionIDs, aValue);
}

void DvProviderUpnpOrgConnectionManager2::GetPropertyCurrentConnectionIDs(Brhz& aValue)
{
    aValue.Set(iPropertyCurrentConnectionIDs->Value());
}

DvProviderUpnpOrgConnectionManager2::DvProviderUpnpOrgConnectionManager2(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "ConnectionManager", 2)
{
    
    iPropertySourceProtocolInfo = new PropertyString(new ParameterString("SourceProtocolInfo"));
    iService->AddProperty(iPropertySourceProtocolInfo); // passes ownership
    iPropertySinkProtocolInfo = new PropertyString(new ParameterString("SinkProtocolInfo"));
    iService->AddProperty(iPropertySinkProtocolInfo); // passes ownership
    iPropertyCurrentConnectionIDs = new PropertyString(new ParameterString("CurrentConnectionIDs"));
    iService->AddProperty(iPropertyCurrentConnectionIDs); // passes ownership
}

void DvProviderUpnpOrgConnectionManager2::EnableActionGetProtocolInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Source", *iPropertySourceProtocolInfo));
    action->AddOutputParameter(new ParameterRelated("Sink", *iPropertySinkProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager2::DoGetProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager2::EnableActionPrepareForConnection()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager2::DoPrepareForConnection);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager2::EnableActionConnectionComplete()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ConnectionComplete");
    action->AddInputParameter(new ParameterInt("ConnectionID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager2::DoConnectionComplete);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager2::EnableActionGetCurrentConnectionIDs()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentConnectionIDs");
    action->AddOutputParameter(new ParameterRelated("ConnectionIDs", *iPropertyCurrentConnectionIDs));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager2::DoGetCurrentConnectionIDs);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager2::EnableActionGetCurrentConnectionInfo()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager2::DoGetCurrentConnectionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager2::DoGetProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respSource(aInvocation, "Source");
    DviInvocationResponseString respSink(aInvocation, "Sink");
    GetProtocolInfo(invocation, aVersion, respSource, respSink);
}

void DvProviderUpnpOrgConnectionManager2::DoPrepareForConnection(IDviInvocation& aInvocation, TUint aVersion)
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
    DviInvocation invocation(aInvocation);
    DviInvocationResponseInt respConnectionID(aInvocation, "ConnectionID");
    DviInvocationResponseInt respAVTransportID(aInvocation, "AVTransportID");
    DviInvocationResponseInt respRcsID(aInvocation, "RcsID");
    PrepareForConnection(invocation, aVersion, RemoteProtocolInfo, PeerConnectionManager, PeerConnectionID, Direction, respConnectionID, respAVTransportID, respRcsID);
}

void DvProviderUpnpOrgConnectionManager2::DoConnectionComplete(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt ConnectionID = aInvocation.InvocationReadInt("ConnectionID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ConnectionComplete(invocation, aVersion, ConnectionID);
}

void DvProviderUpnpOrgConnectionManager2::DoGetCurrentConnectionIDs(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respConnectionIDs(aInvocation, "ConnectionIDs");
    GetCurrentConnectionIDs(invocation, aVersion, respConnectionIDs);
}

void DvProviderUpnpOrgConnectionManager2::DoGetCurrentConnectionInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt ConnectionID = aInvocation.InvocationReadInt("ConnectionID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseInt respRcsID(aInvocation, "RcsID");
    DviInvocationResponseInt respAVTransportID(aInvocation, "AVTransportID");
    DviInvocationResponseString respProtocolInfo(aInvocation, "ProtocolInfo");
    DviInvocationResponseString respPeerConnectionManager(aInvocation, "PeerConnectionManager");
    DviInvocationResponseInt respPeerConnectionID(aInvocation, "PeerConnectionID");
    DviInvocationResponseString respDirection(aInvocation, "Direction");
    DviInvocationResponseString respStatus(aInvocation, "Status");
    GetCurrentConnectionInfo(invocation, aVersion, ConnectionID, respRcsID, respAVTransportID, respProtocolInfo, respPeerConnectionManager, respPeerConnectionID, respDirection, respStatus);
}

void DvProviderUpnpOrgConnectionManager2::GetProtocolInfo(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aSource*/, IDvInvocationResponseString& /*aSink*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgConnectionManager2::PrepareForConnection(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRemoteProtocolInfo*/, const Brx& /*aPeerConnectionManager*/, TInt /*aPeerConnectionID*/, const Brx& /*aDirection*/, IDvInvocationResponseInt& /*aConnectionID*/, IDvInvocationResponseInt& /*aAVTransportID*/, IDvInvocationResponseInt& /*aRcsID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgConnectionManager2::ConnectionComplete(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TInt /*aConnectionID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgConnectionManager2::GetCurrentConnectionIDs(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aConnectionIDs*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgConnectionManager2::GetCurrentConnectionInfo(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TInt /*aConnectionID*/, IDvInvocationResponseInt& /*aRcsID*/, IDvInvocationResponseInt& /*aAVTransportID*/, IDvInvocationResponseString& /*aProtocolInfo*/, IDvInvocationResponseString& /*aPeerConnectionManager*/, IDvInvocationResponseInt& /*aPeerConnectionID*/, IDvInvocationResponseString& /*aDirection*/, IDvInvocationResponseString& /*aStatus*/)
{
    ASSERTS();
}

