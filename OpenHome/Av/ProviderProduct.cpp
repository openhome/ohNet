#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvAvOpenhomeOrgProduct1.h>
#include <OpenHome/Av/ProviderProduct.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/FaultCode.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

ProviderProduct::ProviderProduct(Net::DvDevice& aDevice, Av::Product& aProduct)
    : DvProviderAvOpenhomeOrgProduct1(aDevice)
    , iProduct(aProduct)
{
    EnablePropertyManufacturerName();
    EnablePropertyManufacturerInfo();
    EnablePropertyManufacturerUrl();
    EnablePropertyManufacturerImageUri();
    EnablePropertyModelName();
    EnablePropertyModelInfo();
    EnablePropertyModelUrl();
    EnablePropertyModelImageUri();
    EnablePropertyProductRoom();
    EnablePropertyProductName();
    EnablePropertyProductInfo();
    EnablePropertyProductUrl();
    EnablePropertyProductImageUri();
    EnablePropertyStandby();
    EnablePropertySourceIndex();
    EnablePropertySourceCount();
    EnablePropertySourceXml();
    EnablePropertyAttributes();

    EnableActionManufacturer();
    EnableActionModel();
    EnableActionProduct();
    EnableActionStandby();
    EnableActionSetStandby();
    EnableActionSourceCount();
    EnableActionSourceXml();
    EnableActionSourceIndex();
    EnableActionSetSourceIndex();
    EnableActionSetSourceIndexByName();
    EnableActionSource();
    EnableActionAttributes();
    EnableActionSourceXmlChangeCount();

    {
        Brn name;
        Brn info;
        Brn url;
        Brn imageUri;
        iProduct.GetManufacturerDetails(name, info, url, imageUri);
        SetPropertyManufacturerName(name);
        SetPropertyManufacturerInfo(info);
        SetPropertyManufacturerUrl(url);
        SetPropertyManufacturerImageUri(imageUri);

        iProduct.GetModelDetails(name, info, url, imageUri);
        SetPropertyModelName(name);
        SetPropertyModelInfo(info);
        SetPropertyModelUrl(url);
        SetPropertyModelImageUri(imageUri);
    }

    {
        Bws<Product::kMaxRoomBytes> room;
        Bws<Product::kMaxNameBytes> name;
        Brn info;
        Brn imageUri;
        iProduct.GetProductDetails(room, name, info, imageUri);
        SetPropertyProductRoom(room);
        SetPropertyProductName(name);
        SetPropertyProductInfo(info);
        // TODO (varies between adapter so not a suitable property) - SetPropertyProductUrl();
        SetPropertyProductImageUri(imageUri);
    }

    // TODO - SetPropertyStandby(TBool aValue);
    SetPropertySourceIndex(iProduct.CurrentSourceIndex());
    SetPropertySourceCount(iProduct.SourceCount());
    // TODO - SetPropertySourceXml(const Brx& aValue);
    // TODO - SetPropertyAttributes(const Brx& aValue);
}

ProviderProduct::~ProviderProduct()
{
}

void ProviderProduct::Manufacturer(IDvInvocation& aInvocation, IDvInvocationResponseString& aName, IDvInvocationResponseString& aInfo, IDvInvocationResponseString& aUrl, IDvInvocationResponseString& aImageUri)
{
    Brn name;
    Brn info;
    Brn url;
    Brn imageUri;
    iProduct.GetManufacturerDetails(name, info, url, imageUri);

    aInvocation.StartResponse();
    aName.Write(name);
    aName.WriteFlush();
    aInfo.Write(info);
    aInfo.WriteFlush();
    aUrl.Write(url);
    aUrl.WriteFlush();
    aImageUri.Write(imageUri);
    aImageUri.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderProduct::Model(IDvInvocation& aInvocation, IDvInvocationResponseString& aName, IDvInvocationResponseString& aInfo, IDvInvocationResponseString& aUrl, IDvInvocationResponseString& aImageUri)
{
    Brn name;
    Brn info;
    Brn url;
    Brn imageUri;
    iProduct.GetModelDetails(name, info, url, imageUri);

    aInvocation.StartResponse();
    aName.Write(name);
    aName.WriteFlush();
    aInfo.Write(info);
    aInfo.WriteFlush();
    aUrl.Write(url);
    aUrl.WriteFlush();
    aImageUri.Write(imageUri);
    aImageUri.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderProduct::Product(IDvInvocation& aInvocation, IDvInvocationResponseString& aRoom, IDvInvocationResponseString& aName, IDvInvocationResponseString& aInfo, IDvInvocationResponseString& aUrl, IDvInvocationResponseString& aImageUri)
{
    Bws<Product::kMaxRoomBytes> room;
    Bws<Product::kMaxNameBytes> name;
    Brn info;
    Brn imageUri;
    iProduct.GetProductDetails(room, name, info, imageUri);
    Brn presentationUrl(aInvocation.ResourceUriPrefix());

    aInvocation.StartResponse();
    aRoom.Write(room);
    aRoom.WriteFlush();
    aName.Write(name);
    aName.WriteFlush();
    aInfo.Write(info);
    aInfo.WriteFlush();
    aUrl.Write(presentationUrl);
    aUrl.WriteFlush();
    aImageUri.Write(imageUri);
    aImageUri.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderProduct::Standby(IDvInvocation& aInvocation, IDvInvocationResponseBool& /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented);
}

void ProviderProduct::SetStandby(IDvInvocation& aInvocation, TBool /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented);
}

void ProviderProduct::SourceCount(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    aInvocation.StartResponse();
    aValue.Write(iProduct.SourceCount());
    aInvocation.EndResponse();
}

void ProviderProduct::SourceXml(IDvInvocation& aInvocation, IDvInvocationResponseString& /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderProduct::SourceIndex(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    aInvocation.StartResponse();
    aValue.Write(iProduct.CurrentSourceIndex());
    aInvocation.EndResponse();
}

void ProviderProduct::SetSourceIndex(IDvInvocation& aInvocation, TUint aValue)
{
    aInvocation.StartResponse();
    try {
        iProduct.SetCurrentSource(aValue);
        aInvocation.EndResponse();
    }
    catch(AvSourceNotFound& ) {
        FaultCode::Report(aInvocation, FaultCode::kSourceNotFound);
    }
}

void ProviderProduct::SetSourceIndexByName(IDvInvocation& aInvocation, const Brx& aValue)
{
    aInvocation.StartResponse();
    try {
        iProduct.SetCurrentSource(aValue);
        aInvocation.EndResponse();
    }
    catch(AvSourceNotFound& ) {
        FaultCode::Report(aInvocation, FaultCode::kSourceNotFound);
    }
    aInvocation.EndResponse();
}

void ProviderProduct::Source(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseString& aSystemName, IDvInvocationResponseString& aType, IDvInvocationResponseString& aName, IDvInvocationResponseBool& aVisible)
{
    Bws<Source::kMaxSystemNameBytes> systemName;
    Bws<Source::kMaxSourceTypeBytes> type;
    Bws<Source::kMaxSourceTypeBytes> name;
    TBool visible;
    aInvocation.StartResponse();
    try {
        iProduct.GetSourceDetails(aIndex, systemName, type, name, visible);
    }
    catch(AvSourceNotFound& ) {
        FaultCode::Report(aInvocation, FaultCode::kSourceNotFound);
    }

    aSystemName.Write(systemName);
    aSystemName.WriteFlush();
    aType.Write(type);
    aType.WriteFlush();
    aName.Write(name);
    aName.WriteFlush();
    aVisible.Write(visible);
    aInvocation.EndResponse();
}

void ProviderProduct::Attributes(IDvInvocation& aInvocation, IDvInvocationResponseString& /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented);
}

void ProviderProduct::SourceXmlChangeCount(IDvInvocation& aInvocation, IDvInvocationResponseUint& /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented);
}
