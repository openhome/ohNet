#include "DvAvOpenhomeOrgMediaServer1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyManufacturerName(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerName != NULL);
    return SetPropertyString(*iPropertyManufacturerName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyManufacturerName(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerName != NULL);
    aValue.Set(iPropertyManufacturerName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyManufacturerInfo(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerInfo != NULL);
    return SetPropertyString(*iPropertyManufacturerInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyManufacturerInfo(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerInfo != NULL);
    aValue.Set(iPropertyManufacturerInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyManufacturerUrl(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerUrl != NULL);
    return SetPropertyString(*iPropertyManufacturerUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyManufacturerUrl(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerUrl != NULL);
    aValue.Set(iPropertyManufacturerUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyManufacturerImageUri(const Brx& aValue)
{
    ASSERT(iPropertyManufacturerImageUri != NULL);
    return SetPropertyString(*iPropertyManufacturerImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyManufacturerImageUri(Brhz& aValue)
{
    ASSERT(iPropertyManufacturerImageUri != NULL);
    aValue.Set(iPropertyManufacturerImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyModelName(const Brx& aValue)
{
    ASSERT(iPropertyModelName != NULL);
    return SetPropertyString(*iPropertyModelName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyModelName(Brhz& aValue)
{
    ASSERT(iPropertyModelName != NULL);
    aValue.Set(iPropertyModelName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyModelInfo(const Brx& aValue)
{
    ASSERT(iPropertyModelInfo != NULL);
    return SetPropertyString(*iPropertyModelInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyModelInfo(Brhz& aValue)
{
    ASSERT(iPropertyModelInfo != NULL);
    aValue.Set(iPropertyModelInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyModelUrl(const Brx& aValue)
{
    ASSERT(iPropertyModelUrl != NULL);
    return SetPropertyString(*iPropertyModelUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyModelUrl(Brhz& aValue)
{
    ASSERT(iPropertyModelUrl != NULL);
    aValue.Set(iPropertyModelUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyModelImageUri(const Brx& aValue)
{
    ASSERT(iPropertyModelImageUri != NULL);
    return SetPropertyString(*iPropertyModelImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyModelImageUri(Brhz& aValue)
{
    ASSERT(iPropertyModelImageUri != NULL);
    aValue.Set(iPropertyModelImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyProductName(const Brx& aValue)
{
    ASSERT(iPropertyProductName != NULL);
    return SetPropertyString(*iPropertyProductName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyProductName(Brhz& aValue)
{
    ASSERT(iPropertyProductName != NULL);
    aValue.Set(iPropertyProductName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyProductInfo(const Brx& aValue)
{
    ASSERT(iPropertyProductInfo != NULL);
    return SetPropertyString(*iPropertyProductInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyProductInfo(Brhz& aValue)
{
    ASSERT(iPropertyProductInfo != NULL);
    aValue.Set(iPropertyProductInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyProductUrl(const Brx& aValue)
{
    ASSERT(iPropertyProductUrl != NULL);
    return SetPropertyString(*iPropertyProductUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyProductUrl(Brhz& aValue)
{
    ASSERT(iPropertyProductUrl != NULL);
    aValue.Set(iPropertyProductUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyProductImageUri(const Brx& aValue)
{
    ASSERT(iPropertyProductImageUri != NULL);
    return SetPropertyString(*iPropertyProductImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyProductImageUri(Brhz& aValue)
{
    ASSERT(iPropertyProductImageUri != NULL);
    aValue.Set(iPropertyProductImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyAttributes(const Brx& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    return SetPropertyString(*iPropertyAttributes, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyAttributes(Brhz& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    aValue.Set(iPropertyAttributes->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyQueryPort(TUint aValue)
{
    ASSERT(iPropertyQueryPort != NULL);
    return SetPropertyUint(*iPropertyQueryPort, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyQueryPort(TUint& aValue)
{
    ASSERT(iPropertyQueryPort != NULL);
    aValue = iPropertyQueryPort->Value();
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyBrowsePort(TUint aValue)
{
    ASSERT(iPropertyBrowsePort != NULL);
    return SetPropertyUint(*iPropertyBrowsePort, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyBrowsePort(TUint& aValue)
{
    ASSERT(iPropertyBrowsePort != NULL);
    aValue = iPropertyBrowsePort->Value();
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyUpdateCount(TUint aValue)
{
    ASSERT(iPropertyUpdateCount != NULL);
    return SetPropertyUint(*iPropertyUpdateCount, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyUpdateCount(TUint& aValue)
{
    ASSERT(iPropertyUpdateCount != NULL);
    aValue = iPropertyUpdateCount->Value();
}

DvProviderAvOpenhomeOrgMediaServer1::DvProviderAvOpenhomeOrgMediaServer1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "MediaServer", 1)
{
    Construct();
}

DvProviderAvOpenhomeOrgMediaServer1::DvProviderAvOpenhomeOrgMediaServer1(DviDevice& aDevice)
    : DvProvider(aDevice, "av.openhome.org", "MediaServer", 1)
{
    Construct();
}

void DvProviderAvOpenhomeOrgMediaServer1::Construct()
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

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyManufacturerName()
{
    iPropertyManufacturerName = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerName"));
    iService->AddProperty(iPropertyManufacturerName); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyManufacturerInfo()
{
    iPropertyManufacturerInfo = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerInfo"));
    iService->AddProperty(iPropertyManufacturerInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyManufacturerUrl()
{
    iPropertyManufacturerUrl = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerUrl"));
    iService->AddProperty(iPropertyManufacturerUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyManufacturerImageUri()
{
    iPropertyManufacturerImageUri = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerImageUri"));
    iService->AddProperty(iPropertyManufacturerImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyModelName()
{
    iPropertyModelName = new PropertyString(iDvStack.Env(), new ParameterString("ModelName"));
    iService->AddProperty(iPropertyModelName); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyModelInfo()
{
    iPropertyModelInfo = new PropertyString(iDvStack.Env(), new ParameterString("ModelInfo"));
    iService->AddProperty(iPropertyModelInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyModelUrl()
{
    iPropertyModelUrl = new PropertyString(iDvStack.Env(), new ParameterString("ModelUrl"));
    iService->AddProperty(iPropertyModelUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyModelImageUri()
{
    iPropertyModelImageUri = new PropertyString(iDvStack.Env(), new ParameterString("ModelImageUri"));
    iService->AddProperty(iPropertyModelImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyProductName()
{
    iPropertyProductName = new PropertyString(iDvStack.Env(), new ParameterString("ProductName"));
    iService->AddProperty(iPropertyProductName); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyProductInfo()
{
    iPropertyProductInfo = new PropertyString(iDvStack.Env(), new ParameterString("ProductInfo"));
    iService->AddProperty(iPropertyProductInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyProductUrl()
{
    iPropertyProductUrl = new PropertyString(iDvStack.Env(), new ParameterString("ProductUrl"));
    iService->AddProperty(iPropertyProductUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyProductImageUri()
{
    iPropertyProductImageUri = new PropertyString(iDvStack.Env(), new ParameterString("ProductImageUri"));
    iService->AddProperty(iPropertyProductImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyAttributes()
{
    iPropertyAttributes = new PropertyString(iDvStack.Env(), new ParameterString("Attributes"));
    iService->AddProperty(iPropertyAttributes); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyQueryPort()
{
    iPropertyQueryPort = new PropertyUint(iDvStack.Env(), new ParameterUint("QueryPort"));
    iService->AddProperty(iPropertyQueryPort); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyBrowsePort()
{
    iPropertyBrowsePort = new PropertyUint(iDvStack.Env(), new ParameterUint("BrowsePort"));
    iService->AddProperty(iPropertyBrowsePort); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnablePropertyUpdateCount()
{
    iPropertyUpdateCount = new PropertyUint(iDvStack.Env(), new ParameterUint("UpdateCount"));
    iService->AddProperty(iPropertyUpdateCount); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1::EnableActionManufacturer()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Manufacturer");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyManufacturerName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyManufacturerInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyManufacturerUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyManufacturerImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1::DoManufacturer);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1::EnableActionModel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Model");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyModelName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyModelInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyModelUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyModelImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1::DoModel);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1::EnableActionProduct()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Product");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyProductName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyProductInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyProductUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyProductImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1::DoProduct);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1::EnableActionAttributes()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Attributes");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAttributes));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1::DoAttributes);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1::EnableActionQueryPort()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("QueryPort");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyQueryPort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1::DoQueryPort);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1::EnableActionBrowsePort()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BrowsePort");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyBrowsePort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1::DoBrowsePort);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1::EnableActionUpdateCount()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("UpdateCount");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyUpdateCount));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1::DoUpdateCount);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoManufacturer(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respInfo(aInvocation, "Info");
    DviInvocationResponseString respUrl(aInvocation, "Url");
    DviInvocationResponseString respImageUri(aInvocation, "ImageUri");
    Manufacturer(invocation, respName, respInfo, respUrl, respImageUri);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoModel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respInfo(aInvocation, "Info");
    DviInvocationResponseString respUrl(aInvocation, "Url");
    DviInvocationResponseString respImageUri(aInvocation, "ImageUri");
    Model(invocation, respName, respInfo, respUrl, respImageUri);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoProduct(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respInfo(aInvocation, "Info");
    DviInvocationResponseString respUrl(aInvocation, "Url");
    DviInvocationResponseString respImageUri(aInvocation, "ImageUri");
    Product(invocation, respName, respInfo, respUrl, respImageUri);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoAttributes(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    Attributes(invocation, respValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoQueryPort(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    QueryPort(invocation, respValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoBrowsePort(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    BrowsePort(invocation, respValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoUpdateCount(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    UpdateCount(invocation, respValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::Manufacturer(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aName*/, IDvInvocationResponseString& /*aInfo*/, IDvInvocationResponseString& /*aUrl*/, IDvInvocationResponseString& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1::Model(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aName*/, IDvInvocationResponseString& /*aInfo*/, IDvInvocationResponseString& /*aUrl*/, IDvInvocationResponseString& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1::Product(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aName*/, IDvInvocationResponseString& /*aInfo*/, IDvInvocationResponseString& /*aUrl*/, IDvInvocationResponseString& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1::Attributes(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1::QueryPort(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1::BrowsePort(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1::UpdateCount(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

