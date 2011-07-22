using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;
using System.IO;

using System.Xml;
using System.Xml.Schema;
using System.Xml.XPath;

namespace OpenHome.Net.Xml.UpnpServiceXml
{
    public class Service
    {
        public string iPublisher;
        public string iDcpDir;
		public string iDomain;
		public string iType;
        public uint iVersion;

        internal Service(XPathNavigator aNavigator)
        {
            XmlNamespaceManager nsmanager = new XmlNamespaceManager(aNavigator.NameTable);

            iPublisher = aNavigator.SelectSingleNode("publisher", nsmanager).Value;
            iPublisher = iPublisher.Trim();
            iDcpDir = aNavigator.SelectSingleNode("dcpdir", nsmanager).Value;
            iDcpDir = iDcpDir.Trim();
            iDomain = aNavigator.SelectSingleNode("domain", nsmanager).Value;
            iDomain = iDomain.Trim();
            iType = aNavigator.SelectSingleNode("type", nsmanager).Value;
            iType = iType.Trim();
            iVersion = (uint)aNavigator.SelectSingleNode("version", nsmanager).ValueAsInt;
        }
    }

    public class Document
    {
        public List<Service> iServices = new List<Service>();

        private static void XmlValidationEventHandler(object sender, ValidationEventArgs e)
        {
            throw (e.Exception);
        }

        private XPathDocument CreateDocument(string uri, string aSchema)
        {
            ValidationEventHandler validator = new ValidationEventHandler(XmlValidationEventHandler);

            // Read the schema from the same directory as this library
            //Assembly assembly = Assembly.GetExecutingAssembly();
            //string path = System.IO.Path.GetDirectoryName(assembly.Location) + "/" + aSchema;

            //XmlSchema schema = XmlSchema.Read(new StreamReader(path), validator);

            XmlReaderSettings settings = new XmlReaderSettings();

            settings.CloseInput = true;
            settings.IgnoreComments = true;
            settings.IgnoreWhitespace = true;
            //settings.ValidationFlags |= XmlSchemaValidationFlags.ReportValidationWarnings;
            //settings.ValidationType = ValidationType.Schema;
            settings.ValidationEventHandler += validator;
            //settings.Schemas.Add(schema);

            XmlReader reader = XmlReader.Create(uri, settings);

            return new XPathDocument(reader);
        }

        public Document(string uri)
        {
            XPathDocument document = CreateDocument(uri, "UpnpServiceDescription.xsd");
            XPathNavigator navigator = document.CreateNavigator();
            XmlNamespaceManager nsmanager = new XmlNamespaceManager(navigator.NameTable);

            foreach (XPathNavigator service in navigator.Select("/servicelist/service", nsmanager))
            {
                iServices.Add(new Service(service));
            }
        }
    }
}
