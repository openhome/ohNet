#include <DeviceXml.h>
#include <Debug.h>
#include <XmlParser.h>
#include <Parser.h>
#include <Error.h>
#include <Converter.h>
#include <Stack.h>

using namespace Zapp;

// DeviceXmlDocument

DeviceXmlDocument::DeviceXmlDocument(const Brx& aXml)
	: iXml(aXml)
{
    Brn root = XmlParserBasic::Find("root", iXml);
    iRoot = new DeviceXml(XmlParserBasic::Find("device", root));
}

DeviceXmlDocument::~DeviceXmlDocument()
{
    delete iRoot;
}

Brn DeviceXmlDocument::Find(const Brx& aUdn)
{
	return (iRoot->Find(aUdn));
}

const Brx& DeviceXmlDocument::Xml() const
{
	return (iXml);
}

const DeviceXml& DeviceXmlDocument::Root() const
{
	return (*iRoot);
}

// DeviceXml

DeviceXml::DeviceXml(const Brx& aXml)
	: iXml(aXml)
{
	Brn udn = XmlParserBasic::Find("UDN", iXml);
	
	Parser parser(udn);
	
	if (parser.Next(':') != Brn("uuid")) {
		THROW(XmlError);
	}
	
	iUdn.Set(parser.Remaining());
}
    
Brn DeviceXml::Find(const Brx& aUdn)
{
	if (iUdn == aUdn) {
		return (iXml);
	}

    Brn deviceList = XmlParserBasic::Find("deviceList", iXml);

	for (;;) {
		Brn xml = XmlParserBasic::Find("device", deviceList, deviceList);

		DeviceXml device(xml);

		try {
			return (device.Find(aUdn));
		}
		catch (XmlError&) {
		}
	}
}

void DeviceXml::FriendlyName(Brh& aValue) const
{
	Bwh friendlyName(XmlParserBasic::Find("friendlyName", iXml));
    Converter::FromXmlEscaped(friendlyName);
    friendlyName.TransferTo(aValue);
}

Brn DeviceXml::ServiceVersion(const Brx& aServiceType) const
{
	const TUint kMaxDomainBytes = 64;
	const TUint kMaxTypeBytes = 64;
	
	Bws<kMaxDomainBytes> domain;
	Bws<kMaxTypeBytes> upnpType;
	
	Parser parser(aServiceType);
	
	TUint count = 0;
	
	while (!parser.Finished()) {
		upnpType.Replace(parser.Next('.'));
		count++;
	}

	parser.Restart();
		
	while (--count) {
		Brn element = parser.Next('.');
		
		if (domain.Bytes() > 0) {
			domain.Append('.');
		}
		
		domain.Append(element);
	}
	
	Bws<kMaxDomainBytes> upnpDomain;
	
	Ssdp::CanonicalDomainToUpnp(domain, upnpDomain);
	
	Brn serviceList = XmlParserBasic::Find("serviceList", iXml);
	
	for (;;) {
		Brn service = XmlParserBasic::Find("service", serviceList, serviceList);
		Brn type = XmlParserBasic::Find("serviceType", service);

		Parser parser(type);
		
		if (parser.Next(':') == Brn("urn")) {
			if (parser.Next(':') == upnpDomain) {
				if (parser.Next(':') == Brn("service")) {
					if (parser.Next(':') == upnpType) {
						return (parser.Remaining());
					}
				}
			}
		}
	}
}
