using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkDiagnostics1 : ICpProxy, IDisposable
    {
        void SyncEcho(string aaIn, out string aaOut);
        void BeginEcho(string aaIn, CpProxy.CallbackAsyncComplete aCallback);
        void EndEcho(uint aAsyncHandle, out string aaOut);
        void SyncElfFile(out string aaElfFile);
        void BeginElfFile(CpProxy.CallbackAsyncComplete aCallback);
        void EndElfFile(uint aAsyncHandle, out string aaElfFile);
        void SyncElfFingerprint(out string aaElfFileFingerprint);
        void BeginElfFingerprint(CpProxy.CallbackAsyncComplete aCallback);
        void EndElfFingerprint(uint aAsyncHandle, out string aaElfFileFingerprint);
        void SyncCrashDataStatus(out string aaCrashDataStatus);
        void BeginCrashDataStatus(CpProxy.CallbackAsyncComplete aCallback);
        void EndCrashDataStatus(uint aAsyncHandle, out string aaCrashDataStatus);
        void SyncCrashDataFetch(out string aaCrashData);
        void BeginCrashDataFetch(CpProxy.CallbackAsyncComplete aCallback);
        void EndCrashDataFetch(uint aAsyncHandle, out string aaCrashData);
        void SyncCrashDataClear();
        void BeginCrashDataClear(CpProxy.CallbackAsyncComplete aCallback);
        void EndCrashDataClear(uint aAsyncHandle);
        void SyncSysLog(out string aaSysLog);
        void BeginSysLog(CpProxy.CallbackAsyncComplete aCallback);
        void EndSysLog(uint aAsyncHandle, out string aaSysLog);
        void SyncDiagnostic(string aaDiagnosticType, out string aaDiagnosticInfo);
        void BeginDiagnostic(string aaDiagnosticType, CpProxy.CallbackAsyncComplete aCallback);
        void EndDiagnostic(uint aAsyncHandle, out string aaDiagnosticInfo);
        void SyncStateVariable(out uint aaStateVariable);
        void BeginStateVariable(CpProxy.CallbackAsyncComplete aCallback);
        void EndStateVariable(uint aAsyncHandle, out uint aaStateVariable);
        void SyncSetStateVariable(uint aaStateVariable);
        void BeginSetStateVariable(uint aaStateVariable, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStateVariable(uint aAsyncHandle);
        void SyncStateVariablePeriod(out uint aaPeriod);
        void BeginStateVariablePeriod(CpProxy.CallbackAsyncComplete aCallback);
        void EndStateVariablePeriod(uint aAsyncHandle, out uint aaPeriod);
        void SyncSetStateVariablePeriod(uint aaPeriod);
        void BeginSetStateVariablePeriod(uint aaPeriod, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStateVariablePeriod(uint aAsyncHandle);
        void SyncReboot(uint aaDelay);
        void BeginReboot(uint aaDelay, CpProxy.CallbackAsyncComplete aCallback);
        void EndReboot(uint aAsyncHandle);

        void SetPropertyaStateVariableChanged(CpProxy.CallbackPropertyChanged aaStateVariableChanged);
        void PropertyaStateVariable(out uint aaStateVariable);
    }

    /// <summary>
    /// Proxy for the linn.co.uk:Diagnostics:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkDiagnostics1 : CpProxy, IDisposable, ICpProxyLinnCoUkDiagnostics1
    {
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern uint CpProxyLinnCoUkDiagnostics1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern void CpProxyLinnCoUkDiagnostics1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncEcho(uint aHandle, char* aaIn, char** aaOut);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginEcho(uint aHandle, char* aaIn, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndEcho(uint aHandle, uint aAsync, char** aaOut);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncElfFile(uint aHandle, char** aaElfFile);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginElfFile(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndElfFile(uint aHandle, uint aAsync, char** aaElfFile);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncElfFingerprint(uint aHandle, char** aaElfFileFingerprint);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginElfFingerprint(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndElfFingerprint(uint aHandle, uint aAsync, char** aaElfFileFingerprint);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncCrashDataStatus(uint aHandle, char** aaCrashDataStatus);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginCrashDataStatus(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndCrashDataStatus(uint aHandle, uint aAsync, char** aaCrashDataStatus);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncCrashDataFetch(uint aHandle, char** aaCrashData, uint* aaCrashDataLen);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginCrashDataFetch(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndCrashDataFetch(uint aHandle, uint aAsync, char** aaCrashData, uint* aaCrashDataLen);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncCrashDataClear(uint aHandle);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginCrashDataClear(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndCrashDataClear(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncSysLog(uint aHandle, char** aaSysLog, uint* aaSysLogLen);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginSysLog(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndSysLog(uint aHandle, uint aAsync, char** aaSysLog, uint* aaSysLogLen);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncDiagnostic(uint aHandle, char* aaDiagnosticType, char** aaDiagnosticInfo);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginDiagnostic(uint aHandle, char* aaDiagnosticType, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndDiagnostic(uint aHandle, uint aAsync, char** aaDiagnosticInfo);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncStateVariable(uint aHandle, uint* aaStateVariable);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginStateVariable(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndStateVariable(uint aHandle, uint aAsync, uint* aaStateVariable);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncSetStateVariable(uint aHandle, uint aaStateVariable);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginSetStateVariable(uint aHandle, uint aaStateVariable, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndSetStateVariable(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncStateVariablePeriod(uint aHandle, uint* aaPeriod);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginStateVariablePeriod(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndStateVariablePeriod(uint aHandle, uint aAsync, uint* aaPeriod);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncSetStateVariablePeriod(uint aHandle, uint aaPeriod);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginSetStateVariablePeriod(uint aHandle, uint aaPeriod, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndSetStateVariablePeriod(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncReboot(uint aHandle, uint aaDelay);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginReboot(uint aHandle, uint aaDelay, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndReboot(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern void CpProxyLinnCoUkDiagnostics1SetPropertyaStateVariableChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1PropertyaStateVariable(uint aHandle, uint* aaStateVariable);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iaStateVariableChanged;
        private Callback iCallbackaStateVariableChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkDiagnostics1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkDiagnostics1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIn"></param>
        /// <param name="aaOut"></param>
        public unsafe void SyncEcho(string aaIn, out string aaOut)
        {
            char* aIn = (char*)Marshal.StringToHGlobalAnsi(aaIn);
            char* aOut;
            {
                CpProxyLinnCoUkDiagnostics1SyncEcho(iHandle, aIn, &aOut);
            }
            Marshal.FreeHGlobal((IntPtr)aIn);
            aaOut = Marshal.PtrToStringAnsi((IntPtr)aOut);
            ZappFree(aOut);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEcho().</remarks>
        /// <param name="aaIn"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginEcho(string aaIn, CallbackAsyncComplete aCallback)
        {
            char* aIn = (char*)Marshal.StringToHGlobalAnsi(aaIn);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginEcho(iHandle, aIn, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aIn);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaOut"></param>
        public unsafe void EndEcho(uint aAsyncHandle, out string aaOut)
        {
            char* aOut;
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndEcho(iHandle, aAsyncHandle, &aOut))
                {
                    throw(new ProxyError());
                }
            }
            aaOut = Marshal.PtrToStringAnsi((IntPtr)aOut);
            ZappFree(aOut);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaElfFile"></param>
        public unsafe void SyncElfFile(out string aaElfFile)
        {
            char* aElfFile;
            {
                CpProxyLinnCoUkDiagnostics1SyncElfFile(iHandle, &aElfFile);
            }
            aaElfFile = Marshal.PtrToStringAnsi((IntPtr)aElfFile);
            ZappFree(aElfFile);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndElfFile().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginElfFile(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginElfFile(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaElfFile"></param>
        public unsafe void EndElfFile(uint aAsyncHandle, out string aaElfFile)
        {
            char* aElfFile;
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndElfFile(iHandle, aAsyncHandle, &aElfFile))
                {
                    throw(new ProxyError());
                }
            }
            aaElfFile = Marshal.PtrToStringAnsi((IntPtr)aElfFile);
            ZappFree(aElfFile);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaElfFileFingerprint"></param>
        public unsafe void SyncElfFingerprint(out string aaElfFileFingerprint)
        {
            char* aElfFileFingerprint;
            {
                CpProxyLinnCoUkDiagnostics1SyncElfFingerprint(iHandle, &aElfFileFingerprint);
            }
            aaElfFileFingerprint = Marshal.PtrToStringAnsi((IntPtr)aElfFileFingerprint);
            ZappFree(aElfFileFingerprint);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndElfFingerprint().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginElfFingerprint(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginElfFingerprint(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaElfFileFingerprint"></param>
        public unsafe void EndElfFingerprint(uint aAsyncHandle, out string aaElfFileFingerprint)
        {
            char* aElfFileFingerprint;
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndElfFingerprint(iHandle, aAsyncHandle, &aElfFileFingerprint))
                {
                    throw(new ProxyError());
                }
            }
            aaElfFileFingerprint = Marshal.PtrToStringAnsi((IntPtr)aElfFileFingerprint);
            ZappFree(aElfFileFingerprint);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCrashDataStatus"></param>
        public unsafe void SyncCrashDataStatus(out string aaCrashDataStatus)
        {
            char* aCrashDataStatus;
            {
                CpProxyLinnCoUkDiagnostics1SyncCrashDataStatus(iHandle, &aCrashDataStatus);
            }
            aaCrashDataStatus = Marshal.PtrToStringAnsi((IntPtr)aCrashDataStatus);
            ZappFree(aCrashDataStatus);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCrashDataStatus().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginCrashDataStatus(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginCrashDataStatus(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaCrashDataStatus"></param>
        public unsafe void EndCrashDataStatus(uint aAsyncHandle, out string aaCrashDataStatus)
        {
            char* aCrashDataStatus;
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndCrashDataStatus(iHandle, aAsyncHandle, &aCrashDataStatus))
                {
                    throw(new ProxyError());
                }
            }
            aaCrashDataStatus = Marshal.PtrToStringAnsi((IntPtr)aCrashDataStatus);
            ZappFree(aCrashDataStatus);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCrashData"></param>
        public unsafe void SyncCrashDataFetch(out string aaCrashData)
        {
            char* aCrashData;
            uint aCrashDataLen;
            {
                CpProxyLinnCoUkDiagnostics1SyncCrashDataFetch(iHandle, &aCrashData, &aCrashDataLen);
            }
            aaCrashData = Marshal.PtrToStringAnsi((IntPtr)aCrashData, (int)aCrashDataLen);
            ZappFree(aCrashData);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCrashDataFetch().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginCrashDataFetch(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginCrashDataFetch(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaCrashData"></param>
        public unsafe void EndCrashDataFetch(uint aAsyncHandle, out string aaCrashData)
        {
            char* aCrashData;
            uint aCrashDataLen;
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndCrashDataFetch(iHandle, aAsyncHandle, &aCrashData, &aCrashDataLen))
                {
                    throw(new ProxyError());
                }
            }
            aaCrashData = Marshal.PtrToStringAnsi((IntPtr)aCrashData, (int)aCrashDataLen);
            ZappFree(aCrashData);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncCrashDataClear()
        {
            {
                CpProxyLinnCoUkDiagnostics1SyncCrashDataClear(iHandle);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCrashDataClear().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginCrashDataClear(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginCrashDataClear(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndCrashDataClear(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndCrashDataClear(iHandle, aAsyncHandle))
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
        /// <param name="aaSysLog"></param>
        public unsafe void SyncSysLog(out string aaSysLog)
        {
            char* aSysLog;
            uint aSysLogLen;
            {
                CpProxyLinnCoUkDiagnostics1SyncSysLog(iHandle, &aSysLog, &aSysLogLen);
            }
            aaSysLog = Marshal.PtrToStringAnsi((IntPtr)aSysLog, (int)aSysLogLen);
            ZappFree(aSysLog);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSysLog().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSysLog(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginSysLog(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSysLog"></param>
        public unsafe void EndSysLog(uint aAsyncHandle, out string aaSysLog)
        {
            char* aSysLog;
            uint aSysLogLen;
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndSysLog(iHandle, aAsyncHandle, &aSysLog, &aSysLogLen))
                {
                    throw(new ProxyError());
                }
            }
            aaSysLog = Marshal.PtrToStringAnsi((IntPtr)aSysLog, (int)aSysLogLen);
            ZappFree(aSysLog);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDiagnosticType"></param>
        /// <param name="aaDiagnosticInfo"></param>
        public unsafe void SyncDiagnostic(string aaDiagnosticType, out string aaDiagnosticInfo)
        {
            char* aDiagnosticType = (char*)Marshal.StringToHGlobalAnsi(aaDiagnosticType);
            char* aDiagnosticInfo;
            {
                CpProxyLinnCoUkDiagnostics1SyncDiagnostic(iHandle, aDiagnosticType, &aDiagnosticInfo);
            }
            Marshal.FreeHGlobal((IntPtr)aDiagnosticType);
            aaDiagnosticInfo = Marshal.PtrToStringAnsi((IntPtr)aDiagnosticInfo);
            ZappFree(aDiagnosticInfo);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDiagnostic().</remarks>
        /// <param name="aaDiagnosticType"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDiagnostic(string aaDiagnosticType, CallbackAsyncComplete aCallback)
        {
            char* aDiagnosticType = (char*)Marshal.StringToHGlobalAnsi(aaDiagnosticType);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginDiagnostic(iHandle, aDiagnosticType, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aDiagnosticType);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaDiagnosticInfo"></param>
        public unsafe void EndDiagnostic(uint aAsyncHandle, out string aaDiagnosticInfo)
        {
            char* aDiagnosticInfo;
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndDiagnostic(iHandle, aAsyncHandle, &aDiagnosticInfo))
                {
                    throw(new ProxyError());
                }
            }
            aaDiagnosticInfo = Marshal.PtrToStringAnsi((IntPtr)aDiagnosticInfo);
            ZappFree(aDiagnosticInfo);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStateVariable"></param>
        public unsafe void SyncStateVariable(out uint aaStateVariable)
        {
            fixed (uint* aStateVariable = &aaStateVariable)
            {
                CpProxyLinnCoUkDiagnostics1SyncStateVariable(iHandle, aStateVariable);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStateVariable().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStateVariable(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginStateVariable(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaStateVariable"></param>
        public unsafe void EndStateVariable(uint aAsyncHandle, out uint aaStateVariable)
        {
            fixed (uint* aStateVariable = &aaStateVariable)
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndStateVariable(iHandle, aAsyncHandle, aStateVariable))
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
        /// <param name="aaStateVariable"></param>
        public unsafe void SyncSetStateVariable(uint aaStateVariable)
        {
            {
                CpProxyLinnCoUkDiagnostics1SyncSetStateVariable(iHandle, aaStateVariable);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStateVariable().</remarks>
        /// <param name="aaStateVariable"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetStateVariable(uint aaStateVariable, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginSetStateVariable(iHandle, aaStateVariable, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetStateVariable(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndSetStateVariable(iHandle, aAsyncHandle))
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
        /// <param name="aaPeriod"></param>
        public unsafe void SyncStateVariablePeriod(out uint aaPeriod)
        {
            fixed (uint* aPeriod = &aaPeriod)
            {
                CpProxyLinnCoUkDiagnostics1SyncStateVariablePeriod(iHandle, aPeriod);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStateVariablePeriod().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStateVariablePeriod(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginStateVariablePeriod(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaPeriod"></param>
        public unsafe void EndStateVariablePeriod(uint aAsyncHandle, out uint aaPeriod)
        {
            fixed (uint* aPeriod = &aaPeriod)
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndStateVariablePeriod(iHandle, aAsyncHandle, aPeriod))
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
        /// <param name="aaPeriod"></param>
        public unsafe void SyncSetStateVariablePeriod(uint aaPeriod)
        {
            {
                CpProxyLinnCoUkDiagnostics1SyncSetStateVariablePeriod(iHandle, aaPeriod);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStateVariablePeriod().</remarks>
        /// <param name="aaPeriod"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetStateVariablePeriod(uint aaPeriod, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginSetStateVariablePeriod(iHandle, aaPeriod, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetStateVariablePeriod(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndSetStateVariablePeriod(iHandle, aAsyncHandle))
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
        public unsafe void SyncReboot(uint aaDelay)
        {
            {
                CpProxyLinnCoUkDiagnostics1SyncReboot(iHandle, aaDelay);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndReboot().</remarks>
        /// <param name="aaDelay"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginReboot(uint aaDelay, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginReboot(iHandle, aaDelay, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndReboot(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkDiagnostics1EndReboot(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the aStateVariable state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDiagnostics1 instance will not overlap.</remarks>
        /// <param name="aaStateVariableChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyaStateVariableChanged(CallbackPropertyChanged aaStateVariableChanged)
        {
            iaStateVariableChanged = aaStateVariableChanged;
            iCallbackaStateVariableChanged = new Callback(PropertyaStateVariableChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDiagnostics1SetPropertyaStateVariableChanged(iHandle, iCallbackaStateVariableChanged, ptr);
        }

        private void PropertyaStateVariableChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDiagnostics1 self = (CpProxyLinnCoUkDiagnostics1)gch.Target;
            self.iaStateVariableChanged();
        }

        /// <summary>
        /// Query the value of the aStateVariable property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aaStateVariable">Will be set to the value of the property</param>
        public unsafe void PropertyaStateVariable(out uint aaStateVariable)
        {
            fixed (uint* aStateVariable = &aaStateVariable)
            {
                CpProxyLinnCoUkDiagnostics1PropertyaStateVariable(iHandle, aStateVariable);
            }
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkDiagnostics1()
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
                CpProxyLinnCoUkDiagnostics1Destroy(iHandle);
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

