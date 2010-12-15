using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderZappOrgTestWidgetController1 : IDisposable
    {
        
    }
    /// <summary>
    /// Provider for the zapp.org:TestWidgetController:1 UPnP service
    /// </summary>
    public class DvProviderZappOrgTestWidgetController1 : DvProvider, IDisposable, IDvProviderZappOrgTestWidgetController1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateCreateWidget;
        private ActionDelegate iDelegateRemoveWidget;
        private ActionDelegate iDelegateSetWidgetRegister;
        private ActionDelegate iDelegateGetWidgetRegister;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderZappOrgTestWidgetController1(DvDevice aDevice)
            : base(aDevice, "zapp-org", "TestWidgetController", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action CreateWidget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoCreateWidget must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCreateWidget()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("CreateWidget");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("WidgetUdn", allowedValues));
            action.AddInputParameter(new ParameterUint("WidgetClass"));
            iDelegateCreateWidget = new ActionDelegate(DoCreateWidget);
            EnableAction(action, iDelegateCreateWidget, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action RemoveWidget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoRemoveWidget must be overridden if this is called.</remarks>
        protected unsafe void EnableActionRemoveWidget()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("RemoveWidget");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("WidgetUdn", allowedValues));
            iDelegateRemoveWidget = new ActionDelegate(DoRemoveWidget);
            EnableAction(action, iDelegateRemoveWidget, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetWidgetRegister is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetWidgetRegister must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetWidgetRegister()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetWidgetRegister");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("WidgetUdn", allowedValues));
            action.AddInputParameter(new ParameterUint("RegisterIndex"));
            action.AddInputParameter(new ParameterUint("RegisterValue"));
            iDelegateSetWidgetRegister = new ActionDelegate(DoSetWidgetRegister);
            EnableAction(action, iDelegateSetWidgetRegister, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetWidgetRegister is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetWidgetRegister must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetWidgetRegister()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetWidgetRegister");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("WidgetUdn", allowedValues));
            action.AddInputParameter(new ParameterUint("RegisterIndex"));
            action.AddOutputParameter(new ParameterUint("RegisterValue"));
            iDelegateGetWidgetRegister = new ActionDelegate(DoGetWidgetRegister);
            EnableAction(action, iDelegateGetWidgetRegister, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// CreateWidget action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// CreateWidget action for the owning device.
        ///
        /// Must be implemented iff EnableActionCreateWidget was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aWidgetClass"></param>
        protected virtual void CreateWidget(uint aVersion, string aWidgetUdn, uint aWidgetClass)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// RemoveWidget action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// RemoveWidget action for the owning device.
        ///
        /// Must be implemented iff EnableActionRemoveWidget was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aWidgetUdn"></param>
        protected virtual void RemoveWidget(uint aVersion, string aWidgetUdn)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetWidgetRegister action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetWidgetRegister action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetWidgetRegister was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        protected virtual void SetWidgetRegister(uint aVersion, string aWidgetUdn, uint aRegisterIndex, uint aRegisterValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetWidgetRegister action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetWidgetRegister action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetWidgetRegister was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        protected virtual void GetWidgetRegister(uint aVersion, string aWidgetUdn, uint aRegisterIndex, out uint aRegisterValue)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoCreateWidget(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidgetController1 self = (DvProviderZappOrgTestWidgetController1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string widgetUdn = invocation.ReadString("WidgetUdn");
            uint widgetClass = invocation.ReadUint("WidgetClass");
            self.CreateWidget(aVersion, widgetUdn, widgetClass);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoRemoveWidget(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidgetController1 self = (DvProviderZappOrgTestWidgetController1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string widgetUdn = invocation.ReadString("WidgetUdn");
            self.RemoveWidget(aVersion, widgetUdn);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSetWidgetRegister(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidgetController1 self = (DvProviderZappOrgTestWidgetController1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string widgetUdn = invocation.ReadString("WidgetUdn");
            uint registerIndex = invocation.ReadUint("RegisterIndex");
            uint registerValue = invocation.ReadUint("RegisterValue");
            self.SetWidgetRegister(aVersion, widgetUdn, registerIndex, registerValue);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoGetWidgetRegister(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidgetController1 self = (DvProviderZappOrgTestWidgetController1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string widgetUdn = invocation.ReadString("WidgetUdn");
            uint registerIndex = invocation.ReadUint("RegisterIndex");
            uint registerValue;
            self.GetWidgetRegister(aVersion, widgetUdn, registerIndex, out registerValue);
            invocation.WriteStart();
            invocation.WriteUint("RegisterValue", registerValue);
            invocation.WriteEnd();
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

        ~DvProviderZappOrgTestWidgetController1()
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

