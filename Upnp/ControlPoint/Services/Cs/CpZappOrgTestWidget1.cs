using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public interface ICpProxyZappOrgTestWidget1
    {
        void SyncSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue);
        void BeginSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetReadWriteRegister(uint aAsyncHandle);

        void SetPropertyReadWriteRegister0Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister0Changed);
        void PropertyReadWriteRegister0(out uint aReadWriteRegister0);
        void SetPropertyReadWriteRegister1Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister1Changed);
        void PropertyReadWriteRegister1(out uint aReadWriteRegister1);
        void SetPropertyReadWriteRegister2Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister2Changed);
        void PropertyReadWriteRegister2(out uint aReadWriteRegister2);
        void SetPropertyReadWriteRegister3Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister3Changed);
        void PropertyReadWriteRegister3(out uint aReadWriteRegister3);
        void SetPropertyReadOnlyRegister4Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister4Changed);
        void PropertyReadOnlyRegister4(out uint aReadOnlyRegister4);
        void SetPropertyReadOnlyRegister5Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister5Changed);
        void PropertyReadOnlyRegister5(out uint aReadOnlyRegister5);
        void SetPropertyReadOnlyRegister6Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister6Changed);
        void PropertyReadOnlyRegister6(out uint aReadOnlyRegister6);
        void SetPropertyReadOnlyRegister7Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister7Changed);
        void PropertyReadOnlyRegister7(out uint aReadOnlyRegister7);
    }

    public class CpProxyZappOrgTestWidget1 : CpProxy, IDisposable, ICpProxyZappOrgTestWidget1
    {
        [DllImport("CpZappOrgTestWidget1")]
        static extern uint CpProxyZappOrgTestWidget1Create(uint aDeviceHandle);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1Destroy(uint aHandle);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1SyncSetReadWriteRegister(uint aHandle, uint aRegisterIndex, uint aRegisterValue);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1BeginSetReadWriteRegister(uint aHandle, uint aRegisterIndex, uint aRegisterValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe int CpProxyZappOrgTestWidget1EndSetReadWriteRegister(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister0Changed(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister1Changed(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister2Changed(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister3Changed(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister4Changed(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister5Changed(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister6Changed(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister7Changed(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadWriteRegister0(uint aHandle, uint* aReadWriteRegister0);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadWriteRegister1(uint aHandle, uint* aReadWriteRegister1);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadWriteRegister2(uint aHandle, uint* aReadWriteRegister2);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadWriteRegister3(uint aHandle, uint* aReadWriteRegister3);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister4(uint aHandle, uint* aReadOnlyRegister4);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister5(uint aHandle, uint* aReadOnlyRegister5);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister6(uint aHandle, uint* aReadOnlyRegister6);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister7(uint aHandle, uint* aReadOnlyRegister7);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iReadWriteRegister0Changed;
        private CallbackPropertyChanged iReadWriteRegister1Changed;
        private CallbackPropertyChanged iReadWriteRegister2Changed;
        private CallbackPropertyChanged iReadWriteRegister3Changed;
        private CallbackPropertyChanged iReadOnlyRegister4Changed;
        private CallbackPropertyChanged iReadOnlyRegister5Changed;
        private CallbackPropertyChanged iReadOnlyRegister6Changed;
        private CallbackPropertyChanged iReadOnlyRegister7Changed;
        private Callback iCallbackReadWriteRegister0Changed;
        private Callback iCallbackReadWriteRegister1Changed;
        private Callback iCallbackReadWriteRegister2Changed;
        private Callback iCallbackReadWriteRegister3Changed;
        private Callback iCallbackReadOnlyRegister4Changed;
        private Callback iCallbackReadOnlyRegister5Changed;
        private Callback iCallbackReadOnlyRegister6Changed;
        private Callback iCallbackReadOnlyRegister7Changed;

        public CpProxyZappOrgTestWidget1(CpDevice aDevice)
        {
            iHandle = CpProxyZappOrgTestWidget1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue)
        {
			{
				CpProxyZappOrgTestWidget1SyncSetReadWriteRegister(iHandle, aRegisterIndex, aRegisterValue);
			}
        }

        public unsafe void BeginSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestWidget1BeginSetReadWriteRegister(iHandle, aRegisterIndex, aRegisterValue, iActionComplete, ptr);
        }

        public unsafe void EndSetReadWriteRegister(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestWidget1EndSetReadWriteRegister(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public void SetPropertyReadWriteRegister0Changed(CallbackPropertyChanged aReadWriteRegister0Changed)
        {
            iReadWriteRegister0Changed = aReadWriteRegister0Changed;
            iCallbackReadWriteRegister0Changed = new Callback(PropertyReadWriteRegister0Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister0Changed(iHandle, iCallbackReadWriteRegister0Changed, ptr);
        }

        private void PropertyReadWriteRegister0Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadWriteRegister0Changed();
        }

        public void SetPropertyReadWriteRegister1Changed(CallbackPropertyChanged aReadWriteRegister1Changed)
        {
            iReadWriteRegister1Changed = aReadWriteRegister1Changed;
            iCallbackReadWriteRegister1Changed = new Callback(PropertyReadWriteRegister1Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister1Changed(iHandle, iCallbackReadWriteRegister1Changed, ptr);
        }

        private void PropertyReadWriteRegister1Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadWriteRegister1Changed();
        }

        public void SetPropertyReadWriteRegister2Changed(CallbackPropertyChanged aReadWriteRegister2Changed)
        {
            iReadWriteRegister2Changed = aReadWriteRegister2Changed;
            iCallbackReadWriteRegister2Changed = new Callback(PropertyReadWriteRegister2Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister2Changed(iHandle, iCallbackReadWriteRegister2Changed, ptr);
        }

        private void PropertyReadWriteRegister2Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadWriteRegister2Changed();
        }

        public void SetPropertyReadWriteRegister3Changed(CallbackPropertyChanged aReadWriteRegister3Changed)
        {
            iReadWriteRegister3Changed = aReadWriteRegister3Changed;
            iCallbackReadWriteRegister3Changed = new Callback(PropertyReadWriteRegister3Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister3Changed(iHandle, iCallbackReadWriteRegister3Changed, ptr);
        }

        private void PropertyReadWriteRegister3Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadWriteRegister3Changed();
        }

        public void SetPropertyReadOnlyRegister4Changed(CallbackPropertyChanged aReadOnlyRegister4Changed)
        {
            iReadOnlyRegister4Changed = aReadOnlyRegister4Changed;
            iCallbackReadOnlyRegister4Changed = new Callback(PropertyReadOnlyRegister4Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister4Changed(iHandle, iCallbackReadOnlyRegister4Changed, ptr);
        }

        private void PropertyReadOnlyRegister4Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadOnlyRegister4Changed();
        }

        public void SetPropertyReadOnlyRegister5Changed(CallbackPropertyChanged aReadOnlyRegister5Changed)
        {
            iReadOnlyRegister5Changed = aReadOnlyRegister5Changed;
            iCallbackReadOnlyRegister5Changed = new Callback(PropertyReadOnlyRegister5Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister5Changed(iHandle, iCallbackReadOnlyRegister5Changed, ptr);
        }

        private void PropertyReadOnlyRegister5Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadOnlyRegister5Changed();
        }

        public void SetPropertyReadOnlyRegister6Changed(CallbackPropertyChanged aReadOnlyRegister6Changed)
        {
            iReadOnlyRegister6Changed = aReadOnlyRegister6Changed;
            iCallbackReadOnlyRegister6Changed = new Callback(PropertyReadOnlyRegister6Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister6Changed(iHandle, iCallbackReadOnlyRegister6Changed, ptr);
        }

        private void PropertyReadOnlyRegister6Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadOnlyRegister6Changed();
        }

        public void SetPropertyReadOnlyRegister7Changed(CallbackPropertyChanged aReadOnlyRegister7Changed)
        {
            iReadOnlyRegister7Changed = aReadOnlyRegister7Changed;
            iCallbackReadOnlyRegister7Changed = new Callback(PropertyReadOnlyRegister7Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister7Changed(iHandle, iCallbackReadOnlyRegister7Changed, ptr);
        }

        private void PropertyReadOnlyRegister7Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadOnlyRegister7Changed();
        }

        public unsafe void PropertyReadWriteRegister0(out uint aReadWriteRegister0)
        {
			fixed (uint* readWriteRegister0 = &aReadWriteRegister0)
			{
	            CpProxyZappOrgTestWidget1PropertyReadWriteRegister0(iHandle, readWriteRegister0);
			}
        }

        public unsafe void PropertyReadWriteRegister1(out uint aReadWriteRegister1)
        {
			fixed (uint* readWriteRegister1 = &aReadWriteRegister1)
			{
	            CpProxyZappOrgTestWidget1PropertyReadWriteRegister1(iHandle, readWriteRegister1);
			}
        }

        public unsafe void PropertyReadWriteRegister2(out uint aReadWriteRegister2)
        {
			fixed (uint* readWriteRegister2 = &aReadWriteRegister2)
			{
	            CpProxyZappOrgTestWidget1PropertyReadWriteRegister2(iHandle, readWriteRegister2);
			}
        }

        public unsafe void PropertyReadWriteRegister3(out uint aReadWriteRegister3)
        {
			fixed (uint* readWriteRegister3 = &aReadWriteRegister3)
			{
	            CpProxyZappOrgTestWidget1PropertyReadWriteRegister3(iHandle, readWriteRegister3);
			}
        }

        public unsafe void PropertyReadOnlyRegister4(out uint aReadOnlyRegister4)
        {
			fixed (uint* readOnlyRegister4 = &aReadOnlyRegister4)
			{
	            CpProxyZappOrgTestWidget1PropertyReadOnlyRegister4(iHandle, readOnlyRegister4);
			}
        }

        public unsafe void PropertyReadOnlyRegister5(out uint aReadOnlyRegister5)
        {
			fixed (uint* readOnlyRegister5 = &aReadOnlyRegister5)
			{
	            CpProxyZappOrgTestWidget1PropertyReadOnlyRegister5(iHandle, readOnlyRegister5);
			}
        }

        public unsafe void PropertyReadOnlyRegister6(out uint aReadOnlyRegister6)
        {
			fixed (uint* readOnlyRegister6 = &aReadOnlyRegister6)
			{
	            CpProxyZappOrgTestWidget1PropertyReadOnlyRegister6(iHandle, readOnlyRegister6);
			}
        }

        public unsafe void PropertyReadOnlyRegister7(out uint aReadOnlyRegister7)
        {
			fixed (uint* readOnlyRegister7 = &aReadOnlyRegister7)
			{
	            CpProxyZappOrgTestWidget1PropertyReadOnlyRegister7(iHandle, readOnlyRegister7);
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyZappOrgTestWidget1()
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
            CpProxyZappOrgTestWidget1Destroy(handle);
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

