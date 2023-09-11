using System;
using System.Runtime.InteropServices;

namespace OpenHome.Net.Device
{
    /// <summary>
    /// UPnP device server.
    /// </summary>
    /// <remarks>Publishes DvDevices as UPnP devices, serves UIs (depending on device configuration) and
    /// manages subscriptions.  This works automatically across all active network interfaces.
    /// One of these servers is setup automatically by the device stack.  This default instance
    /// will be used automatically by all devices.
    /// Additional servers should not be requried for normal use of the device stack.  They may
    /// however be necessary for unusual * cases where a provider is required to make blocking
    /// calls to a proxy.</remarks>
    public class DvServerUpnp : IDisposable
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr DvServerUpnpCreate();
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvServerUpnpDestroy(IntPtr aServer);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvServerUpnpAddDevice(IntPtr aServer, IntPtr aDevice);

        private IntPtr iHandle;

        public DvServerUpnp()
        {
            iHandle = DvServerUpnpCreate();
        }

        /// <summary>
        /// Instruct a device to publish itself using (only) this server.
        /// </summary>
        /// <param name="aDevice"></param>
        public void AddDevice(DvDevice aDevice)
        {
            DvServerUpnpAddDevice(iHandle, aDevice.Handle());
        }

        public void Dispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                DvServerUpnpDestroy(iHandle);
                iHandle = IntPtr.Zero;
            }
        }
    }
}
