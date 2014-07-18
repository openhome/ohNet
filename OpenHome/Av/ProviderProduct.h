#ifndef HEADER_PROVIDER_PRODUCT_1
#define HEADER_PROVIDER_PRODUCT_1

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <Generated/DvAvOpenhomeOrgProduct1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Av {

class ProviderProduct : public Net::DvProviderAvOpenhomeOrgProduct1, private IProductObserver
{
public:
    ProviderProduct(Net::DvDevice& aDevice, Av::Product& aProduct);
    ~ProviderProduct();
private: // from DvProviderAvOpenhomeOrgProduct1
    void Manufacturer(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aName, Net::IDvInvocationResponseString& aInfo, Net::IDvInvocationResponseString& aUrl, Net::IDvInvocationResponseString& aImageUri);
    void Model(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aName, Net::IDvInvocationResponseString& aInfo, Net::IDvInvocationResponseString& aUrl, Net::IDvInvocationResponseString& aImageUri);
    void Product(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aRoom, Net::IDvInvocationResponseString& aName, Net::IDvInvocationResponseString& aInfo, Net::IDvInvocationResponseString& aUrl, Net::IDvInvocationResponseString& aImageUri);
    void Standby(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aValue);
    void SetStandby(Net::IDvInvocation& aInvocation, TBool aValue);
    void SourceCount(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue);
    void SourceXml(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue);
    void SourceIndex(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue);
    void SetSourceIndex(Net::IDvInvocation& aInvocation, TUint aValue);
    void SetSourceIndexByName(Net::IDvInvocation& aInvocation, const Brx& aValue);
    void Source(Net::IDvInvocation& aInvocation, TUint aIndex, Net::IDvInvocationResponseString& aSystemName, Net::IDvInvocationResponseString& aType, Net::IDvInvocationResponseString& aName, Net::IDvInvocationResponseBool& aVisible);
    void Attributes(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue);
    void SourceXmlChangeCount(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue);
private: // from IProductObserver
    void Started();
    void RoomChanged();
    void NameChanged();
    void StandbyChanged();
    void SourceIndexChanged();
    void SourceXmlChanged();
private:
    Av::Product& iProduct;
    Mutex iLock;
    Bws<Product::kMaxSourceXmlBytes> iSourceXml;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_PRODUCT_1
