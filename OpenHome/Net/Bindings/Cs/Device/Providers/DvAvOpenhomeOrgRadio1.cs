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
        /// <returns>Value of the Uri property.</param>
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
        /// <returns>Value of the Metadata property.</param>
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
        /// <returns>Value of the TransportState property.</param>
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
        /// <returns>Value of the Id property.</param>
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
        /// <returns>Value of the IdArray property.</param>
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
        /// <returns>Value of the ChannelsMax property.</param>
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
        /// <returns>Value of the ProtocolInfo property.</param>
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
        }

        /// <summary>
        /// Enable the Uri property.
        /// </summary>
        public void EnablePropertyUri()
        {
            List<String> allowedValues = new List<String>();
            iPropertyUri = new PropertyString(new ParameterString("Uri", allowedValues));
            AddProperty(iPropertyUri);
        }

        /// <summary>
        /// Enable the Metadata property.
        /// </summary>
        public void EnablePropertyMetadata()
        {
            List<String> allowedValues = new List<String>();
            iPropertyMetadata = new PropertyString(new ParameterString("Metadata", allowedValues));
            AddProperty(iPropertyMetadata);
        }

        /// <summary>
        /// Enable the TransportState property.
        /// </summary>
        public void EnablePropertyTransportState()
        {
            List<String> allowedValues = new List<String>();
            allowedValues.Add("Stopped");
            allowedValues.Add("Playing");
            allowedValues.Add("Paused");
            allowedValues.Add("Buffering");
            iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues));
            AddProperty(iPropertyTransportState);
            allowedValues.Clear();
        }

        /// <summary>
        /// Enable the Id property.
        /// </summary>
        public void EnablePropertyId()
        {
            iPropertyId = new PropertyUint(new ParameterUint("Id"));
            AddProperty(iPropertyId);
        }

        /// <summary>
        /// Enable the IdArray property.
        /// </summary>
        public void EnablePropertyIdArray()
        {
            iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"));
            AddProperty(iPropertyIdArray);
        }

        /// <summary>
        /// Enable the ChannelsMax property.
        /// </summary>
        public void EnablePropertyChannelsMax()
        {
            iPropertyChannelsMax = new PropertyUint(new ParameterUint("ChannelsMax"));
            AddProperty(iPropertyChannelsMax);
        }

        /// <summary>
        /// Enable the ProtocolInfo property.
        /// </summary>
        public void EnablePropertyProtocolInfo()
        {
            List<String> allowedValues = new List<String>();
            iPropertyProtocolInfo = new PropertyString(new ParameterString("ProtocolInfo", allowedValues));
            AddProperty(iPropertyProtocolInfo);
        }

        /// <summary>
        /// Set the value of the Uri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyUri has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyUri(string aValue)
        {
            if (iPropertyUri == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyUri, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Uri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyUri has previously been called.</remarks>
        /// <returns>Value of the Uri property.</returns>
        public string PropertyUri()
        {
            if (iPropertyUri == null)
                throw new PropertyDisabledError();
            return iPropertyUri.Value();
        }

        /// <summary>
        /// Set the value of the Metadata property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyMetadata has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyMetadata(string aValue)
        {
            if (iPropertyMetadata == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyMetadata, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Metadata property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyMetadata has previously been called.</remarks>
        /// <returns>Value of the Metadata property.</returns>
        public string PropertyMetadata()
        {
            if (iPropertyMetadata == null)
                throw new PropertyDisabledError();
            return iPropertyMetadata.Value();
        }

        /// <summary>
        /// Set the value of the TransportState property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTransportState has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTransportState(string aValue)
        {
            if (iPropertyTransportState == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyTransportState, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TransportState property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTransportState has previously been called.</remarks>
        /// <returns>Value of the TransportState property.</returns>
        public string PropertyTransportState()
        {
            if (iPropertyTransportState == null)
                throw new PropertyDisabledError();
            return iPropertyTransportState.Value();
        }

        /// <summary>
        /// Set the value of the Id property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyId has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyId(uint aValue)
        {
            if (iPropertyId == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyId, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Id property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyId has previously been called.</remarks>
        /// <returns>Value of the Id property.</returns>
        public uint PropertyId()
        {
            if (iPropertyId == null)
                throw new PropertyDisabledError();
            return iPropertyId.Value();
        }

        /// <summary>
        /// Set the value of the IdArray property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyIdArray has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyIdArray(byte[] aValue)
        {
            if (iPropertyIdArray == null)
                throw new PropertyDisabledError();
            return SetPropertyBinary(iPropertyIdArray, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the IdArray property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyIdArray has previously been called.</remarks>
        /// <returns>Value of the IdArray property.</returns>
        public byte[] PropertyIdArray()
        {
            if (iPropertyIdArray == null)
                throw new PropertyDisabledError();
            return iPropertyIdArray.Value();
        }

        /// <summary>
        /// Set the value of the ChannelsMax property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyChannelsMax has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyChannelsMax(uint aValue)
        {
            if (iPropertyChannelsMax == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyChannelsMax, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ChannelsMax property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyChannelsMax has previously been called.</remarks>
        /// <returns>Value of the ChannelsMax property.</returns>
        public uint PropertyChannelsMax()
        {
            if (iPropertyChannelsMax == null)
                throw new PropertyDisabledError();
            return iPropertyChannelsMax.Value();
        }

        /// <summary>
        /// Set the value of the ProtocolInfo property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProtocolInfo has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProtocolInfo(string aValue)
        {
            if (iPropertyProtocolInfo == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyProtocolInfo, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProtocolInfo property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProtocolInfo has previously been called.</remarks>
        /// <returns>Value of the ProtocolInfo property.</returns>
        public string PropertyProtocolInfo()
        {
            if (iPropertyProtocolInfo == null)
                throw new PropertyDisabledError();
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void Play(IDvInvocation aInvocation)
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
        protected virtual void Pause(IDvInvocation aInvocation)
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
        protected virtual void Stop(IDvInvocation aInvocation)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SeekSecondAbsolute(IDvInvocation aInvocation, uint aValue)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SeekSecondRelative(IDvInvocation aInvocation, int aValue)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aUri"></param>
        /// <param name="aMetadata"></param>
        protected virtual void Channel(IDvInvocation aInvocation, out string aUri, out string aMetadata)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aUri"></param>
        /// <param name="aMetadata"></param>
        protected virtual void SetChannel(IDvInvocation aInvocation, string aUri, string aMetadata)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void TransportState(IDvInvocation aInvocation, out string aValue)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Id(IDvInvocation aInvocation, out uint aValue)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        /// <param name="aUri"></param>
        protected virtual void SetId(IDvInvocation aInvocation, uint aValue, string aUri)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aId"></param>
        /// <param name="aMetadata"></param>
        protected virtual void Read(IDvInvocation aInvocation, uint aId, out string aMetadata)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aIdList"></param>
        /// <param name="aChannelList"></param>
        protected virtual void ReadList(IDvInvocation aInvocation, string aIdList, out string aChannelList)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aToken"></param>
        /// <param name="aArray"></param>
        protected virtual void IdArray(IDvInvocation aInvocation, out uint aToken, out byte[] aArray)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aToken"></param>
        /// <param name="aValue"></param>
        protected virtual void IdArrayChanged(IDvInvocation aInvocation, uint aToken, out bool aValue)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void ChannelsMax(IDvInvocation aInvocation, out uint aValue)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void ProtocolInfo(IDvInvocation aInvocation, out string aValue)
        {
            throw (new ActionDisabledError());
        }

        private static int DoPlay(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Play(invocation);
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
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Pause(invocation);
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

        private static int DoStop(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Stop(invocation);
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

        private static int DoSeekSecondAbsolute(IntPtr aPtr, IntPtr aInvocation)
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
                self.SeekSecondAbsolute(invocation, value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SeekSecondAbsolute");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SeekSecondAbsolute"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SeekSecondAbsolute", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SeekSecondAbsolute", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSeekSecondRelative(IntPtr aPtr, IntPtr aInvocation)
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
                self.SeekSecondRelative(invocation, value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SeekSecondRelative");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SeekSecondRelative"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SeekSecondRelative", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SeekSecondRelative", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoChannel(IntPtr aPtr, IntPtr aInvocation)
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
                self.Channel(invocation, out uri, out metadata);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Channel");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Channel"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Channel", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Channel", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetChannel(IntPtr aPtr, IntPtr aInvocation)
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
                self.SetChannel(invocation, uri, metadata);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetChannel");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetChannel"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetChannel", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetChannel", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoTransportState(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.TransportState(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "TransportState");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "TransportState"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "TransportState", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "TransportState", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoId(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Id(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Id");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Id"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Id", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Id", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetId(IntPtr aPtr, IntPtr aInvocation)
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
                self.SetId(invocation, value, uri);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetId");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetId"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetId", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetId", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoRead(IntPtr aPtr, IntPtr aInvocation)
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
                self.Read(invocation, id, out metadata);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Read");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Read"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Read", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Read", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoReadList(IntPtr aPtr, IntPtr aInvocation)
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
                self.ReadList(invocation, idList, out channelList);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "ReadList");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "ReadList"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ReadList", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ReadList", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoIdArray(IntPtr aPtr, IntPtr aInvocation)
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
                self.IdArray(invocation, out token, out array);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "IdArray");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "IdArray"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "IdArray", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "IdArray", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoIdArrayChanged(IntPtr aPtr, IntPtr aInvocation)
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
                self.IdArrayChanged(invocation, token, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "IdArrayChanged");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "IdArrayChanged"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "IdArrayChanged", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "IdArrayChanged", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoChannelsMax(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ChannelsMax(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "ChannelsMax");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "ChannelsMax"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ChannelsMax", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ChannelsMax", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoProtocolInfo(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgRadio1 self = (DvProviderAvOpenhomeOrgRadio1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ProtocolInfo(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "ProtocolInfo");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "ProtocolInfo"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ProtocolInfo", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ProtocolInfo", e.TargetSite.Name);
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

