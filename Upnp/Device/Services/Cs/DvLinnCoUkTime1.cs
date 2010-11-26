using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    /// <summary>
    /// Provider for the linn.co.uk:Time:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkTime1 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkTime1")]
        static extern uint DvProviderLinnCoUkTime1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkTime1")]
        static extern void DvProviderLinnCoUkTime1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe int DvProviderLinnCoUkTime1SetPropertyTrackCount(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe void DvProviderLinnCoUkTime1GetPropertyTrackCount(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe int DvProviderLinnCoUkTime1SetPropertyDuration(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe void DvProviderLinnCoUkTime1GetPropertyDuration(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe int DvProviderLinnCoUkTime1SetPropertySeconds(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe void DvProviderLinnCoUkTime1GetPropertySeconds(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern void DvProviderLinnCoUkTime1EnableActionTime(uint aHandle, CallbackTime aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackTime(IntPtr aPtr, uint aVersion, uint* aaTrackCount, uint* aaDuration, uint* aaSeconds);

        private GCHandle iGch;
        private CallbackTime iCallbackTime;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkTime1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkTime1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the TrackCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTrackCount(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkTime1SetPropertyTrackCount(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TrackCount property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTrackCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkTime1GetPropertyTrackCount(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the Duration property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDuration(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkTime1SetPropertyDuration(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Duration property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDuration(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkTime1GetPropertyDuration(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the Seconds property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertySeconds(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkTime1SetPropertySeconds(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Seconds property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertySeconds(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkTime1GetPropertySeconds(iHandle, value);
            }
        }

        /// <summary>
        /// Signal that the action Time is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoTime must be overridden if this is called.</remarks>
        protected unsafe void EnableActionTime()
        {
            iCallbackTime = new CallbackTime(DoTime);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkTime1EnableActionTime(iHandle, iCallbackTime, ptr);
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

        private static unsafe int DoTime(IntPtr aPtr, uint aVersion, uint* aaTrackCount, uint* aaDuration, uint* aaSeconds)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkTime1 self = (DvProviderLinnCoUkTime1)gch.Target;
            uint aTrackCount;
            uint aDuration;
            uint aSeconds;
            self.Time(aVersion, out aTrackCount, out aDuration, out aSeconds);
            *aaTrackCount = aTrackCount;
            *aaDuration = aDuration;
            *aaSeconds = aSeconds;
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
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
            uint handle;
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                handle = iHandle;
                iHandle = 0;
            }
            DvProviderLinnCoUkTime1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

