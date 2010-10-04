using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace ZappSpy
{
    /// <summary>
    /// Information about a service provided by a UPnP device.
    /// Immutable.
    /// </summary>
    public class UpnpServiceInfo : IPropertyBag
    {
        public string ServiceType { get; private set; }
        public string ServiceId { get; private set; }
        public string SCPDURL { get; private set; }
        public string ControlURL { get; private set; }
        public string EventSubURL { get; private set; }

        /// <summary>
        /// The XML document obtained by querying the SCPDURL.
        /// </summary>
        public string DescriptionXml { get; private set; }

        public UpnpServiceDescriptionInfo Description { get; private set; }

        public Dictionary<string, string> Properties
        {
            get
            {
                return new Dictionary<string, string>()
                {
                    { "Service type", ServiceType },
                    { "Service id", ServiceId },
                    { "Methods", Description.Actions.Count().ToString() },
                    { "State variables", Description.StateVariables.Count().ToString() },
                    { "Version", ((object)Description.SpecVersion??"null").ToString() },
                };
            }
        }


        private UpnpServiceInfo() { }
        public static UpnpServiceInfo FromXmlServiceNode(XElement aServiceNode, Uri aDocUri, IHttpFetcher aFetcher)
        {
            var instance = new UpnpServiceInfo();
            foreach (var item in aServiceNode.Elements())
            {
                if (item.Name == UpnpDeviceXml.ServiceTypeElement) { instance.ServiceType = item.Value; }
                if (item.Name == UpnpDeviceXml.ServiceIdElement) { instance.ServiceId = item.Value; }
                if (item.Name == UpnpDeviceXml.SCPDURLElement)
                {
                    instance.SCPDURL = item.Value;
                    Uri absoluteUri;
                    if (Uri.TryCreate(aDocUri, instance.SCPDURL, out absoluteUri))
                    {
                        instance.DescriptionXml = aFetcher.SynchronousGetRequest(absoluteUri);
                        var descriptionDoc = XDocument.Parse(instance.DescriptionXml);
                        instance.Description = UpnpServiceDescriptionInfo.FromXmlScpdNode(descriptionDoc.Root);
                    }
                }
                if (item.Name == UpnpDeviceXml.ControlURLElement) { instance.ControlURL = item.Value; }
                if (item.Name == UpnpDeviceXml.EventSubURLElement) { instance.EventSubURL = item.Value; }
            }
            return instance;
        }
        public override string ToString()
        {
            return String.Format("<Service Type={0}, Id={1}>", ServiceType, ServiceId);
        }
    }
}
