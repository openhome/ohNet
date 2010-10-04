using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyUpnpOrgScheduledRecording2 : CpProxy, IDisposable
    {
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern uint CpProxyUpnpOrgScheduledRecording2Create(uint aDeviceHandle);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern void CpProxyUpnpOrgScheduledRecording2Destroy(uint aHandle);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncGetSortCapabilities(uint aHandle, char** aSortCaps, uint* aSortLevelCap);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginGetSortCapabilities(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndGetSortCapabilities(uint aHandle, uint aAsync, char** aSortCaps, uint* aSortLevelCap);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncGetPropertyList(uint aHandle, char* aDataTypeID, char** aPropertyList);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginGetPropertyList(uint aHandle, char* aDataTypeID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndGetPropertyList(uint aHandle, uint aAsync, char** aPropertyList);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncGetAllowedValues(uint aHandle, char* aDataTypeID, char* aFilter, char** aPropertyInfo);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginGetAllowedValues(uint aHandle, char* aDataTypeID, char* aFilter, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndGetAllowedValues(uint aHandle, uint aAsync, char** aPropertyInfo);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncGetStateUpdateID(uint aHandle, uint* aId);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginGetStateUpdateID(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndGetStateUpdateID(uint aHandle, uint aAsync, uint* aId);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncBrowseRecordSchedules(uint aHandle, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginBrowseRecordSchedules(uint aHandle, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndBrowseRecordSchedules(uint aHandle, uint aAsync, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncBrowseRecordTasks(uint aHandle, char* aRecordScheduleID, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginBrowseRecordTasks(uint aHandle, char* aRecordScheduleID, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndBrowseRecordTasks(uint aHandle, uint aAsync, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncCreateRecordSchedule(uint aHandle, char* aElements, char** aRecordScheduleID, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginCreateRecordSchedule(uint aHandle, char* aElements, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndCreateRecordSchedule(uint aHandle, uint aAsync, char** aRecordScheduleID, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncDeleteRecordSchedule(uint aHandle, char* aRecordScheduleID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginDeleteRecordSchedule(uint aHandle, char* aRecordScheduleID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndDeleteRecordSchedule(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncGetRecordSchedule(uint aHandle, char* aRecordScheduleID, char* aFilter, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginGetRecordSchedule(uint aHandle, char* aRecordScheduleID, char* aFilter, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndGetRecordSchedule(uint aHandle, uint aAsync, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncEnableRecordSchedule(uint aHandle, char* aRecordScheduleID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginEnableRecordSchedule(uint aHandle, char* aRecordScheduleID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndEnableRecordSchedule(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncDisableRecordSchedule(uint aHandle, char* aRecordScheduleID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginDisableRecordSchedule(uint aHandle, char* aRecordScheduleID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndDisableRecordSchedule(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncDeleteRecordTask(uint aHandle, char* aRecordTaskID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginDeleteRecordTask(uint aHandle, char* aRecordTaskID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndDeleteRecordTask(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncGetRecordTask(uint aHandle, char* aRecordTaskID, char* aFilter, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginGetRecordTask(uint aHandle, char* aRecordTaskID, char* aFilter, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndGetRecordTask(uint aHandle, uint aAsync, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncEnableRecordTask(uint aHandle, char* aRecordTaskID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginEnableRecordTask(uint aHandle, char* aRecordTaskID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndEnableRecordTask(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncDisableRecordTask(uint aHandle, char* aRecordTaskID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginDisableRecordTask(uint aHandle, char* aRecordTaskID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndDisableRecordTask(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncResetRecordTask(uint aHandle, char* aRecordTaskID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginResetRecordTask(uint aHandle, char* aRecordTaskID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndResetRecordTask(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncGetRecordScheduleConflicts(uint aHandle, char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginGetRecordScheduleConflicts(uint aHandle, char* aRecordScheduleID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndGetRecordScheduleConflicts(uint aHandle, uint aAsync, char** aRecordScheduleConflictIDList, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2SyncGetRecordTaskConflicts(uint aHandle, char* aRecordTaskID, char** aRecordTaskConflictIDList, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2BeginGetRecordTaskConflicts(uint aHandle, char* aRecordTaskID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording2EndGetRecordTaskConflicts(uint aHandle, uint aAsync, char** aRecordTaskConflictIDList, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern void CpProxyUpnpOrgScheduledRecording2SetPropertyLastChangeChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording2")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording2PropertyLastChange(uint aHandle, char** aLastChange);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iLastChangeChanged;
        private Callback iCallbackLastChangeChanged;

        public CpProxyUpnpOrgScheduledRecording2(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgScheduledRecording2Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncGetSortCapabilities(out string aSortCaps, out uint aSortLevelCap)
        {
			char* sortCaps;
			fixed (uint* sortLevelCap = &aSortLevelCap)
			{
				CpProxyUpnpOrgScheduledRecording2SyncGetSortCapabilities(iHandle, &sortCaps, sortLevelCap);
			}
            aSortCaps = Marshal.PtrToStringAnsi((IntPtr)sortCaps);
            ZappFree(sortCaps);
        }

        public unsafe void BeginGetSortCapabilities(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginGetSortCapabilities(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetSortCapabilities(uint aAsyncHandle, out string aSortCaps, out uint aSortLevelCap)
        {
			char* sortCaps;
			fixed (uint* sortLevelCap = &aSortLevelCap)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndGetSortCapabilities(iHandle, aAsyncHandle, &sortCaps, sortLevelCap))
				{
					throw(new ProxyError());
				}
			}
            aSortCaps = Marshal.PtrToStringAnsi((IntPtr)sortCaps);
            ZappFree(sortCaps);
        }

        public unsafe void SyncGetPropertyList(string aDataTypeID, out string aPropertyList)
        {
			char* dataTypeID = (char*)Marshal.StringToHGlobalAnsi(aDataTypeID);
			char* propertyList;
			{
				CpProxyUpnpOrgScheduledRecording2SyncGetPropertyList(iHandle, dataTypeID, &propertyList);
			}
			Marshal.FreeHGlobal((IntPtr)dataTypeID);
            aPropertyList = Marshal.PtrToStringAnsi((IntPtr)propertyList);
            ZappFree(propertyList);
        }

        public unsafe void BeginGetPropertyList(string aDataTypeID, CallbackAsyncComplete aCallback)
        {
			char* dataTypeID = (char*)Marshal.StringToHGlobalAnsi(aDataTypeID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginGetPropertyList(iHandle, dataTypeID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)dataTypeID);
        }

        public unsafe void EndGetPropertyList(uint aAsyncHandle, out string aPropertyList)
        {
			char* propertyList;
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndGetPropertyList(iHandle, aAsyncHandle, &propertyList))
				{
					throw(new ProxyError());
				}
			}
            aPropertyList = Marshal.PtrToStringAnsi((IntPtr)propertyList);
            ZappFree(propertyList);
        }

        public unsafe void SyncGetAllowedValues(string aDataTypeID, string aFilter, out string aPropertyInfo)
        {
			char* dataTypeID = (char*)Marshal.StringToHGlobalAnsi(aDataTypeID);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
			char* propertyInfo;
			{
				CpProxyUpnpOrgScheduledRecording2SyncGetAllowedValues(iHandle, dataTypeID, filter, &propertyInfo);
			}
			Marshal.FreeHGlobal((IntPtr)dataTypeID);
			Marshal.FreeHGlobal((IntPtr)filter);
            aPropertyInfo = Marshal.PtrToStringAnsi((IntPtr)propertyInfo);
            ZappFree(propertyInfo);
        }

        public unsafe void BeginGetAllowedValues(string aDataTypeID, string aFilter, CallbackAsyncComplete aCallback)
        {
			char* dataTypeID = (char*)Marshal.StringToHGlobalAnsi(aDataTypeID);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginGetAllowedValues(iHandle, dataTypeID, filter, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)dataTypeID);
			Marshal.FreeHGlobal((IntPtr)filter);
        }

        public unsafe void EndGetAllowedValues(uint aAsyncHandle, out string aPropertyInfo)
        {
			char* propertyInfo;
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndGetAllowedValues(iHandle, aAsyncHandle, &propertyInfo))
				{
					throw(new ProxyError());
				}
			}
            aPropertyInfo = Marshal.PtrToStringAnsi((IntPtr)propertyInfo);
            ZappFree(propertyInfo);
        }

        public unsafe void SyncGetStateUpdateID(out uint aId)
        {
			fixed (uint* id = &aId)
			{
				CpProxyUpnpOrgScheduledRecording2SyncGetStateUpdateID(iHandle, id);
			}
        }

        public unsafe void BeginGetStateUpdateID(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginGetStateUpdateID(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetStateUpdateID(uint aAsyncHandle, out uint aId)
        {
			fixed (uint* id = &aId)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndGetStateUpdateID(iHandle, aAsyncHandle, id))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncBrowseRecordSchedules(string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
			char* sortCriteria = (char*)Marshal.StringToHGlobalAnsi(aSortCriteria);
			char* result;
			fixed (uint* numberReturned = &aNumberReturned)
			fixed (uint* totalMatches = &aTotalMatches)
			fixed (uint* updateID = &aUpdateID)
			{
				CpProxyUpnpOrgScheduledRecording2SyncBrowseRecordSchedules(iHandle, filter, aStartingIndex, aRequestedCount, sortCriteria, &result, numberReturned, totalMatches, updateID);
			}
			Marshal.FreeHGlobal((IntPtr)filter);
			Marshal.FreeHGlobal((IntPtr)sortCriteria);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void BeginBrowseRecordSchedules(string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, CallbackAsyncComplete aCallback)
        {
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
			char* sortCriteria = (char*)Marshal.StringToHGlobalAnsi(aSortCriteria);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginBrowseRecordSchedules(iHandle, filter, aStartingIndex, aRequestedCount, sortCriteria, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)filter);
			Marshal.FreeHGlobal((IntPtr)sortCriteria);
        }

        public unsafe void EndBrowseRecordSchedules(uint aAsyncHandle, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
			char* result;
			fixed (uint* numberReturned = &aNumberReturned)
			fixed (uint* totalMatches = &aTotalMatches)
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndBrowseRecordSchedules(iHandle, aAsyncHandle, &result, numberReturned, totalMatches, updateID))
				{
					throw(new ProxyError());
				}
			}
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void SyncBrowseRecordTasks(string aRecordScheduleID, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
			char* sortCriteria = (char*)Marshal.StringToHGlobalAnsi(aSortCriteria);
			char* result;
			fixed (uint* numberReturned = &aNumberReturned)
			fixed (uint* totalMatches = &aTotalMatches)
			fixed (uint* updateID = &aUpdateID)
			{
				CpProxyUpnpOrgScheduledRecording2SyncBrowseRecordTasks(iHandle, recordScheduleID, filter, aStartingIndex, aRequestedCount, sortCriteria, &result, numberReturned, totalMatches, updateID);
			}
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
			Marshal.FreeHGlobal((IntPtr)filter);
			Marshal.FreeHGlobal((IntPtr)sortCriteria);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void BeginBrowseRecordTasks(string aRecordScheduleID, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, CallbackAsyncComplete aCallback)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
			char* sortCriteria = (char*)Marshal.StringToHGlobalAnsi(aSortCriteria);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginBrowseRecordTasks(iHandle, recordScheduleID, filter, aStartingIndex, aRequestedCount, sortCriteria, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
			Marshal.FreeHGlobal((IntPtr)filter);
			Marshal.FreeHGlobal((IntPtr)sortCriteria);
        }

        public unsafe void EndBrowseRecordTasks(uint aAsyncHandle, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
			char* result;
			fixed (uint* numberReturned = &aNumberReturned)
			fixed (uint* totalMatches = &aTotalMatches)
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndBrowseRecordTasks(iHandle, aAsyncHandle, &result, numberReturned, totalMatches, updateID))
				{
					throw(new ProxyError());
				}
			}
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void SyncCreateRecordSchedule(string aElements, out string aRecordScheduleID, out string aResult, out uint aUpdateID)
        {
			char* elements = (char*)Marshal.StringToHGlobalAnsi(aElements);
			char* recordScheduleID;
			char* result;
			fixed (uint* updateID = &aUpdateID)
			{
				CpProxyUpnpOrgScheduledRecording2SyncCreateRecordSchedule(iHandle, elements, &recordScheduleID, &result, updateID);
			}
			Marshal.FreeHGlobal((IntPtr)elements);
            aRecordScheduleID = Marshal.PtrToStringAnsi((IntPtr)recordScheduleID);
            ZappFree(recordScheduleID);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void BeginCreateRecordSchedule(string aElements, CallbackAsyncComplete aCallback)
        {
			char* elements = (char*)Marshal.StringToHGlobalAnsi(aElements);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginCreateRecordSchedule(iHandle, elements, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)elements);
        }

        public unsafe void EndCreateRecordSchedule(uint aAsyncHandle, out string aRecordScheduleID, out string aResult, out uint aUpdateID)
        {
			char* recordScheduleID;
			char* result;
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndCreateRecordSchedule(iHandle, aAsyncHandle, &recordScheduleID, &result, updateID))
				{
					throw(new ProxyError());
				}
			}
            aRecordScheduleID = Marshal.PtrToStringAnsi((IntPtr)recordScheduleID);
            ZappFree(recordScheduleID);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void SyncDeleteRecordSchedule(string aRecordScheduleID)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
			{
				CpProxyUpnpOrgScheduledRecording2SyncDeleteRecordSchedule(iHandle, recordScheduleID);
			}
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void BeginDeleteRecordSchedule(string aRecordScheduleID, CallbackAsyncComplete aCallback)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginDeleteRecordSchedule(iHandle, recordScheduleID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void EndDeleteRecordSchedule(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndDeleteRecordSchedule(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetRecordSchedule(string aRecordScheduleID, string aFilter, out string aResult, out uint aUpdateID)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
			char* result;
			fixed (uint* updateID = &aUpdateID)
			{
				CpProxyUpnpOrgScheduledRecording2SyncGetRecordSchedule(iHandle, recordScheduleID, filter, &result, updateID);
			}
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
			Marshal.FreeHGlobal((IntPtr)filter);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void BeginGetRecordSchedule(string aRecordScheduleID, string aFilter, CallbackAsyncComplete aCallback)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginGetRecordSchedule(iHandle, recordScheduleID, filter, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
			Marshal.FreeHGlobal((IntPtr)filter);
        }

        public unsafe void EndGetRecordSchedule(uint aAsyncHandle, out string aResult, out uint aUpdateID)
        {
			char* result;
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndGetRecordSchedule(iHandle, aAsyncHandle, &result, updateID))
				{
					throw(new ProxyError());
				}
			}
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void SyncEnableRecordSchedule(string aRecordScheduleID)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
			{
				CpProxyUpnpOrgScheduledRecording2SyncEnableRecordSchedule(iHandle, recordScheduleID);
			}
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void BeginEnableRecordSchedule(string aRecordScheduleID, CallbackAsyncComplete aCallback)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginEnableRecordSchedule(iHandle, recordScheduleID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void EndEnableRecordSchedule(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndEnableRecordSchedule(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDisableRecordSchedule(string aRecordScheduleID)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
			{
				CpProxyUpnpOrgScheduledRecording2SyncDisableRecordSchedule(iHandle, recordScheduleID);
			}
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void BeginDisableRecordSchedule(string aRecordScheduleID, CallbackAsyncComplete aCallback)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginDisableRecordSchedule(iHandle, recordScheduleID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void EndDisableRecordSchedule(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndDisableRecordSchedule(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDeleteRecordTask(string aRecordTaskID)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
			{
				CpProxyUpnpOrgScheduledRecording2SyncDeleteRecordTask(iHandle, recordTaskID);
			}
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void BeginDeleteRecordTask(string aRecordTaskID, CallbackAsyncComplete aCallback)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginDeleteRecordTask(iHandle, recordTaskID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void EndDeleteRecordTask(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndDeleteRecordTask(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetRecordTask(string aRecordTaskID, string aFilter, out string aResult, out uint aUpdateID)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
			char* result;
			fixed (uint* updateID = &aUpdateID)
			{
				CpProxyUpnpOrgScheduledRecording2SyncGetRecordTask(iHandle, recordTaskID, filter, &result, updateID);
			}
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
			Marshal.FreeHGlobal((IntPtr)filter);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void BeginGetRecordTask(string aRecordTaskID, string aFilter, CallbackAsyncComplete aCallback)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
			char* filter = (char*)Marshal.StringToHGlobalAnsi(aFilter);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginGetRecordTask(iHandle, recordTaskID, filter, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
			Marshal.FreeHGlobal((IntPtr)filter);
        }

        public unsafe void EndGetRecordTask(uint aAsyncHandle, out string aResult, out uint aUpdateID)
        {
			char* result;
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndGetRecordTask(iHandle, aAsyncHandle, &result, updateID))
				{
					throw(new ProxyError());
				}
			}
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        public unsafe void SyncEnableRecordTask(string aRecordTaskID)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
			{
				CpProxyUpnpOrgScheduledRecording2SyncEnableRecordTask(iHandle, recordTaskID);
			}
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void BeginEnableRecordTask(string aRecordTaskID, CallbackAsyncComplete aCallback)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginEnableRecordTask(iHandle, recordTaskID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void EndEnableRecordTask(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndEnableRecordTask(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDisableRecordTask(string aRecordTaskID)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
			{
				CpProxyUpnpOrgScheduledRecording2SyncDisableRecordTask(iHandle, recordTaskID);
			}
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void BeginDisableRecordTask(string aRecordTaskID, CallbackAsyncComplete aCallback)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginDisableRecordTask(iHandle, recordTaskID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void EndDisableRecordTask(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndDisableRecordTask(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncResetRecordTask(string aRecordTaskID)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
			{
				CpProxyUpnpOrgScheduledRecording2SyncResetRecordTask(iHandle, recordTaskID);
			}
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void BeginResetRecordTask(string aRecordTaskID, CallbackAsyncComplete aCallback)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginResetRecordTask(iHandle, recordTaskID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void EndResetRecordTask(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndResetRecordTask(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetRecordScheduleConflicts(string aRecordScheduleID, out string aRecordScheduleConflictIDList, out uint aUpdateID)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
			char* recordScheduleConflictIDList;
			fixed (uint* updateID = &aUpdateID)
			{
				CpProxyUpnpOrgScheduledRecording2SyncGetRecordScheduleConflicts(iHandle, recordScheduleID, &recordScheduleConflictIDList, updateID);
			}
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
            aRecordScheduleConflictIDList = Marshal.PtrToStringAnsi((IntPtr)recordScheduleConflictIDList);
            ZappFree(recordScheduleConflictIDList);
        }

        public unsafe void BeginGetRecordScheduleConflicts(string aRecordScheduleID, CallbackAsyncComplete aCallback)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginGetRecordScheduleConflicts(iHandle, recordScheduleID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void EndGetRecordScheduleConflicts(uint aAsyncHandle, out string aRecordScheduleConflictIDList, out uint aUpdateID)
        {
			char* recordScheduleConflictIDList;
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndGetRecordScheduleConflicts(iHandle, aAsyncHandle, &recordScheduleConflictIDList, updateID))
				{
					throw(new ProxyError());
				}
			}
            aRecordScheduleConflictIDList = Marshal.PtrToStringAnsi((IntPtr)recordScheduleConflictIDList);
            ZappFree(recordScheduleConflictIDList);
        }

        public unsafe void SyncGetRecordTaskConflicts(string aRecordTaskID, out string aRecordTaskConflictIDList, out uint aUpdateID)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
			char* recordTaskConflictIDList;
			fixed (uint* updateID = &aUpdateID)
			{
				CpProxyUpnpOrgScheduledRecording2SyncGetRecordTaskConflicts(iHandle, recordTaskID, &recordTaskConflictIDList, updateID);
			}
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
            aRecordTaskConflictIDList = Marshal.PtrToStringAnsi((IntPtr)recordTaskConflictIDList);
            ZappFree(recordTaskConflictIDList);
        }

        public unsafe void BeginGetRecordTaskConflicts(string aRecordTaskID, CallbackAsyncComplete aCallback)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording2BeginGetRecordTaskConflicts(iHandle, recordTaskID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void EndGetRecordTaskConflicts(uint aAsyncHandle, out string aRecordTaskConflictIDList, out uint aUpdateID)
        {
			char* recordTaskConflictIDList;
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording2EndGetRecordTaskConflicts(iHandle, aAsyncHandle, &recordTaskConflictIDList, updateID))
				{
					throw(new ProxyError());
				}
			}
            aRecordTaskConflictIDList = Marshal.PtrToStringAnsi((IntPtr)recordTaskConflictIDList);
            ZappFree(recordTaskConflictIDList);
        }

        public void SetPropertyLastChangeChanged(CallbackPropertyChanged aLastChangeChanged)
        {
            iLastChangeChanged = aLastChangeChanged;
            iCallbackLastChangeChanged = new Callback(PropertyLastChangeChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgScheduledRecording2SetPropertyLastChangeChanged(iHandle, iCallbackLastChangeChanged, ptr);
        }

        private void PropertyLastChangeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgScheduledRecording2 self = (CpProxyUpnpOrgScheduledRecording2)gch.Target;
            self.iLastChangeChanged();
        }

        public unsafe void PropertyLastChange(out string aLastChange)
        {
			char* ptr;
            CpProxyUpnpOrgScheduledRecording2PropertyLastChange(iHandle, &ptr);
            aLastChange = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgScheduledRecording2()
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
            CpProxyUpnpOrgScheduledRecording2Destroy(handle);
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

