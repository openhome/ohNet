#include "DvAvOpenhomeOrgRadio1.h"
#include <OhNetTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/OhNet.h>
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome::Net;

class DvProviderAvOpenhomeOrgRadio1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgRadio1C(DvDeviceC aDevice);
    TBool SetPropertyUri(const Brx& aValue);
    void GetPropertyUri(Brhz& aValue);
    TBool SetPropertyMetadata(const Brx& aValue);
    void GetPropertyMetadata(Brhz& aValue);
    TBool SetPropertyTransportState(const Brx& aValue);
    void GetPropertyTransportState(Brhz& aValue);
    TBool SetPropertyId(TUint aValue);
    void GetPropertyId(TUint& aValue);
    TBool SetPropertyIdArray(const Brx& aValue);
    void GetPropertyIdArray(Brh& aValue);
    TBool SetPropertyChannelsMax(TUint aValue);
    void GetPropertyChannelsMax(TUint& aValue);
    TBool SetPropertyProtocolInfo(const Brx& aValue);
    void GetPropertyProtocolInfo(Brhz& aValue);
    void EnableActionPlay(CallbackRadio1Play aCallback, void* aPtr);
    void EnableActionPause(CallbackRadio1Pause aCallback, void* aPtr);
    void EnableActionStop(CallbackRadio1Stop aCallback, void* aPtr);
    void EnableActionSeekSecondAbsolute(CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr);
    void EnableActionSeekSecondRelative(CallbackRadio1SeekSecondRelative aCallback, void* aPtr);
    void EnableActionChannel(CallbackRadio1Channel aCallback, void* aPtr);
    void EnableActionSetChannel(CallbackRadio1SetChannel aCallback, void* aPtr);
    void EnableActionTransportState(CallbackRadio1TransportState aCallback, void* aPtr);
    void EnableActionId(CallbackRadio1Id aCallback, void* aPtr);
    void EnableActionSetId(CallbackRadio1SetId aCallback, void* aPtr);
    void EnableActionRead(CallbackRadio1Read aCallback, void* aPtr);
    void EnableActionReadList(CallbackRadio1ReadList aCallback, void* aPtr);
    void EnableActionIdArray(CallbackRadio1IdArray aCallback, void* aPtr);
    void EnableActionIdArrayChanged(CallbackRadio1IdArrayChanged aCallback, void* aPtr);
    void EnableActionChannelsMax(CallbackRadio1ChannelsMax aCallback, void* aPtr);
    void EnableActionProtocolInfo(CallbackRadio1ProtocolInfo aCallback, void* aPtr);
private:
    void DoPlay(IDviInvocation& aInvocation, TUint aVersion);
    void DoPause(IDviInvocation& aInvocation, TUint aVersion);
    void DoStop(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion);
    void DoChannel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetChannel(IDviInvocation& aInvocation, TUint aVersion);
    void DoTransportState(IDviInvocation& aInvocation, TUint aVersion);
    void DoId(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetId(IDviInvocation& aInvocation, TUint aVersion);
    void DoRead(IDviInvocation& aInvocation, TUint aVersion);
    void DoReadList(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArray(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion);
    void DoChannelsMax(IDviInvocation& aInvocation, TUint aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackRadio1Play iCallbackPlay;
    void* iPtrPlay;
    CallbackRadio1Pause iCallbackPause;
    void* iPtrPause;
    CallbackRadio1Stop iCallbackStop;
    void* iPtrStop;
    CallbackRadio1SeekSecondAbsolute iCallbackSeekSecondAbsolute;
    void* iPtrSeekSecondAbsolute;
    CallbackRadio1SeekSecondRelative iCallbackSeekSecondRelative;
    void* iPtrSeekSecondRelative;
    CallbackRadio1Channel iCallbackChannel;
    void* iPtrChannel;
    CallbackRadio1SetChannel iCallbackSetChannel;
    void* iPtrSetChannel;
    CallbackRadio1TransportState iCallbackTransportState;
    void* iPtrTransportState;
    CallbackRadio1Id iCallbackId;
    void* iPtrId;
    CallbackRadio1SetId iCallbackSetId;
    void* iPtrSetId;
    CallbackRadio1Read iCallbackRead;
    void* iPtrRead;
    CallbackRadio1ReadList iCallbackReadList;
    void* iPtrReadList;
    CallbackRadio1IdArray iCallbackIdArray;
    void* iPtrIdArray;
    CallbackRadio1IdArrayChanged iCallbackIdArrayChanged;
    void* iPtrIdArrayChanged;
    CallbackRadio1ChannelsMax iCallbackChannelsMax;
    void* iPtrChannelsMax;
    CallbackRadio1ProtocolInfo iCallbackProtocolInfo;
    void* iPtrProtocolInfo;
    PropertyString* iPropertyUri;
    PropertyString* iPropertyMetadata;
    PropertyString* iPropertyTransportState;
    PropertyUint* iPropertyId;
    PropertyBinary* iPropertyIdArray;
    PropertyUint* iPropertyChannelsMax;
    PropertyString* iPropertyProtocolInfo;
};

DvProviderAvOpenhomeOrgRadio1C::DvProviderAvOpenhomeOrgRadio1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "Radio", 1)
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

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyUri, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyUri(Brhz& aValue)
{
    aValue.Set(iPropertyUri->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyMetadata(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyTransportState(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyTransportState(Brhz& aValue)
{
    aValue.Set(iPropertyTransportState->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyId(TUint aValue)
{
    return SetPropertyUint(*iPropertyId, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyId(TUint& aValue)
{
    aValue = iPropertyId->Value();
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyIdArray(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyIdArray(Brh& aValue)
{
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyChannelsMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyChannelsMax, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyChannelsMax(TUint& aValue)
{
    aValue = iPropertyChannelsMax->Value();
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertyProtocolInfo->Value());
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionPlay(CallbackRadio1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionPause(CallbackRadio1Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionStop(CallbackRadio1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionSeekSecondAbsolute(CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr)
{
    iCallbackSeekSecondAbsolute = aCallback;
    iPtrSeekSecondAbsolute = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionSeekSecondRelative(CallbackRadio1SeekSecondRelative aCallback, void* aPtr)
{
    iCallbackSeekSecondRelative = aCallback;
    iPtrSeekSecondRelative = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionChannel(CallbackRadio1Channel aCallback, void* aPtr)
{
    iCallbackChannel = aCallback;
    iPtrChannel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Channel");
    action->AddOutputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoChannel);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionSetChannel(CallbackRadio1SetChannel aCallback, void* aPtr)
{
    iCallbackSetChannel = aCallback;
    iPtrSetChannel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetChannel");
    action->AddInputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddInputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoSetChannel);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionTransportState(CallbackRadio1TransportState aCallback, void* aPtr)
{
    iCallbackTransportState = aCallback;
    iPtrTransportState = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionId(CallbackRadio1Id aCallback, void* aPtr)
{
    iCallbackId = aCallback;
    iPtrId = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Id");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionSetId(CallbackRadio1SetId aCallback, void* aPtr)
{
    iCallbackSetId = aCallback;
    iPtrSetId = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetId");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyId));
    action->AddInputParameter(new ParameterRelated("Uri", *iPropertyUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoSetId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionRead(CallbackRadio1Read aCallback, void* aPtr)
{
    iCallbackRead = aCallback;
    iPtrRead = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Read");
    action->AddInputParameter(new ParameterRelated("Id", *iPropertyId));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionReadList(CallbackRadio1ReadList aCallback, void* aPtr)
{
    iCallbackReadList = aCallback;
    iPtrReadList = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ReadList");
    action->AddInputParameter(new ParameterString("IdList"));
    action->AddOutputParameter(new ParameterString("ChannelList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionIdArray(CallbackRadio1IdArray aCallback, void* aPtr)
{
    iCallbackIdArray = aCallback;
    iPtrIdArray = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterRelated("Array", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoIdArray);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionIdArrayChanged(CallbackRadio1IdArrayChanged aCallback, void* aPtr)
{
    iCallbackIdArrayChanged = aCallback;
    iPtrIdArrayChanged = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterBool("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionChannelsMax(CallbackRadio1ChannelsMax aCallback, void* aPtr)
{
    iCallbackChannelsMax = aCallback;
    iPtrChannelsMax = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ChannelsMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyChannelsMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoChannelsMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::EnableActionProtocolInfo(CallbackRadio1ProtocolInfo aCallback, void* aPtr)
{
    iCallbackProtocolInfo = aCallback;
    iPtrProtocolInfo = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1C::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1C::DoPlay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoPause(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoStop(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSeekSecondAbsolute != NULL);
    if (0 != iCallbackSeekSecondAbsolute(iPtrSeekSecondAbsolute, aVersion, Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSeekSecondRelative != NULL);
    if (0 != iCallbackSeekSecondRelative(iPtrSeekSecondRelative, aVersion, Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoChannel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Uri;
    char* Metadata;
    ASSERT(iCallbackChannel != NULL);
    if (0 != iCallbackChannel(iPtrChannel, aVersion, &Uri, &Metadata)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respUri(aInvocation, "Uri");
    InvocationResponseString respMetadata(aInvocation, "Metadata");
    resp.Start();
    Brhz bufUri((const TChar*)Uri);
    OhNetFreeExternal(Uri);
    respUri.Write(bufUri);
    respUri.WriteFlush();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoSetChannel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Uri;
    aInvocation.InvocationReadString("Uri", Uri);
    Brhz Metadata;
    aInvocation.InvocationReadString("Metadata", Metadata);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetChannel != NULL);
    if (0 != iCallbackSetChannel(iPtrSetChannel, aVersion, (const char*)Uri.Ptr(), (const char*)Metadata.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoTransportState(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Value;
    ASSERT(iCallbackTransportState != NULL);
    if (0 != iCallbackTransportState(iPtrTransportState, aVersion, &Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respValue(aInvocation, "Value");
    resp.Start();
    Brhz bufValue((const TChar*)Value);
    OhNetFreeExternal(Value);
    respValue.Write(bufValue);
    respValue.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackId != NULL);
    if (0 != iCallbackId(iPtrId, aVersion, &Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respValue(aInvocation, "Value");
    resp.Start();
    respValue.Write(Value);
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoSetId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    Brhz Uri;
    aInvocation.InvocationReadString("Uri", Uri);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetId != NULL);
    if (0 != iCallbackSetId(iPtrSetId, aVersion, Value, (const char*)Uri.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Metadata;
    ASSERT(iCallbackRead != NULL);
    if (0 != iCallbackRead(iPtrRead, aVersion, Id, &Metadata)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respMetadata(aInvocation, "Metadata");
    resp.Start();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoReadList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz IdList;
    aInvocation.InvocationReadString("IdList", IdList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* ChannelList;
    ASSERT(iCallbackReadList != NULL);
    if (0 != iCallbackReadList(iPtrReadList, aVersion, (const char*)IdList.Ptr(), &ChannelList)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respChannelList(aInvocation, "ChannelList");
    resp.Start();
    Brhz bufChannelList((const TChar*)ChannelList);
    OhNetFreeExternal(ChannelList);
    respChannelList.Write(bufChannelList);
    respChannelList.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoIdArray(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Token;
    char* Array;
    uint32_t ArrayLen;
    ASSERT(iCallbackIdArray != NULL);
    if (0 != iCallbackIdArray(iPtrIdArray, aVersion, &Token, &Array, &ArrayLen)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respToken(aInvocation, "Token");
    InvocationResponseBinary respArray(aInvocation, "Array");
    resp.Start();
    respToken.Write(Token);
    Brh bufArray;
    bufArray.Set((const TByte*)Array, ArrayLen);
    OhNetFreeExternal(Array);
    respArray.Write(bufArray);
    respArray.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackIdArrayChanged != NULL);
    if (0 != iCallbackIdArrayChanged(iPtrIdArrayChanged, aVersion, Token, &Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respValue(aInvocation, "Value");
    resp.Start();
    respValue.Write((Value!=0));
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoChannelsMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackChannelsMax != NULL);
    if (0 != iCallbackChannelsMax(iPtrChannelsMax, aVersion, &Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respValue(aInvocation, "Value");
    resp.Start();
    respValue.Write(Value);
    resp.End();
}

void DvProviderAvOpenhomeOrgRadio1C::DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Value;
    ASSERT(iCallbackProtocolInfo != NULL);
    if (0 != iCallbackProtocolInfo(iPtrProtocolInfo, aVersion, &Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respValue(aInvocation, "Value");
    resp.Start();
    Brhz bufValue((const TChar*)Value);
    OhNetFreeExternal(Value);
    respValue.Write(bufValue);
    respValue.WriteFlush();
    resp.End();
}



THandle DvProviderAvOpenhomeOrgRadio1Create(DvDeviceC aDevice)
{
	return new DvProviderAvOpenhomeOrgRadio1C(aDevice);
}

void DvProviderAvOpenhomeOrgRadio1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionPlay(THandle aProvider, CallbackRadio1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionPause(THandle aProvider, CallbackRadio1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionPause(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionStop(THandle aProvider, CallbackRadio1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionSeekSecondAbsolute(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionSeekSecondRelative(THandle aProvider, CallbackRadio1SeekSecondRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionSeekSecondRelative(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionChannel(THandle aProvider, CallbackRadio1Channel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionChannel(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionSetChannel(THandle aProvider, CallbackRadio1SetChannel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionSetChannel(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionTransportState(THandle aProvider, CallbackRadio1TransportState aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionTransportState(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionId(THandle aProvider, CallbackRadio1Id aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionId(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionSetId(THandle aProvider, CallbackRadio1SetId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionSetId(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionRead(THandle aProvider, CallbackRadio1Read aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionRead(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionReadList(THandle aProvider, CallbackRadio1ReadList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionReadList(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionIdArray(THandle aProvider, CallbackRadio1IdArray aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionIdArray(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionIdArrayChanged(THandle aProvider, CallbackRadio1IdArrayChanged aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionIdArrayChanged(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionChannelsMax(THandle aProvider, CallbackRadio1ChannelsMax aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionChannelsMax(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgRadio1EnableActionProtocolInfo(THandle aProvider, CallbackRadio1ProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionProtocolInfo(aCallback, aPtr);
}

int32_t DvProviderAvOpenhomeOrgRadio1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyUri(buf)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgRadio1GetPropertyUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderAvOpenhomeOrgRadio1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyMetadata(buf)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgRadio1GetPropertyMetadata(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderAvOpenhomeOrgRadio1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyTransportState(buf)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgRadio1GetPropertyTransportState(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyTransportState(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderAvOpenhomeOrgRadio1SetPropertyId(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyId(aValue)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgRadio1GetPropertyId(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyId(val);
    *aValue = val;
}

int32_t DvProviderAvOpenhomeOrgRadio1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyIdArray(buf)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgRadio1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyIdArray(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

int32_t DvProviderAvOpenhomeOrgRadio1SetPropertyChannelsMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyChannelsMax(aValue)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgRadio1GetPropertyChannelsMax(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyChannelsMax(val);
    *aValue = val;
}

int32_t DvProviderAvOpenhomeOrgRadio1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyProtocolInfo(buf)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgRadio1GetPropertyProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

