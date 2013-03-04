using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
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
        /// <returns>Value of the LastChange property.</param>
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
        /// <returns>Value of the DRMState property.</param>
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
        }

        /// <summary>
        /// Enable the LastChange property.
        /// </summary>
        public void EnablePropertyLastChange()
        {
            List<String> allowedValues = new List<String>();
            iPropertyLastChange = new PropertyString(new ParameterString("LastChange", allowedValues));
            AddProperty(iPropertyLastChange);
        }

        /// <summary>
        /// Enable the DRMState property.
        /// </summary>
        public void EnablePropertyDRMState()
        {
            List<String> allowedValues = new List<String>();
            allowedValues.Add("OK");
            allowedValues.Add("UNKNOWN");
            allowedValues.Add("PROCESSING_CONTENT_KEY");
            allowedValues.Add("CONTENT_KEY_FAILURE");
            allowedValues.Add("ATTEMPTING_AUTHENTICATION");
            allowedValues.Add("FAILED_AUTHENTICATION");
            allowedValues.Add("NOT_AUTHENTICATED");
            allowedValues.Add("DEVICE_REVOCATION");
            iPropertyDRMState = new PropertyString(new ParameterString("DRMState", allowedValues));
            AddProperty(iPropertyDRMState);
            allowedValues.Clear();
        }

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyLastChange has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyLastChange(string aValue)
        {
            if (iPropertyLastChange == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyLastChange, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyLastChange has previously been called.</remarks>
        /// <returns>Value of the LastChange property.</returns>
        public string PropertyLastChange()
        {
            if (iPropertyLastChange == null)
                throw new PropertyDisabledError();
            return iPropertyLastChange.Value();
        }

        /// <summary>
        /// Set the value of the DRMState property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyDRMState has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDRMState(string aValue)
        {
            if (iPropertyDRMState == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyDRMState, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DRMState property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyDRMState has previously been called.</remarks>
        /// <returns>Value of the DRMState property.</returns>
        public string PropertyDRMState()
        {
            if (iPropertyDRMState == null)
                throw new PropertyDisabledError();
            return iPropertyDRMState.Value();
        }

        /// <summary>
        /// Signal that the action SetAVTransportURI is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetAVTransportURI must be overridden if this is called.</remarks>
        protected void EnableActionSetAVTransportURI()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetAVTransportURI");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetNextAVTransportURI");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetMediaInfo");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("NrTracks", 0));
            action.AddOutputParameter(new ParameterString("MediaDuration", allowedValues));
            action.AddOutputParameter(new ParameterString("CurrentURI", allowedValues));
            action.AddOutputParameter(new ParameterString("CurrentURIMetaData", allowedValues));
            action.AddOutputParameter(new ParameterString("NextURI", allowedValues));
            action.AddOutputParameter(new ParameterString("NextURIMetaData", allowedValues));
            action.AddOutputParameter(new ParameterString("PlayMedium", allowedValues));
            action.AddOutputParameter(new ParameterString("RecordMedium", allowedValues));
            allowedValues.Add("WRITABLE");
            allowedValues.Add("PROTECTED");
            allowedValues.Add("NOT_WRITABLE");
            allowedValues.Add("UNKNOWN");
            allowedValues.Add("NOT_IMPLEMENTED");
            action.AddOutputParameter(new ParameterString("WriteStatus", allowedValues));
            allowedValues.Clear();
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetMediaInfo_Ext");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("NO_MEDIA");
            allowedValues.Add("TRACK_AWARE");
            allowedValues.Add("TRACK_UNAWARE");
            action.AddOutputParameter(new ParameterString("CurrentType", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterUint("NrTracks", 0));
            action.AddOutputParameter(new ParameterString("MediaDuration", allowedValues));
            action.AddOutputParameter(new ParameterString("CurrentURI", allowedValues));
            action.AddOutputParameter(new ParameterString("CurrentURIMetaData", allowedValues));
            action.AddOutputParameter(new ParameterString("NextURI", allowedValues));
            action.AddOutputParameter(new ParameterString("NextURIMetaData", allowedValues));
            action.AddOutputParameter(new ParameterString("PlayMedium", allowedValues));
            action.AddOutputParameter(new ParameterString("RecordMedium", allowedValues));
            allowedValues.Add("WRITABLE");
            allowedValues.Add("PROTECTED");
            allowedValues.Add("NOT_WRITABLE");
            allowedValues.Add("UNKNOWN");
            allowedValues.Add("NOT_IMPLEMENTED");
            action.AddOutputParameter(new ParameterString("WriteStatus", allowedValues));
            allowedValues.Clear();
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetTransportInfo");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterString("CurrentTransportState", allowedValues));
            action.AddOutputParameter(new ParameterString("CurrentTransportStatus", allowedValues));
            action.AddOutputParameter(new ParameterString("CurrentSpeed", allowedValues));
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetPositionInfo");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("Track", 0, 2147483647, 1));
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetDeviceCapabilities");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetTransportSettings");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("NORMAL");
            allowedValues.Add("SHUFFLE");
            allowedValues.Add("REPEAT_ONE");
            allowedValues.Add("REPEAT_ALL");
            allowedValues.Add("RANDOM");
            allowedValues.Add("DIRECT_1");
            allowedValues.Add("INTRO");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Stop");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Play");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterString("Speed", allowedValues));
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Pause");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Record");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Seek");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("ABS_TIME");
            allowedValues.Add("REL_TIME");
            allowedValues.Add("ABS_COUNT");
            allowedValues.Add("REL_COUNT");
            allowedValues.Add("TRACK_NR");
            allowedValues.Add("CHANNEL_FREQ");
            allowedValues.Add("TAPE-INDEX");
            allowedValues.Add("FRAME");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Next");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Previous");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetPlayMode");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("NORMAL");
            allowedValues.Add("SHUFFLE");
            allowedValues.Add("REPEAT_ONE");
            allowedValues.Add("REPEAT_ALL");
            allowedValues.Add("RANDOM");
            allowedValues.Add("DIRECT_1");
            allowedValues.Add("INTRO");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetRecordQualityMode");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetCurrentTransportActions");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetDRMState");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetStateVariables");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetStateVariables");
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentURI"></param>
        /// <param name="aCurrentURIMetaData"></param>
        protected virtual void SetAVTransportURI(IDvInvocation aInvocation, uint aInstanceID, string aCurrentURI, string aCurrentURIMetaData)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aNextURI"></param>
        /// <param name="aNextURIMetaData"></param>
        protected virtual void SetNextAVTransportURI(IDvInvocation aInvocation, uint aInstanceID, string aNextURI, string aNextURIMetaData)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
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
        protected virtual void GetMediaInfo(IDvInvocation aInvocation, uint aInstanceID, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
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
        protected virtual void GetMediaInfo_Ext(IDvInvocation aInvocation, uint aInstanceID, out string aCurrentType, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentTransportState"></param>
        /// <param name="aCurrentTransportStatus"></param>
        /// <param name="aCurrentSpeed"></param>
        protected virtual void GetTransportInfo(IDvInvocation aInvocation, uint aInstanceID, out string aCurrentTransportState, out string aCurrentTransportStatus, out string aCurrentSpeed)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aTrack"></param>
        /// <param name="aTrackDuration"></param>
        /// <param name="aTrackMetaData"></param>
        /// <param name="aTrackURI"></param>
        /// <param name="aRelTime"></param>
        /// <param name="aAbsTime"></param>
        /// <param name="aRelCount"></param>
        /// <param name="aAbsCount"></param>
        protected virtual void GetPositionInfo(IDvInvocation aInvocation, uint aInstanceID, out uint aTrack, out string aTrackDuration, out string aTrackMetaData, out string aTrackURI, out string aRelTime, out string aAbsTime, out int aRelCount, out int aAbsCount)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aPlayMedia"></param>
        /// <param name="aRecMedia"></param>
        /// <param name="aRecQualityModes"></param>
        protected virtual void GetDeviceCapabilities(IDvInvocation aInvocation, uint aInstanceID, out string aPlayMedia, out string aRecMedia, out string aRecQualityModes)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aPlayMode"></param>
        /// <param name="aRecQualityMode"></param>
        protected virtual void GetTransportSettings(IDvInvocation aInvocation, uint aInstanceID, out string aPlayMode, out string aRecQualityMode)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        protected virtual void Stop(IDvInvocation aInvocation, uint aInstanceID)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aSpeed"></param>
        protected virtual void Play(IDvInvocation aInvocation, uint aInstanceID, string aSpeed)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        protected virtual void Pause(IDvInvocation aInvocation, uint aInstanceID)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        protected virtual void Record(IDvInvocation aInvocation, uint aInstanceID)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aUnit"></param>
        /// <param name="aTarget"></param>
        protected virtual void Seek(IDvInvocation aInvocation, uint aInstanceID, string aUnit, string aTarget)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        protected virtual void Next(IDvInvocation aInvocation, uint aInstanceID)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        protected virtual void Previous(IDvInvocation aInvocation, uint aInstanceID)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aNewPlayMode"></param>
        protected virtual void SetPlayMode(IDvInvocation aInvocation, uint aInstanceID, string aNewPlayMode)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aNewRecordQualityMode"></param>
        protected virtual void SetRecordQualityMode(IDvInvocation aInvocation, uint aInstanceID, string aNewRecordQualityMode)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aActions"></param>
        protected virtual void GetCurrentTransportActions(IDvInvocation aInvocation, uint aInstanceID, out string aActions)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentDRMState"></param>
        protected virtual void GetDRMState(IDvInvocation aInvocation, uint aInstanceID, out string aCurrentDRMState)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aStateVariableList"></param>
        /// <param name="aStateVariableValuePairs"></param>
        protected virtual void GetStateVariables(IDvInvocation aInvocation, uint aInstanceID, string aStateVariableList, out string aStateVariableValuePairs)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aAVTransportUDN"></param>
        /// <param name="aServiceType"></param>
        /// <param name="aServiceId"></param>
        /// <param name="aStateVariableValuePairs"></param>
        /// <param name="aStateVariableList"></param>
        protected virtual void SetStateVariables(IDvInvocation aInvocation, uint aInstanceID, string aAVTransportUDN, string aServiceType, string aServiceId, string aStateVariableValuePairs, out string aStateVariableList)
        {
            throw (new ActionDisabledError());
        }

        private static int DoSetAVTransportURI(IntPtr aPtr, IntPtr aInvocation)
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
                self.SetAVTransportURI(invocation, instanceID, currentURI, currentURIMetaData);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetAVTransportURI");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetAVTransportURI"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetAVTransportURI", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetAVTransportURI", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetNextAVTransportURI(IntPtr aPtr, IntPtr aInvocation)
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
                self.SetNextAVTransportURI(invocation, instanceID, nextURI, nextURIMetaData);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetNextAVTransportURI");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetNextAVTransportURI"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetNextAVTransportURI", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetNextAVTransportURI", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetMediaInfo(IntPtr aPtr, IntPtr aInvocation)
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
                self.GetMediaInfo(invocation, instanceID, out nrTracks, out mediaDuration, out currentURI, out currentURIMetaData, out nextURI, out nextURIMetaData, out playMedium, out recordMedium, out writeStatus);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetMediaInfo");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetMediaInfo"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetMediaInfo", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetMediaInfo", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetMediaInfo_Ext(IntPtr aPtr, IntPtr aInvocation)
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
                self.GetMediaInfo_Ext(invocation, instanceID, out currentType, out nrTracks, out mediaDuration, out currentURI, out currentURIMetaData, out nextURI, out nextURIMetaData, out playMedium, out recordMedium, out writeStatus);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetMediaInfo_Ext");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetMediaInfo_Ext"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetMediaInfo_Ext", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetMediaInfo_Ext", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetTransportInfo(IntPtr aPtr, IntPtr aInvocation)
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
                self.GetTransportInfo(invocation, instanceID, out currentTransportState, out currentTransportStatus, out currentSpeed);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetTransportInfo");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetTransportInfo"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetTransportInfo", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetTransportInfo", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetPositionInfo(IntPtr aPtr, IntPtr aInvocation)
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
                self.GetPositionInfo(invocation, instanceID, out track, out trackDuration, out trackMetaData, out trackURI, out relTime, out absTime, out relCount, out absCount);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetPositionInfo");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetPositionInfo"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetPositionInfo", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetPositionInfo", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetDeviceCapabilities(IntPtr aPtr, IntPtr aInvocation)
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
                self.GetDeviceCapabilities(invocation, instanceID, out playMedia, out recMedia, out recQualityModes);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetDeviceCapabilities");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetDeviceCapabilities"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetDeviceCapabilities", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetDeviceCapabilities", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetTransportSettings(IntPtr aPtr, IntPtr aInvocation)
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
                self.GetTransportSettings(invocation, instanceID, out playMode, out recQualityMode);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetTransportSettings");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetTransportSettings"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetTransportSettings", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetTransportSettings", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoStop(IntPtr aPtr, IntPtr aInvocation)
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
                self.Stop(invocation, instanceID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Stop");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Stop"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Stop", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Stop", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlay(IntPtr aPtr, IntPtr aInvocation)
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
                self.Play(invocation, instanceID, speed);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Play");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Play"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Play", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Play", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPause(IntPtr aPtr, IntPtr aInvocation)
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
                self.Pause(invocation, instanceID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Pause");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Pause"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Pause", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Pause", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoRecord(IntPtr aPtr, IntPtr aInvocation)
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
                self.Record(invocation, instanceID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Record");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Record"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Record", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Record", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSeek(IntPtr aPtr, IntPtr aInvocation)
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
                self.Seek(invocation, instanceID, unit, target);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Seek");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Seek"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Seek", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Seek", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoNext(IntPtr aPtr, IntPtr aInvocation)
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
                self.Next(invocation, instanceID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Next");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Next"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Next", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Next", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPrevious(IntPtr aPtr, IntPtr aInvocation)
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
                self.Previous(invocation, instanceID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Previous");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Previous"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Previous", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Previous", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetPlayMode(IntPtr aPtr, IntPtr aInvocation)
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
                self.SetPlayMode(invocation, instanceID, newPlayMode);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetPlayMode");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetPlayMode"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetPlayMode", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetPlayMode", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetRecordQualityMode(IntPtr aPtr, IntPtr aInvocation)
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
                self.SetRecordQualityMode(invocation, instanceID, newRecordQualityMode);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetRecordQualityMode");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetRecordQualityMode"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetRecordQualityMode", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetRecordQualityMode", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetCurrentTransportActions(IntPtr aPtr, IntPtr aInvocation)
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
                self.GetCurrentTransportActions(invocation, instanceID, out actions);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetCurrentTransportActions");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetCurrentTransportActions"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetCurrentTransportActions", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetCurrentTransportActions", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetDRMState(IntPtr aPtr, IntPtr aInvocation)
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
                self.GetDRMState(invocation, instanceID, out currentDRMState);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetDRMState");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetDRMState"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetDRMState", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetDRMState", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetStateVariables(IntPtr aPtr, IntPtr aInvocation)
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
                self.GetStateVariables(invocation, instanceID, stateVariableList, out stateVariableValuePairs);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetStateVariables");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetStateVariables"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetStateVariables", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetStateVariables", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetStateVariables(IntPtr aPtr, IntPtr aInvocation)
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
                self.SetStateVariables(invocation, instanceID, aVTransportUDN, serviceType, serviceId, stateVariableValuePairs, out stateVariableList);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetStateVariables");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetStateVariables"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetStateVariables", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetStateVariables", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            if (DisposeProvider())
                iGch.Free();
        }
    }
}

