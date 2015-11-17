#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <Generated/DvAvOpenhomeOrgProduct1.h>
#include <OpenHome/Av/ProviderProduct.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/Utils/FaultCode.h>
#include <OpenHome/PowerManager.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

ProviderProduct::ProviderProduct(Net::DvDevice& aDevice, Av::Product& aProduct, IPowerManager& aPowerManager)
    : DvProviderAvOpenhomeOrgProduct1(aDevice)
    , iProduct(aProduct)
    , iPowerManager(aPowerManager)
    , iLock("PrPr")
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
        SetPropertyProductImageUri(imageUri);
    }
    const TChar* presentationUrl;
    aDevice.GetAttribute("Upnp.PresentationUrl", &presentationUrl);
    if (presentationUrl == nullptr) {
        presentationUrl = "";
    }
    SetPropertyProductUrl(Brn(presentationUrl));

    iStandbyObserver = aPowerManager.RegisterStandbyHandler(*this);
    iProduct.AddObserver(*this);
    iProduct.AddNameObserver(*this);
}

ProviderProduct::~ProviderProduct()
{
    delete iStandbyObserver;
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
    const TChar* p = aInvocation.ResourceUriPrefix();
    const Brx& presentationUrl = (p != nullptr) ? Brn(p) : Brx::Empty();

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

void ProviderProduct::Standby(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue)
{
    TBool standby;
    GetPropertyStandby(standby);
    aInvocation.StartResponse();
    aValue.Write(standby);
    aInvocation.EndResponse();
}

void ProviderProduct::SetStandby(IDvInvocation& aInvocation, TBool aValue)
{
    if (aValue) {
        iPowerManager.StandbyEnable();
    }
    else {
        iPowerManager.StandbyDisable(eStandbyDisableUser);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderProduct::SourceCount(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    aInvocation.StartResponse();
    aValue.Write(iProduct.SourceCount());
    aInvocation.EndResponse();
}

void ProviderProduct::SourceXml(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue)
{
    aInvocation.StartResponse();
    aValue.Write(iSourceXml);
    aValue.WriteFlush();
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
    try {
        iProduct.SetCurrentSource(aValue);
    }
    catch(AvSourceNotFound& ) {
        FaultCode::Report(aInvocation, FaultCode::kSourceNotFound);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderProduct::SetSourceIndexByName(IDvInvocation& aInvocation, const Brx& aValue)
{
    try {
        iProduct.SetCurrentSource(aValue);
    }
    catch(AvSourceNotFound& ) {
        FaultCode::Report(aInvocation, FaultCode::kSourceNotFound);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderProduct::Source(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseString& aSystemName, IDvInvocationResponseString& aType, IDvInvocationResponseString& aName, IDvInvocationResponseBool& aVisible)
{
    Bws<ISource::kMaxSystemNameBytes> systemName;
    Bws<ISource::kMaxSourceTypeBytes> type;
    Bws<ISource::kMaxSourceTypeBytes> name;
    TBool visible = false;
    try {
        iProduct.GetSourceDetails(aIndex, systemName, type, name, visible);
    }
    catch(AvSourceNotFound& ) {
        FaultCode::Report(aInvocation, FaultCode::kSourceNotFound);
    }

    aInvocation.StartResponse();
    aSystemName.Write(systemName);
    aSystemName.WriteFlush();
    aType.Write(type);
    aType.WriteFlush();
    aName.Write(name);
    aName.WriteFlush();
    aVisible.Write(visible);
    aInvocation.EndResponse();
}

void ProviderProduct::Attributes(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue)
{
    aInvocation.StartResponse();
    aValue.Write(iProduct.Attributes());
    aValue.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderProduct::SourceXmlChangeCount(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    aInvocation.StartResponse();
    aValue.Write(iProduct.SourceXmlChangeCount());
    aInvocation.EndResponse();
}

void ProviderProduct::Started()
{
    SetPropertySourceIndex(iProduct.CurrentSourceIndex());
    SetPropertySourceCount(iProduct.SourceCount());
    SetPropertyAttributes(iProduct.Attributes());
    SourceXmlChanged();
}

void ProviderProduct::SourceIndexChanged()
{
    SetPropertySourceIndex(iProduct.CurrentSourceIndex());
}

void ProviderProduct::SourceXmlChanged()
{
    iLock.Wait();
    iSourceXml.SetBytes(0);
    iProduct.GetSourceXml(iSourceXml);
    SetPropertySourceXml(iSourceXml);
    iLock.Signal();
}

void ProviderProduct::RoomChanged(const Brx& aRoom)
{
    SetPropertyProductRoom(aRoom);
}

void ProviderProduct::NameChanged(const Brx& aName)
{
    SetPropertyProductName(aName);
}

void ProviderProduct::StandbyEnabled()
{
    SetPropertyStandby(true);
}

void ProviderProduct::StandbyDisabled(StandbyDisableReason /*aReason*/)
{
    SetPropertyStandby(false);
}
