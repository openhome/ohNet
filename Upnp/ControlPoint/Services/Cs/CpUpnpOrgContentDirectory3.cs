using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyUpnpOrgContentDirectory3 : CpProxy, IDisposable
    {
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern uint CpProxyUpnpOrgContentDirectory3Create(uint aDeviceHandle);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern void CpProxyUpnpOrgContentDirectory3Destroy(uint aHandle);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncGetSearchCapabilities(uint aHandle, char** aSearchCaps);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginGetSearchCapabilities(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndGetSearchCapabilities(uint aHandle, uint aAsync, char** aSearchCaps);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncGetSortCapabilities(uint aHandle, char** aSortCaps);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginGetSortCapabilities(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndGetSortCapabilities(uint aHandle, uint aAsync, char** aSortCaps);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncGetSortExtensionCapabilities(uint aHandle, char** aSortExtensionCaps);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginGetSortExtensionCapabilities(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndGetSortExtensionCapabilities(uint aHandle, uint aAsync, char** aSortExtensionCaps);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncGetFeatureList(uint aHandle, char** aFeatureList);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginGetFeatureList(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndGetFeatureList(uint aHandle, uint aAsync, char** aFeatureList);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncGetSystemUpdateID(uint aHandle, uint* aId);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginGetSystemUpdateID(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndGetSystemUpdateID(uint aHandle, uint aAsync, uint* aId);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncGetServiceResetToken(uint aHandle, char** aResetToken);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginGetServiceResetToken(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndGetServiceResetToken(uint aHandle, uint aAsync, char** aResetToken);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncBrowse(uint aHandle, char* aObjectID, char* aBrowseFlag, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginBrowse(uint aHandle, char* aObjectID, char* aBrowseFlag, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndBrowse(uint aHandle, uint aAsync, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncSearch(uint aHandle, char* aContainerID, char* aSearchCriteria, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginSearch(uint aHandle, char* aContainerID, char* aSearchCriteria, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndSearch(uint aHandle, uint aAsync, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncCreateObject(uint aHandle, char* aContainerID, char* aElements, char** aObjectID, char** aResult);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginCreateObject(uint aHandle, char* aContainerID, char* aElements, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndCreateObject(uint aHandle, uint aAsync, char** aObjectID, char** aResult);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncDestroyObject(uint aHandle, char* aObjectID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginDestroyObject(uint aHandle, char* aObjectID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndDestroyObject(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncUpdateObject(uint aHandle, char* aObjectID, char* aCurrentTagValue, char* aNewTagValue);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginUpdateObject(uint aHandle, char* aObjectID, char* aCurrentTagValue, char* aNewTagValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndUpdateObject(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncMoveObject(uint aHandle, char* aObjectID, char* aNewParentID, char** aNewObjectID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginMoveObject(uint aHandle, char* aObjectID, char* aNewParentID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndMoveObject(uint aHandle, uint aAsync, char** aNewObjectID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncImportResource(uint aHandle, char* aSourceURI, char* aDestinationURI, uint* aTransferID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginImportResource(uint aHandle, char* aSourceURI, char* aDestinationURI, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndImportResource(uint aHandle, uint aAsync, uint* aTransferID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncExportResource(uint aHandle, char* aSourceURI, char* aDestinationURI, uint* aTransferID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginExportResource(uint aHandle, char* aSourceURI, char* aDestinationURI, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndExportResource(uint aHandle, uint aAsync, uint* aTransferID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncDeleteResource(uint aHandle, char* aResourceURI);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginDeleteResource(uint aHandle, char* aResourceURI, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndDeleteResource(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncStopTransferResource(uint aHandle, uint aTransferID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginStopTransferResource(uint aHandle, uint aTransferID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndStopTransferResource(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncGetTransferProgress(uint aHandle, uint aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginGetTransferProgress(uint aHandle, uint aTransferID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndGetTransferProgress(uint aHandle, uint aAsync, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncCreateReference(uint aHandle, char* aContainerID, char* aObjectID, char** aNewID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginCreateReference(uint aHandle, char* aContainerID, char* aObjectID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndCreateReference(uint aHandle, uint aAsync, char** aNewID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncFreeFormQuery(uint aHandle, char* aContainerID, uint aCDSView, char* aQueryRequest, char** aQueryResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginFreeFormQuery(uint aHandle, char* aContainerID, uint aCDSView, char* aQueryRequest, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndFreeFormQuery(uint aHandle, uint aAsync, char** aQueryResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3SyncGetFreeFormQueryCapabilities(uint aHandle, char** aFFQCapabilities);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3BeginGetFreeFormQueryCapabilities(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory3EndGetFreeFormQueryCapabilities(uint aHandle, uint aAsync, char** aFFQCapabilities);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern void CpProxyUpnpOrgContentDirectory3SetPropertySystemUpdateIDChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern void CpProxyUpnpOrgContentDirectory3SetPropertyContainerUpdateIDsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern void CpProxyUpnpOrgContentDirectory3SetPropertyLastChangeChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern void CpProxyUpnpOrgContentDirectory3SetPropertyTransferIDsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3PropertySystemUpdateID(uint aHandle, uint* aSystemUpdateID);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3PropertyContainerUpdateIDs(uint aHandle, char** aContainerUpdateIDs);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3PropertyLastChange(uint aHandle, char** aLastChange);
        [DllImport("CpUpnpOrgContentDirectory3")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory3PropertyTransferIDs(uint aHandle, char** aTransferIDs);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iSystemUpdateIDChanged;
        private CallbackPropertyChanged iContainerUpdateIDsChanged;
        private CallbackPropertyChanged iLastChangeChanged;
        private CallbackPropertyChanged iTransferIDsChanged;
        private Callback iCallbackSystemUpdateIDChanged;
        private Callback iCallbackContainerUpdateIDsChanged;
        private Callback iCallbackLastChangeChanged;
        private Callback iCallbackTransferIDsChanged;

        public CpProxyUpnpOrgContentDirectory3(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgContentDirectory3Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncGetSearchCapabilities(out string aSearchCaps)
        {
			char* searchCaps;
			{
				CpProxyUpnpOrgContentDirectory3SyncGetSearchCapabilities(iHandle, &searchCaps);
			}
            aSearchCaps = Marshal.PtrToStringAnsi((IntPtr)searchCaps);
            ZappFree(searchCaps);
        }

        public unsafe void BeginGetSearchCapabilities(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginGetSearchCapabilities(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetSearchCapabilities(uint aAsyncHandle, out string aSearchCaps)
        {
			char* searchCaps;
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndGetSearchCapabilities(iHandle, aAsyncHandle, &searchCaps))
				{
					throw(new ProxyError());
				}
			}
            aSearchCaps = Marshal.PtrToStringAnsi((IntPtr)searchCaps);
            ZappFree(searchCaps);
        }

        public unsafe void SyncGetSortCapabilities(out string aSortCaps)
        {
			char* sortCaps;
			{
				CpProxyUpnpOrgContentDirectory3SyncGetSortCapabilities(iHandle, &sortCaps);
			}
            aSortCaps = Marshal.PtrToStringAnsi((IntPtr)sortCaps);
            ZappFree(sortCaps);
        }

        public unsafe void BeginGetSortCapabilities(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginGetSortCapabilities(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetSortCapabilities(uint aAsyncHandle, out string aSortCaps)
        {
			char* sortCaps;
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndGetSortCapabilities(iHandle, aAsyncHandle, &sortCaps))
				{
					throw(new ProxyError());
				}
			}
            aSortCaps = Marshal.PtrToStringAnsi((IntPtr)sortCaps);
            ZappFree(sortCaps);
        }

        public unsafe void SyncGetSortExtensionCapabilities(out string aSortExtensionCaps)
        {
			char* sortExtensionCaps;
			{
				CpProxyUpnpOrgContentDirectory3SyncGetSortExtensionCapabilities(iHandle, &sortExtensionCaps);
			}
            aSortExtensionCaps = Marshal.PtrToStringAnsi((IntPtr)sortExtensionCaps);
            ZappFree(sortExtensionCaps);
        }

        public unsafe void BeginGetSortExtensionCapabilities(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginGetSortExtensionCapabilities(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetSortExtensionCapabilities(uint aAsyncHandle, out string aSortExtensionCaps)
        {
			char* sortExtensionCaps;
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndGetSortExtensionCapabilities(iHandle, aAsyncHandle, &sortExtensionCaps))
				{
					throw(new ProxyError());
				}
			}
            aSortExtensionCaps = Marshal.PtrToStringAnsi((IntPtr)sortExtensionCaps);
            ZappFree(sortExtensionCaps);
        }

        public unsafe void SyncGetFeatureList(out string aFeatureList)
        {
			char* featureList;
			{
				CpProxyUpnpOrgContentDirectory3SyncGetFeatureList(iHandle, &featureList);
			}
            aFeatureList = Marshal.PtrToStringAnsi((IntPtr)featureList);
            ZappFree(featureList);
        }

        public unsafe void BeginGetFeatureList(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginGetFeatureList(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetFeatureList(uint aAsyncHandle, out string aFeatureList)
        {
			char* featureList;
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndGetFeatureList(iHandle, aAsyncHandle, &featureList))
				{
					throw(new ProxyError());
				}
			}
            aFeatureList = Marshal.PtrToStringAnsi((IntPtr)featureList);
            ZappFree(featureList);
        }

        public unsafe void SyncGetSystemUpdateID(out uint aId)
        {
			fixed (uint* id = &aId)
			{
				CpProxyUpnpOrgContentDirectory3SyncGetSystemUpdateID(iHandle, id);
			}
        }

        public unsafe void BeginGetSystemUpdateID(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginGetSystemUpdateID(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetSystemUpdateID(uint aAsyncHandle, out uint aId)
        {
			fixed (uint* id = &aId)
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndGetSystemUpdateID(iHandle, aAsyncHandle, id))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetServiceResetToken(out string aResetToken)
        {
			char* resetToken;
			{
				CpProxyUpnpOrgContentDirectory3SyncGetServiceResetToken(iHandle, &resetToken);
			}
            aResetToken = Marshal.PtrToStringAnsi((IntPtr)resetToken);
            ZappFree(resetToken);
        }

        public unsafe void BeginGetServiceResetToken(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginGetServiceResetToken(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetServiceResetToken(uint aAsyncHandle, out string aResetToken)
        {
			char* resetToken;
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndGetServiceResetToken(iHandle, aAsyncHandle, &resetToken))
				{
					throw(new ProxyError());
				}
			}
            aResetToken = Marshal.PtrToStringAnsi((IntPtr)resetToken);
            ZappFree(resetToken);
        }

        public unsafe void SyncBrowse(string aObjectID, string aBrowseFlag, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
			char* browseFlag = (char*)Marshal.StringToHGlobalAnsi(aBrowseFlag);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
			char* sortCriteria = (char*)Marshal.StringToHGlobalAnsi(aSortCriteria);
			char* result;
			fixed (uint* numberReturned = &aNumberReturned)
			fixed (uint* totalMatches = &aTotalMatches)
			fixed (uint* updateID = &aUpdateID)
			{
				CpProxyUpnpOrgContentDirectory3SyncBrowse(iHandle, objectID, browseFlag, filter, aStartingIndex, aRequestedCount, sortCriteria, &result, numberReturned, totalMatches, updateID);
			}
			Marshal.FreeHGlobal((IntPtr)objectID);
			Marshal.FreeHGlobal((IntPtr)browseFlag);
			Marshal.FreeHGlobal((IntPtr)filter);
			Marshal.FreeHGlobal((IntPtr)sortCriteria);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void BeginBrowse(string aObjectID, string aBrowseFlag, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, CallbackAsyncComplete aCallback)
        {
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
			char* browseFlag = (char*)Marshal.StringToHGlobalAnsi(aBrowseFlag);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
			char* sortCriteria = (char*)Marshal.StringToHGlobalAnsi(aSortCriteria);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginBrowse(iHandle, objectID, browseFlag, filter, aStartingIndex, aRequestedCount, sortCriteria, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)objectID);
			Marshal.FreeHGlobal((IntPtr)browseFlag);
			Marshal.FreeHGlobal((IntPtr)filter);
			Marshal.FreeHGlobal((IntPtr)sortCriteria);
        }

        public unsafe void EndBrowse(uint aAsyncHandle, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
			char* result;
			fixed (uint* numberReturned = &aNumberReturned)
			fixed (uint* totalMatches = &aTotalMatches)
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndBrowse(iHandle, aAsyncHandle, &result, numberReturned, totalMatches, updateID))
				{
					throw(new ProxyError());
				}
			}
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void SyncSearch(string aContainerID, string aSearchCriteria, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
			char* containerID = (char*)Marshal.StringToHGlobalAnsi(aContainerID);
			char* searchCriteria = (char*)Marshal.StringToHGlobalAnsi(aSearchCriteria);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
			char* sortCriteria = (char*)Marshal.StringToHGlobalAnsi(aSortCriteria);
			char* result;
			fixed (uint* numberReturned = &aNumberReturned)
			fixed (uint* totalMatches = &aTotalMatches)
			fixed (uint* updateID = &aUpdateID)
			{
				CpProxyUpnpOrgContentDirectory3SyncSearch(iHandle, containerID, searchCriteria, filter, aStartingIndex, aRequestedCount, sortCriteria, &result, numberReturned, totalMatches, updateID);
			}
			Marshal.FreeHGlobal((IntPtr)containerID);
			Marshal.FreeHGlobal((IntPtr)searchCriteria);
			Marshal.FreeHGlobal((IntPtr)filter);
			Marshal.FreeHGlobal((IntPtr)sortCriteria);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void BeginSearch(string aContainerID, string aSearchCriteria, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, CallbackAsyncComplete aCallback)
        {
			char* containerID = (char*)Marshal.StringToHGlobalAnsi(aContainerID);
			char* searchCriteria = (char*)Marshal.StringToHGlobalAnsi(aSearchCriteria);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
			char* sortCriteria = (char*)Marshal.StringToHGlobalAnsi(aSortCriteria);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginSearch(iHandle, containerID, searchCriteria, filter, aStartingIndex, aRequestedCount, sortCriteria, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)containerID);
			Marshal.FreeHGlobal((IntPtr)searchCriteria);
			Marshal.FreeHGlobal((IntPtr)filter);
			Marshal.FreeHGlobal((IntPtr)sortCriteria);
        }

        public unsafe void EndSearch(uint aAsyncHandle, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
			char* result;
			fixed (uint* numberReturned = &aNumberReturned)
			fixed (uint* totalMatches = &aTotalMatches)
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndSearch(iHandle, aAsyncHandle, &result, numberReturned, totalMatches, updateID))
				{
					throw(new ProxyError());
				}
			}
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void SyncCreateObject(string aContainerID, string aElements, out string aObjectID, out string aResult)
        {
			char* containerID = (char*)Marshal.StringToHGlobalAnsi(aContainerID);
			char* elements = (char*)Marshal.StringToHGlobalAnsi(aElements);
			char* objectID;
			char* result;
			{
				CpProxyUpnpOrgContentDirectory3SyncCreateObject(iHandle, containerID, elements, &objectID, &result);
			}
			Marshal.FreeHGlobal((IntPtr)containerID);
			Marshal.FreeHGlobal((IntPtr)elements);
            aObjectID = Marshal.PtrToStringAnsi((IntPtr)objectID);
            ZappFree(objectID);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void BeginCreateObject(string aContainerID, string aElements, CallbackAsyncComplete aCallback)
        {
			char* containerID = (char*)Marshal.StringToHGlobalAnsi(aContainerID);
			char* elements = (char*)Marshal.StringToHGlobalAnsi(aElements);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginCreateObject(iHandle, containerID, elements, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)containerID);
			Marshal.FreeHGlobal((IntPtr)elements);
        }

        public unsafe void EndCreateObject(uint aAsyncHandle, out string aObjectID, out string aResult)
        {
			char* objectID;
			char* result;
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndCreateObject(iHandle, aAsyncHandle, &objectID, &result))
				{
					throw(new ProxyError());
				}
			}
            aObjectID = Marshal.PtrToStringAnsi((IntPtr)objectID);
            ZappFree(objectID);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void SyncDestroyObject(string aObjectID)
        {
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
			{
				CpProxyUpnpOrgContentDirectory3SyncDestroyObject(iHandle, objectID);
			}
			Marshal.FreeHGlobal((IntPtr)objectID);
        }

        public unsafe void BeginDestroyObject(string aObjectID, CallbackAsyncComplete aCallback)
        {
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginDestroyObject(iHandle, objectID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)objectID);
        }

        public unsafe void EndDestroyObject(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndDestroyObject(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncUpdateObject(string aObjectID, string aCurrentTagValue, string aNewTagValue)
        {
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
			char* currentTagValue = (char*)Marshal.StringToHGlobalAnsi(aCurrentTagValue);
			char* newTagValue = (char*)Marshal.StringToHGlobalAnsi(aNewTagValue);
			{
				CpProxyUpnpOrgContentDirectory3SyncUpdateObject(iHandle, objectID, currentTagValue, newTagValue);
			}
			Marshal.FreeHGlobal((IntPtr)objectID);
			Marshal.FreeHGlobal((IntPtr)currentTagValue);
			Marshal.FreeHGlobal((IntPtr)newTagValue);
        }

        public unsafe void BeginUpdateObject(string aObjectID, string aCurrentTagValue, string aNewTagValue, CallbackAsyncComplete aCallback)
        {
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
			char* currentTagValue = (char*)Marshal.StringToHGlobalAnsi(aCurrentTagValue);
			char* newTagValue = (char*)Marshal.StringToHGlobalAnsi(aNewTagValue);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginUpdateObject(iHandle, objectID, currentTagValue, newTagValue, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)objectID);
			Marshal.FreeHGlobal((IntPtr)currentTagValue);
			Marshal.FreeHGlobal((IntPtr)newTagValue);
        }

        public unsafe void EndUpdateObject(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndUpdateObject(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncMoveObject(string aObjectID, string aNewParentID, out string aNewObjectID)
        {
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
			char* newParentID = (char*)Marshal.StringToHGlobalAnsi(aNewParentID);
			char* newObjectID;
			{
				CpProxyUpnpOrgContentDirectory3SyncMoveObject(iHandle, objectID, newParentID, &newObjectID);
			}
			Marshal.FreeHGlobal((IntPtr)objectID);
			Marshal.FreeHGlobal((IntPtr)newParentID);
            aNewObjectID = Marshal.PtrToStringAnsi((IntPtr)newObjectID);
            ZappFree(newObjectID);
        }

        public unsafe void BeginMoveObject(string aObjectID, string aNewParentID, CallbackAsyncComplete aCallback)
        {
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
			char* newParentID = (char*)Marshal.StringToHGlobalAnsi(aNewParentID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginMoveObject(iHandle, objectID, newParentID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)objectID);
			Marshal.FreeHGlobal((IntPtr)newParentID);
        }

        public unsafe void EndMoveObject(uint aAsyncHandle, out string aNewObjectID)
        {
			char* newObjectID;
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndMoveObject(iHandle, aAsyncHandle, &newObjectID))
				{
					throw(new ProxyError());
				}
			}
            aNewObjectID = Marshal.PtrToStringAnsi((IntPtr)newObjectID);
            ZappFree(newObjectID);
        }

        public unsafe void SyncImportResource(string aSourceURI, string aDestinationURI, out uint aTransferID)
        {
			char* sourceURI = (char*)Marshal.StringToHGlobalAnsi(aSourceURI);
			char* destinationURI = (char*)Marshal.StringToHGlobalAnsi(aDestinationURI);
			fixed (uint* transferID = &aTransferID)
			{
				CpProxyUpnpOrgContentDirectory3SyncImportResource(iHandle, sourceURI, destinationURI, transferID);
			}
			Marshal.FreeHGlobal((IntPtr)sourceURI);
			Marshal.FreeHGlobal((IntPtr)destinationURI);
        }

        public unsafe void BeginImportResource(string aSourceURI, string aDestinationURI, CallbackAsyncComplete aCallback)
        {
			char* sourceURI = (char*)Marshal.StringToHGlobalAnsi(aSourceURI);
			char* destinationURI = (char*)Marshal.StringToHGlobalAnsi(aDestinationURI);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginImportResource(iHandle, sourceURI, destinationURI, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)sourceURI);
			Marshal.FreeHGlobal((IntPtr)destinationURI);
        }

        public unsafe void EndImportResource(uint aAsyncHandle, out uint aTransferID)
        {
			fixed (uint* transferID = &aTransferID)
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndImportResource(iHandle, aAsyncHandle, transferID))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncExportResource(string aSourceURI, string aDestinationURI, out uint aTransferID)
        {
			char* sourceURI = (char*)Marshal.StringToHGlobalAnsi(aSourceURI);
			char* destinationURI = (char*)Marshal.StringToHGlobalAnsi(aDestinationURI);
			fixed (uint* transferID = &aTransferID)
			{
				CpProxyUpnpOrgContentDirectory3SyncExportResource(iHandle, sourceURI, destinationURI, transferID);
			}
			Marshal.FreeHGlobal((IntPtr)sourceURI);
			Marshal.FreeHGlobal((IntPtr)destinationURI);
        }

        public unsafe void BeginExportResource(string aSourceURI, string aDestinationURI, CallbackAsyncComplete aCallback)
        {
			char* sourceURI = (char*)Marshal.StringToHGlobalAnsi(aSourceURI);
			char* destinationURI = (char*)Marshal.StringToHGlobalAnsi(aDestinationURI);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginExportResource(iHandle, sourceURI, destinationURI, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)sourceURI);
			Marshal.FreeHGlobal((IntPtr)destinationURI);
        }

        public unsafe void EndExportResource(uint aAsyncHandle, out uint aTransferID)
        {
			fixed (uint* transferID = &aTransferID)
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndExportResource(iHandle, aAsyncHandle, transferID))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDeleteResource(string aResourceURI)
        {
			char* resourceURI = (char*)Marshal.StringToHGlobalAnsi(aResourceURI);
			{
				CpProxyUpnpOrgContentDirectory3SyncDeleteResource(iHandle, resourceURI);
			}
			Marshal.FreeHGlobal((IntPtr)resourceURI);
        }

        public unsafe void BeginDeleteResource(string aResourceURI, CallbackAsyncComplete aCallback)
        {
			char* resourceURI = (char*)Marshal.StringToHGlobalAnsi(aResourceURI);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginDeleteResource(iHandle, resourceURI, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)resourceURI);
        }

        public unsafe void EndDeleteResource(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndDeleteResource(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStopTransferResource(uint aTransferID)
        {
			{
				CpProxyUpnpOrgContentDirectory3SyncStopTransferResource(iHandle, aTransferID);
			}
        }

        public unsafe void BeginStopTransferResource(uint aTransferID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginStopTransferResource(iHandle, aTransferID, iActionComplete, ptr);
        }

        public unsafe void EndStopTransferResource(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndStopTransferResource(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetTransferProgress(uint aTransferID, out string aTransferStatus, out string aTransferLength, out string aTransferTotal)
        {
			char* transferStatus;
			char* transferLength;
			char* transferTotal;
			{
				CpProxyUpnpOrgContentDirectory3SyncGetTransferProgress(iHandle, aTransferID, &transferStatus, &transferLength, &transferTotal);
			}
            aTransferStatus = Marshal.PtrToStringAnsi((IntPtr)transferStatus);
            ZappFree(transferStatus);
            aTransferLength = Marshal.PtrToStringAnsi((IntPtr)transferLength);
            ZappFree(transferLength);
            aTransferTotal = Marshal.PtrToStringAnsi((IntPtr)transferTotal);
            ZappFree(transferTotal);
        }

        public unsafe void BeginGetTransferProgress(uint aTransferID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginGetTransferProgress(iHandle, aTransferID, iActionComplete, ptr);
        }

        public unsafe void EndGetTransferProgress(uint aAsyncHandle, out string aTransferStatus, out string aTransferLength, out string aTransferTotal)
        {
			char* transferStatus;
			char* transferLength;
			char* transferTotal;
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndGetTransferProgress(iHandle, aAsyncHandle, &transferStatus, &transferLength, &transferTotal))
				{
					throw(new ProxyError());
				}
			}
            aTransferStatus = Marshal.PtrToStringAnsi((IntPtr)transferStatus);
            ZappFree(transferStatus);
            aTransferLength = Marshal.PtrToStringAnsi((IntPtr)transferLength);
            ZappFree(transferLength);
            aTransferTotal = Marshal.PtrToStringAnsi((IntPtr)transferTotal);
            ZappFree(transferTotal);
        }

        public unsafe void SyncCreateReference(string aContainerID, string aObjectID, out string aNewID)
        {
			char* containerID = (char*)Marshal.StringToHGlobalAnsi(aContainerID);
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
			char* newID;
			{
				CpProxyUpnpOrgContentDirectory3SyncCreateReference(iHandle, containerID, objectID, &newID);
			}
			Marshal.FreeHGlobal((IntPtr)containerID);
			Marshal.FreeHGlobal((IntPtr)objectID);
            aNewID = Marshal.PtrToStringAnsi((IntPtr)newID);
            ZappFree(newID);
        }

        public unsafe void BeginCreateReference(string aContainerID, string aObjectID, CallbackAsyncComplete aCallback)
        {
			char* containerID = (char*)Marshal.StringToHGlobalAnsi(aContainerID);
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginCreateReference(iHandle, containerID, objectID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)containerID);
			Marshal.FreeHGlobal((IntPtr)objectID);
        }

        public unsafe void EndCreateReference(uint aAsyncHandle, out string aNewID)
        {
			char* newID;
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndCreateReference(iHandle, aAsyncHandle, &newID))
				{
					throw(new ProxyError());
				}
			}
            aNewID = Marshal.PtrToStringAnsi((IntPtr)newID);
            ZappFree(newID);
        }

        public unsafe void SyncFreeFormQuery(string aContainerID, uint aCDSView, string aQueryRequest, out string aQueryResult, out uint aUpdateID)
        {
			char* containerID = (char*)Marshal.StringToHGlobalAnsi(aContainerID);
			char* queryRequest = (char*)Marshal.StringToHGlobalAnsi(aQueryRequest);
			char* queryResult;
			fixed (uint* updateID = &aUpdateID)
			{
				CpProxyUpnpOrgContentDirectory3SyncFreeFormQuery(iHandle, containerID, aCDSView, queryRequest, &queryResult, updateID);
			}
			Marshal.FreeHGlobal((IntPtr)containerID);
			Marshal.FreeHGlobal((IntPtr)queryRequest);
            aQueryResult = Marshal.PtrToStringAnsi((IntPtr)queryResult);
            ZappFree(queryResult);
        }

        public unsafe void BeginFreeFormQuery(string aContainerID, uint aCDSView, string aQueryRequest, CallbackAsyncComplete aCallback)
        {
			char* containerID = (char*)Marshal.StringToHGlobalAnsi(aContainerID);
			char* queryRequest = (char*)Marshal.StringToHGlobalAnsi(aQueryRequest);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginFreeFormQuery(iHandle, containerID, aCDSView, queryRequest, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)containerID);
			Marshal.FreeHGlobal((IntPtr)queryRequest);
        }

        public unsafe void EndFreeFormQuery(uint aAsyncHandle, out string aQueryResult, out uint aUpdateID)
        {
			char* queryResult;
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndFreeFormQuery(iHandle, aAsyncHandle, &queryResult, updateID))
				{
					throw(new ProxyError());
				}
			}
            aQueryResult = Marshal.PtrToStringAnsi((IntPtr)queryResult);
            ZappFree(queryResult);
        }

        public unsafe void SyncGetFreeFormQueryCapabilities(out string aFFQCapabilities)
        {
			char* fFQCapabilities;
			{
				CpProxyUpnpOrgContentDirectory3SyncGetFreeFormQueryCapabilities(iHandle, &fFQCapabilities);
			}
            aFFQCapabilities = Marshal.PtrToStringAnsi((IntPtr)fFQCapabilities);
            ZappFree(fFQCapabilities);
        }

        public unsafe void BeginGetFreeFormQueryCapabilities(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory3BeginGetFreeFormQueryCapabilities(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetFreeFormQueryCapabilities(uint aAsyncHandle, out string aFFQCapabilities)
        {
			char* fFQCapabilities;
			{
				if (0 != CpProxyUpnpOrgContentDirectory3EndGetFreeFormQueryCapabilities(iHandle, aAsyncHandle, &fFQCapabilities))
				{
					throw(new ProxyError());
				}
			}
            aFFQCapabilities = Marshal.PtrToStringAnsi((IntPtr)fFQCapabilities);
            ZappFree(fFQCapabilities);
        }

        public void SetPropertySystemUpdateIDChanged(CallbackPropertyChanged aSystemUpdateIDChanged)
        {
            iSystemUpdateIDChanged = aSystemUpdateIDChanged;
            iCallbackSystemUpdateIDChanged = new Callback(PropertySystemUpdateIDChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgContentDirectory3SetPropertySystemUpdateIDChanged(iHandle, iCallbackSystemUpdateIDChanged, ptr);
        }

        private void PropertySystemUpdateIDChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgContentDirectory3 self = (CpProxyUpnpOrgContentDirectory3)gch.Target;
            self.iSystemUpdateIDChanged();
        }

        public void SetPropertyContainerUpdateIDsChanged(CallbackPropertyChanged aContainerUpdateIDsChanged)
        {
            iContainerUpdateIDsChanged = aContainerUpdateIDsChanged;
            iCallbackContainerUpdateIDsChanged = new Callback(PropertyContainerUpdateIDsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgContentDirectory3SetPropertyContainerUpdateIDsChanged(iHandle, iCallbackContainerUpdateIDsChanged, ptr);
        }

        private void PropertyContainerUpdateIDsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgContentDirectory3 self = (CpProxyUpnpOrgContentDirectory3)gch.Target;
            self.iContainerUpdateIDsChanged();
        }

        public void SetPropertyLastChangeChanged(CallbackPropertyChanged aLastChangeChanged)
        {
            iLastChangeChanged = aLastChangeChanged;
            iCallbackLastChangeChanged = new Callback(PropertyLastChangeChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgContentDirectory3SetPropertyLastChangeChanged(iHandle, iCallbackLastChangeChanged, ptr);
        }

        private void PropertyLastChangeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgContentDirectory3 self = (CpProxyUpnpOrgContentDirectory3)gch.Target;
            self.iLastChangeChanged();
        }

        public void SetPropertyTransferIDsChanged(CallbackPropertyChanged aTransferIDsChanged)
        {
            iTransferIDsChanged = aTransferIDsChanged;
            iCallbackTransferIDsChanged = new Callback(PropertyTransferIDsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgContentDirectory3SetPropertyTransferIDsChanged(iHandle, iCallbackTransferIDsChanged, ptr);
        }

        private void PropertyTransferIDsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgContentDirectory3 self = (CpProxyUpnpOrgContentDirectory3)gch.Target;
            self.iTransferIDsChanged();
        }

        public unsafe void PropertySystemUpdateID(out uint aSystemUpdateID)
        {
			fixed (uint* systemUpdateID = &aSystemUpdateID)
			{
	            CpProxyUpnpOrgContentDirectory3PropertySystemUpdateID(iHandle, systemUpdateID);
			}
        }

        public unsafe void PropertyContainerUpdateIDs(out string aContainerUpdateIDs)
        {
			char* ptr;
            CpProxyUpnpOrgContentDirectory3PropertyContainerUpdateIDs(iHandle, &ptr);
            aContainerUpdateIDs = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyLastChange(out string aLastChange)
        {
			char* ptr;
            CpProxyUpnpOrgContentDirectory3PropertyLastChange(iHandle, &ptr);
            aLastChange = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyTransferIDs(out string aTransferIDs)
        {
			char* ptr;
            CpProxyUpnpOrgContentDirectory3PropertyTransferIDs(iHandle, &ptr);
            aTransferIDs = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgContentDirectory3()
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
            CpProxyUpnpOrgContentDirectory3Destroy(handle);
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

