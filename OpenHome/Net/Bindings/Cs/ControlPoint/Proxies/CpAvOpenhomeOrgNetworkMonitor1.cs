using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyAvOpenhomeOrgNetworkMonitor1 : ICpProxy, IDisposable
    {
        void SyncName(out String aName);
        void BeginName(CpProxy.CallbackAsyncComplete aCallback);
        void EndName(IntPtr aAsyncHandle, out String aName);
        void SyncPorts(out uint aSender, out uint aReceiver, out uint aResults);
        void BeginPorts(CpProxy.CallbackAsyncComplete aCallback);
        void EndPorts(IntPtr aAsyncHandle, out uint aSender, out uint aReceiver, out uint aResults);
        void SetPropertyNameChanged(System.Action aNameChanged);
        String PropertyName();
        void SetPropertySenderChanged(System.Action aSenderChanged);
        uint PropertySender();
        void SetPropertyReceiverChanged(System.Action aReceiverChanged);
        uint PropertyReceiver();
        void SetPropertyResultsChanged(System.Action aResultsChanged);
        uint PropertyResults();
    }

    internal class SyncNameAvOpenhomeOrgNetworkMonitor1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgNetworkMonitor1 iService;
        private String iName;

        public SyncNameAvOpenhomeOrgNetworkMonitor1(CpProxyAvOpenhomeOrgNetworkMonitor1 aProxy)
        {
            iService = aProxy;
        }
        public String Name()
        {
            return iName;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndName(aAsyncHandle, out iName);
        }
    };

    internal class SyncPortsAvOpenhomeOrgNetworkMonitor1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgNetworkMonitor1 iService;
        private uint iSender;
        private uint iReceiver;
        private uint iResults;

        public SyncPortsAvOpenhomeOrgNetworkMonitor1(CpProxyAvOpenhomeOrgNetworkMonitor1 aProxy)
        {
            iService = aProxy;
        }
        public uint Sender()
        {
            return iSender;
        }
        public uint Receiver()
        {
            return iReceiver;
        }
        public uint Results()
        {
            return iResults;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPorts(aAsyncHandle, out iSender, out iReceiver, out iResults);
        }
    };

    /// <summary>
    /// Proxy for the av.openhome.org:NetworkMonitor:1 UPnP service
    /// </summary>
    public class CpProxyAvOpenhomeOrgNetworkMonitor1 : CpProxy, IDisposable, ICpProxyAvOpenhomeOrgNetworkMonitor1
    {
        private OpenHome.Net.Core.Action iActionName;
        private OpenHome.Net.Core.Action iActionPorts;
        private PropertyString iName;
        private PropertyUint iSender;
        private PropertyUint iReceiver;
        private PropertyUint iResults;
        private System.Action iNameChanged;
        private System.Action iSenderChanged;
        private System.Action iReceiverChanged;
        private System.Action iResultsChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyAvOpenhomeOrgNetworkMonitor1(CpDevice aDevice)
            : base("av-openhome-org", "NetworkMonitor", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionName = new OpenHome.Net.Core.Action("Name");
            param = new ParameterString("Name", allowedValues);
            iActionName.AddOutputParameter(param);

            iActionPorts = new OpenHome.Net.Core.Action("Ports");
            param = new ParameterUint("Sender");
            iActionPorts.AddOutputParameter(param);
            param = new ParameterUint("Receiver");
            iActionPorts.AddOutputParameter(param);
            param = new ParameterUint("Results");
            iActionPorts.AddOutputParameter(param);

            iName = new PropertyString("Name", NamePropertyChanged);
            AddProperty(iName);
            iSender = new PropertyUint("Sender", SenderPropertyChanged);
            AddProperty(iSender);
            iReceiver = new PropertyUint("Receiver", ReceiverPropertyChanged);
            AddProperty(iReceiver);
            iResults = new PropertyUint("Results", ResultsPropertyChanged);
            AddProperty(iResults);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aName"></param>
        public void SyncName(out String aName)
        {
            SyncNameAvOpenhomeOrgNetworkMonitor1 sync = new SyncNameAvOpenhomeOrgNetworkMonitor1(this);
            BeginName(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aName = sync.Name();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndName().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginName(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionName, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionName.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aName"></param>
        public void EndName(IntPtr aAsyncHandle, out String aName)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aName = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aSender"></param>
        /// <param name="aReceiver"></param>
        /// <param name="aResults"></param>
        public void SyncPorts(out uint aSender, out uint aReceiver, out uint aResults)
        {
            SyncPortsAvOpenhomeOrgNetworkMonitor1 sync = new SyncPortsAvOpenhomeOrgNetworkMonitor1(this);
            BeginPorts(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSender = sync.Sender();
            aReceiver = sync.Receiver();
            aResults = sync.Results();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPorts().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginPorts(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionPorts, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionPorts.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionPorts.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionPorts.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aSender"></param>
        /// <param name="aReceiver"></param>
        /// <param name="aResults"></param>
        public void EndPorts(IntPtr aAsyncHandle, out uint aSender, out uint aReceiver, out uint aResults)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aSender = Invocation.OutputUint(aAsyncHandle, index++);
            aReceiver = Invocation.OutputUint(aAsyncHandle, index++);
            aResults = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the Name state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.</remarks>
        /// <param name="aNameChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyNameChanged(System.Action aNameChanged)
        {
            lock (iPropertyLock)
            {
                iNameChanged = aNameChanged;
            }
        }

        private void NamePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iNameChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Sender state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.</remarks>
        /// <param name="aSenderChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySenderChanged(System.Action aSenderChanged)
        {
            lock (iPropertyLock)
            {
                iSenderChanged = aSenderChanged;
            }
        }

        private void SenderPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iSenderChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Receiver state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.</remarks>
        /// <param name="aReceiverChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyReceiverChanged(System.Action aReceiverChanged)
        {
            lock (iPropertyLock)
            {
                iReceiverChanged = aReceiverChanged;
            }
        }

        private void ReceiverPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iReceiverChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Results state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.</remarks>
        /// <param name="aResultsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyResultsChanged(System.Action aResultsChanged)
        {
            lock (iPropertyLock)
            {
                iResultsChanged = aResultsChanged;
            }
        }

        private void ResultsPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iResultsChanged);
            }
        }

        /// <summary>
        /// Query the value of the Name property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Name property</returns>
        public String PropertyName()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iName.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Sender property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Sender property</returns>
        public uint PropertySender()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iSender.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Receiver property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Receiver property</returns>
        public uint PropertyReceiver()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iReceiver.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Results property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Results property</returns>
        public uint PropertyResults()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iResults.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                DisposeProxy();
                iHandle = IntPtr.Zero;
            }
            iActionName.Dispose();
            iActionPorts.Dispose();
            iName.Dispose();
            iSender.Dispose();
            iReceiver.Dispose();
            iResults.Dispose();
        }
    }
}

