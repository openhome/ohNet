using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderUpnpOrgScheduledRecording1 : IDisposable
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
        string PropertyLastChange();
        
    }
    /// <summary>
    /// Provider for the upnp.org:ScheduledRecording:1 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgScheduledRecording1 : DvProvider, IDisposable, IDvProviderUpnpOrgScheduledRecording1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateGetSortCapabilities;
        private ActionDelegate iDelegateGetPropertyList;
        private ActionDelegate iDelegateGetAllowedValues;
        private ActionDelegate iDelegateGetStateUpdateID;
        private ActionDelegate iDelegateBrowseRecordSchedules;
        private ActionDelegate iDelegateBrowseRecordTasks;
        private ActionDelegate iDelegateCreateRecordSchedule;
        private ActionDelegate iDelegateDeleteRecordSchedule;
        private ActionDelegate iDelegateGetRecordSchedule;
        private ActionDelegate iDelegateEnableRecordSchedule;
        private ActionDelegate iDelegateDisableRecordSchedule;
        private ActionDelegate iDelegateDeleteRecordTask;
        private ActionDelegate iDelegateGetRecordTask;
        private ActionDelegate iDelegateEnableRecordTask;
        private ActionDelegate iDelegateDisableRecordTask;
        private ActionDelegate iDelegateResetRecordTask;
        private ActionDelegate iDelegateGetRecordScheduleConflicts;
        private ActionDelegate iDelegateGetRecordTaskConflicts;
        private PropertyString iPropertyLastChange;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgScheduledRecording1(DvDevice aDevice)
            : base(aDevice, "schemas-upnp-org", "ScheduledRecording", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyLastChange = new PropertyString(new ParameterString("LastChange", allowedValues));
            AddProperty(iPropertyLastChange);
        }

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyLastChange(string aValue)
        {
            return SetPropertyString(iPropertyLastChange, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyLastChange()
        {
            return iPropertyLastChange.Value();
        }

        /// <summary>
        /// Signal that the action GetSortCapabilities is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetSortCapabilities must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetSortCapabilities()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetSortCapabilities");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("SortCaps", allowedValues));
            action.AddOutputParameter(new ParameterUint("SortLevelCap"));
            iDelegateGetSortCapabilities = new ActionDelegate(DoGetSortCapabilities);
            EnableAction(action, iDelegateGetSortCapabilities, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetPropertyList is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetPropertyList must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetPropertyList()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetPropertyList");
            List<String> allowedValues = new List<String>();
            allowedValues.Add("A_ARG_TYPE_RecordSchedule");
            allowedValues.Add("A_ARG_TYPE_RecordTask");
            allowedValues.Add("A_ARG_TYPE_RecordScheduleParts");
            action.AddInputParameter(new ParameterString("DataTypeID", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterString("PropertyList", allowedValues));
            iDelegateGetPropertyList = new ActionDelegate(DoGetPropertyList);
            EnableAction(action, iDelegateGetPropertyList, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetAllowedValues is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetAllowedValues must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetAllowedValues()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetAllowedValues");
            List<String> allowedValues = new List<String>();
            allowedValues.Add("A_ARG_TYPE_RecordSchedule");
            allowedValues.Add("A_ARG_TYPE_RecordTask");
            allowedValues.Add("A_ARG_TYPE_RecordScheduleParts");
            action.AddInputParameter(new ParameterString("DataTypeID", allowedValues));
            allowedValues.Clear();
            action.AddInputParameter(new ParameterString("Filter", allowedValues));
            action.AddOutputParameter(new ParameterString("PropertyInfo", allowedValues));
            iDelegateGetAllowedValues = new ActionDelegate(DoGetAllowedValues);
            EnableAction(action, iDelegateGetAllowedValues, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetStateUpdateID is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetStateUpdateID must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetStateUpdateID()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetStateUpdateID");
            action.AddOutputParameter(new ParameterUint("Id"));
            iDelegateGetStateUpdateID = new ActionDelegate(DoGetStateUpdateID);
            EnableAction(action, iDelegateGetStateUpdateID, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action BrowseRecordSchedules is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBrowseRecordSchedules must be overridden if this is called.</remarks>
        protected unsafe void EnableActionBrowseRecordSchedules()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("BrowseRecordSchedules");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("Filter", allowedValues));
            action.AddInputParameter(new ParameterUint("StartingIndex"));
            action.AddInputParameter(new ParameterUint("RequestedCount"));
            action.AddInputParameter(new ParameterString("SortCriteria", allowedValues));
            action.AddOutputParameter(new ParameterString("Result", allowedValues));
            action.AddOutputParameter(new ParameterUint("NumberReturned"));
            action.AddOutputParameter(new ParameterUint("TotalMatches"));
            action.AddOutputParameter(new ParameterUint("UpdateID"));
            iDelegateBrowseRecordSchedules = new ActionDelegate(DoBrowseRecordSchedules);
            EnableAction(action, iDelegateBrowseRecordSchedules, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action BrowseRecordTasks is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBrowseRecordTasks must be overridden if this is called.</remarks>
        protected unsafe void EnableActionBrowseRecordTasks()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("BrowseRecordTasks");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordScheduleID", allowedValues));
            action.AddInputParameter(new ParameterString("Filter", allowedValues));
            action.AddInputParameter(new ParameterUint("StartingIndex"));
            action.AddInputParameter(new ParameterUint("RequestedCount"));
            action.AddInputParameter(new ParameterString("SortCriteria", allowedValues));
            action.AddOutputParameter(new ParameterString("Result", allowedValues));
            action.AddOutputParameter(new ParameterUint("NumberReturned"));
            action.AddOutputParameter(new ParameterUint("TotalMatches"));
            action.AddOutputParameter(new ParameterUint("UpdateID"));
            iDelegateBrowseRecordTasks = new ActionDelegate(DoBrowseRecordTasks);
            EnableAction(action, iDelegateBrowseRecordTasks, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action CreateRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoCreateRecordSchedule must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCreateRecordSchedule()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("CreateRecordSchedule");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("Elements", allowedValues));
            action.AddOutputParameter(new ParameterString("RecordScheduleID", allowedValues));
            action.AddOutputParameter(new ParameterString("Result", allowedValues));
            action.AddOutputParameter(new ParameterUint("UpdateID"));
            iDelegateCreateRecordSchedule = new ActionDelegate(DoCreateRecordSchedule);
            EnableAction(action, iDelegateCreateRecordSchedule, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DeleteRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDeleteRecordSchedule must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDeleteRecordSchedule()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DeleteRecordSchedule");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordScheduleID", allowedValues));
            iDelegateDeleteRecordSchedule = new ActionDelegate(DoDeleteRecordSchedule);
            EnableAction(action, iDelegateDeleteRecordSchedule, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRecordSchedule must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRecordSchedule()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetRecordSchedule");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordScheduleID", allowedValues));
            action.AddInputParameter(new ParameterString("Filter", allowedValues));
            action.AddOutputParameter(new ParameterString("Result", allowedValues));
            action.AddOutputParameter(new ParameterUint("UpdateID"));
            iDelegateGetRecordSchedule = new ActionDelegate(DoGetRecordSchedule);
            EnableAction(action, iDelegateGetRecordSchedule, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action EnableRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoEnableRecordSchedule must be overridden if this is called.</remarks>
        protected unsafe void EnableActionEnableRecordSchedule()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("EnableRecordSchedule");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordScheduleID", allowedValues));
            iDelegateEnableRecordSchedule = new ActionDelegate(DoEnableRecordSchedule);
            EnableAction(action, iDelegateEnableRecordSchedule, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisableRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisableRecordSchedule must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisableRecordSchedule()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DisableRecordSchedule");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordScheduleID", allowedValues));
            iDelegateDisableRecordSchedule = new ActionDelegate(DoDisableRecordSchedule);
            EnableAction(action, iDelegateDisableRecordSchedule, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DeleteRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDeleteRecordTask must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDeleteRecordTask()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DeleteRecordTask");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordTaskID", allowedValues));
            iDelegateDeleteRecordTask = new ActionDelegate(DoDeleteRecordTask);
            EnableAction(action, iDelegateDeleteRecordTask, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRecordTask must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRecordTask()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetRecordTask");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordTaskID", allowedValues));
            action.AddInputParameter(new ParameterString("Filter", allowedValues));
            action.AddOutputParameter(new ParameterString("Result", allowedValues));
            action.AddOutputParameter(new ParameterUint("UpdateID"));
            iDelegateGetRecordTask = new ActionDelegate(DoGetRecordTask);
            EnableAction(action, iDelegateGetRecordTask, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action EnableRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoEnableRecordTask must be overridden if this is called.</remarks>
        protected unsafe void EnableActionEnableRecordTask()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("EnableRecordTask");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordTaskID", allowedValues));
            iDelegateEnableRecordTask = new ActionDelegate(DoEnableRecordTask);
            EnableAction(action, iDelegateEnableRecordTask, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisableRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisableRecordTask must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisableRecordTask()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DisableRecordTask");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordTaskID", allowedValues));
            iDelegateDisableRecordTask = new ActionDelegate(DoDisableRecordTask);
            EnableAction(action, iDelegateDisableRecordTask, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ResetRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoResetRecordTask must be overridden if this is called.</remarks>
        protected unsafe void EnableActionResetRecordTask()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ResetRecordTask");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordTaskID", allowedValues));
            iDelegateResetRecordTask = new ActionDelegate(DoResetRecordTask);
            EnableAction(action, iDelegateResetRecordTask, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRecordScheduleConflicts is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRecordScheduleConflicts must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRecordScheduleConflicts()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetRecordScheduleConflicts");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordScheduleID", allowedValues));
            action.AddOutputParameter(new ParameterString("RecordScheduleConflictIDList", allowedValues));
            action.AddOutputParameter(new ParameterUint("UpdateID"));
            iDelegateGetRecordScheduleConflicts = new ActionDelegate(DoGetRecordScheduleConflicts);
            EnableAction(action, iDelegateGetRecordScheduleConflicts, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRecordTaskConflicts is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRecordTaskConflicts must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRecordTaskConflicts()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetRecordTaskConflicts");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordTaskID", allowedValues));
            action.AddOutputParameter(new ParameterString("RecordTaskConflictIDList", allowedValues));
            action.AddOutputParameter(new ParameterUint("UpdateID"));
            iDelegateGetRecordTaskConflicts = new ActionDelegate(DoGetRecordTaskConflicts);
            EnableAction(action, iDelegateGetRecordTaskConflicts, GCHandle.ToIntPtr(iGch));
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

        private static unsafe int DoGetSortCapabilities(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                string sortCaps;
                uint sortLevelCap;
                self.GetSortCapabilities(aVersion, out sortCaps, out sortLevelCap);
                invocation.WriteStart();
                invocation.WriteString("SortCaps", sortCaps);
                invocation.WriteUint("SortLevelCap", sortLevelCap);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetPropertyList(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string dataTypeID = invocation.ReadString("DataTypeID");
                invocation.ReadEnd();
                string propertyList;
                self.GetPropertyList(aVersion, dataTypeID, out propertyList);
                invocation.WriteStart();
                invocation.WriteString("PropertyList", propertyList);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetAllowedValues(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string dataTypeID = invocation.ReadString("DataTypeID");
                string filter = invocation.ReadString("Filter");
                invocation.ReadEnd();
                string propertyInfo;
                self.GetAllowedValues(aVersion, dataTypeID, filter, out propertyInfo);
                invocation.WriteStart();
                invocation.WriteString("PropertyInfo", propertyInfo);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetStateUpdateID(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                uint id;
                self.GetStateUpdateID(aVersion, out id);
                invocation.WriteStart();
                invocation.WriteUint("Id", id);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoBrowseRecordSchedules(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string filter = invocation.ReadString("Filter");
                uint startingIndex = invocation.ReadUint("StartingIndex");
                uint requestedCount = invocation.ReadUint("RequestedCount");
                string sortCriteria = invocation.ReadString("SortCriteria");
                invocation.ReadEnd();
                string result;
                uint numberReturned;
                uint totalMatches;
                uint updateID;
                self.BrowseRecordSchedules(aVersion, filter, startingIndex, requestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
                invocation.WriteStart();
                invocation.WriteString("Result", result);
                invocation.WriteUint("NumberReturned", numberReturned);
                invocation.WriteUint("TotalMatches", totalMatches);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoBrowseRecordTasks(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordScheduleID = invocation.ReadString("RecordScheduleID");
                string filter = invocation.ReadString("Filter");
                uint startingIndex = invocation.ReadUint("StartingIndex");
                uint requestedCount = invocation.ReadUint("RequestedCount");
                string sortCriteria = invocation.ReadString("SortCriteria");
                invocation.ReadEnd();
                string result;
                uint numberReturned;
                uint totalMatches;
                uint updateID;
                self.BrowseRecordTasks(aVersion, recordScheduleID, filter, startingIndex, requestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
                invocation.WriteStart();
                invocation.WriteString("Result", result);
                invocation.WriteUint("NumberReturned", numberReturned);
                invocation.WriteUint("TotalMatches", totalMatches);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoCreateRecordSchedule(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string elements = invocation.ReadString("Elements");
                invocation.ReadEnd();
                string recordScheduleID;
                string result;
                uint updateID;
                self.CreateRecordSchedule(aVersion, elements, out recordScheduleID, out result, out updateID);
                invocation.WriteStart();
                invocation.WriteString("RecordScheduleID", recordScheduleID);
                invocation.WriteString("Result", result);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoDeleteRecordSchedule(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordScheduleID = invocation.ReadString("RecordScheduleID");
                invocation.ReadEnd();
                self.DeleteRecordSchedule(aVersion, recordScheduleID);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetRecordSchedule(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordScheduleID = invocation.ReadString("RecordScheduleID");
                string filter = invocation.ReadString("Filter");
                invocation.ReadEnd();
                string result;
                uint updateID;
                self.GetRecordSchedule(aVersion, recordScheduleID, filter, out result, out updateID);
                invocation.WriteStart();
                invocation.WriteString("Result", result);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoEnableRecordSchedule(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordScheduleID = invocation.ReadString("RecordScheduleID");
                invocation.ReadEnd();
                self.EnableRecordSchedule(aVersion, recordScheduleID);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoDisableRecordSchedule(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordScheduleID = invocation.ReadString("RecordScheduleID");
                invocation.ReadEnd();
                self.DisableRecordSchedule(aVersion, recordScheduleID);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoDeleteRecordTask(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordTaskID = invocation.ReadString("RecordTaskID");
                invocation.ReadEnd();
                self.DeleteRecordTask(aVersion, recordTaskID);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetRecordTask(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordTaskID = invocation.ReadString("RecordTaskID");
                string filter = invocation.ReadString("Filter");
                invocation.ReadEnd();
                string result;
                uint updateID;
                self.GetRecordTask(aVersion, recordTaskID, filter, out result, out updateID);
                invocation.WriteStart();
                invocation.WriteString("Result", result);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoEnableRecordTask(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordTaskID = invocation.ReadString("RecordTaskID");
                invocation.ReadEnd();
                self.EnableRecordTask(aVersion, recordTaskID);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoDisableRecordTask(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordTaskID = invocation.ReadString("RecordTaskID");
                invocation.ReadEnd();
                self.DisableRecordTask(aVersion, recordTaskID);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoResetRecordTask(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordTaskID = invocation.ReadString("RecordTaskID");
                invocation.ReadEnd();
                self.ResetRecordTask(aVersion, recordTaskID);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetRecordScheduleConflicts(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordScheduleID = invocation.ReadString("RecordScheduleID");
                invocation.ReadEnd();
                string recordScheduleConflictIDList;
                uint updateID;
                self.GetRecordScheduleConflicts(aVersion, recordScheduleID, out recordScheduleConflictIDList, out updateID);
                invocation.WriteStart();
                invocation.WriteString("RecordScheduleConflictIDList", recordScheduleConflictIDList);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetRecordTaskConflicts(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording1 self = (DvProviderUpnpOrgScheduledRecording1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string recordTaskID = invocation.ReadString("RecordTaskID");
                invocation.ReadEnd();
                string recordTaskConflictIDList;
                uint updateID;
                self.GetRecordTaskConflicts(aVersion, recordTaskID, out recordTaskConflictIDList, out updateID);
                invocation.WriteStart();
                invocation.WriteString("RecordTaskConflictIDList", recordTaskConflictIDList);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
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

        ~DvProviderUpnpOrgScheduledRecording1()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProvider();
                iHandle = IntPtr.Zero;
            }
            iGch.Free();
        }
    }
}

