using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Zapp
{
    public class CpDeviceDv : CpDevice
    {
        [DllImport ("ZappUpnp", CharSet = CharSet.Ansi)]
        static extern uint CpDeviceDvCreate(uint aDevice);

        public CpDeviceDv(DvDevice aDevice)
            : base(CpDeviceDvCreate(aDevice.Handle()))
        {
        }
    }
}
