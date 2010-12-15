using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkConfiguration1 : ICpProxy, IDisposable
    {
        void SyncConfigurationXml(out String aaConfigurationXml);
        void BeginConfigurationXml(CpProxy.CallbackAsyncComplete aCallback);
        void EndConfigurationXml(IntPtr aAsyncHandle, out String aaConfigurationXml);
        void SyncParameterXml(out String aaParameterXml);
        void BeginParameterXml(CpProxy.CallbackAsyncComplete aCallback);
        void EndParameterXml(IntPtr aAsyncHandle, out String aaParameterXml);
        void SyncSetParameter(String aaTarget, String aaName, String aaValue);
        void BeginSetParameter(String aaTarget, String aaName, String aaValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetParameter(IntPtr aAsyncHandle);
        void SetPropertyConfigurationXmlChanged(CpProxy.CallbackPropertyChanged aConfigurationXmlChanged);
        String PropertyConfigurationXml();
        void SetPropertyParameterXmlChanged(CpProxy.CallbackPropertyChanged aParameterXmlChanged);
        String PropertyParameterXml();
    }

    internal class SyncConfigurationXmlLinnCoUkConfiguration1 : SyncProxyAction
    {
        private CpProxyLinnCoUkConfiguration1 iService;
        private String iConfigurationXml;

        public SyncConfigurationXmlLinnCoUkConfiguration1(CpProxyLinnCoUkConfiguration1 aProxy)
        {
            iService = aProxy;
        }
        public String ConfigurationXml()
        {
            return iConfigurationXml;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndConfigurationXml(aAsyncHandle, out iConfigurationXml);
        }
    };

    internal class SyncParameterXmlLinnCoUkConfiguration1 : SyncProxyAction
    {
        private CpProxyLinnCoUkConfiguration1 iService;
        private String iParameterXml;

        public SyncParameterXmlLinnCoUkConfiguration1(CpProxyLinnCoUkConfiguration1 aProxy)
        {
            iService = aProxy;
        }
        public String ParameterXml()
        {
            return iParameterXml;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndParameterXml(aAsyncHandle, out iParameterXml);
        }
    };

    internal class SyncSetParameterLinnCoUkConfiguration1 : SyncProxyAction
    {
        private CpProxyLinnCoUkConfiguration1 iService;

        public SyncSetParameterLinnCoUkConfiguration1(CpProxyLinnCoUkConfiguration1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetParameter(aAsyncHandle);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Configuration:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkConfiguration1 : CpProxy, IDisposable, ICpProxyLinnCoUkConfiguration1
    {
        private Zapp.Core.Action iActionConfigurationXml;
        private Zapp.Core.Action iActionParameterXml;
        private Zapp.Core.Action iActionSetParameter;
        private PropertyString iConfigurationXml;
        private PropertyString iParameterXml;
        private CallbackPropertyChanged iConfigurationXmlChanged;
        private CallbackPropertyChanged iParameterXmlChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkConfiguration1(CpDevice aDevice)
            : base("linn-co-uk", "Configuration", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionConfigurationXml = new Zapp.Core.Action("ConfigurationXml");
            param = new ParameterString("aConfigurationXml", allowedValues);
            iActionConfigurationXml.AddOutputParameter(param);

            iActionParameterXml = new Zapp.Core.Action("ParameterXml");
            param = new ParameterString("aParameterXml", allowedValues);
            iActionParameterXml.AddOutputParameter(param);

            iActionSetParameter = new Zapp.Core.Action("SetParameter");
            param = new ParameterString("aTarget", allowedValues);
            iActionSetParameter.AddInputParameter(param);
            param = new ParameterString("aName", allowedValues);
            iActionSetParameter.AddInputParameter(param);
            param = new ParameterString("aValue", allowedValues);
            iActionSetParameter.AddInputParameter(param);

            iConfigurationXml = new PropertyString("ConfigurationXml", ConfigurationXmlPropertyChanged);
            AddProperty(iConfigurationXml);
            iParameterXml = new PropertyString("ParameterXml", ParameterXmlPropertyChanged);
            AddProperty(iParameterXml);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaConfigurationXml"></param>
        public void SyncConfigurationXml(out String aaConfigurationXml)
        {
            SyncConfigurationXmlLinnCoUkConfiguration1 sync = new SyncConfigurationXmlLinnCoUkConfiguration1(this);
            BeginConfigurationXml(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aConfigurationXml = sync.ConfigurationXml();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndConfigurationXml().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginConfigurationXml(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionConfigurationXml, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionConfigurationXml.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaConfigurationXml"></param>
        public void EndConfigurationXml(IntPtr aAsyncHandle, out String aaConfigurationXml)
        {
            uint index = 0;
            aConfigurationXml = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaParameterXml"></param>
        public void SyncParameterXml(out String aaParameterXml)
        {
            SyncParameterXmlLinnCoUkConfiguration1 sync = new SyncParameterXmlLinnCoUkConfiguration1(this);
            BeginParameterXml(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aParameterXml = sync.ParameterXml();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndParameterXml().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginParameterXml(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionParameterXml, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionParameterXml.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaParameterXml"></param>
        public void EndParameterXml(IntPtr aAsyncHandle, out String aaParameterXml)
        {
            uint index = 0;
            aParameterXml = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTarget"></param>
        /// <param name="aaName"></param>
        /// <param name="aaValue"></param>
        public void SyncSetParameter(String aaTarget, String aaName, String aaValue)
        {
            SyncSetParameterLinnCoUkConfiguration1 sync = new SyncSetParameterLinnCoUkConfiguration1(this);
            BeginSetParameter(aTarget, aName, aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetParameter().</remarks>
        /// <param name="aaTarget"></param>
        /// <param name="aaName"></param>
        /// <param name="aaValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetParameter(String aaTarget, String aaName, String aaValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetParameter, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetParameter.InputParameter(inIndex++), aTarget));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetParameter.InputParameter(inIndex++), aName));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetParameter.InputParameter(inIndex++), aValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetParameter(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Set a delegate to be run when the ConfigurationXml state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkConfiguration1 instance will not overlap.</remarks>
        /// <param name="aConfigurationXmlChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyConfigurationXmlChanged(CallbackPropertyChanged aConfigurationXmlChanged)
        {
            lock (this)
            {
                iConfigurationXmlChanged = aConfigurationXmlChanged;
            }
        }

        private void ConfigurationXmlPropertyChanged()
        {
            lock (this)
            {
                if (iConfigurationXmlChanged != null)
                {
                    iConfigurationXmlChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ParameterXml state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkConfiguration1 instance will not overlap.</remarks>
        /// <param name="aParameterXmlChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyParameterXmlChanged(CallbackPropertyChanged aParameterXmlChanged)
        {
            lock (this)
            {
                iParameterXmlChanged = aParameterXmlChanged;
            }
        }

        private void ParameterXmlPropertyChanged()
        {
            lock (this)
            {
                if (iParameterXmlChanged != null)
                {
                    iParameterXmlChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the ConfigurationXml property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aConfigurationXml">Will be set to the value of the property</param>
        public String PropertyConfigurationXml()
        {
            return iConfigurationXml.Value();
        }

        /// <summary>
        /// Query the value of the ParameterXml property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aParameterXml">Will be set to the value of the property</param>
        public String PropertyParameterXml()
        {
            return iParameterXml.Value();
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkConfiguration1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProxy();
                iHandle = IntPtr.Zero;
                iActionConfigurationXml.Dispose();
                iActionParameterXml.Dispose();
                iActionSetParameter.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

