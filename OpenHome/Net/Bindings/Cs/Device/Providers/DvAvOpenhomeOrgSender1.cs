using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderAvOpenhomeOrgSender1 : IDisposable
    {

        /// <summary>
        /// Set the value of the PresentationUrl property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyPresentationUrl(string aValue);

        /// <summary>
        /// Get a copy of the value of the PresentationUrl property
        /// </summary>
        /// <returns>Value of the PresentationUrl property.</param>
        string PropertyPresentationUrl();

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
        /// Set the value of the Audio property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyAudio(bool aValue);

        /// <summary>
        /// Get a copy of the value of the Audio property
        /// </summary>
        /// <returns>Value of the Audio property.</param>
        bool PropertyAudio();

        /// <summary>
        /// Set the value of the Status property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStatus(string aValue);

        /// <summary>
        /// Get a copy of the value of the Status property
        /// </summary>
        /// <returns>Value of the Status property.</param>
        string PropertyStatus();

        /// <summary>
        /// Set the value of the Attributes property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyAttributes(string aValue);

        /// <summary>
        /// Get a copy of the value of the Attributes property
        /// </summary>
        /// <returns>Value of the Attributes property.</param>
        string PropertyAttributes();
    }
    /// <summary>
    /// Provider for the av.openhome.org:Sender:1 UPnP service
    /// </summary>
    public class DvProviderAvOpenhomeOrgSender1 : DvProvider, IDisposable, IDvProviderAvOpenhomeOrgSender1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegatePresentationUrl;
        private ActionDelegate iDelegateMetadata;
        private ActionDelegate iDelegateAudio;
        private ActionDelegate iDelegateStatus;
        private ActionDelegate iDelegateAttributes;
        private PropertyString iPropertyPresentationUrl;
        private PropertyString iPropertyMetadata;
        private PropertyBool iPropertyAudio;
        private PropertyString iPropertyStatus;
        private PropertyString iPropertyAttributes;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderAvOpenhomeOrgSender1(DvDevice aDevice)
            : base(aDevice, "av.openhome.org", "Sender", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Enable the PresentationUrl property.
        /// </summary>
        public void EnablePropertyPresentationUrl()
        {
            List<String> allowedValues = new List<String>();
            iPropertyPresentationUrl = new PropertyString(new ParameterString("PresentationUrl", allowedValues));
            AddProperty(iPropertyPresentationUrl);
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
        /// Enable the Audio property.
        /// </summary>
        public void EnablePropertyAudio()
        {
            iPropertyAudio = new PropertyBool(new ParameterBool("Audio"));
            AddProperty(iPropertyAudio);
        }

        /// <summary>
        /// Enable the Status property.
        /// </summary>
        public void EnablePropertyStatus()
        {
            List<String> allowedValues = new List<String>();
            allowedValues.Add("Enabled");
            allowedValues.Add("Disabled");
            allowedValues.Add("Blocked");
            iPropertyStatus = new PropertyString(new ParameterString("Status", allowedValues));
            AddProperty(iPropertyStatus);
            allowedValues.Clear();
        }

        /// <summary>
        /// Enable the Attributes property.
        /// </summary>
        public void EnablePropertyAttributes()
        {
            List<String> allowedValues = new List<String>();
            iPropertyAttributes = new PropertyString(new ParameterString("Attributes", allowedValues));
            AddProperty(iPropertyAttributes);
        }

        /// <summary>
        /// Set the value of the PresentationUrl property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyPresentationUrl has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyPresentationUrl(string aValue)
        {
            if (iPropertyPresentationUrl == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyPresentationUrl, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the PresentationUrl property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyPresentationUrl has previously been called.</remarks>
        /// <returns>Value of the PresentationUrl property.</returns>
        public string PropertyPresentationUrl()
        {
            if (iPropertyPresentationUrl == null)
                throw new PropertyDisabledError();
            return iPropertyPresentationUrl.Value();
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
        /// Set the value of the Audio property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyAudio has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyAudio(bool aValue)
        {
            if (iPropertyAudio == null)
                throw new PropertyDisabledError();
            return SetPropertyBool(iPropertyAudio, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Audio property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyAudio has previously been called.</remarks>
        /// <returns>Value of the Audio property.</returns>
        public bool PropertyAudio()
        {
            if (iPropertyAudio == null)
                throw new PropertyDisabledError();
            return iPropertyAudio.Value();
        }

        /// <summary>
        /// Set the value of the Status property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyStatus has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyStatus(string aValue)
        {
            if (iPropertyStatus == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyStatus, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Status property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyStatus has previously been called.</remarks>
        /// <returns>Value of the Status property.</returns>
        public string PropertyStatus()
        {
            if (iPropertyStatus == null)
                throw new PropertyDisabledError();
            return iPropertyStatus.Value();
        }

        /// <summary>
        /// Set the value of the Attributes property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyAttributes has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyAttributes(string aValue)
        {
            if (iPropertyAttributes == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyAttributes, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Attributes property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyAttributes has previously been called.</remarks>
        /// <returns>Value of the Attributes property.</returns>
        public string PropertyAttributes()
        {
            if (iPropertyAttributes == null)
                throw new PropertyDisabledError();
            return iPropertyAttributes.Value();
        }

        /// <summary>
        /// Signal that the action PresentationUrl is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PresentationUrl must be overridden if this is called.</remarks>
        protected void EnableActionPresentationUrl()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PresentationUrl");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyPresentationUrl));
            iDelegatePresentationUrl = new ActionDelegate(DoPresentationUrl);
            EnableAction(action, iDelegatePresentationUrl, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Metadata is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Metadata must be overridden if this is called.</remarks>
        protected void EnableActionMetadata()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Metadata");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyMetadata));
            iDelegateMetadata = new ActionDelegate(DoMetadata);
            EnableAction(action, iDelegateMetadata, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Audio is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Audio must be overridden if this is called.</remarks>
        protected void EnableActionAudio()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Audio");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyAudio));
            iDelegateAudio = new ActionDelegate(DoAudio);
            EnableAction(action, iDelegateAudio, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Status is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Status must be overridden if this is called.</remarks>
        protected void EnableActionStatus()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Status");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyStatus));
            iDelegateStatus = new ActionDelegate(DoStatus);
            EnableAction(action, iDelegateStatus, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Attributes is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Attributes must be overridden if this is called.</remarks>
        protected void EnableActionAttributes()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Attributes");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyAttributes));
            iDelegateAttributes = new ActionDelegate(DoAttributes);
            EnableAction(action, iDelegateAttributes, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// PresentationUrl action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PresentationUrl action for the owning device.
        ///
        /// Must be implemented iff EnableActionPresentationUrl was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void PresentationUrl(IDvInvocation aInvocation, out string aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Metadata action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Metadata action for the owning device.
        ///
        /// Must be implemented iff EnableActionMetadata was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Metadata(IDvInvocation aInvocation, out string aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Audio action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Audio action for the owning device.
        ///
        /// Must be implemented iff EnableActionAudio was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Audio(IDvInvocation aInvocation, out bool aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Status action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Status action for the owning device.
        ///
        /// Must be implemented iff EnableActionStatus was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Status(IDvInvocation aInvocation, out string aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Attributes action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Attributes action for the owning device.
        ///
        /// Must be implemented iff EnableActionAttributes was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Attributes(IDvInvocation aInvocation, out string aValue)
        {
            throw (new ActionDisabledError());
        }

        private static int DoPresentationUrl(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgSender1 self = (DvProviderAvOpenhomeOrgSender1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.PresentationUrl(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PresentationUrl");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "PresentationUrl" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "PresentationUrl" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "PresentationUrl" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoMetadata(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgSender1 self = (DvProviderAvOpenhomeOrgSender1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Metadata(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Metadata");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Metadata" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Metadata" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Metadata" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoAudio(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgSender1 self = (DvProviderAvOpenhomeOrgSender1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Audio(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Audio");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Audio" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Audio" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Audio" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoStatus(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgSender1 self = (DvProviderAvOpenhomeOrgSender1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Status(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Status");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Status" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Status" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Status" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoAttributes(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgSender1 self = (DvProviderAvOpenhomeOrgSender1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Attributes(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Attributes");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Attributes" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Attributes" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Attributes" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
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

