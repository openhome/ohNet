using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkProxyManager1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern IntPtr CpProxyLinnCoUkProxyManager1Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncKontrolProductConnected(IntPtr aHandle, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginKontrolProductConnected(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndKontrolProductConnected(IntPtr aHandle, IntPtr aAsync, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductConnected(IntPtr aHandle, char* aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductConnected(IntPtr aHandle, char* aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetKontrolProductConnected(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncKontrolProductComPort(IntPtr aHandle, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginKontrolProductComPort(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndKontrolProductComPort(IntPtr aHandle, IntPtr aAsync, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductComPort(IntPtr aHandle, uint aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductComPort(IntPtr aHandle, uint aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetKontrolProductComPort(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncDiscPlayerConnected(IntPtr aHandle, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginDiscPlayerConnected(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndDiscPlayerConnected(IntPtr aHandle, IntPtr aAsync, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerConnected(IntPtr aHandle, char* aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerConnected(IntPtr aHandle, char* aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetDiscPlayerConnected(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncDiscPlayerComPort(IntPtr aHandle, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginDiscPlayerComPort(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndDiscPlayerComPort(IntPtr aHandle, IntPtr aAsync, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerComPort(IntPtr aHandle, uint aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerComPort(IntPtr aHandle, uint aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetDiscPlayerComPort(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncTestKontrolProductConnection(IntPtr aHandle, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginTestKontrolProductConnection(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndTestKontrolProductConnection(IntPtr aHandle, IntPtr aAsync, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncTestDiscPlayerConnection(IntPtr aHandle, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginTestDiscPlayerConnection(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndTestDiscPlayerConnection(IntPtr aHandle, IntPtr aAsync, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductConnectedChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductComPortChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerConnectedChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerComPortChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyKontrolProductConnected(IntPtr aHandle, char** aKontrolProductConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyKontrolProductComPort(IntPtr aHandle, uint* aKontrolProductComPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerConnected(IntPtr aHandle, char** aDiscPlayerConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerComPort(IntPtr aHandle, uint* aDiscPlayerComPort);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iKontrolProductConnectedChanged;
        private CallbackPropertyChanged iKontrolProductComPortChanged;
        private CallbackPropertyChanged iDiscPlayerConnectedChanged;
        private CallbackPropertyChanged iDiscPlayerComPortChanged;
        private Callback iCallbackKontrolProductConnectedChanged;
        private Callback iCallbackKontrolProductComPortChanged;
        private Callback iCallbackDiscPlayerConnectedChanged;
        private Callback iCallbackDiscPlayerComPortChanged;

        public CpProxyLinnCoUkProxyManager1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkProxyManager1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncKontrolProductConnected(out string aaConnected)
        {
			char* aConnected;
			{
				CpProxyLinnCoUkProxyManager1SyncKontrolProductConnected(iHandle, &aConnected);
			}
            aaConnected = Marshal.PtrToStringAnsi((IntPtr)aConnected);
            ZappFree(aConnected);
        }

        public unsafe void BeginKontrolProductConnected(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginKontrolProductConnected(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndKontrolProductConnected(IntPtr aAsyncHandle, out string aaConnected)
        {
			char* aConnected;
			{
				if (0 != CpProxyLinnCoUkProxyManager1EndKontrolProductConnected(iHandle, aAsyncHandle, &aConnected))
				{
					throw(new ProxyError());
				}
			}
            aaConnected = Marshal.PtrToStringAnsi((IntPtr)aConnected);
            ZappFree(aConnected);
        }

        public unsafe void SyncSetKontrolProductConnected(string aaConnected)
        {
			char* aConnected = (char*)Marshal.StringToHGlobalAnsi(aaConnected);
			{
				CpProxyLinnCoUkProxyManager1SyncSetKontrolProductConnected(iHandle, aConnected);
			}
			Marshal.FreeHGlobal((IntPtr)aConnected);
        }

        public unsafe void BeginSetKontrolProductConnected(string aaConnected, CallbackAsyncComplete aCallback)
        {
			char* aConnected = (char*)Marshal.StringToHGlobalAnsi(aaConnected);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginSetKontrolProductConnected(iHandle, aConnected, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aConnected);
        }

        public unsafe void EndSetKontrolProductConnected(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProxyManager1EndSetKontrolProductConnected(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncKontrolProductComPort(out uint aaPort)
        {
			fixed (uint* aPort = &aaPort)
			{
				CpProxyLinnCoUkProxyManager1SyncKontrolProductComPort(iHandle, aPort);
			}
        }

        public unsafe void BeginKontrolProductComPort(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginKontrolProductComPort(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndKontrolProductComPort(IntPtr aAsyncHandle, out uint aaPort)
        {
			fixed (uint* aPort = &aaPort)
			{
				if (0 != CpProxyLinnCoUkProxyManager1EndKontrolProductComPort(iHandle, aAsyncHandle, aPort))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetKontrolProductComPort(uint aaConnected)
        {
			{
				CpProxyLinnCoUkProxyManager1SyncSetKontrolProductComPort(iHandle, aaConnected);
			}
        }

        public unsafe void BeginSetKontrolProductComPort(uint aaConnected, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginSetKontrolProductComPort(iHandle, aaConnected, iActionComplete, ptr);
        }

        public unsafe void EndSetKontrolProductComPort(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProxyManager1EndSetKontrolProductComPort(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDiscPlayerConnected(out string aaConnected)
        {
			char* aConnected;
			{
				CpProxyLinnCoUkProxyManager1SyncDiscPlayerConnected(iHandle, &aConnected);
			}
            aaConnected = Marshal.PtrToStringAnsi((IntPtr)aConnected);
            ZappFree(aConnected);
        }

        public unsafe void BeginDiscPlayerConnected(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginDiscPlayerConnected(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDiscPlayerConnected(IntPtr aAsyncHandle, out string aaConnected)
        {
			char* aConnected;
			{
				if (0 != CpProxyLinnCoUkProxyManager1EndDiscPlayerConnected(iHandle, aAsyncHandle, &aConnected))
				{
					throw(new ProxyError());
				}
			}
            aaConnected = Marshal.PtrToStringAnsi((IntPtr)aConnected);
            ZappFree(aConnected);
        }

        public unsafe void SyncSetDiscPlayerConnected(string aaConnected)
        {
			char* aConnected = (char*)Marshal.StringToHGlobalAnsi(aaConnected);
			{
				CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerConnected(iHandle, aConnected);
			}
			Marshal.FreeHGlobal((IntPtr)aConnected);
        }

        public unsafe void BeginSetDiscPlayerConnected(string aaConnected, CallbackAsyncComplete aCallback)
        {
			char* aConnected = (char*)Marshal.StringToHGlobalAnsi(aaConnected);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerConnected(iHandle, aConnected, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aConnected);
        }

        public unsafe void EndSetDiscPlayerConnected(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProxyManager1EndSetDiscPlayerConnected(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDiscPlayerComPort(out uint aaPort)
        {
			fixed (uint* aPort = &aaPort)
			{
				CpProxyLinnCoUkProxyManager1SyncDiscPlayerComPort(iHandle, aPort);
			}
        }

        public unsafe void BeginDiscPlayerComPort(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginDiscPlayerComPort(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDiscPlayerComPort(IntPtr aAsyncHandle, out uint aaPort)
        {
			fixed (uint* aPort = &aaPort)
			{
				if (0 != CpProxyLinnCoUkProxyManager1EndDiscPlayerComPort(iHandle, aAsyncHandle, aPort))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetDiscPlayerComPort(uint aaConnected)
        {
			{
				CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerComPort(iHandle, aaConnected);
			}
        }

        public unsafe void BeginSetDiscPlayerComPort(uint aaConnected, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerComPort(iHandle, aaConnected, iActionComplete, ptr);
        }

        public unsafe void EndSetDiscPlayerComPort(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProxyManager1EndSetDiscPlayerComPort(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncTestKontrolProductConnection(out bool aaResult)
        {
			uint aResult;
			{
				CpProxyLinnCoUkProxyManager1SyncTestKontrolProductConnection(iHandle, &aResult);
			}
			aaResult = (aResult != 0);
        }

        public unsafe void BeginTestKontrolProductConnection(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginTestKontrolProductConnection(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndTestKontrolProductConnection(IntPtr aAsyncHandle, out bool aaResult)
        {
			uint aResult;
			{
				if (0 != CpProxyLinnCoUkProxyManager1EndTestKontrolProductConnection(iHandle, aAsyncHandle, &aResult))
				{
					throw(new ProxyError());
				}
			}
			aaResult = (aResult != 0);
        }

        public unsafe void SyncTestDiscPlayerConnection(out bool aaResult)
        {
			uint aResult;
			{
				CpProxyLinnCoUkProxyManager1SyncTestDiscPlayerConnection(iHandle, &aResult);
			}
			aaResult = (aResult != 0);
        }

        public unsafe void BeginTestDiscPlayerConnection(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginTestDiscPlayerConnection(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndTestDiscPlayerConnection(IntPtr aAsyncHandle, out bool aaResult)
        {
			uint aResult;
			{
				if (0 != CpProxyLinnCoUkProxyManager1EndTestDiscPlayerConnection(iHandle, aAsyncHandle, &aResult))
				{
					throw(new ProxyError());
				}
			}
			aaResult = (aResult != 0);
        }

        public void SetPropertyKontrolProductConnectedChanged(CallbackPropertyChanged aKontrolProductConnectedChanged)
        {
            iKontrolProductConnectedChanged = aKontrolProductConnectedChanged;
            iCallbackKontrolProductConnectedChanged = new Callback(PropertyKontrolProductConnectedChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductConnectedChanged(iHandle, iCallbackKontrolProductConnectedChanged, ptr);
        }

        private void PropertyKontrolProductConnectedChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProxyManager1 self = (CpProxyLinnCoUkProxyManager1)gch.Target;
            self.iKontrolProductConnectedChanged();
        }

        public void SetPropertyKontrolProductComPortChanged(CallbackPropertyChanged aKontrolProductComPortChanged)
        {
            iKontrolProductComPortChanged = aKontrolProductComPortChanged;
            iCallbackKontrolProductComPortChanged = new Callback(PropertyKontrolProductComPortChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductComPortChanged(iHandle, iCallbackKontrolProductComPortChanged, ptr);
        }

        private void PropertyKontrolProductComPortChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProxyManager1 self = (CpProxyLinnCoUkProxyManager1)gch.Target;
            self.iKontrolProductComPortChanged();
        }

        public void SetPropertyDiscPlayerConnectedChanged(CallbackPropertyChanged aDiscPlayerConnectedChanged)
        {
            iDiscPlayerConnectedChanged = aDiscPlayerConnectedChanged;
            iCallbackDiscPlayerConnectedChanged = new Callback(PropertyDiscPlayerConnectedChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerConnectedChanged(iHandle, iCallbackDiscPlayerConnectedChanged, ptr);
        }

        private void PropertyDiscPlayerConnectedChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProxyManager1 self = (CpProxyLinnCoUkProxyManager1)gch.Target;
            self.iDiscPlayerConnectedChanged();
        }

        public void SetPropertyDiscPlayerComPortChanged(CallbackPropertyChanged aDiscPlayerComPortChanged)
        {
            iDiscPlayerComPortChanged = aDiscPlayerComPortChanged;
            iCallbackDiscPlayerComPortChanged = new Callback(PropertyDiscPlayerComPortChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerComPortChanged(iHandle, iCallbackDiscPlayerComPortChanged, ptr);
        }

        private void PropertyDiscPlayerComPortChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProxyManager1 self = (CpProxyLinnCoUkProxyManager1)gch.Target;
            self.iDiscPlayerComPortChanged();
        }

        public unsafe void PropertyKontrolProductConnected(out string aKontrolProductConnected)
        {
			char* ptr;
            CpProxyLinnCoUkProxyManager1PropertyKontrolProductConnected(iHandle, &ptr);
            aKontrolProductConnected = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyKontrolProductComPort(out uint aKontrolProductComPort)
        {
			fixed (uint* kontrolProductComPort = &aKontrolProductComPort)
			{
	            CpProxyLinnCoUkProxyManager1PropertyKontrolProductComPort(iHandle, kontrolProductComPort);
			}
        }

        public unsafe void PropertyDiscPlayerConnected(out string aDiscPlayerConnected)
        {
			char* ptr;
            CpProxyLinnCoUkProxyManager1PropertyDiscPlayerConnected(iHandle, &ptr);
            aDiscPlayerConnected = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyDiscPlayerComPort(out uint aDiscPlayerComPort)
        {
			fixed (uint* discPlayerComPort = &aDiscPlayerComPort)
			{
	            CpProxyLinnCoUkProxyManager1PropertyDiscPlayerComPort(iHandle, discPlayerComPort);
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkProxyManager1()
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
            CpProxyLinnCoUkProxyManager1Destroy(handle);
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

