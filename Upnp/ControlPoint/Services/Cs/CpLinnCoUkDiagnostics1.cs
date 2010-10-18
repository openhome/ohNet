using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkDiagnostics1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern IntPtr CpProxyLinnCoUkDiagnostics1Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern void CpProxyLinnCoUkDiagnostics1Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncEcho(IntPtr aHandle, char* aaIn, char** aaOut);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginEcho(IntPtr aHandle, char* aaIn, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndEcho(IntPtr aHandle, IntPtr aAsync, char** aaOut);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncElfFile(IntPtr aHandle, char** aaElfFile);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginElfFile(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndElfFile(IntPtr aHandle, IntPtr aAsync, char** aaElfFile);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncElfFingerprint(IntPtr aHandle, char** aaElfFileFingerprint);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginElfFingerprint(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndElfFingerprint(IntPtr aHandle, IntPtr aAsync, char** aaElfFileFingerprint);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncCrashDataStatus(IntPtr aHandle, char** aaCrashDataStatus);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginCrashDataStatus(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndCrashDataStatus(IntPtr aHandle, IntPtr aAsync, char** aaCrashDataStatus);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncCrashDataFetch(IntPtr aHandle, char** aaCrashData, uint* aaCrashDataLen);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginCrashDataFetch(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndCrashDataFetch(IntPtr aHandle, IntPtr aAsync, char** aaCrashData, uint* aaCrashDataLen);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncCrashDataClear(IntPtr aHandle);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginCrashDataClear(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndCrashDataClear(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncSysLog(IntPtr aHandle, char** aaSysLog, uint* aaSysLogLen);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginSysLog(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndSysLog(IntPtr aHandle, IntPtr aAsync, char** aaSysLog, uint* aaSysLogLen);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncDiagnostic(IntPtr aHandle, char* aaDiagnosticType, char** aaDiagnosticInfo);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginDiagnostic(IntPtr aHandle, char* aaDiagnosticType, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndDiagnostic(IntPtr aHandle, IntPtr aAsync, char** aaDiagnosticInfo);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncStateVariable(IntPtr aHandle, uint* aaStateVariable);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginStateVariable(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndStateVariable(IntPtr aHandle, IntPtr aAsync, uint* aaStateVariable);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncSetStateVariable(IntPtr aHandle, uint aaStateVariable);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginSetStateVariable(IntPtr aHandle, uint aaStateVariable, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndSetStateVariable(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncStateVariablePeriod(IntPtr aHandle, uint* aaPeriod);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginStateVariablePeriod(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndStateVariablePeriod(IntPtr aHandle, IntPtr aAsync, uint* aaPeriod);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncSetStateVariablePeriod(IntPtr aHandle, uint aaPeriod);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginSetStateVariablePeriod(IntPtr aHandle, uint aaPeriod, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndSetStateVariablePeriod(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1SyncReboot(IntPtr aHandle, uint aaDelay);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1BeginReboot(IntPtr aHandle, uint aaDelay, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe int CpProxyLinnCoUkDiagnostics1EndReboot(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern void CpProxyLinnCoUkDiagnostics1SetPropertyaStateVariableChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDiagnostics1")]
        static extern unsafe void CpProxyLinnCoUkDiagnostics1PropertyaStateVariable(IntPtr aHandle, uint* aaStateVariable);
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

        public unsafe void EndEcho(IntPtr aAsyncHandle, out string aaOut)
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

        public unsafe void EndElfFile(IntPtr aAsyncHandle, out string aaElfFile)
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

        public unsafe void EndElfFingerprint(IntPtr aAsyncHandle, out string aaElfFileFingerprint)
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

        public unsafe void EndCrashDataStatus(IntPtr aAsyncHandle, out string aaCrashDataStatus)
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

        public unsafe void EndCrashDataFetch(IntPtr aAsyncHandle, out string aaCrashData)
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

        public unsafe void EndCrashDataClear(IntPtr aAsyncHandle)
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

        public unsafe void EndSysLog(IntPtr aAsyncHandle, out string aaSysLog)
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

        public unsafe void EndDiagnostic(IntPtr aAsyncHandle, out string aaDiagnosticInfo)
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

        public unsafe void EndStateVariable(IntPtr aAsyncHandle, out uint aaStateVariable)
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

        public unsafe void EndSetStateVariable(IntPtr aAsyncHandle)
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

        public unsafe void EndStateVariablePeriod(IntPtr aAsyncHandle, out uint aaPeriod)
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

        public unsafe void EndSetStateVariablePeriod(IntPtr aAsyncHandle)
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

        public unsafe void EndReboot(IntPtr aAsyncHandle)
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
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
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

