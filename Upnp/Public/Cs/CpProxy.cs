using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class ProxyError : Exception
    {
    }

    public class CpProxy
    {
        [DllImport("ZappUpnp")]
        static extern void CpProxyCSubscribe(uint aHandle);
        [DllImport("ZappUpnp")]
        static extern void CpProxyCUnsubscribe(uint aHandle);
        [DllImport("ZappUpnp")]
        static extern void CpProxyCSetPropertyChanged(uint aHandle, Callback aCallback, IntPtr aPtr);

        public delegate void CallbackPropertyChanged();
        public delegate void CallbackAsyncComplete(uint aAsyncHandle);
        protected delegate void CallbackActionComplete(IntPtr aPtr, uint aAsyncHandle);
        protected delegate void Callback(IntPtr aPtr);
        
        protected uint iHandle;
        protected CallbackActionComplete iActionComplete;
        private GCHandle iGchProxy;
        private CallbackPropertyChanged iPropertyChanged;
        private Callback iCallbackPropertyChanged;

        public void Subscribe()
        {
            CpProxyCSubscribe(iHandle);
        }

        public void Unsubscribe()
        {
            CpProxyCUnsubscribe(iHandle);
        }

        public void SetPropertyChanged(CallbackPropertyChanged aPropertyChanged)
        {
            iPropertyChanged = aPropertyChanged;
            iCallbackPropertyChanged = new Callback(PropertyChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGchProxy);
            CpProxyCSetPropertyChanged(iHandle, iCallbackPropertyChanged, ptr);
        }

        protected CpProxy()
        {
            iGchProxy = GCHandle.Alloc(this);
            iActionComplete = new CallbackActionComplete(ActionComplete);
        }
        
        protected void ActionComplete(IntPtr aPtr, uint aAsyncHandle)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CallbackAsyncComplete cb = (CallbackAsyncComplete)gch.Target;
            gch.Free();
            cb(aAsyncHandle);
        }

        private void PropertyChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxy self = (CpProxy)gch.Target;
            self.iPropertyChanged();
        }
    
        ~CpProxy()
        {
            DisposeProxy();
        }

        protected void DisposeProxy()
        {
            if(iGchProxy.IsAllocated)
                iGchProxy.Free();
        }
    }
}
