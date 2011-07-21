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
    public class UpnpServiceXmlException : Exception
    {
        public UpnpServiceXmlException(string aMessage)
            : base(aMessage)
        {
        }
    }

    public class Argument
    {
        public string name;
        public string related;
        public Variable variable;

        internal Argument(XPathNavigator navigator, string nspace)
        {
            XmlNamespaceManager nsmanager = new XmlNamespaceManager(navigator.NameTable);
            nsmanager.AddNamespace("u", nspace);

            name = navigator.SelectSingleNode("u:name", nsmanager).Value;
            name = name.Trim();
            related = navigator.SelectSingleNode("u:relatedStateVariable", nsmanager).Value;
            related = related.Trim();
        }

        internal void Resolve(Variable variable)
        {
            this.variable = variable;
        }
    }

    public class Method
    {
        public string name;

        public List<Argument> inargs = new List<Argument>();
        public List<Argument> outargs = new List<Argument>();

        internal Method(XPathNavigator navigator, string nspace)
        {
            XmlNamespaceManager nsmanager = new XmlNamespaceManager(navigator.NameTable);
            nsmanager.AddNamespace("u", nspace);

            name = navigator.SelectSingleNode("u:name", nsmanager).Value;
            name = name.Trim();

            foreach (XPathNavigator a in navigator.Select("u:argumentList/u:argument", nsmanager))
            {
                if (a.SelectSingleNode("u:direction", nsmanager).Value == "out")
                {
                    outargs.Add(new Argument(a, nspace));
                }
                else
                {
                    inargs.Add(new Argument(a, nspace));
                }
            }
        }
    }

    public class Variable
    {
        public string name;
        public string type;
		public string prettyname;

        public bool evented = false;

        public bool isnumeric = false;
        public bool issigned = false;
        public bool isunsigned = false;
        public uint numericbytes = 0;

        public List<string> values = new List<string>();

        public long min;
        public long max;
        public long step;

        public bool minspecified = false;
        public bool maxspecified = false;
        public bool stepspecified = false;

        internal Variable(XPathNavigator navigator, string nspace, string eventedTag)
        {
            XmlNamespaceManager nsmanager = new XmlNamespaceManager(navigator.NameTable);
            nsmanager.AddNamespace("u", nspace);

            name = navigator.SelectSingleNode("u:name", nsmanager).Value;
            type = navigator.SelectSingleNode("u:dataType", nsmanager).Value;
            name = name.Trim();
            type = type.Trim();

            prettyname = name;

            if (prettyname.StartsWith("A_ARG_TYPE_"))
			{
				prettyname = prettyname.Substring(11);
			}

            XPathNavigator e = navigator.SelectSingleNode(eventedTag, nsmanager);
            if (e != null)
            {
                if (e.Value == "yes")
                {
                    evented = true;
                }
            }

            if (type == "string")
            {
                foreach (XPathNavigator v in navigator.Select("u:allowedValueList/u:allowedValue", nsmanager))
                {
                    values.Add(v.Value);
                }
            }

            if (type.StartsWith("i"))
            {
                isnumeric = true;
                issigned = true;

                if (type == "i1")
                {
                    numericbytes = 1;
                }
                else if (type == "i2")
                {
                    numericbytes = 2;
                }
                else if (type == "i4")
                {
                    numericbytes = 4;
                }
                else
                {
                    throw (new UpnpServiceXmlException("Invalid numeric type in state variable " + name));
                }

                XPathNavigator v;
                
                v = navigator.SelectSingleNode("u:allowedValueRange/u:minimum", nsmanager);

                if (v != null)
                {
                    min = Convert.ToInt64(v.Value);
                    minspecified = true;
                }

                v = navigator.SelectSingleNode("u:allowedValueRange/u:maximum", nsmanager);

                if (v != null)
                {
                    max = Convert.ToInt64(v.Value);
                    maxspecified = true;
                }

                v = navigator.SelectSingleNode("u:allowedValueRange/u:step", nsmanager);

                if (v != null)
                {
                    step = Convert.ToInt64(v.Value);
                    stepspecified = true;

                    if (step < 1)
                    {
                        throw (new UpnpServiceXmlException("Invalid step value specified in state variable " + name));
                    }
                }

                if (minspecified && maxspecified)
                {
                    if (max < min)
                    {
                        throw (new UpnpServiceXmlException("Maximum value less than minimum value in state variable " + name));
                    }
                }
            }

            else if (type.StartsWith("ui"))
            {
                isnumeric = true;
                isunsigned = true;

                if (type == "ui1")
                {
                    numericbytes = 1;
                }
                else if (type == "ui2")
                {
                    numericbytes = 2;
                }
                else if (type == "ui4")
                {
                    numericbytes = 4;
                }
                else
                {
                    throw (new UpnpServiceXmlException("Invalid numeric type in state variable " + name));
                }

                XPathNavigator v;
                
                v = navigator.SelectSingleNode("u:allowedValueRange/u:minimum", nsmanager);

                if (v != null)
                {
                    min = Convert.ToInt64(v.Value);
                    minspecified = true;

                    if (min < 0)
                    {
                        throw (new UpnpServiceXmlException("Negative minimum value specified in unsigned state variable " + name));
                    }
                }

                v = navigator.SelectSingleNode("u:allowedValueRange/u:maximum", nsmanager);

                if (v != null)
                {
                    max = Convert.ToInt64(v.Value);
                    maxspecified = true;

                    if (max < 0)
                    {
                        throw (new UpnpServiceXmlException("Negative maximum value specified in unsigned state variable " + name));
                    }
                }

                v = navigator.SelectSingleNode("u:allowedValueRange/u:step", nsmanager);

                if (v != null)
                {
                    step = Convert.ToInt64(v.Value);
                    stepspecified = true;

                    if (step < 1)
                    {
                        throw (new UpnpServiceXmlException("Invalid step value specified in state variable " + name));
                    }
                }

                if (minspecified && maxspecified)
                {
                    if (max < min)
                    {
                        throw (new UpnpServiceXmlException("Maximum value less than minimum value in state variable " + name));
                    }
                }
            }
        }
    }

    public class Document
    {
        public bool specversionspecified = false;

        public uint specversionmajor;
        public uint specversionminor;

        public List<Method> methods = new List<Method>();
        public List<Variable> variables = new List<Variable>();
        public List<Variable> evented = new List<Variable>();
        
        private static void XmlValidationEventHandler(object sender, ValidationEventArgs e)
        {
            throw (e.Exception);
        }

        private XPathDocument CreateDocument(string uri, string aSchema)
        {
            ValidationEventHandler validator = new ValidationEventHandler(XmlValidationEventHandler);

            // Read the schema from the same directory as this library
            Assembly assembly = Assembly.GetExecutingAssembly();
            string path = System.IO.Path.GetDirectoryName(assembly.Location) + "/" + aSchema;

            XmlSchema schema = XmlSchema.Read(new StreamReader(path), validator);

            XmlReaderSettings settings = new XmlReaderSettings();

            settings.CloseInput = true;
            settings.IgnoreComments = true;
            settings.IgnoreWhitespace = true;
            settings.ValidationFlags |= XmlSchemaValidationFlags.ReportValidationWarnings;
            settings.ValidationType = ValidationType.Schema;
            settings.ValidationEventHandler += validator;
            settings.Schemas.Add(schema);

            XmlReader reader = XmlReader.Create(uri, settings);

            return new XPathDocument(reader);
        }

        public Document(string uri)
        {
            string nspace = "urn:schemas-upnp-org:service-1-0";
            string eventedTag = "@sendEvents";
            //Console.WriteLine("\nProcessing " + uri + "\n");
            XPathDocument document;
            try
            {
                document = CreateDocument(uri, "UpnpServiceDescription.xsd");
            }
            catch
            {
                document = CreateDocument(uri, "UpnpServiceTemplate.xsd");
                nspace = "";
                eventedTag = "u:sendEventsAttribute";
            }

            XPathNavigator navigator = document.CreateNavigator();

            XmlNamespaceManager nsmanager = new XmlNamespaceManager(navigator.NameTable);

            nsmanager.AddNamespace("u", nspace);

            // Process the xml file

            XPathNavigator major = navigator.SelectSingleNode("/u:scpd/u:specVersion/u:major", nsmanager);

            if (major != null)
            {
                specversionspecified = true;
                specversionmajor = Convert.ToUInt32(major.Value);
                specversionminor = Convert.ToUInt32(navigator.SelectSingleNode("/u:scpd/u:specVersion/u:minor", nsmanager).Value);
            }

            foreach (XPathNavigator a in navigator.Select("/u:scpd/u:actionList/u:action", nsmanager))
            {
                methods.Add(new Method(a, nspace));
            }

            foreach (XPathNavigator s in navigator.Select("/u:scpd/u:serviceStateTable/u:stateVariable", nsmanager))
            {
                variables.Add(new Variable(s, nspace, eventedTag));
            }

            foreach (Variable s in variables)
            {
                if (s.evented)
                {
                    evented.Add(s);
                }
            }

            foreach (Method action in methods)
            {
                foreach (Argument argument in action.inargs)
                {
                    foreach (Variable v in variables)
                    {
                        if (argument.related == v.name)
                        {
                            argument.Resolve(v);
                            break;
                        }
                    }

                    if (argument.variable == null)
                    {
                        throw (new UpnpServiceXmlException("Variable " + argument.related + " referenced by " + argument.name + " in " + action.name + " not found."));
                    }
                }

                foreach (Argument argument in action.outargs)
                {
                    foreach (Variable v in variables)
                    {
                        if (argument.related == v.name)
                        {
                            argument.Resolve(v);
                            break;
                        }
                    }

                    if (argument.variable == null)
                    {
                        throw (new UpnpServiceXmlException("Variable " + argument.related + " referenced by " + argument.name + " in " + action.name + " not found."));
                    }
                }
            }
        }
    }
}
