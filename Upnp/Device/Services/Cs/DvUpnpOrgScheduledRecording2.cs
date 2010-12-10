using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderUpnpOrgScheduledRecording2 : IDisposable
    {

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyLastChange(string aValue);

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyLastChange(out string aValue);
        
    }
    /// <summary>
    /// Provider for the upnp.org:ScheduledRecording:2 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgScheduledRecording2 : DvProvider, IDisposable, IDvProviderUpnpOrgScheduledRecording2
    {
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern IntPtr DvProviderUpnpOrgScheduledRecording2Create(IntPtr aDeviceHandle);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2Destroy(IntPtr aHandle);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern unsafe int DvProviderUpnpOrgScheduledRecording2SetPropertyLastChange(IntPtr aHandle, char* aValue, uint* aChanged);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern unsafe void DvProviderUpnpOrgScheduledRecording2GetPropertyLastChange(IntPtr aHandle, char** aValue);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionGetSortCapabilities(IntPtr aHandle, CallbackGetSortCapabilities aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionGetPropertyList(IntPtr aHandle, CallbackGetPropertyList aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionGetAllowedValues(IntPtr aHandle, CallbackGetAllowedValues aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionGetStateUpdateID(IntPtr aHandle, CallbackGetStateUpdateID aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules(IntPtr aHandle, CallbackBrowseRecordSchedules aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks(IntPtr aHandle, CallbackBrowseRecordTasks aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule(IntPtr aHandle, CallbackCreateRecordSchedule aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule(IntPtr aHandle, CallbackDeleteRecordSchedule aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordSchedule(IntPtr aHandle, CallbackGetRecordSchedule aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule(IntPtr aHandle, CallbackEnableRecordSchedule aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule(IntPtr aHandle, CallbackDisableRecordSchedule aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordTask(IntPtr aHandle, CallbackDeleteRecordTask aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTask(IntPtr aHandle, CallbackGetRecordTask aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordTask(IntPtr aHandle, CallbackEnableRecordTask aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordTask(IntPtr aHandle, CallbackDisableRecordTask aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionResetRecordTask(IntPtr aHandle, CallbackResetRecordTask aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts(IntPtr aHandle, CallbackGetRecordScheduleConflicts aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgScheduledRecording2")]
        static extern void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts(IntPtr aHandle, CallbackGetRecordTaskConflicts aCallback, IntPtr aPtr);
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgScheduledRecording2(DvDevice aDevice)
        {
            iHandle = DvProviderUpnpOrgScheduledRecording2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyLastChange(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderUpnpOrgScheduledRecording2SetPropertyLastChange(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyLastChange(out string aValue)
        {
            char* value;
            DvProviderUpnpOrgScheduledRecording2GetPropertyLastChange(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Signal that the action GetSortCapabilities is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetSortCapabilities must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetSortCapabilities()
        {
            iCallbackGetSortCapabilities = new CallbackGetSortCapabilities(DoGetSortCapabilities);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionGetSortCapabilities(iHandle, iCallbackGetSortCapabilities, ptr);
        }

        /// <summary>
        /// Signal that the action GetPropertyList is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetPropertyList must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetPropertyList()
        {
            iCallbackGetPropertyList = new CallbackGetPropertyList(DoGetPropertyList);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionGetPropertyList(iHandle, iCallbackGetPropertyList, ptr);
        }

        /// <summary>
        /// Signal that the action GetAllowedValues is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetAllowedValues must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetAllowedValues()
        {
            iCallbackGetAllowedValues = new CallbackGetAllowedValues(DoGetAllowedValues);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionGetAllowedValues(iHandle, iCallbackGetAllowedValues, ptr);
        }

        /// <summary>
        /// Signal that the action GetStateUpdateID is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetStateUpdateID must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetStateUpdateID()
        {
            iCallbackGetStateUpdateID = new CallbackGetStateUpdateID(DoGetStateUpdateID);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionGetStateUpdateID(iHandle, iCallbackGetStateUpdateID, ptr);
        }

        /// <summary>
        /// Signal that the action BrowseRecordSchedules is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBrowseRecordSchedules must be overridden if this is called.</remarks>
        protected unsafe void EnableActionBrowseRecordSchedules()
        {
            iCallbackBrowseRecordSchedules = new CallbackBrowseRecordSchedules(DoBrowseRecordSchedules);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules(iHandle, iCallbackBrowseRecordSchedules, ptr);
        }

        /// <summary>
        /// Signal that the action BrowseRecordTasks is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBrowseRecordTasks must be overridden if this is called.</remarks>
        protected unsafe void EnableActionBrowseRecordTasks()
        {
            iCallbackBrowseRecordTasks = new CallbackBrowseRecordTasks(DoBrowseRecordTasks);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks(iHandle, iCallbackBrowseRecordTasks, ptr);
        }

        /// <summary>
        /// Signal that the action CreateRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoCreateRecordSchedule must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCreateRecordSchedule()
        {
            iCallbackCreateRecordSchedule = new CallbackCreateRecordSchedule(DoCreateRecordSchedule);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule(iHandle, iCallbackCreateRecordSchedule, ptr);
        }

        /// <summary>
        /// Signal that the action DeleteRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDeleteRecordSchedule must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDeleteRecordSchedule()
        {
            iCallbackDeleteRecordSchedule = new CallbackDeleteRecordSchedule(DoDeleteRecordSchedule);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule(iHandle, iCallbackDeleteRecordSchedule, ptr);
        }

        /// <summary>
        /// Signal that the action GetRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRecordSchedule must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRecordSchedule()
        {
            iCallbackGetRecordSchedule = new CallbackGetRecordSchedule(DoGetRecordSchedule);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordSchedule(iHandle, iCallbackGetRecordSchedule, ptr);
        }

        /// <summary>
        /// Signal that the action EnableRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoEnableRecordSchedule must be overridden if this is called.</remarks>
        protected unsafe void EnableActionEnableRecordSchedule()
        {
            iCallbackEnableRecordSchedule = new CallbackEnableRecordSchedule(DoEnableRecordSchedule);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule(iHandle, iCallbackEnableRecordSchedule, ptr);
        }

        /// <summary>
        /// Signal that the action DisableRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisableRecordSchedule must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisableRecordSchedule()
        {
            iCallbackDisableRecordSchedule = new CallbackDisableRecordSchedule(DoDisableRecordSchedule);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule(iHandle, iCallbackDisableRecordSchedule, ptr);
        }

        /// <summary>
        /// Signal that the action DeleteRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDeleteRecordTask must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDeleteRecordTask()
        {
            iCallbackDeleteRecordTask = new CallbackDeleteRecordTask(DoDeleteRecordTask);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordTask(iHandle, iCallbackDeleteRecordTask, ptr);
        }

        /// <summary>
        /// Signal that the action GetRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRecordTask must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRecordTask()
        {
            iCallbackGetRecordTask = new CallbackGetRecordTask(DoGetRecordTask);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTask(iHandle, iCallbackGetRecordTask, ptr);
        }

        /// <summary>
        /// Signal that the action EnableRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoEnableRecordTask must be overridden if this is called.</remarks>
        protected unsafe void EnableActionEnableRecordTask()
        {
            iCallbackEnableRecordTask = new CallbackEnableRecordTask(DoEnableRecordTask);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordTask(iHandle, iCallbackEnableRecordTask, ptr);
        }

        /// <summary>
        /// Signal that the action DisableRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisableRecordTask must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisableRecordTask()
        {
            iCallbackDisableRecordTask = new CallbackDisableRecordTask(DoDisableRecordTask);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordTask(iHandle, iCallbackDisableRecordTask, ptr);
        }

        /// <summary>
        /// Signal that the action ResetRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoResetRecordTask must be overridden if this is called.</remarks>
        protected unsafe void EnableActionResetRecordTask()
        {
            iCallbackResetRecordTask = new CallbackResetRecordTask(DoResetRecordTask);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionResetRecordTask(iHandle, iCallbackResetRecordTask, ptr);
        }

        /// <summary>
        /// Signal that the action GetRecordScheduleConflicts is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRecordScheduleConflicts must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRecordScheduleConflicts()
        {
            iCallbackGetRecordScheduleConflicts = new CallbackGetRecordScheduleConflicts(DoGetRecordScheduleConflicts);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts(iHandle, iCallbackGetRecordScheduleConflicts, ptr);
        }

        /// <summary>
        /// Signal that the action GetRecordTaskConflicts is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRecordTaskConflicts must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRecordTaskConflicts()
        {
            iCallbackGetRecordTaskConflicts = new CallbackGetRecordTaskConflicts(DoGetRecordTaskConflicts);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts(iHandle, iCallbackGetRecordTaskConflicts, ptr);
        }

        /// <summary>
        /// GetSortCapabilities action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetSortCapabilities action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetSortCapabilities was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aSortCaps"></param>
        /// <param name="aSortLevelCap"></param>
        protected virtual void GetSortCapabilities(uint aVersion, out string aSortCaps, out uint aSortLevelCap)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetPropertyList action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetPropertyList action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetPropertyList was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aDataTypeID"></param>
        /// <param name="aPropertyList"></param>
        protected virtual void GetPropertyList(uint aVersion, string aDataTypeID, out string aPropertyList)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetAllowedValues action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetAllowedValues action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetAllowedValues was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aDataTypeID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aPropertyInfo"></param>
        protected virtual void GetAllowedValues(uint aVersion, string aDataTypeID, string aFilter, out string aPropertyInfo)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetStateUpdateID action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetStateUpdateID action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetStateUpdateID was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aId"></param>
        protected virtual void GetStateUpdateID(uint aVersion, out uint aId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BrowseRecordSchedules action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BrowseRecordSchedules action for the owning device.
        ///
        /// Must be implemented iff EnableActionBrowseRecordSchedules was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        protected virtual void BrowseRecordSchedules(uint aVersion, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BrowseRecordTasks action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BrowseRecordTasks action for the owning device.
        ///
        /// Must be implemented iff EnableActionBrowseRecordTasks was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        protected virtual void BrowseRecordTasks(uint aVersion, string aRecordScheduleID, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// CreateRecordSchedule action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// CreateRecordSchedule action for the owning device.
        ///
        /// Must be implemented iff EnableActionCreateRecordSchedule was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aElements"></param>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aResult"></param>
        /// <param name="aUpdateID"></param>
        protected virtual void CreateRecordSchedule(uint aVersion, string aElements, out string aRecordScheduleID, out string aResult, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DeleteRecordSchedule action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DeleteRecordSchedule action for the owning device.
        ///
        /// Must be implemented iff EnableActionDeleteRecordSchedule was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordScheduleID"></param>
        protected virtual void DeleteRecordSchedule(uint aVersion, string aRecordScheduleID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRecordSchedule action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRecordSchedule action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRecordSchedule was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aResult"></param>
        /// <param name="aUpdateID"></param>
        protected virtual void GetRecordSchedule(uint aVersion, string aRecordScheduleID, string aFilter, out string aResult, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// EnableRecordSchedule action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// EnableRecordSchedule action for the owning device.
        ///
        /// Must be implemented iff EnableActionEnableRecordSchedule was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordScheduleID"></param>
        protected virtual void EnableRecordSchedule(uint aVersion, string aRecordScheduleID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisableRecordSchedule action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisableRecordSchedule action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisableRecordSchedule was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordScheduleID"></param>
        protected virtual void DisableRecordSchedule(uint aVersion, string aRecordScheduleID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DeleteRecordTask action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DeleteRecordTask action for the owning device.
        ///
        /// Must be implemented iff EnableActionDeleteRecordTask was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordTaskID"></param>
        protected virtual void DeleteRecordTask(uint aVersion, string aRecordTaskID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRecordTask action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRecordTask action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRecordTask was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordTaskID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aResult"></param>
        /// <param name="aUpdateID"></param>
        protected virtual void GetRecordTask(uint aVersion, string aRecordTaskID, string aFilter, out string aResult, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// EnableRecordTask action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// EnableRecordTask action for the owning device.
        ///
        /// Must be implemented iff EnableActionEnableRecordTask was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordTaskID"></param>
        protected virtual void EnableRecordTask(uint aVersion, string aRecordTaskID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisableRecordTask action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisableRecordTask action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisableRecordTask was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordTaskID"></param>
        protected virtual void DisableRecordTask(uint aVersion, string aRecordTaskID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ResetRecordTask action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ResetRecordTask action for the owning device.
        ///
        /// Must be implemented iff EnableActionResetRecordTask was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordTaskID"></param>
        protected virtual void ResetRecordTask(uint aVersion, string aRecordTaskID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRecordScheduleConflicts action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRecordScheduleConflicts action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRecordScheduleConflicts was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aRecordScheduleConflictIDList"></param>
        /// <param name="aUpdateID"></param>
        protected virtual void GetRecordScheduleConflicts(uint aVersion, string aRecordScheduleID, out string aRecordScheduleConflictIDList, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRecordTaskConflicts action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRecordTaskConflicts action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRecordTaskConflicts was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRecordTaskID"></param>
        /// <param name="aRecordTaskConflictIDList"></param>
        /// <param name="aUpdateID"></param>
        protected virtual void GetRecordTaskConflicts(uint aVersion, string aRecordTaskID, out string aRecordTaskConflictIDList, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoGetSortCapabilities(IntPtr aPtr, uint aVersion, char** aSortCaps, uint* aSortLevelCap)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
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
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            string dataTypeID = Marshal.PtrToStringAnsi((IntPtr)aDataTypeID);
            string propertyList;
            self.GetPropertyList(aVersion, dataTypeID, out propertyList);
            *aPropertyList = (char*)Marshal.StringToHGlobalAnsi(propertyList).ToPointer();
            return 0;
        }

        private static unsafe int DoGetAllowedValues(IntPtr aPtr, uint aVersion, char* aDataTypeID, char* aFilter, char** aPropertyInfo)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
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
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            uint id;
            self.GetStateUpdateID(aVersion, out id);
            *aId = id;
            return 0;
        }

        private static unsafe int DoBrowseRecordSchedules(IntPtr aPtr, uint aVersion, char* aFilter, uint aStartingIndex, uint aRequestedCount, char* aSortCriteria, char** aResult, uint* aNumberReturned, uint* aTotalMatches, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
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
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
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
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
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
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            string recordScheduleID = Marshal.PtrToStringAnsi((IntPtr)aRecordScheduleID);
            self.DeleteRecordSchedule(aVersion, recordScheduleID);
            return 0;
        }

        private static unsafe int DoGetRecordSchedule(IntPtr aPtr, uint aVersion, char* aRecordScheduleID, char* aFilter, char** aResult, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
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
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            string recordScheduleID = Marshal.PtrToStringAnsi((IntPtr)aRecordScheduleID);
            self.EnableRecordSchedule(aVersion, recordScheduleID);
            return 0;
        }

        private static unsafe int DoDisableRecordSchedule(IntPtr aPtr, uint aVersion, char* aRecordScheduleID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            string recordScheduleID = Marshal.PtrToStringAnsi((IntPtr)aRecordScheduleID);
            self.DisableRecordSchedule(aVersion, recordScheduleID);
            return 0;
        }

        private static unsafe int DoDeleteRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            string recordTaskID = Marshal.PtrToStringAnsi((IntPtr)aRecordTaskID);
            self.DeleteRecordTask(aVersion, recordTaskID);
            return 0;
        }

        private static unsafe int DoGetRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID, char* aFilter, char** aResult, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
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
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            string recordTaskID = Marshal.PtrToStringAnsi((IntPtr)aRecordTaskID);
            self.EnableRecordTask(aVersion, recordTaskID);
            return 0;
        }

        private static unsafe int DoDisableRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            string recordTaskID = Marshal.PtrToStringAnsi((IntPtr)aRecordTaskID);
            self.DisableRecordTask(aVersion, recordTaskID);
            return 0;
        }

        private static unsafe int DoResetRecordTask(IntPtr aPtr, uint aVersion, char* aRecordTaskID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            string recordTaskID = Marshal.PtrToStringAnsi((IntPtr)aRecordTaskID);
            self.ResetRecordTask(aVersion, recordTaskID);
            return 0;
        }

        private static unsafe int DoGetRecordScheduleConflicts(IntPtr aPtr, uint aVersion, char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint* aUpdateID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
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
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            string recordTaskID = Marshal.PtrToStringAnsi((IntPtr)aRecordTaskID);
            string recordTaskConflictIDList;
            uint updateID;
            self.GetRecordTaskConflicts(aVersion, recordTaskID, out recordTaskConflictIDList, out updateID);
            *aRecordTaskConflictIDList = (char*)Marshal.StringToHGlobalAnsi(recordTaskConflictIDList).ToPointer();
            *aUpdateID = updateID;
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderUpnpOrgScheduledRecording2()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
            }
            DvProviderUpnpOrgScheduledRecording2Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

