#include "DvAvOpenhomeOrgRadio1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
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
    void EnablePropertyUri();
    void EnablePropertyMetadata();
    void EnablePropertyTransportState();
    void EnablePropertyId();
    void EnablePropertyIdArray();
    void EnablePropertyChannelsMax();
    void EnablePropertyProtocolInfo();
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
    void DoPlay(IDviInvocation& aInvocation);
    void DoPause(IDviInvocation& aInvocation);
    void DoStop(IDviInvocation& aInvocation);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation);
    void DoSeekSecondRelative(IDviInvocation& aInvocation);
    void DoChannel(IDviInvocation& aInvocation);
    void DoSetChannel(IDviInvocation& aInvocation);
    void DoTransportState(IDviInvocation& aInvocation);
    void DoId(IDviInvocation& aInvocation);
    void DoSetId(IDviInvocation& aInvocation);
    void DoRead(IDviInvocation& aInvocation);
    void DoReadList(IDviInvocation& aInvocation);
    void DoIdArray(IDviInvocation& aInvocation);
    void DoIdArrayChanged(IDviInvocation& aInvocation);
    void DoChannelsMax(IDviInvocation& aInvocation);
    void DoProtocolInfo(IDviInvocation& aInvocation);
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
    iPropertyUri = NULL;
    iPropertyMetadata = NULL;
    iPropertyTransportState = NULL;
    iPropertyId = NULL;
    iPropertyIdArray = NULL;
    iPropertyChannelsMax = NULL;
    iPropertyProtocolInfo = NULL;
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyUri(const Brx& aValue)
{
    ASSERT(iPropertyUri != NULL);
    return SetPropertyString(*iPropertyUri, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyUri(Brhz& aValue)
{
    ASSERT(iPropertyUri != NULL);
    aValue.Set(iPropertyUri->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyMetadata(const Brx& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyMetadata(Brhz& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyTransportState(const Brx& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyTransportState(Brhz& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    aValue.Set(iPropertyTransportState->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyId(TUint aValue)
{
    ASSERT(iPropertyId != NULL);
    return SetPropertyUint(*iPropertyId, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyId(TUint& aValue)
{
    ASSERT(iPropertyId != NULL);
    aValue = iPropertyId->Value();
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyIdArray(const Brx& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyIdArray(Brh& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyChannelsMax(TUint aValue)
{
    ASSERT(iPropertyChannelsMax != NULL);
    return SetPropertyUint(*iPropertyChannelsMax, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyChannelsMax(TUint& aValue)
{
    ASSERT(iPropertyChannelsMax != NULL);
    aValue = iPropertyChannelsMax->Value();
}

TBool DvProviderAvOpenhomeOrgRadio1C::SetPropertyProtocolInfo(const Brx& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    return SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvProviderAvOpenhomeOrgRadio1C::GetPropertyProtocolInfo(Brhz& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    aValue.Set(iPropertyProtocolInfo->Value());
}

void DvProviderAvOpenhomeOrgRadio1C::EnablePropertyUri()
{
    iPropertyUri = new PropertyString(iDvStack.Env(), new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1C::EnablePropertyMetadata()
{
    iPropertyMetadata = new PropertyString(iDvStack.Env(), new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1C::EnablePropertyTransportState()
{
    TChar** allowedValues;
    TUint index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(iDvStack.Env(), new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1C::EnablePropertyId()
{
    iPropertyId = new PropertyUint(iDvStack.Env(), new ParameterUint("Id"));
    iService->AddProperty(iPropertyId); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1C::EnablePropertyIdArray()
{
    iPropertyIdArray = new PropertyBinary(iDvStack.Env(), new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1C::EnablePropertyChannelsMax()
{
    iPropertyChannelsMax = new PropertyUint(iDvStack.Env(), new ParameterUint("ChannelsMax"));
    iService->AddProperty(iPropertyChannelsMax); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1C::EnablePropertyProtocolInfo()
{
    iPropertyProtocolInfo = new PropertyString(iDvStack.Env(), new ParameterString("ProtocolInfo"));
    iService->AddProperty(iPropertyProtocolInfo); // passes ownership
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

void DvProviderAvOpenhomeOrgRadio1C::DoPlay(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoPause(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoStop(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoSeekSecondAbsolute(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSeekSecondAbsolute != NULL);
    if (0 != iCallbackSeekSecondAbsolute(iPtrSeekSecondAbsolute, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoSeekSecondRelative(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSeekSecondRelative != NULL);
    if (0 != iCallbackSeekSecondRelative(iPtrSeekSecondRelative, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoChannel(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Uri;
    char* Metadata;
    ASSERT(iCallbackChannel != NULL);
    if (0 != iCallbackChannel(iPtrChannel, invocationC, invocationCPtr, &Uri, &Metadata)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respUri(aInvocation, "Uri");
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    invocation.StartResponse();
    Brhz bufUri((const TChar*)Uri);
    OhNetFreeExternal(Uri);
    respUri.Write(bufUri);
    respUri.WriteFlush();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoSetChannel(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz Uri;
    aInvocation.InvocationReadString("Uri", Uri);
    Brhz Metadata;
    aInvocation.InvocationReadString("Metadata", Metadata);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetChannel != NULL);
    if (0 != iCallbackSetChannel(iPtrSetChannel, invocationC, invocationCPtr, (const char*)Uri.Ptr(), (const char*)Metadata.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoTransportState(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Value;
    ASSERT(iCallbackTransportState != NULL);
    if (0 != iCallbackTransportState(iPtrTransportState, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respValue(aInvocation, "Value");
    invocation.StartResponse();
    Brhz bufValue((const TChar*)Value);
    OhNetFreeExternal(Value);
    respValue.Write(bufValue);
    respValue.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoId(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackId != NULL);
    if (0 != iCallbackId(iPtrId, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoSetId(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    Brhz Uri;
    aInvocation.InvocationReadString("Uri", Uri);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetId != NULL);
    if (0 != iCallbackSetId(iPtrSetId, invocationC, invocationCPtr, Value, (const char*)Uri.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoRead(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Metadata;
    ASSERT(iCallbackRead != NULL);
    if (0 != iCallbackRead(iPtrRead, invocationC, invocationCPtr, Id, &Metadata)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    invocation.StartResponse();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoReadList(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz IdList;
    aInvocation.InvocationReadString("IdList", IdList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* ChannelList;
    ASSERT(iCallbackReadList != NULL);
    if (0 != iCallbackReadList(iPtrReadList, invocationC, invocationCPtr, (const char*)IdList.Ptr(), &ChannelList)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respChannelList(aInvocation, "ChannelList");
    invocation.StartResponse();
    Brhz bufChannelList((const TChar*)ChannelList);
    OhNetFreeExternal(ChannelList);
    respChannelList.Write(bufChannelList);
    respChannelList.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoIdArray(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Token;
    char* Array;
    uint32_t ArrayLen;
    ASSERT(iCallbackIdArray != NULL);
    if (0 != iCallbackIdArray(iPtrIdArray, invocationC, invocationCPtr, &Token, &Array, &ArrayLen)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respToken(aInvocation, "Token");
    DviInvocationResponseBinary respArray(aInvocation, "Array");
    invocation.StartResponse();
    respToken.Write(Token);
    Brh bufArray;
    bufArray.Set((const TByte*)Array, ArrayLen);
    OhNetFreeExternal(Array);
    respArray.Write(bufArray);
    respArray.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoIdArrayChanged(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackIdArrayChanged != NULL);
    if (0 != iCallbackIdArrayChanged(iPtrIdArrayChanged, invocationC, invocationCPtr, Token, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write((Value!=0));
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoChannelsMax(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackChannelsMax != NULL);
    if (0 != iCallbackChannelsMax(iPtrChannelsMax, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgRadio1C::DoProtocolInfo(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Value;
    ASSERT(iCallbackProtocolInfo != NULL);
    if (0 != iCallbackProtocolInfo(iPtrProtocolInfo, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respValue(aInvocation, "Value");
    invocation.StartResponse();
    Brhz bufValue((const TChar*)Value);
    OhNetFreeExternal(Value);
    respValue.Write(bufValue);
    respValue.WriteFlush();
    invocation.EndResponse();
}



THandle STDCALL DvProviderAvOpenhomeOrgRadio1Create(DvDeviceC aDevice)
{
    return new DvProviderAvOpenhomeOrgRadio1C(aDevice);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionPlay(THandle aProvider, CallbackRadio1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionPause(THandle aProvider, CallbackRadio1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionPause(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionStop(THandle aProvider, CallbackRadio1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionSeekSecondAbsolute(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionSeekSecondRelative(THandle aProvider, CallbackRadio1SeekSecondRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionSeekSecondRelative(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionChannel(THandle aProvider, CallbackRadio1Channel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionChannel(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionSetChannel(THandle aProvider, CallbackRadio1SetChannel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionSetChannel(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionTransportState(THandle aProvider, CallbackRadio1TransportState aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionTransportState(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionId(THandle aProvider, CallbackRadio1Id aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionId(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionSetId(THandle aProvider, CallbackRadio1SetId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionSetId(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionRead(THandle aProvider, CallbackRadio1Read aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionRead(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionReadList(THandle aProvider, CallbackRadio1ReadList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionReadList(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionIdArray(THandle aProvider, CallbackRadio1IdArray aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionIdArray(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionIdArrayChanged(THandle aProvider, CallbackRadio1IdArrayChanged aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionIdArrayChanged(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionChannelsMax(THandle aProvider, CallbackRadio1ChannelsMax aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionChannelsMax(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionProtocolInfo(THandle aProvider, CallbackRadio1ProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnableActionProtocolInfo(aCallback, aPtr);
}

int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyUri(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyMetadata(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyMetadata(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyTransportState(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyTransportState(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyTransportState(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyId(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyId(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyId(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyId(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyIdArray(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyIdArray(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyChannelsMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyChannelsMax(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyChannelsMax(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyChannelsMax(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->SetPropertyProtocolInfo(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->GetPropertyProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyUri(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnablePropertyUri();
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyMetadata(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnablePropertyMetadata();
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyTransportState(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnablePropertyTransportState();
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyId(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnablePropertyId();
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyIdArray(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnablePropertyIdArray();
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyChannelsMax(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnablePropertyChannelsMax();
}

void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyProtocolInfo(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgRadio1C*>(aProvider)->EnablePropertyProtocolInfo();
}

