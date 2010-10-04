using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkDiagnostics1 : CpProxy, IDisposable
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

        public CpProxyLinnCoUkDiagnostics1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkDiagnostics1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

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

        public unsafe void BeginEcho(string aaIn, CallbackAsyncComplete aCallback)
        {
			char* aIn = (char*)Marshal.StringToHGlobalAnsi(aaIn);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginEcho(iHandle, aIn, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aIn);
        }

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

        public unsafe void SyncElfFile(out string aaElfFile)
        {
			char* aElfFile;
			{
				CpProxyLinnCoUkDiagnostics1SyncElfFile(iHandle, &aElfFile);
			}
            aaElfFile = Marshal.PtrToStringAnsi((IntPtr)aElfFile);
            ZappFree(aElfFile);
        }

        public unsafe void BeginElfFile(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginElfFile(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncElfFingerprint(out string aaElfFileFingerprint)
        {
			char* aElfFileFingerprint;
			{
				CpProxyLinnCoUkDiagnostics1SyncElfFingerprint(iHandle, &aElfFileFingerprint);
			}
            aaElfFileFingerprint = Marshal.PtrToStringAnsi((IntPtr)aElfFileFingerprint);
            ZappFree(aElfFileFingerprint);
        }

        public unsafe void BeginElfFingerprint(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginElfFingerprint(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncCrashDataStatus(out string aaCrashDataStatus)
        {
			char* aCrashDataStatus;
			{
				CpProxyLinnCoUkDiagnostics1SyncCrashDataStatus(iHandle, &aCrashDataStatus);
			}
            aaCrashDataStatus = Marshal.PtrToStringAnsi((IntPtr)aCrashDataStatus);
            ZappFree(aCrashDataStatus);
        }

        public unsafe void BeginCrashDataStatus(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginCrashDataStatus(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void BeginCrashDataFetch(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginCrashDataFetch(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncCrashDataClear()
        {
			{
				CpProxyLinnCoUkDiagnostics1SyncCrashDataClear(iHandle);
			}
        }

        public unsafe void BeginCrashDataClear(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginCrashDataClear(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndCrashDataClear(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDiagnostics1EndCrashDataClear(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

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

        public unsafe void BeginSysLog(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginSysLog(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void BeginDiagnostic(string aaDiagnosticType, CallbackAsyncComplete aCallback)
        {
			char* aDiagnosticType = (char*)Marshal.StringToHGlobalAnsi(aaDiagnosticType);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginDiagnostic(iHandle, aDiagnosticType, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aDiagnosticType);
        }

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

        public unsafe void SyncStateVariable(out uint aaStateVariable)
        {
			fixed (uint* aStateVariable = &aaStateVariable)
			{
				CpProxyLinnCoUkDiagnostics1SyncStateVariable(iHandle, aStateVariable);
			}
        }

        public unsafe void BeginStateVariable(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginStateVariable(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncSetStateVariable(uint aaStateVariable)
        {
			{
				CpProxyLinnCoUkDiagnostics1SyncSetStateVariable(iHandle, aaStateVariable);
			}
        }

        public unsafe void BeginSetStateVariable(uint aaStateVariable, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginSetStateVariable(iHandle, aaStateVariable, iActionComplete, ptr);
        }

        public unsafe void EndSetStateVariable(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDiagnostics1EndSetStateVariable(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStateVariablePeriod(out uint aaPeriod)
        {
			fixed (uint* aPeriod = &aaPeriod)
			{
				CpProxyLinnCoUkDiagnostics1SyncStateVariablePeriod(iHandle, aPeriod);
			}
        }

        public unsafe void BeginStateVariablePeriod(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginStateVariablePeriod(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncSetStateVariablePeriod(uint aaPeriod)
        {
			{
				CpProxyLinnCoUkDiagnostics1SyncSetStateVariablePeriod(iHandle, aaPeriod);
			}
        }

        public unsafe void BeginSetStateVariablePeriod(uint aaPeriod, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginSetStateVariablePeriod(iHandle, aaPeriod, iActionComplete, ptr);
        }

        public unsafe void EndSetStateVariablePeriod(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDiagnostics1EndSetStateVariablePeriod(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncReboot(uint aaDelay)
        {
			{
				CpProxyLinnCoUkDiagnostics1SyncReboot(iHandle, aaDelay);
			}
        }

        public unsafe void BeginReboot(uint aaDelay, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDiagnostics1BeginReboot(iHandle, aaDelay, iActionComplete, ptr);
        }

        public unsafe void EndReboot(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDiagnostics1EndReboot(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

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

        public unsafe void PropertyaStateVariable(out uint aaStateVariable)
        {
			fixed (uint* aStateVariable = &aaStateVariable)
			{
	            CpProxyLinnCoUkDiagnostics1PropertyaStateVariable(iHandle, aStateVariable);
			}
        }

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
            CpProxyLinnCoUkDiagnostics1Destroy(handle);
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

