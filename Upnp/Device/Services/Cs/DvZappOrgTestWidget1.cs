using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderZappOrgTestWidget1 : IDisposable
    {

        /// <summary>
        /// Set the value of the ReadWriteRegister0 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadWriteRegister0(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister0 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyReadWriteRegister0();

        /// <summary>
        /// Set the value of the ReadWriteRegister1 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadWriteRegister1(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister1 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyReadWriteRegister1();

        /// <summary>
        /// Set the value of the ReadWriteRegister2 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadWriteRegister2(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister2 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyReadWriteRegister2();

        /// <summary>
        /// Set the value of the ReadWriteRegister3 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadWriteRegister3(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister3 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyReadWriteRegister3();

        /// <summary>
        /// Set the value of the ReadOnlyRegister4 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadOnlyRegister4(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister4 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyReadOnlyRegister4();

        /// <summary>
        /// Set the value of the ReadOnlyRegister5 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadOnlyRegister5(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister5 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyReadOnlyRegister5();

        /// <summary>
        /// Set the value of the ReadOnlyRegister6 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadOnlyRegister6(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister6 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyReadOnlyRegister6();

        /// <summary>
        /// Set the value of the ReadOnlyRegister7 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadOnlyRegister7(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister7 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyReadOnlyRegister7();
        
    }
    /// <summary>
    /// Provider for the zapp.org:TestWidget:1 UPnP service
    /// </summary>
    public class DvProviderZappOrgTestWidget1 : DvProvider, IDisposable, IDvProviderZappOrgTestWidget1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateSetReadWriteRegister;
        private ActionDelegate iDelegateGetWidgetClass;
        private PropertyUint iPropertyReadWriteRegister0;
        private PropertyUint iPropertyReadWriteRegister1;
        private PropertyUint iPropertyReadWriteRegister2;
        private PropertyUint iPropertyReadWriteRegister3;
        private PropertyUint iPropertyReadOnlyRegister4;
        private PropertyUint iPropertyReadOnlyRegister5;
        private PropertyUint iPropertyReadOnlyRegister6;
        private PropertyUint iPropertyReadOnlyRegister7;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderZappOrgTestWidget1(DvDevice aDevice)
            : base(aDevice, "zapp-org", "TestWidget", 1)
        {
            iGch = GCHandle.Alloc(this);
            iPropertyReadWriteRegister0 = new PropertyUint(new ParameterUint("ReadWriteRegister0"));
            AddProperty(iPropertyReadWriteRegister0);
            iPropertyReadWriteRegister1 = new PropertyUint(new ParameterUint("ReadWriteRegister1"));
            AddProperty(iPropertyReadWriteRegister1);
            iPropertyReadWriteRegister2 = new PropertyUint(new ParameterUint("ReadWriteRegister2"));
            AddProperty(iPropertyReadWriteRegister2);
            iPropertyReadWriteRegister3 = new PropertyUint(new ParameterUint("ReadWriteRegister3"));
            AddProperty(iPropertyReadWriteRegister3);
            iPropertyReadOnlyRegister4 = new PropertyUint(new ParameterUint("ReadOnlyRegister4"));
            AddProperty(iPropertyReadOnlyRegister4);
            iPropertyReadOnlyRegister5 = new PropertyUint(new ParameterUint("ReadOnlyRegister5"));
            AddProperty(iPropertyReadOnlyRegister5);
            iPropertyReadOnlyRegister6 = new PropertyUint(new ParameterUint("ReadOnlyRegister6"));
            AddProperty(iPropertyReadOnlyRegister6);
            iPropertyReadOnlyRegister7 = new PropertyUint(new ParameterUint("ReadOnlyRegister7"));
            AddProperty(iPropertyReadOnlyRegister7);
        }

        /// <summary>
        /// Set the value of the ReadWriteRegister0 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyReadWriteRegister0(uint aValue)
        {
            return SetPropertyUint(iPropertyReadWriteRegister0, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister0 property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyReadWriteRegister0()
        {
            return iPropertyReadWriteRegister0.Value();
        }

        /// <summary>
        /// Set the value of the ReadWriteRegister1 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyReadWriteRegister1(uint aValue)
        {
            return SetPropertyUint(iPropertyReadWriteRegister1, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister1 property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyReadWriteRegister1()
        {
            return iPropertyReadWriteRegister1.Value();
        }

        /// <summary>
        /// Set the value of the ReadWriteRegister2 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyReadWriteRegister2(uint aValue)
        {
            return SetPropertyUint(iPropertyReadWriteRegister2, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister2 property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyReadWriteRegister2()
        {
            return iPropertyReadWriteRegister2.Value();
        }

        /// <summary>
        /// Set the value of the ReadWriteRegister3 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyReadWriteRegister3(uint aValue)
        {
            return SetPropertyUint(iPropertyReadWriteRegister3, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister3 property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyReadWriteRegister3()
        {
            return iPropertyReadWriteRegister3.Value();
        }

        /// <summary>
        /// Set the value of the ReadOnlyRegister4 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyReadOnlyRegister4(uint aValue)
        {
            return SetPropertyUint(iPropertyReadOnlyRegister4, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister4 property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyReadOnlyRegister4()
        {
            return iPropertyReadOnlyRegister4.Value();
        }

        /// <summary>
        /// Set the value of the ReadOnlyRegister5 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyReadOnlyRegister5(uint aValue)
        {
            return SetPropertyUint(iPropertyReadOnlyRegister5, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister5 property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyReadOnlyRegister5()
        {
            return iPropertyReadOnlyRegister5.Value();
        }

        /// <summary>
        /// Set the value of the ReadOnlyRegister6 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyReadOnlyRegister6(uint aValue)
        {
            return SetPropertyUint(iPropertyReadOnlyRegister6, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister6 property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyReadOnlyRegister6()
        {
            return iPropertyReadOnlyRegister6.Value();
        }

        /// <summary>
        /// Set the value of the ReadOnlyRegister7 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyReadOnlyRegister7(uint aValue)
        {
            return SetPropertyUint(iPropertyReadOnlyRegister7, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister7 property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyReadOnlyRegister7()
        {
            return iPropertyReadOnlyRegister7.Value();
        }

        /// <summary>
        /// Signal that the action SetReadWriteRegister is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetReadWriteRegister must be overridden if this is called.</remarks>
        protected void EnableActionSetReadWriteRegister()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetReadWriteRegister");
            action.AddInputParameter(new ParameterUint("RegisterIndex"));
            action.AddInputParameter(new ParameterUint("RegisterValue"));
            iDelegateSetReadWriteRegister = new ActionDelegate(DoSetReadWriteRegister);
            EnableAction(action, iDelegateSetReadWriteRegister, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetWidgetClass is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetWidgetClass must be overridden if this is called.</remarks>
        protected void EnableActionGetWidgetClass()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetWidgetClass");
            action.AddOutputParameter(new ParameterUint("WidgetClass"));
            iDelegateGetWidgetClass = new ActionDelegate(DoGetWidgetClass);
            EnableAction(action, iDelegateGetWidgetClass, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// SetReadWriteRegister action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetReadWriteRegister action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetReadWriteRegister was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        protected virtual void SetReadWriteRegister(uint aVersion, uint aRegisterIndex, uint aRegisterValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetWidgetClass action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetWidgetClass action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetWidgetClass was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aWidgetClass"></param>
        protected virtual void GetWidgetClass(uint aVersion, out uint aWidgetClass)
        {
            throw (new ActionDisabledError());
        }

        private static int DoSetReadWriteRegister(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidget1 self = (DvProviderZappOrgTestWidget1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint registerIndex;
            uint registerValue;
            try
            {
                invocation.ReadStart();
                registerIndex = invocation.ReadUint("RegisterIndex");
                registerValue = invocation.ReadUint("RegisterValue");
                invocation.ReadEnd();
                self.SetReadWriteRegister(aVersion, registerIndex, registerValue);
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

        private static int DoGetWidgetClass(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidget1 self = (DvProviderZappOrgTestWidget1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint widgetClass;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetWidgetClass(aVersion, out widgetClass);
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
                invocation.WriteUint("WidgetClass", widgetClass);
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

        ~DvProviderZappOrgTestWidget1()
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

