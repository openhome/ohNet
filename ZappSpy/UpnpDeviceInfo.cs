using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace ZappSpy
{
    /// <summary>
    /// Information about a UPnP device observed on the network.
    /// Immutable.
    /// </summary>
    public class UpnpDeviceInfo : IPropertyBag
    {
        public string DeviceType { get; private set; }
        public string FriendlyName { get; private set; }
        public string Manufacturer { get; private set; }
        public string ManufacturerURL { get; private set; }
        public string ModelDescription { get; private set; }
        public string ModelName { get; private set; }
        public string ModelNumber { get; private set; }
        public string ModelURL { get; private set; }
        public string SerialNumber { get; private set; }
        public string UDN { get; private set; }
        public string UPC { get; private set; }
        public string DeviceXml { get; private set; }
        public Uri BaseURI { get; private set; }

        public IEnumerable<UpnpDeviceInfo> EmbeddedDevices { get; private set; }
        public IEnumerable<UpnpServiceInfo> Services { get; private set; }

        public Dictionary<string, string> Properties
        {
            get
            {
                return new Dictionary<string, string>()
                {
                    { "Manufacturer", Manufacturer },
                    { "Manufacturer URL", ManufacturerURL },
                    { "Model description", ModelDescription },
                    { "Model name", ModelName },
                    { "Model number", ModelNumber },
                    { "Model URL", ModelURL },
                    { "Serial number", SerialNumber },
                    { "UDN", UDN },
                    { "UPC", UPC },
                    { "Embedded devices", EmbeddedDevices.Count().ToString() },
                    { "Services", Services.Count().ToString() },
                    { "Base URL", BaseURI.ToString() },
                    { "Friendly name", FriendlyName },
                };
            }
        }

        private UpnpDeviceInfo() { }
        public static UpnpDeviceInfo FromXmlDeviceNode(XElement aDeviceNode, Uri aDocUri, IHttpFetcher aFetcher)
        {
            var instance = new UpnpDeviceInfo();
            List<UpnpDeviceInfo> embeddedDevices = new List<UpnpDeviceInfo>();
            List<UpnpServiceInfo> services = new List<UpnpServiceInfo>();
            instance.EmbeddedDevices = embeddedDevices;
            instance.Services = services;
            foreach (var item in aDeviceNode.Elements())
            {
                if (item.Name == UpnpDeviceXml.DeviceTypeElement) { instance.DeviceType = item.Value; }
                if (item.Name == UpnpDeviceXml.FriendlyNameElement) { instance.FriendlyName = item.Value; }
                if (item.Name == UpnpDeviceXml.ManufacturerElement) { instance.Manufacturer = item.Value; }
                if (item.Name == UpnpDeviceXml.ManufacturerURLElement) { instance.ManufacturerURL = item.Value; }
                if (item.Name == UpnpDeviceXml.ModelDescriptionElement) { instance.ModelDescription = item.Value; }
                if (item.Name == UpnpDeviceXml.ModelNameElement) { instance.ModelName = item.Value; }
                if (item.Name == UpnpDeviceXml.ModelNumberElement) { instance.ModelNumber = item.Value; }
                if (item.Name == UpnpDeviceXml.ModelURLElement) { instance.ModelURL = item.Value; }
                if (item.Name == UpnpDeviceXml.SerialNumberElement) { instance.SerialNumber = item.Value; }
                if (item.Name == UpnpDeviceXml.UDNElement) { instance.UDN = item.Value; }
                if (item.Name == UpnpDeviceXml.UPCElement) { instance.UPC = item.Value; }
                if (item.Name == UpnpDeviceXml.DeviceListElement)
                {
                    foreach (var embeddedDeviceNode in item.Elements(UpnpDeviceXml.DeviceElement))
                    {
                        embeddedDevices.Add(UpnpDeviceInfo.FromXmlDeviceNode(embeddedDeviceNode, aDocUri, aFetcher));
                    }
                }
                if (item.Name == UpnpDeviceXml.ServiceListElement)
                {
                    foreach (var serviceNode in item.Elements(UpnpDeviceXml.ServiceElement))
                    {
                        services.Add(UpnpServiceInfo.FromXmlServiceNode(serviceNode, aDocUri, aFetcher));
                    }
                }
            }
            instance.BaseURI = aDocUri;
            return instance;
        }
        public static UpnpDeviceInfo FromXmlString(string aXml, Uri aDocUri, IHttpFetcher aFetcher)
        {
            var doc = XDocument.Parse(aXml);
            var deviceInfo = FromXmlDeviceNode(doc.Root.Element(UpnpDeviceXml.DeviceElement), aDocUri, aFetcher);
            deviceInfo.DeviceXml = aXml;
            return deviceInfo;
        }
    }
}
