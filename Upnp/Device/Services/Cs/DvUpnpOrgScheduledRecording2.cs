using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
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
        string PropertyLastChange();
        
    }
    /// <summary>
    /// Provider for the upnp.org:ScheduledRecording:2 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgScheduledRecording2 : DvProvider, IDisposable, IDvProviderUpnpOrgScheduledRecording2
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
        protected DvProviderUpnpOrgScheduledRecording2(DvDevice aDevice)
            : base(aDevice, "upnp.org", "ScheduledRecording", 2)
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
        /// GetSortCapabilities must be overridden if this is called.</remarks>
        protected void EnableActionGetSortCapabilities()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetSortCapabilities");
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
        /// GetPropertyList must be overridden if this is called.</remarks>
        protected void EnableActionGetPropertyList()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetPropertyList");
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
        /// GetAllowedValues must be overridden if this is called.</remarks>
        protected void EnableActionGetAllowedValues()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetAllowedValues");
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
        /// GetStateUpdateID must be overridden if this is called.</remarks>
        protected void EnableActionGetStateUpdateID()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetStateUpdateID");
            action.AddOutputParameter(new ParameterUint("Id"));
            iDelegateGetStateUpdateID = new ActionDelegate(DoGetStateUpdateID);
            EnableAction(action, iDelegateGetStateUpdateID, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action BrowseRecordSchedules is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// BrowseRecordSchedules must be overridden if this is called.</remarks>
        protected void EnableActionBrowseRecordSchedules()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("BrowseRecordSchedules");
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
        /// BrowseRecordTasks must be overridden if this is called.</remarks>
        protected void EnableActionBrowseRecordTasks()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("BrowseRecordTasks");
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
        /// CreateRecordSchedule must be overridden if this is called.</remarks>
        protected void EnableActionCreateRecordSchedule()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("CreateRecordSchedule");
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
        /// DeleteRecordSchedule must be overridden if this is called.</remarks>
        protected void EnableActionDeleteRecordSchedule()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("DeleteRecordSchedule");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordScheduleID", allowedValues));
            iDelegateDeleteRecordSchedule = new ActionDelegate(DoDeleteRecordSchedule);
            EnableAction(action, iDelegateDeleteRecordSchedule, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetRecordSchedule must be overridden if this is called.</remarks>
        protected void EnableActionGetRecordSchedule()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetRecordSchedule");
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
        /// EnableRecordSchedule must be overridden if this is called.</remarks>
        protected void EnableActionEnableRecordSchedule()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("EnableRecordSchedule");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordScheduleID", allowedValues));
            iDelegateEnableRecordSchedule = new ActionDelegate(DoEnableRecordSchedule);
            EnableAction(action, iDelegateEnableRecordSchedule, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisableRecordSchedule is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DisableRecordSchedule must be overridden if this is called.</remarks>
        protected void EnableActionDisableRecordSchedule()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("DisableRecordSchedule");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordScheduleID", allowedValues));
            iDelegateDisableRecordSchedule = new ActionDelegate(DoDisableRecordSchedule);
            EnableAction(action, iDelegateDisableRecordSchedule, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DeleteRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DeleteRecordTask must be overridden if this is called.</remarks>
        protected void EnableActionDeleteRecordTask()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("DeleteRecordTask");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordTaskID", allowedValues));
            iDelegateDeleteRecordTask = new ActionDelegate(DoDeleteRecordTask);
            EnableAction(action, iDelegateDeleteRecordTask, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetRecordTask must be overridden if this is called.</remarks>
        protected void EnableActionGetRecordTask()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetRecordTask");
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
        /// EnableRecordTask must be overridden if this is called.</remarks>
        protected void EnableActionEnableRecordTask()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("EnableRecordTask");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordTaskID", allowedValues));
            iDelegateEnableRecordTask = new ActionDelegate(DoEnableRecordTask);
            EnableAction(action, iDelegateEnableRecordTask, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisableRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DisableRecordTask must be overridden if this is called.</remarks>
        protected void EnableActionDisableRecordTask()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("DisableRecordTask");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordTaskID", allowedValues));
            iDelegateDisableRecordTask = new ActionDelegate(DoDisableRecordTask);
            EnableAction(action, iDelegateDisableRecordTask, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ResetRecordTask is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ResetRecordTask must be overridden if this is called.</remarks>
        protected void EnableActionResetRecordTask()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("ResetRecordTask");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("RecordTaskID", allowedValues));
            iDelegateResetRecordTask = new ActionDelegate(DoResetRecordTask);
            EnableAction(action, iDelegateResetRecordTask, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRecordScheduleConflicts is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetRecordScheduleConflicts must be overridden if this is called.</remarks>
        protected void EnableActionGetRecordScheduleConflicts()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetRecordScheduleConflicts");
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
        /// GetRecordTaskConflicts must be overridden if this is called.</remarks>
        protected void EnableActionGetRecordTaskConflicts()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetRecordTaskConflicts");
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

        private static int DoGetSortCapabilities(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sortCaps;
            uint sortLevelCap;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetSortCapabilities(aVersion, out sortCaps, out sortLevelCap);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("SortCaps", sortCaps);
                invocation.WriteUint("SortLevelCap", sortLevelCap);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoGetPropertyList(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string dataTypeID;
            string propertyList;
            try
            {
                invocation.ReadStart();
                dataTypeID = invocation.ReadString("DataTypeID");
                invocation.ReadEnd();
                self.GetPropertyList(aVersion, dataTypeID, out propertyList);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("PropertyList", propertyList);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoGetAllowedValues(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string dataTypeID;
            string filter;
            string propertyInfo;
            try
            {
                invocation.ReadStart();
                dataTypeID = invocation.ReadString("DataTypeID");
                filter = invocation.ReadString("Filter");
                invocation.ReadEnd();
                self.GetAllowedValues(aVersion, dataTypeID, filter, out propertyInfo);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("PropertyInfo", propertyInfo);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoGetStateUpdateID(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetStateUpdateID(aVersion, out id);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Id", id);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoBrowseRecordSchedules(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string filter;
            uint startingIndex;
            uint requestedCount;
            string sortCriteria;
            string result;
            uint numberReturned;
            uint totalMatches;
            uint updateID;
            try
            {
                invocation.ReadStart();
                filter = invocation.ReadString("Filter");
                startingIndex = invocation.ReadUint("StartingIndex");
                requestedCount = invocation.ReadUint("RequestedCount");
                sortCriteria = invocation.ReadString("SortCriteria");
                invocation.ReadEnd();
                self.BrowseRecordSchedules(aVersion, filter, startingIndex, requestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoBrowseRecordTasks(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordScheduleID;
            string filter;
            uint startingIndex;
            uint requestedCount;
            string sortCriteria;
            string result;
            uint numberReturned;
            uint totalMatches;
            uint updateID;
            try
            {
                invocation.ReadStart();
                recordScheduleID = invocation.ReadString("RecordScheduleID");
                filter = invocation.ReadString("Filter");
                startingIndex = invocation.ReadUint("StartingIndex");
                requestedCount = invocation.ReadUint("RequestedCount");
                sortCriteria = invocation.ReadString("SortCriteria");
                invocation.ReadEnd();
                self.BrowseRecordTasks(aVersion, recordScheduleID, filter, startingIndex, requestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoCreateRecordSchedule(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string elements;
            string recordScheduleID;
            string result;
            uint updateID;
            try
            {
                invocation.ReadStart();
                elements = invocation.ReadString("Elements");
                invocation.ReadEnd();
                self.CreateRecordSchedule(aVersion, elements, out recordScheduleID, out result, out updateID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoDeleteRecordSchedule(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordScheduleID;
            try
            {
                invocation.ReadStart();
                recordScheduleID = invocation.ReadString("RecordScheduleID");
                invocation.ReadEnd();
                self.DeleteRecordSchedule(aVersion, recordScheduleID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoGetRecordSchedule(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordScheduleID;
            string filter;
            string result;
            uint updateID;
            try
            {
                invocation.ReadStart();
                recordScheduleID = invocation.ReadString("RecordScheduleID");
                filter = invocation.ReadString("Filter");
                invocation.ReadEnd();
                self.GetRecordSchedule(aVersion, recordScheduleID, filter, out result, out updateID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Result", result);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoEnableRecordSchedule(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordScheduleID;
            try
            {
                invocation.ReadStart();
                recordScheduleID = invocation.ReadString("RecordScheduleID");
                invocation.ReadEnd();
                self.EnableRecordSchedule(aVersion, recordScheduleID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoDisableRecordSchedule(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordScheduleID;
            try
            {
                invocation.ReadStart();
                recordScheduleID = invocation.ReadString("RecordScheduleID");
                invocation.ReadEnd();
                self.DisableRecordSchedule(aVersion, recordScheduleID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoDeleteRecordTask(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordTaskID;
            try
            {
                invocation.ReadStart();
                recordTaskID = invocation.ReadString("RecordTaskID");
                invocation.ReadEnd();
                self.DeleteRecordTask(aVersion, recordTaskID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoGetRecordTask(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordTaskID;
            string filter;
            string result;
            uint updateID;
            try
            {
                invocation.ReadStart();
                recordTaskID = invocation.ReadString("RecordTaskID");
                filter = invocation.ReadString("Filter");
                invocation.ReadEnd();
                self.GetRecordTask(aVersion, recordTaskID, filter, out result, out updateID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Result", result);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoEnableRecordTask(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordTaskID;
            try
            {
                invocation.ReadStart();
                recordTaskID = invocation.ReadString("RecordTaskID");
                invocation.ReadEnd();
                self.EnableRecordTask(aVersion, recordTaskID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoDisableRecordTask(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordTaskID;
            try
            {
                invocation.ReadStart();
                recordTaskID = invocation.ReadString("RecordTaskID");
                invocation.ReadEnd();
                self.DisableRecordTask(aVersion, recordTaskID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoResetRecordTask(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordTaskID;
            try
            {
                invocation.ReadStart();
                recordTaskID = invocation.ReadString("RecordTaskID");
                invocation.ReadEnd();
                self.ResetRecordTask(aVersion, recordTaskID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoGetRecordScheduleConflicts(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordScheduleID;
            string recordScheduleConflictIDList;
            uint updateID;
            try
            {
                invocation.ReadStart();
                recordScheduleID = invocation.ReadString("RecordScheduleID");
                invocation.ReadEnd();
                self.GetRecordScheduleConflicts(aVersion, recordScheduleID, out recordScheduleConflictIDList, out updateID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("RecordScheduleConflictIDList", recordScheduleConflictIDList);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoGetRecordTaskConflicts(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgScheduledRecording2 self = (DvProviderUpnpOrgScheduledRecording2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string recordTaskID;
            string recordTaskConflictIDList;
            uint updateID;
            try
            {
                invocation.ReadStart();
                recordTaskID = invocation.ReadString("RecordTaskID");
                invocation.ReadEnd();
                self.GetRecordTaskConflicts(aVersion, recordTaskID, out recordTaskConflictIDList, out updateID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("RecordTaskConflictIDList", recordTaskConflictIDList);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
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

