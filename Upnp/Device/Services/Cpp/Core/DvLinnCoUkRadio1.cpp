#include <Core/DvLinnCoUkRadio1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkRadio1::SetPropertyChannelUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyChannelUri, aValue);
}

void DvProviderLinnCoUkRadio1::GetPropertyChannelUri(Brhz& aValue)
{
    aValue.Set(iPropertyChannelUri->Value());
}

TBool DvProviderLinnCoUkRadio1::SetPropertyChannelMetadata(const Brx& aValue)
{
    return SetPropertyString(*iPropertyChannelMetadata, aValue);
}

void DvProviderLinnCoUkRadio1::GetPropertyChannelMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyChannelMetadata->Value());
}

TBool DvProviderLinnCoUkRadio1::SetPropertyTransportState(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderLinnCoUkRadio1::GetPropertyTransportState(Brhz& aValue)
{
    aValue.Set(iPropertyTransportState->Value());
}

TBool DvProviderLinnCoUkRadio1::SetPropertyProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvProviderLinnCoUkRadio1::GetPropertyProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertyProtocolInfo->Value());
}

TBool DvProviderLinnCoUkRadio1::SetPropertyId(TUint aValue)
{
    return SetPropertyUint(*iPropertyId, aValue);
}

void DvProviderLinnCoUkRadio1::GetPropertyId(TUint& aValue)
{
    aValue = iPropertyId->Value();
}

TBool DvProviderLinnCoUkRadio1::SetPropertyIdArray(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderLinnCoUkRadio1::GetPropertyIdArray(Brh& aValue)
{
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderLinnCoUkRadio1::SetPropertyIdsMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyIdsMax, aValue);
}

void DvProviderLinnCoUkRadio1::GetPropertyIdsMax(TUint& aValue)
{
    aValue = iPropertyIdsMax->Value();
}

DvProviderLinnCoUkRadio1::DvProviderLinnCoUkRadio1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Radio", 1)
{
    
    TChar** allowedValues;
    TUint index;
    iPropertyChannelUri = new PropertyString(new ParameterString("ChannelUri"));
    iService->AddProperty(iPropertyChannelUri); // passes ownership
    iPropertyChannelMetadata = new PropertyString(new ParameterString("ChannelMetadata"));
    iService->AddProperty(iPropertyChannelMetadata); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
    iPropertyProtocolInfo = new PropertyString(new ParameterString("ProtocolInfo"));
    iService->AddProperty(iPropertyProtocolInfo); // passes ownership
    iPropertyId = new PropertyUint(new ParameterUint("Id"));
    iService->AddProperty(iPropertyId); // passes ownership
    iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
    iPropertyIdsMax = new PropertyUint(new ParameterUint("IdsMax"));
    iService->AddProperty(iPropertyIdsMax); // passes ownership
}

void DvProviderLinnCoUkRadio1::EnableActionPlay()
{
    Zapp::Action* action = new Zapp::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionPause()
{
    Zapp::Action* action = new Zapp::Action("Pause");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionStop()
{
    Zapp::Action* action = new Zapp::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionSeekSecondAbsolute()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("aSecond"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionSeekSecondRelative()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("aSecond"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionChannel()
{
    Zapp::Action* action = new Zapp::Action("Channel");
    action->AddOutputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoChannel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionSetChannel()
{
    Zapp::Action* action = new Zapp::Action("SetChannel");
    action->AddInputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    action->AddInputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoSetChannel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionProtocolInfo()
{
    Zapp::Action* action = new Zapp::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("aInfo", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionTransportState()
{
    Zapp::Action* action = new Zapp::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("aState", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionId()
{
    Zapp::Action* action = new Zapp::Action("Id");
    action->AddOutputParameter(new ParameterRelated("aId", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionSetId()
{
    Zapp::Action* action = new Zapp::Action("SetId");
    action->AddInputParameter(new ParameterRelated("aId", *iPropertyId));
    action->AddInputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoSetId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionRead()
{
    Zapp::Action* action = new Zapp::Action("Read");
    action->AddInputParameter(new ParameterRelated("aId", *iPropertyId));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionReadList()
{
    Zapp::Action* action = new Zapp::Action("ReadList");
    action->AddInputParameter(new ParameterString("aIdList"));
    action->AddOutputParameter(new ParameterString("aMetadataList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionIdArray()
{
    Zapp::Action* action = new Zapp::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterRelated("aIdArray", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoIdArray);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionIdArrayChanged()
{
    Zapp::Action* action = new Zapp::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterBool("aIdArrayChanged"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::EnableActionIdsMax()
{
    Zapp::Action* action = new Zapp::Action("IdsMax");
    action->AddOutputParameter(new ParameterRelated("aIdsMax", *iPropertyIdsMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1::DoIdsMax);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1::DoPlay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Play(resp, aVersion);
}

void DvProviderLinnCoUkRadio1::DoPause(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Pause(resp, aVersion);
}

void DvProviderLinnCoUkRadio1::DoStop(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Stop(resp, aVersion);
}

void DvProviderLinnCoUkRadio1::DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSecond = aInvocation.InvocationReadUint("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekSecondAbsolute(resp, aVersion, aSecond);
}

void DvProviderLinnCoUkRadio1::DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aSecond = aInvocation.InvocationReadInt("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekSecondRelative(resp, aVersion, aSecond);
}

void DvProviderLinnCoUkRadio1::DoChannel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaUri(aInvocation, "aUri");
    InvocationResponseString respaMetadata(aInvocation, "aMetadata");
    Channel(resp, aVersion, respaUri, respaMetadata);
}

void DvProviderLinnCoUkRadio1::DoSetChannel(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkRadio1::DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaInfo(aInvocation, "aInfo");
    ProtocolInfo(resp, aVersion, respaInfo);
}

void DvProviderLinnCoUkRadio1::DoTransportState(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaState(aInvocation, "aState");
    TransportState(resp, aVersion, respaState);
}

void DvProviderLinnCoUkRadio1::DoId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaId(aInvocation, "aId");
    Id(resp, aVersion, respaId);
}

void DvProviderLinnCoUkRadio1::DoSetId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    Brhz aUri;
    aInvocation.InvocationReadString("aUri", aUri);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetId(resp, aVersion, aId, aUri);
}

void DvProviderLinnCoUkRadio1::DoRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMetadata(aInvocation, "aMetadata");
    Read(resp, aVersion, aId, respaMetadata);
}

void DvProviderLinnCoUkRadio1::DoReadList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aIdList;
    aInvocation.InvocationReadString("aIdList", aIdList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMetadataList(aInvocation, "aMetadataList");
    ReadList(resp, aVersion, aIdList, respaMetadataList);
}

void DvProviderLinnCoUkRadio1::DoIdArray(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaIdArrayToken(aInvocation, "aIdArrayToken");
    InvocationResponseBinary respaIdArray(aInvocation, "aIdArray");
    IdArray(resp, aVersion, respaIdArrayToken, respaIdArray);
}

void DvProviderLinnCoUkRadio1::DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIdArrayToken = aInvocation.InvocationReadUint("aIdArrayToken");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaIdArrayChanged(aInvocation, "aIdArrayChanged");
    IdArrayChanged(resp, aVersion, aIdArrayToken, respaIdArrayChanged);
}

void DvProviderLinnCoUkRadio1::DoIdsMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaIdsMax(aInvocation, "aIdsMax");
    IdsMax(resp, aVersion, respaIdsMax);
}

void DvProviderLinnCoUkRadio1::Play(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::Pause(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::Stop(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::SeekSecondAbsolute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSecond*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::SeekSecondRelative(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aaSecond*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::Channel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaUri*/, IInvocationResponseString& /*aaMetadata*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::SetChannel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaUri*/, const Brx& /*aaMetadata*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::ProtocolInfo(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaInfo*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::TransportState(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaState*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::Id(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaId*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::SetId(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaId*/, const Brx& /*aaUri*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::Read(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaId*/, IInvocationResponseString& /*aaMetadata*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::ReadList(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaIdList*/, IInvocationResponseString& /*aaMetadataList*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::IdArray(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaIdArrayToken*/, IInvocationResponseBinary& /*aaIdArray*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::IdArrayChanged(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIdArrayToken*/, IInvocationResponseBool& /*aaIdArrayChanged*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkRadio1::IdsMax(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaIdsMax*/)
{
    ASSERTS();
}

