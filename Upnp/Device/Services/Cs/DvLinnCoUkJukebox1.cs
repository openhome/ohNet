using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    /// <summary>
    /// Provider for the linn.co.uk:Jukebox:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkJukebox1 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkJukebox1")]
        static extern uint DvProviderLinnCoUkJukebox1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvProviderLinnCoUkJukebox1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe int DvProviderLinnCoUkJukebox1SetPropertyCurrentPreset(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe void DvProviderLinnCoUkJukebox1GetPropertyCurrentPreset(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe int DvProviderLinnCoUkJukebox1SetPropertyPresetPrefix(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe void DvProviderLinnCoUkJukebox1GetPropertyPresetPrefix(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe int DvProviderLinnCoUkJukebox1SetPropertyAlbumArtFileName(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe void DvProviderLinnCoUkJukebox1GetPropertyAlbumArtFileName(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvProviderLinnCoUkJukebox1EnableActionSetPresetPrefix(uint aHandle, CallbackSetPresetPrefix aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvProviderLinnCoUkJukebox1EnableActionPresetPrefix(uint aHandle, CallbackPresetPrefix aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvProviderLinnCoUkJukebox1EnableActionSetAlbumArtFileName(uint aHandle, CallbackSetAlbumArtFileName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvProviderLinnCoUkJukebox1EnableActionAlbumArtFileName(uint aHandle, CallbackAlbumArtFileName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvProviderLinnCoUkJukebox1EnableActionSetCurrentPreset(uint aHandle, CallbackSetCurrentPreset aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvProviderLinnCoUkJukebox1EnableActionCurrentPreset(uint aHandle, CallbackCurrentPreset aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvProviderLinnCoUkJukebox1EnableActionPresetMetaData(uint aHandle, CallbackPresetMetaData aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvProviderLinnCoUkJukebox1EnableActionLoadManifest(uint aHandle, CallbackLoadManifest aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSetPresetPrefix(IntPtr aPtr, uint aVersion, char* aaUri);
        private unsafe delegate int CallbackPresetPrefix(IntPtr aPtr, uint aVersion, char** aaUri);
        private unsafe delegate int CallbackSetAlbumArtFileName(IntPtr aPtr, uint aVersion, char* aaName);
        private unsafe delegate int CallbackAlbumArtFileName(IntPtr aPtr, uint aVersion, char** aaName);
        private unsafe delegate int CallbackSetCurrentPreset(IntPtr aPtr, uint aVersion, uint aaPreset);
        private unsafe delegate int CallbackCurrentPreset(IntPtr aPtr, uint aVersion, uint* aaPreset);
        private unsafe delegate int CallbackPresetMetaData(IntPtr aPtr, uint aVersion, uint aaPreset, char** aaMetaData);
        private unsafe delegate int CallbackLoadManifest(IntPtr aPtr, uint aVersion, uint* aaTotalPresets);

        private GCHandle iGch;
        private CallbackSetPresetPrefix iCallbackSetPresetPrefix;
        private CallbackPresetPrefix iCallbackPresetPrefix;
        private CallbackSetAlbumArtFileName iCallbackSetAlbumArtFileName;
        private CallbackAlbumArtFileName iCallbackAlbumArtFileName;
        private CallbackSetCurrentPreset iCallbackSetCurrentPreset;
        private CallbackCurrentPreset iCallbackCurrentPreset;
        private CallbackPresetMetaData iCallbackPresetMetaData;
        private CallbackLoadManifest iCallbackLoadManifest;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkJukebox1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkJukebox1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the CurrentPreset property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyCurrentPreset(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkJukebox1SetPropertyCurrentPreset(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the CurrentPreset property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyCurrentPreset(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkJukebox1GetPropertyCurrentPreset(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the PresetPrefix property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyPresetPrefix(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkJukebox1SetPropertyPresetPrefix(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the PresetPrefix property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyPresetPrefix(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkJukebox1GetPropertyPresetPrefix(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the AlbumArtFileName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyAlbumArtFileName(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkJukebox1SetPropertyAlbumArtFileName(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the AlbumArtFileName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyAlbumArtFileName(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkJukebox1GetPropertyAlbumArtFileName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Signal that the action SetPresetPrefix is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetPresetPrefix must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetPresetPrefix()
        {
            iCallbackSetPresetPrefix = new CallbackSetPresetPrefix(DoSetPresetPrefix);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkJukebox1EnableActionSetPresetPrefix(iHandle, iCallbackSetPresetPrefix, ptr);
        }

        /// <summary>
        /// Signal that the action PresetPrefix is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPresetPrefix must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPresetPrefix()
        {
            iCallbackPresetPrefix = new CallbackPresetPrefix(DoPresetPrefix);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkJukebox1EnableActionPresetPrefix(iHandle, iCallbackPresetPrefix, ptr);
        }

        /// <summary>
        /// Signal that the action SetAlbumArtFileName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetAlbumArtFileName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetAlbumArtFileName()
        {
            iCallbackSetAlbumArtFileName = new CallbackSetAlbumArtFileName(DoSetAlbumArtFileName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkJukebox1EnableActionSetAlbumArtFileName(iHandle, iCallbackSetAlbumArtFileName, ptr);
        }

        /// <summary>
        /// Signal that the action AlbumArtFileName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoAlbumArtFileName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionAlbumArtFileName()
        {
            iCallbackAlbumArtFileName = new CallbackAlbumArtFileName(DoAlbumArtFileName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkJukebox1EnableActionAlbumArtFileName(iHandle, iCallbackAlbumArtFileName, ptr);
        }

        /// <summary>
        /// Signal that the action SetCurrentPreset is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetCurrentPreset must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetCurrentPreset()
        {
            iCallbackSetCurrentPreset = new CallbackSetCurrentPreset(DoSetCurrentPreset);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkJukebox1EnableActionSetCurrentPreset(iHandle, iCallbackSetCurrentPreset, ptr);
        }

        /// <summary>
        /// Signal that the action CurrentPreset is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoCurrentPreset must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCurrentPreset()
        {
            iCallbackCurrentPreset = new CallbackCurrentPreset(DoCurrentPreset);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkJukebox1EnableActionCurrentPreset(iHandle, iCallbackCurrentPreset, ptr);
        }

        /// <summary>
        /// Signal that the action PresetMetaData is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPresetMetaData must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPresetMetaData()
        {
            iCallbackPresetMetaData = new CallbackPresetMetaData(DoPresetMetaData);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkJukebox1EnableActionPresetMetaData(iHandle, iCallbackPresetMetaData, ptr);
        }

        /// <summary>
        /// Signal that the action LoadManifest is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoLoadManifest must be overridden if this is called.</remarks>
        protected unsafe void EnableActionLoadManifest()
        {
            iCallbackLoadManifest = new CallbackLoadManifest(DoLoadManifest);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkJukebox1EnableActionLoadManifest(iHandle, iCallbackLoadManifest, ptr);
        }

        /// <summary>
        /// SetPresetPrefix action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetPresetPrefix action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetPresetPrefix was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUri"></param>
        protected virtual void SetPresetPrefix(uint aVersion, string aaUri)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PresetPrefix action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PresetPrefix action for the owning device.
        ///
        /// Must be implemented iff EnableActionPresetPrefix was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUri"></param>
        protected virtual void PresetPrefix(uint aVersion, out string aaUri)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetAlbumArtFileName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetAlbumArtFileName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetAlbumArtFileName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaName"></param>
        protected virtual void SetAlbumArtFileName(uint aVersion, string aaName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// AlbumArtFileName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// AlbumArtFileName action for the owning device.
        ///
        /// Must be implemented iff EnableActionAlbumArtFileName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaName"></param>
        protected virtual void AlbumArtFileName(uint aVersion, out string aaName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetCurrentPreset action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetCurrentPreset action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetCurrentPreset was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPreset"></param>
        protected virtual void SetCurrentPreset(uint aVersion, uint aaPreset)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// CurrentPreset action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// CurrentPreset action for the owning device.
        ///
        /// Must be implemented iff EnableActionCurrentPreset was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPreset"></param>
        protected virtual void CurrentPreset(uint aVersion, out uint aaPreset)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PresetMetaData action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PresetMetaData action for the owning device.
        ///
        /// Must be implemented iff EnableActionPresetMetaData was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPreset"></param>
        /// <param name="aaMetaData"></param>
        protected virtual void PresetMetaData(uint aVersion, uint aaPreset, out string aaMetaData)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// LoadManifest action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// LoadManifest action for the owning device.
        ///
        /// Must be implemented iff EnableActionLoadManifest was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTotalPresets"></param>
        protected virtual void LoadManifest(uint aVersion, out uint aaTotalPresets)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetPresetPrefix(IntPtr aPtr, uint aVersion, char* aaUri)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            string aUri = Marshal.PtrToStringAnsi((IntPtr)aaUri);
            self.SetPresetPrefix(aVersion, aUri);
            return 0;
        }

        private static unsafe int DoPresetPrefix(IntPtr aPtr, uint aVersion, char** aaUri)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            string aUri;
            self.PresetPrefix(aVersion, out aUri);
            *aaUri = (char*)Marshal.StringToHGlobalAnsi(aUri).ToPointer();
            return 0;
        }

        private static unsafe int DoSetAlbumArtFileName(IntPtr aPtr, uint aVersion, char* aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            string aName = Marshal.PtrToStringAnsi((IntPtr)aaName);
            self.SetAlbumArtFileName(aVersion, aName);
            return 0;
        }

        private static unsafe int DoAlbumArtFileName(IntPtr aPtr, uint aVersion, char** aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            string aName;
            self.AlbumArtFileName(aVersion, out aName);
            *aaName = (char*)Marshal.StringToHGlobalAnsi(aName).ToPointer();
            return 0;
        }

        private static unsafe int DoSetCurrentPreset(IntPtr aPtr, uint aVersion, uint aaPreset)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            self.SetCurrentPreset(aVersion, aaPreset);
            return 0;
        }

        private static unsafe int DoCurrentPreset(IntPtr aPtr, uint aVersion, uint* aaPreset)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            uint aPreset;
            self.CurrentPreset(aVersion, out aPreset);
            *aaPreset = aPreset;
            return 0;
        }

        private static unsafe int DoPresetMetaData(IntPtr aPtr, uint aVersion, uint aaPreset, char** aaMetaData)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            string aMetaData;
            self.PresetMetaData(aVersion, aaPreset, out aMetaData);
            *aaMetaData = (char*)Marshal.StringToHGlobalAnsi(aMetaData).ToPointer();
            return 0;
        }

        private static unsafe int DoLoadManifest(IntPtr aPtr, uint aVersion, uint* aaTotalPresets)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            uint aTotalPresets;
            self.LoadManifest(aVersion, out aTotalPresets);
            *aaTotalPresets = aTotalPresets;
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

        ~DvProviderLinnCoUkJukebox1()
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
            DvProviderLinnCoUkJukebox1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

