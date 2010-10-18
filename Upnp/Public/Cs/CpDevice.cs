using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Zapp
{
    public class CpDevice
    {
        [DllImport ("ZappUpnp", CharSet = CharSet.Ansi)]
        static extern IntPtr CpDeviceCUdn(IntPtr aDevice);
        [DllImport ("ZappUpnp")]
        static extern void CpDeviceCAddRef(IntPtr aDevice);
        [DllImport ("ZappUpnp")]
        static extern void CpDeviceCRemoveRef(IntPtr aDevice);
        [DllImport ("ZappUpnp", CharSet = CharSet.Ansi)]
        static extern unsafe int CpDeviceCGetAttribute(IntPtr aDevice, char* aKey, char** aValue);
        [DllImport ("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private IntPtr iHandle;

        public CpDevice(IntPtr aHandle)
        {
            iHandle = aHandle;
        }

        public String Udn()
        {
            IntPtr ip = CpDeviceCUdn(iHandle);
            String udn = Marshal.PtrToStringAnsi(ip);
            return udn;
        }
        
        public void AddRef()
        {
            CpDeviceCAddRef(iHandle);
        }
        
        public void RemoveRef()
        {
            CpDeviceCRemoveRef(iHandle);
        }
        
        public unsafe bool GetAttribute(string aKey, out string aValue)
        {
            char* key = (char*)Marshal.StringToHGlobalAnsi(aKey).ToPointer();
            char* value;
            int ret = CpDeviceCGetAttribute(iHandle, key, &value);
            Marshal.FreeHGlobal((IntPtr)key);
            if (ret != 0)
            {
                aValue = Marshal.PtrToStringAnsi((IntPtr)value);
                ZappFree(value);
                return true;
            }
            aValue = null;
            return false;
        }
        
        public IntPtr Handle()
        {
            return iHandle;
        }
    }

    public class CpDeviceList : IDisposable
    {
        [DllImport ("ZappUpnp")]
        static extern void CpDeviceListDestroy(IntPtr aListHandle);
        [DllImport ("ZappUpnp")]
        static extern void CpDeviceListRefresh(IntPtr aListHandle);

        protected IntPtr iHandle;
        protected GCHandle iGch;
        protected ChangeHandler iAdded;
        protected ChangeHandler iRemoved;
        protected CallbackDevice iFnAdded;
        protected CallbackDevice iFnRemoved;

        protected delegate void CallbackDevice(IntPtr aPtr, IntPtr aHandle);

        public delegate void ChangeHandler(CpDeviceList aList, CpDevice aDevice);

        public void Refresh()
        {
            CpDeviceListRefresh(iHandle);
        }

        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        protected CpDeviceList()
        {
            iGch = GCHandle.Alloc(this);
            iFnAdded = new CallbackDevice(Added);
            iFnRemoved = new CallbackDevice(Removed);
        }

        protected static void Added(IntPtr aPtr, IntPtr aHandle)
        {
            CpDevice device = new CpDevice(aHandle);
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpDeviceList list = (CpDeviceList)gch.Target;
            if (list.iAdded != null) {
                list.iAdded(list, device);
            }
        }

        protected static void Removed(IntPtr aPtr, IntPtr aHandle)
        {
            CpDevice device = new CpDevice(aHandle);
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpDeviceList list = (CpDeviceList)gch.Target;
            if (list.iRemoved != null) {
                list.iRemoved(list, device);
            }
        }

        ~CpDeviceList()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            if (iHandle != IntPtr.Zero)
            {
                CpDeviceListDestroy(iHandle);
                iHandle = IntPtr.Zero;
                iGch.Free();
            }
        }
    }
}
