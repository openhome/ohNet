using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

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
        uint PropertyaStateVariable();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Diagnostics:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkDiagnostics1 : DvProvider, IDisposable, IDvProviderLinnCoUkDiagnostics1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateEcho;
        private ActionDelegate iDelegateElfFile;
        private ActionDelegate iDelegateElfFingerprint;
        private ActionDelegate iDelegateCrashDataStatus;
        private ActionDelegate iDelegateCrashDataFetch;
        private ActionDelegate iDelegateCrashDataClear;
        private ActionDelegate iDelegateSysLog;
        private ActionDelegate iDelegateDiagnostic;
        private ActionDelegate iDelegateStateVariable;
        private ActionDelegate iDelegateSetStateVariable;
        private ActionDelegate iDelegateStateVariablePeriod;
        private ActionDelegate iDelegateSetStateVariablePeriod;
        private ActionDelegate iDelegateReboot;
        private PropertyUint iPropertyaStateVariable;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkDiagnostics1(DvDevice aDevice)
            : base(aDevice, "linn.co.uk", "Diagnostics", 1)
        {
            iGch = GCHandle.Alloc(this);
            iPropertyaStateVariable = new PropertyUint(new ParameterUint("aStateVariable"));
            AddProperty(iPropertyaStateVariable);
        }

        /// <summary>
        /// Set the value of the aStateVariable property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyaStateVariable(uint aValue)
        {
            return SetPropertyUint(iPropertyaStateVariable, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the aStateVariable property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyaStateVariable()
        {
            return iPropertyaStateVariable.Value();
        }

        /// <summary>
        /// Signal that the action Echo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Echo must be overridden if this is called.</remarks>
        protected void EnableActionEcho()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Echo");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("aIn", allowedValues));
            action.AddOutputParameter(new ParameterString("aOut", allowedValues));
            iDelegateEcho = new ActionDelegate(DoEcho);
            EnableAction(action, iDelegateEcho, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ElfFile is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ElfFile must be overridden if this is called.</remarks>
        protected void EnableActionElfFile()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ElfFile");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("aElfFile", allowedValues));
            iDelegateElfFile = new ActionDelegate(DoElfFile);
            EnableAction(action, iDelegateElfFile, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ElfFingerprint is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ElfFingerprint must be overridden if this is called.</remarks>
        protected void EnableActionElfFingerprint()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ElfFingerprint");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("aElfFileFingerprint", allowedValues));
            iDelegateElfFingerprint = new ActionDelegate(DoElfFingerprint);
            EnableAction(action, iDelegateElfFingerprint, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action CrashDataStatus is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// CrashDataStatus must be overridden if this is called.</remarks>
        protected void EnableActionCrashDataStatus()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("CrashDataStatus");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("aCrashDataStatus", allowedValues));
            iDelegateCrashDataStatus = new ActionDelegate(DoCrashDataStatus);
            EnableAction(action, iDelegateCrashDataStatus, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action CrashDataFetch is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// CrashDataFetch must be overridden if this is called.</remarks>
        protected void EnableActionCrashDataFetch()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("CrashDataFetch");
            action.AddOutputParameter(new ParameterBinary("aCrashData"));
            iDelegateCrashDataFetch = new ActionDelegate(DoCrashDataFetch);
            EnableAction(action, iDelegateCrashDataFetch, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action CrashDataClear is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// CrashDataClear must be overridden if this is called.</remarks>
        protected void EnableActionCrashDataClear()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("CrashDataClear");
            iDelegateCrashDataClear = new ActionDelegate(DoCrashDataClear);
            EnableAction(action, iDelegateCrashDataClear, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SysLog is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SysLog must be overridden if this is called.</remarks>
        protected void EnableActionSysLog()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SysLog");
            action.AddOutputParameter(new ParameterBinary("aSysLog"));
            iDelegateSysLog = new ActionDelegate(DoSysLog);
            EnableAction(action, iDelegateSysLog, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Diagnostic is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Diagnostic must be overridden if this is called.</remarks>
        protected void EnableActionDiagnostic()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Diagnostic");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("aDiagnosticType", allowedValues));
            action.AddOutputParameter(new ParameterString("aDiagnosticInfo", allowedValues));
            iDelegateDiagnostic = new ActionDelegate(DoDiagnostic);
            EnableAction(action, iDelegateDiagnostic, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StateVariable is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// StateVariable must be overridden if this is called.</remarks>
        protected void EnableActionStateVariable()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("StateVariable");
            action.AddOutputParameter(new ParameterRelated("aStateVariable", iPropertyaStateVariable));
            iDelegateStateVariable = new ActionDelegate(DoStateVariable);
            EnableAction(action, iDelegateStateVariable, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetStateVariable is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetStateVariable must be overridden if this is called.</remarks>
        protected void EnableActionSetStateVariable()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetStateVariable");
            action.AddInputParameter(new ParameterRelated("aStateVariable", iPropertyaStateVariable));
            iDelegateSetStateVariable = new ActionDelegate(DoSetStateVariable);
            EnableAction(action, iDelegateSetStateVariable, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StateVariablePeriod is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// StateVariablePeriod must be overridden if this is called.</remarks>
        protected void EnableActionStateVariablePeriod()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("StateVariablePeriod");
            action.AddOutputParameter(new ParameterUint("aPeriod"));
            iDelegateStateVariablePeriod = new ActionDelegate(DoStateVariablePeriod);
            EnableAction(action, iDelegateStateVariablePeriod, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetStateVariablePeriod is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetStateVariablePeriod must be overridden if this is called.</remarks>
        protected void EnableActionSetStateVariablePeriod()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetStateVariablePeriod");
            action.AddInputParameter(new ParameterUint("aPeriod"));
            iDelegateSetStateVariablePeriod = new ActionDelegate(DoSetStateVariablePeriod);
            EnableAction(action, iDelegateSetStateVariablePeriod, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Reboot is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Reboot must be overridden if this is called.</remarks>
        protected void EnableActionReboot()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Reboot");
            action.AddInputParameter(new ParameterUint("aDelay"));
            iDelegateReboot = new ActionDelegate(DoReboot);
            EnableAction(action, iDelegateReboot, GCHandle.ToIntPtr(iGch));
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
        protected virtual void CrashDataFetch(uint aVersion, out byte[] aaCrashData)
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
        protected virtual void SysLog(uint aVersion, out byte[] aaSysLog)
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

        private static int DoEcho(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aIn;
            string aOut;
            try
            {
                invocation.ReadStart();
                aIn = invocation.ReadString("aIn");
                invocation.ReadEnd();
                self.Echo(aVersion, aIn, out aOut);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aOut", aOut);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoElfFile(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aElfFile;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ElfFile(aVersion, out aElfFile);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aElfFile", aElfFile);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoElfFingerprint(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aElfFileFingerprint;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ElfFingerprint(aVersion, out aElfFileFingerprint);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aElfFileFingerprint", aElfFileFingerprint);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoCrashDataStatus(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aCrashDataStatus;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.CrashDataStatus(aVersion, out aCrashDataStatus);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aCrashDataStatus", aCrashDataStatus);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoCrashDataFetch(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            byte[] aCrashData;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.CrashDataFetch(aVersion, out aCrashData);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBinary("aCrashData", aCrashData);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoCrashDataClear(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.CrashDataClear(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSysLog(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            byte[] aSysLog;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.SysLog(aVersion, out aSysLog);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBinary("aSysLog", aSysLog);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoDiagnostic(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aDiagnosticType;
            string aDiagnosticInfo;
            try
            {
                invocation.ReadStart();
                aDiagnosticType = invocation.ReadString("aDiagnosticType");
                invocation.ReadEnd();
                self.Diagnostic(aVersion, aDiagnosticType, out aDiagnosticInfo);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aDiagnosticInfo", aDiagnosticInfo);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoStateVariable(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aStateVariable;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StateVariable(aVersion, out aStateVariable);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("aStateVariable", aStateVariable);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSetStateVariable(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aStateVariable;
            try
            {
                invocation.ReadStart();
                aStateVariable = invocation.ReadUint("aStateVariable");
                invocation.ReadEnd();
                self.SetStateVariable(aVersion, aStateVariable);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoStateVariablePeriod(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aPeriod;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StateVariablePeriod(aVersion, out aPeriod);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("aPeriod", aPeriod);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSetStateVariablePeriod(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aPeriod;
            try
            {
                invocation.ReadStart();
                aPeriod = invocation.ReadUint("aPeriod");
                invocation.ReadEnd();
                self.SetStateVariablePeriod(aVersion, aPeriod);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoReboot(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDiagnostics1 self = (DvProviderLinnCoUkDiagnostics1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aDelay;
            try
            {
                invocation.ReadStart();
                aDelay = invocation.ReadUint("aDelay");
                invocation.ReadEnd();
                self.Reboot(aVersion, aDelay);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
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
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProvider();
                iHandle = IntPtr.Zero;
            }
            iGch.Free();
        }
    }
}

