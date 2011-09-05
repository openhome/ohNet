#include "DvAvOpenhomeOrgMediaServer1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyManufacturerName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyManufacturerName(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyManufacturerInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyManufacturerInfo(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyManufacturerUrl(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyManufacturerUrl(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyManufacturerImageUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyManufacturerImageUri(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyModelName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyModelName(Brhz& aValue)
{
    aValue.Set(iPropertyModelName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyModelInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyModelInfo(Brhz& aValue)
{
    aValue.Set(iPropertyModelInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyModelUrl(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyModelUrl(Brhz& aValue)
{
    aValue.Set(iPropertyModelUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyModelImageUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyModelImageUri(Brhz& aValue)
{
    aValue.Set(iPropertyModelImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyProductName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductName, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyProductName(Brhz& aValue)
{
    aValue.Set(iPropertyProductName->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyProductInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductInfo, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyProductInfo(Brhz& aValue)
{
    aValue.Set(iPropertyProductInfo->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyProductUrl(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductUrl, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyProductUrl(Brhz& aValue)
{
    aValue.Set(iPropertyProductUrl->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyProductImageUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductImageUri, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyProductImageUri(Brhz& aValue)
{
    aValue.Set(iPropertyProductImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgMediaServer1::SetPropertyAttributes(const Brx& aValue)
{
    return SetPropertyString(*iPropertyAttributes, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::GetPropertyAttributes(Brhz& aValue)
{
    aValue.Set(iPropertyAttributes->Value());
}

DvProviderAvOpenhomeOrgMediaServer1::DvProviderAvOpenhomeOrgMediaServer1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "MediaServer", 1)
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

void DvProviderAvOpenhomeOrgMediaServer1::EnableActionQuery()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Query");
    action->AddInputParameter(new ParameterString("Request"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1::DoQuery);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoManufacturer(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respName(aInvocation, "Name");
    InvocationResponseString respInfo(aInvocation, "Info");
    InvocationResponseString respUrl(aInvocation, "Url");
    InvocationResponseString respImageUri(aInvocation, "ImageUri");
    Manufacturer(resp, aVersion, respName, respInfo, respUrl, respImageUri);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoModel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respName(aInvocation, "Name");
    InvocationResponseString respInfo(aInvocation, "Info");
    InvocationResponseString respUrl(aInvocation, "Url");
    InvocationResponseString respImageUri(aInvocation, "ImageUri");
    Model(resp, aVersion, respName, respInfo, respUrl, respImageUri);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoProduct(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respName(aInvocation, "Name");
    InvocationResponseString respInfo(aInvocation, "Info");
    InvocationResponseString respUrl(aInvocation, "Url");
    InvocationResponseString respImageUri(aInvocation, "ImageUri");
    Product(resp, aVersion, respName, respInfo, respUrl, respImageUri);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoAttributes(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respValue(aInvocation, "Value");
    Attributes(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgMediaServer1::DoQuery(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Request;
    aInvocation.InvocationReadString("Request", Request);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respResult(aInvocation, "Result");
    Query(resp, aVersion, Request, respResult);
}

void DvProviderAvOpenhomeOrgMediaServer1::Manufacturer(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aName*/, IInvocationResponseString& /*aInfo*/, IInvocationResponseString& /*aUrl*/, IInvocationResponseString& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1::Model(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aName*/, IInvocationResponseString& /*aInfo*/, IInvocationResponseString& /*aUrl*/, IInvocationResponseString& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1::Product(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aName*/, IInvocationResponseString& /*aInfo*/, IInvocationResponseString& /*aUrl*/, IInvocationResponseString& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1::Attributes(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1::Query(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRequest*/, IInvocationResponseString& /*aResult*/)
{
    ASSERTS();
}

