#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviDevice.h>

namespace OpenHome {
    class NetworkAdapter;
namespace Net {

class DviProtocolFactoryOdp : public IDvProtocolFactory
{
private: // from IDvProtocolFactory
    IDvProtocol* CreateProtocol(DviDevice& aDevice) override;
};

class DviProtocolOdp : public IDvProtocol
{
    static const Brn kProtocolName;
public:
    DviProtocolOdp(DviDevice& aDevice);
private: // from IResourceManager
    void WriteResource(const Brx& aUriTail,
                       TIpAddress aAdapter,
                       std::vector<char*>& aLanguageList,
                       IResourceWriter& aResourceWriter) override;
private: // from IDvProtocol
    const Brx& ProtocolName() const override;
    void Enable() override;
    void Disable(Functor& aComplete) override;
    void GetAttribute(const TChar* aKey, const TChar** aValue) const override;
    void SetAttribute(const TChar* aKey, const TChar* aValue) override;
    void SetCustomData(const TChar* aTag, void* aData) override;
    void GetResourceManagerUri(const NetworkAdapter& aAdapter, Brh& aUri) override;
private:
    DviDevice& iDevice;
    AttributeMap iAttributeMap;
};

} // namespace Net
} // namespace OpenHome
