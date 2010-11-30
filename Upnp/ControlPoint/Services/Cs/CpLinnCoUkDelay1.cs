using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkDelay1 : ICpProxy, IDisposable
    {
        void SyncPresetXml(out string aaPresetXml);
        void BeginPresetXml(CpProxy.CallbackAsyncComplete aCallback);
        void EndPresetXml(uint aAsyncHandle, out string aaPresetXml);
        void SyncPresetIndex(out uint aaIndex);
        void BeginPresetIndex(CpProxy.CallbackAsyncComplete aCallback);
        void EndPresetIndex(uint aAsyncHandle, out uint aaIndex);
        void SyncSetPresetIndex(uint aaIndex);
        void BeginSetPresetIndex(uint aaIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetPresetIndex(uint aAsyncHandle);
        void SyncSetPresetDelay(uint aaIndex, uint aaDelay);
        void BeginSetPresetDelay(uint aaIndex, uint aaDelay, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetPresetDelay(uint aAsyncHandle);
        void SyncSetPresetVisible(uint aaIndex, bool aaVisible);
        void BeginSetPresetVisible(uint aaIndex, bool aaVisible, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetPresetVisible(uint aAsyncHandle);
        void SyncSetPresetName(uint aaIndex, string aaName);
        void BeginSetPresetName(uint aaIndex, string aaName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetPresetName(uint aAsyncHandle);
        void SyncDelayMinimum(out uint aaDelay);
        void BeginDelayMinimum(CpProxy.CallbackAsyncComplete aCallback);
        void EndDelayMinimum(uint aAsyncHandle, out uint aaDelay);
        void SyncDelayMaximum(out uint aaDelay);
        void BeginDelayMaximum(CpProxy.CallbackAsyncComplete aCallback);
        void EndDelayMaximum(uint aAsyncHandle, out uint aaDelay);
        void SyncPresetCount(out uint aaCount);
        void BeginPresetCount(CpProxy.CallbackAsyncComplete aCallback);
        void EndPresetCount(uint aAsyncHandle, out uint aaCount);

        void SetPropertyPresetXmlChanged(CpProxy.CallbackPropertyChanged aPresetXmlChanged);
        void PropertyPresetXml(out string aPresetXml);
        void SetPropertyPresetIndexChanged(CpProxy.CallbackPropertyChanged aPresetIndexChanged);
        void PropertyPresetIndex(out uint aPresetIndex);
    }

    /// <summary>
    /// Proxy for the linn.co.uk:Delay:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkDelay1 : CpProxy, IDisposable, ICpProxyLinnCoUkDelay1
    {
        [DllImport("CpLinnCoUkDelay1")]
        static extern uint CpProxyLinnCoUkDelay1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkDelay1")]
        static extern void CpProxyLinnCoUkDelay1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncPresetXml(uint aHandle, char** aaPresetXml);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginPresetXml(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndPresetXml(uint aHandle, uint aAsync, char** aaPresetXml);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncPresetIndex(uint aHandle, uint* aaIndex);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginPresetIndex(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndPresetIndex(uint aHandle, uint aAsync, uint* aaIndex);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncSetPresetIndex(uint aHandle, uint aaIndex);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginSetPresetIndex(uint aHandle, uint aaIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndSetPresetIndex(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncSetPresetDelay(uint aHandle, uint aaIndex, uint aaDelay);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginSetPresetDelay(uint aHandle, uint aaIndex, uint aaDelay, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndSetPresetDelay(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncSetPresetVisible(uint aHandle, uint aaIndex, uint aaVisible);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginSetPresetVisible(uint aHandle, uint aaIndex, uint aaVisible, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndSetPresetVisible(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncSetPresetName(uint aHandle, uint aaIndex, char* aaName);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginSetPresetName(uint aHandle, uint aaIndex, char* aaName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndSetPresetName(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncDelayMinimum(uint aHandle, uint* aaDelay);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginDelayMinimum(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndDelayMinimum(uint aHandle, uint aAsync, uint* aaDelay);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncDelayMaximum(uint aHandle, uint* aaDelay);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginDelayMaximum(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndDelayMaximum(uint aHandle, uint aAsync, uint* aaDelay);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1SyncPresetCount(uint aHandle, uint* aaCount);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1BeginPresetCount(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe int CpProxyLinnCoUkDelay1EndPresetCount(uint aHandle, uint aAsync, uint* aaCount);
        [DllImport("CpLinnCoUkDelay1")]
        static extern void CpProxyLinnCoUkDelay1SetPropertyPresetXmlChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern void CpProxyLinnCoUkDelay1SetPropertyPresetIndexChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1PropertyPresetXml(uint aHandle, char** aPresetXml);
        [DllImport("CpLinnCoUkDelay1")]
        static extern unsafe void CpProxyLinnCoUkDelay1PropertyPresetIndex(uint aHandle, uint* aPresetIndex);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iPresetXmlChanged;
        private CallbackPropertyChanged iPresetIndexChanged;
        private Callback iCallbackPresetXmlChanged;
        private Callback iCallbackPresetIndexChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkDelay1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkDelay1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPresetXml"></param>
        public unsafe void SyncPresetXml(out string aaPresetXml)
        {
            char* aPresetXml;
            {
                CpProxyLinnCoUkDelay1SyncPresetXml(iHandle, &aPresetXml);
            }
            aaPresetXml = Marshal.PtrToStringAnsi((IntPtr)aPresetXml);
            ZappFree(aPresetXml);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPresetXml().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPresetXml(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginPresetXml(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaPresetXml"></param>
        public unsafe void EndPresetXml(uint aAsyncHandle, out string aaPresetXml)
        {
            char* aPresetXml;
            {
                if (0 != CpProxyLinnCoUkDelay1EndPresetXml(iHandle, aAsyncHandle, &aPresetXml))
                {
                    throw(new ProxyError());
                }
            }
            aaPresetXml = Marshal.PtrToStringAnsi((IntPtr)aPresetXml);
            ZappFree(aPresetXml);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIndex"></param>
        public unsafe void SyncPresetIndex(out uint aaIndex)
        {
            fixed (uint* aIndex = &aaIndex)
            {
                CpProxyLinnCoUkDelay1SyncPresetIndex(iHandle, aIndex);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPresetIndex().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPresetIndex(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginPresetIndex(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIndex"></param>
        public unsafe void EndPresetIndex(uint aAsyncHandle, out uint aaIndex)
        {
            fixed (uint* aIndex = &aaIndex)
            {
                if (0 != CpProxyLinnCoUkDelay1EndPresetIndex(iHandle, aAsyncHandle, aIndex))
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
        /// <param name="aaIndex"></param>
        public unsafe void SyncSetPresetIndex(uint aaIndex)
        {
            {
                CpProxyLinnCoUkDelay1SyncSetPresetIndex(iHandle, aaIndex);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetPresetIndex().</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetPresetIndex(uint aaIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginSetPresetIndex(iHandle, aaIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetPresetIndex(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkDelay1EndSetPresetIndex(iHandle, aAsyncHandle))
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
        /// <param name="aaIndex"></param>
        /// <param name="aaDelay"></param>
        public unsafe void SyncSetPresetDelay(uint aaIndex, uint aaDelay)
        {
            {
                CpProxyLinnCoUkDelay1SyncSetPresetDelay(iHandle, aaIndex, aaDelay);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetPresetDelay().</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aaDelay"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetPresetDelay(uint aaIndex, uint aaDelay, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginSetPresetDelay(iHandle, aaIndex, aaDelay, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetPresetDelay(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkDelay1EndSetPresetDelay(iHandle, aAsyncHandle))
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
        /// <param name="aaIndex"></param>
        /// <param name="aaVisible"></param>
        public unsafe void SyncSetPresetVisible(uint aaIndex, bool aaVisible)
        {
            uint aVisible = (aaVisible? 1u : 0u);
            {
                CpProxyLinnCoUkDelay1SyncSetPresetVisible(iHandle, aaIndex, aVisible);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetPresetVisible().</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aaVisible"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetPresetVisible(uint aaIndex, bool aaVisible, CallbackAsyncComplete aCallback)
        {
            uint aVisible = (aaVisible? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginSetPresetVisible(iHandle, aaIndex, aVisible, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetPresetVisible(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkDelay1EndSetPresetVisible(iHandle, aAsyncHandle))
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
        /// <param name="aaIndex"></param>
        /// <param name="aaName"></param>
        public unsafe void SyncSetPresetName(uint aaIndex, string aaName)
        {
            char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
            {
                CpProxyLinnCoUkDelay1SyncSetPresetName(iHandle, aaIndex, aName);
            }
            Marshal.FreeHGlobal((IntPtr)aName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetPresetName().</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aaName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetPresetName(uint aaIndex, string aaName, CallbackAsyncComplete aCallback)
        {
            char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginSetPresetName(iHandle, aaIndex, aName, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aName);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetPresetName(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkDelay1EndSetPresetName(iHandle, aAsyncHandle))
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
        /// <param name="aaDelay"></param>
        public unsafe void SyncDelayMinimum(out uint aaDelay)
        {
            fixed (uint* aDelay = &aaDelay)
            {
                CpProxyLinnCoUkDelay1SyncDelayMinimum(iHandle, aDelay);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDelayMinimum().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDelayMinimum(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginDelayMinimum(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaDelay"></param>
        public unsafe void EndDelayMinimum(uint aAsyncHandle, out uint aaDelay)
        {
            fixed (uint* aDelay = &aaDelay)
            {
                if (0 != CpProxyLinnCoUkDelay1EndDelayMinimum(iHandle, aAsyncHandle, aDelay))
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
        /// <param name="aaDelay"></param>
        public unsafe void SyncDelayMaximum(out uint aaDelay)
        {
            fixed (uint* aDelay = &aaDelay)
            {
                CpProxyLinnCoUkDelay1SyncDelayMaximum(iHandle, aDelay);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDelayMaximum().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDelayMaximum(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginDelayMaximum(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaDelay"></param>
        public unsafe void EndDelayMaximum(uint aAsyncHandle, out uint aaDelay)
        {
            fixed (uint* aDelay = &aaDelay)
            {
                if (0 != CpProxyLinnCoUkDelay1EndDelayMaximum(iHandle, aAsyncHandle, aDelay))
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
        /// <param name="aaCount"></param>
        public unsafe void SyncPresetCount(out uint aaCount)
        {
            fixed (uint* aCount = &aaCount)
            {
                CpProxyLinnCoUkDelay1SyncPresetCount(iHandle, aCount);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPresetCount().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPresetCount(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDelay1BeginPresetCount(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaCount"></param>
        public unsafe void EndPresetCount(uint aAsyncHandle, out uint aaCount)
        {
            fixed (uint* aCount = &aaCount)
            {
                if (0 != CpProxyLinnCoUkDelay1EndPresetCount(iHandle, aAsyncHandle, aCount))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the PresetXml state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDelay1 instance will not overlap.</remarks>
        /// <param name="aPresetXmlChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyPresetXmlChanged(CallbackPropertyChanged aPresetXmlChanged)
        {
            iPresetXmlChanged = aPresetXmlChanged;
            iCallbackPresetXmlChanged = new Callback(PropertyPresetXmlChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDelay1SetPropertyPresetXmlChanged(iHandle, iCallbackPresetXmlChanged, ptr);
        }

        private void PropertyPresetXmlChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDelay1 self = (CpProxyLinnCoUkDelay1)gch.Target;
            self.iPresetXmlChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the PresetIndex state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDelay1 instance will not overlap.</remarks>
        /// <param name="aPresetIndexChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyPresetIndexChanged(CallbackPropertyChanged aPresetIndexChanged)
        {
            iPresetIndexChanged = aPresetIndexChanged;
            iCallbackPresetIndexChanged = new Callback(PropertyPresetIndexChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDelay1SetPropertyPresetIndexChanged(iHandle, iCallbackPresetIndexChanged, ptr);
        }

        private void PropertyPresetIndexChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDelay1 self = (CpProxyLinnCoUkDelay1)gch.Target;
            self.iPresetIndexChanged();
        }

        /// <summary>
        /// Query the value of the PresetXml property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aPresetXml">Will be set to the value of the property</param>
        public unsafe void PropertyPresetXml(out string aPresetXml)
        {
            char* ptr;
            CpProxyLinnCoUkDelay1PropertyPresetXml(iHandle, &ptr);
            aPresetXml = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the PresetIndex property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aPresetIndex">Will be set to the value of the property</param>
        public unsafe void PropertyPresetIndex(out uint aPresetIndex)
        {
            fixed (uint* presetIndex = &aPresetIndex)
            {
                CpProxyLinnCoUkDelay1PropertyPresetIndex(iHandle, presetIndex);
            }
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkDelay1()
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
                CpProxyLinnCoUkDelay1Destroy(iHandle);
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

