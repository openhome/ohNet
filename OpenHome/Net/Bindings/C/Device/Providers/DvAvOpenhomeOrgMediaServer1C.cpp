#include "DvAvOpenhomeOrgMediaServer1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderAvOpenhomeOrgMediaServer1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgMediaServer1C(DvDeviceC aDevice);
    TBool SetPropertyManufacturerName(const Brx& aValue);
    void GetPropertyManufacturerName(Brhz& aValue);
    TBool SetPropertyManufacturerInfo(const Brx& aValue);
    void GetPropertyManufacturerInfo(Brhz& aValue);
    TBool SetPropertyManufacturerUrl(const Brx& aValue);
    void GetPropertyManufacturerUrl(Brhz& aValue);
    TBool SetPropertyManufacturerImageUri(const Brx& aValue);
    void GetPropertyManufacturerImageUri(Brhz& aValue);
    TBool SetPropertyModelName(const Brx& aValue);
    void GetPropertyModelName(Brhz& aValue);
    TBool SetPropertyModelInfo(const Brx& aValue);
    void GetPropertyModelInfo(Brhz& aValue);
    TBool SetPropertyModelUrl(const Brx& aValue);
    void GetPropertyModelUrl(Brhz& aValue);
    TBool SetPropertyModelImageUri(const Brx& aValue);
    void GetPropertyModelImageUri(Brhz& aValue);
    TBool SetPropertyProductName(const Brx& aValue);
    void GetPropertyProductName(Brhz& aValue);
    TBool SetPropertyProductInfo(const Brx& aValue);
    void GetPropertyProductInfo(Brhz& aValue);
    TBool SetPropertyProductUrl(const Brx& aValue);
    void GetPropertyProductUrl(Brhz& aValue);
    TBool SetPropertyProductImageUri(const Brx& aValue);
    void GetPropertyProductImageUri(Brhz& aValue);
    TBool SetPropertyAttributes(const Brx& aValue);
    void GetPropertyAttributes(Brhz& aValue);
    void EnableActionManufacturer(CallbackMediaServer1Manufacturer aCallback, void* aPtr);
    void EnableActionModel(CallbackMediaServer1Model aCallback, void* aPtr);
    void EnableActionProduct(CallbackMediaServer1Product aCallback, void* aPtr);
    void EnableActionAttributes(CallbackMediaServer1Attributes aCallback, void* aPtr);
    void EnableActionQuery(CallbackMediaServer1Query aCallback, void* aPtr);
private:
    void DoManufacturer(IDviInvocation& aInvocation);
    void DoModel(IDviInvocation& aInvocation);
    void DoProduct(IDviInvocation& aInvocation);
    void DoAttributes(IDviInvocation& aInvocation);
    void DoQuery(IDviInvocation& aInvocation);
private:
    CallbackMediaServer1Manufacturer iCallbackManufacturer;
    void* iPtrManufacturer;
    CallbackMediaServer1Model iCallbackModel;
    void* iPtrModel;
    CallbackMediaServer1Product iCallbackProduct;
    void* iPtrProduct;
    CallbackMediaServer1Attributes iCallbackAttributes;
    void* iPtrAttributes;
    CallbackMediaServer1Query iCallbackQuery;
    void* iPtrQuery;
    PropertyString* iPropertyManufacturerName;
    PropertyString* iPropertyManufacturerInfo;
    PropertyString* iPropertyManufacturerUrl;
    PropertyString* iPropertyManufacturerImageUri;
    PropertyString* iPropertyModelName;
    PropertyString* iPropertyModelInfo;
    PropertyString* iPropertyModelUrl;
    PropertyString* iPropertyModelImageUri;
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductInfo;
    PropertyString* iPropertyProductUrl;
    PropertyString* iPropertyProductImageUri;
    PropertyString* iPropertyAttributes;
};

DvProviderAvOpenhomeOrgMediaServer1C::DvProviderAvOpenhomeOrgMediaServer1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "MediaServer", 1)
{
    
    iPropertyManufacturerName = new PropertyString(new ParameterString("ManufacturerName"));
    iService->AddProperty(iPropertyManufacturerName); // passes ownership
    iPropertyManufacturerInfo = new PropertyString(new ParameterString("ManufacturerInfo"));
    iService->AddProperty(iPropertyManufacturerInfo); // passes ownership
    iPropertyManufacturerUrl = new PropertyString(new ParameterString("ManufacturerUrl"));
    iService->AddProperty(iPropertyManufacturerUrl); // passes ownership
    iPropertyManufacturerImageUri = new PropertyString(new ParameterString("ManufacturerImageUri"));
    iService->AddProperty(iPropertyManufacturerImageUri); // passes ownership
    iPropertyModelName = new PropertyString(new ParameterString("ModelName"));
    iService->AddProperty(iPropertyModelName); // passes ownership
    iPropertyModelInfo = new PropertyString(new ParameterString("ModelInfo"));
    iService->AddProperty(iPropertyModelInfo); // passes ownership
    iPropertyModelUrl = new PropertyString(new ParameterString("ModelUrl"));
    iService->AddProperty(iPropertyModelUrl); // passes ownership
    iPropertyModelImageUri = new PropertyString(new ParameterString("ModelImageUri"));
    iService->AddProperty(iPropertyModelImageUri); // passes ownership
    iPropertyProductName = new PropertyString(new ParameterString("ProductName"));
    iService->AddProperty(iPropertyProductName); // passes ownership
    iPropertyProductInfo = new PropertyString(new ParameterString("ProductInfo"));
    iService->AddProperty(iPropertyProductInfo); // passes ownership
    iPropertyProductUrl = new PropertyString(new ParameterString("ProductUrl"));
    iService->AddProperty(iPropertyProductUrl); // passes ownership
    iPropertyProductImageUri = new PropertyString(new ParameterString("ProductImageUri"));
    iService->AddProperty(iPropertyProductImageUri); // passes ownership
    iPropertyAttributes = new PropertyString(new ParameterString("Attributes"));
    iService->AddProperty(iPropertyAttributes); // passes ownership
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyManufacturerName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyManufacturerName(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyManufacturerInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyManufacturerInfo(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyManufacturerUrl(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyManufacturerUrl(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyManufacturerImageUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyManufacturerImageUri(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyModelName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyModelName(Brhz& aValue)
{
    aValue.Set(iPropertyModelName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyModelInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyModelInfo(Brhz& aValue)
{
    aValue.Set(iPropertyModelInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyModelUrl(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyModelUrl(Brhz& aValue)
{
    aValue.Set(iPropertyModelUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyModelImageUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyModelImageUri(Brhz& aValue)
{
    aValue.Set(iPropertyModelImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyProductName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyProductName(Brhz& aValue)
{
    aValue.Set(iPropertyProductName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyProductInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyProductInfo(Brhz& aValue)
{
    aValue.Set(iPropertyProductInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyProductUrl(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyProductUrl(Brhz& aValue)
{
    aValue.Set(iPropertyProductUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyProductImageUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyProductImageUri(Brhz& aValue)
{
    aValue.Set(iPropertyProductImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyAttributes(const Brx& aValue)
{
    return SetPropertyString(*iPropertyAttributes, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyAttributes(Brhz& aValue)
{
    aValue.Set(iPropertyAttributes->Value());
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnableActionManufacturer(CallbackMediaServer1Manufacturer aCallback, void* aPtr)
{
    iCallbackManufacturer = aCallback;
    iPtrManufacturer = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Manufacturer");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyManufacturerName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyManufacturerInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyManufacturerUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyManufacturerImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1C::DoManufacturer);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnableActionModel(CallbackMediaServer1Model aCallback, void* aPtr)
{
    iCallbackModel = aCallback;
    iPtrModel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Model");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyModelName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyModelInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyModelUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyModelImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1C::DoModel);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnableActionProduct(CallbackMediaServer1Product aCallback, void* aPtr)
{
    iCallbackProduct = aCallback;
    iPtrProduct = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Product");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyProductName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyProductInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyProductUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyProductImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1C::DoProduct);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnableActionAttributes(CallbackMediaServer1Attributes aCallback, void* aPtr)
{
    iCallbackAttributes = aCallback;
    iPtrAttributes = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Attributes");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAttributes));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1C::DoAttributes);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnableActionQuery(CallbackMediaServer1Query aCallback, void* aPtr)
{
    iCallbackQuery = aCallback;
    iPtrQuery = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Query");
    action->AddInputParameter(new ParameterString("Request"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1C::DoQuery);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1C::DoManufacturer(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Name;
    char* Info;
    char* Url;
    char* ImageUri;
    ASSERT(iCallbackManufacturer != NULL);
    if (0 != iCallbackManufacturer(iPtrManufacturer, invocationC, invocationCPtr, &Name, &Info, &Url, &ImageUri)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respInfo(aInvocation, "Info");
    DviInvocationResponseString respUrl(aInvocation, "Url");
    DviInvocationResponseString respImageUri(aInvocation, "ImageUri");
    invocation.StartResponse();
    Brhz bufName((const TChar*)Name);
    OhNetFreeExternal(Name);
    respName.Write(bufName);
    respName.WriteFlush();
    Brhz bufInfo((const TChar*)Info);
    OhNetFreeExternal(Info);
    respInfo.Write(bufInfo);
    respInfo.WriteFlush();
    Brhz bufUrl((const TChar*)Url);
    OhNetFreeExternal(Url);
    respUrl.Write(bufUrl);
    respUrl.WriteFlush();
    Brhz bufImageUri((const TChar*)ImageUri);
    OhNetFreeExternal(ImageUri);
    respImageUri.Write(bufImageUri);
    respImageUri.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgMediaServer1C::DoModel(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Name;
    char* Info;
    char* Url;
    char* ImageUri;
    ASSERT(iCallbackModel != NULL);
    if (0 != iCallbackModel(iPtrModel, invocationC, invocationCPtr, &Name, &Info, &Url, &ImageUri)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respInfo(aInvocation, "Info");
    DviInvocationResponseString respUrl(aInvocation, "Url");
    DviInvocationResponseString respImageUri(aInvocation, "ImageUri");
    invocation.StartResponse();
    Brhz bufName((const TChar*)Name);
    OhNetFreeExternal(Name);
    respName.Write(bufName);
    respName.WriteFlush();
    Brhz bufInfo((const TChar*)Info);
    OhNetFreeExternal(Info);
    respInfo.Write(bufInfo);
    respInfo.WriteFlush();
    Brhz bufUrl((const TChar*)Url);
    OhNetFreeExternal(Url);
    respUrl.Write(bufUrl);
    respUrl.WriteFlush();
    Brhz bufImageUri((const TChar*)ImageUri);
    OhNetFreeExternal(ImageUri);
    respImageUri.Write(bufImageUri);
    respImageUri.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgMediaServer1C::DoProduct(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Name;
    char* Info;
    char* Url;
    char* ImageUri;
    ASSERT(iCallbackProduct != NULL);
    if (0 != iCallbackProduct(iPtrProduct, invocationC, invocationCPtr, &Name, &Info, &Url, &ImageUri)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respInfo(aInvocation, "Info");
    DviInvocationResponseString respUrl(aInvocation, "Url");
    DviInvocationResponseString respImageUri(aInvocation, "ImageUri");
    invocation.StartResponse();
    Brhz bufName((const TChar*)Name);
    OhNetFreeExternal(Name);
    respName.Write(bufName);
    respName.WriteFlush();
    Brhz bufInfo((const TChar*)Info);
    OhNetFreeExternal(Info);
    respInfo.Write(bufInfo);
    respInfo.WriteFlush();
    Brhz bufUrl((const TChar*)Url);
    OhNetFreeExternal(Url);
    respUrl.Write(bufUrl);
    respUrl.WriteFlush();
    Brhz bufImageUri((const TChar*)ImageUri);
    OhNetFreeExternal(ImageUri);
    respImageUri.Write(bufImageUri);
    respImageUri.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgMediaServer1C::DoAttributes(IDviInvocation& aInvocation)
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

void DvProviderAvOpenhomeOrgMediaServer1C::DoQuery(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz Request;
    aInvocation.InvocationReadString("Request", Request);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Result;
    ASSERT(iCallbackQuery != NULL);
    if (0 != iCallbackQuery(iPtrQuery, invocationC, invocationCPtr, (const char*)Request.Ptr(), &Result)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respResult(aInvocation, "Result");
    invocation.StartResponse();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    invocation.EndResponse();
}



THandle STDCALL DvProviderAvOpenhomeOrgMediaServer1Create(DvDeviceC aDevice)
{
	return new DvProviderAvOpenhomeOrgMediaServer1C(aDevice);
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider);
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionManufacturer(THandle aProvider, CallbackMediaServer1Manufacturer aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnableActionManufacturer(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionModel(THandle aProvider, CallbackMediaServer1Model aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnableActionModel(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionProduct(THandle aProvider, CallbackMediaServer1Product aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnableActionProduct(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionAttributes(THandle aProvider, CallbackMediaServer1Attributes aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnableActionAttributes(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionQuery(THandle aProvider, CallbackMediaServer1Query aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnableActionQuery(aCallback, aPtr);
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyManufacturerName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyManufacturerName(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyManufacturerName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyManufacturerName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyManufacturerInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyManufacturerInfo(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyManufacturerInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyManufacturerInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyManufacturerUrl(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyManufacturerUrl(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyManufacturerUrl(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyManufacturerUrl(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyManufacturerImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyManufacturerImageUri(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyManufacturerImageUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyManufacturerImageUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyModelName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyModelName(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyModelName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyModelName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyModelInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyModelInfo(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyModelInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyModelInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyModelUrl(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyModelUrl(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyModelUrl(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyModelUrl(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyModelImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyModelImageUri(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyModelImageUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyModelImageUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyProductName(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyProductName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyProductName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyProductInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyProductInfo(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyProductInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyProductInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyProductUrl(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyProductUrl(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyProductUrl(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyProductUrl(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyProductImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyProductImageUri(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyProductImageUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyProductImageUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyAttributes(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyAttributes(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyAttributes(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyAttributes(buf);
    *aValue = (char*)buf.Transfer();
}

