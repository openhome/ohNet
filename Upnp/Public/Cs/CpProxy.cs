using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint
{
    public class ProxyError : Exception
    {
    }
    
    /// <summary>
    /// Base interface for all proxies
    /// </summary>
    public interface ICpProxy
    {
        /// <summary>
        /// Subscribe to notification of changes in state variables.
        /// </summary>
        /// <remarks>Use SetProperty[stateVarName]Changed() to register a callback on change
        /// in a given variable or SetPropertyChangesComplete() to register a callback
        /// which runs after each group of 1..n changes is processed.</remarks>
        void Subscribe();
        /// <summary>
        /// Unsubscribe to notification of changes in state variables.
        /// </summary>
        /// <remarks>No further notifications will be published until Subscribe() is called again.</remarks>
        void Unsubscribe();
        /// <summary>
        /// Register a delegate which will run after each group of 1..n changes to state variable is processed.
        /// </summary>
        /// <param name="aPropertyChanged">The delegate to be run</param>
        void SetPropertyChanged(CpProxy.CallbackPropertyChanged aPropertyChanged);
        /// <summary>
        /// Register a delegate which will run when the state of all properties becomes available.
        /// </summary>
        /// <remarks>This is often the first point at which UI elements can be fully initialised.</remarks>
        /// <param name="aInitialEvent">The delegate to be run</param>
        void SetPropertyInitialEvent(CpProxy.CallbackPropertyChanged aInitialEvent);
    }

    /// <summary>
    /// Base class for all proxies
    /// </summary>
    public class CpProxy : ICpProxy
    {
        [DllImport("ZappUpnp")]
        static extern void CpProxyCSubscribe(IntPtr aHandle);
        [DllImport("ZappUpnp")]
        static extern void CpProxyCUnsubscribe(IntPtr aHandle);
        [DllImport("ZappUpnp")]
        static extern void CpProxyCSetPropertyChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void CpProxyCSetPropertyInitialEvent(IntPtr aHandle, Callback aCallback, IntPtr aPtr);

        public delegate void CallbackPropertyChanged();
        public delegate void CallbackAsyncComplete(IntPtr aAsyncHandle);
        protected delegate void CallbackActionComplete(IntPtr aPtr, IntPtr aAsyncHandle);
        protected delegate void Callback(IntPtr aPtr);
        
        protected IntPtr iHandle;
        protected CallbackActionComplete iActionComplete;
        private GCHandle iGchProxy;
        private CallbackPropertyChanged iPropertyChanged;
        private Callback iCallbackPropertyChanged;
        private CallbackPropertyChanged iInitialEvent;
        private Callback iCallbackInitialEvent;

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

        public void SetPropertyInitialEvent(CallbackPropertyChanged aInitialEvent)
        {
            iInitialEvent = aInitialEvent;
            iCallbackInitialEvent = new Callback(InitialEvent);
            IntPtr ptr = GCHandle.ToIntPtr(iGchProxy);
            CpProxyCSetPropertyInitialEvent(iHandle, iCallbackInitialEvent, ptr);
        }

        protected CpProxy()
        {
            iGchProxy = GCHandle.Alloc(this);
            iActionComplete = new CallbackActionComplete(ActionComplete);
        }
        
        protected void ActionComplete(IntPtr aPtr, IntPtr aAsyncHandle)
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

        private void InitialEvent(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxy self = (CpProxy)gch.Target;
            self.iInitialEvent();
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
