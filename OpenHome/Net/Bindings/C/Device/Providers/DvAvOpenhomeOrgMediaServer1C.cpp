#include "DvAvOpenhomeOrgMediaServer1.h"
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
    TBool SetPropertyQueryPort(TUint aValue);
    void GetPropertyQueryPort(TUint& aValue);
    TBool SetPropertyBrowsePort(TUint aValue);
    void GetPropertyBrowsePort(TUint& aValue);
    TBool SetPropertyUpdateCount(TUint aValue);
    void GetPropertyUpdateCount(TUint& aValue);
    void EnablePropertyManufacturerName();
    void EnablePropertyManufacturerInfo();
    void EnablePropertyManufacturerUrl();
    void EnablePropertyManufacturerImageUri();
    void EnablePropertyModelName();
    void EnablePropertyModelInfo();
    void EnablePropertyModelUrl();
    void EnablePropertyModelImageUri();
    void EnablePropertyProductName();
    void EnablePropertyProductInfo();
    void EnablePropertyProductUrl();
    void EnablePropertyProductImageUri();
    void EnablePropertyAttributes();
    void EnablePropertyQueryPort();
    void EnablePropertyBrowsePort();
    void EnablePropertyUpdateCount();
    void EnableActionManufacturer(CallbackMediaServer1Manufacturer aCallback, void* aPtr);
    void EnableActionModel(CallbackMediaServer1Model aCallback, void* aPtr);
    void EnableActionProduct(CallbackMediaServer1Product aCallback, void* aPtr);
    void EnableActionAttributes(CallbackMediaServer1Attributes aCallback, void* aPtr);
    void EnableActionQueryPort(CallbackMediaServer1QueryPort aCallback, void* aPtr);
    void EnableActionBrowsePort(CallbackMediaServer1BrowsePort aCallback, void* aPtr);
    void EnableActionUpdateCount(CallbackMediaServer1UpdateCount aCallback, void* aPtr);
private:
    void DoManufacturer(IDviInvocation& aInvocation);
    void DoModel(IDviInvocation& aInvocation);
    void DoProduct(IDviInvocation& aInvocation);
    void DoAttributes(IDviInvocation& aInvocation);
    void DoQueryPort(IDviInvocation& aInvocation);
    void DoBrowsePort(IDviInvocation& aInvocation);
    void DoUpdateCount(IDviInvocation& aInvocation);
private:
    CallbackMediaServer1Manufacturer iCallbackManufacturer;
    void* iPtrManufacturer;
    CallbackMediaServer1Model iCallbackModel;
    void* iPtrModel;
    CallbackMediaServer1Product iCallbackProduct;
    void* iPtrProduct;
    CallbackMediaServer1Attributes iCallbackAttributes;
    void* iPtrAttributes;
    CallbackMediaServer1QueryPort iCallbackQueryPort;
    void* iPtrQueryPort;
    CallbackMediaServer1BrowsePort iCallbackBrowsePort;
    void* iPtrBrowsePort;
    CallbackMediaServer1UpdateCount iCallbackUpdateCount;
    void* iPtrUpdateCount;
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
    PropertyUint* iPropertyQueryPort;
    PropertyUint* iPropertyBrowsePort;
    PropertyUint* iPropertyUpdateCount;
};

DvProviderAvOpenhomeOrgMediaServer1C::DvProviderAvOpenhomeOrgMediaServer1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "MediaServer", 1)
{
    iPropertyManufacturerName = NULL;
    iPropertyManufacturerInfo = NULL;
    iPropertyManufacturerUrl = NULL;
    iPropertyManufacturerImageUri = NULL;
    iPropertyModelName = NULL;
    iPropertyModelInfo = NULL;
    iPropertyModelUrl = NULL;
    iPropertyModelImageUri = NULL;
    iPropertyProductName = NULL;
    iPropertyProductInfo = NULL;
    iPropertyProductUrl = NULL;
    iPropertyProductImageUri = NULL;
    iPropertyAttributes = NULL;
    iPropertyQueryPort = NULL;
    iPropertyBrowsePort = NULL;
    iPropertyUpdateCount = NULL;
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyManufacturerName(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerName != NULL);
    return SetPropertyString(*iPropertyManufacturerName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyManufacturerName(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerName != NULL);
    aValue.Set(iPropertyManufacturerName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyManufacturerInfo(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerInfo != NULL);
    return SetPropertyString(*iPropertyManufacturerInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyManufacturerInfo(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerInfo != NULL);
    aValue.Set(iPropertyManufacturerInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyManufacturerUrl(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerUrl != NULL);
    return SetPropertyString(*iPropertyManufacturerUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyManufacturerUrl(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerUrl != NULL);
    aValue.Set(iPropertyManufacturerUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyManufacturerImageUri(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerImageUri != NULL);
    return SetPropertyString(*iPropertyManufacturerImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyManufacturerImageUri(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerImageUri != NULL);
    aValue.Set(iPropertyManufacturerImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyModelName(const Brx& aValue)
{
    ASSERT(iPropertyModelName != NULL);
    return SetPropertyString(*iPropertyModelName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyModelName(Brhz& aValue)
{
    ASSERT(iPropertyModelName != NULL);
    aValue.Set(iPropertyModelName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyModelInfo(const Brx& aValue)
{
    ASSERT(iPropertyModelInfo != NULL);
    return SetPropertyString(*iPropertyModelInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyModelInfo(Brhz& aValue)
{
    ASSERT(iPropertyModelInfo != NULL);
    aValue.Set(iPropertyModelInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyModelUrl(const Brx& aValue)
{
    ASSERT(iPropertyModelUrl != NULL);
    return SetPropertyString(*iPropertyModelUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyModelUrl(Brhz& aValue)
{
    ASSERT(iPropertyModelUrl != NULL);
    aValue.Set(iPropertyModelUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyModelImageUri(const Brx& aValue)
{
    ASSERT(iPropertyModelImageUri != NULL);
    return SetPropertyString(*iPropertyModelImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyModelImageUri(Brhz& aValue)
{
    ASSERT(iPropertyModelImageUri != NULL);
    aValue.Set(iPropertyModelImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyProductName(const Brx& aValue)
{
    ASSERT(iPropertyProductName != NULL);
    return SetPropertyString(*iPropertyProductName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyProductName(Brhz& aValue)
{
    ASSERT(iPropertyProductName != NULL);
    aValue.Set(iPropertyProductName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyProductInfo(const Brx& aValue)
{
    ASSERT(iPropertyProductInfo != NULL);
    return SetPropertyString(*iPropertyProductInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyProductInfo(Brhz& aValue)
{
    ASSERT(iPropertyProductInfo != NULL);
    aValue.Set(iPropertyProductInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyProductUrl(const Brx& aValue)
{
    ASSERT(iPropertyProductUrl != NULL);
    return SetPropertyString(*iPropertyProductUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyProductUrl(Brhz& aValue)
{
    ASSERT(iPropertyProductUrl != NULL);
    aValue.Set(iPropertyProductUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyProductImageUri(const Brx& aValue)
{
    ASSERT(iPropertyProductImageUri != NULL);
    return SetPropertyString(*iPropertyProductImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyProductImageUri(Brhz& aValue)
{
    ASSERT(iPropertyProductImageUri != NULL);
    aValue.Set(iPropertyProductImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyAttributes(const Brx& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    return SetPropertyString(*iPropertyAttributes, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyAttributes(Brhz& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    aValue.Set(iPropertyAttributes->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyQueryPort(TUint aValue)
{
    ASSERT(iPropertyQueryPort != NULL);
    return SetPropertyUint(*iPropertyQueryPort, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyQueryPort(TUint& aValue)
{
    ASSERT(iPropertyQueryPort != NULL);
    aValue = iPropertyQueryPort->Value();
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyBrowsePort(TUint aValue)
{
    ASSERT(iPropertyBrowsePort != NULL);
    return SetPropertyUint(*iPropertyBrowsePort, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyBrowsePort(TUint& aValue)
{
    ASSERT(iPropertyBrowsePort != NULL);
    aValue = iPropertyBrowsePort->Value();
}

TBool DvProviderAvOpenhomeOrgMediaServer1C::SetPropertyUpdateCount(TUint aValue)
{
    ASSERT(iPropertyUpdateCount != NULL);
    return SetPropertyUint(*iPropertyUpdateCount, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1C::GetPropertyUpdateCount(TUint& aValue)
{
    ASSERT(iPropertyUpdateCount != NULL);
    aValue = iPropertyUpdateCount->Value();
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyManufacturerName()
{
    iPropertyManufacturerName = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerName"));
    iService->AddProperty(iPropertyManufacturerName); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyManufacturerInfo()
{
    iPropertyManufacturerInfo = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerInfo"));
    iService->AddProperty(iPropertyManufacturerInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyManufacturerUrl()
{
    iPropertyManufacturerUrl = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerUrl"));
    iService->AddProperty(iPropertyManufacturerUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyManufacturerImageUri()
{
    iPropertyManufacturerImageUri = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerImageUri"));
    iService->AddProperty(iPropertyManufacturerImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyModelName()
{
    iPropertyModelName = new PropertyString(iDvStack.Env(), new ParameterString("ModelName"));
    iService->AddProperty(iPropertyModelName); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyModelInfo()
{
    iPropertyModelInfo = new PropertyString(iDvStack.Env(), new ParameterString("ModelInfo"));
    iService->AddProperty(iPropertyModelInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyModelUrl()
{
    iPropertyModelUrl = new PropertyString(iDvStack.Env(), new ParameterString("ModelUrl"));
    iService->AddProperty(iPropertyModelUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyModelImageUri()
{
    iPropertyModelImageUri = new PropertyString(iDvStack.Env(), new ParameterString("ModelImageUri"));
    iService->AddProperty(iPropertyModelImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyProductName()
{
    iPropertyProductName = new PropertyString(iDvStack.Env(), new ParameterString("ProductName"));
    iService->AddProperty(iPropertyProductName); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyProductInfo()
{
    iPropertyProductInfo = new PropertyString(iDvStack.Env(), new ParameterString("ProductInfo"));
    iService->AddProperty(iPropertyProductInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyProductUrl()
{
    iPropertyProductUrl = new PropertyString(iDvStack.Env(), new ParameterString("ProductUrl"));
    iService->AddProperty(iPropertyProductUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyProductImageUri()
{
    iPropertyProductImageUri = new PropertyString(iDvStack.Env(), new ParameterString("ProductImageUri"));
    iService->AddProperty(iPropertyProductImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyAttributes()
{
    iPropertyAttributes = new PropertyString(iDvStack.Env(), new ParameterString("Attributes"));
    iService->AddProperty(iPropertyAttributes); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyQueryPort()
{
    iPropertyQueryPort = new PropertyUint(iDvStack.Env(), new ParameterUint("QueryPort"));
    iService->AddProperty(iPropertyQueryPort); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyBrowsePort()
{
    iPropertyBrowsePort = new PropertyUint(iDvStack.Env(), new ParameterUint("BrowsePort"));
    iService->AddProperty(iPropertyBrowsePort); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnablePropertyUpdateCount()
{
    iPropertyUpdateCount = new PropertyUint(iDvStack.Env(), new ParameterUint("UpdateCount"));
    iService->AddProperty(iPropertyUpdateCount); // passes ownership
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

void DvProviderAvOpenhomeOrgMediaServer1C::EnableActionQueryPort(CallbackMediaServer1QueryPort aCallback, void* aPtr)
{
    iCallbackQueryPort = aCallback;
    iPtrQueryPort = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("QueryPort");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyQueryPort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1C::DoQueryPort);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnableActionBrowsePort(CallbackMediaServer1BrowsePort aCallback, void* aPtr)
{
    iCallbackBrowsePort = aCallback;
    iPtrBrowsePort = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BrowsePort");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyBrowsePort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1C::DoBrowsePort);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1C::EnableActionUpdateCount(CallbackMediaServer1UpdateCount aCallback, void* aPtr)
{
    iCallbackUpdateCount = aCallback;
    iPtrUpdateCount = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("UpdateCount");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyUpdateCount));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1C::DoUpdateCount);
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

void DvProviderAvOpenhomeOrgMediaServer1C::DoQueryPort(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackQueryPort != NULL);
    if (0 != iCallbackQueryPort(iPtrQueryPort, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgMediaServer1C::DoBrowsePort(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackBrowsePort != NULL);
    if (0 != iCallbackBrowsePort(iPtrBrowsePort, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgMediaServer1C::DoUpdateCount(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackUpdateCount != NULL);
    if (0 != iCallbackUpdateCount(iPtrUpdateCount, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
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

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionQueryPort(THandle aProvider, CallbackMediaServer1QueryPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnableActionQueryPort(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionBrowsePort(THandle aProvider, CallbackMediaServer1BrowsePort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnableActionBrowsePort(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionUpdateCount(THandle aProvider, CallbackMediaServer1UpdateCount aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnableActionUpdateCount(aCallback, aPtr);
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

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyQueryPort(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyQueryPort(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyQueryPort(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyQueryPort(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyBrowsePort(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyBrowsePort(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyBrowsePort(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyBrowsePort(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyUpdateCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->SetPropertyUpdateCount(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyUpdateCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->GetPropertyUpdateCount(val);
    *aValue = val;
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerName(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyManufacturerName();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerInfo(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyManufacturerInfo();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerUrl(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyManufacturerUrl();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerImageUri(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyManufacturerImageUri();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelName(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyModelName();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelInfo(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyModelInfo();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelUrl(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyModelUrl();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelImageUri(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyModelImageUri();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductName(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyProductName();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductInfo(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyProductInfo();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductUrl(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyProductUrl();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductImageUri(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyProductImageUri();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyAttributes(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyAttributes();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyQueryPort(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyQueryPort();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyBrowsePort(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyBrowsePort();
}

void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyUpdateCount(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgMediaServer1C*>(aProvider)->EnablePropertyUpdateCount();
}

