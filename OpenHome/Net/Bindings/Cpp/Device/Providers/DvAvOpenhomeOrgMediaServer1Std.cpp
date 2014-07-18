#include "DvAvOpenhomeOrgMediaServer1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerName(const std::string& aValue)
{
    ASSERT(iPropertyManufacturerName != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyManufacturerName, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyManufacturerName(std::string& aValue)
{
    ASSERT(iPropertyManufacturerName != NULL);
    const Brx& val = iPropertyManufacturerName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerInfo(const std::string& aValue)
{
    ASSERT(iPropertyManufacturerInfo != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyManufacturerInfo, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyManufacturerInfo(std::string& aValue)
{
    ASSERT(iPropertyManufacturerInfo != NULL);
    const Brx& val = iPropertyManufacturerInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerUrl(const std::string& aValue)
{
    ASSERT(iPropertyManufacturerUrl != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyManufacturerUrl, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyManufacturerUrl(std::string& aValue)
{
    ASSERT(iPropertyManufacturerUrl != NULL);
    const Brx& val = iPropertyManufacturerUrl->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerImageUri(const std::string& aValue)
{
    ASSERT(iPropertyManufacturerImageUri != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyManufacturerImageUri, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyManufacturerImageUri(std::string& aValue)
{
    ASSERT(iPropertyManufacturerImageUri != NULL);
    const Brx& val = iPropertyManufacturerImageUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelName(const std::string& aValue)
{
    ASSERT(iPropertyModelName != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyModelName, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyModelName(std::string& aValue)
{
    ASSERT(iPropertyModelName != NULL);
    const Brx& val = iPropertyModelName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelInfo(const std::string& aValue)
{
    ASSERT(iPropertyModelInfo != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyModelInfo, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyModelInfo(std::string& aValue)
{
    ASSERT(iPropertyModelInfo != NULL);
    const Brx& val = iPropertyModelInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelUrl(const std::string& aValue)
{
    ASSERT(iPropertyModelUrl != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyModelUrl, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyModelUrl(std::string& aValue)
{
    ASSERT(iPropertyModelUrl != NULL);
    const Brx& val = iPropertyModelUrl->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelImageUri(const std::string& aValue)
{
    ASSERT(iPropertyModelImageUri != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyModelImageUri, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyModelImageUri(std::string& aValue)
{
    ASSERT(iPropertyModelImageUri != NULL);
    const Brx& val = iPropertyModelImageUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductName(const std::string& aValue)
{
    ASSERT(iPropertyProductName != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProductName, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyProductName(std::string& aValue)
{
    ASSERT(iPropertyProductName != NULL);
    const Brx& val = iPropertyProductName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductInfo(const std::string& aValue)
{
    ASSERT(iPropertyProductInfo != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProductInfo, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyProductInfo(std::string& aValue)
{
    ASSERT(iPropertyProductInfo != NULL);
    const Brx& val = iPropertyProductInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductUrl(const std::string& aValue)
{
    ASSERT(iPropertyProductUrl != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProductUrl, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyProductUrl(std::string& aValue)
{
    ASSERT(iPropertyProductUrl != NULL);
    const Brx& val = iPropertyProductUrl->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductImageUri(const std::string& aValue)
{
    ASSERT(iPropertyProductImageUri != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProductImageUri, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyProductImageUri(std::string& aValue)
{
    ASSERT(iPropertyProductImageUri != NULL);
    const Brx& val = iPropertyProductImageUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyAttributes(const std::string& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyAttributes, buf);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyAttributes(std::string& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    const Brx& val = iPropertyAttributes->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyQueryPort(uint32_t aValue)
{
    ASSERT(iPropertyQueryPort != NULL);
    return SetPropertyUint(*iPropertyQueryPort, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyQueryPort(uint32_t& aValue)
{
    ASSERT(iPropertyQueryPort != NULL);
    aValue = iPropertyQueryPort->Value();
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyBrowsePort(uint32_t aValue)
{
    ASSERT(iPropertyBrowsePort != NULL);
    return SetPropertyUint(*iPropertyBrowsePort, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyBrowsePort(uint32_t& aValue)
{
    ASSERT(iPropertyBrowsePort != NULL);
    aValue = iPropertyBrowsePort->Value();
}

bool DvProviderAvOpenhomeOrgMediaServer1Cpp::SetPropertyUpdateCount(uint32_t aValue)
{
    ASSERT(iPropertyUpdateCount != NULL);
    return SetPropertyUint(*iPropertyUpdateCount, aValue);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::GetPropertyUpdateCount(uint32_t& aValue)
{
    ASSERT(iPropertyUpdateCount != NULL);
    aValue = iPropertyUpdateCount->Value();
}

DvProviderAvOpenhomeOrgMediaServer1Cpp::DvProviderAvOpenhomeOrgMediaServer1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "MediaServer", 1)
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

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyManufacturerName()
{
    iPropertyManufacturerName = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerName"));
    iService->AddProperty(iPropertyManufacturerName); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyManufacturerInfo()
{
    iPropertyManufacturerInfo = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerInfo"));
    iService->AddProperty(iPropertyManufacturerInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyManufacturerUrl()
{
    iPropertyManufacturerUrl = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerUrl"));
    iService->AddProperty(iPropertyManufacturerUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyManufacturerImageUri()
{
    iPropertyManufacturerImageUri = new PropertyString(iDvStack.Env(), new ParameterString("ManufacturerImageUri"));
    iService->AddProperty(iPropertyManufacturerImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyModelName()
{
    iPropertyModelName = new PropertyString(iDvStack.Env(), new ParameterString("ModelName"));
    iService->AddProperty(iPropertyModelName); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyModelInfo()
{
    iPropertyModelInfo = new PropertyString(iDvStack.Env(), new ParameterString("ModelInfo"));
    iService->AddProperty(iPropertyModelInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyModelUrl()
{
    iPropertyModelUrl = new PropertyString(iDvStack.Env(), new ParameterString("ModelUrl"));
    iService->AddProperty(iPropertyModelUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyModelImageUri()
{
    iPropertyModelImageUri = new PropertyString(iDvStack.Env(), new ParameterString("ModelImageUri"));
    iService->AddProperty(iPropertyModelImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyProductName()
{
    iPropertyProductName = new PropertyString(iDvStack.Env(), new ParameterString("ProductName"));
    iService->AddProperty(iPropertyProductName); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyProductInfo()
{
    iPropertyProductInfo = new PropertyString(iDvStack.Env(), new ParameterString("ProductInfo"));
    iService->AddProperty(iPropertyProductInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyProductUrl()
{
    iPropertyProductUrl = new PropertyString(iDvStack.Env(), new ParameterString("ProductUrl"));
    iService->AddProperty(iPropertyProductUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyProductImageUri()
{
    iPropertyProductImageUri = new PropertyString(iDvStack.Env(), new ParameterString("ProductImageUri"));
    iService->AddProperty(iPropertyProductImageUri); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyAttributes()
{
    iPropertyAttributes = new PropertyString(iDvStack.Env(), new ParameterString("Attributes"));
    iService->AddProperty(iPropertyAttributes); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyQueryPort()
{
    iPropertyQueryPort = new PropertyUint(iDvStack.Env(), new ParameterUint("QueryPort"));
    iService->AddProperty(iPropertyQueryPort); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyBrowsePort()
{
    iPropertyBrowsePort = new PropertyUint(iDvStack.Env(), new ParameterUint("BrowsePort"));
    iService->AddProperty(iPropertyBrowsePort); // passes ownership
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnablePropertyUpdateCount()
{
    iPropertyUpdateCount = new PropertyUint(iDvStack.Env(), new ParameterUint("UpdateCount"));
    iService->AddProperty(iPropertyUpdateCount); // passes ownership
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

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnableActionQueryPort()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("QueryPort");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyQueryPort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1Cpp::DoQueryPort);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnableActionBrowsePort()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BrowsePort");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyBrowsePort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1Cpp::DoBrowsePort);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::EnableActionUpdateCount()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("UpdateCount");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyUpdateCount));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgMediaServer1Cpp::DoUpdateCount);
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

void DvProviderAvOpenhomeOrgMediaServer1Cpp::DoQueryPort(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    DvInvocationStd invocation(aInvocation);
    QueryPort(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::DoBrowsePort(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    DvInvocationStd invocation(aInvocation);
    BrowsePort(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::DoUpdateCount(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    DvInvocationStd invocation(aInvocation);
    UpdateCount(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
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

void DvProviderAvOpenhomeOrgMediaServer1Cpp::QueryPort(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::BrowsePort(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgMediaServer1Cpp::UpdateCount(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

