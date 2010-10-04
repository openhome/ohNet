using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkRadio1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkRadio1")]
        static extern uint CpProxyLinnCoUkRadio1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncPlay(uint aHandle);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginPlay(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndPlay(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncPause(uint aHandle);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginPause(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndPause(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncStop(uint aHandle);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginStop(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndStop(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncSeekSecondAbsolute(uint aHandle, uint aaSecond);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginSeekSecondAbsolute(uint aHandle, uint aaSecond, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndSeekSecondAbsolute(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncSeekSecondRelative(uint aHandle, int aaSecond);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginSeekSecondRelative(uint aHandle, int aaSecond, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndSeekSecondRelative(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncChannel(uint aHandle, char** aaUri, char** aaMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginChannel(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndChannel(uint aHandle, uint aAsync, char** aaUri, char** aaMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncSetChannel(uint aHandle, char* aaUri, char* aaMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginSetChannel(uint aHandle, char* aaUri, char* aaMetadata, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndSetChannel(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncProtocolInfo(uint aHandle, char** aaInfo);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginProtocolInfo(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndProtocolInfo(uint aHandle, uint aAsync, char** aaInfo);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncTransportState(uint aHandle, char** aaState);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginTransportState(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndTransportState(uint aHandle, uint aAsync, char** aaState);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncId(uint aHandle, uint* aaId);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginId(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndId(uint aHandle, uint aAsync, uint* aaId);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncSetId(uint aHandle, uint aaId, char* aaUri);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginSetId(uint aHandle, uint aaId, char* aaUri, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndSetId(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncRead(uint aHandle, uint aaId, char** aaMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginRead(uint aHandle, uint aaId, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndRead(uint aHandle, uint aAsync, char** aaMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncReadList(uint aHandle, char* aaIdList, char** aaMetadataList);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginReadList(uint aHandle, char* aaIdList, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndReadList(uint aHandle, uint aAsync, char** aaMetadataList);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncIdArray(uint aHandle, uint* aaIdArrayToken, char** aaIdArray, uint* aaIdArrayLen);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginIdArray(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndIdArray(uint aHandle, uint aAsync, uint* aaIdArrayToken, char** aaIdArray, uint* aaIdArrayLen);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncIdArrayChanged(uint aHandle, uint aaIdArrayToken, uint* aaIdArrayChanged);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginIdArrayChanged(uint aHandle, uint aaIdArrayToken, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndIdArrayChanged(uint aHandle, uint aAsync, uint* aaIdArrayChanged);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncIdsMax(uint aHandle, uint* aaIdsMax);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginIdsMax(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndIdsMax(uint aHandle, uint aAsync, uint* aaIdsMax);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyChannelUriChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyChannelMetadataChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyTransportStateChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyProtocolInfoChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyIdChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyIdArrayChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyIdsMaxChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyChannelUri(uint aHandle, char** aChannelUri);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyChannelMetadata(uint aHandle, char** aChannelMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyTransportState(uint aHandle, char** aTransportState);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyProtocolInfo(uint aHandle, char** aProtocolInfo);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyId(uint aHandle, uint* aId);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyIdArray(uint aHandle, char** aIdArray, uint* aLen);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyIdsMax(uint aHandle, uint* aIdsMax);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iChannelUriChanged;
        private CallbackPropertyChanged iChannelMetadataChanged;
        private CallbackPropertyChanged iTransportStateChanged;
        private CallbackPropertyChanged iProtocolInfoChanged;
        private CallbackPropertyChanged iIdChanged;
        private CallbackPropertyChanged iIdArrayChanged;
        private CallbackPropertyChanged iIdsMaxChanged;
        private Callback iCallbackChannelUriChanged;
        private Callback iCallbackChannelMetadataChanged;
        private Callback iCallbackTransportStateChanged;
        private Callback iCallbackProtocolInfoChanged;
        private Callback iCallbackIdChanged;
        private Callback iCallbackIdArrayChanged;
        private Callback iCallbackIdsMaxChanged;

        public CpProxyLinnCoUkRadio1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkRadio1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncPlay()
        {
			{
				CpProxyLinnCoUkRadio1SyncPlay(iHandle);
			}
        }

        public unsafe void BeginPlay(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginPlay(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndPlay(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkRadio1EndPlay(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncPause()
        {
			{
				CpProxyLinnCoUkRadio1SyncPause(iHandle);
			}
        }

        public unsafe void BeginPause(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginPause(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndPause(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkRadio1EndPause(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStop()
        {
			{
				CpProxyLinnCoUkRadio1SyncStop(iHandle);
			}
        }

        public unsafe void BeginStop(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginStop(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStop(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkRadio1EndStop(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSeekSecondAbsolute(uint aaSecond)
        {
			{
				CpProxyLinnCoUkRadio1SyncSeekSecondAbsolute(iHandle, aaSecond);
			}
        }

        public unsafe void BeginSeekSecondAbsolute(uint aaSecond, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginSeekSecondAbsolute(iHandle, aaSecond, iActionComplete, ptr);
        }

        public unsafe void EndSeekSecondAbsolute(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkRadio1EndSeekSecondAbsolute(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSeekSecondRelative(int aaSecond)
        {
			{
				CpProxyLinnCoUkRadio1SyncSeekSecondRelative(iHandle, aaSecond);
			}
        }

        public unsafe void BeginSeekSecondRelative(int aaSecond, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginSeekSecondRelative(iHandle, aaSecond, iActionComplete, ptr);
        }

        public unsafe void EndSeekSecondRelative(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkRadio1EndSeekSecondRelative(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncChannel(out string aaUri, out string aaMetadata)
        {
			char* aUri;
			char* aMetadata;
			{
				CpProxyLinnCoUkRadio1SyncChannel(iHandle, &aUri, &aMetadata);
			}
            aaUri = Marshal.PtrToStringAnsi((IntPtr)aUri);
            ZappFree(aUri);
            aaMetadata = Marshal.PtrToStringAnsi((IntPtr)aMetadata);
            ZappFree(aMetadata);
        }

        public unsafe void BeginChannel(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginChannel(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndChannel(uint aAsyncHandle, out string aaUri, out string aaMetadata)
        {
			char* aUri;
			char* aMetadata;
			{
				if (0 != CpProxyLinnCoUkRadio1EndChannel(iHandle, aAsyncHandle, &aUri, &aMetadata))
				{
					throw(new ProxyError());
				}
			}
            aaUri = Marshal.PtrToStringAnsi((IntPtr)aUri);
            ZappFree(aUri);
            aaMetadata = Marshal.PtrToStringAnsi((IntPtr)aMetadata);
            ZappFree(aMetadata);
        }

        public unsafe void SyncSetChannel(string aaUri, string aaMetadata)
        {
			char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
			char* aMetadata = (char*)Marshal.StringToHGlobalAnsi(aaMetadata);
			{
				CpProxyLinnCoUkRadio1SyncSetChannel(iHandle, aUri, aMetadata);
			}
			Marshal.FreeHGlobal((IntPtr)aUri);
			Marshal.FreeHGlobal((IntPtr)aMetadata);
        }

        public unsafe void BeginSetChannel(string aaUri, string aaMetadata, CallbackAsyncComplete aCallback)
        {
			char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
			char* aMetadata = (char*)Marshal.StringToHGlobalAnsi(aaMetadata);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginSetChannel(iHandle, aUri, aMetadata, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aUri);
			Marshal.FreeHGlobal((IntPtr)aMetadata);
        }

        public unsafe void EndSetChannel(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkRadio1EndSetChannel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncProtocolInfo(out string aaInfo)
        {
			char* aInfo;
			{
				CpProxyLinnCoUkRadio1SyncProtocolInfo(iHandle, &aInfo);
			}
            aaInfo = Marshal.PtrToStringAnsi((IntPtr)aInfo);
            ZappFree(aInfo);
        }

        public unsafe void BeginProtocolInfo(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginProtocolInfo(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndProtocolInfo(uint aAsyncHandle, out string aaInfo)
        {
			char* aInfo;
			{
				if (0 != CpProxyLinnCoUkRadio1EndProtocolInfo(iHandle, aAsyncHandle, &aInfo))
				{
					throw(new ProxyError());
				}
			}
            aaInfo = Marshal.PtrToStringAnsi((IntPtr)aInfo);
            ZappFree(aInfo);
        }

        public unsafe void SyncTransportState(out string aaState)
        {
			char* aState;
			{
				CpProxyLinnCoUkRadio1SyncTransportState(iHandle, &aState);
			}
            aaState = Marshal.PtrToStringAnsi((IntPtr)aState);
            ZappFree(aState);
        }

        public unsafe void BeginTransportState(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginTransportState(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndTransportState(uint aAsyncHandle, out string aaState)
        {
			char* aState;
			{
				if (0 != CpProxyLinnCoUkRadio1EndTransportState(iHandle, aAsyncHandle, &aState))
				{
					throw(new ProxyError());
				}
			}
            aaState = Marshal.PtrToStringAnsi((IntPtr)aState);
            ZappFree(aState);
        }

        public unsafe void SyncId(out uint aaId)
        {
			fixed (uint* aId = &aaId)
			{
				CpProxyLinnCoUkRadio1SyncId(iHandle, aId);
			}
        }

        public unsafe void BeginId(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginId(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndId(uint aAsyncHandle, out uint aaId)
        {
			fixed (uint* aId = &aaId)
			{
				if (0 != CpProxyLinnCoUkRadio1EndId(iHandle, aAsyncHandle, aId))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetId(uint aaId, string aaUri)
        {
			char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
			{
				CpProxyLinnCoUkRadio1SyncSetId(iHandle, aaId, aUri);
			}
			Marshal.FreeHGlobal((IntPtr)aUri);
        }

        public unsafe void BeginSetId(uint aaId, string aaUri, CallbackAsyncComplete aCallback)
        {
			char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginSetId(iHandle, aaId, aUri, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aUri);
        }

        public unsafe void EndSetId(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkRadio1EndSetId(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncRead(uint aaId, out string aaMetadata)
        {
			char* aMetadata;
			{
				CpProxyLinnCoUkRadio1SyncRead(iHandle, aaId, &aMetadata);
			}
            aaMetadata = Marshal.PtrToStringAnsi((IntPtr)aMetadata);
            ZappFree(aMetadata);
        }

        public unsafe void BeginRead(uint aaId, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginRead(iHandle, aaId, iActionComplete, ptr);
        }

        public unsafe void EndRead(uint aAsyncHandle, out string aaMetadata)
        {
			char* aMetadata;
			{
				if (0 != CpProxyLinnCoUkRadio1EndRead(iHandle, aAsyncHandle, &aMetadata))
				{
					throw(new ProxyError());
				}
			}
            aaMetadata = Marshal.PtrToStringAnsi((IntPtr)aMetadata);
            ZappFree(aMetadata);
        }

        public unsafe void SyncReadList(string aaIdList, out string aaMetadataList)
        {
			char* aIdList = (char*)Marshal.StringToHGlobalAnsi(aaIdList);
			char* aMetadataList;
			{
				CpProxyLinnCoUkRadio1SyncReadList(iHandle, aIdList, &aMetadataList);
			}
			Marshal.FreeHGlobal((IntPtr)aIdList);
            aaMetadataList = Marshal.PtrToStringAnsi((IntPtr)aMetadataList);
            ZappFree(aMetadataList);
        }

        public unsafe void BeginReadList(string aaIdList, CallbackAsyncComplete aCallback)
        {
			char* aIdList = (char*)Marshal.StringToHGlobalAnsi(aaIdList);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginReadList(iHandle, aIdList, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aIdList);
        }

        public unsafe void EndReadList(uint aAsyncHandle, out string aaMetadataList)
        {
			char* aMetadataList;
			{
				if (0 != CpProxyLinnCoUkRadio1EndReadList(iHandle, aAsyncHandle, &aMetadataList))
				{
					throw(new ProxyError());
				}
			}
            aaMetadataList = Marshal.PtrToStringAnsi((IntPtr)aMetadataList);
            ZappFree(aMetadataList);
        }

        public unsafe void SyncIdArray(out uint aaIdArrayToken, out string aaIdArray)
        {
			char* aIdArray;
			uint aIdArrayLen;
			fixed (uint* aIdArrayToken = &aaIdArrayToken)
			{
				CpProxyLinnCoUkRadio1SyncIdArray(iHandle, aIdArrayToken, &aIdArray, &aIdArrayLen);
			}
            aaIdArray = Marshal.PtrToStringAnsi((IntPtr)aIdArray, (int)aIdArrayLen);
            ZappFree(aIdArray);
        }

        public unsafe void BeginIdArray(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginIdArray(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndIdArray(uint aAsyncHandle, out uint aaIdArrayToken, out string aaIdArray)
        {
			char* aIdArray;
			uint aIdArrayLen;
			fixed (uint* aIdArrayToken = &aaIdArrayToken)
			{
				if (0 != CpProxyLinnCoUkRadio1EndIdArray(iHandle, aAsyncHandle, aIdArrayToken, &aIdArray, &aIdArrayLen))
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
				CpProxyLinnCoUkRadio1SyncIdArrayChanged(iHandle, aaIdArrayToken, &aIdArrayChanged);
			}
			aaIdArrayChanged = (aIdArrayChanged != 0);
        }

        public unsafe void BeginIdArrayChanged(uint aaIdArrayToken, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginIdArrayChanged(iHandle, aaIdArrayToken, iActionComplete, ptr);
        }

        public unsafe void EndIdArrayChanged(uint aAsyncHandle, out bool aaIdArrayChanged)
        {
			uint aIdArrayChanged;
			{
				if (0 != CpProxyLinnCoUkRadio1EndIdArrayChanged(iHandle, aAsyncHandle, &aIdArrayChanged))
				{
					throw(new ProxyError());
				}
			}
			aaIdArrayChanged = (aIdArrayChanged != 0);
        }

        public unsafe void SyncIdsMax(out uint aaIdsMax)
        {
			fixed (uint* aIdsMax = &aaIdsMax)
			{
				CpProxyLinnCoUkRadio1SyncIdsMax(iHandle, aIdsMax);
			}
        }

        public unsafe void BeginIdsMax(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginIdsMax(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndIdsMax(uint aAsyncHandle, out uint aaIdsMax)
        {
			fixed (uint* aIdsMax = &aaIdsMax)
			{
				if (0 != CpProxyLinnCoUkRadio1EndIdsMax(iHandle, aAsyncHandle, aIdsMax))
				{
					throw(new ProxyError());
				}
			}
        }

        public void SetPropertyChannelUriChanged(CallbackPropertyChanged aChannelUriChanged)
        {
            iChannelUriChanged = aChannelUriChanged;
            iCallbackChannelUriChanged = new Callback(PropertyChannelUriChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyChannelUriChanged(iHandle, iCallbackChannelUriChanged, ptr);
        }

        private void PropertyChannelUriChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iChannelUriChanged();
        }

        public void SetPropertyChannelMetadataChanged(CallbackPropertyChanged aChannelMetadataChanged)
        {
            iChannelMetadataChanged = aChannelMetadataChanged;
            iCallbackChannelMetadataChanged = new Callback(PropertyChannelMetadataChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyChannelMetadataChanged(iHandle, iCallbackChannelMetadataChanged, ptr);
        }

        private void PropertyChannelMetadataChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iChannelMetadataChanged();
        }

        public void SetPropertyTransportStateChanged(CallbackPropertyChanged aTransportStateChanged)
        {
            iTransportStateChanged = aTransportStateChanged;
            iCallbackTransportStateChanged = new Callback(PropertyTransportStateChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyTransportStateChanged(iHandle, iCallbackTransportStateChanged, ptr);
        }

        private void PropertyTransportStateChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iTransportStateChanged();
        }

        public void SetPropertyProtocolInfoChanged(CallbackPropertyChanged aProtocolInfoChanged)
        {
            iProtocolInfoChanged = aProtocolInfoChanged;
            iCallbackProtocolInfoChanged = new Callback(PropertyProtocolInfoChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyProtocolInfoChanged(iHandle, iCallbackProtocolInfoChanged, ptr);
        }

        private void PropertyProtocolInfoChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iProtocolInfoChanged();
        }

        public void SetPropertyIdChanged(CallbackPropertyChanged aIdChanged)
        {
            iIdChanged = aIdChanged;
            iCallbackIdChanged = new Callback(PropertyIdChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyIdChanged(iHandle, iCallbackIdChanged, ptr);
        }

        private void PropertyIdChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iIdChanged();
        }

        public void SetPropertyIdArrayChanged(CallbackPropertyChanged aIdArrayChanged)
        {
            iIdArrayChanged = aIdArrayChanged;
            iCallbackIdArrayChanged = new Callback(PropertyIdArrayChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyIdArrayChanged(iHandle, iCallbackIdArrayChanged, ptr);
        }

        private void PropertyIdArrayChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iIdArrayChanged();
        }

        public void SetPropertyIdsMaxChanged(CallbackPropertyChanged aIdsMaxChanged)
        {
            iIdsMaxChanged = aIdsMaxChanged;
            iCallbackIdsMaxChanged = new Callback(PropertyIdsMaxChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyIdsMaxChanged(iHandle, iCallbackIdsMaxChanged, ptr);
        }

        private void PropertyIdsMaxChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iIdsMaxChanged();
        }

        public unsafe void PropertyChannelUri(out string aChannelUri)
        {
			char* ptr;
            CpProxyLinnCoUkRadio1PropertyChannelUri(iHandle, &ptr);
            aChannelUri = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyChannelMetadata(out string aChannelMetadata)
        {
			char* ptr;
            CpProxyLinnCoUkRadio1PropertyChannelMetadata(iHandle, &ptr);
            aChannelMetadata = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyTransportState(out string aTransportState)
        {
			char* ptr;
            CpProxyLinnCoUkRadio1PropertyTransportState(iHandle, &ptr);
            aTransportState = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyProtocolInfo(out string aProtocolInfo)
        {
			char* ptr;
            CpProxyLinnCoUkRadio1PropertyProtocolInfo(iHandle, &ptr);
            aProtocolInfo = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyId(out uint aId)
        {
			fixed (uint* id = &aId)
			{
	            CpProxyLinnCoUkRadio1PropertyId(iHandle, id);
			}
        }

        public unsafe void PropertyIdArray(out string aIdArray)
        {
			char* ptr;
			uint len;
	        CpProxyLinnCoUkRadio1PropertyIdArray(iHandle, &ptr, &len);
            aIdArray = Marshal.PtrToStringAnsi((IntPtr)ptr, (int)len);
            ZappFree(ptr);
        }

        public unsafe void PropertyIdsMax(out uint aIdsMax)
        {
			fixed (uint* idsMax = &aIdsMax)
			{
	            CpProxyLinnCoUkRadio1PropertyIdsMax(iHandle, idsMax);
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkRadio1()
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
            CpProxyLinnCoUkRadio1Destroy(handle);
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

