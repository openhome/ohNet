#pragma once

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
    void Manufacturer(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aName, Net::IDvInvocationResponseString& aInfo, Net::IDvInvocationResponseString& aUrl, Net::IDvInvocationResponseString& aImageUri) override;
    void Model(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aName, Net::IDvInvocationResponseString& aInfo, Net::IDvInvocationResponseString& aUrl, Net::IDvInvocationResponseString& aImageUri) override;
    void Product(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aRoom, Net::IDvInvocationResponseString& aName, Net::IDvInvocationResponseString& aInfo, Net::IDvInvocationResponseString& aUrl, Net::IDvInvocationResponseString& aImageUri) override;
    void Standby(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aValue) override;
    void SetStandby(Net::IDvInvocation& aInvocation, TBool aValue) override;
    void SourceCount(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue) override;
    void SourceXml(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
    void SourceIndex(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue) override;
    void SetSourceIndex(Net::IDvInvocation& aInvocation, TUint aValue) override;
    void SetSourceIndexByName(Net::IDvInvocation& aInvocation, const Brx& aValue) override;
    void Source(Net::IDvInvocation& aInvocation, TUint aIndex, Net::IDvInvocationResponseString& aSystemName, Net::IDvInvocationResponseString& aType, Net::IDvInvocationResponseString& aName, Net::IDvInvocationResponseBool& aVisible) override;
    void Attributes(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
    void SourceXmlChangeCount(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue) override;
private: // from IProductObserver
    void Started() override;
    void RoomChanged() override;
    void NameChanged() override;
    void StandbyChanged() override;
    void SourceIndexChanged() override;
    void SourceXmlChanged() override;
private:
    Av::Product& iProduct;
    Mutex iLock;
    Bws<Product::kMaxSourceXmlBytes> iSourceXml;
};

} // namespace Av
} // namespace OpenHome

