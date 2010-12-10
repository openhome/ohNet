using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgAVTransport2 : ICpProxy, IDisposable
    {
        void SyncSetAVTransportURI(uint aInstanceID, string aCurrentURI, string aCurrentURIMetaData);
        void BeginSetAVTransportURI(uint aInstanceID, string aCurrentURI, string aCurrentURIMetaData, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetAVTransportURI(IntPtr aAsyncHandle);
        void SyncSetNextAVTransportURI(uint aInstanceID, string aNextURI, string aNextURIMetaData);
        void BeginSetNextAVTransportURI(uint aInstanceID, string aNextURI, string aNextURIMetaData, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetNextAVTransportURI(IntPtr aAsyncHandle);
        void SyncGetMediaInfo(uint aInstanceID, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus);
        void BeginGetMediaInfo(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetMediaInfo(IntPtr aAsyncHandle, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus);
        void SyncGetMediaInfo_Ext(uint aInstanceID, out string aCurrentType, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus);
        void BeginGetMediaInfo_Ext(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetMediaInfo_Ext(IntPtr aAsyncHandle, out string aCurrentType, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus);
        void SyncGetTransportInfo(uint aInstanceID, out string aCurrentTransportState, out string aCurrentTransportStatus, out string aCurrentSpeed);
        void BeginGetTransportInfo(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetTransportInfo(IntPtr aAsyncHandle, out string aCurrentTransportState, out string aCurrentTransportStatus, out string aCurrentSpeed);
        void SyncGetPositionInfo(uint aInstanceID, out uint aTrack, out string aTrackDuration, out string aTrackMetaData, out string aTrackURI, out string aRelTime, out string aAbsTime, out int aRelCount, out int aAbsCount);
        void BeginGetPositionInfo(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetPositionInfo(IntPtr aAsyncHandle, out uint aTrack, out string aTrackDuration, out string aTrackMetaData, out string aTrackURI, out string aRelTime, out string aAbsTime, out int aRelCount, out int aAbsCount);
        void SyncGetDeviceCapabilities(uint aInstanceID, out string aPlayMedia, out string aRecMedia, out string aRecQualityModes);
        void BeginGetDeviceCapabilities(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetDeviceCapabilities(IntPtr aAsyncHandle, out string aPlayMedia, out string aRecMedia, out string aRecQualityModes);
        void SyncGetTransportSettings(uint aInstanceID, out string aPlayMode, out string aRecQualityMode);
        void BeginGetTransportSettings(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetTransportSettings(IntPtr aAsyncHandle, out string aPlayMode, out string aRecQualityMode);
        void SyncStop(uint aInstanceID);
        void BeginStop(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndStop(IntPtr aAsyncHandle);
        void SyncPlay(uint aInstanceID, string aSpeed);
        void BeginPlay(uint aInstanceID, string aSpeed, CpProxy.CallbackAsyncComplete aCallback);
        void EndPlay(IntPtr aAsyncHandle);
        void SyncPause(uint aInstanceID);
        void BeginPause(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndPause(IntPtr aAsyncHandle);
        void SyncRecord(uint aInstanceID);
        void BeginRecord(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndRecord(IntPtr aAsyncHandle);
        void SyncSeek(uint aInstanceID, string aUnit, string aTarget);
        void BeginSeek(uint aInstanceID, string aUnit, string aTarget, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeek(IntPtr aAsyncHandle);
        void SyncNext(uint aInstanceID);
        void BeginNext(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndNext(IntPtr aAsyncHandle);
        void SyncPrevious(uint aInstanceID);
        void BeginPrevious(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndPrevious(IntPtr aAsyncHandle);
        void SyncSetPlayMode(uint aInstanceID, string aNewPlayMode);
        void BeginSetPlayMode(uint aInstanceID, string aNewPlayMode, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetPlayMode(IntPtr aAsyncHandle);
        void SyncSetRecordQualityMode(uint aInstanceID, string aNewRecordQualityMode);
        void BeginSetRecordQualityMode(uint aInstanceID, string aNewRecordQualityMode, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRecordQualityMode(IntPtr aAsyncHandle);
        void SyncGetCurrentTransportActions(uint aInstanceID, out string aActions);
        void BeginGetCurrentTransportActions(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetCurrentTransportActions(IntPtr aAsyncHandle, out string aActions);
        void SyncGetDRMState(uint aInstanceID, out string aCurrentDRMState);
        void BeginGetDRMState(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetDRMState(IntPtr aAsyncHandle, out string aCurrentDRMState);
        void SyncGetStateVariables(uint aInstanceID, string aStateVariableList, out string aStateVariableValuePairs);
        void BeginGetStateVariables(uint aInstanceID, string aStateVariableList, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetStateVariables(IntPtr aAsyncHandle, out string aStateVariableValuePairs);
        void SyncSetStateVariables(uint aInstanceID, string aAVTransportUDN, string aServiceType, string aServiceId, string aStateVariableValuePairs, out string aStateVariableList);
        void BeginSetStateVariables(uint aInstanceID, string aAVTransportUDN, string aServiceType, string aServiceId, string aStateVariableValuePairs, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStateVariables(IntPtr aAsyncHandle, out string aStateVariableList);

        void SetPropertyLastChangeChanged(CpProxy.CallbackPropertyChanged aLastChangeChanged);
        void PropertyLastChange(out string aLastChange);
        void SetPropertyDRMStateChanged(CpProxy.CallbackPropertyChanged aDRMStateChanged);
        void PropertyDRMState(out string aDRMState);
    }

    /// <summary>
    /// Proxy for the upnp.org:AVTransport:2 UPnP service
    /// </summary>
    public class CpProxyUpnpOrgAVTransport2 : CpProxy, IDisposable, ICpProxyUpnpOrgAVTransport2
    {
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern IntPtr CpProxyUpnpOrgAVTransport2Create(IntPtr aDeviceHandle);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern void CpProxyUpnpOrgAVTransport2Destroy(IntPtr aHandle);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncSetAVTransportURI(IntPtr aHandle, uint aInstanceID, char* aCurrentURI, char* aCurrentURIMetaData);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginSetAVTransportURI(IntPtr aHandle, uint aInstanceID, char* aCurrentURI, char* aCurrentURIMetaData, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndSetAVTransportURI(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncSetNextAVTransportURI(IntPtr aHandle, uint aInstanceID, char* aNextURI, char* aNextURIMetaData);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginSetNextAVTransportURI(IntPtr aHandle, uint aInstanceID, char* aNextURI, char* aNextURIMetaData, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndSetNextAVTransportURI(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncGetMediaInfo(IntPtr aHandle, uint aInstanceID, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginGetMediaInfo(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndGetMediaInfo(IntPtr aHandle, IntPtr aAsync, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncGetMediaInfo_Ext(IntPtr aHandle, uint aInstanceID, char** aCurrentType, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginGetMediaInfo_Ext(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndGetMediaInfo_Ext(IntPtr aHandle, IntPtr aAsync, char** aCurrentType, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncGetTransportInfo(IntPtr aHandle, uint aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginGetTransportInfo(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndGetTransportInfo(IntPtr aHandle, IntPtr aAsync, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncGetPositionInfo(IntPtr aHandle, uint aInstanceID, uint* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int* aRelCount, int* aAbsCount);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginGetPositionInfo(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndGetPositionInfo(IntPtr aHandle, IntPtr aAsync, uint* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int* aRelCount, int* aAbsCount);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncGetDeviceCapabilities(IntPtr aHandle, uint aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginGetDeviceCapabilities(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndGetDeviceCapabilities(IntPtr aHandle, IntPtr aAsync, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncGetTransportSettings(IntPtr aHandle, uint aInstanceID, char** aPlayMode, char** aRecQualityMode);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginGetTransportSettings(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndGetTransportSettings(IntPtr aHandle, IntPtr aAsync, char** aPlayMode, char** aRecQualityMode);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncStop(IntPtr aHandle, uint aInstanceID);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginStop(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndStop(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncPlay(IntPtr aHandle, uint aInstanceID, char* aSpeed);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginPlay(IntPtr aHandle, uint aInstanceID, char* aSpeed, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndPlay(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncPause(IntPtr aHandle, uint aInstanceID);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginPause(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndPause(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncRecord(IntPtr aHandle, uint aInstanceID);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginRecord(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndRecord(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncSeek(IntPtr aHandle, uint aInstanceID, char* aUnit, char* aTarget);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginSeek(IntPtr aHandle, uint aInstanceID, char* aUnit, char* aTarget, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndSeek(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncNext(IntPtr aHandle, uint aInstanceID);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginNext(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndNext(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncPrevious(IntPtr aHandle, uint aInstanceID);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginPrevious(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndPrevious(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncSetPlayMode(IntPtr aHandle, uint aInstanceID, char* aNewPlayMode);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginSetPlayMode(IntPtr aHandle, uint aInstanceID, char* aNewPlayMode, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndSetPlayMode(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncSetRecordQualityMode(IntPtr aHandle, uint aInstanceID, char* aNewRecordQualityMode);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginSetRecordQualityMode(IntPtr aHandle, uint aInstanceID, char* aNewRecordQualityMode, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndSetRecordQualityMode(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncGetCurrentTransportActions(IntPtr aHandle, uint aInstanceID, char** aActions);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginGetCurrentTransportActions(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndGetCurrentTransportActions(IntPtr aHandle, IntPtr aAsync, char** aActions);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncGetDRMState(IntPtr aHandle, uint aInstanceID, char** aCurrentDRMState);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginGetDRMState(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndGetDRMState(IntPtr aHandle, IntPtr aAsync, char** aCurrentDRMState);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncGetStateVariables(IntPtr aHandle, uint aInstanceID, char* aStateVariableList, char** aStateVariableValuePairs);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginGetStateVariables(IntPtr aHandle, uint aInstanceID, char* aStateVariableList, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndGetStateVariables(IntPtr aHandle, IntPtr aAsync, char** aStateVariableValuePairs);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2SyncSetStateVariables(IntPtr aHandle, uint aInstanceID, char* aAVTransportUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, char** aStateVariableList);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2BeginSetStateVariables(IntPtr aHandle, uint aInstanceID, char* aAVTransportUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe int CpProxyUpnpOrgAVTransport2EndSetStateVariables(IntPtr aHandle, IntPtr aAsync, char** aStateVariableList);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern void CpProxyUpnpOrgAVTransport2SetPropertyLastChangeChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern void CpProxyUpnpOrgAVTransport2SetPropertyDRMStateChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2PropertyLastChange(IntPtr aHandle, char** aLastChange);
        [DllImport("CpUpnpOrgAVTransport2")]
        static extern unsafe void CpProxyUpnpOrgAVTransport2PropertyDRMState(IntPtr aHandle, char** aDRMState);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iLastChangeChanged;
        private CallbackPropertyChanged iDRMStateChanged;
        private Callback iCallbackLastChangeChanged;
        private Callback iCallbackDRMStateChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgAVTransport2(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgAVTransport2Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentURI"></param>
        /// <param name="aCurrentURIMetaData"></param>
        public unsafe void SyncSetAVTransportURI(uint aInstanceID, string aCurrentURI, string aCurrentURIMetaData)
        {
            char* currentURI = (char*)Marshal.StringToHGlobalAnsi(aCurrentURI);
            char* currentURIMetaData = (char*)Marshal.StringToHGlobalAnsi(aCurrentURIMetaData);
            {
                CpProxyUpnpOrgAVTransport2SyncSetAVTransportURI(iHandle, aInstanceID, currentURI, currentURIMetaData);
            }
            Marshal.FreeHGlobal((IntPtr)currentURI);
            Marshal.FreeHGlobal((IntPtr)currentURIMetaData);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetAVTransportURI().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentURI"></param>
        /// <param name="aCurrentURIMetaData"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetAVTransportURI(uint aInstanceID, string aCurrentURI, string aCurrentURIMetaData, CallbackAsyncComplete aCallback)
        {
            char* currentURI = (char*)Marshal.StringToHGlobalAnsi(aCurrentURI);
            char* currentURIMetaData = (char*)Marshal.StringToHGlobalAnsi(aCurrentURIMetaData);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginSetAVTransportURI(iHandle, aInstanceID, currentURI, currentURIMetaData, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)currentURI);
            Marshal.FreeHGlobal((IntPtr)currentURIMetaData);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetAVTransportURI(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndSetAVTransportURI(iHandle, aAsyncHandle))
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
        /// <param name="aInstanceID"></param>
        /// <param name="aNextURI"></param>
        /// <param name="aNextURIMetaData"></param>
        public unsafe void SyncSetNextAVTransportURI(uint aInstanceID, string aNextURI, string aNextURIMetaData)
        {
            char* nextURI = (char*)Marshal.StringToHGlobalAnsi(aNextURI);
            char* nextURIMetaData = (char*)Marshal.StringToHGlobalAnsi(aNextURIMetaData);
            {
                CpProxyUpnpOrgAVTransport2SyncSetNextAVTransportURI(iHandle, aInstanceID, nextURI, nextURIMetaData);
            }
            Marshal.FreeHGlobal((IntPtr)nextURI);
            Marshal.FreeHGlobal((IntPtr)nextURIMetaData);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetNextAVTransportURI().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aNextURI"></param>
        /// <param name="aNextURIMetaData"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetNextAVTransportURI(uint aInstanceID, string aNextURI, string aNextURIMetaData, CallbackAsyncComplete aCallback)
        {
            char* nextURI = (char*)Marshal.StringToHGlobalAnsi(aNextURI);
            char* nextURIMetaData = (char*)Marshal.StringToHGlobalAnsi(aNextURIMetaData);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginSetNextAVTransportURI(iHandle, aInstanceID, nextURI, nextURIMetaData, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)nextURI);
            Marshal.FreeHGlobal((IntPtr)nextURIMetaData);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetNextAVTransportURI(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndSetNextAVTransportURI(iHandle, aAsyncHandle))
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
        /// <param name="aInstanceID"></param>
        /// <param name="aNrTracks"></param>
        /// <param name="aMediaDuration"></param>
        /// <param name="aCurrentURI"></param>
        /// <param name="aCurrentURIMetaData"></param>
        /// <param name="aNextURI"></param>
        /// <param name="aNextURIMetaData"></param>
        /// <param name="aPlayMedium"></param>
        /// <param name="aRecordMedium"></param>
        /// <param name="aWriteStatus"></param>
        public unsafe void SyncGetMediaInfo(uint aInstanceID, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
        {
            char* mediaDuration;
            char* currentURI;
            char* currentURIMetaData;
            char* nextURI;
            char* nextURIMetaData;
            char* playMedium;
            char* recordMedium;
            char* writeStatus;
            fixed (uint* nrTracks = &aNrTracks)
            {
                CpProxyUpnpOrgAVTransport2SyncGetMediaInfo(iHandle, aInstanceID, nrTracks, &mediaDuration, &currentURI, &currentURIMetaData, &nextURI, &nextURIMetaData, &playMedium, &recordMedium, &writeStatus);
            }
            aMediaDuration = Marshal.PtrToStringAnsi((IntPtr)mediaDuration);
            ZappFree(mediaDuration);
            aCurrentURI = Marshal.PtrToStringAnsi((IntPtr)currentURI);
            ZappFree(currentURI);
            aCurrentURIMetaData = Marshal.PtrToStringAnsi((IntPtr)currentURIMetaData);
            ZappFree(currentURIMetaData);
            aNextURI = Marshal.PtrToStringAnsi((IntPtr)nextURI);
            ZappFree(nextURI);
            aNextURIMetaData = Marshal.PtrToStringAnsi((IntPtr)nextURIMetaData);
            ZappFree(nextURIMetaData);
            aPlayMedium = Marshal.PtrToStringAnsi((IntPtr)playMedium);
            ZappFree(playMedium);
            aRecordMedium = Marshal.PtrToStringAnsi((IntPtr)recordMedium);
            ZappFree(recordMedium);
            aWriteStatus = Marshal.PtrToStringAnsi((IntPtr)writeStatus);
            ZappFree(writeStatus);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetMediaInfo().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetMediaInfo(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginGetMediaInfo(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aNrTracks"></param>
        /// <param name="aMediaDuration"></param>
        /// <param name="aCurrentURI"></param>
        /// <param name="aCurrentURIMetaData"></param>
        /// <param name="aNextURI"></param>
        /// <param name="aNextURIMetaData"></param>
        /// <param name="aPlayMedium"></param>
        /// <param name="aRecordMedium"></param>
        /// <param name="aWriteStatus"></param>
        public unsafe void EndGetMediaInfo(IntPtr aAsyncHandle, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
        {
            char* mediaDuration;
            char* currentURI;
            char* currentURIMetaData;
            char* nextURI;
            char* nextURIMetaData;
            char* playMedium;
            char* recordMedium;
            char* writeStatus;
            fixed (uint* nrTracks = &aNrTracks)
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndGetMediaInfo(iHandle, aAsyncHandle, nrTracks, &mediaDuration, &currentURI, &currentURIMetaData, &nextURI, &nextURIMetaData, &playMedium, &recordMedium, &writeStatus))
                {
                    throw(new ProxyError());
                }
            }
            aMediaDuration = Marshal.PtrToStringAnsi((IntPtr)mediaDuration);
            ZappFree(mediaDuration);
            aCurrentURI = Marshal.PtrToStringAnsi((IntPtr)currentURI);
            ZappFree(currentURI);
            aCurrentURIMetaData = Marshal.PtrToStringAnsi((IntPtr)currentURIMetaData);
            ZappFree(currentURIMetaData);
            aNextURI = Marshal.PtrToStringAnsi((IntPtr)nextURI);
            ZappFree(nextURI);
            aNextURIMetaData = Marshal.PtrToStringAnsi((IntPtr)nextURIMetaData);
            ZappFree(nextURIMetaData);
            aPlayMedium = Marshal.PtrToStringAnsi((IntPtr)playMedium);
            ZappFree(playMedium);
            aRecordMedium = Marshal.PtrToStringAnsi((IntPtr)recordMedium);
            ZappFree(recordMedium);
            aWriteStatus = Marshal.PtrToStringAnsi((IntPtr)writeStatus);
            ZappFree(writeStatus);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentType"></param>
        /// <param name="aNrTracks"></param>
        /// <param name="aMediaDuration"></param>
        /// <param name="aCurrentURI"></param>
        /// <param name="aCurrentURIMetaData"></param>
        /// <param name="aNextURI"></param>
        /// <param name="aNextURIMetaData"></param>
        /// <param name="aPlayMedium"></param>
        /// <param name="aRecordMedium"></param>
        /// <param name="aWriteStatus"></param>
        public unsafe void SyncGetMediaInfo_Ext(uint aInstanceID, out string aCurrentType, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
        {
            char* currentType;
            char* mediaDuration;
            char* currentURI;
            char* currentURIMetaData;
            char* nextURI;
            char* nextURIMetaData;
            char* playMedium;
            char* recordMedium;
            char* writeStatus;
            fixed (uint* nrTracks = &aNrTracks)
            {
                CpProxyUpnpOrgAVTransport2SyncGetMediaInfo_Ext(iHandle, aInstanceID, &currentType, nrTracks, &mediaDuration, &currentURI, &currentURIMetaData, &nextURI, &nextURIMetaData, &playMedium, &recordMedium, &writeStatus);
            }
            aCurrentType = Marshal.PtrToStringAnsi((IntPtr)currentType);
            ZappFree(currentType);
            aMediaDuration = Marshal.PtrToStringAnsi((IntPtr)mediaDuration);
            ZappFree(mediaDuration);
            aCurrentURI = Marshal.PtrToStringAnsi((IntPtr)currentURI);
            ZappFree(currentURI);
            aCurrentURIMetaData = Marshal.PtrToStringAnsi((IntPtr)currentURIMetaData);
            ZappFree(currentURIMetaData);
            aNextURI = Marshal.PtrToStringAnsi((IntPtr)nextURI);
            ZappFree(nextURI);
            aNextURIMetaData = Marshal.PtrToStringAnsi((IntPtr)nextURIMetaData);
            ZappFree(nextURIMetaData);
            aPlayMedium = Marshal.PtrToStringAnsi((IntPtr)playMedium);
            ZappFree(playMedium);
            aRecordMedium = Marshal.PtrToStringAnsi((IntPtr)recordMedium);
            ZappFree(recordMedium);
            aWriteStatus = Marshal.PtrToStringAnsi((IntPtr)writeStatus);
            ZappFree(writeStatus);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetMediaInfo_Ext().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetMediaInfo_Ext(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginGetMediaInfo_Ext(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentType"></param>
        /// <param name="aNrTracks"></param>
        /// <param name="aMediaDuration"></param>
        /// <param name="aCurrentURI"></param>
        /// <param name="aCurrentURIMetaData"></param>
        /// <param name="aNextURI"></param>
        /// <param name="aNextURIMetaData"></param>
        /// <param name="aPlayMedium"></param>
        /// <param name="aRecordMedium"></param>
        /// <param name="aWriteStatus"></param>
        public unsafe void EndGetMediaInfo_Ext(IntPtr aAsyncHandle, out string aCurrentType, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
        {
            char* currentType;
            char* mediaDuration;
            char* currentURI;
            char* currentURIMetaData;
            char* nextURI;
            char* nextURIMetaData;
            char* playMedium;
            char* recordMedium;
            char* writeStatus;
            fixed (uint* nrTracks = &aNrTracks)
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndGetMediaInfo_Ext(iHandle, aAsyncHandle, &currentType, nrTracks, &mediaDuration, &currentURI, &currentURIMetaData, &nextURI, &nextURIMetaData, &playMedium, &recordMedium, &writeStatus))
                {
                    throw(new ProxyError());
                }
            }
            aCurrentType = Marshal.PtrToStringAnsi((IntPtr)currentType);
            ZappFree(currentType);
            aMediaDuration = Marshal.PtrToStringAnsi((IntPtr)mediaDuration);
            ZappFree(mediaDuration);
            aCurrentURI = Marshal.PtrToStringAnsi((IntPtr)currentURI);
            ZappFree(currentURI);
            aCurrentURIMetaData = Marshal.PtrToStringAnsi((IntPtr)currentURIMetaData);
            ZappFree(currentURIMetaData);
            aNextURI = Marshal.PtrToStringAnsi((IntPtr)nextURI);
            ZappFree(nextURI);
            aNextURIMetaData = Marshal.PtrToStringAnsi((IntPtr)nextURIMetaData);
            ZappFree(nextURIMetaData);
            aPlayMedium = Marshal.PtrToStringAnsi((IntPtr)playMedium);
            ZappFree(playMedium);
            aRecordMedium = Marshal.PtrToStringAnsi((IntPtr)recordMedium);
            ZappFree(recordMedium);
            aWriteStatus = Marshal.PtrToStringAnsi((IntPtr)writeStatus);
            ZappFree(writeStatus);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentTransportState"></param>
        /// <param name="aCurrentTransportStatus"></param>
        /// <param name="aCurrentSpeed"></param>
        public unsafe void SyncGetTransportInfo(uint aInstanceID, out string aCurrentTransportState, out string aCurrentTransportStatus, out string aCurrentSpeed)
        {
            char* currentTransportState;
            char* currentTransportStatus;
            char* currentSpeed;
            {
                CpProxyUpnpOrgAVTransport2SyncGetTransportInfo(iHandle, aInstanceID, &currentTransportState, &currentTransportStatus, &currentSpeed);
            }
            aCurrentTransportState = Marshal.PtrToStringAnsi((IntPtr)currentTransportState);
            ZappFree(currentTransportState);
            aCurrentTransportStatus = Marshal.PtrToStringAnsi((IntPtr)currentTransportStatus);
            ZappFree(currentTransportStatus);
            aCurrentSpeed = Marshal.PtrToStringAnsi((IntPtr)currentSpeed);
            ZappFree(currentSpeed);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetTransportInfo().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetTransportInfo(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginGetTransportInfo(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentTransportState"></param>
        /// <param name="aCurrentTransportStatus"></param>
        /// <param name="aCurrentSpeed"></param>
        public unsafe void EndGetTransportInfo(IntPtr aAsyncHandle, out string aCurrentTransportState, out string aCurrentTransportStatus, out string aCurrentSpeed)
        {
            char* currentTransportState;
            char* currentTransportStatus;
            char* currentSpeed;
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndGetTransportInfo(iHandle, aAsyncHandle, &currentTransportState, &currentTransportStatus, &currentSpeed))
                {
                    throw(new ProxyError());
                }
            }
            aCurrentTransportState = Marshal.PtrToStringAnsi((IntPtr)currentTransportState);
            ZappFree(currentTransportState);
            aCurrentTransportStatus = Marshal.PtrToStringAnsi((IntPtr)currentTransportStatus);
            ZappFree(currentTransportStatus);
            aCurrentSpeed = Marshal.PtrToStringAnsi((IntPtr)currentSpeed);
            ZappFree(currentSpeed);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aTrack"></param>
        /// <param name="aTrackDuration"></param>
        /// <param name="aTrackMetaData"></param>
        /// <param name="aTrackURI"></param>
        /// <param name="aRelTime"></param>
        /// <param name="aAbsTime"></param>
        /// <param name="aRelCount"></param>
        /// <param name="aAbsCount"></param>
        public unsafe void SyncGetPositionInfo(uint aInstanceID, out uint aTrack, out string aTrackDuration, out string aTrackMetaData, out string aTrackURI, out string aRelTime, out string aAbsTime, out int aRelCount, out int aAbsCount)
        {
            char* trackDuration;
            char* trackMetaData;
            char* trackURI;
            char* relTime;
            char* absTime;
            fixed (uint* track = &aTrack)
            fixed (int* relCount = &aRelCount)
            fixed (int* absCount = &aAbsCount)
            {
                CpProxyUpnpOrgAVTransport2SyncGetPositionInfo(iHandle, aInstanceID, track, &trackDuration, &trackMetaData, &trackURI, &relTime, &absTime, relCount, absCount);
            }
            aTrackDuration = Marshal.PtrToStringAnsi((IntPtr)trackDuration);
            ZappFree(trackDuration);
            aTrackMetaData = Marshal.PtrToStringAnsi((IntPtr)trackMetaData);
            ZappFree(trackMetaData);
            aTrackURI = Marshal.PtrToStringAnsi((IntPtr)trackURI);
            ZappFree(trackURI);
            aRelTime = Marshal.PtrToStringAnsi((IntPtr)relTime);
            ZappFree(relTime);
            aAbsTime = Marshal.PtrToStringAnsi((IntPtr)absTime);
            ZappFree(absTime);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetPositionInfo().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetPositionInfo(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginGetPositionInfo(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aTrack"></param>
        /// <param name="aTrackDuration"></param>
        /// <param name="aTrackMetaData"></param>
        /// <param name="aTrackURI"></param>
        /// <param name="aRelTime"></param>
        /// <param name="aAbsTime"></param>
        /// <param name="aRelCount"></param>
        /// <param name="aAbsCount"></param>
        public unsafe void EndGetPositionInfo(IntPtr aAsyncHandle, out uint aTrack, out string aTrackDuration, out string aTrackMetaData, out string aTrackURI, out string aRelTime, out string aAbsTime, out int aRelCount, out int aAbsCount)
        {
            char* trackDuration;
            char* trackMetaData;
            char* trackURI;
            char* relTime;
            char* absTime;
            fixed (uint* track = &aTrack)
            fixed (int* relCount = &aRelCount)
            fixed (int* absCount = &aAbsCount)
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndGetPositionInfo(iHandle, aAsyncHandle, track, &trackDuration, &trackMetaData, &trackURI, &relTime, &absTime, relCount, absCount))
                {
                    throw(new ProxyError());
                }
            }
            aTrackDuration = Marshal.PtrToStringAnsi((IntPtr)trackDuration);
            ZappFree(trackDuration);
            aTrackMetaData = Marshal.PtrToStringAnsi((IntPtr)trackMetaData);
            ZappFree(trackMetaData);
            aTrackURI = Marshal.PtrToStringAnsi((IntPtr)trackURI);
            ZappFree(trackURI);
            aRelTime = Marshal.PtrToStringAnsi((IntPtr)relTime);
            ZappFree(relTime);
            aAbsTime = Marshal.PtrToStringAnsi((IntPtr)absTime);
            ZappFree(absTime);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aPlayMedia"></param>
        /// <param name="aRecMedia"></param>
        /// <param name="aRecQualityModes"></param>
        public unsafe void SyncGetDeviceCapabilities(uint aInstanceID, out string aPlayMedia, out string aRecMedia, out string aRecQualityModes)
        {
            char* playMedia;
            char* recMedia;
            char* recQualityModes;
            {
                CpProxyUpnpOrgAVTransport2SyncGetDeviceCapabilities(iHandle, aInstanceID, &playMedia, &recMedia, &recQualityModes);
            }
            aPlayMedia = Marshal.PtrToStringAnsi((IntPtr)playMedia);
            ZappFree(playMedia);
            aRecMedia = Marshal.PtrToStringAnsi((IntPtr)recMedia);
            ZappFree(recMedia);
            aRecQualityModes = Marshal.PtrToStringAnsi((IntPtr)recQualityModes);
            ZappFree(recQualityModes);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetDeviceCapabilities().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetDeviceCapabilities(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginGetDeviceCapabilities(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aPlayMedia"></param>
        /// <param name="aRecMedia"></param>
        /// <param name="aRecQualityModes"></param>
        public unsafe void EndGetDeviceCapabilities(IntPtr aAsyncHandle, out string aPlayMedia, out string aRecMedia, out string aRecQualityModes)
        {
            char* playMedia;
            char* recMedia;
            char* recQualityModes;
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndGetDeviceCapabilities(iHandle, aAsyncHandle, &playMedia, &recMedia, &recQualityModes))
                {
                    throw(new ProxyError());
                }
            }
            aPlayMedia = Marshal.PtrToStringAnsi((IntPtr)playMedia);
            ZappFree(playMedia);
            aRecMedia = Marshal.PtrToStringAnsi((IntPtr)recMedia);
            ZappFree(recMedia);
            aRecQualityModes = Marshal.PtrToStringAnsi((IntPtr)recQualityModes);
            ZappFree(recQualityModes);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aPlayMode"></param>
        /// <param name="aRecQualityMode"></param>
        public unsafe void SyncGetTransportSettings(uint aInstanceID, out string aPlayMode, out string aRecQualityMode)
        {
            char* playMode;
            char* recQualityMode;
            {
                CpProxyUpnpOrgAVTransport2SyncGetTransportSettings(iHandle, aInstanceID, &playMode, &recQualityMode);
            }
            aPlayMode = Marshal.PtrToStringAnsi((IntPtr)playMode);
            ZappFree(playMode);
            aRecQualityMode = Marshal.PtrToStringAnsi((IntPtr)recQualityMode);
            ZappFree(recQualityMode);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetTransportSettings().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetTransportSettings(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginGetTransportSettings(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aPlayMode"></param>
        /// <param name="aRecQualityMode"></param>
        public unsafe void EndGetTransportSettings(IntPtr aAsyncHandle, out string aPlayMode, out string aRecQualityMode)
        {
            char* playMode;
            char* recQualityMode;
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndGetTransportSettings(iHandle, aAsyncHandle, &playMode, &recQualityMode))
                {
                    throw(new ProxyError());
                }
            }
            aPlayMode = Marshal.PtrToStringAnsi((IntPtr)playMode);
            ZappFree(playMode);
            aRecQualityMode = Marshal.PtrToStringAnsi((IntPtr)recQualityMode);
            ZappFree(recQualityMode);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        public unsafe void SyncStop(uint aInstanceID)
        {
            {
                CpProxyUpnpOrgAVTransport2SyncStop(iHandle, aInstanceID);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStop().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStop(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginStop(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndStop(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndStop(iHandle, aAsyncHandle))
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
        /// <param name="aInstanceID"></param>
        /// <param name="aSpeed"></param>
        public unsafe void SyncPlay(uint aInstanceID, string aSpeed)
        {
            char* speed = (char*)Marshal.StringToHGlobalAnsi(aSpeed);
            {
                CpProxyUpnpOrgAVTransport2SyncPlay(iHandle, aInstanceID, speed);
            }
            Marshal.FreeHGlobal((IntPtr)speed);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPlay().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aSpeed"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPlay(uint aInstanceID, string aSpeed, CallbackAsyncComplete aCallback)
        {
            char* speed = (char*)Marshal.StringToHGlobalAnsi(aSpeed);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginPlay(iHandle, aInstanceID, speed, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)speed);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndPlay(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndPlay(iHandle, aAsyncHandle))
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
        /// <param name="aInstanceID"></param>
        public unsafe void SyncPause(uint aInstanceID)
        {
            {
                CpProxyUpnpOrgAVTransport2SyncPause(iHandle, aInstanceID);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPause().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPause(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginPause(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndPause(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndPause(iHandle, aAsyncHandle))
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
        /// <param name="aInstanceID"></param>
        public unsafe void SyncRecord(uint aInstanceID)
        {
            {
                CpProxyUpnpOrgAVTransport2SyncRecord(iHandle, aInstanceID);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRecord().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginRecord(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginRecord(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndRecord(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndRecord(iHandle, aAsyncHandle))
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
        /// <param name="aInstanceID"></param>
        /// <param name="aUnit"></param>
        /// <param name="aTarget"></param>
        public unsafe void SyncSeek(uint aInstanceID, string aUnit, string aTarget)
        {
            char* unit = (char*)Marshal.StringToHGlobalAnsi(aUnit);
            char* target = (char*)Marshal.StringToHGlobalAnsi(aTarget);
            {
                CpProxyUpnpOrgAVTransport2SyncSeek(iHandle, aInstanceID, unit, target);
            }
            Marshal.FreeHGlobal((IntPtr)unit);
            Marshal.FreeHGlobal((IntPtr)target);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeek().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aUnit"></param>
        /// <param name="aTarget"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSeek(uint aInstanceID, string aUnit, string aTarget, CallbackAsyncComplete aCallback)
        {
            char* unit = (char*)Marshal.StringToHGlobalAnsi(aUnit);
            char* target = (char*)Marshal.StringToHGlobalAnsi(aTarget);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginSeek(iHandle, aInstanceID, unit, target, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)unit);
            Marshal.FreeHGlobal((IntPtr)target);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSeek(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndSeek(iHandle, aAsyncHandle))
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
        /// <param name="aInstanceID"></param>
        public unsafe void SyncNext(uint aInstanceID)
        {
            {
                CpProxyUpnpOrgAVTransport2SyncNext(iHandle, aInstanceID);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndNext().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginNext(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginNext(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndNext(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndNext(iHandle, aAsyncHandle))
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
        /// <param name="aInstanceID"></param>
        public unsafe void SyncPrevious(uint aInstanceID)
        {
            {
                CpProxyUpnpOrgAVTransport2SyncPrevious(iHandle, aInstanceID);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPrevious().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPrevious(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginPrevious(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndPrevious(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndPrevious(iHandle, aAsyncHandle))
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
        /// <param name="aInstanceID"></param>
        /// <param name="aNewPlayMode"></param>
        public unsafe void SyncSetPlayMode(uint aInstanceID, string aNewPlayMode)
        {
            char* newPlayMode = (char*)Marshal.StringToHGlobalAnsi(aNewPlayMode);
            {
                CpProxyUpnpOrgAVTransport2SyncSetPlayMode(iHandle, aInstanceID, newPlayMode);
            }
            Marshal.FreeHGlobal((IntPtr)newPlayMode);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetPlayMode().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aNewPlayMode"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetPlayMode(uint aInstanceID, string aNewPlayMode, CallbackAsyncComplete aCallback)
        {
            char* newPlayMode = (char*)Marshal.StringToHGlobalAnsi(aNewPlayMode);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginSetPlayMode(iHandle, aInstanceID, newPlayMode, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)newPlayMode);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetPlayMode(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndSetPlayMode(iHandle, aAsyncHandle))
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
        /// <param name="aInstanceID"></param>
        /// <param name="aNewRecordQualityMode"></param>
        public unsafe void SyncSetRecordQualityMode(uint aInstanceID, string aNewRecordQualityMode)
        {
            char* newRecordQualityMode = (char*)Marshal.StringToHGlobalAnsi(aNewRecordQualityMode);
            {
                CpProxyUpnpOrgAVTransport2SyncSetRecordQualityMode(iHandle, aInstanceID, newRecordQualityMode);
            }
            Marshal.FreeHGlobal((IntPtr)newRecordQualityMode);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetRecordQualityMode().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aNewRecordQualityMode"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetRecordQualityMode(uint aInstanceID, string aNewRecordQualityMode, CallbackAsyncComplete aCallback)
        {
            char* newRecordQualityMode = (char*)Marshal.StringToHGlobalAnsi(aNewRecordQualityMode);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginSetRecordQualityMode(iHandle, aInstanceID, newRecordQualityMode, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)newRecordQualityMode);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetRecordQualityMode(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndSetRecordQualityMode(iHandle, aAsyncHandle))
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
        /// <param name="aInstanceID"></param>
        /// <param name="aActions"></param>
        public unsafe void SyncGetCurrentTransportActions(uint aInstanceID, out string aActions)
        {
            char* actions;
            {
                CpProxyUpnpOrgAVTransport2SyncGetCurrentTransportActions(iHandle, aInstanceID, &actions);
            }
            aActions = Marshal.PtrToStringAnsi((IntPtr)actions);
            ZappFree(actions);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetCurrentTransportActions().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetCurrentTransportActions(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginGetCurrentTransportActions(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aActions"></param>
        public unsafe void EndGetCurrentTransportActions(IntPtr aAsyncHandle, out string aActions)
        {
            char* actions;
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndGetCurrentTransportActions(iHandle, aAsyncHandle, &actions))
                {
                    throw(new ProxyError());
                }
            }
            aActions = Marshal.PtrToStringAnsi((IntPtr)actions);
            ZappFree(actions);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentDRMState"></param>
        public unsafe void SyncGetDRMState(uint aInstanceID, out string aCurrentDRMState)
        {
            char* currentDRMState;
            {
                CpProxyUpnpOrgAVTransport2SyncGetDRMState(iHandle, aInstanceID, &currentDRMState);
            }
            aCurrentDRMState = Marshal.PtrToStringAnsi((IntPtr)currentDRMState);
            ZappFree(currentDRMState);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetDRMState().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetDRMState(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginGetDRMState(iHandle, aInstanceID, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentDRMState"></param>
        public unsafe void EndGetDRMState(IntPtr aAsyncHandle, out string aCurrentDRMState)
        {
            char* currentDRMState;
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndGetDRMState(iHandle, aAsyncHandle, &currentDRMState))
                {
                    throw(new ProxyError());
                }
            }
            aCurrentDRMState = Marshal.PtrToStringAnsi((IntPtr)currentDRMState);
            ZappFree(currentDRMState);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aStateVariableList"></param>
        /// <param name="aStateVariableValuePairs"></param>
        public unsafe void SyncGetStateVariables(uint aInstanceID, string aStateVariableList, out string aStateVariableValuePairs)
        {
            char* stateVariableList = (char*)Marshal.StringToHGlobalAnsi(aStateVariableList);
            char* stateVariableValuePairs;
            {
                CpProxyUpnpOrgAVTransport2SyncGetStateVariables(iHandle, aInstanceID, stateVariableList, &stateVariableValuePairs);
            }
            Marshal.FreeHGlobal((IntPtr)stateVariableList);
            aStateVariableValuePairs = Marshal.PtrToStringAnsi((IntPtr)stateVariableValuePairs);
            ZappFree(stateVariableValuePairs);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetStateVariables().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aStateVariableList"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetStateVariables(uint aInstanceID, string aStateVariableList, CallbackAsyncComplete aCallback)
        {
            char* stateVariableList = (char*)Marshal.StringToHGlobalAnsi(aStateVariableList);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginGetStateVariables(iHandle, aInstanceID, stateVariableList, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)stateVariableList);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aStateVariableValuePairs"></param>
        public unsafe void EndGetStateVariables(IntPtr aAsyncHandle, out string aStateVariableValuePairs)
        {
            char* stateVariableValuePairs;
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndGetStateVariables(iHandle, aAsyncHandle, &stateVariableValuePairs))
                {
                    throw(new ProxyError());
                }
            }
            aStateVariableValuePairs = Marshal.PtrToStringAnsi((IntPtr)stateVariableValuePairs);
            ZappFree(stateVariableValuePairs);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aAVTransportUDN"></param>
        /// <param name="aServiceType"></param>
        /// <param name="aServiceId"></param>
        /// <param name="aStateVariableValuePairs"></param>
        /// <param name="aStateVariableList"></param>
        public unsafe void SyncSetStateVariables(uint aInstanceID, string aAVTransportUDN, string aServiceType, string aServiceId, string aStateVariableValuePairs, out string aStateVariableList)
        {
            char* aVTransportUDN = (char*)Marshal.StringToHGlobalAnsi(aAVTransportUDN);
            char* serviceType = (char*)Marshal.StringToHGlobalAnsi(aServiceType);
            char* serviceId = (char*)Marshal.StringToHGlobalAnsi(aServiceId);
            char* stateVariableValuePairs = (char*)Marshal.StringToHGlobalAnsi(aStateVariableValuePairs);
            char* stateVariableList;
            {
                CpProxyUpnpOrgAVTransport2SyncSetStateVariables(iHandle, aInstanceID, aVTransportUDN, serviceType, serviceId, stateVariableValuePairs, &stateVariableList);
            }
            Marshal.FreeHGlobal((IntPtr)aVTransportUDN);
            Marshal.FreeHGlobal((IntPtr)serviceType);
            Marshal.FreeHGlobal((IntPtr)serviceId);
            Marshal.FreeHGlobal((IntPtr)stateVariableValuePairs);
            aStateVariableList = Marshal.PtrToStringAnsi((IntPtr)stateVariableList);
            ZappFree(stateVariableList);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStateVariables().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aAVTransportUDN"></param>
        /// <param name="aServiceType"></param>
        /// <param name="aServiceId"></param>
        /// <param name="aStateVariableValuePairs"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetStateVariables(uint aInstanceID, string aAVTransportUDN, string aServiceType, string aServiceId, string aStateVariableValuePairs, CallbackAsyncComplete aCallback)
        {
            char* aVTransportUDN = (char*)Marshal.StringToHGlobalAnsi(aAVTransportUDN);
            char* serviceType = (char*)Marshal.StringToHGlobalAnsi(aServiceType);
            char* serviceId = (char*)Marshal.StringToHGlobalAnsi(aServiceId);
            char* stateVariableValuePairs = (char*)Marshal.StringToHGlobalAnsi(aStateVariableValuePairs);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport2BeginSetStateVariables(iHandle, aInstanceID, aVTransportUDN, serviceType, serviceId, stateVariableValuePairs, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aVTransportUDN);
            Marshal.FreeHGlobal((IntPtr)serviceType);
            Marshal.FreeHGlobal((IntPtr)serviceId);
            Marshal.FreeHGlobal((IntPtr)stateVariableValuePairs);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aStateVariableList"></param>
        public unsafe void EndSetStateVariables(IntPtr aAsyncHandle, out string aStateVariableList)
        {
            char* stateVariableList;
            {
                if (0 != CpProxyUpnpOrgAVTransport2EndSetStateVariables(iHandle, aAsyncHandle, &stateVariableList))
                {
                    throw(new ProxyError());
                }
            }
            aStateVariableList = Marshal.PtrToStringAnsi((IntPtr)stateVariableList);
            ZappFree(stateVariableList);
        }

        /// <summary>
        /// Set a delegate to be run when the LastChange state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgAVTransport2 instance will not overlap.</remarks>
        /// <param name="aLastChangeChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyLastChangeChanged(CallbackPropertyChanged aLastChangeChanged)
        {
            iLastChangeChanged = aLastChangeChanged;
            iCallbackLastChangeChanged = new Callback(PropertyLastChangeChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgAVTransport2SetPropertyLastChangeChanged(iHandle, iCallbackLastChangeChanged, ptr);
        }

        private void PropertyLastChangeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgAVTransport2 self = (CpProxyUpnpOrgAVTransport2)gch.Target;
            self.iLastChangeChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the DRMState state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgAVTransport2 instance will not overlap.</remarks>
        /// <param name="aDRMStateChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDRMStateChanged(CallbackPropertyChanged aDRMStateChanged)
        {
            iDRMStateChanged = aDRMStateChanged;
            iCallbackDRMStateChanged = new Callback(PropertyDRMStateChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgAVTransport2SetPropertyDRMStateChanged(iHandle, iCallbackDRMStateChanged, ptr);
        }

        private void PropertyDRMStateChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgAVTransport2 self = (CpProxyUpnpOrgAVTransport2)gch.Target;
            self.iDRMStateChanged();
        }

        /// <summary>
        /// Query the value of the LastChange property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aLastChange">Will be set to the value of the property</param>
        public unsafe void PropertyLastChange(out string aLastChange)
        {
            char* ptr;
            CpProxyUpnpOrgAVTransport2PropertyLastChange(iHandle, &ptr);
            aLastChange = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the DRMState property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDRMState">Will be set to the value of the property</param>
        public unsafe void PropertyDRMState(out string aDRMState)
        {
            char* ptr;
            CpProxyUpnpOrgAVTransport2PropertyDRMState(iHandle, &ptr);
            aDRMState = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgAVTransport2()
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
                CpProxyUpnpOrgAVTransport2Destroy(iHandle);
                iHandle = IntPtr.Zero;
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

