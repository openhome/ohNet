using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderAvOpenhomeOrgPlaylistManager1 : IDisposable
    {

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
        /// Set the value of the ImagesXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyImagesXml(string aValue);

        /// <summary>
        /// Get a copy of the value of the ImagesXml property
        /// </summary>
        /// <returns>Value of the ImagesXml property.</param>
        string PropertyImagesXml();

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
        /// Set the value of the TokenArray property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTokenArray(byte[] aValue);

        /// <summary>
        /// Get a copy of the value of the TokenArray property
        /// </summary>
        /// <returns>Value of the TokenArray property.</param>
        byte[] PropertyTokenArray();

        /// <summary>
        /// Set the value of the PlaylistsMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyPlaylistsMax(uint aValue);

        /// <summary>
        /// Get a copy of the value of the PlaylistsMax property
        /// </summary>
        /// <returns>Value of the PlaylistsMax property.</param>
        uint PropertyPlaylistsMax();

        /// <summary>
        /// Set the value of the TracksMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTracksMax(uint aValue);

        /// <summary>
        /// Get a copy of the value of the TracksMax property
        /// </summary>
        /// <returns>Value of the TracksMax property.</param>
        uint PropertyTracksMax();
        
    }
    /// <summary>
    /// Provider for the av.openhome.org:PlaylistManager:1 UPnP service
    /// </summary>
    public class DvProviderAvOpenhomeOrgPlaylistManager1 : DvProvider, IDisposable, IDvProviderAvOpenhomeOrgPlaylistManager1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateMetadata;
        private ActionDelegate iDelegateImagesXml;
        private ActionDelegate iDelegatePlaylistReadArray;
        private ActionDelegate iDelegatePlaylistReadList;
        private ActionDelegate iDelegatePlaylistRead;
        private ActionDelegate iDelegatePlaylistSetName;
        private ActionDelegate iDelegatePlaylistSetDescription;
        private ActionDelegate iDelegatePlaylistSetImageId;
        private ActionDelegate iDelegatePlaylistInsert;
        private ActionDelegate iDelegatePlaylistDeleteId;
        private ActionDelegate iDelegatePlaylistMove;
        private ActionDelegate iDelegatePlaylistsMax;
        private ActionDelegate iDelegateTracksMax;
        private ActionDelegate iDelegatePlaylistArrays;
        private ActionDelegate iDelegatePlaylistArraysChanged;
        private ActionDelegate iDelegateRead;
        private ActionDelegate iDelegateReadList;
        private ActionDelegate iDelegateInsert;
        private ActionDelegate iDelegateDeleteId;
        private ActionDelegate iDelegateDeleteAll;
        private PropertyString iPropertyMetadata;
        private PropertyString iPropertyImagesXml;
        private PropertyBinary iPropertyIdArray;
        private PropertyBinary iPropertyTokenArray;
        private PropertyUint iPropertyPlaylistsMax;
        private PropertyUint iPropertyTracksMax;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderAvOpenhomeOrgPlaylistManager1(DvDevice aDevice)
            : base(aDevice, "av.openhome.org", "PlaylistManager", 1)
        {
            iGch = GCHandle.Alloc(this);
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
        /// Enable the ImagesXml property.
        /// </summary>
        public void EnablePropertyImagesXml()
        {
            List<String> allowedValues = new List<String>();
            iPropertyImagesXml = new PropertyString(new ParameterString("ImagesXml", allowedValues));
            AddProperty(iPropertyImagesXml);
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
        /// Enable the TokenArray property.
        /// </summary>
        public void EnablePropertyTokenArray()
        {
            iPropertyTokenArray = new PropertyBinary(new ParameterBinary("TokenArray"));
            AddProperty(iPropertyTokenArray);
        }

        /// <summary>
        /// Enable the PlaylistsMax property.
        /// </summary>
        public void EnablePropertyPlaylistsMax()
        {
            iPropertyPlaylistsMax = new PropertyUint(new ParameterUint("PlaylistsMax"));
            AddProperty(iPropertyPlaylistsMax);
        }

        /// <summary>
        /// Enable the TracksMax property.
        /// </summary>
        public void EnablePropertyTracksMax()
        {
            iPropertyTracksMax = new PropertyUint(new ParameterUint("TracksMax"));
            AddProperty(iPropertyTracksMax);
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
        /// Set the value of the ImagesXml property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyImagesXml has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyImagesXml(string aValue)
        {
            if (iPropertyImagesXml == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyImagesXml, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ImagesXml property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyImagesXml has previously been called.</remarks>
        /// <returns>Value of the ImagesXml property.</returns>
        public string PropertyImagesXml()
        {
            if (iPropertyImagesXml == null)
                throw new PropertyDisabledError();
            return iPropertyImagesXml.Value();
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
        /// Set the value of the TokenArray property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTokenArray has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTokenArray(byte[] aValue)
        {
            if (iPropertyTokenArray == null)
                throw new PropertyDisabledError();
            return SetPropertyBinary(iPropertyTokenArray, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TokenArray property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTokenArray has previously been called.</remarks>
        /// <returns>Value of the TokenArray property.</returns>
        public byte[] PropertyTokenArray()
        {
            if (iPropertyTokenArray == null)
                throw new PropertyDisabledError();
            return iPropertyTokenArray.Value();
        }

        /// <summary>
        /// Set the value of the PlaylistsMax property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyPlaylistsMax has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyPlaylistsMax(uint aValue)
        {
            if (iPropertyPlaylistsMax == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyPlaylistsMax, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the PlaylistsMax property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyPlaylistsMax has previously been called.</remarks>
        /// <returns>Value of the PlaylistsMax property.</returns>
        public uint PropertyPlaylistsMax()
        {
            if (iPropertyPlaylistsMax == null)
                throw new PropertyDisabledError();
            return iPropertyPlaylistsMax.Value();
        }

        /// <summary>
        /// Set the value of the TracksMax property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTracksMax has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTracksMax(uint aValue)
        {
            if (iPropertyTracksMax == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyTracksMax, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TracksMax property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTracksMax has previously been called.</remarks>
        /// <returns>Value of the TracksMax property.</returns>
        public uint PropertyTracksMax()
        {
            if (iPropertyTracksMax == null)
                throw new PropertyDisabledError();
            return iPropertyTracksMax.Value();
        }

        /// <summary>
        /// Signal that the action Metadata is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Metadata must be overridden if this is called.</remarks>
        protected void EnableActionMetadata()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Metadata");
            action.AddOutputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
            iDelegateMetadata = new ActionDelegate(DoMetadata);
            EnableAction(action, iDelegateMetadata, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ImagesXml is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ImagesXml must be overridden if this is called.</remarks>
        protected void EnableActionImagesXml()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("ImagesXml");
            action.AddOutputParameter(new ParameterRelated("ImagesXml", iPropertyImagesXml));
            iDelegateImagesXml = new ActionDelegate(DoImagesXml);
            EnableAction(action, iDelegateImagesXml, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistReadArray is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistReadArray must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistReadArray()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistReadArray");
            action.AddInputParameter(new ParameterUint("Id"));
            action.AddOutputParameter(new ParameterRelated("Array", iPropertyIdArray));
            iDelegatePlaylistReadArray = new ActionDelegate(DoPlaylistReadArray);
            EnableAction(action, iDelegatePlaylistReadArray, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistReadList is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistReadList must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistReadList()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistReadList");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("IdList", allowedValues));
            action.AddOutputParameter(new ParameterString("PlaylistList", allowedValues));
            iDelegatePlaylistReadList = new ActionDelegate(DoPlaylistReadList);
            EnableAction(action, iDelegatePlaylistReadList, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistRead is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistRead must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistRead()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistRead");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("Id"));
            action.AddOutputParameter(new ParameterString("Name", allowedValues));
            action.AddOutputParameter(new ParameterString("Description", allowedValues));
            action.AddOutputParameter(new ParameterUint("ImageId"));
            iDelegatePlaylistRead = new ActionDelegate(DoPlaylistRead);
            EnableAction(action, iDelegatePlaylistRead, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistSetName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistSetName must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistSetName()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistSetName");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("Id"));
            action.AddInputParameter(new ParameterString("Name", allowedValues));
            iDelegatePlaylistSetName = new ActionDelegate(DoPlaylistSetName);
            EnableAction(action, iDelegatePlaylistSetName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistSetDescription is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistSetDescription must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistSetDescription()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistSetDescription");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("Id"));
            action.AddInputParameter(new ParameterString("Description", allowedValues));
            iDelegatePlaylistSetDescription = new ActionDelegate(DoPlaylistSetDescription);
            EnableAction(action, iDelegatePlaylistSetDescription, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistSetImageId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistSetImageId must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistSetImageId()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistSetImageId");
            action.AddInputParameter(new ParameterUint("Id"));
            action.AddInputParameter(new ParameterUint("ImageId"));
            iDelegatePlaylistSetImageId = new ActionDelegate(DoPlaylistSetImageId);
            EnableAction(action, iDelegatePlaylistSetImageId, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistInsert is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistInsert must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistInsert()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistInsert");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("AfterId"));
            action.AddInputParameter(new ParameterString("Name", allowedValues));
            action.AddInputParameter(new ParameterString("Description", allowedValues));
            action.AddInputParameter(new ParameterUint("ImageId"));
            action.AddOutputParameter(new ParameterUint("NewId"));
            iDelegatePlaylistInsert = new ActionDelegate(DoPlaylistInsert);
            EnableAction(action, iDelegatePlaylistInsert, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistDeleteId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistDeleteId must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistDeleteId()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistDeleteId");
            action.AddInputParameter(new ParameterUint("Value"));
            iDelegatePlaylistDeleteId = new ActionDelegate(DoPlaylistDeleteId);
            EnableAction(action, iDelegatePlaylistDeleteId, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistMove is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistMove must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistMove()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistMove");
            action.AddInputParameter(new ParameterUint("Id"));
            action.AddInputParameter(new ParameterUint("AfterId"));
            iDelegatePlaylistMove = new ActionDelegate(DoPlaylistMove);
            EnableAction(action, iDelegatePlaylistMove, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistsMax is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistsMax must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistsMax()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistsMax");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyPlaylistsMax));
            iDelegatePlaylistsMax = new ActionDelegate(DoPlaylistsMax);
            EnableAction(action, iDelegatePlaylistsMax, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action TracksMax is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// TracksMax must be overridden if this is called.</remarks>
        protected void EnableActionTracksMax()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("TracksMax");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyTracksMax));
            iDelegateTracksMax = new ActionDelegate(DoTracksMax);
            EnableAction(action, iDelegateTracksMax, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistArrays is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistArrays must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistArrays()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistArrays");
            action.AddOutputParameter(new ParameterUint("Token"));
            action.AddOutputParameter(new ParameterRelated("IdArray", iPropertyIdArray));
            action.AddOutputParameter(new ParameterRelated("TokenArray", iPropertyTokenArray));
            iDelegatePlaylistArrays = new ActionDelegate(DoPlaylistArrays);
            EnableAction(action, iDelegatePlaylistArrays, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PlaylistArraysChanged is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PlaylistArraysChanged must be overridden if this is called.</remarks>
        protected void EnableActionPlaylistArraysChanged()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PlaylistArraysChanged");
            action.AddInputParameter(new ParameterUint("Token"));
            action.AddOutputParameter(new ParameterBool("Value"));
            iDelegatePlaylistArraysChanged = new ActionDelegate(DoPlaylistArraysChanged);
            EnableAction(action, iDelegatePlaylistArraysChanged, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Read is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Read must be overridden if this is called.</remarks>
        protected void EnableActionRead()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Read");
            action.AddInputParameter(new ParameterUint("Id"));
            action.AddInputParameter(new ParameterUint("TrackId"));
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
            action.AddInputParameter(new ParameterUint("Id"));
            action.AddInputParameter(new ParameterString("TrackIdList", allowedValues));
            action.AddOutputParameter(new ParameterString("TrackList", allowedValues));
            iDelegateReadList = new ActionDelegate(DoReadList);
            EnableAction(action, iDelegateReadList, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Insert is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Insert must be overridden if this is called.</remarks>
        protected void EnableActionInsert()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Insert");
            action.AddInputParameter(new ParameterUint("Id"));
            action.AddInputParameter(new ParameterUint("AfterTrackId"));
            action.AddInputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
            action.AddOutputParameter(new ParameterUint("NewTrackId"));
            iDelegateInsert = new ActionDelegate(DoInsert);
            EnableAction(action, iDelegateInsert, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DeleteId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DeleteId must be overridden if this is called.</remarks>
        protected void EnableActionDeleteId()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("DeleteId");
            action.AddInputParameter(new ParameterUint("Id"));
            action.AddInputParameter(new ParameterUint("TrackId"));
            iDelegateDeleteId = new ActionDelegate(DoDeleteId);
            EnableAction(action, iDelegateDeleteId, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DeleteAll is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DeleteAll must be overridden if this is called.</remarks>
        protected void EnableActionDeleteAll()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("DeleteAll");
            action.AddInputParameter(new ParameterUint("Id"));
            iDelegateDeleteAll = new ActionDelegate(DoDeleteAll);
            EnableAction(action, iDelegateDeleteAll, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Metadata action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Metadata action for the owning device.
        ///
        /// Must be implemented iff EnableActionMetadata was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aMetadata"></param>
        protected virtual void Metadata(IDvInvocation aInvocation, out string aMetadata)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ImagesXml action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ImagesXml action for the owning device.
        ///
        /// Must be implemented iff EnableActionImagesXml was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aImagesXml"></param>
        protected virtual void ImagesXml(IDvInvocation aInvocation, out string aImagesXml)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistReadArray action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistReadArray action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistReadArray was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aId"></param>
        /// <param name="aArray"></param>
        protected virtual void PlaylistReadArray(IDvInvocation aInvocation, uint aId, out byte[] aArray)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistReadList action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistReadList action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistReadList was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aIdList"></param>
        /// <param name="aPlaylistList"></param>
        protected virtual void PlaylistReadList(IDvInvocation aInvocation, string aIdList, out string aPlaylistList)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistRead action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistRead action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistRead was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aId"></param>
        /// <param name="aName"></param>
        /// <param name="aDescription"></param>
        /// <param name="aImageId"></param>
        protected virtual void PlaylistRead(IDvInvocation aInvocation, uint aId, out string aName, out string aDescription, out uint aImageId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistSetName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistSetName action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistSetName was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aId"></param>
        /// <param name="aName"></param>
        protected virtual void PlaylistSetName(IDvInvocation aInvocation, uint aId, string aName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistSetDescription action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistSetDescription action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistSetDescription was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aId"></param>
        /// <param name="aDescription"></param>
        protected virtual void PlaylistSetDescription(IDvInvocation aInvocation, uint aId, string aDescription)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistSetImageId action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistSetImageId action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistSetImageId was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aId"></param>
        /// <param name="aImageId"></param>
        protected virtual void PlaylistSetImageId(IDvInvocation aInvocation, uint aId, uint aImageId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistInsert action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistInsert action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistInsert was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aAfterId"></param>
        /// <param name="aName"></param>
        /// <param name="aDescription"></param>
        /// <param name="aImageId"></param>
        /// <param name="aNewId"></param>
        protected virtual void PlaylistInsert(IDvInvocation aInvocation, uint aAfterId, string aName, string aDescription, uint aImageId, out uint aNewId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistDeleteId action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistDeleteId action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistDeleteId was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void PlaylistDeleteId(IDvInvocation aInvocation, uint aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistMove action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistMove action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistMove was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aId"></param>
        /// <param name="aAfterId"></param>
        protected virtual void PlaylistMove(IDvInvocation aInvocation, uint aId, uint aAfterId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistsMax action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistsMax action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistsMax was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void PlaylistsMax(IDvInvocation aInvocation, out uint aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// TracksMax action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// TracksMax action for the owning device.
        ///
        /// Must be implemented iff EnableActionTracksMax was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void TracksMax(IDvInvocation aInvocation, out uint aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistArrays action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistArrays action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistArrays was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aToken"></param>
        /// <param name="aIdArray"></param>
        /// <param name="aTokenArray"></param>
        protected virtual void PlaylistArrays(IDvInvocation aInvocation, out uint aToken, out byte[] aIdArray, out byte[] aTokenArray)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PlaylistArraysChanged action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PlaylistArraysChanged action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlaylistArraysChanged was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aToken"></param>
        /// <param name="aValue"></param>
        protected virtual void PlaylistArraysChanged(IDvInvocation aInvocation, uint aToken, out bool aValue)
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
        /// <param name="aTrackId"></param>
        /// <param name="aMetadata"></param>
        protected virtual void Read(IDvInvocation aInvocation, uint aId, uint aTrackId, out string aMetadata)
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
        /// <param name="aId"></param>
        /// <param name="aTrackIdList"></param>
        /// <param name="aTrackList"></param>
        protected virtual void ReadList(IDvInvocation aInvocation, uint aId, string aTrackIdList, out string aTrackList)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Insert action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Insert action for the owning device.
        ///
        /// Must be implemented iff EnableActionInsert was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aId"></param>
        /// <param name="aAfterTrackId"></param>
        /// <param name="aMetadata"></param>
        /// <param name="aNewTrackId"></param>
        protected virtual void Insert(IDvInvocation aInvocation, uint aId, uint aAfterTrackId, string aMetadata, out uint aNewTrackId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DeleteId action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DeleteId action for the owning device.
        ///
        /// Must be implemented iff EnableActionDeleteId was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aId"></param>
        /// <param name="aTrackId"></param>
        protected virtual void DeleteId(IDvInvocation aInvocation, uint aId, uint aTrackId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DeleteAll action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DeleteAll action for the owning device.
        ///
        /// Must be implemented iff EnableActionDeleteAll was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aId"></param>
        protected virtual void DeleteAll(IDvInvocation aInvocation, uint aId)
        {
            throw (new ActionDisabledError());
        }

        private static int DoMetadata(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string metadata;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Metadata(invocation, out metadata);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Metadata");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Metadata"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Metadata", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Metadata", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoImagesXml(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string imagesXml;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ImagesXml(invocation, out imagesXml);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "ImagesXml");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "ImagesXml"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ImagesXml", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("ImagesXml", imagesXml);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ImagesXml", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistReadArray(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            byte[] array;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                invocation.ReadEnd();
                self.PlaylistReadArray(invocation, id, out array);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistReadArray");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistReadArray"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistReadArray", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBinary("Array", array);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistReadArray", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistReadList(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string idList;
            string playlistList;
            try
            {
                invocation.ReadStart();
                idList = invocation.ReadString("IdList");
                invocation.ReadEnd();
                self.PlaylistReadList(invocation, idList, out playlistList);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistReadList");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistReadList"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistReadList", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("PlaylistList", playlistList);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistReadList", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistRead(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            string name;
            string description;
            uint imageId;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                invocation.ReadEnd();
                self.PlaylistRead(invocation, id, out name, out description, out imageId);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistRead");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistRead"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistRead", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Name", name);
                invocation.WriteString("Description", description);
                invocation.WriteUint("ImageId", imageId);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistRead", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistSetName(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            string name;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                name = invocation.ReadString("Name");
                invocation.ReadEnd();
                self.PlaylistSetName(invocation, id, name);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistSetName");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistSetName"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistSetName", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistSetName", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistSetDescription(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            string description;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                description = invocation.ReadString("Description");
                invocation.ReadEnd();
                self.PlaylistSetDescription(invocation, id, description);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistSetDescription");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistSetDescription"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistSetDescription", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistSetDescription", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistSetImageId(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            uint imageId;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                imageId = invocation.ReadUint("ImageId");
                invocation.ReadEnd();
                self.PlaylistSetImageId(invocation, id, imageId);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistSetImageId");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistSetImageId"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistSetImageId", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistSetImageId", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistInsert(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint afterId;
            string name;
            string description;
            uint imageId;
            uint newId;
            try
            {
                invocation.ReadStart();
                afterId = invocation.ReadUint("AfterId");
                name = invocation.ReadString("Name");
                description = invocation.ReadString("Description");
                imageId = invocation.ReadUint("ImageId");
                invocation.ReadEnd();
                self.PlaylistInsert(invocation, afterId, name, description, imageId, out newId);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistInsert");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistInsert"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistInsert", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("NewId", newId);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistInsert", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistDeleteId(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadUint("Value");
                invocation.ReadEnd();
                self.PlaylistDeleteId(invocation, value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistDeleteId");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistDeleteId"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistDeleteId", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistDeleteId", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistMove(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            uint afterId;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                afterId = invocation.ReadUint("AfterId");
                invocation.ReadEnd();
                self.PlaylistMove(invocation, id, afterId);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistMove");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistMove"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistMove", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistMove", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistsMax(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.PlaylistsMax(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistsMax");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistsMax"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistsMax", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistsMax", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoTracksMax(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.TracksMax(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "TracksMax");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "TracksMax"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "TracksMax", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "TracksMax", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistArrays(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint token;
            byte[] idArray;
            byte[] tokenArray;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.PlaylistArrays(invocation, out token, out idArray, out tokenArray);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistArrays");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistArrays"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistArrays", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Token", token);
                invocation.WriteBinary("IdArray", idArray);
                invocation.WriteBinary("TokenArray", tokenArray);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistArrays", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPlaylistArraysChanged(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint token;
            bool value;
            try
            {
                invocation.ReadStart();
                token = invocation.ReadUint("Token");
                invocation.ReadEnd();
                self.PlaylistArraysChanged(invocation, token, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PlaylistArraysChanged");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PlaylistArraysChanged"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistArraysChanged", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PlaylistArraysChanged", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoRead(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            uint trackId;
            string metadata;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                trackId = invocation.ReadUint("TrackId");
                invocation.ReadEnd();
                self.Read(invocation, id, trackId, out metadata);
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
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            string trackIdList;
            string trackList;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                trackIdList = invocation.ReadString("TrackIdList");
                invocation.ReadEnd();
                self.ReadList(invocation, id, trackIdList, out trackList);
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
                invocation.WriteString("TrackList", trackList);
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

        private static int DoInsert(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            uint afterTrackId;
            string metadata;
            uint newTrackId;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                afterTrackId = invocation.ReadUint("AfterTrackId");
                metadata = invocation.ReadString("Metadata");
                invocation.ReadEnd();
                self.Insert(invocation, id, afterTrackId, metadata, out newTrackId);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Insert");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Insert"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Insert", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("NewTrackId", newTrackId);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Insert", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoDeleteId(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            uint trackId;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                trackId = invocation.ReadUint("TrackId");
                invocation.ReadEnd();
                self.DeleteId(invocation, id, trackId);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "DeleteId");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "DeleteId"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "DeleteId", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "DeleteId", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoDeleteAll(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgPlaylistManager1 self = (DvProviderAvOpenhomeOrgPlaylistManager1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            try
            {
                invocation.ReadStart();
                id = invocation.ReadUint("Id");
                invocation.ReadEnd();
                self.DeleteAll(invocation, id);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "DeleteAll");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "DeleteAll"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "DeleteAll", e.TargetSite.Name);
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "DeleteAll", e.TargetSite.Name);
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

