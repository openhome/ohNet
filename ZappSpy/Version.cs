using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace ZappSpy
{
    public class Version
    {
        private readonly int iMajor;
        private readonly int iMinor;
        public int Major { get { return iMajor; } }
        public int Minor { get { return iMinor; } }
        public Version(int aMajor, int aMinor)
        {
            iMinor = aMinor;
            iMajor = aMajor;
        }
        public static Version FromServiceXmlVersionElement(XElement aVersionElement)
        {
            if (aVersionElement == null)
            {
                // Yikes. This is supposed to be a required element, but it's missing
                // from some of the devices we've scanned.
                return null;
            }
            int major = int.Parse(aVersionElement.Element(UpnpServiceXml.MajorElement).Value);
            int minor = int.Parse(aVersionElement.Element(UpnpServiceXml.MinorElement).Value);
            return new Version(major, minor);
        }
        public override string ToString()
        {
            return String.Format("{0}.{1}", Major, Minor);
        }
    }
}
