using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyUpnpOrgSwitchPower1 : CpProxy, IDisposable
    {
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern uint CpProxyUpnpOrgSwitchPower1Create(uint aDeviceHandle);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern void CpProxyUpnpOrgSwitchPower1Destroy(uint aHandle);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1SyncSetTarget(uint aHandle, uint anewTargetValue);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1BeginSetTarget(uint aHandle, uint anewTargetValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe int CpProxyUpnpOrgSwitchPower1EndSetTarget(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1SyncGetTarget(uint aHandle, uint* aRetTargetValue);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1BeginGetTarget(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe int CpProxyUpnpOrgSwitchPower1EndGetTarget(uint aHandle, uint aAsync, uint* aRetTargetValue);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1SyncGetStatus(uint aHandle, uint* aResultStatus);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1BeginGetStatus(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe int CpProxyUpnpOrgSwitchPower1EndGetStatus(uint aHandle, uint aAsync, uint* aResultStatus);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern void CpProxyUpnpOrgSwitchPower1SetPropertyStatusChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1PropertyStatus(uint aHandle, uint* aStatus);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iStatusChanged;
        private Callback iCallbackStatusChanged;

        public CpProxyUpnpOrgSwitchPower1(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgSwitchPower1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncSetTarget(bool anewTargetValue)
        {
			uint newTargetValue = (anewTargetValue? 1u : 0u);
			{
				CpProxyUpnpOrgSwitchPower1SyncSetTarget(iHandle, newTargetValue);
			}
        }

        public unsafe void BeginSetTarget(bool anewTargetValue, CallbackAsyncComplete aCallback)
        {
			uint newTargetValue = (anewTargetValue? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgSwitchPower1BeginSetTarget(iHandle, newTargetValue, iActionComplete, ptr);
        }

        public unsafe void EndSetTarget(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgSwitchPower1EndSetTarget(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetTarget(out bool aRetTargetValue)
        {
			uint retTargetValue;
			{
				CpProxyUpnpOrgSwitchPower1SyncGetTarget(iHandle, &retTargetValue);
			}
			aRetTargetValue = (retTargetValue != 0);
        }

        public unsafe void BeginGetTarget(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgSwitchPower1BeginGetTarget(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetTarget(uint aAsyncHandle, out bool aRetTargetValue)
        {
			uint retTargetValue;
			{
				if (0 != CpProxyUpnpOrgSwitchPower1EndGetTarget(iHandle, aAsyncHandle, &retTargetValue))
				{
					throw(new ProxyError());
				}
			}
			aRetTargetValue = (retTargetValue != 0);
        }

        public unsafe void SyncGetStatus(out bool aResultStatus)
        {
			uint resultStatus;
			{
				CpProxyUpnpOrgSwitchPower1SyncGetStatus(iHandle, &resultStatus);
			}
			aResultStatus = (resultStatus != 0);
        }

        public unsafe void BeginGetStatus(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgSwitchPower1BeginGetStatus(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetStatus(uint aAsyncHandle, out bool aResultStatus)
        {
			uint resultStatus;
			{
				if (0 != CpProxyUpnpOrgSwitchPower1EndGetStatus(iHandle, aAsyncHandle, &resultStatus))
				{
					throw(new ProxyError());
				}
			}
			aResultStatus = (resultStatus != 0);
        }

        public void SetPropertyStatusChanged(CallbackPropertyChanged aStatusChanged)
        {
            iStatusChanged = aStatusChanged;
            iCallbackStatusChanged = new Callback(PropertyStatusChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgSwitchPower1SetPropertyStatusChanged(iHandle, iCallbackStatusChanged, ptr);
        }

        private void PropertyStatusChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgSwitchPower1 self = (CpProxyUpnpOrgSwitchPower1)gch.Target;
            self.iStatusChanged();
        }

        public unsafe void PropertyStatus(out bool aStatus)
        {
			uint status;
	        CpProxyUpnpOrgSwitchPower1PropertyStatus(iHandle, &status);
			aStatus = (status != 0);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgSwitchPower1()
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
            CpProxyUpnpOrgSwitchPower1Destroy(handle);
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

