using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyZappOrgTestDimmableLight1 : ICpProxy, IDisposable
    {
        void SyncGetLevel(out uint aLevel);
        void BeginGetLevel(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLevel(uint aAsyncHandle, out uint aLevel);
        void SyncSetLevel(uint aLevel);
        void BeginSetLevel(uint aLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetLevel(uint aAsyncHandle);

        void SetPropertyA_ARG_LevelChanged(CpProxy.CallbackPropertyChanged aA_ARG_LevelChanged);
        void PropertyA_ARG_Level(out uint aA_ARG_Level);
    }

    /// <summary>
    /// Proxy for the zapp.org:TestDimmableLight:1 UPnP service
    /// </summary>
    public class CpProxyZappOrgTestDimmableLight1 : CpProxy, IDisposable, ICpProxyZappOrgTestDimmableLight1
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyZappOrgTestDimmableLight1(CpDevice aDevice)
        {
            iHandle = CpProxyZappOrgTestDimmableLight1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aLevel"></param>
        public unsafe void SyncGetLevel(out uint aLevel)
        {
            fixed (uint* level = &aLevel)
            {
                CpProxyZappOrgTestDimmableLight1SyncGetLevel(iHandle, level);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetLevel().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetLevel(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestDimmableLight1BeginGetLevel(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aLevel"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aLevel"></param>
        public unsafe void SyncSetLevel(uint aLevel)
        {
            {
                CpProxyZappOrgTestDimmableLight1SyncSetLevel(iHandle, aLevel);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetLevel().</remarks>
        /// <param name="aLevel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetLevel(uint aLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestDimmableLight1BeginSetLevel(iHandle, aLevel, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetLevel(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyZappOrgTestDimmableLight1EndSetLevel(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the A_ARG_Level state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestDimmableLight1 instance will not overlap.</remarks>
        /// <param name="aA_ARG_LevelChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Query the value of the A_ARG_Level property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aA_ARG_Level">Will be set to the value of the property</param>
        public unsafe void PropertyA_ARG_Level(out uint aA_ARG_Level)
        {
            fixed (uint* a_ARG_Level = &aA_ARG_Level)
            {
                CpProxyZappOrgTestDimmableLight1PropertyA_ARG_Level(iHandle, a_ARG_Level);
            }
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                CpProxyZappOrgTestDimmableLight1Destroy(iHandle);
                iHandle = 0;
            }
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

