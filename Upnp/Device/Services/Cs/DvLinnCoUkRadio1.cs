using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkRadio1 : IDisposable
    {

        /// <summary>
        /// Set the value of the ChannelUri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyChannelUri(string aValue);

        /// <summary>
        /// Get a copy of the value of the ChannelUri property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyChannelUri();

        /// <summary>
        /// Set the value of the ChannelMetadata property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyChannelMetadata(string aValue);

        /// <summary>
        /// Get a copy of the value of the ChannelMetadata property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyChannelMetadata();

        /// <summary>
        /// Set the value of the TransportState property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTransportState(string aValue);

        /// <summary>
        /// Get a copy of the value of the TransportState property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyTransportState();

        /// <summary>
        /// Set the value of the ProtocolInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProtocolInfo(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProtocolInfo property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyProtocolInfo();

        /// <summary>
        /// Set the value of the Id property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyId(uint aValue);

        /// <summary>
        /// Get a copy of the value of the Id property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyId();

        /// <summary>
        /// Set the value of the IdArray property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyIdArray(string aValue);

        /// <summary>
        /// Get a copy of the value of the IdArray property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyIdArray();

        /// <summary>
        /// Set the value of the IdsMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyIdsMax(uint aValue);

        /// <summary>
        /// Get a copy of the value of the IdsMax property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyIdsMax();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Radio:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkRadio1 : DvProvider, IDisposable, IDvProviderLinnCoUkRadio1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegatePlay;
        private ActionDelegate iDelegatePause;
        private ActionDelegate iDelegateStop;
        private ActionDelegate iDelegateSeekSecondAbsolute;
        private ActionDelegate iDelegateSeekSecondRelative;
        private ActionDelegate iDelegateChannel;
        private ActionDelegate iDelegateSetChannel;
        private ActionDelegate iDelegateProtocolInfo;
        private ActionDelegate iDelegateTransportState;
        private ActionDelegate iDelegateId;
        private ActionDelegate iDelegateSetId;
        private ActionDelegate iDelegateRead;
        private ActionDelegate iDelegateReadList;
        private ActionDelegate iDelegateIdArray;
        private ActionDelegate iDelegateIdArrayChanged;
        private ActionDelegate iDelegateIdsMax;
        private PropertyString iPropertyChannelUri;
        private PropertyString iPropertyChannelMetadata;
        private PropertyString iPropertyTransportState;
        private PropertyString iPropertyProtocolInfo;
        private PropertyUint iPropertyId;
        private PropertyBinary iPropertyIdArray;
        private PropertyUint iPropertyIdsMax;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkRadio1(DvDevice aDevice)
            : base(aDevice, "linn-co-uk", "Radio", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyChannelUri = new PropertyString(new ParameterString("ChannelUri", allowedValues));
            AddProperty(iPropertyChannelUri);
            iPropertyChannelMetadata = new PropertyString(new ParameterString("ChannelMetadata", allowedValues));
            AddProperty(iPropertyChannelMetadata);
            allowedValues.Add("Stopped");
            allowedValues.Add("Playing");
            allowedValues.Add("Paused");
            allowedValues.Add("Buffering");
            iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues));
            AddProperty(iPropertyTransportState);
            allowedValues.Clear();
            iPropertyProtocolInfo = new PropertyString(new ParameterString("ProtocolInfo", allowedValues));
            AddProperty(iPropertyProtocolInfo);
            iPropertyId = new PropertyUint(new ParameterUint("Id"));
            AddProperty(iPropertyId);
            iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"));
            AddProperty(iPropertyIdArray);
            iPropertyIdsMax = new PropertyUint(new ParameterUint("IdsMax"));
            AddProperty(iPropertyIdsMax);
        }

        /// <summary>
        /// Set the value of the ChannelUri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyChannelUri(string aValue)
        {
            return SetPropertyString(iPropertyChannelUri, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ChannelUri property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyChannelUri()
        {
            return iPropertyChannelUri.Value();
        }

        /// <summary>
        /// Set the value of the ChannelMetadata property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyChannelMetadata(string aValue)
        {
            return SetPropertyString(iPropertyChannelMetadata, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ChannelMetadata property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyChannelMetadata()
        {
            return iPropertyChannelMetadata.Value();
        }

        /// <summary>
        /// Set the value of the TransportState property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTransportState(string aValue)
        {
            return SetPropertyString(iPropertyTransportState, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TransportState property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyTransportState()
        {
            return iPropertyTransportState.Value();
        }

        /// <summary>
        /// Set the value of the ProtocolInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProtocolInfo(string aValue)
        {
            return SetPropertyString(iPropertyProtocolInfo, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProtocolInfo property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyProtocolInfo()
        {
            return iPropertyProtocolInfo.Value();
        }

        /// <summary>
        /// Set the value of the Id property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyId(uint aValue)
        {
            return SetPropertyUint(iPropertyId, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Id property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyId()
        {
            return iPropertyId.Value();
        }

        /// <summary>
        /// Set the value of the IdArray property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyIdArray(string aValue)
        {
            return SetPropertyBinary(iPropertyIdArray, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the IdArray property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyIdArray()
        {
            return iPropertyIdArray.Value();
        }

        /// <summary>
        /// Set the value of the IdsMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyIdsMax(uint aValue)
        {
            return SetPropertyUint(iPropertyIdsMax, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the IdsMax property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyIdsMax()
        {
            return iPropertyIdsMax.Value();
        }

        /// <summary>
        /// Signal that the action Play is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPlay must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPlay()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Play");
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
            iDelegatePause = new ActionDelegate(DoPause);
            EnableAction(action, iDelegatePause, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Stop is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStop must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStop()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Stop");
            iDelegateStop = new ActionDelegate(DoStop);
            EnableAction(action, iDelegateStop, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SeekSecondAbsolute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSeekSecondAbsolute must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeekSecondAbsolute()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SeekSecondAbsolute");
            action.AddInputParameter(new ParameterUint("aSecond"));
            iDelegateSeekSecondAbsolute = new ActionDelegate(DoSeekSecondAbsolute);
            EnableAction(action, iDelegateSeekSecondAbsolute, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SeekSecondRelative is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSeekSecondRelative must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeekSecondRelative()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SeekSecondRelative");
            action.AddInputParameter(new ParameterInt("aSecond"));
            iDelegateSeekSecondRelative = new ActionDelegate(DoSeekSecondRelative);
            EnableAction(action, iDelegateSeekSecondRelative, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Channel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoChannel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionChannel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Channel");
            action.AddOutputParameter(new ParameterRelated("aUri", iPropertyChannelUri));
            action.AddOutputParameter(new ParameterRelated("aMetadata", iPropertyChannelMetadata));
            iDelegateChannel = new ActionDelegate(DoChannel);
            EnableAction(action, iDelegateChannel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetChannel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetChannel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetChannel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetChannel");
            action.AddInputParameter(new ParameterRelated("aUri", iPropertyChannelUri));
            action.AddInputParameter(new ParameterRelated("aMetadata", iPropertyChannelMetadata));
            iDelegateSetChannel = new ActionDelegate(DoSetChannel);
            EnableAction(action, iDelegateSetChannel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ProtocolInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoProtocolInfo must be overridden if this is called.</remarks>
        protected unsafe void EnableActionProtocolInfo()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ProtocolInfo");
            action.AddOutputParameter(new ParameterRelated("aInfo", iPropertyProtocolInfo));
            iDelegateProtocolInfo = new ActionDelegate(DoProtocolInfo);
            EnableAction(action, iDelegateProtocolInfo, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action TransportState is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoTransportState must be overridden if this is called.</remarks>
        protected unsafe void EnableActionTransportState()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("TransportState");
            action.AddOutputParameter(new ParameterRelated("aState", iPropertyTransportState));
            iDelegateTransportState = new ActionDelegate(DoTransportState);
            EnableAction(action, iDelegateTransportState, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Id is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoId must be overridden if this is called.</remarks>
        protected unsafe void EnableActionId()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Id");
            action.AddOutputParameter(new ParameterRelated("aId", iPropertyId));
            iDelegateId = new ActionDelegate(DoId);
            EnableAction(action, iDelegateId, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetId must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetId()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetId");
            action.AddInputParameter(new ParameterRelated("aId", iPropertyId));
            action.AddInputParameter(new ParameterRelated("aUri", iPropertyChannelUri));
            iDelegateSetId = new ActionDelegate(DoSetId);
            EnableAction(action, iDelegateSetId, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Read is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoRead must be overridden if this is called.</remarks>
        protected unsafe void EnableActionRead()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Read");
            action.AddInputParameter(new ParameterRelated("aId", iPropertyId));
            action.AddOutputParameter(new ParameterRelated("aMetadata", iPropertyChannelMetadata));
            iDelegateRead = new ActionDelegate(DoRead);
            EnableAction(action, iDelegateRead, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ReadList is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoReadList must be overridden if this is called.</remarks>
        protected unsafe void EnableActionReadList()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ReadList");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("aIdList", allowedValues));
            action.AddOutputParameter(new ParameterString("aMetadataList", allowedValues));
            iDelegateReadList = new ActionDelegate(DoReadList);
            EnableAction(action, iDelegateReadList, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action IdArray is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoIdArray must be overridden if this is called.</remarks>
        protected unsafe void EnableActionIdArray()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("IdArray");
            action.AddOutputParameter(new ParameterUint("aIdArrayToken"));
            action.AddOutputParameter(new ParameterRelated("aIdArray", iPropertyIdArray));
            iDelegateIdArray = new ActionDelegate(DoIdArray);
            EnableAction(action, iDelegateIdArray, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action IdArrayChanged is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoIdArrayChanged must be overridden if this is called.</remarks>
        protected unsafe void EnableActionIdArrayChanged()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("IdArrayChanged");
            action.AddInputParameter(new ParameterUint("aIdArrayToken"));
            action.AddOutputParameter(new ParameterBool("aIdArrayChanged"));
            iDelegateIdArrayChanged = new ActionDelegate(DoIdArrayChanged);
            EnableAction(action, iDelegateIdArrayChanged, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action IdsMax is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoIdsMax must be overridden if this is called.</remarks>
        protected unsafe void EnableActionIdsMax()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("IdsMax");
            action.AddOutputParameter(new ParameterRelated("aIdsMax", iPropertyIdsMax));
            iDelegateIdsMax = new ActionDelegate(DoIdsMax);
            EnableAction(action, iDelegateIdsMax, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Play action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Play action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlay was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Play(uint aVersion)
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
        protected virtual void Pause(uint aVersion)
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
        protected virtual void Stop(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekSecondAbsolute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekSecondAbsolute action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekSecondAbsolute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSecond"></param>
        protected virtual void SeekSecondAbsolute(uint aVersion, uint aaSecond)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekSecondRelative action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekSecondRelative action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekSecondRelative was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSecond"></param>
        protected virtual void SeekSecondRelative(uint aVersion, int aaSecond)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Channel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Channel action for the owning device.
        ///
        /// Must be implemented iff EnableActionChannel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        protected virtual void Channel(uint aVersion, out string aaUri, out string aaMetadata)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetChannel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetChannel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetChannel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        protected virtual void SetChannel(uint aVersion, string aaUri, string aaMetadata)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ProtocolInfo action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ProtocolInfo action for the owning device.
        ///
        /// Must be implemented iff EnableActionProtocolInfo was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaInfo"></param>
        protected virtual void ProtocolInfo(uint aVersion, out string aaInfo)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// TransportState action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// TransportState action for the owning device.
        ///
        /// Must be implemented iff EnableActionTransportState was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaState"></param>
        protected virtual void TransportState(uint aVersion, out string aaState)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Id action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Id action for the owning device.
        ///
        /// Must be implemented iff EnableActionId was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaId"></param>
        protected virtual void Id(uint aVersion, out uint aaId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetId action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetId action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetId was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaId"></param>
        /// <param name="aaUri"></param>
        protected virtual void SetId(uint aVersion, uint aaId, string aaUri)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Read action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Read action for the owning device.
        ///
        /// Must be implemented iff EnableActionRead was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaId"></param>
        /// <param name="aaMetadata"></param>
        protected virtual void Read(uint aVersion, uint aaId, out string aaMetadata)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ReadList action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ReadList action for the owning device.
        ///
        /// Must be implemented iff EnableActionReadList was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIdList"></param>
        /// <param name="aaMetadataList"></param>
        protected virtual void ReadList(uint aVersion, string aaIdList, out string aaMetadataList)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// IdArray action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// IdArray action for the owning device.
        ///
        /// Must be implemented iff EnableActionIdArray was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArray"></param>
        protected virtual void IdArray(uint aVersion, out uint aaIdArrayToken, out string aaIdArray)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// IdArrayChanged action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// IdArrayChanged action for the owning device.
        ///
        /// Must be implemented iff EnableActionIdArrayChanged was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArrayChanged"></param>
        protected virtual void IdArrayChanged(uint aVersion, uint aaIdArrayToken, out bool aaIdArrayChanged)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// IdsMax action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// IdsMax action for the owning device.
        ///
        /// Must be implemented iff EnableActionIdsMax was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIdsMax"></param>
        protected virtual void IdsMax(uint aVersion, out uint aaIdsMax)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoPlay(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            self.Play(aVersion);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoPause(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            self.Pause(aVersion);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoStop(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            self.Stop(aVersion);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSeekSecondAbsolute(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            uint aSecond = invocation.ReadUint("aSecond");
            invocation.ReadEnd();
            self.SeekSecondAbsolute(aVersion, aSecond);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSeekSecondRelative(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            int aSecond = invocation.ReadInt("aSecond");
            invocation.ReadEnd();
            self.SeekSecondRelative(aVersion, aSecond);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoChannel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            string aUri;
            string aMetadata;
            self.Channel(aVersion, out aUri, out aMetadata);
            invocation.WriteStart();
            invocation.WriteString("aUri", aUri);
            invocation.WriteString("aMetadata", aMetadata);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSetChannel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            string aUri = invocation.ReadString("aUri");
            string aMetadata = invocation.ReadString("aMetadata");
            invocation.ReadEnd();
            self.SetChannel(aVersion, aUri, aMetadata);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoProtocolInfo(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            string aInfo;
            self.ProtocolInfo(aVersion, out aInfo);
            invocation.WriteStart();
            invocation.WriteString("aInfo", aInfo);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoTransportState(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            string aState;
            self.TransportState(aVersion, out aState);
            invocation.WriteStart();
            invocation.WriteString("aState", aState);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoId(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            uint aId;
            self.Id(aVersion, out aId);
            invocation.WriteStart();
            invocation.WriteUint("aId", aId);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSetId(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            uint aId = invocation.ReadUint("aId");
            string aUri = invocation.ReadString("aUri");
            invocation.ReadEnd();
            self.SetId(aVersion, aId, aUri);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoRead(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            uint aId = invocation.ReadUint("aId");
            invocation.ReadEnd();
            string aMetadata;
            self.Read(aVersion, aId, out aMetadata);
            invocation.WriteStart();
            invocation.WriteString("aMetadata", aMetadata);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoReadList(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            string aIdList = invocation.ReadString("aIdList");
            invocation.ReadEnd();
            string aMetadataList;
            self.ReadList(aVersion, aIdList, out aMetadataList);
            invocation.WriteStart();
            invocation.WriteString("aMetadataList", aMetadataList);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoIdArray(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            uint aIdArrayToken;
            string aIdArray;
            self.IdArray(aVersion, out aIdArrayToken, out aIdArray);
            invocation.WriteStart();
            invocation.WriteUint("aIdArrayToken", aIdArrayToken);
            invocation.WriteBinary("aIdArray", aIdArray);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoIdArrayChanged(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            uint aIdArrayToken = invocation.ReadUint("aIdArrayToken");
            invocation.ReadEnd();
            bool aIdArrayChanged;
            self.IdArrayChanged(aVersion, aIdArrayToken, out aIdArrayChanged);
            invocation.WriteStart();
            invocation.WriteBool("aIdArrayChanged", aIdArrayChanged);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoIdsMax(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            uint aIdsMax;
            self.IdsMax(aVersion, out aIdsMax);
            invocation.WriteStart();
            invocation.WriteUint("aIdsMax", aIdsMax);
            invocation.WriteEnd();
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

        ~DvProviderLinnCoUkRadio1()
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

