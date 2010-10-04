using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceUpnpOrgScheduledRecording2 : IDisposable
    {
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern uint DvServiceUpnpOrgScheduledRecording2Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2Destroy(uint aHandle);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern unsafe int DvServiceUpnpOrgScheduledRecording2SetPropertyLastChange(uint aHandle, char* aValue);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern unsafe void DvServiceUpnpOrgScheduledRecording2GetPropertyLastChange(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionGetSortCapabilities(uint aHandle, CallbackGetSortCapabilities aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionGetPropertyList(uint aHandle, CallbackGetPropertyList aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionGetAllowedValues(uint aHandle, CallbackGetAllowedValues aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionGetStateUpdateID(uint aHandle, CallbackGetStateUpdateID aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules(uint aHandle, CallbackBrowseRecordSchedules aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks(uint aHandle, CallbackBrowseRecordTasks aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule(uint aHandle, CallbackCreateRecordSchedule aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule(uint aHandle, CallbackDeleteRecordSchedule aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordSchedule(uint aHandle, CallbackGetRecordSchedule aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule(uint aHandle, CallbackEnableRecordSchedule aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule(uint aHandle, CallbackDisableRecordSchedule aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionDeleteRecordTask(uint aHandle, CallbackDeleteRecordTask aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordTask(uint aHandle, CallbackGetRecordTask aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionEnableRecordTask(uint aHandle, CallbackEnableRecordTask aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionDisableRecordTask(uint aHandle, CallbackDisableRecordTask aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionResetRecordTask(uint aHandle, CallbackResetRecordTask aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts(uint aHandle, CallbackGetRecordScheduleConflicts aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts(uint aHandle, CallbackGetRecordTaskConflicts aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackGetSortCapabilities(IntPtr aPtr, uint aVersion, char** aSortCaps, uint* aSortLevelCap);
        private unsafe delegate int CallbackGetPropertyList(IntPtr aPtr, uint aVersion, char* aDataTypeID, char** aPropertyList);
        private unsafe delegate int CallbackGetAllowedValues(IntPtr aPtr, uint aVersion, char* aDataTypeID, char* aFilter, char** aPropertyInfo);
        private unsafe delegate int CallbackGetStateUpdateID(IntPtr aPtr, uint aVersion, uint* aId);
        private unsafe delegate int CallbackBrowseRecordSchedules(IntPtr aPtr, uint aVersion, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        private unsafe delegate int CallbackBrowseRecordTasks(IntPtr aPtr, uint aVersion, char* aRecordScheduleID, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID);
        private unsafe delegate int CallbackCreateRecordSchedule(IntPtr aPtr, uint aVersion, char* aElements, char** aRecordScheduleID, char** aResult, uint* aUpdateID);
        private unsafe delegate int CallbackDeleteRecordSchedule(IntPtr aPtr, uint aVersion, char* aRecordScheduleID);
        private unsafe delegate int CallbackGetRecordSchedule(IntPtr aPtr, uint aVersion, char* aRecordScheduleID, char* aFilter, char** aResult, uint* aUpdateID);
        private unsafe delegate int CallbackEnableRecordSchedule(IntPtr aPtr, uint aVersion, char* aRecordScheduleID);
        private unsafe delegate int CallbackDisableRecordSchedule(IntPtr aPtr, uint aVersion, char* aRecordScheduleID);
        private unsafe delegate int CallbackDeleteRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID);
        private unsafe delegate int CallbackGetRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID, char* aFilter, char** aResult, uint* aUpdateID);
        private unsafe delegate int CallbackEnableRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID);
        private unsafe delegate int CallbackDisableRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID);
        private unsafe delegate int CallbackResetRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID);
        private unsafe delegate int CallbackGetRecordScheduleConflicts(IntPtr aPtr, uint aVersion, char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint* aUpdateID);
        private unsafe delegate int CallbackGetRecordTaskConflicts(IntPtr aPtr, uint aVersion, char* aRecordTaskID, char** aRecordTaskConflictIDList, uint* aUpdateID);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackGetSortCapabilities iCallbackGetSortCapabilities;
        private CallbackGetPropertyList iCallbackGetPropertyList;
        private CallbackGetAllowedValues iCallbackGetAllowedValues;
        private CallbackGetStateUpdateID iCallbackGetStateUpdateID;
        private CallbackBrowseRecordSchedules iCallbackBrowseRecordSchedules;
        private CallbackBrowseRecordTasks iCallbackBrowseRecordTasks;
        private CallbackCreateRecordSchedule iCallbackCreateRecordSchedule;
        private CallbackDeleteRecordSchedule iCallbackDeleteRecordSchedule;
        private CallbackGetRecordSchedule iCallbackGetRecordSchedule;
        private CallbackEnableRecordSchedule iCallbackEnableRecordSchedule;
        private CallbackDisableRecordSchedule iCallbackDisableRecordSchedule;
        private CallbackDeleteRecordTask iCallbackDeleteRecordTask;
        private CallbackGetRecordTask iCallbackGetRecordTask;
        private CallbackEnableRecordTask iCallbackEnableRecordTask;
        private CallbackDisableRecordTask iCallbackDisableRecordTask;
        private CallbackResetRecordTask iCallbackResetRecordTask;
        private CallbackGetRecordScheduleConflicts iCallbackGetRecordScheduleConflicts;
        private CallbackGetRecordTaskConflicts iCallbackGetRecordTaskConflicts;

        public DvServiceUpnpOrgScheduledRecording2(DvDevice aDevice)
        {
            iHandle = DvServiceUpnpOrgScheduledRecording2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyLastChange(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceUpnpOrgScheduledRecording2SetPropertyLastChange(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyLastChange(out string aValue)
        {
            char* value;
            DvServiceUpnpOrgScheduledRecording2GetPropertyLastChange(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionGetSortCapabilities()
        {
            iCallbackGetSortCapabilities = new CallbackGetSortCapabilities(DoGetSortCapabilities);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionGetSortCapabilities(iHandle, iCallbackGetSortCapabilities, ptr);
        }

        protected unsafe void EnableActionGetPropertyList()
        {
            iCallbackGetPropertyList = new CallbackGetPropertyList(DoGetPropertyList);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionGetPropertyList(iHandle, iCallbackGetPropertyList, ptr);
        }

        protected unsafe void EnableActionGetAllowedValues()
        {
            iCallbackGetAllowedValues = new CallbackGetAllowedValues(DoGetAllowedValues);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionGetAllowedValues(iHandle, iCallbackGetAllowedValues, ptr);
        }

        protected unsafe void EnableActionGetStateUpdateID()
        {
            iCallbackGetStateUpdateID = new CallbackGetStateUpdateID(DoGetStateUpdateID);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionGetStateUpdateID(iHandle, iCallbackGetStateUpdateID, ptr);
        }

        protected unsafe void EnableActionBrowseRecordSchedules()
        {
            iCallbackBrowseRecordSchedules = new CallbackBrowseRecordSchedules(DoBrowseRecordSchedules);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules(iHandle, iCallbackBrowseRecordSchedules, ptr);
        }

        protected unsafe void EnableActionBrowseRecordTasks()
        {
            iCallbackBrowseRecordTasks = new CallbackBrowseRecordTasks(DoBrowseRecordTasks);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks(iHandle, iCallbackBrowseRecordTasks, ptr);
        }

        protected unsafe void EnableActionCreateRecordSchedule()
        {
            iCallbackCreateRecordSchedule = new CallbackCreateRecordSchedule(DoCreateRecordSchedule);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule(iHandle, iCallbackCreateRecordSchedule, ptr);
        }

        protected unsafe void EnableActionDeleteRecordSchedule()
        {
            iCallbackDeleteRecordSchedule = new CallbackDeleteRecordSchedule(DoDeleteRecordSchedule);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule(iHandle, iCallbackDeleteRecordSchedule, ptr);
        }

        protected unsafe void EnableActionGetRecordSchedule()
        {
            iCallbackGetRecordSchedule = new CallbackGetRecordSchedule(DoGetRecordSchedule);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordSchedule(iHandle, iCallbackGetRecordSchedule, ptr);
        }

        protected unsafe void EnableActionEnableRecordSchedule()
        {
            iCallbackEnableRecordSchedule = new CallbackEnableRecordSchedule(DoEnableRecordSchedule);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule(iHandle, iCallbackEnableRecordSchedule, ptr);
        }

        protected unsafe void EnableActionDisableRecordSchedule()
        {
            iCallbackDisableRecordSchedule = new CallbackDisableRecordSchedule(DoDisableRecordSchedule);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule(iHandle, iCallbackDisableRecordSchedule, ptr);
        }

        protected unsafe void EnableActionDeleteRecordTask()
        {
            iCallbackDeleteRecordTask = new CallbackDeleteRecordTask(DoDeleteRecordTask);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionDeleteRecordTask(iHandle, iCallbackDeleteRecordTask, ptr);
        }

        protected unsafe void EnableActionGetRecordTask()
        {
            iCallbackGetRecordTask = new CallbackGetRecordTask(DoGetRecordTask);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordTask(iHandle, iCallbackGetRecordTask, ptr);
        }

        protected unsafe void EnableActionEnableRecordTask()
        {
            iCallbackEnableRecordTask = new CallbackEnableRecordTask(DoEnableRecordTask);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionEnableRecordTask(iHandle, iCallbackEnableRecordTask, ptr);
        }

        protected unsafe void EnableActionDisableRecordTask()
        {
            iCallbackDisableRecordTask = new CallbackDisableRecordTask(DoDisableRecordTask);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionDisableRecordTask(iHandle, iCallbackDisableRecordTask, ptr);
        }

        protected unsafe void EnableActionResetRecordTask()
        {
            iCallbackResetRecordTask = new CallbackResetRecordTask(DoResetRecordTask);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionResetRecordTask(iHandle, iCallbackResetRecordTask, ptr);
        }

        protected unsafe void EnableActionGetRecordScheduleConflicts()
        {
            iCallbackGetRecordScheduleConflicts = new CallbackGetRecordScheduleConflicts(DoGetRecordScheduleConflicts);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts(iHandle, iCallbackGetRecordScheduleConflicts, ptr);
        }

        protected unsafe void EnableActionGetRecordTaskConflicts()
        {
            iCallbackGetRecordTaskConflicts = new CallbackGetRecordTaskConflicts(DoGetRecordTaskConflicts);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts(iHandle, iCallbackGetRecordTaskConflicts, ptr);
        }

        protected virtual void GetSortCapabilities(uint aVersion, out string aSortCaps, out uint aSortLevelCap)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetPropertyList(uint aVersion, string aDataTypeID, out string aPropertyList)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetAllowedValues(uint aVersion, string aDataTypeID, string aFilter, out string aPropertyInfo)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetStateUpdateID(uint aVersion, out uint aId)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void BrowseRecordSchedules(uint aVersion, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void BrowseRecordTasks(uint aVersion, string aRecordScheduleID, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void CreateRecordSchedule(uint aVersion, string aElements, out string aRecordScheduleID, out string aResult, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DeleteRecordSchedule(uint aVersion, string aRecordScheduleID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetRecordSchedule(uint aVersion, string aRecordScheduleID, string aFilter, out string aResult, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void EnableRecordSchedule(uint aVersion, string aRecordScheduleID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DisableRecordSchedule(uint aVersion, string aRecordScheduleID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DeleteRecordTask(uint aVersion, string aRecordTaskID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetRecordTask(uint aVersion, string aRecordTaskID, string aFilter, out string aResult, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void EnableRecordTask(uint aVersion, string aRecordTaskID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DisableRecordTask(uint aVersion, string aRecordTaskID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void ResetRecordTask(uint aVersion, string aRecordTaskID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetRecordScheduleConflicts(uint aVersion, string aRecordScheduleID, out string aRecordScheduleConflictIDList, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetRecordTaskConflicts(uint aVersion, string aRecordTaskID, out string aRecordTaskConflictIDList, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoGetSortCapabilities(IntPtr aPtr, uint aVersion, char** aSortCaps, uint* aSortLevelCap)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string sortCaps;
            uint sortLevelCap;
            self.GetSortCapabilities(aVersion, out sortCaps, out sortLevelCap);
            *aSortCaps = (char*)Marshal.StringToHGlobalAnsi(sortCaps).ToPointer();
            *aSortLevelCap = sortLevelCap;
            return 0;
        }

        private static unsafe int DoGetPropertyList(IntPtr aPtr, uint aVersion, char* aDataTypeID, char** aPropertyList)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string dataTypeID = Marshal.PtrToStringAnsi((IntPtr)aDataTypeID);
            string propertyList;
            self.GetPropertyList(aVersion, dataTypeID, out propertyList);
            *aPropertyList = (char*)Marshal.StringToHGlobalAnsi(propertyList).ToPointer();
            return 0;
        }

        private static unsafe int DoGetAllowedValues(IntPtr aPtr, uint aVersion, char* aDataTypeID, char* aFilter, char** aPropertyInfo)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string dataTypeID = Marshal.PtrToStringAnsi((IntPtr)aDataTypeID);
            string filter = Marshal.PtrToStringAnsi((IntPtr)aFilter);
            string propertyInfo;
            self.GetAllowedValues(aVersion, dataTypeID, filter, out propertyInfo);
            *aPropertyInfo = (char*)Marshal.StringToHGlobalAnsi(propertyInfo).ToPointer();
            return 0;
        }

        private static unsafe int DoGetStateUpdateID(IntPtr aPtr, uint aVersion, uint* aId)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            uint id;
            self.GetStateUpdateID(aVersion, out id);
            *aId = id;
            return 0;
        }

        private static unsafe int DoBrowseRecordSchedules(IntPtr aPtr, uint aVersion, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string filter = Marshal.PtrToStringAnsi((IntPtr)aFilter);
            string sortCriteria = Marshal.PtrToStringAnsi((IntPtr)aSortCriteria);
            string result;
            uint numberReturned;
            uint totalMatches;
            uint updateID;
            self.BrowseRecordSchedules(aVersion, filter, aStartingIndex, aRequestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            *aResult = (char*)Marshal.StringToHGlobalAnsi(result).ToPointer();
            *aNumberReturned = numberReturned;
            *aTotalMatches = totalMatches;
            *aUpdateID = updateID;
            return 0;
        }

        private static unsafe int DoBrowseRecordTasks(IntPtr aPtr, uint aVersion, char* aRecordScheduleID, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordScheduleID = Marshal.PtrToStringAnsi((IntPtr)aRecordScheduleID);
            string filter = Marshal.PtrToStringAnsi((IntPtr)aFilter);
            string sortCriteria = Marshal.PtrToStringAnsi((IntPtr)aSortCriteria);
            string result;
            uint numberReturned;
            uint totalMatches;
            uint updateID;
            self.BrowseRecordTasks(aVersion, recordScheduleID, filter, aStartingIndex, aRequestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            *aResult = (char*)Marshal.StringToHGlobalAnsi(result).ToPointer();
            *aNumberReturned = numberReturned;
            *aTotalMatches = totalMatches;
            *aUpdateID = updateID;
            return 0;
        }

        private static unsafe int DoCreateRecordSchedule(IntPtr aPtr, uint aVersion, char* aElements, char** aRecordScheduleID, char** aResult, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string elements = Marshal.PtrToStringAnsi((IntPtr)aElements);
            string recordScheduleID;
            string result;
            uint updateID;
            self.CreateRecordSchedule(aVersion, elements, out recordScheduleID, out result, out updateID);
            *aRecordScheduleID = (char*)Marshal.StringToHGlobalAnsi(recordScheduleID).ToPointer();
            *aResult = (char*)Marshal.StringToHGlobalAnsi(result).ToPointer();
            *aUpdateID = updateID;
            return 0;
        }

        private static unsafe int DoDeleteRecordSchedule(IntPtr aPtr, uint aVersion, char* aRecordScheduleID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordScheduleID = Marshal.PtrToStringAnsi((IntPtr)aRecordScheduleID);
            self.DeleteRecordSchedule(aVersion, recordScheduleID);
            return 0;
        }

        private static unsafe int DoGetRecordSchedule(IntPtr aPtr, uint aVersion, char* aRecordScheduleID, char* aFilter, char** aResult, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordScheduleID = Marshal.PtrToStringAnsi((IntPtr)aRecordScheduleID);
            string filter = Marshal.PtrToStringAnsi((IntPtr)aFilter);
            string result;
            uint updateID;
            self.GetRecordSchedule(aVersion, recordScheduleID, filter, out result, out updateID);
            *aResult = (char*)Marshal.StringToHGlobalAnsi(result).ToPointer();
            *aUpdateID = updateID;
            return 0;
        }

        private static unsafe int DoEnableRecordSchedule(IntPtr aPtr, uint aVersion, char* aRecordScheduleID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordScheduleID = Marshal.PtrToStringAnsi((IntPtr)aRecordScheduleID);
            self.EnableRecordSchedule(aVersion, recordScheduleID);
            return 0;
        }

        private static unsafe int DoDisableRecordSchedule(IntPtr aPtr, uint aVersion, char* aRecordScheduleID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordScheduleID = Marshal.PtrToStringAnsi((IntPtr)aRecordScheduleID);
            self.DisableRecordSchedule(aVersion, recordScheduleID);
            return 0;
        }

        private static unsafe int DoDeleteRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordTaskID = Marshal.PtrToStringAnsi((IntPtr)aRecordTaskID);
            self.DeleteRecordTask(aVersion, recordTaskID);
            return 0;
        }

        private static unsafe int DoGetRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID, char* aFilter, char** aResult, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordTaskID = Marshal.PtrToStringAnsi((IntPtr)aRecordTaskID);
            string filter = Marshal.PtrToStringAnsi((IntPtr)aFilter);
            string result;
            uint updateID;
            self.GetRecordTask(aVersion, recordTaskID, filter, out result, out updateID);
            *aResult = (char*)Marshal.StringToHGlobalAnsi(result).ToPointer();
            *aUpdateID = updateID;
            return 0;
        }

        private static unsafe int DoEnableRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordTaskID = Marshal.PtrToStringAnsi((IntPtr)aRecordTaskID);
            self.EnableRecordTask(aVersion, recordTaskID);
            return 0;
        }

        private static unsafe int DoDisableRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordTaskID = Marshal.PtrToStringAnsi((IntPtr)aRecordTaskID);
            self.DisableRecordTask(aVersion, recordTaskID);
            return 0;
        }

        private static unsafe int DoResetRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordTaskID = Marshal.PtrToStringAnsi((IntPtr)aRecordTaskID);
            self.ResetRecordTask(aVersion, recordTaskID);
            return 0;
        }

        private static unsafe int DoGetRecordScheduleConflicts(IntPtr aPtr, uint aVersion, char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordScheduleID = Marshal.PtrToStringAnsi((IntPtr)aRecordScheduleID);
            string recordScheduleConflictIDList;
            uint updateID;
            self.GetRecordScheduleConflicts(aVersion, recordScheduleID, out recordScheduleConflictIDList, out updateID);
            *aRecordScheduleConflictIDList = (char*)Marshal.StringToHGlobalAnsi(recordScheduleConflictIDList).ToPointer();
            *aUpdateID = updateID;
            return 0;
        }

        private static unsafe int DoGetRecordTaskConflicts(IntPtr aPtr, uint aVersion, char* aRecordTaskID, char** aRecordTaskConflictIDList, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgScheduledRecording2 self = (DvServiceUpnpOrgScheduledRecording2)gch.Target;
            string recordTaskID = Marshal.PtrToStringAnsi((IntPtr)aRecordTaskID);
            string recordTaskConflictIDList;
            uint updateID;
            self.GetRecordTaskConflicts(aVersion, recordTaskID, out recordTaskConflictIDList, out updateID);
            *aRecordTaskConflictIDList = (char*)Marshal.StringToHGlobalAnsi(recordTaskConflictIDList).ToPointer();
            *aUpdateID = updateID;
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceUpnpOrgScheduledRecording2()
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
            DvServiceUpnpOrgScheduledRecording2Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

