using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderUpnpOrgConnectionManager1 : IDisposable
    {

        /// <summary>
        /// Set the value of the SourceProtocolInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertySourceProtocolInfo(string aValue);

        /// <summary>
        /// Get a copy of the value of the SourceProtocolInfo property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertySourceProtocolInfo();

        /// <summary>
        /// Set the value of the SinkProtocolInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertySinkProtocolInfo(string aValue);

        /// <summary>
        /// Get a copy of the value of the SinkProtocolInfo property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertySinkProtocolInfo();

        /// <summary>
        /// Set the value of the CurrentConnectionIDs property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyCurrentConnectionIDs(string aValue);

        /// <summary>
        /// Get a copy of the value of the CurrentConnectionIDs property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyCurrentConnectionIDs();
        
    }
    /// <summary>
    /// Provider for the upnp.org:ConnectionManager:1 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgConnectionManager1 : DvProvider, IDisposable, IDvProviderUpnpOrgConnectionManager1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateGetProtocolInfo;
        private ActionDelegate iDelegatePrepareForConnection;
        private ActionDelegate iDelegateConnectionComplete;
        private ActionDelegate iDelegateGetCurrentConnectionIDs;
        private ActionDelegate iDelegateGetCurrentConnectionInfo;
        private PropertyString iPropertySourceProtocolInfo;
        private PropertyString iPropertySinkProtocolInfo;
        private PropertyString iPropertyCurrentConnectionIDs;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgConnectionManager1(DvDevice aDevice)
            : base(aDevice, "schemas-upnp-org", "ConnectionManager", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertySourceProtocolInfo = new PropertyString(new ParameterString("SourceProtocolInfo", allowedValues));
            AddProperty(iPropertySourceProtocolInfo);
            iPropertySinkProtocolInfo = new PropertyString(new ParameterString("SinkProtocolInfo", allowedValues));
            AddProperty(iPropertySinkProtocolInfo);
            iPropertyCurrentConnectionIDs = new PropertyString(new ParameterString("CurrentConnectionIDs", allowedValues));
            AddProperty(iPropertyCurrentConnectionIDs);
        }

        /// <summary>
        /// Set the value of the SourceProtocolInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySourceProtocolInfo(string aValue)
        {
            return SetPropertyString(iPropertySourceProtocolInfo, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the SourceProtocolInfo property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertySourceProtocolInfo()
        {
            return iPropertySourceProtocolInfo.Value();
        }

        /// <summary>
        /// Set the value of the SinkProtocolInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySinkProtocolInfo(string aValue)
        {
            return SetPropertyString(iPropertySinkProtocolInfo, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the SinkProtocolInfo property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertySinkProtocolInfo()
        {
            return iPropertySinkProtocolInfo.Value();
        }

        /// <summary>
        /// Set the value of the CurrentConnectionIDs property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyCurrentConnectionIDs(string aValue)
        {
            return SetPropertyString(iPropertyCurrentConnectionIDs, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the CurrentConnectionIDs property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyCurrentConnectionIDs()
        {
            return iPropertyCurrentConnectionIDs.Value();
        }

        /// <summary>
        /// Signal that the action GetProtocolInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetProtocolInfo must be overridden if this is called.</remarks>
        protected void EnableActionGetProtocolInfo()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetProtocolInfo");
            action.AddOutputParameter(new ParameterRelated("Source", iPropertySourceProtocolInfo));
            action.AddOutputParameter(new ParameterRelated("Sink", iPropertySinkProtocolInfo));
            iDelegateGetProtocolInfo = new ActionDelegate(DoGetProtocolInfo);
            EnableAction(action, iDelegateGetProtocolInfo, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PrepareForConnection is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPrepareForConnection must be overridden if this is called.</remarks>
        protected void EnableActionPrepareForConnection()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("PrepareForConnection");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RemoteProtocolInfo", allowedValues));
            action.AddInputParameter(new ParameterString("PeerConnectionManager", allowedValues));
            action.AddInputParameter(new ParameterInt("PeerConnectionID"));
            allowedValues.Add("Input");
            allowedValues.Add("Output");
            action.AddInputParameter(new ParameterString("Direction", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterInt("ConnectionID"));
            action.AddOutputParameter(new ParameterInt("AVTransportID"));
            action.AddOutputParameter(new ParameterInt("RcsID"));
            iDelegatePrepareForConnection = new ActionDelegate(DoPrepareForConnection);
            EnableAction(action, iDelegatePrepareForConnection, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ConnectionComplete is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoConnectionComplete must be overridden if this is called.</remarks>
        protected void EnableActionConnectionComplete()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ConnectionComplete");
            action.AddInputParameter(new ParameterInt("ConnectionID"));
            iDelegateConnectionComplete = new ActionDelegate(DoConnectionComplete);
            EnableAction(action, iDelegateConnectionComplete, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetCurrentConnectionIDs is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetCurrentConnectionIDs must be overridden if this is called.</remarks>
        protected void EnableActionGetCurrentConnectionIDs()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetCurrentConnectionIDs");
            action.AddOutputParameter(new ParameterRelated("ConnectionIDs", iPropertyCurrentConnectionIDs));
            iDelegateGetCurrentConnectionIDs = new ActionDelegate(DoGetCurrentConnectionIDs);
            EnableAction(action, iDelegateGetCurrentConnectionIDs, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetCurrentConnectionInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetCurrentConnectionInfo must be overridden if this is called.</remarks>
        protected void EnableActionGetCurrentConnectionInfo()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetCurrentConnectionInfo");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterInt("ConnectionID"));
            action.AddOutputParameter(new ParameterInt("RcsID"));
            action.AddOutputParameter(new ParameterInt("AVTransportID"));
            action.AddOutputParameter(new ParameterString("ProtocolInfo", allowedValues));
            action.AddOutputParameter(new ParameterString("PeerConnectionManager", allowedValues));
            action.AddOutputParameter(new ParameterInt("PeerConnectionID"));
            allowedValues.Add("Input");
            allowedValues.Add("Output");
            action.AddOutputParameter(new ParameterString("Direction", allowedValues));
            allowedValues.Clear();
            allowedValues.Add("OK");
            allowedValues.Add("ContentFormatMismatch");
            allowedValues.Add("InsufficientBandwidth");
            allowedValues.Add("UnreliableChannel");
            allowedValues.Add("Unknown");
            action.AddOutputParameter(new ParameterString("Status", allowedValues));
            allowedValues.Clear();
            iDelegateGetCurrentConnectionInfo = new ActionDelegate(DoGetCurrentConnectionInfo);
            EnableAction(action, iDelegateGetCurrentConnectionInfo, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// GetProtocolInfo action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetProtocolInfo action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetProtocolInfo was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aSource"></param>
        /// <param name="aSink"></param>
        protected virtual void GetProtocolInfo(uint aVersion, out string aSource, out string aSink)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PrepareForConnection action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PrepareForConnection action for the owning device.
        ///
        /// Must be implemented iff EnableActionPrepareForConnection was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRemoteProtocolInfo"></param>
        /// <param name="aPeerConnectionManager"></param>
        /// <param name="aPeerConnectionID"></param>
        /// <param name="aDirection"></param>
        /// <param name="aConnectionID"></param>
        /// <param name="aAVTransportID"></param>
        /// <param name="aRcsID"></param>
        protected virtual void PrepareForConnection(uint aVersion, string aRemoteProtocolInfo, string aPeerConnectionManager, int aPeerConnectionID, string aDirection, out int aConnectionID, out int aAVTransportID, out int aRcsID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ConnectionComplete action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ConnectionComplete action for the owning device.
        ///
        /// Must be implemented iff EnableActionConnectionComplete was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aConnectionID"></param>
        protected virtual void ConnectionComplete(uint aVersion, int aConnectionID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetCurrentConnectionIDs action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetCurrentConnectionIDs action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetCurrentConnectionIDs was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aConnectionIDs"></param>
        protected virtual void GetCurrentConnectionIDs(uint aVersion, out string aConnectionIDs)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetCurrentConnectionInfo action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetCurrentConnectionInfo action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetCurrentConnectionInfo was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aConnectionID"></param>
        /// <param name="aRcsID"></param>
        /// <param name="aAVTransportID"></param>
        /// <param name="aProtocolInfo"></param>
        /// <param name="aPeerConnectionManager"></param>
        /// <param name="aPeerConnectionID"></param>
        /// <param name="aDirection"></param>
        /// <param name="aStatus"></param>
        protected virtual void GetCurrentConnectionInfo(uint aVersion, int aConnectionID, out int aRcsID, out int aAVTransportID, out string aProtocolInfo, out string aPeerConnectionManager, out int aPeerConnectionID, out string aDirection, out string aStatus)
        {
            throw (new ActionDisabledError());
        }

        private static int DoGetProtocolInfo(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgConnectionManager1 self = (DvProviderUpnpOrgConnectionManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string source;
            string sink;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetProtocolInfo(aVersion, out source, out sink);
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
                invocation.WriteString("Source", source);
                invocation.WriteString("Sink", sink);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoPrepareForConnection(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgConnectionManager1 self = (DvProviderUpnpOrgConnectionManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string remoteProtocolInfo;
            string peerConnectionManager;
            int peerConnectionID;
            string direction;
            int connectionID;
            int aVTransportID;
            int rcsID;
            try
            {
                invocation.ReadStart();
                remoteProtocolInfo = invocation.ReadString("RemoteProtocolInfo");
                peerConnectionManager = invocation.ReadString("PeerConnectionManager");
                peerConnectionID = invocation.ReadInt("PeerConnectionID");
                direction = invocation.ReadString("Direction");
                invocation.ReadEnd();
                self.PrepareForConnection(aVersion, remoteProtocolInfo, peerConnectionManager, peerConnectionID, direction, out connectionID, out aVTransportID, out rcsID);
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
                invocation.WriteInt("ConnectionID", connectionID);
                invocation.WriteInt("AVTransportID", aVTransportID);
                invocation.WriteInt("RcsID", rcsID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoConnectionComplete(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgConnectionManager1 self = (DvProviderUpnpOrgConnectionManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int connectionID;
            try
            {
                invocation.ReadStart();
                connectionID = invocation.ReadInt("ConnectionID");
                invocation.ReadEnd();
                self.ConnectionComplete(aVersion, connectionID);
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

        private static int DoGetCurrentConnectionIDs(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgConnectionManager1 self = (DvProviderUpnpOrgConnectionManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string connectionIDs;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetCurrentConnectionIDs(aVersion, out connectionIDs);
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
                invocation.WriteString("ConnectionIDs", connectionIDs);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetCurrentConnectionInfo(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgConnectionManager1 self = (DvProviderUpnpOrgConnectionManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int connectionID;
            int rcsID;
            int aVTransportID;
            string protocolInfo;
            string peerConnectionManager;
            int peerConnectionID;
            string direction;
            string status;
            try
            {
                invocation.ReadStart();
                connectionID = invocation.ReadInt("ConnectionID");
                invocation.ReadEnd();
                self.GetCurrentConnectionInfo(aVersion, connectionID, out rcsID, out aVTransportID, out protocolInfo, out peerConnectionManager, out peerConnectionID, out direction, out status);
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
                invocation.WriteInt("RcsID", rcsID);
                invocation.WriteInt("AVTransportID", aVTransportID);
                invocation.WriteString("ProtocolInfo", protocolInfo);
                invocation.WriteString("PeerConnectionManager", peerConnectionManager);
                invocation.WriteInt("PeerConnectionID", peerConnectionID);
                invocation.WriteString("Direction", direction);
                invocation.WriteString("Status", status);
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

        ~DvProviderUpnpOrgConnectionManager1()
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

