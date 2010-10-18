using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkDelay1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkDelay1")]
        static extern IntPtr CpProxyLinnCoUkDelay1Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkDelay1")]
        static extern void CpProxyLinnCoUkDelay1Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncPresetXml(IntPtr aHandle, char** aaPresetXml);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginPresetXml(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndPresetXml(IntPtr aHandle, IntPtr aAsync, char** aaPresetXml);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncPresetIndex(IntPtr aHandle, uint* aaIndex);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginPresetIndex(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndPresetIndex(IntPtr aHandle, IntPtr aAsync, uint* aaIndex);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncSetPresetIndex(IntPtr aHandle, uint aaIndex);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginSetPresetIndex(IntPtr aHandle, uint aaIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndSetPresetIndex(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncSetPresetDelay(IntPtr aHandle, uint aaIndex, uint aaDelay);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginSetPresetDelay(IntPtr aHandle, uint aaIndex, uint aaDelay, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndSetPresetDelay(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncSetPresetVisible(IntPtr aHandle, uint aaIndex, uint aaVisible);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginSetPresetVisible(IntPtr aHandle, uint aaIndex, uint aaVisible, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndSetPresetVisible(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncSetPresetName(IntPtr aHandle, uint aaIndex, char* aaName);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginSetPresetName(IntPtr aHandle, uint aaIndex, char* aaName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndSetPresetName(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncDelayMinimum(IntPtr aHandle, uint* aaDelay);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginDelayMinimum(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndDelayMinimum(IntPtr aHandle, IntPtr aAsync, uint* aaDelay);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncDelayMaximum(IntPtr aHandle, uint* aaDelay);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginDelayMaximum(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndDelayMaximum(IntPtr aHandle, IntPtr aAsync, uint* aaDelay);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncPresetCount(IntPtr aHandle, uint* aaCount);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginPresetCount(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndPresetCount(IntPtr aHandle, IntPtr aAsync, uint* aaCount);
        [DllImport("CpLinnCoUkDelay1")]
        static extern void CpProxyLinnCoUkDelay1SetPropertyPresetXmlChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern void CpProxyLinnCoUkDelay1SetPropertyPresetIndexChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1PropertyPresetXml(IntPtr aHandle, char** aPresetXml);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1PropertyPresetIndex(IntPtr aHandle, uint* aPresetIndex);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iPresetXmlChanged;
        private CallbackPropertyChanged iPresetIndexChanged;
        private Callback iCallbackPresetXmlChanged;
        private Callback iCallbackPresetIndexChanged;

        public CpProxyLinnCoUkDelay1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkDelay1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncPresetXml(out string aaPresetXml)
        {
			char* aPresetXml;
			{
				CpProxyLinnCoUkDelay1SyncPresetXml(iHandle, &aPresetXml);
			}
            aaPresetXml = Marshal.PtrToStringAnsi((IntPtr)aPresetXml);
            ZappFree(aPresetXml);
        }

        public unsafe void BeginPresetXml(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginPresetXml(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndPresetXml(IntPtr aAsyncHandle, out string aaPresetXml)
        {
			char* aPresetXml;
			{
				if (0 != CpProxyLinnCoUkDelay1EndPresetXml(iHandle, aAsyncHandle, &aPresetXml))
				{
					throw(new ProxyError());
				}
			}
            aaPresetXml = Marshal.PtrToStringAnsi((IntPtr)aPresetXml);
            ZappFree(aPresetXml);
        }

        public unsafe void SyncPresetIndex(out uint aaIndex)
        {
			fixed (uint* aIndex = &aaIndex)
			{
				CpProxyLinnCoUkDelay1SyncPresetIndex(iHandle, aIndex);
			}
        }

        public unsafe void BeginPresetIndex(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginPresetIndex(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndPresetIndex(IntPtr aAsyncHandle, out uint aaIndex)
        {
			fixed (uint* aIndex = &aaIndex)
			{
				if (0 != CpProxyLinnCoUkDelay1EndPresetIndex(iHandle, aAsyncHandle, aIndex))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetPresetIndex(uint aaIndex)
        {
			{
				CpProxyLinnCoUkDelay1SyncSetPresetIndex(iHandle, aaIndex);
			}
        }

        public unsafe void BeginSetPresetIndex(uint aaIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginSetPresetIndex(iHandle, aaIndex, iActionComplete, ptr);
        }

        public unsafe void EndSetPresetIndex(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDelay1EndSetPresetIndex(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetPresetDelay(uint aaIndex, uint aaDelay)
        {
			{
				CpProxyLinnCoUkDelay1SyncSetPresetDelay(iHandle, aaIndex, aaDelay);
			}
        }

        public unsafe void BeginSetPresetDelay(uint aaIndex, uint aaDelay, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginSetPresetDelay(iHandle, aaIndex, aaDelay, iActionComplete, ptr);
        }

        public unsafe void EndSetPresetDelay(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDelay1EndSetPresetDelay(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetPresetVisible(uint aaIndex, bool aaVisible)
        {
			uint aVisible = (aaVisible? 1u : 0u);
			{
				CpProxyLinnCoUkDelay1SyncSetPresetVisible(iHandle, aaIndex, aVisible);
			}
        }

        public unsafe void BeginSetPresetVisible(uint aaIndex, bool aaVisible, CallbackAsyncComplete aCallback)
        {
			uint aVisible = (aaVisible? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginSetPresetVisible(iHandle, aaIndex, aVisible, iActionComplete, ptr);
        }

        public unsafe void EndSetPresetVisible(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDelay1EndSetPresetVisible(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetPresetName(uint aaIndex, string aaName)
        {
			char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
			{
				CpProxyLinnCoUkDelay1SyncSetPresetName(iHandle, aaIndex, aName);
			}
			Marshal.FreeHGlobal((IntPtr)aName);
        }

        public unsafe void BeginSetPresetName(uint aaIndex, string aaName, CallbackAsyncComplete aCallback)
        {
			char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginSetPresetName(iHandle, aaIndex, aName, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aName);
        }

        public unsafe void EndSetPresetName(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDelay1EndSetPresetName(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDelayMinimum(out uint aaDelay)
        {
			fixed (uint* aDelay = &aaDelay)
			{
				CpProxyLinnCoUkDelay1SyncDelayMinimum(iHandle, aDelay);
			}
        }

        public unsafe void BeginDelayMinimum(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginDelayMinimum(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDelayMinimum(IntPtr aAsyncHandle, out uint aaDelay)
        {
			fixed (uint* aDelay = &aaDelay)
			{
				if (0 != CpProxyLinnCoUkDelay1EndDelayMinimum(iHandle, aAsyncHandle, aDelay))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDelayMaximum(out uint aaDelay)
        {
			fixed (uint* aDelay = &aaDelay)
			{
				CpProxyLinnCoUkDelay1SyncDelayMaximum(iHandle, aDelay);
			}
        }

        public unsafe void BeginDelayMaximum(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginDelayMaximum(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDelayMaximum(IntPtr aAsyncHandle, out uint aaDelay)
        {
			fixed (uint* aDelay = &aaDelay)
			{
				if (0 != CpProxyLinnCoUkDelay1EndDelayMaximum(iHandle, aAsyncHandle, aDelay))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncPresetCount(out uint aaCount)
        {
			fixed (uint* aCount = &aaCount)
			{
				CpProxyLinnCoUkDelay1SyncPresetCount(iHandle, aCount);
			}
        }

        public unsafe void BeginPresetCount(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginPresetCount(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndPresetCount(IntPtr aAsyncHandle, out uint aaCount)
        {
			fixed (uint* aCount = &aaCount)
			{
				if (0 != CpProxyLinnCoUkDelay1EndPresetCount(iHandle, aAsyncHandle, aCount))
				{
					throw(new ProxyError());
				}
			}
        }

        public void SetPropertyPresetXmlChanged(CallbackPropertyChanged aPresetXmlChanged)
        {
            iPresetXmlChanged = aPresetXmlChanged;
            iCallbackPresetXmlChanged = new Callback(PropertyPresetXmlChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDelay1SetPropertyPresetXmlChanged(iHandle, iCallbackPresetXmlChanged, ptr);
        }

        private void PropertyPresetXmlChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDelay1 self = (CpProxyLinnCoUkDelay1)gch.Target;
            self.iPresetXmlChanged();
        }

        public void SetPropertyPresetIndexChanged(CallbackPropertyChanged aPresetIndexChanged)
        {
            iPresetIndexChanged = aPresetIndexChanged;
            iCallbackPresetIndexChanged = new Callback(PropertyPresetIndexChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDelay1SetPropertyPresetIndexChanged(iHandle, iCallbackPresetIndexChanged, ptr);
        }

        private void PropertyPresetIndexChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDelay1 self = (CpProxyLinnCoUkDelay1)gch.Target;
            self.iPresetIndexChanged();
        }

        public unsafe void PropertyPresetXml(out string aPresetXml)
        {
			char* ptr;
            CpProxyLinnCoUkDelay1PropertyPresetXml(iHandle, &ptr);
            aPresetXml = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyPresetIndex(out uint aPresetIndex)
        {
			fixed (uint* presetIndex = &aPresetIndex)
			{
	            CpProxyLinnCoUkDelay1PropertyPresetIndex(iHandle, presetIndex);
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkDelay1()
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
            CpProxyLinnCoUkDelay1Destroy(handle);
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

