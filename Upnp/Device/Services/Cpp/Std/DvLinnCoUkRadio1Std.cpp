#include <Std/DvLinnCoUkRadio1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkRadio1Cpp::SetPropertyChannelUri(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyChannelUri, buf);
}

void DvServiceLinnCoUkRadio1Cpp::GetPropertyChannelUri(std::string& aValue)
{
    const Brx& val = iPropertyChannelUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkRadio1Cpp::SetPropertyChannelMetadata(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyChannelMetadata, buf);
}

void DvServiceLinnCoUkRadio1Cpp::GetPropertyChannelMetadata(std::string& aValue)
{
    const Brx& val = iPropertyChannelMetadata->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkRadio1Cpp::SetPropertyTransportState(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyTransportState, buf);
}

void DvServiceLinnCoUkRadio1Cpp::GetPropertyTransportState(std::string& aValue)
{
    const Brx& val = iPropertyTransportState->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkRadio1Cpp::SetPropertyProtocolInfo(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyProtocolInfo, buf);
}

void DvServiceLinnCoUkRadio1Cpp::GetPropertyProtocolInfo(std::string& aValue)
{
    const Brx& val = iPropertyProtocolInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkRadio1Cpp::SetPropertyId(uint32_t aValue)
{
    SetPropertyUint(*iPropertyId, aValue);
}

void DvServiceLinnCoUkRadio1Cpp::GetPropertyId(uint32_t& aValue)
{
    aValue = iPropertyId->Value();
}

void DvServiceLinnCoUkRadio1Cpp::SetPropertyIdArray(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyBinary(*iPropertyIdArray, buf);
}

void DvServiceLinnCoUkRadio1Cpp::GetPropertyIdArray(std::string& aValue)
{
    const Brx& val = iPropertyIdArray->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkRadio1Cpp::SetPropertyIdsMax(uint32_t aValue)
{
    SetPropertyUint(*iPropertyIdsMax, aValue);
}

void DvServiceLinnCoUkRadio1Cpp::GetPropertyIdsMax(uint32_t& aValue)
{
    aValue = iPropertyIdsMax->Value();
}

DvServiceLinnCoUkRadio1Cpp::DvServiceLinnCoUkRadio1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Radio", 1)
{
    Functor empty;
    TChar** allowedValues;
    TUint index;
    iPropertyChannelUri = new PropertyString(new ParameterString("ChannelUri"), empty);
    iService->AddProperty(iPropertyChannelUri); // passes ownership
    iPropertyChannelMetadata = new PropertyString(new ParameterString("ChannelMetadata"), empty);
    iService->AddProperty(iPropertyChannelMetadata); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues, 4), empty);
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
    iPropertyProtocolInfo = new PropertyString(new ParameterString("ProtocolInfo"), empty);
    iService->AddProperty(iPropertyProtocolInfo); // passes ownership
    iPropertyId = new PropertyUint(new ParameterUint("Id"), empty);
    iService->AddProperty(iPropertyId); // passes ownership
    iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"), empty);
    iService->AddProperty(iPropertyIdArray); // passes ownership
    iPropertyIdsMax = new PropertyUint(new ParameterUint("IdsMax"), empty);
    iService->AddProperty(iPropertyIdsMax); // passes ownership
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionPlay()
{
    Zapp::Action* action = new Zapp::Action("Play");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoPlay);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionPause()
{
    Zapp::Action* action = new Zapp::Action("Pause");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoPause);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionStop()
{
    Zapp::Action* action = new Zapp::Action("Stop");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoStop);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionSeekSecondAbsolute()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("aSecond"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionSeekSecondRelative()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("aSecond"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionChannel()
{
    Zapp::Action* action = new Zapp::Action("Channel");
    action->AddOutputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoChannel);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionSetChannel()
{
    Zapp::Action* action = new Zapp::Action("SetChannel");
    action->AddInputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    action->AddInputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoSetChannel);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionProtocolInfo()
{
    Zapp::Action* action = new Zapp::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("aInfo", *iPropertyProtocolInfo));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionTransportState()
{
    Zapp::Action* action = new Zapp::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("aState", *iPropertyTransportState));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoTransportState);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionId()
{
    Zapp::Action* action = new Zapp::Action("Id");
    action->AddOutputParameter(new ParameterRelated("aId", *iPropertyId));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoId);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionSetId()
{
    Zapp::Action* action = new Zapp::Action("SetId");
    action->AddInputParameter(new ParameterRelated("aId", *iPropertyId));
    action->AddInputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoSetId);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionRead()
{
    Zapp::Action* action = new Zapp::Action("Read");
    action->AddInputParameter(new ParameterRelated("aId", *iPropertyId));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoRead);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionReadList()
{
    Zapp::Action* action = new Zapp::Action("ReadList");
    action->AddInputParameter(new ParameterString("aIdList"));
    action->AddOutputParameter(new ParameterString("aMetadataList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoReadList);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionIdArray()
{
    Zapp::Action* action = new Zapp::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterRelated("aIdArray", *iPropertyIdArray));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoIdArray);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionIdArrayChanged()
{
    Zapp::Action* action = new Zapp::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterBool("aIdArrayChanged"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::EnableActionIdsMax()
{
    Zapp::Action* action = new Zapp::Action("IdsMax");
    action->AddOutputParameter(new ParameterRelated("aIdsMax", *iPropertyIdsMax));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1Cpp::DoIdsMax);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1Cpp::DoPlay(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Play(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoPause(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Pause(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoStop(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Stop(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoSeekSecondAbsolute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aSecond = aInvocation.InvocationReadUint("aSecond");
    aInvocation.InvocationReadEnd();
    SeekSecondAbsolute(aVersion, aSecond);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoSeekSecondRelative(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t aSecond = aInvocation.InvocationReadInt("aSecond");
    aInvocation.InvocationReadEnd();
    SeekSecondRelative(aVersion, aSecond);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoChannel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaUri;
    std::string respaMetadata;
    Channel(aVersion, respaUri, respaMetadata);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraUri(aInvocation, "aUri");
    Brn buf_aUri((const TByte*)respaUri.c_str(), respaUri.length());
    respWriteraUri.Write(buf_aUri);
    aInvocation.InvocationWriteStringEnd("aUri");
    InvocationResponseString respWriteraMetadata(aInvocation, "aMetadata");
    Brn buf_aMetadata((const TByte*)respaMetadata.c_str(), respaMetadata.length());
    respWriteraMetadata.Write(buf_aMetadata);
    aInvocation.InvocationWriteStringEnd("aMetadata");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoSetChannel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aUri;
    aInvocation.InvocationReadString("aUri", buf_aUri);
    std::string aUri((const char*)buf_aUri.Ptr(), buf_aUri.Bytes());
    Brhz buf_aMetadata;
    aInvocation.InvocationReadString("aMetadata", buf_aMetadata);
    std::string aMetadata((const char*)buf_aMetadata.Ptr(), buf_aMetadata.Bytes());
    aInvocation.InvocationReadEnd();
    SetChannel(aVersion, aUri, aMetadata);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoProtocolInfo(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaInfo;
    ProtocolInfo(aVersion, respaInfo);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraInfo(aInvocation, "aInfo");
    Brn buf_aInfo((const TByte*)respaInfo.c_str(), respaInfo.length());
    respWriteraInfo.Write(buf_aInfo);
    aInvocation.InvocationWriteStringEnd("aInfo");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoTransportState(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaState;
    TransportState(aVersion, respaState);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraState(aInvocation, "aState");
    Brn buf_aState((const TByte*)respaState.c_str(), respaState.length());
    respWriteraState.Write(buf_aState);
    aInvocation.InvocationWriteStringEnd("aState");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaId;
    Id(aVersion, respaId);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraId(aInvocation, "aId");
    respWriteraId.Write(respaId);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoSetId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aId = aInvocation.InvocationReadUint("aId");
    Brhz buf_aUri;
    aInvocation.InvocationReadString("aUri", buf_aUri);
    std::string aUri((const char*)buf_aUri.Ptr(), buf_aUri.Bytes());
    aInvocation.InvocationReadEnd();
    SetId(aVersion, aId, aUri);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoRead(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    std::string respaMetadata;
    Read(aVersion, aId, respaMetadata);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraMetadata(aInvocation, "aMetadata");
    Brn buf_aMetadata((const TByte*)respaMetadata.c_str(), respaMetadata.length());
    respWriteraMetadata.Write(buf_aMetadata);
    aInvocation.InvocationWriteStringEnd("aMetadata");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoReadList(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aIdList;
    aInvocation.InvocationReadString("aIdList", buf_aIdList);
    std::string aIdList((const char*)buf_aIdList.Ptr(), buf_aIdList.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respaMetadataList;
    ReadList(aVersion, aIdList, respaMetadataList);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraMetadataList(aInvocation, "aMetadataList");
    Brn buf_aMetadataList((const TByte*)respaMetadataList.c_str(), respaMetadataList.length());
    respWriteraMetadataList.Write(buf_aMetadataList);
    aInvocation.InvocationWriteStringEnd("aMetadataList");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoIdArray(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaIdArrayToken;
    std::string respaIdArray;
    IdArray(aVersion, respaIdArrayToken, respaIdArray);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraIdArrayToken(aInvocation, "aIdArrayToken");
    respWriteraIdArrayToken.Write(respaIdArrayToken);
    InvocationResponseBinary respWriteraIdArray(aInvocation, "aIdArray");
    Brn buf_aIdArray((const TByte*)respaIdArray.c_str(), respaIdArray.length());
    respWriteraIdArray.Write(buf_aIdArray);
    aInvocation.InvocationWriteBinaryEnd("aIdArray");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoIdArrayChanged(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIdArrayToken = aInvocation.InvocationReadUint("aIdArrayToken");
    aInvocation.InvocationReadEnd();
    bool respaIdArrayChanged;
    IdArrayChanged(aVersion, aIdArrayToken, respaIdArrayChanged);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraIdArrayChanged(aInvocation, "aIdArrayChanged");
    respWriteraIdArrayChanged.Write(respaIdArrayChanged);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::DoIdsMax(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaIdsMax;
    IdsMax(aVersion, respaIdsMax);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraIdsMax(aInvocation, "aIdsMax");
    respWriteraIdsMax.Write(respaIdsMax);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkRadio1Cpp::Play(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::Pause(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::Stop(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::SeekSecondAbsolute(uint32_t /*aVersion*/, uint32_t /*aaSecond*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::SeekSecondRelative(uint32_t /*aVersion*/, int32_t /*aaSecond*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::Channel(uint32_t /*aVersion*/, std::string& /*aaUri*/, std::string& /*aaMetadata*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::SetChannel(uint32_t /*aVersion*/, const std::string& /*aaUri*/, const std::string& /*aaMetadata*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::ProtocolInfo(uint32_t /*aVersion*/, std::string& /*aaInfo*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::TransportState(uint32_t /*aVersion*/, std::string& /*aaState*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::Id(uint32_t /*aVersion*/, uint32_t& /*aaId*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::SetId(uint32_t /*aVersion*/, uint32_t /*aaId*/, const std::string& /*aaUri*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::Read(uint32_t /*aVersion*/, uint32_t /*aaId*/, std::string& /*aaMetadata*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::ReadList(uint32_t /*aVersion*/, const std::string& /*aaIdList*/, std::string& /*aaMetadataList*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::IdArray(uint32_t /*aVersion*/, uint32_t& /*aaIdArrayToken*/, std::string& /*aaIdArray*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::IdArrayChanged(uint32_t /*aVersion*/, uint32_t /*aaIdArrayToken*/, bool& /*aaIdArrayChanged*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1Cpp::IdsMax(uint32_t /*aVersion*/, uint32_t& /*aaIdsMax*/)
{
    ASSERTS();
}

