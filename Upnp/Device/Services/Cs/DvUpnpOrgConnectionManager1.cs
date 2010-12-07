using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

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
        void GetPropertySourceProtocolInfo(out string aValue);

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
        void GetPropertySinkProtocolInfo(out string aValue);

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
        void GetPropertyCurrentConnectionIDs(out string aValue);
        
    }
    /// <summary>
    /// Provider for the upnp.org:ConnectionManager:1 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgConnectionManager1 : DvProvider, IDisposable, IDvProviderUpnpOrgConnectionManager1
    {
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern IntPtr DvProviderUpnpOrgConnectionManager1Create(IntPtr aDeviceHandle);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvProviderUpnpOrgConnectionManager1Destroy(IntPtr aHandle);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe int DvProviderUpnpOrgConnectionManager1SetPropertySourceProtocolInfo(IntPtr aHandle, char* aValue, uint* aChanged);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe void DvProviderUpnpOrgConnectionManager1GetPropertySourceProtocolInfo(IntPtr aHandle, char** aValue);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe int DvProviderUpnpOrgConnectionManager1SetPropertySinkProtocolInfo(IntPtr aHandle, char* aValue, uint* aChanged);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe void DvProviderUpnpOrgConnectionManager1GetPropertySinkProtocolInfo(IntPtr aHandle, char** aValue);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe int DvProviderUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDs(IntPtr aHandle, char* aValue, uint* aChanged);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe void DvProviderUpnpOrgConnectionManager1GetPropertyCurrentConnectionIDs(IntPtr aHandle, char** aValue);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvProviderUpnpOrgConnectionManager1EnableActionGetProtocolInfo(IntPtr aHandle, CallbackGetProtocolInfo aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvProviderUpnpOrgConnectionManager1EnableActionPrepareForConnection(IntPtr aHandle, CallbackPrepareForConnection aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvProviderUpnpOrgConnectionManager1EnableActionConnectionComplete(IntPtr aHandle, CallbackConnectionComplete aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs(IntPtr aHandle, CallbackGetCurrentConnectionIDs aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo(IntPtr aHandle, CallbackGetCurrentConnectionInfo aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackGetProtocolInfo(IntPtr aPtr, uint aVersion, char** aSource, char** aSink);
        private unsafe delegate int CallbackPrepareForConnection(IntPtr aPtr, uint aVersion, char* aRemoteProtocolInfo, char* aPeerConnectionManager, int aPeerConnectionID, char* aDirection, int* aConnectionID, int* aAVTransportID, int* aRcsID);
        private unsafe delegate int CallbackConnectionComplete(IntPtr aPtr, uint aVersion, int aConnectionID);
        private unsafe delegate int CallbackGetCurrentConnectionIDs(IntPtr aPtr, uint aVersion, char** aConnectionIDs);
        private unsafe delegate int CallbackGetCurrentConnectionInfo(IntPtr aPtr, uint aVersion, int aConnectionID, int* aRcsID, int* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int* aPeerConnectionID, char** aDirection, char** aStatus);

        private GCHandle iGch;
        private CallbackGetProtocolInfo iCallbackGetProtocolInfo;
        private CallbackPrepareForConnection iCallbackPrepareForConnection;
        private CallbackConnectionComplete iCallbackConnectionComplete;
        private CallbackGetCurrentConnectionIDs iCallbackGetCurrentConnectionIDs;
        private CallbackGetCurrentConnectionInfo iCallbackGetCurrentConnectionInfo;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgConnectionManager1(DvDevice aDevice)
        {
            iHandle = DvProviderUpnpOrgConnectionManager1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the SourceProtocolInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertySourceProtocolInfo(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderUpnpOrgConnectionManager1SetPropertySourceProtocolInfo(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the SourceProtocolInfo property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertySourceProtocolInfo(out string aValue)
        {
            char* value;
            DvProviderUpnpOrgConnectionManager1GetPropertySourceProtocolInfo(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the SinkProtocolInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertySinkProtocolInfo(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderUpnpOrgConnectionManager1SetPropertySinkProtocolInfo(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the SinkProtocolInfo property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertySinkProtocolInfo(out string aValue)
        {
            char* value;
            DvProviderUpnpOrgConnectionManager1GetPropertySinkProtocolInfo(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the CurrentConnectionIDs property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyCurrentConnectionIDs(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDs(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the CurrentConnectionIDs property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyCurrentConnectionIDs(out string aValue)
        {
            char* value;
            DvProviderUpnpOrgConnectionManager1GetPropertyCurrentConnectionIDs(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Signal that the action GetProtocolInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetProtocolInfo must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetProtocolInfo()
        {
            iCallbackGetProtocolInfo = new CallbackGetProtocolInfo(DoGetProtocolInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgConnectionManager1EnableActionGetProtocolInfo(iHandle, iCallbackGetProtocolInfo, ptr);
        }

        /// <summary>
        /// Signal that the action PrepareForConnection is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPrepareForConnection must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPrepareForConnection()
        {
            iCallbackPrepareForConnection = new CallbackPrepareForConnection(DoPrepareForConnection);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgConnectionManager1EnableActionPrepareForConnection(iHandle, iCallbackPrepareForConnection, ptr);
        }

        /// <summary>
        /// Signal that the action ConnectionComplete is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoConnectionComplete must be overridden if this is called.</remarks>
        protected unsafe void EnableActionConnectionComplete()
        {
            iCallbackConnectionComplete = new CallbackConnectionComplete(DoConnectionComplete);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgConnectionManager1EnableActionConnectionComplete(iHandle, iCallbackConnectionComplete, ptr);
        }

        /// <summary>
        /// Signal that the action GetCurrentConnectionIDs is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetCurrentConnectionIDs must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetCurrentConnectionIDs()
        {
            iCallbackGetCurrentConnectionIDs = new CallbackGetCurrentConnectionIDs(DoGetCurrentConnectionIDs);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs(iHandle, iCallbackGetCurrentConnectionIDs, ptr);
        }

        /// <summary>
        /// Signal that the action GetCurrentConnectionInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetCurrentConnectionInfo must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetCurrentConnectionInfo()
        {
            iCallbackGetCurrentConnectionInfo = new CallbackGetCurrentConnectionInfo(DoGetCurrentConnectionInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo(iHandle, iCallbackGetCurrentConnectionInfo, ptr);
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

        private static unsafe int DoGetProtocolInfo(IntPtr aPtr, uint aVersion, char** aSource, char** aSink)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgConnectionManager1 self = (DvProviderUpnpOrgConnectionManager1)gch.Target;
            string source;
            string sink;
            self.GetProtocolInfo(aVersion, out source, out sink);
            *aSource = (char*)Marshal.StringToHGlobalAnsi(source).ToPointer();
            *aSink = (char*)Marshal.StringToHGlobalAnsi(sink).ToPointer();
            return 0;
        }

        private static unsafe int DoPrepareForConnection(IntPtr aPtr, uint aVersion, char* aRemoteProtocolInfo, char* aPeerConnectionManager, int aPeerConnectionID, char* aDirection, int* aConnectionID, int* aAVTransportID, int* aRcsID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgConnectionManager1 self = (DvProviderUpnpOrgConnectionManager1)gch.Target;
            string remoteProtocolInfo = Marshal.PtrToStringAnsi((IntPtr)aRemoteProtocolInfo);
            string peerConnectionManager = Marshal.PtrToStringAnsi((IntPtr)aPeerConnectionManager);
            string direction = Marshal.PtrToStringAnsi((IntPtr)aDirection);
            int connectionID;
            int aVTransportID;
            int rcsID;
            self.PrepareForConnection(aVersion, remoteProtocolInfo, peerConnectionManager, aPeerConnectionID, direction, out connectionID, out aVTransportID, out rcsID);
            *aConnectionID = connectionID;
            *aAVTransportID = aVTransportID;
            *aRcsID = rcsID;
            return 0;
        }

        private static unsafe int DoConnectionComplete(IntPtr aPtr, uint aVersion, int aConnectionID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgConnectionManager1 self = (DvProviderUpnpOrgConnectionManager1)gch.Target;
            self.ConnectionComplete(aVersion, aConnectionID);
            return 0;
        }

        private static unsafe int DoGetCurrentConnectionIDs(IntPtr aPtr, uint aVersion, char** aConnectionIDs)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgConnectionManager1 self = (DvProviderUpnpOrgConnectionManager1)gch.Target;
            string connectionIDs;
            self.GetCurrentConnectionIDs(aVersion, out connectionIDs);
            *aConnectionIDs = (char*)Marshal.StringToHGlobalAnsi(connectionIDs).ToPointer();
            return 0;
        }

        private static unsafe int DoGetCurrentConnectionInfo(IntPtr aPtr, uint aVersion, int aConnectionID, int* aRcsID, int* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int* aPeerConnectionID, char** aDirection, char** aStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgConnectionManager1 self = (DvProviderUpnpOrgConnectionManager1)gch.Target;
            int rcsID;
            int aVTransportID;
            string protocolInfo;
            string peerConnectionManager;
            int peerConnectionID;
            string direction;
            string status;
            self.GetCurrentConnectionInfo(aVersion, aConnectionID, out rcsID, out aVTransportID, out protocolInfo, out peerConnectionManager, out peerConnectionID, out direction, out status);
            *aRcsID = rcsID;
            *aAVTransportID = aVTransportID;
            *aProtocolInfo = (char*)Marshal.StringToHGlobalAnsi(protocolInfo).ToPointer();
            *aPeerConnectionManager = (char*)Marshal.StringToHGlobalAnsi(peerConnectionManager).ToPointer();
            *aPeerConnectionID = peerConnectionID;
            *aDirection = (char*)Marshal.StringToHGlobalAnsi(direction).ToPointer();
            *aStatus = (char*)Marshal.StringToHGlobalAnsi(status).ToPointer();
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
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
            }
            DvProviderUpnpOrgConnectionManager1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

