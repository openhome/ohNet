/**
 * Invocation of a UPnP request on a particular device
 */

#ifndef HEADER_DEVICE_XML
#define HEADER_DEVICE_XML

#include <ZappTypes.h>
#include <Buffer.h>

namespace Zapp {

class DeviceXml
{
public:
	DeviceXml(const Brx& aXml);
    Brn Find(const Brx& aUdn);
	void FriendlyName(Brh& aValue) const;
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

} // namespace Zapp

#endif // HEADER_DEVICE_XML
