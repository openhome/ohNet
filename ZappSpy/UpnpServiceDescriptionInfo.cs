using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace ZappSpy
{
    public class UpnpServiceActionArgumentInfo
    {
        public enum ArgDirection
        {
            InArg, OutArg
        };
        
        public string Name { get; private set; }
        public ArgDirection Direction { get; private set; }
        public string DirectionAsString { get { return Direction == ArgDirection.InArg ? "in" : "out"; } }
        public bool IsReturnValue { get; private set; }
        public string RelatedStateVariable { get; private set; }

        private static ArgDirection ParseDirection(string aDirection)
        {
            if (aDirection == "in")
            {
                return ArgDirection.InArg;
            }
            if (aDirection == "out")
            {
                return ArgDirection.OutArg;
            }
            throw new Exception(String.Format("Expected 'in' or 'out'. Got '{0}", aDirection));
        }

        public static UpnpServiceActionArgumentInfo FromXmlArgumentNode(XElement aArgumentNode)
        {
            return new UpnpServiceActionArgumentInfo
            {
                Name = aArgumentNode.Element(UpnpServiceXml.NameElement).Value,
                Direction = ParseDirection(aArgumentNode.Element(UpnpServiceXml.DirectionElement).Value),
                IsReturnValue = aArgumentNode.Elements(UpnpServiceXml.RetvalElement).Any(),
                RelatedStateVariable = aArgumentNode.Element(UpnpServiceXml.RelatedStateVariableElement).Value
            };
        }
    }
    public class UpnpServiceActionInfo
    {
        public string Name { get; private set; }
        public IEnumerable<UpnpServiceActionArgumentInfo> Arguments { get; private set; }

        public static UpnpServiceActionInfo FromXmlActionNode(XElement aActionNode)
        {
            var argumentListNode = aActionNode.Element(UpnpServiceXml.ArgumentListElement);
            List<UpnpServiceActionArgumentInfo> argumentList;
            if (argumentListNode == null)
            {
                argumentList = new List<UpnpServiceActionArgumentInfo>();
            }
            else
            {
                argumentList = (
                    from argumentNode in argumentListNode.Elements(UpnpServiceXml.ArgumentElement)
                    select UpnpServiceActionArgumentInfo.FromXmlArgumentNode(argumentNode)
                    ).ToList();
            }
            return new UpnpServiceActionInfo
            {
                Name = aActionNode.Element(UpnpServiceXml.NameElement).Value,
                Arguments = argumentList
            };
        }
    }

    public class UpnpServiceStateVariableInfo
    {
        public string Name { get; private set; }
        public bool SendEvents { get; private set; }
        public bool Multicast { get; private set; }
        public string DataType { get; private set; }
        public string DefaultValue { get; private set; }
        public IEnumerable<string> AllowedValueList { get; private set; }
        public string AllowedMinimum { get; private set; }
        public string AllowedMaximum { get; private set; }
        public string AllowedStep { get; private set; }

        private static bool AttributeToBool(XAttribute aAttr, bool aDefault)
        {
            if (aAttr == null)
            {
                return aDefault;
            }
            return aAttr.Value == "yes";
        }

        private static string ValueOrNull(XElement aElement)
        {
            if (aElement != null)
            {
                return aElement.Value;
            }
            return null;
        }

        public static UpnpServiceStateVariableInfo FromXmlVariableNode(XElement aVariableNode)
        {
            return new UpnpServiceStateVariableInfo
            {
                Name = aVariableNode.Element(UpnpServiceXml.NameElement).Value,
                SendEvents = AttributeToBool(aVariableNode.Attribute(UpnpServiceXml.SendEventsElement), false),
                Multicast = AttributeToBool(aVariableNode.Attribute(UpnpServiceXml.MulticastElement), false),
                DataType = aVariableNode.Element(UpnpServiceXml.DataTypeElement).Value, // TODO: type attribute
                DefaultValue = ValueOrNull(aVariableNode.Element(UpnpServiceXml.DefaultValueElement))
            };
        }
    }
    public class UpnpServiceDescriptionInfo
    {
        public Version SpecVersion { get; private set; }
        public IEnumerable<UpnpServiceActionInfo> Actions { get; private set; }
        public IEnumerable<UpnpServiceStateVariableInfo> StateVariables { get; private set; }

        public static UpnpServiceDescriptionInfo FromXmlScpdNode(XElement aScpdNode)
        {
            var instance = new UpnpServiceDescriptionInfo();
            instance.SpecVersion = Version.FromServiceXmlVersionElement(aScpdNode.Element(UpnpServiceXml.SpecVersionElement));
            var actionList = new List<UpnpServiceActionInfo>();
            instance.Actions = actionList;
            var variableList = new List<UpnpServiceStateVariableInfo>();
            instance.StateVariables = variableList;
            var actionListNode = aScpdNode.Element(UpnpServiceXml.ActionListElement);
            if (actionListNode != null)
            {
                foreach (var actionNode in actionListNode.Elements(UpnpServiceXml.ActionElement))
                {
                    actionList.Add(UpnpServiceActionInfo.FromXmlActionNode(actionNode));
                }
            }
            var variableListNode = aScpdNode.Element(UpnpServiceXml.ServiceStateTableElement);
            if (variableListNode != null)
            {
                foreach (var variableNode in variableListNode.Elements(UpnpServiceXml.StateVariableElement))
                {
                    variableList.Add(UpnpServiceStateVariableInfo.FromXmlVariableNode(variableNode));
                }
            }
            return instance;
        }
    }

}
