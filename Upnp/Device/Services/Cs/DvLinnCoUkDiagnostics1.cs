using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkDiagnostics1 : IDisposable
    {
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern uint DvServiceLinnCoUkDiagnostics1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern unsafe int DvServiceLinnCoUkDiagnostics1SetPropertyaStateVariable(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern unsafe void DvServiceLinnCoUkDiagnostics1GetPropertyaStateVariable(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionEcho(uint aHandle, CallbackEcho aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionElfFile(uint aHandle, CallbackElfFile aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionElfFingerprint(uint aHandle, CallbackElfFingerprint aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionCrashDataStatus(uint aHandle, CallbackCrashDataStatus aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionCrashDataFetch(uint aHandle, CallbackCrashDataFetch aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionCrashDataClear(uint aHandle, CallbackCrashDataClear aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionSysLog(uint aHandle, CallbackSysLog aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionDiagnostic(uint aHandle, CallbackDiagnostic aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionStateVariable(uint aHandle, CallbackStateVariable aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionSetStateVariable(uint aHandle, CallbackSetStateVariable aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionStateVariablePeriod(uint aHandle, CallbackStateVariablePeriod aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionSetStateVariablePeriod(uint aHandle, CallbackSetStateVariablePeriod aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvServiceLinnCoUkDiagnostics1EnableActionReboot(uint aHandle, CallbackReboot aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackEcho(IntPtr aPtr, uint aVersion, char* aaIn, char** aaOut);
        private unsafe delegate int CallbackElfFile(IntPtr aPtr, uint aVersion, char** aaElfFile);
        private unsafe delegate int CallbackElfFingerprint(IntPtr aPtr, uint aVersion, char** aaElfFileFingerprint);
        private unsafe delegate int CallbackCrashDataStatus(IntPtr aPtr, uint aVersion, char** aaCrashDataStatus);
        private unsafe delegate int CallbackCrashDataFetch(IntPtr aPtr, uint aVersion, char** aaCrashData, int* aaCrashDataLen);
        private unsafe delegate int CallbackCrashDataClear(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackSysLog(IntPtr aPtr, uint aVersion, char** aaSysLog, int* aaSysLogLen);
        private unsafe delegate int CallbackDiagnostic(IntPtr aPtr, uint aVersion, char* aaDiagnosticType, char** aaDiagnosticInfo);
        private unsafe delegate int CallbackStateVariable(IntPtr aPtr, uint aVersion, uint* aaStateVariable);
        private unsafe delegate int CallbackSetStateVariable(IntPtr aPtr, uint aVersion, uint aaStateVariable);
        private unsafe delegate int CallbackStateVariablePeriod(IntPtr aPtr, uint aVersion, uint* aaPeriod);
        private unsafe delegate int CallbackSetStateVariablePeriod(IntPtr aPtr, uint aVersion, uint aaPeriod);
        private unsafe delegate int CallbackReboot(IntPtr aPtr, uint aVersion, uint aaDelay);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackEcho iCallbackEcho;
        private CallbackElfFile iCallbackElfFile;
        private CallbackElfFingerprint iCallbackElfFingerprint;
        private CallbackCrashDataStatus iCallbackCrashDataStatus;
        private CallbackCrashDataFetch iCallbackCrashDataFetch;
        private CallbackCrashDataClear iCallbackCrashDataClear;
        private CallbackSysLog iCallbackSysLog;
        private CallbackDiagnostic iCallbackDiagnostic;
        private CallbackStateVariable iCallbackStateVariable;
        private CallbackSetStateVariable iCallbackSetStateVariable;
        private CallbackStateVariablePeriod iCallbackStateVariablePeriod;
        private CallbackSetStateVariablePeriod iCallbackSetStateVariablePeriod;
        private CallbackReboot iCallbackReboot;

        public DvServiceLinnCoUkDiagnostics1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkDiagnostics1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyaStateVariable(uint aValue)
        {
            if (0 != DvServiceLinnCoUkDiagnostics1SetPropertyaStateVariable(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyaStateVariable(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkDiagnostics1GetPropertyaStateVariable(iHandle, value);
            }
        }

        protected unsafe void EnableActionEcho()
        {
            iCallbackEcho = new CallbackEcho(DoEcho);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionEcho(iHandle, iCallbackEcho, ptr);
        }

        protected unsafe void EnableActionElfFile()
        {
            iCallbackElfFile = new CallbackElfFile(DoElfFile);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionElfFile(iHandle, iCallbackElfFile, ptr);
        }

        protected unsafe void EnableActionElfFingerprint()
        {
            iCallbackElfFingerprint = new CallbackElfFingerprint(DoElfFingerprint);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionElfFingerprint(iHandle, iCallbackElfFingerprint, ptr);
        }

        protected unsafe void EnableActionCrashDataStatus()
        {
            iCallbackCrashDataStatus = new CallbackCrashDataStatus(DoCrashDataStatus);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionCrashDataStatus(iHandle, iCallbackCrashDataStatus, ptr);
        }

        protected unsafe void EnableActionCrashDataFetch()
        {
            iCallbackCrashDataFetch = new CallbackCrashDataFetch(DoCrashDataFetch);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionCrashDataFetch(iHandle, iCallbackCrashDataFetch, ptr);
        }

        protected unsafe void EnableActionCrashDataClear()
        {
            iCallbackCrashDataClear = new CallbackCrashDataClear(DoCrashDataClear);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionCrashDataClear(iHandle, iCallbackCrashDataClear, ptr);
        }

        protected unsafe void EnableActionSysLog()
        {
            iCallbackSysLog = new CallbackSysLog(DoSysLog);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionSysLog(iHandle, iCallbackSysLog, ptr);
        }

        protected unsafe void EnableActionDiagnostic()
        {
            iCallbackDiagnostic = new CallbackDiagnostic(DoDiagnostic);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionDiagnostic(iHandle, iCallbackDiagnostic, ptr);
        }

        protected unsafe void EnableActionStateVariable()
        {
            iCallbackStateVariable = new CallbackStateVariable(DoStateVariable);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionStateVariable(iHandle, iCallbackStateVariable, ptr);
        }

        protected unsafe void EnableActionSetStateVariable()
        {
            iCallbackSetStateVariable = new CallbackSetStateVariable(DoSetStateVariable);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionSetStateVariable(iHandle, iCallbackSetStateVariable, ptr);
        }

        protected unsafe void EnableActionStateVariablePeriod()
        {
            iCallbackStateVariablePeriod = new CallbackStateVariablePeriod(DoStateVariablePeriod);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionStateVariablePeriod(iHandle, iCallbackStateVariablePeriod, ptr);
        }

        protected unsafe void EnableActionSetStateVariablePeriod()
        {
            iCallbackSetStateVariablePeriod = new CallbackSetStateVariablePeriod(DoSetStateVariablePeriod);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionSetStateVariablePeriod(iHandle, iCallbackSetStateVariablePeriod, ptr);
        }

        protected unsafe void EnableActionReboot()
        {
            iCallbackReboot = new CallbackReboot(DoReboot);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDiagnostics1EnableActionReboot(iHandle, iCallbackReboot, ptr);
        }

        protected virtual void Echo(uint aVersion, string aaIn, out string aaOut)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void ElfFile(uint aVersion, out string aaElfFile)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void ElfFingerprint(uint aVersion, out string aaElfFileFingerprint)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void CrashDataStatus(uint aVersion, out string aaCrashDataStatus)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void CrashDataFetch(uint aVersion, out string aaCrashData)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void CrashDataClear(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SysLog(uint aVersion, out string aaSysLog)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Diagnostic(uint aVersion, string aaDiagnosticType, out string aaDiagnosticInfo)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StateVariable(uint aVersion, out uint aaStateVariable)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetStateVariable(uint aVersion, uint aaStateVariable)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StateVariablePeriod(uint aVersion, out uint aaPeriod)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetStateVariablePeriod(uint aVersion, uint aaPeriod)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Reboot(uint aVersion, uint aaDelay)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoEcho(IntPtr aPtr, uint aVersion, char* aaIn, char** aaOut)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            string aIn = Marshal.PtrToStringAnsi((IntPtr)aaIn);
            string aOut;
            self.Echo(aVersion, aIn, out aOut);
            *aaOut = (char*)Marshal.StringToHGlobalAnsi(aOut).ToPointer();
            return 0;
        }

        private static unsafe int DoElfFile(IntPtr aPtr, uint aVersion, char** aaElfFile)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            string aElfFile;
            self.ElfFile(aVersion, out aElfFile);
            *aaElfFile = (char*)Marshal.StringToHGlobalAnsi(aElfFile).ToPointer();
            return 0;
        }

        private static unsafe int DoElfFingerprint(IntPtr aPtr, uint aVersion, char** aaElfFileFingerprint)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            string aElfFileFingerprint;
            self.ElfFingerprint(aVersion, out aElfFileFingerprint);
            *aaElfFileFingerprint = (char*)Marshal.StringToHGlobalAnsi(aElfFileFingerprint).ToPointer();
            return 0;
        }

        private static unsafe int DoCrashDataStatus(IntPtr aPtr, uint aVersion, char** aaCrashDataStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            string aCrashDataStatus;
            self.CrashDataStatus(aVersion, out aCrashDataStatus);
            *aaCrashDataStatus = (char*)Marshal.StringToHGlobalAnsi(aCrashDataStatus).ToPointer();
            return 0;
        }

        private static unsafe int DoCrashDataFetch(IntPtr aPtr, uint aVersion, char** aaCrashData, int* aaCrashDataLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            string aCrashData;
            self.CrashDataFetch(aVersion, out aCrashData);
            *aaCrashData = (char*)Marshal.StringToHGlobalAnsi(aCrashData).ToPointer();
            *aaCrashDataLen = aCrashData.Length;
            return 0;
        }

        private static unsafe int DoCrashDataClear(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            self.CrashDataClear(aVersion);
            return 0;
        }

        private static unsafe int DoSysLog(IntPtr aPtr, uint aVersion, char** aaSysLog, int* aaSysLogLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            string aSysLog;
            self.SysLog(aVersion, out aSysLog);
            *aaSysLog = (char*)Marshal.StringToHGlobalAnsi(aSysLog).ToPointer();
            *aaSysLogLen = aSysLog.Length;
            return 0;
        }

        private static unsafe int DoDiagnostic(IntPtr aPtr, uint aVersion, char* aaDiagnosticType, char** aaDiagnosticInfo)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            string aDiagnosticType = Marshal.PtrToStringAnsi((IntPtr)aaDiagnosticType);
            string aDiagnosticInfo;
            self.Diagnostic(aVersion, aDiagnosticType, out aDiagnosticInfo);
            *aaDiagnosticInfo = (char*)Marshal.StringToHGlobalAnsi(aDiagnosticInfo).ToPointer();
            return 0;
        }

        private static unsafe int DoStateVariable(IntPtr aPtr, uint aVersion, uint* aaStateVariable)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            uint aStateVariable;
            self.StateVariable(aVersion, out aStateVariable);
            *aaStateVariable = aStateVariable;
            return 0;
        }

        private static unsafe int DoSetStateVariable(IntPtr aPtr, uint aVersion, uint aaStateVariable)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            self.SetStateVariable(aVersion, aaStateVariable);
            return 0;
        }

        private static unsafe int DoStateVariablePeriod(IntPtr aPtr, uint aVersion, uint* aaPeriod)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            uint aPeriod;
            self.StateVariablePeriod(aVersion, out aPeriod);
            *aaPeriod = aPeriod;
            return 0;
        }

        private static unsafe int DoSetStateVariablePeriod(IntPtr aPtr, uint aVersion, uint aaPeriod)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            self.SetStateVariablePeriod(aVersion, aaPeriod);
            return 0;
        }

        private static unsafe int DoReboot(IntPtr aPtr, uint aVersion, uint aaDelay)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDiagnostics1 self = (DvServiceLinnCoUkDiagnostics1)gch.Target;
            self.Reboot(aVersion, aaDelay);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkDiagnostics1()
        {
            DoDispose();
        }

        private void DoDispose()
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
            DvServiceLinnCoUkDiagnostics1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

