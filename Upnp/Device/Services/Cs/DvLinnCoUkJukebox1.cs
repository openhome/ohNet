using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkJukebox1 : IDisposable
    {
        [DllImport("DvLinnCoUkJukebox1")]
        static extern IntPtr DvServiceLinnCoUkJukebox1Create(IntPtr aDeviceHandle);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvServiceLinnCoUkJukebox1Destroy(IntPtr aHandle);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe int DvServiceLinnCoUkJukebox1SetPropertyCurrentPreset(IntPtr aHandle, uint aValue);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe void DvServiceLinnCoUkJukebox1GetPropertyCurrentPreset(IntPtr aHandle, uint* aValue);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe int DvServiceLinnCoUkJukebox1SetPropertyPresetPrefix(IntPtr aHandle, char* aValue);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe void DvServiceLinnCoUkJukebox1GetPropertyPresetPrefix(IntPtr aHandle, char** aValue);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe int DvServiceLinnCoUkJukebox1SetPropertyAlbumArtFileName(IntPtr aHandle, char* aValue);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern unsafe void DvServiceLinnCoUkJukebox1GetPropertyAlbumArtFileName(IntPtr aHandle, char** aValue);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvServiceLinnCoUkJukebox1EnableActionSetPresetPrefix(IntPtr aHandle, CallbackSetPresetPrefix aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvServiceLinnCoUkJukebox1EnableActionPresetPrefix(IntPtr aHandle, CallbackPresetPrefix aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvServiceLinnCoUkJukebox1EnableActionSetAlbumArtFileName(IntPtr aHandle, CallbackSetAlbumArtFileName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvServiceLinnCoUkJukebox1EnableActionAlbumArtFileName(IntPtr aHandle, CallbackAlbumArtFileName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvServiceLinnCoUkJukebox1EnableActionSetCurrentPreset(IntPtr aHandle, CallbackSetCurrentPreset aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvServiceLinnCoUkJukebox1EnableActionCurrentPreset(IntPtr aHandle, CallbackCurrentPreset aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvServiceLinnCoUkJukebox1EnableActionPresetMetaData(IntPtr aHandle, CallbackPresetMetaData aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkJukebox1")]
        static extern void DvServiceLinnCoUkJukebox1EnableActionLoadManifest(IntPtr aHandle, CallbackLoadManifest aCallback, IntPtr aPtr);
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

        private IntPtr iHandle;
        private GCHandle iGch;
        private CallbackSetPresetPrefix iCallbackSetPresetPrefix;
        private CallbackPresetPrefix iCallbackPresetPrefix;
        private CallbackSetAlbumArtFileName iCallbackSetAlbumArtFileName;
        private CallbackAlbumArtFileName iCallbackAlbumArtFileName;
        private CallbackSetCurrentPreset iCallbackSetCurrentPreset;
        private CallbackCurrentPreset iCallbackCurrentPreset;
        private CallbackPresetMetaData iCallbackPresetMetaData;
        private CallbackLoadManifest iCallbackLoadManifest;

        public DvServiceLinnCoUkJukebox1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkJukebox1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyCurrentPreset(uint aValue)
        {
            if (0 != DvServiceLinnCoUkJukebox1SetPropertyCurrentPreset(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyCurrentPreset(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkJukebox1GetPropertyCurrentPreset(iHandle, value);
            }
        }

        public unsafe void SetPropertyPresetPrefix(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkJukebox1SetPropertyPresetPrefix(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyPresetPrefix(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkJukebox1GetPropertyPresetPrefix(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyAlbumArtFileName(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkJukebox1SetPropertyAlbumArtFileName(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyAlbumArtFileName(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkJukebox1GetPropertyAlbumArtFileName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionSetPresetPrefix()
        {
            iCallbackSetPresetPrefix = new CallbackSetPresetPrefix(DoSetPresetPrefix);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkJukebox1EnableActionSetPresetPrefix(iHandle, iCallbackSetPresetPrefix, ptr);
        }

        protected unsafe void EnableActionPresetPrefix()
        {
            iCallbackPresetPrefix = new CallbackPresetPrefix(DoPresetPrefix);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkJukebox1EnableActionPresetPrefix(iHandle, iCallbackPresetPrefix, ptr);
        }

        protected unsafe void EnableActionSetAlbumArtFileName()
        {
            iCallbackSetAlbumArtFileName = new CallbackSetAlbumArtFileName(DoSetAlbumArtFileName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkJukebox1EnableActionSetAlbumArtFileName(iHandle, iCallbackSetAlbumArtFileName, ptr);
        }

        protected unsafe void EnableActionAlbumArtFileName()
        {
            iCallbackAlbumArtFileName = new CallbackAlbumArtFileName(DoAlbumArtFileName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkJukebox1EnableActionAlbumArtFileName(iHandle, iCallbackAlbumArtFileName, ptr);
        }

        protected unsafe void EnableActionSetCurrentPreset()
        {
            iCallbackSetCurrentPreset = new CallbackSetCurrentPreset(DoSetCurrentPreset);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkJukebox1EnableActionSetCurrentPreset(iHandle, iCallbackSetCurrentPreset, ptr);
        }

        protected unsafe void EnableActionCurrentPreset()
        {
            iCallbackCurrentPreset = new CallbackCurrentPreset(DoCurrentPreset);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkJukebox1EnableActionCurrentPreset(iHandle, iCallbackCurrentPreset, ptr);
        }

        protected unsafe void EnableActionPresetMetaData()
        {
            iCallbackPresetMetaData = new CallbackPresetMetaData(DoPresetMetaData);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkJukebox1EnableActionPresetMetaData(iHandle, iCallbackPresetMetaData, ptr);
        }

        protected unsafe void EnableActionLoadManifest()
        {
            iCallbackLoadManifest = new CallbackLoadManifest(DoLoadManifest);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkJukebox1EnableActionLoadManifest(iHandle, iCallbackLoadManifest, ptr);
        }

        protected virtual void SetPresetPrefix(uint aVersion, string aaUri)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void PresetPrefix(uint aVersion, out string aaUri)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetAlbumArtFileName(uint aVersion, string aaName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void AlbumArtFileName(uint aVersion, out string aaName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetCurrentPreset(uint aVersion, uint aaPreset)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void CurrentPreset(uint aVersion, out uint aaPreset)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void PresetMetaData(uint aVersion, uint aaPreset, out string aaMetaData)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void LoadManifest(uint aVersion, out uint aaTotalPresets)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetPresetPrefix(IntPtr aPtr, uint aVersion, char* aaUri)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkJukebox1 self = (DvServiceLinnCoUkJukebox1)gch.Target;
            string aUri = Marshal.PtrToStringAnsi((IntPtr)aaUri);
            self.SetPresetPrefix(aVersion, aUri);
            return 0;
        }

        private static unsafe int DoPresetPrefix(IntPtr aPtr, uint aVersion, char** aaUri)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkJukebox1 self = (DvServiceLinnCoUkJukebox1)gch.Target;
            string aUri;
            self.PresetPrefix(aVersion, out aUri);
            *aaUri = (char*)Marshal.StringToHGlobalAnsi(aUri).ToPointer();
            return 0;
        }

        private static unsafe int DoSetAlbumArtFileName(IntPtr aPtr, uint aVersion, char* aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkJukebox1 self = (DvServiceLinnCoUkJukebox1)gch.Target;
            string aName = Marshal.PtrToStringAnsi((IntPtr)aaName);
            self.SetAlbumArtFileName(aVersion, aName);
            return 0;
        }

        private static unsafe int DoAlbumArtFileName(IntPtr aPtr, uint aVersion, char** aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkJukebox1 self = (DvServiceLinnCoUkJukebox1)gch.Target;
            string aName;
            self.AlbumArtFileName(aVersion, out aName);
            *aaName = (char*)Marshal.StringToHGlobalAnsi(aName).ToPointer();
            return 0;
        }

        private static unsafe int DoSetCurrentPreset(IntPtr aPtr, uint aVersion, uint aaPreset)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkJukebox1 self = (DvServiceLinnCoUkJukebox1)gch.Target;
            self.SetCurrentPreset(aVersion, aaPreset);
            return 0;
        }

        private static unsafe int DoCurrentPreset(IntPtr aPtr, uint aVersion, uint* aaPreset)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkJukebox1 self = (DvServiceLinnCoUkJukebox1)gch.Target;
            uint aPreset;
            self.CurrentPreset(aVersion, out aPreset);
            *aaPreset = aPreset;
            return 0;
        }

        private static unsafe int DoPresetMetaData(IntPtr aPtr, uint aVersion, uint aaPreset, char** aaMetaData)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkJukebox1 self = (DvServiceLinnCoUkJukebox1)gch.Target;
            string aMetaData;
            self.PresetMetaData(aVersion, aaPreset, out aMetaData);
            *aaMetaData = (char*)Marshal.StringToHGlobalAnsi(aMetaData).ToPointer();
            return 0;
        }

        private static unsafe int DoLoadManifest(IntPtr aPtr, uint aVersion, uint* aaTotalPresets)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkJukebox1 self = (DvServiceLinnCoUkJukebox1)gch.Target;
            uint aTotalPresets;
            self.LoadManifest(aVersion, out aTotalPresets);
            *aaTotalPresets = aTotalPresets;
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkJukebox1()
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
            DvServiceLinnCoUkJukebox1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

