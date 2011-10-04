#include "DvAvOpenhomeOrgMediaServer1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerName(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyManufacturerName, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyManufacturerName(std::string& aValue)
{
    const Brx& val = iPropertyManufacturerName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerInfo(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyManufacturerInfo, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyManufacturerInfo(std::string& aValue)
{
    const Brx& val = iPropertyManufacturerInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerUrl(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyManufacturerUrl, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyManufacturerUrl(std::string& aValue)
{
    const Brx& val = iPropertyManufacturerUrl->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerImageUri(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyManufacturerImageUri, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyManufacturerImageUri(std::string& aValue)
{
    const Brx& val = iPropertyManufacturerImageUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelName(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyModelName, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyModelName(std::string& aValue)
{
    const Brx& val = iPropertyModelName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelInfo(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyModelInfo, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyModelInfo(std::string& aValue)
{
    const Brx& val = iPropertyModelInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelUrl(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyModelUrl, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyModelUrl(std::string& aValue)
{
    const Brx& val = iPropertyModelUrl->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelImageUri(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyModelImageUri, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyModelImageUri(std::string& aValue)
{
    const Brx& val = iPropertyModelImageUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductName(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProductName, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyProductName(std::string& aValue)
{
    const Brx& val = iPropertyProductName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductInfo(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProductInfo, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyProductInfo(std::string& aValue)
{
    const Brx& val = iPropertyProductInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductUrl(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProductUrl, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyProductUrl(std::string& aValue)
{
    const Brx& val = iPropertyProductUrl->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductImageUri(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProductImageUri, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyProductImageUri(std::string& aValue)
{
    const Brx& val = iPropertyProductImageUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyAttributes(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyAttributes, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyAttributes(std::string& aValue)
{
    const Brx& val = iPropertyAttributes->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderAvOpenhomeOrgMediaServer1Cpp::DvProviderAvOpenhomeOrgMediaServer1Cpp(DvDeviceStd& aDevice)
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

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnableActionManufacturer()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Manufacturer");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyManufacturerName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyManufacturerInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyManufacturerUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyManufacturerImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1Cpp::DoManufacturer);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnableActionModel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Model");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyModelName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyModelInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyModelUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyModelImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1Cpp::DoModel);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnableActionProduct()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Product");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyProductName));
    action->AddOutputParameter(new ParameterRelated("Info", *iPropertyProductInfo));
    action->AddOutputParameter(new ParameterRelated("Url", *iPropertyProductUrl));
    action->AddOutputParameter(new ParameterRelated("ImageUri", *iPropertyProductImageUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1Cpp::DoProduct);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnableActionAttributes()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Attributes");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAttributes));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1Cpp::DoAttributes);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnableActionQuery()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Query");
    action->AddInputParameter(new ParameterString("Request"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1Cpp::DoQuery);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::DoManufacturer(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respName;
    std::string respInfo;
    std::string respUrl;
    std::string respImageUri;
    DvInvocationStd invocation(aInvocation);
    Manufacturer(invocation, respName, respInfo, respUrl, respImageUri);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterName(aInvocation, "Name");
    Brn buf_Name((const TByte*)respName.c_str(), (TUint)respName.length());
    respWriterName.Write(buf_Name);
    aInvocation.InvocationWriteStringEnd("Name");
    DviInvocationResponseString respWriterInfo(aInvocation, "Info");
    Brn buf_Info((const TByte*)respInfo.c_str(), (TUint)respInfo.length());
    respWriterInfo.Write(buf_Info);
    aInvocation.InvocationWriteStringEnd("Info");
    DviInvocationResponseString respWriterUrl(aInvocation, "Url");
    Brn buf_Url((const TByte*)respUrl.c_str(), (TUint)respUrl.length());
    respWriterUrl.Write(buf_Url);
    aInvocation.InvocationWriteStringEnd("Url");
    DviInvocationResponseString respWriterImageUri(aInvocation, "ImageUri");
    Brn buf_ImageUri((const TByte*)respImageUri.c_str(), (TUint)respImageUri.length());
    respWriterImageUri.Write(buf_ImageUri);
    aInvocation.InvocationWriteStringEnd("ImageUri");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::DoModel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respName;
    std::string respInfo;
    std::string respUrl;
    std::string respImageUri;
    DvInvocationStd invocation(aInvocation);
    Model(invocation, respName, respInfo, respUrl, respImageUri);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterName(aInvocation, "Name");
    Brn buf_Name((const TByte*)respName.c_str(), (TUint)respName.length());
    respWriterName.Write(buf_Name);
    aInvocation.InvocationWriteStringEnd("Name");
    DviInvocationResponseString respWriterInfo(aInvocation, "Info");
    Brn buf_Info((const TByte*)respInfo.c_str(), (TUint)respInfo.length());
    respWriterInfo.Write(buf_Info);
    aInvocation.InvocationWriteStringEnd("Info");
    DviInvocationResponseString respWriterUrl(aInvocation, "Url");
    Brn buf_Url((const TByte*)respUrl.c_str(), (TUint)respUrl.length());
    respWriterUrl.Write(buf_Url);
    aInvocation.InvocationWriteStringEnd("Url");
    DviInvocationResponseString respWriterImageUri(aInvocation, "ImageUri");
    Brn buf_ImageUri((const TByte*)respImageUri.c_str(), (TUint)respImageUri.length());
    respWriterImageUri.Write(buf_ImageUri);
    aInvocation.InvocationWriteStringEnd("ImageUri");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::DoProduct(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respName;
    std::string respInfo;
    std::string respUrl;
    std::string respImageUri;
    DvInvocationStd invocation(aInvocation);
    Product(invocation, respName, respInfo, respUrl, respImageUri);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterName(aInvocation, "Name");
    Brn buf_Name((const TByte*)respName.c_str(), (TUint)respName.length());
    respWriterName.Write(buf_Name);
    aInvocation.InvocationWriteStringEnd("Name");
    DviInvocationResponseString respWriterInfo(aInvocation, "Info");
    Brn buf_Info((const TByte*)respInfo.c_str(), (TUint)respInfo.length());
    respWriterInfo.Write(buf_Info);
    aInvocation.InvocationWriteStringEnd("Info");
    DviInvocationResponseString respWriterUrl(aInvocation, "Url");
    Brn buf_Url((const TByte*)respUrl.c_str(), (TUint)respUrl.length());
    respWriterUrl.Write(buf_Url);
    aInvocation.InvocationWriteStringEnd("Url");
    DviInvocationResponseString respWriterImageUri(aInvocation, "ImageUri");
    Brn buf_ImageUri((const TByte*)respImageUri.c_str(), (TUint)respImageUri.length());
    respWriterImageUri.Write(buf_ImageUri);
    aInvocation.InvocationWriteStringEnd("ImageUri");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::DoAttributes(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    DvInvocationStd invocation(aInvocation);
    Attributes(invocation, respValue);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::DoQuery(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Request;
    aInvocation.InvocationReadString("Request", buf_Request);
    std::string Request((const char*)buf_Request.Ptr(), buf_Request.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    DvInvocationStd invocation(aInvocation);
    Query(invocation, Request, respResult);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::Manufacturer(IDvInvocationStd& /*aInvocation*/, std::string& /*aName*/, std::string& /*aInfo*/, std::string& /*aUrl*/, std::string& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::Model(IDvInvocationStd& /*aInvocation*/, std::string& /*aName*/, std::string& /*aInfo*/, std::string& /*aUrl*/, std::string& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::Product(IDvInvocationStd& /*aInvocation*/, std::string& /*aName*/, std::string& /*aInfo*/, std::string& /*aUrl*/, std::string& /*aImageUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::Attributes(IDvInvocationStd& /*aInvocation*/, std::string& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::Query(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRequest*/, std::string& /*aResult*/)
{
    ASSERTS();
}

