using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkPlaylist1 : ICpProxy, IDisposable
    {
        void SyncRead(uint aaId, out string aaUri, out string aaMetaData);
        void BeginRead(uint aaId, CpProxy.CallbackAsyncComplete aCallback);
        void EndRead(IntPtr aAsyncHandle, out string aaUri, out string aaMetaData);
        void SyncReadList(string aaIdList, out string aaMetaDataList);
        void BeginReadList(string aaIdList, CpProxy.CallbackAsyncComplete aCallback);
        void EndReadList(IntPtr aAsyncHandle, out string aaMetaDataList);
        void SyncInsert(uint aaAfterId, string aaUri, string aaMetaData, out uint aaNewId);
        void BeginInsert(uint aaAfterId, string aaUri, string aaMetaData, CpProxy.CallbackAsyncComplete aCallback);
        void EndInsert(IntPtr aAsyncHandle, out uint aaNewId);
        void SyncDelete(uint aaId);
        void BeginDelete(uint aaId, CpProxy.CallbackAsyncComplete aCallback);
        void EndDelete(IntPtr aAsyncHandle);
        void SyncDeleteAll();
        void BeginDeleteAll(CpProxy.CallbackAsyncComplete aCallback);
        void EndDeleteAll(IntPtr aAsyncHandle);
        void SyncSetRepeat(bool aaRepeat);
        void BeginSetRepeat(bool aaRepeat, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRepeat(IntPtr aAsyncHandle);
        void SyncRepeat(out bool aaRepeat);
        void BeginRepeat(CpProxy.CallbackAsyncComplete aCallback);
        void EndRepeat(IntPtr aAsyncHandle, out bool aaRepeat);
        void SyncSetShuffle(bool aaShuffle);
        void BeginSetShuffle(bool aaShuffle, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetShuffle(IntPtr aAsyncHandle);
        void SyncShuffle(out bool aaShuffle);
        void BeginShuffle(CpProxy.CallbackAsyncComplete aCallback);
        void EndShuffle(IntPtr aAsyncHandle, out bool aaShuffle);
        void SyncTracksMax(out uint aaTracksMax);
        void BeginTracksMax(CpProxy.CallbackAsyncComplete aCallback);
        void EndTracksMax(IntPtr aAsyncHandle, out uint aaTracksMax);
        void SyncIdArray(out uint aaIdArrayToken, out string aaIdArray);
        void BeginIdArray(CpProxy.CallbackAsyncComplete aCallback);
        void EndIdArray(IntPtr aAsyncHandle, out uint aaIdArrayToken, out string aaIdArray);
        void SyncIdArrayChanged(uint aaIdArrayToken, out bool aaIdArrayChanged);
        void BeginIdArrayChanged(uint aaIdArrayToken, CpProxy.CallbackAsyncComplete aCallback);
        void EndIdArrayChanged(IntPtr aAsyncHandle, out bool aaIdArrayChanged);

        void SetPropertyIdArrayChanged(CpProxy.CallbackPropertyChanged aIdArrayChanged);
        void PropertyIdArray(out string aIdArray);
        void SetPropertyRepeatChanged(CpProxy.CallbackPropertyChanged aRepeatChanged);
        void PropertyRepeat(out bool aRepeat);
        void SetPropertyShuffleChanged(CpProxy.CallbackPropertyChanged aShuffleChanged);
        void PropertyShuffle(out bool aShuffle);
        void SetPropertyTracksMaxChanged(CpProxy.CallbackPropertyChanged aTracksMaxChanged);
        void PropertyTracksMax(out uint aTracksMax);
    }

    /// <summary>
    /// Proxy for the linn.co.uk:Playlist:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkPlaylist1 : CpProxy, IDisposable, ICpProxyLinnCoUkPlaylist1
    {
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern IntPtr CpProxyLinnCoUkPlaylist1Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern void CpProxyLinnCoUkPlaylist1Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncRead(IntPtr aHandle, uint aaId, char** aaUri, char** aaMetaData);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginRead(IntPtr aHandle, uint aaId, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndRead(IntPtr aHandle, IntPtr aAsync, char** aaUri, char** aaMetaData);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncReadList(IntPtr aHandle, char* aaIdList, char** aaMetaDataList);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginReadList(IntPtr aHandle, char* aaIdList, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndReadList(IntPtr aHandle, IntPtr aAsync, char** aaMetaDataList);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncInsert(IntPtr aHandle, uint aaAfterId, char* aaUri, char* aaMetaData, uint* aaNewId);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginInsert(IntPtr aHandle, uint aaAfterId, char* aaUri, char* aaMetaData, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndInsert(IntPtr aHandle, IntPtr aAsync, uint* aaNewId);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncDelete(IntPtr aHandle, uint aaId);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginDelete(IntPtr aHandle, uint aaId, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndDelete(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncDeleteAll(IntPtr aHandle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginDeleteAll(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndDeleteAll(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncSetRepeat(IntPtr aHandle, uint aaRepeat);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginSetRepeat(IntPtr aHandle, uint aaRepeat, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndSetRepeat(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncRepeat(IntPtr aHandle, uint* aaRepeat);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginRepeat(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndRepeat(IntPtr aHandle, IntPtr aAsync, uint* aaRepeat);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncSetShuffle(IntPtr aHandle, uint aaShuffle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginSetShuffle(IntPtr aHandle, uint aaShuffle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndSetShuffle(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncShuffle(IntPtr aHandle, uint* aaShuffle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginShuffle(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndShuffle(IntPtr aHandle, IntPtr aAsync, uint* aaShuffle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncTracksMax(IntPtr aHandle, uint* aaTracksMax);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginTracksMax(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndTracksMax(IntPtr aHandle, IntPtr aAsync, uint* aaTracksMax);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncIdArray(IntPtr aHandle, uint* aaIdArrayToken, char** aaIdArray, uint* aaIdArrayLen);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginIdArray(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndIdArray(IntPtr aHandle, IntPtr aAsync, uint* aaIdArrayToken, char** aaIdArray, uint* aaIdArrayLen);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1SyncIdArrayChanged(IntPtr aHandle, uint aaIdArrayToken, uint* aaIdArrayChanged);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1BeginIdArrayChanged(IntPtr aHandle, uint aaIdArrayToken, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe int CpProxyLinnCoUkPlaylist1EndIdArrayChanged(IntPtr aHandle, IntPtr aAsync, uint* aaIdArrayChanged);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern void CpProxyLinnCoUkPlaylist1SetPropertyIdArrayChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern void CpProxyLinnCoUkPlaylist1SetPropertyRepeatChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern void CpProxyLinnCoUkPlaylist1SetPropertyShuffleChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern void CpProxyLinnCoUkPlaylist1SetPropertyTracksMaxChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1PropertyIdArray(IntPtr aHandle, char** aIdArray, uint* aLen);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1PropertyRepeat(IntPtr aHandle, uint* aRepeat);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1PropertyShuffle(IntPtr aHandle, uint* aShuffle);
        [DllImport("CpLinnCoUkPlaylist1")]
        static extern unsafe void CpProxyLinnCoUkPlaylist1PropertyTracksMax(IntPtr aHandle, uint* aTracksMax);
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkPlaylist1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkPlaylist1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaId"></param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetaData"></param>
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

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRead().</remarks>
        /// <param name="aaId"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginRead(uint aaId, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginRead(iHandle, aaId, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetaData"></param>
        public unsafe void EndRead(IntPtr aAsyncHandle, out string aaUri, out string aaMetaData)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdList"></param>
        /// <param name="aaMetaDataList"></param>
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

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndReadList().</remarks>
        /// <param name="aaIdList"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginReadList(string aaIdList, CallbackAsyncComplete aCallback)
        {
            char* aIdList = (char*)Marshal.StringToHGlobalAnsi(aaIdList);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginReadList(iHandle, aIdList, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aIdList);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMetaDataList"></param>
        public unsafe void EndReadList(IntPtr aAsyncHandle, out string aaMetaDataList)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaAfterId"></param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetaData"></param>
        /// <param name="aaNewId"></param>
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

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndInsert().</remarks>
        /// <param name="aaAfterId"></param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetaData"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
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

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaNewId"></param>
        public unsafe void EndInsert(IntPtr aAsyncHandle, out uint aaNewId)
        {
            fixed (uint* aNewId = &aaNewId)
            {
                if (0 != CpProxyLinnCoUkPlaylist1EndInsert(iHandle, aAsyncHandle, aNewId))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaId"></param>
        public unsafe void SyncDelete(uint aaId)
        {
            {
                CpProxyLinnCoUkPlaylist1SyncDelete(iHandle, aaId);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDelete().</remarks>
        /// <param name="aaId"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDelete(uint aaId, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginDelete(iHandle, aaId, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndDelete(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkPlaylist1EndDelete(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncDeleteAll()
        {
            {
                CpProxyLinnCoUkPlaylist1SyncDeleteAll(iHandle);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDeleteAll().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDeleteAll(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginDeleteAll(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndDeleteAll(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkPlaylist1EndDeleteAll(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRepeat"></param>
        public unsafe void SyncSetRepeat(bool aaRepeat)
        {
            uint aRepeat = (aaRepeat? 1u : 0u);
            {
                CpProxyLinnCoUkPlaylist1SyncSetRepeat(iHandle, aRepeat);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetRepeat().</remarks>
        /// <param name="aaRepeat"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetRepeat(bool aaRepeat, CallbackAsyncComplete aCallback)
        {
            uint aRepeat = (aaRepeat? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginSetRepeat(iHandle, aRepeat, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetRepeat(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkPlaylist1EndSetRepeat(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRepeat"></param>
        public unsafe void SyncRepeat(out bool aaRepeat)
        {
            uint aRepeat;
            {
                CpProxyLinnCoUkPlaylist1SyncRepeat(iHandle, &aRepeat);
            }
            aaRepeat = (aRepeat != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRepeat().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginRepeat(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginRepeat(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaRepeat"></param>
        public unsafe void EndRepeat(IntPtr aAsyncHandle, out bool aaRepeat)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaShuffle"></param>
        public unsafe void SyncSetShuffle(bool aaShuffle)
        {
            uint aShuffle = (aaShuffle? 1u : 0u);
            {
                CpProxyLinnCoUkPlaylist1SyncSetShuffle(iHandle, aShuffle);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetShuffle().</remarks>
        /// <param name="aaShuffle"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetShuffle(bool aaShuffle, CallbackAsyncComplete aCallback)
        {
            uint aShuffle = (aaShuffle? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginSetShuffle(iHandle, aShuffle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetShuffle(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkPlaylist1EndSetShuffle(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaShuffle"></param>
        public unsafe void SyncShuffle(out bool aaShuffle)
        {
            uint aShuffle;
            {
                CpProxyLinnCoUkPlaylist1SyncShuffle(iHandle, &aShuffle);
            }
            aaShuffle = (aShuffle != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndShuffle().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginShuffle(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginShuffle(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaShuffle"></param>
        public unsafe void EndShuffle(IntPtr aAsyncHandle, out bool aaShuffle)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTracksMax"></param>
        public unsafe void SyncTracksMax(out uint aaTracksMax)
        {
            fixed (uint* aTracksMax = &aaTracksMax)
            {
                CpProxyLinnCoUkPlaylist1SyncTracksMax(iHandle, aTracksMax);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTracksMax().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginTracksMax(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginTracksMax(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaTracksMax"></param>
        public unsafe void EndTracksMax(IntPtr aAsyncHandle, out uint aaTracksMax)
        {
            fixed (uint* aTracksMax = &aaTracksMax)
            {
                if (0 != CpProxyLinnCoUkPlaylist1EndTracksMax(iHandle, aAsyncHandle, aTracksMax))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArray"></param>
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

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIdArray().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginIdArray(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginIdArray(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArray"></param>
        public unsafe void EndIdArray(IntPtr aAsyncHandle, out uint aaIdArrayToken, out string aaIdArray)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArrayChanged"></param>
        public unsafe void SyncIdArrayChanged(uint aaIdArrayToken, out bool aaIdArrayChanged)
        {
            uint aIdArrayChanged;
            {
                CpProxyLinnCoUkPlaylist1SyncIdArrayChanged(iHandle, aaIdArrayToken, &aIdArrayChanged);
            }
            aaIdArrayChanged = (aIdArrayChanged != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIdArrayChanged().</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginIdArrayChanged(uint aaIdArrayToken, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPlaylist1BeginIdArrayChanged(iHandle, aaIdArrayToken, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIdArrayChanged"></param>
        public unsafe void EndIdArrayChanged(IntPtr aAsyncHandle, out bool aaIdArrayChanged)
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

        /// <summary>
        /// Set a delegate to be run when the IdArray state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPlaylist1 instance will not overlap.</remarks>
        /// <param name="aIdArrayChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the Repeat state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPlaylist1 instance will not overlap.</remarks>
        /// <param name="aRepeatChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the Shuffle state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPlaylist1 instance will not overlap.</remarks>
        /// <param name="aShuffleChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the TracksMax state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPlaylist1 instance will not overlap.</remarks>
        /// <param name="aTracksMaxChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Query the value of the IdArray property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aIdArray">Will be set to the value of the property</param>
        public unsafe void PropertyIdArray(out string aIdArray)
        {
            char* ptr;
            uint len;
            CpProxyLinnCoUkPlaylist1PropertyIdArray(iHandle, &ptr, &len);
            aIdArray = Marshal.PtrToStringAnsi((IntPtr)ptr, (int)len);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the Repeat property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aRepeat">Will be set to the value of the property</param>
        public unsafe void PropertyRepeat(out bool aRepeat)
        {
            uint repeat;
            CpProxyLinnCoUkPlaylist1PropertyRepeat(iHandle, &repeat);
            aRepeat = (repeat != 0);
        }

        /// <summary>
        /// Query the value of the Shuffle property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aShuffle">Will be set to the value of the property</param>
        public unsafe void PropertyShuffle(out bool aShuffle)
        {
            uint shuffle;
            CpProxyLinnCoUkPlaylist1PropertyShuffle(iHandle, &shuffle);
            aShuffle = (shuffle != 0);
        }

        /// <summary>
        /// Query the value of the TracksMax property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTracksMax">Will be set to the value of the property</param>
        public unsafe void PropertyTracksMax(out uint aTracksMax)
        {
            fixed (uint* tracksMax = &aTracksMax)
            {
                CpProxyLinnCoUkPlaylist1PropertyTracksMax(iHandle, tracksMax);
            }
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                CpProxyLinnCoUkPlaylist1Destroy(iHandle);
                iHandle = IntPtr.Zero;
            }
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

