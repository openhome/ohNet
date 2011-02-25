using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkPlaylist1 : IDisposable
    {

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
        /// Set the value of the Repeat property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyRepeat(bool aValue);

        /// <summary>
        /// Get a copy of the value of the Repeat property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyRepeat();

        /// <summary>
        /// Set the value of the Shuffle property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyShuffle(bool aValue);

        /// <summary>
        /// Get a copy of the value of the Shuffle property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyShuffle();

        /// <summary>
        /// Set the value of the TracksMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTracksMax(uint aValue);

        /// <summary>
        /// Get a copy of the value of the TracksMax property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyTracksMax();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Playlist:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkPlaylist1 : DvProvider, IDisposable, IDvProviderLinnCoUkPlaylist1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateRead;
        private ActionDelegate iDelegateReadList;
        private ActionDelegate iDelegateInsert;
        private ActionDelegate iDelegateDelete;
        private ActionDelegate iDelegateDeleteAll;
        private ActionDelegate iDelegateSetRepeat;
        private ActionDelegate iDelegateRepeat;
        private ActionDelegate iDelegateSetShuffle;
        private ActionDelegate iDelegateShuffle;
        private ActionDelegate iDelegateTracksMax;
        private ActionDelegate iDelegateIdArray;
        private ActionDelegate iDelegateIdArrayChanged;
        private PropertyBinary iPropertyIdArray;
        private PropertyBool iPropertyRepeat;
        private PropertyBool iPropertyShuffle;
        private PropertyUint iPropertyTracksMax;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkPlaylist1(DvDevice aDevice)
            : base(aDevice, "linn.co.uk", "Playlist", 1)
        {
            iGch = GCHandle.Alloc(this);
            iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"));
            AddProperty(iPropertyIdArray);
            iPropertyRepeat = new PropertyBool(new ParameterBool("Repeat"));
            AddProperty(iPropertyRepeat);
            iPropertyShuffle = new PropertyBool(new ParameterBool("Shuffle"));
            AddProperty(iPropertyShuffle);
            iPropertyTracksMax = new PropertyUint(new ParameterUint("TracksMax"));
            AddProperty(iPropertyTracksMax);
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
        /// Set the value of the Repeat property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyRepeat(bool aValue)
        {
            return SetPropertyBool(iPropertyRepeat, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Repeat property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyRepeat()
        {
            return iPropertyRepeat.Value();
        }

        /// <summary>
        /// Set the value of the Shuffle property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyShuffle(bool aValue)
        {
            return SetPropertyBool(iPropertyShuffle, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Shuffle property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyShuffle()
        {
            return iPropertyShuffle.Value();
        }

        /// <summary>
        /// Set the value of the TracksMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTracksMax(uint aValue)
        {
            return SetPropertyUint(iPropertyTracksMax, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TracksMax property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyTracksMax()
        {
            return iPropertyTracksMax.Value();
        }

        /// <summary>
        /// Signal that the action Read is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Read must be overridden if this is called.</remarks>
        protected void EnableActionRead()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Read");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("aId"));
            action.AddOutputParameter(new ParameterString("aUri", allowedValues));
            action.AddOutputParameter(new ParameterString("aMetaData", allowedValues));
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
            Zapp.Core.Action action = new Zapp.Core.Action("ReadList");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("aIdList", allowedValues));
            action.AddOutputParameter(new ParameterString("aMetaDataList", allowedValues));
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
            Zapp.Core.Action action = new Zapp.Core.Action("Insert");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("aAfterId"));
            action.AddInputParameter(new ParameterString("aUri", allowedValues));
            action.AddInputParameter(new ParameterString("aMetaData", allowedValues));
            action.AddOutputParameter(new ParameterUint("aNewId"));
            iDelegateInsert = new ActionDelegate(DoInsert);
            EnableAction(action, iDelegateInsert, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Delete is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Delete must be overridden if this is called.</remarks>
        protected void EnableActionDelete()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Delete");
            action.AddInputParameter(new ParameterUint("aId"));
            iDelegateDelete = new ActionDelegate(DoDelete);
            EnableAction(action, iDelegateDelete, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DeleteAll is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DeleteAll must be overridden if this is called.</remarks>
        protected void EnableActionDeleteAll()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DeleteAll");
            iDelegateDeleteAll = new ActionDelegate(DoDeleteAll);
            EnableAction(action, iDelegateDeleteAll, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetRepeat is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetRepeat must be overridden if this is called.</remarks>
        protected void EnableActionSetRepeat()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetRepeat");
            action.AddInputParameter(new ParameterRelated("aRepeat", iPropertyRepeat));
            iDelegateSetRepeat = new ActionDelegate(DoSetRepeat);
            EnableAction(action, iDelegateSetRepeat, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Repeat is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Repeat must be overridden if this is called.</remarks>
        protected void EnableActionRepeat()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Repeat");
            action.AddOutputParameter(new ParameterRelated("aRepeat", iPropertyRepeat));
            iDelegateRepeat = new ActionDelegate(DoRepeat);
            EnableAction(action, iDelegateRepeat, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetShuffle is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetShuffle must be overridden if this is called.</remarks>
        protected void EnableActionSetShuffle()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetShuffle");
            action.AddInputParameter(new ParameterRelated("aShuffle", iPropertyShuffle));
            iDelegateSetShuffle = new ActionDelegate(DoSetShuffle);
            EnableAction(action, iDelegateSetShuffle, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Shuffle is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Shuffle must be overridden if this is called.</remarks>
        protected void EnableActionShuffle()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Shuffle");
            action.AddOutputParameter(new ParameterRelated("aShuffle", iPropertyShuffle));
            iDelegateShuffle = new ActionDelegate(DoShuffle);
            EnableAction(action, iDelegateShuffle, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action TracksMax is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// TracksMax must be overridden if this is called.</remarks>
        protected void EnableActionTracksMax()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("TracksMax");
            action.AddOutputParameter(new ParameterRelated("aTracksMax", iPropertyTracksMax));
            iDelegateTracksMax = new ActionDelegate(DoTracksMax);
            EnableAction(action, iDelegateTracksMax, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action IdArray is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// IdArray must be overridden if this is called.</remarks>
        protected void EnableActionIdArray()
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
        /// IdArrayChanged must be overridden if this is called.</remarks>
        protected void EnableActionIdArrayChanged()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("IdArrayChanged");
            action.AddInputParameter(new ParameterUint("aIdArrayToken"));
            action.AddOutputParameter(new ParameterBool("aIdArrayChanged"));
            iDelegateIdArrayChanged = new ActionDelegate(DoIdArrayChanged);
            EnableAction(action, iDelegateIdArrayChanged, GCHandle.ToIntPtr(iGch));
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
        /// <param name="aaUri"></param>
        /// <param name="aaMetaData"></param>
        protected virtual void Read(uint aVersion, uint aaId, out string aaUri, out string aaMetaData)
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
        /// <param name="aaMetaDataList"></param>
        protected virtual void ReadList(uint aVersion, string aaIdList, out string aaMetaDataList)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaAfterId"></param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetaData"></param>
        /// <param name="aaNewId"></param>
        protected virtual void Insert(uint aVersion, uint aaAfterId, string aaUri, string aaMetaData, out uint aaNewId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Delete action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Delete action for the owning device.
        ///
        /// Must be implemented iff EnableActionDelete was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaId"></param>
        protected virtual void Delete(uint aVersion, uint aaId)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void DeleteAll(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetRepeat action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetRepeat action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetRepeat was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaRepeat"></param>
        protected virtual void SetRepeat(uint aVersion, bool aaRepeat)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Repeat action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Repeat action for the owning device.
        ///
        /// Must be implemented iff EnableActionRepeat was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaRepeat"></param>
        protected virtual void Repeat(uint aVersion, out bool aaRepeat)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetShuffle action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetShuffle action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetShuffle was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaShuffle"></param>
        protected virtual void SetShuffle(uint aVersion, bool aaShuffle)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Shuffle action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Shuffle action for the owning device.
        ///
        /// Must be implemented iff EnableActionShuffle was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaShuffle"></param>
        protected virtual void Shuffle(uint aVersion, out bool aaShuffle)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTracksMax"></param>
        protected virtual void TracksMax(uint aVersion, out uint aaTracksMax)
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
        protected virtual void IdArray(uint aVersion, out uint aaIdArrayToken, out byte[] aaIdArray)
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

        private static int DoRead(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aId;
            string aUri;
            string aMetaData;
            try
            {
                invocation.ReadStart();
                aId = invocation.ReadUint("aId");
                invocation.ReadEnd();
                self.Read(aVersion, aId, out aUri, out aMetaData);
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
                invocation.WriteString("aUri", aUri);
                invocation.WriteString("aMetaData", aMetaData);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoReadList(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aIdList;
            string aMetaDataList;
            try
            {
                invocation.ReadStart();
                aIdList = invocation.ReadString("aIdList");
                invocation.ReadEnd();
                self.ReadList(aVersion, aIdList, out aMetaDataList);
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
                invocation.WriteString("aMetaDataList", aMetaDataList);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoInsert(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aAfterId;
            string aUri;
            string aMetaData;
            uint aNewId;
            try
            {
                invocation.ReadStart();
                aAfterId = invocation.ReadUint("aAfterId");
                aUri = invocation.ReadString("aUri");
                aMetaData = invocation.ReadString("aMetaData");
                invocation.ReadEnd();
                self.Insert(aVersion, aAfterId, aUri, aMetaData, out aNewId);
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
                invocation.WriteUint("aNewId", aNewId);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoDelete(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aId;
            try
            {
                invocation.ReadStart();
                aId = invocation.ReadUint("aId");
                invocation.ReadEnd();
                self.Delete(aVersion, aId);
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

        private static int DoDeleteAll(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.DeleteAll(aVersion);
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

        private static int DoSetRepeat(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aRepeat;
            try
            {
                invocation.ReadStart();
                aRepeat = invocation.ReadBool("aRepeat");
                invocation.ReadEnd();
                self.SetRepeat(aVersion, aRepeat);
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

        private static int DoRepeat(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aRepeat;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Repeat(aVersion, out aRepeat);
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
                invocation.WriteBool("aRepeat", aRepeat);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetShuffle(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aShuffle;
            try
            {
                invocation.ReadStart();
                aShuffle = invocation.ReadBool("aShuffle");
                invocation.ReadEnd();
                self.SetShuffle(aVersion, aShuffle);
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

        private static int DoShuffle(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aShuffle;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Shuffle(aVersion, out aShuffle);
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
                invocation.WriteBool("aShuffle", aShuffle);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoTracksMax(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aTracksMax;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.TracksMax(aVersion, out aTracksMax);
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
                invocation.WriteUint("aTracksMax", aTracksMax);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoIdArray(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aIdArrayToken;
            byte[] aIdArray;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.IdArray(aVersion, out aIdArrayToken, out aIdArray);
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
                invocation.WriteUint("aIdArrayToken", aIdArrayToken);
                invocation.WriteBinary("aIdArray", aIdArray);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoIdArrayChanged(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aIdArrayToken;
            bool aIdArrayChanged;
            try
            {
                invocation.ReadStart();
                aIdArrayToken = invocation.ReadUint("aIdArrayToken");
                invocation.ReadEnd();
                self.IdArrayChanged(aVersion, aIdArrayToken, out aIdArrayChanged);
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
                invocation.WriteBool("aIdArrayChanged", aIdArrayChanged);
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

        ~DvProviderLinnCoUkPlaylist1()
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

