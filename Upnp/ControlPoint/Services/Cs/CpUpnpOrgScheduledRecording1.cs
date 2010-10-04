using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyUpnpOrgScheduledRecording1 : CpProxy, IDisposable
    {
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern uint CpProxyUpnpOrgScheduledRecording1Create(uint aDeviceHandle);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern void CpProxyUpnpOrgScheduledRecording1Destroy(uint aHandle);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncGetSortCapabilities(uint aHandle, char** aSortCaps, uint* aSortLevelCap);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginGetSortCapabilities(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndGetSortCapabilities(uint aHandle, uint aAsync, char** aSortCaps, uint* aSortLevelCap);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncGetPropertyList(uint aHandle, char* aDataTypeID, char** aPropertyList);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginGetPropertyList(uint aHandle, char* aDataTypeID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndGetPropertyList(uint aHandle, uint aAsync, char** aPropertyList);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncGetAllowedValues(uint aHandle, char* aDataTypeID, char* aFilter, char** aPropertyInfo);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginGetAllowedValues(uint aHandle, char* aDataTypeID, char* aFilter, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndGetAllowedValues(uint aHandle, uint aAsync, char** aPropertyInfo);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncGetStateUpdateID(uint aHandle, uint* aId);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginGetStateUpdateID(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndGetStateUpdateID(uint aHandle, uint aAsync, uint* aId);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncBrowseRecordSchedules(uint aHandle, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginBrowseRecordSchedules(uint aHandle, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndBrowseRecordSchedules(uint aHandle, uint aAsync, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncBrowseRecordTasks(uint aHandle, char* aRecordScheduleID, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginBrowseRecordTasks(uint aHandle, char* aRecordScheduleID, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndBrowseRecordTasks(uint aHandle, uint aAsync, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncCreateRecordSchedule(uint aHandle, char* aElements, char** aRecordScheduleID, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginCreateRecordSchedule(uint aHandle, char* aElements, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndCreateRecordSchedule(uint aHandle, uint aAsync, char** aRecordScheduleID, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncDeleteRecordSchedule(uint aHandle, char* aRecordScheduleID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginDeleteRecordSchedule(uint aHandle, char* aRecordScheduleID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndDeleteRecordSchedule(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncGetRecordSchedule(uint aHandle, char* aRecordScheduleID, char* aFilter, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginGetRecordSchedule(uint aHandle, char* aRecordScheduleID, char* aFilter, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndGetRecordSchedule(uint aHandle, uint aAsync, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncEnableRecordSchedule(uint aHandle, char* aRecordScheduleID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginEnableRecordSchedule(uint aHandle, char* aRecordScheduleID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndEnableRecordSchedule(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncDisableRecordSchedule(uint aHandle, char* aRecordScheduleID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginDisableRecordSchedule(uint aHandle, char* aRecordScheduleID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndDisableRecordSchedule(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncDeleteRecordTask(uint aHandle, char* aRecordTaskID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginDeleteRecordTask(uint aHandle, char* aRecordTaskID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndDeleteRecordTask(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncGetRecordTask(uint aHandle, char* aRecordTaskID, char* aFilter, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginGetRecordTask(uint aHandle, char* aRecordTaskID, char* aFilter, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndGetRecordTask(uint aHandle, uint aAsync, char** aResult, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncEnableRecordTask(uint aHandle, char* aRecordTaskID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginEnableRecordTask(uint aHandle, char* aRecordTaskID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndEnableRecordTask(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncDisableRecordTask(uint aHandle, char* aRecordTaskID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginDisableRecordTask(uint aHandle, char* aRecordTaskID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndDisableRecordTask(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncResetRecordTask(uint aHandle, char* aRecordTaskID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginResetRecordTask(uint aHandle, char* aRecordTaskID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndResetRecordTask(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncGetRecordScheduleConflicts(uint aHandle, char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginGetRecordScheduleConflicts(uint aHandle, char* aRecordScheduleID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndGetRecordScheduleConflicts(uint aHandle, uint aAsync, char** aRecordScheduleConflictIDList, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1SyncGetRecordTaskConflicts(uint aHandle, char* aRecordTaskID, char** aRecordTaskConflictIDList, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1BeginGetRecordTaskConflicts(uint aHandle, char* aRecordTaskID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe int CpProxyUpnpOrgScheduledRecording1EndGetRecordTaskConflicts(uint aHandle, uint aAsync, char** aRecordTaskConflictIDList, uint* aUpdateID);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern void CpProxyUpnpOrgScheduledRecording1SetPropertyLastChangeChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgScheduledRecording1")]
        static extern unsafe void CpProxyUpnpOrgScheduledRecording1PropertyLastChange(uint aHandle, char** aLastChange);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iLastChangeChanged;
        private Callback iCallbackLastChangeChanged;

        public CpProxyUpnpOrgScheduledRecording1(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgScheduledRecording1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncGetSortCapabilities(out string aSortCaps, out uint aSortLevelCap)
        {
			char* sortCaps;
			fixed (uint* sortLevelCap = &aSortLevelCap)
			{
				CpProxyUpnpOrgScheduledRecording1SyncGetSortCapabilities(iHandle, &sortCaps, sortLevelCap);
			}
            aSortCaps = Marshal.PtrToStringAnsi((IntPtr)sortCaps);
            ZappFree(sortCaps);
        }

        public unsafe void BeginGetSortCapabilities(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording1BeginGetSortCapabilities(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetSortCapabilities(uint aAsyncHandle, out string aSortCaps, out uint aSortLevelCap)
        {
			char* sortCaps;
			fixed (uint* sortLevelCap = &aSortLevelCap)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndGetSortCapabilities(iHandle, aAsyncHandle, &sortCaps, sortLevelCap))
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
				CpProxyUpnpOrgScheduledRecording1SyncGetPropertyList(iHandle, dataTypeID, &propertyList);
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
            CpProxyUpnpOrgScheduledRecording1BeginGetPropertyList(iHandle, dataTypeID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)dataTypeID);
        }

        public unsafe void EndGetPropertyList(uint aAsyncHandle, out string aPropertyList)
        {
			char* propertyList;
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndGetPropertyList(iHandle, aAsyncHandle, &propertyList))
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
				CpProxyUpnpOrgScheduledRecording1SyncGetAllowedValues(iHandle, dataTypeID, filter, &propertyInfo);
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
            CpProxyUpnpOrgScheduledRecording1BeginGetAllowedValues(iHandle, dataTypeID, filter, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)dataTypeID);
			Marshal.FreeHGlobal((IntPtr)filter);
        }

        public unsafe void EndGetAllowedValues(uint aAsyncHandle, out string aPropertyInfo)
        {
			char* propertyInfo;
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndGetAllowedValues(iHandle, aAsyncHandle, &propertyInfo))
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
				CpProxyUpnpOrgScheduledRecording1SyncGetStateUpdateID(iHandle, id);
			}
        }

        public unsafe void BeginGetStateUpdateID(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording1BeginGetStateUpdateID(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetStateUpdateID(uint aAsyncHandle, out uint aId)
        {
			fixed (uint* id = &aId)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndGetStateUpdateID(iHandle, aAsyncHandle, id))
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
				CpProxyUpnpOrgScheduledRecording1SyncBrowseRecordSchedules(iHandle, filter, aStartingIndex, aRequestedCount, sortCriteria, &result, numberReturned, totalMatches, updateID);
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
            CpProxyUpnpOrgScheduledRecording1BeginBrowseRecordSchedules(iHandle, filter, aStartingIndex, aRequestedCount, sortCriteria, iActionComplete, ptr);
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
				if (0 != CpProxyUpnpOrgScheduledRecording1EndBrowseRecordSchedules(iHandle, aAsyncHandle, &result, numberReturned, totalMatches, updateID))
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
				CpProxyUpnpOrgScheduledRecording1SyncBrowseRecordTasks(iHandle, recordScheduleID, filter, aStartingIndex, aRequestedCount, sortCriteria, &result, numberReturned, totalMatches, updateID);
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
            CpProxyUpnpOrgScheduledRecording1BeginBrowseRecordTasks(iHandle, recordScheduleID, filter, aStartingIndex, aRequestedCount, sortCriteria, iActionComplete, ptr);
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
				if (0 != CpProxyUpnpOrgScheduledRecording1EndBrowseRecordTasks(iHandle, aAsyncHandle, &result, numberReturned, totalMatches, updateID))
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
				CpProxyUpnpOrgScheduledRecording1SyncCreateRecordSchedule(iHandle, elements, &recordScheduleID, &result, updateID);
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
            CpProxyUpnpOrgScheduledRecording1BeginCreateRecordSchedule(iHandle, elements, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)elements);
        }

        public unsafe void EndCreateRecordSchedule(uint aAsyncHandle, out string aRecordScheduleID, out string aResult, out uint aUpdateID)
        {
			char* recordScheduleID;
			char* result;
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndCreateRecordSchedule(iHandle, aAsyncHandle, &recordScheduleID, &result, updateID))
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
				CpProxyUpnpOrgScheduledRecording1SyncDeleteRecordSchedule(iHandle, recordScheduleID);
			}
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void BeginDeleteRecordSchedule(string aRecordScheduleID, CallbackAsyncComplete aCallback)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording1BeginDeleteRecordSchedule(iHandle, recordScheduleID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void EndDeleteRecordSchedule(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndDeleteRecordSchedule(iHandle, aAsyncHandle))
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
				CpProxyUpnpOrgScheduledRecording1SyncGetRecordSchedule(iHandle, recordScheduleID, filter, &result, updateID);
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
            CpProxyUpnpOrgScheduledRecording1BeginGetRecordSchedule(iHandle, recordScheduleID, filter, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
			Marshal.FreeHGlobal((IntPtr)filter);
        }

        public unsafe void EndGetRecordSchedule(uint aAsyncHandle, out string aResult, out uint aUpdateID)
        {
			char* result;
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndGetRecordSchedule(iHandle, aAsyncHandle, &result, updateID))
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
				CpProxyUpnpOrgScheduledRecording1SyncEnableRecordSchedule(iHandle, recordScheduleID);
			}
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void BeginEnableRecordSchedule(string aRecordScheduleID, CallbackAsyncComplete aCallback)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording1BeginEnableRecordSchedule(iHandle, recordScheduleID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void EndEnableRecordSchedule(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndEnableRecordSchedule(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDisableRecordSchedule(string aRecordScheduleID)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
			{
				CpProxyUpnpOrgScheduledRecording1SyncDisableRecordSchedule(iHandle, recordScheduleID);
			}
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void BeginDisableRecordSchedule(string aRecordScheduleID, CallbackAsyncComplete aCallback)
        {
			char* recordScheduleID = (char*)Marshal.StringToHGlobalAnsi(aRecordScheduleID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording1BeginDisableRecordSchedule(iHandle, recordScheduleID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void EndDisableRecordSchedule(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndDisableRecordSchedule(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDeleteRecordTask(string aRecordTaskID)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
			{
				CpProxyUpnpOrgScheduledRecording1SyncDeleteRecordTask(iHandle, recordTaskID);
			}
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void BeginDeleteRecordTask(string aRecordTaskID, CallbackAsyncComplete aCallback)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording1BeginDeleteRecordTask(iHandle, recordTaskID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void EndDeleteRecordTask(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndDeleteRecordTask(iHandle, aAsyncHandle))
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
				CpProxyUpnpOrgScheduledRecording1SyncGetRecordTask(iHandle, recordTaskID, filter, &result, updateID);
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
            CpProxyUpnpOrgScheduledRecording1BeginGetRecordTask(iHandle, recordTaskID, filter, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
			Marshal.FreeHGlobal((IntPtr)filter);
        }

        public unsafe void EndGetRecordTask(uint aAsyncHandle, out string aResult, out uint aUpdateID)
        {
			char* result;
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndGetRecordTask(iHandle, aAsyncHandle, &result, updateID))
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
				CpProxyUpnpOrgScheduledRecording1SyncEnableRecordTask(iHandle, recordTaskID);
			}
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void BeginEnableRecordTask(string aRecordTaskID, CallbackAsyncComplete aCallback)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording1BeginEnableRecordTask(iHandle, recordTaskID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void EndEnableRecordTask(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndEnableRecordTask(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDisableRecordTask(string aRecordTaskID)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
			{
				CpProxyUpnpOrgScheduledRecording1SyncDisableRecordTask(iHandle, recordTaskID);
			}
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void BeginDisableRecordTask(string aRecordTaskID, CallbackAsyncComplete aCallback)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording1BeginDisableRecordTask(iHandle, recordTaskID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void EndDisableRecordTask(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndDisableRecordTask(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncResetRecordTask(string aRecordTaskID)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
			{
				CpProxyUpnpOrgScheduledRecording1SyncResetRecordTask(iHandle, recordTaskID);
			}
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void BeginResetRecordTask(string aRecordTaskID, CallbackAsyncComplete aCallback)
        {
			char* recordTaskID = (char*)Marshal.StringToHGlobalAnsi(aRecordTaskID);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgScheduledRecording1BeginResetRecordTask(iHandle, recordTaskID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void EndResetRecordTask(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndResetRecordTask(iHandle, aAsyncHandle))
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
				CpProxyUpnpOrgScheduledRecording1SyncGetRecordScheduleConflicts(iHandle, recordScheduleID, &recordScheduleConflictIDList, updateID);
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
            CpProxyUpnpOrgScheduledRecording1BeginGetRecordScheduleConflicts(iHandle, recordScheduleID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordScheduleID);
        }

        public unsafe void EndGetRecordScheduleConflicts(uint aAsyncHandle, out string aRecordScheduleConflictIDList, out uint aUpdateID)
        {
			char* recordScheduleConflictIDList;
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndGetRecordScheduleConflicts(iHandle, aAsyncHandle, &recordScheduleConflictIDList, updateID))
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
				CpProxyUpnpOrgScheduledRecording1SyncGetRecordTaskConflicts(iHandle, recordTaskID, &recordTaskConflictIDList, updateID);
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
            CpProxyUpnpOrgScheduledRecording1BeginGetRecordTaskConflicts(iHandle, recordTaskID, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)recordTaskID);
        }

        public unsafe void EndGetRecordTaskConflicts(uint aAsyncHandle, out string aRecordTaskConflictIDList, out uint aUpdateID)
        {
			char* recordTaskConflictIDList;
			fixed (uint* updateID = &aUpdateID)
			{
				if (0 != CpProxyUpnpOrgScheduledRecording1EndGetRecordTaskConflicts(iHandle, aAsyncHandle, &recordTaskConflictIDList, updateID))
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
            CpProxyUpnpOrgScheduledRecording1SetPropertyLastChangeChanged(iHandle, iCallbackLastChangeChanged, ptr);
        }

        private void PropertyLastChangeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgScheduledRecording1 self = (CpProxyUpnpOrgScheduledRecording1)gch.Target;
            self.iLastChangeChanged();
        }

        public unsafe void PropertyLastChange(out string aLastChange)
        {
			char* ptr;
            CpProxyUpnpOrgScheduledRecording1PropertyLastChange(iHandle, &ptr);
            aLastChange = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgScheduledRecording1()
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
            CpProxyUpnpOrgScheduledRecording1Destroy(handle);
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

