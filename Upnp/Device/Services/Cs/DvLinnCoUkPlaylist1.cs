using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkPlaylist1 : IDisposable
    {
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern uint DvServiceLinnCoUkPlaylist1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe int DvServiceLinnCoUkPlaylist1SetPropertyIdArray(uint aHandle, char* aValue, int aValueLen);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe void DvServiceLinnCoUkPlaylist1GetPropertyIdArray(uint aHandle, char** aValue, int* aValueLen);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe int DvServiceLinnCoUkPlaylist1SetPropertyRepeat(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe void DvServiceLinnCoUkPlaylist1GetPropertyRepeat(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe int DvServiceLinnCoUkPlaylist1SetPropertyShuffle(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe void DvServiceLinnCoUkPlaylist1GetPropertyShuffle(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe int DvServiceLinnCoUkPlaylist1SetPropertyTracksMax(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern unsafe void DvServiceLinnCoUkPlaylist1GetPropertyTracksMax(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionRead(uint aHandle, CallbackRead aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionReadList(uint aHandle, CallbackReadList aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionInsert(uint aHandle, CallbackInsert aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionDelete(uint aHandle, CallbackDelete aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionDeleteAll(uint aHandle, CallbackDeleteAll aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionSetRepeat(uint aHandle, CallbackSetRepeat aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionRepeat(uint aHandle, CallbackRepeat aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionSetShuffle(uint aHandle, CallbackSetShuffle aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionShuffle(uint aHandle, CallbackShuffle aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionTracksMax(uint aHandle, CallbackTracksMax aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionIdArray(uint aHandle, CallbackIdArray aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPlaylist1")]
        static extern void DvServiceLinnCoUkPlaylist1EnableActionIdArrayChanged(uint aHandle, CallbackIdArrayChanged aCallback, IntPtr aPtr);
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

        private uint iHandle;
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

        public DvServiceLinnCoUkPlaylist1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkPlaylist1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyIdArray(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int valueLen = aValue.Length;
            int err = DvServiceLinnCoUkPlaylist1SetPropertyIdArray(iHandle, value, valueLen);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyIdArray(out string aValue)
        {
            char* value;
            int valueLen;
             DvServiceLinnCoUkPlaylist1GetPropertyIdArray(iHandle, &value, &valueLen);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value, valueLen);
            ZappFree(value);
        }

        public unsafe void SetPropertyRepeat(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkPlaylist1SetPropertyRepeat(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyRepeat(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkPlaylist1GetPropertyRepeat(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyShuffle(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkPlaylist1SetPropertyShuffle(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyShuffle(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkPlaylist1GetPropertyShuffle(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyTracksMax(uint aValue)
        {
            if (0 != DvServiceLinnCoUkPlaylist1SetPropertyTracksMax(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyTracksMax(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkPlaylist1GetPropertyTracksMax(iHandle, value);
            }
        }

        protected unsafe void EnableActionRead()
        {
            iCallbackRead = new CallbackRead(DoRead);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionRead(iHandle, iCallbackRead, ptr);
        }

        protected unsafe void EnableActionReadList()
        {
            iCallbackReadList = new CallbackReadList(DoReadList);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionReadList(iHandle, iCallbackReadList, ptr);
        }

        protected unsafe void EnableActionInsert()
        {
            iCallbackInsert = new CallbackInsert(DoInsert);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionInsert(iHandle, iCallbackInsert, ptr);
        }

        protected unsafe void EnableActionDelete()
        {
            iCallbackDelete = new CallbackDelete(DoDelete);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionDelete(iHandle, iCallbackDelete, ptr);
        }

        protected unsafe void EnableActionDeleteAll()
        {
            iCallbackDeleteAll = new CallbackDeleteAll(DoDeleteAll);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionDeleteAll(iHandle, iCallbackDeleteAll, ptr);
        }

        protected unsafe void EnableActionSetRepeat()
        {
            iCallbackSetRepeat = new CallbackSetRepeat(DoSetRepeat);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionSetRepeat(iHandle, iCallbackSetRepeat, ptr);
        }

        protected unsafe void EnableActionRepeat()
        {
            iCallbackRepeat = new CallbackRepeat(DoRepeat);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionRepeat(iHandle, iCallbackRepeat, ptr);
        }

        protected unsafe void EnableActionSetShuffle()
        {
            iCallbackSetShuffle = new CallbackSetShuffle(DoSetShuffle);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionSetShuffle(iHandle, iCallbackSetShuffle, ptr);
        }

        protected unsafe void EnableActionShuffle()
        {
            iCallbackShuffle = new CallbackShuffle(DoShuffle);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionShuffle(iHandle, iCallbackShuffle, ptr);
        }

        protected unsafe void EnableActionTracksMax()
        {
            iCallbackTracksMax = new CallbackTracksMax(DoTracksMax);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionTracksMax(iHandle, iCallbackTracksMax, ptr);
        }

        protected unsafe void EnableActionIdArray()
        {
            iCallbackIdArray = new CallbackIdArray(DoIdArray);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionIdArray(iHandle, iCallbackIdArray, ptr);
        }

        protected unsafe void EnableActionIdArrayChanged()
        {
            iCallbackIdArrayChanged = new CallbackIdArrayChanged(DoIdArrayChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPlaylist1EnableActionIdArrayChanged(iHandle, iCallbackIdArrayChanged, ptr);
        }

        protected virtual void Read(uint aVersion, uint aaId, out string aaUri, out string aaMetaData)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void ReadList(uint aVersion, string aaIdList, out string aaMetaDataList)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Insert(uint aVersion, uint aaAfterId, string aaUri, string aaMetaData, out uint aaNewId)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Delete(uint aVersion, uint aaId)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DeleteAll(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetRepeat(uint aVersion, bool aaRepeat)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Repeat(uint aVersion, out bool aaRepeat)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetShuffle(uint aVersion, bool aaShuffle)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Shuffle(uint aVersion, out bool aaShuffle)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void TracksMax(uint aVersion, out uint aaTracksMax)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void IdArray(uint aVersion, out uint aaIdArrayToken, out string aaIdArray)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void IdArrayChanged(uint aVersion, uint aaIdArrayToken, out bool aaIdArrayChanged)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoRead(IntPtr aPtr, uint aVersion, uint aaId, char** aaUri, char** aaMetaData)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
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
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
            string aIdList = Marshal.PtrToStringAnsi((IntPtr)aaIdList);
            string aMetaDataList;
            self.ReadList(aVersion, aIdList, out aMetaDataList);
            *aaMetaDataList = (char*)Marshal.StringToHGlobalAnsi(aMetaDataList).ToPointer();
            return 0;
        }

        private static unsafe int DoInsert(IntPtr aPtr, uint aVersion, uint aaAfterId, char* aaUri, char* aaMetaData, uint* aaNewId)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
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
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
            self.Delete(aVersion, aaId);
            return 0;
        }

        private static unsafe int DoDeleteAll(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
            self.DeleteAll(aVersion);
            return 0;
        }

        private static unsafe int DoSetRepeat(IntPtr aPtr, uint aVersion, int aaRepeat)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
            bool aRepeat = (aaRepeat != 0);
            self.SetRepeat(aVersion, aRepeat);
            return 0;
        }

        private static unsafe int DoRepeat(IntPtr aPtr, uint aVersion, int* aaRepeat)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
            bool aRepeat;
            self.Repeat(aVersion, out aRepeat);
            *aaRepeat = (aRepeat ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetShuffle(IntPtr aPtr, uint aVersion, int aaShuffle)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
            bool aShuffle = (aaShuffle != 0);
            self.SetShuffle(aVersion, aShuffle);
            return 0;
        }

        private static unsafe int DoShuffle(IntPtr aPtr, uint aVersion, int* aaShuffle)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
            bool aShuffle;
            self.Shuffle(aVersion, out aShuffle);
            *aaShuffle = (aShuffle ? 1 : 0);
            return 0;
        }

        private static unsafe int DoTracksMax(IntPtr aPtr, uint aVersion, uint* aaTracksMax)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
            uint aTracksMax;
            self.TracksMax(aVersion, out aTracksMax);
            *aaTracksMax = aTracksMax;
            return 0;
        }

        private static unsafe int DoIdArray(IntPtr aPtr, uint aVersion, uint* aaIdArrayToken, char** aaIdArray, int* aaIdArrayLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
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
            DvServiceLinnCoUkPlaylist1 self = (DvServiceLinnCoUkPlaylist1)gch.Target;
            bool aIdArrayChanged;
            self.IdArrayChanged(aVersion, aaIdArrayToken, out aIdArrayChanged);
            *aaIdArrayChanged = (aIdArrayChanged ? 1 : 0);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkPlaylist1()
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
            DvServiceLinnCoUkPlaylist1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

