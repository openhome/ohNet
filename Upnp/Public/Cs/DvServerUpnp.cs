using System;
using System.Runtime.InteropServices;

namespace Zapp.Device
{
    public class DvServerUpnp : IDisposable
    {
        [DllImport("ZappUpnp")]
        static extern IntPtr DvServerUpnpCreate();
        [DllImport("ZappUpnp")]
        static extern void DvServerUpnpDestroy(IntPtr aServer);
        [DllImport("ZappUpnp")]
        static extern void DvServerUpnpAddDevice(IntPtr aServer, IntPtr aDevice);

        private IntPtr iHandle;

        public DvServerUpnp()
        {
            iHandle = DvServerUpnpCreate();
        }

        public void AddDevice(DvDevice aDevice)
        {
            DvServerUpnpAddDevice(iHandle, aDevice.Handle());
        }

        public void Dispose()
        {
            DvServerUpnpDestroy(iHandle);
            iHandle = IntPtr.Zero;
        }
    }
}
