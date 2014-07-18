#ifndef HEADER_DVI_PROTOCOL_LPEC
#define HEADER_DVI_PROTOCOL_LPEC

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviDevice.h>

namespace OpenHome {
    class NetworkAdapter;
namespace Net {

class DvStack;
class DviServerLpec;

class DviProtocolLpec : public IDvProtocol
{
    static const Brn kProtocolName;
public:
    DviProtocolLpec(DviDevice& aDevice);
private: // from IResourceManager
    void WriteResource(const Brx& aUriTail, TIpAddress aAdapter, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
private: // from IDvProtocol
    const Brx& ProtocolName() const;
    void Enable();
    void Disable(Functor& aComplete);
    void GetAttribute(const TChar* aKey, const TChar** aValue) const;
    void SetAttribute(const TChar* aKey, const TChar* aValue);
    void SetCustomData(const TChar* aTag, void* aData);
    void GetResourceManagerUri(const NetworkAdapter& aAdapter, Brh& aUri);
private:
    DviDevice& iDevice;
    AttributeMap iAttributeMap;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_PROTOCOL_LPEC
