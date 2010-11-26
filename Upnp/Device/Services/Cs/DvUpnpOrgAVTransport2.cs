using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    /// <summary>
    /// Provider for the upnp.org:AVTransport:2 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgAVTransport2 : DvProvider, IDisposable
    {
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern uint DvProviderUpnpOrgAVTransport2Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2Destroy(uint aHandle);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern unsafe int DvProviderUpnpOrgAVTransport2SetPropertyLastChange(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern unsafe void DvProviderUpnpOrgAVTransport2GetPropertyLastChange(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern unsafe int DvProviderUpnpOrgAVTransport2SetPropertyDRMState(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern unsafe void DvProviderUpnpOrgAVTransport2GetPropertyDRMState(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionSetAVTransportURI(uint aHandle, CallbackSetAVTransportURI aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionSetNextAVTransportURI(uint aHandle, CallbackSetNextAVTransportURI aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo(uint aHandle, CallbackGetMediaInfo aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo_Ext(uint aHandle, CallbackGetMediaInfo_Ext aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionGetTransportInfo(uint aHandle, CallbackGetTransportInfo aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionGetPositionInfo(uint aHandle, CallbackGetPositionInfo aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionGetDeviceCapabilities(uint aHandle, CallbackGetDeviceCapabilities aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionGetTransportSettings(uint aHandle, CallbackGetTransportSettings aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionStop(uint aHandle, CallbackStop aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionPlay(uint aHandle, CallbackPlay aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionPause(uint aHandle, CallbackPause aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionRecord(uint aHandle, CallbackRecord aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionSeek(uint aHandle, CallbackSeek aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionNext(uint aHandle, CallbackNext aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionPrevious(uint aHandle, CallbackPrevious aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionSetPlayMode(uint aHandle, CallbackSetPlayMode aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionSetRecordQualityMode(uint aHandle, CallbackSetRecordQualityMode aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionGetCurrentTransportActions(uint aHandle, CallbackGetCurrentTransportActions aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionGetDRMState(uint aHandle, CallbackGetDRMState aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionGetStateVariables(uint aHandle, CallbackGetStateVariables aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvProviderUpnpOrgAVTransport2EnableActionSetStateVariables(uint aHandle, CallbackSetStateVariables aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSetAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aCurrentURI, char* aCurrentURIMetaData);
        private unsafe delegate int CallbackSetNextAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNextURI, char* aNextURIMetaData);
        private unsafe delegate int CallbackGetMediaInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
        private unsafe delegate int CallbackGetMediaInfo_Ext(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentType, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
        private unsafe delegate int CallbackGetTransportInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);
        private unsafe delegate int CallbackGetPositionInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int* aRelCount, int* aAbsCount);
        private unsafe delegate int CallbackGetDeviceCapabilities(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);
        private unsafe delegate int CallbackGetTransportSettings(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aPlayMode, char** aRecQualityMode);
        private unsafe delegate int CallbackStop(IntPtr aPtr, uint aVersion, uint aInstanceID);
        private unsafe delegate int CallbackPlay(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aSpeed);
        private unsafe delegate int CallbackPause(IntPtr aPtr, uint aVersion, uint aInstanceID);
        private unsafe delegate int CallbackRecord(IntPtr aPtr, uint aVersion, uint aInstanceID);
        private unsafe delegate int CallbackSeek(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aUnit, char* aTarget);
        private unsafe delegate int CallbackNext(IntPtr aPtr, uint aVersion, uint aInstanceID);
        private unsafe delegate int CallbackPrevious(IntPtr aPtr, uint aVersion, uint aInstanceID);
        private unsafe delegate int CallbackSetPlayMode(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNewPlayMode);
        private unsafe delegate int CallbackSetRecordQualityMode(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNewRecordQualityMode);
        private unsafe delegate int CallbackGetCurrentTransportActions(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aActions);
        private unsafe delegate int CallbackGetDRMState(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentDRMState);
        private unsafe delegate int CallbackGetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aStateVariableList, char** aStateVariableValuePairs);
        private unsafe delegate int CallbackSetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aAVTransportUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, char** aStateVariableList);

        private GCHandle iGch;
        private CallbackSetAVTransportURI iCallbackSetAVTransportURI;
        private CallbackSetNextAVTransportURI iCallbackSetNextAVTransportURI;
        private CallbackGetMediaInfo iCallbackGetMediaInfo;
        private CallbackGetMediaInfo_Ext iCallbackGetMediaInfo_Ext;
        private CallbackGetTransportInfo iCallbackGetTransportInfo;
        private CallbackGetPositionInfo iCallbackGetPositionInfo;
        private CallbackGetDeviceCapabilities iCallbackGetDeviceCapabilities;
        private CallbackGetTransportSettings iCallbackGetTransportSettings;
        private CallbackStop iCallbackStop;
        private CallbackPlay iCallbackPlay;
        private CallbackPause iCallbackPause;
        private CallbackRecord iCallbackRecord;
        private CallbackSeek iCallbackSeek;
        private CallbackNext iCallbackNext;
        private CallbackPrevious iCallbackPrevious;
        private CallbackSetPlayMode iCallbackSetPlayMode;
        private CallbackSetRecordQualityMode iCallbackSetRecordQualityMode;
        private CallbackGetCurrentTransportActions iCallbackGetCurrentTransportActions;
        private CallbackGetDRMState iCallbackGetDRMState;
        private CallbackGetStateVariables iCallbackGetStateVariables;
        private CallbackSetStateVariables iCallbackSetStateVariables;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgAVTransport2(DvDevice aDevice)
        {
            iHandle = DvProviderUpnpOrgAVTransport2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyLastChange(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderUpnpOrgAVTransport2SetPropertyLastChange(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyLastChange(out string aValue)
        {
            char* value;
            DvProviderUpnpOrgAVTransport2GetPropertyLastChange(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the DRMState property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDRMState(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderUpnpOrgAVTransport2SetPropertyDRMState(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DRMState property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDRMState(out string aValue)
        {
            char* value;
            DvProviderUpnpOrgAVTransport2GetPropertyDRMState(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Signal that the action SetAVTransportURI is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetAVTransportURI must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetAVTransportURI()
        {
            iCallbackSetAVTransportURI = new CallbackSetAVTransportURI(DoSetAVTransportURI);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionSetAVTransportURI(iHandle, iCallbackSetAVTransportURI, ptr);
        }

        /// <summary>
        /// Signal that the action SetNextAVTransportURI is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetNextAVTransportURI must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetNextAVTransportURI()
        {
            iCallbackSetNextAVTransportURI = new CallbackSetNextAVTransportURI(DoSetNextAVTransportURI);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionSetNextAVTransportURI(iHandle, iCallbackSetNextAVTransportURI, ptr);
        }

        /// <summary>
        /// Signal that the action GetMediaInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetMediaInfo must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetMediaInfo()
        {
            iCallbackGetMediaInfo = new CallbackGetMediaInfo(DoGetMediaInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo(iHandle, iCallbackGetMediaInfo, ptr);
        }

        /// <summary>
        /// Signal that the action GetMediaInfo_Ext is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetMediaInfo_Ext must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetMediaInfo_Ext()
        {
            iCallbackGetMediaInfo_Ext = new CallbackGetMediaInfo_Ext(DoGetMediaInfo_Ext);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo_Ext(iHandle, iCallbackGetMediaInfo_Ext, ptr);
        }

        /// <summary>
        /// Signal that the action GetTransportInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetTransportInfo must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetTransportInfo()
        {
            iCallbackGetTransportInfo = new CallbackGetTransportInfo(DoGetTransportInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionGetTransportInfo(iHandle, iCallbackGetTransportInfo, ptr);
        }

        /// <summary>
        /// Signal that the action GetPositionInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetPositionInfo must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetPositionInfo()
        {
            iCallbackGetPositionInfo = new CallbackGetPositionInfo(DoGetPositionInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionGetPositionInfo(iHandle, iCallbackGetPositionInfo, ptr);
        }

        /// <summary>
        /// Signal that the action GetDeviceCapabilities is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetDeviceCapabilities must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetDeviceCapabilities()
        {
            iCallbackGetDeviceCapabilities = new CallbackGetDeviceCapabilities(DoGetDeviceCapabilities);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionGetDeviceCapabilities(iHandle, iCallbackGetDeviceCapabilities, ptr);
        }

        /// <summary>
        /// Signal that the action GetTransportSettings is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetTransportSettings must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetTransportSettings()
        {
            iCallbackGetTransportSettings = new CallbackGetTransportSettings(DoGetTransportSettings);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionGetTransportSettings(iHandle, iCallbackGetTransportSettings, ptr);
        }

        /// <summary>
        /// Signal that the action Stop is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStop must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStop()
        {
            iCallbackStop = new CallbackStop(DoStop);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionStop(iHandle, iCallbackStop, ptr);
        }

        /// <summary>
        /// Signal that the action Play is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPlay must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPlay()
        {
            iCallbackPlay = new CallbackPlay(DoPlay);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionPlay(iHandle, iCallbackPlay, ptr);
        }

        /// <summary>
        /// Signal that the action Pause is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPause must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPause()
        {
            iCallbackPause = new CallbackPause(DoPause);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionPause(iHandle, iCallbackPause, ptr);
        }

        /// <summary>
        /// Signal that the action Record is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoRecord must be overridden if this is called.</remarks>
        protected unsafe void EnableActionRecord()
        {
            iCallbackRecord = new CallbackRecord(DoRecord);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionRecord(iHandle, iCallbackRecord, ptr);
        }

        /// <summary>
        /// Signal that the action Seek is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSeek must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeek()
        {
            iCallbackSeek = new CallbackSeek(DoSeek);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionSeek(iHandle, iCallbackSeek, ptr);
        }

        /// <summary>
        /// Signal that the action Next is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoNext must be overridden if this is called.</remarks>
        protected unsafe void EnableActionNext()
        {
            iCallbackNext = new CallbackNext(DoNext);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionNext(iHandle, iCallbackNext, ptr);
        }

        /// <summary>
        /// Signal that the action Previous is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPrevious must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPrevious()
        {
            iCallbackPrevious = new CallbackPrevious(DoPrevious);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionPrevious(iHandle, iCallbackPrevious, ptr);
        }

        /// <summary>
        /// Signal that the action SetPlayMode is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetPlayMode must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetPlayMode()
        {
            iCallbackSetPlayMode = new CallbackSetPlayMode(DoSetPlayMode);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionSetPlayMode(iHandle, iCallbackSetPlayMode, ptr);
        }

        /// <summary>
        /// Signal that the action SetRecordQualityMode is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetRecordQualityMode must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetRecordQualityMode()
        {
            iCallbackSetRecordQualityMode = new CallbackSetRecordQualityMode(DoSetRecordQualityMode);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionSetRecordQualityMode(iHandle, iCallbackSetRecordQualityMode, ptr);
        }

        /// <summary>
        /// Signal that the action GetCurrentTransportActions is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetCurrentTransportActions must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetCurrentTransportActions()
        {
            iCallbackGetCurrentTransportActions = new CallbackGetCurrentTransportActions(DoGetCurrentTransportActions);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionGetCurrentTransportActions(iHandle, iCallbackGetCurrentTransportActions, ptr);
        }

        /// <summary>
        /// Signal that the action GetDRMState is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetDRMState must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetDRMState()
        {
            iCallbackGetDRMState = new CallbackGetDRMState(DoGetDRMState);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionGetDRMState(iHandle, iCallbackGetDRMState, ptr);
        }

        /// <summary>
        /// Signal that the action GetStateVariables is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetStateVariables must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetStateVariables()
        {
            iCallbackGetStateVariables = new CallbackGetStateVariables(DoGetStateVariables);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionGetStateVariables(iHandle, iCallbackGetStateVariables, ptr);
        }

        /// <summary>
        /// Signal that the action SetStateVariables is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStateVariables must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStateVariables()
        {
            iCallbackSetStateVariables = new CallbackSetStateVariables(DoSetStateVariables);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgAVTransport2EnableActionSetStateVariables(iHandle, iCallbackSetStateVariables, ptr);
        }

        /// <summary>
        /// SetAVTransportURI action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetAVTransportURI action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetAVTransportURI was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentURI"></param>
        /// <param name="aCurrentURIMetaData"></param>
        protected virtual void SetAVTransportURI(uint aVersion, uint aInstanceID, string aCurrentURI, string aCurrentURIMetaData)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetNextAVTransportURI action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetNextAVTransportURI action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetNextAVTransportURI was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aNextURI"></param>
        /// <param name="aNextURIMetaData"></param>
        protected virtual void SetNextAVTransportURI(uint aVersion, uint aInstanceID, string aNextURI, string aNextURIMetaData)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetMediaInfo action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetMediaInfo action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetMediaInfo was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
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
        protected virtual void GetMediaInfo(uint aVersion, uint aInstanceID, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetMediaInfo_Ext action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetMediaInfo_Ext action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetMediaInfo_Ext was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
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
        protected virtual void GetMediaInfo_Ext(uint aVersion, uint aInstanceID, out string aCurrentType, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetTransportInfo action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetTransportInfo action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetTransportInfo was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentTransportState"></param>
        /// <param name="aCurrentTransportStatus"></param>
        /// <param name="aCurrentSpeed"></param>
        protected virtual void GetTransportInfo(uint aVersion, uint aInstanceID, out string aCurrentTransportState, out string aCurrentTransportStatus, out string aCurrentSpeed)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetPositionInfo action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetPositionInfo action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetPositionInfo was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aTrack"></param>
        /// <param name="aTrackDuration"></param>
        /// <param name="aTrackMetaData"></param>
        /// <param name="aTrackURI"></param>
        /// <param name="aRelTime"></param>
        /// <param name="aAbsTime"></param>
        /// <param name="aRelCount"></param>
        /// <param name="aAbsCount"></param>
        protected virtual void GetPositionInfo(uint aVersion, uint aInstanceID, out uint aTrack, out string aTrackDuration, out string aTrackMetaData, out string aTrackURI, out string aRelTime, out string aAbsTime, out int aRelCount, out int aAbsCount)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetDeviceCapabilities action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetDeviceCapabilities action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetDeviceCapabilities was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aPlayMedia"></param>
        /// <param name="aRecMedia"></param>
        /// <param name="aRecQualityModes"></param>
        protected virtual void GetDeviceCapabilities(uint aVersion, uint aInstanceID, out string aPlayMedia, out string aRecMedia, out string aRecQualityModes)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetTransportSettings action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetTransportSettings action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetTransportSettings was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aPlayMode"></param>
        /// <param name="aRecQualityMode"></param>
        protected virtual void GetTransportSettings(uint aVersion, uint aInstanceID, out string aPlayMode, out string aRecQualityMode)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Stop action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Stop action for the owning device.
        ///
        /// Must be implemented iff EnableActionStop was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        protected virtual void Stop(uint aVersion, uint aInstanceID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Play action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Play action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlay was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aSpeed"></param>
        protected virtual void Play(uint aVersion, uint aInstanceID, string aSpeed)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Pause action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Pause action for the owning device.
        ///
        /// Must be implemented iff EnableActionPause was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        protected virtual void Pause(uint aVersion, uint aInstanceID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Record action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Record action for the owning device.
        ///
        /// Must be implemented iff EnableActionRecord was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        protected virtual void Record(uint aVersion, uint aInstanceID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Seek action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Seek action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeek was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aUnit"></param>
        /// <param name="aTarget"></param>
        protected virtual void Seek(uint aVersion, uint aInstanceID, string aUnit, string aTarget)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Next action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Next action for the owning device.
        ///
        /// Must be implemented iff EnableActionNext was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        protected virtual void Next(uint aVersion, uint aInstanceID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Previous action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Previous action for the owning device.
        ///
        /// Must be implemented iff EnableActionPrevious was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        protected virtual void Previous(uint aVersion, uint aInstanceID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetPlayMode action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetPlayMode action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetPlayMode was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aNewPlayMode"></param>
        protected virtual void SetPlayMode(uint aVersion, uint aInstanceID, string aNewPlayMode)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetRecordQualityMode action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetRecordQualityMode action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetRecordQualityMode was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aNewRecordQualityMode"></param>
        protected virtual void SetRecordQualityMode(uint aVersion, uint aInstanceID, string aNewRecordQualityMode)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetCurrentTransportActions action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetCurrentTransportActions action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetCurrentTransportActions was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aActions"></param>
        protected virtual void GetCurrentTransportActions(uint aVersion, uint aInstanceID, out string aActions)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetDRMState action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetDRMState action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetDRMState was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentDRMState"></param>
        protected virtual void GetDRMState(uint aVersion, uint aInstanceID, out string aCurrentDRMState)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetStateVariables action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetStateVariables action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetStateVariables was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aStateVariableList"></param>
        /// <param name="aStateVariableValuePairs"></param>
        protected virtual void GetStateVariables(uint aVersion, uint aInstanceID, string aStateVariableList, out string aStateVariableValuePairs)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStateVariables action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStateVariables action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStateVariables was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aAVTransportUDN"></param>
        /// <param name="aServiceType"></param>
        /// <param name="aServiceId"></param>
        /// <param name="aStateVariableValuePairs"></param>
        /// <param name="aStateVariableList"></param>
        protected virtual void SetStateVariables(uint aVersion, uint aInstanceID, string aAVTransportUDN, string aServiceType, string aServiceId, string aStateVariableValuePairs, out string aStateVariableList)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aCurrentURI, char* aCurrentURIMetaData)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string currentURI = Marshal.PtrToStringAnsi((IntPtr)aCurrentURI);
            string currentURIMetaData = Marshal.PtrToStringAnsi((IntPtr)aCurrentURIMetaData);
            self.SetAVTransportURI(aVersion, aInstanceID, currentURI, currentURIMetaData);
            return 0;
        }

        private static unsafe int DoSetNextAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNextURI, char* aNextURIMetaData)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string nextURI = Marshal.PtrToStringAnsi((IntPtr)aNextURI);
            string nextURIMetaData = Marshal.PtrToStringAnsi((IntPtr)aNextURIMetaData);
            self.SetNextAVTransportURI(aVersion, aInstanceID, nextURI, nextURIMetaData);
            return 0;
        }

        private static unsafe int DoGetMediaInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            uint nrTracks;
            string mediaDuration;
            string currentURI;
            string currentURIMetaData;
            string nextURI;
            string nextURIMetaData;
            string playMedium;
            string recordMedium;
            string writeStatus;
            self.GetMediaInfo(aVersion, aInstanceID, out nrTracks, out mediaDuration, out currentURI, out currentURIMetaData, out nextURI, out nextURIMetaData, out playMedium, out recordMedium, out writeStatus);
            *aNrTracks = nrTracks;
            *aMediaDuration = (char*)Marshal.StringToHGlobalAnsi(mediaDuration).ToPointer();
            *aCurrentURI = (char*)Marshal.StringToHGlobalAnsi(currentURI).ToPointer();
            *aCurrentURIMetaData = (char*)Marshal.StringToHGlobalAnsi(currentURIMetaData).ToPointer();
            *aNextURI = (char*)Marshal.StringToHGlobalAnsi(nextURI).ToPointer();
            *aNextURIMetaData = (char*)Marshal.StringToHGlobalAnsi(nextURIMetaData).ToPointer();
            *aPlayMedium = (char*)Marshal.StringToHGlobalAnsi(playMedium).ToPointer();
            *aRecordMedium = (char*)Marshal.StringToHGlobalAnsi(recordMedium).ToPointer();
            *aWriteStatus = (char*)Marshal.StringToHGlobalAnsi(writeStatus).ToPointer();
            return 0;
        }

        private static unsafe int DoGetMediaInfo_Ext(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentType, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string currentType;
            uint nrTracks;
            string mediaDuration;
            string currentURI;
            string currentURIMetaData;
            string nextURI;
            string nextURIMetaData;
            string playMedium;
            string recordMedium;
            string writeStatus;
            self.GetMediaInfo_Ext(aVersion, aInstanceID, out currentType, out nrTracks, out mediaDuration, out currentURI, out currentURIMetaData, out nextURI, out nextURIMetaData, out playMedium, out recordMedium, out writeStatus);
            *aCurrentType = (char*)Marshal.StringToHGlobalAnsi(currentType).ToPointer();
            *aNrTracks = nrTracks;
            *aMediaDuration = (char*)Marshal.StringToHGlobalAnsi(mediaDuration).ToPointer();
            *aCurrentURI = (char*)Marshal.StringToHGlobalAnsi(currentURI).ToPointer();
            *aCurrentURIMetaData = (char*)Marshal.StringToHGlobalAnsi(currentURIMetaData).ToPointer();
            *aNextURI = (char*)Marshal.StringToHGlobalAnsi(nextURI).ToPointer();
            *aNextURIMetaData = (char*)Marshal.StringToHGlobalAnsi(nextURIMetaData).ToPointer();
            *aPlayMedium = (char*)Marshal.StringToHGlobalAnsi(playMedium).ToPointer();
            *aRecordMedium = (char*)Marshal.StringToHGlobalAnsi(recordMedium).ToPointer();
            *aWriteStatus = (char*)Marshal.StringToHGlobalAnsi(writeStatus).ToPointer();
            return 0;
        }

        private static unsafe int DoGetTransportInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string currentTransportState;
            string currentTransportStatus;
            string currentSpeed;
            self.GetTransportInfo(aVersion, aInstanceID, out currentTransportState, out currentTransportStatus, out currentSpeed);
            *aCurrentTransportState = (char*)Marshal.StringToHGlobalAnsi(currentTransportState).ToPointer();
            *aCurrentTransportStatus = (char*)Marshal.StringToHGlobalAnsi(currentTransportStatus).ToPointer();
            *aCurrentSpeed = (char*)Marshal.StringToHGlobalAnsi(currentSpeed).ToPointer();
            return 0;
        }

        private static unsafe int DoGetPositionInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int* aRelCount, int* aAbsCount)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            uint track;
            string trackDuration;
            string trackMetaData;
            string trackURI;
            string relTime;
            string absTime;
            int relCount;
            int absCount;
            self.GetPositionInfo(aVersion, aInstanceID, out track, out trackDuration, out trackMetaData, out trackURI, out relTime, out absTime, out relCount, out absCount);
            *aTrack = track;
            *aTrackDuration = (char*)Marshal.StringToHGlobalAnsi(trackDuration).ToPointer();
            *aTrackMetaData = (char*)Marshal.StringToHGlobalAnsi(trackMetaData).ToPointer();
            *aTrackURI = (char*)Marshal.StringToHGlobalAnsi(trackURI).ToPointer();
            *aRelTime = (char*)Marshal.StringToHGlobalAnsi(relTime).ToPointer();
            *aAbsTime = (char*)Marshal.StringToHGlobalAnsi(absTime).ToPointer();
            *aRelCount = relCount;
            *aAbsCount = absCount;
            return 0;
        }

        private static unsafe int DoGetDeviceCapabilities(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string playMedia;
            string recMedia;
            string recQualityModes;
            self.GetDeviceCapabilities(aVersion, aInstanceID, out playMedia, out recMedia, out recQualityModes);
            *aPlayMedia = (char*)Marshal.StringToHGlobalAnsi(playMedia).ToPointer();
            *aRecMedia = (char*)Marshal.StringToHGlobalAnsi(recMedia).ToPointer();
            *aRecQualityModes = (char*)Marshal.StringToHGlobalAnsi(recQualityModes).ToPointer();
            return 0;
        }

        private static unsafe int DoGetTransportSettings(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aPlayMode, char** aRecQualityMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string playMode;
            string recQualityMode;
            self.GetTransportSettings(aVersion, aInstanceID, out playMode, out recQualityMode);
            *aPlayMode = (char*)Marshal.StringToHGlobalAnsi(playMode).ToPointer();
            *aRecQualityMode = (char*)Marshal.StringToHGlobalAnsi(recQualityMode).ToPointer();
            return 0;
        }

        private static unsafe int DoStop(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            self.Stop(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoPlay(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aSpeed)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string speed = Marshal.PtrToStringAnsi((IntPtr)aSpeed);
            self.Play(aVersion, aInstanceID, speed);
            return 0;
        }

        private static unsafe int DoPause(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            self.Pause(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoRecord(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            self.Record(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoSeek(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aUnit, char* aTarget)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string unit = Marshal.PtrToStringAnsi((IntPtr)aUnit);
            string target = Marshal.PtrToStringAnsi((IntPtr)aTarget);
            self.Seek(aVersion, aInstanceID, unit, target);
            return 0;
        }

        private static unsafe int DoNext(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            self.Next(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoPrevious(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            self.Previous(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoSetPlayMode(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNewPlayMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string newPlayMode = Marshal.PtrToStringAnsi((IntPtr)aNewPlayMode);
            self.SetPlayMode(aVersion, aInstanceID, newPlayMode);
            return 0;
        }

        private static unsafe int DoSetRecordQualityMode(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNewRecordQualityMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string newRecordQualityMode = Marshal.PtrToStringAnsi((IntPtr)aNewRecordQualityMode);
            self.SetRecordQualityMode(aVersion, aInstanceID, newRecordQualityMode);
            return 0;
        }

        private static unsafe int DoGetCurrentTransportActions(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aActions)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string actions;
            self.GetCurrentTransportActions(aVersion, aInstanceID, out actions);
            *aActions = (char*)Marshal.StringToHGlobalAnsi(actions).ToPointer();
            return 0;
        }

        private static unsafe int DoGetDRMState(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentDRMState)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string currentDRMState;
            self.GetDRMState(aVersion, aInstanceID, out currentDRMState);
            *aCurrentDRMState = (char*)Marshal.StringToHGlobalAnsi(currentDRMState).ToPointer();
            return 0;
        }

        private static unsafe int DoGetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aStateVariableList, char** aStateVariableValuePairs)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string stateVariableList = Marshal.PtrToStringAnsi((IntPtr)aStateVariableList);
            string stateVariableValuePairs;
            self.GetStateVariables(aVersion, aInstanceID, stateVariableList, out stateVariableValuePairs);
            *aStateVariableValuePairs = (char*)Marshal.StringToHGlobalAnsi(stateVariableValuePairs).ToPointer();
            return 0;
        }

        private static unsafe int DoSetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aAVTransportUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, char** aStateVariableList)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            string aVTransportUDN = Marshal.PtrToStringAnsi((IntPtr)aAVTransportUDN);
            string serviceType = Marshal.PtrToStringAnsi((IntPtr)aServiceType);
            string serviceId = Marshal.PtrToStringAnsi((IntPtr)aServiceId);
            string stateVariableValuePairs = Marshal.PtrToStringAnsi((IntPtr)aStateVariableValuePairs);
            string stateVariableList;
            self.SetStateVariables(aVersion, aInstanceID, aVTransportUDN, serviceType, serviceId, stateVariableValuePairs, out stateVariableList);
            *aStateVariableList = (char*)Marshal.StringToHGlobalAnsi(stateVariableList).ToPointer();
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

        ~DvProviderUpnpOrgAVTransport2()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            uint handle;
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                handle = iHandle;
                iHandle = 0;
            }
            DvProviderUpnpOrgAVTransport2Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

