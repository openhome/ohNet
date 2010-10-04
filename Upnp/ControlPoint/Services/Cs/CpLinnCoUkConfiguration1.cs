using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkConfiguration1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern uint CpProxyLinnCoUkConfiguration1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern void CpProxyLinnCoUkConfiguration1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1SyncConfigurationXml(uint aHandle, char** aaConfigurationXml);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1BeginConfigurationXml(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe int CpProxyLinnCoUkConfiguration1EndConfigurationXml(uint aHandle, uint aAsync, char** aaConfigurationXml);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1SyncParameterXml(uint aHandle, char** aaParameterXml);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1BeginParameterXml(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe int CpProxyLinnCoUkConfiguration1EndParameterXml(uint aHandle, uint aAsync, char** aaParameterXml);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1SyncSetParameter(uint aHandle, char* aaTarget, char* aaName, char* aaValue);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1BeginSetParameter(uint aHandle, char* aaTarget, char* aaName, char* aaValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe int CpProxyLinnCoUkConfiguration1EndSetParameter(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern void CpProxyLinnCoUkConfiguration1SetPropertyConfigurationXmlChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern void CpProxyLinnCoUkConfiguration1SetPropertyParameterXmlChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1PropertyConfigurationXml(uint aHandle, char** aConfigurationXml);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1PropertyParameterXml(uint aHandle, char** aParameterXml);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iConfigurationXmlChanged;
        private CallbackPropertyChanged iParameterXmlChanged;
        private Callback iCallbackConfigurationXmlChanged;
        private Callback iCallbackParameterXmlChanged;

        public CpProxyLinnCoUkConfiguration1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkConfiguration1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncConfigurationXml(out string aaConfigurationXml)
        {
			char* aConfigurationXml;
			{
				CpProxyLinnCoUkConfiguration1SyncConfigurationXml(iHandle, &aConfigurationXml);
			}
            aaConfigurationXml = Marshal.PtrToStringAnsi((IntPtr)aConfigurationXml);
            ZappFree(aConfigurationXml);
        }

        public unsafe void BeginConfigurationXml(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkConfiguration1BeginConfigurationXml(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndConfigurationXml(uint aAsyncHandle, out string aaConfigurationXml)
        {
			char* aConfigurationXml;
			{
				if (0 != CpProxyLinnCoUkConfiguration1EndConfigurationXml(iHandle, aAsyncHandle, &aConfigurationXml))
				{
					throw(new ProxyError());
				}
			}
            aaConfigurationXml = Marshal.PtrToStringAnsi((IntPtr)aConfigurationXml);
            ZappFree(aConfigurationXml);
        }

        public unsafe void SyncParameterXml(out string aaParameterXml)
        {
			char* aParameterXml;
			{
				CpProxyLinnCoUkConfiguration1SyncParameterXml(iHandle, &aParameterXml);
			}
            aaParameterXml = Marshal.PtrToStringAnsi((IntPtr)aParameterXml);
            ZappFree(aParameterXml);
        }

        public unsafe void BeginParameterXml(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkConfiguration1BeginParameterXml(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndParameterXml(uint aAsyncHandle, out string aaParameterXml)
        {
			char* aParameterXml;
			{
				if (0 != CpProxyLinnCoUkConfiguration1EndParameterXml(iHandle, aAsyncHandle, &aParameterXml))
				{
					throw(new ProxyError());
				}
			}
            aaParameterXml = Marshal.PtrToStringAnsi((IntPtr)aParameterXml);
            ZappFree(aParameterXml);
        }

        public unsafe void SyncSetParameter(string aaTarget, string aaName, string aaValue)
        {
			char* aTarget = (char*)Marshal.StringToHGlobalAnsi(aaTarget);
			char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
			char* aValue = (char*)Marshal.StringToHGlobalAnsi(aaValue);
			{
				CpProxyLinnCoUkConfiguration1SyncSetParameter(iHandle, aTarget, aName, aValue);
			}
			Marshal.FreeHGlobal((IntPtr)aTarget);
			Marshal.FreeHGlobal((IntPtr)aName);
			Marshal.FreeHGlobal((IntPtr)aValue);
        }

        public unsafe void BeginSetParameter(string aaTarget, string aaName, string aaValue, CallbackAsyncComplete aCallback)
        {
			char* aTarget = (char*)Marshal.StringToHGlobalAnsi(aaTarget);
			char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
			char* aValue = (char*)Marshal.StringToHGlobalAnsi(aaValue);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkConfiguration1BeginSetParameter(iHandle, aTarget, aName, aValue, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aTarget);
			Marshal.FreeHGlobal((IntPtr)aName);
			Marshal.FreeHGlobal((IntPtr)aValue);
        }

        public unsafe void EndSetParameter(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkConfiguration1EndSetParameter(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public void SetPropertyConfigurationXmlChanged(CallbackPropertyChanged aConfigurationXmlChanged)
        {
            iConfigurationXmlChanged = aConfigurationXmlChanged;
            iCallbackConfigurationXmlChanged = new Callback(PropertyConfigurationXmlChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkConfiguration1SetPropertyConfigurationXmlChanged(iHandle, iCallbackConfigurationXmlChanged, ptr);
        }

        private void PropertyConfigurationXmlChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkConfiguration1 self = (CpProxyLinnCoUkConfiguration1)gch.Target;
            self.iConfigurationXmlChanged();
        }

        public void SetPropertyParameterXmlChanged(CallbackPropertyChanged aParameterXmlChanged)
        {
            iParameterXmlChanged = aParameterXmlChanged;
            iCallbackParameterXmlChanged = new Callback(PropertyParameterXmlChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkConfiguration1SetPropertyParameterXmlChanged(iHandle, iCallbackParameterXmlChanged, ptr);
        }

        private void PropertyParameterXmlChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkConfiguration1 self = (CpProxyLinnCoUkConfiguration1)gch.Target;
            self.iParameterXmlChanged();
        }

        public unsafe void PropertyConfigurationXml(out string aConfigurationXml)
        {
			char* ptr;
            CpProxyLinnCoUkConfiguration1PropertyConfigurationXml(iHandle, &ptr);
            aConfigurationXml = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyParameterXml(out string aParameterXml)
        {
			char* ptr;
            CpProxyLinnCoUkConfiguration1PropertyParameterXml(iHandle, &ptr);
            aParameterXml = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkConfiguration1()
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
            CpProxyLinnCoUkConfiguration1Destroy(handle);
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

