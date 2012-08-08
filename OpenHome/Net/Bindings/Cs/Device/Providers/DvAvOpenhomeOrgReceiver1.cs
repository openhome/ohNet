using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderAvOpenhomeOrgReceiver1 : IDisposable
    {

        /// <summary>
        /// Set the value of the Uri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyUri(string aValue);

        /// <summary>
        /// Get a copy of the value of the Uri property
        /// </summary>
        /// <returns>Value of the Uri property.</param>
        string PropertyUri();

        /// <summary>
        /// Set the value of the Metadata property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyMetadata(string aValue);

        /// <summary>
        /// Get a copy of the value of the Metadata property
        /// </summary>
        /// <returns>Value of the Metadata property.</param>
        string PropertyMetadata();

        /// <summary>
        /// Set the value of the TransportState property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTransportState(string aValue);

        /// <summary>
        /// Get a copy of the value of the TransportState property
        /// </summary>
        /// <returns>Value of the TransportState property.</param>
        string PropertyTransportState();

        /// <summary>
        /// Set the value of the ProtocolInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProtocolInfo(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProtocolInfo property
        /// </summary>
        /// <returns>Value of the ProtocolInfo property.</param>
        string PropertyProtocolInfo();
        
    }
    /// <summary>
    /// Provider for the av.openhome.org:Receiver:1 UPnP service
    /// </summary>
    public class DvProviderAvOpenhomeOrgReceiver1 : DvProvider, IDisposable, IDvProviderAvOpenhomeOrgReceiver1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegatePlay;
        private ActionDelegate iDelegateStop;
        private ActionDelegate iDelegateSetSender;
        private ActionDelegate iDelegateSender;
        private ActionDelegate iDelegateProtocolInfo;
        private ActionDelegate iDelegateTransportState;
        private PropertyString iPropertyUri;
        private PropertyString iPropertyMetadata;
        private PropertyString iPropertyTransportState;
        private PropertyString iPropertyProtocolInfo;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderAvOpenhomeOrgReceiver1(DvDevice aDevice)
            : base(aDevice, "av.openhome.org", "Receiver", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Enable the Uri property.
        /// </summary>
        public void EnablePropertyUri()
        {
            List<String> allowedValues = new List<String>();
            iPropertyUri = new PropertyString(new ParameterString("Uri", allowedValues));
            AddProperty(iPropertyUri);
        }

        /// <summary>
        /// Enable the Metadata property.
        /// </summary>
        public void EnablePropertyMetadata()
        {
            List<String> allowedValues = new List<String>();
            iPropertyMetadata = new PropertyString(new ParameterString("Metadata", allowedValues));
            AddProperty(iPropertyMetadata);
        }

        /// <summary>
        /// Enable the TransportState property.
        /// </summary>
        public void EnablePropertyTransportState()
        {
            List<String> allowedValues = new List<String>();
            allowedValues.Add("Stopped");
            allowedValues.Add("Playing");
            allowedValues.Add("Waiting");
            allowedValues.Add("Buffering");
            iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues));
            AddProperty(iPropertyTransportState);
            allowedValues.Clear();
        }

        /// <summary>
        /// Enable the ProtocolInfo property.
        /// </summary>
        public void EnablePropertyProtocolInfo()
        {
            List<String> allowedValues = new List<String>();
            iPropertyProtocolInfo = new PropertyString(new ParameterString("ProtocolInfo", allowedValues));
            AddProperty(iPropertyProtocolInfo);
        }

        /// <summary>
        /// Set the value of the Uri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyUri has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyUri(string aValue)
        {
            if (iPropertyUri == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyUri, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Uri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyUri has previously been called.</remarks>
        /// <returns>Value of the Uri property.</returns>
        public string PropertyUri()
        {
            if (iPropertyUri == null)
                throw new PropertyDisabledError();
            return iPropertyUri.Value();
        }

        /// <summary>
        /// Set the value of the Metadata property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyMetadata has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyMetadata(string aValue)
        {
            if (iPropertyMetadata == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyMetadata, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Metadata property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyMetadata has previously been called.</remarks>
        /// <returns>Value of the Metadata property.</returns>
        public string PropertyMetadata()
        {
            if (iPropertyMetadata == null)
                throw new PropertyDisabledError();
            return iPropertyMetadata.Value();
        }

        /// <summary>
        /// Set the value of the TransportState property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTransportState has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTransportState(string aValue)
        {
            if (iPropertyTransportState == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyTransportState, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TransportState property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTransportState has previously been called.</remarks>
        /// <returns>Value of the TransportState property.</returns>
        public string PropertyTransportState()
        {
            if (iPropertyTransportState == null)
                throw new PropertyDisabledError();
            return iPropertyTransportState.Value();
        }

        /// <summary>
        /// Set the value of the ProtocolInfo property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProtocolInfo has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProtocolInfo(string aValue)
        {
            if (iPropertyProtocolInfo == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyProtocolInfo, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProtocolInfo property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProtocolInfo has previously been called.</remarks>
        /// <returns>Value of the ProtocolInfo property.</returns>
        public string PropertyProtocolInfo()
        {
            if (iPropertyProtocolInfo == null)
                throw new PropertyDisabledError();
            return iPropertyProtocolInfo.Value();
        }

        /// <summary>
        /// Signal that the action Play is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Play must be overridden if this is called.</remarks>
        protected void EnableActionPlay()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Play");
            iDelegatePlay = new ActionDelegate(DoPlay);
            EnableAction(action, iDelegatePlay, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Stop is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Stop must be overridden if this is called.</remarks>
        protected void EnableActionStop()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Stop");
            iDelegateStop = new ActionDelegate(DoStop);
            EnableAction(action, iDelegateStop, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetSender is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetSender must be overridden if this is called.</remarks>
        protected void EnableActionSetSender()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetSender");
            action.AddInputParameter(new ParameterRelated("Uri", iPropertyUri));
            action.AddInputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
            iDelegateSetSender = new ActionDelegate(DoSetSender);
            EnableAction(action, iDelegateSetSender, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Sender is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Sender must be overridden if this is called.</remarks>
        protected void EnableActionSender()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Sender");
            action.AddOutputParameter(new ParameterRelated("Uri", iPropertyUri));
            action.AddOutputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
            iDelegateSender = new ActionDelegate(DoSender);
            EnableAction(action, iDelegateSender, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ProtocolInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ProtocolInfo must be overridden if this is called.</remarks>
        protected void EnableActionProtocolInfo()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("ProtocolInfo");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyProtocolInfo));
            iDelegateProtocolInfo = new ActionDelegate(DoProtocolInfo);
            EnableAction(action, iDelegateProtocolInfo, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action TransportState is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// TransportState must be overridden if this is called.</remarks>
        protected void EnableActionTransportState()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("TransportState");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyTransportState));
            iDelegateTransportState = new ActionDelegate(DoTransportState);
            EnableAction(action, iDelegateTransportState, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Play action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Play action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlay was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void Play(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Stop action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Stop action for the owning device.
        ///
        /// Must be implemented iff EnableActionStop was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void Stop(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSender action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSender action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSender was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aUri"></param>
        /// <param name="aMetadata"></param>
        protected virtual void SetSender(IDvInvocation aInvocation, string aUri, string aMetadata)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Sender action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Sender action for the owning device.
        ///
        /// Must be implemented iff EnableActionSender was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aUri"></param>
        /// <param name="aMetadata"></param>
        protected virtual void Sender(IDvInvocation aInvocation, out string aUri, out string aMetadata)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ProtocolInfo action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ProtocolInfo action for the owning device.
        ///
        /// Must be implemented iff EnableActionProtocolInfo was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void ProtocolInfo(IDvInvocation aInvocation, out string aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// TransportState action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// TransportState action for the owning device.
        ///
        /// Must be implemented iff EnableActionTransportState was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void TransportState(IDvInvocation aInvocation, out string aValue)
        {
            throw (new ActionDisabledError());
        }

        private static int DoPlay(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgReceiver1 self = (DvProviderAvOpenhomeOrgReceiver1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Play(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Play");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Play"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Play", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Play", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoStop(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgReceiver1 self = (DvProviderAvOpenhomeOrgReceiver1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Stop(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Stop");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Stop"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Stop", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Stop", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetSender(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgReceiver1 self = (DvProviderAvOpenhomeOrgReceiver1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string uri;
            string metadata;
            try
            {
                invocation.ReadStart();
                uri = invocation.ReadString("Uri");
                metadata = invocation.ReadString("Metadata");
                invocation.ReadEnd();
                self.SetSender(invocation, uri, metadata);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetSender");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetSender"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetSender", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetSender", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSender(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgReceiver1 self = (DvProviderAvOpenhomeOrgReceiver1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string uri;
            string metadata;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Sender(invocation, out uri, out metadata);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Sender");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Sender"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Sender", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Uri", uri);
                invocation.WriteString("Metadata", metadata);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Sender", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoProtocolInfo(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgReceiver1 self = (DvProviderAvOpenhomeOrgReceiver1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ProtocolInfo(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "ProtocolInfo");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "ProtocolInfo"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ProtocolInfo", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ProtocolInfo", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoTransportState(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgReceiver1 self = (DvProviderAvOpenhomeOrgReceiver1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.TransportState(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "TransportState");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "TransportState"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "TransportState", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "TransportState", e.TargetSite.Name);
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

