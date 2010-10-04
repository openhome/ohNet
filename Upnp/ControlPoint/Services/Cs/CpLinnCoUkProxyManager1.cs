using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkProxyManager1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern uint CpProxyLinnCoUkProxyManager1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncKontrolProductConnected(uint aHandle, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginKontrolProductConnected(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndKontrolProductConnected(uint aHandle, uint aAsync, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductConnected(uint aHandle, char* aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductConnected(uint aHandle, char* aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetKontrolProductConnected(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncKontrolProductComPort(uint aHandle, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginKontrolProductComPort(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndKontrolProductComPort(uint aHandle, uint aAsync, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductComPort(uint aHandle, uint aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductComPort(uint aHandle, uint aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetKontrolProductComPort(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncDiscPlayerConnected(uint aHandle, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginDiscPlayerConnected(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndDiscPlayerConnected(uint aHandle, uint aAsync, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerConnected(uint aHandle, char* aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerConnected(uint aHandle, char* aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetDiscPlayerConnected(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncDiscPlayerComPort(uint aHandle, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginDiscPlayerComPort(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndDiscPlayerComPort(uint aHandle, uint aAsync, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerComPort(uint aHandle, uint aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerComPort(uint aHandle, uint aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetDiscPlayerComPort(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncTestKontrolProductConnection(uint aHandle, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginTestKontrolProductConnection(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndTestKontrolProductConnection(uint aHandle, uint aAsync, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncTestDiscPlayerConnection(uint aHandle, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginTestDiscPlayerConnection(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndTestDiscPlayerConnection(uint aHandle, uint aAsync, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductConnectedChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductComPortChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerConnectedChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerComPortChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyKontrolProductConnected(uint aHandle, char** aKontrolProductConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyKontrolProductComPort(uint aHandle, uint* aKontrolProductComPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerConnected(uint aHandle, char** aDiscPlayerConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerComPort(uint aHandle, uint* aDiscPlayerComPort);
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

        public unsafe void EndKontrolProductConnected(uint aAsyncHandle, out string aaConnected)
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

        public unsafe void EndSetKontrolProductConnected(uint aAsyncHandle)
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

        public unsafe void EndKontrolProductComPort(uint aAsyncHandle, out uint aaPort)
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

        public unsafe void EndSetKontrolProductComPort(uint aAsyncHandle)
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

        public unsafe void EndDiscPlayerConnected(uint aAsyncHandle, out string aaConnected)
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

        public unsafe void EndSetDiscPlayerConnected(uint aAsyncHandle)
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

        public unsafe void EndDiscPlayerComPort(uint aAsyncHandle, out uint aaPort)
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

        public unsafe void EndSetDiscPlayerComPort(uint aAsyncHandle)
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

        public unsafe void EndTestKontrolProductConnection(uint aAsyncHandle, out bool aaResult)
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

        public unsafe void EndTestDiscPlayerConnection(uint aAsyncHandle, out bool aaResult)
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

