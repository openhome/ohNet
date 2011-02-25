using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderUpnpOrgAVTransport2 : IDisposable
    {

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyLastChange(string aValue);

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyLastChange();

        /// <summary>
        /// Set the value of the DRMState property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDRMState(string aValue);

        /// <summary>
        /// Get a copy of the value of the DRMState property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyDRMState();
        
    }
    /// <summary>
    /// Provider for the upnp.org:AVTransport:2 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgAVTransport2 : DvProvider, IDisposable, IDvProviderUpnpOrgAVTransport2
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateSetAVTransportURI;
        private ActionDelegate iDelegateSetNextAVTransportURI;
        private ActionDelegate iDelegateGetMediaInfo;
        private ActionDelegate iDelegateGetMediaInfo_Ext;
        private ActionDelegate iDelegateGetTransportInfo;
        private ActionDelegate iDelegateGetPositionInfo;
        private ActionDelegate iDelegateGetDeviceCapabilities;
        private ActionDelegate iDelegateGetTransportSettings;
        private ActionDelegate iDelegateStop;
        private ActionDelegate iDelegatePlay;
        private ActionDelegate iDelegatePause;
        private ActionDelegate iDelegateRecord;
        private ActionDelegate iDelegateSeek;
        private ActionDelegate iDelegateNext;
        private ActionDelegate iDelegatePrevious;
        private ActionDelegate iDelegateSetPlayMode;
        private ActionDelegate iDelegateSetRecordQualityMode;
        private ActionDelegate iDelegateGetCurrentTransportActions;
        private ActionDelegate iDelegateGetDRMState;
        private ActionDelegate iDelegateGetStateVariables;
        private ActionDelegate iDelegateSetStateVariables;
        private PropertyString iPropertyLastChange;
        private PropertyString iPropertyDRMState;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgAVTransport2(DvDevice aDevice)
            : base(aDevice, "upnp.org", "AVTransport", 2)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyLastChange = new PropertyString(new ParameterString("LastChange", allowedValues));
            AddProperty(iPropertyLastChange);
            allowedValues.Add("OK");
            iPropertyDRMState = new PropertyString(new ParameterString("DRMState", allowedValues));
            AddProperty(iPropertyDRMState);
            allowedValues.Clear();
        }

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyLastChange(string aValue)
        {
            return SetPropertyString(iPropertyLastChange, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyLastChange()
        {
            return iPropertyLastChange.Value();
        }

        /// <summary>
        /// Set the value of the DRMState property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDRMState(string aValue)
        {
            return SetPropertyString(iPropertyDRMState, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DRMState property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyDRMState()
        {
            return iPropertyDRMState.Value();
        }

        /// <summary>
        /// Signal that the action SetAVTransportURI is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetAVTransportURI must be overridden if this is called.</remarks>
        protected void EnableActionSetAVTransportURI()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetAVTransportURI");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterString("CurrentURI", allowedValues));
            action.AddInputParameter(new ParameterString("CurrentURIMetaData", allowedValues));
            iDelegateSetAVTransportURI = new ActionDelegate(DoSetAVTransportURI);
            EnableAction(action, iDelegateSetAVTransportURI, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetNextAVTransportURI is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetNextAVTransportURI must be overridden if this is called.</remarks>
        protected void EnableActionSetNextAVTransportURI()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetNextAVTransportURI");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterString("NextURI", allowedValues));
            action.AddInputParameter(new ParameterString("NextURIMetaData", allowedValues));
            iDelegateSetNextAVTransportURI = new ActionDelegate(DoSetNextAVTransportURI);
            EnableAction(action, iDelegateSetNextAVTransportURI, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetMediaInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetMediaInfo must be overridden if this is called.</remarks>
        protected void EnableActionGetMediaInfo()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetMediaInfo");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("NrTracks", 0, 0));
            action.AddOutputParameter(new ParameterString("MediaDuration", allowedValues));
            action.AddOutputParameter(new ParameterString("CurrentURI", allowedValues));
            action.AddOutputParameter(new ParameterString("CurrentURIMetaData", allowedValues));
            action.AddOutputParameter(new ParameterString("NextURI", allowedValues));
            action.AddOutputParameter(new ParameterString("NextURIMetaData", allowedValues));
            action.AddOutputParameter(new ParameterString("PlayMedium", allowedValues));
            action.AddOutputParameter(new ParameterString("RecordMedium", allowedValues));
            action.AddOutputParameter(new ParameterString("WriteStatus", allowedValues));
            iDelegateGetMediaInfo = new ActionDelegate(DoGetMediaInfo);
            EnableAction(action, iDelegateGetMediaInfo, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetMediaInfo_Ext is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetMediaInfo_Ext must be overridden if this is called.</remarks>
        protected void EnableActionGetMediaInfo_Ext()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetMediaInfo_Ext");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("NO_MEDIA");
            allowedValues.Add("TRACK_AWARE");
            allowedValues.Add("TRACK_UNAWARE");
            action.AddOutputParameter(new ParameterString("CurrentType", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterUint("NrTracks", 0, 0));
            action.AddOutputParameter(new ParameterString("MediaDuration", allowedValues));
            action.AddOutputParameter(new ParameterString("CurrentURI", allowedValues));
            action.AddOutputParameter(new ParameterString("CurrentURIMetaData", allowedValues));
            action.AddOutputParameter(new ParameterString("NextURI", allowedValues));
            action.AddOutputParameter(new ParameterString("NextURIMetaData", allowedValues));
            action.AddOutputParameter(new ParameterString("PlayMedium", allowedValues));
            action.AddOutputParameter(new ParameterString("RecordMedium", allowedValues));
            action.AddOutputParameter(new ParameterString("WriteStatus", allowedValues));
            iDelegateGetMediaInfo_Ext = new ActionDelegate(DoGetMediaInfo_Ext);
            EnableAction(action, iDelegateGetMediaInfo_Ext, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetTransportInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetTransportInfo must be overridden if this is called.</remarks>
        protected void EnableActionGetTransportInfo()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetTransportInfo");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("STOPPED");
            allowedValues.Add("PLAYING");
            action.AddOutputParameter(new ParameterString("CurrentTransportState", allowedValues));
            allowedValues.Clear();
            allowedValues.Add("OK");
            allowedValues.Add("ERROR_OCCURRED");
            action.AddOutputParameter(new ParameterString("CurrentTransportStatus", allowedValues));
            allowedValues.Clear();
            allowedValues.Add("1");
            action.AddOutputParameter(new ParameterString("CurrentSpeed", allowedValues));
            allowedValues.Clear();
            iDelegateGetTransportInfo = new ActionDelegate(DoGetTransportInfo);
            EnableAction(action, iDelegateGetTransportInfo, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetPositionInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetPositionInfo must be overridden if this is called.</remarks>
        protected void EnableActionGetPositionInfo()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetPositionInfo");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("Track", 0, 0, 1));
            action.AddOutputParameter(new ParameterString("TrackDuration", allowedValues));
            action.AddOutputParameter(new ParameterString("TrackMetaData", allowedValues));
            action.AddOutputParameter(new ParameterString("TrackURI", allowedValues));
            action.AddOutputParameter(new ParameterString("RelTime", allowedValues));
            action.AddOutputParameter(new ParameterString("AbsTime", allowedValues));
            action.AddOutputParameter(new ParameterInt("RelCount"));
            action.AddOutputParameter(new ParameterInt("AbsCount"));
            iDelegateGetPositionInfo = new ActionDelegate(DoGetPositionInfo);
            EnableAction(action, iDelegateGetPositionInfo, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetDeviceCapabilities is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetDeviceCapabilities must be overridden if this is called.</remarks>
        protected void EnableActionGetDeviceCapabilities()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetDeviceCapabilities");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterString("PlayMedia", allowedValues));
            action.AddOutputParameter(new ParameterString("RecMedia", allowedValues));
            action.AddOutputParameter(new ParameterString("RecQualityModes", allowedValues));
            iDelegateGetDeviceCapabilities = new ActionDelegate(DoGetDeviceCapabilities);
            EnableAction(action, iDelegateGetDeviceCapabilities, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetTransportSettings is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetTransportSettings must be overridden if this is called.</remarks>
        protected void EnableActionGetTransportSettings()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetTransportSettings");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("NORMAL");
            action.AddOutputParameter(new ParameterString("PlayMode", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterString("RecQualityMode", allowedValues));
            iDelegateGetTransportSettings = new ActionDelegate(DoGetTransportSettings);
            EnableAction(action, iDelegateGetTransportSettings, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Stop is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Stop must be overridden if this is called.</remarks>
        protected void EnableActionStop()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Stop");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            iDelegateStop = new ActionDelegate(DoStop);
            EnableAction(action, iDelegateStop, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Play is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Play must be overridden if this is called.</remarks>
        protected void EnableActionPlay()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Play");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("1");
            action.AddInputParameter(new ParameterString("Speed", allowedValues));
            allowedValues.Clear();
            iDelegatePlay = new ActionDelegate(DoPlay);
            EnableAction(action, iDelegatePlay, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Pause is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Pause must be overridden if this is called.</remarks>
        protected void EnableActionPause()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Pause");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            iDelegatePause = new ActionDelegate(DoPause);
            EnableAction(action, iDelegatePause, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Record is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Record must be overridden if this is called.</remarks>
        protected void EnableActionRecord()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Record");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            iDelegateRecord = new ActionDelegate(DoRecord);
            EnableAction(action, iDelegateRecord, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Seek is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Seek must be overridden if this is called.</remarks>
        protected void EnableActionSeek()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Seek");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("TRACK_NR");
            action.AddInputParameter(new ParameterString("Unit", allowedValues));
            allowedValues.Clear();
            action.AddInputParameter(new ParameterString("Target", allowedValues));
            iDelegateSeek = new ActionDelegate(DoSeek);
            EnableAction(action, iDelegateSeek, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Next is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Next must be overridden if this is called.</remarks>
        protected void EnableActionNext()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Next");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            iDelegateNext = new ActionDelegate(DoNext);
            EnableAction(action, iDelegateNext, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Previous is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Previous must be overridden if this is called.</remarks>
        protected void EnableActionPrevious()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Previous");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            iDelegatePrevious = new ActionDelegate(DoPrevious);
            EnableAction(action, iDelegatePrevious, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetPlayMode is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetPlayMode must be overridden if this is called.</remarks>
        protected void EnableActionSetPlayMode()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetPlayMode");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("NORMAL");
            action.AddInputParameter(new ParameterString("NewPlayMode", allowedValues));
            allowedValues.Clear();
            iDelegateSetPlayMode = new ActionDelegate(DoSetPlayMode);
            EnableAction(action, iDelegateSetPlayMode, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetRecordQualityMode is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetRecordQualityMode must be overridden if this is called.</remarks>
        protected void EnableActionSetRecordQualityMode()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetRecordQualityMode");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterString("NewRecordQualityMode", allowedValues));
            iDelegateSetRecordQualityMode = new ActionDelegate(DoSetRecordQualityMode);
            EnableAction(action, iDelegateSetRecordQualityMode, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetCurrentTransportActions is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetCurrentTransportActions must be overridden if this is called.</remarks>
        protected void EnableActionGetCurrentTransportActions()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetCurrentTransportActions");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterString("Actions", allowedValues));
            iDelegateGetCurrentTransportActions = new ActionDelegate(DoGetCurrentTransportActions);
            EnableAction(action, iDelegateGetCurrentTransportActions, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetDRMState is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetDRMState must be overridden if this is called.</remarks>
        protected void EnableActionGetDRMState()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetDRMState");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterRelated("CurrentDRMState", iPropertyDRMState));
            iDelegateGetDRMState = new ActionDelegate(DoGetDRMState);
            EnableAction(action, iDelegateGetDRMState, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetStateVariables is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetStateVariables must be overridden if this is called.</remarks>
        protected void EnableActionGetStateVariables()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetStateVariables");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterString("StateVariableList", allowedValues));
            action.AddOutputParameter(new ParameterString("StateVariableValuePairs", allowedValues));
            iDelegateGetStateVariables = new ActionDelegate(DoGetStateVariables);
            EnableAction(action, iDelegateGetStateVariables, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetStateVariables is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetStateVariables must be overridden if this is called.</remarks>
        protected void EnableActionSetStateVariables()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetStateVariables");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterString("AVTransportUDN", allowedValues));
            action.AddInputParameter(new ParameterString("ServiceType", allowedValues));
            action.AddInputParameter(new ParameterString("ServiceId", allowedValues));
            action.AddInputParameter(new ParameterString("StateVariableValuePairs", allowedValues));
            action.AddOutputParameter(new ParameterString("StateVariableList", allowedValues));
            iDelegateSetStateVariables = new ActionDelegate(DoSetStateVariables);
            EnableAction(action, iDelegateSetStateVariables, GCHandle.ToIntPtr(iGch));
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

        private static int DoSetAVTransportURI(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string currentURI;
            string currentURIMetaData;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                currentURI = invocation.ReadString("CurrentURI");
                currentURIMetaData = invocation.ReadString("CurrentURIMetaData");
                invocation.ReadEnd();
                self.SetAVTransportURI(aVersion, instanceID, currentURI, currentURIMetaData);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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

        private static int DoSetNextAVTransportURI(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string nextURI;
            string nextURIMetaData;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                nextURI = invocation.ReadString("NextURI");
                nextURIMetaData = invocation.ReadString("NextURIMetaData");
                invocation.ReadEnd();
                self.SetNextAVTransportURI(aVersion, instanceID, nextURI, nextURIMetaData);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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

        private static int DoGetMediaInfo(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            uint nrTracks;
            string mediaDuration;
            string currentURI;
            string currentURIMetaData;
            string nextURI;
            string nextURIMetaData;
            string playMedium;
            string recordMedium;
            string writeStatus;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.GetMediaInfo(aVersion, instanceID, out nrTracks, out mediaDuration, out currentURI, out currentURIMetaData, out nextURI, out nextURIMetaData, out playMedium, out recordMedium, out writeStatus);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("NrTracks", nrTracks);
                invocation.WriteString("MediaDuration", mediaDuration);
                invocation.WriteString("CurrentURI", currentURI);
                invocation.WriteString("CurrentURIMetaData", currentURIMetaData);
                invocation.WriteString("NextURI", nextURI);
                invocation.WriteString("NextURIMetaData", nextURIMetaData);
                invocation.WriteString("PlayMedium", playMedium);
                invocation.WriteString("RecordMedium", recordMedium);
                invocation.WriteString("WriteStatus", writeStatus);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetMediaInfo_Ext(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
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
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.GetMediaInfo_Ext(aVersion, instanceID, out currentType, out nrTracks, out mediaDuration, out currentURI, out currentURIMetaData, out nextURI, out nextURIMetaData, out playMedium, out recordMedium, out writeStatus);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("CurrentType", currentType);
                invocation.WriteUint("NrTracks", nrTracks);
                invocation.WriteString("MediaDuration", mediaDuration);
                invocation.WriteString("CurrentURI", currentURI);
                invocation.WriteString("CurrentURIMetaData", currentURIMetaData);
                invocation.WriteString("NextURI", nextURI);
                invocation.WriteString("NextURIMetaData", nextURIMetaData);
                invocation.WriteString("PlayMedium", playMedium);
                invocation.WriteString("RecordMedium", recordMedium);
                invocation.WriteString("WriteStatus", writeStatus);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetTransportInfo(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string currentTransportState;
            string currentTransportStatus;
            string currentSpeed;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.GetTransportInfo(aVersion, instanceID, out currentTransportState, out currentTransportStatus, out currentSpeed);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("CurrentTransportState", currentTransportState);
                invocation.WriteString("CurrentTransportStatus", currentTransportStatus);
                invocation.WriteString("CurrentSpeed", currentSpeed);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetPositionInfo(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            uint track;
            string trackDuration;
            string trackMetaData;
            string trackURI;
            string relTime;
            string absTime;
            int relCount;
            int absCount;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.GetPositionInfo(aVersion, instanceID, out track, out trackDuration, out trackMetaData, out trackURI, out relTime, out absTime, out relCount, out absCount);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Track", track);
                invocation.WriteString("TrackDuration", trackDuration);
                invocation.WriteString("TrackMetaData", trackMetaData);
                invocation.WriteString("TrackURI", trackURI);
                invocation.WriteString("RelTime", relTime);
                invocation.WriteString("AbsTime", absTime);
                invocation.WriteInt("RelCount", relCount);
                invocation.WriteInt("AbsCount", absCount);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetDeviceCapabilities(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string playMedia;
            string recMedia;
            string recQualityModes;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.GetDeviceCapabilities(aVersion, instanceID, out playMedia, out recMedia, out recQualityModes);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("PlayMedia", playMedia);
                invocation.WriteString("RecMedia", recMedia);
                invocation.WriteString("RecQualityModes", recQualityModes);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetTransportSettings(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string playMode;
            string recQualityMode;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.GetTransportSettings(aVersion, instanceID, out playMode, out recQualityMode);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("PlayMode", playMode);
                invocation.WriteString("RecQualityMode", recQualityMode);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoStop(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.Stop(aVersion, instanceID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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

        private static int DoPlay(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string speed;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                speed = invocation.ReadString("Speed");
                invocation.ReadEnd();
                self.Play(aVersion, instanceID, speed);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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

        private static int DoPause(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.Pause(aVersion, instanceID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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

        private static int DoRecord(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.Record(aVersion, instanceID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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

        private static int DoSeek(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string unit;
            string target;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                unit = invocation.ReadString("Unit");
                target = invocation.ReadString("Target");
                invocation.ReadEnd();
                self.Seek(aVersion, instanceID, unit, target);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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

        private static int DoNext(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.Next(aVersion, instanceID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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

        private static int DoPrevious(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.Previous(aVersion, instanceID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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

        private static int DoSetPlayMode(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string newPlayMode;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                newPlayMode = invocation.ReadString("NewPlayMode");
                invocation.ReadEnd();
                self.SetPlayMode(aVersion, instanceID, newPlayMode);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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

        private static int DoSetRecordQualityMode(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string newRecordQualityMode;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                newRecordQualityMode = invocation.ReadString("NewRecordQualityMode");
                invocation.ReadEnd();
                self.SetRecordQualityMode(aVersion, instanceID, newRecordQualityMode);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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

        private static int DoGetCurrentTransportActions(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string actions;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.GetCurrentTransportActions(aVersion, instanceID, out actions);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Actions", actions);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetDRMState(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string currentDRMState;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                self.GetDRMState(aVersion, instanceID, out currentDRMState);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("CurrentDRMState", currentDRMState);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetStateVariables(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string stateVariableList;
            string stateVariableValuePairs;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                stateVariableList = invocation.ReadString("StateVariableList");
                invocation.ReadEnd();
                self.GetStateVariables(aVersion, instanceID, stateVariableList, out stateVariableValuePairs);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("StateVariableValuePairs", stateVariableValuePairs);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetStateVariables(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport2 self = (DvProviderUpnpOrgAVTransport2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint instanceID;
            string aVTransportUDN;
            string serviceType;
            string serviceId;
            string stateVariableValuePairs;
            string stateVariableList;
            try
            {
                invocation.ReadStart();
                instanceID = invocation.ReadUint("InstanceID");
                aVTransportUDN = invocation.ReadString("AVTransportUDN");
                serviceType = invocation.ReadString("ServiceType");
                serviceId = invocation.ReadString("ServiceId");
                stateVariableValuePairs = invocation.ReadString("StateVariableValuePairs");
                invocation.ReadEnd();
                self.SetStateVariables(aVersion, instanceID, aVTransportUDN, serviceType, serviceId, stateVariableValuePairs, out stateVariableList);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("StateVariableList", stateVariableList);
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

        ~DvProviderUpnpOrgAVTransport2()
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

