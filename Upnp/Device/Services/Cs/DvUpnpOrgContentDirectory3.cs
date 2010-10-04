using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceUpnpOrgContentDirectory3 : IDisposable
    {
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern uint DvServiceUpnpOrgContentDirectory3Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3Destroy(uint aHandle);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern unsafe int DvServiceUpnpOrgContentDirectory3SetPropertySystemUpdateID(uint aHandle, uint aValue);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern unsafe void DvServiceUpnpOrgContentDirectory3GetPropertySystemUpdateID(uint aHandle, uint* aValue);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern unsafe int DvServiceUpnpOrgContentDirectory3SetPropertyContainerUpdateIDs(uint aHandle, char* aValue);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern unsafe void DvServiceUpnpOrgContentDirectory3GetPropertyContainerUpdateIDs(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern unsafe int DvServiceUpnpOrgContentDirectory3SetPropertyLastChange(uint aHandle, char* aValue);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern unsafe void DvServiceUpnpOrgContentDirectory3GetPropertyLastChange(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern unsafe int DvServiceUpnpOrgContentDirectory3SetPropertyTransferIDs(uint aHandle, char* aValue);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern unsafe void DvServiceUpnpOrgContentDirectory3GetPropertyTransferIDs(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionGetSearchCapabilities(uint aHandle, CallbackGetSearchCapabilities aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionGetSortCapabilities(uint aHandle, CallbackGetSortCapabilities aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionGetSortExtensionCapabilities(uint aHandle, CallbackGetSortExtensionCapabilities aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionGetFeatureList(uint aHandle, CallbackGetFeatureList aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionGetSystemUpdateID(uint aHandle, CallbackGetSystemUpdateID aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionGetServiceResetToken(uint aHandle, CallbackGetServiceResetToken aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionBrowse(uint aHandle, CallbackBrowse aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionSearch(uint aHandle, CallbackSearch aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionCreateObject(uint aHandle, CallbackCreateObject aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionDestroyObject(uint aHandle, CallbackDestroyObject aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionUpdateObject(uint aHandle, CallbackUpdateObject aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionMoveObject(uint aHandle, CallbackMoveObject aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionImportResource(uint aHandle, CallbackImportResource aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionExportResource(uint aHandle, CallbackExportResource aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionDeleteResource(uint aHandle, CallbackDeleteResource aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionStopTransferResource(uint aHandle, CallbackStopTransferResource aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionGetTransferProgress(uint aHandle, CallbackGetTransferProgress aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionCreateReference(uint aHandle, CallbackCreateReference aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionFreeFormQuery(uint aHandle, CallbackFreeFormQuery aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgContentDirectory3")]
        static extern void DvServiceUpnpOrgContentDirectory3EnableActionGetFreeFormQueryCapabilities(uint aHandle, CallbackGetFreeFormQueryCapabilities aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackGetSearchCapabilities(IntPtr aPtr, uint aVersion, char** aSearchCaps);
        private unsafe delegate int CallbackGetSortCapabilities(IntPtr aPtr, uint aVersion, char** aSortCaps);
        private unsafe delegate int CallbackGetSortExtensionCapabilities(IntPtr aPtr, uint aVersion, char** aSortExtensionCaps);
        private unsafe delegate int CallbackGetFeatureList(IntPtr aPtr, uint aVersion, char** aFeatureList);
        private unsafe delegate int CallbackGetSystemUpdateID(IntPtr aPtr, uint aVersion, uint* aId);
        private unsafe delegate int CallbackGetServiceResetToken(IntPtr aPtr, uint aVersion, char** aResetToken);
        private unsafe delegate int CallbackBrowse(IntPtr aPtr, uint aVersion, char* aObjectID, char* aBrowseFlag, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        private unsafe delegate int CallbackSearch(IntPtr aPtr, uint aVersion, char* aContainerID, char* aSearchCriteria, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        private unsafe delegate int CallbackCreateObject(IntPtr aPtr, uint aVersion, char* aContainerID, char* aElements, char** aObjectID, char** aResult);
        private unsafe delegate int CallbackDestroyObject(IntPtr aPtr, uint aVersion, char* aObjectID);
        private unsafe delegate int CallbackUpdateObject(IntPtr aPtr, uint aVersion, char* aObjectID, char* aCurrentTagValue, char* aNewTagValue);
        private unsafe delegate int CallbackMoveObject(IntPtr aPtr, uint aVersion, char* aObjectID, char* aNewParentID, char** aNewObjectID);
        private unsafe delegate int CallbackImportResource(IntPtr aPtr, uint aVersion, char* aSourceURI, char* aDestinationURI, uint* aTransferID);
        private unsafe delegate int CallbackExportResource(IntPtr aPtr, uint aVersion, char* aSourceURI, char* aDestinationURI, uint* aTransferID);
        private unsafe delegate int CallbackDeleteResource(IntPtr aPtr, uint aVersion, char* aResourceURI);
        private unsafe delegate int CallbackStopTransferResource(IntPtr aPtr, uint aVersion, uint aTransferID);
        private unsafe delegate int CallbackGetTransferProgress(IntPtr aPtr, uint aVersion, uint aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
        private unsafe delegate int CallbackCreateReference(IntPtr aPtr, uint aVersion, char* aContainerID, char* aObjectID, char** aNewID);
        private unsafe delegate int CallbackFreeFormQuery(IntPtr aPtr, uint aVersion, char* aContainerID, uint aCDSView, char* aQueryRequest, char** aQueryResult, uint* aUpdateID);
        private unsafe delegate int CallbackGetFreeFormQueryCapabilities(IntPtr aPtr, uint aVersion, char** aFFQCapabilities);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackGetSearchCapabilities iCallbackGetSearchCapabilities;
        private CallbackGetSortCapabilities iCallbackGetSortCapabilities;
        private CallbackGetSortExtensionCapabilities iCallbackGetSortExtensionCapabilities;
        private CallbackGetFeatureList iCallbackGetFeatureList;
        private CallbackGetSystemUpdateID iCallbackGetSystemUpdateID;
        private CallbackGetServiceResetToken iCallbackGetServiceResetToken;
        private CallbackBrowse iCallbackBrowse;
        private CallbackSearch iCallbackSearch;
        private CallbackCreateObject iCallbackCreateObject;
        private CallbackDestroyObject iCallbackDestroyObject;
        private CallbackUpdateObject iCallbackUpdateObject;
        private CallbackMoveObject iCallbackMoveObject;
        private CallbackImportResource iCallbackImportResource;
        private CallbackExportResource iCallbackExportResource;
        private CallbackDeleteResource iCallbackDeleteResource;
        private CallbackStopTransferResource iCallbackStopTransferResource;
        private CallbackGetTransferProgress iCallbackGetTransferProgress;
        private CallbackCreateReference iCallbackCreateReference;
        private CallbackFreeFormQuery iCallbackFreeFormQuery;
        private CallbackGetFreeFormQueryCapabilities iCallbackGetFreeFormQueryCapabilities;

        public DvServiceUpnpOrgContentDirectory3(DvDevice aDevice)
        {
            iHandle = DvServiceUpnpOrgContentDirectory3Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertySystemUpdateID(uint aValue)
        {
            if (0 != DvServiceUpnpOrgContentDirectory3SetPropertySystemUpdateID(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertySystemUpdateID(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceUpnpOrgContentDirectory3GetPropertySystemUpdateID(iHandle, value);
            }
        }

        public unsafe void SetPropertyContainerUpdateIDs(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceUpnpOrgContentDirectory3SetPropertyContainerUpdateIDs(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyContainerUpdateIDs(out string aValue)
        {
            char* value;
            DvServiceUpnpOrgContentDirectory3GetPropertyContainerUpdateIDs(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyLastChange(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceUpnpOrgContentDirectory3SetPropertyLastChange(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyLastChange(out string aValue)
        {
            char* value;
            DvServiceUpnpOrgContentDirectory3GetPropertyLastChange(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyTransferIDs(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceUpnpOrgContentDirectory3SetPropertyTransferIDs(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyTransferIDs(out string aValue)
        {
            char* value;
            DvServiceUpnpOrgContentDirectory3GetPropertyTransferIDs(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionGetSearchCapabilities()
        {
            iCallbackGetSearchCapabilities = new CallbackGetSearchCapabilities(DoGetSearchCapabilities);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionGetSearchCapabilities(iHandle, iCallbackGetSearchCapabilities, ptr);
        }

        protected unsafe void EnableActionGetSortCapabilities()
        {
            iCallbackGetSortCapabilities = new CallbackGetSortCapabilities(DoGetSortCapabilities);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionGetSortCapabilities(iHandle, iCallbackGetSortCapabilities, ptr);
        }

        protected unsafe void EnableActionGetSortExtensionCapabilities()
        {
            iCallbackGetSortExtensionCapabilities = new CallbackGetSortExtensionCapabilities(DoGetSortExtensionCapabilities);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionGetSortExtensionCapabilities(iHandle, iCallbackGetSortExtensionCapabilities, ptr);
        }

        protected unsafe void EnableActionGetFeatureList()
        {
            iCallbackGetFeatureList = new CallbackGetFeatureList(DoGetFeatureList);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionGetFeatureList(iHandle, iCallbackGetFeatureList, ptr);
        }

        protected unsafe void EnableActionGetSystemUpdateID()
        {
            iCallbackGetSystemUpdateID = new CallbackGetSystemUpdateID(DoGetSystemUpdateID);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionGetSystemUpdateID(iHandle, iCallbackGetSystemUpdateID, ptr);
        }

        protected unsafe void EnableActionGetServiceResetToken()
        {
            iCallbackGetServiceResetToken = new CallbackGetServiceResetToken(DoGetServiceResetToken);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionGetServiceResetToken(iHandle, iCallbackGetServiceResetToken, ptr);
        }

        protected unsafe void EnableActionBrowse()
        {
            iCallbackBrowse = new CallbackBrowse(DoBrowse);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionBrowse(iHandle, iCallbackBrowse, ptr);
        }

        protected unsafe void EnableActionSearch()
        {
            iCallbackSearch = new CallbackSearch(DoSearch);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionSearch(iHandle, iCallbackSearch, ptr);
        }

        protected unsafe void EnableActionCreateObject()
        {
            iCallbackCreateObject = new CallbackCreateObject(DoCreateObject);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionCreateObject(iHandle, iCallbackCreateObject, ptr);
        }

        protected unsafe void EnableActionDestroyObject()
        {
            iCallbackDestroyObject = new CallbackDestroyObject(DoDestroyObject);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionDestroyObject(iHandle, iCallbackDestroyObject, ptr);
        }

        protected unsafe void EnableActionUpdateObject()
        {
            iCallbackUpdateObject = new CallbackUpdateObject(DoUpdateObject);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionUpdateObject(iHandle, iCallbackUpdateObject, ptr);
        }

        protected unsafe void EnableActionMoveObject()
        {
            iCallbackMoveObject = new CallbackMoveObject(DoMoveObject);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionMoveObject(iHandle, iCallbackMoveObject, ptr);
        }

        protected unsafe void EnableActionImportResource()
        {
            iCallbackImportResource = new CallbackImportResource(DoImportResource);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionImportResource(iHandle, iCallbackImportResource, ptr);
        }

        protected unsafe void EnableActionExportResource()
        {
            iCallbackExportResource = new CallbackExportResource(DoExportResource);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionExportResource(iHandle, iCallbackExportResource, ptr);
        }

        protected unsafe void EnableActionDeleteResource()
        {
            iCallbackDeleteResource = new CallbackDeleteResource(DoDeleteResource);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionDeleteResource(iHandle, iCallbackDeleteResource, ptr);
        }

        protected unsafe void EnableActionStopTransferResource()
        {
            iCallbackStopTransferResource = new CallbackStopTransferResource(DoStopTransferResource);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionStopTransferResource(iHandle, iCallbackStopTransferResource, ptr);
        }

        protected unsafe void EnableActionGetTransferProgress()
        {
            iCallbackGetTransferProgress = new CallbackGetTransferProgress(DoGetTransferProgress);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionGetTransferProgress(iHandle, iCallbackGetTransferProgress, ptr);
        }

        protected unsafe void EnableActionCreateReference()
        {
            iCallbackCreateReference = new CallbackCreateReference(DoCreateReference);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionCreateReference(iHandle, iCallbackCreateReference, ptr);
        }

        protected unsafe void EnableActionFreeFormQuery()
        {
            iCallbackFreeFormQuery = new CallbackFreeFormQuery(DoFreeFormQuery);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionFreeFormQuery(iHandle, iCallbackFreeFormQuery, ptr);
        }

        protected unsafe void EnableActionGetFreeFormQueryCapabilities()
        {
            iCallbackGetFreeFormQueryCapabilities = new CallbackGetFreeFormQueryCapabilities(DoGetFreeFormQueryCapabilities);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgContentDirectory3EnableActionGetFreeFormQueryCapabilities(iHandle, iCallbackGetFreeFormQueryCapabilities, ptr);
        }

        protected virtual void GetSearchCapabilities(uint aVersion, out string aSearchCaps)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetSortCapabilities(uint aVersion, out string aSortCaps)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetSortExtensionCapabilities(uint aVersion, out string aSortExtensionCaps)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetFeatureList(uint aVersion, out string aFeatureList)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetSystemUpdateID(uint aVersion, out uint aId)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetServiceResetToken(uint aVersion, out string aResetToken)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Browse(uint aVersion, string aObjectID, string aBrowseFlag, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Search(uint aVersion, string aContainerID, string aSearchCriteria, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void CreateObject(uint aVersion, string aContainerID, string aElements, out string aObjectID, out string aResult)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DestroyObject(uint aVersion, string aObjectID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void UpdateObject(uint aVersion, string aObjectID, string aCurrentTagValue, string aNewTagValue)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void MoveObject(uint aVersion, string aObjectID, string aNewParentID, out string aNewObjectID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void ImportResource(uint aVersion, string aSourceURI, string aDestinationURI, out uint aTransferID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void ExportResource(uint aVersion, string aSourceURI, string aDestinationURI, out uint aTransferID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DeleteResource(uint aVersion, string aResourceURI)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StopTransferResource(uint aVersion, uint aTransferID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetTransferProgress(uint aVersion, uint aTransferID, out string aTransferStatus, out string aTransferLength, out string aTransferTotal)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void CreateReference(uint aVersion, string aContainerID, string aObjectID, out string aNewID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void FreeFormQuery(uint aVersion, string aContainerID, uint aCDSView, string aQueryRequest, out string aQueryResult, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetFreeFormQueryCapabilities(uint aVersion, out string aFFQCapabilities)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoGetSearchCapabilities(IntPtr aPtr, uint aVersion, char** aSearchCaps)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string searchCaps;
            self.GetSearchCapabilities(aVersion, out searchCaps);
            *aSearchCaps = (char*)Marshal.StringToHGlobalAnsi(searchCaps).ToPointer();
            return 0;
        }

        private static unsafe int DoGetSortCapabilities(IntPtr aPtr, uint aVersion, char** aSortCaps)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string sortCaps;
            self.GetSortCapabilities(aVersion, out sortCaps);
            *aSortCaps = (char*)Marshal.StringToHGlobalAnsi(sortCaps).ToPointer();
            return 0;
        }

        private static unsafe int DoGetSortExtensionCapabilities(IntPtr aPtr, uint aVersion, char** aSortExtensionCaps)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string sortExtensionCaps;
            self.GetSortExtensionCapabilities(aVersion, out sortExtensionCaps);
            *aSortExtensionCaps = (char*)Marshal.StringToHGlobalAnsi(sortExtensionCaps).ToPointer();
            return 0;
        }

        private static unsafe int DoGetFeatureList(IntPtr aPtr, uint aVersion, char** aFeatureList)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string featureList;
            self.GetFeatureList(aVersion, out featureList);
            *aFeatureList = (char*)Marshal.StringToHGlobalAnsi(featureList).ToPointer();
            return 0;
        }

        private static unsafe int DoGetSystemUpdateID(IntPtr aPtr, uint aVersion, uint* aId)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            uint id;
            self.GetSystemUpdateID(aVersion, out id);
            *aId = id;
            return 0;
        }

        private static unsafe int DoGetServiceResetToken(IntPtr aPtr, uint aVersion, char** aResetToken)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string resetToken;
            self.GetServiceResetToken(aVersion, out resetToken);
            *aResetToken = (char*)Marshal.StringToHGlobalAnsi(resetToken).ToPointer();
            return 0;
        }

        private static unsafe int DoBrowse(IntPtr aPtr, uint aVersion, char* aObjectID, char* aBrowseFlag, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string objectID = Marshal.PtrToStringAnsi((IntPtr)aObjectID);
            string browseFlag = Marshal.PtrToStringAnsi((IntPtr)aBrowseFlag);
            string filter = Marshal.PtrToStringAnsi((IntPtr)aFilter);
            string sortCriteria = Marshal.PtrToStringAnsi((IntPtr)aSortCriteria);
            string result;
            uint numberReturned;
            uint totalMatches;
            uint updateID;
            self.Browse(aVersion, objectID, browseFlag, filter, aStartingIndex, aRequestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            *aResult = (char*)Marshal.StringToHGlobalAnsi(result).ToPointer();
            *aNumberReturned = numberReturned;
            *aTotalMatches = totalMatches;
            *aUpdateID = updateID;
            return 0;
        }

        private static unsafe int DoSearch(IntPtr aPtr, uint aVersion, char* aContainerID, char* aSearchCriteria, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string containerID = Marshal.PtrToStringAnsi((IntPtr)aContainerID);
            string searchCriteria = Marshal.PtrToStringAnsi((IntPtr)aSearchCriteria);
            string filter = Marshal.PtrToStringAnsi((IntPtr)aFilter);
            string sortCriteria = Marshal.PtrToStringAnsi((IntPtr)aSortCriteria);
            string result;
            uint numberReturned;
            uint totalMatches;
            uint updateID;
            self.Search(aVersion, containerID, searchCriteria, filter, aStartingIndex, aRequestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            *aResult = (char*)Marshal.StringToHGlobalAnsi(result).ToPointer();
            *aNumberReturned = numberReturned;
            *aTotalMatches = totalMatches;
            *aUpdateID = updateID;
            return 0;
        }

        private static unsafe int DoCreateObject(IntPtr aPtr, uint aVersion, char* aContainerID, char* aElements, char** aObjectID, char** aResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string containerID = Marshal.PtrToStringAnsi((IntPtr)aContainerID);
            string elements = Marshal.PtrToStringAnsi((IntPtr)aElements);
            string objectID;
            string result;
            self.CreateObject(aVersion, containerID, elements, out objectID, out result);
            *aObjectID = (char*)Marshal.StringToHGlobalAnsi(objectID).ToPointer();
            *aResult = (char*)Marshal.StringToHGlobalAnsi(result).ToPointer();
            return 0;
        }

        private static unsafe int DoDestroyObject(IntPtr aPtr, uint aVersion, char* aObjectID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string objectID = Marshal.PtrToStringAnsi((IntPtr)aObjectID);
            self.DestroyObject(aVersion, objectID);
            return 0;
        }

        private static unsafe int DoUpdateObject(IntPtr aPtr, uint aVersion, char* aObjectID, char* aCurrentTagValue, char* aNewTagValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string objectID = Marshal.PtrToStringAnsi((IntPtr)aObjectID);
            string currentTagValue = Marshal.PtrToStringAnsi((IntPtr)aCurrentTagValue);
            string newTagValue = Marshal.PtrToStringAnsi((IntPtr)aNewTagValue);
            self.UpdateObject(aVersion, objectID, currentTagValue, newTagValue);
            return 0;
        }

        private static unsafe int DoMoveObject(IntPtr aPtr, uint aVersion, char* aObjectID, char* aNewParentID, char** aNewObjectID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string objectID = Marshal.PtrToStringAnsi((IntPtr)aObjectID);
            string newParentID = Marshal.PtrToStringAnsi((IntPtr)aNewParentID);
            string newObjectID;
            self.MoveObject(aVersion, objectID, newParentID, out newObjectID);
            *aNewObjectID = (char*)Marshal.StringToHGlobalAnsi(newObjectID).ToPointer();
            return 0;
        }

        private static unsafe int DoImportResource(IntPtr aPtr, uint aVersion, char* aSourceURI, char* aDestinationURI, uint* aTransferID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string sourceURI = Marshal.PtrToStringAnsi((IntPtr)aSourceURI);
            string destinationURI = Marshal.PtrToStringAnsi((IntPtr)aDestinationURI);
            uint transferID;
            self.ImportResource(aVersion, sourceURI, destinationURI, out transferID);
            *aTransferID = transferID;
            return 0;
        }

        private static unsafe int DoExportResource(IntPtr aPtr, uint aVersion, char* aSourceURI, char* aDestinationURI, uint* aTransferID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string sourceURI = Marshal.PtrToStringAnsi((IntPtr)aSourceURI);
            string destinationURI = Marshal.PtrToStringAnsi((IntPtr)aDestinationURI);
            uint transferID;
            self.ExportResource(aVersion, sourceURI, destinationURI, out transferID);
            *aTransferID = transferID;
            return 0;
        }

        private static unsafe int DoDeleteResource(IntPtr aPtr, uint aVersion, char* aResourceURI)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string resourceURI = Marshal.PtrToStringAnsi((IntPtr)aResourceURI);
            self.DeleteResource(aVersion, resourceURI);
            return 0;
        }

        private static unsafe int DoStopTransferResource(IntPtr aPtr, uint aVersion, uint aTransferID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            self.StopTransferResource(aVersion, aTransferID);
            return 0;
        }

        private static unsafe int DoGetTransferProgress(IntPtr aPtr, uint aVersion, uint aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string transferStatus;
            string transferLength;
            string transferTotal;
            self.GetTransferProgress(aVersion, aTransferID, out transferStatus, out transferLength, out transferTotal);
            *aTransferStatus = (char*)Marshal.StringToHGlobalAnsi(transferStatus).ToPointer();
            *aTransferLength = (char*)Marshal.StringToHGlobalAnsi(transferLength).ToPointer();
            *aTransferTotal = (char*)Marshal.StringToHGlobalAnsi(transferTotal).ToPointer();
            return 0;
        }

        private static unsafe int DoCreateReference(IntPtr aPtr, uint aVersion, char* aContainerID, char* aObjectID, char** aNewID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string containerID = Marshal.PtrToStringAnsi((IntPtr)aContainerID);
            string objectID = Marshal.PtrToStringAnsi((IntPtr)aObjectID);
            string newID;
            self.CreateReference(aVersion, containerID, objectID, out newID);
            *aNewID = (char*)Marshal.StringToHGlobalAnsi(newID).ToPointer();
            return 0;
        }

        private static unsafe int DoFreeFormQuery(IntPtr aPtr, uint aVersion, char* aContainerID, uint aCDSView, char* aQueryRequest, char** aQueryResult, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string containerID = Marshal.PtrToStringAnsi((IntPtr)aContainerID);
            string queryRequest = Marshal.PtrToStringAnsi((IntPtr)aQueryRequest);
            string queryResult;
            uint updateID;
            self.FreeFormQuery(aVersion, containerID, aCDSView, queryRequest, out queryResult, out updateID);
            *aQueryResult = (char*)Marshal.StringToHGlobalAnsi(queryResult).ToPointer();
            *aUpdateID = updateID;
            return 0;
        }

        private static unsafe int DoGetFreeFormQueryCapabilities(IntPtr aPtr, uint aVersion, char** aFFQCapabilities)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgContentDirectory3 self = (DvServiceUpnpOrgContentDirectory3)gch.Target;
            string fFQCapabilities;
            self.GetFreeFormQueryCapabilities(aVersion, out fFQCapabilities);
            *aFFQCapabilities = (char*)Marshal.StringToHGlobalAnsi(fFQCapabilities).ToPointer();
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceUpnpOrgContentDirectory3()
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
            DvServiceUpnpOrgContentDirectory3Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

