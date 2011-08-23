#include "DvAvOpenhomeOrgProduct1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyManufacturerName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerName, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyManufacturerName(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerName->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyManufacturerInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerInfo, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyManufacturerInfo(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerInfo->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyManufacturerUrl(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerUrl, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyManufacturerUrl(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerUrl->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyManufacturerImageUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyManufacturerImageUri, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyManufacturerImageUri(Brhz& aValue)
{
    aValue.Set(iPropertyManufacturerImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyModelName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelName, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyModelName(Brhz& aValue)
{
    aValue.Set(iPropertyModelName->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyModelInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelInfo, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyModelInfo(Brhz& aValue)
{
    aValue.Set(iPropertyModelInfo->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyModelUrl(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelUrl, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyModelUrl(Brhz& aValue)
{
    aValue.Set(iPropertyModelUrl->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyModelImageUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyModelImageUri, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyModelImageUri(Brhz& aValue)
{
    aValue.Set(iPropertyModelImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyProductRoom(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductRoom, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyProductRoom(Brhz& aValue)
{
    aValue.Set(iPropertyProductRoom->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyProductName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductName, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyProductName(Brhz& aValue)
{
    aValue.Set(iPropertyProductName->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyProductInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductInfo, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyProductInfo(Brhz& aValue)
{
    aValue.Set(iPropertyProductInfo->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyProductUrl(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductUrl, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyProductUrl(Brhz& aValue)
{
    aValue.Set(iPropertyProductUrl->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyProductImageUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProductImageUri, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyProductImageUri(Brhz& aValue)
{
    aValue.Set(iPropertyProductImageUri->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyStandby(TBool aValue)
{
    return SetPropertyBool(*iPropertyStandby, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyStandby(TBool& aValue)
{
    aValue = iPropertyStandby->Value();
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertySourceIndex(TUint aValue)
{
    return SetPropertyUint(*iPropertySourceIndex, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertySourceIndex(TUint& aValue)
{
    aValue = iPropertySourceIndex->Value();
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertySourceCount(TUint aValue)
{
    return SetPropertyUint(*iPropertySourceCount, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertySourceCount(TUint& aValue)
{
    aValue = iPropertySourceCount->Value();
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertySourceXml(const Brx& aValue)
{
    return SetPropertyString(*iPropertySourceXml, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertySourceXml(Brhz& aValue)
{
    aValue.Set(iPropertySourceXml->Value());
}

TBool DvProviderAvOpenhomeOrgProduct1::SetPropertyAttributes(const Brx& aValue)
{
    return SetPropertyString(*iPropertyAttributes, aValue);
}

void DvProviderAvOpenhomeOrgProduct1::GetPropertyAttributes(Brhz& aValue)
{
    aValue.Set(iPropertyAttributes->Value());
}

DvProviderAvOpenhomeOrgProduct1::DvProviderAvOpenhomeOrgProduct1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Product", 1)
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
    iPropertyProductRoom = new PropertyString(new ParameterString("ProductRoom"));
    iService->AddProperty(iPropertyProductRoom); // passes ownership
    iPropertyProductName = new PropertyString(new ParameterString("ProductName"));
    iService->AddProperty(iPropertyProductName); // passes ownership
    iPropertyProductInfo = new PropertyString(new ParameterString("ProductInfo"));
    iService->AddProperty(iPropertyProductInfo); // passes ownership
    iPropertyProductUrl = new PropertyString(new ParameterString("ProductUrl"));
    iService->AddProperty(iPropertyProductUrl); // passes ownership
    iPropertyProductImageUri = new PropertyString(new ParameterString("ProductImageUri"));
    iService->AddProperty(iPropertyProductImageUri); // passes ownership
    iPropertyStandby = new PropertyBool(new ParameterBool("Standby"));
    iService->AddProperty(iPropertyStandby); // passes ownership
    iPropertySourceIndex = new PropertyUint(new ParameterUint("SourceIndex"));
    iService->AddProperty(iPropertySourceIndex); // passes ownership
    iPropertySourceCount = new PropertyUint(new ParameterUint("SourceCount"));
    iService->AddProperty(iPropertySourceCount); // passes ownership
    iPropertySourceXml = new PropertyString(new ParameterString("SourceXml"));
    iService->AddProperty(iPropertySourceXml); // passes ownership
    iPropertyAttributes = new PropertyString(new ParameterString("Attributes"));
    iService->AddProperty(iPropertyAttributes); // passes ownership
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionManufacturer()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Manufacturer");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyManufacturerName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyManufacturerInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyManufacturerUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyManufacturerImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoManufacturer);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionModel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Model");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyModelName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyModelInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyModelUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyModelImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoModel);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionProduct()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Product");
    action->AddOutputParameter(new ParameterRelated("Room", *iPropertyProductRoom));
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyProductName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyProductInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyProductUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyProductImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoProduct);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionStandby()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Standby");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoStandby);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionSetStandby()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetStandby");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyStandby));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoSetStandby);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionSourceCount()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SourceCount");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertySourceCount));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoSourceCount);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionSourceXml()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SourceXml");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertySourceXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoSourceXml);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionSourceIndex()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SourceIndex");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertySourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionSetSourceIndex()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSourceIndex");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertySourceIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoSetSourceIndex);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionSetSourceIndexByName()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSourceIndexByName");
    action->AddInputParameter(new ParameterString("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoSetSourceIndexByName);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionSource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Source");
    action->AddInputParameter(new ParameterRelated("Index", *iPropertySourceIndex));
    action->AddOutputParameter(new ParameterString("SystemName"));
    action->AddOutputParameter(new ParameterString("Type"));
    action->AddOutputParameter(new ParameterString("Name"));
    action->AddOutputParameter(new ParameterBool("Visible"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoSource);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionAttributes()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Attributes");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAttributes));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoAttributes);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::EnableActionSourceXmlChangeCount()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SourceXmlChangeCount");
    action->AddOutputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgProduct1::DoSourceXmlChangeCount);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgProduct1::DoManufacturer(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respInfo(aInvocation, "Info");
    DviInvocationResponseString respUrl(aInvocation, "Url");
    DviInvocationResponseString respImageUri(aInvocation, "ImageUri");
    Manufacturer(resp, aVersion, respName, respInfo, respUrl, respImageUri);
}

void DvProviderAvOpenhomeOrgProduct1::DoModel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respInfo(aInvocation, "Info");
    DviInvocationResponseString respUrl(aInvocation, "Url");
    DviInvocationResponseString respImageUri(aInvocation, "ImageUri");
    Model(resp, aVersion, respName, respInfo, respUrl, respImageUri);
}

void DvProviderAvOpenhomeOrgProduct1::DoProduct(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respRoom(aInvocation, "Room");
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respInfo(aInvocation, "Info");
    DviInvocationResponseString respUrl(aInvocation, "Url");
    DviInvocationResponseString respImageUri(aInvocation, "ImageUri");
    Product(resp, aVersion, respRoom, respName, respInfo, respUrl, respImageUri);
}

void DvProviderAvOpenhomeOrgProduct1::DoStandby(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseBool respValue(aInvocation, "Value");
    Standby(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgProduct1::DoSetStandby(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetStandby(resp, aVersion, Value);
}

void DvProviderAvOpenhomeOrgProduct1::DoSourceCount(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    SourceCount(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgProduct1::DoSourceXml(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    SourceXml(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgProduct1::DoSourceIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    SourceIndex(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgProduct1::DoSetSourceIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetSourceIndex(resp, aVersion, Value);
}

void DvProviderAvOpenhomeOrgProduct1::DoSetSourceIndexByName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Value;
    aInvocation.InvocationReadString("Value", Value);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetSourceIndexByName(resp, aVersion, Value);
}

void DvProviderAvOpenhomeOrgProduct1::DoSource(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respSystemName(aInvocation, "SystemName");
    DviInvocationResponseString respType(aInvocation, "Type");
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseBool respVisible(aInvocation, "Visible");
    Source(resp, aVersion, Index, respSystemName, respType, respName, respVisible);
}

void DvProviderAvOpenhomeOrgProduct1::DoAttributes(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    Attributes(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgProduct1::DoSourceXmlChangeCount(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    SourceXmlChangeCount(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgProduct1::Manufacturer(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aName*/, IDvInvocationResponseString& /*aInfo*/, IDvInvocationResponseString& /*aUrl*/, IDvInvocationResponseString& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::Model(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aName*/, IDvInvocationResponseString& /*aInfo*/, IDvInvocationResponseString& /*aUrl*/, IDvInvocationResponseString& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::Product(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aRoom*/, IDvInvocationResponseString& /*aName*/, IDvInvocationResponseString& /*aInfo*/, IDvInvocationResponseString& /*aUrl*/, IDvInvocationResponseString& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::Standby(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::SetStandby(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::SourceCount(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::SourceXml(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::SourceIndex(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::SetSourceIndex(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::SetSourceIndexByName(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::Source(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aIndex*/, IDvInvocationResponseString& /*aSystemName*/, IDvInvocationResponseString& /*aType*/, IDvInvocationResponseString& /*aName*/, IDvInvocationResponseBool& /*aVisible*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::Attributes(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgProduct1::SourceXmlChangeCount(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

