#include "DvUpnpOrgConnectionManager1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgConnectionManager1Cpp::SetPropertySourceProtocolInfo(const std::string& aValue)
{
    ASSERT(iPropertySourceProtocolInfo != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertySourceProtocolInfo, buf);
}

void DvProviderUpnpOrgConnectionManager1Cpp::GetPropertySourceProtocolInfo(std::string& aValue)
{
    ASSERT(iPropertySourceProtocolInfo != NULL);
    const Brx& val = iPropertySourceProtocolInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderUpnpOrgConnectionManager1Cpp::SetPropertySinkProtocolInfo(const std::string& aValue)
{
    ASSERT(iPropertySinkProtocolInfo != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertySinkProtocolInfo, buf);
}

void DvProviderUpnpOrgConnectionManager1Cpp::GetPropertySinkProtocolInfo(std::string& aValue)
{
    ASSERT(iPropertySinkProtocolInfo != NULL);
    const Brx& val = iPropertySinkProtocolInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderUpnpOrgConnectionManager1Cpp::SetPropertyCurrentConnectionIDs(const std::string& aValue)
{
    ASSERT(iPropertyCurrentConnectionIDs != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyCurrentConnectionIDs, buf);
}

void DvProviderUpnpOrgConnectionManager1Cpp::GetPropertyCurrentConnectionIDs(std::string& aValue)
{
    ASSERT(iPropertyCurrentConnectionIDs != NULL);
    const Brx& val = iPropertyCurrentConnectionIDs->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderUpnpOrgConnectionManager1Cpp::DvProviderUpnpOrgConnectionManager1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "ConnectionManager", 1)
{
    iPropertySourceProtocolInfo = NULL;
    iPropertySinkProtocolInfo = NULL;
    iPropertyCurrentConnectionIDs = NULL;
}

void DvProviderUpnpOrgConnectionManager1Cpp::EnablePropertySourceProtocolInfo()
{
    iPropertySourceProtocolInfo = new PropertyString(new ParameterString("SourceProtocolInfo"));
    iService->AddProperty(iPropertySourceProtocolInfo); // passes ownership
}

void DvProviderUpnpOrgConnectionManager1Cpp::EnablePropertySinkProtocolInfo()
{
    iPropertySinkProtocolInfo = new PropertyString(new ParameterString("SinkProtocolInfo"));
    iService->AddProperty(iPropertySinkProtocolInfo); // passes ownership
}

void DvProviderUpnpOrgConnectionManager1Cpp::EnablePropertyCurrentConnectionIDs()
{
    iPropertyCurrentConnectionIDs = new PropertyString(new ParameterString("CurrentConnectionIDs"));
    iService->AddProperty(iPropertyCurrentConnectionIDs); // passes ownership
}

void DvProviderUpnpOrgConnectionManager1Cpp::EnableActionGetProtocolInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Source", *iPropertySourceProtocolInfo));
    action->AddOutputParameter(new ParameterRelated("Sink", *iPropertySinkProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager1Cpp::DoGetProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager1Cpp::EnableActionPrepareForConnection()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager1Cpp::DoPrepareForConnection);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager1Cpp::EnableActionConnectionComplete()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ConnectionComplete");
    action->AddInputParameter(new ParameterInt("ConnectionID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager1Cpp::DoConnectionComplete);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager1Cpp::EnableActionGetCurrentConnectionIDs()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentConnectionIDs");
    action->AddOutputParameter(new ParameterRelated("ConnectionIDs", *iPropertyCurrentConnectionIDs));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager1Cpp::DoGetCurrentConnectionIDs);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager1Cpp::EnableActionGetCurrentConnectionInfo()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager1Cpp::DoGetCurrentConnectionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager1Cpp::DoGetProtocolInfo(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSource;
    std::string respSink;
    DvInvocationStd invocation(aInvocation);
    GetProtocolInfo(invocation, respSource, respSink);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterSource(aInvocation, "Source");
    Brn buf_Source((const TByte*)respSource.c_str(), (TUint)respSource.length());
    respWriterSource.Write(buf_Source);
    aInvocation.InvocationWriteStringEnd("Source");
    DviInvocationResponseString respWriterSink(aInvocation, "Sink");
    Brn buf_Sink((const TByte*)respSink.c_str(), (TUint)respSink.length());
    respWriterSink.Write(buf_Sink);
    aInvocation.InvocationWriteStringEnd("Sink");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgConnectionManager1Cpp::DoPrepareForConnection(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RemoteProtocolInfo;
    aInvocation.InvocationReadString("RemoteProtocolInfo", buf_RemoteProtocolInfo);
    std::string RemoteProtocolInfo((const char*)buf_RemoteProtocolInfo.Ptr(), buf_RemoteProtocolInfo.Bytes());
    Brhz buf_PeerConnectionManager;
    aInvocation.InvocationReadString("PeerConnectionManager", buf_PeerConnectionManager);
    std::string PeerConnectionManager((const char*)buf_PeerConnectionManager.Ptr(), buf_PeerConnectionManager.Bytes());
    int32_t PeerConnectionID = aInvocation.InvocationReadInt("PeerConnectionID");
    Brhz buf_Direction;
    aInvocation.InvocationReadString("Direction", buf_Direction);
    std::string Direction((const char*)buf_Direction.Ptr(), buf_Direction.Bytes());
    aInvocation.InvocationReadEnd();
    int32_t respConnectionID;
    int32_t respAVTransportID;
    int32_t respRcsID;
    DvInvocationStd invocation(aInvocation);
    PrepareForConnection(invocation, RemoteProtocolInfo, PeerConnectionManager, PeerConnectionID, Direction, respConnectionID, respAVTransportID, respRcsID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterConnectionID(aInvocation, "ConnectionID");
    respWriterConnectionID.Write(respConnectionID);
    DviInvocationResponseInt respWriterAVTransportID(aInvocation, "AVTransportID");
    respWriterAVTransportID.Write(respAVTransportID);
    DviInvocationResponseInt respWriterRcsID(aInvocation, "RcsID");
    respWriterRcsID.Write(respRcsID);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgConnectionManager1Cpp::DoConnectionComplete(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    int32_t ConnectionID = aInvocation.InvocationReadInt("ConnectionID");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    ConnectionComplete(invocation, ConnectionID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgConnectionManager1Cpp::DoGetCurrentConnectionIDs(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respConnectionIDs;
    DvInvocationStd invocation(aInvocation);
    GetCurrentConnectionIDs(invocation, respConnectionIDs);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterConnectionIDs(aInvocation, "ConnectionIDs");
    Brn buf_ConnectionIDs((const TByte*)respConnectionIDs.c_str(), (TUint)respConnectionIDs.length());
    respWriterConnectionIDs.Write(buf_ConnectionIDs);
    aInvocation.InvocationWriteStringEnd("ConnectionIDs");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgConnectionManager1Cpp::DoGetCurrentConnectionInfo(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    int32_t ConnectionID = aInvocation.InvocationReadInt("ConnectionID");
    aInvocation.InvocationReadEnd();
    int32_t respRcsID;
    int32_t respAVTransportID;
    std::string respProtocolInfo;
    std::string respPeerConnectionManager;
    int32_t respPeerConnectionID;
    std::string respDirection;
    std::string respStatus;
    DvInvocationStd invocation(aInvocation);
    GetCurrentConnectionInfo(invocation, ConnectionID, respRcsID, respAVTransportID, respProtocolInfo, respPeerConnectionManager, respPeerConnectionID, respDirection, respStatus);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterRcsID(aInvocation, "RcsID");
    respWriterRcsID.Write(respRcsID);
    DviInvocationResponseInt respWriterAVTransportID(aInvocation, "AVTransportID");
    respWriterAVTransportID.Write(respAVTransportID);
    DviInvocationResponseString respWriterProtocolInfo(aInvocation, "ProtocolInfo");
    Brn buf_ProtocolInfo((const TByte*)respProtocolInfo.c_str(), (TUint)respProtocolInfo.length());
    respWriterProtocolInfo.Write(buf_ProtocolInfo);
    aInvocation.InvocationWriteStringEnd("ProtocolInfo");
    DviInvocationResponseString respWriterPeerConnectionManager(aInvocation, "PeerConnectionManager");
    Brn buf_PeerConnectionManager((const TByte*)respPeerConnectionManager.c_str(), (TUint)respPeerConnectionManager.length());
    respWriterPeerConnectionManager.Write(buf_PeerConnectionManager);
    aInvocation.InvocationWriteStringEnd("PeerConnectionManager");
    DviInvocationResponseInt respWriterPeerConnectionID(aInvocation, "PeerConnectionID");
    respWriterPeerConnectionID.Write(respPeerConnectionID);
    DviInvocationResponseString respWriterDirection(aInvocation, "Direction");
    Brn buf_Direction((const TByte*)respDirection.c_str(), (TUint)respDirection.length());
    respWriterDirection.Write(buf_Direction);
    aInvocation.InvocationWriteStringEnd("Direction");
    DviInvocationResponseString respWriterStatus(aInvocation, "Status");
    Brn buf_Status((const TByte*)respStatus.c_str(), (TUint)respStatus.length());
    respWriterStatus.Write(buf_Status);
    aInvocation.InvocationWriteStringEnd("Status");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgConnectionManager1Cpp::GetProtocolInfo(IDvInvocationStd& /*aInvocation*/, std::string& /*aSource*/, std::string& /*aSink*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgConnectionManager1Cpp::PrepareForConnection(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRemoteProtocolInfo*/, const std::string& /*aPeerConnectionManager*/, int32_t /*aPeerConnectionID*/, const std::string& /*aDirection*/, int32_t& /*aConnectionID*/, int32_t& /*aAVTransportID*/, int32_t& /*aRcsID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgConnectionManager1Cpp::ConnectionComplete(IDvInvocationStd& /*aInvocation*/, int32_t /*aConnectionID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgConnectionManager1Cpp::GetCurrentConnectionIDs(IDvInvocationStd& /*aInvocation*/, std::string& /*aConnectionIDs*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgConnectionManager1Cpp::GetCurrentConnectionInfo(IDvInvocationStd& /*aInvocation*/, int32_t /*aConnectionID*/, int32_t& /*aRcsID*/, int32_t& /*aAVTransportID*/, std::string& /*aProtocolInfo*/, std::string& /*aPeerConnectionManager*/, int32_t& /*aPeerConnectionID*/, std::string& /*aDirection*/, std::string& /*aStatus*/)
{
    ASSERTS();
}

