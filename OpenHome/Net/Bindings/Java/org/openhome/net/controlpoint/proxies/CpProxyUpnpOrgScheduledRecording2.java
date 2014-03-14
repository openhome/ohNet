package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyUpnpOrgScheduledRecording2.*;
import org.openhome.net.core.*;

    
interface ICpProxyUpnpOrgScheduledRecording2 extends ICpProxy
{
    public GetSortCapabilities syncGetSortCapabilities();
    public void beginGetSortCapabilities(ICpProxyListener aCallback);
    public GetSortCapabilities endGetSortCapabilities(long aAsyncHandle);
    public String syncGetPropertyList(String aDataTypeID);
    public void beginGetPropertyList(String aDataTypeID, ICpProxyListener aCallback);
    public String endGetPropertyList(long aAsyncHandle);
    public String syncGetAllowedValues(String aDataTypeID, String aFilter);
    public void beginGetAllowedValues(String aDataTypeID, String aFilter, ICpProxyListener aCallback);
    public String endGetAllowedValues(long aAsyncHandle);
    public long syncGetStateUpdateID();
    public void beginGetStateUpdateID(ICpProxyListener aCallback);
    public long endGetStateUpdateID(long aAsyncHandle);
    public BrowseRecordSchedules syncBrowseRecordSchedules(String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria);
    public void beginBrowseRecordSchedules(String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria, ICpProxyListener aCallback);
    public BrowseRecordSchedules endBrowseRecordSchedules(long aAsyncHandle);
    public BrowseRecordTasks syncBrowseRecordTasks(String aRecordScheduleID, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria);
    public void beginBrowseRecordTasks(String aRecordScheduleID, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria, ICpProxyListener aCallback);
    public BrowseRecordTasks endBrowseRecordTasks(long aAsyncHandle);
    public CreateRecordSchedule syncCreateRecordSchedule(String aElements);
    public void beginCreateRecordSchedule(String aElements, ICpProxyListener aCallback);
    public CreateRecordSchedule endCreateRecordSchedule(long aAsyncHandle);
    public void syncDeleteRecordSchedule(String aRecordScheduleID);
    public void beginDeleteRecordSchedule(String aRecordScheduleID, ICpProxyListener aCallback);
    public void endDeleteRecordSchedule(long aAsyncHandle);
    public GetRecordSchedule syncGetRecordSchedule(String aRecordScheduleID, String aFilter);
    public void beginGetRecordSchedule(String aRecordScheduleID, String aFilter, ICpProxyListener aCallback);
    public GetRecordSchedule endGetRecordSchedule(long aAsyncHandle);
    public void syncEnableRecordSchedule(String aRecordScheduleID);
    public void beginEnableRecordSchedule(String aRecordScheduleID, ICpProxyListener aCallback);
    public void endEnableRecordSchedule(long aAsyncHandle);
    public void syncDisableRecordSchedule(String aRecordScheduleID);
    public void beginDisableRecordSchedule(String aRecordScheduleID, ICpProxyListener aCallback);
    public void endDisableRecordSchedule(long aAsyncHandle);
    public void syncDeleteRecordTask(String aRecordTaskID);
    public void beginDeleteRecordTask(String aRecordTaskID, ICpProxyListener aCallback);
    public void endDeleteRecordTask(long aAsyncHandle);
    public GetRecordTask syncGetRecordTask(String aRecordTaskID, String aFilter);
    public void beginGetRecordTask(String aRecordTaskID, String aFilter, ICpProxyListener aCallback);
    public GetRecordTask endGetRecordTask(long aAsyncHandle);
    public void syncEnableRecordTask(String aRecordTaskID);
    public void beginEnableRecordTask(String aRecordTaskID, ICpProxyListener aCallback);
    public void endEnableRecordTask(long aAsyncHandle);
    public void syncDisableRecordTask(String aRecordTaskID);
    public void beginDisableRecordTask(String aRecordTaskID, ICpProxyListener aCallback);
    public void endDisableRecordTask(long aAsyncHandle);
    public void syncResetRecordTask(String aRecordTaskID);
    public void beginResetRecordTask(String aRecordTaskID, ICpProxyListener aCallback);
    public void endResetRecordTask(long aAsyncHandle);
    public GetRecordScheduleConflicts syncGetRecordScheduleConflicts(String aRecordScheduleID);
    public void beginGetRecordScheduleConflicts(String aRecordScheduleID, ICpProxyListener aCallback);
    public GetRecordScheduleConflicts endGetRecordScheduleConflicts(long aAsyncHandle);
    public GetRecordTaskConflicts syncGetRecordTaskConflicts(String aRecordTaskID);
    public void beginGetRecordTaskConflicts(String aRecordTaskID, ICpProxyListener aCallback);
    public GetRecordTaskConflicts endGetRecordTaskConflicts(long aAsyncHandle);
    public void setPropertyLastChangeChanged(IPropertyChangeListener aLastChangeChanged);
    public String getPropertyLastChange();
}

class SyncGetSortCapabilitiesUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;
    private String iSortCaps;
    private long iSortLevelCap;

    public SyncGetSortCapabilitiesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    public String getSortCaps()
    {
        return iSortCaps;
    }
    public long getSortLevelCap()
    {
        return iSortLevelCap;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetSortCapabilities result = iService.endGetSortCapabilities(aAsyncHandle);
        
        iSortCaps = result.getSortCaps();
        iSortLevelCap = result.getSortLevelCap();
    }
}

class SyncGetPropertyListUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;
    private String iPropertyList;

    public SyncGetPropertyListUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    public String getPropertyList()
    {
        return iPropertyList;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetPropertyList(aAsyncHandle);
        
        iPropertyList = result;
    }
}

class SyncGetAllowedValuesUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;
    private String iPropertyInfo;

    public SyncGetAllowedValuesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    public String getPropertyInfo()
    {
        return iPropertyInfo;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetAllowedValues(aAsyncHandle);
        
        iPropertyInfo = result;
    }
}

class SyncGetStateUpdateIDUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;
    private long iId;

    public SyncGetStateUpdateIDUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    public long getId()
    {
        return iId;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetStateUpdateID(aAsyncHandle);
        
        iId = result;
    }
}

class SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;
    private String iResult;
    private long iNumberReturned;
    private long iTotalMatches;
    private long iUpdateID;

    public SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    public String getResult()
    {
        return iResult;
    }
    public long getNumberReturned()
    {
        return iNumberReturned;
    }
    public long getTotalMatches()
    {
        return iTotalMatches;
    }
    public long getUpdateID()
    {
        return iUpdateID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        BrowseRecordSchedules result = iService.endBrowseRecordSchedules(aAsyncHandle);
        
        iResult = result.getResult();
        iNumberReturned = result.getNumberReturned();
        iTotalMatches = result.getTotalMatches();
        iUpdateID = result.getUpdateID();
    }
}

class SyncBrowseRecordTasksUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;
    private String iResult;
    private long iNumberReturned;
    private long iTotalMatches;
    private long iUpdateID;

    public SyncBrowseRecordTasksUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    public String getResult()
    {
        return iResult;
    }
    public long getNumberReturned()
    {
        return iNumberReturned;
    }
    public long getTotalMatches()
    {
        return iTotalMatches;
    }
    public long getUpdateID()
    {
        return iUpdateID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        BrowseRecordTasks result = iService.endBrowseRecordTasks(aAsyncHandle);
        
        iResult = result.getResult();
        iNumberReturned = result.getNumberReturned();
        iTotalMatches = result.getTotalMatches();
        iUpdateID = result.getUpdateID();
    }
}

class SyncCreateRecordScheduleUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;
    private String iRecordScheduleID;
    private String iResult;
    private long iUpdateID;

    public SyncCreateRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    public String getRecordScheduleID()
    {
        return iRecordScheduleID;
    }
    public String getResult()
    {
        return iResult;
    }
    public long getUpdateID()
    {
        return iUpdateID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        CreateRecordSchedule result = iService.endCreateRecordSchedule(aAsyncHandle);
        
        iRecordScheduleID = result.getRecordScheduleID();
        iResult = result.getResult();
        iUpdateID = result.getUpdateID();
    }
}

class SyncDeleteRecordScheduleUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;

    public SyncDeleteRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endDeleteRecordSchedule(aAsyncHandle);
        
    }
}

class SyncGetRecordScheduleUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;
    private String iResult;
    private long iUpdateID;

    public SyncGetRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    public String getResult()
    {
        return iResult;
    }
    public long getUpdateID()
    {
        return iUpdateID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetRecordSchedule result = iService.endGetRecordSchedule(aAsyncHandle);
        
        iResult = result.getResult();
        iUpdateID = result.getUpdateID();
    }
}

class SyncEnableRecordScheduleUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;

    public SyncEnableRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endEnableRecordSchedule(aAsyncHandle);
        
    }
}

class SyncDisableRecordScheduleUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;

    public SyncDisableRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endDisableRecordSchedule(aAsyncHandle);
        
    }
}

class SyncDeleteRecordTaskUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;

    public SyncDeleteRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endDeleteRecordTask(aAsyncHandle);
        
    }
}

class SyncGetRecordTaskUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;
    private String iResult;
    private long iUpdateID;

    public SyncGetRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    public String getResult()
    {
        return iResult;
    }
    public long getUpdateID()
    {
        return iUpdateID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetRecordTask result = iService.endGetRecordTask(aAsyncHandle);
        
        iResult = result.getResult();
        iUpdateID = result.getUpdateID();
    }
}

class SyncEnableRecordTaskUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;

    public SyncEnableRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endEnableRecordTask(aAsyncHandle);
        
    }
}

class SyncDisableRecordTaskUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;

    public SyncDisableRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endDisableRecordTask(aAsyncHandle);
        
    }
}

class SyncResetRecordTaskUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;

    public SyncResetRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endResetRecordTask(aAsyncHandle);
        
    }
}

class SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;
    private String iRecordScheduleConflictIDList;
    private long iUpdateID;

    public SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    public String getRecordScheduleConflictIDList()
    {
        return iRecordScheduleConflictIDList;
    }
    public long getUpdateID()
    {
        return iUpdateID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetRecordScheduleConflicts result = iService.endGetRecordScheduleConflicts(aAsyncHandle);
        
        iRecordScheduleConflictIDList = result.getRecordScheduleConflictIDList();
        iUpdateID = result.getUpdateID();
    }
}

class SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2 extends SyncProxyAction
{
    private CpProxyUpnpOrgScheduledRecording2 iService;
    private String iRecordTaskConflictIDList;
    private long iUpdateID;

    public SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2 aProxy)
    {
        iService = aProxy;
    }
    public String getRecordTaskConflictIDList()
    {
        return iRecordTaskConflictIDList;
    }
    public long getUpdateID()
    {
        return iUpdateID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetRecordTaskConflicts result = iService.endGetRecordTaskConflicts(aAsyncHandle);
        
        iRecordTaskConflictIDList = result.getRecordTaskConflictIDList();
        iUpdateID = result.getUpdateID();
    }
}

/**
 * Proxy for the upnp.org:ScheduledRecording:2 UPnP service
 */
public class CpProxyUpnpOrgScheduledRecording2 extends CpProxy implements ICpProxyUpnpOrgScheduledRecording2
{

    public class GetSortCapabilities
    {
        private String iSortCaps;
        private long iSortLevelCap;

        public GetSortCapabilities(
            String aSortCaps,
            long aSortLevelCap
        )
        {
            iSortCaps = aSortCaps;
            iSortLevelCap = aSortLevelCap;
        }
        public String getSortCaps()
        {
            return iSortCaps;
        }
        public long getSortLevelCap()
        {
            return iSortLevelCap;
        }
    }

    public class BrowseRecordSchedules
    {
        private String iResult;
        private long iNumberReturned;
        private long iTotalMatches;
        private long iUpdateID;

        public BrowseRecordSchedules(
            String aResult,
            long aNumberReturned,
            long aTotalMatches,
            long aUpdateID
        )
        {
            iResult = aResult;
            iNumberReturned = aNumberReturned;
            iTotalMatches = aTotalMatches;
            iUpdateID = aUpdateID;
        }
        public String getResult()
        {
            return iResult;
        }
        public long getNumberReturned()
        {
            return iNumberReturned;
        }
        public long getTotalMatches()
        {
            return iTotalMatches;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class BrowseRecordTasks
    {
        private String iResult;
        private long iNumberReturned;
        private long iTotalMatches;
        private long iUpdateID;

        public BrowseRecordTasks(
            String aResult,
            long aNumberReturned,
            long aTotalMatches,
            long aUpdateID
        )
        {
            iResult = aResult;
            iNumberReturned = aNumberReturned;
            iTotalMatches = aTotalMatches;
            iUpdateID = aUpdateID;
        }
        public String getResult()
        {
            return iResult;
        }
        public long getNumberReturned()
        {
            return iNumberReturned;
        }
        public long getTotalMatches()
        {
            return iTotalMatches;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class CreateRecordSchedule
    {
        private String iRecordScheduleID;
        private String iResult;
        private long iUpdateID;

        public CreateRecordSchedule(
            String aRecordScheduleID,
            String aResult,
            long aUpdateID
        )
        {
            iRecordScheduleID = aRecordScheduleID;
            iResult = aResult;
            iUpdateID = aUpdateID;
        }
        public String getRecordScheduleID()
        {
            return iRecordScheduleID;
        }
        public String getResult()
        {
            return iResult;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class GetRecordSchedule
    {
        private String iResult;
        private long iUpdateID;

        public GetRecordSchedule(
            String aResult,
            long aUpdateID
        )
        {
            iResult = aResult;
            iUpdateID = aUpdateID;
        }
        public String getResult()
        {
            return iResult;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class GetRecordTask
    {
        private String iResult;
        private long iUpdateID;

        public GetRecordTask(
            String aResult,
            long aUpdateID
        )
        {
            iResult = aResult;
            iUpdateID = aUpdateID;
        }
        public String getResult()
        {
            return iResult;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class GetRecordScheduleConflicts
    {
        private String iRecordScheduleConflictIDList;
        private long iUpdateID;

        public GetRecordScheduleConflicts(
            String aRecordScheduleConflictIDList,
            long aUpdateID
        )
        {
            iRecordScheduleConflictIDList = aRecordScheduleConflictIDList;
            iUpdateID = aUpdateID;
        }
        public String getRecordScheduleConflictIDList()
        {
            return iRecordScheduleConflictIDList;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class GetRecordTaskConflicts
    {
        private String iRecordTaskConflictIDList;
        private long iUpdateID;

        public GetRecordTaskConflicts(
            String aRecordTaskConflictIDList,
            long aUpdateID
        )
        {
            iRecordTaskConflictIDList = aRecordTaskConflictIDList;
            iUpdateID = aUpdateID;
        }
        public String getRecordTaskConflictIDList()
        {
            return iRecordTaskConflictIDList;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    private Action iActionGetSortCapabilities;
    private Action iActionGetPropertyList;
    private Action iActionGetAllowedValues;
    private Action iActionGetStateUpdateID;
    private Action iActionBrowseRecordSchedules;
    private Action iActionBrowseRecordTasks;
    private Action iActionCreateRecordSchedule;
    private Action iActionDeleteRecordSchedule;
    private Action iActionGetRecordSchedule;
    private Action iActionEnableRecordSchedule;
    private Action iActionDisableRecordSchedule;
    private Action iActionDeleteRecordTask;
    private Action iActionGetRecordTask;
    private Action iActionEnableRecordTask;
    private Action iActionDisableRecordTask;
    private Action iActionResetRecordTask;
    private Action iActionGetRecordScheduleConflicts;
    private Action iActionGetRecordTaskConflicts;
    private PropertyString iLastChange;
    private IPropertyChangeListener iLastChangeChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyUpnpOrgScheduledRecording2(CpDevice aDevice)
    {
        super("schemas-upnp-org", "ScheduledRecording", 2, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionGetSortCapabilities = new Action("GetSortCapabilities");
        param = new ParameterString("SortCaps", allowedValues);
        iActionGetSortCapabilities.addOutputParameter(param);
        param = new ParameterUint("SortLevelCap");
        iActionGetSortCapabilities.addOutputParameter(param);

        iActionGetPropertyList = new Action("GetPropertyList");
        allowedValues.add("A_ARG_TYPE_RecordSchedule");
        allowedValues.add("A_ARG_TYPE_RecordTask");
        allowedValues.add("A_ARG_TYPE_RecordScheduleParts");
        param = new ParameterString("DataTypeID", allowedValues);
        iActionGetPropertyList.addInputParameter(param);
        allowedValues.clear();
        param = new ParameterString("PropertyList", allowedValues);
        iActionGetPropertyList.addOutputParameter(param);

        iActionGetAllowedValues = new Action("GetAllowedValues");
        allowedValues.add("A_ARG_TYPE_RecordSchedule");
        allowedValues.add("A_ARG_TYPE_RecordTask");
        allowedValues.add("A_ARG_TYPE_RecordScheduleParts");
        param = new ParameterString("DataTypeID", allowedValues);
        iActionGetAllowedValues.addInputParameter(param);
        allowedValues.clear();
        param = new ParameterString("Filter", allowedValues);
        iActionGetAllowedValues.addInputParameter(param);
        param = new ParameterString("PropertyInfo", allowedValues);
        iActionGetAllowedValues.addOutputParameter(param);

        iActionGetStateUpdateID = new Action("GetStateUpdateID");
        param = new ParameterUint("Id");
        iActionGetStateUpdateID.addOutputParameter(param);

        iActionBrowseRecordSchedules = new Action("BrowseRecordSchedules");
        param = new ParameterString("Filter", allowedValues);
        iActionBrowseRecordSchedules.addInputParameter(param);
        param = new ParameterUint("StartingIndex");
        iActionBrowseRecordSchedules.addInputParameter(param);
        param = new ParameterUint("RequestedCount");
        iActionBrowseRecordSchedules.addInputParameter(param);
        param = new ParameterString("SortCriteria", allowedValues);
        iActionBrowseRecordSchedules.addInputParameter(param);
        param = new ParameterString("Result", allowedValues);
        iActionBrowseRecordSchedules.addOutputParameter(param);
        param = new ParameterUint("NumberReturned");
        iActionBrowseRecordSchedules.addOutputParameter(param);
        param = new ParameterUint("TotalMatches");
        iActionBrowseRecordSchedules.addOutputParameter(param);
        param = new ParameterUint("UpdateID");
        iActionBrowseRecordSchedules.addOutputParameter(param);

        iActionBrowseRecordTasks = new Action("BrowseRecordTasks");
        param = new ParameterString("RecordScheduleID", allowedValues);
        iActionBrowseRecordTasks.addInputParameter(param);
        param = new ParameterString("Filter", allowedValues);
        iActionBrowseRecordTasks.addInputParameter(param);
        param = new ParameterUint("StartingIndex");
        iActionBrowseRecordTasks.addInputParameter(param);
        param = new ParameterUint("RequestedCount");
        iActionBrowseRecordTasks.addInputParameter(param);
        param = new ParameterString("SortCriteria", allowedValues);
        iActionBrowseRecordTasks.addInputParameter(param);
        param = new ParameterString("Result", allowedValues);
        iActionBrowseRecordTasks.addOutputParameter(param);
        param = new ParameterUint("NumberReturned");
        iActionBrowseRecordTasks.addOutputParameter(param);
        param = new ParameterUint("TotalMatches");
        iActionBrowseRecordTasks.addOutputParameter(param);
        param = new ParameterUint("UpdateID");
        iActionBrowseRecordTasks.addOutputParameter(param);

        iActionCreateRecordSchedule = new Action("CreateRecordSchedule");
        param = new ParameterString("Elements", allowedValues);
        iActionCreateRecordSchedule.addInputParameter(param);
        param = new ParameterString("RecordScheduleID", allowedValues);
        iActionCreateRecordSchedule.addOutputParameter(param);
        param = new ParameterString("Result", allowedValues);
        iActionCreateRecordSchedule.addOutputParameter(param);
        param = new ParameterUint("UpdateID");
        iActionCreateRecordSchedule.addOutputParameter(param);

        iActionDeleteRecordSchedule = new Action("DeleteRecordSchedule");
        param = new ParameterString("RecordScheduleID", allowedValues);
        iActionDeleteRecordSchedule.addInputParameter(param);

        iActionGetRecordSchedule = new Action("GetRecordSchedule");
        param = new ParameterString("RecordScheduleID", allowedValues);
        iActionGetRecordSchedule.addInputParameter(param);
        param = new ParameterString("Filter", allowedValues);
        iActionGetRecordSchedule.addInputParameter(param);
        param = new ParameterString("Result", allowedValues);
        iActionGetRecordSchedule.addOutputParameter(param);
        param = new ParameterUint("UpdateID");
        iActionGetRecordSchedule.addOutputParameter(param);

        iActionEnableRecordSchedule = new Action("EnableRecordSchedule");
        param = new ParameterString("RecordScheduleID", allowedValues);
        iActionEnableRecordSchedule.addInputParameter(param);

        iActionDisableRecordSchedule = new Action("DisableRecordSchedule");
        param = new ParameterString("RecordScheduleID", allowedValues);
        iActionDisableRecordSchedule.addInputParameter(param);

        iActionDeleteRecordTask = new Action("DeleteRecordTask");
        param = new ParameterString("RecordTaskID", allowedValues);
        iActionDeleteRecordTask.addInputParameter(param);

        iActionGetRecordTask = new Action("GetRecordTask");
        param = new ParameterString("RecordTaskID", allowedValues);
        iActionGetRecordTask.addInputParameter(param);
        param = new ParameterString("Filter", allowedValues);
        iActionGetRecordTask.addInputParameter(param);
        param = new ParameterString("Result", allowedValues);
        iActionGetRecordTask.addOutputParameter(param);
        param = new ParameterUint("UpdateID");
        iActionGetRecordTask.addOutputParameter(param);

        iActionEnableRecordTask = new Action("EnableRecordTask");
        param = new ParameterString("RecordTaskID", allowedValues);
        iActionEnableRecordTask.addInputParameter(param);

        iActionDisableRecordTask = new Action("DisableRecordTask");
        param = new ParameterString("RecordTaskID", allowedValues);
        iActionDisableRecordTask.addInputParameter(param);

        iActionResetRecordTask = new Action("ResetRecordTask");
        param = new ParameterString("RecordTaskID", allowedValues);
        iActionResetRecordTask.addInputParameter(param);

        iActionGetRecordScheduleConflicts = new Action("GetRecordScheduleConflicts");
        param = new ParameterString("RecordScheduleID", allowedValues);
        iActionGetRecordScheduleConflicts.addInputParameter(param);
        param = new ParameterString("RecordScheduleConflictIDList", allowedValues);
        iActionGetRecordScheduleConflicts.addOutputParameter(param);
        param = new ParameterUint("UpdateID");
        iActionGetRecordScheduleConflicts.addOutputParameter(param);

        iActionGetRecordTaskConflicts = new Action("GetRecordTaskConflicts");
        param = new ParameterString("RecordTaskID", allowedValues);
        iActionGetRecordTaskConflicts.addInputParameter(param);
        param = new ParameterString("RecordTaskConflictIDList", allowedValues);
        iActionGetRecordTaskConflicts.addOutputParameter(param);
        param = new ParameterUint("UpdateID");
        iActionGetRecordTaskConflicts.addOutputParameter(param);

        iLastChangeChanged = new PropertyChangeListener();
        iLastChange = new PropertyString("LastChange",
            new PropertyChangeListener() {
                public void notifyChange() {
                    lastChangePropertyChanged();
                }
            }
        );
        addProperty(iLastChange);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetSortCapabilities syncGetSortCapabilities()
    {
        SyncGetSortCapabilitiesUpnpOrgScheduledRecording2 sync = new SyncGetSortCapabilitiesUpnpOrgScheduledRecording2(this);
        beginGetSortCapabilities(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetSortCapabilities(
            sync.getSortCaps(),
            sync.getSortLevelCap()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetSortCapabilities}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetSortCapabilities(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetSortCapabilities, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetSortCapabilities.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetSortCapabilities.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetSortCapabilities} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetSortCapabilities} method.
     * @return the result of the previously invoked action.
     */
    public GetSortCapabilities endGetSortCapabilities(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String sortCaps = Invocation.getOutputString(aAsyncHandle, index++);
        long sortLevelCap = Invocation.getOutputUint(aAsyncHandle, index++);
        return new GetSortCapabilities(
            sortCaps,
            sortLevelCap
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetPropertyList(String aDataTypeID)
    {
        SyncGetPropertyListUpnpOrgScheduledRecording2 sync = new SyncGetPropertyListUpnpOrgScheduledRecording2(this);
        beginGetPropertyList(aDataTypeID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getPropertyList();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetPropertyList}.
     * 
     * @param aDataTypeID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetPropertyList(String aDataTypeID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetPropertyList, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionGetPropertyList.getInputParameter(inIndex++), aDataTypeID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetPropertyList.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetPropertyList} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetPropertyList} method.
     * @return the result of the previously invoked action.
     */
    public String endGetPropertyList(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String propertyList = Invocation.getOutputString(aAsyncHandle, index++);
        return propertyList;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetAllowedValues(String aDataTypeID, String aFilter)
    {
        SyncGetAllowedValuesUpnpOrgScheduledRecording2 sync = new SyncGetAllowedValuesUpnpOrgScheduledRecording2(this);
        beginGetAllowedValues(aDataTypeID, aFilter, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getPropertyInfo();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetAllowedValues}.
     * 
     * @param aDataTypeID
     * @param aFilter
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetAllowedValues(String aDataTypeID, String aFilter, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetAllowedValues, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionGetAllowedValues.getInputParameter(inIndex++), aDataTypeID));
        invocation.addInput(new ArgumentString((ParameterString)iActionGetAllowedValues.getInputParameter(inIndex++), aFilter));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetAllowedValues.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetAllowedValues} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetAllowedValues} method.
     * @return the result of the previously invoked action.
     */
    public String endGetAllowedValues(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String propertyInfo = Invocation.getOutputString(aAsyncHandle, index++);
        return propertyInfo;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetStateUpdateID()
    {
        SyncGetStateUpdateIDUpnpOrgScheduledRecording2 sync = new SyncGetStateUpdateIDUpnpOrgScheduledRecording2(this);
        beginGetStateUpdateID(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getId();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetStateUpdateID}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetStateUpdateID(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetStateUpdateID, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetStateUpdateID.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetStateUpdateID} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetStateUpdateID} method.
     * @return the result of the previously invoked action.
     */
    public long endGetStateUpdateID(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long id = Invocation.getOutputUint(aAsyncHandle, index++);
        return id;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public BrowseRecordSchedules syncBrowseRecordSchedules(String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria)
    {
        SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2 sync = new SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2(this);
        beginBrowseRecordSchedules(aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new BrowseRecordSchedules(
            sync.getResult(),
            sync.getNumberReturned(),
            sync.getTotalMatches(),
            sync.getUpdateID()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endBrowseRecordSchedules}.
     * 
     * @param aFilter
     * @param aStartingIndex
     * @param aRequestedCount
     * @param aSortCriteria
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginBrowseRecordSchedules(String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionBrowseRecordSchedules, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionBrowseRecordSchedules.getInputParameter(inIndex++), aFilter));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionBrowseRecordSchedules.getInputParameter(inIndex++), aStartingIndex));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionBrowseRecordSchedules.getInputParameter(inIndex++), aRequestedCount));
        invocation.addInput(new ArgumentString((ParameterString)iActionBrowseRecordSchedules.getInputParameter(inIndex++), aSortCriteria));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionBrowseRecordSchedules.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordSchedules.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordSchedules.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordSchedules.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginBrowseRecordSchedules} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginBrowseRecordSchedules} method.
     * @return the result of the previously invoked action.
     */
    public BrowseRecordSchedules endBrowseRecordSchedules(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String result = Invocation.getOutputString(aAsyncHandle, index++);
        long numberReturned = Invocation.getOutputUint(aAsyncHandle, index++);
        long totalMatches = Invocation.getOutputUint(aAsyncHandle, index++);
        long updateID = Invocation.getOutputUint(aAsyncHandle, index++);
        return new BrowseRecordSchedules(
            result,
            numberReturned,
            totalMatches,
            updateID
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public BrowseRecordTasks syncBrowseRecordTasks(String aRecordScheduleID, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria)
    {
        SyncBrowseRecordTasksUpnpOrgScheduledRecording2 sync = new SyncBrowseRecordTasksUpnpOrgScheduledRecording2(this);
        beginBrowseRecordTasks(aRecordScheduleID, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new BrowseRecordTasks(
            sync.getResult(),
            sync.getNumberReturned(),
            sync.getTotalMatches(),
            sync.getUpdateID()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endBrowseRecordTasks}.
     * 
     * @param aRecordScheduleID
     * @param aFilter
     * @param aStartingIndex
     * @param aRequestedCount
     * @param aSortCriteria
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginBrowseRecordTasks(String aRecordScheduleID, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionBrowseRecordTasks, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionBrowseRecordTasks.getInputParameter(inIndex++), aRecordScheduleID));
        invocation.addInput(new ArgumentString((ParameterString)iActionBrowseRecordTasks.getInputParameter(inIndex++), aFilter));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionBrowseRecordTasks.getInputParameter(inIndex++), aStartingIndex));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionBrowseRecordTasks.getInputParameter(inIndex++), aRequestedCount));
        invocation.addInput(new ArgumentString((ParameterString)iActionBrowseRecordTasks.getInputParameter(inIndex++), aSortCriteria));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionBrowseRecordTasks.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordTasks.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordTasks.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionBrowseRecordTasks.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginBrowseRecordTasks} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginBrowseRecordTasks} method.
     * @return the result of the previously invoked action.
     */
    public BrowseRecordTasks endBrowseRecordTasks(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String result = Invocation.getOutputString(aAsyncHandle, index++);
        long numberReturned = Invocation.getOutputUint(aAsyncHandle, index++);
        long totalMatches = Invocation.getOutputUint(aAsyncHandle, index++);
        long updateID = Invocation.getOutputUint(aAsyncHandle, index++);
        return new BrowseRecordTasks(
            result,
            numberReturned,
            totalMatches,
            updateID
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public CreateRecordSchedule syncCreateRecordSchedule(String aElements)
    {
        SyncCreateRecordScheduleUpnpOrgScheduledRecording2 sync = new SyncCreateRecordScheduleUpnpOrgScheduledRecording2(this);
        beginCreateRecordSchedule(aElements, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new CreateRecordSchedule(
            sync.getRecordScheduleID(),
            sync.getResult(),
            sync.getUpdateID()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endCreateRecordSchedule}.
     * 
     * @param aElements
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginCreateRecordSchedule(String aElements, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionCreateRecordSchedule, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionCreateRecordSchedule.getInputParameter(inIndex++), aElements));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionCreateRecordSchedule.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionCreateRecordSchedule.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionCreateRecordSchedule.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginCreateRecordSchedule} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginCreateRecordSchedule} method.
     * @return the result of the previously invoked action.
     */
    public CreateRecordSchedule endCreateRecordSchedule(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String recordScheduleID = Invocation.getOutputString(aAsyncHandle, index++);
        String result = Invocation.getOutputString(aAsyncHandle, index++);
        long updateID = Invocation.getOutputUint(aAsyncHandle, index++);
        return new CreateRecordSchedule(
            recordScheduleID,
            result,
            updateID
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncDeleteRecordSchedule(String aRecordScheduleID)
    {
        SyncDeleteRecordScheduleUpnpOrgScheduledRecording2 sync = new SyncDeleteRecordScheduleUpnpOrgScheduledRecording2(this);
        beginDeleteRecordSchedule(aRecordScheduleID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endDeleteRecordSchedule}.
     * 
     * @param aRecordScheduleID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginDeleteRecordSchedule(String aRecordScheduleID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionDeleteRecordSchedule, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionDeleteRecordSchedule.getInputParameter(inIndex++), aRecordScheduleID));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDeleteRecordSchedule} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginDeleteRecordSchedule} method.
     */
    public void endDeleteRecordSchedule(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetRecordSchedule syncGetRecordSchedule(String aRecordScheduleID, String aFilter)
    {
        SyncGetRecordScheduleUpnpOrgScheduledRecording2 sync = new SyncGetRecordScheduleUpnpOrgScheduledRecording2(this);
        beginGetRecordSchedule(aRecordScheduleID, aFilter, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetRecordSchedule(
            sync.getResult(),
            sync.getUpdateID()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetRecordSchedule}.
     * 
     * @param aRecordScheduleID
     * @param aFilter
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetRecordSchedule(String aRecordScheduleID, String aFilter, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetRecordSchedule, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionGetRecordSchedule.getInputParameter(inIndex++), aRecordScheduleID));
        invocation.addInput(new ArgumentString((ParameterString)iActionGetRecordSchedule.getInputParameter(inIndex++), aFilter));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetRecordSchedule.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetRecordSchedule.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetRecordSchedule} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetRecordSchedule} method.
     * @return the result of the previously invoked action.
     */
    public GetRecordSchedule endGetRecordSchedule(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String result = Invocation.getOutputString(aAsyncHandle, index++);
        long updateID = Invocation.getOutputUint(aAsyncHandle, index++);
        return new GetRecordSchedule(
            result,
            updateID
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncEnableRecordSchedule(String aRecordScheduleID)
    {
        SyncEnableRecordScheduleUpnpOrgScheduledRecording2 sync = new SyncEnableRecordScheduleUpnpOrgScheduledRecording2(this);
        beginEnableRecordSchedule(aRecordScheduleID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endEnableRecordSchedule}.
     * 
     * @param aRecordScheduleID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginEnableRecordSchedule(String aRecordScheduleID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionEnableRecordSchedule, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionEnableRecordSchedule.getInputParameter(inIndex++), aRecordScheduleID));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginEnableRecordSchedule} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginEnableRecordSchedule} method.
     */
    public void endEnableRecordSchedule(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncDisableRecordSchedule(String aRecordScheduleID)
    {
        SyncDisableRecordScheduleUpnpOrgScheduledRecording2 sync = new SyncDisableRecordScheduleUpnpOrgScheduledRecording2(this);
        beginDisableRecordSchedule(aRecordScheduleID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endDisableRecordSchedule}.
     * 
     * @param aRecordScheduleID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginDisableRecordSchedule(String aRecordScheduleID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionDisableRecordSchedule, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionDisableRecordSchedule.getInputParameter(inIndex++), aRecordScheduleID));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDisableRecordSchedule} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginDisableRecordSchedule} method.
     */
    public void endDisableRecordSchedule(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncDeleteRecordTask(String aRecordTaskID)
    {
        SyncDeleteRecordTaskUpnpOrgScheduledRecording2 sync = new SyncDeleteRecordTaskUpnpOrgScheduledRecording2(this);
        beginDeleteRecordTask(aRecordTaskID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endDeleteRecordTask}.
     * 
     * @param aRecordTaskID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginDeleteRecordTask(String aRecordTaskID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionDeleteRecordTask, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionDeleteRecordTask.getInputParameter(inIndex++), aRecordTaskID));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDeleteRecordTask} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginDeleteRecordTask} method.
     */
    public void endDeleteRecordTask(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetRecordTask syncGetRecordTask(String aRecordTaskID, String aFilter)
    {
        SyncGetRecordTaskUpnpOrgScheduledRecording2 sync = new SyncGetRecordTaskUpnpOrgScheduledRecording2(this);
        beginGetRecordTask(aRecordTaskID, aFilter, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetRecordTask(
            sync.getResult(),
            sync.getUpdateID()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetRecordTask}.
     * 
     * @param aRecordTaskID
     * @param aFilter
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetRecordTask(String aRecordTaskID, String aFilter, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetRecordTask, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionGetRecordTask.getInputParameter(inIndex++), aRecordTaskID));
        invocation.addInput(new ArgumentString((ParameterString)iActionGetRecordTask.getInputParameter(inIndex++), aFilter));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetRecordTask.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetRecordTask.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetRecordTask} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetRecordTask} method.
     * @return the result of the previously invoked action.
     */
    public GetRecordTask endGetRecordTask(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String result = Invocation.getOutputString(aAsyncHandle, index++);
        long updateID = Invocation.getOutputUint(aAsyncHandle, index++);
        return new GetRecordTask(
            result,
            updateID
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncEnableRecordTask(String aRecordTaskID)
    {
        SyncEnableRecordTaskUpnpOrgScheduledRecording2 sync = new SyncEnableRecordTaskUpnpOrgScheduledRecording2(this);
        beginEnableRecordTask(aRecordTaskID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endEnableRecordTask}.
     * 
     * @param aRecordTaskID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginEnableRecordTask(String aRecordTaskID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionEnableRecordTask, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionEnableRecordTask.getInputParameter(inIndex++), aRecordTaskID));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginEnableRecordTask} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginEnableRecordTask} method.
     */
    public void endEnableRecordTask(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncDisableRecordTask(String aRecordTaskID)
    {
        SyncDisableRecordTaskUpnpOrgScheduledRecording2 sync = new SyncDisableRecordTaskUpnpOrgScheduledRecording2(this);
        beginDisableRecordTask(aRecordTaskID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endDisableRecordTask}.
     * 
     * @param aRecordTaskID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginDisableRecordTask(String aRecordTaskID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionDisableRecordTask, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionDisableRecordTask.getInputParameter(inIndex++), aRecordTaskID));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDisableRecordTask} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginDisableRecordTask} method.
     */
    public void endDisableRecordTask(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncResetRecordTask(String aRecordTaskID)
    {
        SyncResetRecordTaskUpnpOrgScheduledRecording2 sync = new SyncResetRecordTaskUpnpOrgScheduledRecording2(this);
        beginResetRecordTask(aRecordTaskID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endResetRecordTask}.
     * 
     * @param aRecordTaskID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginResetRecordTask(String aRecordTaskID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionResetRecordTask, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionResetRecordTask.getInputParameter(inIndex++), aRecordTaskID));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginResetRecordTask} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginResetRecordTask} method.
     */
    public void endResetRecordTask(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetRecordScheduleConflicts syncGetRecordScheduleConflicts(String aRecordScheduleID)
    {
        SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2 sync = new SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2(this);
        beginGetRecordScheduleConflicts(aRecordScheduleID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetRecordScheduleConflicts(
            sync.getRecordScheduleConflictIDList(),
            sync.getUpdateID()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetRecordScheduleConflicts}.
     * 
     * @param aRecordScheduleID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetRecordScheduleConflicts(String aRecordScheduleID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetRecordScheduleConflicts, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionGetRecordScheduleConflicts.getInputParameter(inIndex++), aRecordScheduleID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetRecordScheduleConflicts.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetRecordScheduleConflicts.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetRecordScheduleConflicts} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetRecordScheduleConflicts} method.
     * @return the result of the previously invoked action.
     */
    public GetRecordScheduleConflicts endGetRecordScheduleConflicts(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String recordScheduleConflictIDList = Invocation.getOutputString(aAsyncHandle, index++);
        long updateID = Invocation.getOutputUint(aAsyncHandle, index++);
        return new GetRecordScheduleConflicts(
            recordScheduleConflictIDList,
            updateID
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetRecordTaskConflicts syncGetRecordTaskConflicts(String aRecordTaskID)
    {
        SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2 sync = new SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2(this);
        beginGetRecordTaskConflicts(aRecordTaskID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetRecordTaskConflicts(
            sync.getRecordTaskConflictIDList(),
            sync.getUpdateID()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetRecordTaskConflicts}.
     * 
     * @param aRecordTaskID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetRecordTaskConflicts(String aRecordTaskID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetRecordTaskConflicts, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionGetRecordTaskConflicts.getInputParameter(inIndex++), aRecordTaskID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetRecordTaskConflicts.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetRecordTaskConflicts.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetRecordTaskConflicts} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetRecordTaskConflicts} method.
     * @return the result of the previously invoked action.
     */
    public GetRecordTaskConflicts endGetRecordTaskConflicts(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String recordTaskConflictIDList = Invocation.getOutputString(aAsyncHandle, index++);
        long updateID = Invocation.getOutputUint(aAsyncHandle, index++);
        return new GetRecordTaskConflicts(
            recordTaskConflictIDList,
            updateID
        );
    }
        
    /**
     * Set a delegate to be run when the LastChange state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgScheduledRecording2 instance will not overlap.
     *
     * @param aLastChangeChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyLastChangeChanged(IPropertyChangeListener aLastChangeChanged)
    {
        synchronized (iPropertyLock)
        {
            iLastChangeChanged = aLastChangeChanged;
        }
    }

    private void lastChangePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iLastChangeChanged);
        }
    }

    /**
     * Query the value of the LastChange property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the LastChange property.
     */
    public String getPropertyLastChange()
    {
        propertyReadLock();
        String val = iLastChange.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Dispose of this control point proxy.
     * Must be called for each class instance.
     * Must be called before <tt>Library.close()</tt>.
     */
    public void dispose()
    {
        synchronized (this)
        {
            if (iHandle == 0)
            {
                return;
            }
            disposeProxy();
            iHandle = 0;
            iActionGetSortCapabilities.destroy();
            iActionGetPropertyList.destroy();
            iActionGetAllowedValues.destroy();
            iActionGetStateUpdateID.destroy();
            iActionBrowseRecordSchedules.destroy();
            iActionBrowseRecordTasks.destroy();
            iActionCreateRecordSchedule.destroy();
            iActionDeleteRecordSchedule.destroy();
            iActionGetRecordSchedule.destroy();
            iActionEnableRecordSchedule.destroy();
            iActionDisableRecordSchedule.destroy();
            iActionDeleteRecordTask.destroy();
            iActionGetRecordTask.destroy();
            iActionEnableRecordTask.destroy();
            iActionDisableRecordTask.destroy();
            iActionResetRecordTask.destroy();
            iActionGetRecordScheduleConflicts.destroy();
            iActionGetRecordTaskConflicts.destroy();
            iLastChange.destroy();
        }
    }
}

