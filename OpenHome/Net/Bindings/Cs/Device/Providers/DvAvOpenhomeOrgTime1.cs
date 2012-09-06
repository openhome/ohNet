using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderAvOpenhomeOrgTime1 : IDisposable
    {

        /// <summary>
        /// Set the value of the TrackCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTrackCount(uint aValue);

        /// <summary>
        /// Get a copy of the value of the TrackCount property
        /// </summary>
        /// <returns>Value of the TrackCount property.</param>
        uint PropertyTrackCount();

        /// <summary>
        /// Set the value of the Duration property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDuration(uint aValue);

        /// <summary>
        /// Get a copy of the value of the Duration property
        /// </summary>
        /// <returns>Value of the Duration property.</param>
        uint PropertyDuration();

        /// <summary>
        /// Set the value of the Seconds property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertySeconds(uint aValue);

        /// <summary>
        /// Get a copy of the value of the Seconds property
        /// </summary>
        /// <returns>Value of the Seconds property.</param>
        uint PropertySeconds();
        
    }
    /// <summary>
    /// Provider for the av.openhome.org:Time:1 UPnP service
    /// </summary>
    public class DvProviderAvOpenhomeOrgTime1 : DvProvider, IDisposable, IDvProviderAvOpenhomeOrgTime1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateTime;
        private PropertyUint iPropertyTrackCount;
        private PropertyUint iPropertyDuration;
        private PropertyUint iPropertySeconds;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderAvOpenhomeOrgTime1(DvDevice aDevice)
            : base(aDevice, "av.openhome.org", "Time", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Enable the TrackCount property.
        /// </summary>
        public void EnablePropertyTrackCount()
        {
            iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"));
            AddProperty(iPropertyTrackCount);
        }

        /// <summary>
        /// Enable the Duration property.
        /// </summary>
        public void EnablePropertyDuration()
        {
            iPropertyDuration = new PropertyUint(new ParameterUint("Duration"));
            AddProperty(iPropertyDuration);
        }

        /// <summary>
        /// Enable the Seconds property.
        /// </summary>
        public void EnablePropertySeconds()
        {
            iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"));
            AddProperty(iPropertySeconds);
        }

        /// <summary>
        /// Set the value of the TrackCount property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTrackCount has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTrackCount(uint aValue)
        {
            if (iPropertyTrackCount == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyTrackCount, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TrackCount property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTrackCount has previously been called.</remarks>
        /// <returns>Value of the TrackCount property.</returns>
        public uint PropertyTrackCount()
        {
            if (iPropertyTrackCount == null)
                throw new PropertyDisabledError();
            return iPropertyTrackCount.Value();
        }

        /// <summary>
        /// Set the value of the Duration property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyDuration has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDuration(uint aValue)
        {
            if (iPropertyDuration == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyDuration, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Duration property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyDuration has previously been called.</remarks>
        /// <returns>Value of the Duration property.</returns>
        public uint PropertyDuration()
        {
            if (iPropertyDuration == null)
                throw new PropertyDisabledError();
            return iPropertyDuration.Value();
        }

        /// <summary>
        /// Set the value of the Seconds property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySeconds has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySeconds(uint aValue)
        {
            if (iPropertySeconds == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertySeconds, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Seconds property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySeconds has previously been called.</remarks>
        /// <returns>Value of the Seconds property.</returns>
        public uint PropertySeconds()
        {
            if (iPropertySeconds == null)
                throw new PropertyDisabledError();
            return iPropertySeconds.Value();
        }

        /// <summary>
        /// Signal that the action Time is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Time must be overridden if this is called.</remarks>
        protected void EnableActionTime()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Time");
            action.AddOutputParameter(new ParameterRelated("TrackCount", iPropertyTrackCount));
            action.AddOutputParameter(new ParameterRelated("Duration", iPropertyDuration));
            action.AddOutputParameter(new ParameterRelated("Seconds", iPropertySeconds));
            iDelegateTime = new ActionDelegate(DoTime);
            EnableAction(action, iDelegateTime, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Time action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Time action for the owning device.
        ///
        /// Must be implemented iff EnableActionTime was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aTrackCount"></param>
        /// <param name="aDuration"></param>
        /// <param name="aSeconds"></param>
        protected virtual void Time(IDvInvocation aInvocation, out uint aTrackCount, out uint aDuration, out uint aSeconds)
        {
            throw (new ActionDisabledError());
        }

        private static int DoTime(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgTime1 self = (DvProviderAvOpenhomeOrgTime1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint trackCount;
            uint duration;
            uint seconds;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Time(invocation, out trackCount, out duration, out seconds);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Time");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Time"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Time", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("TrackCount", trackCount);
                invocation.WriteUint("Duration", duration);
                invocation.WriteUint("Seconds", seconds);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Time", e.TargetSite.Name);
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

