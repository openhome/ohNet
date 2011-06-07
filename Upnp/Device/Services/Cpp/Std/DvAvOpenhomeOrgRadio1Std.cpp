#include "DvAvOpenhomeOrgRadio1.h"
#include <OhNetTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgRadio1Cpp::SetPropertyUri(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyUri, buf);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::GetPropertyUri(std::string& aValue)
{
    const Brx& val = iPropertyUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgRadio1Cpp::SetPropertyMetadata(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyMetadata, buf);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::GetPropertyMetadata(std::string& aValue)
{
    const Brx& val = iPropertyMetadata->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgRadio1Cpp::SetPropertyTransportState(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyTransportState, buf);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::GetPropertyTransportState(std::string& aValue)
{
    const Brx& val = iPropertyTransportState->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgRadio1Cpp::SetPropertyId(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyId, aValue);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::GetPropertyId(uint32_t& aValue)
{
    aValue = iPropertyId->Value();
}

bool DvProviderAvOpenhomeOrgRadio1Cpp::SetPropertyIdArray(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyBinary(*iPropertyIdArray, buf);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::GetPropertyIdArray(std::string& aValue)
{
    const Brx& val = iPropertyIdArray->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgRadio1Cpp::SetPropertyChannelsMax(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyChannelsMax, aValue);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::GetPropertyChannelsMax(uint32_t& aValue)
{
    aValue = iPropertyChannelsMax->Value();
}

bool DvProviderAvOpenhomeOrgRadio1Cpp::SetPropertyProtocolInfo(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProtocolInfo, buf);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::GetPropertyProtocolInfo(std::string& aValue)
{
    const Brx& val = iPropertyProtocolInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderAvOpenhomeOrgRadio1Cpp::DvProviderAvOpenhomeOrgRadio1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Radio", 1)
{
    
    TChar** allowedValues;
    TUint index;
    iPropertyUri = new PropertyString(new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
    iPropertyMetadata = new PropertyString(new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
    iPropertyId = new PropertyUint(new ParameterUint("Id"));
    iService->AddProperty(iPropertyId); // passes ownership
    iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
    iPropertyChannelsMax = new PropertyUint(new ParameterUint("ChannelsMax"));
    iService->AddProperty(iPropertyChannelsMax); // passes ownership
    iPropertyProtocolInfo = new PropertyString(new ParameterString("ProtocolInfo"));
    iService->AddProperty(iPropertyProtocolInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionPlay()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionPause()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionStop()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionSeekSecondAbsolute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionSeekSecondRelative()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionChannel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Channel");
    action->AddOutputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoChannel);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionSetChannel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetChannel");
    action->AddInputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddInputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoSetChannel);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionTransportState()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Id");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionSetId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetId");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyId));
    action->AddInputParameter(new ParameterRelated("Uri", *iPropertyUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoSetId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionRead()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Read");
    action->AddInputParameter(new ParameterRelated("Id", *iPropertyId));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionReadList()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ReadList");
    action->AddInputParameter(new ParameterString("IdList"));
    action->AddOutputParameter(new ParameterString("ChannelList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionIdArray()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterRelated("Array", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoIdArray);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionIdArrayChanged()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterBool("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionChannelsMax()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ChannelsMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyChannelsMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoChannelsMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::EnableActionProtocolInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1Cpp::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoPlay(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Play(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoPause(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Pause(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoStop(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Stop(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoSeekSecondAbsolute(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    SeekSecondAbsolute(aVersion, Value);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoSeekSecondRelative(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    SeekSecondRelative(aVersion, Value);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoChannel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respUri;
    std::string respMetadata;
    Channel(aVersion, respUri, respMetadata);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterUri(aInvocation, "Uri");
    Brn buf_Uri((const TByte*)respUri.c_str(), (TUint)respUri.length());
    respWriterUri.Write(buf_Uri);
    aInvocation.InvocationWriteStringEnd("Uri");
    InvocationResponseString respWriterMetadata(aInvocation, "Metadata");
    Brn buf_Metadata((const TByte*)respMetadata.c_str(), (TUint)respMetadata.length());
    respWriterMetadata.Write(buf_Metadata);
    aInvocation.InvocationWriteStringEnd("Metadata");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoSetChannel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Uri;
    aInvocation.InvocationReadString("Uri", buf_Uri);
    std::string Uri((const char*)buf_Uri.Ptr(), buf_Uri.Bytes());
    Brhz buf_Metadata;
    aInvocation.InvocationReadString("Metadata", buf_Metadata);
    std::string Metadata((const char*)buf_Metadata.Ptr(), buf_Metadata.Bytes());
    aInvocation.InvocationReadEnd();
    SetChannel(aVersion, Uri, Metadata);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoTransportState(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    TransportState(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoId(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    Id(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoSetId(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    Brhz buf_Uri;
    aInvocation.InvocationReadString("Uri", buf_Uri);
    std::string Uri((const char*)buf_Uri.Ptr(), buf_Uri.Bytes());
    aInvocation.InvocationReadEnd();
    SetId(aVersion, Value, Uri);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoRead(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    std::string respMetadata;
    Read(aVersion, Id, respMetadata);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterMetadata(aInvocation, "Metadata");
    Brn buf_Metadata((const TByte*)respMetadata.c_str(), (TUint)respMetadata.length());
    respWriterMetadata.Write(buf_Metadata);
    aInvocation.InvocationWriteStringEnd("Metadata");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoReadList(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_IdList;
    aInvocation.InvocationReadString("IdList", buf_IdList);
    std::string IdList((const char*)buf_IdList.Ptr(), buf_IdList.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respChannelList;
    ReadList(aVersion, IdList, respChannelList);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterChannelList(aInvocation, "ChannelList");
    Brn buf_ChannelList((const TByte*)respChannelList.c_str(), (TUint)respChannelList.length());
    respWriterChannelList.Write(buf_ChannelList);
    aInvocation.InvocationWriteStringEnd("ChannelList");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoIdArray(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respToken;
    std::string respArray;
    IdArray(aVersion, respToken, respArray);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterToken(aInvocation, "Token");
    respWriterToken.Write(respToken);
    InvocationResponseBinary respWriterArray(aInvocation, "Array");
    Brn buf_Array((const TByte*)respArray.c_str(), (TUint)respArray.length());
    respWriterArray.Write(buf_Array);
    aInvocation.InvocationWriteBinaryEnd("Array");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoIdArrayChanged(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    bool respValue;
    IdArrayChanged(aVersion, Token, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoChannelsMax(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    ChannelsMax(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::DoProtocolInfo(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    ProtocolInfo(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::Play(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::Pause(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::Stop(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::SeekSecondAbsolute(uint32_t /*aVersion*/, uint32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::SeekSecondRelative(uint32_t /*aVersion*/, int32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::Channel(uint32_t /*aVersion*/, std::string& /*aUri*/, std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::SetChannel(uint32_t /*aVersion*/, const std::string& /*aUri*/, const std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::TransportState(uint32_t /*aVersion*/, std::string& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::Id(uint32_t /*aVersion*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::SetId(uint32_t /*aVersion*/, uint32_t /*aValue*/, const std::string& /*aUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::Read(uint32_t /*aVersion*/, uint32_t /*aId*/, std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::ReadList(uint32_t /*aVersion*/, const std::string& /*aIdList*/, std::string& /*aChannelList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::IdArray(uint32_t /*aVersion*/, uint32_t& /*aToken*/, std::string& /*aArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::IdArrayChanged(uint32_t /*aVersion*/, uint32_t /*aToken*/, bool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::ChannelsMax(uint32_t /*aVersion*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1Cpp::ProtocolInfo(uint32_t /*aVersion*/, std::string& /*aValue*/)
{
    ASSERTS();
}

