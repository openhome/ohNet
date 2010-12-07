using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkDebug2 : IDisposable
    {
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Debug:2 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkDebug2 : DvProvider, IDisposable, IDvProviderLinnCoUkDebug2
    {
        [DllImport("DvLinnCoUkDebug2")]
        static extern IntPtr DvProviderLinnCoUkDebug2Create(IntPtr aDeviceHandle);
        [DllImport("DvLinnCoUkDebug2")]
        static extern void DvProviderLinnCoUkDebug2Destroy(IntPtr aHandle);
        [DllImport("DvLinnCoUkDebug2")]
        static extern void DvProviderLinnCoUkDebug2EnableActionSetDebugLevel(IntPtr aHandle, CallbackSetDebugLevel aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDebug2")]
        static extern void DvProviderLinnCoUkDebug2EnableActionDebugLevel(IntPtr aHandle, CallbackDebugLevel aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDebug2")]
        static extern void DvProviderLinnCoUkDebug2EnableActionMemWrite(IntPtr aHandle, CallbackMemWrite aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSetDebugLevel(IntPtr aPtr, uint aVersion, uint aaDebugLevel);
        private unsafe delegate int CallbackDebugLevel(IntPtr aPtr, uint aVersion, uint* aaDebugLevel);
        private unsafe delegate int CallbackMemWrite(IntPtr aPtr, uint aVersion, uint aaMemAddress, char* aaMemData, int aaMemDataLen);

        private GCHandle iGch;
        private CallbackSetDebugLevel iCallbackSetDebugLevel;
        private CallbackDebugLevel iCallbackDebugLevel;
        private CallbackMemWrite iCallbackMemWrite;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkDebug2(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkDebug2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action SetDebugLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDebugLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDebugLevel()
        {
            iCallbackSetDebugLevel = new CallbackSetDebugLevel(DoSetDebugLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDebug2EnableActionSetDebugLevel(iHandle, iCallbackSetDebugLevel, ptr);
        }

        /// <summary>
        /// Signal that the action DebugLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDebugLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDebugLevel()
        {
            iCallbackDebugLevel = new CallbackDebugLevel(DoDebugLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDebug2EnableActionDebugLevel(iHandle, iCallbackDebugLevel, ptr);
        }

        /// <summary>
        /// Signal that the action MemWrite is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoMemWrite must be overridden if this is called.</remarks>
        protected unsafe void EnableActionMemWrite()
        {
            iCallbackMemWrite = new CallbackMemWrite(DoMemWrite);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDebug2EnableActionMemWrite(iHandle, iCallbackMemWrite, ptr);
        }

        /// <summary>
        /// SetDebugLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDebugLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDebugLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDebugLevel"></param>
        protected virtual void SetDebugLevel(uint aVersion, uint aaDebugLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DebugLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DebugLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionDebugLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDebugLevel"></param>
        protected virtual void DebugLevel(uint aVersion, out uint aaDebugLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// MemWrite action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// MemWrite action for the owning device.
        ///
        /// Must be implemented iff EnableActionMemWrite was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMemAddress"></param>
        /// <param name="aaMemData"></param>
        protected virtual void MemWrite(uint aVersion, uint aaMemAddress, string aaMemData)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetDebugLevel(IntPtr aPtr, uint aVersion, uint aaDebugLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDebug2 self = (DvProviderLinnCoUkDebug2)gch.Target;
            self.SetDebugLevel(aVersion, aaDebugLevel);
            return 0;
        }

        private static unsafe int DoDebugLevel(IntPtr aPtr, uint aVersion, uint* aaDebugLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDebug2 self = (DvProviderLinnCoUkDebug2)gch.Target;
            uint aDebugLevel;
            self.DebugLevel(aVersion, out aDebugLevel);
            *aaDebugLevel = aDebugLevel;
            return 0;
        }

        private static unsafe int DoMemWrite(IntPtr aPtr, uint aVersion, uint aaMemAddress, char* aaMemData, int aaMemDataLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDebug2 self = (DvProviderLinnCoUkDebug2)gch.Target;
            string aMemData = Marshal.PtrToStringAnsi((IntPtr)aaMemData, aaMemDataLen);
            self.MemWrite(aVersion, aaMemAddress, aMemData);
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

        ~DvProviderLinnCoUkDebug2()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
            }
            DvProviderLinnCoUkDebug2Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

