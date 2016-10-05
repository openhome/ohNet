using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgConnectionManager1 : ICpProxy, IDisposable
    {
        void SyncGetProtocolInfo(out String aSource, out String aSink);
        void BeginGetProtocolInfo(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetProtocolInfo(IntPtr aAsyncHandle, out String aSource, out String aSink);
        void SyncPrepareForConnection(String aRemoteProtocolInfo, String aPeerConnectionManager, int aPeerConnectionID, String aDirection, out int aConnectionID, out int aAVTransportID, out int aRcsID);
        void BeginPrepareForConnection(String aRemoteProtocolInfo, String aPeerConnectionManager, int aPeerConnectionID, String aDirection, CpProxy.CallbackAsyncComplete aCallback);
        void EndPrepareForConnection(IntPtr aAsyncHandle, out int aConnectionID, out int aAVTransportID, out int aRcsID);
        void SyncConnectionComplete(int aConnectionID);
        void BeginConnectionComplete(int aConnectionID, CpProxy.CallbackAsyncComplete aCallback);
        void EndConnectionComplete(IntPtr aAsyncHandle);
        void SyncGetCurrentConnectionIDs(out String aConnectionIDs);
        void BeginGetCurrentConnectionIDs(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetCurrentConnectionIDs(IntPtr aAsyncHandle, out String aConnectionIDs);
        void SyncGetCurrentConnectionInfo(int aConnectionID, out int aRcsID, out int aAVTransportID, out String aProtocolInfo, out String aPeerConnectionManager, out int aPeerConnectionID, out String aDirection, out String aStatus);
        void BeginGetCurrentConnectionInfo(int aConnectionID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetCurrentConnectionInfo(IntPtr aAsyncHandle, out int aRcsID, out int aAVTransportID, out String aProtocolInfo, out String aPeerConnectionManager, out int aPeerConnectionID, out String aDirection, out String aStatus);
        void SetPropertySourceProtocolInfoChanged(System.Action aSourceProtocolInfoChanged);
        String PropertySourceProtocolInfo();
        void SetPropertySinkProtocolInfoChanged(System.Action aSinkProtocolInfoChanged);
        String PropertySinkProtocolInfo();
        void SetPropertyCurrentConnectionIDsChanged(System.Action aCurrentConnectionIDsChanged);
        String PropertyCurrentConnectionIDs();
    }

    internal class SyncGetProtocolInfoUpnpOrgConnectionManager1 : SyncProxyAction
    {
        private CpProxyUpnpOrgConnectionManager1 iService;
        private String iSource;
        private String iSink;

        public SyncGetProtocolInfoUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1 aProxy)
        {
            iService = aProxy;
        }
        public String Source()
        {
            return iSource;
        }
        public String Sink()
        {
            return iSink;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetProtocolInfo(aAsyncHandle, out iSource, out iSink);
        }
    };

    internal class SyncPrepareForConnectionUpnpOrgConnectionManager1 : SyncProxyAction
    {
        private CpProxyUpnpOrgConnectionManager1 iService;
        private int iConnectionID;
        private int iAVTransportID;
        private int iRcsID;

        public SyncPrepareForConnectionUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1 aProxy)
        {
            iService = aProxy;
        }
        public int ConnectionID()
        {
            return iConnectionID;
        }
        public int AVTransportID()
        {
            return iAVTransportID;
        }
        public int RcsID()
        {
            return iRcsID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPrepareForConnection(aAsyncHandle, out iConnectionID, out iAVTransportID, out iRcsID);
        }
    };

    internal class SyncConnectionCompleteUpnpOrgConnectionManager1 : SyncProxyAction
    {
        private CpProxyUpnpOrgConnectionManager1 iService;

        public SyncConnectionCompleteUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndConnectionComplete(aAsyncHandle);
        }
    };

    internal class SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1 : SyncProxyAction
    {
        private CpProxyUpnpOrgConnectionManager1 iService;
        private String iConnectionIDs;

        public SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1 aProxy)
        {
            iService = aProxy;
        }
        public String ConnectionIDs()
        {
            return iConnectionIDs;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetCurrentConnectionIDs(aAsyncHandle, out iConnectionIDs);
        }
    };

    internal class SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1 : SyncProxyAction
    {
        private CpProxyUpnpOrgConnectionManager1 iService;
        private int iRcsID;
        private int iAVTransportID;
        private String iProtocolInfo;
        private String iPeerConnectionManager;
        private int iPeerConnectionID;
        private String iDirection;
        private String iStatus;

        public SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1 aProxy)
        {
            iService = aProxy;
        }
        public int RcsID()
        {
            return iRcsID;
        }
        public int AVTransportID()
        {
            return iAVTransportID;
        }
        public String ProtocolInfo()
        {
            return iProtocolInfo;
        }
        public String PeerConnectionManager()
        {
            return iPeerConnectionManager;
        }
        public int PeerConnectionID()
        {
            return iPeerConnectionID;
        }
        public String Direction()
        {
            return iDirection;
        }
        public String Status()
        {
            return iStatus;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetCurrentConnectionInfo(aAsyncHandle, out iRcsID, out iAVTransportID, out iProtocolInfo, out iPeerConnectionManager, out iPeerConnectionID, out iDirection, out iStatus);
        }
    };

    /// <summary>
    /// Proxy for the upnp.org:ConnectionManager:1 UPnP service
    /// </summary>
    public class CpProxyUpnpOrgConnectionManager1 : CpProxy, IDisposable, ICpProxyUpnpOrgConnectionManager1
    {
        private OpenHome.Net.Core.Action iActionGetProtocolInfo;
        private OpenHome.Net.Core.Action iActionPrepareForConnection;
        private OpenHome.Net.Core.Action iActionConnectionComplete;
        private OpenHome.Net.Core.Action iActionGetCurrentConnectionIDs;
        private OpenHome.Net.Core.Action iActionGetCurrentConnectionInfo;
        private PropertyString iSourceProtocolInfo;
        private PropertyString iSinkProtocolInfo;
        private PropertyString iCurrentConnectionIDs;
        private System.Action iSourceProtocolInfoChanged;
        private System.Action iSinkProtocolInfoChanged;
        private System.Action iCurrentConnectionIDsChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgConnectionManager1(ICpDevice aDevice)
            : base("schemas-upnp-org", "ConnectionManager", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionGetProtocolInfo = new OpenHome.Net.Core.Action("GetProtocolInfo");
            param = new ParameterString("Source", allowedValues);
            iActionGetProtocolInfo.AddOutputParameter(param);
            param = new ParameterString("Sink", allowedValues);
            iActionGetProtocolInfo.AddOutputParameter(param);

            iActionPrepareForConnection = new OpenHome.Net.Core.Action("PrepareForConnection");
            param = new ParameterString("RemoteProtocolInfo", allowedValues);
            iActionPrepareForConnection.AddInputParameter(param);
            param = new ParameterString("PeerConnectionManager", allowedValues);
            iActionPrepareForConnection.AddInputParameter(param);
            param = new ParameterInt("PeerConnectionID");
            iActionPrepareForConnection.AddInputParameter(param);
            allowedValues.Add("Input");
            allowedValues.Add("Output");
            param = new ParameterString("Direction", allowedValues);
            iActionPrepareForConnection.AddInputParameter(param);
            allowedValues.Clear();
            param = new ParameterInt("ConnectionID");
            iActionPrepareForConnection.AddOutputParameter(param);
            param = new ParameterInt("AVTransportID");
            iActionPrepareForConnection.AddOutputParameter(param);
            param = new ParameterInt("RcsID");
            iActionPrepareForConnection.AddOutputParameter(param);

            iActionConnectionComplete = new OpenHome.Net.Core.Action("ConnectionComplete");
            param = new ParameterInt("ConnectionID");
            iActionConnectionComplete.AddInputParameter(param);

            iActionGetCurrentConnectionIDs = new OpenHome.Net.Core.Action("GetCurrentConnectionIDs");
            param = new ParameterString("ConnectionIDs", allowedValues);
            iActionGetCurrentConnectionIDs.AddOutputParameter(param);

            iActionGetCurrentConnectionInfo = new OpenHome.Net.Core.Action("GetCurrentConnectionInfo");
            param = new ParameterInt("ConnectionID");
            iActionGetCurrentConnectionInfo.AddInputParameter(param);
            param = new ParameterInt("RcsID");
            iActionGetCurrentConnectionInfo.AddOutputParameter(param);
            param = new ParameterInt("AVTransportID");
            iActionGetCurrentConnectionInfo.AddOutputParameter(param);
            param = new ParameterString("ProtocolInfo", allowedValues);
            iActionGetCurrentConnectionInfo.AddOutputParameter(param);
            param = new ParameterString("PeerConnectionManager", allowedValues);
            iActionGetCurrentConnectionInfo.AddOutputParameter(param);
            param = new ParameterInt("PeerConnectionID");
            iActionGetCurrentConnectionInfo.AddOutputParameter(param);
            allowedValues.Add("Input");
            allowedValues.Add("Output");
            param = new ParameterString("Direction", allowedValues);
            iActionGetCurrentConnectionInfo.AddOutputParameter(param);
            allowedValues.Clear();
            allowedValues.Add("OK");
            allowedValues.Add("ContentFormatMismatch");
            allowedValues.Add("InsufficientBandwidth");
            allowedValues.Add("UnreliableChannel");
            allowedValues.Add("Unknown");
            param = new ParameterString("Status", allowedValues);
            iActionGetCurrentConnectionInfo.AddOutputParameter(param);
            allowedValues.Clear();

            iSourceProtocolInfo = new PropertyString("SourceProtocolInfo", SourceProtocolInfoPropertyChanged);
            AddProperty(iSourceProtocolInfo);
            iSinkProtocolInfo = new PropertyString("SinkProtocolInfo", SinkProtocolInfoPropertyChanged);
            AddProperty(iSinkProtocolInfo);
            iCurrentConnectionIDs = new PropertyString("CurrentConnectionIDs", CurrentConnectionIDsPropertyChanged);
            AddProperty(iCurrentConnectionIDs);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aSource"></param>
        /// <param name="aSink"></param>
        public void SyncGetProtocolInfo(out String aSource, out String aSink)
        {
            SyncGetProtocolInfoUpnpOrgConnectionManager1 sync = new SyncGetProtocolInfoUpnpOrgConnectionManager1(this);
            BeginGetProtocolInfo(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSource = sync.Source();
            aSink = sync.Sink();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetProtocolInfo().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetProtocolInfo(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetProtocolInfo, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetProtocolInfo.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetProtocolInfo.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aSource"></param>
        /// <param name="aSink"></param>
        public void EndGetProtocolInfo(IntPtr aAsyncHandle, out String aSource, out String aSink)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aSource = Invocation.OutputString(aAsyncHandle, index++);
            aSink = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRemoteProtocolInfo"></param>
        /// <param name="aPeerConnectionManager"></param>
        /// <param name="aPeerConnectionID"></param>
        /// <param name="aDirection"></param>
        /// <param name="aConnectionID"></param>
        /// <param name="aAVTransportID"></param>
        /// <param name="aRcsID"></param>
        public void SyncPrepareForConnection(String aRemoteProtocolInfo, String aPeerConnectionManager, int aPeerConnectionID, String aDirection, out int aConnectionID, out int aAVTransportID, out int aRcsID)
        {
            SyncPrepareForConnectionUpnpOrgConnectionManager1 sync = new SyncPrepareForConnectionUpnpOrgConnectionManager1(this);
            BeginPrepareForConnection(aRemoteProtocolInfo, aPeerConnectionManager, aPeerConnectionID, aDirection, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aConnectionID = sync.ConnectionID();
            aAVTransportID = sync.AVTransportID();
            aRcsID = sync.RcsID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPrepareForConnection().</remarks>
        /// <param name="aRemoteProtocolInfo"></param>
        /// <param name="aPeerConnectionManager"></param>
        /// <param name="aPeerConnectionID"></param>
        /// <param name="aDirection"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginPrepareForConnection(String aRemoteProtocolInfo, String aPeerConnectionManager, int aPeerConnectionID, String aDirection, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionPrepareForConnection, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionPrepareForConnection.InputParameter(inIndex++), aRemoteProtocolInfo));
            invocation.AddInput(new ArgumentString((ParameterString)iActionPrepareForConnection.InputParameter(inIndex++), aPeerConnectionManager));
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionPrepareForConnection.InputParameter(inIndex++), aPeerConnectionID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionPrepareForConnection.InputParameter(inIndex++), aDirection));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionPrepareForConnection.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionPrepareForConnection.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionPrepareForConnection.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aConnectionID"></param>
        /// <param name="aAVTransportID"></param>
        /// <param name="aRcsID"></param>
        public void EndPrepareForConnection(IntPtr aAsyncHandle, out int aConnectionID, out int aAVTransportID, out int aRcsID)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aConnectionID = Invocation.OutputInt(aAsyncHandle, index++);
            aAVTransportID = Invocation.OutputInt(aAsyncHandle, index++);
            aRcsID = Invocation.OutputInt(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aConnectionID"></param>
        public void SyncConnectionComplete(int aConnectionID)
        {
            SyncConnectionCompleteUpnpOrgConnectionManager1 sync = new SyncConnectionCompleteUpnpOrgConnectionManager1(this);
            BeginConnectionComplete(aConnectionID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndConnectionComplete().</remarks>
        /// <param name="aConnectionID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginConnectionComplete(int aConnectionID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionConnectionComplete, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionConnectionComplete.InputParameter(inIndex++), aConnectionID));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndConnectionComplete(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aConnectionIDs"></param>
        public void SyncGetCurrentConnectionIDs(out String aConnectionIDs)
        {
            SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1 sync = new SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1(this);
            BeginGetCurrentConnectionIDs(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aConnectionIDs = sync.ConnectionIDs();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetCurrentConnectionIDs().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetCurrentConnectionIDs(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetCurrentConnectionIDs, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetCurrentConnectionIDs.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aConnectionIDs"></param>
        public void EndGetCurrentConnectionIDs(IntPtr aAsyncHandle, out String aConnectionIDs)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aConnectionIDs = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aConnectionID"></param>
        /// <param name="aRcsID"></param>
        /// <param name="aAVTransportID"></param>
        /// <param name="aProtocolInfo"></param>
        /// <param name="aPeerConnectionManager"></param>
        /// <param name="aPeerConnectionID"></param>
        /// <param name="aDirection"></param>
        /// <param name="aStatus"></param>
        public void SyncGetCurrentConnectionInfo(int aConnectionID, out int aRcsID, out int aAVTransportID, out String aProtocolInfo, out String aPeerConnectionManager, out int aPeerConnectionID, out String aDirection, out String aStatus)
        {
            SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1 sync = new SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1(this);
            BeginGetCurrentConnectionInfo(aConnectionID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRcsID = sync.RcsID();
            aAVTransportID = sync.AVTransportID();
            aProtocolInfo = sync.ProtocolInfo();
            aPeerConnectionManager = sync.PeerConnectionManager();
            aPeerConnectionID = sync.PeerConnectionID();
            aDirection = sync.Direction();
            aStatus = sync.Status();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetCurrentConnectionInfo().</remarks>
        /// <param name="aConnectionID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetCurrentConnectionInfo(int aConnectionID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetCurrentConnectionInfo, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionGetCurrentConnectionInfo.InputParameter(inIndex++), aConnectionID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionGetCurrentConnectionInfo.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionGetCurrentConnectionInfo.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetCurrentConnectionInfo.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetCurrentConnectionInfo.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionGetCurrentConnectionInfo.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetCurrentConnectionInfo.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetCurrentConnectionInfo.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRcsID"></param>
        /// <param name="aAVTransportID"></param>
        /// <param name="aProtocolInfo"></param>
        /// <param name="aPeerConnectionManager"></param>
        /// <param name="aPeerConnectionID"></param>
        /// <param name="aDirection"></param>
        /// <param name="aStatus"></param>
        public void EndGetCurrentConnectionInfo(IntPtr aAsyncHandle, out int aRcsID, out int aAVTransportID, out String aProtocolInfo, out String aPeerConnectionManager, out int aPeerConnectionID, out String aDirection, out String aStatus)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRcsID = Invocation.OutputInt(aAsyncHandle, index++);
            aAVTransportID = Invocation.OutputInt(aAsyncHandle, index++);
            aProtocolInfo = Invocation.OutputString(aAsyncHandle, index++);
            aPeerConnectionManager = Invocation.OutputString(aAsyncHandle, index++);
            aPeerConnectionID = Invocation.OutputInt(aAsyncHandle, index++);
            aDirection = Invocation.OutputString(aAsyncHandle, index++);
            aStatus = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the SourceProtocolInfo state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgConnectionManager1 instance will not overlap.</remarks>
        /// <param name="aSourceProtocolInfoChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySourceProtocolInfoChanged(System.Action aSourceProtocolInfoChanged)
        {
            lock (iPropertyLock)
            {
                iSourceProtocolInfoChanged = aSourceProtocolInfoChanged;
            }
        }

        private void SourceProtocolInfoPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iSourceProtocolInfoChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the SinkProtocolInfo state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgConnectionManager1 instance will not overlap.</remarks>
        /// <param name="aSinkProtocolInfoChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySinkProtocolInfoChanged(System.Action aSinkProtocolInfoChanged)
        {
            lock (iPropertyLock)
            {
                iSinkProtocolInfoChanged = aSinkProtocolInfoChanged;
            }
        }

        private void SinkProtocolInfoPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iSinkProtocolInfoChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the CurrentConnectionIDs state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgConnectionManager1 instance will not overlap.</remarks>
        /// <param name="aCurrentConnectionIDsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyCurrentConnectionIDsChanged(System.Action aCurrentConnectionIDsChanged)
        {
            lock (iPropertyLock)
            {
                iCurrentConnectionIDsChanged = aCurrentConnectionIDsChanged;
            }
        }

        private void CurrentConnectionIDsPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iCurrentConnectionIDsChanged);
            }
        }

        /// <summary>
        /// Query the value of the SourceProtocolInfo property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the SourceProtocolInfo property</returns>
        public String PropertySourceProtocolInfo()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iSourceProtocolInfo.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the SinkProtocolInfo property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the SinkProtocolInfo property</returns>
        public String PropertySinkProtocolInfo()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iSinkProtocolInfo.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the CurrentConnectionIDs property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the CurrentConnectionIDs property</returns>
        public String PropertyCurrentConnectionIDs()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iCurrentConnectionIDs.Value();
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
            iActionGetProtocolInfo.Dispose();
            iActionPrepareForConnection.Dispose();
            iActionConnectionComplete.Dispose();
            iActionGetCurrentConnectionIDs.Dispose();
            iActionGetCurrentConnectionInfo.Dispose();
            iSourceProtocolInfo.Dispose();
            iSinkProtocolInfo.Dispose();
            iCurrentConnectionIDs.Dispose();
        }
    }
}

