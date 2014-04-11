using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgScheduledRecording2 : ICpProxy, IDisposable
    {
        void SyncGetSortCapabilities(out String aSortCaps, out uint aSortLevelCap);
        void BeginGetSortCapabilities(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetSortCapabilities(IntPtr aAsyncHandle, out String aSortCaps, out uint aSortLevelCap);
        void SyncGetPropertyList(String aDataTypeID, out String aPropertyList);
        void BeginGetPropertyList(String aDataTypeID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetPropertyList(IntPtr aAsyncHandle, out String aPropertyList);
        void SyncGetAllowedValues(String aDataTypeID, String aFilter, out String aPropertyInfo);
        void BeginGetAllowedValues(String aDataTypeID, String aFilter, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetAllowedValues(IntPtr aAsyncHandle, out String aPropertyInfo);
        void SyncGetStateUpdateID(out uint aId);
        void BeginGetStateUpdateID(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetStateUpdateID(IntPtr aAsyncHandle, out uint aId);
        void SyncBrowseRecordSchedules(String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID);
        void BeginBrowseRecordSchedules(String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, CpProxy.CallbackAsyncComplete aCallback);
        void EndBrowseRecordSchedules(IntPtr aAsyncHandle, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID);
        void SyncBrowseRecordTasks(String aRecordScheduleID, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID);
        void BeginBrowseRecordTasks(String aRecordScheduleID, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, CpProxy.CallbackAsyncComplete aCallback);
        void EndBrowseRecordTasks(IntPtr aAsyncHandle, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID);
        void SyncCreateRecordSchedule(String aElements, out String aRecordScheduleID, out String aResult, out uint aUpdateID);
        void BeginCreateRecordSchedule(String aElements, CpProxy.CallbackAsyncComplete aCallback);
        void EndCreateRecordSchedule(IntPtr aAsyncHandle, out String aRecordScheduleID, out String aResult, out uint aUpdateID);
        void SyncDeleteRecordSchedule(String aRecordScheduleID);
        void BeginDeleteRecordSchedule(String aRecordScheduleID, CpProxy.CallbackAsyncComplete aCallback);
        void EndDeleteRecordSchedule(IntPtr aAsyncHandle);
        void SyncGetRecordSchedule(String aRecordScheduleID, String aFilter, out String aResult, out uint aUpdateID);
        void BeginGetRecordSchedule(String aRecordScheduleID, String aFilter, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRecordSchedule(IntPtr aAsyncHandle, out String aResult, out uint aUpdateID);
        void SyncEnableRecordSchedule(String aRecordScheduleID);
        void BeginEnableRecordSchedule(String aRecordScheduleID, CpProxy.CallbackAsyncComplete aCallback);
        void EndEnableRecordSchedule(IntPtr aAsyncHandle);
        void SyncDisableRecordSchedule(String aRecordScheduleID);
        void BeginDisableRecordSchedule(String aRecordScheduleID, CpProxy.CallbackAsyncComplete aCallback);
        void EndDisableRecordSchedule(IntPtr aAsyncHandle);
        void SyncDeleteRecordTask(String aRecordTaskID);
        void BeginDeleteRecordTask(String aRecordTaskID, CpProxy.CallbackAsyncComplete aCallback);
        void EndDeleteRecordTask(IntPtr aAsyncHandle);
        void SyncGetRecordTask(String aRecordTaskID, String aFilter, out String aResult, out uint aUpdateID);
        void BeginGetRecordTask(String aRecordTaskID, String aFilter, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRecordTask(IntPtr aAsyncHandle, out String aResult, out uint aUpdateID);
        void SyncEnableRecordTask(String aRecordTaskID);
        void BeginEnableRecordTask(String aRecordTaskID, CpProxy.CallbackAsyncComplete aCallback);
        void EndEnableRecordTask(IntPtr aAsyncHandle);
        void SyncDisableRecordTask(String aRecordTaskID);
        void BeginDisableRecordTask(String aRecordTaskID, CpProxy.CallbackAsyncComplete aCallback);
        void EndDisableRecordTask(IntPtr aAsyncHandle);
        void SyncResetRecordTask(String aRecordTaskID);
        void BeginResetRecordTask(String aRecordTaskID, CpProxy.CallbackAsyncComplete aCallback);
        void EndResetRecordTask(IntPtr aAsyncHandle);
        void SyncGetRecordScheduleConflicts(String aRecordScheduleID, out String aRecordScheduleConflictIDList, out uint aUpdateID);
        void BeginGetRecordScheduleConflicts(String aRecordScheduleID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRecordScheduleConflicts(IntPtr aAsyncHandle, out String aRecordScheduleConflictIDList, out uint aUpdateID);
        void SyncGetRecordTaskConflicts(String aRecordTaskID, out String aRecordTaskConflictIDList, out uint aUpdateID);
        void BeginGetRecordTaskConflicts(String aRecordTaskID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRecordTaskConflicts(IntPtr aAsyncHandle, out String aRecordTaskConflictIDList, out uint aUpdateID);
        void SetPropertyLastChangeChanged(System.Action aLastChangeChanged);
        String PropertyLastChange();
    }

    internal class SyncGetSortCapabilitiesUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;
        private String iSortCaps;
        private uint iSortLevelCap;

        public SyncGetSortCapabilitiesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        public String SortCaps()
        {
            return iSortCaps;
        }
        public uint SortLevelCap()
        {
            return iSortLevelCap;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetSortCapabilities(aAsyncHandle, out iSortCaps, out iSortLevelCap);
        }
    };

    internal class SyncGetPropertyListUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;
        private String iPropertyList;

        public SyncGetPropertyListUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        public String PropertyList()
        {
            return iPropertyList;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetPropertyList(aAsyncHandle, out iPropertyList);
        }
    };

    internal class SyncGetAllowedValuesUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;
        private String iPropertyInfo;

        public SyncGetAllowedValuesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        public String PropertyInfo()
        {
            return iPropertyInfo;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetAllowedValues(aAsyncHandle, out iPropertyInfo);
        }
    };

    internal class SyncGetStateUpdateIDUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;
        private uint iId;

        public SyncGetStateUpdateIDUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        public uint Id()
        {
            return iId;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetStateUpdateID(aAsyncHandle, out iId);
        }
    };

    internal class SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;
        private String iResult;
        private uint iNumberReturned;
        private uint iTotalMatches;
        private uint iUpdateID;

        public SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        public String Result()
        {
            return iResult;
        }
        public uint NumberReturned()
        {
            return iNumberReturned;
        }
        public uint TotalMatches()
        {
            return iTotalMatches;
        }
        public uint UpdateID()
        {
            return iUpdateID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndBrowseRecordSchedules(aAsyncHandle, out iResult, out iNumberReturned, out iTotalMatches, out iUpdateID);
        }
    };

    internal class SyncBrowseRecordTasksUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;
        private String iResult;
        private uint iNumberReturned;
        private uint iTotalMatches;
        private uint iUpdateID;

        public SyncBrowseRecordTasksUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        public String Result()
        {
            return iResult;
        }
        public uint NumberReturned()
        {
            return iNumberReturned;
        }
        public uint TotalMatches()
        {
            return iTotalMatches;
        }
        public uint UpdateID()
        {
            return iUpdateID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndBrowseRecordTasks(aAsyncHandle, out iResult, out iNumberReturned, out iTotalMatches, out iUpdateID);
        }
    };

    internal class SyncCreateRecordScheduleUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;
        private String iRecordScheduleID;
        private String iResult;
        private uint iUpdateID;

        public SyncCreateRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        public String RecordScheduleID()
        {
            return iRecordScheduleID;
        }
        public String Result()
        {
            return iResult;
        }
        public uint UpdateID()
        {
            return iUpdateID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndCreateRecordSchedule(aAsyncHandle, out iRecordScheduleID, out iResult, out iUpdateID);
        }
    };

    internal class SyncDeleteRecordScheduleUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;

        public SyncDeleteRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDeleteRecordSchedule(aAsyncHandle);
        }
    };

    internal class SyncGetRecordScheduleUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;
        private String iResult;
        private uint iUpdateID;

        public SyncGetRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        public String Result()
        {
            return iResult;
        }
        public uint UpdateID()
        {
            return iUpdateID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRecordSchedule(aAsyncHandle, out iResult, out iUpdateID);
        }
    };

    internal class SyncEnableRecordScheduleUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;

        public SyncEnableRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndEnableRecordSchedule(aAsyncHandle);
        }
    };

    internal class SyncDisableRecordScheduleUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;

        public SyncDisableRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDisableRecordSchedule(aAsyncHandle);
        }
    };

    internal class SyncDeleteRecordTaskUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;

        public SyncDeleteRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDeleteRecordTask(aAsyncHandle);
        }
    };

    internal class SyncGetRecordTaskUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;
        private String iResult;
        private uint iUpdateID;

        public SyncGetRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        public String Result()
        {
            return iResult;
        }
        public uint UpdateID()
        {
            return iUpdateID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRecordTask(aAsyncHandle, out iResult, out iUpdateID);
        }
    };

    internal class SyncEnableRecordTaskUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;

        public SyncEnableRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndEnableRecordTask(aAsyncHandle);
        }
    };

    internal class SyncDisableRecordTaskUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;

        public SyncDisableRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDisableRecordTask(aAsyncHandle);
        }
    };

    internal class SyncResetRecordTaskUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;

        public SyncResetRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndResetRecordTask(aAsyncHandle);
        }
    };

    internal class SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;
        private String iRecordScheduleConflictIDList;
        private uint iUpdateID;

        public SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        public String RecordScheduleConflictIDList()
        {
            return iRecordScheduleConflictIDList;
        }
        public uint UpdateID()
        {
            return iUpdateID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRecordScheduleConflicts(aAsyncHandle, out iRecordScheduleConflictIDList, out iUpdateID);
        }
    };

    internal class SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2 : SyncProxyAction
    {
        private CpProxyUpnpOrgScheduledRecording2 iService;
        private String iRecordTaskConflictIDList;
        private uint iUpdateID;

        public SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
        {
            iService = aProxy;
        }
        public String RecordTaskConflictIDList()
        {
            return iRecordTaskConflictIDList;
        }
        public uint UpdateID()
        {
            return iUpdateID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRecordTaskConflicts(aAsyncHandle, out iRecordTaskConflictIDList, out iUpdateID);
        }
    };

    /// <summary>
    /// Proxy for the upnp.org:ScheduledRecording:2 UPnP service
    /// </summary>
    public class CpProxyUpnpOrgScheduledRecording2 : CpProxy, IDisposable, ICpProxyUpnpOrgScheduledRecording2
    {
        private OpenHome.Net.Core.Action iActionGetSortCapabilities;
        private OpenHome.Net.Core.Action iActionGetPropertyList;
        private OpenHome.Net.Core.Action iActionGetAllowedValues;
        private OpenHome.Net.Core.Action iActionGetStateUpdateID;
        private OpenHome.Net.Core.Action iActionBrowseRecordSchedules;
        private OpenHome.Net.Core.Action iActionBrowseRecordTasks;
        private OpenHome.Net.Core.Action iActionCreateRecordSchedule;
        private OpenHome.Net.Core.Action iActionDeleteRecordSchedule;
        private OpenHome.Net.Core.Action iActionGetRecordSchedule;
        private OpenHome.Net.Core.Action iActionEnableRecordSchedule;
        private OpenHome.Net.Core.Action iActionDisableRecordSchedule;
        private OpenHome.Net.Core.Action iActionDeleteRecordTask;
        private OpenHome.Net.Core.Action iActionGetRecordTask;
        private OpenHome.Net.Core.Action iActionEnableRecordTask;
        private OpenHome.Net.Core.Action iActionDisableRecordTask;
        private OpenHome.Net.Core.Action iActionResetRecordTask;
        private OpenHome.Net.Core.Action iActionGetRecordScheduleConflicts;
        private OpenHome.Net.Core.Action iActionGetRecordTaskConflicts;
        private PropertyString iLastChange;
        private System.Action iLastChangeChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgScheduledRecording2(CpDevice aDevice)
            : base("schemas-upnp-org", "ScheduledRecording", 2, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionGetSortCapabilities = new OpenHome.Net.Core.Action("GetSortCapabilities");
            param = new ParameterString("SortCaps", allowedValues);
            iActionGetSortCapabilities.AddOutputParameter(param);
            param = new ParameterUint("SortLevelCap");
            iActionGetSortCapabilities.AddOutputParameter(param);

            iActionGetPropertyList = new OpenHome.Net.Core.Action("GetPropertyList");
            allowedValues.Add("A_ARG_TYPE_RecordSchedule");
            allowedValues.Add("A_ARG_TYPE_RecordTask");
            allowedValues.Add("A_ARG_TYPE_RecordScheduleParts");
            param = new ParameterString("DataTypeID", allowedValues);
            iActionGetPropertyList.AddInputParameter(param);
            allowedValues.Clear();
            param = new ParameterString("PropertyList", allowedValues);
            iActionGetPropertyList.AddOutputParameter(param);

            iActionGetAllowedValues = new OpenHome.Net.Core.Action("GetAllowedValues");
            allowedValues.Add("A_ARG_TYPE_RecordSchedule");
            allowedValues.Add("A_ARG_TYPE_RecordTask");
            allowedValues.Add("A_ARG_TYPE_RecordScheduleParts");
            param = new ParameterString("DataTypeID", allowedValues);
            iActionGetAllowedValues.AddInputParameter(param);
            allowedValues.Clear();
            param = new ParameterString("Filter", allowedValues);
            iActionGetAllowedValues.AddInputParameter(param);
            param = new ParameterString("PropertyInfo", allowedValues);
            iActionGetAllowedValues.AddOutputParameter(param);

            iActionGetStateUpdateID = new OpenHome.Net.Core.Action("GetStateUpdateID");
            param = new ParameterUint("Id");
            iActionGetStateUpdateID.AddOutputParameter(param);

            iActionBrowseRecordSchedules = new OpenHome.Net.Core.Action("BrowseRecordSchedules");
            param = new ParameterString("Filter", allowedValues);
            iActionBrowseRecordSchedules.AddInputParameter(param);
            param = new ParameterUint("StartingIndex");
            iActionBrowseRecordSchedules.AddInputParameter(param);
            param = new ParameterUint("RequestedCount");
            iActionBrowseRecordSchedules.AddInputParameter(param);
            param = new ParameterString("SortCriteria", allowedValues);
            iActionBrowseRecordSchedules.AddInputParameter(param);
            param = new ParameterString("Result", allowedValues);
            iActionBrowseRecordSchedules.AddOutputParameter(param);
            param = new ParameterUint("NumberReturned");
            iActionBrowseRecordSchedules.AddOutputParameter(param);
            param = new ParameterUint("TotalMatches");
            iActionBrowseRecordSchedules.AddOutputParameter(param);
            param = new ParameterUint("UpdateID");
            iActionBrowseRecordSchedules.AddOutputParameter(param);

            iActionBrowseRecordTasks = new OpenHome.Net.Core.Action("BrowseRecordTasks");
            param = new ParameterString("RecordScheduleID", allowedValues);
            iActionBrowseRecordTasks.AddInputParameter(param);
            param = new ParameterString("Filter", allowedValues);
            iActionBrowseRecordTasks.AddInputParameter(param);
            param = new ParameterUint("StartingIndex");
            iActionBrowseRecordTasks.AddInputParameter(param);
            param = new ParameterUint("RequestedCount");
            iActionBrowseRecordTasks.AddInputParameter(param);
            param = new ParameterString("SortCriteria", allowedValues);
            iActionBrowseRecordTasks.AddInputParameter(param);
            param = new ParameterString("Result", allowedValues);
            iActionBrowseRecordTasks.AddOutputParameter(param);
            param = new ParameterUint("NumberReturned");
            iActionBrowseRecordTasks.AddOutputParameter(param);
            param = new ParameterUint("TotalMatches");
            iActionBrowseRecordTasks.AddOutputParameter(param);
            param = new ParameterUint("UpdateID");
            iActionBrowseRecordTasks.AddOutputParameter(param);

            iActionCreateRecordSchedule = new OpenHome.Net.Core.Action("CreateRecordSchedule");
            param = new ParameterString("Elements", allowedValues);
            iActionCreateRecordSchedule.AddInputParameter(param);
            param = new ParameterString("RecordScheduleID", allowedValues);
            iActionCreateRecordSchedule.AddOutputParameter(param);
            param = new ParameterString("Result", allowedValues);
            iActionCreateRecordSchedule.AddOutputParameter(param);
            param = new ParameterUint("UpdateID");
            iActionCreateRecordSchedule.AddOutputParameter(param);

            iActionDeleteRecordSchedule = new OpenHome.Net.Core.Action("DeleteRecordSchedule");
            param = new ParameterString("RecordScheduleID", allowedValues);
            iActionDeleteRecordSchedule.AddInputParameter(param);

            iActionGetRecordSchedule = new OpenHome.Net.Core.Action("GetRecordSchedule");
            param = new ParameterString("RecordScheduleID", allowedValues);
            iActionGetRecordSchedule.AddInputParameter(param);
            param = new ParameterString("Filter", allowedValues);
            iActionGetRecordSchedule.AddInputParameter(param);
            param = new ParameterString("Result", allowedValues);
            iActionGetRecordSchedule.AddOutputParameter(param);
            param = new ParameterUint("UpdateID");
            iActionGetRecordSchedule.AddOutputParameter(param);

            iActionEnableRecordSchedule = new OpenHome.Net.Core.Action("EnableRecordSchedule");
            param = new ParameterString("RecordScheduleID", allowedValues);
            iActionEnableRecordSchedule.AddInputParameter(param);

            iActionDisableRecordSchedule = new OpenHome.Net.Core.Action("DisableRecordSchedule");
            param = new ParameterString("RecordScheduleID", allowedValues);
            iActionDisableRecordSchedule.AddInputParameter(param);

            iActionDeleteRecordTask = new OpenHome.Net.Core.Action("DeleteRecordTask");
            param = new ParameterString("RecordTaskID", allowedValues);
            iActionDeleteRecordTask.AddInputParameter(param);

            iActionGetRecordTask = new OpenHome.Net.Core.Action("GetRecordTask");
            param = new ParameterString("RecordTaskID", allowedValues);
            iActionGetRecordTask.AddInputParameter(param);
            param = new ParameterString("Filter", allowedValues);
            iActionGetRecordTask.AddInputParameter(param);
            param = new ParameterString("Result", allowedValues);
            iActionGetRecordTask.AddOutputParameter(param);
            param = new ParameterUint("UpdateID");
            iActionGetRecordTask.AddOutputParameter(param);

            iActionEnableRecordTask = new OpenHome.Net.Core.Action("EnableRecordTask");
            param = new ParameterString("RecordTaskID", allowedValues);
            iActionEnableRecordTask.AddInputParameter(param);

            iActionDisableRecordTask = new OpenHome.Net.Core.Action("DisableRecordTask");
            param = new ParameterString("RecordTaskID", allowedValues);
            iActionDisableRecordTask.AddInputParameter(param);

            iActionResetRecordTask = new OpenHome.Net.Core.Action("ResetRecordTask");
            param = new ParameterString("RecordTaskID", allowedValues);
            iActionResetRecordTask.AddInputParameter(param);

            iActionGetRecordScheduleConflicts = new OpenHome.Net.Core.Action("GetRecordScheduleConflicts");
            param = new ParameterString("RecordScheduleID", allowedValues);
            iActionGetRecordScheduleConflicts.AddInputParameter(param);
            param = new ParameterString("RecordScheduleConflictIDList", allowedValues);
            iActionGetRecordScheduleConflicts.AddOutputParameter(param);
            param = new ParameterUint("UpdateID");
            iActionGetRecordScheduleConflicts.AddOutputParameter(param);

            iActionGetRecordTaskConflicts = new OpenHome.Net.Core.Action("GetRecordTaskConflicts");
            param = new ParameterString("RecordTaskID", allowedValues);
            iActionGetRecordTaskConflicts.AddInputParameter(param);
            param = new ParameterString("RecordTaskConflictIDList", allowedValues);
            iActionGetRecordTaskConflicts.AddOutputParameter(param);
            param = new ParameterUint("UpdateID");
            iActionGetRecordTaskConflicts.AddOutputParameter(param);

            iLastChange = new PropertyString("LastChange", LastChangePropertyChanged);
            AddProperty(iLastChange);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aSortCaps"></param>
        /// <param name="aSortLevelCap"></param>
        public void SyncGetSortCapabilities(out String aSortCaps, out uint aSortLevelCap)
        {
            SyncGetSortCapabilitiesUpnpOrgScheduledRecording2 sync = new SyncGetSortCapabilitiesUpnpOrgScheduledRecording2(this);
            BeginGetSortCapabilities(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSortCaps = sync.SortCaps();
            aSortLevelCap = sync.SortLevelCap();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetSortCapabilities().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetSortCapabilities(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetSortCapabilities, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetSortCapabilities.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetSortCapabilities.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aSortCaps"></param>
        /// <param name="aSortLevelCap"></param>
        public void EndGetSortCapabilities(IntPtr aAsyncHandle, out String aSortCaps, out uint aSortLevelCap)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aSortCaps = Invocation.OutputString(aAsyncHandle, index++);
            aSortLevelCap = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aDataTypeID"></param>
        /// <param name="aPropertyList"></param>
        public void SyncGetPropertyList(String aDataTypeID, out String aPropertyList)
        {
            SyncGetPropertyListUpnpOrgScheduledRecording2 sync = new SyncGetPropertyListUpnpOrgScheduledRecording2(this);
            BeginGetPropertyList(aDataTypeID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aPropertyList = sync.PropertyList();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetPropertyList().</remarks>
        /// <param name="aDataTypeID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetPropertyList(String aDataTypeID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetPropertyList, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetPropertyList.InputParameter(inIndex++), aDataTypeID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetPropertyList.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aPropertyList"></param>
        public void EndGetPropertyList(IntPtr aAsyncHandle, out String aPropertyList)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aPropertyList = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aDataTypeID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aPropertyInfo"></param>
        public void SyncGetAllowedValues(String aDataTypeID, String aFilter, out String aPropertyInfo)
        {
            SyncGetAllowedValuesUpnpOrgScheduledRecording2 sync = new SyncGetAllowedValuesUpnpOrgScheduledRecording2(this);
            BeginGetAllowedValues(aDataTypeID, aFilter, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aPropertyInfo = sync.PropertyInfo();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetAllowedValues().</remarks>
        /// <param name="aDataTypeID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetAllowedValues(String aDataTypeID, String aFilter, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetAllowedValues, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetAllowedValues.InputParameter(inIndex++), aDataTypeID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetAllowedValues.InputParameter(inIndex++), aFilter));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetAllowedValues.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aPropertyInfo"></param>
        public void EndGetAllowedValues(IntPtr aAsyncHandle, out String aPropertyInfo)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aPropertyInfo = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aId"></param>
        public void SyncGetStateUpdateID(out uint aId)
        {
            SyncGetStateUpdateIDUpnpOrgScheduledRecording2 sync = new SyncGetStateUpdateIDUpnpOrgScheduledRecording2(this);
            BeginGetStateUpdateID(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aId = sync.Id();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetStateUpdateID().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetStateUpdateID(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetStateUpdateID, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetStateUpdateID.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aId"></param>
        public void EndGetStateUpdateID(IntPtr aAsyncHandle, out uint aId)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aId = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        public void SyncBrowseRecordSchedules(String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2 sync = new SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2(this);
            BeginBrowseRecordSchedules(aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
            aNumberReturned = sync.NumberReturned();
            aTotalMatches = sync.TotalMatches();
            aUpdateID = sync.UpdateID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBrowseRecordSchedules().</remarks>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginBrowseRecordSchedules(String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionBrowseRecordSchedules, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionBrowseRecordSchedules.InputParameter(inIndex++), aFilter));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionBrowseRecordSchedules.InputParameter(inIndex++), aStartingIndex));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionBrowseRecordSchedules.InputParameter(inIndex++), aRequestedCount));
            invocation.AddInput(new ArgumentString((ParameterString)iActionBrowseRecordSchedules.InputParameter(inIndex++), aSortCriteria));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionBrowseRecordSchedules.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordSchedules.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordSchedules.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordSchedules.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        public void EndBrowseRecordSchedules(IntPtr aAsyncHandle, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aResult = Invocation.OutputString(aAsyncHandle, index++);
            aNumberReturned = Invocation.OutputUint(aAsyncHandle, index++);
            aTotalMatches = Invocation.OutputUint(aAsyncHandle, index++);
            aUpdateID = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        public void SyncBrowseRecordTasks(String aRecordScheduleID, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            SyncBrowseRecordTasksUpnpOrgScheduledRecording2 sync = new SyncBrowseRecordTasksUpnpOrgScheduledRecording2(this);
            BeginBrowseRecordTasks(aRecordScheduleID, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
            aNumberReturned = sync.NumberReturned();
            aTotalMatches = sync.TotalMatches();
            aUpdateID = sync.UpdateID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBrowseRecordTasks().</remarks>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginBrowseRecordTasks(String aRecordScheduleID, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionBrowseRecordTasks, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionBrowseRecordTasks.InputParameter(inIndex++), aRecordScheduleID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionBrowseRecordTasks.InputParameter(inIndex++), aFilter));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionBrowseRecordTasks.InputParameter(inIndex++), aStartingIndex));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionBrowseRecordTasks.InputParameter(inIndex++), aRequestedCount));
            invocation.AddInput(new ArgumentString((ParameterString)iActionBrowseRecordTasks.InputParameter(inIndex++), aSortCriteria));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionBrowseRecordTasks.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordTasks.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordTasks.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordTasks.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        public void EndBrowseRecordTasks(IntPtr aAsyncHandle, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aResult = Invocation.OutputString(aAsyncHandle, index++);
            aNumberReturned = Invocation.OutputUint(aAsyncHandle, index++);
            aTotalMatches = Invocation.OutputUint(aAsyncHandle, index++);
            aUpdateID = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aElements"></param>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aResult"></param>
        /// <param name="aUpdateID"></param>
        public void SyncCreateRecordSchedule(String aElements, out String aRecordScheduleID, out String aResult, out uint aUpdateID)
        {
            SyncCreateRecordScheduleUpnpOrgScheduledRecording2 sync = new SyncCreateRecordScheduleUpnpOrgScheduledRecording2(this);
            BeginCreateRecordSchedule(aElements, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRecordScheduleID = sync.RecordScheduleID();
            aResult = sync.Result();
            aUpdateID = sync.UpdateID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCreateRecordSchedule().</remarks>
        /// <param name="aElements"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginCreateRecordSchedule(String aElements, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionCreateRecordSchedule, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionCreateRecordSchedule.InputParameter(inIndex++), aElements));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionCreateRecordSchedule.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionCreateRecordSchedule.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionCreateRecordSchedule.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aResult"></param>
        /// <param name="aUpdateID"></param>
        public void EndCreateRecordSchedule(IntPtr aAsyncHandle, out String aRecordScheduleID, out String aResult, out uint aUpdateID)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRecordScheduleID = Invocation.OutputString(aAsyncHandle, index++);
            aResult = Invocation.OutputString(aAsyncHandle, index++);
            aUpdateID = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordScheduleID"></param>
        public void SyncDeleteRecordSchedule(String aRecordScheduleID)
        {
            SyncDeleteRecordScheduleUpnpOrgScheduledRecording2 sync = new SyncDeleteRecordScheduleUpnpOrgScheduledRecording2(this);
            BeginDeleteRecordSchedule(aRecordScheduleID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDeleteRecordSchedule().</remarks>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDeleteRecordSchedule(String aRecordScheduleID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDeleteRecordSchedule, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionDeleteRecordSchedule.InputParameter(inIndex++), aRecordScheduleID));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndDeleteRecordSchedule(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aResult"></param>
        /// <param name="aUpdateID"></param>
        public void SyncGetRecordSchedule(String aRecordScheduleID, String aFilter, out String aResult, out uint aUpdateID)
        {
            SyncGetRecordScheduleUpnpOrgScheduledRecording2 sync = new SyncGetRecordScheduleUpnpOrgScheduledRecording2(this);
            BeginGetRecordSchedule(aRecordScheduleID, aFilter, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
            aUpdateID = sync.UpdateID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRecordSchedule().</remarks>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRecordSchedule(String aRecordScheduleID, String aFilter, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRecordSchedule, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetRecordSchedule.InputParameter(inIndex++), aRecordScheduleID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetRecordSchedule.InputParameter(inIndex++), aFilter));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetRecordSchedule.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetRecordSchedule.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        /// <param name="aUpdateID"></param>
        public void EndGetRecordSchedule(IntPtr aAsyncHandle, out String aResult, out uint aUpdateID)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aResult = Invocation.OutputString(aAsyncHandle, index++);
            aUpdateID = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordScheduleID"></param>
        public void SyncEnableRecordSchedule(String aRecordScheduleID)
        {
            SyncEnableRecordScheduleUpnpOrgScheduledRecording2 sync = new SyncEnableRecordScheduleUpnpOrgScheduledRecording2(this);
            BeginEnableRecordSchedule(aRecordScheduleID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEnableRecordSchedule().</remarks>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginEnableRecordSchedule(String aRecordScheduleID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionEnableRecordSchedule, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionEnableRecordSchedule.InputParameter(inIndex++), aRecordScheduleID));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndEnableRecordSchedule(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordScheduleID"></param>
        public void SyncDisableRecordSchedule(String aRecordScheduleID)
        {
            SyncDisableRecordScheduleUpnpOrgScheduledRecording2 sync = new SyncDisableRecordScheduleUpnpOrgScheduledRecording2(this);
            BeginDisableRecordSchedule(aRecordScheduleID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisableRecordSchedule().</remarks>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDisableRecordSchedule(String aRecordScheduleID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDisableRecordSchedule, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionDisableRecordSchedule.InputParameter(inIndex++), aRecordScheduleID));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndDisableRecordSchedule(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordTaskID"></param>
        public void SyncDeleteRecordTask(String aRecordTaskID)
        {
            SyncDeleteRecordTaskUpnpOrgScheduledRecording2 sync = new SyncDeleteRecordTaskUpnpOrgScheduledRecording2(this);
            BeginDeleteRecordTask(aRecordTaskID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDeleteRecordTask().</remarks>
        /// <param name="aRecordTaskID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDeleteRecordTask(String aRecordTaskID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDeleteRecordTask, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionDeleteRecordTask.InputParameter(inIndex++), aRecordTaskID));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndDeleteRecordTask(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordTaskID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aResult"></param>
        /// <param name="aUpdateID"></param>
        public void SyncGetRecordTask(String aRecordTaskID, String aFilter, out String aResult, out uint aUpdateID)
        {
            SyncGetRecordTaskUpnpOrgScheduledRecording2 sync = new SyncGetRecordTaskUpnpOrgScheduledRecording2(this);
            BeginGetRecordTask(aRecordTaskID, aFilter, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
            aUpdateID = sync.UpdateID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRecordTask().</remarks>
        /// <param name="aRecordTaskID"></param>
        /// <param name="aFilter"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRecordTask(String aRecordTaskID, String aFilter, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRecordTask, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetRecordTask.InputParameter(inIndex++), aRecordTaskID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetRecordTask.InputParameter(inIndex++), aFilter));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetRecordTask.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetRecordTask.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        /// <param name="aUpdateID"></param>
        public void EndGetRecordTask(IntPtr aAsyncHandle, out String aResult, out uint aUpdateID)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aResult = Invocation.OutputString(aAsyncHandle, index++);
            aUpdateID = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordTaskID"></param>
        public void SyncEnableRecordTask(String aRecordTaskID)
        {
            SyncEnableRecordTaskUpnpOrgScheduledRecording2 sync = new SyncEnableRecordTaskUpnpOrgScheduledRecording2(this);
            BeginEnableRecordTask(aRecordTaskID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEnableRecordTask().</remarks>
        /// <param name="aRecordTaskID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginEnableRecordTask(String aRecordTaskID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionEnableRecordTask, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionEnableRecordTask.InputParameter(inIndex++), aRecordTaskID));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndEnableRecordTask(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordTaskID"></param>
        public void SyncDisableRecordTask(String aRecordTaskID)
        {
            SyncDisableRecordTaskUpnpOrgScheduledRecording2 sync = new SyncDisableRecordTaskUpnpOrgScheduledRecording2(this);
            BeginDisableRecordTask(aRecordTaskID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisableRecordTask().</remarks>
        /// <param name="aRecordTaskID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDisableRecordTask(String aRecordTaskID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDisableRecordTask, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionDisableRecordTask.InputParameter(inIndex++), aRecordTaskID));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndDisableRecordTask(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordTaskID"></param>
        public void SyncResetRecordTask(String aRecordTaskID)
        {
            SyncResetRecordTaskUpnpOrgScheduledRecording2 sync = new SyncResetRecordTaskUpnpOrgScheduledRecording2(this);
            BeginResetRecordTask(aRecordTaskID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndResetRecordTask().</remarks>
        /// <param name="aRecordTaskID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginResetRecordTask(String aRecordTaskID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionResetRecordTask, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionResetRecordTask.InputParameter(inIndex++), aRecordTaskID));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndResetRecordTask(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aRecordScheduleConflictIDList"></param>
        /// <param name="aUpdateID"></param>
        public void SyncGetRecordScheduleConflicts(String aRecordScheduleID, out String aRecordScheduleConflictIDList, out uint aUpdateID)
        {
            SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2 sync = new SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2(this);
            BeginGetRecordScheduleConflicts(aRecordScheduleID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRecordScheduleConflictIDList = sync.RecordScheduleConflictIDList();
            aUpdateID = sync.UpdateID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRecordScheduleConflicts().</remarks>
        /// <param name="aRecordScheduleID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRecordScheduleConflicts(String aRecordScheduleID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRecordScheduleConflicts, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetRecordScheduleConflicts.InputParameter(inIndex++), aRecordScheduleID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetRecordScheduleConflicts.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetRecordScheduleConflicts.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRecordScheduleConflictIDList"></param>
        /// <param name="aUpdateID"></param>
        public void EndGetRecordScheduleConflicts(IntPtr aAsyncHandle, out String aRecordScheduleConflictIDList, out uint aUpdateID)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRecordScheduleConflictIDList = Invocation.OutputString(aAsyncHandle, index++);
            aUpdateID = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRecordTaskID"></param>
        /// <param name="aRecordTaskConflictIDList"></param>
        /// <param name="aUpdateID"></param>
        public void SyncGetRecordTaskConflicts(String aRecordTaskID, out String aRecordTaskConflictIDList, out uint aUpdateID)
        {
            SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2 sync = new SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2(this);
            BeginGetRecordTaskConflicts(aRecordTaskID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRecordTaskConflictIDList = sync.RecordTaskConflictIDList();
            aUpdateID = sync.UpdateID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRecordTaskConflicts().</remarks>
        /// <param name="aRecordTaskID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRecordTaskConflicts(String aRecordTaskID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRecordTaskConflicts, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetRecordTaskConflicts.InputParameter(inIndex++), aRecordTaskID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetRecordTaskConflicts.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetRecordTaskConflicts.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRecordTaskConflictIDList"></param>
        /// <param name="aUpdateID"></param>
        public void EndGetRecordTaskConflicts(IntPtr aAsyncHandle, out String aRecordTaskConflictIDList, out uint aUpdateID)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRecordTaskConflictIDList = Invocation.OutputString(aAsyncHandle, index++);
            aUpdateID = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the LastChange state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgScheduledRecording2 instance will not overlap.</remarks>
        /// <param name="aLastChangeChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyLastChangeChanged(System.Action aLastChangeChanged)
        {
            lock (iPropertyLock)
            {
                iLastChangeChanged = aLastChangeChanged;
            }
        }

        private void LastChangePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iLastChangeChanged);
            }
        }

        /// <summary>
        /// Query the value of the LastChange property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the LastChange property</returns>
        public String PropertyLastChange()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iLastChange.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                DisposeProxy();
                iHandle = IntPtr.Zero;
            }
            iActionGetSortCapabilities.Dispose();
            iActionGetPropertyList.Dispose();
            iActionGetAllowedValues.Dispose();
            iActionGetStateUpdateID.Dispose();
            iActionBrowseRecordSchedules.Dispose();
            iActionBrowseRecordTasks.Dispose();
            iActionCreateRecordSchedule.Dispose();
            iActionDeleteRecordSchedule.Dispose();
            iActionGetRecordSchedule.Dispose();
            iActionEnableRecordSchedule.Dispose();
            iActionDisableRecordSchedule.Dispose();
            iActionDeleteRecordTask.Dispose();
            iActionGetRecordTask.Dispose();
            iActionEnableRecordTask.Dispose();
            iActionDisableRecordTask.Dispose();
            iActionResetRecordTask.Dispose();
            iActionGetRecordScheduleConflicts.Dispose();
            iActionGetRecordTaskConflicts.Dispose();
            iLastChange.Dispose();
        }
    }
}

