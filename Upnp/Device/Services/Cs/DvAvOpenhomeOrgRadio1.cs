using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderAvOpenhomeOrgRadio1 : IDisposable
    {

        /// <summary>
        /// Set the value of the Uri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyUri(string aValue);

        /// <summary>
        /// Get a copy of the value of the Uri property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyUri();

        /// <summary>
        /// Set the value of the Metadata property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyMetadata(string aValue);

        /// <summary>
        /// Get a copy of the value of the Metadata property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyMetadata();

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
        bool SetPropertyIdArray(byte[] aValue);

        /// <summary>
        /// Get a copy of the value of the IdArray property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        byte[] PropertyIdArray();

        /// <summary>
        /// Set the value of the ChannelsMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyChannelsMax(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ChannelsMax property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyChannelsMax();

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
        
    }
    /// <summary>
    /// Provider for the av.openhome.org:Radio:1 UPnP service
    /// </summary>
    public class DvProviderAvOpenhomeOrgRadio1 : DvProvider, IDisposable, IDvProviderAvOpenhomeOrgRadio1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegatePlay;
        private ActionDelegate iDelegatePause;
        private ActionDelegate iDelegateStop;
        private ActionDelegate iDelegateSeekSecondAbsolute;
        private ActionDelegate iDelegateSeekSecondRelative;
        private ActionDelegate iDelegateChannel;
        private ActionDelegate iDelegateSetChannel;
        private ActionDelegate iDelegateTransportState;
        private ActionDelegate iDelegateId;
        private ActionDelegate iDelegateSetId;
        private ActionDelegate iDelegateRead;
        private ActionDelegate iDelegateReadList;
        private ActionDelegate iDelegateIdArray;
        private ActionDelegate iDelegateIdArrayChanged;
        private ActionDelegate iDelegateChannelsMax;
        private ActionDelegate iDelegateProtocolInfo;
        private PropertyString iPropertyUri;
        private PropertyString iPropertyMetadata;
        private PropertyString iPropertyTransportState;
        private PropertyUint iPropertyId;
        private PropertyBinary iPropertyIdArray;
        private PropertyUint iPropertyChannelsMax;
        private PropertyString iPropertyProtocolInfo;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderAvOpenhomeOrgRadio1(DvDevice aDevice)
            : base(aDevice, "av.openhome.org", "Radio", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyUri = new PropertyString(new ParameterString("Uri", allowedValues));
            AddProperty(iPropertyUri);
            iPropertyMetadata = new PropertyString(new ParameterString("Metadata", allowedValues));
            AddProperty(iPropertyMetadata);
            allowedValues.Add("Stopped");
            allowedValues.Add("Playing");
            allowedValues.Add("Paused");
            allowedValues.Add("Buffering");
            iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues));
            AddProperty(iPropertyTransportState);
            allowedValues.Clear();
            iPropertyId = new PropertyUint(new ParameterUint("Id"));
            AddProperty(iPropertyId);
            iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"));
            AddProperty(iPropertyIdArray);
            iPropertyChannelsMax = new PropertyUint(new ParameterUint("ChannelsMax"));
            AddProperty(iPropertyChannelsMax);
            iPropertyProtocolInfo = new PropertyString(new ParameterString("ProtocolInfo", allowedValues));
            AddProperty(iPropertyProtocolInfo);
        }

        /// <summary>
        /// Set the value of the Uri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyUri(string aValue)
        {
            return SetPropertyString(iPropertyUri, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Uri property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyUri()
        {
            return iPropertyUri.Value();
        }

        /// <summary>
        /// Set the value of the Metadata property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyMetadata(string aValue)
        {
            return SetPropertyString(iPropertyMetadata, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Metadata property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyMetadata()
        {
            return iPropertyMetadata.Value();
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
        public bool SetPropertyIdArray(byte[] aValue)
        {
            return SetPropertyBinary(iPropertyIdArray, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the IdArray property
        /// </summary>
        /// <returns>The value of the property</returns>
        public byte[] PropertyIdArray()
        {
            return iPropertyIdArray.Value();
        }

        /// <summary>
        /// Set the value of the ChannelsMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyChannelsMax(uint aValue)
        {
            return SetPropertyUint(iPropertyChannelsMax, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ChannelsMax property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyChannelsMax()
        {
            return iPropertyChannelsMax.Value();
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
        /// Signal that the action Play is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Play must be overridden if this is called.</remarks>
        protected void EnableActionPlay()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Play");
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
            iDelegatePause = new ActionDelegate(DoPause);
            EnableAction(action, iDelegatePause, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Stop is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Stop must be overridden if this is called.</remarks>
        protected void EnableActionStop()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Stop");
            iDelegateStop = new ActionDelegate(DoStop);
            EnableAction(action, iDelegateStop, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SeekSecondAbsolute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SeekSecondAbsolute must be overridden if this is called.</remarks>
        protected void EnableActionSeekSecondAbsolute()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SeekSecondAbsolute");
            action.AddInputParameter(new ParameterUint("Value"));
            iDelegateSeekSecondAbsolute = new ActionDelegate(DoSeekSecondAbsolute);
            EnableAction(action, iDelegateSeekSecondAbsolute, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SeekSecondRelative is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SeekSecondRelative must be overridden if this is called.</remarks>
        protected void EnableActionSeekSecondRelative()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SeekSecondRelative");
            action.AddInputParameter(new ParameterInt("Value"));
            iDelegateSeekSecondRelative = new ActionDelegate(DoSeekSecondRelative);
            EnableAction(action, iDelegateSeekSecondRelative, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Channel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Channel must be overridden if this is called.</remarks>
        protected void EnableActionChannel()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Channel");
            action.AddOutputParameter(new ParameterRelated("Uri", iPropertyUri));
            action.AddOutputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
            iDelegateChannel = new ActionDelegate(DoChannel);
            EnableAction(action, iDelegateChannel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetChannel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetChannel must be overridden if this is called.</remarks>
        protected void EnableActionSetChannel()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetChannel");
            action.AddInputParameter(new ParameterRelated("Uri", iPropertyUri));
            action.AddInputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
            iDelegateSetChannel = new ActionDelegate(DoSetChannel);
            EnableAction(action, iDelegateSetChannel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action TransportState is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// TransportState must be overridden if this is called.</remarks>
        protected void EnableActionTransportState()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("TransportState");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyTransportState));
            iDelegateTransportState = new ActionDelegate(DoTransportState);
            EnableAction(action, iDelegateTransportState, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Id is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Id must be overridden if this is called.</remarks>
        protected void EnableActionId()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Id");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyId));
            iDelegateId = new ActionDelegate(DoId);
            EnableAction(action, iDelegateId, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetId must be overridden if this is called.</remarks>
        protected void EnableActionSetId()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetId");
            action.AddInputParameter(new ParameterRelated("Value", iPropertyId));
            action.AddInputParameter(new ParameterRelated("Uri", iPropertyUri));
            iDelegateSetId = new ActionDelegate(DoSetId);
            EnableAction(action, iDelegateSetId, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Read is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Read must be overridden if this is called.</remarks>
        protected void EnableActionRead()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Read");
            action.AddInputParameter(new ParameterRelated("Id", iPropertyId));
            action.AddOutputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
            iDelegateRead = new ActionDelegate(DoRead);
            EnableAction(action, iDelegateRead, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ReadList is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ReadList must be overridden if this is called.</remarks>
        protected void EnableActionReadList()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("ReadList");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("IdList", allowedValues));
            action.AddOutputParameter(new ParameterString("ChannelList", allowedValues));
            iDelegateReadList = new ActionDelegate(DoReadList);
            EnableAction(action, iDelegateReadList, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action IdArray is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// IdArray must be overridden if this is called.</remarks>
        protected void EnableActionIdArray()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("IdArray");
            action.AddOutputParameter(new ParameterUint("Token"));
            action.AddOutputParameter(new ParameterRelated("Array", iPropertyIdArray));
            iDelegateIdArray = new ActionDelegate(DoIdArray);
            EnableAction(action, iDelegateIdArray, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action IdArrayChanged is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// IdArrayChanged must be overridden if this is called.</remarks>
        protected void EnableActionIdArrayChanged()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("IdArrayChanged");
            action.AddInputParameter(new ParameterUint("Token"));
            action.AddOutputParameter(new ParameterBool("Value"));
            iDelegateIdArrayChanged = new ActionDelegate(DoIdArrayChanged);
            EnableAction(action, iDelegateIdArrayChanged, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ChannelsMax is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ChannelsMax must be overridden if this is called.</remarks>
        protected void EnableActionChannelsMax()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("ChannelsMax");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyChannelsMax));
            iDelegateChannelsMax = new ActionDelegate(DoChannelsMax);
            EnableAction(action, iDelegateChannelsMax, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ProtocolInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ProtocolInfo must be overridden if this is called.</remarks>
        protected void EnableActionProtocolInfo()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("ProtocolInfo");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyProtocolInfo));
            iDelegateProtocolInfo = new ActionDelegate(DoProtocolInfo);
            EnableAction(action, iDelegateProtocolInfo, GCHandle.ToIntPtr(iGch));
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
        /// <param name="aValue"></param>
        protected virtual void SeekSecondAbsolute(uint aVersion, uint aValue)
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
        /// <param name="aValue"></param>
        protected virtual void SeekSecondRelative(uint aVersion, int aValue)
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
        /// <param name="aUri"></param>
        /// <param name="aMetadata"></param>
        protected virtual void Channel(uint aVersion, out string aUri, out string aMetadata)
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
        /// <param name="aUri"></param>
        /// <param name="aMetadata"></param>
        protected virtual void SetChannel(uint aVersion, string aUri, string aMetadata)
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
        /// <param name="aValue"></param>
        protected virtual void TransportState(uint aVersion, out string aValue)
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
        /// <param name="aValue"></param>
        protected virtual void Id(uint aVersion, out uint aValue)
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
        /// <param name="aValue"></param>
        /// <param name="aUri"></param>
        protected virtual void SetId(uint aVersion, uint aValue, string aUri)
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
        /// <param name="aId"></param>
        /// <param name="aMetadata"></param>
        protected virtual void Read(uint aVersion, uint aId, out string aMetadata)
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
        /// <param name="aIdList"></param>
        /// <param name="aChannelList"></param>
        protected virtual void ReadList(uint aVersion, string aIdList, out string aChannelList)
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
        /// <param name="aToken"></param>
        /// <param name="aArray"></param>
        protected virtual void IdArray(uint aVersion, out uint aToken, out byte[] aArray)
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
        /// <param name="aToken"></param>
        /// <param name="aValue"></param>
        protected virtual void IdArrayChanged(uint aVersion, uint aToken, out bool aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ChannelsMax action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ChannelsMax action for the owning device.
        ///
        /// Must be implemented iff EnableActionChannelsMax was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValue"></param>
        protected virtual void ChannelsMax(uint aVersion, out uint aValue)
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
        /// <param name="aValue"></param>
        protected virtual void ProtocolInfo(uint aVersion, out string aValue)
        {
            throw (new ActionDisabledError());
        }

        private static int DoPlay(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Play(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoPause(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Pause(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoStop(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Stop(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSeekSecondAbsolute(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadUint("Value");
                invocation.ReadEnd();
                self.SeekSecondAbsolute(aVersion, value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSeekSecondRelative(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int value;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadInt("Value");
                invocation.ReadEnd();
                self.SeekSecondRelative(aVersion, value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoChannel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string uri;
            string metadata;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Channel(aVersion, out uri, out metadata);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Uri", uri);
                invocation.WriteString("Metadata", metadata);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSetChannel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string uri;
            string metadata;
            try
            {
                invocation.ReadStart();
                uri = invocation.ReadString("Uri");
                metadata = invocation.ReadString("Metadata");
                invocation.ReadEnd();
                self.SetChannel(aVersion, uri, metadata);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoTransportState(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.TransportState(aVersion, out value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoId(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Id(aVersion, out value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSetId(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            string uri;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadUint("Value");
                uri = invocation.ReadString("Uri");
                invocation.ReadEnd();
                self.SetId(aVersion, value, uri);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoRead(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            string metadata;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                invocation.ReadEnd();
                self.Read(aVersion, id, out metadata);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Metadata", metadata);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoReadList(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string idList;
            string channelList;
            try
            {
                invocation.ReadStart();
                idList = invocation.ReadString("IdList");
                invocation.ReadEnd();
                self.ReadList(aVersion, idList, out channelList);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("ChannelList", channelList);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoIdArray(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint token;
            byte[] array;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.IdArray(aVersion, out token, out array);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Token", token);
                invocation.WriteBinary("Array", array);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoIdArrayChanged(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint token;
            bool value;
            try
            {
                invocation.ReadStart();
                token = invocation.ReadUint("Token");
                invocation.ReadEnd();
                self.IdArrayChanged(aVersion, token, out value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoChannelsMax(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ChannelsMax(aVersion, out value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoProtocolInfo(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ProtocolInfo(aVersion, out value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderAvOpenhomeOrgRadio1()
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

