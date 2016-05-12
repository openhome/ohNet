using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderOpenhomeOrgSubscriptionLongPoll1 : IDisposable
    {
    }
    /// <summary>
    /// Provider for the openhome.org:SubscriptionLongPoll:1 UPnP service
    /// </summary>
    public class DvProviderOpenhomeOrgSubscriptionLongPoll1 : DvProvider, IDisposable, IDvProviderOpenhomeOrgSubscriptionLongPoll1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateSubscribe;
        private ActionDelegate iDelegateUnsubscribe;
        private ActionDelegate iDelegateRenew;
        private ActionDelegate iDelegateGetPropertyUpdates;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderOpenhomeOrgSubscriptionLongPoll1(DvDevice aDevice)
            : base(aDevice, "openhome.org", "SubscriptionLongPoll", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action Subscribe is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Subscribe must be overridden if this is called.</remarks>
        protected void EnableActionSubscribe()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Subscribe");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ClientId", allowedValues));
            action.AddInputParameter(new ParameterString("Udn", allowedValues));
            action.AddInputParameter(new ParameterString("Service", allowedValues));
            action.AddInputParameter(new ParameterUint("RequestedDuration"));
            action.AddOutputParameter(new ParameterString("Sid", allowedValues));
            action.AddOutputParameter(new ParameterUint("Duration"));
            iDelegateSubscribe = new ActionDelegate(DoSubscribe);
            EnableAction(action, iDelegateSubscribe, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Unsubscribe is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Unsubscribe must be overridden if this is called.</remarks>
        protected void EnableActionUnsubscribe()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Unsubscribe");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("Sid", allowedValues));
            iDelegateUnsubscribe = new ActionDelegate(DoUnsubscribe);
            EnableAction(action, iDelegateUnsubscribe, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Renew is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Renew must be overridden if this is called.</remarks>
        protected void EnableActionRenew()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Renew");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("Sid", allowedValues));
            action.AddInputParameter(new ParameterUint("RequestedDuration"));
            action.AddOutputParameter(new ParameterUint("Duration"));
            iDelegateRenew = new ActionDelegate(DoRenew);
            EnableAction(action, iDelegateRenew, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetPropertyUpdates is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetPropertyUpdates must be overridden if this is called.</remarks>
        protected void EnableActionGetPropertyUpdates()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetPropertyUpdates");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ClientId", allowedValues));
            action.AddOutputParameter(new ParameterString("Updates", allowedValues));
            iDelegateGetPropertyUpdates = new ActionDelegate(DoGetPropertyUpdates);
            EnableAction(action, iDelegateGetPropertyUpdates, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Subscribe action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Subscribe action for the owning device.
        ///
        /// Must be implemented iff EnableActionSubscribe was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aClientId"></param>
        /// <param name="aUdn"></param>
        /// <param name="aService"></param>
        /// <param name="aRequestedDuration"></param>
        /// <param name="aSid"></param>
        /// <param name="aDuration"></param>
        protected virtual void Subscribe(IDvInvocation aInvocation, string aClientId, string aUdn, string aService, uint aRequestedDuration, out string aSid, out uint aDuration)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Unsubscribe action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Unsubscribe action for the owning device.
        ///
        /// Must be implemented iff EnableActionUnsubscribe was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aSid"></param>
        protected virtual void Unsubscribe(IDvInvocation aInvocation, string aSid)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Renew action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Renew action for the owning device.
        ///
        /// Must be implemented iff EnableActionRenew was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aSid"></param>
        /// <param name="aRequestedDuration"></param>
        /// <param name="aDuration"></param>
        protected virtual void Renew(IDvInvocation aInvocation, string aSid, uint aRequestedDuration, out uint aDuration)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetPropertyUpdates action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetPropertyUpdates action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetPropertyUpdates was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aClientId"></param>
        /// <param name="aUpdates"></param>
        protected virtual void GetPropertyUpdates(IDvInvocation aInvocation, string aClientId, out string aUpdates)
        {
            throw (new ActionDisabledError());
        }

        private static int DoSubscribe(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgSubscriptionLongPoll1 self = (DvProviderOpenhomeOrgSubscriptionLongPoll1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string clientId;
            string udn;
            string service;
            uint requestedDuration;
            string sid;
            uint duration;
            try
            {
                invocation.ReadStart();
                clientId = invocation.ReadString("ClientId");
                udn = invocation.ReadString("Udn");
                service = invocation.ReadString("Service");
                requestedDuration = invocation.ReadUint("RequestedDuration");
                invocation.ReadEnd();
                self.Subscribe(invocation, clientId, udn, service, requestedDuration, out sid, out duration);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Subscribe");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Subscribe" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Subscribe" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Sid", sid);
                invocation.WriteUint("Duration", duration);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Subscribe" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoUnsubscribe(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgSubscriptionLongPoll1 self = (DvProviderOpenhomeOrgSubscriptionLongPoll1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sid;
            try
            {
                invocation.ReadStart();
                sid = invocation.ReadString("Sid");
                invocation.ReadEnd();
                self.Unsubscribe(invocation, sid);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Unsubscribe");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Unsubscribe" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Unsubscribe" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Unsubscribe" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoRenew(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgSubscriptionLongPoll1 self = (DvProviderOpenhomeOrgSubscriptionLongPoll1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sid;
            uint requestedDuration;
            uint duration;
            try
            {
                invocation.ReadStart();
                sid = invocation.ReadString("Sid");
                requestedDuration = invocation.ReadUint("RequestedDuration");
                invocation.ReadEnd();
                self.Renew(invocation, sid, requestedDuration, out duration);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Renew");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Renew" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Renew" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Duration", duration);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Renew" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetPropertyUpdates(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgSubscriptionLongPoll1 self = (DvProviderOpenhomeOrgSubscriptionLongPoll1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string clientId;
            string updates;
            try
            {
                invocation.ReadStart();
                clientId = invocation.ReadString("ClientId");
                invocation.ReadEnd();
                self.GetPropertyUpdates(invocation, clientId, out updates);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetPropertyUpdates");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "GetPropertyUpdates" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetPropertyUpdates" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Updates", updates);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetPropertyUpdates" });
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

