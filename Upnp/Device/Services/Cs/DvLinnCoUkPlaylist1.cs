using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkPlaylist1 : IDisposable
    {

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
        void GetPropertyIdArray(out string aValue);

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
        void GetPropertyRepeat(out bool aValue);

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
        void GetPropertyShuffle(out bool aValue);

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
        void GetPropertyTracksMax(out uint aValue);
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Playlist:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkPlaylist1 : DvProvider, IDisposable, IDvProviderLinnCoUkPlaylist1
    {
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern IntPtr DvProviderLinnCoUkPlaylist1Create(IntPtr aDeviceHandle);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1Destroy(IntPtr aHandle);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe int DvProviderLinnCoUkPlaylist1SetPropertyIdArray(IntPtr aHandle, char* aValue, int aValueLen, uint* aChanged);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe void DvProviderLinnCoUkPlaylist1GetPropertyIdArray(IntPtr aHandle, char** aValue, int* aValueLen);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe int DvProviderLinnCoUkPlaylist1SetPropertyRepeat(IntPtr aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe void DvProviderLinnCoUkPlaylist1GetPropertyRepeat(IntPtr aHandle, int* aValue);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe int DvProviderLinnCoUkPlaylist1SetPropertyShuffle(IntPtr aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe void DvProviderLinnCoUkPlaylist1GetPropertyShuffle(IntPtr aHandle, int* aValue);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe int DvProviderLinnCoUkPlaylist1SetPropertyTracksMax(IntPtr aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe void DvProviderLinnCoUkPlaylist1GetPropertyTracksMax(IntPtr aHandle, uint* aValue);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionRead(IntPtr aHandle, CallbackRead aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionReadList(IntPtr aHandle, CallbackReadList aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionInsert(IntPtr aHandle, CallbackInsert aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionDelete(IntPtr aHandle, CallbackDelete aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionDeleteAll(IntPtr aHandle, CallbackDeleteAll aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionSetRepeat(IntPtr aHandle, CallbackSetRepeat aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionRepeat(IntPtr aHandle, CallbackRepeat aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionSetShuffle(IntPtr aHandle, CallbackSetShuffle aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionShuffle(IntPtr aHandle, CallbackShuffle aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionTracksMax(IntPtr aHandle, CallbackTracksMax aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionIdArray(IntPtr aHandle, CallbackIdArray aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvProviderLinnCoUkPlaylist1EnableActionIdArrayChanged(IntPtr aHandle, CallbackIdArrayChanged aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackRead(IntPtr aPtr, uint aVersion, uint aaId, char** aaUri, char** aaMetaData);
        private unsafe delegate int CallbackReadList(IntPtr aPtr, uint aVersion, char* aaIdList, char** aaMetaDataList);
        private unsafe delegate int CallbackInsert(IntPtr aPtr, uint aVersion, uint aaAfterId, char* aaUri, char* aaMetaData, uint* aaNewId);
        private unsafe delegate int CallbackDelete(IntPtr aPtr, uint aVersion, uint aaId);
        private unsafe delegate int CallbackDeleteAll(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackSetRepeat(IntPtr aPtr, uint aVersion, int aaRepeat);
        private unsafe delegate int CallbackRepeat(IntPtr aPtr, uint aVersion, int* aaRepeat);
        private unsafe delegate int CallbackSetShuffle(IntPtr aPtr, uint aVersion, int aaShuffle);
        private unsafe delegate int CallbackShuffle(IntPtr aPtr, uint aVersion, int* aaShuffle);
        private unsafe delegate int CallbackTracksMax(IntPtr aPtr, uint aVersion, uint* aaTracksMax);
        private unsafe delegate int CallbackIdArray(IntPtr aPtr, uint aVersion, uint* aaIdArrayToken, char** aaIdArray, int* aaIdArrayLen);
        private unsafe delegate int CallbackIdArrayChanged(IntPtr aPtr, uint aVersion, uint aaIdArrayToken, int* aaIdArrayChanged);

        private GCHandle iGch;
        private CallbackRead iCallbackRead;
        private CallbackReadList iCallbackReadList;
        private CallbackInsert iCallbackInsert;
        private CallbackDelete iCallbackDelete;
        private CallbackDeleteAll iCallbackDeleteAll;
        private CallbackSetRepeat iCallbackSetRepeat;
        private CallbackRepeat iCallbackRepeat;
        private CallbackSetShuffle iCallbackSetShuffle;
        private CallbackShuffle iCallbackShuffle;
        private CallbackTracksMax iCallbackTracksMax;
        private CallbackIdArray iCallbackIdArray;
        private CallbackIdArrayChanged iCallbackIdArrayChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkPlaylist1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkPlaylist1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the IdArray property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyIdArray(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int valueLen = aValue.Length;
            int err = DvProviderLinnCoUkPlaylist1SetPropertyIdArray(iHandle, value, valueLen, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the IdArray property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyIdArray(out string aValue)
        {
            char* value;
            int valueLen;
             DvProviderLinnCoUkPlaylist1GetPropertyIdArray(iHandle, &value, &valueLen);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value, valueLen);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the Repeat property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyRepeat(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkPlaylist1SetPropertyRepeat(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Repeat property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyRepeat(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkPlaylist1GetPropertyRepeat(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the Shuffle property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyShuffle(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkPlaylist1SetPropertyShuffle(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Shuffle property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyShuffle(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkPlaylist1GetPropertyShuffle(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the TracksMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTracksMax(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkPlaylist1SetPropertyTracksMax(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TracksMax property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTracksMax(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkPlaylist1GetPropertyTracksMax(iHandle, value);
            }
        }

        /// <summary>
        /// Signal that the action Read is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoRead must be overridden if this is called.</remarks>
        protected unsafe void EnableActionRead()
        {
            iCallbackRead = new CallbackRead(DoRead);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionRead(iHandle, iCallbackRead, ptr);
        }

        /// <summary>
        /// Signal that the action ReadList is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoReadList must be overridden if this is called.</remarks>
        protected unsafe void EnableActionReadList()
        {
            iCallbackReadList = new CallbackReadList(DoReadList);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionReadList(iHandle, iCallbackReadList, ptr);
        }

        /// <summary>
        /// Signal that the action Insert is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoInsert must be overridden if this is called.</remarks>
        protected unsafe void EnableActionInsert()
        {
            iCallbackInsert = new CallbackInsert(DoInsert);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionInsert(iHandle, iCallbackInsert, ptr);
        }

        /// <summary>
        /// Signal that the action Delete is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDelete must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDelete()
        {
            iCallbackDelete = new CallbackDelete(DoDelete);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionDelete(iHandle, iCallbackDelete, ptr);
        }

        /// <summary>
        /// Signal that the action DeleteAll is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDeleteAll must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDeleteAll()
        {
            iCallbackDeleteAll = new CallbackDeleteAll(DoDeleteAll);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionDeleteAll(iHandle, iCallbackDeleteAll, ptr);
        }

        /// <summary>
        /// Signal that the action SetRepeat is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetRepeat must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetRepeat()
        {
            iCallbackSetRepeat = new CallbackSetRepeat(DoSetRepeat);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionSetRepeat(iHandle, iCallbackSetRepeat, ptr);
        }

        /// <summary>
        /// Signal that the action Repeat is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoRepeat must be overridden if this is called.</remarks>
        protected unsafe void EnableActionRepeat()
        {
            iCallbackRepeat = new CallbackRepeat(DoRepeat);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionRepeat(iHandle, iCallbackRepeat, ptr);
        }

        /// <summary>
        /// Signal that the action SetShuffle is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetShuffle must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetShuffle()
        {
            iCallbackSetShuffle = new CallbackSetShuffle(DoSetShuffle);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionSetShuffle(iHandle, iCallbackSetShuffle, ptr);
        }

        /// <summary>
        /// Signal that the action Shuffle is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoShuffle must be overridden if this is called.</remarks>
        protected unsafe void EnableActionShuffle()
        {
            iCallbackShuffle = new CallbackShuffle(DoShuffle);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionShuffle(iHandle, iCallbackShuffle, ptr);
        }

        /// <summary>
        /// Signal that the action TracksMax is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoTracksMax must be overridden if this is called.</remarks>
        protected unsafe void EnableActionTracksMax()
        {
            iCallbackTracksMax = new CallbackTracksMax(DoTracksMax);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionTracksMax(iHandle, iCallbackTracksMax, ptr);
        }

        /// <summary>
        /// Signal that the action IdArray is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoIdArray must be overridden if this is called.</remarks>
        protected unsafe void EnableActionIdArray()
        {
            iCallbackIdArray = new CallbackIdArray(DoIdArray);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionIdArray(iHandle, iCallbackIdArray, ptr);
        }

        /// <summary>
        /// Signal that the action IdArrayChanged is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoIdArrayChanged must be overridden if this is called.</remarks>
        protected unsafe void EnableActionIdArrayChanged()
        {
            iCallbackIdArrayChanged = new CallbackIdArrayChanged(DoIdArrayChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPlaylist1EnableActionIdArrayChanged(iHandle, iCallbackIdArrayChanged, ptr);
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

        private static unsafe int DoRead(IntPtr aPtr, uint aVersion, uint aaId, char** aaUri, char** aaMetaData)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            string aUri;
            string aMetaData;
            self.Read(aVersion, aaId, out aUri, out aMetaData);
            *aaUri = (char*)Marshal.StringToHGlobalAnsi(aUri).ToPointer();
            *aaMetaData = (char*)Marshal.StringToHGlobalAnsi(aMetaData).ToPointer();
            return 0;
        }

        private static unsafe int DoReadList(IntPtr aPtr, uint aVersion, char* aaIdList, char** aaMetaDataList)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            string aIdList = Marshal.PtrToStringAnsi((IntPtr)aaIdList);
            string aMetaDataList;
            self.ReadList(aVersion, aIdList, out aMetaDataList);
            *aaMetaDataList = (char*)Marshal.StringToHGlobalAnsi(aMetaDataList).ToPointer();
            return 0;
        }

        private static unsafe int DoInsert(IntPtr aPtr, uint aVersion, uint aaAfterId, char* aaUri, char* aaMetaData, uint* aaNewId)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            string aUri = Marshal.PtrToStringAnsi((IntPtr)aaUri);
            string aMetaData = Marshal.PtrToStringAnsi((IntPtr)aaMetaData);
            uint aNewId;
            self.Insert(aVersion, aaAfterId, aUri, aMetaData, out aNewId);
            *aaNewId = aNewId;
            return 0;
        }

        private static unsafe int DoDelete(IntPtr aPtr, uint aVersion, uint aaId)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            self.Delete(aVersion, aaId);
            return 0;
        }

        private static unsafe int DoDeleteAll(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            self.DeleteAll(aVersion);
            return 0;
        }

        private static unsafe int DoSetRepeat(IntPtr aPtr, uint aVersion, int aaRepeat)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            bool aRepeat = (aaRepeat != 0);
            self.SetRepeat(aVersion, aRepeat);
            return 0;
        }

        private static unsafe int DoRepeat(IntPtr aPtr, uint aVersion, int* aaRepeat)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            bool aRepeat;
            self.Repeat(aVersion, out aRepeat);
            *aaRepeat = (aRepeat ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetShuffle(IntPtr aPtr, uint aVersion, int aaShuffle)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            bool aShuffle = (aaShuffle != 0);
            self.SetShuffle(aVersion, aShuffle);
            return 0;
        }

        private static unsafe int DoShuffle(IntPtr aPtr, uint aVersion, int* aaShuffle)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            bool aShuffle;
            self.Shuffle(aVersion, out aShuffle);
            *aaShuffle = (aShuffle ? 1 : 0);
            return 0;
        }

        private static unsafe int DoTracksMax(IntPtr aPtr, uint aVersion, uint* aaTracksMax)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            uint aTracksMax;
            self.TracksMax(aVersion, out aTracksMax);
            *aaTracksMax = aTracksMax;
            return 0;
        }

        private static unsafe int DoIdArray(IntPtr aPtr, uint aVersion, uint* aaIdArrayToken, char** aaIdArray, int* aaIdArrayLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            uint aIdArrayToken;
            string aIdArray;
            self.IdArray(aVersion, out aIdArrayToken, out aIdArray);
            *aaIdArrayToken = aIdArrayToken;
            *aaIdArray = (char*)Marshal.StringToHGlobalAnsi(aIdArray).ToPointer();
            *aaIdArrayLen = aIdArray.Length;
            return 0;
        }

        private static unsafe int DoIdArrayChanged(IntPtr aPtr, uint aVersion, uint aaIdArrayToken, int* aaIdArrayChanged)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPlaylist1 self = (DvProviderLinnCoUkPlaylist1)gch.Target;
            bool aIdArrayChanged;
            self.IdArrayChanged(aVersion, aaIdArrayToken, out aIdArrayChanged);
            *aaIdArrayChanged = (aIdArrayChanged ? 1 : 0);
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
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
            }
            DvProviderLinnCoUkPlaylist1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

