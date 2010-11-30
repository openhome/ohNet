using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    /// <summary>
    /// Provider for the linn.co.uk:MediaTime:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkMediaTime1 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern uint DvProviderLinnCoUkMediaTime1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern void DvProviderLinnCoUkMediaTime1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern unsafe int DvProviderLinnCoUkMediaTime1SetPropertySeconds(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern unsafe void DvProviderLinnCoUkMediaTime1GetPropertySeconds(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern void DvProviderLinnCoUkMediaTime1EnableActionSeconds(uint aHandle, CallbackSeconds aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSeconds(IntPtr aPtr, uint aVersion, uint* aaSeconds);

        private GCHandle iGch;
        private CallbackSeconds iCallbackSeconds;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkMediaTime1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkMediaTime1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the Seconds property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertySeconds(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkMediaTime1SetPropertySeconds(iHandle, aValue, &changed))
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
                DvProviderLinnCoUkMediaTime1GetPropertySeconds(iHandle, value);
            }
        }

        /// <summary>
        /// Signal that the action Seconds is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSeconds must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeconds()
        {
            iCallbackSeconds = new CallbackSeconds(DoSeconds);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkMediaTime1EnableActionSeconds(iHandle, iCallbackSeconds, ptr);
        }

        /// <summary>
        /// Seconds action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Seconds action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeconds was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSeconds"></param>
        protected virtual void Seconds(uint aVersion, out uint aaSeconds)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSeconds(IntPtr aPtr, uint aVersion, uint* aaSeconds)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkMediaTime1 self = (DvProviderLinnCoUkMediaTime1)gch.Target;
            uint aSeconds;
            self.Seconds(aVersion, out aSeconds);
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

        ~DvProviderLinnCoUkMediaTime1()
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
            DvProviderLinnCoUkMediaTime1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

