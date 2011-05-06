using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkTime1 : IDisposable
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
        /// <param name="aValue">Property's value will be copied here</param>
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
        /// <param name="aValue">Property's value will be copied here</param>
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
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertySeconds();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Time:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkTime1 : DvProvider, IDisposable, IDvProviderLinnCoUkTime1
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
        protected DvProviderLinnCoUkTime1(DvDevice aDevice)
            : base(aDevice, "linn.co.uk", "Time", 1)
        {
            iGch = GCHandle.Alloc(this);
            iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"));
            AddProperty(iPropertyTrackCount);
            iPropertyDuration = new PropertyUint(new ParameterUint("Duration"));
            AddProperty(iPropertyDuration);
            iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"));
            AddProperty(iPropertySeconds);
        }

        /// <summary>
        /// Set the value of the TrackCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTrackCount(uint aValue)
        {
            return SetPropertyUint(iPropertyTrackCount, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TrackCount property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyTrackCount()
        {
            return iPropertyTrackCount.Value();
        }

        /// <summary>
        /// Set the value of the Duration property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDuration(uint aValue)
        {
            return SetPropertyUint(iPropertyDuration, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Duration property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyDuration()
        {
            return iPropertyDuration.Value();
        }

        /// <summary>
        /// Set the value of the Seconds property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySeconds(uint aValue)
        {
            return SetPropertyUint(iPropertySeconds, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Seconds property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertySeconds()
        {
            return iPropertySeconds.Value();
        }

        /// <summary>
        /// Signal that the action Time is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Time must be overridden if this is called.</remarks>
        protected void EnableActionTime()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Time");
            action.AddOutputParameter(new ParameterRelated("aTrackCount", iPropertyTrackCount));
            action.AddOutputParameter(new ParameterRelated("aDuration", iPropertyDuration));
            action.AddOutputParameter(new ParameterRelated("aSeconds", iPropertySeconds));
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTrackCount"></param>
        /// <param name="aaDuration"></param>
        /// <param name="aaSeconds"></param>
        protected virtual void Time(uint aVersion, out uint aaTrackCount, out uint aaDuration, out uint aaSeconds)
        {
            throw (new ActionDisabledError());
        }

        private static int DoTime(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkTime1 self = (DvProviderLinnCoUkTime1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aTrackCount;
            uint aDuration;
            uint aSeconds;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Time(aVersion, out aTrackCount, out aDuration, out aSeconds);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("aTrackCount", aTrackCount);
                invocation.WriteUint("aDuration", aDuration);
                invocation.WriteUint("aSeconds", aSeconds);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkTime1()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProvider();
                iHandle = IntPtr.Zero;
            }
            iGch.Free();
        }
    }
}

