using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgConnectionManager2 : ICpProxy, IDisposable
    {
        void SyncGetProtocolInfo(out string aSource, out string aSink);
        void BeginGetProtocolInfo(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetProtocolInfo(uint aAsyncHandle, out string aSource, out string aSink);
        void SyncPrepareForConnection(string aRemoteProtocolInfo, string aPeerConnectionManager, int aPeerConnectionID, string aDirection, out int aConnectionID, out int aAVTransportID, out int aRcsID);
        void BeginPrepareForConnection(string aRemoteProtocolInfo, string aPeerConnectionManager, int aPeerConnectionID, string aDirection, CpProxy.CallbackAsyncComplete aCallback);
        void EndPrepareForConnection(uint aAsyncHandle, out int aConnectionID, out int aAVTransportID, out int aRcsID);
        void SyncConnectionComplete(int aConnectionID);
        void BeginConnectionComplete(int aConnectionID, CpProxy.CallbackAsyncComplete aCallback);
        void EndConnectionComplete(uint aAsyncHandle);
        void SyncGetCurrentConnectionIDs(out string aConnectionIDs);
        void BeginGetCurrentConnectionIDs(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetCurrentConnectionIDs(uint aAsyncHandle, out string aConnectionIDs);
        void SyncGetCurrentConnectionInfo(int aConnectionID, out int aRcsID, out int aAVTransportID, out string aProtocolInfo, out string aPeerConnectionManager, out int aPeerConnectionID, out string aDirection, out string aStatus);
        void BeginGetCurrentConnectionInfo(int aConnectionID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetCurrentConnectionInfo(uint aAsyncHandle, out int aRcsID, out int aAVTransportID, out string aProtocolInfo, out string aPeerConnectionManager, out int aPeerConnectionID, out string aDirection, out string aStatus);

        void SetPropertySourceProtocolInfoChanged(CpProxy.CallbackPropertyChanged aSourceProtocolInfoChanged);
        void PropertySourceProtocolInfo(out string aSourceProtocolInfo);
        void SetPropertySinkProtocolInfoChanged(CpProxy.CallbackPropertyChanged aSinkProtocolInfoChanged);
        void PropertySinkProtocolInfo(out string aSinkProtocolInfo);
        void SetPropertyCurrentConnectionIDsChanged(CpProxy.CallbackPropertyChanged aCurrentConnectionIDsChanged);
        void PropertyCurrentConnectionIDs(out string aCurrentConnectionIDs);
    }

    public class CpProxyUpnpOrgConnectionManager2 : CpProxy, IDisposable, ICpProxyUpnpOrgConnectionManager2
    {
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern uint CpProxyUpnpOrgConnectionManager2Create(uint aDeviceHandle);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern void CpProxyUpnpOrgConnectionManager2Destroy(uint aHandle);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2SyncGetProtocolInfo(uint aHandle, char** aSource, char** aSink);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2BeginGetProtocolInfo(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe int CpProxyUpnpOrgConnectionManager2EndGetProtocolInfo(uint aHandle, uint aAsync, char** aSource, char** aSink);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2SyncPrepareForConnection(uint aHandle, char* aRemoteProtocolInfo, char* aPeerConnectionManager, int aPeerConnectionID, char* aDirection, int* aConnectionID, int* aAVTransportID, int* aRcsID);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2BeginPrepareForConnection(uint aHandle, char* aRemoteProtocolInfo, char* aPeerConnectionManager, int aPeerConnectionID, char* aDirection, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe int CpProxyUpnpOrgConnectionManager2EndPrepareForConnection(uint aHandle, uint aAsync, int* aConnectionID, int* aAVTransportID, int* aRcsID);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2SyncConnectionComplete(uint aHandle, int aConnectionID);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2BeginConnectionComplete(uint aHandle, int aConnectionID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe int CpProxyUpnpOrgConnectionManager2EndConnectionComplete(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2SyncGetCurrentConnectionIDs(uint aHandle, char** aConnectionIDs);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2BeginGetCurrentConnectionIDs(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe int CpProxyUpnpOrgConnectionManager2EndGetCurrentConnectionIDs(uint aHandle, uint aAsync, char** aConnectionIDs);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2SyncGetCurrentConnectionInfo(uint aHandle, int aConnectionID, int* aRcsID, int* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int* aPeerConnectionID, char** aDirection, char** aStatus);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2BeginGetCurrentConnectionInfo(uint aHandle, int aConnectionID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe int CpProxyUpnpOrgConnectionManager2EndGetCurrentConnectionInfo(uint aHandle, uint aAsync, int* aRcsID, int* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int* aPeerConnectionID, char** aDirection, char** aStatus);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern void CpProxyUpnpOrgConnectionManager2SetPropertySourceProtocolInfoChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern void CpProxyUpnpOrgConnectionManager2SetPropertySinkProtocolInfoChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern void CpProxyUpnpOrgConnectionManager2SetPropertyCurrentConnectionIDsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2PropertySourceProtocolInfo(uint aHandle, char** aSourceProtocolInfo);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2PropertySinkProtocolInfo(uint aHandle, char** aSinkProtocolInfo);
        [DllImport("CpUpnpOrgConnectionManager2")]
        static extern unsafe void CpProxyUpnpOrgConnectionManager2PropertyCurrentConnectionIDs(uint aHandle, char** aCurrentConnectionIDs);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iSourceProtocolInfoChanged;
        private CallbackPropertyChanged iSinkProtocolInfoChanged;
        private CallbackPropertyChanged iCurrentConnectionIDsChanged;
        private Callback iCallbackSourceProtocolInfoChanged;
        private Callback iCallbackSinkProtocolInfoChanged;
        private Callback iCallbackCurrentConnectionIDsChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgConnectionManager2(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgConnectionManager2Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aSource"></param>
        /// <param name="aSink"></param>
        public unsafe void SyncGetProtocolInfo(out string aSource, out string aSink)
        {
			char* source;
			char* sink;
			{
				CpProxyUpnpOrgConnectionManager2SyncGetProtocolInfo(iHandle, &source, &sink);
			}
            aSource = Marshal.PtrToStringAnsi((IntPtr)source);
            ZappFree(source);
            aSink = Marshal.PtrToStringAnsi((IntPtr)sink);
            ZappFree(sink);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetProtocolInfo().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetProtocolInfo(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgConnectionManager2BeginGetProtocolInfo(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aSource"></param>
        /// <param name="aSink"></param>
        public unsafe void EndGetProtocolInfo(uint aAsyncHandle, out string aSource, out string aSink)
        {
			char* source;
			char* sink;
			{
				if (0 != CpProxyUpnpOrgConnectionManager2EndGetProtocolInfo(iHandle, aAsyncHandle, &source, &sink))
				{
					throw(new ProxyError());
				}
			}
            aSource = Marshal.PtrToStringAnsi((IntPtr)source);
            ZappFree(source);
            aSink = Marshal.PtrToStringAnsi((IntPtr)sink);
            ZappFree(sink);
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
        public unsafe void SyncPrepareForConnection(string aRemoteProtocolInfo, string aPeerConnectionManager, int aPeerConnectionID, string aDirection, out int aConnectionID, out int aAVTransportID, out int aRcsID)
        {
			char* remoteProtocolInfo = (char*)Marshal.StringToHGlobalAnsi(aRemoteProtocolInfo);
			char* peerConnectionManager = (char*)Marshal.StringToHGlobalAnsi(aPeerConnectionManager);
			char* direction = (char*)Marshal.StringToHGlobalAnsi(aDirection);
			fixed (int* connectionID = &aConnectionID)
			fixed (int* aVTransportID = &aAVTransportID)
			fixed (int* rcsID = &aRcsID)
			{
				CpProxyUpnpOrgConnectionManager2SyncPrepareForConnection(iHandle, remoteProtocolInfo, peerConnectionManager, aPeerConnectionID, direction, connectionID, aVTransportID, rcsID);
			}
			Marshal.FreeHGlobal((IntPtr)remoteProtocolInfo);
			Marshal.FreeHGlobal((IntPtr)peerConnectionManager);
			Marshal.FreeHGlobal((IntPtr)direction);
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
        public unsafe void BeginPrepareForConnection(string aRemoteProtocolInfo, string aPeerConnectionManager, int aPeerConnectionID, string aDirection, CallbackAsyncComplete aCallback)
        {
			char* remoteProtocolInfo = (char*)Marshal.StringToHGlobalAnsi(aRemoteProtocolInfo);
			char* peerConnectionManager = (char*)Marshal.StringToHGlobalAnsi(aPeerConnectionManager);
			char* direction = (char*)Marshal.StringToHGlobalAnsi(aDirection);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgConnectionManager2BeginPrepareForConnection(iHandle, remoteProtocolInfo, peerConnectionManager, aPeerConnectionID, direction, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)remoteProtocolInfo);
			Marshal.FreeHGlobal((IntPtr)peerConnectionManager);
			Marshal.FreeHGlobal((IntPtr)direction);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aConnectionID"></param>
        /// <param name="aAVTransportID"></param>
        /// <param name="aRcsID"></param>
        public unsafe void EndPrepareForConnection(uint aAsyncHandle, out int aConnectionID, out int aAVTransportID, out int aRcsID)
        {
			fixed (int* connectionID = &aConnectionID)
			fixed (int* aVTransportID = &aAVTransportID)
			fixed (int* rcsID = &aRcsID)
			{
				if (0 != CpProxyUpnpOrgConnectionManager2EndPrepareForConnection(iHandle, aAsyncHandle, connectionID, aVTransportID, rcsID))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aConnectionID"></param>
        public unsafe void SyncConnectionComplete(int aConnectionID)
        {
			{
				CpProxyUpnpOrgConnectionManager2SyncConnectionComplete(iHandle, aConnectionID);
			}
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
        public unsafe void BeginConnectionComplete(int aConnectionID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgConnectionManager2BeginConnectionComplete(iHandle, aConnectionID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndConnectionComplete(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgConnectionManager2EndConnectionComplete(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aConnectionIDs"></param>
        public unsafe void SyncGetCurrentConnectionIDs(out string aConnectionIDs)
        {
			char* connectionIDs;
			{
				CpProxyUpnpOrgConnectionManager2SyncGetCurrentConnectionIDs(iHandle, &connectionIDs);
			}
            aConnectionIDs = Marshal.PtrToStringAnsi((IntPtr)connectionIDs);
            ZappFree(connectionIDs);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetCurrentConnectionIDs().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetCurrentConnectionIDs(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgConnectionManager2BeginGetCurrentConnectionIDs(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aConnectionIDs"></param>
        public unsafe void EndGetCurrentConnectionIDs(uint aAsyncHandle, out string aConnectionIDs)
        {
			char* connectionIDs;
			{
				if (0 != CpProxyUpnpOrgConnectionManager2EndGetCurrentConnectionIDs(iHandle, aAsyncHandle, &connectionIDs))
				{
					throw(new ProxyError());
				}
			}
            aConnectionIDs = Marshal.PtrToStringAnsi((IntPtr)connectionIDs);
            ZappFree(connectionIDs);
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
        public unsafe void SyncGetCurrentConnectionInfo(int aConnectionID, out int aRcsID, out int aAVTransportID, out string aProtocolInfo, out string aPeerConnectionManager, out int aPeerConnectionID, out string aDirection, out string aStatus)
        {
			char* protocolInfo;
			char* peerConnectionManager;
			char* direction;
			char* status;
			fixed (int* rcsID = &aRcsID)
			fixed (int* aVTransportID = &aAVTransportID)
			fixed (int* peerConnectionID = &aPeerConnectionID)
			{
				CpProxyUpnpOrgConnectionManager2SyncGetCurrentConnectionInfo(iHandle, aConnectionID, rcsID, aVTransportID, &protocolInfo, &peerConnectionManager, peerConnectionID, &direction, &status);
			}
            aProtocolInfo = Marshal.PtrToStringAnsi((IntPtr)protocolInfo);
            ZappFree(protocolInfo);
            aPeerConnectionManager = Marshal.PtrToStringAnsi((IntPtr)peerConnectionManager);
            ZappFree(peerConnectionManager);
            aDirection = Marshal.PtrToStringAnsi((IntPtr)direction);
            ZappFree(direction);
            aStatus = Marshal.PtrToStringAnsi((IntPtr)status);
            ZappFree(status);
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
        public unsafe void BeginGetCurrentConnectionInfo(int aConnectionID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgConnectionManager2BeginGetCurrentConnectionInfo(iHandle, aConnectionID, iActionComplete, ptr);
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
        public unsafe void EndGetCurrentConnectionInfo(uint aAsyncHandle, out int aRcsID, out int aAVTransportID, out string aProtocolInfo, out string aPeerConnectionManager, out int aPeerConnectionID, out string aDirection, out string aStatus)
        {
			char* protocolInfo;
			char* peerConnectionManager;
			char* direction;
			char* status;
			fixed (int* rcsID = &aRcsID)
			fixed (int* aVTransportID = &aAVTransportID)
			fixed (int* peerConnectionID = &aPeerConnectionID)
			{
				if (0 != CpProxyUpnpOrgConnectionManager2EndGetCurrentConnectionInfo(iHandle, aAsyncHandle, rcsID, aVTransportID, &protocolInfo, &peerConnectionManager, peerConnectionID, &direction, &status))
				{
					throw(new ProxyError());
				}
			}
            aProtocolInfo = Marshal.PtrToStringAnsi((IntPtr)protocolInfo);
            ZappFree(protocolInfo);
            aPeerConnectionManager = Marshal.PtrToStringAnsi((IntPtr)peerConnectionManager);
            ZappFree(peerConnectionManager);
            aDirection = Marshal.PtrToStringAnsi((IntPtr)direction);
            ZappFree(direction);
            aStatus = Marshal.PtrToStringAnsi((IntPtr)status);
            ZappFree(status);
        }

        /// <summary>
        /// Set a delegate to be run when the SourceProtocolInfo state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgConnectionManager2 instance will not overlap.</remarks>
        /// <param name="aSourceProtocolInfoChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySourceProtocolInfoChanged(CallbackPropertyChanged aSourceProtocolInfoChanged)
        {
            iSourceProtocolInfoChanged = aSourceProtocolInfoChanged;
            iCallbackSourceProtocolInfoChanged = new Callback(PropertySourceProtocolInfoChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgConnectionManager2SetPropertySourceProtocolInfoChanged(iHandle, iCallbackSourceProtocolInfoChanged, ptr);
        }

        private void PropertySourceProtocolInfoChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgConnectionManager2 self = (CpProxyUpnpOrgConnectionManager2)gch.Target;
            self.iSourceProtocolInfoChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the SinkProtocolInfo state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgConnectionManager2 instance will not overlap.</remarks>
        /// <param name="aSinkProtocolInfoChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySinkProtocolInfoChanged(CallbackPropertyChanged aSinkProtocolInfoChanged)
        {
            iSinkProtocolInfoChanged = aSinkProtocolInfoChanged;
            iCallbackSinkProtocolInfoChanged = new Callback(PropertySinkProtocolInfoChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgConnectionManager2SetPropertySinkProtocolInfoChanged(iHandle, iCallbackSinkProtocolInfoChanged, ptr);
        }

        private void PropertySinkProtocolInfoChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgConnectionManager2 self = (CpProxyUpnpOrgConnectionManager2)gch.Target;
            self.iSinkProtocolInfoChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the CurrentConnectionIDs state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgConnectionManager2 instance will not overlap.</remarks>
        /// <param name="aCurrentConnectionIDsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyCurrentConnectionIDsChanged(CallbackPropertyChanged aCurrentConnectionIDsChanged)
        {
            iCurrentConnectionIDsChanged = aCurrentConnectionIDsChanged;
            iCallbackCurrentConnectionIDsChanged = new Callback(PropertyCurrentConnectionIDsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgConnectionManager2SetPropertyCurrentConnectionIDsChanged(iHandle, iCallbackCurrentConnectionIDsChanged, ptr);
        }

        private void PropertyCurrentConnectionIDsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgConnectionManager2 self = (CpProxyUpnpOrgConnectionManager2)gch.Target;
            self.iCurrentConnectionIDsChanged();
        }

        /// <summary>
        /// Query the value of the SourceProtocolInfo property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aSourceProtocolInfo">Will be set to the value of the property</param>
        public unsafe void PropertySourceProtocolInfo(out string aSourceProtocolInfo)
        {
			char* ptr;
            CpProxyUpnpOrgConnectionManager2PropertySourceProtocolInfo(iHandle, &ptr);
            aSourceProtocolInfo = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the SinkProtocolInfo property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aSinkProtocolInfo">Will be set to the value of the property</param>
        public unsafe void PropertySinkProtocolInfo(out string aSinkProtocolInfo)
        {
			char* ptr;
            CpProxyUpnpOrgConnectionManager2PropertySinkProtocolInfo(iHandle, &ptr);
            aSinkProtocolInfo = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the CurrentConnectionIDs property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aCurrentConnectionIDs">Will be set to the value of the property</param>
        public unsafe void PropertyCurrentConnectionIDs(out string aCurrentConnectionIDs)
        {
			char* ptr;
            CpProxyUpnpOrgConnectionManager2PropertyCurrentConnectionIDs(iHandle, &ptr);
            aCurrentConnectionIDs = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgConnectionManager2()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
        {
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                CpProxyUpnpOrgConnectionManager2Destroy(iHandle);
                iHandle = 0;
            }
            iGch.Free();
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
            else
            {
                DisposeProxy();
            }
        }
    }
}

