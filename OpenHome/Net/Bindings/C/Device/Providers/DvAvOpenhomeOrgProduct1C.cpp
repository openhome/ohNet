#include "DvAvOpenhomeOrgProduct1.h"
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

class DvProviderAvOpenhomeOrgProduct1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgProduct1C(DvDeviceC aDevice);
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
    TBool SetPropertyProductRoom(const Brx& aValue);
    void GetPropertyProductRoom(Brhz& aValue);
    TBool SetPropertyProductName(const Brx& aValue);
    void GetPropertyProductName(Brhz& aValue);
    TBool SetPropertyProductInfo(const Brx& aValue);
    void GetPropertyProductInfo(Brhz& aValue);
    TBool SetPropertyProductUrl(const Brx& aValue);
    void GetPropertyProductUrl(Brhz& aValue);
    TBool SetPropertyProductImageUri(const Brx& aValue);
    void GetPropertyProductImageUri(Brhz& aValue);
    TBool SetPropertyStandby(TBool aValue);
    void GetPropertyStandby(TBool& aValue);
    TBool SetPropertySourceIndex(TUint aValue);
    void GetPropertySourceIndex(TUint& aValue);
    TBool SetPropertySourceCount(TUint aValue);
    void GetPropertySourceCount(TUint& aValue);
    TBool SetPropertySourceXml(const Brx& aValue);
    void GetPropertySourceXml(Brhz& aValue);
    TBool SetPropertyAttributes(const Brx& aValue);
    void GetPropertyAttributes(Brhz& aValue);
    void EnablePropertyManufacturerName();
    void EnablePropertyManufacturerInfo();
    void EnablePropertyManufacturerUrl();
    void EnablePropertyManufacturerImageUri();
    void EnablePropertyModelName();
    void EnablePropertyModelInfo();
    void EnablePropertyModelUrl();
    void EnablePropertyModelImageUri();
    void EnablePropertyProductRoom();
    void EnablePropertyProductName();
    void EnablePropertyProductInfo();
    void EnablePropertyProductUrl();
    void EnablePropertyProductImageUri();
    void EnablePropertyStandby();
    void EnablePropertySourceIndex();
    void EnablePropertySourceCount();
    void EnablePropertySourceXml();
    void EnablePropertyAttributes();
    void EnableActionManufacturer(CallbackProduct1Manufacturer aCallback, void* aPtr);
    void EnableActionModel(CallbackProduct1Model aCallback, void* aPtr);
    void EnableActionProduct(CallbackProduct1Product aCallback, void* aPtr);
    void EnableActionStandby(CallbackProduct1Standby aCallback, void* aPtr);
    void EnableActionSetStandby(CallbackProduct1SetStandby aCallback, void* aPtr);
    void EnableActionSourceCount(CallbackProduct1SourceCount aCallback, void* aPtr);
    void EnableActionSourceXml(CallbackProduct1SourceXml aCallback, void* aPtr);
    void EnableActionSourceIndex(CallbackProduct1SourceIndex aCallback, void* aPtr);
    void EnableActionSetSourceIndex(CallbackProduct1SetSourceIndex aCallback, void* aPtr);
    void EnableActionSetSourceIndexByName(CallbackProduct1SetSourceIndexByName aCallback, void* aPtr);
    void EnableActionSource(CallbackProduct1Source aCallback, void* aPtr);
    void EnableActionAttributes(CallbackProduct1Attributes aCallback, void* aPtr);
    void EnableActionSourceXmlChangeCount(CallbackProduct1SourceXmlChangeCount aCallback, void* aPtr);
private:
    void DoManufacturer(IDviInvocation& aInvocation);
    void DoModel(IDviInvocation& aInvocation);
    void DoProduct(IDviInvocation& aInvocation);
    void DoStandby(IDviInvocation& aInvocation);
    void DoSetStandby(IDviInvocation& aInvocation);
    void DoSourceCount(IDviInvocation& aInvocation);
    void DoSourceXml(IDviInvocation& aInvocation);
    void DoSourceIndex(IDviInvocation& aInvocation);
    void DoSetSourceIndex(IDviInvocation& aInvocation);
    void DoSetSourceIndexByName(IDviInvocation& aInvocation);
    void DoSource(IDviInvocation& aInvocation);
    void DoAttributes(IDviInvocation& aInvocation);
    void DoSourceXmlChangeCount(IDviInvocation& aInvocation);
private:
    CallbackProduct1Manufacturer iCallbackManufacturer;
    void* iPtrManufacturer;
    CallbackProduct1Model iCallbackModel;
    void* iPtrModel;
    CallbackProduct1Product iCallbackProduct;
    void* iPtrProduct;
    CallbackProduct1Standby iCallbackStandby;
    void* iPtrStandby;
    CallbackProduct1SetStandby iCallbackSetStandby;
    void* iPtrSetStandby;
    CallbackProduct1SourceCount iCallbackSourceCount;
    void* iPtrSourceCount;
    CallbackProduct1SourceXml iCallbackSourceXml;
    void* iPtrSourceXml;
    CallbackProduct1SourceIndex iCallbackSourceIndex;
    void* iPtrSourceIndex;
    CallbackProduct1SetSourceIndex iCallbackSetSourceIndex;
    void* iPtrSetSourceIndex;
    CallbackProduct1SetSourceIndexByName iCallbackSetSourceIndexByName;
    void* iPtrSetSourceIndexByName;
    CallbackProduct1Source iCallbackSource;
    void* iPtrSource;
    CallbackProduct1Attributes iCallbackAttributes;
    void* iPtrAttributes;
    CallbackProduct1SourceXmlChangeCount iCallbackSourceXmlChangeCount;
    void* iPtrSourceXmlChangeCount;
    PropertyString* iPropertyManufacturerName;
    PropertyString* iPropertyManufacturerInfo;
    PropertyString* iPropertyManufacturerUrl;
    PropertyString* iPropertyManufacturerImageUri;
    PropertyString* iPropertyModelName;
    PropertyString* iPropertyModelInfo;
    PropertyString* iPropertyModelUrl;
    PropertyString* iPropertyModelImageUri;
    PropertyString* iPropertyProductRoom;
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductInfo;
    PropertyString* iPropertyProductUrl;
    PropertyString* iPropertyProductImageUri;
    PropertyBool* iPropertyStandby;
    PropertyUint* iPropertySourceIndex;
    PropertyUint* iPropertySourceCount;
    PropertyString* iPropertySourceXml;
    PropertyString* iPropertyAttributes;
};

DvProviderAvOpenhomeOrgProduct1C::DvProviderAvOpenhomeOrgProduct1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "Product", 1)
{
    iPropertyManufacturerName = NULL;
    iPropertyManufacturerInfo = NULL;
    iPropertyManufacturerUrl = NULL;
    iPropertyManufacturerImageUri = NULL;
    iPropertyModelName = NULL;
    iPropertyModelInfo = NULL;
    iPropertyModelUrl = NULL;
    iPropertyModelImageUri = NULL;
    iPropertyProductRoom = NULL;
    iPropertyProductName = NULL;
    iPropertyProductInfo = NULL;
    iPropertyProductUrl = NULL;
    iPropertyProductImageUri = NULL;
    iPropertyStandby = NULL;
    iPropertySourceIndex = NULL;
    iPropertySourceCount = NULL;
    iPropertySourceXml = NULL;
    iPropertyAttributes = NULL;
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyManufacturerName(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerName != NULL);
    return SetPropertyString(*iPropertyManufacturerName, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyManufacturerName(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerName != NULL);
    aValue.Set(iPropertyManufacturerName->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyManufacturerInfo(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerInfo != NULL);
    return SetPropertyString(*iPropertyManufacturerInfo, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyManufacturerInfo(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerInfo != NULL);
    aValue.Set(iPropertyManufacturerInfo->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyManufacturerUrl(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerUrl != NULL);
    return SetPropertyString(*iPropertyManufacturerUrl, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyManufacturerUrl(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerUrl != NULL);
    aValue.Set(iPropertyManufacturerUrl->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyManufacturerImageUri(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerImageUri != NULL);
    return SetPropertyString(*iPropertyManufacturerImageUri, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyManufacturerImageUri(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerImageUri != NULL);
    aValue.Set(iPropertyManufacturerImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyModelName(const Brx& aValue)
{
    ASSERT(iPropertyModelName != NULL);
    return SetPropertyString(*iPropertyModelName, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyModelName(Brhz& aValue)
{
    ASSERT(iPropertyModelName != NULL);
    aValue.Set(iPropertyModelName->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyModelInfo(const Brx& aValue)
{
    ASSERT(iPropertyModelInfo != NULL);
    return SetPropertyString(*iPropertyModelInfo, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyModelInfo(Brhz& aValue)
{
    ASSERT(iPropertyModelInfo != NULL);
    aValue.Set(iPropertyModelInfo->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyModelUrl(const Brx& aValue)
{
    ASSERT(iPropertyModelUrl != NULL);
    return SetPropertyString(*iPropertyModelUrl, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyModelUrl(Brhz& aValue)
{
    ASSERT(iPropertyModelUrl != NULL);
    aValue.Set(iPropertyModelUrl->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyModelImageUri(const Brx& aValue)
{
    ASSERT(iPropertyModelImageUri != NULL);
    return SetPropertyString(*iPropertyModelImageUri, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyModelImageUri(Brhz& aValue)
{
    ASSERT(iPropertyModelImageUri != NULL);
    aValue.Set(iPropertyModelImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyProductRoom(const Brx& aValue)
{
    ASSERT(iPropertyProductRoom != NULL);
    return SetPropertyString(*iPropertyProductRoom, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyProductRoom(Brhz& aValue)
{
    ASSERT(iPropertyProductRoom != NULL);
    aValue.Set(iPropertyProductRoom->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyProductName(const Brx& aValue)
{
    ASSERT(iPropertyProductName != NULL);
    return SetPropertyString(*iPropertyProductName, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyProductName(Brhz& aValue)
{
    ASSERT(iPropertyProductName != NULL);
    aValue.Set(iPropertyProductName->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyProductInfo(const Brx& aValue)
{
    ASSERT(iPropertyProductInfo != NULL);
    return SetPropertyString(*iPropertyProductInfo, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyProductInfo(Brhz& aValue)
{
    ASSERT(iPropertyProductInfo != NULL);
    aValue.Set(iPropertyProductInfo->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyProductUrl(const Brx& aValue)
{
    ASSERT(iPropertyProductUrl != NULL);
    return SetPropertyString(*iPropertyProductUrl, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyProductUrl(Brhz& aValue)
{
    ASSERT(iPropertyProductUrl != NULL);
    aValue.Set(iPropertyProductUrl->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyProductImageUri(const Brx& aValue)
{
    ASSERT(iPropertyProductImageUri != NULL);
    return SetPropertyString(*iPropertyProductImageUri, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyProductImageUri(Brhz& aValue)
{
    ASSERT(iPropertyProductImageUri != NULL);
    aValue.Set(iPropertyProductImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyStandby(TBool aValue)
{
    ASSERT(iPropertyStandby != NULL);
    return SetPropertyBool(*iPropertyStandby, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyStandby(TBool& aValue)
{
    ASSERT(iPropertyStandby != NULL);
    aValue = iPropertyStandby->Value();
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertySourceIndex(TUint aValue)
{
    ASSERT(iPropertySourceIndex != NULL);
    return SetPropertyUint(*iPropertySourceIndex, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertySourceIndex(TUint& aValue)
{
    ASSERT(iPropertySourceIndex != NULL);
    aValue = iPropertySourceIndex->Value();
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertySourceCount(TUint aValue)
{
    ASSERT(iPropertySourceCount != NULL);
    return SetPropertyUint(*iPropertySourceCount, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertySourceCount(TUint& aValue)
{
    ASSERT(iPropertySourceCount != NULL);
    aValue = iPropertySourceCount->Value();
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertySourceXml(const Brx& aValue)
{
    ASSERT(iPropertySourceXml != NULL);
    return SetPropertyString(*iPropertySourceXml, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertySourceXml(Brhz& aValue)
{
    ASSERT(iPropertySourceXml != NULL);
    aValue.Set(iPropertySourceXml->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1C::SetPropertyAttributes(const Brx& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    return SetPropertyString(*iPropertyAttributes, aValue);
}

void DvProviderAvOpenhomeOrgProduct1C::GetPropertyAttributes(Brhz& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    aValue.Set(iPropertyAttributes->Value());
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyManufacturerName()
{
    iPropertyManufacturerName = new PropertyString(new ParameterString("ManufacturerName"));
    iService->AddProperty(iPropertyManufacturerName); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyManufacturerInfo()
{
    iPropertyManufacturerInfo = new PropertyString(new ParameterString("ManufacturerInfo"));
    iService->AddProperty(iPropertyManufacturerInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyManufacturerUrl()
{
    iPropertyManufacturerUrl = new PropertyString(new ParameterString("ManufacturerUrl"));
    iService->AddProperty(iPropertyManufacturerUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyManufacturerImageUri()
{
    iPropertyManufacturerImageUri = new PropertyString(new ParameterString("ManufacturerImageUri"));
    iService->AddProperty(iPropertyManufacturerImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyModelName()
{
    iPropertyModelName = new PropertyString(new ParameterString("ModelName"));
    iService->AddProperty(iPropertyModelName); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyModelInfo()
{
    iPropertyModelInfo = new PropertyString(new ParameterString("ModelInfo"));
    iService->AddProperty(iPropertyModelInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyModelUrl()
{
    iPropertyModelUrl = new PropertyString(new ParameterString("ModelUrl"));
    iService->AddProperty(iPropertyModelUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyModelImageUri()
{
    iPropertyModelImageUri = new PropertyString(new ParameterString("ModelImageUri"));
    iService->AddProperty(iPropertyModelImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyProductRoom()
{
    iPropertyProductRoom = new PropertyString(new ParameterString("ProductRoom"));
    iService->AddProperty(iPropertyProductRoom); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyProductName()
{
    iPropertyProductName = new PropertyString(new ParameterString("ProductName"));
    iService->AddProperty(iPropertyProductName); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyProductInfo()
{
    iPropertyProductInfo = new PropertyString(new ParameterString("ProductInfo"));
    iService->AddProperty(iPropertyProductInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyProductUrl()
{
    iPropertyProductUrl = new PropertyString(new ParameterString("ProductUrl"));
    iService->AddProperty(iPropertyProductUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyProductImageUri()
{
    iPropertyProductImageUri = new PropertyString(new ParameterString("ProductImageUri"));
    iService->AddProperty(iPropertyProductImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyStandby()
{
    iPropertyStandby = new PropertyBool(new ParameterBool("Standby"));
    iService->AddProperty(iPropertyStandby); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertySourceIndex()
{
    iPropertySourceIndex = new PropertyUint(new ParameterUint("SourceIndex"));
    iService->AddProperty(iPropertySourceIndex); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertySourceCount()
{
    iPropertySourceCount = new PropertyUint(new ParameterUint("SourceCount"));
    iService->AddProperty(iPropertySourceCount); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertySourceXml()
{
    iPropertySourceXml = new PropertyString(new ParameterString("SourceXml"));
    iService->AddProperty(iPropertySourceXml); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnablePropertyAttributes()
{
    iPropertyAttributes = new PropertyString(new ParameterString("Attributes"));
    iService->AddProperty(iPropertyAttributes); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionManufacturer(CallbackProduct1Manufacturer aCallback, void* aPtr)
{
    iCallbackManufacturer = aCallback;
    iPtrManufacturer = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Manufacturer");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyManufacturerName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyManufacturerInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyManufacturerUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyManufacturerImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoManufacturer);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionModel(CallbackProduct1Model aCallback, void* aPtr)
{
    iCallbackModel = aCallback;
    iPtrModel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Model");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyModelName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyModelInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyModelUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyModelImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoModel);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionProduct(CallbackProduct1Product aCallback, void* aPtr)
{
    iCallbackProduct = aCallback;
    iPtrProduct = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Product");
    action->AddOutputParameter(new ParameterRelated("Room", *iPropertyProductRoom));
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyProductName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyProductInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyProductUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyProductImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoProduct);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionStandby(CallbackProduct1Standby aCallback, void* aPtr)
{
    iCallbackStandby = aCallback;
    iPtrStandby = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoStandby);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionSetStandby(CallbackProduct1SetStandby aCallback, void* aPtr)
{
    iCallbackSetStandby = aCallback;
    iPtrSetStandby = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionSourceCount(CallbackProduct1SourceCount aCallback, void* aPtr)
{
    iCallbackSourceCount = aCallback;
    iPtrSourceCount = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SourceCount");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertySourceCount));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoSourceCount);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionSourceXml(CallbackProduct1SourceXml aCallback, void* aPtr)
{
    iCallbackSourceXml = aCallback;
    iPtrSourceXml = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SourceXml");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertySourceXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoSourceXml);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionSourceIndex(CallbackProduct1SourceIndex aCallback, void* aPtr)
{
    iCallbackSourceIndex = aCallback;
    iPtrSourceIndex = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SourceIndex");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertySourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionSetSourceIndex(CallbackProduct1SetSourceIndex aCallback, void* aPtr)
{
    iCallbackSetSourceIndex = aCallback;
    iPtrSetSourceIndex = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSourceIndex");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertySourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoSetSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionSetSourceIndexByName(CallbackProduct1SetSourceIndexByName aCallback, void* aPtr)
{
    iCallbackSetSourceIndexByName = aCallback;
    iPtrSetSourceIndexByName = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSourceIndexByName");
    action->AddInputParameter(new ParameterString("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoSetSourceIndexByName);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionSource(CallbackProduct1Source aCallback, void* aPtr)
{
    iCallbackSource = aCallback;
    iPtrSource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Source");
    action->AddInputParameter(new ParameterRelated("Index", *iPropertySourceIndex));
    action->AddOutputParameter(new ParameterString("SystemName"));
    action->AddOutputParameter(new ParameterString("Type"));
    action->AddOutputParameter(new ParameterString("Name"));
    action->AddOutputParameter(new ParameterBool("Visible"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoSource);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionAttributes(CallbackProduct1Attributes aCallback, void* aPtr)
{
    iCallbackAttributes = aCallback;
    iPtrAttributes = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Attributes");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAttributes));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoAttributes);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::EnableActionSourceXmlChangeCount(CallbackProduct1SourceXmlChangeCount aCallback, void* aPtr)
{
    iCallbackSourceXmlChangeCount = aCallback;
    iPtrSourceXmlChangeCount = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SourceXmlChangeCount");
    action->AddOutputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1C::DoSourceXmlChangeCount);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1C::DoManufacturer(IDviInvocation& aInvocation)
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

void DvProviderAvOpenhomeOrgProduct1C::DoModel(IDviInvocation& aInvocation)
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

void DvProviderAvOpenhomeOrgProduct1C::DoProduct(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Room;
    char* Name;
    char* Info;
    char* Url;
    char* ImageUri;
    ASSERT(iCallbackProduct != NULL);
    if (0 != iCallbackProduct(iPtrProduct, invocationC, invocationCPtr, &Room, &Name, &Info, &Url, &ImageUri)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respRoom(aInvocation, "Room");
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respInfo(aInvocation, "Info");
    DviInvocationResponseString respUrl(aInvocation, "Url");
    DviInvocationResponseString respImageUri(aInvocation, "ImageUri");
    invocation.StartResponse();
    Brhz bufRoom((const TChar*)Room);
    OhNetFreeExternal(Room);
    respRoom.Write(bufRoom);
    respRoom.WriteFlush();
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

void DvProviderAvOpenhomeOrgProduct1C::DoStandby(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackStandby != NULL);
    if (0 != iCallbackStandby(iPtrStandby, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write((Value!=0));
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgProduct1C::DoSetStandby(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetStandby != NULL);
    if (0 != iCallbackSetStandby(iPtrSetStandby, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgProduct1C::DoSourceCount(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackSourceCount != NULL);
    if (0 != iCallbackSourceCount(iPtrSourceCount, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgProduct1C::DoSourceXml(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Value;
    ASSERT(iCallbackSourceXml != NULL);
    if (0 != iCallbackSourceXml(iPtrSourceXml, invocationC, invocationCPtr, &Value)) {
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

void DvProviderAvOpenhomeOrgProduct1C::DoSourceIndex(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackSourceIndex != NULL);
    if (0 != iCallbackSourceIndex(iPtrSourceIndex, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgProduct1C::DoSetSourceIndex(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetSourceIndex != NULL);
    if (0 != iCallbackSetSourceIndex(iPtrSetSourceIndex, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgProduct1C::DoSetSourceIndexByName(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz Value;
    aInvocation.InvocationReadString("Value", Value);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetSourceIndexByName != NULL);
    if (0 != iCallbackSetSourceIndexByName(iPtrSetSourceIndexByName, invocationC, invocationCPtr, (const char*)Value.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgProduct1C::DoSource(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* SystemName;
    char* Type;
    char* Name;
    uint32_t Visible;
    ASSERT(iCallbackSource != NULL);
    if (0 != iCallbackSource(iPtrSource, invocationC, invocationCPtr, Index, &SystemName, &Type, &Name, &Visible)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respSystemName(aInvocation, "SystemName");
    DviInvocationResponseString respType(aInvocation, "Type");
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseBool respVisible(aInvocation, "Visible");
    invocation.StartResponse();
    Brhz bufSystemName((const TChar*)SystemName);
    OhNetFreeExternal(SystemName);
    respSystemName.Write(bufSystemName);
    respSystemName.WriteFlush();
    Brhz bufType((const TChar*)Type);
    OhNetFreeExternal(Type);
    respType.Write(bufType);
    respType.WriteFlush();
    Brhz bufName((const TChar*)Name);
    OhNetFreeExternal(Name);
    respName.Write(bufName);
    respName.WriteFlush();
    respVisible.Write((Visible!=0));
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgProduct1C::DoAttributes(IDviInvocation& aInvocation)
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

void DvProviderAvOpenhomeOrgProduct1C::DoSourceXmlChangeCount(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackSourceXmlChangeCount != NULL);
    if (0 != iCallbackSourceXmlChangeCount(iPtrSourceXmlChangeCount, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}



THandle STDCALL DvProviderAvOpenhomeOrgProduct1Create(DvDeviceC aDevice)
{
    return new DvProviderAvOpenhomeOrgProduct1C(aDevice);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionManufacturer(THandle aProvider, CallbackProduct1Manufacturer aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionManufacturer(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionModel(THandle aProvider, CallbackProduct1Model aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionModel(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionProduct(THandle aProvider, CallbackProduct1Product aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionProduct(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionStandby(THandle aProvider, CallbackProduct1Standby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionStandby(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSetStandby(THandle aProvider, CallbackProduct1SetStandby aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionSetStandby(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceCount(THandle aProvider, CallbackProduct1SourceCount aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionSourceCount(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceXml(THandle aProvider, CallbackProduct1SourceXml aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionSourceXml(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceIndex(THandle aProvider, CallbackProduct1SourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionSourceIndex(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSetSourceIndex(THandle aProvider, CallbackProduct1SetSourceIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionSetSourceIndex(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSetSourceIndexByName(THandle aProvider, CallbackProduct1SetSourceIndexByName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionSetSourceIndexByName(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSource(THandle aProvider, CallbackProduct1Source aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionSource(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionAttributes(THandle aProvider, CallbackProduct1Attributes aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionAttributes(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceXmlChangeCount(THandle aProvider, CallbackProduct1SourceXmlChangeCount aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnableActionSourceXmlChangeCount(aCallback, aPtr);
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyManufacturerName(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyManufacturerName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyManufacturerInfo(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyManufacturerInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerUrl(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyManufacturerUrl(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerUrl(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyManufacturerUrl(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyManufacturerImageUri(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerImageUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyManufacturerImageUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyModelName(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyModelName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyModelInfo(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyModelInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelUrl(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyModelUrl(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelUrl(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyModelUrl(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyModelImageUri(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelImageUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyModelImageUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductRoom(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyProductRoom(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductRoom(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyProductRoom(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyProductName(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyProductName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyProductInfo(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyProductInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductUrl(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyProductUrl(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductUrl(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyProductUrl(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyProductImageUri(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductImageUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyProductImageUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyStandby((aValue!=0))? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyStandby(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyStandby(val);
    *aValue = (val? 1 : 0);
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertySourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertySourceIndex(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertySourceIndex(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertySourceIndex(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertySourceCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertySourceCount(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertySourceCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertySourceCount(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertySourceXml(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertySourceXml(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertySourceXml(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertySourceXml(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyAttributes(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->SetPropertyAttributes(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyAttributes(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->GetPropertyAttributes(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerName(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyManufacturerName();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerInfo(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyManufacturerInfo();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerUrl(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyManufacturerUrl();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerImageUri(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyManufacturerImageUri();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyModelName(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyModelName();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyModelInfo(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyModelInfo();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyModelUrl(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyModelUrl();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyModelImageUri(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyModelImageUri();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyProductRoom(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyProductRoom();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyProductName(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyProductName();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyProductInfo(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyProductInfo();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyProductUrl(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyProductUrl();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyProductImageUri(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyProductImageUri();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyStandby(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyStandby();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertySourceIndex(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertySourceIndex();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertySourceCount(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertySourceCount();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertySourceXml(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertySourceXml();
}

void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyAttributes(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgProduct1C*>(aProvider)->EnablePropertyAttributes();
}

