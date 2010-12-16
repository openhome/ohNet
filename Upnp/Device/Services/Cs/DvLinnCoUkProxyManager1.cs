using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkProxyManager1 : IDisposable
    {

        /// <summary>
        /// Set the value of the KontrolProductConnected property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyKontrolProductConnected(string aValue);

        /// <summary>
        /// Get a copy of the value of the KontrolProductConnected property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyKontrolProductConnected();

        /// <summary>
        /// Set the value of the KontrolProductComPort property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyKontrolProductComPort(uint aValue);

        /// <summary>
        /// Get a copy of the value of the KontrolProductComPort property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyKontrolProductComPort();

        /// <summary>
        /// Set the value of the DiscPlayerConnected property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDiscPlayerConnected(string aValue);

        /// <summary>
        /// Get a copy of the value of the DiscPlayerConnected property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyDiscPlayerConnected();

        /// <summary>
        /// Set the value of the DiscPlayerComPort property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDiscPlayerComPort(uint aValue);

        /// <summary>
        /// Get a copy of the value of the DiscPlayerComPort property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyDiscPlayerComPort();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:ProxyManager:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkProxyManager1 : DvProvider, IDisposable, IDvProviderLinnCoUkProxyManager1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateKontrolProductConnected;
        private ActionDelegate iDelegateSetKontrolProductConnected;
        private ActionDelegate iDelegateKontrolProductComPort;
        private ActionDelegate iDelegateSetKontrolProductComPort;
        private ActionDelegate iDelegateDiscPlayerConnected;
        private ActionDelegate iDelegateSetDiscPlayerConnected;
        private ActionDelegate iDelegateDiscPlayerComPort;
        private ActionDelegate iDelegateSetDiscPlayerComPort;
        private ActionDelegate iDelegateTestKontrolProductConnection;
        private ActionDelegate iDelegateTestDiscPlayerConnection;
        private PropertyString iPropertyKontrolProductConnected;
        private PropertyUint iPropertyKontrolProductComPort;
        private PropertyString iPropertyDiscPlayerConnected;
        private PropertyUint iPropertyDiscPlayerComPort;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkProxyManager1(DvDevice aDevice)
            : base(aDevice, "linn-co-uk", "ProxyManager", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            allowedValues.Add("None");
            allowedValues.Add("Klimax Kontrol");
            allowedValues.Add("Akurate Kontrol");
            allowedValues.Add("Kisto");
            allowedValues.Add("Kinos");
            allowedValues.Add("Majik Kontrol");
            allowedValues.Add("Majik-I");
            allowedValues.Add("Unidisk SC");
            allowedValues.Add("Classik Movie");
            allowedValues.Add("Classik Music");
            allowedValues.Add("Roomamp 2");
            iPropertyKontrolProductConnected = new PropertyString(new ParameterString("KontrolProductConnected", allowedValues));
            AddProperty(iPropertyKontrolProductConnected);
            allowedValues.Clear();
            iPropertyKontrolProductComPort = new PropertyUint(new ParameterUint("KontrolProductComPort"));
            AddProperty(iPropertyKontrolProductComPort);
            allowedValues.Add("None");
            allowedValues.Add("CD12");
            allowedValues.Add("Akurate CD");
            allowedValues.Add("Unidisk 1.1");
            allowedValues.Add("Unidisk 2.1");
            allowedValues.Add("Majik CD");
            allowedValues.Add("Unidisk SC");
            allowedValues.Add("Classik Movie");
            allowedValues.Add("Classik Music");
            iPropertyDiscPlayerConnected = new PropertyString(new ParameterString("DiscPlayerConnected", allowedValues));
            AddProperty(iPropertyDiscPlayerConnected);
            allowedValues.Clear();
            iPropertyDiscPlayerComPort = new PropertyUint(new ParameterUint("DiscPlayerComPort"));
            AddProperty(iPropertyDiscPlayerComPort);
        }

        /// <summary>
        /// Set the value of the KontrolProductConnected property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyKontrolProductConnected(string aValue)
        {
            return SetPropertyString(iPropertyKontrolProductConnected, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the KontrolProductConnected property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyKontrolProductConnected()
        {
            return iPropertyKontrolProductConnected.Value();
        }

        /// <summary>
        /// Set the value of the KontrolProductComPort property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyKontrolProductComPort(uint aValue)
        {
            return SetPropertyUint(iPropertyKontrolProductComPort, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the KontrolProductComPort property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyKontrolProductComPort()
        {
            return iPropertyKontrolProductComPort.Value();
        }

        /// <summary>
        /// Set the value of the DiscPlayerConnected property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDiscPlayerConnected(string aValue)
        {
            return SetPropertyString(iPropertyDiscPlayerConnected, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DiscPlayerConnected property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyDiscPlayerConnected()
        {
            return iPropertyDiscPlayerConnected.Value();
        }

        /// <summary>
        /// Set the value of the DiscPlayerComPort property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDiscPlayerComPort(uint aValue)
        {
            return SetPropertyUint(iPropertyDiscPlayerComPort, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DiscPlayerComPort property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyDiscPlayerComPort()
        {
            return iPropertyDiscPlayerComPort.Value();
        }

        /// <summary>
        /// Signal that the action KontrolProductConnected is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoKontrolProductConnected must be overridden if this is called.</remarks>
        protected unsafe void EnableActionKontrolProductConnected()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("KontrolProductConnected");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterRelated("aConnected", iPropertyKontrolProductConnected));
            iDelegateKontrolProductConnected = new ActionDelegate(DoKontrolProductConnected);
            EnableAction(action, iDelegateKontrolProductConnected, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetKontrolProductConnected is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetKontrolProductConnected must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetKontrolProductConnected()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetKontrolProductConnected");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterRelated("aConnected", iPropertyKontrolProductConnected));
            iDelegateSetKontrolProductConnected = new ActionDelegate(DoSetKontrolProductConnected);
            EnableAction(action, iDelegateSetKontrolProductConnected, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action KontrolProductComPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoKontrolProductComPort must be overridden if this is called.</remarks>
        protected unsafe void EnableActionKontrolProductComPort()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("KontrolProductComPort");
            action.AddOutputParameter(new ParameterRelated("aPort", iPropertyKontrolProductComPort));
            iDelegateKontrolProductComPort = new ActionDelegate(DoKontrolProductComPort);
            EnableAction(action, iDelegateKontrolProductComPort, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetKontrolProductComPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetKontrolProductComPort must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetKontrolProductComPort()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetKontrolProductComPort");
            action.AddInputParameter(new ParameterRelated("aConnected", iPropertyKontrolProductComPort));
            iDelegateSetKontrolProductComPort = new ActionDelegate(DoSetKontrolProductComPort);
            EnableAction(action, iDelegateSetKontrolProductComPort, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DiscPlayerConnected is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDiscPlayerConnected must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDiscPlayerConnected()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DiscPlayerConnected");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterRelated("aConnected", iPropertyDiscPlayerConnected));
            iDelegateDiscPlayerConnected = new ActionDelegate(DoDiscPlayerConnected);
            EnableAction(action, iDelegateDiscPlayerConnected, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetDiscPlayerConnected is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDiscPlayerConnected must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDiscPlayerConnected()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetDiscPlayerConnected");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterRelated("aConnected", iPropertyDiscPlayerConnected));
            iDelegateSetDiscPlayerConnected = new ActionDelegate(DoSetDiscPlayerConnected);
            EnableAction(action, iDelegateSetDiscPlayerConnected, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DiscPlayerComPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDiscPlayerComPort must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDiscPlayerComPort()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DiscPlayerComPort");
            action.AddOutputParameter(new ParameterRelated("aPort", iPropertyDiscPlayerComPort));
            iDelegateDiscPlayerComPort = new ActionDelegate(DoDiscPlayerComPort);
            EnableAction(action, iDelegateDiscPlayerComPort, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetDiscPlayerComPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDiscPlayerComPort must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDiscPlayerComPort()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetDiscPlayerComPort");
            action.AddInputParameter(new ParameterRelated("aConnected", iPropertyDiscPlayerComPort));
            iDelegateSetDiscPlayerComPort = new ActionDelegate(DoSetDiscPlayerComPort);
            EnableAction(action, iDelegateSetDiscPlayerComPort, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action TestKontrolProductConnection is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoTestKontrolProductConnection must be overridden if this is called.</remarks>
        protected unsafe void EnableActionTestKontrolProductConnection()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("TestKontrolProductConnection");
            action.AddOutputParameter(new ParameterBool("aResult"));
            iDelegateTestKontrolProductConnection = new ActionDelegate(DoTestKontrolProductConnection);
            EnableAction(action, iDelegateTestKontrolProductConnection, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action TestDiscPlayerConnection is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoTestDiscPlayerConnection must be overridden if this is called.</remarks>
        protected unsafe void EnableActionTestDiscPlayerConnection()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("TestDiscPlayerConnection");
            action.AddOutputParameter(new ParameterBool("aResult"));
            iDelegateTestDiscPlayerConnection = new ActionDelegate(DoTestDiscPlayerConnection);
            EnableAction(action, iDelegateTestDiscPlayerConnection, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// KontrolProductConnected action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// KontrolProductConnected action for the owning device.
        ///
        /// Must be implemented iff EnableActionKontrolProductConnected was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void KontrolProductConnected(uint aVersion, out string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetKontrolProductConnected action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetKontrolProductConnected action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetKontrolProductConnected was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void SetKontrolProductConnected(uint aVersion, string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// KontrolProductComPort action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// KontrolProductComPort action for the owning device.
        ///
        /// Must be implemented iff EnableActionKontrolProductComPort was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPort"></param>
        protected virtual void KontrolProductComPort(uint aVersion, out uint aaPort)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetKontrolProductComPort action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetKontrolProductComPort action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetKontrolProductComPort was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void SetKontrolProductComPort(uint aVersion, uint aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DiscPlayerConnected action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DiscPlayerConnected action for the owning device.
        ///
        /// Must be implemented iff EnableActionDiscPlayerConnected was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void DiscPlayerConnected(uint aVersion, out string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDiscPlayerConnected action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDiscPlayerConnected action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDiscPlayerConnected was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void SetDiscPlayerConnected(uint aVersion, string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DiscPlayerComPort action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DiscPlayerComPort action for the owning device.
        ///
        /// Must be implemented iff EnableActionDiscPlayerComPort was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPort"></param>
        protected virtual void DiscPlayerComPort(uint aVersion, out uint aaPort)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDiscPlayerComPort action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDiscPlayerComPort action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDiscPlayerComPort was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void SetDiscPlayerComPort(uint aVersion, uint aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// TestKontrolProductConnection action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// TestKontrolProductConnection action for the owning device.
        ///
        /// Must be implemented iff EnableActionTestKontrolProductConnection was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaResult"></param>
        protected virtual void TestKontrolProductConnection(uint aVersion, out bool aaResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// TestDiscPlayerConnection action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// TestDiscPlayerConnection action for the owning device.
        ///
        /// Must be implemented iff EnableActionTestDiscPlayerConnection was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaResult"></param>
        protected virtual void TestDiscPlayerConnection(uint aVersion, out bool aaResult)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoKontrolProductConnected(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            string aConnected;
            self.KontrolProductConnected(aVersion, out aConnected);
            invocation.WriteStart();
            invocation.WriteString("aConnected", aConnected);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSetKontrolProductConnected(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            string aConnected = invocation.ReadString("aConnected");
            invocation.ReadEnd();
            self.SetKontrolProductConnected(aVersion, aConnected);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoKontrolProductComPort(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            uint aPort;
            self.KontrolProductComPort(aVersion, out aPort);
            invocation.WriteStart();
            invocation.WriteUint("aPort", aPort);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSetKontrolProductComPort(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            uint aConnected = invocation.ReadUint("aConnected");
            invocation.ReadEnd();
            self.SetKontrolProductComPort(aVersion, aConnected);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoDiscPlayerConnected(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            string aConnected;
            self.DiscPlayerConnected(aVersion, out aConnected);
            invocation.WriteStart();
            invocation.WriteString("aConnected", aConnected);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSetDiscPlayerConnected(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            string aConnected = invocation.ReadString("aConnected");
            invocation.ReadEnd();
            self.SetDiscPlayerConnected(aVersion, aConnected);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoDiscPlayerComPort(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            uint aPort;
            self.DiscPlayerComPort(aVersion, out aPort);
            invocation.WriteStart();
            invocation.WriteUint("aPort", aPort);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSetDiscPlayerComPort(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            uint aConnected = invocation.ReadUint("aConnected");
            invocation.ReadEnd();
            self.SetDiscPlayerComPort(aVersion, aConnected);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoTestKontrolProductConnection(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            bool aResult;
            self.TestKontrolProductConnection(aVersion, out aResult);
            invocation.WriteStart();
            invocation.WriteBool("aResult", aResult);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoTestDiscPlayerConnection(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            bool aResult;
            self.TestDiscPlayerConnection(aVersion, out aResult);
            invocation.WriteStart();
            invocation.WriteBool("aResult", aResult);
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

        ~DvProviderLinnCoUkProxyManager1()
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

