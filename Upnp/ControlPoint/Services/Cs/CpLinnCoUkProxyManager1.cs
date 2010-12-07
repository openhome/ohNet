using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkProxyManager1 : ICpProxy, IDisposable
    {
        void SyncKontrolProductConnected(out string aaConnected);
        void BeginKontrolProductConnected(CpProxy.CallbackAsyncComplete aCallback);
        void EndKontrolProductConnected(IntPtr aAsyncHandle, out string aaConnected);
        void SyncSetKontrolProductConnected(string aaConnected);
        void BeginSetKontrolProductConnected(string aaConnected, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetKontrolProductConnected(IntPtr aAsyncHandle);
        void SyncKontrolProductComPort(out uint aaPort);
        void BeginKontrolProductComPort(CpProxy.CallbackAsyncComplete aCallback);
        void EndKontrolProductComPort(IntPtr aAsyncHandle, out uint aaPort);
        void SyncSetKontrolProductComPort(uint aaConnected);
        void BeginSetKontrolProductComPort(uint aaConnected, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetKontrolProductComPort(IntPtr aAsyncHandle);
        void SyncDiscPlayerConnected(out string aaConnected);
        void BeginDiscPlayerConnected(CpProxy.CallbackAsyncComplete aCallback);
        void EndDiscPlayerConnected(IntPtr aAsyncHandle, out string aaConnected);
        void SyncSetDiscPlayerConnected(string aaConnected);
        void BeginSetDiscPlayerConnected(string aaConnected, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDiscPlayerConnected(IntPtr aAsyncHandle);
        void SyncDiscPlayerComPort(out uint aaPort);
        void BeginDiscPlayerComPort(CpProxy.CallbackAsyncComplete aCallback);
        void EndDiscPlayerComPort(IntPtr aAsyncHandle, out uint aaPort);
        void SyncSetDiscPlayerComPort(uint aaConnected);
        void BeginSetDiscPlayerComPort(uint aaConnected, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDiscPlayerComPort(IntPtr aAsyncHandle);
        void SyncTestKontrolProductConnection(out bool aaResult);
        void BeginTestKontrolProductConnection(CpProxy.CallbackAsyncComplete aCallback);
        void EndTestKontrolProductConnection(IntPtr aAsyncHandle, out bool aaResult);
        void SyncTestDiscPlayerConnection(out bool aaResult);
        void BeginTestDiscPlayerConnection(CpProxy.CallbackAsyncComplete aCallback);
        void EndTestDiscPlayerConnection(IntPtr aAsyncHandle, out bool aaResult);

        void SetPropertyKontrolProductConnectedChanged(CpProxy.CallbackPropertyChanged aKontrolProductConnectedChanged);
        void PropertyKontrolProductConnected(out string aKontrolProductConnected);
        void SetPropertyKontrolProductComPortChanged(CpProxy.CallbackPropertyChanged aKontrolProductComPortChanged);
        void PropertyKontrolProductComPort(out uint aKontrolProductComPort);
        void SetPropertyDiscPlayerConnectedChanged(CpProxy.CallbackPropertyChanged aDiscPlayerConnectedChanged);
        void PropertyDiscPlayerConnected(out string aDiscPlayerConnected);
        void SetPropertyDiscPlayerComPortChanged(CpProxy.CallbackPropertyChanged aDiscPlayerComPortChanged);
        void PropertyDiscPlayerComPort(out uint aDiscPlayerComPort);
    }

    /// <summary>
    /// Proxy for the linn.co.uk:ProxyManager:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkProxyManager1 : CpProxy, IDisposable, ICpProxyLinnCoUkProxyManager1
    {
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern IntPtr CpProxyLinnCoUkProxyManager1Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncKontrolProductConnected(IntPtr aHandle, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginKontrolProductConnected(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndKontrolProductConnected(IntPtr aHandle, IntPtr aAsync, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductConnected(IntPtr aHandle, char* aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductConnected(IntPtr aHandle, char* aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetKontrolProductConnected(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncKontrolProductComPort(IntPtr aHandle, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginKontrolProductComPort(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndKontrolProductComPort(IntPtr aHandle, IntPtr aAsync, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductComPort(IntPtr aHandle, uint aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductComPort(IntPtr aHandle, uint aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetKontrolProductComPort(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncDiscPlayerConnected(IntPtr aHandle, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginDiscPlayerConnected(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndDiscPlayerConnected(IntPtr aHandle, IntPtr aAsync, char** aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerConnected(IntPtr aHandle, char* aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerConnected(IntPtr aHandle, char* aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetDiscPlayerConnected(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncDiscPlayerComPort(IntPtr aHandle, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginDiscPlayerComPort(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndDiscPlayerComPort(IntPtr aHandle, IntPtr aAsync, uint* aaPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerComPort(IntPtr aHandle, uint aaConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerComPort(IntPtr aHandle, uint aaConnected, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndSetDiscPlayerComPort(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncTestKontrolProductConnection(IntPtr aHandle, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginTestKontrolProductConnection(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndTestKontrolProductConnection(IntPtr aHandle, IntPtr aAsync, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1SyncTestDiscPlayerConnection(IntPtr aHandle, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1BeginTestDiscPlayerConnection(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe int CpProxyLinnCoUkProxyManager1EndTestDiscPlayerConnection(IntPtr aHandle, IntPtr aAsync, uint* aaResult);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductConnectedChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductComPortChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerConnectedChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerComPortChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyKontrolProductConnected(IntPtr aHandle, char** aKontrolProductConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyKontrolProductComPort(IntPtr aHandle, uint* aKontrolProductComPort);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerConnected(IntPtr aHandle, char** aDiscPlayerConnected);
        [DllImport("CpLinnCoUkProxyManager1")]
        static extern unsafe void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerComPort(IntPtr aHandle, uint* aDiscPlayerComPort);
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkProxyManager1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkProxyManager1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaConnected"></param>
        public unsafe void SyncKontrolProductConnected(out string aaConnected)
        {
            char* aConnected;
            {
                CpProxyLinnCoUkProxyManager1SyncKontrolProductConnected(iHandle, &aConnected);
            }
            aaConnected = Marshal.PtrToStringAnsi((IntPtr)aConnected);
            ZappFree(aConnected);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndKontrolProductConnected().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginKontrolProductConnected(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginKontrolProductConnected(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaConnected"></param>
        public unsafe void EndKontrolProductConnected(IntPtr aAsyncHandle, out string aaConnected)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaConnected"></param>
        public unsafe void SyncSetKontrolProductConnected(string aaConnected)
        {
            char* aConnected = (char*)Marshal.StringToHGlobalAnsi(aaConnected);
            {
                CpProxyLinnCoUkProxyManager1SyncSetKontrolProductConnected(iHandle, aConnected);
            }
            Marshal.FreeHGlobal((IntPtr)aConnected);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetKontrolProductConnected().</remarks>
        /// <param name="aaConnected"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetKontrolProductConnected(string aaConnected, CallbackAsyncComplete aCallback)
        {
            char* aConnected = (char*)Marshal.StringToHGlobalAnsi(aaConnected);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginSetKontrolProductConnected(iHandle, aConnected, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aConnected);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetKontrolProductConnected(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProxyManager1EndSetKontrolProductConnected(iHandle, aAsyncHandle))
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
        /// <param name="aaPort"></param>
        public unsafe void SyncKontrolProductComPort(out uint aaPort)
        {
            fixed (uint* aPort = &aaPort)
            {
                CpProxyLinnCoUkProxyManager1SyncKontrolProductComPort(iHandle, aPort);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndKontrolProductComPort().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginKontrolProductComPort(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginKontrolProductComPort(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaPort"></param>
        public unsafe void EndKontrolProductComPort(IntPtr aAsyncHandle, out uint aaPort)
        {
            fixed (uint* aPort = &aaPort)
            {
                if (0 != CpProxyLinnCoUkProxyManager1EndKontrolProductComPort(iHandle, aAsyncHandle, aPort))
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
        /// <param name="aaConnected"></param>
        public unsafe void SyncSetKontrolProductComPort(uint aaConnected)
        {
            {
                CpProxyLinnCoUkProxyManager1SyncSetKontrolProductComPort(iHandle, aaConnected);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetKontrolProductComPort().</remarks>
        /// <param name="aaConnected"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetKontrolProductComPort(uint aaConnected, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginSetKontrolProductComPort(iHandle, aaConnected, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetKontrolProductComPort(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProxyManager1EndSetKontrolProductComPort(iHandle, aAsyncHandle))
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
        /// <param name="aaConnected"></param>
        public unsafe void SyncDiscPlayerConnected(out string aaConnected)
        {
            char* aConnected;
            {
                CpProxyLinnCoUkProxyManager1SyncDiscPlayerConnected(iHandle, &aConnected);
            }
            aaConnected = Marshal.PtrToStringAnsi((IntPtr)aConnected);
            ZappFree(aConnected);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDiscPlayerConnected().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDiscPlayerConnected(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginDiscPlayerConnected(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaConnected"></param>
        public unsafe void EndDiscPlayerConnected(IntPtr aAsyncHandle, out string aaConnected)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaConnected"></param>
        public unsafe void SyncSetDiscPlayerConnected(string aaConnected)
        {
            char* aConnected = (char*)Marshal.StringToHGlobalAnsi(aaConnected);
            {
                CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerConnected(iHandle, aConnected);
            }
            Marshal.FreeHGlobal((IntPtr)aConnected);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDiscPlayerConnected().</remarks>
        /// <param name="aaConnected"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetDiscPlayerConnected(string aaConnected, CallbackAsyncComplete aCallback)
        {
            char* aConnected = (char*)Marshal.StringToHGlobalAnsi(aaConnected);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerConnected(iHandle, aConnected, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aConnected);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetDiscPlayerConnected(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProxyManager1EndSetDiscPlayerConnected(iHandle, aAsyncHandle))
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
        /// <param name="aaPort"></param>
        public unsafe void SyncDiscPlayerComPort(out uint aaPort)
        {
            fixed (uint* aPort = &aaPort)
            {
                CpProxyLinnCoUkProxyManager1SyncDiscPlayerComPort(iHandle, aPort);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDiscPlayerComPort().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDiscPlayerComPort(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginDiscPlayerComPort(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaPort"></param>
        public unsafe void EndDiscPlayerComPort(IntPtr aAsyncHandle, out uint aaPort)
        {
            fixed (uint* aPort = &aaPort)
            {
                if (0 != CpProxyLinnCoUkProxyManager1EndDiscPlayerComPort(iHandle, aAsyncHandle, aPort))
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
        /// <param name="aaConnected"></param>
        public unsafe void SyncSetDiscPlayerComPort(uint aaConnected)
        {
            {
                CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerComPort(iHandle, aaConnected);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDiscPlayerComPort().</remarks>
        /// <param name="aaConnected"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetDiscPlayerComPort(uint aaConnected, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerComPort(iHandle, aaConnected, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetDiscPlayerComPort(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProxyManager1EndSetDiscPlayerComPort(iHandle, aAsyncHandle))
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
        /// <param name="aaResult"></param>
        public unsafe void SyncTestKontrolProductConnection(out bool aaResult)
        {
            uint aResult;
            {
                CpProxyLinnCoUkProxyManager1SyncTestKontrolProductConnection(iHandle, &aResult);
            }
            aaResult = (aResult != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTestKontrolProductConnection().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginTestKontrolProductConnection(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginTestKontrolProductConnection(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaResult"></param>
        public unsafe void EndTestKontrolProductConnection(IntPtr aAsyncHandle, out bool aaResult)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaResult"></param>
        public unsafe void SyncTestDiscPlayerConnection(out bool aaResult)
        {
            uint aResult;
            {
                CpProxyLinnCoUkProxyManager1SyncTestDiscPlayerConnection(iHandle, &aResult);
            }
            aaResult = (aResult != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTestDiscPlayerConnection().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginTestDiscPlayerConnection(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProxyManager1BeginTestDiscPlayerConnection(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaResult"></param>
        public unsafe void EndTestDiscPlayerConnection(IntPtr aAsyncHandle, out bool aaResult)
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

        /// <summary>
        /// Set a delegate to be run when the KontrolProductConnected state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProxyManager1 instance will not overlap.</remarks>
        /// <param name="aKontrolProductConnectedChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the KontrolProductComPort state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProxyManager1 instance will not overlap.</remarks>
        /// <param name="aKontrolProductComPortChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the DiscPlayerConnected state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProxyManager1 instance will not overlap.</remarks>
        /// <param name="aDiscPlayerConnectedChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the DiscPlayerComPort state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProxyManager1 instance will not overlap.</remarks>
        /// <param name="aDiscPlayerComPortChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Query the value of the KontrolProductConnected property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aKontrolProductConnected">Will be set to the value of the property</param>
        public unsafe void PropertyKontrolProductConnected(out string aKontrolProductConnected)
        {
            char* ptr;
            CpProxyLinnCoUkProxyManager1PropertyKontrolProductConnected(iHandle, &ptr);
            aKontrolProductConnected = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the KontrolProductComPort property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aKontrolProductComPort">Will be set to the value of the property</param>
        public unsafe void PropertyKontrolProductComPort(out uint aKontrolProductComPort)
        {
            fixed (uint* kontrolProductComPort = &aKontrolProductComPort)
            {
                CpProxyLinnCoUkProxyManager1PropertyKontrolProductComPort(iHandle, kontrolProductComPort);
            }
        }

        /// <summary>
        /// Query the value of the DiscPlayerConnected property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDiscPlayerConnected">Will be set to the value of the property</param>
        public unsafe void PropertyDiscPlayerConnected(out string aDiscPlayerConnected)
        {
            char* ptr;
            CpProxyLinnCoUkProxyManager1PropertyDiscPlayerConnected(iHandle, &ptr);
            aDiscPlayerConnected = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the DiscPlayerComPort property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDiscPlayerComPort">Will be set to the value of the property</param>
        public unsafe void PropertyDiscPlayerComPort(out uint aDiscPlayerComPort)
        {
            fixed (uint* discPlayerComPort = &aDiscPlayerComPort)
            {
                CpProxyLinnCoUkProxyManager1PropertyDiscPlayerComPort(iHandle, discPlayerComPort);
            }
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                CpProxyLinnCoUkProxyManager1Destroy(iHandle);
                iHandle = IntPtr.Zero;
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

