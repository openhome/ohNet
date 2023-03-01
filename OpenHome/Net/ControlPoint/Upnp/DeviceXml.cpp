#include <OpenHome/Net/Private/DeviceXml.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/Ssdp.h>

using namespace OpenHome;
using namespace OpenHome::Net;

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

const Brx& DeviceXml::Udn() const
{
    return iUdn;
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

void DeviceXml::GetFriendlyName(Brh& aValue) const
{
    Bwh friendlyName(XmlParserBasic::Find("friendlyName", iXml));
    Converter::FromXmlEscaped(friendlyName);
    friendlyName.TransferTo(aValue);
}

void DeviceXml::GetPresentationUrl(Brh& aValue) const
{
    Bwh friendlyName(XmlParserBasic::Find("PresentationURL", iXml));
    Converter::FromXmlEscaped(friendlyName);
    friendlyName.TransferTo(aValue);
}

void DeviceXml::GetModelName(Brh& aValue) const
{
    Bwh modelName(XmlParserBasic::Find("modelName", iXml));
    Converter::FromXmlEscaped(modelName);
    modelName.TransferTo(aValue);
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

        Parser parser2(type);
        
        if (parser2.Next(':') == Brn("urn")) {
            if (parser2.Next(':') == upnpDomain) {
                if (parser2.Next(':') == Brn("service")) {
                    if (parser2.Next(':') == upnpType) {
                        return (parser2.Remaining());
                    }
                }
            }
        }
    }
}
