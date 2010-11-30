using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkPtest1 : IDisposable
    {
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Ptest:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkPtest1 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkPtest1")]
        static extern uint DvProviderLinnCoUkPtest1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkPtest1")]
        static extern void DvProviderLinnCoUkPtest1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkPtest1")]
        static extern void DvProviderLinnCoUkPtest1EnableActionTestComPort(uint aHandle, CallbackTestComPort aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPtest1")]
        static extern void DvProviderLinnCoUkPtest1EnableActionLedsOn(uint aHandle, CallbackLedsOn aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPtest1")]
        static extern void DvProviderLinnCoUkPtest1EnableActionLedsOff(uint aHandle, CallbackLedsOff aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackTestComPort(IntPtr aPtr, uint aVersion, uint aaPort, int* aaResult);
        private unsafe delegate int CallbackLedsOn(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackLedsOff(IntPtr aPtr, uint aVersion);

        private GCHandle iGch;
        private CallbackTestComPort iCallbackTestComPort;
        private CallbackLedsOn iCallbackLedsOn;
        private CallbackLedsOff iCallbackLedsOff;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkPtest1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkPtest1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action TestComPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoTestComPort must be overridden if this is called.</remarks>
        protected unsafe void EnableActionTestComPort()
        {
            iCallbackTestComPort = new CallbackTestComPort(DoTestComPort);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPtest1EnableActionTestComPort(iHandle, iCallbackTestComPort, ptr);
        }

        /// <summary>
        /// Signal that the action LedsOn is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoLedsOn must be overridden if this is called.</remarks>
        protected unsafe void EnableActionLedsOn()
        {
            iCallbackLedsOn = new CallbackLedsOn(DoLedsOn);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPtest1EnableActionLedsOn(iHandle, iCallbackLedsOn, ptr);
        }

        /// <summary>
        /// Signal that the action LedsOff is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoLedsOff must be overridden if this is called.</remarks>
        protected unsafe void EnableActionLedsOff()
        {
            iCallbackLedsOff = new CallbackLedsOff(DoLedsOff);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPtest1EnableActionLedsOff(iHandle, iCallbackLedsOff, ptr);
        }

        /// <summary>
        /// TestComPort action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// TestComPort action for the owning device.
        ///
        /// Must be implemented iff EnableActionTestComPort was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPort"></param>
        /// <param name="aaResult"></param>
        protected virtual void TestComPort(uint aVersion, uint aaPort, out bool aaResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// LedsOn action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// LedsOn action for the owning device.
        ///
        /// Must be implemented iff EnableActionLedsOn was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void LedsOn(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// LedsOff action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// LedsOff action for the owning device.
        ///
        /// Must be implemented iff EnableActionLedsOff was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void LedsOff(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoTestComPort(IntPtr aPtr, uint aVersion, uint aaPort, int* aaResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPtest1 self = (DvProviderLinnCoUkPtest1)gch.Target;
            bool aResult;
            self.TestComPort(aVersion, aaPort, out aResult);
            *aaResult = (aResult ? 1 : 0);
            return 0;
        }

        private static unsafe int DoLedsOn(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPtest1 self = (DvProviderLinnCoUkPtest1)gch.Target;
            self.LedsOn(aVersion);
            return 0;
        }

        private static unsafe int DoLedsOff(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPtest1 self = (DvProviderLinnCoUkPtest1)gch.Target;
            self.LedsOff(aVersion);
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

        ~DvProviderLinnCoUkPtest1()
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
            DvProviderLinnCoUkPtest1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

