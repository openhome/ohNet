using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkDiagnostics1 : IDisposable
    {

        /// <summary>
        /// Set the value of the aStateVariable property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyaStateVariable(uint aValue);

        /// <summary>
        /// Get a copy of the value of the aStateVariable property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyaStateVariable(out uint aValue);
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Diagnostics:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkDiagnostics1 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern uint DvProviderLinnCoUkDiagnostics1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern unsafe int DvProviderLinnCoUkDiagnostics1SetPropertyaStateVariable(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern unsafe void DvProviderLinnCoUkDiagnostics1GetPropertyaStateVariable(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionEcho(uint aHandle, CallbackEcho aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionElfFile(uint aHandle, CallbackElfFile aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionElfFingerprint(uint aHandle, CallbackElfFingerprint aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataStatus(uint aHandle, CallbackCrashDataStatus aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataFetch(uint aHandle, CallbackCrashDataFetch aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataClear(uint aHandle, CallbackCrashDataClear aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionSysLog(uint aHandle, CallbackSysLog aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionDiagnostic(uint aHandle, CallbackDiagnostic aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionStateVariable(uint aHandle, CallbackStateVariable aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariable(uint aHandle, CallbackSetStateVariable aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionStateVariablePeriod(uint aHandle, CallbackStateVariablePeriod aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariablePeriod(uint aHandle, CallbackSetStateVariablePeriod aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDiagnostics1")]
        static extern void DvProviderLinnCoUkDiagnostics1EnableActionReboot(uint aHandle, CallbackReboot aCallback, IntPtr aPtr);
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkDiagnostics1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkDiagnostics1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the aStateVariable property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyaStateVariable(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkDiagnostics1SetPropertyaStateVariable(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the aStateVariable property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyaStateVariable(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkDiagnostics1GetPropertyaStateVariable(iHandle, value);
            }
        }

        /// <summary>
        /// Signal that the action Echo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoEcho must be overridden if this is called.</remarks>
        protected unsafe void EnableActionEcho()
        {
            iCallbackEcho = new CallbackEcho(DoEcho);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionEcho(iHandle, iCallbackEcho, ptr);
        }

        /// <summary>
        /// Signal that the action ElfFile is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoElfFile must be overridden if this is called.</remarks>
        protected unsafe void EnableActionElfFile()
        {
            iCallbackElfFile = new CallbackElfFile(DoElfFile);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionElfFile(iHandle, iCallbackElfFile, ptr);
        }

        /// <summary>
        /// Signal that the action ElfFingerprint is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoElfFingerprint must be overridden if this is called.</remarks>
        protected unsafe void EnableActionElfFingerprint()
        {
            iCallbackElfFingerprint = new CallbackElfFingerprint(DoElfFingerprint);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionElfFingerprint(iHandle, iCallbackElfFingerprint, ptr);
        }

        /// <summary>
        /// Signal that the action CrashDataStatus is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoCrashDataStatus must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCrashDataStatus()
        {
            iCallbackCrashDataStatus = new CallbackCrashDataStatus(DoCrashDataStatus);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionCrashDataStatus(iHandle, iCallbackCrashDataStatus, ptr);
        }

        /// <summary>
        /// Signal that the action CrashDataFetch is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoCrashDataFetch must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCrashDataFetch()
        {
            iCallbackCrashDataFetch = new CallbackCrashDataFetch(DoCrashDataFetch);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionCrashDataFetch(iHandle, iCallbackCrashDataFetch, ptr);
        }

        /// <summary>
        /// Signal that the action CrashDataClear is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoCrashDataClear must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCrashDataClear()
        {
            iCallbackCrashDataClear = new CallbackCrashDataClear(DoCrashDataClear);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionCrashDataClear(iHandle, iCallbackCrashDataClear, ptr);
        }

        /// <summary>
        /// Signal that the action SysLog is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSysLog must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSysLog()
        {
            iCallbackSysLog = new CallbackSysLog(DoSysLog);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionSysLog(iHandle, iCallbackSysLog, ptr);
        }

        /// <summary>
        /// Signal that the action Diagnostic is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDiagnostic must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDiagnostic()
        {
            iCallbackDiagnostic = new CallbackDiagnostic(DoDiagnostic);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionDiagnostic(iHandle, iCallbackDiagnostic, ptr);
        }

        /// <summary>
        /// Signal that the action StateVariable is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStateVariable must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStateVariable()
        {
            iCallbackStateVariable = new CallbackStateVariable(DoStateVariable);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionStateVariable(iHandle, iCallbackStateVariable, ptr);
        }

        /// <summary>
        /// Signal that the action SetStateVariable is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStateVariable must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStateVariable()
        {
            iCallbackSetStateVariable = new CallbackSetStateVariable(DoSetStateVariable);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariable(iHandle, iCallbackSetStateVariable, ptr);
        }

        /// <summary>
        /// Signal that the action StateVariablePeriod is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStateVariablePeriod must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStateVariablePeriod()
        {
            iCallbackStateVariablePeriod = new CallbackStateVariablePeriod(DoStateVariablePeriod);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionStateVariablePeriod(iHandle, iCallbackStateVariablePeriod, ptr);
        }

        /// <summary>
        /// Signal that the action SetStateVariablePeriod is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStateVariablePeriod must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStateVariablePeriod()
        {
            iCallbackSetStateVariablePeriod = new CallbackSetStateVariablePeriod(DoSetStateVariablePeriod);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariablePeriod(iHandle, iCallbackSetStateVariablePeriod, ptr);
        }

        /// <summary>
        /// Signal that the action Reboot is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoReboot must be overridden if this is called.</remarks>
        protected unsafe void EnableActionReboot()
        {
            iCallbackReboot = new CallbackReboot(DoReboot);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDiagnostics1EnableActionReboot(iHandle, iCallbackReboot, ptr);
        }

        /// <summary>
        /// Echo action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Echo action for the owning device.
        ///
        /// Must be implemented iff EnableActionEcho was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIn"></param>
        /// <param name="aaOut"></param>
        protected virtual void Echo(uint aVersion, string aaIn, out string aaOut)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ElfFile action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ElfFile action for the owning device.
        ///
        /// Must be implemented iff EnableActionElfFile was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaElfFile"></param>
        protected virtual void ElfFile(uint aVersion, out string aaElfFile)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ElfFingerprint action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ElfFingerprint action for the owning device.
        ///
        /// Must be implemented iff EnableActionElfFingerprint was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaElfFileFingerprint"></param>
        protected virtual void ElfFingerprint(uint aVersion, out string aaElfFileFingerprint)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// CrashDataStatus action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// CrashDataStatus action for the owning device.
        ///
        /// Must be implemented iff EnableActionCrashDataStatus was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCrashDataStatus"></param>
        protected virtual void CrashDataStatus(uint aVersion, out string aaCrashDataStatus)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// CrashDataFetch action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// CrashDataFetch action for the owning device.
        ///
        /// Must be implemented iff EnableActionCrashDataFetch was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCrashData"></param>
        protected virtual void CrashDataFetch(uint aVersion, out string aaCrashData)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// CrashDataClear action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// CrashDataClear action for the owning device.
        ///
        /// Must be implemented iff EnableActionCrashDataClear was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void CrashDataClear(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SysLog action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SysLog action for the owning device.
        ///
        /// Must be implemented iff EnableActionSysLog was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSysLog"></param>
        protected virtual void SysLog(uint aVersion, out string aaSysLog)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Diagnostic action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Diagnostic action for the owning device.
        ///
        /// Must be implemented iff EnableActionDiagnostic was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDiagnosticType"></param>
        /// <param name="aaDiagnosticInfo"></param>
        protected virtual void Diagnostic(uint aVersion, string aaDiagnosticType, out string aaDiagnosticInfo)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StateVariable action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StateVariable action for the owning device.
        ///
        /// Must be implemented iff EnableActionStateVariable was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStateVariable"></param>
        protected virtual void StateVariable(uint aVersion, out uint aaStateVariable)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStateVariable action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStateVariable action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStateVariable was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStateVariable"></param>
        protected virtual void SetStateVariable(uint aVersion, uint aaStateVariable)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StateVariablePeriod action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StateVariablePeriod action for the owning device.
        ///
        /// Must be implemented iff EnableActionStateVariablePeriod was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPeriod"></param>
        protected virtual void StateVariablePeriod(uint aVersion, out uint aaPeriod)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStateVariablePeriod action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStateVariablePeriod action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStateVariablePeriod was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPeriod"></param>
        protected virtual void SetStateVariablePeriod(uint aVersion, uint aaPeriod)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Reboot action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Reboot action for the owning device.
        ///
        /// Must be implemented iff EnableActionReboot was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDelay"></param>
        protected virtual void Reboot(uint aVersion, uint aaDelay)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoEcho(IntPtr aPtr, uint aVersion, char* aaIn, char** aaOut)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            string aIn = Marshal.PtrToStringAnsi((IntPtr)aaIn);
            string aOut;
            self.Echo(aVersion, aIn, out aOut);
            *aaOut = (char*)Marshal.StringToHGlobalAnsi(aOut).ToPointer();
            return 0;
        }

        private static unsafe int DoElfFile(IntPtr aPtr, uint aVersion, char** aaElfFile)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            string aElfFile;
            self.ElfFile(aVersion, out aElfFile);
            *aaElfFile = (char*)Marshal.StringToHGlobalAnsi(aElfFile).ToPointer();
            return 0;
        }

        private static unsafe int DoElfFingerprint(IntPtr aPtr, uint aVersion, char** aaElfFileFingerprint)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            string aElfFileFingerprint;
            self.ElfFingerprint(aVersion, out aElfFileFingerprint);
            *aaElfFileFingerprint = (char*)Marshal.StringToHGlobalAnsi(aElfFileFingerprint).ToPointer();
            return 0;
        }

        private static unsafe int DoCrashDataStatus(IntPtr aPtr, uint aVersion, char** aaCrashDataStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            string aCrashDataStatus;
            self.CrashDataStatus(aVersion, out aCrashDataStatus);
            *aaCrashDataStatus = (char*)Marshal.StringToHGlobalAnsi(aCrashDataStatus).ToPointer();
            return 0;
        }

        private static unsafe int DoCrashDataFetch(IntPtr aPtr, uint aVersion, char** aaCrashData, int* aaCrashDataLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            string aCrashData;
            self.CrashDataFetch(aVersion, out aCrashData);
            *aaCrashData = (char*)Marshal.StringToHGlobalAnsi(aCrashData).ToPointer();
            *aaCrashDataLen = aCrashData.Length;
            return 0;
        }

        private static unsafe int DoCrashDataClear(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            self.CrashDataClear(aVersion);
            return 0;
        }

        private static unsafe int DoSysLog(IntPtr aPtr, uint aVersion, char** aaSysLog, int* aaSysLogLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            string aSysLog;
            self.SysLog(aVersion, out aSysLog);
            *aaSysLog = (char*)Marshal.StringToHGlobalAnsi(aSysLog).ToPointer();
            *aaSysLogLen = aSysLog.Length;
            return 0;
        }

        private static unsafe int DoDiagnostic(IntPtr aPtr, uint aVersion, char* aaDiagnosticType, char** aaDiagnosticInfo)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            string aDiagnosticType = Marshal.PtrToStringAnsi((IntPtr)aaDiagnosticType);
            string aDiagnosticInfo;
            self.Diagnostic(aVersion, aDiagnosticType, out aDiagnosticInfo);
            *aaDiagnosticInfo = (char*)Marshal.StringToHGlobalAnsi(aDiagnosticInfo).ToPointer();
            return 0;
        }

        private static unsafe int DoStateVariable(IntPtr aPtr, uint aVersion, uint* aaStateVariable)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            uint aStateVariable;
            self.StateVariable(aVersion, out aStateVariable);
            *aaStateVariable = aStateVariable;
            return 0;
        }

        private static unsafe int DoSetStateVariable(IntPtr aPtr, uint aVersion, uint aaStateVariable)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            self.SetStateVariable(aVersion, aaStateVariable);
            return 0;
        }

        private static unsafe int DoStateVariablePeriod(IntPtr aPtr, uint aVersion, uint* aaPeriod)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            uint aPeriod;
            self.StateVariablePeriod(aVersion, out aPeriod);
            *aaPeriod = aPeriod;
            return 0;
        }

        private static unsafe int DoSetStateVariablePeriod(IntPtr aPtr, uint aVersion, uint aaPeriod)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            self.SetStateVariablePeriod(aVersion, aaPeriod);
            return 0;
        }

        private static unsafe int DoReboot(IntPtr aPtr, uint aVersion, uint aaDelay)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            self.Reboot(aVersion, aaDelay);
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkDiagnostics1()
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
            DvProviderLinnCoUkDiagnostics1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

