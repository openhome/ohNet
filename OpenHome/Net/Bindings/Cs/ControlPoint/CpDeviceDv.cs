using System;
using System.Runtime.InteropServices;
using System.Text;

namespace OpenHome.Net.ControlPoint
{
    /// <summary>
    /// Control point device which communicates directly with a device stack's device
    /// </summary>
    public class CpDeviceDv : CpDevice
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr CpDeviceDvCreate(IntPtr aDevice);

        public CpDeviceDv(Device.DvDevice aDevice)
            : base(CpDeviceDvCreate(aDevice.Handle()))
        {
        }
    }
}
