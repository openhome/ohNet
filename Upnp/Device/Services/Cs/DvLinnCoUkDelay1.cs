using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkDelay1 : IDisposable
    {

        /// <summary>
        /// Set the value of the PresetXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyPresetXml(string aValue);

        /// <summary>
        /// Get a copy of the value of the PresetXml property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyPresetXml(out string aValue);

        /// <summary>
        /// Set the value of the PresetIndex property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyPresetIndex(uint aValue);

        /// <summary>
        /// Get a copy of the value of the PresetIndex property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyPresetIndex(out uint aValue);
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Delay:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkDelay1 : DvProvider, IDisposable, IDvProviderLinnCoUkDelay1
    {
        [DllImport("DvLinnCoUkDelay1")]
        static extern IntPtr DvProviderLinnCoUkDelay1Create(IntPtr aDeviceHandle);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvProviderLinnCoUkDelay1Destroy(IntPtr aHandle);
        [DllImport("DvLinnCoUkDelay1")]
        static extern unsafe int DvProviderLinnCoUkDelay1SetPropertyPresetXml(IntPtr aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDelay1")]
        static extern unsafe void DvProviderLinnCoUkDelay1GetPropertyPresetXml(IntPtr aHandle, char** aValue);
        [DllImport("DvLinnCoUkDelay1")]
        static extern unsafe int DvProviderLinnCoUkDelay1SetPropertyPresetIndex(IntPtr aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDelay1")]
        static extern unsafe void DvProviderLinnCoUkDelay1GetPropertyPresetIndex(IntPtr aHandle, uint* aValue);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvProviderLinnCoUkDelay1EnableActionPresetXml(IntPtr aHandle, CallbackPresetXml aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvProviderLinnCoUkDelay1EnableActionPresetIndex(IntPtr aHandle, CallbackPresetIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvProviderLinnCoUkDelay1EnableActionSetPresetIndex(IntPtr aHandle, CallbackSetPresetIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvProviderLinnCoUkDelay1EnableActionSetPresetDelay(IntPtr aHandle, CallbackSetPresetDelay aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvProviderLinnCoUkDelay1EnableActionSetPresetVisible(IntPtr aHandle, CallbackSetPresetVisible aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvProviderLinnCoUkDelay1EnableActionSetPresetName(IntPtr aHandle, CallbackSetPresetName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvProviderLinnCoUkDelay1EnableActionDelayMinimum(IntPtr aHandle, CallbackDelayMinimum aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvProviderLinnCoUkDelay1EnableActionDelayMaximum(IntPtr aHandle, CallbackDelayMaximum aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvProviderLinnCoUkDelay1EnableActionPresetCount(IntPtr aHandle, CallbackPresetCount aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackPresetXml(IntPtr aPtr, uint aVersion, char** aaPresetXml);
        private unsafe delegate int CallbackPresetIndex(IntPtr aPtr, uint aVersion, uint* aaIndex);
        private unsafe delegate int CallbackSetPresetIndex(IntPtr aPtr, uint aVersion, uint aaIndex);
        private unsafe delegate int CallbackSetPresetDelay(IntPtr aPtr, uint aVersion, uint aaIndex, uint aaDelay);
        private unsafe delegate int CallbackSetPresetVisible(IntPtr aPtr, uint aVersion, uint aaIndex, int aaVisible);
        private unsafe delegate int CallbackSetPresetName(IntPtr aPtr, uint aVersion, uint aaIndex, char* aaName);
        private unsafe delegate int CallbackDelayMinimum(IntPtr aPtr, uint aVersion, uint* aaDelay);
        private unsafe delegate int CallbackDelayMaximum(IntPtr aPtr, uint aVersion, uint* aaDelay);
        private unsafe delegate int CallbackPresetCount(IntPtr aPtr, uint aVersion, uint* aaCount);

        private GCHandle iGch;
        private CallbackPresetXml iCallbackPresetXml;
        private CallbackPresetIndex iCallbackPresetIndex;
        private CallbackSetPresetIndex iCallbackSetPresetIndex;
        private CallbackSetPresetDelay iCallbackSetPresetDelay;
        private CallbackSetPresetVisible iCallbackSetPresetVisible;
        private CallbackSetPresetName iCallbackSetPresetName;
        private CallbackDelayMinimum iCallbackDelayMinimum;
        private CallbackDelayMaximum iCallbackDelayMaximum;
        private CallbackPresetCount iCallbackPresetCount;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkDelay1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkDelay1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the PresetXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyPresetXml(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkDelay1SetPropertyPresetXml(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the PresetXml property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyPresetXml(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkDelay1GetPropertyPresetXml(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the PresetIndex property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyPresetIndex(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkDelay1SetPropertyPresetIndex(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the PresetIndex property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyPresetIndex(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkDelay1GetPropertyPresetIndex(iHandle, value);
            }
        }

        /// <summary>
        /// Signal that the action PresetXml is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPresetXml must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPresetXml()
        {
            iCallbackPresetXml = new CallbackPresetXml(DoPresetXml);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDelay1EnableActionPresetXml(iHandle, iCallbackPresetXml, ptr);
        }

        /// <summary>
        /// Signal that the action PresetIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPresetIndex must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPresetIndex()
        {
            iCallbackPresetIndex = new CallbackPresetIndex(DoPresetIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDelay1EnableActionPresetIndex(iHandle, iCallbackPresetIndex, ptr);
        }

        /// <summary>
        /// Signal that the action SetPresetIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetPresetIndex must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetPresetIndex()
        {
            iCallbackSetPresetIndex = new CallbackSetPresetIndex(DoSetPresetIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDelay1EnableActionSetPresetIndex(iHandle, iCallbackSetPresetIndex, ptr);
        }

        /// <summary>
        /// Signal that the action SetPresetDelay is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetPresetDelay must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetPresetDelay()
        {
            iCallbackSetPresetDelay = new CallbackSetPresetDelay(DoSetPresetDelay);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDelay1EnableActionSetPresetDelay(iHandle, iCallbackSetPresetDelay, ptr);
        }

        /// <summary>
        /// Signal that the action SetPresetVisible is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetPresetVisible must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetPresetVisible()
        {
            iCallbackSetPresetVisible = new CallbackSetPresetVisible(DoSetPresetVisible);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDelay1EnableActionSetPresetVisible(iHandle, iCallbackSetPresetVisible, ptr);
        }

        /// <summary>
        /// Signal that the action SetPresetName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetPresetName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetPresetName()
        {
            iCallbackSetPresetName = new CallbackSetPresetName(DoSetPresetName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDelay1EnableActionSetPresetName(iHandle, iCallbackSetPresetName, ptr);
        }

        /// <summary>
        /// Signal that the action DelayMinimum is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDelayMinimum must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDelayMinimum()
        {
            iCallbackDelayMinimum = new CallbackDelayMinimum(DoDelayMinimum);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDelay1EnableActionDelayMinimum(iHandle, iCallbackDelayMinimum, ptr);
        }

        /// <summary>
        /// Signal that the action DelayMaximum is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDelayMaximum must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDelayMaximum()
        {
            iCallbackDelayMaximum = new CallbackDelayMaximum(DoDelayMaximum);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDelay1EnableActionDelayMaximum(iHandle, iCallbackDelayMaximum, ptr);
        }

        /// <summary>
        /// Signal that the action PresetCount is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPresetCount must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPresetCount()
        {
            iCallbackPresetCount = new CallbackPresetCount(DoPresetCount);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDelay1EnableActionPresetCount(iHandle, iCallbackPresetCount, ptr);
        }

        /// <summary>
        /// PresetXml action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PresetXml action for the owning device.
        ///
        /// Must be implemented iff EnableActionPresetXml was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPresetXml"></param>
        protected virtual void PresetXml(uint aVersion, out string aaPresetXml)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PresetIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PresetIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionPresetIndex was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIndex"></param>
        protected virtual void PresetIndex(uint aVersion, out uint aaIndex)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetPresetIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetPresetIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetPresetIndex was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIndex"></param>
        protected virtual void SetPresetIndex(uint aVersion, uint aaIndex)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetPresetDelay action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetPresetDelay action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetPresetDelay was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIndex"></param>
        /// <param name="aaDelay"></param>
        protected virtual void SetPresetDelay(uint aVersion, uint aaIndex, uint aaDelay)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetPresetVisible action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetPresetVisible action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetPresetVisible was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIndex"></param>
        /// <param name="aaVisible"></param>
        protected virtual void SetPresetVisible(uint aVersion, uint aaIndex, bool aaVisible)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetPresetName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetPresetName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetPresetName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIndex"></param>
        /// <param name="aaName"></param>
        protected virtual void SetPresetName(uint aVersion, uint aaIndex, string aaName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DelayMinimum action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DelayMinimum action for the owning device.
        ///
        /// Must be implemented iff EnableActionDelayMinimum was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDelay"></param>
        protected virtual void DelayMinimum(uint aVersion, out uint aaDelay)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DelayMaximum action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DelayMaximum action for the owning device.
        ///
        /// Must be implemented iff EnableActionDelayMaximum was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDelay"></param>
        protected virtual void DelayMaximum(uint aVersion, out uint aaDelay)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PresetCount action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PresetCount action for the owning device.
        ///
        /// Must be implemented iff EnableActionPresetCount was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCount"></param>
        protected virtual void PresetCount(uint aVersion, out uint aaCount)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoPresetXml(IntPtr aPtr, uint aVersion, char** aaPresetXml)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDelay1 self = (DvProviderLinnCoUkDelay1)gch.Target;
            string aPresetXml;
            self.PresetXml(aVersion, out aPresetXml);
            *aaPresetXml = (char*)Marshal.StringToHGlobalAnsi(aPresetXml).ToPointer();
            return 0;
        }

        private static unsafe int DoPresetIndex(IntPtr aPtr, uint aVersion, uint* aaIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDelay1 self = (DvProviderLinnCoUkDelay1)gch.Target;
            uint aIndex;
            self.PresetIndex(aVersion, out aIndex);
            *aaIndex = aIndex;
            return 0;
        }

        private static unsafe int DoSetPresetIndex(IntPtr aPtr, uint aVersion, uint aaIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDelay1 self = (DvProviderLinnCoUkDelay1)gch.Target;
            self.SetPresetIndex(aVersion, aaIndex);
            return 0;
        }

        private static unsafe int DoSetPresetDelay(IntPtr aPtr, uint aVersion, uint aaIndex, uint aaDelay)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDelay1 self = (DvProviderLinnCoUkDelay1)gch.Target;
            self.SetPresetDelay(aVersion, aaIndex, aaDelay);
            return 0;
        }

        private static unsafe int DoSetPresetVisible(IntPtr aPtr, uint aVersion, uint aaIndex, int aaVisible)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDelay1 self = (DvProviderLinnCoUkDelay1)gch.Target;
            bool aVisible = (aaVisible != 0);
            self.SetPresetVisible(aVersion, aaIndex, aVisible);
            return 0;
        }

        private static unsafe int DoSetPresetName(IntPtr aPtr, uint aVersion, uint aaIndex, char* aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDelay1 self = (DvProviderLinnCoUkDelay1)gch.Target;
            string aName = Marshal.PtrToStringAnsi((IntPtr)aaName);
            self.SetPresetName(aVersion, aaIndex, aName);
            return 0;
        }

        private static unsafe int DoDelayMinimum(IntPtr aPtr, uint aVersion, uint* aaDelay)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDelay1 self = (DvProviderLinnCoUkDelay1)gch.Target;
            uint aDelay;
            self.DelayMinimum(aVersion, out aDelay);
            *aaDelay = aDelay;
            return 0;
        }

        private static unsafe int DoDelayMaximum(IntPtr aPtr, uint aVersion, uint* aaDelay)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDelay1 self = (DvProviderLinnCoUkDelay1)gch.Target;
            uint aDelay;
            self.DelayMaximum(aVersion, out aDelay);
            *aaDelay = aDelay;
            return 0;
        }

        private static unsafe int DoPresetCount(IntPtr aPtr, uint aVersion, uint* aaCount)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDelay1 self = (DvProviderLinnCoUkDelay1)gch.Target;
            uint aCount;
            self.PresetCount(aVersion, out aCount);
            *aaCount = aCount;
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

        ~DvProviderLinnCoUkDelay1()
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
            DvProviderLinnCoUkDelay1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

