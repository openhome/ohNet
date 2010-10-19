using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyZappOrgTestDimmableLight1 : CpProxy, IDisposable
    {
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern uint CpProxyZappOrgTestDimmableLight1Create(uint aDeviceHandle);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern void CpProxyZappOrgTestDimmableLight1Destroy(uint aHandle);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe void CpProxyZappOrgTestDimmableLight1SyncGetLevel(uint aHandle, uint* aLevel);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe void CpProxyZappOrgTestDimmableLight1BeginGetLevel(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe int CpProxyZappOrgTestDimmableLight1EndGetLevel(uint aHandle, uint aAsync, uint* aLevel);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe void CpProxyZappOrgTestDimmableLight1SyncSetLevel(uint aHandle, uint aLevel);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe void CpProxyZappOrgTestDimmableLight1BeginSetLevel(uint aHandle, uint aLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe int CpProxyZappOrgTestDimmableLight1EndSetLevel(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern void CpProxyZappOrgTestDimmableLight1SetPropertyA_ARG_LevelChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe void CpProxyZappOrgTestDimmableLight1PropertyA_ARG_Level(uint aHandle, uint* aA_ARG_Level);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iA_ARG_LevelChanged;
        private Callback iCallbackA_ARG_LevelChanged;

        public CpProxyZappOrgTestDimmableLight1(CpDevice aDevice)
        {
            iHandle = CpProxyZappOrgTestDimmableLight1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncGetLevel(out uint aLevel)
        {
			fixed (uint* level = &aLevel)
			{
				CpProxyZappOrgTestDimmableLight1SyncGetLevel(iHandle, level);
			}
        }

        public unsafe void BeginGetLevel(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestDimmableLight1BeginGetLevel(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetLevel(uint aAsyncHandle, out uint aLevel)
        {
			fixed (uint* level = &aLevel)
			{
				if (0 != CpProxyZappOrgTestDimmableLight1EndGetLevel(iHandle, aAsyncHandle, level))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetLevel(uint aLevel)
        {
			{
				CpProxyZappOrgTestDimmableLight1SyncSetLevel(iHandle, aLevel);
			}
        }

        public unsafe void BeginSetLevel(uint aLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestDimmableLight1BeginSetLevel(iHandle, aLevel, iActionComplete, ptr);
        }

        public unsafe void EndSetLevel(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestDimmableLight1EndSetLevel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public void SetPropertyA_ARG_LevelChanged(CallbackPropertyChanged aA_ARG_LevelChanged)
        {
            iA_ARG_LevelChanged = aA_ARG_LevelChanged;
            iCallbackA_ARG_LevelChanged = new Callback(PropertyA_ARG_LevelChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestDimmableLight1SetPropertyA_ARG_LevelChanged(iHandle, iCallbackA_ARG_LevelChanged, ptr);
        }

        private void PropertyA_ARG_LevelChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestDimmableLight1 self = (CpProxyZappOrgTestDimmableLight1)gch.Target;
            self.iA_ARG_LevelChanged();
        }

        public unsafe void PropertyA_ARG_Level(out uint aA_ARG_Level)
        {
			fixed (uint* a_ARG_Level = &aA_ARG_Level)
			{
	            CpProxyZappOrgTestDimmableLight1PropertyA_ARG_Level(iHandle, a_ARG_Level);
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyZappOrgTestDimmableLight1()
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
            CpProxyZappOrgTestDimmableLight1Destroy(handle);
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

