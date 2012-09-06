using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderUpnpOrgSwitchPower1 : IDisposable
    {

        /// <summary>
        /// Set the value of the Status property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStatus(bool aValue);

        /// <summary>
        /// Get a copy of the value of the Status property
        /// </summary>
        /// <returns>Value of the Status property.</param>
        bool PropertyStatus();
        
    }
    /// <summary>
    /// Provider for the upnp.org:SwitchPower:1 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgSwitchPower1 : DvProvider, IDisposable, IDvProviderUpnpOrgSwitchPower1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateSetTarget;
        private ActionDelegate iDelegateGetTarget;
        private ActionDelegate iDelegateGetStatus;
        private PropertyBool iPropertyStatus;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgSwitchPower1(DvDevice aDevice)
            : base(aDevice, "upnp.org", "SwitchPower", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Enable the Status property.
        /// </summary>
        public void EnablePropertyStatus()
        {
            iPropertyStatus = new PropertyBool(new ParameterBool("Status"));
            AddProperty(iPropertyStatus);
        }

        /// <summary>
        /// Set the value of the Status property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyStatus has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyStatus(bool aValue)
        {
            if (iPropertyStatus == null)
                throw new PropertyDisabledError();
            return SetPropertyBool(iPropertyStatus, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Status property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyStatus has previously been called.</remarks>
        /// <returns>Value of the Status property.</returns>
        public bool PropertyStatus()
        {
            if (iPropertyStatus == null)
                throw new PropertyDisabledError();
            return iPropertyStatus.Value();
        }

        /// <summary>
        /// Signal that the action SetTarget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetTarget must be overridden if this is called.</remarks>
        protected void EnableActionSetTarget()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetTarget");
            action.AddInputParameter(new ParameterBool("newTargetValue"));
            iDelegateSetTarget = new ActionDelegate(DoSetTarget);
            EnableAction(action, iDelegateSetTarget, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetTarget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetTarget must be overridden if this is called.</remarks>
        protected void EnableActionGetTarget()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetTarget");
            action.AddOutputParameter(new ParameterBool("RetTargetValue"));
            iDelegateGetTarget = new ActionDelegate(DoGetTarget);
            EnableAction(action, iDelegateGetTarget, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetStatus is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetStatus must be overridden if this is called.</remarks>
        protected void EnableActionGetStatus()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetStatus");
            action.AddOutputParameter(new ParameterRelated("ResultStatus", iPropertyStatus));
            iDelegateGetStatus = new ActionDelegate(DoGetStatus);
            EnableAction(action, iDelegateGetStatus, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// SetTarget action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetTarget action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetTarget was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="anewTargetValue"></param>
        protected virtual void SetTarget(IDvInvocation aInvocation, bool anewTargetValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetTarget action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetTarget action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetTarget was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aRetTargetValue"></param>
        protected virtual void GetTarget(IDvInvocation aInvocation, out bool aRetTargetValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetStatus action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetStatus action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetStatus was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aResultStatus"></param>
        protected virtual void GetStatus(IDvInvocation aInvocation, out bool aResultStatus)
        {
            throw (new ActionDisabledError());
        }

        private static int DoSetTarget(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgSwitchPower1 self = (DvProviderUpnpOrgSwitchPower1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool newTargetValue;
            try
            {
                invocation.ReadStart();
                newTargetValue = invocation.ReadBool("newTargetValue");
                invocation.ReadEnd();
                self.SetTarget(invocation, newTargetValue);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetTarget");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetTarget"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetTarget", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetTarget", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetTarget(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgSwitchPower1 self = (DvProviderUpnpOrgSwitchPower1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool retTargetValue;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetTarget(invocation, out retTargetValue);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetTarget");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetTarget"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetTarget", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("RetTargetValue", retTargetValue);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetTarget", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetStatus(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgSwitchPower1 self = (DvProviderUpnpOrgSwitchPower1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool resultStatus;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetStatus(invocation, out resultStatus);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetStatus");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetStatus"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetStatus", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("ResultStatus", resultStatus);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetStatus", e.TargetSite.Name);
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

