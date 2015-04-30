#include "DvAvOpenhomeOrgSender1.h"
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

class DvProviderAvOpenhomeOrgSender1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgSender1C(DvDeviceC aDevice);
    TBool SetPropertyPresentationUrl(const Brx& aValue);
    void GetPropertyPresentationUrl(Brhz& aValue);
    TBool SetPropertyMetadata(const Brx& aValue);
    void GetPropertyMetadata(Brhz& aValue);
    TBool SetPropertyAudio(TBool aValue);
    void GetPropertyAudio(TBool& aValue);
    TBool SetPropertyStatus(const Brx& aValue);
    void GetPropertyStatus(Brhz& aValue);
    TBool SetPropertyAttributes(const Brx& aValue);
    void GetPropertyAttributes(Brhz& aValue);
    void EnablePropertyPresentationUrl();
    void EnablePropertyMetadata();
    void EnablePropertyAudio();
    void EnablePropertyStatus();
    void EnablePropertyAttributes();
    void EnableActionPresentationUrl(CallbackSender1PresentationUrl aCallback, void* aPtr);
    void EnableActionMetadata(CallbackSender1Metadata aCallback, void* aPtr);
    void EnableActionAudio(CallbackSender1Audio aCallback, void* aPtr);
    void EnableActionStatus(CallbackSender1Status aCallback, void* aPtr);
    void EnableActionAttributes(CallbackSender1Attributes aCallback, void* aPtr);
private:
    void DoPresentationUrl(IDviInvocation& aInvocation);
    void DoMetadata(IDviInvocation& aInvocation);
    void DoAudio(IDviInvocation& aInvocation);
    void DoStatus(IDviInvocation& aInvocation);
    void DoAttributes(IDviInvocation& aInvocation);
private:
    CallbackSender1PresentationUrl iCallbackPresentationUrl;
    void* iPtrPresentationUrl;
    CallbackSender1Metadata iCallbackMetadata;
    void* iPtrMetadata;
    CallbackSender1Audio iCallbackAudio;
    void* iPtrAudio;
    CallbackSender1Status iCallbackStatus;
    void* iPtrStatus;
    CallbackSender1Attributes iCallbackAttributes;
    void* iPtrAttributes;
    PropertyString* iPropertyPresentationUrl;
    PropertyString* iPropertyMetadata;
    PropertyBool* iPropertyAudio;
    PropertyString* iPropertyStatus;
    PropertyString* iPropertyAttributes;
};

DvProviderAvOpenhomeOrgSender1C::DvProviderAvOpenhomeOrgSender1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "Sender", 1)
{
    iPropertyPresentationUrl = NULL;
    iPropertyMetadata = NULL;
    iPropertyAudio = NULL;
    iPropertyStatus = NULL;
    iPropertyAttributes = NULL;
}

TBool DvProviderAvOpenhomeOrgSender1C::SetPropertyPresentationUrl(const Brx& aValue)
{
    ASSERT(iPropertyPresentationUrl != NULL);
    return SetPropertyString(*iPropertyPresentationUrl, aValue);
}

void DvProviderAvOpenhomeOrgSender1C::GetPropertyPresentationUrl(Brhz& aValue)
{
    ASSERT(iPropertyPresentationUrl != NULL);
    aValue.Set(iPropertyPresentationUrl->Value());
}

TBool DvProviderAvOpenhomeOrgSender1C::SetPropertyMetadata(const Brx& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgSender1C::GetPropertyMetadata(Brhz& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgSender1C::SetPropertyAudio(TBool aValue)
{
    ASSERT(iPropertyAudio != NULL);
    return SetPropertyBool(*iPropertyAudio, aValue);
}

void DvProviderAvOpenhomeOrgSender1C::GetPropertyAudio(TBool& aValue)
{
    ASSERT(iPropertyAudio != NULL);
    aValue = iPropertyAudio->Value();
}

TBool DvProviderAvOpenhomeOrgSender1C::SetPropertyStatus(const Brx& aValue)
{
    ASSERT(iPropertyStatus != NULL);
    return SetPropertyString(*iPropertyStatus, aValue);
}

void DvProviderAvOpenhomeOrgSender1C::GetPropertyStatus(Brhz& aValue)
{
    ASSERT(iPropertyStatus != NULL);
    aValue.Set(iPropertyStatus->Value());
}

TBool DvProviderAvOpenhomeOrgSender1C::SetPropertyAttributes(const Brx& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    return SetPropertyString(*iPropertyAttributes, aValue);
}

void DvProviderAvOpenhomeOrgSender1C::GetPropertyAttributes(Brhz& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    aValue.Set(iPropertyAttributes->Value());
}

void DvProviderAvOpenhomeOrgSender1C::EnablePropertyPresentationUrl()
{
    iPropertyPresentationUrl = new PropertyString(new ParameterString("PresentationUrl"));
    iService->AddProperty(iPropertyPresentationUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgSender1C::EnablePropertyMetadata()
{
    iPropertyMetadata = new PropertyString(new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
}

void DvProviderAvOpenhomeOrgSender1C::EnablePropertyAudio()
{
    iPropertyAudio = new PropertyBool(new ParameterBool("Audio"));
    iService->AddProperty(iPropertyAudio); // passes ownership
}

void DvProviderAvOpenhomeOrgSender1C::EnablePropertyStatus()
{
    TChar** allowedValues;
    TUint index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"Enabled";
    allowedValues[index++] = (TChar*)"Disabled";
    allowedValues[index++] = (TChar*)"Blocked";
    iPropertyStatus = new PropertyString(new ParameterString("Status", allowedValues, 3));
    delete[] allowedValues;
    iService->AddProperty(iPropertyStatus); // passes ownership
}

void DvProviderAvOpenhomeOrgSender1C::EnablePropertyAttributes()
{
    iPropertyAttributes = new PropertyString(new ParameterString("Attributes"));
    iService->AddProperty(iPropertyAttributes); // passes ownership
}

void DvProviderAvOpenhomeOrgSender1C::EnableActionPresentationUrl(CallbackSender1PresentationUrl aCallback, void* aPtr)
{
    iCallbackPresentationUrl = aCallback;
    iPtrPresentationUrl = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PresentationUrl");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyPresentationUrl));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1C::DoPresentationUrl);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1C::EnableActionMetadata(CallbackSender1Metadata aCallback, void* aPtr)
{
    iCallbackMetadata = aCallback;
    iPtrMetadata = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Metadata");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1C::DoMetadata);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1C::EnableActionAudio(CallbackSender1Audio aCallback, void* aPtr)
{
    iCallbackAudio = aCallback;
    iPtrAudio = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Audio");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAudio));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1C::DoAudio);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1C::EnableActionStatus(CallbackSender1Status aCallback, void* aPtr)
{
    iCallbackStatus = aCallback;
    iPtrStatus = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Status");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyStatus));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1C::DoStatus);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1C::EnableActionAttributes(CallbackSender1Attributes aCallback, void* aPtr)
{
    iCallbackAttributes = aCallback;
    iPtrAttributes = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Attributes");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAttributes));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1C::DoAttributes);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1C::DoPresentationUrl(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Value;
    ASSERT(iCallbackPresentationUrl != NULL);
    if (0 != iCallbackPresentationUrl(iPtrPresentationUrl, invocationC, invocationCPtr, &Value)) {
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

void DvProviderAvOpenhomeOrgSender1C::DoMetadata(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Value;
    ASSERT(iCallbackMetadata != NULL);
    if (0 != iCallbackMetadata(iPtrMetadata, invocationC, invocationCPtr, &Value)) {
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

void DvProviderAvOpenhomeOrgSender1C::DoAudio(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackAudio != NULL);
    if (0 != iCallbackAudio(iPtrAudio, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write((Value!=0));
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgSender1C::DoStatus(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Value;
    ASSERT(iCallbackStatus != NULL);
    if (0 != iCallbackStatus(iPtrStatus, invocationC, invocationCPtr, &Value)) {
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

void DvProviderAvOpenhomeOrgSender1C::DoAttributes(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Value;
    ASSERT(iCallbackAttributes != NULL);
    if (0 != iCallbackAttributes(iPtrAttributes, invocationC, invocationCPtr, &Value)) {
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



THandle STDCALL DvProviderAvOpenhomeOrgSender1Create(DvDeviceC aDevice)
{
    return new DvProviderAvOpenhomeOrgSender1C(aDevice);
}

void STDCALL DvProviderAvOpenhomeOrgSender1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider);
}

void STDCALL DvProviderAvOpenhomeOrgSender1EnableActionPresentationUrl(THandle aProvider, CallbackSender1PresentationUrl aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->EnableActionPresentationUrl(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgSender1EnableActionMetadata(THandle aProvider, CallbackSender1Metadata aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->EnableActionMetadata(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgSender1EnableActionAudio(THandle aProvider, CallbackSender1Audio aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->EnableActionAudio(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgSender1EnableActionStatus(THandle aProvider, CallbackSender1Status aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->EnableActionStatus(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgSender1EnableActionAttributes(THandle aProvider, CallbackSender1Attributes aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->EnableActionAttributes(aCallback, aPtr);
}

int32_t STDCALL DvProviderAvOpenhomeOrgSender1SetPropertyPresentationUrl(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->SetPropertyPresentationUrl(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgSender1GetPropertyPresentationUrl(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->GetPropertyPresentationUrl(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgSender1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->SetPropertyMetadata(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgSender1GetPropertyMetadata(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->GetPropertyMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgSender1SetPropertyAudio(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->SetPropertyAudio((aValue!=0))? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgSender1GetPropertyAudio(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->GetPropertyAudio(val);
    *aValue = (val? 1 : 0);
}

int32_t STDCALL DvProviderAvOpenhomeOrgSender1SetPropertyStatus(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->SetPropertyStatus(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgSender1GetPropertyStatus(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->GetPropertyStatus(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgSender1SetPropertyAttributes(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->SetPropertyAttributes(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgSender1GetPropertyAttributes(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->GetPropertyAttributes(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderAvOpenhomeOrgSender1EnablePropertyPresentationUrl(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->EnablePropertyPresentationUrl();
}

void STDCALL DvProviderAvOpenhomeOrgSender1EnablePropertyMetadata(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->EnablePropertyMetadata();
}

void STDCALL DvProviderAvOpenhomeOrgSender1EnablePropertyAudio(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->EnablePropertyAudio();
}

void STDCALL DvProviderAvOpenhomeOrgSender1EnablePropertyStatus(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->EnablePropertyStatus();
}

void STDCALL DvProviderAvOpenhomeOrgSender1EnablePropertyAttributes(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgSender1C*>(aProvider)->EnablePropertyAttributes();
}

