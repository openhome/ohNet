/**
 * Invocation of a UPnP request on a particular device
 */

#ifndef HEADER_DEVICE_XML
#define HEADER_DEVICE_XML

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

namespace OpenHome {
namespace Net {

class DeviceXml
{
public:
    DeviceXml(const Brx& aXml);
    const Brx& Udn() const;
    Brn Find(const Brx& aUdn);
    void GetFriendlyName(Brh& aValue) const;
    void GetPresentationUrl(Brh& aValue) const;
    Brn ServiceVersion(const Brx& aService) const; // e.g "upnp.org.ContentDirectory"
private:
    Brn iXml;
    Brn iUdn;
};

class DeviceXmlDocument
{
public:
    DeviceXmlDocument(const Brx& aXml);
    ~DeviceXmlDocument();
    Brn Find(const Brx& aUdn);
    const Brx& Xml() const;
    const DeviceXml& Root() const;
private:
    Brn iXml;
    DeviceXml* iRoot;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DEVICE_XML
