using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkConfiguration1 : IDisposable
    {

        /// <summary>
        /// Set the value of the ConfigurationXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyConfigurationXml(string aValue);

        /// <summary>
        /// Get a copy of the value of the ConfigurationXml property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyConfigurationXml();

        /// <summary>
        /// Set the value of the ParameterXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyParameterXml(string aValue);

        /// <summary>
        /// Get a copy of the value of the ParameterXml property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyParameterXml();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Configuration:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkConfiguration1 : DvProvider, IDisposable, IDvProviderLinnCoUkConfiguration1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateConfigurationXml;
        private ActionDelegate iDelegateParameterXml;
        private ActionDelegate iDelegateSetParameter;
        private PropertyString iPropertyConfigurationXml;
        private PropertyString iPropertyParameterXml;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkConfiguration1(DvDevice aDevice)
            : base(aDevice, "linn-co-uk", "Configuration", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyConfigurationXml = new PropertyString(new ParameterString("ConfigurationXml", allowedValues));
            AddProperty(iPropertyConfigurationXml);
            iPropertyParameterXml = new PropertyString(new ParameterString("ParameterXml", allowedValues));
            AddProperty(iPropertyParameterXml);
        }

        /// <summary>
        /// Set the value of the ConfigurationXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyConfigurationXml(string aValue)
        {
            return SetPropertyString(iPropertyConfigurationXml, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ConfigurationXml property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyConfigurationXml()
        {
            return iPropertyConfigurationXml.Value();
        }

        /// <summary>
        /// Set the value of the ParameterXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyParameterXml(string aValue)
        {
            return SetPropertyString(iPropertyParameterXml, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ParameterXml property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyParameterXml()
        {
            return iPropertyParameterXml.Value();
        }

        /// <summary>
        /// Signal that the action ConfigurationXml is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoConfigurationXml must be overridden if this is called.</remarks>
        protected unsafe void EnableActionConfigurationXml()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ConfigurationXml");
            action.AddOutputParameter(new ParameterRelated("aConfigurationXml", iPropertyConfigurationXml));
            iDelegateConfigurationXml = new ActionDelegate(DoConfigurationXml);
            EnableAction(action, iDelegateConfigurationXml, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ParameterXml is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoParameterXml must be overridden if this is called.</remarks>
        protected unsafe void EnableActionParameterXml()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ParameterXml");
            action.AddOutputParameter(new ParameterRelated("aParameterXml", iPropertyParameterXml));
            iDelegateParameterXml = new ActionDelegate(DoParameterXml);
            EnableAction(action, iDelegateParameterXml, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetParameter is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetParameter must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetParameter()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetParameter");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("aTarget", allowedValues));
            action.AddInputParameter(new ParameterString("aName", allowedValues));
            action.AddInputParameter(new ParameterString("aValue", allowedValues));
            iDelegateSetParameter = new ActionDelegate(DoSetParameter);
            EnableAction(action, iDelegateSetParameter, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// ConfigurationXml action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ConfigurationXml action for the owning device.
        ///
        /// Must be implemented iff EnableActionConfigurationXml was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConfigurationXml"></param>
        protected virtual void ConfigurationXml(uint aVersion, out string aaConfigurationXml)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ParameterXml action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ParameterXml action for the owning device.
        ///
        /// Must be implemented iff EnableActionParameterXml was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaParameterXml"></param>
        protected virtual void ParameterXml(uint aVersion, out string aaParameterXml)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetParameter action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetParameter action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetParameter was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTarget"></param>
        /// <param name="aaName"></param>
        /// <param name="aaValue"></param>
        protected virtual void SetParameter(uint aVersion, string aaTarget, string aaName, string aaValue)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoConfigurationXml(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkConfiguration1 self = (DvProviderLinnCoUkConfiguration1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aConfigurationXml;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ConfigurationXml(aVersion, out aConfigurationXml);
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
                invocation.WriteString("aConfigurationXml", aConfigurationXml);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoParameterXml(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkConfiguration1 self = (DvProviderLinnCoUkConfiguration1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aParameterXml;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ParameterXml(aVersion, out aParameterXml);
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
                invocation.WriteString("aParameterXml", aParameterXml);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetParameter(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkConfiguration1 self = (DvProviderLinnCoUkConfiguration1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aTarget;
            string aName;
            string aValue;
            try
            {
                invocation.ReadStart();
                aTarget = invocation.ReadString("aTarget");
                aName = invocation.ReadString("aName");
                aValue = invocation.ReadString("aValue");
                invocation.ReadEnd();
                self.SetParameter(aVersion, aTarget, aName, aValue);
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

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkConfiguration1()
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

