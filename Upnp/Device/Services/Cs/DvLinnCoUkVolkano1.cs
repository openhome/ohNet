using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkVolkano1 : IDisposable
    {
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Volkano:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkVolkano1 : DvProvider, IDisposable, IDvProviderLinnCoUkVolkano1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateReboot;
        private ActionDelegate iDelegateBootMode;
        private ActionDelegate iDelegateSetBootMode;
        private ActionDelegate iDelegateBspType;
        private ActionDelegate iDelegateUglyName;
        private ActionDelegate iDelegateMacAddress;
        private ActionDelegate iDelegateProductId;
        private ActionDelegate iDelegateBoardId;
        private ActionDelegate iDelegateBoardType;
        private ActionDelegate iDelegateMaxBoards;
        private ActionDelegate iDelegateSoftwareVersion;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkVolkano1(DvDevice aDevice)
            : base(aDevice, "linn-co-uk", "Volkano", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action Reboot is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoReboot must be overridden if this is called.</remarks>
        protected void EnableActionReboot()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Reboot");
            iDelegateReboot = new ActionDelegate(DoReboot);
            EnableAction(action, iDelegateReboot, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action BootMode is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBootMode must be overridden if this is called.</remarks>
        protected void EnableActionBootMode()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("BootMode");
            List<String> allowedValues = new List<String>();
            allowedValues.Add("Main");
            allowedValues.Add("Fallback");
            allowedValues.Add("Ram");
            action.AddOutputParameter(new ParameterString("aMode", allowedValues));
            allowedValues.Clear();
            iDelegateBootMode = new ActionDelegate(DoBootMode);
            EnableAction(action, iDelegateBootMode, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetBootMode is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetBootMode must be overridden if this is called.</remarks>
        protected void EnableActionSetBootMode()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetBootMode");
            List<String> allowedValues = new List<String>();
            allowedValues.Add("Main");
            allowedValues.Add("Fallback");
            action.AddInputParameter(new ParameterString("aMode", allowedValues));
            allowedValues.Clear();
            iDelegateSetBootMode = new ActionDelegate(DoSetBootMode);
            EnableAction(action, iDelegateSetBootMode, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action BspType is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBspType must be overridden if this is called.</remarks>
        protected void EnableActionBspType()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("BspType");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("aBspType", allowedValues));
            iDelegateBspType = new ActionDelegate(DoBspType);
            EnableAction(action, iDelegateBspType, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action UglyName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoUglyName must be overridden if this is called.</remarks>
        protected void EnableActionUglyName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("UglyName");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("aUglyName", allowedValues));
            iDelegateUglyName = new ActionDelegate(DoUglyName);
            EnableAction(action, iDelegateUglyName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action MacAddress is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoMacAddress must be overridden if this is called.</remarks>
        protected void EnableActionMacAddress()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("MacAddress");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("aMacAddress", allowedValues));
            iDelegateMacAddress = new ActionDelegate(DoMacAddress);
            EnableAction(action, iDelegateMacAddress, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ProductId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoProductId must be overridden if this is called.</remarks>
        protected void EnableActionProductId()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ProductId");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("aProductNumber", allowedValues));
            iDelegateProductId = new ActionDelegate(DoProductId);
            EnableAction(action, iDelegateProductId, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action BoardId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBoardId must be overridden if this is called.</remarks>
        protected void EnableActionBoardId()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("BoardId");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("aIndex"));
            action.AddOutputParameter(new ParameterString("aBoardNumber", allowedValues));
            iDelegateBoardId = new ActionDelegate(DoBoardId);
            EnableAction(action, iDelegateBoardId, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action BoardType is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBoardType must be overridden if this is called.</remarks>
        protected void EnableActionBoardType()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("BoardType");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("aIndex"));
            action.AddOutputParameter(new ParameterString("aBoardNumber", allowedValues));
            iDelegateBoardType = new ActionDelegate(DoBoardType);
            EnableAction(action, iDelegateBoardType, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action MaxBoards is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoMaxBoards must be overridden if this is called.</remarks>
        protected void EnableActionMaxBoards()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("MaxBoards");
            action.AddOutputParameter(new ParameterUint("aMaxBoards"));
            iDelegateMaxBoards = new ActionDelegate(DoMaxBoards);
            EnableAction(action, iDelegateMaxBoards, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SoftwareVersion is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSoftwareVersion must be overridden if this is called.</remarks>
        protected void EnableActionSoftwareVersion()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SoftwareVersion");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("aSoftwareVersion", allowedValues));
            iDelegateSoftwareVersion = new ActionDelegate(DoSoftwareVersion);
            EnableAction(action, iDelegateSoftwareVersion, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Reboot action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Reboot action for the owning device.
        ///
        /// Must be implemented iff EnableActionReboot was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Reboot(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BootMode action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BootMode action for the owning device.
        ///
        /// Must be implemented iff EnableActionBootMode was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMode"></param>
        protected virtual void BootMode(uint aVersion, out string aaMode)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBootMode action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBootMode action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBootMode was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMode"></param>
        protected virtual void SetBootMode(uint aVersion, string aaMode)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BspType action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BspType action for the owning device.
        ///
        /// Must be implemented iff EnableActionBspType was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBspType"></param>
        protected virtual void BspType(uint aVersion, out string aaBspType)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// UglyName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// UglyName action for the owning device.
        ///
        /// Must be implemented iff EnableActionUglyName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUglyName"></param>
        protected virtual void UglyName(uint aVersion, out string aaUglyName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// MacAddress action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// MacAddress action for the owning device.
        ///
        /// Must be implemented iff EnableActionMacAddress was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMacAddress"></param>
        protected virtual void MacAddress(uint aVersion, out string aaMacAddress)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ProductId action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ProductId action for the owning device.
        ///
        /// Must be implemented iff EnableActionProductId was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaProductNumber"></param>
        protected virtual void ProductId(uint aVersion, out string aaProductNumber)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BoardId action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BoardId action for the owning device.
        ///
        /// Must be implemented iff EnableActionBoardId was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIndex"></param>
        /// <param name="aaBoardNumber"></param>
        protected virtual void BoardId(uint aVersion, uint aaIndex, out string aaBoardNumber)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BoardType action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BoardType action for the owning device.
        ///
        /// Must be implemented iff EnableActionBoardType was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIndex"></param>
        /// <param name="aaBoardNumber"></param>
        protected virtual void BoardType(uint aVersion, uint aaIndex, out string aaBoardNumber)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// MaxBoards action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// MaxBoards action for the owning device.
        ///
        /// Must be implemented iff EnableActionMaxBoards was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMaxBoards"></param>
        protected virtual void MaxBoards(uint aVersion, out uint aaMaxBoards)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SoftwareVersion action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SoftwareVersion action for the owning device.
        ///
        /// Must be implemented iff EnableActionSoftwareVersion was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSoftwareVersion"></param>
        protected virtual void SoftwareVersion(uint aVersion, out string aaSoftwareVersion)
        {
            throw (new ActionDisabledError());
        }

        private static int DoReboot(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Reboot(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
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
            return 0;
        }

        private static int DoBootMode(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aMode;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.BootMode(aVersion, out aMode);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aMode", aMode);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetBootMode(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aMode;
            try
            {
                invocation.ReadStart();
                aMode = invocation.ReadString("aMode");
                invocation.ReadEnd();
                self.SetBootMode(aVersion, aMode);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
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
            return 0;
        }

        private static int DoBspType(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aBspType;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.BspType(aVersion, out aBspType);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aBspType", aBspType);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoUglyName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aUglyName;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.UglyName(aVersion, out aUglyName);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aUglyName", aUglyName);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoMacAddress(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aMacAddress;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.MacAddress(aVersion, out aMacAddress);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aMacAddress", aMacAddress);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoProductId(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aProductNumber;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ProductId(aVersion, out aProductNumber);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aProductNumber", aProductNumber);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoBoardId(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aIndex;
            string aBoardNumber;
            try
            {
                invocation.ReadStart();
                aIndex = invocation.ReadUint("aIndex");
                invocation.ReadEnd();
                self.BoardId(aVersion, aIndex, out aBoardNumber);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aBoardNumber", aBoardNumber);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoBoardType(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aIndex;
            string aBoardNumber;
            try
            {
                invocation.ReadStart();
                aIndex = invocation.ReadUint("aIndex");
                invocation.ReadEnd();
                self.BoardType(aVersion, aIndex, out aBoardNumber);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aBoardNumber", aBoardNumber);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoMaxBoards(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aMaxBoards;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.MaxBoards(aVersion, out aMaxBoards);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("aMaxBoards", aMaxBoards);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSoftwareVersion(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aSoftwareVersion;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.SoftwareVersion(aVersion, out aSoftwareVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aSoftwareVersion", aSoftwareVersion);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
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

        ~DvProviderLinnCoUkVolkano1()
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

