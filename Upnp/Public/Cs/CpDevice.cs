using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Zapp.ControlPoint
{
    /// <summary>
    /// Protocol-independent device
    /// </summary>
    /// <remarks>Instance of this class are reference counted and are automatically deleted
    /// when the reference count falls to zero.
    /// All references to class instances must have been removed before Core.Library.Close() is called.</remarks>
    public class CpDevice
    {
        [DllImport ("ZappUpnp", CharSet = CharSet.Ansi)]
        static extern IntPtr CpDeviceCUdn(uint aDevice);
        [DllImport ("ZappUpnp")]
        static extern void CpDeviceCAddRef(uint aDevice);
        [DllImport ("ZappUpnp")]
        static extern void CpDeviceCRemoveRef(uint aDevice);
        [DllImport ("ZappUpnp", CharSet = CharSet.Ansi)]
        static extern unsafe int CpDeviceCGetAttribute(uint aDevice, char* aKey, char** aValue);
        [DllImport ("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private uint iHandle;

        /// <summary>
        /// Constructor. Not intended for external use.
        /// </summary>
        /// <remarks>Devices should be constructed via CpDevice or CpDeviceList subclasses.</remarks>
        /// <param name="aHandle">Handle to the underlying native device</param>
        public CpDevice(uint aHandle)
        {
            iHandle = aHandle;
        }

        /// <summary>
        /// Query the unique identifier associated with a device
        /// </summary>
        /// <returns>Device's (universally unique) name</returns>
        public String Udn()
        {
            IntPtr ip = CpDeviceCUdn(iHandle);
            String udn = Marshal.PtrToStringAnsi(ip);
            return udn;
        }
        
        /// <summary>
        /// Claim a reference to a device.
        /// </summary>
        /// <remarks>Can only be called from code that can guarantee another reference is already held.
        /// Each call to AddRef() must later have exactly one matching call to RemoveRef().</remarks>
        public void AddRef()
        {
            CpDeviceCAddRef(iHandle);
        }
        
        /// <summary>
        /// Remove a reference to a device.
        /// </summary>
        /// <remarks>Removing the final reference causes a device to be deleted.</remarks>
        public void RemoveRef()
        {
            CpDeviceCRemoveRef(iHandle);
        }
        
        /// <summary>
        /// Query the value of one of the device's attributes
        /// </summary>
        /// <param name="aKey">The name of the attribute being queried.  Available attributes
        /// will be listed in a protocol-specific header</param>
        /// <param name="aValue">The value of the attribute</param>
        /// <returns>true if the attribute was available on the device; false otherwise.
        /// aValue will not have been set if false is returned</returns>
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
        
        /// <summary>
        /// Get the handle to the underlying native device
        /// </summary>
        /// <returns>Handle to the underlying native device</returns>
        public uint Handle()
        {
            return iHandle;
        }
    }

    /// <summary>
    /// List of devices available on the current subnet
    /// </summary>
    /// <remarks>Runs callbacks when a device is detected on or removed from a network.
    /// Clients can't iterate the list's contents so must take note of the device in their 'added'
    /// callback and remove the device in their 'removed' callback.
    /// Since CpDevice instances are reference counted, a reference must be claimed inside the
    /// 'added' callback and removed inside the 'removed' callback.
    /// 
    /// This class can't be directly instantiated.  Clients should instead use subclasses which
    /// will define policy on how to detect devices etc.
    /// 
    /// Dispose() must be called before Core.Library.Close().</remarks>
    public class CpDeviceList : IDisposable
    {
        [DllImport ("ZappUpnp")]
        static extern void CpDeviceListDestroy(uint aListHandle);
        [DllImport ("ZappUpnp")]
        static extern void CpDeviceListRefresh(uint aListHandle);

        protected uint iHandle;
        protected GCHandle iGch;
        protected ChangeHandler iAdded;
        protected ChangeHandler iRemoved;
        protected CallbackDevice iFnAdded;
        protected CallbackDevice iFnRemoved;

        protected delegate void CallbackDevice(IntPtr aPtr, uint aHandle);

        public delegate void ChangeHandler(CpDeviceList aList, CpDevice aDevice);

        /// <summary>
        /// Refresh the contents of the list.
        /// </summary>
        /// <remarks>This may be a useful way to quickly update a list after a device has been removed
        /// abruptly from the network (without announcing its removal).
        /// 
        /// The 'added' callback may run any time after this is called to notify new devices.
        /// Any removed devices will be notified by a burst of calls to the 'removed' callback
        /// Core.InitParams::MsearchTimeSecs() seconds after this call is made.
        /// There is no notification that a refresh has completed.  Existing CpDevice instances
        /// can be used as normal throughout the refresh.</remarks>
        public void Refresh()
        {
            CpDeviceListRefresh(iHandle);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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

        protected static void Added(IntPtr aPtr, uint aHandle)
        {
            CpDevice device = new CpDevice(aHandle);
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpDeviceList list = (CpDeviceList)gch.Target;
            if (list.iAdded != null) {
                list.iAdded(list, device);
            }
        }

        protected static void Removed(IntPtr aPtr, uint aHandle)
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
            if (iHandle != 0)
            {
                CpDeviceListDestroy(iHandle);
                iHandle = 0;
                iGch.Free();
            }
        }
    }
}
