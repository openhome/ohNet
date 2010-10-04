using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyUpnpOrgContentDirectory1 : CpProxy, IDisposable
    {
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern uint CpProxyUpnpOrgContentDirectory1Create(uint aDeviceHandle);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern void CpProxyUpnpOrgContentDirectory1Destroy(uint aHandle);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncGetSearchCapabilities(uint aHandle, char** aSearchCaps);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginGetSearchCapabilities(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndGetSearchCapabilities(uint aHandle, uint aAsync, char** aSearchCaps);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncGetSortCapabilities(uint aHandle, char** aSortCaps);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginGetSortCapabilities(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndGetSortCapabilities(uint aHandle, uint aAsync, char** aSortCaps);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncGetSystemUpdateID(uint aHandle, uint* aId);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginGetSystemUpdateID(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndGetSystemUpdateID(uint aHandle, uint aAsync, uint* aId);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncBrowse(uint aHandle, char* aObjectID, char* aBrowseFlag, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginBrowse(uint aHandle, char* aObjectID, char* aBrowseFlag, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndBrowse(uint aHandle, uint aAsync, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncSearch(uint aHandle, char* aContainerID, char* aSearchCriteria, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginSearch(uint aHandle, char* aContainerID, char* aSearchCriteria, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndSearch(uint aHandle, uint aAsync, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncCreateObject(uint aHandle, char* aContainerID, char* aElements, char** aObjectID, char** aResult);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginCreateObject(uint aHandle, char* aContainerID, char* aElements, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndCreateObject(uint aHandle, uint aAsync, char** aObjectID, char** aResult);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncDestroyObject(uint aHandle, char* aObjectID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginDestroyObject(uint aHandle, char* aObjectID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndDestroyObject(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncUpdateObject(uint aHandle, char* aObjectID, char* aCurrentTagValue, char* aNewTagValue);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginUpdateObject(uint aHandle, char* aObjectID, char* aCurrentTagValue, char* aNewTagValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndUpdateObject(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncImportResource(uint aHandle, char* aSourceURI, char* aDestinationURI, uint* aTransferID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginImportResource(uint aHandle, char* aSourceURI, char* aDestinationURI, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndImportResource(uint aHandle, uint aAsync, uint* aTransferID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncExportResource(uint aHandle, char* aSourceURI, char* aDestinationURI, uint* aTransferID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginExportResource(uint aHandle, char* aSourceURI, char* aDestinationURI, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndExportResource(uint aHandle, uint aAsync, uint* aTransferID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncStopTransferResource(uint aHandle, uint aTransferID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginStopTransferResource(uint aHandle, uint aTransferID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndStopTransferResource(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncGetTransferProgress(uint aHandle, uint aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginGetTransferProgress(uint aHandle, uint aTransferID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndGetTransferProgress(uint aHandle, uint aAsync, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncDeleteResource(uint aHandle, char* aResourceURI);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginDeleteResource(uint aHandle, char* aResourceURI, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndDeleteResource(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1SyncCreateReference(uint aHandle, char* aContainerID, char* aObjectID, char** aNewID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1BeginCreateReference(uint aHandle, char* aContainerID, char* aObjectID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe int CpProxyUpnpOrgContentDirectory1EndCreateReference(uint aHandle, uint aAsync, char** aNewID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern void CpProxyUpnpOrgContentDirectory1SetPropertyTransferIDsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern void CpProxyUpnpOrgContentDirectory1SetPropertySystemUpdateIDChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern void CpProxyUpnpOrgContentDirectory1SetPropertyContainerUpdateIDsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1PropertyTransferIDs(uint aHandle, char** aTransferIDs);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1PropertySystemUpdateID(uint aHandle, uint* aSystemUpdateID);
        [DllImport("CpUpnpOrgContentDirectory1")]
        static extern unsafe void CpProxyUpnpOrgContentDirectory1PropertyContainerUpdateIDs(uint aHandle, char** aContainerUpdateIDs);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iTransferIDsChanged;
        private CallbackPropertyChanged iSystemUpdateIDChanged;
        private CallbackPropertyChanged iContainerUpdateIDsChanged;
        private Callback iCallbackTransferIDsChanged;
        private Callback iCallbackSystemUpdateIDChanged;
        private Callback iCallbackContainerUpdateIDsChanged;

        public CpProxyUpnpOrgContentDirectory1(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgContentDirectory1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncGetSearchCapabilities(out string aSearchCaps)
        {
			char* searchCaps;
			{
				CpProxyUpnpOrgContentDirectory1SyncGetSearchCapabilities(iHandle, &searchCaps);
			}
            aSearchCaps = Marshal.PtrToStringAnsi((IntPtr)searchCaps);
            ZappFree(searchCaps);
        }

        public unsafe void BeginGetSearchCapabilities(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory1BeginGetSearchCapabilities(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetSearchCapabilities(uint aAsyncHandle, out string aSearchCaps)
        {
			char* searchCaps;
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndGetSearchCapabilities(iHandle, aAsyncHandle, &searchCaps))
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
				CpProxyUpnpOrgContentDirectory1SyncGetSortCapabilities(iHandle, &sortCaps);
			}
            aSortCaps = Marshal.PtrToStringAnsi((IntPtr)sortCaps);
            ZappFree(sortCaps);
        }

        public unsafe void BeginGetSortCapabilities(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory1BeginGetSortCapabilities(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetSortCapabilities(uint aAsyncHandle, out string aSortCaps)
        {
			char* sortCaps;
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndGetSortCapabilities(iHandle, aAsyncHandle, &sortCaps))
				{
					throw(new ProxyError());
				}
			}
            aSortCaps = Marshal.PtrToStringAnsi((IntPtr)sortCaps);
            ZappFree(sortCaps);
        }

        public unsafe void SyncGetSystemUpdateID(out uint aId)
        {
			fixed (uint* id = &aId)
			{
				CpProxyUpnpOrgContentDirectory1SyncGetSystemUpdateID(iHandle, id);
			}
        }

        public unsafe void BeginGetSystemUpdateID(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory1BeginGetSystemUpdateID(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetSystemUpdateID(uint aAsyncHandle, out uint aId)
        {
			fixed (uint* id = &aId)
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndGetSystemUpdateID(iHandle, aAsyncHandle, id))
				{
					throw(new ProxyError());
				}
			}
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
				CpProxyUpnpOrgContentDirectory1SyncBrowse(iHandle, objectID, browseFlag, filter, aStartingIndex, aRequestedCount, sortCriteria, &result, numberReturned, totalMatches, updateID);
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
            CpProxyUpnpOrgContentDirectory1BeginBrowse(iHandle, objectID, browseFlag, filter, aStartingIndex, aRequestedCount, sortCriteria, iActionComplete, ptr);
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
				if (0 != CpProxyUpnpOrgContentDirectory1EndBrowse(iHandle, aAsyncHandle, &result, numberReturned, totalMatches, updateID))
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
				CpProxyUpnpOrgContentDirectory1SyncSearch(iHandle, containerID, searchCriteria, filter, aStartingIndex, aRequestedCount, sortCriteria, &result, numberReturned, totalMatches, updateID);
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
            CpProxyUpnpOrgContentDirectory1BeginSearch(iHandle, containerID, searchCriteria, filter, aStartingIndex, aRequestedCount, sortCriteria, iActionComplete, ptr);
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
				if (0 != CpProxyUpnpOrgContentDirectory1EndSearch(iHandle, aAsyncHandle, &result, numberReturned, totalMatches, updateID))
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
				CpProxyUpnpOrgContentDirectory1SyncCreateObject(iHandle, containerID, elements, &objectID, &result);
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
            CpProxyUpnpOrgContentDirectory1BeginCreateObject(iHandle, containerID, elements, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)containerID);
			Marshal.FreeHGlobal((IntPtr)elements);
        }

        public unsafe void EndCreateObject(uint aAsyncHandle, out string aObjectID, out string aResult)
        {
			char* objectID;
			char* result;
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndCreateObject(iHandle, aAsyncHandle, &objectID, &result))
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
				CpProxyUpnpOrgContentDirectory1SyncDestroyObject(iHandle, objectID);
			}
			Marshal.FreeHGlobal((IntPtr)objectID);
        }

        public unsafe void BeginDestroyObject(string aObjectID, CallbackAsyncComplete aCallback)
        {
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory1BeginDestroyObject(iHandle, objectID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)objectID);
        }

        public unsafe void EndDestroyObject(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndDestroyObject(iHandle, aAsyncHandle))
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
				CpProxyUpnpOrgContentDirectory1SyncUpdateObject(iHandle, objectID, currentTagValue, newTagValue);
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
            CpProxyUpnpOrgContentDirectory1BeginUpdateObject(iHandle, objectID, currentTagValue, newTagValue, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)objectID);
			Marshal.FreeHGlobal((IntPtr)currentTagValue);
			Marshal.FreeHGlobal((IntPtr)newTagValue);
        }

        public unsafe void EndUpdateObject(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndUpdateObject(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncImportResource(string aSourceURI, string aDestinationURI, out uint aTransferID)
        {
			char* sourceURI = (char*)Marshal.StringToHGlobalAnsi(aSourceURI);
			char* destinationURI = (char*)Marshal.StringToHGlobalAnsi(aDestinationURI);
			fixed (uint* transferID = &aTransferID)
			{
				CpProxyUpnpOrgContentDirectory1SyncImportResource(iHandle, sourceURI, destinationURI, transferID);
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
            CpProxyUpnpOrgContentDirectory1BeginImportResource(iHandle, sourceURI, destinationURI, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)sourceURI);
			Marshal.FreeHGlobal((IntPtr)destinationURI);
        }

        public unsafe void EndImportResource(uint aAsyncHandle, out uint aTransferID)
        {
			fixed (uint* transferID = &aTransferID)
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndImportResource(iHandle, aAsyncHandle, transferID))
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
				CpProxyUpnpOrgContentDirectory1SyncExportResource(iHandle, sourceURI, destinationURI, transferID);
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
            CpProxyUpnpOrgContentDirectory1BeginExportResource(iHandle, sourceURI, destinationURI, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)sourceURI);
			Marshal.FreeHGlobal((IntPtr)destinationURI);
        }

        public unsafe void EndExportResource(uint aAsyncHandle, out uint aTransferID)
        {
			fixed (uint* transferID = &aTransferID)
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndExportResource(iHandle, aAsyncHandle, transferID))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStopTransferResource(uint aTransferID)
        {
			{
				CpProxyUpnpOrgContentDirectory1SyncStopTransferResource(iHandle, aTransferID);
			}
        }

        public unsafe void BeginStopTransferResource(uint aTransferID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory1BeginStopTransferResource(iHandle, aTransferID, iActionComplete, ptr);
        }

        public unsafe void EndStopTransferResource(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndStopTransferResource(iHandle, aAsyncHandle))
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
				CpProxyUpnpOrgContentDirectory1SyncGetTransferProgress(iHandle, aTransferID, &transferStatus, &transferLength, &transferTotal);
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
            CpProxyUpnpOrgContentDirectory1BeginGetTransferProgress(iHandle, aTransferID, iActionComplete, ptr);
        }

        public unsafe void EndGetTransferProgress(uint aAsyncHandle, out string aTransferStatus, out string aTransferLength, out string aTransferTotal)
        {
			char* transferStatus;
			char* transferLength;
			char* transferTotal;
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndGetTransferProgress(iHandle, aAsyncHandle, &transferStatus, &transferLength, &transferTotal))
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

        public unsafe void SyncDeleteResource(string aResourceURI)
        {
			char* resourceURI = (char*)Marshal.StringToHGlobalAnsi(aResourceURI);
			{
				CpProxyUpnpOrgContentDirectory1SyncDeleteResource(iHandle, resourceURI);
			}
			Marshal.FreeHGlobal((IntPtr)resourceURI);
        }

        public unsafe void BeginDeleteResource(string aResourceURI, CallbackAsyncComplete aCallback)
        {
			char* resourceURI = (char*)Marshal.StringToHGlobalAnsi(aResourceURI);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgContentDirectory1BeginDeleteResource(iHandle, resourceURI, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)resourceURI);
        }

        public unsafe void EndDeleteResource(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndDeleteResource(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncCreateReference(string aContainerID, string aObjectID, out string aNewID)
        {
			char* containerID = (char*)Marshal.StringToHGlobalAnsi(aContainerID);
			char* objectID = (char*)Marshal.StringToHGlobalAnsi(aObjectID);
			char* newID;
			{
				CpProxyUpnpOrgContentDirectory1SyncCreateReference(iHandle, containerID, objectID, &newID);
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
            CpProxyUpnpOrgContentDirectory1BeginCreateReference(iHandle, containerID, objectID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)containerID);
			Marshal.FreeHGlobal((IntPtr)objectID);
        }

        public unsafe void EndCreateReference(uint aAsyncHandle, out string aNewID)
        {
			char* newID;
			{
				if (0 != CpProxyUpnpOrgContentDirectory1EndCreateReference(iHandle, aAsyncHandle, &newID))
				{
					throw(new ProxyError());
				}
			}
            aNewID = Marshal.PtrToStringAnsi((IntPtr)newID);
            ZappFree(newID);
        }

        public void SetPropertyTransferIDsChanged(CallbackPropertyChanged aTransferIDsChanged)
        {
            iTransferIDsChanged = aTransferIDsChanged;
            iCallbackTransferIDsChanged = new Callback(PropertyTransferIDsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgContentDirectory1SetPropertyTransferIDsChanged(iHandle, iCallbackTransferIDsChanged, ptr);
        }

        private void PropertyTransferIDsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgContentDirectory1 self = (CpProxyUpnpOrgContentDirectory1)gch.Target;
            self.iTransferIDsChanged();
        }

        public void SetPropertySystemUpdateIDChanged(CallbackPropertyChanged aSystemUpdateIDChanged)
        {
            iSystemUpdateIDChanged = aSystemUpdateIDChanged;
            iCallbackSystemUpdateIDChanged = new Callback(PropertySystemUpdateIDChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgContentDirectory1SetPropertySystemUpdateIDChanged(iHandle, iCallbackSystemUpdateIDChanged, ptr);
        }

        private void PropertySystemUpdateIDChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgContentDirectory1 self = (CpProxyUpnpOrgContentDirectory1)gch.Target;
            self.iSystemUpdateIDChanged();
        }

        public void SetPropertyContainerUpdateIDsChanged(CallbackPropertyChanged aContainerUpdateIDsChanged)
        {
            iContainerUpdateIDsChanged = aContainerUpdateIDsChanged;
            iCallbackContainerUpdateIDsChanged = new Callback(PropertyContainerUpdateIDsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgContentDirectory1SetPropertyContainerUpdateIDsChanged(iHandle, iCallbackContainerUpdateIDsChanged, ptr);
        }

        private void PropertyContainerUpdateIDsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgContentDirectory1 self = (CpProxyUpnpOrgContentDirectory1)gch.Target;
            self.iContainerUpdateIDsChanged();
        }

        public unsafe void PropertyTransferIDs(out string aTransferIDs)
        {
			char* ptr;
            CpProxyUpnpOrgContentDirectory1PropertyTransferIDs(iHandle, &ptr);
            aTransferIDs = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertySystemUpdateID(out uint aSystemUpdateID)
        {
			fixed (uint* systemUpdateID = &aSystemUpdateID)
			{
	            CpProxyUpnpOrgContentDirectory1PropertySystemUpdateID(iHandle, systemUpdateID);
			}
        }

        public unsafe void PropertyContainerUpdateIDs(out string aContainerUpdateIDs)
        {
			char* ptr;
            CpProxyUpnpOrgContentDirectory1PropertyContainerUpdateIDs(iHandle, &ptr);
            aContainerUpdateIDs = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgContentDirectory1()
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
            CpProxyUpnpOrgContentDirectory1Destroy(handle);
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

