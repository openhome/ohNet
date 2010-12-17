using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderUpnpOrgAVTransport1 : IDisposable
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
        
    }
    /// <summary>
    /// Provider for the upnp.org:AVTransport:1 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgAVTransport1 : DvProvider, IDisposable, IDvProviderUpnpOrgAVTransport1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateSetAVTransportURI;
        private ActionDelegate iDelegateSetNextAVTransportURI;
        private ActionDelegate iDelegateGetMediaInfo;
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
        private PropertyString iPropertyLastChange;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgAVTransport1(DvDevice aDevice)
            : base(aDevice, "schemas-upnp-org", "AVTransport", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyLastChange = new PropertyString(new ParameterString("LastChange", allowedValues));
            AddProperty(iPropertyLastChange);
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
        /// Signal that the action SetAVTransportURI is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetAVTransportURI must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetAVTransportURI()
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
        /// DoSetNextAVTransportURI must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetNextAVTransportURI()
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
        /// DoGetMediaInfo must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetMediaInfo()
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
        /// Signal that the action GetTransportInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetTransportInfo must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetTransportInfo()
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
        /// DoGetPositionInfo must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetPositionInfo()
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
        /// DoGetDeviceCapabilities must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetDeviceCapabilities()
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
        /// DoGetTransportSettings must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetTransportSettings()
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
        /// DoStop must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStop()
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
        /// DoPlay must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPlay()
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
        /// DoPause must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPause()
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
        /// DoRecord must be overridden if this is called.</remarks>
        protected unsafe void EnableActionRecord()
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
        /// DoSeek must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeek()
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
        /// DoNext must be overridden if this is called.</remarks>
        protected unsafe void EnableActionNext()
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
        /// DoPrevious must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPrevious()
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
        /// DoSetPlayMode must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetPlayMode()
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
        /// DoSetRecordQualityMode must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetRecordQualityMode()
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
        /// DoGetCurrentTransportActions must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetCurrentTransportActions()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetCurrentTransportActions");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterString("Actions", allowedValues));
            iDelegateGetCurrentTransportActions = new ActionDelegate(DoGetCurrentTransportActions);
            EnableAction(action, iDelegateGetCurrentTransportActions, GCHandle.ToIntPtr(iGch));
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

        private static unsafe int DoSetAVTransportURI(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoSetNextAVTransportURI(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoGetMediaInfo(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoGetTransportInfo(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoGetPositionInfo(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoGetDeviceCapabilities(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoGetTransportSettings(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoStop(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoPlay(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoPause(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoRecord(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoSeek(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoNext(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoPrevious(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoSetPlayMode(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoSetRecordQualityMode(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoGetCurrentTransportActions(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgAVTransport1 self = (DvProviderUpnpOrgAVTransport1)gch.Target;
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
                invocation.WriteString("Actions", actions);
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

        ~DvProviderUpnpOrgAVTransport1()
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

