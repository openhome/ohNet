#include <Core/DvLinnCoUkRadio1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkRadio1::SetPropertyChannelUri(const Brx& aValue)
{
    SetPropertyString(*iPropertyChannelUri, aValue);
}

void DvServiceLinnCoUkRadio1::GetPropertyChannelUri(Brhz& aValue)
{
    aValue.Set(iPropertyChannelUri->Value());
}

void DvServiceLinnCoUkRadio1::SetPropertyChannelMetadata(const Brx& aValue)
{
    SetPropertyString(*iPropertyChannelMetadata, aValue);
}

void DvServiceLinnCoUkRadio1::GetPropertyChannelMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyChannelMetadata->Value());
}

void DvServiceLinnCoUkRadio1::SetPropertyTransportState(const Brx& aValue)
{
    SetPropertyString(*iPropertyTransportState, aValue);
}

void DvServiceLinnCoUkRadio1::GetPropertyTransportState(Brhz& aValue)
{
    aValue.Set(iPropertyTransportState->Value());
}

void DvServiceLinnCoUkRadio1::SetPropertyProtocolInfo(const Brx& aValue)
{
    SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvServiceLinnCoUkRadio1::GetPropertyProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertyProtocolInfo->Value());
}

void DvServiceLinnCoUkRadio1::SetPropertyId(TUint aValue)
{
    SetPropertyUint(*iPropertyId, aValue);
}

void DvServiceLinnCoUkRadio1::GetPropertyId(TUint& aValue)
{
    aValue = iPropertyId->Value();
}

void DvServiceLinnCoUkRadio1::SetPropertyIdArray(const Brx& aValue)
{
    SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvServiceLinnCoUkRadio1::GetPropertyIdArray(Brh& aValue)
{
    aValue.Set(iPropertyIdArray->Value());
}

void DvServiceLinnCoUkRadio1::SetPropertyIdsMax(TUint aValue)
{
    SetPropertyUint(*iPropertyIdsMax, aValue);
}

void DvServiceLinnCoUkRadio1::GetPropertyIdsMax(TUint& aValue)
{
    aValue = iPropertyIdsMax->Value();
}

DvServiceLinnCoUkRadio1::DvServiceLinnCoUkRadio1(DvDevice& aDevice)
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

void DvServiceLinnCoUkRadio1::EnableActionPlay()
{
    Zapp::Action* action = new Zapp::Action("Play");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoPlay);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionPause()
{
    Zapp::Action* action = new Zapp::Action("Pause");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoPause);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionStop()
{
    Zapp::Action* action = new Zapp::Action("Stop");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoStop);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionSeekSecondAbsolute()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("aSecond"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionSeekSecondRelative()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("aSecond"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionChannel()
{
    Zapp::Action* action = new Zapp::Action("Channel");
    action->AddOutputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoChannel);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionSetChannel()
{
    Zapp::Action* action = new Zapp::Action("SetChannel");
    action->AddInputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    action->AddInputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoSetChannel);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionProtocolInfo()
{
    Zapp::Action* action = new Zapp::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("aInfo", *iPropertyProtocolInfo));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionTransportState()
{
    Zapp::Action* action = new Zapp::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("aState", *iPropertyTransportState));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoTransportState);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionId()
{
    Zapp::Action* action = new Zapp::Action("Id");
    action->AddOutputParameter(new ParameterRelated("aId", *iPropertyId));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoId);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionSetId()
{
    Zapp::Action* action = new Zapp::Action("SetId");
    action->AddInputParameter(new ParameterRelated("aId", *iPropertyId));
    action->AddInputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoSetId);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionRead()
{
    Zapp::Action* action = new Zapp::Action("Read");
    action->AddInputParameter(new ParameterRelated("aId", *iPropertyId));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoRead);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionReadList()
{
    Zapp::Action* action = new Zapp::Action("ReadList");
    action->AddInputParameter(new ParameterString("aIdList"));
    action->AddOutputParameter(new ParameterString("aMetadataList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoReadList);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionIdArray()
{
    Zapp::Action* action = new Zapp::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterRelated("aIdArray", *iPropertyIdArray));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoIdArray);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionIdArrayChanged()
{
    Zapp::Action* action = new Zapp::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterBool("aIdArrayChanged"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::EnableActionIdsMax()
{
    Zapp::Action* action = new Zapp::Action("IdsMax");
    action->AddOutputParameter(new ParameterRelated("aIdsMax", *iPropertyIdsMax));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkRadio1::DoIdsMax);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkRadio1::DoPlay(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Play(resp, aVersion);
}

void DvServiceLinnCoUkRadio1::DoPause(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Pause(resp, aVersion);
}

void DvServiceLinnCoUkRadio1::DoStop(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Stop(resp, aVersion);
}

void DvServiceLinnCoUkRadio1::DoSeekSecondAbsolute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSecond = aInvocation.InvocationReadUint("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekSecondAbsolute(resp, aVersion, aSecond);
}

void DvServiceLinnCoUkRadio1::DoSeekSecondRelative(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aSecond = aInvocation.InvocationReadInt("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekSecondRelative(resp, aVersion, aSecond);
}

void DvServiceLinnCoUkRadio1::DoChannel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaUri(aInvocation, "aUri");
    InvocationResponseString respaMetadata(aInvocation, "aMetadata");
    Channel(resp, aVersion, respaUri, respaMetadata);
}

void DvServiceLinnCoUkRadio1::DoSetChannel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aUri;
    aInvocation.InvocationReadString("aUri", aUri);
    Brhz aMetadata;
    aInvocation.InvocationReadString("aMetadata", aMetadata);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetChannel(resp, aVersion, aUri, aMetadata);
}

void DvServiceLinnCoUkRadio1::DoProtocolInfo(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaInfo(aInvocation, "aInfo");
    ProtocolInfo(resp, aVersion, respaInfo);
}

void DvServiceLinnCoUkRadio1::DoTransportState(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaState(aInvocation, "aState");
    TransportState(resp, aVersion, respaState);
}

void DvServiceLinnCoUkRadio1::DoId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaId(aInvocation, "aId");
    Id(resp, aVersion, respaId);
}

void DvServiceLinnCoUkRadio1::DoSetId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    Brhz aUri;
    aInvocation.InvocationReadString("aUri", aUri);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetId(resp, aVersion, aId, aUri);
}

void DvServiceLinnCoUkRadio1::DoRead(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMetadata(aInvocation, "aMetadata");
    Read(resp, aVersion, aId, respaMetadata);
}

void DvServiceLinnCoUkRadio1::DoReadList(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aIdList;
    aInvocation.InvocationReadString("aIdList", aIdList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMetadataList(aInvocation, "aMetadataList");
    ReadList(resp, aVersion, aIdList, respaMetadataList);
}

void DvServiceLinnCoUkRadio1::DoIdArray(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaIdArrayToken(aInvocation, "aIdArrayToken");
    InvocationResponseBinary respaIdArray(aInvocation, "aIdArray");
    IdArray(resp, aVersion, respaIdArrayToken, respaIdArray);
}

void DvServiceLinnCoUkRadio1::DoIdArrayChanged(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIdArrayToken = aInvocation.InvocationReadUint("aIdArrayToken");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaIdArrayChanged(aInvocation, "aIdArrayChanged");
    IdArrayChanged(resp, aVersion, aIdArrayToken, respaIdArrayChanged);
}

void DvServiceLinnCoUkRadio1::DoIdsMax(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaIdsMax(aInvocation, "aIdsMax");
    IdsMax(resp, aVersion, respaIdsMax);
}

void DvServiceLinnCoUkRadio1::Play(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::Pause(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::Stop(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::SeekSecondAbsolute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSecond*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::SeekSecondRelative(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aaSecond*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::Channel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaUri*/, IInvocationResponseString& /*aaMetadata*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::SetChannel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaUri*/, const Brx& /*aaMetadata*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::ProtocolInfo(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaInfo*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::TransportState(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaState*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::Id(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaId*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::SetId(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaId*/, const Brx& /*aaUri*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::Read(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaId*/, IInvocationResponseString& /*aaMetadata*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::ReadList(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaIdList*/, IInvocationResponseString& /*aaMetadataList*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::IdArray(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaIdArrayToken*/, IInvocationResponseBinary& /*aaIdArray*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::IdArrayChanged(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIdArrayToken*/, IInvocationResponseBool& /*aaIdArrayChanged*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkRadio1::IdsMax(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaIdsMax*/)
{
    ASSERTS();
}

