#include "DvLinnCoUkRadio1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderLinnCoUkRadio1C : public DvProvider
{
public:
    DvProviderLinnCoUkRadio1C(DvDeviceC aDevice);
    TBool SetPropertyChannelUri(const Brx& aValue);
    void GetPropertyChannelUri(Brhz& aValue);
    TBool SetPropertyChannelMetadata(const Brx& aValue);
    void GetPropertyChannelMetadata(Brhz& aValue);
    TBool SetPropertyTransportState(const Brx& aValue);
    void GetPropertyTransportState(Brhz& aValue);
    TBool SetPropertyProtocolInfo(const Brx& aValue);
    void GetPropertyProtocolInfo(Brhz& aValue);
    TBool SetPropertyId(TUint aValue);
    void GetPropertyId(TUint& aValue);
    TBool SetPropertyIdArray(const Brx& aValue);
    void GetPropertyIdArray(Brh& aValue);
    TBool SetPropertyIdsMax(TUint aValue);
    void GetPropertyIdsMax(TUint& aValue);
    void EnableActionPlay(CallbackRadio1Play aCallback, void* aPtr);
    void EnableActionPause(CallbackRadio1Pause aCallback, void* aPtr);
    void EnableActionStop(CallbackRadio1Stop aCallback, void* aPtr);
    void EnableActionSeekSecondAbsolute(CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr);
    void EnableActionSeekSecondRelative(CallbackRadio1SeekSecondRelative aCallback, void* aPtr);
    void EnableActionChannel(CallbackRadio1Channel aCallback, void* aPtr);
    void EnableActionSetChannel(CallbackRadio1SetChannel aCallback, void* aPtr);
    void EnableActionProtocolInfo(CallbackRadio1ProtocolInfo aCallback, void* aPtr);
    void EnableActionTransportState(CallbackRadio1TransportState aCallback, void* aPtr);
    void EnableActionId(CallbackRadio1Id aCallback, void* aPtr);
    void EnableActionSetId(CallbackRadio1SetId aCallback, void* aPtr);
    void EnableActionRead(CallbackRadio1Read aCallback, void* aPtr);
    void EnableActionReadList(CallbackRadio1ReadList aCallback, void* aPtr);
    void EnableActionIdArray(CallbackRadio1IdArray aCallback, void* aPtr);
    void EnableActionIdArrayChanged(CallbackRadio1IdArrayChanged aCallback, void* aPtr);
    void EnableActionIdsMax(CallbackRadio1IdsMax aCallback, void* aPtr);
private:
    void DoPlay(IDviInvocation& aInvocation, TUint aVersion);
    void DoPause(IDviInvocation& aInvocation, TUint aVersion);
    void DoStop(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion);
    void DoChannel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetChannel(IDviInvocation& aInvocation, TUint aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoTransportState(IDviInvocation& aInvocation, TUint aVersion);
    void DoId(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetId(IDviInvocation& aInvocation, TUint aVersion);
    void DoRead(IDviInvocation& aInvocation, TUint aVersion);
    void DoReadList(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArray(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdsMax(IDviInvocation& aInvocation, TUint aVersion);
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
    CallbackRadio1ProtocolInfo iCallbackProtocolInfo;
    void* iPtrProtocolInfo;
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
    CallbackRadio1IdsMax iCallbackIdsMax;
    void* iPtrIdsMax;
    PropertyString* iPropertyChannelUri;
    PropertyString* iPropertyChannelMetadata;
    PropertyString* iPropertyTransportState;
    PropertyString* iPropertyProtocolInfo;
    PropertyUint* iPropertyId;
    PropertyBinary* iPropertyIdArray;
    PropertyUint* iPropertyIdsMax;
};

DvProviderLinnCoUkRadio1C::DvProviderLinnCoUkRadio1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Radio", 1)
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

TBool DvProviderLinnCoUkRadio1C::SetPropertyChannelUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyChannelUri, aValue);
}

void DvProviderLinnCoUkRadio1C::GetPropertyChannelUri(Brhz& aValue)
{
    aValue.Set(iPropertyChannelUri->Value());
}

TBool DvProviderLinnCoUkRadio1C::SetPropertyChannelMetadata(const Brx& aValue)
{
    return SetPropertyString(*iPropertyChannelMetadata, aValue);
}

void DvProviderLinnCoUkRadio1C::GetPropertyChannelMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyChannelMetadata->Value());
}

TBool DvProviderLinnCoUkRadio1C::SetPropertyTransportState(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderLinnCoUkRadio1C::GetPropertyTransportState(Brhz& aValue)
{
    aValue.Set(iPropertyTransportState->Value());
}

TBool DvProviderLinnCoUkRadio1C::SetPropertyProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvProviderLinnCoUkRadio1C::GetPropertyProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertyProtocolInfo->Value());
}

TBool DvProviderLinnCoUkRadio1C::SetPropertyId(TUint aValue)
{
    return SetPropertyUint(*iPropertyId, aValue);
}

void DvProviderLinnCoUkRadio1C::GetPropertyId(TUint& aValue)
{
    aValue = iPropertyId->Value();
}

TBool DvProviderLinnCoUkRadio1C::SetPropertyIdArray(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderLinnCoUkRadio1C::GetPropertyIdArray(Brh& aValue)
{
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderLinnCoUkRadio1C::SetPropertyIdsMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyIdsMax, aValue);
}

void DvProviderLinnCoUkRadio1C::GetPropertyIdsMax(TUint& aValue)
{
    aValue = iPropertyIdsMax->Value();
}

void DvProviderLinnCoUkRadio1C::EnableActionPlay(CallbackRadio1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    Zapp::Action* action = new Zapp::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionPause(CallbackRadio1Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    Zapp::Action* action = new Zapp::Action("Pause");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionStop(CallbackRadio1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    Zapp::Action* action = new Zapp::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionSeekSecondAbsolute(CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr)
{
    iCallbackSeekSecondAbsolute = aCallback;
    iPtrSeekSecondAbsolute = aPtr;
    Zapp::Action* action = new Zapp::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("aSecond"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionSeekSecondRelative(CallbackRadio1SeekSecondRelative aCallback, void* aPtr)
{
    iCallbackSeekSecondRelative = aCallback;
    iPtrSeekSecondRelative = aPtr;
    Zapp::Action* action = new Zapp::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("aSecond"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionChannel(CallbackRadio1Channel aCallback, void* aPtr)
{
    iCallbackChannel = aCallback;
    iPtrChannel = aPtr;
    Zapp::Action* action = new Zapp::Action("Channel");
    action->AddOutputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoChannel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionSetChannel(CallbackRadio1SetChannel aCallback, void* aPtr)
{
    iCallbackSetChannel = aCallback;
    iPtrSetChannel = aPtr;
    Zapp::Action* action = new Zapp::Action("SetChannel");
    action->AddInputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    action->AddInputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoSetChannel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionProtocolInfo(CallbackRadio1ProtocolInfo aCallback, void* aPtr)
{
    iCallbackProtocolInfo = aCallback;
    iPtrProtocolInfo = aPtr;
    Zapp::Action* action = new Zapp::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("aInfo", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionTransportState(CallbackRadio1TransportState aCallback, void* aPtr)
{
    iCallbackTransportState = aCallback;
    iPtrTransportState = aPtr;
    Zapp::Action* action = new Zapp::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("aState", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionId(CallbackRadio1Id aCallback, void* aPtr)
{
    iCallbackId = aCallback;
    iPtrId = aPtr;
    Zapp::Action* action = new Zapp::Action("Id");
    action->AddOutputParameter(new ParameterRelated("aId", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionSetId(CallbackRadio1SetId aCallback, void* aPtr)
{
    iCallbackSetId = aCallback;
    iPtrSetId = aPtr;
    Zapp::Action* action = new Zapp::Action("SetId");
    action->AddInputParameter(new ParameterRelated("aId", *iPropertyId));
    action->AddInputParameter(new ParameterRelated("aUri", *iPropertyChannelUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoSetId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionRead(CallbackRadio1Read aCallback, void* aPtr)
{
    iCallbackRead = aCallback;
    iPtrRead = aPtr;
    Zapp::Action* action = new Zapp::Action("Read");
    action->AddInputParameter(new ParameterRelated("aId", *iPropertyId));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyChannelMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionReadList(CallbackRadio1ReadList aCallback, void* aPtr)
{
    iCallbackReadList = aCallback;
    iPtrReadList = aPtr;
    Zapp::Action* action = new Zapp::Action("ReadList");
    action->AddInputParameter(new ParameterString("aIdList"));
    action->AddOutputParameter(new ParameterString("aMetadataList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionIdArray(CallbackRadio1IdArray aCallback, void* aPtr)
{
    iCallbackIdArray = aCallback;
    iPtrIdArray = aPtr;
    Zapp::Action* action = new Zapp::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterRelated("aIdArray", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoIdArray);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionIdArrayChanged(CallbackRadio1IdArrayChanged aCallback, void* aPtr)
{
    iCallbackIdArrayChanged = aCallback;
    iPtrIdArrayChanged = aPtr;
    Zapp::Action* action = new Zapp::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterBool("aIdArrayChanged"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::EnableActionIdsMax(CallbackRadio1IdsMax aCallback, void* aPtr)
{
    iCallbackIdsMax = aCallback;
    iPtrIdsMax = aPtr;
    Zapp::Action* action = new Zapp::Action("IdsMax");
    action->AddOutputParameter(new ParameterRelated("aIdsMax", *iPropertyIdsMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkRadio1C::DoIdsMax);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkRadio1C::DoPlay(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkRadio1C::DoPause(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkRadio1C::DoStop(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkRadio1C::DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSecond = aInvocation.InvocationReadUint("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSeekSecondAbsolute != NULL);
    if (0 != iCallbackSeekSecondAbsolute(iPtrSeekSecondAbsolute, aVersion, aSecond)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aSecond = aInvocation.InvocationReadInt("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSeekSecondRelative != NULL);
    if (0 != iCallbackSeekSecondRelative(iPtrSeekSecondRelative, aVersion, aSecond)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoChannel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aUri;
    char* aMetadata;
    ASSERT(iCallbackChannel != NULL);
    if (0 != iCallbackChannel(iPtrChannel, aVersion, &aUri, &aMetadata)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaUri(aInvocation, "aUri");
    InvocationResponseString respaMetadata(aInvocation, "aMetadata");
    resp.Start();
    Brhz bufaUri((const TChar*)aUri);
    ZappFreeExternal(aUri);
    respaUri.Write(bufaUri);
    respaUri.WriteFlush();
    Brhz bufaMetadata((const TChar*)aMetadata);
    ZappFreeExternal(aMetadata);
    respaMetadata.Write(bufaMetadata);
    respaMetadata.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoSetChannel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aUri;
    aInvocation.InvocationReadString("aUri", aUri);
    Brhz aMetadata;
    aInvocation.InvocationReadString("aMetadata", aMetadata);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetChannel != NULL);
    if (0 != iCallbackSetChannel(iPtrSetChannel, aVersion, (const char*)aUri.Ptr(), (const char*)aMetadata.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aInfo;
    ASSERT(iCallbackProtocolInfo != NULL);
    if (0 != iCallbackProtocolInfo(iPtrProtocolInfo, aVersion, &aInfo)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaInfo(aInvocation, "aInfo");
    resp.Start();
    Brhz bufaInfo((const TChar*)aInfo);
    ZappFreeExternal(aInfo);
    respaInfo.Write(bufaInfo);
    respaInfo.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoTransportState(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aState;
    ASSERT(iCallbackTransportState != NULL);
    if (0 != iCallbackTransportState(iPtrTransportState, aVersion, &aState)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaState(aInvocation, "aState");
    resp.Start();
    Brhz bufaState((const TChar*)aState);
    ZappFreeExternal(aState);
    respaState.Write(bufaState);
    respaState.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aId;
    ASSERT(iCallbackId != NULL);
    if (0 != iCallbackId(iPtrId, aVersion, &aId)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaId(aInvocation, "aId");
    resp.Start();
    respaId.Write(aId);
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoSetId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    Brhz aUri;
    aInvocation.InvocationReadString("aUri", aUri);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetId != NULL);
    if (0 != iCallbackSetId(iPtrSetId, aVersion, aId, (const char*)aUri.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aMetadata;
    ASSERT(iCallbackRead != NULL);
    if (0 != iCallbackRead(iPtrRead, aVersion, aId, &aMetadata)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaMetadata(aInvocation, "aMetadata");
    resp.Start();
    Brhz bufaMetadata((const TChar*)aMetadata);
    ZappFreeExternal(aMetadata);
    respaMetadata.Write(bufaMetadata);
    respaMetadata.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoReadList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aIdList;
    aInvocation.InvocationReadString("aIdList", aIdList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aMetadataList;
    ASSERT(iCallbackReadList != NULL);
    if (0 != iCallbackReadList(iPtrReadList, aVersion, (const char*)aIdList.Ptr(), &aMetadataList)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaMetadataList(aInvocation, "aMetadataList");
    resp.Start();
    Brhz bufaMetadataList((const TChar*)aMetadataList);
    ZappFreeExternal(aMetadataList);
    respaMetadataList.Write(bufaMetadataList);
    respaMetadataList.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoIdArray(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aIdArrayToken;
    char* aIdArray;
    uint32_t aIdArrayLen;
    ASSERT(iCallbackIdArray != NULL);
    if (0 != iCallbackIdArray(iPtrIdArray, aVersion, &aIdArrayToken, &aIdArray, &aIdArrayLen)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaIdArrayToken(aInvocation, "aIdArrayToken");
    InvocationResponseBinary respaIdArray(aInvocation, "aIdArray");
    resp.Start();
    respaIdArrayToken.Write(aIdArrayToken);
    Brh bufaIdArray;
    bufaIdArray.Set((const TByte*)aIdArray, aIdArrayLen);
    ZappFreeExternal(aIdArray);
    respaIdArray.Write(bufaIdArray);
    respaIdArray.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIdArrayToken = aInvocation.InvocationReadUint("aIdArrayToken");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aIdArrayChanged;
    ASSERT(iCallbackIdArrayChanged != NULL);
    if (0 != iCallbackIdArrayChanged(iPtrIdArrayChanged, aVersion, aIdArrayToken, &aIdArrayChanged)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaIdArrayChanged(aInvocation, "aIdArrayChanged");
    resp.Start();
    respaIdArrayChanged.Write((aIdArrayChanged!=0));
    resp.End();
}

void DvProviderLinnCoUkRadio1C::DoIdsMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aIdsMax;
    ASSERT(iCallbackIdsMax != NULL);
    if (0 != iCallbackIdsMax(iPtrIdsMax, aVersion, &aIdsMax)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaIdsMax(aInvocation, "aIdsMax");
    resp.Start();
    respaIdsMax.Write(aIdsMax);
    resp.End();
}



THandle DvProviderLinnCoUkRadio1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkRadio1C(aDevice);
}

void DvProviderLinnCoUkRadio1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider);
}

void DvProviderLinnCoUkRadio1EnableActionPlay(THandle aProvider, CallbackRadio1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionPause(THandle aProvider, CallbackRadio1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionPause(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionStop(THandle aProvider, CallbackRadio1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionSeekSecondAbsolute(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionSeekSecondRelative(THandle aProvider, CallbackRadio1SeekSecondRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionSeekSecondRelative(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionChannel(THandle aProvider, CallbackRadio1Channel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionChannel(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionSetChannel(THandle aProvider, CallbackRadio1SetChannel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionSetChannel(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionProtocolInfo(THandle aProvider, CallbackRadio1ProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionProtocolInfo(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionTransportState(THandle aProvider, CallbackRadio1TransportState aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionTransportState(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionId(THandle aProvider, CallbackRadio1Id aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionId(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionSetId(THandle aProvider, CallbackRadio1SetId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionSetId(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionRead(THandle aProvider, CallbackRadio1Read aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionRead(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionReadList(THandle aProvider, CallbackRadio1ReadList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionReadList(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionIdArray(THandle aProvider, CallbackRadio1IdArray aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionIdArray(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionIdArrayChanged(THandle aProvider, CallbackRadio1IdArrayChanged aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionIdArrayChanged(aCallback, aPtr);
}

void DvProviderLinnCoUkRadio1EnableActionIdsMax(THandle aProvider, CallbackRadio1IdsMax aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->EnableActionIdsMax(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkRadio1SetPropertyChannelUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyChannelUri(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyChannelUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyChannelUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkRadio1SetPropertyChannelMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyChannelMetadata(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyChannelMetadata(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyChannelMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkRadio1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyTransportState(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyTransportState(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyTransportState(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkRadio1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyProtocolInfo(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkRadio1SetPropertyId(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyId(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyId(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyId(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkRadio1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyIdArray(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyIdArray(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

int32_t DvProviderLinnCoUkRadio1SetPropertyIdsMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->SetPropertyIdsMax(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkRadio1GetPropertyIdsMax(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkRadio1C*>(aProvider)->GetPropertyIdsMax(val);
    *aValue = val;
}

