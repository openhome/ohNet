using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
// Foo bar baz
namespace ZappSpy
{
    internal static class UpnpDeviceXml
    {
        public static XNamespace Namespace = "urn:schemas-upnp-org:device-1-0";
		public static XName DeviceTypeElement = Namespace + "deviceType";
        public static XName FriendlyNameElement = Namespace + "friendlyName";
        public static XName ManufacturerElement = Namespace + "manufacturer";
        public static XName ManufacturerURLElement = Namespace + "manufacturerURL";
        public static XName ModelDescriptionElement = Namespace + "modelDescription";
        public static XName ModelNameElement = Namespace + "modelName";
        public static XName ModelNumberElement = Namespace + "modelNumber";
        public static XName ModelURLElement = Namespace + "modelURL";
        public static XName SerialNumberElement = Namespace + "serialNumber";
        public static XName UDNElement = Namespace + "UDN";
        public static XName UPCElement = Namespace + "UPC";
        public static XName ServiceTypeElement = Namespace + "serviceType";
        public static XName ServiceIdElement = Namespace + "serviceId";
        public static XName SCPDURLElement = Namespace + "SCPDURL";
        public static XName ControlURLElement = Namespace + "controlURL";
        public static XName EventSubURLElement = Namespace + "eventSubURL";
        public static XName ActionElement = Namespace + "action";
        public static XName ActionListElement = Namespace + "actionList";
        public static XName SpecVersionElement = Namespace + "specVersion";
        public static XName MajorElement = Namespace + "major";
        public static XName MinorElement = Namespace + "minor";
        public static XName NameElement = Namespace + "name";
        public static XName DeviceElement = Namespace + "device";
        public static XName ServiceElement = Namespace + "service";
        public static XName DeviceListElement = Namespace + "deviceList";
        public static XName ServiceListElement = Namespace + "serviceList";
        public static XName IconListElement = Namespace + "iconList";
        
	}

	internal static class UpnpServiceXml
    {
        public static XNamespace Namespace = "urn:schemas-upnp-org:service-1-0";
		public static XName SpecVersionElement = Namespace + "specVersion";
        public static XName MajorElement = Namespace + "major";
        public static XName MinorElement = Namespace + "minor";
        public static XName ActionListElement = Namespace + "actionList";
        public static XName ActionElement = Namespace + "action";
        public static XName NameElement = Namespace + "name";
        public static XName ArgumentListElement = Namespace + "argumentList";
        public static XName ArgumentElement = Namespace + "argument";
        public static XName DirectionElement = Namespace + "direction";
        public static XName RelatedStateVariableElement = Namespace + "relatedStateVariable";
        public static XName RetvalElement = Namespace + "retval";
        public static XName ServiceStateTableElement = Namespace + "serviceStateTable";
        public static XName StateVariableElement = Namespace + "stateVariable";
        public static XName SendEventsElement = Namespace + "sendEvents";
        public static XName MulticastElement = Namespace + "multicast";
        public static XName DataTypeElement = Namespace + "dataType";
        public static XName DefaultValueElement = Namespace + "defaultValue";
        public static XName AllowedValueRangeElement = Namespace + "allowedValueRange";
        public static XName MinimumElement = Namespace + "minimum";
        public static XName MaximumElement = Namespace + "maximum";
        public static XName StepElement = Namespace + "step";
        
	}
}

