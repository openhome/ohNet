#include <Std/DvUpnpOrgConnectionManager1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgConnectionManager1Cpp::SetPropertySourceProtocolInfo(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertySourceProtocolInfo, buf);
}

void DvServiceUpnpOrgConnectionManager1Cpp::GetPropertySourceProtocolInfo(std::string& aValue)
{
    const Brx& val = iPropertySourceProtocolInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceUpnpOrgConnectionManager1Cpp::SetPropertySinkProtocolInfo(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertySinkProtocolInfo, buf);
}

void DvServiceUpnpOrgConnectionManager1Cpp::GetPropertySinkProtocolInfo(std::string& aValue)
{
    const Brx& val = iPropertySinkProtocolInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceUpnpOrgConnectionManager1Cpp::SetPropertyCurrentConnectionIDs(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyCurrentConnectionIDs, buf);
}

void DvServiceUpnpOrgConnectionManager1Cpp::GetPropertyCurrentConnectionIDs(std::string& aValue)
{
    const Brx& val = iPropertyCurrentConnectionIDs->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvServiceUpnpOrgConnectionManager1Cpp::DvServiceUpnpOrgConnectionManager1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "ConnectionManager", 1)
{
    Functor empty;
    iPropertySourceProtocolInfo = new PropertyString(new ParameterString("SourceProtocolInfo"), empty);
    iService->AddProperty(iPropertySourceProtocolInfo); // passes ownership
    iPropertySinkProtocolInfo = new PropertyString(new ParameterString("SinkProtocolInfo"), empty);
    iService->AddProperty(iPropertySinkProtocolInfo); // passes ownership
    iPropertyCurrentConnectionIDs = new PropertyString(new ParameterString("CurrentConnectionIDs"), empty);
    iService->AddProperty(iPropertyCurrentConnectionIDs); // passes ownership
}

void DvServiceUpnpOrgConnectionManager1Cpp::EnableActionGetProtocolInfo()
{
    Zapp::Action* action = new Zapp::Action("GetProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Source", *iPropertySourceProtocolInfo));
    action->AddOutputParameter(new ParameterRelated("Sink", *iPropertySinkProtocolInfo));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgConnectionManager1Cpp::DoGetProtocolInfo);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgConnectionManager1Cpp::EnableActionPrepareForConnection()
{
    Zapp::Action* action = new Zapp::Action("PrepareForConnection");
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgConnectionManager1Cpp::DoPrepareForConnection);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgConnectionManager1Cpp::EnableActionConnectionComplete()
{
    Zapp::Action* action = new Zapp::Action("ConnectionComplete");
    action->AddInputParameter(new ParameterInt("ConnectionID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgConnectionManager1Cpp::DoConnectionComplete);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgConnectionManager1Cpp::EnableActionGetCurrentConnectionIDs()
{
    Zapp::Action* action = new Zapp::Action("GetCurrentConnectionIDs");
    action->AddOutputParameter(new ParameterRelated("ConnectionIDs", *iPropertyCurrentConnectionIDs));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgConnectionManager1Cpp::DoGetCurrentConnectionIDs);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgConnectionManager1Cpp::EnableActionGetCurrentConnectionInfo()
{
    Zapp::Action* action = new Zapp::Action("GetCurrentConnectionInfo");
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgConnectionManager1Cpp::DoGetCurrentConnectionInfo);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgConnectionManager1Cpp::DoGetProtocolInfo(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSource;
    std::string respSink;
    GetProtocolInfo(aVersion, respSource, respSink);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterSource(aInvocation, "Source");
    Brn buf_Source((const TByte*)respSource.c_str(), respSource.length());
    respWriterSource.Write(buf_Source);
    aInvocation.InvocationWriteStringEnd("Source");
    InvocationResponseString respWriterSink(aInvocation, "Sink");
    Brn buf_Sink((const TByte*)respSink.c_str(), respSink.length());
    respWriterSink.Write(buf_Sink);
    aInvocation.InvocationWriteStringEnd("Sink");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgConnectionManager1Cpp::DoPrepareForConnection(IDvInvocation& aInvocation, TUint aVersion)
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
    PrepareForConnection(aVersion, RemoteProtocolInfo, PeerConnectionManager, PeerConnectionID, Direction, respConnectionID, respAVTransportID, respRcsID);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterConnectionID(aInvocation, "ConnectionID");
    respWriterConnectionID.Write(respConnectionID);
    InvocationResponseInt respWriterAVTransportID(aInvocation, "AVTransportID");
    respWriterAVTransportID.Write(respAVTransportID);
    InvocationResponseInt respWriterRcsID(aInvocation, "RcsID");
    respWriterRcsID.Write(respRcsID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgConnectionManager1Cpp::DoConnectionComplete(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t ConnectionID = aInvocation.InvocationReadInt("ConnectionID");
    aInvocation.InvocationReadEnd();
    ConnectionComplete(aVersion, ConnectionID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgConnectionManager1Cpp::DoGetCurrentConnectionIDs(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respConnectionIDs;
    GetCurrentConnectionIDs(aVersion, respConnectionIDs);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterConnectionIDs(aInvocation, "ConnectionIDs");
    Brn buf_ConnectionIDs((const TByte*)respConnectionIDs.c_str(), respConnectionIDs.length());
    respWriterConnectionIDs.Write(buf_ConnectionIDs);
    aInvocation.InvocationWriteStringEnd("ConnectionIDs");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgConnectionManager1Cpp::DoGetCurrentConnectionInfo(IDvInvocation& aInvocation, TUint aVersion)
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
    GetCurrentConnectionInfo(aVersion, ConnectionID, respRcsID, respAVTransportID, respProtocolInfo, respPeerConnectionManager, respPeerConnectionID, respDirection, respStatus);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterRcsID(aInvocation, "RcsID");
    respWriterRcsID.Write(respRcsID);
    InvocationResponseInt respWriterAVTransportID(aInvocation, "AVTransportID");
    respWriterAVTransportID.Write(respAVTransportID);
    InvocationResponseString respWriterProtocolInfo(aInvocation, "ProtocolInfo");
    Brn buf_ProtocolInfo((const TByte*)respProtocolInfo.c_str(), respProtocolInfo.length());
    respWriterProtocolInfo.Write(buf_ProtocolInfo);
    aInvocation.InvocationWriteStringEnd("ProtocolInfo");
    InvocationResponseString respWriterPeerConnectionManager(aInvocation, "PeerConnectionManager");
    Brn buf_PeerConnectionManager((const TByte*)respPeerConnectionManager.c_str(), respPeerConnectionManager.length());
    respWriterPeerConnectionManager.Write(buf_PeerConnectionManager);
    aInvocation.InvocationWriteStringEnd("PeerConnectionManager");
    InvocationResponseInt respWriterPeerConnectionID(aInvocation, "PeerConnectionID");
    respWriterPeerConnectionID.Write(respPeerConnectionID);
    InvocationResponseString respWriterDirection(aInvocation, "Direction");
    Brn buf_Direction((const TByte*)respDirection.c_str(), respDirection.length());
    respWriterDirection.Write(buf_Direction);
    aInvocation.InvocationWriteStringEnd("Direction");
    InvocationResponseString respWriterStatus(aInvocation, "Status");
    Brn buf_Status((const TByte*)respStatus.c_str(), respStatus.length());
    respWriterStatus.Write(buf_Status);
    aInvocation.InvocationWriteStringEnd("Status");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgConnectionManager1Cpp::GetProtocolInfo(uint32_t /*aVersion*/, std::string& /*aSource*/, std::string& /*aSink*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgConnectionManager1Cpp::PrepareForConnection(uint32_t /*aVersion*/, const std::string& /*aRemoteProtocolInfo*/, const std::string& /*aPeerConnectionManager*/, int32_t /*aPeerConnectionID*/, const std::string& /*aDirection*/, int32_t& /*aConnectionID*/, int32_t& /*aAVTransportID*/, int32_t& /*aRcsID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgConnectionManager1Cpp::ConnectionComplete(uint32_t /*aVersion*/, int32_t /*aConnectionID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgConnectionManager1Cpp::GetCurrentConnectionIDs(uint32_t /*aVersion*/, std::string& /*aConnectionIDs*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgConnectionManager1Cpp::GetCurrentConnectionInfo(uint32_t /*aVersion*/, int32_t /*aConnectionID*/, int32_t& /*aRcsID*/, int32_t& /*aAVTransportID*/, std::string& /*aProtocolInfo*/, std::string& /*aPeerConnectionManager*/, int32_t& /*aPeerConnectionID*/, std::string& /*aDirection*/, std::string& /*aStatus*/)
{
    ASSERTS();
}

