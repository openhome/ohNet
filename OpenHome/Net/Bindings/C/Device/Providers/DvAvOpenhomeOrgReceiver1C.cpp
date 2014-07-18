#include "DvAvOpenhomeOrgReceiver1.h"
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

class DvProviderAvOpenhomeOrgReceiver1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgReceiver1C(DvDeviceC aDevice);
    TBool SetPropertyUri(const Brx& aValue);
    void GetPropertyUri(Brhz& aValue);
    TBool SetPropertyMetadata(const Brx& aValue);
    void GetPropertyMetadata(Brhz& aValue);
    TBool SetPropertyTransportState(const Brx& aValue);
    void GetPropertyTransportState(Brhz& aValue);
    TBool SetPropertyProtocolInfo(const Brx& aValue);
    void GetPropertyProtocolInfo(Brhz& aValue);
    void EnablePropertyUri();
    void EnablePropertyMetadata();
    void EnablePropertyTransportState();
    void EnablePropertyProtocolInfo();
    void EnableActionPlay(CallbackReceiver1Play aCallback, void* aPtr);
    void EnableActionStop(CallbackReceiver1Stop aCallback, void* aPtr);
    void EnableActionSetSender(CallbackReceiver1SetSender aCallback, void* aPtr);
    void EnableActionSender(CallbackReceiver1Sender aCallback, void* aPtr);
    void EnableActionProtocolInfo(CallbackReceiver1ProtocolInfo aCallback, void* aPtr);
    void EnableActionTransportState(CallbackReceiver1TransportState aCallback, void* aPtr);
private:
    void DoPlay(IDviInvocation& aInvocation);
    void DoStop(IDviInvocation& aInvocation);
    void DoSetSender(IDviInvocation& aInvocation);
    void DoSender(IDviInvocation& aInvocation);
    void DoProtocolInfo(IDviInvocation& aInvocation);
    void DoTransportState(IDviInvocation& aInvocation);
private:
    CallbackReceiver1Play iCallbackPlay;
    void* iPtrPlay;
    CallbackReceiver1Stop iCallbackStop;
    void* iPtrStop;
    CallbackReceiver1SetSender iCallbackSetSender;
    void* iPtrSetSender;
    CallbackReceiver1Sender iCallbackSender;
    void* iPtrSender;
    CallbackReceiver1ProtocolInfo iCallbackProtocolInfo;
    void* iPtrProtocolInfo;
    CallbackReceiver1TransportState iCallbackTransportState;
    void* iPtrTransportState;
    PropertyString* iPropertyUri;
    PropertyString* iPropertyMetadata;
    PropertyString* iPropertyTransportState;
    PropertyString* iPropertyProtocolInfo;
};

DvProviderAvOpenhomeOrgReceiver1C::DvProviderAvOpenhomeOrgReceiver1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "Receiver", 1)
{
    iPropertyUri = NULL;
    iPropertyMetadata = NULL;
    iPropertyTransportState = NULL;
    iPropertyProtocolInfo = NULL;
}

TBool DvProviderAvOpenhomeOrgReceiver1C::SetPropertyUri(const Brx& aValue)
{
    ASSERT(iPropertyUri != NULL);
    return SetPropertyString(*iPropertyUri, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1C::GetPropertyUri(Brhz& aValue)
{
    ASSERT(iPropertyUri != NULL);
    aValue.Set(iPropertyUri->Value());
}

TBool DvProviderAvOpenhomeOrgReceiver1C::SetPropertyMetadata(const Brx& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1C::GetPropertyMetadata(Brhz& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgReceiver1C::SetPropertyTransportState(const Brx& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1C::GetPropertyTransportState(Brhz& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    aValue.Set(iPropertyTransportState->Value());
}

TBool DvProviderAvOpenhomeOrgReceiver1C::SetPropertyProtocolInfo(const Brx& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    return SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1C::GetPropertyProtocolInfo(Brhz& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    aValue.Set(iPropertyProtocolInfo->Value());
}

void DvProviderAvOpenhomeOrgReceiver1C::EnablePropertyUri()
{
    iPropertyUri = new PropertyString(iDvStack.Env(), new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
}

void DvProviderAvOpenhomeOrgReceiver1C::EnablePropertyMetadata()
{
    iPropertyMetadata = new PropertyString(iDvStack.Env(), new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
}

void DvProviderAvOpenhomeOrgReceiver1C::EnablePropertyTransportState()
{
    TChar** allowedValues;
    TUint index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Waiting";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(iDvStack.Env(), new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
}

void DvProviderAvOpenhomeOrgReceiver1C::EnablePropertyProtocolInfo()
{
    iPropertyProtocolInfo = new PropertyString(iDvStack.Env(), new ParameterString("ProtocolInfo"));
    iService->AddProperty(iPropertyProtocolInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionPlay(CallbackReceiver1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionStop(CallbackReceiver1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionSetSender(CallbackReceiver1SetSender aCallback, void* aPtr)
{
    iCallbackSetSender = aCallback;
    iPtrSetSender = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSender");
    action->AddInputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddInputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoSetSender);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionSender(CallbackReceiver1Sender aCallback, void* aPtr)
{
    iCallbackSender = aCallback;
    iPtrSender = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Sender");
    action->AddOutputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoSender);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionProtocolInfo(CallbackReceiver1ProtocolInfo aCallback, void* aPtr)
{
    iCallbackProtocolInfo = aCallback;
    iPtrProtocolInfo = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionTransportState(CallbackReceiver1TransportState aCallback, void* aPtr)
{
    iCallbackTransportState = aCallback;
    iPtrTransportState = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::DoPlay(IDviInvocation& aInvocation)
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

void DvProviderAvOpenhomeOrgReceiver1C::DoStop(IDviInvocation& aInvocation)
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

void DvProviderAvOpenhomeOrgReceiver1C::DoSetSender(IDviInvocation& aInvocation)
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
    ASSERT(iCallbackSetSender != NULL);
    if (0 != iCallbackSetSender(iPtrSetSender, invocationC, invocationCPtr, (const char*)Uri.Ptr(), (const char*)Metadata.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgReceiver1C::DoSender(IDviInvocation& aInvocation)
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
    ASSERT(iCallbackSender != NULL);
    if (0 != iCallbackSender(iPtrSender, invocationC, invocationCPtr, &Uri, &Metadata)) {
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

void DvProviderAvOpenhomeOrgReceiver1C::DoProtocolInfo(IDviInvocation& aInvocation)
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

void DvProviderAvOpenhomeOrgReceiver1C::DoTransportState(IDviInvocation& aInvocation)
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



THandle STDCALL DvProviderAvOpenhomeOrgReceiver1Create(DvDeviceC aDevice)
{
    return new DvProviderAvOpenhomeOrgReceiver1C(aDevice);
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider);
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionPlay(THandle aProvider, CallbackReceiver1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionStop(THandle aProvider, CallbackReceiver1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionSetSender(THandle aProvider, CallbackReceiver1SetSender aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionSetSender(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionSender(THandle aProvider, CallbackReceiver1Sender aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionSender(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionProtocolInfo(THandle aProvider, CallbackReceiver1ProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionProtocolInfo(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionTransportState(THandle aProvider, CallbackReceiver1TransportState aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionTransportState(aCallback, aPtr);
}

int32_t STDCALL DvProviderAvOpenhomeOrgReceiver1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->SetPropertyUri(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1GetPropertyUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->GetPropertyUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgReceiver1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->SetPropertyMetadata(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1GetPropertyMetadata(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->GetPropertyMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgReceiver1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->SetPropertyTransportState(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1GetPropertyTransportState(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->GetPropertyTransportState(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgReceiver1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->SetPropertyProtocolInfo(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1GetPropertyProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->GetPropertyProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1EnablePropertyUri(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnablePropertyUri();
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1EnablePropertyMetadata(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnablePropertyMetadata();
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1EnablePropertyTransportState(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnablePropertyTransportState();
}

void STDCALL DvProviderAvOpenhomeOrgReceiver1EnablePropertyProtocolInfo(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnablePropertyProtocolInfo();
}

