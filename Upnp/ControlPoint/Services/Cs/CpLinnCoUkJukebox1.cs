using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkJukebox1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkJukebox1")]
        static extern IntPtr CpProxyLinnCoUkJukebox1Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern void CpProxyLinnCoUkJukebox1Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncSetPresetPrefix(IntPtr aHandle, char* aaUri);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginSetPresetPrefix(IntPtr aHandle, char* aaUri, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndSetPresetPrefix(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncPresetPrefix(IntPtr aHandle, char** aaUri);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginPresetPrefix(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndPresetPrefix(IntPtr aHandle, IntPtr aAsync, char** aaUri);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncSetAlbumArtFileName(IntPtr aHandle, char* aaName);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginSetAlbumArtFileName(IntPtr aHandle, char* aaName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndSetAlbumArtFileName(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncAlbumArtFileName(IntPtr aHandle, char** aaName);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginAlbumArtFileName(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndAlbumArtFileName(IntPtr aHandle, IntPtr aAsync, char** aaName);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncSetCurrentPreset(IntPtr aHandle, uint aaPreset);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginSetCurrentPreset(IntPtr aHandle, uint aaPreset, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndSetCurrentPreset(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncCurrentPreset(IntPtr aHandle, uint* aaPreset);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginCurrentPreset(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndCurrentPreset(IntPtr aHandle, IntPtr aAsync, uint* aaPreset);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncPresetMetaData(IntPtr aHandle, uint aaPreset, char** aaMetaData);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginPresetMetaData(IntPtr aHandle, uint aaPreset, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndPresetMetaData(IntPtr aHandle, IntPtr aAsync, char** aaMetaData);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncLoadManifest(IntPtr aHandle, uint* aaTotalPresets);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginLoadManifest(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndLoadManifest(IntPtr aHandle, IntPtr aAsync, uint* aaTotalPresets);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern void CpProxyLinnCoUkJukebox1SetPropertyCurrentPresetChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern void CpProxyLinnCoUkJukebox1SetPropertyPresetPrefixChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern void CpProxyLinnCoUkJukebox1SetPropertyAlbumArtFileNameChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1PropertyCurrentPreset(IntPtr aHandle, uint* aCurrentPreset);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1PropertyPresetPrefix(IntPtr aHandle, char** aPresetPrefix);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1PropertyAlbumArtFileName(IntPtr aHandle, char** aAlbumArtFileName);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iCurrentPresetChanged;
        private CallbackPropertyChanged iPresetPrefixChanged;
        private CallbackPropertyChanged iAlbumArtFileNameChanged;
        private Callback iCallbackCurrentPresetChanged;
        private Callback iCallbackPresetPrefixChanged;
        private Callback iCallbackAlbumArtFileNameChanged;

        public CpProxyLinnCoUkJukebox1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkJukebox1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncSetPresetPrefix(string aaUri)
        {
			char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
			{
				CpProxyLinnCoUkJukebox1SyncSetPresetPrefix(iHandle, aUri);
			}
			Marshal.FreeHGlobal((IntPtr)aUri);
        }

        public unsafe void BeginSetPresetPrefix(string aaUri, CallbackAsyncComplete aCallback)
        {
			char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginSetPresetPrefix(iHandle, aUri, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aUri);
        }

        public unsafe void EndSetPresetPrefix(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkJukebox1EndSetPresetPrefix(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncPresetPrefix(out string aaUri)
        {
			char* aUri;
			{
				CpProxyLinnCoUkJukebox1SyncPresetPrefix(iHandle, &aUri);
			}
            aaUri = Marshal.PtrToStringAnsi((IntPtr)aUri);
            ZappFree(aUri);
        }

        public unsafe void BeginPresetPrefix(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginPresetPrefix(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndPresetPrefix(IntPtr aAsyncHandle, out string aaUri)
        {
			char* aUri;
			{
				if (0 != CpProxyLinnCoUkJukebox1EndPresetPrefix(iHandle, aAsyncHandle, &aUri))
				{
					throw(new ProxyError());
				}
			}
            aaUri = Marshal.PtrToStringAnsi((IntPtr)aUri);
            ZappFree(aUri);
        }

        public unsafe void SyncSetAlbumArtFileName(string aaName)
        {
			char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
			{
				CpProxyLinnCoUkJukebox1SyncSetAlbumArtFileName(iHandle, aName);
			}
			Marshal.FreeHGlobal((IntPtr)aName);
        }

        public unsafe void BeginSetAlbumArtFileName(string aaName, CallbackAsyncComplete aCallback)
        {
			char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginSetAlbumArtFileName(iHandle, aName, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aName);
        }

        public unsafe void EndSetAlbumArtFileName(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkJukebox1EndSetAlbumArtFileName(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncAlbumArtFileName(out string aaName)
        {
			char* aName;
			{
				CpProxyLinnCoUkJukebox1SyncAlbumArtFileName(iHandle, &aName);
			}
            aaName = Marshal.PtrToStringAnsi((IntPtr)aName);
            ZappFree(aName);
        }

        public unsafe void BeginAlbumArtFileName(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginAlbumArtFileName(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndAlbumArtFileName(IntPtr aAsyncHandle, out string aaName)
        {
			char* aName;
			{
				if (0 != CpProxyLinnCoUkJukebox1EndAlbumArtFileName(iHandle, aAsyncHandle, &aName))
				{
					throw(new ProxyError());
				}
			}
            aaName = Marshal.PtrToStringAnsi((IntPtr)aName);
            ZappFree(aName);
        }

        public unsafe void SyncSetCurrentPreset(uint aaPreset)
        {
			{
				CpProxyLinnCoUkJukebox1SyncSetCurrentPreset(iHandle, aaPreset);
			}
        }

        public unsafe void BeginSetCurrentPreset(uint aaPreset, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginSetCurrentPreset(iHandle, aaPreset, iActionComplete, ptr);
        }

        public unsafe void EndSetCurrentPreset(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkJukebox1EndSetCurrentPreset(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncCurrentPreset(out uint aaPreset)
        {
			fixed (uint* aPreset = &aaPreset)
			{
				CpProxyLinnCoUkJukebox1SyncCurrentPreset(iHandle, aPreset);
			}
        }

        public unsafe void BeginCurrentPreset(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginCurrentPreset(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndCurrentPreset(IntPtr aAsyncHandle, out uint aaPreset)
        {
			fixed (uint* aPreset = &aaPreset)
			{
				if (0 != CpProxyLinnCoUkJukebox1EndCurrentPreset(iHandle, aAsyncHandle, aPreset))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncPresetMetaData(uint aaPreset, out string aaMetaData)
        {
			char* aMetaData;
			{
				CpProxyLinnCoUkJukebox1SyncPresetMetaData(iHandle, aaPreset, &aMetaData);
			}
            aaMetaData = Marshal.PtrToStringAnsi((IntPtr)aMetaData);
            ZappFree(aMetaData);
        }

        public unsafe void BeginPresetMetaData(uint aaPreset, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginPresetMetaData(iHandle, aaPreset, iActionComplete, ptr);
        }

        public unsafe void EndPresetMetaData(IntPtr aAsyncHandle, out string aaMetaData)
        {
			char* aMetaData;
			{
				if (0 != CpProxyLinnCoUkJukebox1EndPresetMetaData(iHandle, aAsyncHandle, &aMetaData))
				{
					throw(new ProxyError());
				}
			}
            aaMetaData = Marshal.PtrToStringAnsi((IntPtr)aMetaData);
            ZappFree(aMetaData);
        }

        public unsafe void SyncLoadManifest(out uint aaTotalPresets)
        {
			fixed (uint* aTotalPresets = &aaTotalPresets)
			{
				CpProxyLinnCoUkJukebox1SyncLoadManifest(iHandle, aTotalPresets);
			}
        }

        public unsafe void BeginLoadManifest(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginLoadManifest(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndLoadManifest(IntPtr aAsyncHandle, out uint aaTotalPresets)
        {
			fixed (uint* aTotalPresets = &aaTotalPresets)
			{
				if (0 != CpProxyLinnCoUkJukebox1EndLoadManifest(iHandle, aAsyncHandle, aTotalPresets))
				{
					throw(new ProxyError());
				}
			}
        }

        public void SetPropertyCurrentPresetChanged(CallbackPropertyChanged aCurrentPresetChanged)
        {
            iCurrentPresetChanged = aCurrentPresetChanged;
            iCallbackCurrentPresetChanged = new Callback(PropertyCurrentPresetChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkJukebox1SetPropertyCurrentPresetChanged(iHandle, iCallbackCurrentPresetChanged, ptr);
        }

        private void PropertyCurrentPresetChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkJukebox1 self = (CpProxyLinnCoUkJukebox1)gch.Target;
            self.iCurrentPresetChanged();
        }

        public void SetPropertyPresetPrefixChanged(CallbackPropertyChanged aPresetPrefixChanged)
        {
            iPresetPrefixChanged = aPresetPrefixChanged;
            iCallbackPresetPrefixChanged = new Callback(PropertyPresetPrefixChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkJukebox1SetPropertyPresetPrefixChanged(iHandle, iCallbackPresetPrefixChanged, ptr);
        }

        private void PropertyPresetPrefixChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkJukebox1 self = (CpProxyLinnCoUkJukebox1)gch.Target;
            self.iPresetPrefixChanged();
        }

        public void SetPropertyAlbumArtFileNameChanged(CallbackPropertyChanged aAlbumArtFileNameChanged)
        {
            iAlbumArtFileNameChanged = aAlbumArtFileNameChanged;
            iCallbackAlbumArtFileNameChanged = new Callback(PropertyAlbumArtFileNameChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkJukebox1SetPropertyAlbumArtFileNameChanged(iHandle, iCallbackAlbumArtFileNameChanged, ptr);
        }

        private void PropertyAlbumArtFileNameChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkJukebox1 self = (CpProxyLinnCoUkJukebox1)gch.Target;
            self.iAlbumArtFileNameChanged();
        }

        public unsafe void PropertyCurrentPreset(out uint aCurrentPreset)
        {
			fixed (uint* currentPreset = &aCurrentPreset)
			{
	            CpProxyLinnCoUkJukebox1PropertyCurrentPreset(iHandle, currentPreset);
			}
        }

        public unsafe void PropertyPresetPrefix(out string aPresetPrefix)
        {
			char* ptr;
            CpProxyLinnCoUkJukebox1PropertyPresetPrefix(iHandle, &ptr);
            aPresetPrefix = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyAlbumArtFileName(out string aAlbumArtFileName)
        {
			char* ptr;
            CpProxyLinnCoUkJukebox1PropertyAlbumArtFileName(iHandle, &ptr);
            aAlbumArtFileName = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkJukebox1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
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
            CpProxyLinnCoUkJukebox1Destroy(handle);
            iGch.Free();
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
            else
            {
                DisposeProxy();
            }
        }
    }
}

