using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp.Core;
using System.Threading;

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
        /// Register an action which will run after each group of 1..n changes to state variable is processed.
        /// </summary>
        /// <param name="aPropertyChanged">The action to be run</param>
        void SetPropertyChanged(System.Action aPropertyChanged);
        /// <summary>
        /// Register a action which will run when the state of all properties becomes available.
        /// </summary>
        /// <remarks>This is often the first point at which UI elements can be fully initialised.</remarks>
        /// <param name="aInitialEvent">The action to be run</param>
        void SetPropertyInitialEvent(System.Action aInitialEvent);
    }

    /// <summary>
    /// Base class for all proxies
    /// </summary>
    public class CpProxy : ICpProxy
    {
        [DllImport("ZappUpnp")]
        static extern unsafe IntPtr CpProxyCreate(char* aDomain, char* aName, uint aVersion, IntPtr aDevice);
        [DllImport("ZappUpnp")]
        static extern void CpProxyDestroy(IntPtr Proxy);
        [DllImport("ZappUpnp")]
        static extern IntPtr CpProxyService(IntPtr aProxy);
        [DllImport("ZappUpnp")]
        static extern void CpProxySubscribe(IntPtr aHandle);
        [DllImport("ZappUpnp")]
        static extern void CpProxyUnsubscribe(IntPtr aHandle);
        [DllImport("ZappUpnp")]
        static extern void CpProxySetPropertyChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void CpProxySetPropertyInitialEvent(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void CpProxyPropertyReadLock(IntPtr aHandle);
        [DllImport("ZappUpnp")]
        static extern void CpProxyPropertyReadUnlock(IntPtr aHandle);
        [DllImport("ZappUpnp")]
        static extern void CpProxyAddProperty(IntPtr aHandle, IntPtr aProperty);

        public delegate void CallbackAsyncComplete(IntPtr aAsyncHandle);
        public delegate void CallbackActionComplete(IntPtr aPtr, IntPtr aAsyncHandle);
        public delegate void Callback(IntPtr aPtr);

        enum SubscriptionStatus
        {
            eNotSubscribed,
            eSubscribing,
            eSubscribed
        };
        
        protected IntPtr iHandle;
        protected CpService iService;
        private GCHandle iGchProxy;
        private System.Action iPropertyChanged;
        private Callback iCallbackPropertyChanged;
        private System.Action iInitialEvent;
        private Callback iCallbackInitialEvent;
        private SubscriptionStatus iSubscriptionStatus = SubscriptionStatus.eNotSubscribed;
        private Mutex iSubscriptionStatusLock;

        public void Subscribe()
        {
            lock (iSubscriptionStatusLock)
            {
                iSubscriptionStatus = SubscriptionStatus.eSubscribing;
            }
            CpProxySubscribe(iHandle);
        }

        public void Unsubscribe()
        {
            lock (iSubscriptionStatusLock)
            {
                iSubscriptionStatus = SubscriptionStatus.eNotSubscribed;
            }
            CpProxyUnsubscribe(iHandle);
        }

        public void SetPropertyChanged(System.Action aPropertyChanged)
        {
            iPropertyChanged = aPropertyChanged;
            iCallbackPropertyChanged = new Callback(PropertyChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGchProxy);
            CpProxySetPropertyChanged(iHandle, iCallbackPropertyChanged, ptr);
        }

        public void SetPropertyInitialEvent(System.Action aInitialEvent)
        {
            iInitialEvent = aInitialEvent;
            iCallbackInitialEvent = new Callback(InitialEvent);
            IntPtr ptr = GCHandle.ToIntPtr(iGchProxy);
            CpProxySetPropertyInitialEvent(iHandle, iCallbackInitialEvent, ptr);
        }

        protected unsafe CpProxy(String aDomain, String aName, uint aVersion, CpDevice aDevice)
        {
            char* domain = (char*)Marshal.StringToHGlobalAnsi(aDomain);
            char* name = (char*)Marshal.StringToHGlobalAnsi(aName);
            iHandle = CpProxyCreate(domain, name, aVersion, aDevice.Handle());
            Marshal.FreeHGlobal((IntPtr)domain);
            Marshal.FreeHGlobal((IntPtr)name);
            IntPtr serviceHandle = CpProxyService(iHandle);
            iService = new CpService(serviceHandle);
            iGchProxy = GCHandle.Alloc(this);
            iSubscriptionStatusLock = new Mutex();
        }

        protected void PropertyReadLock()
        {
            CpProxyPropertyReadLock(iHandle);
        }

        protected void PropertyReadUnlock()
        {
            CpProxyPropertyReadUnlock(iHandle);
        }

        protected void ReportEvent(System.Action aCallback)
        {
            lock (iSubscriptionStatusLock)
            {
                if (iSubscriptionStatus == SubscriptionStatus.eSubscribing)
                {
                    iSubscriptionStatus = SubscriptionStatus.eSubscribed;
                }
                if (iSubscriptionStatus == SubscriptionStatus.eSubscribed && aCallback != null)
                {
                    aCallback();
                }
            }
        }

        protected void AddProperty(Property aProperty)
        {
            CpProxyAddProperty(iHandle, aProperty.Handle());
        }
        
        private void PropertyChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxy self = (CpProxy)gch.Target;
            Property.CallPropertyChangedDelegate(self.iPropertyChanged);
        }

        private void InitialEvent(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxy self = (CpProxy)gch.Target;
            Property.CallPropertyChangedDelegate(self.iInitialEvent);
        }

        protected void DisposeProxy()
        {
            if(iGchProxy.IsAllocated)
                iGchProxy.Free();
            CpProxyDestroy(iHandle);
        }
    }

    public abstract class SyncProxyAction
    {
        private CpProxy.CallbackAsyncComplete iAsyncComplete;
        private Semaphore iSem;
        private bool iError;

        public CpProxy.CallbackAsyncComplete AsyncComplete()
        {
            return iAsyncComplete;
        }

        public void Wait()
        {
            iSem.WaitOne();
        }

        public void ReportError()
        {
            if (iError)
            {
                throw new ProxyError();
            }
        }

        protected SyncProxyAction()
        {
            iAsyncComplete = new CpProxy.CallbackAsyncComplete(CallbackAsyncComplete);
            iSem = new Semaphore(0, 1);
        }

        protected abstract void CompleteRequest(IntPtr aAsyncHandle);

        private void CallbackAsyncComplete(IntPtr aAsyncHandle)
        {
            try
            {
                CompleteRequest(aAsyncHandle);
            }
            catch (ProxyError)
            {
                iError = true;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ProxyError can be thrown by action complete delegates");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            iSem.Release();
        }
    };
}
