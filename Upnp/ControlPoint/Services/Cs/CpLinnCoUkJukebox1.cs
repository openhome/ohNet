using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkJukebox1 : ICpProxy, IDisposable
    {
        void SyncSetPresetPrefix(string aaUri);
        void BeginSetPresetPrefix(string aaUri, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetPresetPrefix(uint aAsyncHandle);
        void SyncPresetPrefix(out string aaUri);
        void BeginPresetPrefix(CpProxy.CallbackAsyncComplete aCallback);
        void EndPresetPrefix(uint aAsyncHandle, out string aaUri);
        void SyncSetAlbumArtFileName(string aaName);
        void BeginSetAlbumArtFileName(string aaName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetAlbumArtFileName(uint aAsyncHandle);
        void SyncAlbumArtFileName(out string aaName);
        void BeginAlbumArtFileName(CpProxy.CallbackAsyncComplete aCallback);
        void EndAlbumArtFileName(uint aAsyncHandle, out string aaName);
        void SyncSetCurrentPreset(uint aaPreset);
        void BeginSetCurrentPreset(uint aaPreset, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetCurrentPreset(uint aAsyncHandle);
        void SyncCurrentPreset(out uint aaPreset);
        void BeginCurrentPreset(CpProxy.CallbackAsyncComplete aCallback);
        void EndCurrentPreset(uint aAsyncHandle, out uint aaPreset);
        void SyncPresetMetaData(uint aaPreset, out string aaMetaData);
        void BeginPresetMetaData(uint aaPreset, CpProxy.CallbackAsyncComplete aCallback);
        void EndPresetMetaData(uint aAsyncHandle, out string aaMetaData);
        void SyncLoadManifest(out uint aaTotalPresets);
        void BeginLoadManifest(CpProxy.CallbackAsyncComplete aCallback);
        void EndLoadManifest(uint aAsyncHandle, out uint aaTotalPresets);

        void SetPropertyCurrentPresetChanged(CpProxy.CallbackPropertyChanged aCurrentPresetChanged);
        void PropertyCurrentPreset(out uint aCurrentPreset);
        void SetPropertyPresetPrefixChanged(CpProxy.CallbackPropertyChanged aPresetPrefixChanged);
        void PropertyPresetPrefix(out string aPresetPrefix);
        void SetPropertyAlbumArtFileNameChanged(CpProxy.CallbackPropertyChanged aAlbumArtFileNameChanged);
        void PropertyAlbumArtFileName(out string aAlbumArtFileName);
    }

    public class CpProxyLinnCoUkJukebox1 : CpProxy, IDisposable, ICpProxyLinnCoUkJukebox1
    {
        [DllImport("CpLinnCoUkJukebox1")]
        static extern uint CpProxyLinnCoUkJukebox1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern void CpProxyLinnCoUkJukebox1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncSetPresetPrefix(uint aHandle, char* aaUri);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginSetPresetPrefix(uint aHandle, char* aaUri, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndSetPresetPrefix(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncPresetPrefix(uint aHandle, char** aaUri);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginPresetPrefix(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndPresetPrefix(uint aHandle, uint aAsync, char** aaUri);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncSetAlbumArtFileName(uint aHandle, char* aaName);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginSetAlbumArtFileName(uint aHandle, char* aaName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndSetAlbumArtFileName(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncAlbumArtFileName(uint aHandle, char** aaName);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginAlbumArtFileName(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndAlbumArtFileName(uint aHandle, uint aAsync, char** aaName);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncSetCurrentPreset(uint aHandle, uint aaPreset);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginSetCurrentPreset(uint aHandle, uint aaPreset, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndSetCurrentPreset(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncCurrentPreset(uint aHandle, uint* aaPreset);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginCurrentPreset(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndCurrentPreset(uint aHandle, uint aAsync, uint* aaPreset);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncPresetMetaData(uint aHandle, uint aaPreset, char** aaMetaData);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginPresetMetaData(uint aHandle, uint aaPreset, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndPresetMetaData(uint aHandle, uint aAsync, char** aaMetaData);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1SyncLoadManifest(uint aHandle, uint* aaTotalPresets);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1BeginLoadManifest(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe int CpProxyLinnCoUkJukebox1EndLoadManifest(uint aHandle, uint aAsync, uint* aaTotalPresets);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern void CpProxyLinnCoUkJukebox1SetPropertyCurrentPresetChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern void CpProxyLinnCoUkJukebox1SetPropertyPresetPrefixChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern void CpProxyLinnCoUkJukebox1SetPropertyAlbumArtFileNameChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1PropertyCurrentPreset(uint aHandle, uint* aCurrentPreset);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1PropertyPresetPrefix(uint aHandle, char** aPresetPrefix);
        [DllImport("CpLinnCoUkJukebox1")]
        static extern unsafe void CpProxyLinnCoUkJukebox1PropertyAlbumArtFileName(uint aHandle, char** aAlbumArtFileName);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iCurrentPresetChanged;
        private CallbackPropertyChanged iPresetPrefixChanged;
        private CallbackPropertyChanged iAlbumArtFileNameChanged;
        private Callback iCallbackCurrentPresetChanged;
        private Callback iCallbackPresetPrefixChanged;
        private Callback iCallbackAlbumArtFileNameChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkJukebox1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkJukebox1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUri"></param>
        public unsafe void SyncSetPresetPrefix(string aaUri)
        {
			char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
			{
				CpProxyLinnCoUkJukebox1SyncSetPresetPrefix(iHandle, aUri);
			}
			Marshal.FreeHGlobal((IntPtr)aUri);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetPresetPrefix().</remarks>
        /// <param name="aaUri"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetPresetPrefix(string aaUri, CallbackAsyncComplete aCallback)
        {
			char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginSetPresetPrefix(iHandle, aUri, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aUri);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetPresetPrefix(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkJukebox1EndSetPresetPrefix(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUri"></param>
        public unsafe void SyncPresetPrefix(out string aaUri)
        {
			char* aUri;
			{
				CpProxyLinnCoUkJukebox1SyncPresetPrefix(iHandle, &aUri);
			}
            aaUri = Marshal.PtrToStringAnsi((IntPtr)aUri);
            ZappFree(aUri);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPresetPrefix().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPresetPrefix(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginPresetPrefix(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaUri"></param>
        public unsafe void EndPresetPrefix(uint aAsyncHandle, out string aaUri)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaName"></param>
        public unsafe void SyncSetAlbumArtFileName(string aaName)
        {
			char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
			{
				CpProxyLinnCoUkJukebox1SyncSetAlbumArtFileName(iHandle, aName);
			}
			Marshal.FreeHGlobal((IntPtr)aName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetAlbumArtFileName().</remarks>
        /// <param name="aaName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetAlbumArtFileName(string aaName, CallbackAsyncComplete aCallback)
        {
			char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginSetAlbumArtFileName(iHandle, aName, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aName);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetAlbumArtFileName(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkJukebox1EndSetAlbumArtFileName(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaName"></param>
        public unsafe void SyncAlbumArtFileName(out string aaName)
        {
			char* aName;
			{
				CpProxyLinnCoUkJukebox1SyncAlbumArtFileName(iHandle, &aName);
			}
            aaName = Marshal.PtrToStringAnsi((IntPtr)aName);
            ZappFree(aName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndAlbumArtFileName().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginAlbumArtFileName(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginAlbumArtFileName(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaName"></param>
        public unsafe void EndAlbumArtFileName(uint aAsyncHandle, out string aaName)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPreset"></param>
        public unsafe void SyncSetCurrentPreset(uint aaPreset)
        {
			{
				CpProxyLinnCoUkJukebox1SyncSetCurrentPreset(iHandle, aaPreset);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetCurrentPreset().</remarks>
        /// <param name="aaPreset"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetCurrentPreset(uint aaPreset, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginSetCurrentPreset(iHandle, aaPreset, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetCurrentPreset(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkJukebox1EndSetCurrentPreset(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPreset"></param>
        public unsafe void SyncCurrentPreset(out uint aaPreset)
        {
			fixed (uint* aPreset = &aaPreset)
			{
				CpProxyLinnCoUkJukebox1SyncCurrentPreset(iHandle, aPreset);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCurrentPreset().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginCurrentPreset(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginCurrentPreset(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaPreset"></param>
        public unsafe void EndCurrentPreset(uint aAsyncHandle, out uint aaPreset)
        {
			fixed (uint* aPreset = &aaPreset)
			{
				if (0 != CpProxyLinnCoUkJukebox1EndCurrentPreset(iHandle, aAsyncHandle, aPreset))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPreset"></param>
        /// <param name="aaMetaData"></param>
        public unsafe void SyncPresetMetaData(uint aaPreset, out string aaMetaData)
        {
			char* aMetaData;
			{
				CpProxyLinnCoUkJukebox1SyncPresetMetaData(iHandle, aaPreset, &aMetaData);
			}
            aaMetaData = Marshal.PtrToStringAnsi((IntPtr)aMetaData);
            ZappFree(aMetaData);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPresetMetaData().</remarks>
        /// <param name="aaPreset"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPresetMetaData(uint aaPreset, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginPresetMetaData(iHandle, aaPreset, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMetaData"></param>
        public unsafe void EndPresetMetaData(uint aAsyncHandle, out string aaMetaData)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTotalPresets"></param>
        public unsafe void SyncLoadManifest(out uint aaTotalPresets)
        {
			fixed (uint* aTotalPresets = &aaTotalPresets)
			{
				CpProxyLinnCoUkJukebox1SyncLoadManifest(iHandle, aTotalPresets);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndLoadManifest().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginLoadManifest(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkJukebox1BeginLoadManifest(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaTotalPresets"></param>
        public unsafe void EndLoadManifest(uint aAsyncHandle, out uint aaTotalPresets)
        {
			fixed (uint* aTotalPresets = &aaTotalPresets)
			{
				if (0 != CpProxyLinnCoUkJukebox1EndLoadManifest(iHandle, aAsyncHandle, aTotalPresets))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Set a delegate to be run when the CurrentPreset state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkJukebox1 instance will not overlap.</remarks>
        /// <param name="aCurrentPresetChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the PresetPrefix state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkJukebox1 instance will not overlap.</remarks>
        /// <param name="aPresetPrefixChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the AlbumArtFileName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkJukebox1 instance will not overlap.</remarks>
        /// <param name="aAlbumArtFileNameChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Query the value of the CurrentPreset property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aCurrentPreset">Will be set to the value of the property</param>
        public unsafe void PropertyCurrentPreset(out uint aCurrentPreset)
        {
			fixed (uint* currentPreset = &aCurrentPreset)
			{
	            CpProxyLinnCoUkJukebox1PropertyCurrentPreset(iHandle, currentPreset);
			}
        }

        /// <summary>
        /// Query the value of the PresetPrefix property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aPresetPrefix">Will be set to the value of the property</param>
        public unsafe void PropertyPresetPrefix(out string aPresetPrefix)
        {
			char* ptr;
            CpProxyLinnCoUkJukebox1PropertyPresetPrefix(iHandle, &ptr);
            aPresetPrefix = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the AlbumArtFileName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aAlbumArtFileName">Will be set to the value of the property</param>
        public unsafe void PropertyAlbumArtFileName(out string aAlbumArtFileName)
        {
			char* ptr;
            CpProxyLinnCoUkJukebox1PropertyAlbumArtFileName(iHandle, &ptr);
            aAlbumArtFileName = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                CpProxyLinnCoUkJukebox1Destroy(iHandle);
                iHandle = 0;
            }
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

