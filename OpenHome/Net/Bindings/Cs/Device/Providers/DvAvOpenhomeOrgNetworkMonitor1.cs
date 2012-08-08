using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderAvOpenhomeOrgNetworkMonitor1 : IDisposable
    {

        /// <summary>
        /// Set the value of the Name property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyName(string aValue);

        /// <summary>
        /// Get a copy of the value of the Name property
        /// </summary>
        /// <returns>Value of the Name property.</param>
        string PropertyName();

        /// <summary>
        /// Set the value of the Sender property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertySender(uint aValue);

        /// <summary>
        /// Get a copy of the value of the Sender property
        /// </summary>
        /// <returns>Value of the Sender property.</param>
        uint PropertySender();

        /// <summary>
        /// Set the value of the Receiver property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReceiver(uint aValue);

        /// <summary>
        /// Get a copy of the value of the Receiver property
        /// </summary>
        /// <returns>Value of the Receiver property.</param>
        uint PropertyReceiver();

        /// <summary>
        /// Set the value of the Results property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyResults(uint aValue);

        /// <summary>
        /// Get a copy of the value of the Results property
        /// </summary>
        /// <returns>Value of the Results property.</param>
        uint PropertyResults();
        
    }
    /// <summary>
    /// Provider for the av.openhome.org:NetworkMonitor:1 UPnP service
    /// </summary>
    public class DvProviderAvOpenhomeOrgNetworkMonitor1 : DvProvider, IDisposable, IDvProviderAvOpenhomeOrgNetworkMonitor1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateName;
        private ActionDelegate iDelegatePorts;
        private PropertyString iPropertyName;
        private PropertyUint iPropertySender;
        private PropertyUint iPropertyReceiver;
        private PropertyUint iPropertyResults;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderAvOpenhomeOrgNetworkMonitor1(DvDevice aDevice)
            : base(aDevice, "av.openhome.org", "NetworkMonitor", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Enable the Name property.
        /// </summary>
        public void EnablePropertyName()
        {
            List<String> allowedValues = new List<String>();
            iPropertyName = new PropertyString(new ParameterString("Name", allowedValues));
            AddProperty(iPropertyName);
        }

        /// <summary>
        /// Enable the Sender property.
        /// </summary>
        public void EnablePropertySender()
        {
            iPropertySender = new PropertyUint(new ParameterUint("Sender"));
            AddProperty(iPropertySender);
        }

        /// <summary>
        /// Enable the Receiver property.
        /// </summary>
        public void EnablePropertyReceiver()
        {
            iPropertyReceiver = new PropertyUint(new ParameterUint("Receiver"));
            AddProperty(iPropertyReceiver);
        }

        /// <summary>
        /// Enable the Results property.
        /// </summary>
        public void EnablePropertyResults()
        {
            iPropertyResults = new PropertyUint(new ParameterUint("Results"));
            AddProperty(iPropertyResults);
        }

        /// <summary>
        /// Set the value of the Name property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyName has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyName(string aValue)
        {
            if (iPropertyName == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyName, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Name property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyName has previously been called.</remarks>
        /// <returns>Value of the Name property.</returns>
        public string PropertyName()
        {
            if (iPropertyName == null)
                throw new PropertyDisabledError();
            return iPropertyName.Value();
        }

        /// <summary>
        /// Set the value of the Sender property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySender has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySender(uint aValue)
        {
            if (iPropertySender == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertySender, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Sender property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySender has previously been called.</remarks>
        /// <returns>Value of the Sender property.</returns>
        public uint PropertySender()
        {
            if (iPropertySender == null)
                throw new PropertyDisabledError();
            return iPropertySender.Value();
        }

        /// <summary>
        /// Set the value of the Receiver property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyReceiver has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyReceiver(uint aValue)
        {
            if (iPropertyReceiver == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyReceiver, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Receiver property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyReceiver has previously been called.</remarks>
        /// <returns>Value of the Receiver property.</returns>
        public uint PropertyReceiver()
        {
            if (iPropertyReceiver == null)
                throw new PropertyDisabledError();
            return iPropertyReceiver.Value();
        }

        /// <summary>
        /// Set the value of the Results property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyResults has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyResults(uint aValue)
        {
            if (iPropertyResults == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyResults, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Results property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyResults has previously been called.</remarks>
        /// <returns>Value of the Results property.</returns>
        public uint PropertyResults()
        {
            if (iPropertyResults == null)
                throw new PropertyDisabledError();
            return iPropertyResults.Value();
        }

        /// <summary>
        /// Signal that the action Name is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Name must be overridden if this is called.</remarks>
        protected void EnableActionName()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Name");
            action.AddOutputParameter(new ParameterRelated("Name", iPropertyName));
            iDelegateName = new ActionDelegate(DoName);
            EnableAction(action, iDelegateName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Ports is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Ports must be overridden if this is called.</remarks>
        protected void EnableActionPorts()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Ports");
            action.AddOutputParameter(new ParameterRelated("Sender", iPropertySender));
            action.AddOutputParameter(new ParameterRelated("Receiver", iPropertyReceiver));
            action.AddOutputParameter(new ParameterRelated("Results", iPropertyResults));
            iDelegatePorts = new ActionDelegate(DoPorts);
            EnableAction(action, iDelegatePorts, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Name action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Name action for the owning device.
        ///
        /// Must be implemented iff EnableActionName was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aName"></param>
        protected virtual void Name(IDvInvocation aInvocation, out string aName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Ports action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Ports action for the owning device.
        ///
        /// Must be implemented iff EnableActionPorts was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aSender"></param>
        /// <param name="aReceiver"></param>
        /// <param name="aResults"></param>
        protected virtual void Ports(IDvInvocation aInvocation, out uint aSender, out uint aReceiver, out uint aResults)
        {
            throw (new ActionDisabledError());
        }

        private static int DoName(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgNetworkMonitor1 self = (DvProviderAvOpenhomeOrgNetworkMonitor1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string name;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Name(invocation, out name);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Name");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Name"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Name", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Name", name);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Name", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPorts(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgNetworkMonitor1 self = (DvProviderAvOpenhomeOrgNetworkMonitor1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint sender;
            uint receiver;
            uint results;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Ports(invocation, out sender, out receiver, out results);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Ports");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Ports"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Ports", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Sender", sender);
                invocation.WriteUint("Receiver", receiver);
                invocation.WriteUint("Results", results);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Ports", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            if (DisposeProvider())
                iGch.Free();
        }
    }
}

