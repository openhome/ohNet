using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkPlaylist1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern uint CpProxyLinnCoUkPlaylist1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern void CpProxyLinnCoUkPlaylist1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncRead(uint aHandle, uint aaId, char** aaUri, char** aaMetaData);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginRead(uint aHandle, uint aaId, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndRead(uint aHandle, uint aAsync, char** aaUri, char** aaMetaData);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncReadList(uint aHandle, char* aaIdList, char** aaMetaDataList);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginReadList(uint aHandle, char* aaIdList, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndReadList(uint aHandle, uint aAsync, char** aaMetaDataList);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncInsert(uint aHandle, uint aaAfterId, char* aaUri, char* aaMetaData, uint* aaNewId);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginInsert(uint aHandle, uint aaAfterId, char* aaUri, char* aaMetaData, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndInsert(uint aHandle, uint aAsync, uint* aaNewId);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncDelete(uint aHandle, uint aaId);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginDelete(uint aHandle, uint aaId, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndDelete(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncDeleteAll(uint aHandle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginDeleteAll(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndDeleteAll(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncSetRepeat(uint aHandle, uint aaRepeat);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginSetRepeat(uint aHandle, uint aaRepeat, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndSetRepeat(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncRepeat(uint aHandle, uint* aaRepeat);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginRepeat(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndRepeat(uint aHandle, uint aAsync, uint* aaRepeat);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncSetShuffle(uint aHandle, uint aaShuffle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginSetShuffle(uint aHandle, uint aaShuffle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndSetShuffle(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncShuffle(uint aHandle, uint* aaShuffle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginShuffle(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndShuffle(uint aHandle, uint aAsync, uint* aaShuffle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncTracksMax(uint aHandle, uint* aaTracksMax);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginTracksMax(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndTracksMax(uint aHandle, uint aAsync, uint* aaTracksMax);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncIdArray(uint aHandle, uint* aaIdArrayToken, char** aaIdArray, uint* aaIdArrayLen);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginIdArray(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndIdArray(uint aHandle, uint aAsync, uint* aaIdArrayToken, char** aaIdArray, uint* aaIdArrayLen);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncIdArrayChanged(uint aHandle, uint aaIdArrayToken, uint* aaIdArrayChanged);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginIdArrayChanged(uint aHandle, uint aaIdArrayToken, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndIdArrayChanged(uint aHandle, uint aAsync, uint* aaIdArrayChanged);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern void CpProxyLinnCoUkPlaylist1SetPropertyIdArrayChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern void CpProxyLinnCoUkPlaylist1SetPropertyRepeatChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern void CpProxyLinnCoUkPlaylist1SetPropertyShuffleChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern void CpProxyLinnCoUkPlaylist1SetPropertyTracksMaxChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1PropertyIdArray(uint aHandle, char** aIdArray, uint* aLen);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1PropertyRepeat(uint aHandle, uint* aRepeat);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1PropertyShuffle(uint aHandle, uint* aShuffle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1PropertyTracksMax(uint aHandle, uint* aTracksMax);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iIdArrayChanged;
        private CallbackPropertyChanged iRepeatChanged;
        private CallbackPropertyChanged iShuffleChanged;
        private CallbackPropertyChanged iTracksMaxChanged;
        private Callback iCallbackIdArrayChanged;
        private Callback iCallbackRepeatChanged;
        private Callback iCallbackShuffleChanged;
        private Callback iCallbackTracksMaxChanged;

        public CpProxyLinnCoUkPlaylist1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkPlaylist1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncRead(uint aaId, out string aaUri, out string aaMetaData)
        {
			char* aUri;
			char* aMetaData;
			{
				CpProxyLinnCoUkPlaylist1SyncRead(iHandle, aaId, &aUri, &aMetaData);
			}
            aaUri = Marshal.PtrToStringAnsi((IntPtr)aUri);
            ZappFree(aUri);
            aaMetaData = Marshal.PtrToStringAnsi((IntPtr)aMetaData);
            ZappFree(aMetaData);
        }

        public unsafe void BeginRead(uint aaId, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginRead(iHandle, aaId, iActionComplete, ptr);
        }

        public unsafe void EndRead(uint aAsyncHandle, out string aaUri, out string aaMetaData)
        {
			char* aUri;
			char* aMetaData;
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndRead(iHandle, aAsyncHandle, &aUri, &aMetaData))
				{
					throw(new ProxyError());
				}
			}
            aaUri = Marshal.PtrToStringAnsi((IntPtr)aUri);
            ZappFree(aUri);
            aaMetaData = Marshal.PtrToStringAnsi((IntPtr)aMetaData);
            ZappFree(aMetaData);
        }

        public unsafe void SyncReadList(string aaIdList, out string aaMetaDataList)
        {
			char* aIdList = (char*)Marshal.StringToHGlobalAnsi(aaIdList);
			char* aMetaDataList;
			{
				CpProxyLinnCoUkPlaylist1SyncReadList(iHandle, aIdList, &aMetaDataList);
			}
			Marshal.FreeHGlobal((IntPtr)aIdList);
            aaMetaDataList = Marshal.PtrToStringAnsi((IntPtr)aMetaDataList);
            ZappFree(aMetaDataList);
        }

        public unsafe void BeginReadList(string aaIdList, CallbackAsyncComplete aCallback)
        {
			char* aIdList = (char*)Marshal.StringToHGlobalAnsi(aaIdList);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginReadList(iHandle, aIdList, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aIdList);
        }

        public unsafe void EndReadList(uint aAsyncHandle, out string aaMetaDataList)
        {
			char* aMetaDataList;
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndReadList(iHandle, aAsyncHandle, &aMetaDataList))
				{
					throw(new ProxyError());
				}
			}
            aaMetaDataList = Marshal.PtrToStringAnsi((IntPtr)aMetaDataList);
            ZappFree(aMetaDataList);
        }

        public unsafe void SyncInsert(uint aaAfterId, string aaUri, string aaMetaData, out uint aaNewId)
        {
			char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
			char* aMetaData = (char*)Marshal.StringToHGlobalAnsi(aaMetaData);
			fixed (uint* aNewId = &aaNewId)
			{
				CpProxyLinnCoUkPlaylist1SyncInsert(iHandle, aaAfterId, aUri, aMetaData, aNewId);
			}
			Marshal.FreeHGlobal((IntPtr)aUri);
			Marshal.FreeHGlobal((IntPtr)aMetaData);
        }

        public unsafe void BeginInsert(uint aaAfterId, string aaUri, string aaMetaData, CallbackAsyncComplete aCallback)
        {
			char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
			char* aMetaData = (char*)Marshal.StringToHGlobalAnsi(aaMetaData);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginInsert(iHandle, aaAfterId, aUri, aMetaData, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aUri);
			Marshal.FreeHGlobal((IntPtr)aMetaData);
        }

        public unsafe void EndInsert(uint aAsyncHandle, out uint aaNewId)
        {
			fixed (uint* aNewId = &aaNewId)
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndInsert(iHandle, aAsyncHandle, aNewId))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDelete(uint aaId)
        {
			{
				CpProxyLinnCoUkPlaylist1SyncDelete(iHandle, aaId);
			}
        }

        public unsafe void BeginDelete(uint aaId, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginDelete(iHandle, aaId, iActionComplete, ptr);
        }

        public unsafe void EndDelete(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndDelete(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDeleteAll()
        {
			{
				CpProxyLinnCoUkPlaylist1SyncDeleteAll(iHandle);
			}
        }

        public unsafe void BeginDeleteAll(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginDeleteAll(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDeleteAll(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndDeleteAll(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetRepeat(bool aaRepeat)
        {
			uint aRepeat = (aaRepeat? 1u : 0u);
			{
				CpProxyLinnCoUkPlaylist1SyncSetRepeat(iHandle, aRepeat);
			}
        }

        public unsafe void BeginSetRepeat(bool aaRepeat, CallbackAsyncComplete aCallback)
        {
			uint aRepeat = (aaRepeat? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginSetRepeat(iHandle, aRepeat, iActionComplete, ptr);
        }

        public unsafe void EndSetRepeat(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndSetRepeat(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncRepeat(out bool aaRepeat)
        {
			uint aRepeat;
			{
				CpProxyLinnCoUkPlaylist1SyncRepeat(iHandle, &aRepeat);
			}
			aaRepeat = (aRepeat != 0);
        }

        public unsafe void BeginRepeat(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginRepeat(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndRepeat(uint aAsyncHandle, out bool aaRepeat)
        {
			uint aRepeat;
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndRepeat(iHandle, aAsyncHandle, &aRepeat))
				{
					throw(new ProxyError());
				}
			}
			aaRepeat = (aRepeat != 0);
        }

        public unsafe void SyncSetShuffle(bool aaShuffle)
        {
			uint aShuffle = (aaShuffle? 1u : 0u);
			{
				CpProxyLinnCoUkPlaylist1SyncSetShuffle(iHandle, aShuffle);
			}
        }

        public unsafe void BeginSetShuffle(bool aaShuffle, CallbackAsyncComplete aCallback)
        {
			uint aShuffle = (aaShuffle? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginSetShuffle(iHandle, aShuffle, iActionComplete, ptr);
        }

        public unsafe void EndSetShuffle(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndSetShuffle(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncShuffle(out bool aaShuffle)
        {
			uint aShuffle;
			{
				CpProxyLinnCoUkPlaylist1SyncShuffle(iHandle, &aShuffle);
			}
			aaShuffle = (aShuffle != 0);
        }

        public unsafe void BeginShuffle(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginShuffle(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndShuffle(uint aAsyncHandle, out bool aaShuffle)
        {
			uint aShuffle;
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndShuffle(iHandle, aAsyncHandle, &aShuffle))
				{
					throw(new ProxyError());
				}
			}
			aaShuffle = (aShuffle != 0);
        }

        public unsafe void SyncTracksMax(out uint aaTracksMax)
        {
			fixed (uint* aTracksMax = &aaTracksMax)
			{
				CpProxyLinnCoUkPlaylist1SyncTracksMax(iHandle, aTracksMax);
			}
        }

        public unsafe void BeginTracksMax(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginTracksMax(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndTracksMax(uint aAsyncHandle, out uint aaTracksMax)
        {
			fixed (uint* aTracksMax = &aaTracksMax)
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndTracksMax(iHandle, aAsyncHandle, aTracksMax))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncIdArray(out uint aaIdArrayToken, out string aaIdArray)
        {
			char* aIdArray;
			uint aIdArrayLen;
			fixed (uint* aIdArrayToken = &aaIdArrayToken)
			{
				CpProxyLinnCoUkPlaylist1SyncIdArray(iHandle, aIdArrayToken, &aIdArray, &aIdArrayLen);
			}
            aaIdArray = Marshal.PtrToStringAnsi((IntPtr)aIdArray, (int)aIdArrayLen);
            ZappFree(aIdArray);
        }

        public unsafe void BeginIdArray(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginIdArray(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndIdArray(uint aAsyncHandle, out uint aaIdArrayToken, out string aaIdArray)
        {
			char* aIdArray;
			uint aIdArrayLen;
			fixed (uint* aIdArrayToken = &aaIdArrayToken)
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndIdArray(iHandle, aAsyncHandle, aIdArrayToken, &aIdArray, &aIdArrayLen))
				{
					throw(new ProxyError());
				}
			}
            aaIdArray = Marshal.PtrToStringAnsi((IntPtr)aIdArray, (int)aIdArrayLen);
            ZappFree(aIdArray);
        }

        public unsafe void SyncIdArrayChanged(uint aaIdArrayToken, out bool aaIdArrayChanged)
        {
			uint aIdArrayChanged;
			{
				CpProxyLinnCoUkPlaylist1SyncIdArrayChanged(iHandle, aaIdArrayToken, &aIdArrayChanged);
			}
			aaIdArrayChanged = (aIdArrayChanged != 0);
        }

        public unsafe void BeginIdArrayChanged(uint aaIdArrayToken, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginIdArrayChanged(iHandle, aaIdArrayToken, iActionComplete, ptr);
        }

        public unsafe void EndIdArrayChanged(uint aAsyncHandle, out bool aaIdArrayChanged)
        {
			uint aIdArrayChanged;
			{
				if (0 != CpProxyLinnCoUkPlaylist1EndIdArrayChanged(iHandle, aAsyncHandle, &aIdArrayChanged))
				{
					throw(new ProxyError());
				}
			}
			aaIdArrayChanged = (aIdArrayChanged != 0);
        }

        public void SetPropertyIdArrayChanged(CallbackPropertyChanged aIdArrayChanged)
        {
            iIdArrayChanged = aIdArrayChanged;
            iCallbackIdArrayChanged = new Callback(PropertyIdArrayChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkPlaylist1SetPropertyIdArrayChanged(iHandle, iCallbackIdArrayChanged, ptr);
        }

        private void PropertyIdArrayChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkPlaylist1 self = (CpProxyLinnCoUkPlaylist1)gch.Target;
            self.iIdArrayChanged();
        }

        public void SetPropertyRepeatChanged(CallbackPropertyChanged aRepeatChanged)
        {
            iRepeatChanged = aRepeatChanged;
            iCallbackRepeatChanged = new Callback(PropertyRepeatChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkPlaylist1SetPropertyRepeatChanged(iHandle, iCallbackRepeatChanged, ptr);
        }

        private void PropertyRepeatChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkPlaylist1 self = (CpProxyLinnCoUkPlaylist1)gch.Target;
            self.iRepeatChanged();
        }

        public void SetPropertyShuffleChanged(CallbackPropertyChanged aShuffleChanged)
        {
            iShuffleChanged = aShuffleChanged;
            iCallbackShuffleChanged = new Callback(PropertyShuffleChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkPlaylist1SetPropertyShuffleChanged(iHandle, iCallbackShuffleChanged, ptr);
        }

        private void PropertyShuffleChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkPlaylist1 self = (CpProxyLinnCoUkPlaylist1)gch.Target;
            self.iShuffleChanged();
        }

        public void SetPropertyTracksMaxChanged(CallbackPropertyChanged aTracksMaxChanged)
        {
            iTracksMaxChanged = aTracksMaxChanged;
            iCallbackTracksMaxChanged = new Callback(PropertyTracksMaxChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkPlaylist1SetPropertyTracksMaxChanged(iHandle, iCallbackTracksMaxChanged, ptr);
        }

        private void PropertyTracksMaxChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkPlaylist1 self = (CpProxyLinnCoUkPlaylist1)gch.Target;
            self.iTracksMaxChanged();
        }

        public unsafe void PropertyIdArray(out string aIdArray)
        {
			char* ptr;
			uint len;
	        CpProxyLinnCoUkPlaylist1PropertyIdArray(iHandle, &ptr, &len);
            aIdArray = Marshal.PtrToStringAnsi((IntPtr)ptr, (int)len);
            ZappFree(ptr);
        }

        public unsafe void PropertyRepeat(out bool aRepeat)
        {
			uint repeat;
	        CpProxyLinnCoUkPlaylist1PropertyRepeat(iHandle, &repeat);
			aRepeat = (repeat != 0);
        }

        public unsafe void PropertyShuffle(out bool aShuffle)
        {
			uint shuffle;
	        CpProxyLinnCoUkPlaylist1PropertyShuffle(iHandle, &shuffle);
			aShuffle = (shuffle != 0);
        }

        public unsafe void PropertyTracksMax(out uint aTracksMax)
        {
			fixed (uint* tracksMax = &aTracksMax)
			{
	            CpProxyLinnCoUkPlaylist1PropertyTracksMax(iHandle, tracksMax);
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkPlaylist1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
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
            CpProxyLinnCoUkPlaylist1Destroy(handle);
            iGch.Free();
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
            else
            {
                DisposeProxy();
            }
        }
    }
}

